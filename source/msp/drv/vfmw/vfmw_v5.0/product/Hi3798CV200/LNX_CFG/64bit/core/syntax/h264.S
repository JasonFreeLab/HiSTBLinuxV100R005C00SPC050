#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"h264.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	IsSTRefFlg
	.type	IsSTRefFlg, %function
IsSTRefFlg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19]
	ldr	x19, [sp, 16]
	and	w0, w0, 16776960
	cmp	w0, 65536
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	IsSTRefFlg, .-IsSTRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IsLTRefFlg
	.type	IsLTRefFlg, %function
IsLTRefFlg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19]
	ldr	x19, [sp, 16]
	and	w0, w0, 16776960
	cmp	w0, 256
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	IsLTRefFlg, .-IsLTRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	compare_pic_by_pic_num_desc
	.type	compare_pic_by_pic_num_desc, %function
compare_pic_by_pic_num_desc:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19]
	mov	w3, 1
	ldr	x2, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	w1, [x0, 8]
	ldr	w2, [x2, 8]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	csetm	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	compare_pic_by_pic_num_desc, .-compare_pic_by_pic_num_desc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	compare_pic_by_lt_pic_num_asc
	.type	compare_pic_by_lt_pic_num_asc, %function
compare_pic_by_lt_pic_num_asc:
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
	ldr	w1, [x0, 4]
	ldr	w2, [x2, 4]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	cset	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	compare_pic_by_lt_pic_num_asc, .-compare_pic_by_lt_pic_num_asc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	compare_fs_by_frame_num_desc
	.type	compare_fs_by_frame_num_desc, %function
compare_fs_by_frame_num_desc:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19]
	mov	w3, 1
	ldr	x2, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	w1, [x0, 656]
	ldr	w2, [x2, 656]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	csetm	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	compare_fs_by_frame_num_desc, .-compare_fs_by_frame_num_desc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	compare_fs_by_lt_pic_idx_asc
	.type	compare_fs_by_lt_pic_idx_asc, %function
compare_fs_by_lt_pic_idx_asc:
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
	ldr	w1, [x0, 660]
	ldr	w2, [x2, 660]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	cset	w0, hi
	csel	w0, w0, w3, cs
	ret
	.size	compare_fs_by_lt_pic_idx_asc, .-compare_fs_by_lt_pic_idx_asc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	compare_pic_by_poc_asc
	.type	compare_pic_by_poc_asc, %function
compare_pic_by_poc_asc:
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
	ldr	w1, [x0, 12]
	ldr	w2, [x2, 12]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	cset	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	compare_pic_by_poc_asc, .-compare_pic_by_poc_asc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	compare_pic_by_poc_desc
	.type	compare_pic_by_poc_desc, %function
compare_pic_by_poc_desc:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19]
	mov	w3, 1
	ldr	x2, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	w1, [x0, 12]
	ldr	w2, [x2, 12]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	csetm	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	compare_pic_by_poc_desc, .-compare_pic_by_poc_desc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	compare_fs_by_poc_asc
	.type	compare_fs_by_poc_asc, %function
compare_fs_by_poc_asc:
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
	ldr	w1, [x0, 664]
	ldr	w2, [x2, 664]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	cset	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	compare_fs_by_poc_asc, .-compare_fs_by_poc_asc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	compare_fs_by_poc_desc
	.type	compare_fs_by_poc_desc, %function
compare_fs_by_poc_desc:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19]
	mov	w3, 1
	ldr	x2, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	w1, [x0, 664]
	ldr	w2, [x2, 664]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	csetm	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	compare_fs_by_poc_desc, .-compare_fs_by_poc_desc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	SetFrmRepeatCount.part.3, %function
SetFrmRepeatCount.part.3:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	add	x3, x19, 65536
	add	x19, x19, 24576
	ldr	w2, [x3, 1664]
	ldr	w1, [x19, 3704]
	ldr	w0, [x3, 1660]
	add	w2, w1, w2, lsr 1
	lsr	w0, w0, 1
	add	w4, w2, 1
	cmp	w0, w4
	bcc	.L28
	sub	w0, w0, #1
	sub	w0, w0, w2
	cmp	w0, 1
	bls	.L29
	mov	w0, 2
	str	w0, [x20, 16]
	ldr	w0, [x3, 1664]
	add	w0, w0, 4
	str	w0, [x3, 1664]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L28:
	str	wzr, [x20, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L29:
	mov	w0, 1
	str	w0, [x20, 16]
	ldr	w0, [x3, 1664]
	add	w0, w0, 2
	str	w0, [x3, 1664]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SetFrmRepeatCount.part.3, .-SetFrmRepeatCount.part.3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	DumpList.part.7, %function
DumpList.part.7:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	add	x24, x20, 20480
	mov	w21, 0
	bl	_mcount
	ldr	x23, .LC3
	add	x25, x24, 1624
.L33:
	ldr	w0, [x25]
	cbz	w0, .L37
	uxtw	x0, w21
	mov	w19, 0
	lsl	x22, x0, 5
	add	x22, x22, x0
	.p2align 2
.L34:
	add	x4, x22, x19, uxtw
	mov	w3, w19
	mov	w2, w21
	mov	x1, x23
	add	x4, x20, x4, lsl 3
	mov	w0, 13
	add	w19, w19, 1
	ldr	x4, [x4, 28696]
	ldr	x4, [x4, 40]
	ldr	w5, [x4, 664]
	ldr	w4, [x4, 652]
	bl	dprint_vfmw
	ldr	w0, [x25]
	cmp	w19, w0
	bcc	.L34
.L37:
	add	w21, w21, 1
	add	x25, x25, 4
	cmp	w21, 2
	bne	.L33
	ldr	w0, [x24, 1624]
	cbnz	w0, .L65
.L38:
	ldr	w0, [x24, 1628]
	cbnz	w0, .L66
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L66:
	ldr	x1, .LC15
	mov	w0, 13
	mov	w19, 0
	bl	dprint_vfmw
	ldr	w0, [x24, 1628]
	cbz	w0, .L53
	ldr	x23, .LC9
	ldr	x21, .LC13
	ldr	x22, .LC11
	b	.L58
	.p2align 3
.L67:
	cmp	w0, 2
	cbz	w0, .L50
	mov	x1, x21
	mov	w0, 13
	bne	.L48
	ldr	x2, [x2, 40]
	ldr	w2, [x2, 664]
	bl	dprint_vfmw
.L48:
	ldr	w0, [x24, 1628]
	add	w19, w19, 1
	cmp	w19, w0
	bcs	.L53
.L58:
	add	x0, x20, x19, uxtw 3
	ldr	x2, [x0, 28960]
	ldrb	w0, [x2]
	cmp	w0, 1
	bne	.L67
	ldr	x2, [x2, 40]
	mov	x1, x22
	mov	w0, 13
	add	w19, w19, 1
	ldr	w2, [x2, 664]
	bl	dprint_vfmw
	ldr	w0, [x24, 1628]
	cmp	w19, w0
	bcc	.L58
.L53:
	ldr	x1, .LC7
	mov	w0, 13
	bl	dprint_vfmw
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L50:
	ldr	x2, [x2, 40]
	mov	x1, x23
	mov	w0, 13
	ldr	w2, [x2, 664]
	bl	dprint_vfmw
	b	.L48
	.p2align 3
.L65:
	ldr	x1, .LC5
	mov	w0, 13
	mov	w19, 0
	bl	dprint_vfmw
	ldr	w0, [x24, 1624]
	cbz	w0, .L45
	ldr	x23, .LC9
	ldr	x21, .LC13
	ldr	x22, .LC11
	b	.L59
	.p2align 3
.L68:
	cmp	w0, 2
	cbz	w0, .L42
	mov	x1, x21
	mov	w0, 13
	bne	.L40
	ldr	x2, [x2, 40]
	ldr	w2, [x2, 664]
	bl	dprint_vfmw
.L40:
	ldr	w0, [x24, 1624]
	add	w19, w19, 1
	cmp	w19, w0
	bcs	.L45
.L59:
	add	x0, x20, x19, uxtw 3
	ldr	x2, [x0, 28696]
	ldrb	w0, [x2]
	cmp	w0, 1
	bne	.L68
	ldr	x2, [x2, 40]
	mov	x1, x22
	mov	w0, 13
	add	w19, w19, 1
	ldr	w2, [x2, 664]
	bl	dprint_vfmw
	ldr	w0, [x24, 1624]
	cmp	w19, w0
	bcc	.L59
.L45:
	ldr	x1, .LC7
	mov	w0, 13
	bl	dprint_vfmw
	b	.L38
	.p2align 3
.L42:
	ldr	x2, [x2, 40]
	mov	x1, x23
	mov	w0, 13
	ldr	w2, [x2, 664]
	bl	dprint_vfmw
	b	.L40
	.size	DumpList.part.7, .-DumpList.part.7
	.align	3
.LC3:
	.xword	.LC2
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	CombinePacket.part.13, %function
CombinePacket.part.13:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC17
	mov	w0, 7
	bl	dprint_vfmw
	ldr	x2, [x19, 632]
	mov	w0, 7
	ldr	x1, .LC19
	ldp	w5, w3, [x2, 48]
	ldr	w4, [x2, 16]
	ldr	w2, [x2, 20]
	bl	dprint_vfmw
	ldr	x1, [x19, 632]
	ldr	x3, .LC20
	ldr	w2, [x1, 16]
	ldr	x0, [x1, 40]
	ldr	x3, [x3, 104]
	ldr	x1, [x1, 8]
	sub	x0, x0, x2
	blr	x3
	ldr	x2, [x19, 632]
	mov	w4, 1
	ldr	x1, .LC22
	mov	w0, 7
	ldr	w3, [x2, 68]
	ldr	w20, [x2, 36]
	str	w3, [x2, 36]
	ldr	x2, [x19, 632]
	str	wzr, [x2, 28]
	ldr	x2, [x19, 632]
	ldr	w5, [x2, 16]
	ldr	x3, [x2, 40]
	sub	x3, x3, x5
	str	x3, [x2, 8]
	ldr	x2, [x19, 632]
	ldr	w5, [x2, 16]
	ldr	w3, [x2, 52]
	sub	w3, w3, w5
	str	w3, [x2, 20]
	ldr	x2, [x19, 632]
	ldr	w5, [x2, 16]
	ldr	w3, [x2, 48]
	add	w3, w5, w3
	str	w3, [x2, 16]
	ldr	x2, [x19, 632]
	str	w4, [x2, 76]
	ldr	x2, [x19, 632]
	ldp	w3, w2, [x2, 16]
	bl	dprint_vfmw
	add	x0, x19, 65536
	mov	w1, w20
	ldr	w0, [x0, 1644]
	bl	SM_ReleaseStreamSeg
	ldr	x0, [x19, 632]
	str	xzr, [x0, 40]
	ldr	x0, [x19, 632]
	str	wzr, [x0, 60]
	ldr	x0, [x19, 632]
	str	wzr, [x0, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CombinePacket.part.13, .-CombinePacket.part.13
	.align	3
.LC17:
	.xword	.LC16
	.align	3
.LC19:
	.xword	.LC18
	.align	3
.LC20:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC22:
	.xword	.LC21
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ue_v
	.type	ue_v, %function
ue_v:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x21, x22, 12288
	mov	x23, x1
	add	x21, x21, 2600
	bl	_mcount
	mov	w1, 32
	mov	x0, x21
	bl	BsShow
	mov	w20, w0
	bl	ZerosMS_32
	cmp	w0, 15
	mov	w19, w0
	bls	.L74
	cmp	w0, 31
	bls	.L75
	add	x0, x22, 65536
	mov	w1, 1
	mov	w20, -1
	mov	w19, 32
	str	w1, [x0, 1584]
.L72:
	ldr	x4, [x22, 632]
	mov	w3, w20
	ldr	x1, .LC24
	mov	x2, x23
	mov	w0, 21
	ldr	w5, [x4, 72]
	add	w19, w5, w19
	str	w19, [x4, 72]
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L74:
	lsl	w19, w0, 1
	mov	w2, 32
	add	w19, w19, 1
	mov	x0, x21
	sub	w2, w2, w19
	mov	w1, w19
	lsr	w20, w20, w2
	sub	w20, w20, #1
	bl	BsSkip
	b	.L72
	.p2align 3
.L75:
	mov	w1, w0
	mov	x0, x21
	add	w24, w19, 1
	lsl	w19, w19, 1
	bl	BsSkip
	add	w19, w19, 1
	mov	w1, w24
	mov	x0, x21
	bl	BsShow
	sub	w20, w0, #1
	mov	w1, w24
	mov	x0, x21
	bl	BsSkip
	b	.L72
	.size	ue_v, .-ue_v
	.align	3
.LC24:
	.xword	.LC23
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	se_v
	.type	se_v, %function
se_v:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x21, x22, 12288
	mov	x23, x1
	add	x21, x21, 2600
	bl	_mcount
	mov	w1, 32
	mov	x0, x21
	bl	BsShow
	mov	w20, w0
	bl	ZerosMS_32
	cmp	w0, 15
	mov	w19, w0
	bhi	.L77
	lsl	w19, w0, 1
	mov	w2, 32
	add	w19, w19, 1
	mov	x0, x21
	sub	w2, w2, w19
	mov	w1, w19
	lsr	w20, w20, w2
	and	w2, w20, 1
	lsr	w20, w20, 1
	cmp	w2, wzr
	csneg	w20, w20, w20, eq
	bl	BsSkip
.L79:
	ldr	x4, [x22, 632]
	mov	w3, w20
	ldr	x1, .LC25
	mov	x2, x23
	mov	w0, 21
	ldr	w5, [x4, 72]
	add	w19, w5, w19
	str	w19, [x4, 72]
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L77:
	cmp	w0, 31
	bls	.L86
	add	x0, x22, 65536
	mov	w1, 1
	mov	w20, 2147483647
	mov	w19, 32
	str	w1, [x0, 1584]
	b	.L79
	.p2align 3
.L86:
	mov	w1, w0
	mov	x0, x21
	bl	BsSkip
	mov	w1, w19
	mov	x0, x21
	lsl	w19, w19, 1
	bl	BsGet
	mov	w20, w0
	mov	w1, 1
	mov	x0, x21
	add	w19, w19, 1
	bl	BsGet
	and	w0, w0, 1
	cmp	w0, wzr
	csneg	w20, w20, w20, eq
	b	.L79
	.size	se_v, .-se_v
	.align	3
.LC25:
	.xword	.LC23
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	u_v
	.type	u_v, %function
u_v:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x22, x2
	mov	w19, w1
	bl	_mcount
	add	x0, x21, 12288
	mov	w1, w19
	add	x0, x0, 2600
	bl	BsGet
	mov	w20, w0
	ldr	x4, [x21, 632]
	mov	w3, w0
	ldr	x1, .LC26
	mov	x2, x22
	mov	w0, 21
	ldr	w5, [x4, 72]
	add	w19, w5, w19
	str	w19, [x4, 72]
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	u_v, .-u_v
	.align	3
.LC26:
	.xword	.LC23
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	u_1
	.type	u_1, %function
u_1:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	add	x0, x20, 12288
	mov	w1, 1
	add	x0, x0, 2600
	bl	BsGet
	mov	w19, w0
	ldr	x5, [x20, 632]
	mov	w3, w0
	ldr	x1, .LC27
	mov	x2, x21
	mov	w0, 21
	ldr	w4, [x5, 72]
	add	w4, w4, 1
	str	w4, [x5, 72]
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	u_1, .-u_1
	.align	3
.LC27:
	.xword	.LC23
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_IsEosNal
	.type	H264_IsEosNal, %function
H264_IsEosNal:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 12288
	bl	_mcount
	add	x19, x19, 2600
	mov	w1, 32
	mov	x0, x19
	bl	BsGet
	mov	w20, w0
	mov	w1, 32
	mov	x0, x19
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
	.size	H264_IsEosNal, .-H264_IsEosNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetMinPOC
	.type	GetMinPOC, %function
GetMinPOC:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x2
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	str	wzr, [x21]
	add	x1, x20, 24576
	mov	w0, 2147483647
	str	w0, [x19]
	ldr	w0, [x1, 3704]
	ldr	w2, [x1, 3708]
	cmp	w2, w0
	bls	.L91
	mov	w2, w0
	str	w0, [x1, 3708]
.L91:
	mov	w0, 0
	cbz	w2, .L90
	.p2align 2
.L98:
	add	x3, x20, x0, uxtw 3
	ldr	w5, [x19]
	ldr	x3, [x3, 27896]
	ldr	w4, [x3, 664]
	cmp	w5, w4
	ble	.L93
	ldrb	w3, [x3, 4]
	cbz	w3, .L93
	str	w4, [x19]
	str	w0, [x21]
.L93:
	ldr	w3, [x1, 3708]
	add	w0, w0, 1
	cmp	w3, w0
	bhi	.L98
.L90:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	GetMinPOC, .-GetMinPOC
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetMinPOCInDPB
	.type	GetMinPOCInDPB, %function
GetMinPOCInDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x2
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	str	wzr, [x21]
	add	x1, x20, 24576
	mov	w0, 2147483647
	str	w0, [x19]
	ldr	w0, [x1, 3704]
	ldr	w2, [x1, 3708]
	cmp	w2, w0
	bls	.L102
	mov	w2, w0
	str	w0, [x1, 3708]
.L102:
	mov	w0, 0
	cbz	w2, .L101
	.p2align 2
.L107:
	add	x3, x20, x0, uxtw 3
	ldr	w4, [x19]
	ldr	x3, [x3, 27896]
	ldr	w3, [x3, 664]
	cmp	w4, w3
	ble	.L104
	str	w3, [x19]
	str	w0, [x21]
.L104:
	ldr	w3, [x1, 3708]
	add	w0, w0, 1
	cmp	w3, w0
	bhi	.L107
.L101:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	GetMinPOCInDPB, .-GetMinPOCInDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetMaxPOC
	.type	GetMaxPOC, %function
GetMaxPOC:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x2
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	str	wzr, [x21]
	add	x1, x20, 24576
	str	wzr, [x19]
	ldr	w0, [x1, 3704]
	ldr	w2, [x1, 3708]
	cmp	w2, w0
	bls	.L110
	mov	w2, w0
	str	w0, [x1, 3708]
.L110:
	mov	w0, 0
	cbz	w2, .L109
	.p2align 2
.L117:
	add	x3, x20, x0, uxtw 3
	ldr	w5, [x19]
	ldr	x3, [x3, 27896]
	ldr	w4, [x3, 664]
	cmp	w5, w4
	bge	.L112
	ldrb	w3, [x3, 4]
	cbz	w3, .L112
	str	w4, [x19]
	str	w0, [x21]
.L112:
	ldr	w3, [x1, 3708]
	add	w0, w0, 1
	cmp	w3, w0
	bhi	.L117
.L109:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	GetMaxPOC, .-GetMaxPOC
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FrameStoreRefFlg
	.type	FrameStoreRefFlg, %function
FrameStoreRefFlg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x19, 2]
	ldr	x19, [sp, 16]
	cmp	w0, wzr
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	FrameStoreRefFlg, .-FrameStoreRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ShortTermRefFlg
	.type	ShortTermRefFlg, %function
ShortTermRefFlg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w1, [x19, 2]
	cmp	w1, 3
	beq	.L137
	tbnz	x1, 0, .L138
.L125:
	mov	w0, 0
	tbnz	x1, 1, .L126
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L138:
	ldr	w0, [x19, 744]
	and	w0, w0, 16776960
	cmp	w0, 65536
	bne	.L125
.L130:
	mov	w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L137:
	ldr	w0, [x19, 696]
	and	w0, w0, 16776960
	cmp	w0, 65536
	beq	.L130
	ldr	w0, [x19, 744]
	and	w0, w0, 16776960
	cmp	w0, 65536
	beq	.L130
.L126:
	ldr	w0, [x19, 792]
	ldr	x19, [sp, 16]
	and	w0, w0, 16776960
	cmp	w0, 65536
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	ShortTermRefFlg, .-ShortTermRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	LongTermRefFlg
	.type	LongTermRefFlg, %function
LongTermRefFlg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w1, [x19, 2]
	cmp	w1, 3
	beq	.L155
	tbnz	x1, 0, .L156
.L143:
	mov	w0, 0
	tbnz	x1, 1, .L144
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L156:
	ldr	w0, [x19, 744]
	and	w0, w0, 16776960
	cmp	w0, 256
	bne	.L143
.L148:
	mov	w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L155:
	ldr	w0, [x19, 696]
	and	w0, w0, 16776960
	cmp	w0, 256
	beq	.L148
	ldr	w0, [x19, 744]
	and	w0, w0, 16776960
	cmp	w0, 256
	beq	.L148
.L144:
	ldr	w0, [x19, 792]
	ldr	x19, [sp, 16]
	and	w0, w0, 16776960
	cmp	w0, 256
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	LongTermRefFlg, .-LongTermRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UpdateLTReflist
	.type	UpdateLTReflist, %function
UpdateLTReflist:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x24, x22, 24576
	bl	_mcount
	ldr	w0, [x24, 3708]
	cbz	w0, .L164
	sub	w23, w0, #1
	add	x20, x24, 3320
	add	x23, x23, 3488
	mov	w19, 0
	add	x23, x22, x23, lsl 3
	.p2align 2
.L160:
	ldr	x21, [x20]
	add	x20, x20, 8
	mov	x0, x21
	bl	LongTermRefFlg
	add	x1, x22, x19, uxtw 3
	cmp	x20, x23
	cbz	w0, .L159
	add	w19, w19, 1
	str	x21, [x1, 28152]
.L159:
	bne	.L160
.L158:
	ldr	w1, [x24, 3704]
	str	w19, [x24, 3716]
	cmp	w1, w19
	bls	.L157
	.p2align 2
.L167:
	add	x0, x22, x19, uxtw 3
	add	w19, w19, 1
	cmp	w19, w1
	str	xzr, [x0, 28152]
	bne	.L167
.L157:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L164:
	mov	w19, 0
	b	.L158
	.size	UpdateLTReflist, .-UpdateLTReflist
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UpdateReflist
	.type	UpdateReflist, %function
UpdateReflist:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x24, x22, 24576
	bl	_mcount
	ldr	w0, [x24, 3708]
	cbz	w0, .L178
	sub	w23, w0, #1
	add	x20, x24, 3320
	add	x23, x23, 3488
	mov	w19, 0
	add	x23, x22, x23, lsl 3
	.p2align 2
.L174:
	ldr	x21, [x20]
	add	x20, x20, 8
	mov	x0, x21
	bl	ShortTermRefFlg
	add	x1, x22, x19, uxtw 3
	cmp	x20, x23
	cbz	w0, .L173
	add	w19, w19, 1
	str	x21, [x1, 28024]
.L173:
	bne	.L174
.L172:
	ldr	w1, [x24, 3704]
	str	w19, [x24, 3712]
	cmp	w1, w19
	bls	.L171
	.p2align 2
.L181:
	add	x0, x22, x19, uxtw 3
	add	w19, w19, 1
	cmp	w19, w1
	str	xzr, [x0, 28024]
	bne	.L181
.L171:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L178:
	mov	w19, 0
	b	.L172
	.size	UpdateReflist, .-UpdateReflist
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetPicNumX
	.type	GetPicNumX, %function
GetPicNumX:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldrb	w0, [x20, 3]
	ldr	w2, [x20, 664]
	cbz	w0, .L187
	lsl	w2, w2, 1
	add	w2, w2, 1
.L187:
	mvn	w0, w19
	add	w0, w0, w2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	GetPicNumX, .-GetPicNumX
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UnMarkFrameStoreRef
	.type	UnMarkFrameStoreRef, %function
UnMarkFrameStoreRef:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x19, 1]
	tbz	x0, 0, .L189
	ldrb	w1, [x19, 2]
	strb	wzr, [x19, 745]
	and	w1, w1, 2
	strb	wzr, [x19, 746]
	strb	w1, [x19, 2]
.L189:
	tbz	x0, 1, .L190
	ldrb	w1, [x19, 2]
	strb	wzr, [x19, 793]
	and	w1, w1, 1
	strb	wzr, [x19, 794]
	strb	w1, [x19, 2]
.L190:
	cmp	w0, 3
	bne	.L191
	strb	wzr, [x19, 698]
	strb	wzr, [x19, 697]
.L191:
	add	x20, x20, 65536
	strb	wzr, [x19, 2]
	ldr	w1, [x19, 648]
	mov	w2, 0
	ldr	w0, [x20, 1644]
	bl	FSP_SetRef
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	UnMarkFrameStoreRef, .-UnMarkFrameStoreRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	SlidingWinMark.part.4, %function
SlidingWinMark.part.4:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	add	x19, x22, 24576
	bl	_mcount
	ldr	w0, [x19, 3708]
	cbz	w0, .L198
	sub	w21, w0, #1
	add	x19, x19, 3320
	add	x21, x21, 3488
	add	x21, x22, x21, lsl 3
	.p2align 2
.L201:
	ldr	x20, [x19]
	add	x19, x19, 8
	mov	x0, x20
	ldrb	w1, [x20, 2]
	cbz	w1, .L200
	bl	ShortTermRefFlg
	cbnz	w0, .L212
.L200:
	cmp	x19, x21
	bne	.L201
.L198:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L212:
	mov	x1, x20
	mov	x0, x22
	bl	UnMarkFrameStoreRef
	mov	x0, x22
	bl	UpdateReflist
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	SlidingWinMark.part.4, .-SlidingWinMark.part.4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UnMarkLTFrmByFrmIdx
	.type	UnMarkLTFrmByFrmIdx, %function
UnMarkLTFrmByFrmIdx:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	add	x0, x20, 24576
	ldr	w4, [x0, 3716]
	cbz	w4, .L213
	ldr	x1, [x20, 28152]
	ldr	w0, [x1, 660]
	cmp	w19, w0
	beq	.L215
	sub	w4, w4, #1
	mov	x0, x20
	add	x4, x20, x4, lsl 3
	b	.L217
	.p2align 3
.L218:
	ldr	x1, [x0, 28160]
	add	x0, x0, 8
	ldr	w3, [x1, 660]
	cmp	w3, w19
	beq	.L215
.L217:
	cmp	x0, x4
	bne	.L218
.L213:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L215:
	mov	x0, x20
	bl	UnMarkFrameStoreRef
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	UnMarkLTFrmByFrmIdx, .-UnMarkLTFrmByFrmIdx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UnMarkLTFldByFrmIdx
	.type	UnMarkLTFldByFrmIdx, %function
UnMarkLTFldByFrmIdx:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	mov	x21, x1
	mov	w20, w2
	mov	w19, w3
	bl	_mcount
	add	x0, x22, 24576
	ldr	w4, [x0, 3716]
	cbz	w4, .L224
	sub	w6, w4, #1
	add	x0, x0, 3576
	add	x6, x6, 3520
	add	x6, x22, x6, lsl 3
	b	.L228
	.p2align 3
.L226:
	cmp	x0, x6
	beq	.L224
.L228:
	ldr	x4, [x0]
	add	x0, x0, 8
	ldr	w5, [x4, 660]
	cmp	w5, w19
	bne	.L226
	cmp	w20, 1
	beq	.L240
	cmp	w20, 2
	bne	.L226
	ldrb	w1, [x4, 745]
	cmp	w1, wzr
	ccmp	x4, x21, 0, ne
	beq	.L226
.L239:
	mov	x1, x4
	mov	x0, x22
	bl	UnMarkFrameStoreRef
.L224:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L240:
	ldrb	w1, [x4, 793]
	cmp	w1, wzr
	ccmp	x4, x21, 0, ne
	beq	.L226
	b	.L239
	.size	UnMarkLTFldByFrmIdx, .-UnMarkLTFldByFrmIdx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UnMarkSTRef
	.type	UnMarkSTRef, %function
UnMarkSTRef:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	mov	w21, w2
	bl	_mcount
	ldrb	w0, [x20, 3]
	cbnz	w0, .L242
	add	x0, x19, 24576
	ldr	w3, [x20, 664]
	sub	w3, w3, #1
	ldr	w1, [x0, 3712]
	sub	w2, w3, w21
	cbz	w1, .L241
	sub	w4, w1, #1
	add	x0, x0, 3448
	add	x4, x4, 3504
	add	x4, x19, x4, lsl 3
	b	.L248
	.p2align 3
.L247:
	cmp	x0, x4
	beq	.L241
.L248:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldr	w3, [x1, 704]
	cmp	w3, w2
	bne	.L247
	ldrb	w3, [x1, 2]
	cmp	w3, 3
	bne	.L247
	ldr	w3, [x1, 696]
	and	w3, w3, 16776960
	cmp	w3, 65536
	bne	.L247
	mov	x0, x19
	bl	UnMarkFrameStoreRef
.L241:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L242:
	add	x1, x19, 24576
	ldr	w0, [x20, 664]
	add	x4, x1, 3448
	mov	w3, 0
	lsl	w0, w0, 1
	ldr	w6, [x1, 3712]
	sub	w2, w0, w21
	cbz	w6, .L241
	.p2align 2
.L262:
	ldr	x1, [x4]
	add	x4, x4, 8
	ldrb	w0, [x1, 2]
	and	w7, w0, 1
	tbz	x0, 0, .L249
	ldr	w5, [x1, 744]
	and	w5, w5, 16776960
	cmp	w5, 65536
	beq	.L274
.L249:
	tbz	x0, 1, .L251
	ldr	w0, [x1, 792]
	and	w0, w0, 16776960
	cmp	w0, 65536
	beq	.L275
.L251:
	add	w3, w3, 1
	cmp	w3, w6
	bne	.L262
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L274:
	ldr	w5, [x1, 752]
	cmp	w5, w2
	bne	.L249
	add	x3, x19, x3, uxtw 3
	and	w0, w0, 2
	strb	w0, [x1, 2]
	ldr	x0, [x3, 28024]
	strb	wzr, [x0, 746]
	b	.L273
	.p2align 3
.L275:
	ldr	w0, [x1, 800]
	cmp	w0, w2
	bne	.L251
	add	x3, x19, x3, uxtw 3
	strb	w7, [x1, 2]
	ldr	x0, [x3, 28024]
	strb	wzr, [x0, 794]
.L273:
	ldr	x0, [x3, 28024]
	ldrb	w1, [x0, 696]
	cmp	w1, 3
	ccmp	w1, wzr, 4, ne
	bne	.L252
	strb	wzr, [x0, 698]
	ldr	x0, [x3, 28024]
	strb	wzr, [x0, 697]
	ldr	x0, [x3, 28024]
.L252:
	ldrb	w1, [x0, 2]
	cbnz	w1, .L241
	ldr	w1, [x0, 684]
	add	x3, x19, 65536
	mov	w2, 0
	add	x1, x1, 16384
	add	x19, x19, x1, lsl 2
	str	wzr, [x19, 232]
	ldr	w1, [x0, 648]
	ldr	w0, [x3, 1644]
	bl	FSP_SetRef
	b	.L241
	.size	UnMarkSTRef, .-UnMarkSTRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UnMarkLTRef
	.type	UnMarkLTRef, %function
UnMarkLTRef:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x1
	mov	x20, x0
	mov	x0, x30
	mov	w19, w2
	bl	_mcount
	ldrb	w0, [x21, 3]
	cbz	w0, .L277
	add	x0, x20, 24576
	mov	w3, 0
	add	x4, x0, 3576
	ldr	w2, [x0, 3716]
	cbz	w2, .L276
	.p2align 2
.L297:
	ldr	x1, [x4]
	add	x4, x4, 8
	ldrb	w0, [x1, 2]
	and	w6, w0, 1
	tbz	x0, 0, .L282
	ldr	w5, [x1, 744]
	and	w5, w5, 16776960
	cmp	w5, 256
	beq	.L309
.L282:
	tbz	x0, 1, .L284
	ldr	w0, [x1, 792]
	and	w0, w0, 16776960
	cmp	w0, 256
	beq	.L310
.L284:
	add	w3, w3, 1
	cmp	w3, w2
	bne	.L297
.L276:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L309:
	ldr	w5, [x1, 748]
	cmp	w19, w5
	bne	.L282
	add	x3, x20, x3, uxtw 3
	and	w0, w0, 2
	strb	w0, [x1, 2]
	ldr	x0, [x3, 28152]
	strb	wzr, [x0, 745]
	b	.L308
	.p2align 3
.L310:
	ldr	w0, [x1, 796]
	cmp	w19, w0
	bne	.L284
	add	x3, x20, x3, uxtw 3
	strb	w6, [x1, 2]
	ldr	x0, [x3, 28152]
	strb	wzr, [x0, 793]
.L308:
	ldr	x0, [x3, 28152]
	ldrb	w1, [x0, 696]
	cmp	w1, 3
	ccmp	w1, wzr, 4, ne
	bne	.L285
	strb	wzr, [x0, 698]
	ldr	x0, [x3, 28152]
	strb	wzr, [x0, 697]
	ldr	x0, [x3, 28152]
.L285:
	ldrb	w1, [x0, 2]
	cbnz	w1, .L276
	ldr	w0, [x0, 684]
	add	x0, x0, 16384
	add	x20, x20, x0, lsl 2
	str	wzr, [x20, 232]
	b	.L276
	.p2align 3
.L277:
	add	x0, x20, 24576
	ldr	w1, [x0, 3716]
	cbz	w1, .L276
	sub	w2, w1, #1
	add	x0, x0, 3576
	add	x2, x2, 3520
	add	x2, x20, x2, lsl 3
	b	.L288
	.p2align 3
.L287:
	cmp	x0, x2
	beq	.L276
.L288:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldr	w3, [x1, 700]
	cmp	w3, w19
	bne	.L287
	ldrb	w3, [x1, 2]
	cmp	w3, 3
	bne	.L287
	ldr	w3, [x1, 696]
	and	w3, w3, 16776960
	cmp	w3, 256
	bne	.L287
	mov	x0, x20
	bl	UnMarkFrameStoreRef
	b	.L276
	.size	UnMarkLTRef, .-UnMarkLTRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MarkPicLTRef
	.type	MarkPicLTRef, %function
MarkPicLTRef:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x3
	mov	x21, x0
	mov	x0, x30
	mov	w19, w2
	mov	w20, w1
	bl	_mcount
	ldrb	w2, [x22, 3]
	add	x0, x21, 24576
	cbz	w2, .L312
	ldr	w7, [x0, 3712]
	mov	w3, 0
	add	x4, x0, 3448
	cbz	w7, .L311
	.p2align 2
.L333:
	ldr	x0, [x4]
	ldrb	w5, [x0, 2]
	tbz	x5, 0, .L318
	ldr	w6, [x0, 744]
	and	w6, w6, 16776960
	cmp	w6, 65536
	beq	.L339
.L318:
	tbz	x5, 1, .L321
	ldr	w5, [x0, 792]
	and	w5, w5, 16776960
	cmp	w5, 65536
	beq	.L340
.L321:
	add	w3, w3, 1
	add	x4, x4, 8
	cmp	w3, w7
	bne	.L333
.L311:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L339:
	ldr	w1, [x0, 752]
	cmp	w19, w1
	bne	.L318
	ldrb	w1, [x0, 793]
	cmp	w1, 1
	bne	.L322
	ldr	w1, [x0, 660]
	cmp	w20, w1
	bne	.L321
.L322:
	add	x3, x21, x3, uxtw 3
	str	w20, [x0, 660]
	cmp	w2, 1
	lsl	w0, w20, 1
	csinc	w0, w0, w0, ne
	mov	w1, 1
	ldr	x2, [x3, 28024]
	str	w0, [x2, 748]
	ldr	x0, [x3, 28024]
	strb	w1, [x0, 745]
	ldr	x0, [x3, 28024]
	strb	wzr, [x0, 746]
	ldr	x0, [x3, 28024]
	ldrb	w1, [x0, 696]
	cmp	w1, 3
	ccmp	w1, wzr, 4, ne
	bne	.L311
	ldrb	w2, [x0, 745]
	ldrb	w1, [x0, 793]
	cmp	w1, w2
	bne	.L311
	strb	w1, [x0, 697]
	ldr	x0, [x3, 28024]
	ldrb	w1, [x0, 746]
	strb	w1, [x0, 698]
	b	.L311
	.p2align 3
.L340:
	ldr	w1, [x0, 800]
	cmp	w1, w19
	bne	.L321
	ldrb	w1, [x0, 745]
	cmp	w1, 1
	bne	.L325
	ldr	w1, [x0, 660]
	cmp	w1, w20
	bne	.L321
.L325:
	add	x3, x21, x3, uxtw 3
	str	w20, [x0, 660]
	cmp	w2, 2
	lsl	w0, w20, 1
	csinc	w0, w0, w0, ne
	mov	w1, 1
	ldr	x2, [x3, 28024]
	str	w0, [x2, 796]
	ldr	x0, [x3, 28024]
	strb	w1, [x0, 793]
	ldr	x0, [x3, 28024]
	strb	wzr, [x0, 794]
	ldr	x0, [x3, 28024]
	ldrb	w1, [x0, 696]
	cmp	w1, 3
	ccmp	w1, wzr, 4, ne
	bne	.L311
	ldrb	w2, [x0, 745]
	ldrb	w1, [x0, 793]
	cmp	w1, w2
	bne	.L311
	strb	w1, [x0, 697]
	ldr	x0, [x3, 28024]
	ldrb	w1, [x0, 794]
	strb	w1, [x0, 698]
	b	.L311
	.p2align 3
.L312:
	ldr	w7, [x0, 3712]
	cbz	w7, .L311
	add	x0, x0, 3448
	mov	w4, 0
	b	.L317
	.p2align 3
.L316:
	add	w4, w4, 1
	cmp	w4, w7
	beq	.L311
.L317:
	ldr	x5, [x0]
	add	x0, x0, 8
	ldrb	w6, [x5, 2]
	cmp	w6, 3
	bne	.L316
	ldr	w6, [x5, 696]
	and	w6, w6, 16776960
	cmp	w6, 65536
	bne	.L316
	ldr	w1, [x5, 704]
	cmp	w19, w1
	bne	.L316
	add	x4, x21, x4, uxtw 3
	str	w20, [x5, 660]
	mov	w0, 1
	ldr	x1, [x4, 28024]
	str	w20, [x1, 700]
	ldr	x1, [x4, 28024]
	strb	w0, [x1, 697]
	ldr	x1, [x4, 28024]
	strb	w0, [x1, 745]
	ldr	x1, [x4, 28024]
	strb	w0, [x1, 793]
	ldr	x0, [x4, 28024]
	strb	wzr, [x0, 698]
	ldr	x0, [x4, 28024]
	strb	wzr, [x0, 746]
	ldr	x0, [x4, 28024]
	strb	wzr, [x0, 794]
	b	.L311
	.size	MarkPicLTRef, .-MarkPicLTRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MarkSTToLTRef
	.type	MarkSTToLTRef, %function
MarkSTToLTRef:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x1
	mov	x21, x0
	mov	x0, x30
	mov	w19, w2
	mov	w20, w3
	bl	_mcount
	ldrb	w0, [x22, 3]
	cbnz	w0, .L342
	add	x0, x21, 24576
	ldr	w2, [x22, 664]
	sub	w2, w2, #1
	ldr	w4, [x0, 3716]
	sub	w19, w2, w19
	cbz	w4, .L344
	ldr	x1, [x21, 28152]
	ldr	w0, [x1, 660]
	cmp	w20, w0
	beq	.L346
	sub	w4, w4, #1
	mov	x0, x21
	add	x4, x21, x4, lsl 3
	b	.L348
	.p2align 3
.L349:
	ldr	x1, [x0, 28160]
	add	x0, x0, 8
	ldr	w3, [x1, 660]
	cmp	w20, w3
	beq	.L346
.L348:
	cmp	x4, x0
	bne	.L349
.L344:
	mov	x3, x22
	mov	w2, w19
	mov	w1, w20
	mov	x0, x21
	bl	MarkPicLTRef
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L342:
	add	x0, x21, 24576
	ldr	w2, [x22, 664]
	lsl	w2, w2, 1
	ldr	w1, [x0, 3712]
	sub	w19, w2, w19
	cbz	w1, .L344
	sub	w5, w1, #1
	add	x0, x0, 3448
	add	x5, x5, 3504
	add	x5, x21, x5, lsl 3
	.p2align 2
.L352:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w3, [x1, 2]
	tbz	x3, 0, .L350
	ldr	w4, [x1, 744]
	and	w4, w4, 16776960
	cmp	w4, 65536
	beq	.L362
.L350:
	tbz	x3, 1, .L351
	ldr	w3, [x1, 792]
	and	w3, w3, 16776960
	cmp	w3, 65536
	beq	.L363
.L351:
	cmp	x0, x5
	bne	.L352
	b	.L344
	.p2align 3
.L362:
	ldr	w2, [x1, 752]
	cmp	w2, w19
	bne	.L350
	mov	w3, w20
	mov	w2, 1
	mov	x0, x21
	bl	UnMarkLTFldByFrmIdx
	b	.L344
	.p2align 3
.L363:
	ldr	w2, [x1, 800]
	cmp	w2, w19
	bne	.L351
	mov	w3, w20
	mov	w2, 2
	mov	x0, x21
	bl	UnMarkLTFldByFrmIdx
	b	.L344
	.p2align 3
.L346:
	mov	x0, x21
	bl	UnMarkFrameStoreRef
	b	.L344
	.size	MarkSTToLTRef, .-MarkSTToLTRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UpdateMaxLTFrmIdx
	.type	UpdateMaxLTFrmIdx, %function
UpdateMaxLTFrmIdx:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	add	x21, x22, 24576
	mov	w20, w1
	bl	_mcount
	ldr	w0, [x21, 3716]
	str	w20, [x21, 3720]
	cbz	w0, .L364
	mov	w19, 0
	mov	w2, w20
	b	.L366
	.p2align 3
.L367:
	ldr	w0, [x21, 3716]
	cmp	w0, w19
	bls	.L364
.L371:
	ldr	w2, [x21, 3720]
.L366:
	add	x0, x22, x19, uxtw 3
	add	w19, w19, 1
	ldr	x1, [x0, 28152]
	ldr	w0, [x1, 660]
	cmp	w0, w2
	bcc	.L367
	mov	x0, x22
	bl	UnMarkFrameStoreRef
	ldr	w0, [x21, 3716]
	cmp	w0, w19
	bhi	.L371
.L364:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	UpdateMaxLTFrmIdx, .-UpdateMaxLTFrmIdx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UnMarkAllSTRef
	.type	UnMarkAllSTRef, %function
UnMarkAllSTRef:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x21, x20, 24576
	mov	w19, 0
	bl	_mcount
	ldr	w0, [x21, 3712]
	cbz	w0, .L372
	.p2align 2
.L376:
	add	x1, x20, x19, uxtw 3
	mov	x0, x20
	add	w19, w19, 1
	ldr	x1, [x1, 28024]
	bl	UnMarkFrameStoreRef
	ldr	w0, [x21, 3712]
	cmp	w0, w19
	bhi	.L376
.L372:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	UnMarkAllSTRef, .-UnMarkAllSTRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MarkCurrPicLT
	.type	MarkCurrPicLT, %function
MarkCurrPicLT:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x1
	mov	x21, x0
	mov	x0, x30
	mov	w19, w2
	bl	_mcount
	ldrb	w2, [x20, 3]
	cbnz	w2, .L379
	add	x0, x21, 24576
	ldr	w3, [x0, 3716]
	cbz	w3, .L380
	ldr	x1, [x21, 28152]
	ldr	w0, [x1, 660]
	cmp	w19, w0
	beq	.L381
	sub	w3, w3, #1
	mov	x0, x21
	add	x3, x21, x3, lsl 3
	b	.L383
	.p2align 3
.L384:
	ldr	x1, [x0, 28160]
	add	x0, x0, 8
	ldr	w2, [x1, 660]
	cmp	w19, w2
	beq	.L381
.L383:
	cmp	x0, x3
	bne	.L384
.L380:
	strb	wzr, [x20, 5]
	mov	w0, 1
	str	w19, [x20, 668]
	strb	w0, [x20, 4]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L381:
	mov	x0, x21
	bl	UnMarkFrameStoreRef
	strb	wzr, [x20, 5]
	str	w19, [x20, 668]
	mov	w0, 1
	strb	w0, [x20, 4]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L379:
	ldr	x1, [x20, 648]
	mov	w3, w19
	mov	x0, x21
	bl	UnMarkLTFldByFrmIdx
	strb	wzr, [x20, 5]
	str	w19, [x20, 668]
	mov	w0, 1
	strb	w0, [x20, 4]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	MarkCurrPicLT, .-MarkCurrPicLT
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RemoveFrameStoreOutDPB
	.type	RemoveFrameStoreOutDPB, %function
RemoveFrameStoreOutDPB:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	uxtw	x21, w1
	mov	x20, x0
	mov	x0, x30
	mov	x19, x21
	add	x22, x20, x21, lsl 3
	bl	_mcount
	ldr	x1, [x22, 27896]
	cbz	x1, .L408
	ldr	w0, [x1, 688]
	add	x23, x20, 24576
	add	x24, x20, 65536
	add	x0, x0, 4096
	add	x0, x0, 2980
	str	wzr, [x20, x0, lsl 2]
	ldr	w0, [x23, 3988]
	cmp	w0, wzr
	cset	w2, ne
	sub	w0, w0, w2
	str	w0, [x23, 3988]
	ldr	w1, [x1, 648]
	ldr	w0, [x24, 1644]
	bl	FSP_GetLogicFs
	cbz	x0, .L394
	ldrsb	w0, [x0, 1]
	cmp	w0, 3
	beq	.L395
	ldr	x1, [x22, 27896]
	mov	w2, 0
	ldr	w0, [x24, 1644]
	ldr	w1, [x1, 648]
	bl	FSP_SetDisplay
.L395:
	ldr	x1, [x22, 27896]
	mov	w2, 0
	ldr	w0, [x24, 1644]
	ldr	w1, [x1, 648]
	bl	FSP_SetRef
.L394:
	ldr	x0, [x22, 27896]
	mov	w1, -1
	strb	wzr, [x0, 1]
	ldr	x0, [x22, 27896]
	strb	wzr, [x0, 4]
	ldr	x0, [x22, 27896]
	strb	wzr, [x0, 2]
	ldr	x0, [x22, 27896]
	str	w1, [x0, 648]
	ldr	w2, [x23, 3708]
	add	w2, w2, w1
	cmp	w19, w2
	bcs	.L397
	.p2align 2
.L405:
	add	w0, w19, 1
	add	x1, x20, x21, lsl 3
	mov	w19, w0
	cmp	w0, w2
	mov	x21, x0
	add	x0, x20, x0, lsl 3
	ldr	x0, [x0, 27896]
	str	x0, [x1, 27896]
	bne	.L405
.L397:
	add	x20, x20, x2, uxtw 3
	str	xzr, [x20, 27896]
	str	w2, [x23, 3708]
.L390:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L408:
	ldr	x2, .LC30
	mov	w3, w21
	ldr	x1, .LC32
	mov	w0, 1
	bl	dprint_vfmw
	b	.L390
	.size	RemoveFrameStoreOutDPB, .-RemoveFrameStoreOutDPB
	.align	3
.LC30:
	.xword	.LANCHOR0
	.align	3
.LC32:
	.xword	.LC31
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RemoveUnUsedFrameStore
	.type	RemoveUnUsedFrameStore, %function
RemoveUnUsedFrameStore:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x22, x0
	mov	x0, x30
	bl	_mcount
	cbz	x22, .L419
	add	x0, x22, 24576
	ldr	w23, [x0, 3708]
	cbz	w23, .L418
	mov	w21, 0
	mov	w20, 0
	add	x24, x22, 65536
	mov	w25, -1
	b	.L417
	.p2align 3
.L428:
	ldrb	w1, [x0, 4]
	cbnz	w1, .L415
	ldr	w1, [x0, 840]
	cmp	w1, 1
	beq	.L415
	strb	wzr, [x0, 1]
	mov	w1, w21
	mov	x0, x22
	add	w20, w20, 1
	bl	RemoveFrameStoreOutDPB
	cmp	w23, w20
	beq	.L418
	.p2align 2
.L417:
	add	x19, x22, x21, uxtw 3
	ldr	w0, [x24, 1644]
	ldr	x1, [x19, 27896]
	ldr	w1, [x1, 648]
	bl	FSP_GetLogicFs
	cbz	x0, .L412
	ldrsh	w1, [x0]
	cbnz	w1, .L413
	ldr	x1, [x19, 27896]
	ldrb	w2, [x1, 2]
	cbnz	w2, .L414
	ldrsb	w0, [x0]
	cbnz	w0, .L427
.L414:
	str	w25, [x1, 648]
	ldr	x0, [x19, 27896]
	strb	wzr, [x0, 2]
.L412:
	ldr	x0, [x19, 27896]
	ldr	w1, [x0, 840]
	cmp	w1, 1
	cset	w1, eq
	strb	w1, [x0, 4]
.L413:
	ldr	x0, [x19, 27896]
	ldrb	w1, [x0, 2]
	cbz	w1, .L428
.L415:
	add	w20, w20, 1
	add	w21, w21, 1
	cmp	w23, w20
	bne	.L417
.L418:
	mov	w0, 0
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L427:
	ldr	w1, [x1, 648]
	ldr	w0, [x24, 1644]
	bl	FSP_SetRef
	ldr	x1, [x19, 27896]
	b	.L414
	.p2align 3
.L419:
	mov	w0, -1
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.size	RemoveUnUsedFrameStore, .-RemoveUnUsedFrameStore
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CheckFrameStore
	.type	CheckFrameStore, %function
CheckFrameStore:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	add	x0, x20, 65536
	ldr	w1, [x0, 316]
	cbnz	w1, .L430
	ldr	w1, [x19, 840]
	cmp	w1, 1
	beq	.L431
	ldr	w1, [x0, 1572]
	cbz	w1, .L455
.L431:
	mov	w1, 1
	str	w1, [x0, 316]
.L430:
	ldr	w0, [x0, 1644]
	ldr	w1, [x19, 648]
	bl	FSP_GetLogicFs
	cbz	x0, .L433
	ldrsb	w3, [x0, 1]
	cmp	w3, 3
	ccmp	w3, wzr, 4, ne
	beq	.L456
	ldrb	w2, [x19, 1]
	ldrb	w3, [x19]
	cbz	w2, .L441
	cmp	w3, 1
	beq	.L441
	ldr	w1, [x19]
	mov	w3, 50332416
	and	w1, w1, -16711936
	cmp	w1, w3
	beq	.L457
	cmp	w2, 1
	beq	.L458
	cmp	w2, 2
	beq	.L459
.L439:
	ldr	x1, [x20]
	ldr	w2, [x0, 200]
	mov	w0, 0
	ldr	w3, [x1, 4]
	cmp	w2, w3
	bhi	.L460
.L451:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L455:
	ldr	x1, [x20]
	ldr	w1, [x1, 24]
	cbnz	w1, .L431
	mov	w0, -1
	b	.L451
	.p2align 3
.L456:
	ldr	x1, .LC34
	mov	w0, 1
	ldr	w2, [x19, 648]
	bl	dprint_vfmw
.L435:
	ldr	w0, [x19, 840]
	cmp	w0, 1
	beq	.L442
	mov	w0, -3
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L458:
	ldrb	w3, [x19, 3]
	tbz	x3, 0, .L439
	ldr	x1, .LC42
	mov	w0, w2
	bl	dprint_vfmw
	mov	w0, -1
	b	.L451
	.p2align 3
.L459:
	ldrb	w3, [x19, 3]
	tbz	x3, 1, .L439
	ldr	x1, .LC44
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L451
	.p2align 3
.L442:
	mov	w1, 2
	mov	w0, -3
	str	w1, [x19, 840]
	b	.L451
	.p2align 3
.L433:
	ldr	x1, .LC36
	mov	x2, x19
	ldr	w4, [x19, 648]
	mov	w0, 1
	ldr	w3, [x19, 840]
	bl	dprint_vfmw
	b	.L435
	.p2align 3
.L441:
	ldr	x1, .LC38
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L451
	.p2align 3
.L460:
	ldr	x1, .LC46
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L451
.L457:
	ldrb	w3, [x19, 3]
	mov	w0, 1
	ldr	x1, .LC40
	bl	dprint_vfmw
	mov	w0, -1
	b	.L451
	.size	CheckFrameStore, .-CheckFrameStore
	.align	3
.LC34:
	.xword	.LC33
	.align	3
.LC36:
	.xword	.LC35
	.align	3
.LC38:
	.xword	.LC37
	.align	3
.LC40:
	.xword	.LC39
	.align	3
.LC42:
	.xword	.LC41
	.align	3
.LC44:
	.xword	.LC43
	.align	3
.LC46:
	.xword	.LC45
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetImagePara
	.type	GetImagePara, %function
GetImagePara:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x21, x0
	mov	x0, x30
	mov	x19, x1
	add	x23, x21, 65536
	bl	_mcount
	add	x26, x21, 24576
	add	x2, x21, 20480
	mov	w3, 2208
	ldr	x7, [x21, 14968]
	ldrb	w0, [x19, 81]
	ldr	w4, [x2, 1592]
	mov	w2, 4000
	ldrb	w1, [x19, 80]
	and	w5, w0, -4
	ldr	x6, [x21, 14960]
	mov	w0, w5
	umull	x3, w4, w3
	ldrb	w4, [x19, 82]
	and	w1, w1, -4
	add	x3, x7, x3
	ldrb	w7, [x19, 5]
	bfi	w4, w7, 1, 1
	ldr	w3, [x3, 28]
	strb	w5, [x19, 81]
	strb	w1, [x19, 80]
	umull	x2, w3, w2
	ldrb	w3, [x19, 1]
	ldr	w5, [x23, 324]
	add	x2, x6, x2
	strb	w4, [x19, 82]
	cmp	w3, 3
	ldr	w4, [x19, 8]
	str	w5, [x19, 124]
	str	w4, [x19, 136]
	bhi	.L462
	ldr	x4, .LC47
	ldrh	w4, [x4,w3,uxtw #1]
	adr	x5, .Lrtx464
	add	x4, x5, w4, sxth #2
	br	x4
.Lrtx464:
	.section	.rodata
	.align	0
	.align	2
.L464:
	.2byte	(.L463 - .Lrtx464) / 4
	.2byte	(.L465 - .Lrtx464) / 4
	.2byte	(.L466 - .Lrtx464) / 4
	.2byte	(.L463 - .Lrtx464) / 4
	.text
	.p2align 3
.L463:
	ldrb	w4, [x19, 696]
	cbnz	w4, .L467
	ldr	w5, [x19, 680]
	ldr	w4, [x19, 672]
	str	w5, [x19, 168]
	ldr	w9, [x19, 676]
	ldr	w6, [x19, 764]
	ldr	w5, [x19, 812]
	cbnz	w4, .L468
	mov	w10, 2
	mov	w8, 3
.L469:
	ldr	w7, [x19, 756]
	ldr	w4, [x19, 804]
	cmp	w7, w4
	beq	.L527
	cset	w4, le
.L480:
	add	x26, x21, 24576
	ldrb	w7, [x26, 3220]
	cmp	w7, 3
	beq	.L496
	cmp	w7, 4
	mov	w7, 0
	csel	w4, w4, w7, ne
.L481:
	bfi	w0, w4, 4, 2
	bfi	w1, w9, 0, 2
	bfi	w0, w8, 2, 2
	strb	w1, [x19, 80]
	bfi	w0, w10, 0, 2
	strb	w0, [x19, 81]
	stp	w6, w5, [x19, 72]
.L462:
	ldrb	w1, [x2, 18]
	mov	w4, 0
	str	w1, [x19, 412]
	str	w1, [x19, 416]
	ldrb	w1, [x2, 22]
	cbz	w1, .L482
	ldr	w4, [x2, 3332]
.L482:
	str	w4, [x19, 424]
	mov	w1, 1
	str	w1, [x19, 420]
	ldr	x1, [x21]
	ldr	w1, [x1, 596]
	str	w1, [x19, 140]
	ldr	x1, [x21]
	ldr	w1, [x1, 600]
	str	w1, [x19, 144]
	ldr	x1, [x21]
	ldr	w1, [x1, 604]
	str	w1, [x19, 148]
	ldr	x1, [x21]
	ldr	w1, [x1, 24]
	cbz	w1, .L483
	ldrb	w1, [x19, 696]
	cbz	w1, .L528
.L483:
	ldr	x0, [x19, 600]
	cmn	x0, #1
	beq	.L485
	ldr	w0, [x26, 3708]
	cbz	w0, .L485
	mov	w25, -1
	mov	x24, -2
	mov	w20, 0
	.p2align 2
.L488:
	add	x22, x21, x20, sxtw 3
	ldr	x0, [x22, 27896]
	cbz	x0, .L487
	ldr	w1, [x0, 648]
	ldr	w0, [x23, 1644]
	bl	FSP_GetLogicFs
	cbz	x0, .L487
	ldrsb	w0, [x0, 1]
	cmp	w0, 3
	ccmp	w0, wzr, 4, ne
	beq	.L487
	ldr	x0, [x22, 27896]
	ldr	x0, [x0, 600]
	cmp	x0, x24
	bcs	.L487
	mov	w25, w20
	mov	x24, x0
	.p2align 2
.L487:
	ldr	w0, [x26, 3708]
	add	w20, w20, 1
	cmp	w0, w20
	bhi	.L488
	cmn	w25, #1
	beq	.L485
	ldr	x1, [x19, 600]
	cmp	x1, x24
	bhi	.L529
.L485:
	ldrsb	w0, [x26, 3184]
	cbz	w0, .L489
	ldr	w0, [x26, 3200]
	cmp	w0, 3
	beq	.L530
	cmp	w0, 4
	beq	.L531
	cmp	w0, 5
	beq	.L532
	str	wzr, [x19, 292]
	mov	w0, 0
	ldr	x1, .LC51
	ldr	w2, [x26, 3200]
	bl	dprint_vfmw
	.p2align 2
.L489:
	ldr	w1, [x19, 648]
	ldr	w0, [x23, 1644]
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L461
	ldr	x3, .LC52
	mov	x2, 632
	add	x1, x19, 16
	ldr	x3, [x3, 104]
	blr	x3
	str	wzr, [x20, 296]
	mov	w2, 4
	mov	w1, 1
	ldrb	w0, [x19, 696]
	strb	w1, [x20, 291]
	cmp	w0, wzr
	csel	w0, w0, w2, eq
	strb	w0, [x20, 284]
	ldr	w0, [x19, 720]
	str	w0, [x20, 300]
	strb	w1, [x20, 289]
	str	w0, [x20, 304]
	str	w0, [x20, 308]
	ldr	w0, [x19, 728]
	str	w0, [x20, 236]
.L461:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L529:
	ldr	w0, [x23, 1644]
	mov	x2, x24
	bl	IsPtsRewind
	cbnz	w0, .L485
	ldr	x1, .LC49
	mov	x3, x24
	ldr	x2, [x19, 600]
	mov	w0, 29
	add	x21, x21, x25, sxtw 3
	bl	dprint_vfmw
	ldr	x0, [x21, 27896]
	ldr	x1, [x19, 600]
	str	x1, [x0, 600]
	str	x24, [x19, 600]
	b	.L485
	.p2align 3
.L528:
	cmp	w3, 3
	bne	.L483
	and	w0, w0, -4
	strb	w0, [x19, 81]
	b	.L483
	.p2align 3
.L465:
	ldr	w6, [x19, 676]
	mov	w4, 1
	bfi	w0, w4, 2, 2
	ldr	w5, [x19, 680]
	bfi	w1, w6, 0, 2
	ldr	w4, [x19, 764]
	strb	w1, [x19, 80]
	orr	w0, w0, 3
	ldr	x1, [x19, 784]
	add	x26, x21, 24576
	str	w4, [x19, 72]
	mov	w4, 3
	strb	w0, [x19, 81]
	str	w5, [x19, 168]
	str	w4, [x19, 76]
	ldr	w1, [x1, 692]
	str	w1, [x19, 728]
	b	.L462
	.p2align 3
.L466:
	ldr	w6, [x19, 676]
	mov	w4, 2
	bfi	w0, w4, 2, 2
	ldr	w5, [x19, 812]
	bfi	w1, w6, 0, 2
	ldr	w4, [x19, 680]
	strb	w1, [x19, 80]
	orr	w0, w0, 3
	ldr	x1, [x19, 832]
	add	x26, x21, 24576
	str	w4, [x19, 168]
	mov	w4, 3
	strb	w0, [x19, 81]
	str	w5, [x19, 76]
	str	w4, [x19, 72]
	ldr	w1, [x1, 692]
	str	w1, [x19, 728]
	b	.L462
	.p2align 3
.L530:
	mov	w0, 1
	str	w0, [x19, 292]
	b	.L489
	.p2align 3
.L532:
	mov	w0, 3
	str	w0, [x19, 292]
	b	.L489
	.p2align 3
.L467:
	ldr	w7, [x19, 760]
	ldr	w4, [x23, 1640]
	ldr	w10, [x19, 808]
	cmp	w7, w4
	bhi	.L533
	cmp	w4, w10
	bcc	.L473
.L471:
	ldr	w4, [x19, 680]
	mov	w8, 3
	ldr	w9, [x19, 676]
	ldr	w6, [x19, 764]
	ldr	w5, [x19, 812]
	str	w4, [x19, 168]
.L474:
	ldrb	w4, [x19, 3]
	cmp	w4, 1
	beq	.L534
	cmp	w4, 2
	beq	.L535
.L476:
	ldr	w7, [x19, 776]
	mov	w10, 3
	ldr	w4, [x19, 824]
	stp	w6, w5, [x19, 72]
	add	w4, w7, w4
	add	w4, w4, w4, lsr 31
	asr	w4, w4, 1
	str	w4, [x19, 252]
	b	.L469
.L473:
	ldr	w9, [x19, 764]
	mov	w8, 1
	ldr	w5, [x19, 812]
	mov	w6, w9
	str	w7, [x19, 168]
	b	.L474
	.p2align 3
.L531:
	mov	w0, 2
	str	w0, [x19, 292]
	b	.L489
.L496:
	mov	w4, 1
	b	.L481
.L527:
	ldr	w4, [x19, 84]
	cmp	w4, 720
	mov	w4, 1
	bne	.L480
	ldr	w4, [x19, 88]
	cmp	w4, 480
	cset	w4, ne
	b	.L480
.L533:
	cmp	w4, w10
	bcc	.L471
	ldr	w9, [x19, 812]
	mov	w8, 2
	ldr	w6, [x19, 764]
	mov	w5, w9
	str	w10, [x19, 168]
	b	.L474
.L468:
	mov	w10, 3
	mov	w8, w10
	b	.L469
.L534:
	mov	w9, w5
	mov	w8, 2
	str	w10, [x19, 168]
	b	.L476
.L535:
	mov	w9, w6
	mov	w8, 1
	str	w7, [x19, 168]
	b	.L476
	.size	GetImagePara, .-GetImagePara
	.align	3
.LC47:
	.xword	.L464
	.align	3
.LC49:
	.xword	.LC48
	.align	3
.LC51:
	.xword	.LC50
	.align	3
.LC52:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SetFrmRepeatCount
	.type	SetFrmRepeatCount, %function
SetFrmRepeatCount:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, [x19]
	ldr	w0, [x0, 612]
	add	w0, w0, 2047
	cmp	w0, 4095
	bls	.L537
	mov	x1, x20
	mov	x0, x19
	bl	SetFrmRepeatCount.part.3
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L537:
	str	wzr, [x20, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SetFrmRepeatCount, .-SetFrmRepeatCount
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SplitFrmToFlds
	.type	SplitFrmToFlds, %function
SplitFrmToFlds:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w4, [x19, 697]
	mov	w6, 1
	ldrb	w3, [x19, 698]
	mov	w5, 2
	ldr	w2, [x19, 712]
	ldr	w1, [x19, 716]
	ldr	x0, [x19, 736]
	strb	w4, [x19, 745]
	strb	w3, [x19, 746]
	strb	w6, [x19, 744]
	strb	w4, [x19, 793]
	strb	w3, [x19, 794]
	strb	w5, [x19, 792]
	str	w2, [x19, 760]
	str	w1, [x19, 764]
	str	x0, [x19, 784]
	str	w2, [x19, 808]
	str	w1, [x19, 812]
	str	x0, [x19, 832]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SplitFrmToFlds, .-SplitFrmToFlds
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CombineFldsToFrm
	.type	CombineFldsToFrm, %function
CombineFldsToFrm:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x19, 756]
	mov	w5, 3
	ldr	w3, [x19, 760]
	ldr	w2, [x19, 804]
	ldr	w0, [x19, 808]
	cmp	w1, w2
	ldr	x4, [x19, 784]
	add	w0, w3, w0
	ldrb	w3, [x19, 793]
	csel	w1, w1, w2, le
	lsr	w0, w0, 1
	strb	w5, [x19, 696]
	str	w1, [x19, 664]
	str	w1, [x19, 708]
	str	w0, [x19, 712]
	str	x4, [x19, 736]
	cbz	w3, .L541
	ldrb	w1, [x19, 745]
	cbz	w1, .L541
	mov	w1, 1
	strb	w1, [x19, 697]
.L543:
	mov	w2, 0
.L544:
	ldr	w1, [x19, 764]
	strb	w2, [x19, 698]
	cbz	w1, .L545
	ldr	w2, [x19, 812]
	cbz	w2, .L547
	cmp	w1, w2
	csel	w1, w1, w2, cs
.L545:
	str	w1, [x19, 676]
	str	w0, [x19, 680]
	str	w1, [x19, 716]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L541:
	ldr	w1, [x19, 792]
	strb	wzr, [x19, 697]
	tst	w1, 16776960
	beq	.L543
	ldr	w1, [x19, 744]
	mov	w2, 1
	tst	w1, 16776960
	bne	.L544
	b	.L543
	.p2align 3
.L547:
	mov	w1, 0
	str	w0, [x19, 680]
	str	w1, [x19, 676]
	str	w1, [x19, 716]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CombineFldsToFrm, .-CombineFldsToFrm
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetAPC
	.type	GetAPC, %function
GetAPC:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x22, x1
	mov	x0, x30
	mov	w19, w2
	bl	_mcount
	cbz	x22, .L582
	cmp	w19, 1
	beq	.L562
	cmp	w19, 2
	beq	.L563
	ldr	w23, [x22, 756]
	ldr	w24, [x22, 804]
.L564:
	add	x21, x20, 24576
	ldr	w2, [x21, 3984]
	cbz	w2, .L573
	ldr	w0, [x21, 3728]
	cbz	w0, .L583
	add	x0, x21, 3732
	mov	w19, 0
	b	.L567
	.p2align 3
.L571:
	ldr	w1, [x0], 4
	cbz	w1, .L565
.L567:
	add	w19, w19, 1
	cmp	w19, w2
	bne	.L571
.L573:
	mov	w0, -1
.L577:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L563:
	ldr	w23, [x22, 804]
	mov	w24, w23
	b	.L564
.L583:
	mov	w19, 0
	.p2align 2
.L565:
	add	x0, x20, 65536
	ldr	w1, [x22, 648]
	ldr	w0, [x0, 1644]
	bl	FSP_GetLogicFs
	cbz	x0, .L568
	ldr	x1, [x0, 32]
	cbz	x1, .L568
	add	x20, x20, x19, uxtw 2
	mov	w1, 1
	add	x20, x20, 24576
	mov	w4, 16
	mov	w3, w19
	str	w1, [x20, 3728]
	ldr	x1, .LC58
	ldr	x0, [x0, 32]
	ldr	w0, [x0, 4]
	str	w0, [x20, 3792]
	mov	w0, 13
	str	w23, [x20, 3856]
	str	w24, [x20, 3920]
	ldr	w2, [x21, 3988]
	cmp	w2, 15
	csinc	w2, w4, w2, hi
	str	w2, [x21, 3988]
	ldr	w2, [x22, 164]
	bl	dprint_vfmw
	str	w19, [x22, 688]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L562:
	ldr	w23, [x22, 756]
	mov	w24, w23
	b	.L564
.L568:
	ldrb	w3, [x22, 2]
	mov	x4, x0
	ldr	x1, .LC60
	mov	x5, 0
	ldr	w2, [x22, 648]
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L577
.L582:
	ldr	x2, .LC54
	mov	w3, 2206
	ldr	x1, .LC56
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L577
	.size	GetAPC, .-GetAPC
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
	.global	SlidingWinMark
	.type	SlidingWinMark, %function
SlidingWinMark:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 24576
	add	x0, x19, 16384
	ldr	w2, [x1, 3716]
	ldr	w0, [x0, 1836]
	ldr	w1, [x1, 3712]
	sub	w0, w0, w2
	cmp	w1, w0
	bne	.L584
	mov	x0, x19
	bl	SlidingWinMark.part.4
.L584:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SlidingWinMark, .-SlidingWinMark
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DumpDPB
	.type	DumpDPB, %function
DumpDPB:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x22, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC61
	ldr	w0, [x0]
	tbz	x0, 14, .L586
	add	x21, x22, 24576
	ldr	w0, [x21, 3708]
	cbz	w0, .L592
	ldr	x20, .LC64
	mov	w19, 0
	.p2align 2
.L591:
	add	x3, x22, x19, uxtw 3
	mov	w2, w19
	mov	x1, x20
	mov	w0, 14
	add	w19, w19, 1
	ldr	x3, [x3, 27896]
	ldrb	w5, [x3, 2]
	ldr	w4, [x3, 664]
	ldr	w3, [x3, 652]
	bl	dprint_vfmw
	ldr	w0, [x21, 3708]
	cmp	w0, w19
	bhi	.L591
.L592:
	ldr	x25, .LC62
	mov	w0, 14
	mov	x1, x25
	bl	dprint_vfmw
	ldr	w0, [x21, 3712]
	cbz	w0, .L590
	ldr	x24, .LC66
	mov	w19, 0
	ldr	x23, .LC68
	.p2align 2
.L593:
	add	x20, x22, x19, uxtw 3
	mov	w2, w19
	mov	x1, x24
	mov	w0, 14
	ldr	x3, [x20, 28024]
	ldrb	w5, [x3, 2]
	ldr	w4, [x3, 664]
	ldr	w3, [x3, 652]
	bl	dprint_vfmw
	ldr	x3, [x20, 28024]
	mov	w2, w19
	mov	x1, x23
	mov	w0, 14
	add	w19, w19, 1
	ldr	w3, [x3, 708]
	bl	dprint_vfmw
	ldr	w0, [x21, 3712]
	cmp	w0, w19
	bhi	.L593
.L590:
	mov	x1, x25
	mov	w0, 14
	bl	dprint_vfmw
.L586:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	DumpDPB, .-DumpDPB
	.align	3
.LC61:
	.xword	g_PrintEnable
	.align	3
.LC62:
	.xword	.LC6
	.align	3
.LC64:
	.xword	.LC63
	.align	3
.LC66:
	.xword	.LC65
	.align	3
.LC68:
	.xword	.LC67
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UpdateCurrFrameInfo
	.type	UpdateCurrFrameInfo, %function
UpdateCurrFrameInfo:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 61440
	mov	w2, 3
	ldr	x19, [x1, 2352]
	ldrb	w3, [x1, 1706]
	strb	w3, [x19]
	ldrb	w3, [x1, 1708]
	cbnz	w3, .L600
	ldrb	w2, [x1, 1709]
	mov	w0, 3
	cmp	w2, wzr
	csel	w2, w2, w0, eq
.L600:
	add	x3, x1, 1704
	strb	w2, [x19, 2]
	mov	w2, 3
	ldr	w0, [x3, 664]
	str	w0, [x19, 652]
	ldr	w0, [x3, 700]
	str	w0, [x19, 680]
	ldr	w0, [x3, 692]
	str	w0, [x19, 676]
	ldr	w0, [x3, 676]
	str	w0, [x19, 664]
	ldr	w0, [x3, 724]
	str	w0, [x19, 684]
	ldr	w0, [x3, 668]
	str	w0, [x19, 660]
	ldrb	w0, [x3, 9]
	str	w0, [x19, 672]
	ldrb	w0, [x3, 7]
	cmp	w0, 1
	csel	w0, w2, wzr, eq
	strb	w0, [x19, 3]
	ldrb	w4, [x3, 3]
	cmp	w4, 1
	beq	.L603
	cbz	w4, .L604
	cmp	w4, 2
	bne	.L599
	str	x19, [x19, 832]
	mov	w5, 1
	strb	w5, [x19, 792]
	ldrb	w5, [x3, 4]
	strb	w5, [x19, 793]
	ldrb	w5, [x3, 5]
	strb	w5, [x19, 794]
	ldr	w5, [x3, 684]
	str	w5, [x19, 804]
	ldr	w6, [x3, 692]
	str	w6, [x19, 812]
	ldr	w5, [x3, 700]
	str	w5, [x19, 808]
	str	wzr, [x19, 672]
	ldrb	w7, [x3, 1]
	cbz	w7, .L626
	ldr	w4, [x19, 760]
	orr	w0, w0, 2
	strb	w2, [x19, 1]
	mov	w2, 0
	add	w5, w5, w4
	str	w5, [x19, 680]
	str	w5, [x19, 712]
	ldrb	w3, [x3, 7]
	cmp	w3, 1
	csel	w0, w0, w2, eq
	strb	w0, [x19, 3]
	ldr	x0, [x1, 2304]
	cmn	x0, #1
	beq	.L612
	ldr	x2, [x19, 600]
	cmn	x2, #1
	beq	.L627
.L612:
	ldr	w2, [x19, 764]
.L630:
	cmp	w2, w6
	mov	x0, x19
	csel	w6, w2, w6, cs
	str	w6, [x19, 676]
	ldr	w1, [x1, 2380]
	str	w1, [x19, 664]
	bl	CombineFldsToFrm
.L599:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L604:
	strb	w2, [x19, 1]
	add	x1, x1, 1720
	strb	wzr, [x19, 696]
	mov	x2, 632
	str	x19, [x19, 736]
	add	x0, x19, 16
	ldrb	w23, [x3, 4]
	strb	w23, [x19, 697]
	ldrb	w22, [x3, 5]
	strb	w22, [x19, 698]
	ldr	w4, [x3, 680]
	str	w4, [x19, 708]
	ldr	w20, [x3, 692]
	str	w20, [x19, 716]
	ldr	w21, [x3, 700]
	str	w21, [x19, 712]
	ldr	w4, [x3, 684]
	str	w4, [x19, 756]
	ldr	w3, [x3, 688]
	str	w3, [x19, 804]
	bl	memcpy
	strb	w23, [x19, 745]
	strb	w22, [x19, 746]
	mov	w1, 1
	strb	w23, [x19, 793]
	mov	w0, 2
	strb	w1, [x19, 744]
	strb	w22, [x19, 794]
	strb	w0, [x19, 792]
	str	w21, [x19, 760]
	str	w20, [x19, 764]
	str	x19, [x19, 784]
	str	w21, [x19, 808]
	str	w20, [x19, 812]
	str	x19, [x19, 832]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L603:
	strb	w4, [x19, 744]
	str	x19, [x19, 784]
	ldrb	w5, [x3, 4]
	strb	w5, [x19, 745]
	ldrb	w5, [x3, 5]
	strb	w5, [x19, 746]
	ldr	w5, [x3, 684]
	str	w5, [x19, 756]
	ldr	w6, [x3, 692]
	str	w6, [x19, 764]
	ldr	w5, [x3, 700]
	str	w5, [x19, 760]
	str	wzr, [x19, 672]
	ldrb	w7, [x3, 1]
	cbz	w7, .L628
	ldr	w4, [x19, 808]
	orr	w0, w0, 1
	strb	w2, [x19, 1]
	mov	w2, 0
	add	w5, w5, w4
	str	w5, [x19, 680]
	str	w5, [x19, 712]
	ldrb	w3, [x3, 7]
	cmp	w3, 1
	csel	w0, w0, w2, eq
	strb	w0, [x19, 3]
	ldr	x0, [x1, 2304]
	cmn	x0, #1
	beq	.L608
	ldr	x2, [x19, 600]
	cmn	x2, #1
	beq	.L629
.L608:
	ldr	w2, [x19, 812]
	mov	x0, x19
	cmp	w2, w6
	csel	w6, w2, w6, cs
	str	w6, [x19, 676]
	ldr	w1, [x1, 2380]
	str	w1, [x19, 664]
	bl	CombineFldsToFrm
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L626:
	strb	w4, [x19, 1]
	mov	x2, 632
	str	w5, [x19, 680]
	add	x1, x1, 1720
	str	w5, [x19, 712]
	add	x0, x19, 16
	ldrb	w3, [x3, 7]
	cmp	w3, 1
	csel	w7, wzr, w4, ne
	strb	w7, [x19, 3]
	bl	memcpy
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L628:
	strb	w4, [x19, 1]
	mov	x2, 632
	str	w5, [x19, 680]
	add	x1, x1, 1720
	str	w5, [x19, 712]
	add	x0, x19, 16
	ldrb	w3, [x3, 7]
	cmp	w3, 1
	cset	w3, eq
	strb	w3, [x19, 3]
	bl	memcpy
	b	.L599
	.p2align 3
.L629:
	str	x0, [x19, 600]
	b	.L608
	.p2align 3
.L627:
	str	x0, [x19, 600]
	ldr	w2, [x19, 764]
	b	.L630
	.size	UpdateCurrFrameInfo, .-UpdateCurrFrameInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SimpleSlideDPB
	.type	SimpleSlideDPB, %function
SimpleSlideDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 24576
	ldr	w1, [x0, 3708]
	ldr	w0, [x0, 3704]
	cmp	w1, w0
	bcs	.L637
.L632:
	add	x19, x19, 61440
	ldr	w0, [x19, 2376]
	strb	wzr, [x19, 1708]
	cbz	w0, .L631
	mov	w0, 1
	strb	w0, [x19, 1709]
.L631:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L637:
	ldr	x1, [x19, 27896]
	mov	x0, x19
	bl	UnMarkFrameStoreRef
	mov	w1, 0
	mov	x0, x19
	bl	RemoveFrameStoreOutDPB
	b	.L632
	.size	SimpleSlideDPB, .-SimpleSlideDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReleaseNAL
	.type	ReleaseNAL, %function
ReleaseNAL:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w21, w0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L647
	ldr	x23, .LC72
	add	x19, x20, 8
	strb	wzr, [x20, 1]
	add	x22, x20, 72
	strb	wzr, [x20, 4]
.L642:
	ldr	x1, [x19]
	mov	w0, w21
	cbz	x1, .L641
	ldr	w1, [x19, 28]
	bl	SM_ReleaseStreamSeg
	ldr	w3, [x19, 8]
	mov	x1, x23
	ldr	x2, [x19]
	mov	w0, 7
	bl	dprint_vfmw
	str	xzr, [x19]
	str	wzr, [x19, 8]
	str	wzr, [x19, 20]
.L641:
	add	x19, x19, 32
	cmp	x19, x22
	bne	.L642
	strb	wzr, [x20]
	str	wzr, [x20, 76]
.L638:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L647:
	ldr	x2, .LC69
	mov	w3, 3961
	ldr	x1, .LC70
	mov	w0, 0
	bl	dprint_vfmw
	b	.L638
	.size	ReleaseNAL, .-ReleaseNAL
	.align	3
.LC69:
	.xword	.LC53
	.align	3
.LC70:
	.xword	.LC55
	.align	3
.LC72:
	.xword	.LC71
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ClearCurrNal
	.type	ClearCurrNal, %function
ClearCurrNal:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, [x19, 632]
	cbz	x1, .L649
	add	x0, x19, 65536
	ldr	w0, [x0, 1644]
	bl	ReleaseNAL
	str	xzr, [x19, 632]
.L649:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ClearCurrNal, .-ClearCurrNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ClearCurrSlice
	.type	ClearCurrSlice, %function
ClearCurrSlice:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 65536
	bl	_mcount
	ldr	x1, .LC74
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x20, 632]
	cbz	x1, .L654
	ldr	w0, [x19, 1644]
	bl	ReleaseNAL
	str	xzr, [x20, 632]
.L654:
	ldr	w1, [x19, 1600]
	mov	w0, 0
	add	w1, w1, 1
	str	w1, [x19, 1600]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ClearCurrSlice, .-ClearCurrSlice
	.align	3
.LC74:
	.xword	.LC73
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ClearAllNal
	.type	ClearAllNal, %function
ClearAllNal:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 640
	add	x21, x20, 65536
	add	x20, x20, 12288
	bl	_mcount
	add	x20, x20, 2600
	b	.L660
	.p2align 3
.L659:
	add	x19, x19, 104
	cmp	x19, x20
	beq	.L662
.L660:
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	bne	.L659
	ldr	w0, [x21, 1644]
	mov	x1, x19
	add	x19, x19, 104
	bl	ReleaseNAL
	cmp	x19, x20
	bne	.L660
.L662:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	ClearAllNal, .-ClearAllNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ClearAllSlice
	.type	ClearAllSlice, %function
ClearAllSlice:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 65536
	add	x19, x19, 61440
	add	x19, x19, 3240
	add	x20, x21, 232
	bl	_mcount
	.p2align 2
.L665:
	ldr	x0, [x19]
	mov	x1, x0
	cbz	x0, .L664
	ldr	w0, [x21, 1644]
	bl	ReleaseNAL
	str	xzr, [x19]
.L664:
	add	x19, x19, 8
	cmp	x19, x20
	bne	.L665
	str	wzr, [x21, 1568]
	mov	w0, 0
	str	wzr, [x21, 1628]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	ClearAllSlice, .-ClearAllSlice
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_ClearCurrPic
	.type	H264_ClearCurrPic, %function
H264_ClearCurrPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	ClearAllSlice
	add	x0, x19, 20480
	mov	w4, 32
	ldr	w8, [x19, 14948]
	mov	w7, 23352
	movk	w7, 0x1, lsl 16
	mov	w6, 2
	strb	w4, [x0, 3226]
	add	x4, x0, 3072
	strb	wzr, [x0, 3224]
	mov	w5, 7
	strb	w6, [x0, 3225]
	mov	w3, 3
	str	w8, [x0, 3232]
	mov	w2, -1
	str	w5, [x0, 3236]
	mov	w1, 262144
	str	w7, [x0, 3240]
	stp	w3, w2, [x4, 176]
	stp	wzr, wzr, [x4, 184]
	str	w1, [x0, 3264]
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	H264_ClearCurrPic, .-H264_ClearCurrPic
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_ArrangeVahbMem
	.type	H264_ArrangeVahbMem, %function
H264_ArrangeVahbMem:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w20, w2
	mov	w19, w1
	mov	w22, w4
	bl	_mcount
	mov	w0, 8160
	sub	w2, w20, #32
	sub	w1, w19, #32
	cmp	w2, w0
	ccmp	w1, w0, 2, ls
	bhi	.L672
	ldr	x3, .LC77
	mov	x2, 20
	mov	w1, 0
	add	x0, x29, 56
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x0, [x21]
	stp	w19, w20, [x29, 60]
	stp	w19, w20, [x29, 68]
	ldr	w0, [x0, 28]
	cmp	w0, 24
	beq	.L688
	add	x0, x21, 24576
	mov	w1, 5
	sxtb	w4, w22
	strb	w1, [x29, 58]
	ldr	w0, [x0, 3704]
	add	w0, w0, 1
	strb	w0, [x29, 57]
.L681:
	mov	w0, 63
	strb	w4, [x29, 59]
	cmp	w19, w0
	ccmp	w20, w0, 0, hi
	bls	.L689
	add	x19, x21, 65536
	add	x1, x29, 56
	ldr	w0, [x19, 1644]
	bl	FSP_ConfigInstance
	cbnz	w0, .L677
	ldr	x1, [x21]
	add	x3, x29, 52
	ldr	w0, [x19, 1644]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
	cmp	w0, 2
	mov	w1, w0
	beq	.L690
	mov	w0, 1
	cbnz	w1, .L691
.L682:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L688:
	mov	w1, 1
	mov	w0, 5
	strb	w1, [x29, 57]
	mov	w4, 1
	strb	w0, [x29, 58]
	b	.L681
	.p2align 3
.L672:
	ldr	x1, .LC79
.L685:
	mov	w3, w20
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
.L692:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L689:
	ldr	x1, .LC81
	b	.L685
	.p2align 3
.L677:
	ldr	x1, .LC85
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L682
	.p2align 3
.L691:
	ldr	x1, .LC83
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L692
.L690:
	add	x0, x21, 8
	bl	ResetVoQueue
	mov	w0, -20
	b	.L692
	.size	H264_ArrangeVahbMem, .-H264_ArrangeVahbMem
	.align	3
.LC77:
	.xword	vfmw_Osal_Func_Ptr_S
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RepairList
	.type	RepairList, %function
RepairList:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x7, x19, 20480
	ldrb	w2, [x7, 1584]
	cmp	w2, 1
	beq	.L712
	cbz	w2, .L696
	cmp	w2, 2
	mov	w0, 0
	bne	.L724
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L724:
	ldr	x1, .LC87
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	ClearCurrSlice
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
.L696:
	mov	w11, 1
.L695:
	add	x6, x19, 28672
	add	x7, x7, 1624
	add	x6, x6, 24
	mov	x8, 0
	mov	x9, 0
	mov	w2, 0
	mov	w13, 1
	add	x12, x19, 61440
	.p2align 2
.L708:
	ldr	w0, [x7]
	cbz	w0, .L698
	ldr	x1, [x6]
	cbnz	x1, .L725
	sub	w3, w0, #1
	add	x10, x8, 3588
	add	x0, x6, 8
	add	x5, x10, x3, uxtw
	add	x5, x19, x5, lsl 3
	b	.L701
	.p2align 3
.L702:
	ldr	x4, [x0], 8
	cbnz	x4, .L699
.L701:
	cmp	x0, x5
	bne	.L702
	ldr	x0, [x19]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L726
	ldr	x9, [x12, 2352]
	add	x9, x9, 696
.L709:
	add	x3, x10, x3, uxtw
	mov	x0, x6
	add	x3, x19, x3, lsl 3
	cbz	x1, .L727
	.p2align 2
.L704:
	add	x0, x0, 8
	cmp	x0, x3
	beq	.L705
.L728:
	ldr	x1, [x0]
	cbnz	x1, .L704
.L727:
	str	x9, [x0]
	add	x0, x0, 8
	cmp	x0, x3
	bne	.L728
	.p2align 2
.L705:
	add	w2, w2, 1
	add	x7, x7, 4
	cmp	w2, w11
	add	x6, x6, 264
	add	x8, x8, 33
	bcc	.L708
.L730:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L698:
	ldr	x0, [x19]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L729
	str	w13, [x7]
	add	w2, w2, 1
	cmp	w2, w11
	add	x7, x7, 4
	ldr	x0, [x12, 2352]
	add	x8, x8, 33
	add	x0, x0, 696
	str	x0, [x6]
	add	x6, x6, 264
	bcc	.L708
	b	.L730
.L725:
	sub	w3, w0, #1
	mov	x4, x1
	add	x10, x8, 3588
	.p2align 2
.L699:
	mov	x9, x4
	b	.L709
.L712:
	mov	w11, 2
	b	.L695
.L729:
	ldr	x1, .LC91
	mov	w3, 0
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	ClearCurrSlice
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
.L726:
	ldr	x1, .LC89
	mov	w3, 0
	mov	x2, x9
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	ClearCurrSlice
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
	.size	RepairList, .-RepairList
	.align	3
.LC87:
	.xword	.LC86
	.align	3
.LC89:
	.xword	.LC88
	.align	3
.LC91:
	.xword	.LC90
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetShortTermPicPoint
	.type	GetShortTermPicPoint, %function
GetShortTermPicPoint:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	add	x0, x20, 20480
	mov	w5, 0
	ldrb	w1, [x0, 1585]
	cbz	w1, .L732
	ldrb	w0, [x0, 1586]
	mov	w5, 2
	cmp	w0, wzr
	csinc	w5, w5, wzr, ne
.L732:
	add	x0, x20, 24576
	ldr	w2, [x0, 3712]
	cbz	w2, .L740
	sub	w2, w2, #1
	add	x0, x0, 3448
	add	x2, x2, 3504
	add	x4, x20, x2, lsl 3
	b	.L737
	.p2align 3
.L750:
	cmp	w3, 3
	beq	.L749
.L735:
	add	x0, x0, 8
	cmp	x0, x4
	beq	.L740
.L737:
	ldr	x2, [x0]
	ldrb	w3, [x2, 2]
	cbz	w5, .L750
	tbz	x3, 0, .L736
	ldr	w6, [x2, 744]
	and	w6, w6, 16776960
	cmp	w6, 65536
	beq	.L751
.L736:
	tbz	x3, 1, .L735
	ldr	w3, [x2, 792]
	and	w3, w3, 16776960
	cmp	w3, 65536
	bne	.L735
	ldr	w1, [x2, 800]
	cmp	w19, w1
	bne	.L735
	add	x0, x2, 792
	b	.L733
	.p2align 3
.L751:
	ldr	w1, [x2, 752]
	cmp	w1, w19
	bne	.L736
	add	x0, x2, 744
	b	.L733
	.p2align 3
.L749:
	ldr	w3, [x2, 696]
	and	w3, w3, 16776960
	cmp	w3, 65536
	bne	.L735
	ldr	w1, [x2, 704]
	cmp	w19, w1
	bne	.L735
	add	x0, x2, 696
	b	.L733
	.p2align 3
.L740:
	mov	x0, 0
.L733:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	GetShortTermPicPoint, .-GetShortTermPicPoint
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetLongTermPicPoint
	.type	GetLongTermPicPoint, %function
GetLongTermPicPoint:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	add	x0, x20, 20480
	mov	w5, 0
	ldrb	w1, [x0, 1585]
	cbz	w1, .L753
	ldrb	w0, [x0, 1586]
	mov	w5, 2
	cmp	w0, wzr
	csinc	w5, w5, wzr, ne
.L753:
	add	x0, x20, 24576
	ldr	w2, [x0, 3716]
	cbz	w2, .L761
	sub	w2, w2, #1
	add	x0, x0, 3576
	add	x2, x2, 3520
	add	x4, x20, x2, lsl 3
	b	.L758
	.p2align 3
.L771:
	cmp	w3, 3
	beq	.L770
.L756:
	add	x0, x0, 8
	cmp	x0, x4
	beq	.L761
.L758:
	ldr	x2, [x0]
	ldrb	w3, [x2, 2]
	cbz	w5, .L771
	tbz	x3, 0, .L757
	ldr	w6, [x2, 744]
	and	w6, w6, 16776960
	cmp	w6, 256
	beq	.L772
.L757:
	tbz	x3, 1, .L756
	ldr	w3, [x2, 792]
	and	w3, w3, 16776960
	cmp	w3, 256
	bne	.L756
	ldr	w1, [x2, 796]
	cmp	w19, w1
	bne	.L756
	add	x0, x2, 792
	b	.L754
	.p2align 3
.L772:
	ldr	w1, [x2, 748]
	cmp	w1, w19
	bne	.L757
	add	x0, x2, 744
	b	.L754
	.p2align 3
.L770:
	ldr	w3, [x2, 696]
	and	w3, w3, 16776960
	cmp	w3, 256
	bne	.L756
	ldr	w1, [x2, 700]
	cmp	w19, w1
	bne	.L756
	add	x0, x2, 696
	b	.L754
	.p2align 3
.L761:
	mov	x0, 0
.L754:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	GetLongTermPicPoint, .-GetLongTermPicPoint
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReorderSTList
	.type	ReorderSTList, %function
ReorderSTList:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x23, x0
	mov	x0, x30
	mov	w22, w3
	mov	x21, x4
	mov	w20, w2
	mov	x19, x1
	bl	_mcount
	mov	w1, w22
	mov	x0, x23
	bl	GetShortTermPicPoint
	ldr	w5, [x21]
	add	w2, w20, 1
	cmp	w2, w5
	ble	.L774
	mov	w1, w2
	.p2align 2
.L775:
	add	x5, x19, x1, sxtw 3
	ldr	x5, [x5, -8]
	str	x5, [x19, w1, sxtw 3]
	sub	w1, w1, #1
	ldr	w5, [x21]
	cmp	w5, w1
	blt	.L775
.L774:
	add	w1, w5, 1
	str	w1, [x21]
	str	x0, [x19, w5, sxtw 3]
	ldr	w0, [x21]
	cmp	w2, w0
	mov	w4, w0
	blt	.L773
	.p2align 2
.L783:
	ldr	x1, [x19, w0, sxtw 3]
	add	w0, w0, 1
	cbz	x1, .L777
	ldrb	w5, [x1, 1]
	cbnz	w5, .L778
	ldr	w5, [x1, 8]
	cmp	w22, w5
	beq	.L777
.L778:
	str	x1, [x19, w4, sxtw 3]
	add	w4, w4, 1
.L777:
	cmp	w2, w0
	bge	.L783
.L773:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	ReorderSTList, .-ReorderSTList
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReorderLTList
	.type	ReorderLTList, %function
ReorderLTList:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x23, x0
	mov	x0, x30
	mov	w22, w3
	mov	x21, x4
	mov	w20, w2
	mov	x19, x1
	bl	_mcount
	mov	w1, w22
	mov	x0, x23
	bl	GetLongTermPicPoint
	ldr	w5, [x21]
	add	w2, w20, 1
	cmp	w2, w5
	ble	.L788
	mov	w1, w2
	.p2align 2
.L789:
	add	x5, x19, x1, sxtw 3
	ldr	x5, [x5, -8]
	str	x5, [x19, w1, sxtw 3]
	sub	w1, w1, #1
	ldr	w5, [x21]
	cmp	w5, w1
	blt	.L789
.L788:
	add	w1, w5, 1
	str	w1, [x21]
	str	x0, [x19, w5, sxtw 3]
	ldr	w0, [x21]
	cmp	w2, w0
	mov	w4, w0
	blt	.L787
	.p2align 2
.L799:
	ldr	x1, [x19, w0, sxtw 3]
	add	w0, w0, 1
	cbz	x1, .L791
	ldrb	w5, [x1, 1]
	cbz	w5, .L792
	ldr	w5, [x1, 4]
	cmp	w22, w5
	beq	.L791
.L792:
	str	x1, [x19, w4, sxtw 3]
	add	w4, w4, 1
.L791:
	cmp	w2, w0
	bge	.L799
.L787:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	ReorderLTList, .-ReorderLTList
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReorderRefPiclist
	.type	ReorderRefPiclist, %function
ReorderRefPiclist:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	x22, x1
	mov	w21, w3
	mov	x25, x4
	mov	x28, x5
	str	x6, [x29, 104]
	bl	_mcount
	add	x0, x20, 20480
	str	wzr, [x29, 124]
	ldrb	w1, [x0, 1585]
	ldr	w2, [x0, 1592]
	cbz	w1, .L805
	mov	w1, 2208
	ldr	w26, [x0, 1600]
	ldr	x3, [x20, 14968]
	mov	w23, 2
	umull	x0, w2, w1
	ldr	x2, [x20, 14960]
	lsl	w26, w26, 1
	add	x1, x3, x0
	mov	w0, 4000
	add	w26, w26, 1
	ldr	w1, [x1, 28]
	umull	x0, w1, w0
	add	x0, x2, x0
	ldr	w0, [x0, 2196]
	add	w0, w0, 4
	lsl	w23, w23, w0
.L815:
	cmn	w21, #2
	beq	.L804
	ldr	w3, [x25]
	cmp	w3, 3
	beq	.L804
	add	w24, w21, 1
	mov	w27, w26
	lsl	x24, x24, 2
	mov	x19, 0
	b	.L808
	.p2align 3
.L809:
	ldr	x3, [x29, 104]
	ldr	w3, [x3, x19]
	bl	ReorderLTList
	cmp	x24, x19
	add	x19, x19, 4
	beq	.L804
.L814:
	ldr	w3, [x25, x19]
	cmp	w3, 3
	beq	.L804
.L808:
	cmp	w3, 1
	add	x4, x29, 124
	mov	w2, w21
	mov	x1, x22
	mov	x0, x20
	bhi	.L809
	ldr	w0, [x28, x19]
	cbnz	w3, .L810
	mvn	w0, w0
	add	w27, w27, w0
	add	w0, w27, w23
	cmp	w27, wzr
	csel	w27, w0, w27, lt
.L811:
	cmp	w26, w27
	sub	w3, w27, w23
	csel	w3, w3, w27, lt
	add	x4, x29, 124
	mov	w2, w21
	mov	x1, x22
	mov	x0, x20
	bl	ReorderSTList
	cmp	x24, x19
	add	x19, x19, 4
	bne	.L814
.L804:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L810:
	add	w0, w0, 1
	add	w27, w27, w0
	cmp	w23, w27
	sub	w0, w27, w23
	csel	w27, w0, w27, le
	b	.L811
	.p2align 3
.L805:
	mov	w1, 2208
	ldr	w26, [x0, 1600]
	ldr	x3, [x20, 14968]
	mov	w23, 1
	umull	x0, w2, w1
	ldr	x2, [x20, 14960]
	add	x1, x3, x0
	mov	w0, 4000
	ldr	w1, [x1, 28]
	umull	x0, w1, w0
	add	x0, x2, x0
	ldr	w0, [x0, 2196]
	add	w0, w0, 4
	lsl	w23, w23, w0
	b	.L815
	.size	ReorderRefPiclist, .-ReorderRefPiclist
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReorderListX
	.type	ReorderListX, %function
ReorderListX:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 20480
	bl	_mcount
	ldrb	w0, [x19, 1584]
	cmp	w0, 2
	beq	.L823
	ldrb	w1, [x19, 796]
	cbnz	w1, .L835
.L826:
	ldr	w1, [x19, 1636]
	cmp	w0, 1
	add	w0, w1, 1
	str	w0, [x19, 1624]
	bne	.L823
	ldrb	w0, [x19, 797]
	cbnz	w0, .L836
.L828:
	ldr	w0, [x19, 1640]
	add	w0, w0, 1
	str	w0, [x19, 1628]
.L823:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L835:
	add	x1, x20, 28672
	ldr	w3, [x19, 1636]
	mov	x0, x20
	add	x6, x19, 1328
	add	x5, x19, 1064
	add	x4, x19, 800
	add	x2, x19, 1624
	add	x1, x1, 24
	bl	ReorderRefPiclist
	ldrb	w0, [x19, 1584]
	b	.L826
	.p2align 3
.L836:
	add	x1, x20, 28672
	ldr	w3, [x19, 1640]
	add	x6, x19, 1456
	add	x5, x19, 1196
	add	x4, x19, 932
	add	x2, x19, 1628
	add	x1, x1, 288
	mov	x0, x20
	bl	ReorderRefPiclist
	b	.L828
	.size	ReorderListX, .-ReorderListX
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GenPiclistfromFrmlist
	.type	GenPiclistfromFrmlist, %function
GenPiclistfromFrmlist:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w21, w0
	mov	x0, x30
	mov	w20, w2
	mov	x19, x1
	mov	x25, x3
	mov	x24, x4
	mov	w23, w5
	bl	_mcount
	cmp	w20, 31
	mov	w22, 31
	csel	w22, w20, w22, ls
	cbnz	w23, .L859
	cmp	w21, 1
	ldr	x23, .LC93
	beq	.L899
.L839:
	cmp	w21, 2
	bne	.L848
	mov	w21, 0
	mov	w20, 0
	.p2align 2
.L850:
	cmp	w20, w22
	ccmp	w21, w22, 0, cs
	bcs	.L848
.L900:
	cmp	w21, w22
	bcc	.L883
	b	.L855
	.p2align 3
.L851:
	add	w21, w21, 1
	cmp	w22, w21
	bls	.L855
.L883:
	ldr	x0, [x19, w21, uxtw 3]
	add	x26, x19, x21, uxtw 3
	ldrb	w1, [x0, 1]
	tbz	x1, 1, .L851
	add	x0, x0, 792
	blr	x23
	cbz	w0, .L851
	ldr	w1, [x24]
	add	w21, w21, 1
	ldr	x0, [x26]
	add	x0, x0, 792
	str	x0, [x25, w1, uxtw 3]
	ldr	w0, [x24]
	add	w0, w0, 1
	str	w0, [x24]
.L855:
	cmp	w20, w22
	bcc	.L882
	b	.L850
	.p2align 3
.L856:
	add	w20, w20, 1
	cmp	w22, w20
	bls	.L850
.L882:
	ldr	x0, [x19, w20, uxtw 3]
	add	x26, x19, x20, uxtw 3
	ldrb	w1, [x0, 1]
	tbz	x1, 0, .L856
	add	x0, x0, 744
	blr	x23
	cbz	w0, .L856
	ldr	w1, [x24]
	add	w20, w20, 1
	ldr	x0, [x26]
	cmp	w20, w22
	ccmp	w21, w22, 0, cs
	add	x0, x0, 744
	str	x0, [x25, w1, uxtw 3]
	ldr	w0, [x24]
	add	w0, w0, 1
	str	w0, [x24]
	bcc	.L900
.L848:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L859:
	cmp	w21, 1
	ldr	x23, .LC92
	bne	.L839
.L899:
	mov	w21, 0
	mov	w20, 0
	.p2align 2
.L840:
	cmp	w20, w22
	ccmp	w21, w22, 0, cs
	bcs	.L848
	cmp	w20, w22
	bcc	.L881
	b	.L898
	.p2align 3
.L841:
	add	w20, w20, 1
	cmp	w20, w22
	bcs	.L898
.L881:
	ldr	x0, [x19, w20, uxtw 3]
	add	x26, x19, x20, uxtw 3
	ldrb	w1, [x0, 1]
	tbz	x1, 0, .L841
	add	x0, x0, 744
	blr	x23
	cbz	w0, .L841
	ldr	w1, [x24]
	add	w20, w20, 1
	ldr	x0, [x26]
	add	x0, x0, 744
	str	x0, [x25, w1, uxtw 3]
	ldr	w0, [x24]
	add	w0, w0, 1
	str	w0, [x24]
	.p2align 2
.L898:
	cmp	w21, w22
	bcs	.L840
	ldr	x0, [x19, w21, uxtw 3]
	add	x26, x19, x21, uxtw 3
	ldrb	w1, [x0, 1]
	tbnz	x1, 1, .L901
.L846:
	add	w21, w21, 1
	b	.L898
	.p2align 3
.L901:
	add	x0, x0, 792
	blr	x23
	cbz	w0, .L846
	ldr	w1, [x24]
	add	w21, w21, 1
	ldr	x0, [x26]
	add	x0, x0, 792
	str	x0, [x25, w1, uxtw 3]
	ldr	w0, [x24]
	add	w0, w0, 1
	str	w0, [x24]
	b	.L840
	.size	GenPiclistfromFrmlist, .-GenPiclistfromFrmlist
	.align	3
.LC92:
	.xword	IsLTRefFlg
	.align	3
.LC93:
	.xword	IsSTRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InitListX
	.type	InitListX, %function
InitListX:
	stp	x29, x30, [sp, -480]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 20480
	add	x22, x19, 61440
	bl	_mcount
	ldrb	w0, [x20, 1584]
	cbnz	w0, .L903
	ldrb	w0, [x22, 1707]
	add	x21, x19, 24576
	cbnz	w0, .L1023
	ldr	w0, [x21, 3712]
	cbz	w0, .L970
	sub	w3, w0, #1
	mov	w23, 0
	add	x3, x3, 3504
	add	x0, x21, 3448
	add	x3, x19, x3, lsl 3
	b	.L909
	.p2align 3
.L908:
	cmp	x3, x0
	beq	.L907
.L909:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 2]
	cmp	w2, 3
	bne	.L908
	ldr	w2, [x1, 696]
	and	w2, w2, 16776960
	cmp	w2, 65536
	bne	.L908
	add	x2, x19, x23, uxtw 3
	add	x1, x1, 696
	cmp	x3, x0
	add	w23, w23, 1
	str	x1, [x2, 28696]
	bne	.L909
	.p2align 2
.L907:
	add	x0, x19, 28672
	ldr	x3, .LC94
	mov	w1, w23
	mov	w2, 8
	add	x0, x0, 24
	bl	qsort
	str	w23, [x20, 1624]
	ldr	w1, [x21, 3716]
	cbz	w1, .L971
	sub	w3, w1, #1
	add	x0, x21, 3576
	add	x3, x3, 3520
	mov	w21, w23
	add	x3, x19, x3, lsl 3
	b	.L912
	.p2align 3
.L911:
	cmp	x0, x3
	beq	.L1024
.L912:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 2]
	cmp	w2, 3
	bne	.L911
	ldr	w2, [x1, 696]
	and	w2, w2, 16776960
	cmp	w2, 256
	bne	.L911
	add	x2, x19, x21, uxtw 3
	add	x1, x1, 696
	cmp	x0, x3
	add	w21, w21, 1
	str	x1, [x2, 28696]
	bne	.L912
	.p2align 2
.L1024:
	sub	w1, w21, w23
.L910:
	uxtw	x0, w23
	ldr	x3, .LC95
	add	x0, x0, 3586
	mov	w2, 8
	add	x0, x19, x0, lsl 3
	add	x0, x0, 8
	bl	qsort
	str	w21, [x20, 1624]
	mov	w2, w21
	str	wzr, [x20, 1628]
	cbz	w2, .L1025
.L918:
	ldr	w0, [x20, 1636]
	mov	w1, 0
	str	wzr, [x20, 1628]
	add	w0, w0, 1
	cmp	w0, w2
	csel	w0, w0, w2, ls
	str	w0, [x20, 1624]
	cmp	w0, 32
	bhi	.L965
	add	x2, x19, x0, uxtw 3
	add	w0, w0, 1
	cmp	w0, 33
	str	xzr, [x2, 28696]
	bne	.L963
	.p2align 2
.L964:
	cmp	w1, 32
	bhi	.L962
	.p2align 2
.L965:
	add	x0, x19, x1, uxtw 3
	add	w1, w1, 1
	cmp	w1, 33
	str	xzr, [x0, 28960]
	bne	.L965
.L962:
	mov	w0, 0
.L1014:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 480
	ret
	.p2align 3
.L903:
	ldrb	w0, [x22, 1707]
	add	x21, x19, 24576
	cbz	w0, .L924
	ldr	w0, [x21, 3712]
	cbz	w0, .L1026
	sub	w3, w0, #1
	mov	w23, 0
	add	x3, x3, 3504
	add	x0, x21, 3448
	add	x3, x19, x3, lsl 3
	.p2align 2
.L943:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 1]
	cbz	w2, .L942
	ldr	w4, [x1, 664]
	add	x2, x29, 480
	ldr	w5, [x22, 2380]
	add	x2, x2, x23, uxtw 3
	sub	x2, x2, #4096
	cmp	w5, w4
	blt	.L942
	add	w23, w23, 1
	str	x1, [x2, 3712]
.L942:
	cmp	x0, x3
	bne	.L943
	add	x26, x29, 96
	ldr	x3, .LC102
	mov	w2, 8
	mov	w1, w23
	mov	x0, x26
	bl	qsort
	ldr	w24, [x21, 3712]
	cbz	w24, .L944
.L968:
	sub	w1, w24, #1
	add	x0, x21, 3448
	add	x1, x1, 3504
	mov	w25, w23
	add	x1, x19, x1, lsl 3
	.p2align 2
.L946:
	ldr	x2, [x0]
	add	x0, x0, 8
	ldrb	w3, [x2, 1]
	cbz	w3, .L945
	ldr	w4, [x2, 664]
	add	x3, x29, 480
	ldr	w5, [x22, 2380]
	add	x3, x3, x25, uxtw 3
	sub	x3, x3, #4096
	cmp	w5, w4
	bge	.L945
	add	w25, w25, 1
	str	x2, [x3, 3712]
.L945:
	cmp	x0, x1
	bne	.L946
	sub	w24, w25, w23
	ldr	x3, .LC103
	mov	w2, 8
	mov	w1, w24
	add	x0, x26, x23, uxtw 3
	bl	qsort
	cbz	w23, .L947
.L967:
	mov	x0, 0
	.p2align 2
.L948:
	add	w1, w24, w0
	add	x3, x29, 480
	ldr	x2, [x26, x0, lsl 3]
	add	x0, x0, 1
	add	x1, x3, x1, lsl 3
	cmp	w23, w0
	str	x2, [x1, -256]
	bhi	.L948
.L947:
	cmp	w25, w23
	bls	.L949
	mov	w0, w23
	.p2align 2
.L950:
	add	x2, x29, 480
	sub	w1, w0, w23
	add	x2, x2, x0, uxtw 3
	add	x3, x29, 480
	sub	x2, x2, #4096
	add	x1, x3, x1, lsl 3
	add	w0, w0, 1
	cmp	w25, w0
	ldr	x2, [x2, 3712]
	str	x2, [x1, -256]
	bne	.L950
.L949:
	str	wzr, [x20, 1624]
	add	x23, x19, 28672
	str	wzr, [x20, 1628]
	add	x24, x23, 24
	add	x27, x20, 1624
	mov	x1, x26
	ldrb	w0, [x22, 1707]
	mov	w2, w25
	mov	w5, 0
	mov	x4, x27
	mov	x3, x24
	add	x23, x23, 288
	add	x26, x20, 1628
	bl	GenPiclistfromFrmlist
	ldrb	w0, [x22, 1707]
	mov	w2, w25
	mov	w5, 0
	mov	x4, x26
	mov	x3, x23
	add	x1, x29, 224
	add	x25, x29, 352
	bl	GenPiclistfromFrmlist
	ldr	w28, [x21, 3716]
	cbz	w28, .L951
	add	x21, x21, 3576
	mov	x0, 0
	add	x25, x29, 352
	.p2align 2
.L952:
	ldr	x1, [x21], 8
	str	x1, [x25, x0, lsl 3]
	add	x0, x0, 1
	cmp	w28, w0
	bhi	.L952
.L951:
	ldr	x3, .LC97
	mov	w2, 8
	mov	w1, w28
	mov	x0, x25
	bl	qsort
	ldrb	w0, [x22, 1707]
	mov	w5, 1
	mov	x4, x27
	mov	x3, x24
	mov	w2, w28
	mov	x1, x25
	bl	GenPiclistfromFrmlist
	ldrb	w0, [x22, 1707]
	mov	x4, x26
	mov	x3, x23
	mov	x1, x25
	mov	w5, 1
	mov	w2, w28
	bl	GenPiclistfromFrmlist
	ldr	w3, [x20, 1624]
	ldr	w4, [x20, 1628]
	cmp	w4, w3
	cset	w1, eq
.L941:
	cmp	w3, 1
	cset	w0, hi
	tst	w1, w0
	beq	.L953
	cbz	w3, .L954
	ldr	x6, [x19, 28696]
	ldr	x0, [x19, 28960]
	cmp	x6, x0
	bne	.L953
	sub	w0, w3, #1
	mov	x2, x19
	add	x0, x19, x0, lsl 3
.L956:
	cmp	x0, x2
	beq	.L958
	ldr	x5, [x2, 28704]
	add	x2, x2, 8
	ldr	x1, [x2, 28960]
	cmp	x5, x1
	beq	.L956
	.p2align 2
.L953:
	ldr	x0, [x19, 22104]
	cbz	x0, .L1027
	ldr	w0, [x20, 1636]
	ldr	w1, [x20, 1640]
	add	w0, w0, 1
	add	w1, w1, 1
	cmp	w0, w3
	csel	w0, w0, w3, ls
	cmp	w1, w4
	csel	w1, w1, w4, ls
	str	w0, [x20, 1624]
	cmp	w0, 32
	str	w1, [x20, 1628]
	bhi	.L964
	.p2align 2
.L963:
	add	x2, x19, x0, uxtw 3
	add	w0, w0, 1
	cmp	w0, 33
	str	xzr, [x2, 28696]
	bne	.L963
	b	.L964
	.p2align 3
.L924:
	ldr	w0, [x21, 3712]
	cbz	w0, .L972
	sub	w3, w0, #1
	mov	w23, 0
	add	x3, x3, 3504
	add	x0, x21, 3448
	add	x3, x19, x3, lsl 3
	b	.L929
	.p2align 3
.L928:
	cmp	x0, x3
	beq	.L927
.L929:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 2]
	cmp	w2, 3
	bne	.L928
	ldr	w2, [x1, 708]
	add	x5, x19, x23, uxtw 3
	ldr	w4, [x22, 2384]
	add	x1, x1, 696
	cmp	w4, w2
	blt	.L928
	str	x1, [x5, 28696]
	cmp	x0, x3
	add	w23, w23, 1
	bne	.L929
	.p2align 2
.L927:
	add	x25, x19, 28672
	ldr	x3, .LC100
	mov	w2, 8
	mov	w1, w23
	add	x0, x25, 24
	bl	qsort
	ldr	w24, [x21, 3712]
	cbz	w24, .L930
	sub	w3, w24, #1
	add	x0, x21, 3448
	add	x3, x3, 3504
	mov	w26, w23
	add	x3, x19, x3, lsl 3
	b	.L932
	.p2align 3
.L931:
	cmp	x0, x3
	beq	.L1028
.L932:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 2]
	cmp	w2, 3
	bne	.L931
	ldr	w2, [x1, 708]
	add	x5, x19, x26, uxtw 3
	ldr	w4, [x22, 2384]
	add	x1, x1, 696
	cmp	w4, w2
	bge	.L931
	str	x1, [x5, 28696]
	cmp	x0, x3
	add	w26, w26, 1
	bne	.L932
	.p2align 2
.L1028:
	uxtw	x0, w23
	uxtw	x22, w26
	add	x0, x0, 3586
	sub	w24, w26, w23
	ldr	x3, .LC101
	add	x22, x22, 3586
	add	x0, x19, x0, lsl 3
	mov	w2, 8
	add	x0, x0, 8
	mov	w1, w24
	add	x22, x19, x22, lsl 3
	bl	qsort
	add	x22, x22, 8
	cbz	w23, .L934
.L966:
	add	x25, x25, 24
	mov	w0, 0
	.p2align 2
.L935:
	add	w1, w24, w0
	ldr	x2, [x25], 8
	add	w0, w0, 1
	add	x1, x19, x1, lsl 3
	cmp	w0, w23
	str	x2, [x1, 28960]
	bcc	.L935
.L934:
	cmp	w26, w23
	bls	.L936
	mov	w0, w23
	.p2align 2
.L937:
	sub	w1, w0, w23
	add	x2, x19, x0, uxtw 3
	add	w0, w0, 1
	add	x1, x19, x1, lsl 3
	cmp	w0, w26
	ldr	x2, [x2, 28696]
	str	x2, [x1, 28960]
	bne	.L937
.L936:
	str	w26, [x20, 1624]
	str	w26, [x20, 1628]
	ldr	w1, [x21, 3716]
	cbz	w1, .L973
	sub	w3, w1, #1
	add	x0, x21, 3576
	add	x3, x3, 3520
	mov	w21, w26
	add	x3, x19, x3, lsl 3
	b	.L940
	.p2align 3
.L939:
	cmp	x3, x0
	beq	.L1029
.L940:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 1]
	cmp	w2, 3
	bne	.L939
	ldrb	w2, [x1, 697]
	cmp	w2, 1
	bne	.L939
	add	x2, x19, x21, uxtw 3
	add	x1, x1, 696
	cmp	x3, x0
	add	w21, w21, 1
	str	x1, [x2, 28696]
	str	x1, [x2, 28960]
	bne	.L940
	.p2align 2
.L1029:
	sub	w1, w21, w26
.L938:
	ldr	x23, .LC95
	mov	w2, 8
	mov	x0, x22
	mov	x3, x23
	bl	qsort
	ldr	w0, [x20, 1624]
	mov	x3, x23
	mov	w2, 8
	sub	w1, w21, w0
	uxtw	x0, w0
	add	x0, x0, 3619
	add	x0, x19, x0, lsl 3
	add	x0, x0, 8
	bl	qsort
	str	w21, [x20, 1624]
	mov	w4, w21
	mov	w3, w21
	mov	w1, 1
	str	w21, [x20, 1628]
	b	.L941
	.p2align 3
.L1023:
	ldr	w0, [x21, 3712]
	mov	w23, 0
	cbz	w0, .L906
	sub	w4, w0, #1
	mov	w23, 0
	add	x4, x4, 3504
	add	x0, x21, 3448
	add	x4, x19, x4, lsl 3
	.p2align 2
.L915:
	ldr	x2, [x0]
	add	x1, x29, 480
	add	x1, x1, x23, uxtw 3
	add	x0, x0, 8
	sub	x1, x1, #4096
	cmp	x4, x0
	ldrb	w3, [x2, 2]
	cbz	w3, .L914
	add	w23, w23, 1
	str	x2, [x1, 3712]
.L914:
	bne	.L915
.L906:
	ldr	x3, .LC96
	mov	w1, w23
	mov	w2, 8
	add	x0, x29, 96
	add	x24, x19, 28672
	add	x26, x20, 1624
	bl	qsort
	str	wzr, [x20, 1624]
	add	x24, x24, 24
	mov	w2, w23
	ldrb	w0, [x22, 1707]
	mov	w5, 0
	mov	x4, x26
	add	x1, x29, 96
	mov	x3, x24
	add	x25, x29, 352
	bl	GenPiclistfromFrmlist
	ldr	w23, [x21, 3716]
	cbz	w23, .L916
	add	x21, x21, 3576
	mov	x0, 0
	add	x25, x29, 352
	.p2align 2
.L917:
	ldr	x1, [x21], 8
	str	x1, [x25, x0, lsl 3]
	add	x0, x0, 1
	cmp	w23, w0
	bhi	.L917
.L916:
	ldr	x3, .LC97
	mov	w2, 8
	mov	w1, w23
	mov	x0, x25
	bl	qsort
	ldrb	w0, [x22, 1707]
	mov	w2, w23
	mov	w5, 1
	mov	x4, x26
	mov	x3, x24
	mov	x1, x25
	bl	GenPiclistfromFrmlist
	str	wzr, [x20, 1628]
	ldr	w2, [x20, 1624]
	cbnz	w2, .L918
.L1025:
	ldr	x0, [x19]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L919
	ldrb	w0, [x22, 1707]
	cbz	w0, .L1030
	cmp	w0, 1
	ldr	x0, [x22, 2352]
	beq	.L1031
	add	x0, x0, 792
	mov	w2, 1
	str	x0, [x19, 28696]
	b	.L918
	.p2align 3
.L1030:
	ldr	x0, [x22, 2352]
	mov	w2, 1
	add	x0, x0, 696
	str	x0, [x19, 28696]
	b	.L918
.L954:
	ldr	x6, [x19, 28960]
.L958:
	ldr	x0, [x19, 28968]
	str	x0, [x19, 28960]
	str	x6, [x19, 28968]
	b	.L953
.L1031:
	add	x0, x0, 744
	mov	w2, 1
	str	x0, [x19, 28696]
	b	.L918
.L1026:
	add	x26, x29, 96
	ldr	x3, .LC102
	mov	w2, 8
	mov	w1, 0
	mov	x0, x26
	mov	w23, 0
	bl	qsort
	ldr	w24, [x21, 3712]
	cbnz	w24, .L968
	ldr	x3, .LC103
	mov	w2, 8
	mov	w1, 0
	mov	x0, x26
	mov	w25, 0
	bl	qsort
	b	.L949
	.p2align 3
.L972:
	mov	w23, 0
	b	.L927
.L930:
	uxtw	x22, w23
	ldr	x3, .LC101
	add	x22, x22, 3586
	mov	w2, 8
	mov	w1, 0
	mov	w26, w23
	add	x22, x19, x22, lsl 3
	add	x22, x22, 8
	mov	x0, x22
	bl	qsort
	cbnz	w23, .L966
	b	.L936
	.p2align 3
.L973:
	mov	w21, w26
	b	.L938
.L971:
	mov	w21, w23
	b	.L910
.L970:
	mov	w23, 0
	b	.L907
.L944:
	ldr	x3, .LC103
	mov	w2, 8
	mov	w1, 0
	add	x0, x26, x23, uxtw 3
	mov	w25, w23
	bl	qsort
	cbnz	w23, .L967
	b	.L949
	.p2align 3
.L919:
	ldr	x1, .LC99
.L1019:
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	ClearCurrSlice
	mov	w0, -1
	b	.L1014
.L1027:
	ldr	x1, .LC105
	b	.L1019
	.size	InitListX, .-InitListX
	.align	3
.LC94:
	.xword	compare_pic_by_pic_num_desc
	.align	3
.LC95:
	.xword	compare_pic_by_lt_pic_num_asc
	.align	3
.LC96:
	.xword	compare_fs_by_frame_num_desc
	.align	3
.LC97:
	.xword	compare_fs_by_lt_pic_idx_asc
	.align	3
.LC99:
	.xword	.LC98
	.align	3
.LC100:
	.xword	compare_pic_by_poc_desc
	.align	3
.LC101:
	.xword	compare_pic_by_poc_asc
	.align	3
.LC102:
	.xword	compare_fs_by_poc_desc
	.align	3
.LC103:
	.xword	compare_fs_by_poc_asc
	.align	3
.LC105:
	.xword	.LC104
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DumpList
	.type	DumpList, %function
DumpList:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC106
	ldr	w0, [x0]
	tbz	x0, 13, .L1032
	mov	x0, x19
	bl	DumpList.part.7
.L1032:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	DumpList, .-DumpList
	.align	3
.LC106:
	.xword	g_PrintEnable
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FindNearestPOCPicId
	.type	FindNearestPOCPicId, %function
FindNearestPOCPicId:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x2, x19, 24576
	ldr	w0, [x2, 3708]
	cbz	w0, .L1041
	add	x1, x19, 61440
	ldr	x3, [x19, 27896]
	cmp	w0, 1
	ldr	w7, [x1, 2380]
	ldr	w1, [x3, 664]
	sub	w1, w7, w1
	sxtw	x1, w1
	eor	x6, x1, x1, asr 63
	sub	x6, x6, x1, asr 63
	bls	.L1042
	sub	w0, w0, #2
	add	x2, x2, 3328
	add	x1, x0, 3489
	mov	w0, 0
	add	x5, x19, x1, lsl 3
	.p2align 2
.L1040:
	ldr	x4, [x2]
	add	x2, x2, 8
	ldr	w1, [x4, 664]
	sub	w1, w7, w1
	sxtw	x1, w1
	eor	x3, x1, x1, asr 63
	sub	x3, x3, x1, asr 63
	cmp	w3, w6
	bge	.L1039
	ldr	w0, [x4, 164]
	mov	w6, w3
.L1039:
	cmp	x2, x5
	bne	.L1040
.L1038:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1042:
	mov	w0, 0
	b	.L1038
.L1041:
	mov	w0, -1
	b	.L1038
	.size	FindNearestPOCPicId, .-FindNearestPOCPicId
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FindMinRefIdx
	.type	FindMinRefIdx, %function
FindMinRefIdx:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 20480
	ldrb	w1, [x0, 1584]
	cmp	w1, 2
	beq	.L1044
	add	x1, x19, 61440
	ldrb	w1, [x1, 1707]
	cbnz	w1, .L1074
	add	x6, x19, 24576
	ldr	w5, [x0, 1624]
	add	x6, x6, 3992
	mov	w4, 0
	add	x7, x19, 28672
	.p2align 2
.L1048:
	cbz	w5, .L1052
	add	x1, x7, 24
	mov	w3, 32
	mov	w0, 0
	b	.L1050
	.p2align 3
.L1049:
	add	w0, w0, 1
	cmp	w0, w5
	beq	.L1075
.L1050:
	ldr	x2, [x1]
	add	x1, x1, 8
	ldr	x2, [x2, 40]
	ldr	w2, [x2, 688]
	cmp	w2, w4
	bne	.L1049
	cmp	w3, w0
	csel	w3, w3, w0, ls
	add	w0, w0, 1
	stp	w3, w3, [x6]
	cmp	w0, w5
	bne	.L1050
.L1075:
	cmp	w3, 31
	bhi	.L1052
.L1051:
	add	w4, w4, 1
	add	x6, x6, 8
	cmp	w4, 16
	bne	.L1048
.L1044:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1074:
	ldr	w6, [x0, 1624]
	add	x7, x19, 24576
	add	x7, x7, 3992
	mov	w4, 0
	add	x8, x19, 28672
	cbz	w6, .L1056
	.p2align 2
.L1077:
	add	x2, x8, 24
	mov	w5, 32
	mov	w1, 0
	b	.L1054
	.p2align 3
.L1053:
	add	w1, w1, 1
	cmp	w1, w6
	beq	.L1076
.L1054:
	ldr	x0, [x2]
	add	x2, x2, 8
	ldr	x3, [x0, 40]
	ldrb	w0, [x0]
	cmp	w0, 2
	ldr	w0, [x3, 688]
	cset	w3, eq
	orr	w0, w3, w0, lsl 1
	cmp	w0, w4
	bne	.L1053
	cmp	w5, w1
	csel	w5, w5, w1, ls
	add	w1, w1, 1
	str	w5, [x7]
	cmp	w1, w6
	bne	.L1054
.L1076:
	cmp	w5, 31
	bhi	.L1056
.L1055:
	add	w4, w4, 1
	add	x7, x7, 4
	cmp	w4, 32
	beq	.L1044
	cbnz	w6, .L1077
	.p2align 2
.L1056:
	str	wzr, [x7]
	b	.L1055
	.p2align 3
.L1052:
	stp	wzr, wzr, [x6]
	b	.L1051
	.size	FindMinRefIdx, .-FindMinRefIdx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecList
	.type	DecList, %function
DecList:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 24576
	mov	w7, -1
	ldr	w0, [x1, 3708]
	cbz	w0, .L1079
	add	x2, x19, 61440
	ldr	x3, [x19, 27896]
	cmp	w0, 1
	ldr	w6, [x2, 2380]
	ldr	w2, [x3, 664]
	sub	w2, w6, w2
	sxtw	x2, w2
	eor	x5, x2, x2, asr 63
	sub	x5, x5, x2, asr 63
	bls	.L1088
	sub	w4, w0, #2
	add	x1, x1, 3328
	add	x4, x4, 3489
	mov	w7, 0
	add	x4, x19, x4, lsl 3
	.p2align 2
.L1081:
	ldr	x3, [x1]
	add	x1, x1, 8
	ldr	w0, [x3, 664]
	sub	w0, w6, w0
	sxtw	x0, w0
	eor	x2, x0, x0, asr 63
	sub	x2, x2, x0, asr 63
	cmp	w2, w5
	bge	.L1080
	ldr	w7, [x3, 164]
	mov	w5, w2
.L1080:
	cmp	x1, x4
	bne	.L1081
.L1079:
	add	x20, x19, 20480
	mov	w21, -1
	ldrb	w0, [x20, 1584]
	str	w21, [x20, 3208]
	cmp	w0, 2
	str	w7, [x20, 3212]
	beq	.L1098
	mov	x0, x19
	bl	InitListX
	cbnz	w0, .L1099
	ldr	x1, .LC110
	mov	w0, 13
	bl	dprint_vfmw
	ldr	x22, .LC111
	ldr	w0, [x22]
	tbnz	x0, 13, .L1100
.L1085:
	mov	x0, x19
	bl	ReorderListX
	mov	x0, x19
	bl	RepairList
	cbnz	w0, .L1089
	mov	x0, x19
	bl	FindMinRefIdx
	ldr	x0, [x19, 28696]
	cbz	x0, .L1090
	ldr	x0, [x0, 40]
	ldr	w0, [x0, 164]
.L1086:
	ldr	x1, .LC113
	mov	w21, 0
	str	w0, [x20, 3208]
	mov	w0, 13
	bl	dprint_vfmw
	ldr	w0, [x22]
	tbz	x0, 13, .L1083
	mov	x0, x19
	bl	DumpList.part.7
.L1083:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1098:
	str	wzr, [x20, 1624]
	mov	w21, 0
	str	wzr, [x20, 1628]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1100:
	mov	x0, x19
	bl	DumpList.part.7
	b	.L1085
	.p2align 3
.L1090:
	mov	w0, -1
	b	.L1086
	.p2align 3
.L1089:
	mov	w21, -1
	b	.L1083
.L1088:
	mov	w7, 0
	b	.L1079
.L1099:
	ldr	x1, .LC108
	mov	w0, 13
	bl	dprint_vfmw
	b	.L1083
	.size	DecList, .-DecList
	.align	3
.LC108:
	.xword	.LC107
	.align	3
.LC110:
	.xword	.LC109
	.align	3
.LC111:
	.xword	g_PrintEnable
	.align	3
.LC113:
	.xword	.LC112
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	NoPicOut
	.type	NoPicOut, %function
NoPicOut:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 65536
	ldr	w0, [x1, 300]
	cbz	w0, .L1108
	sub	w2, w0, #1
	mov	w4, 848
	mov	x3, 30076
	add	x0, x19, 28672
	add	x0, x0, 556
	umaddl	x3, w2, w4, x3
	add	x3, x19, x3
	b	.L1107
	.p2align 3
.L1115:
	ldrb	w2, [x0]
	cmp	w2, 1
	beq	.L1105
	add	x0, x0, 848
	cmp	x0, x3
	beq	.L1108
.L1107:
	ldr	w2, [x0, 664]
	cmp	w2, 1
	bne	.L1115
.L1105:
	strb	wzr, [x0, -3]
	strb	wzr, [x0, -2]
	add	x0, x0, 848
	cmp	x0, x3
	bne	.L1107
.L1108:
	ldr	w0, [x1, 304]
	cbz	w0, .L1101
	sub	w0, w0, #1
	add	x1, x1, 232
	add	x0, x0, 16384
	add	x0, x0, 59
	add	x0, x19, x0, lsl 2
	.p2align 2
.L1109:
	str	wzr, [x1], 4
	cmp	x1, x0
	bne	.L1109
.L1101:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	NoPicOut, .-NoPicOut
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetBackPicFromVOQueue
	.type	GetBackPicFromVOQueue, %function
GetBackPicFromVOQueue:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x20, x22, 65536
	bl	_mcount
	ldr	w0, [x20, 1644]
	bl	FSP_GetFspType
	cbz	w0, .L1133
.L1117:
	ldr	w0, [x20, 300]
	mov	w21, 0
	mov	w23, 848
	cbz	w0, .L1124
	.p2align 2
.L1128:
	uxtw	x1, w21
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 1
	sub	x0, x0, x1
	umull	x24, w21, w23
	add	x0, x22, x0, lsl 4
	add	x0, x0, 28672
	add	x24, x24, 28672
	add	x19, x24, 1112
	add	x24, x24, 1144
	add	x19, x22, x19
	add	x24, x22, x24
	strb	wzr, [x0, 553]
	strb	wzr, [x0, 554]
.L1122:
	ldr	x0, [x19]
	mov	x1, x0
	cbz	x0, .L1121
	ldr	w0, [x20, 1644]
	bl	FreeUsdByDec
	str	xzr, [x19]
.L1121:
	add	x19, x19, 8
	cmp	x19, x24
	bne	.L1122
	ldr	w0, [x20, 300]
	add	w21, w21, 1
	cmp	w0, w21
	bhi	.L1128
.L1124:
	ldr	w0, [x20, 304]
	cbz	w0, .L1116
	sub	w0, w0, #1
	add	x20, x20, 232
	add	x0, x0, 16384
	add	x0, x0, 59
	add	x22, x22, x0, lsl 2
	.p2align 2
.L1125:
	str	wzr, [x20], 4
	cmp	x20, x22
	bne	.L1125
.L1116:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L1133:
	add	x0, x22, 8
	bl	ResetVoQueue
	b	.L1117
	.size	GetBackPicFromVOQueue, .-GetBackPicFromVOQueue
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	wait_vo
	.type	wait_vo, %function
wait_vo:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	wait_vo, .-wait_vo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetReRangeFlag
	.type	GetReRangeFlag, %function
GetReRangeFlag:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x20, x1
	mov	w19, 4000
	bl	_mcount
	add	x1, x21, 20480
	mov	w0, 2208
	ldr	x5, [x21, 14968]
	ldr	x2, [x21, 14960]
	ldr	w1, [x1, 1592]
	ldr	w4, [x21, 14932]
	ldr	w3, [x21, 14936]
	umull	x0, w1, w0
	mov	w1, 2
	add	x0, x5, x0
	ldr	w0, [x0, 28]
	umull	x0, w0, w19
	add	x19, x2, x0
	ldrb	w0, [x19, 18]
	ldr	w5, [x19, 3252]
	sub	w0, w1, w0
	ldr	w2, [x19, 3248]
	madd	w0, w5, w0, w0
	add	w1, w2, 1
	cmp	w4, w1
	ccmp	w3, w0, 0, eq
	bne	.L1136
	add	x2, x21, 24576
	ldr	w5, [x19, 3272]
	ldr	w2, [x2, 3704]
	add	w2, w2, 1
	cmp	w5, w2
	beq	.L1139
.L1136:
	ldr	x2, .LC114
	ldr	x6, [x2]
	cbz	x6, .L1140
	add	x5, x21, 65536
	ubfiz	w2, w1, 4, 12
	ubfiz	w3, w3, 4, 12
	ubfiz	w1, w0, 4, 12
	ubfiz	w4, w4, 4, 12
	strh	w3, [x29, 58]
	ldr	w0, [x5, 1644]
	mov	w3, 8
	strh	w2, [x29, 60]
	add	x2, x29, 56
	strh	w1, [x29, 62]
	mov	w1, 2
	strh	w4, [x29, 56]
	blr	x6
.L1140:
	ldr	w2, [x19, 3272]
	mov	w3, 1
.L1137:
	add	x1, x21, 16384
	ldr	w4, [x19, 36]
	ldr	w5, [x21, 15012]
	mov	w0, w3
	ldr	w1, [x1, 1864]
	cmp	w5, w4
	ccmp	w1, w2, 0, eq
	cset	w1, ne
	orr	w1, w3, w1
	str	w1, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1139:
	mov	w3, 0
	b	.L1137
	.size	GetReRangeFlag, .-GetReRangeFlag
	.align	3
.LC114:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecPOC
	.type	DecPOC, %function
DecPOC:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 20480
	mov	w2, 2208
	ldr	x6, [x19, 14968]
	mov	w1, 4000
	ldr	x5, [x19, 14960]
	mov	w4, 1
	ldr	w3, [x0, 1592]
	ldrb	w7, [x0, 1587]
	umull	x2, w3, w2
	add	x2, x6, x2
	ldr	w2, [x2, 28]
	umull	x1, w2, w1
	add	x1, x5, x1
	ldr	w3, [x1, 2200]
	ldr	w2, [x1, 2196]
	cmp	w3, w4
	add	w2, w2, 4
	lsl	w2, w4, w2
	beq	.L1143
	cbz	w3, .L1144
	cmp	w3, 2
	bne	.L1141
	cmp	w7, 5
	beq	.L1198
	ldr	w1, [x0, 728]
	cbz	w1, .L1177
	ldr	w1, [x0, 768]
	mov	w3, 0
	mov	w2, 0
	str	wzr, [x0, 764]
	str	wzr, [x0, 776]
.L1178:
	str	w2, [x0, 772]
.L1180:
	ldr	w4, [x0, 1612]
	add	w2, w1, w2
	str	w2, [x0, 760]
	lsl	w1, w2, 1
	cbnz	w4, .L1181
	sub	w1, w1, #1
	str	w1, [x0, 748]
.L1182:
	ldrb	w2, [x0, 1585]
	cbnz	w2, .L1183
	str	w1, [x0, 736]
	str	w1, [x0, 740]
	str	w1, [x0, 744]
.L1176:
	ldr	w1, [x0, 768]
	str	w1, [x0, 764]
	str	w3, [x0, 776]
.L1141:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1144:
	ldr	w1, [x1, 2204]
	cmp	w7, 5
	add	w1, w1, 4
	lsl	w4, w4, w1
	beq	.L1150
	ldr	w1, [x0, 728]
	cbnz	w1, .L1148
	ldr	w5, [x0, 712]
	ldr	w3, [x0, 716]
	mov	w2, w5
.L1149:
	ldr	w1, [x0, 704]
	cmp	w1, w3
	bcs	.L1147
	sub	w6, w3, w1
	cmp	w6, w4, lsr 1
	bcc	.L1147
	add	w2, w2, w4
	str	w2, [x0, 720]
.L1151:
	ldrb	w3, [x0, 1585]
	cbnz	w3, .L1153
.L1201:
	ldr	w3, [x0, 708]
	add	w1, w1, w2
	str	w1, [x0, 736]
	add	w2, w1, w3
	str	w2, [x0, 740]
	cmp	w1, w2
	csel	w1, w1, w2, le
	str	w1, [x0, 748]
.L1154:
	ldr	w3, [x0, 764]
	ldr	w2, [x0, 768]
	str	w1, [x0, 744]
	cmp	w2, w3
	beq	.L1156
	str	w2, [x0, 764]
.L1156:
	ldr	w1, [x0, 1612]
	cbz	w1, .L1141
	ldr	w2, [x0, 704]
	ldr	w1, [x0, 720]
	str	w1, [x0, 712]
	str	w2, [x0, 716]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1143:
	cmp	w7, 5
	beq	.L1199
	ldr	w3, [x0, 728]
	cbz	w3, .L1159
	mov	w2, 0
	str	wzr, [x0, 764]
	str	wzr, [x0, 776]
.L1160:
	str	w2, [x0, 772]
.L1158:
	ldr	w2, [x1, 2216]
	cbz	w2, .L1162
	ldr	w2, [x0, 768]
	ldr	w5, [x0, 772]
	ldr	w6, [x0, 1612]
	add	w5, w5, w2
	str	w5, [x0, 760]
	cbnz	w6, .L1164
	cbz	w5, .L1165
	sub	w5, w5, #1
	str	w5, [x0, 760]
.L1164:
	str	wzr, [x0, 792]
	ldr	w2, [x1, 2216]
	cmp	w2, wzr
	ble	.L1166
.L1185:
	mov	w4, 0
	mov	w3, 0
	.p2align 2
.L1167:
	add	x2, x1, x3, sxtw 2
	add	w3, w3, 1
	ldr	w2, [x2, 2220]
	add	w4, w4, w2
	str	w4, [x0, 792]
	ldr	w2, [x1, 2216]
	cmp	w2, w3
	bgt	.L1167
.L1166:
	cbz	w5, .L1168
	sub	w5, w5, #1
	ldr	w7, [x0, 792]
	udiv	w2, w5, w2
	str	w2, [x0, 784]
	ldr	w4, [x1, 2216]
	udiv	w3, w5, w4
	mul	w2, w2, w7
	str	w2, [x0, 788]
	msub	w5, w3, w4, w5
	str	w5, [x0, 780]
	tbnz	w5, #31, .L1169
	mov	w3, 0
	.p2align 2
.L1170:
	add	x4, x1, x3, sxtw 2
	add	w3, w3, 1
	cmp	w5, w3
	ldr	w4, [x4, 2220]
	add	w2, w2, w4
	str	w2, [x0, 788]
	bge	.L1170
.L1169:
	cbnz	w6, .L1171
	ldr	w3, [x1, 2208]
	add	w2, w2, w3
	str	w2, [x0, 788]
.L1171:
	ldrb	w3, [x0, 1585]
	cbnz	w3, .L1172
	ldr	w3, [x0, 752]
	ldr	w4, [x0, 756]
	add	w2, w2, w3
	str	w2, [x0, 736]
	ldr	w1, [x1, 2212]
	add	w1, w2, w1
	add	w1, w1, w4
	str	w1, [x0, 740]
	cmp	w2, w1
	csel	w2, w2, w1, le
	str	w2, [x0, 748]
.L1173:
	ldr	w3, [x0, 768]
	ldr	w1, [x0, 772]
	str	w2, [x0, 744]
	str	w3, [x0, 764]
	str	w1, [x0, 776]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1148:
	ldr	w5, [x0, 732]
	cbz	w5, .L1200
.L1150:
	ldr	w1, [x0, 704]
	mov	w2, 0
	mov	w5, 0
	str	wzr, [x0, 712]
	str	wzr, [x0, 716]
.L1147:
	cmp	w1, w3
	bls	.L1152
	sub	w3, w1, w3
	cmp	w3, w4, lsr 1
	bls	.L1152
	sub	w2, w2, w4
	str	w2, [x0, 720]
	b	.L1151
	.p2align 3
.L1198:
	add	x1, x0, 512
	mov	w3, 0
	stp	wzr, wzr, [x1, 224]
	stp	wzr, wzr, [x1, 232]
	str	wzr, [x0, 772]
	b	.L1176
	.p2align 3
.L1199:
	str	wzr, [x0, 772]
	b	.L1158
	.p2align 3
.L1152:
	ldrb	w3, [x0, 1585]
	str	w5, [x0, 720]
	cbz	w3, .L1201
.L1153:
	ldrb	w3, [x0, 1586]
	add	w1, w1, w2
	cbnz	w3, .L1155
	str	w1, [x0, 736]
	str	w1, [x0, 748]
	b	.L1154
	.p2align 3
.L1162:
	ldr	w6, [x0, 1612]
	str	wzr, [x0, 760]
.L1165:
	str	wzr, [x0, 792]
	mov	w5, 0
	ldr	w2, [x1, 2216]
	cmp	w2, wzr
	bgt	.L1185
	.p2align 2
.L1168:
	mov	w2, 0
	str	wzr, [x0, 788]
	b	.L1169
	.p2align 3
.L1172:
	ldrb	w3, [x0, 1586]
	cbnz	w3, .L1174
	ldr	w1, [x0, 752]
	add	w2, w2, w1
	str	w2, [x0, 736]
	str	w2, [x0, 748]
	b	.L1173
	.p2align 3
.L1177:
	ldr	w3, [x0, 764]
	ldr	w1, [x0, 768]
	cmp	w1, w3
	ldr	w3, [x0, 776]
	bcs	.L1179
	add	w2, w2, w3
	str	w2, [x0, 772]
	mov	w3, w2
	b	.L1180
	.p2align 3
.L1159:
	ldr	w3, [x0, 764]
	ldr	w4, [x0, 768]
	cmp	w4, w3
	bcs	.L1161
	ldr	w3, [x0, 776]
	add	w2, w3, w2
	str	w2, [x0, 772]
	b	.L1158
	.p2align 3
.L1183:
	ldrb	w2, [x0, 1586]
	str	w1, [x0, 744]
	cbnz	w2, .L1184
	str	w1, [x0, 736]
	b	.L1176
	.p2align 3
.L1181:
	str	w1, [x0, 748]
	b	.L1182
	.p2align 3
.L1155:
	str	w1, [x0, 740]
	str	w1, [x0, 748]
	b	.L1154
	.p2align 3
.L1174:
	ldr	w3, [x1, 2212]
	ldr	w1, [x0, 752]
	add	w2, w2, w3
	add	w2, w2, w1
	str	w2, [x0, 740]
	str	w2, [x0, 748]
	b	.L1173
	.p2align 3
.L1200:
	ldr	w3, [x0, 736]
	mov	w2, 0
	str	wzr, [x0, 712]
	str	w3, [x0, 716]
	b	.L1149
	.p2align 3
.L1184:
	str	w1, [x0, 740]
	b	.L1176
.L1161:
	ldr	w2, [x0, 776]
	b	.L1160
.L1179:
	mov	w2, w3
	b	.L1178
	.size	DecPOC, .-DecPOC
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CalcPicNum
	.type	CalcPicNum, %function
CalcPicNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x2, x19, 20480
	mov	w1, 2208
	ldr	x4, [x19, 14968]
	mov	w0, 4000
	ldr	x3, [x19, 14960]
	add	x6, x19, 61440
	ldr	w2, [x2, 1592]
	mov	w7, 1
	umull	x1, w2, w1
	ldrb	w2, [x6, 1707]
	add	x1, x4, x1
	ldr	w1, [x1, 28]
	umull	x0, w1, w0
	add	x0, x3, x0
	ldr	w0, [x0, 2196]
	add	w0, w0, 4
	lsl	w7, w7, w0
	add	x0, x19, 24576
	cbz	w2, .L1203
	cmp	w2, 1
	mov	w1, 0
	cset	w8, eq
	cmp	w2, 2
	ldr	w2, [x0, 3712]
	cset	w9, eq
	cbz	w2, .L1223
	.p2align 2
.L1240:
	add	x3, x19, x1, uxtw 3
	ldr	x2, [x3, 28024]
	ldrb	w4, [x2, 2]
	cbz	w4, .L1217
	ldr	w4, [x2, 652]
	ldr	w5, [x6, 2368]
	cmp	w4, w5
	bls	.L1218
	sub	w4, w4, w7
	str	w4, [x2, 656]
.L1219:
	ldr	x2, [x3, 28024]
	ldrb	w4, [x2, 2]
	tbz	x4, 0, .L1220
	ldr	w5, [x2, 744]
	and	w5, w5, 16776960
	cmp	w5, 65536
	beq	.L1250
.L1220:
	tbz	x4, 1, .L1217
	ldr	w3, [x2, 792]
	and	w3, w3, 16776960
	cmp	w3, 65536
	beq	.L1251
	.p2align 2
.L1217:
	ldr	w2, [x0, 3712]
	add	w1, w1, 1
	cmp	w2, w1
	bhi	.L1240
.L1223:
	ldr	w2, [x0, 3716]
	mov	w1, 0
	cbz	w2, .L1202
	.p2align 2
.L1239:
	add	x4, x19, x1, uxtw 3
	add	w1, w1, 1
	ldr	x3, [x4, 28152]
	ldrb	w2, [x3, 2]
	cbz	w2, .L1225
	tbz	x2, 0, .L1226
	ldr	w5, [x3, 744]
	and	w5, w5, 16776960
	cmp	w5, 256
	beq	.L1252
.L1226:
	tbz	x2, 1, .L1225
	ldr	w2, [x3, 792]
	and	w2, w2, 16776960
	cmp	w2, 256
	beq	.L1253
	.p2align 2
.L1225:
	ldr	w2, [x0, 3716]
	cmp	w2, w1
	bhi	.L1239
.L1202:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1218:
	str	w4, [x2, 656]
	b	.L1219
	.p2align 3
.L1203:
	ldr	w2, [x0, 3712]
	mov	w1, 0
	cbnz	w2, .L1238
	.p2align 2
.L1213:
	ldr	w2, [x0, 3716]
	mov	w1, 0
	cbz	w2, .L1202
	add	x2, x19, x1, uxtw 3
	add	w1, w1, 1
	ldr	x2, [x2, 28152]
	ldrb	w3, [x2, 2]
	cmp	w3, 3
	beq	.L1254
	.p2align 2
.L1214:
	ldr	w2, [x0, 3716]
	cmp	w2, w1
	bls	.L1202
	add	x2, x19, x1, uxtw 3
	add	w1, w1, 1
	ldr	x2, [x2, 28152]
	ldrb	w3, [x2, 2]
	cmp	w3, 3
	bne	.L1214
.L1254:
	ldr	w3, [x2, 696]
	and	w3, w3, 16776960
	cmp	w3, 256
	bne	.L1214
	ldr	w3, [x2, 660]
	str	w3, [x2, 700]
	b	.L1214
	.p2align 3
.L1256:
	ldr	w4, [x2, 696]
	and	w4, w4, 16776960
	cmp	w4, 65536
	bne	.L1209
	ldr	w4, [x2, 652]
	ldr	w5, [x6, 2368]
	cmp	w4, w5
	sub	w5, w4, w7
	bhi	.L1255
	str	w4, [x2, 656]
.L1211:
	ldr	x2, [x3, 28024]
	ldr	w3, [x2, 656]
	str	w3, [x2, 704]
	.p2align 2
.L1209:
	ldr	w2, [x0, 3712]
	add	w1, w1, 1
	cmp	w2, w1
	bls	.L1213
.L1238:
	add	x3, x19, x1, uxtw 3
	ldr	x2, [x3, 28024]
	ldrb	w4, [x2, 2]
	cmp	w4, 3
	bne	.L1209
	b	.L1256
	.p2align 3
.L1252:
	ldr	w2, [x3, 660]
	add	w2, w8, w2, lsl 1
	str	w2, [x3, 748]
	ldr	x3, [x4, 28152]
	ldrb	w2, [x3, 2]
	b	.L1226
	.p2align 3
.L1250:
	ldr	w4, [x2, 656]
	add	w4, w8, w4, lsl 1
	str	w4, [x2, 752]
	ldr	x2, [x3, 28024]
	ldrb	w4, [x2, 2]
	b	.L1220
	.p2align 3
.L1253:
	ldr	w2, [x3, 660]
	add	w2, w9, w2, lsl 1
	str	w2, [x3, 796]
	b	.L1225
	.p2align 3
.L1251:
	ldr	w3, [x2, 656]
	add	w3, w9, w3, lsl 1
	str	w3, [x2, 800]
	b	.L1217
	.p2align 3
.L1255:
	str	w5, [x2, 656]
	b	.L1211
	.size	CalcPicNum, .-CalcPicNum
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IsOutDPB
	.type	IsOutDPB, %function
IsOutDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L1262
	add	x0, x19, 24576
	ldr	w3, [x0, 3708]
	cbz	w3, .L1262
	ldr	x0, [x19, 27896]
	cmp	x20, x0
	beq	.L1264
	sub	w3, w3, #1
	mov	x0, x19
	add	x3, x19, x3, lsl 3
	b	.L1259
	.p2align 3
.L1260:
	ldr	x2, [x0, 27896]
	cmp	x20, x2
	beq	.L1264
.L1259:
	cmp	x0, x3
	add	x0, x0, 8
	bne	.L1260
.L1262:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1264:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	IsOutDPB, .-IsOutDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	WriteCurrPicYUV
	.type	WriteCurrPicYUV, %function
WriteCurrPicYUV:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 61440
	bl	_mcount
	ldr	x1, .LC116
	mov	w0, 2
	ldr	x3, [x19, 2352]
	ldrb	w20, [x19, 1707]
	ldr	w3, [x3, 164]
	mov	w2, w20
	bl	dprint_vfmw
	cmp	w20, 3
	ldr	w3, [x19, 2408]
	ccmp	w20, wzr, 4, ne
	ldr	w4, [x19, 2412]
	cset	w0, eq
	ldr	x1, .LC118
	cmp	w0, wzr
	mov	w2, 1
	csinc	w2, w2, w20, ne
	mov	w0, 22
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	WriteCurrPicYUV, .-WriteCurrPicYUV
	.align	3
.LC116:
	.xword	.LC115
	.align	3
.LC118:
	.xword	.LC117
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	WritePicMsg
	.type	WritePicMsg, %function
WritePicMsg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	add	x22, x19, 61440
	add	x20, x19, 65536
	bl	_mcount
	add	x21, x19, 12288
	ldr	x1, .LC120
	mov	w0, 2
	ldrb	w3, [x22, 1707]
	add	x24, x19, 16384
	ldr	w4, [x22, 1868]
	ldr	w2, [x22, 2376]
	ldr	w5, [x22, 2428]
	bl	dprint_vfmw
	str	wzr, [x20, 1568]
	ldr	x2, [x20, 1560]
	ldr	x1, [x22, 2304]
	str	x1, [x20, 392]
	add	x1, x19, 20480
	str	x2, [x20, 1312]
	ldr	w2, [x22, 1832]
	str	w2, [x20, 1088]
	ldr	w2, [x22, 1836]
	str	w2, [x20, 1092]
	ldr	w2, [x22, 1856]
	str	w2, [x20, 1096]
	ldr	w2, [x22, 1860]
	str	w2, [x20, 1100]
	ldr	w2, [x22, 2376]
	str	w2, [x20, 400]
	ldrb	w2, [x22, 1707]
	strb	w2, [x20, 368]
	ldrb	w2, [x21, 2707]
	str	w2, [x20, 416]
	ldr	w2, [x22, 2412]
	str	w2, [x20, 404]
	ldr	w2, [x22, 2416]
	str	w2, [x20, 408]
	ldr	w2, [x21, 5936]
	add	w2, w2, 1
	str	w2, [x20, 412]
	ldrb	w2, [x21, 2706]
	strb	w2, [x20, 371]
	ldr	w2, [x24, 2652]
	str	w2, [x20, 420]
	ldrb	w2, [x24, 2592]
	str	w2, [x20, 424]
	ldr	w0, [x21, 2728]
	strb	w0, [x20, 369]
	ldrb	w0, [x24, 2596]
	str	w0, [x20, 428]
	ldr	w0, [x20, 1644]
	ldr	w2, [x1, 748]
	str	w2, [x20, 432]
	ldr	w2, [x1, 736]
	str	w2, [x20, 436]
	ldr	w1, [x1, 740]
	str	w1, [x20, 440]
	ldr	x1, [x22, 2352]
	ldr	w1, [x1, 648]
	bl	FSP_GetLogicFs
	mov	x23, x0
	cbz	x0, .L1302
	ldp	x2, x3, [x0, 32]
	cbz	x2, .L1272
	cbz	x3, .L1272
	ldr	w0, [x20, 1644]
	add	x3, x20, 820
	add	x2, x20, 692
	add	x1, x20, 948
	bl	FSP_GetDecFsAddrTab
	ldr	x3, [x23, 32]
	add	x2, x20, 952
	ldr	w0, [x20, 1644]
	add	x1, x20, 1080
	ldr	w3, [x3, 4]
	str	w3, [x20, 676]
	bl	FSP_GetPmvAddrTab
	ldr	w0, [x22, 2428]
	add	x22, x19, 24576
	str	w0, [x20, 684]
	ldr	w0, [x23, 12]
	str	w0, [x20, 1084]
	ldr	x0, [x23, 40]
	ldr	w0, [x0, 8]
	str	w0, [x20, 680]
	ldr	x0, [x23, 40]
	ldr	w0, [x0, 60]
	str	w0, [x20, 688]
	ldr	w4, [x22, 3984]
	str	w4, [x20, 1304]
	cbz	w4, .L1278
	sub	w3, w4, #1
	add	x0, x22, 3792
	add	x3, x3, 4096
	add	x1, x20, 1112
	add	x3, x3, 2997
	add	x3, x19, x3, lsl 2
	.p2align 2
.L1277:
	ldr	w2, [x0]
	add	x0, x0, 4
	str	w2, [x1]
	add	x1, x1, 4
	cmp	x3, x0
	ldr	w2, [x0, 60]
	str	w2, [x1, 60]
	ldr	w2, [x0, 124]
	str	w2, [x1, 124]
	bne	.L1277
.L1278:
	ldrb	w0, [x21, 2713]
	cbnz	w0, .L1303
	ldrb	w0, [x24, 2610]
	cbnz	w0, .L1279
	ldr	x10, .LC125
	add	x5, x20, 444
	mov	w1, 0
	.p2align 2
.L1280:
	and	w0, w1, 3
	add	w1, w1, 1
	cmp	w1, 24
	ldr	w0, [x10, w0, uxtw 2]
	ubfx	x3, x0, 8, 8
	lsr	w2, w0, 16
	ubfiz	w2, w2, 8, 8
	and	w0, w0, -16776961
	orr	w2, w2, w3, lsl 16
	orr	w0, w2, w0
	str	w0, [x5], 4
	bne	.L1280
	add	x6, x20, 540
	mov	w5, 0
	.p2align 2
.L1281:
	add	w0, w5, 1
	and	w2, w5, 14
	add	x1, x10, 16
	and	w0, w0, 15
	add	x6, x6, 8
	add	w5, w5, 2
	cmp	w5, 32
	ldr	w0, [x1, w0, uxtw 2]
	ldr	w1, [x1, w2, uxtw 2]
	lsr	w8, w0, 16
	ubfx	x2, x0, 8, 8
	lsr	w3, w1, 16
	lsr	w7, w1, 24
	ubfiz	w11, w0, 16, 8
	ubfiz	w9, w3, 8, 8
	and	w0, w0, -16777216
	and	w3, w1, 255
	ubfx	x1, x1, 8, 8
	orr	w0, w0, w2, lsl 16
	orr	w8, w11, w8, lsl 24
	orr	w3, w9, w3
	orr	w1, w1, w7, lsl 8
	orr	w2, w8, w3
	orr	w0, w1, w0
	stp	w2, w0, [x6, -8]
	bne	.L1281
.L1287:
	mov	w23, 0
	cbz	w4, .L1283
	.p2align 2
.L1291:
	add	x21, x19, x23, uxtw 2
	ldr	w0, [x20, 1644]
	add	x24, x21, 24576
	mov	w1, 0
	add	x21, x21, 65536
	add	w23, w23, 1
	ldr	w2, [x24, 3792]
	bl	FSP_GetStoreType
	cmp	w0, wzr
	cset	w0, ne
	str	w0, [x21, 1424]
	ldr	w0, [x24, 3792]
	str	w0, [x21, 1488]
	ldr	w0, [x22, 3984]
	cmp	w0, w23
	bhi	.L1291
.L1283:
	mov	w0, 0
.L1270:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1303:
	ldrb	w0, [x24, 2610]
.L1279:
	cmp	w0, 1
	add	x5, x20, 444
	mov	w1, 0
	beq	.L1285
	.p2align 2
.L1288:
	uxtw	x0, w1
	add	w1, w1, 1
	add	x0, x0, 4096
	cmp	w1, 24
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 564]
	ubfx	x3, x0, 8, 8
	lsr	w2, w0, 16
	ubfiz	w2, w2, 8, 8
	and	w0, w0, -16776961
	orr	w2, w2, w3, lsl 16
	orr	w0, w2, w0
	str	w0, [x5], 4
	bne	.L1288
	add	x6, x20, 540
	mov	w10, 1
	mov	w5, 0
	.p2align 2
.L1289:
	ubfx	x1, x5, 3, 29
	ubfiz	x0, x5, 1, 3
	and	x2, x10, 15
	lsl	x1, x1, 4
	add	x2, x1, x2
	add	x1, x1, x0
	add	x1, x1, 4096
	add	x0, x2, 4096
	add	x6, x6, 8
	add	w5, w5, 1
	add	x0, x19, x0, lsl 2
	add	x1, x19, x1, lsl 2
	cmp	w5, 16
	add	w10, w10, 2
	ldr	w0, [x0, 660]
	ldr	w1, [x1, 660]
	lsr	w3, w0, 16
	ubfx	x8, x0, 8, 8
	lsr	w9, w1, 16
	lsr	w7, w1, 24
	ubfiz	w12, w0, 16, 8
	ubfiz	w11, w9, 8, 8
	ubfx	x2, x1, 8, 8
	and	w9, w1, 255
	lsl	w7, w7, 8
	and	w1, w0, -16777216
	orr	w0, w2, w1
	orr	w3, w12, w3, lsl 24
	orr	w9, w11, w9
	orr	w7, w7, w8, lsl 16
	orr	w1, w9, w3
	orr	w0, w7, w0
	stp	w1, w0, [x6, -8]
	bne	.L1289
	b	.L1287
	.p2align 3
.L1285:
	uxtw	x0, w1
	add	w1, w1, 1
	add	x0, x0, 4096
	cmp	w1, 24
	add	x0, x0, 1144
	ldr	w0, [x19, x0, lsl 2]
	ubfx	x3, x0, 8, 8
	lsr	w2, w0, 16
	ubfiz	w2, w2, 8, 8
	and	w0, w0, -16776961
	orr	w2, w2, w3, lsl 16
	orr	w0, w2, w0
	str	w0, [x5], 4
	bne	.L1285
	add	x6, x20, 540
	mov	w10, 1
	mov	w5, 0
	.p2align 2
.L1286:
	ubfx	x1, x5, 3, 29
	ubfiz	x0, x5, 1, 3
	and	x2, x10, 15
	lsl	x1, x1, 4
	add	x2, x1, x2
	add	x1, x1, x0
	add	x1, x1, 4096
	add	x0, x2, 4096
	add	x0, x0, 1168
	add	x1, x1, 1168
	add	x6, x6, 8
	add	w5, w5, 1
	cmp	w5, 16
	add	w10, w10, 2
	ldr	w0, [x19, x0, lsl 2]
	ldr	w1, [x19, x1, lsl 2]
	lsr	w9, w0, 16
	ubfx	x8, x0, 8, 8
	lsr	w3, w1, 16
	lsr	w7, w1, 24
	ubfiz	w12, w0, 16, 8
	ubfiz	w11, w3, 8, 8
	ubfx	x2, x1, 8, 8
	and	w3, w1, 255
	lsl	w7, w7, 8
	and	w1, w0, -16777216
	orr	w0, w2, w1
	orr	w9, w12, w9, lsl 24
	orr	w3, w11, w3
	orr	w7, w7, w8, lsl 16
	orr	w1, w9, w3
	orr	w0, w7, w0
	stp	w1, w0, [x6, -8]
	bne	.L1286
	b	.L1287
.L1272:
	ldr	x1, .LC124
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1270
.L1302:
	ldr	x2, [x22, 2352]
	mov	w0, 0
	ldr	x1, .LC122
	ldr	w2, [x2, 648]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1270
	.size	WritePicMsg, .-WritePicMsg
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
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UpdatePicQpInf
	.type	UpdatePicQpInf, %function
UpdatePicQpInf:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	ldp	w1, w0, [x19, 24]
	cmp	w1, w20
	csel	w1, w1, w20, ge
	cmp	w0, w20
	csel	w0, w0, w20, le
	stp	w1, w0, [x19, 24]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	UpdatePicQpInf, .-UpdatePicQpInf
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	WriteSliceMsg
	.type	WriteSliceMsg, %function
WriteSliceMsg:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x23, x0
	mov	x0, x30
	add	x21, x23, 65536
	bl	_mcount
	ldr	w5, [x21, 1568]
	ldr	x6, [x21, 1560]
	add	w0, w5, 1
	str	w0, [x21, 1568]
	uxtw	x22, w5
	ldr	w1, [x23, 14940]
	lsl	x4, x22, 7
	sub	x4, x4, x22
	sub	w1, w1, #1
	lsl	x4, x4, 5
	cmp	w5, w1
	add	x20, x6, x4
	bcs	.L1306
	lsl	x1, x0, 7
	sub	x0, x1, x0
	add	x0, x6, x0, lsl 5
	str	x0, [x20, 4056]
.L1307:
	ldr	x3, [x23, 632]
	ldrb	w2, [x3]
	ldr	w0, [x3, 76]
	cmp	w2, 1
	ccmp	w2, w0, 2, ls
	bcs	.L1308
	.p2align 2
.L1309:
	uxtw	x0, w2
	add	w2, w2, 1
	lsl	x1, x0, 5
	add	x3, x3, x1
	add	x0, x20, x0, lsl 2
	ldr	w3, [x3, 28]
	str	w3, [x0, 16]
	ldr	x3, [x23, 632]
	add	x3, x3, x1
	ldr	w3, [x3, 24]
	str	w3, [x0, 8]
	ldr	x3, [x23, 632]
	add	x1, x3, x1
	ldr	w1, [x1, 32]
	str	w1, [x0, 24]
	ldr	x3, [x23, 632]
	ldr	w0, [x3, 76]
	cmp	w0, w2
	ccmp	w2, 1, 2, hi
	bls	.L1309
.L1308:
	cmp	w0, 1
	bhi	.L1314
	.p2align 2
.L1388:
	add	x1, x20, x0, uxtw 2
	add	w0, w0, 1
	cmp	w0, 2
	str	wzr, [x1, 8]
	str	wzr, [x1, 16]
	str	wzr, [x1, 24]
	bne	.L1388
.L1314:
	add	x19, x23, 61440
	add	x24, x23, 16384
	add	x2, x24, 2592
	add	x28, x23, 20480
	add	x1, x23, 12288
	ldrb	w0, [x19, 1713]
	strb	w0, [x20, 1]
	ldr	w0, [x2, 48]
	ldr	w3, [x28, 3192]
	add	w0, w0, 26
	add	w0, w0, w3
	str	w0, [x20, 32]
	ldr	w3, [x28, 3188]
	str	w3, [x20, 36]
	ldr	w3, [x28, 1640]
	str	w3, [x20, 40]
	ldr	w3, [x28, 1636]
	str	w3, [x20, 44]
	ldrb	w3, [x28, 1584]
	strb	w3, [x6, x4]
	ldr	w3, [x28, 1632]
	str	w3, [x20, 48]
	ldrb	w3, [x28, 1590]
	strb	w3, [x20, 2]
	ldrb	w1, [x1, 2708]
	strb	w1, [x20, 3]
	ldr	w1, [x28, 1624]
	str	w1, [x20, 52]
	ldr	w1, [x28, 1628]
	str	w1, [x20, 56]
	ldrb	w1, [x28, 1584]
	cmp	w1, 1
	beq	.L1413
	cbz	w1, .L1414
	strb	wzr, [x20, 4]
.L1315:
	ldr	w2, [x24, 2644]
	str	w2, [x20, 60]
	ldr	w1, [x24, 2648]
	str	w1, [x20, 64]
	ldr	w1, [x28, 3200]
	str	w1, [x20, 68]
	ldr	w1, [x28, 3204]
	str	w1, [x20, 72]
	ldr	w1, [x28, 3196]
	str	w1, [x20, 76]
	ldrb	w1, [x28, 1585]
	cbnz	w1, .L1317
	ldr	x2, [x19, 2352]
	ldr	w3, [x21, 1568]
	ldr	w1, [x2, 692]
	madd	w0, w5, w1, w0
	udiv	w0, w0, w3
	str	w0, [x2, 728]
.L1318:
	ldr	x0, [x19, 2352]
	cbnz	w5, .L1320
	ldr	w1, [x20, 32]
	str	w1, [x0, 720]
	ldr	x0, [x19, 2352]
	ldr	w1, [x20, 32]
	str	w1, [x0, 724]
.L1321:
	ldrb	w0, [x28, 1584]
	cmp	w0, 2
	beq	.L1359
	ldr	w0, [x28, 1624]
	cbz	w0, .L1362
	ldr	x1, [x23, 28696]
	ldr	x1, [x1, 40]
	ldrb	w2, [x1]
	cbz	w2, .L1325
	sub	w3, w0, #1
	mov	x0, x23
	add	x3, x23, x3, lsl 3
	b	.L1327
	.p2align 3
.L1329:
	ldr	x1, [x0, 28704]
	add	x0, x0, 8
	ldr	x1, [x1, 40]
	ldrb	w2, [x1]
	cbz	w2, .L1325
.L1327:
	cmp	x3, x0
	bne	.L1329
.L1362:
	mov	w25, 0
.L1324:
	ldr	w0, [x28, 1628]
	cbz	w0, .L1363
	ldr	x1, [x23, 28960]
	ldr	x1, [x1, 40]
	ldrb	w2, [x1]
	cbz	w2, .L1331
	sub	w3, w0, #1
	mov	x0, x23
	add	x3, x23, x3, lsl 3
	b	.L1333
	.p2align 3
.L1335:
	ldr	x1, [x0, 28968]
	add	x0, x0, 8
	ldr	x1, [x1, 40]
	ldrb	w2, [x1]
	cbz	w2, .L1331
.L1333:
	cmp	x3, x0
	bne	.L1335
.L1363:
	str	wzr, [x29, 108]
.L1330:
	ldrb	w0, [x19, 1707]
	cbz	w0, .L1336
	ldr	w0, [x28, 1624]
	mov	w26, 0
	cbnz	w0, .L1387
	b	.L1352
	.p2align 3
.L1416:
	cbz	x0, .L1369
	ldr	x0, [x0, 32]
	ldr	w1, [x0, 4]
.L1348:
	lsl	x0, x19, 5
	add	x0, x0, x19, lsl 2
	add	x0, x20, x0
	str	w1, [x0, 1640]
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 688]
	str	w1, [x0, 1644]
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 664]
	str	w1, [x0, 1632]
	ldr	x1, [x27, 28696]
	ldrb	w1, [x1]
	strb	w1, [x0, 1624]
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldrb	w1, [x1, 696]
	strb	w1, [x0, 1626]
	ldr	x1, [x27, 28696]
	ldrb	w1, [x1]
	cmp	w1, 1
	beq	.L1415
	strb	w1, [x0, 1630]
	add	w26, w26, 1
	ldr	x1, [x27, 28696]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 1631]
	ldr	x1, [x27, 28696]
	ldr	w1, [x1, 12]
	str	w1, [x0, 1656]
	ldr	w0, [x28, 1624]
	cmp	w0, w26
	bls	.L1352
.L1387:
	uxtw	x19, w26
	ldr	w0, [x21, 1644]
	add	x27, x23, x19, lsl 3
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 648]
	bl	FSP_GetLogicFs
	ldr	x3, [x27, 28696]
	lsl	x1, x19, 5
	add	x1, x1, x19, lsl 2
	add	x1, x20, x1
	ldr	x3, [x3, 40]
	ldr	w3, [x3, 684]
	str	w3, [x1, 1636]
	ldr	x3, [x27, 28696]
	ldr	x3, [x3, 40]
	ldrb	w3, [x3, 1]
	strb	w3, [x1, 1625]
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldrb	w1, [x1]
	cmp	w1, 1
	bne	.L1416
	mov	w1, w25
	b	.L1348
	.p2align 3
.L1306:
	str	xzr, [x20, 4056]
	b	.L1307
	.p2align 3
.L1414:
	ldrb	w1, [x2, 2]
	strb	w1, [x20, 4]
	b	.L1315
	.p2align 3
.L1415:
	strb	w1, [x0, 1628]
	add	w26, w26, 1
	ldr	x1, [x27, 28696]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 1629]
	ldr	x1, [x27, 28696]
	ldr	w1, [x1, 12]
	str	w1, [x0, 1652]
	ldr	w0, [x28, 1624]
	cmp	w0, w26
	bhi	.L1387
.L1352:
	ldrb	w0, [x28, 1584]
	cmp	w0, 1
	beq	.L1417
.L1339:
	add	x1, x23, 24576
	add	x0, x20, 3928
	add	x1, x1, 3992
	add	x3, x20, 4056
	.p2align 2
.L1345:
	ldr	w2, [x1], 4
	str	w2, [x0], 4
	cmp	x3, x0
	bne	.L1345
	ldrb	w0, [x24, 2594]
	str	w0, [x21, 668]
	ldr	w1, [x24, 2636]
	str	w1, [x21, 672]
	cbz	w0, .L1357
	ldrb	w0, [x28, 1584]
	cbnz	w0, .L1357
.L1358:
	ldr	w0, [x28, 1644]
	mov	w2, 0
	str	w0, [x20, 80]
	ldr	w0, [x28, 1648]
	str	w0, [x20, 84]
	.p2align 2
.L1360:
	ubfiz	x0, x2, 2, 32
	add	w2, w2, 1
	add	x1, x23, x0
	add	x0, x20, x0
	add	x1, x1, 20480
	ldr	w3, [x1, 1652]
	str	w3, [x0, 88]
	ldr	w3, [x1, 1780]
	str	w3, [x0, 216]
	ldr	w3, [x1, 1908]
	str	w3, [x0, 344]
	ldr	w3, [x1, 2420]
	str	w3, [x0, 856]
	ldr	w3, [x1, 2548]
	str	w3, [x0, 984]
	ldr	w1, [x1, 2676]
	str	w1, [x0, 1112]
	ldr	w0, [x28, 1636]
	cmp	w0, w2
	bcs	.L1360
	ldrb	w0, [x28, 1584]
	cmp	w0, 1
	beq	.L1418
	.p2align 2
.L1359:
	add	x22, x22, 4096
	ldr	x0, [x23, 632]
	add	x22, x23, x22, lsl 3
	str	x0, [x22, 31912]
	str	xzr, [x23, 632]
.L1305:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1320:
	ldr	w2, [x20, 32]
	ldr	w1, [x0, 720]
	cmp	w1, w2
	csel	w1, w1, w2, ge
	str	w1, [x0, 720]
	ldr	w1, [x0, 724]
	cmp	w1, w2
	csel	w1, w1, w2, le
	str	w1, [x0, 724]
	b	.L1321
	.p2align 3
.L1317:
	ldrb	w1, [x28, 1586]
	ldr	w3, [x21, 1568]
	ldr	x2, [x19, 2352]
	cbnz	w1, .L1319
	ldr	w1, [x2, 692]
	madd	w0, w5, w1, w0
	udiv	w0, w0, w3
	str	w0, [x2, 776]
	b	.L1318
	.p2align 3
.L1369:
	mov	w1, 0
	b	.L1348
	.p2align 3
.L1325:
	ldr	w1, [x1, 648]
	ldr	w0, [x21, 1644]
	bl	FSP_GetLogicFs
	cbz	x0, .L1419
	ldr	x0, [x0, 32]
	ldr	w25, [x0, 4]
	b	.L1324
	.p2align 3
.L1357:
	cmp	w1, 1
	bne	.L1359
	ldrb	w0, [x28, 1584]
	cmp	w0, 1
	bne	.L1359
	b	.L1358
	.p2align 3
.L1336:
	ldr	w0, [x28, 1624]
	mov	w26, 0
	cbnz	w0, .L1386
	b	.L1344
	.p2align 3
.L1420:
	cbz	x0, .L1365
	ldr	x0, [x0, 32]
	ldr	w1, [x0, 4]
.L1342:
	lsl	x0, x19, 5
	add	w26, w26, 1
	add	x0, x0, x19, lsl 2
	add	x0, x20, x0
	str	w1, [x0, 1640]
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 688]
	str	w1, [x0, 1644]
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 664]
	str	w1, [x0, 1632]
	ldr	x1, [x27, 28696]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 1627]
	ldr	x1, [x27, 28696]
	ldrb	w1, [x1]
	strb	w1, [x0, 1626]
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 708]
	str	w1, [x0, 1648]
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 756]
	str	w1, [x0, 1652]
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 804]
	str	w1, [x0, 1656]
	strb	wzr, [x0, 1624]
	ldr	w0, [x28, 1624]
	cmp	w0, w26
	bls	.L1344
.L1386:
	uxtw	x19, w26
	ldr	w0, [x21, 1644]
	add	x27, x23, x19, lsl 3
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 648]
	bl	FSP_GetLogicFs
	ldr	x3, [x27, 28696]
	lsl	x1, x19, 5
	add	x1, x1, x19, lsl 2
	add	x1, x20, x1
	ldr	x3, [x3, 40]
	ldr	w3, [x3, 684]
	str	w3, [x1, 1636]
	ldr	x3, [x27, 28696]
	ldr	x3, [x3, 40]
	ldrb	w3, [x3, 1]
	strb	w3, [x1, 1625]
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldrb	w1, [x1]
	cmp	w1, 1
	bne	.L1420
	mov	w1, w25
	b	.L1342
	.p2align 3
.L1365:
	mov	w1, 0
	b	.L1342
	.p2align 3
.L1344:
	ldrb	w0, [x28, 1584]
	cmp	w0, 1
	bne	.L1339
	ldr	w0, [x28, 1628]
	cbz	w0, .L1339
	mov	w27, 0
	b	.L1347
	.p2align 3
.L1421:
	cbz	x0, .L1367
	ldr	x0, [x0, 32]
	ldr	w1, [x0, 4]
.L1346:
	lsl	x0, x19, 5
	add	w27, w27, 1
	add	x0, x0, x19, lsl 2
	add	x0, x20, x0
	str	w1, [x0, 1640]
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 688]
	str	w1, [x0, 2796]
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 664]
	str	w1, [x0, 2784]
	ldr	x1, [x25, 28960]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 2779]
	ldr	x1, [x25, 28960]
	ldrb	w1, [x1]
	strb	w1, [x0, 2778]
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 708]
	str	w1, [x0, 2800]
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 756]
	str	w1, [x0, 2804]
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 804]
	str	w1, [x0, 2808]
	strb	wzr, [x0, 2776]
	ldr	w0, [x28, 1628]
	cmp	w0, w27
	bls	.L1339
.L1347:
	uxtw	x19, w27
	ldr	w0, [x21, 1644]
	add	x25, x23, x19, lsl 3
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 648]
	bl	FSP_GetLogicFs
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldr	w2, [x1, 684]
	lsl	x1, x19, 5
	add	x1, x1, x19, lsl 2
	add	x1, x20, x1
	str	w2, [x1, 2788]
	ldr	x2, [x25, 28960]
	ldr	x2, [x2, 40]
	ldrb	w2, [x2, 1]
	strb	w2, [x1, 2777]
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldrb	w1, [x1]
	cmp	w1, 1
	bne	.L1421
	ldr	w1, [x29, 108]
	b	.L1346
	.p2align 3
.L1331:
	ldr	w1, [x1, 648]
	ldr	w0, [x21, 1644]
	bl	FSP_GetLogicFs
	cbz	x0, .L1422
	ldr	x0, [x0, 32]
	ldr	w0, [x0, 4]
	str	w0, [x29, 108]
	b	.L1330
	.p2align 3
.L1413:
	ldr	w1, [x2, 44]
	strb	w1, [x20, 4]
	b	.L1315
	.p2align 3
.L1319:
	ldr	w1, [x2, 692]
	madd	w0, w5, w1, w0
	udiv	w0, w0, w3
	str	w0, [x2, 824]
	b	.L1318
.L1418:
	mov	w2, 0
	.p2align 2
.L1361:
	ubfiz	x0, x2, 2, 32
	add	w2, w2, 1
	add	x1, x23, x0
	add	x0, x20, x0
	add	x1, x1, 20480
	ldr	w3, [x1, 2036]
	str	w3, [x0, 472]
	ldr	w3, [x1, 2164]
	str	w3, [x0, 600]
	ldr	w3, [x1, 2292]
	str	w3, [x0, 728]
	ldr	w3, [x1, 2804]
	str	w3, [x0, 1240]
	ldr	w3, [x1, 2932]
	str	w3, [x0, 1368]
	ldr	w1, [x1, 3060]
	str	w1, [x0, 1496]
	ldr	w0, [x28, 1640]
	cmp	w0, w2
	bcs	.L1361
	b	.L1359
.L1367:
	mov	w1, 0
	b	.L1346
.L1417:
	ldr	w0, [x28, 1628]
	cbz	w0, .L1339
	mov	w27, 0
	b	.L1356
	.p2align 3
.L1424:
	cbz	x0, .L1371
	ldr	x0, [x0, 32]
	ldr	w1, [x0, 4]
.L1353:
	lsl	x0, x19, 5
	add	x0, x0, x19, lsl 2
	add	x0, x20, x0
	str	w1, [x0, 2792]
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 688]
	str	w1, [x0, 2796]
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 664]
	str	w1, [x0, 2784]
	ldr	x1, [x25, 28960]
	ldrb	w1, [x1]
	strb	w1, [x0, 2776]
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldrb	w1, [x1, 696]
	strb	w1, [x0, 2778]
	ldr	x1, [x25, 28960]
	ldrb	w1, [x1]
	cmp	w1, 1
	beq	.L1423
	strb	w1, [x0, 2782]
	ldr	x1, [x25, 28960]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 2783]
	ldr	x1, [x25, 28960]
	ldr	w1, [x1, 12]
	str	w1, [x0, 2808]
.L1355:
	ldr	w0, [x28, 1628]
	add	w27, w27, 1
	cmp	w0, w27
	bls	.L1339
.L1356:
	uxtw	x19, w27
	ldr	w0, [x21, 1644]
	add	x25, x23, x19, lsl 3
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 648]
	bl	FSP_GetLogicFs
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldr	w2, [x1, 684]
	lsl	x1, x19, 5
	add	x1, x1, x19, lsl 2
	add	x1, x20, x1
	str	w2, [x1, 2788]
	ldr	x2, [x25, 28960]
	ldr	x2, [x2, 40]
	ldrb	w2, [x2, 1]
	strb	w2, [x1, 2777]
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldrb	w1, [x1]
	cmp	w1, 1
	bne	.L1424
	ldr	w1, [x29, 108]
	b	.L1353
	.p2align 3
.L1423:
	strb	w1, [x0, 2780]
	ldr	x1, [x25, 28960]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 2781]
	ldr	x1, [x25, 28960]
	ldr	w1, [x1, 12]
	str	w1, [x0, 2804]
	b	.L1355
.L1371:
	mov	w1, 0
	b	.L1353
.L1419:
	ldr	x1, .LC128
	mov	w2, 7104
	bl	dprint_vfmw
	b	.L1305
.L1422:
	ldr	x1, .LC128
	mov	w2, 7125
	bl	dprint_vfmw
	b	.L1305
	.size	WriteSliceMsg, .-WriteSliceMsg
	.align	3
.LC128:
	.xword	.LC127
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	StopPicNum
	.type	StopPicNum, %function
StopPicNum:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	StopPicNum, .-StopPicNum
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_GetPicStreamSize
	.type	H264_GetPicStreamSize, %function
H264_GetPicStreamSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 65536
	bl	_mcount
	mov	w0, 0
	ldr	x2, [x19, 1312]
	cbz	x2, .L1427
	.p2align 2
.L1428:
	ldp	w3, w1, [x2, 8]
	ldr	x2, [x2, 4056]
	add	w1, w3, w1
	add	w1, w1, 7
	add	w0, w0, w1, lsr 3
	cbnz	x2, .L1428
.L1427:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	H264_GetPicStreamSize, .-H264_GetPicStreamSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SliceCheck
	.type	SliceCheck, %function
SliceCheck:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 20480
	add	x20, x19, 65536
	bl	_mcount
	ldr	x1, .LC130
	mov	x0, x19
	bl	ue_v
	str	w0, [x21, 1632]
	ldr	w1, [x20, 1584]
	cbnz	w1, .L1441
	mov	w1, 262143
	cmp	w0, w1
	bhi	.L1442
	ldr	w1, [x19, 14932]
	ldr	w2, [x19, 14936]
	mul	w1, w1, w2
	sub	w1, w1, #1
	cmp	w0, w1
	bhi	.L1441
	ldr	x1, .LC134
	mov	x0, x19
	bl	ue_v
	mov	w2, w0
	ldr	x1, .LC136
	mov	w19, w0
	mov	w0, 19
	bl	dprint_vfmw
	ldr	w0, [x20, 1584]
	cbnz	w0, .L1441
	cmp	w19, 9
	bls	.L1443
	ldr	x1, .LC139
	mov	w2, w19
	mov	w0, 1
	bl	dprint_vfmw
.L1441:
	mov	w0, -1
.L1433:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1443:
	ldr	x0, .LC137
	ldrb	w0, [x0,w19,uxtw]
	adr	x1, .Lrtx1438
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx1438:
	.section	.rodata
	.align	0
	.align	2
.L1438:
	.byte	(.L1437 - .Lrtx1438) / 4
	.byte	(.L1439 - .Lrtx1438) / 4
	.byte	(.L1440 - .Lrtx1438) / 4
	.byte	(.L1437 - .Lrtx1438) / 4
	.byte	(.L1440 - .Lrtx1438) / 4
	.byte	(.L1437 - .Lrtx1438) / 4
	.byte	(.L1439 - .Lrtx1438) / 4
	.byte	(.L1440 - .Lrtx1438) / 4
	.byte	(.L1437 - .Lrtx1438) / 4
	.byte	(.L1440 - .Lrtx1438) / 4
	.text
	.p2align 3
.L1437:
	strb	wzr, [x21, 1584]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1440:
	mov	w1, 2
	strb	w1, [x21, 1584]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1439:
	mov	w1, 1
	strb	w1, [x21, 1584]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1442:
	ldr	x1, .LC132
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1433
	.size	SliceCheck, .-SliceCheck
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
	.align	3
.LC137:
	.xword	.L1438
	.align	3
.LC139:
	.xword	.LC138
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PPSSPSCheck
	.type	PPSSPSCheck, %function
PPSSPSCheck:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 20480
	bl	_mcount
	ldr	x1, .LC141
	mov	w0, 19
	ldr	w2, [x20, 1592]
	bl	dprint_vfmw
	ldr	w2, [x20, 1592]
	mov	w0, 2208
	ldr	x1, [x19, 14968]
	umull	x0, w2, w0
	add	x0, x1, x0
	ldrb	w1, [x0, 19]
	cbz	w1, .L1448
	ldr	w2, [x0, 28]
	mov	w1, 4000
	ldr	x3, [x19, 14960]
	mov	w0, 0
	umull	x1, w2, w1
	add	x1, x3, x1
	ldrb	w1, [x1, 23]
	cbz	w1, .L1449
.L1446:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1448:
	ldr	x1, .LC143
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1446
	.p2align 3
.L1449:
	ldr	x1, .LC145
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1446
	.size	PPSSPSCheck, .-PPSSPSCheck
	.align	3
.LC141:
	.xword	.LC140
	.align	3
.LC143:
	.xword	.LC142
	.align	3
.LC145:
	.xword	.LC144
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PPSSPSCheckTmpId
	.type	PPSSPSCheckTmpId, %function
PPSSPSCheckTmpId:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	x1, .LC147
	mov	w2, w20
	mov	w0, 19
	bl	dprint_vfmw
	mov	w0, 2208
	ldr	x1, [x19, 14968]
	umull	x0, w20, w0
	add	x0, x1, x0
	ldrb	w1, [x0, 19]
	cbz	w1, .L1455
	ldr	w1, [x19, 14944]
	ldr	w2, [x0, 28]
	sub	w0, w1, #1
	cmp	w2, w0
	bhi	.L1456
	mov	w1, 4000
	ldr	x3, [x19, 14960]
	mov	w0, 0
	umull	x1, w2, w1
	add	x1, x3, x1
	ldrb	w1, [x1, 23]
	cbz	w1, .L1457
.L1452:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1455:
	ldr	x1, .LC149
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1452
	.p2align 3
.L1456:
	ldr	x1, .LC151
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1452
	.p2align 3
.L1457:
	ldr	x1, .LC153
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1452
	.size	PPSSPSCheckTmpId, .-PPSSPSCheckTmpId
	.align	3
.LC147:
	.xword	.LC146
	.align	3
.LC149:
	.xword	.LC148
	.align	3
.LC151:
	.xword	.LC150
	.align	3
.LC153:
	.xword	.LC152
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IsNewPic
	.type	IsNewPic, %function
IsNewPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 20480
	ldr	w2, [x19, 15012]
	ldr	w0, [x1, 1592]
	ldr	w3, [x1, 3232]
	ldr	w6, [x1, 3228]
	cmp	w3, w0
	ldr	w5, [x1, 3240]
	ldr	w0, [x1, 1600]
	ccmp	w6, w2, 0, eq
	ldrb	w4, [x1, 1585]
	cset	w2, ne
	ldrb	w3, [x1, 3224]
	cmp	w5, w0
	ccmp	w3, w4, 0, eq
	cset	w0, ne
	cmp	w4, wzr
	ccmp	w3, wzr, 4, ne
	orr	w2, w2, w0
	beq	.L1460
	ldrb	w0, [x1, 1586]
	ldrb	w3, [x1, 3225]
	cmp	w3, w0
	cset	w0, ne
	orr	w2, w2, w0
.L1460:
	ldr	w3, [x1, 1612]
	ldr	w0, [x1, 3236]
	cmp	w0, w3
	beq	.L1465
	cmp	w3, wzr
	ccmp	w0, wzr, 4, ne
	cset	w0, eq
.L1461:
	ldrb	w4, [x1, 3226]
	ldrb	w3, [x1, 1587]
	cmp	w4, w3
	cset	w5, ne
	cmp	w4, 5
	ccmp	w3, 5, 0, eq
	orr	w2, w5, w2
	orr	w2, w2, w0
	beq	.L1469
.L1462:
	add	x19, x19, 16384
	ldr	w0, [x19, 792]
	cbnz	w0, .L1463
	ldr	w4, [x1, 704]
	ldr	w5, [x1, 3248]
	ldr	w0, [x1, 708]
	ldr	w3, [x1, 3252]
	cmp	w5, w4
	ccmp	w3, w0, 0, eq
	cset	w0, ne
	orr	w2, w2, w0
.L1464:
	ldr	w3, [x1, 1632]
	mov	w0, 19
	ldr	x1, .LC155
	cmp	w3, wzr
	cset	w19, eq
	orr	w19, w19, w2
	mov	w2, w19
	bl	dprint_vfmw
	mov	w0, w19
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1463:
	cmp	w0, 1
	bne	.L1464
	ldr	w4, [x1, 752]
	ldr	w5, [x1, 3256]
	ldr	w0, [x1, 756]
	ldr	w3, [x1, 3260]
	cmp	w5, w4
	ccmp	w3, w0, 0, eq
	cset	w0, ne
	orr	w2, w2, w0
	b	.L1464
	.p2align 3
.L1465:
	mov	w0, 0
	b	.L1461
	.p2align 3
.L1469:
	ldr	w0, [x1, 1620]
	ldr	w3, [x1, 3244]
	cmp	w3, w0
	cset	w0, ne
	orr	w2, w2, w0
	b	.L1462
	.size	IsNewPic, .-IsNewPic
	.align	3
.LC155:
	.xword	.LC154
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ref_pic_list_reordering
	.type	ref_pic_list_reordering, %function
ref_pic_list_reordering:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 20480
	mov	w23, 1
	bl	_mcount
	mov	w1, 2208
	ldr	x5, [x19, 14968]
	ldr	w2, [x20, 1592]
	mov	w0, 4000
	ldr	x4, [x19, 14960]
	ldrb	w3, [x20, 1585]
	umull	x1, w2, w1
	add	x1, x5, x1
	ldr	w1, [x1, 28]
	strb	wzr, [x20, 796]
	strb	wzr, [x20, 797]
	umull	x0, w1, w0
	add	x0, x4, x0
	ldr	w0, [x0, 2196]
	cbz	w3, .L1471
	add	w0, w0, 5
	add	x22, x19, 65536
	lsl	w23, w23, w0
	ldrb	w0, [x20, 1584]
	cmp	w0, 1
	bls	.L1522
.L1521:
	ldr	w3, [x22, 1584]
.L1489:
	cmp	w3, wzr
	csetm	w0, ne
.L1520:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1471:
	add	w0, w0, 4
	add	x22, x19, 65536
	lsl	w23, w23, w0
	ldrb	w0, [x20, 1584]
	cmp	w0, 1
	bhi	.L1521
.L1522:
	ldr	x1, .LC157
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20, 796]
	cbz	w0, .L1480
	ldr	w0, [x20, 1636]
	cmn	w0, #2
	beq	.L1503
	ldr	x24, .LC159
	mov	w27, 0
	ldr	x26, .LC167
	ldr	x25, .LC163
	b	.L1486
	.p2align 3
.L1481:
	cmp	w0, 2
	beq	.L1523
.L1484:
	ldr	w0, [x20, 1636]
	add	w0, w0, 2
	cmp	w0, w27
	bls	.L1524
.L1486:
	add	x21, x19, x27, uxtw 2
	mov	x1, x24
	add	x21, x21, 20480
	mov	x0, x19
	add	w27, w27, 1
	bl	ue_v
	cmp	w0, 3
	str	w0, [x21, 800]
	ldr	w3, [x22, 1584]
	bhi	.L1477
	cbnz	w3, .L1477
	beq	.L1480
	cmp	w0, 1
	bhi	.L1481
	mov	x1, x25
	mov	x0, x19
	bl	ue_v
	str	w0, [x21, 1064]
	cmp	w23, w0
	ldr	w3, [x22, 1584]
	bls	.L1483
	cbz	w3, .L1484
.L1483:
	ldr	x1, .LC165
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1520
	.p2align 3
.L1480:
	ldrb	w0, [x20, 1584]
.L1473:
	cmp	w0, 1
	bne	.L1521
	ldr	x1, .LC171
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20, 797]
	cbz	w0, .L1521
	ldr	w0, [x20, 1640]
	cmn	w0, #2
	beq	.L1521
	ldr	x24, .LC173
	mov	w27, 0
	ldr	x26, .LC181
	ldr	x25, .LC177
	b	.L1501
	.p2align 3
.L1495:
	cmp	w0, 2
	beq	.L1525
	ldr	w0, [x20, 1640]
	add	w0, w0, 2
	cmp	w27, w0
	beq	.L1502
.L1500:
	add	w27, w27, 1
	cmp	w27, w0
	bcs	.L1521
.L1501:
	add	x21, x19, x27, uxtw 2
	mov	x1, x24
	add	x21, x21, 20480
	mov	x0, x19
	bl	ue_v
	cmp	w0, 3
	str	w0, [x21, 932]
	ldr	w3, [x22, 1584]
	bhi	.L1493
	cbnz	w3, .L1493
	beq	.L1489
	cmp	w0, 1
	bhi	.L1495
	mov	x1, x25
	mov	x0, x19
	bl	ue_v
	str	w0, [x21, 1196]
	cmp	w23, w0
	ldr	w3, [x22, 1584]
	bls	.L1497
	cbnz	w3, .L1497
.L1498:
	ldr	w0, [x20, 1640]
	add	w0, w0, 2
	cmp	w0, w27
	bne	.L1500
	ldr	w1, [x21, 932]
	cmp	w1, 3
	beq	.L1500
.L1502:
	ldr	x1, .LC183
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1520
	.p2align 3
.L1523:
	mov	x1, x26
	mov	x0, x19
	bl	ue_v
	str	w0, [x21, 1328]
	b	.L1484
	.p2align 3
.L1525:
	mov	x1, x26
	mov	x0, x19
	bl	ue_v
	str	w0, [x21, 1456]
	b	.L1498
	.p2align 3
.L1477:
	ldr	x1, .LC161
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1520
	.p2align 3
.L1493:
	ldr	x1, .LC175
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1520
	.p2align 3
.L1524:
	bne	.L1480
.L1475:
	uxtw	x0, w27
	add	x0, x0, 4096
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 4896]
	cmp	w0, 3
	bne	.L1487
	ldrb	w0, [x20, 1584]
	add	x22, x19, 65536
	b	.L1473
.L1497:
	ldr	x1, .LC179
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1520
.L1503:
	mov	w27, 0
	b	.L1475
.L1487:
	ldr	x1, .LC169
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1520
	.size	ref_pic_list_reordering, .-ref_pic_list_reordering
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
.LC173:
	.xword	.LC172
	.align	3
.LC175:
	.xword	.LC174
	.align	3
.LC177:
	.xword	.LC176
	.align	3
.LC179:
	.xword	.LC178
	.align	3
.LC181:
	.xword	.LC180
	.align	3
.LC183:
	.xword	.LC182
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	pred_weight_table
	.type	pred_weight_table, %function
pred_weight_table:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x26, x0
	mov	x0, x30
	add	x21, x26, 20480
	mov	w24, 2208
	bl	_mcount
	mov	w20, 4000
	ldr	x2, [x26, 14968]
	mov	x0, x26
	ldr	w4, [x21, 1592]
	mov	w19, 1
	ldr	x1, .LC185
	mov	w25, 0
	ldr	x5, [x26, 14960]
	umull	x4, w4, w24
	add	x24, x2, x4
	ldr	w2, [x24, 28]
	umull	x2, w2, w20
	add	x20, x5, x2
	bl	ue_v
	str	w0, [x21, 1644]
	lsl	w23, w19, w0
	ldr	w1, [x20, 40]
	cbnz	w1, .L1551
.L1527:
	cmp	w0, 7
	bhi	.L1530
	ldr	w0, [x21, 1648]
	cmp	w0, 7
	bhi	.L1530
	add	x0, x26, 65536
	str	x0, [x29, 104]
	ldr	w2, [x0, 1584]
	cbnz	w2, .L1529
	ldr	x22, .LC191
	mov	w27, 0
	b	.L1538
	.p2align 3
.L1533:
	str	w23, [x1, 1652]
	add	x0, x26, x19, lsl 2
	str	wzr, [x1, 2420]
	add	x0, x0, 20480
	ldr	w1, [x20, 40]
	cbnz	w1, .L1552
.L1535:
	str	wzr, [x0, 1780]
	str	wzr, [x0, 1908]
	str	wzr, [x0, 2548]
	str	wzr, [x0, 2676]
.L1537:
	ldr	w0, [x21, 1636]
	add	w27, w27, 1
	cmp	w0, w27
	bcc	.L1553
.L1538:
	mov	x1, x22
	mov	x0, x26
	uxtw	x19, w27
	bl	u_1
	add	x1, x26, x19, lsl 2
	add	x1, x1, 20480
	cbz	w0, .L1533
	ldr	x1, .LC193
	mov	x0, x26
	bl	se_v
	add	x4, x26, x19, lsl 2
	ldr	x1, .LC195
	add	x28, x4, 20480
	str	w0, [x28, 1652]
	mov	x0, x26
	bl	se_v
	str	w0, [x28, 2420]
	add	x0, x26, x19, lsl 2
	ldr	w1, [x20, 40]
	add	x0, x0, 20480
	cbz	w1, .L1535
.L1552:
	ldr	x1, .LC197
	mov	x0, x26
	bl	u_1
	add	x1, x26, x19, lsl 2
	add	x1, x1, 20480
	cbnz	w0, .L1554
	str	w25, [x1, 1780]
	add	w27, w27, 1
	str	w25, [x1, 1908]
	str	wzr, [x1, 2548]
	str	wzr, [x1, 2676]
	ldr	w0, [x21, 1636]
	cmp	w0, w27
	bcs	.L1538
.L1553:
	ldr	w0, [x24, 44]
	cmp	w0, 1
	beq	.L1539
.L1540:
	ldr	x0, [x29, 104]
	ldr	w0, [x0, 1584]
	cmp	w0, wzr
	csetm	w0, ne
.L1532:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1554:
	ldr	x1, .LC199
	mov	x0, x26
	add	x19, x26, x19, lsl 2
	add	x19, x19, 20480
	bl	se_v
	ldr	x1, .LC201
	str	w0, [x19, 1780]
	mov	x0, x26
	bl	se_v
	str	w0, [x19, 2548]
	ldr	x1, .LC199
	mov	x0, x26
	bl	se_v
	str	w0, [x19, 1908]
	ldr	x1, .LC201
	mov	x0, x26
	bl	se_v
	str	w0, [x19, 2676]
	b	.L1537
	.p2align 3
.L1551:
	ldr	x1, .LC187
	mov	x0, x26
	bl	ue_v
	mov	w25, w0
	ldr	w0, [x21, 1644]
	str	w25, [x21, 1648]
	lsl	w25, w19, w25
	b	.L1527
	.p2align 3
.L1539:
	ldrb	w0, [x21, 1584]
	cmp	w0, 1
	bne	.L1540
	ldr	x22, .LC203
	mov	w28, 0
	ldr	x27, .LC205
	b	.L1546
	.p2align 3
.L1541:
	add	x0, x26, x19, lsl 2
	add	x0, x0, 20480
	str	w23, [x0, 2036]
	str	wzr, [x0, 2804]
	add	x0, x26, x19, lsl 2
	add	x0, x0, 20480
	ldr	w1, [x20, 40]
	cbnz	w1, .L1555
.L1543:
	str	wzr, [x0, 2164]
	str	wzr, [x0, 2292]
	str	wzr, [x0, 2932]
	str	wzr, [x0, 3060]
.L1545:
	ldr	w0, [x21, 1640]
	add	w28, w28, 1
	cmp	w0, w28
	bcc	.L1540
.L1546:
	mov	x1, x22
	mov	x0, x26
	uxtw	x19, w28
	bl	u_1
	cbz	w0, .L1541
	mov	x1, x27
	mov	x0, x26
	bl	se_v
	add	x4, x26, x19, lsl 2
	ldr	x1, .LC207
	add	x24, x4, 20480
	str	w0, [x24, 2036]
	mov	x0, x26
	bl	se_v
	str	w0, [x24, 2804]
	add	x0, x26, x19, lsl 2
	ldr	w1, [x20, 40]
	add	x0, x0, 20480
	cbz	w1, .L1543
.L1555:
	ldr	x1, .LC209
	mov	x0, x26
	bl	u_1
	cbnz	w0, .L1556
	add	x0, x26, x19, lsl 2
	add	x0, x0, 20480
	str	w25, [x0, 2164]
	str	w25, [x0, 2292]
	str	wzr, [x0, 2932]
	str	wzr, [x0, 3060]
	b	.L1545
.L1530:
	add	x3, x26, 65536
	ldr	w2, [x3, 1584]
.L1529:
	ldr	x1, .LC189
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1532
.L1556:
	ldr	x1, .LC211
	mov	x0, x26
	add	x19, x26, x19, lsl 2
	add	x19, x19, 20480
	bl	se_v
	ldr	x1, .LC213
	str	w0, [x19, 2164]
	mov	x0, x26
	bl	se_v
	str	w0, [x19, 2932]
	ldr	x1, .LC211
	mov	x0, x26
	bl	se_v
	str	w0, [x19, 2292]
	ldr	x1, .LC213
	mov	x0, x26
	bl	se_v
	str	w0, [x19, 3060]
	b	.L1545
	.size	pred_weight_table, .-pred_weight_table
	.align	3
.LC185:
	.xword	.LC184
	.align	3
.LC187:
	.xword	.LC186
	.align	3
.LC189:
	.xword	.LC188
	.align	3
.LC191:
	.xword	.LC190
	.align	3
.LC193:
	.xword	.LC192
	.align	3
.LC195:
	.xword	.LC194
	.align	3
.LC197:
	.xword	.LC196
	.align	3
.LC199:
	.xword	.LC198
	.align	3
.LC201:
	.xword	.LC200
	.align	3
.LC203:
	.xword	.LC202
	.align	3
.LC205:
	.xword	.LC204
	.align	3
.LC207:
	.xword	.LC206
	.align	3
.LC209:
	.xword	.LC208
	.align	3
.LC211:
	.xword	.LC210
	.align	3
.LC213:
	.xword	.LC212
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecMMCO
	.type	DecMMCO, %function
DecMMCO:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	w19, w1
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L1558
	mov	w22, 100
	ldr	x21, .LC217
	ldr	x25, .LC219
	add	x23, x20, 65536
	ldr	x27, .LC225
	ldr	x24, .LC223
	ldr	x26, .LC221
	b	.L1569
	.p2align 3
.L1570:
	cmp	w19, 2
	beq	.L1583
.L1571:
	cmp	w19, 6
	cset	w0, eq
	orr	w0, w28, w0
	cbnz	w0, .L1574
	cmp	w19, 4
	beq	.L1584
.L1575:
	cmp	w19, 6
	bhi	.L1567
	ldr	w0, [x23, 1584]
	cbnz	w0, .L1567
.L1585:
	cbz	w19, .L1577
.L1576:
	subs	w22, w22, #1
	beq	.L1578
.L1569:
	mov	x1, x21
	mov	x0, x20
	bl	ue_v
	cmp	w0, 3
	mov	w19, w0
	and	w0, w0, -3
	cset	w28, eq
	cmp	w0, 1
	bne	.L1570
	mov	x1, x25
	mov	x0, x20
	bl	ue_v
	cmp	w19, 2
	bne	.L1571
.L1583:
	mov	x1, x26
	mov	x0, x20
	bl	ue_v
	ldr	w0, [x23, 1584]
	cbz	w0, .L1585
	.p2align 2
.L1567:
	ldr	x1, .LC227
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L1561:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1574:
	mov	x1, x24
	mov	x0, x20
	bl	ue_v
	cmp	w19, 4
	bne	.L1575
.L1584:
	mov	x1, x27
	mov	x0, x20
	bl	ue_v
	ldr	w0, [x23, 1584]
	cbz	w0, .L1576
	b	.L1567
	.p2align 3
.L1558:
	ldr	x21, .LC217
	mov	w26, 0
	ldr	x25, .LC219
	add	x22, x20, 24576
	ldr	x24, .LC223
	add	x23, x20, 65536
	b	.L1560
	.p2align 3
.L1562:
	cmp	w1, 2
	beq	.L1586
.L1563:
	cmp	w1, 3
	ccmp	w1, 6, 4, ne
	beq	.L1587
.L1564:
	cmp	w1, 4
	beq	.L1588
.L1565:
	cmp	w1, 6
	bhi	.L1567
	ldr	w0, [x23, 1584]
	cbnz	w0, .L1567
	add	w26, w26, 1
	cbz	w1, .L1577
	cmp	w26, 100
	beq	.L1589
.L1560:
	ldr	w28, [x22, 3180]
	mov	x1, x21
	mov	x0, x20
	uxtw	x27, w26
	lsl	x19, x27, 4
	bl	ue_v
	uxtw	x28, w28
	mov	w1, w0
	lsl	x0, x28, 6
	sub	x0, x0, x28
	add	x19, x19, x27, lsl 2
	lsl	x0, x0, 2
	and	w2, w1, -3
	sub	x0, x0, x28
	cmp	w2, 1
	lsl	x0, x0, 1
	sub	x0, x0, x28
	add	x19, x19, x0, lsl 2
	add	x19, x20, x19
	add	x19, x19, 20480
	str	w1, [x19, 3272]
	bne	.L1562
	mov	x1, x25
	mov	x0, x20
	bl	ue_v
	str	w0, [x19, 3276]
	ldr	w1, [x19, 3272]
	cmp	w1, 2
	bne	.L1563
.L1586:
	ldr	x1, .LC221
	mov	x0, x20
	bl	ue_v
	lsl	x1, x28, 6
	sub	x1, x1, x28
	lsl	x1, x1, 2
	sub	x1, x1, x28
	lsl	x1, x1, 1
	sub	x2, x1, x28
	lsl	x1, x27, 4
	add	x1, x1, x27, lsl 2
	add	x1, x1, x2, lsl 2
	add	x1, x20, x1
	add	x1, x1, 20480
	str	w0, [x1, 3280]
	ldr	w1, [x1, 3272]
	cmp	w1, 3
	ccmp	w1, 6, 4, ne
	bne	.L1564
	.p2align 2
.L1587:
	mov	x1, x24
	mov	x0, x20
	bl	ue_v
	lsl	x1, x28, 6
	lsl	x2, x27, 4
	sub	x1, x1, x28
	add	x2, x2, x27, lsl 2
	lsl	x1, x1, 2
	sub	x1, x1, x28
	lsl	x1, x1, 1
	sub	x1, x1, x28
	add	x2, x2, x1, lsl 2
	add	x2, x20, x2
	add	x2, x2, 20480
	ldr	w1, [x2, 3272]
	str	w0, [x2, 3284]
	cmp	w1, 4
	bne	.L1565
.L1588:
	ldr	x1, .LC225
	mov	x0, x20
	bl	ue_v
	lsl	x1, x28, 6
	sub	x1, x1, x28
	lsl	x1, x1, 2
	sub	x1, x1, x28
	lsl	x1, x1, 1
	sub	x28, x1, x28
	lsl	x1, x27, 4
	add	x3, x1, x27, lsl 2
	add	x3, x3, x28, lsl 2
	add	x3, x20, x3
	add	x3, x3, 20480
	ldr	w1, [x3, 3272]
	str	w0, [x3, 3288]
	b	.L1565
	.p2align 3
.L1577:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L1589:
	ldr	x1, .LC215
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1561
.L1578:
	mov	w0, -1
	b	.L1561
	.size	DecMMCO, .-DecMMCO
	.align	3
.LC215:
	.xword	.LC214
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
	.align	3
.LC225:
	.xword	.LC224
	.align	3
.LC227:
	.xword	.LC226
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	dec_ref_pic_marking
	.type	dec_ref_pic_marking, %function
dec_ref_pic_marking:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	add	x20, x21, 24576
	bl	_mcount
	add	x1, x21, 20480
	ldr	w23, [x20, 3180]
	ldrb	w0, [x1, 1589]
	cbz	w0, .L1591
	cmp	w23, wzr
	cset	w19, eq
	str	w19, [x20, 3180]
	ldrb	w0, [x1, 1587]
	cmp	w0, 5
	beq	.L1609
.L1592:
	ldr	x1, .LC235
	mov	x0, x21
	bl	u_1
	mov	w4, w0
	lsl	x3, x19, 6
	ldr	x1, .LC237
	sub	x3, x3, x19
	uxtb	w2, w0
	lsl	x3, x3, 2
	mov	w0, 16
	sub	x3, x3, x19
	lsl	x3, x3, 1
	sub	x19, x3, x19
	add	x19, x21, x19, lsl 2
	add	x19, x19, 20480
	strb	w4, [x19, 3271]
	bl	dprint_vfmw
	ldrb	w0, [x19, 3271]
	cbnz	w0, .L1594
.L1598:
	mov	w22, 0
.L1606:
	mov	w0, w22
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1591:
	uxtw	x19, w23
	lsl	x0, x19, 6
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x0, x0, x19
	lsl	x0, x0, 1
	sub	x19, x0, x19
	add	x19, x21, x19, lsl 2
	add	x19, x19, 20480
	ldrb	w0, [x19, 3268]
	cbnz	w0, .L1610
	ldrb	w0, [x1, 1587]
	uxtw	x19, w23
	cmp	w0, 5
	bne	.L1592
.L1609:
	ldr	x1, .LC229
	mov	x0, x21
	mov	w22, 0
	bl	u_1
	lsl	x2, x19, 6
	ldr	x1, .LC231
	sub	x2, x2, x19
	lsl	x2, x2, 2
	sub	x2, x2, x19
	lsl	x2, x2, 1
	sub	x19, x2, x19
	add	x19, x21, x19, lsl 2
	add	x19, x19, 20480
	strb	w0, [x19, 3269]
	mov	x0, x21
	bl	u_1
	strb	w0, [x19, 3270]
	ldrb	w2, [x19, 3269]
	mov	w0, 16
	ldr	x1, .LC233
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1610:
	ldrb	w0, [x1, 1587]
	cmp	w0, 5
	beq	.L1611
	ldr	x1, .LC235
	mov	x0, x21
	ldrb	w20, [x19, 3271]
	bl	u_1
	cmp	w20, w0
	bne	.L1612
	ldrb	w0, [x19, 3271]
	cbz	w0, .L1598
	mov	w1, 0
	mov	x0, x21
	bl	DecMMCO
	mov	w22, w0
	b	.L1606
	.p2align 3
.L1594:
	mov	w1, 1
	mov	x0, x21
	bl	DecMMCO
	cmn	w0, #1
	mov	w22, w0
	beq	.L1613
	mov	w0, 1
	strb	w0, [x19, 3268]
	mov	w22, 0
	mov	w0, w22
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1611:
	ldr	x1, .LC229
	mov	x0, x21
	ldrb	w20, [x19, 3269]
	bl	u_1
	cmp	w20, w0
	bne	.L1614
	ldr	x1, .LC231
	mov	x0, x21
	ldrb	w19, [x19, 3270]
	bl	u_1
	cmp	w19, w0
	beq	.L1598
	ldr	x1, .LC243
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1606
.L1612:
	ldr	x1, .LC245
	add	x21, x21, 65536
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	ldr	x1, .LC247
	mov	w0, 1
	ldr	w4, [x21, 1588]
	ldr	w2, [x21, 1608]
	ldr	w3, [x21, 1624]
	bl	dprint_vfmw
	b	.L1606
.L1614:
	ldr	x1, .LC241
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1606
.L1613:
	strb	wzr, [x19, 3268]
	mov	w0, 1
	ldr	x1, .LC239
	str	w23, [x20, 3180]
	bl	dprint_vfmw
	b	.L1606
	.size	dec_ref_pic_marking, .-dec_ref_pic_marking
	.align	3
.LC229:
	.xword	.LC228
	.align	3
.LC231:
	.xword	.LC230
	.align	3
.LC233:
	.xword	.LC232
	.align	3
.LC235:
	.xword	.LC234
	.align	3
.LC237:
	.xword	.LC236
	.align	3
.LC239:
	.xword	.LC238
	.align	3
.LC241:
	.xword	.LC240
	.align	3
.LC243:
	.xword	.LC242
	.align	3
.LC245:
	.xword	.LC244
	.align	3
.LC247:
	.xword	.LC246
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProcessSliceHeaderFirstPart
	.type	ProcessSliceHeaderFirstPart, %function
ProcessSliceHeaderFirstPart:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x23, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC249
	mov	x0, x23
	bl	ue_v
	mov	w21, w0
	ldr	w0, [x23, 14948]
	sub	w0, w0, #1
	cmp	w21, w0
	bhi	.L1616
	add	x24, x23, 65536
	ldr	w0, [x24, 1584]
	cbnz	w0, .L1616
	mov	w1, w21
	mov	x0, x23
	bl	PPSSPSCheckTmpId
	mov	w22, w0
	cbnz	w0, .L1679
	add	x19, x23, 20480
	mov	w1, 2208
	mov	w20, 4000
	umull	x1, w21, w1
	str	w21, [x19, 1592]
	ldrb	w0, [x19, 1587]
	ldr	x21, [x23, 14968]
	cmp	w0, 5
	ldr	x2, [x23, 14960]
	add	x21, x21, x1
	ldr	w0, [x21, 28]
	umull	x0, w0, w20
	add	x20, x2, x0
	beq	.L1620
	ldr	w0, [x20, 3244]
	cbz	w0, .L1620
.L1621:
	ldr	w1, [x20, 2196]
	mov	x0, x23
	ldr	x2, .LC257
	add	w1, w1, 4
	bl	u_v
	str	w0, [x19, 1600]
	ldr	w1, [x24, 1584]
	cbnz	w1, .L1645
	ldrb	w1, [x19, 1587]
	cmp	w1, 5
	beq	.L1680
.L1624:
	strb	wzr, [x19, 1585]
	strb	wzr, [x19, 1586]
	ldrb	w0, [x20, 18]
	cbz	w0, .L1681
	ldr	w1, [x20, 3252]
	ldr	w2, [x20, 3248]
	add	w0, w1, 1
	madd	w0, w2, w0, w0
.L1648:
	ldrb	w1, [x20, 19]
	cbnz	w1, .L1631
	strb	wzr, [x19, 1588]
.L1633:
	ldr	w1, [x19, 1632]
	cmp	w1, w0
	bcs	.L1682
.L1634:
	ldrb	w0, [x19, 1587]
	cmp	w0, 5
	beq	.L1683
.L1636:
	str	wzr, [x19, 704]
	str	wzr, [x19, 708]
	ldr	w0, [x20, 2200]
	cbz	w0, .L1684
.L1640:
	str	wzr, [x19, 752]
	str	wzr, [x19, 756]
	ldr	w0, [x20, 2200]
	cmp	w0, 1
	beq	.L1685
.L1643:
	ldr	w0, [x24, 1584]
	cbnz	w0, .L1645
	ldrb	w0, [x21, 17]
	cbz	w0, .L1646
	ldr	x1, .LC281
	mov	x0, x23
	bl	ue_v
	cbnz	w0, .L1647
	ldr	w0, [x24, 1584]
	cbnz	w0, .L1647
.L1646:
	mov	x0, x23
	bl	IsNewPic
	uxtb	w0, w0
	strb	w0, [x19, 1589]
	cbnz	w0, .L1659
	ldr	w1, [x19, 1632]
	ldr	w0, [x19, 3264]
	cmp	w1, w0
	bls	.L1686
.L1659:
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1620:
	ldrb	w0, [x19, 1584]
	cmp	w0, 2
	beq	.L1621
	ldr	x1, .LC255
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1659
	.p2align 3
.L1631:
	mov	w1, 1
	strb	w1, [x19, 1588]
.L1650:
	ldr	w1, [x19, 1632]
	cmp	w1, w0, lsr 1
	bcc	.L1634
	ldr	x1, .LC265
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1659
	.p2align 3
.L1647:
	ldr	x1, .LC283
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC284
	ldr	x4, [x0]
	cbz	x4, .L1645
	ldr	w0, [x24, 1644]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	mov	w22, -1
	blr	x4
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1681:
	ldr	x1, .LC261
	mov	x0, x23
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x19, 1585]
	cbnz	w0, .L1687
	ldr	w2, [x20, 3252]
	ldr	w1, [x20, 3248]
	add	w0, w2, 1
	ldrb	w3, [x20, 18]
	madd	w1, w1, w0, w0
	lsl	w0, w1, 1
	cbz	w3, .L1648
.L1628:
	ldrb	w2, [x19, 1585]
	mov	w0, 1
	b	.L1629
	.p2align 3
.L1684:
	ldr	w1, [x20, 2204]
	mov	x0, x23
	ldr	x2, .LC273
	add	w1, w1, 4
	bl	u_v
	str	w0, [x19, 704]
	ldrb	w0, [x21, 1]
	cbz	w0, .L1640
	ldrb	w0, [x19, 1585]
	cbnz	w0, .L1640
	ldr	x1, .LC275
	mov	x0, x23
	bl	se_v
	str	w0, [x19, 708]
	b	.L1640
	.p2align 3
.L1680:
	str	w0, [x19, 1596]
	cbz	w0, .L1624
	ldr	x1, .LC259
	mov	w0, 1
	bl	dprint_vfmw
	b	.L1624
	.p2align 3
.L1685:
	ldrb	w0, [x20, 16]
	cbnz	w0, .L1643
	ldr	x1, .LC277
	mov	x0, x23
	bl	se_v
	str	w0, [x19, 752]
	ldrb	w0, [x21, 1]
	cmp	w0, 1
	bne	.L1643
	ldrb	w0, [x19, 1585]
	cbnz	w0, .L1643
	ldr	x1, .LC279
	mov	x0, x23
	bl	se_v
	str	w0, [x19, 756]
	b	.L1643
	.p2align 3
.L1645:
	mov	w22, -1
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1687:
	ldr	x1, .LC263
	mov	x0, x23
	bl	u_1
	strb	w0, [x19, 1586]
	ldr	w0, [x20, 3252]
	ldr	w1, [x20, 3248]
	ldrb	w2, [x20, 18]
	add	w0, w0, 1
	madd	w1, w1, w0, w0
	cbnz	w2, .L1628
	ldrb	w2, [x19, 1585]
	mov	w0, 2
.L1629:
	mul	w0, w0, w1
	cbz	w2, .L1648
	strb	wzr, [x19, 1588]
	cmp	w2, 1
	bne	.L1633
	b	.L1650
	.p2align 3
.L1683:
	ldr	x1, .LC269
	mov	x0, x23
	bl	ue_v
	str	w0, [x19, 1620]
	mov	w1, 65535
	cmp	w0, w1
	bhi	.L1637
	ldr	w0, [x24, 1584]
	cbz	w0, .L1636
.L1637:
	ldr	x1, .LC271
	mov	w0, 1
	bl	dprint_vfmw
	b	.L1636
	.p2align 3
.L1616:
	ldr	x1, .LC251
	mov	w2, w21
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1679:
	ldr	x1, .LC253
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1659
.L1682:
	ldr	x1, .LC267
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1659
.L1686:
	ldr	x1, .LC286
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1659
	.size	ProcessSliceHeaderFirstPart, .-ProcessSliceHeaderFirstPart
	.align	3
.LC249:
	.xword	.LC248
	.align	3
.LC251:
	.xword	.LC250
	.align	3
.LC253:
	.xword	.LC252
	.align	3
.LC255:
	.xword	.LC254
	.align	3
.LC257:
	.xword	.LC256
	.align	3
.LC259:
	.xword	.LC258
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
.LC267:
	.xword	.LC266
	.align	3
.LC269:
	.xword	.LC268
	.align	3
.LC271:
	.xword	.LC270
	.align	3
.LC273:
	.xword	.LC272
	.align	3
.LC275:
	.xword	.LC274
	.align	3
.LC277:
	.xword	.LC276
	.align	3
.LC279:
	.xword	.LC278
	.align	3
.LC281:
	.xword	.LC280
	.align	3
.LC283:
	.xword	.LC282
	.align	3
.LC284:
	.xword	g_event_report
	.align	3
.LC286:
	.xword	.LC285
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProcessSliceHeaderSecondPart
	.type	ProcessSliceHeaderSecondPart, %function
ProcessSliceHeaderSecondPart:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 20480
	bl	_mcount
	ldr	w0, [x20, 14948]
	ldr	w2, [x19, 1592]
	sub	w0, w0, #1
	cmp	w0, w2
	bcc	.L1689
	add	x24, x20, 65536
	ldr	w0, [x24, 1584]
	cbnz	w0, .L1689
	mov	x0, x20
	bl	PPSSPSCheck
	cbnz	w0, .L1772
	ldr	w22, [x19, 1592]
	mov	w0, 2208
	ldrb	w1, [x19, 1584]
	ldr	x25, [x20, 14968]
	umull	x22, w22, w0
	cmp	w1, 1
	add	x21, x25, x22
	beq	.L1773
	ldr	w0, [x21, 36]
	cmp	w1, 1
	str	w0, [x19, 1636]
	ldr	w0, [x21, 40]
	str	w0, [x19, 1640]
	bls	.L1774
.L1694:
	cmp	w1, 2
	beq	.L1720
.L1704:
	mov	w0, 32
	str	w0, [x19, 1640]
.L1705:
	mov	x0, x20
	bl	ref_pic_list_reordering
	mov	w23, w0
	cbnz	w0, .L1775
	ldrb	w0, [x21, 2]
	cbz	w0, .L1707
	ldrb	w0, [x19, 1584]
	cbnz	w0, .L1707
	mov	w0, 1
	mov	w2, w0
.L1781:
	ldr	x1, .LC304
	strb	w0, [x19, 1591]
	mov	w0, 19
	bl	dprint_vfmw
	str	wzr, [x19, 1644]
	ldrb	w0, [x19, 1591]
	str	wzr, [x19, 1648]
	cbz	w0, .L1709
.L1777:
	mov	x0, x20
	bl	pred_weight_table
	cbz	w0, .L1709
	ldr	x1, .LC306
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L1740
	.p2align 3
.L1707:
	ldr	w0, [x21, 44]
	cmp	w0, 1
	beq	.L1776
.L1724:
	mov	w0, 0
	ldr	x1, .LC304
	strb	w0, [x19, 1591]
	mov	w2, 0
	mov	w0, 19
	bl	dprint_vfmw
	str	wzr, [x19, 1644]
	ldrb	w0, [x19, 1591]
	str	wzr, [x19, 1648]
	cbnz	w0, .L1777
.L1709:
	ldr	w0, [x19, 1612]
	cbnz	w0, .L1778
.L1710:
	str	wzr, [x19, 3188]
	ldrb	w0, [x25, x22]
	cbz	w0, .L1711
	ldrb	w0, [x19, 1584]
	cmp	w0, 1
	bls	.L1779
.L1711:
	ldr	x1, .LC314
	mov	x0, x20
	bl	se_v
	add	x1, x19, 3072
	stp	w0, wzr, [x1, 120]
	stp	wzr, wzr, [x1, 128]
	ldrb	w0, [x21, 3]
	cbnz	w0, .L1780
.L1740:
	mov	w0, w23
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1780:
	ldr	x1, .LC316
	mov	x0, x20
	bl	ue_v
	cmp	w0, 2
	str	w0, [x19, 3196]
	bhi	.L1714
	ldr	w1, [x24, 1584]
	cbnz	w1, .L1714
	cmp	w0, 1
	beq	.L1740
	ldr	x1, .LC320
	mov	x0, x20
	bl	se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x19, 3200]
	bhi	.L1717
	ldr	w0, [x24, 1584]
	cbnz	w0, .L1717
	ldr	x1, .LC324
	mov	x0, x20
	bl	se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x19, 3204]
	bhi	.L1719
	ldr	w0, [x24, 1584]
	cbz	w0, .L1740
.L1719:
	ldr	x1, .LC326
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L1740
	.p2align 3
.L1778:
	mov	x0, x20
	bl	dec_ref_pic_marking
	cbz	w0, .L1710
	ldr	x1, .LC308
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L1740
	.p2align 3
.L1720:
	mov	w0, 32
	str	w0, [x19, 1636]
	b	.L1704
	.p2align 3
.L1776:
	ldrb	w0, [x19, 1584]
	cmp	w0, 1
	bne	.L1724
	mov	w2, w0
	b	.L1781
	.p2align 3
.L1773:
	ldr	x1, .LC290
	mov	x0, x20
	bl	u_1
	strb	w0, [x19, 1590]
	ldrb	w1, [x19, 1584]
	ldr	w0, [x21, 36]
	str	w0, [x19, 1636]
	cmp	w1, 1
	ldr	w0, [x21, 40]
	str	w0, [x19, 1640]
	bhi	.L1694
	.p2align 2
.L1774:
	ldr	x1, .LC292
	mov	x0, x20
	bl	u_1
	cbnz	w0, .L1695
	ldr	w1, [x19, 1636]
.L1696:
	ldrb	w0, [x19, 1585]
	cbnz	w0, .L1697
	cmp	w1, 15
	bhi	.L1698
	ldr	w0, [x19, 1640]
	cmp	w0, 15
	bhi	.L1782
.L1699:
	ldr	w0, [x24, 1584]
	cbnz	w0, .L1698
.L1700:
	ldrb	w0, [x19, 1584]
	cmp	w0, 2
	beq	.L1720
	cmp	w0, 1
	beq	.L1705
	b	.L1704
	.p2align 3
.L1689:
	ldr	x1, .LC287
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	ldr	x25, [sp, 64]
	mov	w0, w23
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1779:
	ldr	x1, .LC310
	mov	x0, x20
	bl	ue_v
	cmp	w0, 2
	str	w0, [x19, 3188]
	bhi	.L1712
	ldr	w0, [x24, 1584]
	cbz	w0, .L1711
.L1712:
	ldr	x1, .LC312
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L1740
	.p2align 3
.L1697:
	cmp	w1, 31
	bhi	.L1701
	ldr	w0, [x19, 1640]
	cmp	w0, 31
	bls	.L1702
	ldrb	w0, [x19, 1584]
	cmp	w0, 1
	bne	.L1702
.L1701:
	ldr	x1, .LC300
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L1740
	.p2align 3
.L1702:
	ldr	w0, [x24, 1584]
	cbz	w0, .L1700
	b	.L1701
	.p2align 3
.L1782:
	ldrb	w0, [x19, 1584]
	cmp	w0, 1
	bne	.L1699
.L1698:
	ldr	x1, .LC298
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L1740
	.p2align 3
.L1695:
	ldr	x1, .LC294
	mov	x0, x20
	bl	ue_v
	mov	w1, w0
	ldrb	w0, [x19, 1584]
	str	w1, [x19, 1636]
	cmp	w0, 1
	bne	.L1696
	ldr	x1, .LC296
	mov	x0, x20
	bl	ue_v
	str	w0, [x19, 1640]
	ldr	w1, [x19, 1636]
	b	.L1696
	.p2align 3
.L1717:
	ldr	x1, .LC322
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L1740
	.p2align 3
.L1714:
	ldr	x1, .LC318
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L1740
	.p2align 3
.L1772:
	ldr	x1, .LC288
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L1740
	.p2align 3
.L1775:
	ldr	x1, .LC302
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L1740
	.size	ProcessSliceHeaderSecondPart, .-ProcessSliceHeaderSecondPart
	.align	3
.LC287:
	.xword	.LC250
	.align	3
.LC288:
	.xword	.LC252
	.align	3
.LC290:
	.xword	.LC289
	.align	3
.LC292:
	.xword	.LC291
	.align	3
.LC294:
	.xword	.LC293
	.align	3
.LC296:
	.xword	.LC295
	.align	3
.LC298:
	.xword	.LC297
	.align	3
.LC300:
	.xword	.LC299
	.align	3
.LC302:
	.xword	.LC301
	.align	3
.LC304:
	.xword	.LC303
	.align	3
.LC306:
	.xword	.LC305
	.align	3
.LC308:
	.xword	.LC307
	.align	3
.LC310:
	.xword	.LC309
	.align	3
.LC312:
	.xword	.LC311
	.align	3
.LC314:
	.xword	.LC313
	.align	3
.LC316:
	.xword	.LC315
	.align	3
.LC318:
	.xword	.LC317
	.align	3
.LC320:
	.xword	.LC319
	.align	3
.LC322:
	.xword	.LC321
	.align	3
.LC324:
	.xword	.LC323
	.align	3
.LC326:
	.xword	.LC325
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ExitSlice
	.type	ExitSlice, %function
ExitSlice:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 20480
	mov	w2, 2208
	ldr	x8, [x19, 14968]
	mov	w1, 4000
	ldr	x7, [x19, 14960]
	ldr	w4, [x0, 1592]
	ldrb	w3, [x0, 1585]
	ldr	w5, [x0, 1600]
	umull	x2, w4, w2
	ldr	w6, [x0, 1632]
	add	x2, x8, x2
	ldr	w2, [x2, 28]
	str	w4, [x0, 3232]
	umull	x1, w2, w1
	add	x1, x7, x1
	ldr	w2, [x1, 36]
	str	w2, [x0, 3228]
	strb	w3, [x0, 3224]
	str	w5, [x0, 3240]
	str	w6, [x0, 3264]
	cbz	w3, .L1784
	ldrb	w2, [x0, 1586]
	strb	w2, [x0, 3225]
.L1784:
	ldrb	w2, [x0, 1587]
	ldr	w3, [x0, 1612]
	strb	w2, [x0, 3226]
	cmp	w2, 5
	str	w3, [x0, 3236]
	beq	.L1791
.L1785:
	ldr	w2, [x1, 2200]
	cbnz	w2, .L1786
	ldr	w2, [x0, 708]
	ldr	w3, [x0, 704]
	str	w3, [x0, 3248]
	str	w2, [x0, 3252]
	ldr	w2, [x1, 2200]
.L1786:
	cmp	w2, 1
	bne	.L1787
	ldr	w2, [x0, 752]
	ldr	w1, [x0, 756]
	str	w2, [x0, 3256]
	str	w1, [x0, 3260]
.L1787:
	add	x19, x19, 65536
	ldr	w0, [x19, 1600]
	add	w0, w0, 1
	str	w0, [x19, 1600]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1791:
	ldr	w2, [x0, 1620]
	str	w2, [x0, 3244]
	b	.L1785
	.size	ExitSlice, .-ExitSlice
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PicTypeStatistic
	.type	PicTypeStatistic, %function
PicTypeStatistic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 20480
	ldrb	w0, [x1, 1584]
	cmp	w0, 1
	beq	.L1794
	cbz	w0, .L1795
	cmp	w0, 2
	bne	.L1792
	ldrb	w0, [x1, 1587]
	add	x19, x19, 61440
	cmp	w0, 5
	beq	.L1802
.L1797:
	str	wzr, [x19, 2400]
.L1792:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1795:
	add	x19, x19, 61440
	ldr	w0, [x19, 2396]
	cmp	w0, 2
	beq	.L1797
	mov	w0, 1
	str	wzr, [x19, 2400]
	str	w0, [x19, 2396]
	b	.L1792
	.p2align 3
.L1794:
	add	x19, x19, 61440
	mov	w0, 2
	str	wzr, [x19, 2400]
	str	w0, [x19, 2396]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1802:
	mov	w0, 1
	str	w0, [x19, 2400]
	b	.L1792
	.size	PicTypeStatistic, .-PicTypeStatistic
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CalcStreamBits
	.type	CalcStreamBits, %function
CalcStreamBits:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 16384
	ldrb	w0, [x0, 2592]
	cbz	w0, .L1804
	ldr	x1, [x19, 632]
	ldr	w0, [x1, 72]
	add	w0, w0, 7
	and	w0, w0, -8
	str	w0, [x1, 72]
	ldr	x1, [x19, 632]
	ldr	w0, [x1, 80]
	sub	w0, w0, #1
	str	w0, [x1, 80]
.L1804:
	ldr	x3, [x19, 632]
	ldrb	w21, [x3]
	cbz	w21, .L1815
	sub	w1, w21, #1
	mov	w4, 32
	mov	x2, 48
	add	x0, x3, 16
	mov	w20, 0
	umaddl	x2, w1, w4, x2
	add	x2, x3, x2
	.p2align 2
.L1806:
	ldr	w1, [x0], 32
	cmp	x0, x2
	add	w20, w20, w1
	bne	.L1806
.L1805:
	sbfiz	x4, x21, 5, 32
	ldr	w2, [x3, 72]
	add	x4, x3, x4
	ldr	w5, [x3, 80]
	ldr	x1, .LC328
	mov	w3, w20
	mov	w0, 7
	ldr	w4, [x4, 16]
	bl	dprint_vfmw
	ldr	x2, [x19, 632]
	ubfiz	x3, x21, 5, 8
	ldrb	w0, [x2]
	ldr	w1, [x2, 72]
	add	x0, x2, x0, lsl 5
	and	w1, w1, 7
	str	w1, [x0, 28]
	ldr	x2, [x19, 632]
	ldrb	w1, [x2]
	ldr	w0, [x2, 72]
	add	x1, x2, x1, lsl 5
	ldr	w2, [x1, 20]
	add	w0, w2, w0, lsr 3
	mov	w2, w21
	sub	w0, w0, w20
	str	w0, [x1, 32]
	ldr	x4, [x19, 632]
	ldrb	w1, [x4]
	ldr	w0, [x4, 72]
	add	x4, x4, x1, lsl 5
	ldr	w1, [x4, 16]
	add	w20, w20, w1
	lsl	w20, w20, 3
	sub	w0, w20, w0
	str	w0, [x4, 24]
	ldr	x1, [x19, 632]
	ldrb	w0, [x1]
	add	x0, x1, x0, lsl 5
	ldp	w4, w1, [x0, 28]
	ubfiz	w1, w1, 3, 2
	add	w1, w1, w4
	str	w1, [x0, 28]
	ldr	x1, .LC330
	ldr	x4, [x19, 632]
	ldrb	w0, [x4]
	add	x4, x4, x0, lsl 5
	mov	w0, 7
	ldr	w5, [x4, 32]
	and	w5, w5, -4
	str	w5, [x4, 32]
	ldr	x6, [x19, 632]
	add	x3, x6, x3
	ldrb	w5, [x6]
	ldp	w4, w3, [x3, 24]
	add	x5, x6, x5, lsl 5
	ldr	w5, [x5, 32]
	bl	dprint_vfmw
	ldr	x0, [x19, 632]
	ldr	w2, [x0, 76]
	sub	w1, w2, #1
	cmp	w1, 1
	bhi	.L1826
	ldrb	w20, [x0]
	add	w3, w20, 1
	cmp	w3, 1
	ccmp	w2, w3, 0, ls
	bls	.L1809
	ldr	x21, .LC334
	add	w20, w20, 2
	.p2align 2
.L1810:
	sub	w2, w20, #1
	mov	x1, x21
	ubfiz	x3, x2, 5, 32
	add	x4, x0, x3
	mov	w0, 7
	str	wzr, [x4, 28]
	ldr	x4, [x19, 632]
	add	x4, x4, x3
	ldr	w5, [x4, 20]
	str	w5, [x4, 32]
	ldr	x4, [x19, 632]
	add	x4, x4, x3
	ldr	w5, [x4, 16]
	lsl	w5, w5, 3
	str	w5, [x4, 24]
	ldr	x4, [x19, 632]
	add	x4, x4, x3
	ldp	w6, w5, [x4, 28]
	ubfiz	w5, w5, 3, 2
	add	w5, w5, w6
	str	w5, [x4, 28]
	ldr	x4, [x19, 632]
	add	x4, x4, x3
	ldr	w5, [x4, 32]
	and	w5, w5, -4
	str	w5, [x4, 32]
	ldr	x4, [x19, 632]
	add	x3, x4, x3
	ldp	w4, w3, [x3, 24]
	bl	dprint_vfmw
	ldr	x0, [x19, 632]
	cmp	w20, 1
	cset	w3, ls
	ldr	w1, [x0, 76]
	cmp	w1, w20
	add	w20, w20, 1
	cset	w2, hi
	tst	w3, w2
	bne	.L1810
	sub	w1, w1, #1
.L1809:
	ubfiz	x1, x1, 5, 32
	ldr	w2, [x0, 80]
	add	x0, x0, x1
	add	x5, x19, 61440
	ldr	w1, [x0, 24]
	sub	w1, w1, w2
	str	w1, [x0, 24]
	ldr	x3, [x19, 632]
	ldrb	w0, [x3]
	ldr	w4, [x3, 76]
	cmp	w0, w4
	bcs	.L1803
	.p2align 2
.L1820:
	ubfiz	x1, x0, 5, 32
	ldr	w2, [x5, 2424]
	add	x1, x3, x1
	add	w0, w0, 1
	ldr	w1, [x1, 32]
	cmp	w1, w2
	bcs	.L1812
	str	w1, [x5, 2424]
	ldr	w4, [x3, 76]
.L1812:
	cmp	w4, w0
	bhi	.L1820
.L1803:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1826:
	ldr	x1, .LC332
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L1815:
	mov	w20, 0
	b	.L1805
	.size	CalcStreamBits, .-CalcStreamBits
	.align	3
.LC328:
	.xword	.LC327
	.align	3
.LC330:
	.xword	.LC329
	.align	3
.LC332:
	.xword	.LC331
	.align	3
.LC334:
	.xword	.LC333
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Scaling_List
	.type	Scaling_List, %function
Scaling_List:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	str	x0, [x29, 104]
	mov	x0, x30
	mov	w27, w3
	mov	x28, x1
	mov	x25, x2
	mov	x22, x4
	bl	_mcount
	cmp	w27, wzr
	ble	.L1827
	sub	w26, w27, #1
	mov	w0, 8
	ldr	x21, .LC337
	add	x26, x26, 1
	mov	x20, 0
	mov	w24, w0
	mov	w23, 255
	b	.L1832
	.p2align 3
.L1831:
	lsr	w6, w19, 2
	str	w24, [x28, w19, uxtw 2]
	ubfiz	w1, w19, 3, 2
	and	w4, w24, 255
	lsl	w5, w23, w1
	lsl	w4, w4, w1
	ldr	w1, [x25, w6, sxtw 2]
	cmp	x26, x20
	bic	w1, w1, w5
	orr	w1, w1, w4
	str	w1, [x25, w6, sxtw 2]
	beq	.L1827
.L1832:
	cmp	w27, 16
	add	x1, x21, 16
	beq	.L1840
	ldrb	w19, [x20, x1]
.L1830:
	add	x20, x20, 1
	cbz	w0, .L1831
	ldr	x1, .LC339
	ldr	x0, [x29, 104]
	bl	se_v
	add	w0, w0, w24
	and	w0, w0, 255
	cmp	w19, wzr
	ccmp	w0, wzr, 0, eq
	cset	w1, eq
	cmp	w0, wzr
	csel	w24, w24, w0, eq
	str	w1, [x22]
	b	.L1831
	.p2align 3
.L1840:
	ldrb	w19, [x21, x20]
	b	.L1830
	.p2align 3
.L1827:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.size	Scaling_List, .-Scaling_List
	.align	3
.LC337:
	.xword	.LANCHOR2
	.align	3
.LC339:
	.xword	.LC338
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProcessPPS
	.type	ProcessPPS, %function
ProcessPPS:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	add	x21, x19, 65536
	bl	_mcount
	ldr	x1, .LC343
	mov	x0, x19
	bl	u_1
	strb	w0, [x20]
	ldr	w0, [x21, 1584]
	cbnz	w0, .L1892
	ldr	x1, .LC345
	mov	x0, x19
	bl	u_1
	strb	w0, [x20, 1]
	ldr	w0, [x21, 1584]
	cbnz	w0, .L1892
	ldr	x1, .LC347
	mov	x0, x19
	bl	ue_v
	str	w0, [x20, 32]
	cbnz	w0, .L1845
	ldr	w0, [x21, 1584]
	cbz	w0, .L1846
.L1845:
	ldr	x1, .LC349
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC350
	ldr	x4, [x0]
	cbz	x4, .L1892
	ldr	w0, [x21, 1644]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
	mov	w0, -1
.L1843:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L1846:
	ldr	x1, .LC352
	mov	x0, x19
	bl	ue_v
	cmp	w0, 31
	str	w0, [x20, 36]
	bhi	.L1847
	ldr	w0, [x21, 1584]
	cbnz	w0, .L1847
	ldr	x1, .LC356
	mov	x0, x19
	bl	ue_v
	cmp	w0, 31
	str	w0, [x20, 40]
	bhi	.L1849
	ldr	w0, [x21, 1584]
	cbnz	w0, .L1849
	ldr	x1, .LC360
	mov	x0, x19
	bl	u_1
	strb	w0, [x20, 2]
	ldr	w0, [x21, 1584]
	cbnz	w0, .L1892
	ldr	x2, .LC362
	mov	w1, 2
	mov	x0, x19
	bl	u_v
	cmp	w0, 2
	str	w0, [x20, 44]
	bhi	.L1893
	ldr	x1, .LC366
	mov	x0, x19
	bl	se_v
	str	w0, [x20, 48]
	ldr	x1, .LC368
	mov	x0, x19
	bl	se_v
	ldr	x1, .LC370
	mov	x0, x19
	bl	se_v
	str	w0, [x20, 52]
	ldr	x1, .LC372
	mov	x0, x19
	bl	u_1
	strb	w0, [x20, 3]
	ldr	x1, .LC374
	mov	x0, x19
	bl	u_1
	strb	w0, [x20, 4]
	ldr	x1, .LC376
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20, 17]
	cbnz	w0, .L1894
.L1852:
	ldr	w1, [x20, 52]
	add	x0, x19, 12288
	stp	w1, wzr, [x20, 56]
	strb	wzr, [x20, 18]
	add	x0, x0, 2600
	bl	BsResidBits
	ldr	x1, [x19, 632]
	ldr	w1, [x1, 80]
	add	w1, w1, 3
	cmp	w0, w1
	bcc	.L1873
	ldr	x1, .LC380
	mov	x0, x19
	bl	u_1
	str	w0, [x20, 60]
	ldr	x1, .LC382
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x20, 18]
	beq	.L1854
.L1872:
	ldr	x1, .LC384
	mov	x0, x19
	bl	se_v
	add	w1, w0, 12
	cmp	w1, 24
	str	w0, [x20, 56]
	bhi	.L1855
	ldr	w0, [x21, 1584]
	cbz	w0, .L1873
.L1855:
	ldr	x1, .LC391
	mov	w0, 1
	bl	dprint_vfmw
.L1892:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, -1
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L1873:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, 0
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L1894:
	ldr	x1, .LC378
	mov	w0, 1
	bl	dprint_vfmw
	b	.L1852
	.p2align 3
.L1847:
	ldr	x1, .LC354
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1843
	.p2align 3
.L1849:
	ldr	x1, .LC358
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1843
	.p2align 3
.L1854:
	ldr	x28, .LC387
	add	x22, x29, 120
	ldr	x26, .LC386
	add	x24, x20, 5
	add	x23, x20, 1984
	add	x25, x20, 64
	mov	w27, 0
	b	.L1863
	.p2align 3
.L1899:
	ldr	w0, [x20, 28]
	mov	w1, 4000
	umull	x0, w0, w1
	ldr	x1, [x19, 14960]
	add	x0, x1, x0
	ldrb	w1, [x0, 25]
	cmp	w1, 1
	beq	.L1895
	ldr	x0, .LC387
	ldr	x3, [x0, 104]
	ldr	x0, .LC341
	add	x1, x0, 96
	cbz	w27, .L1896
.L1891:
	mov	x2, 16
	mov	x0, x23
	blr	x3
.L1858:
	add	w27, w27, 1
	add	x22, x22, 4
	cmp	w27, 6
	add	x24, x24, 1
	add	x23, x23, 16
	add	x25, x25, 64
	beq	.L1897
.L1863:
	mov	x1, x26
	mov	x0, x19
	bl	u_1
	cmp	w0, 1
	strb	w0, [x24]
	str	w0, [x22]
	beq	.L1898
	cmp	w27, wzr
	ccmp	w27, 3, 4, ne
	beq	.L1899
	sub	w1, w27, #1
	ldr	x3, [x28, 104]
	add	x1, x1, 124
	add	x1, x20, x1, lsl 4
	b	.L1891
	.p2align 3
.L1897:
	ldr	x22, .LC387
	add	x26, x20, 2080
	ldr	x24, .LC341
	add	x27, x20, 448
	mov	x28, 0
	add	x23, x29, 112
	mov	w25, 4000
.L1871:
	ldr	w0, [x20, 60]
	mov	w8, w28
	cmp	w0, 1
	beq	.L1900
	add	x0, x20, x28
	str	wzr, [x23, x28, lsl 2]
	strb	wzr, [x0, 11]
.L1866:
	ldr	w0, [x20, 28]
	ldr	x1, [x19, 14960]
	umull	x0, w0, w25
	add	x0, x1, x0
	ldrb	w1, [x0, 25]
	cmp	w1, 1
	beq	.L1901
	add	x1, x24, 176
	ldr	x3, [x22, 104]
	cbz	w8, .L1902
.L1870:
	mov	x2, 64
	mov	x0, x26
	blr	x3
.L1867:
	add	x28, x28, 1
	add	x26, x26, 64
	cmp	x28, 2
	add	x27, x27, 256
	bne	.L1871
	b	.L1872
	.p2align 3
.L1898:
	mov	x0, x19
	mov	x4, x22
	mov	w3, 16
	mov	x2, x23
	mov	x1, x25
	bl	Scaling_List
	ldr	w0, [x22]
	cmp	w0, 1
	bne	.L1858
	ldr	x0, .LC341
	cmp	w27, 2
	add	x1, x0, 80
	add	x0, x0, 96
	csel	x1, x0, x1, hi
.L1890:
	ldr	x0, .LC387
	mov	x2, 16
	ldr	x3, [x0, 104]
	mov	x0, x23
	blr	x3
	b	.L1858
.L1895:
	uxtw	x1, w27
	add	x1, x0, x1, lsl 4
	add	x1, x1, 1972
	b	.L1890
.L1893:
	ldr	x1, .LC364
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1843
.L1900:
	ldr	x1, .LC389
	mov	x0, x19
	str	w28, [x29, 108]
	bl	u_1
	cmp	w0, 1
	add	x1, x20, x28
	str	w0, [x23, x28, lsl 2]
	ldr	w8, [x29, 108]
	strb	w0, [x1, 11]
	bne	.L1866
	mov	x0, x19
	add	x4, x23, x28, lsl 2
	mov	w3, 64
	mov	x2, x26
	mov	x1, x27
	str	w8, [x29, 108]
	bl	Scaling_List
	ldr	w0, [x23, x28, lsl 2]
	ldr	w8, [x29, 108]
	cmp	w0, 1
	bne	.L1867
	ldr	x0, .LC387
	ldr	x3, [x0, 104]
	ldr	x0, .LC341
	add	x1, x0, 176
	cbnz	w8, .L1870
	add	x1, x0, 112
	b	.L1870
	.p2align 3
.L1901:
	ubfiz	x8, x8, 6, 32
	mov	x2, 64
	add	x1, x0, x8
	ldr	x0, .LC387
	add	x1, x1, 2068
	ldr	x3, [x0, 104]
	mov	x0, x26
	blr	x3
	b	.L1867
.L1896:
	add	x1, x0, 80
	b	.L1891
.L1902:
	ldr	x1, .LC341
	add	x1, x1, 112
	b	.L1870
	.size	ProcessPPS, .-ProcessPPS
	.align	3
.LC341:
	.xword	.LANCHOR1
	.align	3
.LC343:
	.xword	.LC342
	.align	3
.LC345:
	.xword	.LC344
	.align	3
.LC347:
	.xword	.LC346
	.align	3
.LC349:
	.xword	.LC348
	.align	3
.LC350:
	.xword	g_event_report
	.align	3
.LC352:
	.xword	.LC351
	.align	3
.LC354:
	.xword	.LC353
	.align	3
.LC356:
	.xword	.LC355
	.align	3
.LC358:
	.xword	.LC357
	.align	3
.LC360:
	.xword	.LC359
	.align	3
.LC362:
	.xword	.LC361
	.align	3
.LC364:
	.xword	.LC363
	.align	3
.LC366:
	.xword	.LC365
	.align	3
.LC368:
	.xword	.LC367
	.align	3
.LC370:
	.xword	.LC369
	.align	3
.LC372:
	.xword	.LC371
	.align	3
.LC374:
	.xword	.LC373
	.align	3
.LC376:
	.xword	.LC375
	.align	3
.LC378:
	.xword	.LC377
	.align	3
.LC380:
	.xword	.LC379
	.align	3
.LC382:
	.xword	.LC381
	.align	3
.LC384:
	.xword	.LC383
	.align	3
.LC386:
	.xword	.LC385
	.align	3
.LC387:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC389:
	.xword	.LC388
	.align	3
.LC391:
	.xword	.LC390
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PPSEqual
	.type	PPSEqual, %function
PPSEqual:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cbz	x19, .L1925
	cbz	x20, .L1926
	ldrb	w3, [x19]
	ldrb	w2, [x20]
	ldrb	w1, [x19, 1]
	ldrb	w0, [x20, 1]
	cmp	w3, w2
	ldp	w4, w2, [x19, 24]
	ccmp	w1, w0, 0, eq
	ldr	w5, [x19, 36]
	ldp	w3, w0, [x20, 24]
	cset	w1, eq
	ldrb	w7, [x19, 2]
	cmp	w4, w3
	ldr	w3, [x19, 40]
	ccmp	w2, w0, 0, eq
	ldr	w6, [x19, 48]
	ldp	w4, w0, [x20, 36]
	cset	w2, eq
	ldr	w10, [x19, 60]
	cmp	w5, w4
	ldrb	w5, [x20, 2]
	ccmp	w3, w0, 0, eq
	ldr	w4, [x19, 44]
	cset	w3, eq
	cmp	w7, w5
	ldp	w0, w5, [x20, 44]
	ldr	w7, [x19, 52]
	and	w1, w1, w2
	ccmp	w4, w0, 0, eq
	ldr	w4, [x20, 52]
	cset	w0, eq
	cmp	w6, w5
	ldrb	w5, [x20, 3]
	and	w1, w3, w1
	ldrb	w6, [x19, 3]
	ccmp	w7, w4, 0, eq
	cset	w4, eq
	ldrb	w2, [x20, 4]
	and	w0, w0, w1
	cmp	w6, w5
	ldrb	w5, [x19, 4]
	and	w0, w4, w0
	ldr	w4, [x20, 60]
	ccmp	w5, w2, 0, eq
	ldrb	w3, [x19, 18]
	ldrb	w1, [x20, 18]
	cset	w2, eq
	cmp	w4, w10
	and	w0, w2, w0
	ccmp	w1, w3, 0, eq
	cset	w2, eq
	and	w2, w2, w0
	cbz	w3, .L1907
	lsl	w10, w10, 1
	cmn	w10, #6
	beq	.L1907
	mov	x1, x20
	add	x7, x19, 64
	mov	w9, -6
	mov	x8, 0
	.p2align 2
.L1912:
	add	x3, x19, x8
	add	x0, x20, x8
	ldrsb	w3, [x3, 5]
	ldrsb	w0, [x0, 5]
	cmp	w0, w3
	cset	w0, eq
	and	w2, w2, w0
	cbz	w3, .L1908
	cmp	w8, 5
	bhi	.L1909
	sub	x0, x7, #64
	mov	x3, x1
	.p2align 2
.L1910:
	ldr	w5, [x0, 64]
	add	x0, x0, 4
	ldr	w4, [x3, 64]
	add	x3, x3, 4
	cmp	w5, w4
	cset	w4, eq
	cmp	x7, x0
	and	w2, w2, w4
	bne	.L1910
.L1908:
	add	w9, w9, 1
	add	x8, x8, 1
	cmp	w9, w10
	add	x1, x1, 64
	add	x7, x7, 64
	bne	.L1912
.L1907:
	ldr	w0, [x20, 56]
	ldr	w1, [x19, 56]
	cmp	w1, w0
	cset	w0, eq
	tst	w0, w2
	csetm	w0, eq
.L1905:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1909:
	ubfiz	x0, x9, 8, 32
	add	x3, x0, 448
	add	x6, x0, 704
	add	x6, x19, x6
	add	x0, x19, x3
	add	x3, x20, x3
	.p2align 2
.L1911:
	ldr	w5, [x0], 4
	ldr	w4, [x3], 4
	cmp	w5, w4
	cset	w4, eq
	cmp	x6, x0
	and	w2, w2, w4
	bne	.L1911
	add	w9, w9, 1
	add	x8, x8, 1
	cmp	w9, w10
	add	x1, x1, 64
	add	x7, x7, 64
	bne	.L1912
	b	.L1907
.L1926:
	ldr	x2, .LC392
	mov	w3, 9299
	ldr	x1, .LC393
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1905
.L1925:
	ldr	x2, .LC392
	mov	w3, 9298
	ldr	x1, .LC393
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1905
	.size	PPSEqual, .-PPSEqual
	.align	3
.LC392:
	.xword	.LC53
	.align	3
.LC393:
	.xword	.LC55
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_DecPPS
	.type	H264_DecPPS, %function
H264_DecPPS:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC395
	mov	x0, x19
	bl	ue_v
	mov	w20, w0
	ldr	w0, [x19, 14948]
	sub	w0, w0, #1
	cmp	w20, w0
	bls	.L1928
	ldr	x1, .LC397
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x19, 14948]
	sub	w1, w0, #1
	cmp	w20, w1
	bls	.L1936
	ldr	x1, .LC398
	ldr	x4, [x1]
	cbz	x4, .L1936
	add	x19, x19, 65536
	mov	w3, 8
	stp	w20, w0, [x29, 56]
	add	x2, x29, 56
	mov	w1, 110
	ldr	w0, [x19, 1644]
	blr	x4
	mov	w0, -1
.L1929:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1928:
	ldr	x1, .LC400
	mov	x0, x19
	bl	ue_v
	mov	w2, w0
	ldr	w0, [x19, 14944]
	sub	w0, w0, #1
	cmp	w2, w0
	bhi	.L1940
	mov	w0, 4000
	ldr	x1, [x19, 14960]
	umull	x0, w2, w0
	add	x0, x1, x0
	ldrb	w0, [x0, 23]
	cbz	w0, .L1941
	mov	w21, 2208
	ldr	x0, [x19, 14968]
	umull	x21, w20, w21
	add	x0, x0, x21
	ldrb	w1, [x0, 19]
	cbz	w1, .L1932
	ldr	x22, .LC405
	mov	x0, x19
	mov	x1, x22
	stp	w20, w2, [x22, 24]
	bl	ProcessPPS
	cbnz	w0, .L1942
	ldr	x1, [x19, 14968]
	mov	x0, x22
	add	x1, x1, x21
	bl	PPSEqual
	cbz	w0, .L1929
	ldr	x3, .LC409
	mov	w1, 1
	ldr	x0, [x19, 14968]
	mov	x2, 2208
	strb	w1, [x22, 20]
	ldr	x3, [x3, 112]
	add	x0, x0, x21
	strb	w1, [x22, 19]
	mov	x1, x22
	blr	x3
	mov	w0, 0
	b	.L1929
	.p2align 3
.L1932:
	str	w20, [x0, 24]
	mov	x0, x19
	ldr	x1, [x19, 14968]
	add	x1, x1, x21
	str	w2, [x1, 28]
	ldr	x1, [x19, 14968]
	add	x1, x1, x21
	bl	ProcessPPS
	cbnz	w0, .L1943
	ldr	x1, [x19, 14968]
	mov	w2, 1
	add	x1, x1, x21
	strb	w2, [x1, 20]
	ldr	x1, [x19, 14968]
	add	x21, x1, x21
	strb	w2, [x21, 19]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1936:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, -1
	ldp	x29, x30, [sp], 64
	ret
.L1940:
	ldr	x1, .LC402
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1929
.L1942:
	ldr	x2, .LC406
	mov	w0, 1
	ldr	x1, .LC408
	add	x2, x2, 80
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1929
.L1941:
	ldr	x1, .LC404
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1929
.L1943:
	ldr	x2, .LC406
	mov	w0, 1
	ldr	x1, .LC411
	add	x2, x2, 80
	bl	dprint_vfmw
	ldr	x1, [x19, 14968]
	mov	w2, 1
	mov	w0, -1
	add	x1, x1, x21
	strb	w2, [x1, 20]
	ldr	x1, [x19, 14968]
	add	x21, x1, x21
	strb	wzr, [x21, 19]
	b	.L1929
	.size	H264_DecPPS, .-H264_DecPPS
	.align	3
.LC395:
	.xword	.LC394
	.align	3
.LC397:
	.xword	.LC396
	.align	3
.LC398:
	.xword	g_event_report
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
.LC405:
	.xword	.LANCHOR3
	.align	3
.LC406:
	.xword	.LANCHOR2
	.align	3
.LC408:
	.xword	.LC407
	.align	3
.LC409:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC411:
	.xword	.LC410
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	vui_parameters
	.type	vui_parameters, %function
vui_parameters:
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
	ldr	x1, .LC413
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20]
	cbnz	w0, .L1987
	strb	wzr, [x20, 15]
.L1946:
	ldr	x1, .LC421
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20, 1]
	cbnz	w0, .L1988
.L1947:
	ldr	x1, .LC425
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20, 3]
	cbnz	w0, .L1989
	mov	w0, 5
	str	w0, [x20, 28]
.L1949:
	ldr	x1, .LC439
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20, 6]
	cbnz	w0, .L1990
.L1950:
	ldr	x1, .LC445
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20, 8]
	cbnz	w0, .L1991
.L1952:
	ldr	x1, .LC454
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20, 7]
	cbz	w0, .L1954
	ldr	x1, .LC456
	mov	x0, x19
	add	x24, x20, 84
	bl	ue_v
	ldr	x2, .LC458
	mov	w1, 4
	str	w0, [x24, 36]
	mov	x0, x19
	bl	u_v
	strb	w0, [x24, 32]
	ldr	x2, .LC460
	mov	w1, 4
	mov	x0, x19
	bl	u_v
	strb	w0, [x24, 33]
	ldr	w1, [x24, 36]
	cmp	w1, 31
	bhi	.L1957
	add	x28, x19, 65536
	ldr	w0, [x28, 1584]
	cbnz	w0, .L1957
	ldr	x27, .LC464
	mov	w21, 0
	ldr	x26, .LC466
	ldr	x25, .LC468
	.p2align 2
.L1958:
	uxtw	x22, w21
	mov	x1, x27
	mov	x0, x19
	add	w21, w21, 1
	add	x23, x20, x22, lsl 2
	bl	ue_v
	mov	x1, x26
	str	w0, [x23, 124]
	mov	x0, x19
	bl	ue_v
	str	w0, [x23, 252]
	mov	x1, x25
	mov	x0, x19
	bl	u_1
	strb	w0, [x24, x22]
	ldr	w0, [x24, 36]
	cmp	w0, w21
	bcs	.L1958
	ldr	x2, .LC470
	mov	w1, 5
	mov	x0, x19
	bl	u_v
	str	w0, [x24, 296]
	ldr	x2, .LC472
	mov	w1, 5
	mov	x0, x19
	bl	u_v
	str	w0, [x24, 300]
	ldr	x2, .LC474
	mov	w1, 5
	mov	x0, x19
	bl	u_v
	str	w0, [x24, 304]
	ldr	x2, .LC476
	mov	w1, 5
	mov	x0, x19
	bl	u_v
	str	w0, [x24, 308]
.L1954:
	ldr	x1, .LC478
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20, 10]
	cbnz	w0, .L1992
	ldrb	w0, [x20, 7]
	add	x28, x19, 65536
	cbz	w0, .L1962
.L1963:
	ldr	x1, .LC480
	mov	x0, x19
	bl	u_1
	strb	w0, [x20, 14]
.L1962:
	ldr	x1, .LC482
	mov	x0, x19
	bl	u_1
	strb	w0, [x20, 11]
	ldr	x1, .LC484
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20, 12]
	cbnz	w0, .L1964
	ldr	w0, [x28, 1584]
.L1965:
	cmp	w0, wzr
	csetm	w0, ne
.L1986:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1991:
	ldr	x2, .LC447
	mov	w1, 32
	mov	x0, x19
	bl	u_v
	str	w0, [x20, 52]
	ldr	x2, .LC449
	mov	w1, 32
	mov	x0, x19
	bl	u_v
	str	w0, [x20, 56]
	ldr	x1, .LC451
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x20, 9]
	bne	.L1952
	ldr	w1, [x20, 52]
	cbz	w1, .L1952
	ldr	w0, [x20, 56]
	mov	w3, 10000
	ldr	x2, .LC452
	add	x28, x19, 65536
	umull	x0, w0, w3
	ldr	x2, [x2, 472]
	lsr	x0, x0, 1
	blr	x2
	add	w0, w0, 5
	mov	w1, 52429
	movk	w1, 0xcccc, lsl 16
	umull	x0, w0, w1
	lsr	x0, x0, 35
	str	w0, [x28, 324]
	b	.L1952
	.p2align 3
.L1990:
	ldr	x1, .LC441
	mov	x0, x19
	bl	ue_v
	str	w0, [x20, 44]
	ldr	x1, .LC443
	mov	x0, x19
	bl	ue_v
	str	w0, [x20, 48]
	b	.L1950
	.p2align 3
.L1989:
	ldr	x2, .LC427
	mov	w1, 3
	mov	x0, x19
	bl	u_v
	str	w0, [x20, 28]
	ldr	x1, .LC429
	mov	x0, x19
	bl	u_1
	strb	w0, [x20, 4]
	ldr	x1, .LC431
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20, 5]
	cbz	w0, .L1949
	ldr	x2, .LC433
	mov	w1, 8
	mov	x0, x19
	bl	u_v
	str	w0, [x20, 32]
	ldr	x2, .LC435
	mov	w1, 8
	mov	x0, x19
	bl	u_v
	str	w0, [x20, 36]
	ldr	x2, .LC437
	mov	w1, 8
	mov	x0, x19
	bl	u_v
	str	w0, [x20, 40]
	b	.L1949
	.p2align 3
.L1988:
	ldr	x1, .LC423
	mov	x0, x19
	bl	u_1
	strb	w0, [x20, 2]
	b	.L1947
	.p2align 3
.L1987:
	ldr	x2, .LC415
	mov	w1, 8
	mov	x0, x19
	bl	u_v
	uxtb	w0, w0
	cmp	w0, 255
	strb	w0, [x20, 15]
	bne	.L1946
	ldr	x2, .LC417
	mov	w1, 16
	mov	x0, x19
	bl	u_v
	str	w0, [x20, 16]
	ldr	x2, .LC419
	mov	w1, 16
	mov	x0, x19
	bl	u_v
	str	w0, [x20, 20]
	b	.L1946
	.p2align 3
.L1992:
	ldr	x1, .LC456
	mov	x0, x19
	add	x24, x20, 396
	bl	ue_v
	ldr	x2, .LC458
	mov	w1, 4
	str	w0, [x24, 36]
	mov	x0, x19
	bl	u_v
	strb	w0, [x24, 32]
	ldr	x2, .LC460
	mov	w1, 4
	mov	x0, x19
	bl	u_v
	strb	w0, [x24, 33]
	ldr	w1, [x24, 36]
	cmp	w1, 31
	bhi	.L1957
	add	x28, x19, 65536
	ldr	w0, [x28, 1584]
	cbnz	w0, .L1957
	ldr	x27, .LC464
	mov	w21, 0
	ldr	x26, .LC466
	ldr	x25, .LC468
	.p2align 2
.L1960:
	uxtw	x22, w21
	mov	x1, x27
	mov	x0, x19
	add	w21, w21, 1
	add	x23, x20, x22, lsl 2
	bl	ue_v
	mov	x1, x26
	str	w0, [x23, 436]
	mov	x0, x19
	bl	ue_v
	str	w0, [x23, 564]
	mov	x1, x25
	mov	x0, x19
	bl	u_1
	strb	w0, [x24, x22]
	ldr	w0, [x24, 36]
	cmp	w0, w21
	bcs	.L1960
	ldr	x2, .LC470
	mov	w1, 5
	mov	x0, x19
	bl	u_v
	str	w0, [x24, 296]
	ldr	x2, .LC472
	mov	w1, 5
	mov	x0, x19
	bl	u_v
	str	w0, [x24, 300]
	ldr	x2, .LC474
	mov	w1, 5
	mov	x0, x19
	bl	u_v
	str	w0, [x24, 304]
	ldr	x2, .LC476
	mov	w1, 5
	mov	x0, x19
	bl	u_v
	str	w0, [x24, 308]
	ldrb	w0, [x20, 7]
	cbnz	w0, .L1963
	ldrb	w0, [x20, 10]
	cbnz	w0, .L1963
	b	.L1962
	.p2align 3
.L1964:
	ldr	x1, .LC486
	mov	x0, x19
	bl	u_1
	strb	w0, [x20, 13]
	ldr	x1, .LC488
	mov	x0, x19
	bl	ue_v
	str	w0, [x20, 60]
	ldr	x1, .LC490
	mov	x0, x19
	bl	ue_v
	str	w0, [x20, 64]
	ldr	x1, .LC492
	mov	x0, x19
	bl	ue_v
	str	w0, [x20, 72]
	ldr	x1, .LC494
	mov	x0, x19
	bl	ue_v
	str	w0, [x20, 68]
	ldr	x1, .LC496
	mov	x0, x19
	bl	ue_v
	str	w0, [x20, 76]
	ldr	x1, .LC498
	mov	x0, x19
	bl	ue_v
	str	w0, [x20, 80]
	ldr	w0, [x28, 1584]
	cbz	w0, .L1965
	mov	w0, -1
	b	.L1986
.L1957:
	ldr	x1, .LC462
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1986
	.size	vui_parameters, .-vui_parameters
	.align	3
.LC413:
	.xword	.LC412
	.align	3
.LC415:
	.xword	.LC414
	.align	3
.LC417:
	.xword	.LC416
	.align	3
.LC419:
	.xword	.LC418
	.align	3
.LC421:
	.xword	.LC420
	.align	3
.LC423:
	.xword	.LC422
	.align	3
.LC425:
	.xword	.LC424
	.align	3
.LC427:
	.xword	.LC426
	.align	3
.LC429:
	.xword	.LC428
	.align	3
.LC431:
	.xword	.LC430
	.align	3
.LC433:
	.xword	.LC432
	.align	3
.LC435:
	.xword	.LC434
	.align	3
.LC437:
	.xword	.LC436
	.align	3
.LC439:
	.xword	.LC438
	.align	3
.LC441:
	.xword	.LC440
	.align	3
.LC443:
	.xword	.LC442
	.align	3
.LC445:
	.xword	.LC444
	.align	3
.LC447:
	.xword	.LC446
	.align	3
.LC449:
	.xword	.LC448
	.align	3
.LC451:
	.xword	.LC450
	.align	3
.LC452:
	.xword	vfmw_Osal_Func_Ptr_S
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
	.align	3
.LC466:
	.xword	.LC465
	.align	3
.LC468:
	.xword	.LC467
	.align	3
.LC470:
	.xword	.LC469
	.align	3
.LC472:
	.xword	.LC471
	.align	3
.LC474:
	.xword	.LC473
	.align	3
.LC476:
	.xword	.LC475
	.align	3
.LC478:
	.xword	.LC477
	.align	3
.LC480:
	.xword	.LC479
	.align	3
.LC482:
	.xword	.LC481
	.align	3
.LC484:
	.xword	.LC483
	.align	3
.LC486:
	.xword	.LC485
	.align	3
.LC488:
	.xword	.LC487
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SPSEqual
	.type	SPSEqual, %function
SPSEqual:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cbz	x19, .L2025
	cbz	x20, .L2026
	ldp	w3, w6, [x19, 28]
	ldp	w2, w5, [x20, 28]
	ldrb	w1, [x19]
	ldrb	w0, [x20]
	cmp	w3, w2
	ldrb	w4, [x19, 1]
	ldrb	w2, [x20, 1]
	ccmp	w1, w0, 0, eq
	ldrb	w1, [x19, 2]
	cset	w3, eq
	ldrb	w0, [x20, 2]
	cmp	w4, w2
	ldr	w2, [x20, 36]
	ccmp	w1, w0, 0, eq
	ldr	w4, [x19, 36]
	cset	w0, eq
	ldrb	w1, [x19, 25]
	and	w0, w3, w0
	cmp	w6, w5
	ldrb	w3, [x20, 25]
	ccmp	w4, w2, 0, eq
	cset	w2, eq
	cmp	w3, w1
	and	w0, w2, w0
	cset	w2, eq
	and	w0, w2, w0
	cbz	w1, .L1997
	mov	x2, x19
	mov	x8, x20
	mov	w9, -6
	mov	x1, 0
	.p2align 2
.L2002:
	add	x4, x19, x1
	add	x3, x20, x1
	add	x6, x2, 64
	ldrsb	w3, [x3, 4]
	ldrsb	w4, [x4, 4]
	cmp	w3, w4
	cset	w3, eq
	and	w0, w0, w3
	cbz	w4, .L1998
	cmp	w1, 5
	bhi	.L1999
	mov	x3, x8
	.p2align 2
.L2000:
	ldr	w5, [x2, 52]
	add	x2, x2, 4
	ldr	w4, [x3, 52]
	add	x3, x3, 4
	cmp	w5, w4
	cset	w4, eq
	cmp	x2, x6
	and	w0, w0, w4
	bne	.L2000
.L1998:
	add	x1, x1, 1
	add	w9, w9, 1
	cmp	x1, 8
	mov	x2, x6
	add	x8, x8, 64
	bne	.L2002
.L1997:
	ldr	w4, [x19, 2196]
	ldr	w3, [x20, 2196]
	ldr	w2, [x20, 2200]
	ldr	w1, [x19, 2200]
	cmp	w4, w3
	ccmp	w2, w1, 0, eq
	cset	w2, eq
	and	w0, w2, w0
	cbz	w1, .L2004
	cmp	w1, 1
	bne	.L2003
	ldrb	w4, [x19, 16]
	ldrb	w3, [x20, 16]
	ldr	w2, [x19, 2208]
	ldr	w1, [x20, 2208]
	cmp	w4, w3
	ldr	w5, [x19, 2212]
	ldr	w4, [x20, 2212]
	ccmp	w2, w1, 0, eq
	ldr	w2, [x20, 2216]
	cset	w3, eq
	ldr	w1, [x19, 2216]
	cmp	w5, w4
	ccmp	w2, w1, 0, eq
	cset	w2, eq
	and	w2, w3, w2
	and	w0, w0, w2
	cbz	w1, .L2003
	sub	w5, w1, #1
	add	x2, x20, 2220
	add	x5, x5, 556
	add	x1, x19, 2220
	add	x5, x19, x5, lsl 2
	.p2align 2
.L2006:
	ldr	w4, [x1], 4
	ldr	w3, [x2], 4
	cmp	w4, w3
	cset	w3, eq
	cmp	x1, x5
	and	w0, w0, w3
	bne	.L2006
.L2003:
	ldr	w4, [x19, 3244]
	ldr	w3, [x20, 3244]
	ldrb	w2, [x19, 17]
	ldrb	w1, [x20, 17]
	cmp	w4, w3
	ldr	w6, [x19, 3248]
	ldr	w4, [x20, 3248]
	ccmp	w2, w1, 0, eq
	ldr	w5, [x19, 3252]
	cset	w2, eq
	ldr	w1, [x20, 3252]
	cmp	w6, w4
	ldrb	w3, [x19, 18]
	ldrb	w4, [x20, 18]
	ccmp	w5, w1, 0, eq
	cset	w1, eq
	cmp	w4, w3
	and	w2, w2, w1
	cset	w1, eq
	and	w1, w2, w1
	and	w0, w1, w0
	cbnz	w3, .L2007
	ldrb	w1, [x20, 19]
	ldrb	w2, [x19, 19]
	cmp	w2, w1
	cset	w1, eq
	and	w0, w0, w1
.L2007:
	ldrb	w4, [x19, 20]
	ldrb	w3, [x20, 20]
	ldrb	w2, [x20, 21]
	ldrb	w1, [x19, 21]
	cmp	w4, w3
	ccmp	w2, w1, 0, eq
	cset	w2, eq
	and	w0, w2, w0
	cbnz	w1, .L2027
.L2008:
	ldrb	w4, [x19, 22]
	ldrb	w3, [x20, 22]
	ldr	w1, [x20, 3316]
	ldr	w2, [x19, 3316]
	cmp	w4, w3
	ccmp	w2, w1, 0, eq
	cset	w1, eq
	tst	w1, w0
	csetm	w0, eq
.L1995:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2027:
	ldr	w4, [x19, 3264]
	ldr	w3, [x20, 3264]
	ldr	w2, [x19, 3268]
	ldr	w1, [x20, 3268]
	cmp	w4, w3
	ldr	w5, [x19, 3256]
	ldr	w4, [x20, 3256]
	ccmp	w2, w1, 0, eq
	ldr	w3, [x19, 3260]
	cset	w2, eq
	ldr	w1, [x20, 3260]
	cmp	w5, w4
	ccmp	w3, w1, 0, eq
	cset	w1, eq
	and	w1, w2, w1
	and	w0, w0, w1
	b	.L2008
	.p2align 3
.L1999:
	ubfiz	x3, x9, 8, 32
	add	x4, x3, 436
	add	x7, x3, 692
	add	x7, x19, x7
	add	x3, x19, x4
	add	x4, x20, x4
	.p2align 2
.L2001:
	ldr	w6, [x3], 4
	ldr	w5, [x4], 4
	cmp	w6, w5
	cset	w5, eq
	cmp	x3, x7
	and	w0, w0, w5
	bne	.L2001
	add	x1, x1, 1
	add	x6, x2, 64
	cmp	x1, 8
	add	w9, w9, 1
	mov	x2, x6
	add	x8, x8, 64
	bne	.L2002
	b	.L1997
	.p2align 3
.L2004:
	ldr	w1, [x20, 2204]
	ldr	w2, [x19, 2204]
	cmp	w2, w1
	cset	w1, eq
	and	w0, w0, w1
	b	.L2003
.L2026:
	ldr	x2, .LC499
	mov	w3, 9536
	ldr	x1, .LC500
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1995
.L2025:
	ldr	x2, .LC499
	mov	w3, 9535
	ldr	x1, .LC500
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1995
	.size	SPSEqual, .-SPSEqual
	.align	3
.LC499:
	.xword	.LC53
	.align	3
.LC500:
	.xword	.LC55
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264GetDar
	.type	H264GetDar, %function
H264GetDar:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	mov	w22, w2
	mov	w21, w3
	mov	w23, w4
	bl	_mcount
	cbz	w19, .L2040
	mov	w0, 255
	cmp	w19, 16
	ccmp	w19, w0, 4, gt
	bne	.L2040
	cmp	w20, wzr
	ccmp	w22, wzr, 4, ne
	ccmp	w19, w0, 0, eq
	beq	.L2040
	cmp	w19, 1
	beq	.L2053
	cmp	w19, 255
	beq	.L2031
	ldr	x0, .LC501
	sbfiz	x19, x19, 3, 32
	add	x0, x0, 96
	add	x1, x0, x19
	ldr	w20, [x0, x19]
	ldr	w22, [x1, 4]
.L2031:
	lsl	w20, w20, 10
	lsl	w21, w21, 10
	sdiv	w20, w20, w22
	sdiv	w2, w21, w23
	mul	w2, w20, w2
	cmp	w2, wzr
	add	w0, w2, 1023
	csel	w2, w0, w2, lt
	asr	w2, w2, 10
	subs	w1, w2, #2406
	bmi	.L2054
.L2032:
	subs	w0, w2, #2263
	bmi	.L2055
	cmp	w1, w0
	mov	w19, 4
	blt	.L2029
.L2036:
	subs	w1, w2, #1820
	bmi	.L2056
	cmp	w0, w1
	mov	w19, 3
	blt	.L2029
.L2037:
	subs	w0, w2, #1365
	bmi	.L2057
.L2035:
	mov	w19, 2
	cmp	w1, w0
	csinc	w19, w19, wzr, lt
	b	.L2029
	.p2align 3
.L2040:
	mov	w19, 0
	mov	w2, 0
.L2029:
	ldr	x1, .LC503
	mov	w3, w19
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2055:
	mov	w0, 2263
	mov	w19, 4
	sub	w0, w0, w2
	cmp	w1, w0
	blt	.L2029
	b	.L2036
	.p2align 3
.L2054:
	mov	w1, 2406
	sub	w1, w1, w2
	b	.L2032
	.p2align 3
.L2053:
	sub	w0, w23, #1080
	mov	w1, 1920
	and	w0, w0, -9
	cmp	w0, wzr
	ccmp	w21, w1, 0, eq
	bne	.L2058
.L2042:
	mov	w19, 2
	mov	w2, 0
	b	.L2029
	.p2align 3
.L2058:
	mov	w0, 720
	cmp	w21, 1280
	ccmp	w23, w0, 0, eq
	beq	.L2042
	mov	w0, 480
	cmp	w21, 640
	ccmp	w23, w0, 0, eq
	mov	w19, 5
	cset	w0, eq
	mov	w2, 0
	cmp	w0, wzr
	csinc	w19, w19, wzr, eq
	b	.L2029
	.p2align 3
.L2056:
	mov	w1, 1820
	mov	w19, 3
	sub	w1, w1, w2
	cmp	w0, w1
	blt	.L2029
	b	.L2037
.L2057:
	mov	w0, 1365
	sub	w0, w0, w2
	b	.L2035
	.size	H264GetDar, .-H264GetDar
	.align	3
.LC501:
	.xword	.LANCHOR2
	.align	3
.LC503:
	.xword	.LC502
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProcessSPS
	.type	ProcessSPS, %function
ProcessSPS:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L2183
	ldr	w0, [x19, 28]
	mov	w2, 144
	mov	w1, 110
	mov	w3, 86
	cmp	w0, 122
	ccmp	w0, w2, 4, ne
	cset	w2, eq
	cmp	w0, 100
	ccmp	w0, w1, 4, ne
	cset	w1, eq
	cmp	w0, 83
	ccmp	w0, w3, 4, ne
	orr	w0, w2, w1
	cset	w1, eq
	orr	w0, w1, w0
	cbnz	w0, .L2184
	mov	w0, 1
	strb	wzr, [x19, 25]
	str	w0, [x19, 40]
.L2076:
	ldr	x1, .LC530
	mov	x0, x20
	bl	ue_v
	cmp	w0, 12
	str	w0, [x19, 2196]
	bhi	.L2089
	add	x21, x20, 65536
	ldr	w0, [x21, 1584]
	cbnz	w0, .L2089
	ldr	x1, .LC534
	mov	x0, x20
	bl	ue_v
	cmp	w0, 2
	str	w0, [x19, 2200]
	bhi	.L2091
	ldr	w1, [x21, 1584]
	cbnz	w1, .L2091
	cbz	w0, .L2185
	cmp	w0, 1
	beq	.L2186
.L2095:
	ldr	x1, .LC591
	mov	x0, x20
	bl	ue_v
	str	w0, [x19, 3244]
	ldr	w0, [x21, 1584]
	cbnz	w0, .L2180
	ldr	x1, .LC554
	mov	x0, x20
	bl	u_1
	strb	w0, [x19, 17]
	ldr	w0, [x21, 1584]
	cbnz	w0, .L2180
	ldr	x1, .LC556
	mov	x0, x20
	bl	ue_v
	sub	w1, w0, #1
	cmp	w1, 509
	str	w0, [x19, 3248]
	bhi	.L2100
	ldr	w1, [x21, 1584]
	cbnz	w1, .L2100
	ldr	x1, .LC560
	mov	x0, x20
	bl	ue_v
	str	w0, [x19, 3252]
	ldr	w0, [x21, 1584]
	cbnz	w0, .L2180
	ldr	x1, .LC562
	mov	x0, x20
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x19, 18]
	ldr	w1, [x21, 1584]
	cbnz	w1, .L2180
	cbnz	w0, .L2187
	ldr	x1, .LC593
	mov	x0, x20
	bl	u_1
	ldr	w23, [x19, 3252]
	strb	w0, [x19, 19]
	add	w23, w23, 1
	cmp	w23, 255
	bhi	.L2133
	ldr	w0, [x19, 3248]
	cmp	w23, 1
	mov	w24, 2
	add	w0, w0, 1
	ccmp	w0, 3, 0, hi
	cset	w1, ls
	cbnz	w1, .L2133
.L2104:
	mul	w23, w24, w23
	lsl	w25, w0, 4
	mov	w1, 100663296
	lsl	w23, w23, 4
	mul	w0, w25, w23
	lsr	w0, w0, 1
	lsl	w22, w0, 2
	sub	w0, w22, w0
	cmp	w0, w1
	bhi	.L2188
	ldr	w2, [x19, 32]
	sub	w1, w2, #10
	cmp	w1, 31
	bls	.L2189
.L2106:
	ldr	x1, .LC569
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2172
	.p2align 3
.L2184:
	ldr	x1, .LC509
	mov	x0, x20
	bl	ue_v
	cmp	w0, 1
	str	w0, [x19, 40]
	bls	.L2190
.L2063:
	ldr	x1, .LC511
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, .LC513
	mov	x0, x20
	bl	ue_v
	uxth	w0, w0
	add	w2, w0, 8
	str	w2, [x19, 44]
	cmp	w2, 8
	beq	.L2191
.L2065:
	ldr	x1, .LC515
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC516
	ldr	x4, [x0]
	cbz	x4, .L2180
	add	x20, x20, 65536
	ldr	w0, [x19, 44]
	stp	wzr, w0, [x29, 120]
	mov	w3, 8
	add	x2, x29, 120
	ldr	w0, [x20, 1644]
	mov	w1, 119
	blr	x4
	mov	w0, -1
.L2172:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L2190:
	add	x21, x20, 65536
	ldr	w1, [x21, 1584]
	cbnz	w1, .L2063
	ldr	x1, .LC513
	mov	x0, x20
	bl	ue_v
	uxth	w0, w0
	add	w2, w0, 8
	str	w2, [x19, 44]
	cmp	w2, 8
	bne	.L2067
	ldr	w0, [x21, 1584]
	cbz	w0, .L2068
.L2067:
	ldr	x1, .LC515
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC516
	ldr	x4, [x0]
	cbz	x4, .L2068
	ldr	w1, [x19, 44]
	mov	w3, 8
	ldr	w0, [x21, 1644]
	add	x2, x29, 120
	stp	wzr, w1, [x29, 120]
	mov	w1, 119
	blr	x4
.L2068:
	ldr	x1, .LC518
	mov	x0, x20
	bl	ue_v
	uxth	w0, w0
	add	w2, w0, 8
	str	w2, [x19, 48]
	cmp	w2, 8
	bne	.L2070
	ldr	w0, [x21, 1584]
	cbnz	w0, .L2070
.L2071:
	ldr	x1, .LC522
	mov	x0, x20
	bl	u_1
	cbnz	w0, .L2073
	ldr	w0, [x21, 1584]
	cbnz	w0, .L2073
	ldr	x1, .LC526
	mov	x0, x20
	bl	u_1
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 25]
	bne	.L2076
	ldr	x26, .LC505
	add	x21, x29, 120
	ldr	x25, .LC527
	add	x23, x19, 4
	add	x22, x19, 1972
	add	x24, x19, 52
	mov	w28, 0
	ldr	x27, .LC528
	b	.L2082
	.p2align 3
.L2194:
	ldr	x0, .LC505
	cmp	w28, wzr
	ldr	x3, [x27, 104]
	mov	x2, 16
	add	x1, x0, 80
	add	x0, x26, 96
	csel	x1, x0, x1, ne
	mov	x0, x22
	blr	x3
.L2078:
	add	w28, w28, 1
	add	x21, x21, 4
	cmp	w28, 6
	add	x23, x23, 1
	add	x22, x22, 16
	add	x24, x24, 64
	beq	.L2192
.L2082:
	mov	x1, x25
	mov	x0, x20
	bl	u_1
	cmp	w0, 1
	strb	w0, [x23]
	str	w0, [x21]
	beq	.L2193
	cmp	w28, wzr
	ccmp	w28, 3, 4, ne
	beq	.L2194
	ldr	x0, .LC528
	sub	w1, w28, #1
	mov	x2, 16
	add	x1, x19, x1, lsl 4
	ldr	x3, [x0, 104]
	add	x1, x1, 1972
	mov	x0, x22
	blr	x3
	b	.L2078
	.p2align 3
.L2191:
	add	x0, x20, 65536
	ldr	w0, [x0, 1584]
	cbnz	w0, .L2065
	.p2align 2
.L2180:
	mov	w0, -1
.L2202:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L2185:
	ldr	x1, .LC538
	mov	x0, x20
	bl	ue_v
	cmp	w0, 12
	str	w0, [x19, 2204]
	bhi	.L2094
	ldr	w0, [x21, 1584]
	cbz	w0, .L2095
.L2094:
	ldr	x1, .LC540
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2172
	.p2align 3
.L2070:
	ldr	x1, .LC520
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC516
	ldr	x4, [x0]
	cbz	x4, .L2071
	ldr	w1, [x19, 48]
	mov	w3, 8
	ldr	w0, [x21, 1644]
	add	x2, x29, 120
	stp	wzr, w1, [x29, 120]
	mov	w1, 119
	blr	x4
	b	.L2071
	.p2align 3
.L2187:
	ldr	w23, [x19, 3252]
	strb	wzr, [x19, 19]
	sub	w0, w23, #1
	cmp	w0, 509
	bhi	.L2133
	ldr	w0, [x19, 3248]
	mov	w24, 1
	add	w23, w23, 1
	add	w0, w0, w24
	b	.L2104
	.p2align 3
.L2189:
	ldr	x3, .LC567
	ldrh	w1, [x3,w1,uxtw #1]
	adr	x3, .Lrtx2108
	add	x1, x3, w1, sxth #2
	br	x1
.Lrtx2108:
	.section	.rodata
	.align	0
	.align	2
.L2108:
	.2byte	(.L2107 - .Lrtx2108) / 4
	.2byte	(.L2140 - .Lrtx2108) / 4
	.2byte	(.L2110 - .Lrtx2108) / 4
	.2byte	(.L2110 - .Lrtx2108) / 4
	.2byte	(.L2106 - .Lrtx2108) / 4
	.2byte	(.L2106 - .Lrtx2108) / 4
	.2byte	(.L2106 - .Lrtx2108) / 4
	.2byte	(.L2106 - .Lrtx2108) / 4
	.2byte	(.L2106 - .Lrtx2108) / 4
	.2byte	(.L2106 - .Lrtx2108) / 4
	.2byte	(.L2110 - .Lrtx2108) / 4
	.2byte	(.L2111 - .Lrtx2108) / 4
	.2byte	(.L2113 - .Lrtx2108) / 4
	.2byte	(.L2106 - .Lrtx2108) / 4
	.2byte	(.L2106 - .Lrtx2108) / 4
	.2byte	(.L2106 - .Lrtx2108) / 4
	.2byte	(.L2106 - .Lrtx2108) / 4
	.2byte	(.L2106 - .Lrtx2108) / 4
	.2byte	(.L2106 - .Lrtx2108) / 4
	.2byte	(.L2106 - .Lrtx2108) / 4
	.2byte	(.L2113 - .Lrtx2108) / 4
	.2byte	(.L2114 - .Lrtx2108) / 4
	.2byte	(.L2115 - .Lrtx2108) / 4
	.2byte	(.L2106 - .Lrtx2108) / 4
	.2byte	(.L2106 - .Lrtx2108) / 4
	.2byte	(.L2106 - .Lrtx2108) / 4
	.2byte	(.L2106 - .Lrtx2108) / 4
	.2byte	(.L2106 - .Lrtx2108) / 4
	.2byte	(.L2106 - .Lrtx2108) / 4
	.2byte	(.L2106 - .Lrtx2108) / 4
	.2byte	(.L2117 - .Lrtx2108) / 4
	.2byte	(.L2117 - .Lrtx2108) / 4
	.text
	.p2align 3
.L2110:
	mov	w22, 60416
	movk	w22, 0xd, lsl 16
.L2109:
	udiv	w22, w22, w0
	mov	w2, 16
	ldr	x1, .LC571
	mov	w0, 21
	cmp	w22, w2
	csel	w22, w22, w2, ls
	mov	w2, w22
	bl	dprint_vfmw
	ldr	w2, [x19, 3244]
	cmp	w2, w22
	bhi	.L2118
	ldr	w0, [x21, 1584]
	cbz	w0, .L2119
.L2118:
	ldr	x1, .LC573
	mov	w3, w22
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x19, 3244]
	cmp	w0, 16
	bhi	.L2177
	cmp	w22, w0
	csel	w22, w22, w0, cs
.L2177:
	str	w22, [x19, 3244]
.L2119:
	ldr	x1, .LC575
	mov	x0, x20
	bl	u_1
	strb	w0, [x19, 20]
	ldr	w0, [x21, 1584]
	cbnz	w0, .L2180
	ldr	x1, .LC577
	mov	x0, x20
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x19, 21]
	ldr	w1, [x21, 1584]
	cbnz	w1, .L2180
	cbnz	w0, .L2195
.L2121:
	add	x2, x19, 3072
	lsr	w1, w25, 1
	lsr	w0, w23, 1
	stp	w25, w23, [x2, 204]
	stp	w1, w0, [x2, 212]
.L2123:
	ldr	x1, .LC587
	mov	x0, x20
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x19, 22]
	ldr	w1, [x21, 1584]
	cbnz	w1, .L2180
	mov	w1, 2
	str	w1, [x19, 3332]
	cbnz	w0, .L2196
	mov	w0, 5
	strb	wzr, [x19, 3307]
	str	w0, [x19, 3320]
	mov	w0, 0
.L2126:
	ldr	w1, [x19, 3308]
	mov	w4, w23
	ldr	w2, [x19, 3312]
	mov	w3, w25
	bl	H264GetDar
	str	w0, [x19, 3316]
	ldr	w1, [x19, 3244]
	cbz	w1, .L2129
	ldr	w0, [x19, 3372]
	cmp	w1, w0
	bls	.L2129
	cmp	w22, w1
	csel	w22, w22, w1, ls
.L2129:
	cmp	w22, 16
	mov	w1, 16
	ldr	x0, [x20]
	csel	w22, w22, w1, ls
	str	w22, [x20, 14952]
	ldr	w1, [x0, 28]
	cmp	w1, 25
	beq	.L2197
.L2130:
	add	w22, w22, 1
	mov	w0, 0
	str	w22, [x19, 3272]
	b	.L2172
	.p2align 3
.L2117:
	mov	w22, 12582912
	b	.L2109
	.p2align 3
.L2113:
	mov	w22, 30208
	movk	w22, 0x2f, lsl 16
	b	.L2109
.L2140:
	mov	w22, 17920
	movk	w22, 0x5, lsl 16
	b	.L2109
.L2111:
	mov	w22, 55296
	movk	w22, 0x1b, lsl 16
	b	.L2109
.L2115:
	mov	w22, 7864320
	b	.L2109
.L2114:
	mov	w22, 30720
	movk	w22, 0x69, lsl 16
	b	.L2109
.L2107:
	mov	w22, 20992
	movk	w22, 0x2, lsl 16
	b	.L2109
.L2133:
	ldr	x1, .LC564
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2172
	.p2align 3
.L2089:
	ldr	x1, .LC532
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2172
	.p2align 3
.L2195:
	ldr	x1, .LC579
	mov	x0, x20
	bl	ue_v
	str	w0, [x19, 3256]
	ldr	x1, .LC581
	mov	x0, x20
	bl	ue_v
	str	w0, [x19, 3260]
	ldr	x1, .LC583
	mov	x0, x20
	bl	ue_v
	str	w0, [x19, 3264]
	ldr	x1, .LC585
	mov	x0, x20
	bl	ue_v
	str	w0, [x19, 3268]
	ldr	w1, [x19, 3264]
	ldr	w2, [x19, 3256]
	lsl	w1, w1, 1
	ldr	w3, [x19, 3260]
	lsl	w2, w2, 1
	mul	w1, w1, w24
	sub	w4, w25, w2
	lsl	w24, w24, 1
	sub	w3, w4, w3, lsl 1
	sub	w4, w23, w1
	cmp	w3, wzr
	msub	w0, w24, w0, w4
	ccmp	w0, wzr, 4, gt
	ble	.L2121
	add	x4, x19, 3072
	add	w2, w2, w3, lsr 1
	add	w1, w1, w0, lsr 1
	stp	w3, w0, [x4, 204]
	stp	w2, w1, [x4, 212]
	b	.L2123
	.p2align 3
.L2196:
	add	x1, x19, 3292
	mov	x0, x20
	bl	vui_parameters
	cbnz	w0, .L2179
	ldrb	w0, [x19, 3304]
	cbz	w0, .L2179
	ldr	w2, [x19, 3372]
	cmp	w2, wzr
	ccmp	w22, w2, 0, ne
	bcc	.L2198
	ldr	w22, [x19, 3244]
	ldrb	w0, [x19, 3307]
	cmp	w22, w2
	csel	w22, w22, w2, cs
	b	.L2126
	.p2align 3
.L2197:
	ldr	w1, [x0, 724]
	cbnz	w1, .L2130
	ldr	w1, [x0, 708]
	cmp	w22, w1
	bls	.L2131
	ldr	x0, .LC516
	ldr	x4, [x0]
	cbz	x4, .L2180
	ldr	w0, [x21, 1644]
	mov	w3, 8
	stp	w22, w1, [x29, 112]
	add	x2, x29, 112
	mov	w1, 106
	blr	x4
	mov	w0, -1
	b	.L2172
.L2198:
	ldr	x1, .LC589
	mov	w3, w22
	mov	w0, 1
	bl	dprint_vfmw
	.p2align 2
.L2179:
	ldrb	w0, [x19, 3307]
	b	.L2126
	.p2align 3
.L2192:
	ldr	x24, .LC528
	add	x21, x19, 2068
	ldr	x23, .LC505
	add	x22, x19, 436
	mov	x27, 0
	add	x26, x29, 104
	mov	x28, x24
.L2087:
	mov	x1, x25
	mov	x0, x20
	bl	u_1
	cmp	w0, 1
	add	x2, x19, x27
	str	w0, [x26, x27, lsl 2]
	add	x1, x23, 176
	strb	w0, [x2, 10]
	beq	.L2199
	ldr	x3, [x24, 104]
	cbz	w27, .L2200
.L2086:
	mov	x0, x21
	mov	x2, 64
.L2176:
	blr	x3
.L2084:
	add	x27, x27, 1
	add	x21, x21, 64
	cmp	x27, 2
	add	x22, x22, 256
	bne	.L2087
	b	.L2076
	.p2align 3
.L2186:
	ldr	x1, .LC542
	mov	x0, x20
	bl	u_1
	strb	w0, [x19, 16]
	ldr	w0, [x21, 1584]
	cbnz	w0, .L2180
	ldr	x1, .LC544
	mov	x0, x20
	bl	se_v
	str	w0, [x19, 2208]
	ldr	w0, [x21, 1584]
	cbnz	w0, .L2180
	ldr	x1, .LC546
	mov	x0, x20
	bl	se_v
	str	w0, [x19, 2212]
	ldr	w0, [x21, 1584]
	cbnz	w0, .L2180
	ldr	x1, .LC548
	mov	x0, x20
	bl	ue_v
	cmp	w0, 255
	str	w0, [x19, 2216]
	bhi	.L2096
	ldr	w1, [x21, 1584]
	cbnz	w1, .L2096
	cbz	w0, .L2095
	ldr	x23, .LC552
	mov	w22, 0
	b	.L2099
	.p2align 3
.L2201:
	ldr	w0, [x19, 2216]
	cmp	w0, w22
	bls	.L2095
.L2099:
	mov	x1, x23
	mov	x0, x20
	bl	se_v
	add	x1, x19, x22, uxtw 2
	add	w22, w22, 1
	str	w0, [x1, 2220]
	ldr	w0, [x21, 1584]
	cbz	w0, .L2201
	mov	w0, -1
	b	.L2202
	.p2align 3
.L2193:
	mov	x0, x20
	mov	x4, x21
	mov	x2, x22
	mov	x1, x24
	mov	w3, 16
	bl	Scaling_List
	ldr	w0, [x21]
	cmp	w0, 1
	bne	.L2078
	ldr	x0, .LC505
	cmp	w28, 2
	mov	x2, 16
	add	x1, x0, 80
	add	x0, x0, 96
	csel	x1, x0, x1, hi
	ldr	x0, .LC528
	ldr	x3, [x0, 104]
	mov	x0, x22
	blr	x3
	b	.L2078
	.p2align 3
.L2100:
	ldr	x1, .LC558
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2172
	.p2align 3
.L2091:
	ldr	x1, .LC536
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2172
	.p2align 3
.L2073:
	ldr	x1, .LC524
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2172
.L2199:
	mov	x0, x20
	add	x4, x26, x27, lsl 2
	mov	x2, x21
	mov	x1, x22
	mov	w3, 64
	bl	Scaling_List
	ldr	w0, [x26, x27, lsl 2]
	cmp	w0, 1
	bne	.L2084
	ldr	x1, .LC505
	mov	x2, 64
	mov	x0, x21
	ldr	x3, [x28, 104]
	add	x1, x1, 176
	cbnz	w27, .L2176
	ldr	x1, .LC505
	add	x1, x1, 112
	b	.L2176
	.p2align 3
.L2131:
	ldr	w2, [x0, 684]
	ldr	w1, [x0, 688]
	cmp	w25, w2
	ccmp	w23, w1, 2, ls
	bls	.L2130
	ldr	x0, .LC516
	ldr	x4, [x0]
	cbz	x4, .L2180
	ldr	w0, [x21, 1644]
	mov	w3, 8
	strh	w2, [x29, 116]
	add	x2, x29, 112
	strh	w1, [x29, 118]
	mov	w1, 107
	strh	w25, [x29, 112]
	strh	w23, [x29, 114]
	blr	x4
	mov	w0, -1
	b	.L2202
.L2183:
	ldr	x2, .LC506
	mov	w3, 9742
	ldr	x1, .LC507
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2172
.L2188:
	ldr	x1, .LC566
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2172
.L2096:
	ldr	x1, .LC550
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2172
.L2200:
	ldr	x1, .LC505
	add	x1, x1, 112
	b	.L2086
	.size	ProcessSPS, .-ProcessSPS
	.align	3
.LC505:
	.xword	.LANCHOR1
	.align	3
.LC506:
	.xword	.LC53
	.align	3
.LC507:
	.xword	.LC55
	.align	3
.LC509:
	.xword	.LC508
	.align	3
.LC511:
	.xword	.LC510
	.align	3
.LC513:
	.xword	.LC512
	.align	3
.LC515:
	.xword	.LC514
	.align	3
.LC516:
	.xword	g_event_report
	.align	3
.LC518:
	.xword	.LC517
	.align	3
.LC520:
	.xword	.LC519
	.align	3
.LC522:
	.xword	.LC521
	.align	3
.LC524:
	.xword	.LC523
	.align	3
.LC526:
	.xword	.LC525
	.align	3
.LC527:
	.xword	.LC385
	.align	3
.LC528:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC530:
	.xword	.LC529
	.align	3
.LC532:
	.xword	.LC531
	.align	3
.LC534:
	.xword	.LC533
	.align	3
.LC536:
	.xword	.LC535
	.align	3
.LC538:
	.xword	.LC537
	.align	3
.LC540:
	.xword	.LC539
	.align	3
.LC542:
	.xword	.LC541
	.align	3
.LC544:
	.xword	.LC543
	.align	3
.LC546:
	.xword	.LC545
	.align	3
.LC548:
	.xword	.LC547
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
	.align	3
.LC564:
	.xword	.LC563
	.align	3
.LC566:
	.xword	.LC565
	.align	3
.LC567:
	.xword	.L2108
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
.LC575:
	.xword	.LC574
	.align	3
.LC577:
	.xword	.LC576
	.align	3
.LC579:
	.xword	.LC578
	.align	3
.LC581:
	.xword	.LC580
	.align	3
.LC583:
	.xword	.LC582
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Sps_SvcExt
	.type	Sps_SvcExt, %function
Sps_SvcExt:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w20, 4000
	bl	_mcount
	add	x1, x19, 20480
	mov	w3, 2208
	ldr	x2, [x19, 14968]
	add	x0, x19, 12288
	ldr	x5, [x19, 14960]
	add	x0, x0, 2600
	ldr	w4, [x1, 1592]
	mov	w1, 32
	umull	x3, w4, w3
	add	x3, x2, x3
	ldr	w2, [x3, 28]
	umull	x2, w2, w20
	add	x20, x5, x2
	bl	BsGet
	mov	w21, w0
	ldr	x1, .LC595
	mov	x0, x19
	bl	u_1
	mov	w2, w0
	ldr	x1, .LC597
	mov	w0, 17
	bl	dprint_vfmw
	ldr	x2, .LC599
	mov	w1, 2
	mov	x0, x19
	bl	u_v
	cmp	w0, 1
	beq	.L2214
	ldr	w0, [x20, 40]
	sub	w1, w0, #1
	cmp	w1, 1
	bls	.L2215
.L2206:
	cmp	w0, 1
	beq	.L2216
.L2207:
	ldr	x1, .LC611
	mov	x0, x19
	bl	u_1
	cbnz	w0, .L2217
.L2208:
	ldr	x1, .LC617
	mov	x0, x19
	mov	w19, 0
	bl	u_1
	cmp	w0, 1
	beq	.L2205
	ldr	x1, .LC619
	mov	w2, w0
	ldr	w4, [x20, 40]
	mov	w3, w21
	mov	w0, 1
	bl	dprint_vfmw
.L2205:
	mov	w0, w19
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2217:
	ldr	x1, .LC613
	mov	x0, x19
	bl	u_1
	mov	w2, w0
	ldr	x1, .LC615
	mov	w0, 17
	bl	dprint_vfmw
	b	.L2208
	.p2align 3
.L2216:
	ldr	x2, .LC607
	mov	w1, 2
	mov	x0, x19
	bl	u_v
	mov	w2, w0
	ldr	x1, .LC609
	mov	w0, 17
	bl	dprint_vfmw
	b	.L2207
	.p2align 3
.L2215:
	ldr	x1, .LC603
	mov	x0, x19
	bl	u_1
	mov	w2, w0
	ldr	x1, .LC605
	mov	w0, 17
	bl	dprint_vfmw
	ldr	w0, [x20, 40]
	b	.L2206
.L2214:
	ldr	x1, .LC601
	mov	w19, -1
	bl	dprint_vfmw
	b	.L2205
	.size	Sps_SvcExt, .-Sps_SvcExt
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_DecSPS
	.type	H264_DecSPS, %function
H264_DecSPS:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	add	x22, x19, 65536
	bl	_mcount
	ldr	x2, .LC621
	mov	w1, 8
	mov	x0, x19
	bl	u_v
	mov	w21, w0
	ldr	x1, .LC623
	mov	x0, x19
	bl	u_1
	mov	w26, w0
	ldr	x1, .LC625
	mov	x0, x19
	bl	u_1
	mov	w25, w0
	ldr	x1, .LC627
	mov	x0, x19
	bl	u_1
	mov	w24, w0
	ldr	x1, .LC629
	mov	x0, x19
	bl	u_1
	mov	w23, w0
	ldr	x2, .LC631
	mov	w1, 4
	mov	x0, x19
	bl	u_v
	ldr	x2, .LC633
	mov	w1, 8
	mov	x0, x19
	bl	u_v
	mov	w20, w0
	ldr	x1, .LC635
	mov	x0, x19
	bl	ue_v
	mov	w27, w0
	ldr	w0, [x22, 1584]
	cbnz	w0, .L2247
	ldr	w0, [x19, 14944]
	sub	w0, w0, #1
	cmp	w27, w0
	bhi	.L2248
	sub	w0, w21, #66
	mov	w22, w21
	cmp	w0, 78
	bls	.L2249
.L2223:
	ldr	x1, .LC646
	mov	w2, w21
	mov	w0, 1
	mov	w22, 100
	bl	dprint_vfmw
.L2226:
	cmp	w20, 9
	mov	w2, w20
	bls	.L2246
	cmp	w20, 41
	bhi	.L2246
	mov	w20, 4000
	ldr	x0, [x19, 14960]
	umull	x20, w27, w20
	add	x0, x0, x20
	ldrb	w1, [x0, 23]
	cbz	w1, .L2231
.L2252:
	ldr	x21, .LC649
	mov	x0, x19
	add	x21, x21, 2208
	strb	w26, [x21]
	mov	x1, x21
	strb	w25, [x21, 1]
	strb	w24, [x21, 2]
	strb	w23, [x21, 3]
	stp	w22, w2, [x21, 28]
	str	w27, [x21, 36]
	bl	ProcessSPS
	cbnz	w0, .L2250
	ldr	x1, [x19, 14960]
	mov	x0, x21
	add	x1, x1, x20
	bl	SPSEqual
	cbnz	w0, .L2251
.L2233:
	mov	w0, 86
	cmp	w22, 83
	ccmp	w22, w0, 4, ne
	beq	.L2235
.L2236:
	mov	w0, 0
.L2220:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L2249:
	ldr	x1, .LC638
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx2225
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx2225:
	.section	.rodata
	.align	0
	.align	2
.L2225:
	.byte	(.L2224 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2226 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2226 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2226 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2227 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2226 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2228 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2228 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2223 - .Lrtx2225) / 4
	.byte	(.L2228 - .Lrtx2225) / 4
	.text
	.p2align 3
.L2235:
	mov	x0, x19
	bl	Sps_SvcExt
	cbz	w0, .L2236
	ldr	x1, .LC654
	mov	w0, 1
	bl	dprint_vfmw
.L2247:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	mov	w0, -1
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L2246:
	ldr	x1, .LC648
	mov	w3, 41
	mov	w0, 1
	mov	w20, 4000
	bl	dprint_vfmw
	umull	x20, w27, w20
	ldr	x0, [x19, 14960]
	mov	w2, 41
	add	x0, x0, x20
	ldrb	w1, [x0, 23]
	cbnz	w1, .L2252
.L2231:
	str	w22, [x0, 28]
	ldr	x0, [x19, 14960]
	strb	w26, [x0, x20]
	mov	x0, x19
	ldr	x1, [x19, 14960]
	add	x1, x1, x20
	strb	w25, [x1, 1]
	ldr	x1, [x19, 14960]
	add	x1, x1, x20
	strb	w24, [x1, 2]
	ldr	x1, [x19, 14960]
	add	x1, x1, x20
	strb	w23, [x1, 3]
	ldr	x1, [x19, 14960]
	add	x1, x1, x20
	str	w2, [x1, 32]
	ldr	x1, [x19, 14960]
	add	x1, x1, x20
	str	w27, [x1, 36]
	ldr	x1, [x19, 14960]
	add	x1, x1, x20
	bl	ProcessSPS
	cbnz	w0, .L2253
	ldr	x0, [x19, 14960]
	mov	w1, 1
	add	x0, x0, x20
	strb	w1, [x0, 24]
	ldr	x0, [x19, 14960]
	add	x20, x0, x20
	strb	w1, [x20, 23]
	b	.L2233
	.p2align 3
.L2248:
	ldr	x1, .LC636
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x19, 14944]
	sub	w0, w1, #1
	cmp	w27, w0
	bls	.L2247
	ldr	x0, .LC637
	ldr	x4, [x0]
	cbz	x4, .L2247
	ldr	w0, [x22, 1644]
	add	x2, x29, 104
	stp	w27, w1, [x29, 104]
	mov	w3, 8
	mov	w1, 109
	blr	x4
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	mov	w0, -1
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L2227:
	ldr	x1, .LC642
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2226
	.p2align 3
.L2228:
	ldr	x1, .LC644
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2226
	.p2align 3
.L2224:
	ldr	x1, .LC640
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2226
	.p2align 3
.L2251:
	ldr	x3, .LC652
	mov	w1, 1
	ldr	x0, [x19, 14960]
	mov	x2, 4000
	strb	w1, [x21, 24]
	ldr	x3, [x3, 112]
	add	x0, x0, x20
	strb	w1, [x21, 23]
	mov	x1, x21
	blr	x3
	b	.L2233
	.p2align 3
.L2250:
	ldr	x1, .LC651
	mov	w3, w27
	mov	w2, 10356
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2220
.L2253:
	ldr	x1, .LC651
	mov	w2, 10381
	mov	w3, w27
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 14960]
	mov	w2, 1
	mov	w0, -1
	add	x1, x1, x20
	strb	w2, [x1, 24]
	ldr	x1, [x19, 14960]
	add	x20, x1, x20
	strb	wzr, [x20, 23]
	b	.L2220
	.size	H264_DecSPS, .-H264_DecSPS
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
.LC636:
	.xword	.LC401
	.align	3
.LC637:
	.xword	g_event_report
	.align	3
.LC638:
	.xword	.L2225
	.align	3
.LC640:
	.xword	.LC639
	.align	3
.LC642:
	.xword	.LC641
	.align	3
.LC644:
	.xword	.LC643
	.align	3
.LC646:
	.xword	.LC645
	.align	3
.LC648:
	.xword	.LC647
	.align	3
.LC649:
	.xword	.LANCHOR3
	.align	3
.LC651:
	.xword	.LC650
	.align	3
.LC652:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC654:
	.xword	.LC653
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PassBytes
	.type	PassBytes, %function
PassBytes:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldr	x0, [x20, 632]
	cmp	w19, wzr
	ccmp	x0, xzr, 4, ne
	beq	.L2263
	ldrb	w2, [x0]
	sbfiz	x1, x2, 5, 32
	add	x1, x0, x1
	ldr	x1, [x1, 8]
	cbz	x1, .L2263
	ldr	w1, [x0, 76]
	cmp	w2, 1
	ccmp	w1, 2, 2, ls
	bhi	.L2263
	cmp	w1, w2
	bls	.L2263
	uxtw	x5, w2
	add	x3, x0, x5, lsl 5
	ldr	w1, [x3, 28]
	ldr	w3, [x3, 16]
	add	w1, w1, w19, lsl 3
	lsl	w3, w3, 3
	cmp	w1, w3
	bhi	.L2258
	b	.L2256
	.p2align 3
.L2259:
	ldr	w4, [x6, 28]
	ldr	w6, [x6, 16]
	sub	w4, w4, w3
	add	w1, w1, w4
	lsl	w3, w6, 3
	cmp	w1, w3
	bls	.L2256
.L2258:
	add	x0, x0, x5, lsl 5
	add	w5, w2, 1
	mov	x2, x5
	str	w3, [x0, 28]
	ldr	x0, [x20, 632]
	ldrb	w4, [x0]
	add	w4, w4, 1
	strb	w4, [x0]
	ldr	x0, [x20, 632]
	add	x6, x0, x5, lsl 5
	ldr	w4, [x0, 76]
	cmp	w4, w5
	bhi	.L2259
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2256:
	add	x5, x0, x5, lsl 5
	mov	w0, 1
	str	w1, [x5, 28]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2263:
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	PassBytes, .-PassBytes
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetBytes
	.type	GetBytes, %function
GetBytes:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x19, x1
	mov	x0, x30
	mov	w20, w2
	bl	_mcount
	cbz	x19, .L2279
	ldr	x1, [x21, 632]
	cmp	x1, xzr
	ccmp	w20, wzr, 4, ne
	ble	.L2279
	ldrb	w2, [x1]
	sbfiz	x0, x2, 5, 32
	add	x0, x1, x0
	ldr	x0, [x0, 8]
	cbz	x0, .L2279
	ldr	w0, [x1, 76]
	cmp	w2, 1
	ccmp	w0, 2, 2, ls
	bhi	.L2279
	cmp	w0, w2
	bls	.L2279
	mov	w6, 0
.L2274:
	ubfiz	x7, x2, 5, 32
	add	x3, x1, x7
	ldr	w0, [x3, 28]
	ldr	x4, [x3, 8]
	ldr	w8, [x3, 16]
	add	w0, w0, 7
	ubfx	x0, x0, 3, 29
	add	x8, x4, x8
	add	x5, x4, x0
	cmp	x5, x8
	bcs	.L2269
	ldrb	w0, [x4, x0]
	add	w6, w6, 1
	strb	w0, [x19]
	cmp	w6, w20
	add	x19, x19, 1
	add	x5, x5, 1
	ldr	x0, [x21, 632]
	add	x0, x0, x7
	ldr	w3, [x0, 28]
	add	w3, w3, 8
	str	w3, [x0, 28]
	bcc	.L2272
	b	.L2271
	.p2align 3
.L2273:
	ldrb	w1, [x5], 1
	add	w6, w6, 1
	strb	w1, [x19], 1
	cmp	w6, w20
	ldr	x3, [x21, 632]
	add	x3, x3, x7
	ldr	w4, [x3, 28]
	add	w4, w4, 8
	str	w4, [x3, 28]
	bcs	.L2271
.L2272:
	cmp	x8, x5
	bne	.L2273
	ldr	x1, [x21, 632]
.L2269:
	ldrb	w0, [x1]
	add	w2, w2, 1
	add	w0, w0, 1
	strb	w0, [x1]
	ldr	x1, [x21, 632]
	ldr	w0, [x1, 76]
	cmp	w0, w2
	bhi	.L2274
	mov	w0, w6
	b	.L2268
	.p2align 3
.L2271:
	mov	w0, w20
.L2268:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2279:
	mov	w0, -1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	GetBytes, .-GetBytes
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_DecFramePackingSEI
	.type	H264_DecFramePackingSEI, %function
H264_DecFramePackingSEI:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 24576
	bl	_mcount
	add	x20, x21, 3184
	ldr	x1, .LC657
	mov	x0, x19
	bl	ue_v
	str	w0, [x20, 24]
	ldr	x2, .LC659
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	sxtb	w0, w0
	strb	w0, [x20, 1]
	cbz	w0, .L2287
.L2282:
	ldr	x2, .LC691
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x21, 3186]
	mov	w1, 1
	strb	w1, [x21, 3184]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2287:
	ldr	x2, .LC661
	mov	w1, 7
	mov	x0, x19
	bl	u_v
	str	w0, [x20, 16]
	ldr	x2, .LC663
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x20, 3]
	ldr	x2, .LC665
	mov	w1, 6
	mov	x0, x19
	bl	u_v
	str	w0, [x20, 20]
	ldr	x2, .LC667
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x20, 4]
	ldr	x2, .LC669
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x20, 5]
	ldr	x2, .LC671
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x20, 6]
	ldr	x2, .LC673
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x20, 7]
	ldr	x2, .LC675
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x20, 8]
	ldr	x2, .LC677
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x20, 9]
	ldrsb	w1, [x20, 3]
	cbnz	w1, .L2283
	ldr	w0, [x20, 16]
	cmp	w0, 5
	beq	.L2283
	ldr	x2, .LC679
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x20, 10]
	ldr	x2, .LC681
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x20, 11]
	ldr	x2, .LC683
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x20, 12]
	ldr	x2, .LC685
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x20, 13]
.L2283:
	ldr	x2, .LC687
	mov	w1, 8
	mov	x0, x19
	bl	u_v
	str	w0, [x21, 3212]
	ldr	x1, .LC689
	mov	x0, x19
	bl	ue_v
	str	w0, [x21, 3216]
	b	.L2282
	.size	H264_DecFramePackingSEI, .-H264_DecFramePackingSEI
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
	.align	3
.LC669:
	.xword	.LC668
	.align	3
.LC671:
	.xword	.LC670
	.align	3
.LC673:
	.xword	.LC672
	.align	3
.LC675:
	.xword	.LC674
	.align	3
.LC677:
	.xword	.LC676
	.align	3
.LC679:
	.xword	.LC678
	.align	3
.LC681:
	.xword	.LC680
	.align	3
.LC683:
	.xword	.LC682
	.align	3
.LC685:
	.xword	.LC684
	.align	3
.LC687:
	.xword	.LC686
	.align	3
.LC689:
	.xword	.LC688
	.align	3
.LC691:
	.xword	.LC690
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_Sei_Get_Dpb_Output_Time
	.type	H264_Sei_Get_Dpb_Output_Time, %function
H264_Sei_Get_Dpb_Output_Time:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 20480
	mov	w1, 2208
	ldr	x9, [x19, 14968]
	add	x3, x19, 24576
	ldr	x8, [x19, 14960]
	ldr	w2, [x0, 1592]
	mov	w0, 4000
	ldr	w5, [x3, 3240]
	ldr	w6, [x3, 3236]
	umull	x1, w2, w1
	add	w2, w5, 1
	ldr	w5, [x3, 3224]
	add	x1, x9, x1
	add	w6, w6, 1
	cmp	w6, 1
	ccmp	w5, wzr, 0, ne
	ldr	w1, [x1, 28]
	str	w2, [x3, 3240]
	ldr	w2, [x3, 3228]
	umull	x0, w1, w0
	str	w6, [x3, 3236]
	add	x0, x8, x0
	str	w5, [x3, 3244]
	add	x0, x0, 3292
	str	w2, [x3, 3252]
	ldr	w1, [x0, 52]
	str	w1, [x3, 3288]
	ldr	w1, [x0, 56]
	str	w1, [x3, 3292]
	bne	.L2289
	ldr	w5, [x3, 3248]
	add	w5, w5, 2
	str	w5, [x3, 3244]
.L2289:
	cmp	w6, 1
	add	x4, x3, 3232
	beq	.L2296
	ldrb	w1, [x4, 80]
	cmp	w1, 1
	ldr	x1, [x4, 48]
	add	x1, x1, x5, uxtw
	str	x1, [x4, 40]
	beq	.L2297
.L2291:
	strb	wzr, [x3, 3312]
	add	x1, x1, x2, uxtw
	lsr	x1, x1, 1
	ldr	w2, [x0, 76]
	ldr	w4, [x0, 52]
	sub	x2, x1, x2
	mul	x2, x2, x4
	str	x2, [x3, 3256]
	ldr	w0, [x0, 76]
	str	w5, [x3, 3248]
	sub	x1, x1, x0
	str	x1, [x3, 3264]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2296:
	mov	x1, 0
	str	xzr, [x3, 3272]
	str	xzr, [x3, 3280]
	b	.L2291
	.p2align 3
.L2297:
	str	x1, [x4, 48]
	b	.L2291
	.size	H264_Sei_Get_Dpb_Output_Time, .-H264_Sei_Get_Dpb_Output_Time
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_Get_Last_IDR_Frame_Info
	.type	H264_Get_Last_IDR_Frame_Info, %function
H264_Get_Last_IDR_Frame_Info:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w20, 5
	beq	.L2303
.L2298:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2303:
	ldr	x0, [x19]
	ldr	x0, [x0, 56]
	cmn	x0, #1
	beq	.L2298
	ldr	x1, [x19, 27840]
	str	x0, [x19, 27872]
	str	x1, [x19, 27880]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	H264_Get_Last_IDR_Frame_Info, .-H264_Get_Last_IDR_Frame_Info
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_Sei_Get_Frame_Pts
	.type	H264_Sei_Get_Frame_Pts, %function
H264_Sei_Get_Frame_Pts:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 24576
	ldr	x3, [x19, 27840]
	ldr	x6, [x19, 27872]
	ldr	x7, [x19, 27880]
	ldr	w4, [x1, 3288]
	ldr	w5, [x1, 3292]
	cbz	w4, .L2307
	mov	w1, w4
	mov	w2, w5
	b	.L2306
	.p2align 3
.L2308:
	mov	w1, w0
.L2306:
	udiv	w0, w2, w1
	msub	w0, w0, w1, w2
	mov	w2, w1
	cbnz	w0, .L2308
.L2305:
	udiv	w4, w4, w1
	sub	x0, x3, x7
	lsl	w2, w0, 6
	add	x19, x19, 61440
	sub	w2, w2, w0
	lsl	w2, w2, 1
	sub	w0, w2, w0
	lsl	w0, w0, 3
	udiv	w1, w5, w1
	mul	w0, w0, w4
	udiv	w1, w0, w1
	add	x1, x1, x6
	str	x1, [x19, 2304]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L2307:
	mov	w1, w5
	b	.L2305
	.size	H264_Sei_Get_Frame_Pts, .-H264_Sei_Get_Frame_Pts
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_DecPicTimingSEI
	.type	H264_DecPicTimingSEI, %function
H264_DecPicTimingSEI:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, 4000
	bl	_mcount
	ldr	w0, [x20, 15012]
	ldr	x3, [x20, 14960]
	umull	x19, w0, w19
	add	x19, x3, x19
	ldrb	w0, [x19, 23]
	cbnz	w0, .L2310
	ldr	w1, [x20, 14944]
	cmp	w1, wzr
	ble	.L2311
	ldrb	w0, [x3, 23]
	cbnz	w0, .L2328
	sub	w1, w1, #1
	add	x0, x3, 4000
	add	x2, x1, 1
	lsl	x1, x2, 6
	sub	x1, x1, x2
	lsl	x1, x1, 1
	sub	x1, x1, x2
	add	x2, x3, x1, lsl 5
	b	.L2314
	.p2align 3
.L2315:
	ldrb	w1, [x1]
	cbnz	w1, .L2312
.L2314:
	cmp	x0, x2
	mov	x19, x0
	add	x0, x0, 4000
	sub	x1, x0, #3977
	bne	.L2315
.L2311:
	ldr	x1, .LC693
	mov	w0, 1
	mov	w19, -1
	bl	dprint_vfmw
.L2316:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L2328:
	mov	x19, x3
	.p2align 2
.L2312:
	cbz	x19, .L2311
.L2310:
	ldrb	w0, [x19, 22]
	cbz	w0, .L2318
	ldrb	w0, [x19, 3299]
	cbz	w0, .L2329
	ldr	w1, [x19, 3676]
	ldr	w22, [x19, 3680]
	add	w1, w1, 1
	add	w22, w22, 1
.L2322:
	ldr	x2, .LC695
	mov	x0, x20
	add	x21, x20, 24576
	bl	u_v
	ldr	x2, .LC697
	mov	w1, w22
	str	w0, [x21, 3224]
	mov	x0, x20
	bl	u_v
	str	w0, [x21, 3228]
	add	x1, x20, 65536
	ldr	x0, .LC698
	ldrsw	x1, [x1, 1644]
	ldr	x0, [x0, x1, lsl 3]
	ldrsb	w1, [x0, 44]
	cmp	w1, 1
	beq	.L2330
.L2318:
	ldrb	w0, [x19, 3303]
	mov	w19, 0
	cbz	w0, .L2316
	ldr	x2, .LC700
	mov	w1, 4
	mov	x0, x20
	bl	u_v
	add	x1, x20, 24576
	strb	w0, [x1, 3220]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2329:
	ldrb	w0, [x19, 3302]
	cbz	w0, .L2318
	ldr	w1, [x19, 3988]
	ldr	w22, [x19, 3992]
	add	w1, w1, 1
	add	w22, w22, 1
	b	.L2322
	.p2align 3
.L2330:
	ldr	w1, [x0, 156]
	cbnz	w1, .L2318
	ldr	w0, [x0, 160]
	cmp	w0, 1
	bne	.L2318
	mov	x0, x20
	bl	H264_Sei_Get_Dpb_Output_Time
	b	.L2318
	.size	H264_DecPicTimingSEI, .-H264_DecPicTimingSEI
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
.LC698:
	.xword	s_pstVfmwChan
	.align	3
.LC700:
	.xword	.LC699
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_DecSEI
	.type	H264_DecSEI, %function
H264_DecSEI:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x27, x0
	mov	x0, x30
	add	x21, x27, 65536
	bl	_mcount
	strb	wzr, [x29, 127]
	ldr	x0, .LC701
	ldrsw	x1, [x21, 1644]
	ldr	x0, [x0, x1, lsl 3]
	ldrsb	w1, [x0, 44]
	cmp	w1, 1
	beq	.L2565
.L2332:
	ldr	x0, [x27, 632]
	mov	w1, 32
	str	w1, [x0, 28]
.L2333:
	add	x20, x27, 12288
	mov	w23, 0
	add	x19, x20, 2600
	b	.L2336
	.p2align 3
.L2567:
	mov	w1, 8
	mov	x0, x19
	bl	BsSkip
	cmp	w22, wzr
	ble	.L2335
	ldrb	w0, [x29, 127]
	cmp	w0, 255
	bne	.L2566
.L2336:
	mov	w2, 1
	add	x1, x29, 127
	mov	x0, x27
	bl	GetBytes
	mov	w22, w0
	ldr	w2, [x27, 14912]
	ldr	w0, [x27, 14920]
	ldrb	w1, [x29, 127]
	add	w0, w0, 8
	cmp	w0, w2, lsl 3
	add	w23, w23, w1
	bls	.L2567
.L2335:
	ldr	x1, .LC703
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2338
	.p2align 3
.L2566:
	ldr	x26, .LC709
	mov	w24, 0
	ldr	x22, .LC706
	add	x0, x26, 232
	str	x0, [x29, 104]
	.p2align 2
.L2517:
	mov	w19, 0
	add	x25, x20, 2600
	b	.L2342
	.p2align 3
.L2569:
	mov	w1, 8
	mov	x0, x25
	bl	BsSkip
	cmp	w28, wzr
	ble	.L2340
	ldrb	w0, [x29, 127]
	cmp	w0, 255
	bne	.L2568
.L2342:
	mov	w2, 1
	add	x1, x29, 127
	mov	x0, x27
	bl	GetBytes
	mov	w28, w0
	ldr	w2, [x27, 14912]
	ldr	w0, [x27, 14920]
	ldrb	w1, [x29, 127]
	add	w0, w0, 8
	cmp	w0, w2, lsl 3
	add	w19, w19, w1
	bls	.L2569
.L2340:
	ldr	x1, .LC705
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L2338:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2568:
	cmp	w19, 409600
	bgt	.L2340
	ldr	x0, [x27, 632]
	ldr	w1, [x0, 76]
	ldr	w2, [x0, 28]
	cmp	w1, 2
	beq	.L2570
.L2344:
	cmp	w23, 45
	bls	.L2571
.L2345:
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2572
.L2507:
	cmp	w19, wzr
	ble	.L2560
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2510
	.p2align 3
.L2511:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
.L2510:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2511
	.p2align 2
.L2560:
	ldr	w0, [x21, 328]
.L2372:
	cmp	w0, 3
	bhi	.L2573
.L2512:
	mov	w23, 0
	add	x19, x20, 2600
	b	.L2516
	.p2align 3
.L2514:
	mov	w1, 8
	mov	x0, x19
	bl	BsSkip
	cmp	w25, wzr
	ble	.L2515
	ldrb	w0, [x29, 127]
	cmp	w0, 255
	bne	.L2574
.L2516:
	mov	w2, 1
	add	x1, x29, 127
	mov	x0, x27
	bl	GetBytes
	mov	w25, w0
	ldr	w2, [x27, 14912]
	ldr	w0, [x27, 14920]
	ldrb	w1, [x29, 127]
	add	w0, w0, 8
	cmp	w0, w2, lsl 3
	add	w23, w23, w1
	bls	.L2514
.L2515:
	mov	w0, 0
.L2575:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2574:
	cmp	w0, 128
	bne	.L2517
	mov	w0, 0
	b	.L2575
	.p2align 3
.L2571:
	ldrh	w0, [x22,w23,uxtw #1]
	adr	x1, .Lrtx2347
	add	x0, x1, w0, sxth #2
	br	x0
.Lrtx2347:
	.section	.rodata
	.align	0
	.align	2
.L2347:
	.2byte	(.L2346 - .Lrtx2347) / 4
	.2byte	(.L2348 - .Lrtx2347) / 4
	.2byte	(.L2349 - .Lrtx2347) / 4
	.2byte	(.L2350 - .Lrtx2347) / 4
	.2byte	(.L2351 - .Lrtx2347) / 4
	.2byte	(.L2352 - .Lrtx2347) / 4
	.2byte	(.L2353 - .Lrtx2347) / 4
	.2byte	(.L2354 - .Lrtx2347) / 4
	.2byte	(.L2355 - .Lrtx2347) / 4
	.2byte	(.L2356 - .Lrtx2347) / 4
	.2byte	(.L2357 - .Lrtx2347) / 4
	.2byte	(.L2358 - .Lrtx2347) / 4
	.2byte	(.L2359 - .Lrtx2347) / 4
	.2byte	(.L2360 - .Lrtx2347) / 4
	.2byte	(.L2361 - .Lrtx2347) / 4
	.2byte	(.L2362 - .Lrtx2347) / 4
	.2byte	(.L2363 - .Lrtx2347) / 4
	.2byte	(.L2364 - .Lrtx2347) / 4
	.2byte	(.L2365 - .Lrtx2347) / 4
	.2byte	(.L2366 - .Lrtx2347) / 4
	.2byte	(.L2367 - .Lrtx2347) / 4
	.2byte	(.L2368 - .Lrtx2347) / 4
	.2byte	(.L2345 - .Lrtx2347) / 4
	.2byte	(.L2345 - .Lrtx2347) / 4
	.2byte	(.L2345 - .Lrtx2347) / 4
	.2byte	(.L2345 - .Lrtx2347) / 4
	.2byte	(.L2345 - .Lrtx2347) / 4
	.2byte	(.L2345 - .Lrtx2347) / 4
	.2byte	(.L2345 - .Lrtx2347) / 4
	.2byte	(.L2345 - .Lrtx2347) / 4
	.2byte	(.L2345 - .Lrtx2347) / 4
	.2byte	(.L2345 - .Lrtx2347) / 4
	.2byte	(.L2345 - .Lrtx2347) / 4
	.2byte	(.L2345 - .Lrtx2347) / 4
	.2byte	(.L2345 - .Lrtx2347) / 4
	.2byte	(.L2345 - .Lrtx2347) / 4
	.2byte	(.L2345 - .Lrtx2347) / 4
	.2byte	(.L2345 - .Lrtx2347) / 4
	.2byte	(.L2345 - .Lrtx2347) / 4
	.2byte	(.L2345 - .Lrtx2347) / 4
	.2byte	(.L2345 - .Lrtx2347) / 4
	.2byte	(.L2345 - .Lrtx2347) / 4
	.2byte	(.L2345 - .Lrtx2347) / 4
	.2byte	(.L2345 - .Lrtx2347) / 4
	.2byte	(.L2345 - .Lrtx2347) / 4
	.2byte	(.L2369 - .Lrtx2347) / 4
	.text
.L2369:
	mov	w1, w19
	mov	x0, x27
	ldr	w25, [x27, 14920]
	bl	H264_DecFramePackingSEI
	ldr	w3, [x27, 14920]
	sub	w0, w3, w25
	lsl	w25, w19, 3
	cmp	w0, w25
	bge	.L2500
	sub	w26, w25, w0
	ldr	w0, [x27, 14912]
	cmp	w26, wzr
	add	w23, w26, 7
	csel	w23, w23, w26, lt
	lsl	w0, w0, 3
	asr	w23, w23, 3
	cmp	w23, wzr
	ble	.L2502
	add	w1, w3, 8
	cmp	w1, w0
	bhi	.L2502
	add	x28, x20, 2600
	mov	w25, 0
	b	.L2503
	.p2align 3
.L2504:
	ldr	w0, [x27, 14912]
	ldr	w3, [x27, 14920]
	lsl	w0, w0, 3
	add	w1, w3, 8
	cmp	w1, w0
	bhi	.L2502
.L2503:
	mov	w1, 8
	mov	x0, x28
	add	w25, w25, 1
	bl	BsSkip
	cmp	w25, w23
	bne	.L2504
	ldr	w0, [x27, 14912]
	ldr	w3, [x27, 14920]
	lsl	w0, w0, 3
.L2502:
	asr	w1, w26, 31
	lsr	w2, w1, 29
	add	w1, w26, w2
	and	w1, w1, 7
	sub	w1, w1, w2
	add	w3, w1, w3
	cmp	w3, w0
	bls	.L2576
.L2500:
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbz	w0, #31, .L2560
	ldr	x1, .LC711
	mov	w3, 11624
	ldr	x2, .LC767
	mov	w0, 20
	bl	dprint_vfmw
	ldr	w0, [x21, 328]
	b	.L2372
.L2368:
	ldr	x1, .LC764
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2577
.L2494:
	cmp	w19, wzr
	ble	.L2560
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2497
	.p2align 3
.L2498:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
.L2497:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2498
	b	.L2560
.L2367:
	ldr	x1, .LC762
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2578
.L2489:
	cmp	w19, wzr
	ble	.L2560
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2492
	.p2align 3
.L2493:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
.L2492:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2493
	b	.L2560
.L2366:
	ldr	x1, .LC760
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2579
.L2484:
	cmp	w19, wzr
	ble	.L2560
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2487
	.p2align 3
.L2488:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
.L2487:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2488
	b	.L2560
.L2365:
	ldr	x1, .LC758
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2580
.L2479:
	cmp	w19, wzr
	ble	.L2560
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2482
	.p2align 3
.L2483:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
.L2482:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2483
	b	.L2560
.L2364:
	ldr	x1, .LC756
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2581
.L2474:
	cmp	w19, wzr
	ble	.L2560
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2477
	.p2align 3
.L2478:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
.L2477:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2478
	b	.L2560
.L2363:
	ldr	x1, .LC754
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2582
.L2469:
	cmp	w19, wzr
	ble	.L2560
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2472
	.p2align 3
.L2473:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
.L2472:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2473
	b	.L2560
.L2362:
	ldr	x1, .LC752
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2583
.L2464:
	cmp	w19, wzr
	ble	.L2560
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2467
	.p2align 3
.L2468:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
.L2467:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2468
	b	.L2560
.L2361:
	ldr	x1, .LC750
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2584
.L2459:
	cmp	w19, wzr
	ble	.L2560
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2462
	.p2align 3
.L2463:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
.L2462:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2463
	b	.L2560
.L2360:
	ldr	x1, .LC748
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2585
.L2454:
	cmp	w19, wzr
	ble	.L2560
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2457
	.p2align 3
.L2458:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
.L2457:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2458
	b	.L2560
.L2359:
	ldr	x1, .LC746
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2586
.L2449:
	cmp	w19, wzr
	ble	.L2560
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2452
	.p2align 3
.L2453:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
.L2452:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2453
	b	.L2560
.L2358:
	ldr	x1, .LC744
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2587
.L2444:
	cmp	w19, wzr
	ble	.L2560
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2447
	.p2align 3
.L2448:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
.L2447:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2448
	b	.L2560
.L2357:
	ldr	x1, .LC742
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2588
.L2439:
	cmp	w19, wzr
	ble	.L2560
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2442
	.p2align 3
.L2443:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
.L2442:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2443
	b	.L2560
.L2356:
	ldr	x1, .LC740
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2589
.L2434:
	cmp	w19, wzr
	ble	.L2560
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2437
	.p2align 3
.L2438:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
.L2437:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2438
	b	.L2560
.L2355:
	ldr	x1, .LC738
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2590
.L2429:
	cmp	w19, wzr
	ble	.L2560
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2432
	.p2align 3
.L2433:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
.L2432:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2433
	b	.L2560
.L2354:
	ldr	x1, .LC736
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2591
.L2424:
	cmp	w19, wzr
	ble	.L2560
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2427
	.p2align 3
.L2428:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
.L2427:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2428
	b	.L2560
.L2353:
	ldr	x1, .LC734
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	cmp	w19, wzr
	ble	.L2421
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2421
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2422
	.p2align 3
.L2423:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2421
.L2422:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2423
.L2421:
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbz	w0, #31, .L2560
	ldr	x2, .LC709
	mov	w3, 11196
	ldr	x1, .LC711
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	ldr	w0, [x21, 328]
	b	.L2372
.L2352:
	cbnz	w24, .L2351
	ldr	x1, .LC721
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	ldr	w23, [x21, 328]
	cmp	w23, 3
	bhi	.L2592
.L2396:
	ldr	w0, [x21, 1644]
	bl	GetUsd
	uxtw	x1, w23
	add	x1, x1, 8192
	add	x1, x1, 42
	str	x0, [x27, x1, lsl 3]
	ldr	w0, [x21, 328]
	add	x0, x0, 8192
	add	x0, x0, 42
	ldr	x6, [x27, x0, lsl 3]
	cbz	x6, .L2520
	ldr	x3, [x27, 632]
	cmp	w19, 1024
	mov	w28, 1024
	csel	w28, w19, w28, le
	ldrb	w2, [x3]
	ldr	w5, [x3, 76]
	cmp	w2, w5
	bcs	.L2521
	mov	w25, 0
	.p2align 2
.L2398:
	ubfiz	x1, x2, 5, 32
	add	w2, w2, 1
	add	x1, x3, x1
	cmp	w2, w5
	ldr	w0, [x1, 28]
	ldr	w1, [x1, 16]
	add	w0, w0, 7
	sub	w0, w1, w0, lsr 3
	add	w25, w25, w0
	bne	.L2398
	mov	w0, w25
.L2397:
	cmp	w28, w0
	csel	w25, w25, w28, gt
	cbnz	w24, .L2593
	mov	w23, 0
	mov	w26, 0
.L2400:
	sub	w2, w25, w23
	cmp	w2, wzr
	ble	.L2594
	ldr	w0, [x21, 328]
	add	x0, x0, 8192
	add	x0, x0, 42
	ldr	x1, [x27, x0, lsl 3]
	mov	x0, x27
	bl	GetBytes
	cmp	w0, wzr
	mov	w25, w0
	ble	.L2595
	sub	w0, w28, w26
	cmp	w25, w0
	bge	.L2406
	ldr	w0, [x21, 328]
	add	x0, x0, 8192
	add	x0, x0, 42
	ldr	x0, [x27, x0, lsl 3]
	str	w25, [x0, 1052]
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2407
	add	x19, x20, 2600
	mov	w23, 0
	b	.L2408
	.p2align 3
.L2411:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2407
.L2408:
	mov	w1, 8
	mov	x0, x19
	add	w23, w23, 1
	bl	BsSkip
	cmp	w25, w23
	bne	.L2411
.L2407:
	ldr	w0, [x21, 328]
	cmp	w24, 1
	ldr	x1, [x27]
	add	x0, x0, 8192
	add	x0, x0, 42
	ldr	x1, [x1, 56]
	ldr	x0, [x27, x0, lsl 3]
	str	x1, [x0, 1056]
	mov	w0, 8
	mov	w1, 9
	csel	w1, w0, w1, eq
	ldr	w0, [x21, 328]
	add	x0, x0, 8192
	add	x0, x0, 42
	ldr	x0, [x27, x0, lsl 3]
	str	w1, [x0, 1040]
	ldr	x0, .LC728
	ldr	x5, [x0]
.L2563:
	ldr	w0, [x21, 328]
	ldr	w1, [x21, 1604]
	add	x0, x0, 8192
	add	x0, x0, 42
	ldr	x0, [x27, x0, lsl 3]
	str	w1, [x0, 1044]
	cbz	x5, .L2417
	ldr	w0, [x21, 328]
	mov	w3, 1064
	mov	w1, 6
	add	x0, x0, 8192
	add	x0, x0, 42
	ldr	x2, [x27, x0, lsl 3]
	ldr	w0, [x21, 1644]
	blr	x5
.L2417:
	ldr	w0, [x21, 328]
	add	x0, x0, 8192
	add	x0, x0, 42
	ldr	x1, [x27, x0, lsl 3]
	ldr	w0, [x21, 1644]
	bl	FreeUsdByDec
	ldr	w0, [x21, 328]
	add	w0, w0, 1
	str	w0, [x21, 328]
	cmp	w0, 3
	bls	.L2512
.L2573:
	ldr	x1, .LC766
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2338
.L2350:
	ldr	x1, .LC717
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2596
.L2389:
	cmp	w19, wzr
	ble	.L2560
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2392
	.p2align 3
.L2393:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
.L2392:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2393
	b	.L2560
.L2346:
	add	x0, x27, 24576
	mov	w3, 1
	ldr	w1, [x0, 3232]
	strb	w3, [x0, 3312]
	mov	w3, w19
	add	w1, w1, 1
	str	w1, [x0, 3232]
	ldr	x1, .LC708
	str	wzr, [x0, 3240]
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2597
.L2370:
	cmp	w19, wzr
	ble	.L2560
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2374
	.p2align 3
.L2375:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
.L2374:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2375
	b	.L2560
.L2349:
	ldr	x1, .LC715
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2598
.L2384:
	cmp	w19, wzr
	ble	.L2560
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2387
	.p2align 3
.L2388:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2560
.L2387:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2388
	b	.L2560
.L2348:
	ldr	x1, .LC713
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	ldr	w25, [x27, 14920]
	mov	w1, w19
	mov	x0, x27
	bl	H264_DecPicTimingSEI
	ldr	w3, [x27, 14920]
	sub	w0, w3, w25
	lsl	w25, w19, 3
	cmp	w0, w25
	bge	.L2377
	sub	w25, w25, w0
	ldr	w0, [x27, 14912]
	cmp	w25, wzr
	add	w23, w25, 7
	csel	w23, w23, w25, lt
	lsl	w0, w0, 3
	asr	w23, w23, 3
	cmp	w23, wzr
	ble	.L2379
	add	w1, w3, 8
	cmp	w0, w1
	bcc	.L2379
	add	x28, x20, 2600
	mov	w26, 0
	b	.L2380
	.p2align 3
.L2381:
	ldr	w0, [x27, 14912]
	ldr	w3, [x27, 14920]
	lsl	w0, w0, 3
	add	w1, w3, 8
	cmp	w1, w0
	bhi	.L2379
.L2380:
	mov	w1, 8
	mov	x0, x28
	add	w26, w26, 1
	bl	BsSkip
	cmp	w23, w26
	bne	.L2381
	ldr	w0, [x27, 14912]
	ldr	w3, [x27, 14920]
	lsl	w0, w0, 3
.L2379:
	asr	w1, w25, 31
	lsr	w2, w1, 29
	add	w1, w25, w2
	and	w1, w1, 7
	sub	w1, w1, w2
	add	w3, w1, w3
	cmp	w3, w0
	bls	.L2599
.L2377:
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbz	w0, #31, .L2560
	ldr	x2, .LC709
	mov	w3, 10951
	ldr	x1, .LC711
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	ldr	w0, [x21, 328]
	b	.L2372
.L2351:
	ldr	x1, .LC719
	mov	w3, w19
	mov	w0, 20
	mov	w24, 1
	bl	dprint_vfmw
	ldr	w23, [x21, 328]
	cmp	w23, 3
	bls	.L2396
.L2592:
	ldr	w0, [x21, 1644]
	mov	w23, 0
	ldr	x1, [x21, 336]
	bl	FreeUsdByDec
	ldr	w0, [x21, 1644]
	ldr	x1, [x21, 344]
	bl	FreeUsdByDec
	ldr	w0, [x21, 1644]
	ldr	x1, [x21, 352]
	bl	FreeUsdByDec
	ldr	w0, [x21, 1644]
	ldr	x1, [x21, 360]
	bl	FreeUsdByDec
	str	wzr, [x21, 328]
	stp	xzr, xzr, [x21, 336]
	stp	xzr, xzr, [x21, 352]
	b	.L2396
	.p2align 3
.L2570:
	ldr	w0, [x0, 60]
	add	w2, w2, w0
	lsr	w2, w2, 3
	b	.L2344
.L2406:
	ldr	w0, [x21, 328]
	sub	w23, w19, w26
	cmp	w28, w19
	add	x0, x0, 8192
	add	x0, x0, 42
	ldr	x0, [x27, x0, lsl 3]
	str	w23, [x0, 1052]
	bcc	.L2600
.L2413:
	cmp	w23, wzr
	ble	.L2407
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2407
	add	x19, x20, 2600
	mov	w25, 0
	b	.L2415
	.p2align 3
.L2416:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2407
.L2415:
	mov	w1, 8
	mov	x0, x19
	add	w25, w25, 1
	bl	BsSkip
	cmp	w23, w25
	bne	.L2416
	b	.L2407
.L2565:
	ldr	w1, [x0, 156]
	cbnz	w1, .L2332
	ldr	w1, [x0, 160]
	cmp	w1, 1
	bne	.L2332
	ldr	w0, [x0, 152]
	cmp	w0, 1
	bne	.L2332
	ldr	x0, [x27, 632]
	mov	w1, 48
	str	w1, [x0, 28]
	b	.L2333
.L2576:
	add	x0, x20, 2600
	bl	BsSkip
	b	.L2500
.L2599:
	add	x0, x20, 2600
	bl	BsSkip
	b	.L2377
.L2593:
	strb	w24, [x6, 1026]
	mov	w1, 8
	ldr	x2, .LC723
	mov	x0, x27
	ldr	w3, [x21, 328]
	add	x3, x3, 8192
	add	x3, x3, 42
	ldr	x23, [x27, x3, lsl 3]
	bl	u_v
	strb	w0, [x23, 1027]
	ldr	w0, [x21, 328]
	add	x0, x0, 8192
	add	x0, x0, 42
	ldr	x23, [x27, x0, lsl 3]
	ldrb	w0, [x23, 1027]
	cmp	w0, 255
	beq	.L2401
	strb	wzr, [x23, 1028]
	mov	w23, 3
	mov	w26, w23
.L2402:
	ldr	w0, [x21, 328]
	mov	w1, 16
	ldr	x2, .LC727
	add	x0, x0, 8192
	add	x0, x0, 42
	ldr	x5, [x27, x0, lsl 3]
	mov	x0, x27
	str	x5, [x29, 96]
	bl	u_v
	ldr	x5, [x29, 96]
	mov	w1, w23
	strh	w0, [x5, 1030]
	mov	x0, x27
	bl	PassBytes
	cmp	w25, w23
	bne	.L2400
	ldr	w0, [x21, 328]
	ldr	x1, [x27]
	add	x0, x0, 8192
	add	x0, x0, 42
	ldr	x1, [x1, 56]
	ldr	x0, [x27, x0, lsl 3]
	str	x1, [x0, 1056]
	mov	w1, 8
	ldr	x0, .LC728
	ldr	x5, [x0]
	ldr	w0, [x21, 328]
	add	x0, x0, 8192
	add	x0, x0, 42
	ldr	x0, [x27, x0, lsl 3]
	str	w1, [x0, 1040]
	b	.L2563
.L2600:
	sub	w1, w19, w28
	mov	x0, x27
	bl	PassBytes
	tbz	w0, #31, .L2413
	ldr	x2, .LC709
	mov	w3, 11145
	ldr	x1, .LC711
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2413
.L2521:
	mov	w0, 0
	mov	w25, 0
	b	.L2397
.L2591:
	ldr	x2, .LC709
	mov	w3, 11208
	ldr	x1, .LC711
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2424
.L2597:
	ldr	x2, .LC709
	mov	w3, 10898
	ldr	x1, .LC711
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2370
.L2596:
	ldr	x2, .LC709
	mov	w3, 10989
	ldr	x1, .LC711
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2389
.L2598:
	ldr	x2, .LC709
	mov	w3, 10963
	ldr	x1, .LC711
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2384
.L2572:
	ldr	x1, .LC711
	mov	w3, 11636
	ldr	x2, [x29, 104]
	mov	w0, 20
	bl	dprint_vfmw
	b	.L2507
.L2578:
	ldr	x2, .LC709
	mov	w3, 11546
	ldr	x1, .LC711
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2489
.L2577:
	ldr	x1, .LC711
	mov	w3, 11572
	ldr	x2, .LC767
	mov	w0, 20
	bl	dprint_vfmw
	b	.L2494
.L2582:
	ldr	x2, .LC709
	mov	w3, 11442
	ldr	x1, .LC711
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2469
.L2581:
	ldr	x2, .LC709
	mov	w3, 11468
	ldr	x1, .LC711
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2474
.L2580:
	ldr	x2, .LC709
	mov	w3, 11494
	ldr	x1, .LC711
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2479
.L2579:
	ldr	x2, .LC709
	mov	w3, 11520
	ldr	x1, .LC711
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2484
.L2590:
	ldr	x2, .LC709
	mov	w3, 11234
	ldr	x1, .LC711
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2429
.L2589:
	ldr	x2, .LC709
	mov	w3, 11260
	ldr	x1, .LC711
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2434
.L2588:
	ldr	x2, .LC709
	mov	w3, 11286
	ldr	x1, .LC711
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2439
.L2587:
	ldr	x2, .LC709
	mov	w3, 11312
	ldr	x1, .LC711
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2444
.L2586:
	ldr	x2, .LC709
	mov	w3, 11338
	ldr	x1, .LC711
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2449
.L2585:
	ldr	x2, .LC709
	mov	w3, 11364
	ldr	x1, .LC711
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2454
.L2584:
	ldr	x2, .LC709
	mov	w3, 11390
	ldr	x1, .LC711
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2459
.L2583:
	ldr	x2, .LC709
	mov	w3, 11416
	ldr	x1, .LC711
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2464
.L2520:
	mov	w0, -1
	b	.L2338
.L2401:
	ldr	x2, .LC725
	mov	w1, 8
	mov	x0, x27
	bl	u_v
	strb	w0, [x23, 1028]
	mov	w23, 4
	mov	w26, w23
	b	.L2402
.L2594:
	ldr	x1, .LC730
	mov	w0, 1
	bl	dprint_vfmw
.L2561:
	ldr	w1, [x21, 328]
	ldr	w0, [x21, 1644]
	add	x1, x1, 8192
	add	x1, x1, 42
	ldr	x1, [x27, x1, lsl 3]
	bl	FreeUsdByDec
	ldr	w1, [x21, 328]
	mov	w0, -1
	add	x1, x1, 8192
	add	x1, x1, 42
	str	xzr, [x27, x1, lsl 3]
	b	.L2338
.L2595:
	ldr	x1, .LC732
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2561
	.size	H264_DecSEI, .-H264_DecSEI
	.align	3
.LC701:
	.xword	s_pstVfmwChan
	.align	3
.LC703:
	.xword	.LC702
	.align	3
.LC705:
	.xword	.LC704
	.align	3
.LC706:
	.xword	.L2347
	.align	3
.LC708:
	.xword	.LC707
	.align	3
.LC709:
	.xword	.LANCHOR2
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
	.align	3
.LC762:
	.xword	.LC761
	.align	3
.LC764:
	.xword	.LC763
	.align	3
.LC766:
	.xword	.LC765
	.align	3
.LC767:
	.xword	.LANCHOR2+232
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InitOldSlice
	.type	InitOldSlice, %function
InitOldSlice:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 20480
	mov	w4, 32
	ldr	w8, [x19, 14948]
	mov	w7, 23352
	movk	w7, 0x1, lsl 16
	mov	w6, 2
	strb	w4, [x0, 3226]
	add	x4, x0, 3072
	strb	wzr, [x0, 3224]
	mov	w5, 7
	strb	w6, [x0, 3225]
	mov	w3, 3
	str	w8, [x0, 3232]
	mov	w2, -1
	str	w5, [x0, 3236]
	mov	w1, 262144
	str	w7, [x0, 3240]
	stp	w3, w2, [x4, 176]
	stp	wzr, wzr, [x4, 184]
	str	w1, [x0, 3264]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	InitOldSlice, .-InitOldSlice
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_IsNewPicNal
	.type	H264_IsNewPicNal, %function
H264_IsNewPicNal:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x20, 3]
	and	w0, w0, 31
	sub	w0, w0, #1
	cmp	w0, 7
	bls	.L2611
.L2610:
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2611:
	ldr	x1, .LC768
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx2605
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx2605:
	.section	.rodata
	.align	0
	.align	2
.L2605:
	.byte	(.L2604 - .Lrtx2605) / 4
	.byte	(.L2610 - .Lrtx2605) / 4
	.byte	(.L2610 - .Lrtx2605) / 4
	.byte	(.L2610 - .Lrtx2605) / 4
	.byte	(.L2604 - .Lrtx2605) / 4
	.byte	(.L2610 - .Lrtx2605) / 4
	.byte	(.L2606 - .Lrtx2605) / 4
	.byte	(.L2606 - .Lrtx2605) / 4
	.text
	.p2align 3
.L2606:
	ldr	w0, [x19]
	mov	w1, 1
	str	w1, [x19]
	cmp	w0, wzr
	csetm	w0, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2604:
	ldr	w0, [x19]
	cbz	w0, .L2607
.L2609:
	mov	w0, -1
	str	wzr, [x19]
.L2612:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2607:
	ldr	w20, [x20, 4]
	rev	w20, w20
	mov	w0, w20
	bl	ZerosMS_32
	cmp	w0, 15
	bhi	.L2609
	mov	w1, 31
	str	wzr, [x19]
	sub	w0, w1, w0, lsl 1
	lsr	w20, w20, w0
	cmp	w20, 1
	csetm	w0, ne
	b	.L2612
	.size	H264_IsNewPicNal, .-H264_IsNewPicNal
	.align	3
.LC768:
	.xword	.L2605
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FindZeroBitsInSeg
	.type	FindZeroBitsInSeg, %function
FindZeroBitsInSeg:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x22, x0
	mov	x0, x30
	mov	w23, w1
	bl	_mcount
	cmp	x22, xzr
	ccmp	w23, wzr, 4, ne
	ble	.L2633
	and	w1, w23, 63
	add	w0, w23, 63
	cmp	w1, wzr
	cset	w26, ne
	cmp	w23, wzr
	csel	w0, w0, w23, lt
	add	w26, w26, w0, asr 6
	cmp	w26, wzr
	ble	.L2626
	ldr	x20, .LC772
	mov	w25, w23
	ldr	x27, .LC771
	mov	w19, 0
	mov	w24, 64
	add	x20, x20, 1856
	.p2align 2
.L2625:
	cmp	w25, 64
	uxtw	x1, w25
	csel	w21, w25, w24, ls
	ldr	x3, [x27, 104]
	sub	x1, x1, x21
	mov	x2, x21
	add	x1, x22, x1
	sub	x21, x21, #1
	mov	x0, x20
	blr	x3
	ldrb	w1, [x20, x21]
	add	x0, x20, x21
	cbnz	w1, .L2617
	cmp	x0, x20
	add	w19, w19, 1
	bne	.L2620
	b	.L2618
	.p2align 3
.L2621:
	add	w19, w19, 1
	beq	.L2618
.L2620:
	ldrb	w1, [x0, -1]!
	cmp	x0, x20
	cbz	w1, .L2621
.L2617:
	lsl	w0, w19, 3
.L2616:
	cmp	w19, w23
	mov	w1, 0
	bge	.L2622
	sxtw	x2, w23
	sub	x2, x2, #1
	sub	x19, x2, x19, sxtw
	ldrb	w2, [x22, x19]
	tbnz	x2, 0, .L2622
	lsr	w2, w2, 1
	mov	w1, 1
	.p2align 2
.L2624:
	tbnz	x2, 0, .L2622
	add	w1, w1, 1
	lsr	w2, w2, 1
	cmp	w1, 8
	bne	.L2624
.L2622:
	add	w0, w1, w0
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L2618:
	subs	w26, w26, #1
	sub	w25, w25, #64
	bne	.L2625
	b	.L2617
.L2633:
	ldr	x1, .LC770
	mov	w2, w23
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x27, [sp, 80]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L2626:
	mov	w0, 0
	mov	w19, 0
	b	.L2616
	.size	FindZeroBitsInSeg, .-FindZeroBitsInSeg
	.align	3
.LC770:
	.xword	.LC769
	.align	3
.LC771:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC772:
	.xword	.LANCHOR4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FindTrailZeros
	.type	FindTrailZeros, %function
FindTrailZeros:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L2640
	ldr	x2, [x19, 632]
	ldr	w0, [x2, 76]
	cmp	w0, 1
	bls	.L2639
	ldr	w1, [x2, 48]
	ldr	x0, [x2, 40]
	bl	FindZeroBitsInSeg
	ldr	x2, [x19, 632]
	ldr	w1, [x2, 48]
	cmp	w0, w1, lsl 3
	bcs	.L2643
	cmn	w0, #1
	beq	.L2639
	add	w0, w0, 1
	str	w0, [x2, 80]
	ldr	x0, [x19, 632]
	ldr	w1, [x0, 76]
	cmp	w1, 1
	bls	.L2641
.L2644:
	ldr	w2, [x0, 48]
	mov	w20, 0
	ldr	w1, [x0, 80]
	cmp	w1, w2, lsl 3
	bcc	.L2635
	add	x2, x19, 65536
	ldr	w1, [x0, 68]
	ldr	w0, [x2, 1644]
	bl	SM_ReleaseStreamSeg
	ldr	x0, [x19, 632]
	mov	w1, 1
	str	xzr, [x0, 40]
	ldr	x0, [x19, 632]
	str	w1, [x0, 76]
	ldr	x0, [x19, 632]
	str	wzr, [x0, 80]
.L2635:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2643:
	add	x0, x19, 65536
	ldr	w1, [x2, 68]
	ldr	w0, [x0, 1644]
	bl	SM_ReleaseStreamSeg
	ldr	x0, [x19, 632]
	mov	w1, 1
	str	xzr, [x0, 40]
	ldr	x0, [x19, 632]
	str	w1, [x0, 76]
	ldr	x2, [x19, 632]
.L2639:
	ldr	w1, [x2, 16]
	ldr	x0, [x2, 8]
	bl	FindZeroBitsInSeg
	add	w0, w0, 1
	ldr	x2, [x19, 632]
	str	w0, [x2, 80]
	ldr	x0, [x19, 632]
	ldr	w1, [x0, 76]
	cmp	w1, 1
	bhi	.L2644
.L2641:
	mov	w20, 0
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L2640:
	mov	w20, -1
	b	.L2635
	.size	FindTrailZeros, .-FindTrailZeros
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CombinePacket
	.type	CombinePacket, %function
CombinePacket:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 632]
	ldr	w0, [x0, 16]
	cmp	w0, 4095
	bhi	.L2645
	mov	x0, x19
	bl	CombinePacket.part.13
.L2645:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CombinePacket, .-CombinePacket
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FindNaluArraySlot
	.type	FindNaluArraySlot, %function
FindNaluArraySlot:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x19, 641]
	cbz	w0, .L2652
	add	x0, x19, 745
	mov	x1, 1
	b	.L2650
	.p2align 3
.L2649:
	add	w1, w1, 1
	cmp	w1, 137
	beq	.L2655
.L2650:
	ldrb	w2, [x0]
	add	x0, x0, 104
	cbnz	w2, .L2649
	mov	w0, w1
.L2648:
	lsl	x2, x1, 3
	mov	w3, 1
	sub	x2, x2, x1
	lsl	x2, x2, x3
	sub	x1, x2, x1
	add	x1, x19, x1, lsl 3
	strb	w3, [x1, 641]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2655:
	mov	w0, -1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L2652:
	mov	w0, 0
	mov	x1, 0
	b	.L2648
	.size	FindNaluArraySlot, .-FindNaluArraySlot
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InquireSliceExtProperty
	.type	InquireSliceExtProperty, %function
InquireSliceExtProperty:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 12288
	mov	w1, 24
	add	x0, x0, 2600
	bl	BsGet
	ubfx	x2, x0, 23, 1
	ldr	x1, [x19, 632]
	strb	w2, [x1, 3]
	ldr	x3, [x19, 632]
	ldrb	w1, [x3, 3]
	cbnz	w1, .L2657
	add	x1, x19, 61440
	ldrb	w2, [x1, 3224]
.L2658:
	cmp	w2, 1
	bne	.L2659
	mov	w0, 5
	strb	w0, [x3, 2]
.L2659:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2657:
	add	x1, x19, 61440
	ubfx	x5, x0, 16, 6
	ubfx	x4, x0, 15, 1
	ubfx	x2, x0, 22, 1
	ubfx	x9, x0, 12, 3
	ubfx	x8, x0, 8, 4
	ubfx	x7, x0, 5, 3
	ubfx	x6, x0, 4, 1
	strb	w5, [x1, 3225]
	ubfx	x5, x0, 3, 1
	strb	w4, [x1, 3226]
	ubfx	x4, x0, 2, 1
	strb	w2, [x1, 3224]
	and	w0, w0, 3
	strb	w9, [x1, 3227]
	strb	w8, [x1, 3228]
	strb	w7, [x1, 3229]
	strb	w6, [x1, 3230]
	strb	w5, [x1, 3231]
	strb	w4, [x1, 3232]
	strb	w0, [x1, 3233]
	b	.L2658
	.size	InquireSliceExtProperty, .-InquireSliceExtProperty
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InquireSliceProperty
	.type	InquireSliceProperty, %function
InquireSliceProperty:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x23, x1
	mov	x20, x2
	bl	_mcount
	add	x21, x19, 20480
	add	x2, x19, 65536
	ldr	x1, .LC775
	mov	w0, 22
	ldr	w2, [x2, 1588]
	sub	w2, w2, #1
	bl	dprint_vfmw
	str	wzr, [x20]
	str	wzr, [x23]
	mov	x0, x19
	ldr	x1, [x19, 632]
	ldrb	w2, [x1, 2]
	strb	w2, [x21, 1587]
	ldr	w1, [x1, 84]
	str	w1, [x21, 1612]
	bl	SliceCheck
	mov	w22, w0
	cbnz	w0, .L2664
	mov	x0, x19
	bl	ProcessSliceHeaderFirstPart
	cbnz	w0, .L2668
	ldrb	w3, [x21, 1589]
	mov	w1, 2208
	mov	w0, 4000
	mov	w2, 2
	cmp	w3, 1
	cset	w3, eq
	str	w3, [x23]
	ldr	w3, [x21, 1592]
	ldr	x4, [x19, 14968]
	ldr	x6, [x19, 14960]
	umull	x1, w3, w1
	ldr	w5, [x19, 14936]
	add	x1, x4, x1
	ldr	w4, [x19, 14932]
	ldr	w1, [x1, 28]
	umull	x0, w1, w0
	add	x0, x6, x0
	ldrb	w1, [x0, 18]
	ldr	w6, [x0, 3252]
	sub	w1, w2, w1
	ldr	w3, [x0, 3248]
	madd	w1, w6, w1, w1
	add	w2, w3, 1
	cmp	w1, w5
	ccmp	w2, w4, 0, eq
	bne	.L2669
.L2663:
	add	x19, x19, 24576
	ldr	w1, [x0, 3272]
	ldr	w0, [x19, 3704]
	add	w0, w0, 1
	cmp	w1, w0
	beq	.L2661
	mov	w0, 1
	str	w0, [x20]
.L2661:
	mov	w0, w22
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2669:
	mov	w1, 1
	str	w1, [x20]
	b	.L2663
	.p2align 3
.L2664:
	mov	w22, -1
	b	.L2661
	.p2align 3
.L2668:
	ldr	x1, .LC777
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L2661
	.size	InquireSliceProperty, .-InquireSliceProperty
	.align	3
.LC775:
	.xword	.LC774
	.align	3
.LC777:
	.xword	.LC776
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HaveSliceToDec
	.type	HaveSliceToDec, %function
HaveSliceToDec:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 65536
	bl	_mcount
	ldr	w0, [x19, 1568]
	ldr	x19, [sp, 16]
	cmp	w0, wzr
	csetm	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	HaveSliceToDec, .-HaveSliceToDec
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IsRefListWrong
	.type	IsRefListWrong, %function
IsRefListWrong:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x21, x20, 20480
	bl	_mcount
	ldr	w0, [x21, 1624]
	cbz	w0, .L2672
	mov	w19, 0
	add	x22, x20, 65536
	b	.L2676
	.p2align 3
.L2673:
	ldr	x0, [x0, 32]
	cbz	x0, .L2675
	ldr	w0, [x21, 1624]
	cmp	w0, w19
	bls	.L2700
.L2676:
	add	x1, x20, x19, sxtw 3
	ldr	w0, [x22, 1644]
	add	w19, w19, 1
	ldr	x1, [x1, 28696]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 648]
	bl	FSP_GetLogicFs
	cbnz	x0, .L2673
.L2675:
	mov	w0, -1
.L2702:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2672:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2700:
	cbz	w0, .L2672
	ldr	w0, [x21, 1628]
	mov	w19, 0
	cbnz	w0, .L2689
	b	.L2672
	.p2align 3
.L2701:
	ldr	x0, [x0, 32]
	cbz	x0, .L2675
	ldr	w0, [x21, 1628]
	cmp	w0, w19
	bls	.L2672
.L2689:
	add	x1, x20, x19, sxtw 3
	ldr	w0, [x22, 1644]
	add	w19, w19, 1
	ldr	x1, [x1, 28960]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 648]
	bl	FSP_GetLogicFs
	cbnz	x0, .L2701
	mov	w0, -1
	b	.L2702
	.size	IsRefListWrong, .-IsRefListWrong
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264DEC_Destroy
	.type	H264DEC_Destroy, %function
H264DEC_Destroy:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	add	x20, x22, 12288
	add	x19, x22, 640
	bl	_mcount
	add	x21, x22, 65536
	mov	x0, x22
	add	x20, x20, 2600
	bl	ClearAllSlice
	add	x0, x22, 20480
	mov	w2, 23352
	ldr	w3, [x22, 14948]
	movk	w2, 0x1, lsl 16
	mov	w1, 7
	mov	w5, 2
	mov	w4, 32
	str	w3, [x0, 3232]
	str	w1, [x0, 3236]
	mov	w3, 3
	str	w2, [x0, 3240]
	mov	w1, 262144
	mov	w2, -1
	strb	wzr, [x0, 3224]
	strb	w5, [x0, 3225]
	strb	w4, [x0, 3226]
	str	wzr, [x0, 3256]
	str	wzr, [x0, 3260]
	str	w3, [x0, 3248]
	str	w2, [x0, 3252]
	str	w1, [x0, 3264]
	b	.L2705
	.p2align 3
.L2704:
	add	x19, x19, 104
	cmp	x20, x19
	beq	.L2725
.L2705:
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	bne	.L2704
	ldr	w0, [x21, 1644]
	mov	x1, x19
	add	x19, x19, 104
	bl	ReleaseNAL
	cmp	x20, x19
	bne	.L2705
.L2725:
	ldr	w0, [x21, 1580]
	cmp	w0, 1
	beq	.L2726
.L2706:
	ldr	w0, [x21, 328]
	mov	w20, 0
	cbz	w0, .L2711
	.p2align 2
.L2719:
	add	x19, x22, x20, uxtw 3
	add	w20, w20, 1
	add	x19, x19, 65536
	ldr	x0, [x19, 336]
	mov	x1, x0
	cbz	x0, .L2709
	ldr	w0, [x21, 1644]
	bl	FreeUsdByDec
	str	xzr, [x19, 336]
.L2709:
	ldr	w0, [x21, 328]
	cmp	w0, w20
	bhi	.L2719
.L2711:
	add	x20, x22, 28672
	add	x22, x22, 61440
	add	x20, x20, 1144
	add	x22, x22, 2296
	.p2align 2
.L2708:
	sub	x19, x20, #32
.L2713:
	ldr	x0, [x19]
	mov	x1, x0
	cbz	x0, .L2712
	ldr	w0, [x21, 1644]
	bl	FreeUsdByDec
	str	xzr, [x19]
.L2712:
	add	x19, x19, 8
	cmp	x19, x20
	bne	.L2713
	add	x20, x19, 848
	cmp	x20, x22
	bne	.L2708
	ldr	x1, .LC779
	mov	w0, 2
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L2726:
	str	wzr, [x21, 1580]
	b	.L2706
	.size	H264DEC_Destroy, .-H264DEC_Destroy
	.align	3
.LC779:
	.xword	.LC778
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264DEC_RecycleImage
	.type	H264DEC_RecycleImage, %function
H264DEC_RecycleImage:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w22, w1
	add	x21, x21, 65536
	bl	_mcount
	ldr	x1, .LC781
	mov	w0, 2
	bl	dprint_vfmw
	ldr	w0, [x21, 1644]
	mov	w1, w22
	bl	FSP_GetLogicFs
	cbz	x0, .L2732
	ldrsb	w1, [x0, 1]
	cbz	w1, .L2732
	add	x19, x0, 592
	add	x20, x0, 624
.L2730:
	ldr	x1, [x19]
	cbnz	x1, .L2737
.L2729:
	add	x19, x19, 8
	cmp	x19, x20
	bne	.L2730
	ldr	w0, [x21, 1644]
	mov	w2, 0
	mov	w1, w22
	bl	FSP_SetDisplay
	mov	w0, 0
.L2728:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2737:
	ldr	w0, [x21, 1644]
	bl	FreeUsdByDec
	str	xzr, [x19]
	b	.L2729
	.p2align 3
.L2732:
	mov	w0, -1
	b	.L2728
	.size	H264DEC_RecycleImage, .-H264DEC_RecycleImage
	.align	3
.LC781:
	.xword	.LC780
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	OutputFrmToVO
	.type	OutputFrmToVO, %function
OutputFrmToVO:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x22, x1
	mov	w23, w2
	bl	_mcount
	cmp	x19, xzr
	ccmp	x22, xzr, 4, ne
	beq	.L2780
	ldr	x0, [x19]
	ldr	w0, [x0, 24]
	cbz	w0, .L2741
	add	x0, x19, 65536
	ldr	w0, [x0, 1572]
	cmp	w0, 2
	beq	.L2741
	add	x19, x19, 61440
	ldr	x0, [x19, 3208]
	cbz	x0, .L2743
	strb	wzr, [x0, 1]
	mov	w0, 1
	str	xzr, [x19, 3208]
.L2740:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2741:
	mov	x1, x22
	mov	x0, x19
	bl	CheckFrameStore
	cmn	w0, #3
	beq	.L2743
	add	x20, x19, 61440
	ldr	x1, [x20, 3208]
	cbz	x1, .L2744
	mov	x0, x19
	bl	GetImagePara
	ldr	x1, [x20, 3208]
	mov	x0, x19
	bl	CheckFrameStore
	cbz	w0, .L2781
	cmn	w0, #3
	beq	.L2751
	ldr	x1, .LC789
	mov	w3, w0
	mov	w2, 2036
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x20, 3208]
	mov	x0, x19
	ldr	w1, [x1, 164]
	bl	H264DEC_RecycleImage
.L2751:
	ldr	x0, [x20, 3208]
	strb	wzr, [x0, 1]
	ldr	x0, [x20, 3208]
	str	xzr, [x20, 3208]
	cmp	x22, x0
	beq	.L2782
.L2744:
	mov	x1, x22
	mov	x0, x19
	bl	GetImagePara
	mov	x1, x22
	mov	x0, x19
	bl	CheckFrameStore
	cbz	w0, .L2783
	cmn	w0, #3
	beq	.L2743
	ldr	x1, .LC789
	mov	w3, w0
	mov	w2, 2093
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x22, 164]
	mov	x0, x19
	bl	H264DEC_RecycleImage
	mov	w0, 2
	b	.L2740
	.p2align 3
.L2780:
	ldr	x1, .LC783
	mov	x3, x22
	mov	x2, x19
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 2
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2743:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2783:
	add	x21, x19, 65536
	ldr	w1, [x22, 648]
	mov	w2, 1
	ldr	w0, [x21, 1644]
	bl	FSP_SetDisplay
	ldr	w0, [x21, 1644]
	ldr	w1, [x22, 648]
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L2784
	cmp	w23, 1
	beq	.L2785
.L2755:
	ldr	w0, [x21, 1644]
	mov	x4, x20
	add	x3, x19, 8
	mov	x2, x19
	mov	w1, 0
	bl	InsertImgToVoQueue
	cmp	w0, 1
	bne	.L2786
	ldr	x0, [x19]
	ldr	w0, [x0, 612]
	add	w0, w0, 2047
	cmp	w0, 4095
	bhi	.L2787
	str	wzr, [x20, 16]
.L2758:
	ldr	w1, [x21, 1664]
	mov	w0, 0
	ldr	w2, [x21, 1672]
	add	w1, w1, 2
	str	w1, [x21, 1664]
	add	w2, w2, 1
	str	w2, [x21, 1672]
	b	.L2740
	.p2align 3
.L2781:
	ldr	x0, [x20, 3208]
	add	x21, x19, 65536
	mov	w2, 1
	ldr	w1, [x0, 648]
	ldr	w0, [x21, 1644]
	bl	FSP_SetDisplay
	ldr	x1, [x20, 3208]
	ldr	w0, [x21, 1644]
	ldr	w1, [x1, 648]
	bl	FSP_GetFsImagePtr
	mov	x24, x0
	cbz	x0, .L2788
	ldr	x0, [x20, 3208]
	cmp	x0, x22
	ccmp	w23, 1, 0, eq
	beq	.L2789
.L2747:
	ldr	w0, [x21, 1644]
	mov	x4, x24
	add	x3, x19, 8
	mov	x2, x19
	mov	w1, 0
	bl	InsertImgToVoQueue
	cmp	w0, 1
	bne	.L2790
	ldr	x0, [x19]
	ldr	w0, [x0, 612]
	add	w0, w0, 2047
	cmp	w0, 4095
	bhi	.L2791
	str	wzr, [x24, 16]
.L2750:
	ldr	w0, [x21, 1664]
	ldr	w1, [x21, 1672]
	add	w0, w0, 2
	str	w0, [x21, 1664]
	add	w1, w1, 1
	str	w1, [x21, 1672]
	b	.L2751
	.p2align 3
.L2785:
	str	w23, [x0, 180]
	b	.L2755
	.p2align 3
.L2787:
	mov	x1, x20
	mov	x0, x19
	bl	SetFrmRepeatCount.part.3
	b	.L2758
	.p2align 3
.L2791:
	mov	x1, x24
	mov	x0, x19
	bl	SetFrmRepeatCount.part.3
	b	.L2750
	.p2align 3
.L2789:
	mov	w0, 1
	str	w0, [x24, 180]
	b	.L2747
	.p2align 3
.L2782:
	mov	w0, 0
	b	.L2740
.L2786:
	ldr	x1, .LC787
	mov	w2, w0
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x21, 1644]
	mov	w2, 0
	ldr	w1, [x22, 648]
	bl	FSP_SetDisplay
	mov	w1, 1
	mov	x0, x19
	bl	ClearAll
	mov	w0, -1
	b	.L2740
.L2790:
	ldr	x1, .LC787
	mov	w2, w0
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x0, [x20, 3208]
	mov	w2, 0
	strb	wzr, [x0, 1]
	ldr	x1, [x20, 3208]
	ldr	w0, [x21, 1644]
	ldr	w1, [x1, 648]
	bl	FSP_SetDisplay
	str	xzr, [x20, 3208]
	mov	w1, 1
	mov	x0, x19
	bl	ClearAll
	mov	w0, -1
	b	.L2740
.L2788:
	ldr	x1, .LC785
	mov	w2, 2007
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2740
.L2784:
	ldr	x1, .LC791
	mov	w2, 2063
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2740
	.size	OutputFrmToVO, .-OutputFrmToVO
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	OutputFrmFromDPB
	.type	OutputFrmFromDPB, %function
OutputFrmFromDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w1
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, x21, uxtw 3
	bl	_mcount
	mov	w2, 0
	mov	x0, x20
	ldr	x1, [x19, 27896]
	strb	wzr, [x1, 4]
	ldr	x1, [x19, 27896]
	bl	OutputFrmToVO
	mov	w22, w0
	ldr	x0, [x19, 27896]
	ldrb	w0, [x0, 2]
	cbnz	w0, .L2793
	mov	w1, w21
	mov	x0, x20
	bl	RemoveFrameStoreOutDPB
.L2793:
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	OutputFrmFromDPB, .-OutputFrmFromDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FlushDPB
	.type	FlushDPB, %function
FlushDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 24576
	mov	w21, 0
	bl	_mcount
	ldr	w0, [x19, 3708]
	cbnz	w0, .L2812
	b	.L2796
	.p2align 3
.L2797:
	ldr	w0, [x19, 3708]
	cmp	w0, w21
	bls	.L2796
.L2812:
	add	x0, x20, x21, uxtw 3
	add	w21, w21, 1
	ldr	x1, [x0, 27896]
	ldrb	w0, [x1, 2]
	cbz	w0, .L2797
	mov	x0, x20
	bl	UnMarkFrameStoreRef
	ldr	w0, [x19, 3708]
	cmp	w0, w21
	bhi	.L2812
	.p2align 2
.L2796:
	mov	x0, x20
	bl	RemoveUnUsedFrameStore
	cbnz	w0, .L2796
	.p2align 2
.L2800:
	ldr	w6, [x19, 3708]
	cbz	w6, .L2817
	ldr	w0, [x19, 3704]
	cmp	w6, w0
	bls	.L2801
	str	w0, [x19, 3708]
	cbz	w0, .L2807
	mov	w6, w0
.L2801:
	add	x2, x19, 3320
	mov	w5, 2147483647
	mov	w0, 0
	mov	w1, 0
	.p2align 2
.L2804:
	ldr	x4, [x2]
	add	x2, x2, 8
	ldr	w3, [x4, 664]
	cmp	w3, w5
	bge	.L2803
	ldrb	w4, [x4, 4]
	cmp	w4, wzr
	csel	w5, w5, w3, eq
	csel	w1, w1, w0, eq
.L2803:
	add	w0, w0, 1
	cmp	w6, w0
	bhi	.L2804
	mov	x0, x20
	bl	OutputFrmFromDPB
	cmn	w0, #1
	bne	.L2800
.L2805:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L2807:
	mov	w1, 0
	mov	x0, x20
	bl	OutputFrmFromDPB
	cmn	w0, #1
	bne	.L2800
	b	.L2805
	.p2align 3
.L2817:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	FlushDPB, .-FlushDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AdaptiveMemMark
	.type	AdaptiveMemMark, %function
AdaptiveMemMark:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	add	x26, x21, 61440
	add	x25, x21, 20480
	bl	_mcount
	ldr	x24, .LC792
	add	x23, x26, 1704
	mov	w27, 1
	ldr	x22, [x26, 2360]
	add	x20, x22, 8
	add	x22, x22, 2008
	.p2align 2
.L2831:
	ldr	w0, [x20, -4]
	cmp	w0, 6
	bhi	.L2819
	ldrb	w0, [x24,w0,uxtw]
	adr	x1, .Lrtx2821
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx2821:
	.section	.rodata
	.align	0
	.align	2
.L2821:
	.byte	(.L2820 - .Lrtx2821) / 4
	.byte	(.L2822 - .Lrtx2821) / 4
	.byte	(.L2823 - .Lrtx2821) / 4
	.byte	(.L2824 - .Lrtx2821) / 4
	.byte	(.L2825 - .Lrtx2821) / 4
	.byte	(.L2826 - .Lrtx2821) / 4
	.byte	(.L2827 - .Lrtx2821) / 4
	.text
	.p2align 3
.L2826:
	add	x28, x21, 24576
	mov	w19, 0
	ldr	w0, [x28, 3712]
	cbz	w0, .L2830
	.p2align 2
.L2838:
	add	x1, x21, x19, uxtw 3
	mov	x0, x21
	add	w19, w19, 1
	ldr	x1, [x1, 28024]
	bl	UnMarkFrameStoreRef
	ldr	w0, [x28, 3712]
	cmp	w19, w0
	bcc	.L2838
.L2830:
	mov	x0, x21
	bl	UpdateReflist
	mov	w1, 0
	mov	x0, x21
	bl	UpdateMaxLTFrmIdx
	mov	x0, x21
	bl	UpdateLTReflist
	str	w27, [x25, 728]
	.p2align 2
.L2819:
	add	x20, x20, 20
	cmp	x20, x22
	bne	.L2831
	.p2align 2
.L2820:
	ldr	w1, [x25, 728]
	mov	w0, 0
	cmp	w1, 1
	beq	.L2841
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L2825:
	ldr	w1, [x20, 12]
	mov	x0, x21
	bl	UpdateMaxLTFrmIdx
	mov	x0, x21
	bl	UpdateLTReflist
	b	.L2819
	.p2align 3
.L2824:
	ldr	w2, [x20]
	mov	x1, x23
	ldr	w3, [x20, 8]
	mov	x0, x21
	bl	MarkSTToLTRef
	mov	x0, x21
	bl	UpdateReflist
	mov	x0, x21
	bl	UpdateLTReflist
	b	.L2819
	.p2align 3
.L2823:
	ldr	w2, [x20, 4]
	mov	x0, x21
	mov	x1, x23
	bl	UnMarkLTRef
	mov	x0, x21
	bl	UpdateLTReflist
	b	.L2819
	.p2align 3
.L2822:
	ldr	w2, [x20]
	mov	x0, x21
	mov	x1, x23
	bl	UnMarkSTRef
	mov	x0, x21
	bl	UpdateReflist
	b	.L2819
	.p2align 3
.L2827:
	ldr	w2, [x20, 8]
	mov	x1, x23
	mov	x0, x21
	bl	MarkCurrPicLT
	b	.L2819
	.p2align 3
.L2841:
	ldrb	w0, [x26, 1707]
	str	wzr, [x26, 2368]
	cmp	w0, 1
	beq	.L2834
	cbz	w0, .L2835
	cmp	w0, 2
	bne	.L2833
	str	wzr, [x26, 2380]
	str	wzr, [x26, 2392]
	str	wzr, [x25, 740]
	str	wzr, [x25, 748]
.L2833:
	mov	x0, x21
	bl	FlushDPB
	cmp	w0, wzr
	csetm	w0, ne
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L2835:
	ldr	w2, [x26, 2380]
	ldr	w0, [x26, 2388]
	ldr	w1, [x26, 2392]
	sub	w0, w0, w2
	str	w0, [x26, 2388]
	sub	w1, w1, w2
	str	w1, [x26, 2392]
	cmp	w0, w1
	csel	w0, w0, w1, le
	str	w0, [x26, 2380]
	str	w0, [x26, 2384]
	ldr	w2, [x25, 748]
	ldr	w0, [x25, 736]
	ldr	w1, [x25, 740]
	sub	w0, w0, w2
	str	w0, [x25, 736]
	sub	w1, w1, w2
	str	w1, [x25, 740]
	cmp	w0, w1
	csel	w0, w0, w1, le
	str	w0, [x25, 744]
	str	w0, [x25, 748]
	b	.L2833
.L2834:
	str	wzr, [x26, 2380]
	str	wzr, [x26, 2388]
	str	wzr, [x25, 736]
	str	wzr, [x25, 748]
	b	.L2833
	.size	AdaptiveMemMark, .-AdaptiveMemMark
	.align	3
.LC792:
	.xword	.L2821
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IDRMemMarking
	.type	IDRMemMarking, %function
IDRMemMarking:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x22, x0
	mov	x0, x30
	add	x24, x22, 61440
	bl	_mcount
	ldr	x0, [x24, 2360]
	ldrb	w0, [x0, 1]
	cbz	w0, .L2843
	add	x23, x22, 24576
	mov	w21, 0
	add	x20, x22, 65536
	mov	w25, 1
	ldr	w0, [x23, 3708]
	cbnz	w0, .L2858
	b	.L2850
	.p2align 3
.L2847:
	strb	wzr, [x0, 698]
	strb	wzr, [x0, 697]
	ldr	x0, [x19, 27896]
	strb	wzr, [x0, 746]
	strb	wzr, [x0, 745]
	ldr	x0, [x19, 27896]
	strb	wzr, [x0, 794]
	strb	wzr, [x0, 793]
	ldr	x0, [x19, 27896]
	strb	wzr, [x0, 2]
	ldr	x1, [x19, 27896]
	ldr	w0, [x20, 1644]
	ldr	w1, [x1, 648]
	bl	FSP_SetRef
	ldr	x0, [x19, 27896]
	strb	wzr, [x0, 1]
	ldr	x0, [x19, 27896]
	strb	wzr, [x0, 4]
	ldr	x0, [x19, 27896]
	str	w25, [x0, 668]
	ldr	x1, [x19, 27896]
	ldr	w0, [x1, 688]
	add	x0, x0, 4096
	add	x0, x0, 2980
	str	wzr, [x22, x0, lsl 2]
	ldr	w1, [x1, 648]
	ldr	w0, [x20, 1644]
	bl	FSP_GetDisplay
	cmp	w0, 3
	mov	w2, 0
	beq	.L2848
	ldr	x1, [x19, 27896]
	ldr	w0, [x20, 1644]
	ldr	w1, [x1, 648]
	bl	FSP_SetDisplay
.L2848:
	str	xzr, [x19, 27896]
	str	xzr, [x19, 28024]
	str	xzr, [x19, 28152]
	ldr	w0, [x23, 3708]
	cmp	w0, w21
	bls	.L2850
.L2858:
	add	x19, x22, x21, uxtw 3
	mov	w2, 0
	add	w21, w21, 1
	ldr	x0, [x19, 27896]
	ldr	w1, [x0, 840]
	cmp	w1, 1
	bne	.L2847
	str	w1, [x20, 316]
	b	.L2847
	.p2align 3
.L2850:
	str	wzr, [x23, 3708]
	ldr	w0, [x20, 304]
	cbz	w0, .L2846
	sub	w1, w0, #1
	add	x0, x20, 232
	add	x1, x1, 16384
	add	x1, x1, 59
	add	x1, x22, x1, lsl 2
	.p2align 2
.L2853:
	str	wzr, [x0], 4
	cmp	x0, x1
	bne	.L2853
.L2846:
	mov	x0, x22
	bl	UpdateReflist
	mov	x0, x22
	bl	UpdateLTReflist
	ldr	x0, [x24, 2360]
	ldrb	w0, [x0, 2]
	cbnz	w0, .L2864
	mov	w0, 1
	str	wzr, [x23, 3720]
	strb	w0, [x24, 1709]
	mov	w0, 0
	strb	wzr, [x24, 1708]
.L2854:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L2864:
	mov	w0, 1
	str	w0, [x23, 3720]
	strb	w0, [x24, 1708]
	mov	w0, 0
	strb	wzr, [x24, 1709]
	str	wzr, [x24, 2372]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L2843:
	mov	x0, x22
	bl	FlushDPB
	cbnz	w0, .L2855
	add	x23, x22, 24576
	b	.L2846
.L2855:
	mov	w0, -1
	b	.L2854
	.size	IDRMemMarking, .-IDRMemMarking
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Marking
	.type	Marking, %function
Marking:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 61440
	bl	_mcount
	add	x0, x20, 20480
	str	wzr, [x0, 728]
	ldrb	w1, [x19, 1707]
	cmp	w1, 2
	cset	w1, eq
	str	w1, [x0, 732]
	ldrb	w0, [x19, 1710]
	cmp	w0, 5
	beq	.L2866
	ldr	w0, [x19, 2396]
	cbnz	w0, .L2867
	ldr	x0, [x20]
	mov	x1, 4294967296
	ldr	x2, [x0, 648]
	cmp	x2, x1
	beq	.L2891
.L2867:
	ldr	x0, [x19, 2360]
	ldrb	w0, [x0, 3]
	cbz	w0, .L2892
	ldr	w0, [x19, 2376]
	cbnz	w0, .L2893
.L2874:
	mov	w0, 0
.L2871:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2892:
	ldr	w0, [x19, 2376]
	cbz	w0, .L2874
.L2873:
	ldrb	w1, [x19, 1705]
	cbnz	w1, .L2878
	add	x1, x20, 24576
	add	x2, x20, 16384
	ldr	w4, [x1, 3716]
	ldr	w2, [x2, 1836]
	ldr	w3, [x1, 3712]
	sub	w1, w2, w4
	cmp	w3, w1
	beq	.L2894
	strb	wzr, [x19, 1708]
.L2876:
	cbz	w0, .L2874
.L2878:
	ldrb	w1, [x19, 1708]
	mov	w0, 0
	cmp	w1, wzr
	cset	w1, eq
	strb	w1, [x19, 1709]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2891:
	ldr	w1, [x0, 656]
	cbnz	w1, .L2867
	ldr	w0, [x0, 612]
	add	w0, w0, 1024
	cmp	w0, 2048
	bls	.L2867
	.p2align 2
.L2866:
	mov	x0, x20
	bl	IDRMemMarking
	cbz	w0, .L2875
.L2868:
	mov	w0, -1
	b	.L2871
	.p2align 3
.L2893:
	mov	x0, x20
	bl	AdaptiveMemMark
	cbnz	w0, .L2868
.L2875:
	ldrb	w0, [x19, 1710]
	cmp	w0, 5
	bne	.L2895
	ldr	w0, [x19, 2376]
	b	.L2876
	.p2align 3
.L2894:
	mov	x0, x20
	bl	SlidingWinMark.part.4
	strb	wzr, [x19, 1708]
	ldr	w0, [x19, 2376]
	b	.L2876
.L2895:
	ldr	w0, [x19, 2376]
	cbz	w0, .L2874
	ldr	x1, [x19, 2360]
	ldrb	w1, [x1, 3]
	cbnz	w1, .L2878
	b	.L2873
	.size	Marking, .-Marking
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DirectOutput
	.type	DirectOutput, %function
DirectOutput:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 61440
	bl	_mcount
	ldrb	w0, [x19, 1707]
	cmp	w0, 1
	beq	.L2898
	cbz	w0, .L2899
	cmp	w0, 2
	beq	.L2900
	mov	w21, 0
.L2897:
	mov	w0, w21
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L2900:
	ldr	x0, [x19, 2352]
	mov	w1, 3
	strb	w1, [x0, 696]
	ldrb	w0, [x19, 1705]
	cbnz	w0, .L2916
	ldr	x1, [x19, 3208]
	cbz	x1, .L2917
	mov	w2, 0
	mov	x0, x20
	bl	OutputFrmToVO
	mov	w21, w0
	cbnz	w0, .L2982
.L2918:
	ldr	x0, [x19, 2352]
	str	x0, [x19, 3208]
	str	x0, [x0, 832]
.L2919:
	ldr	x0, [x19, 3208]
	mov	w22, 2
	ldrb	w3, [x19, 1706]
	mov	x2, 632
	add	x1, x19, 1720
	add	x23, x20, 65536
	strb	w3, [x0]
	ldr	x0, [x19, 3208]
	strb	w22, [x0, 1]
	ldr	x0, [x19, 3208]
	strb	wzr, [x0, 4]
	ldr	x0, [x19, 3208]
	str	wzr, [x0, 668]
	ldr	x0, [x19, 3208]
	strb	wzr, [x0, 2]
	ldr	x0, [x19, 3208]
	ldr	w3, [x19, 2396]
	str	w3, [x0, 676]
	ldr	x0, [x19, 3208]
	str	wzr, [x0, 672]
	ldr	x0, [x19, 3208]
	add	x0, x0, 16
	bl	memcpy
	ldr	x1, [x19, 3208]
	mov	w0, 2
	ldr	w2, [x19, 2404]
	str	w2, [x1, 808]
	ldr	x1, [x19, 3208]
	ldr	w2, [x1, 808]
	str	w2, [x1, 680]
	str	w2, [x1, 712]
	ldr	x1, [x19, 3208]
	strb	w22, [x1, 792]
	ldrb	w2, [x19, 1711]
	ldr	x1, [x19, 3208]
	cmp	w2, 1
	csel	w0, wzr, w0, ne
	strb	w0, [x1, 3]
	ldr	w22, [x23, 1576]
	cmp	w22, 1
	bne	.L2897
.L2976:
	ldr	x1, [x19, 3208]
	mov	w2, 0
	ldr	w0, [x23, 1644]
	ldr	w1, [x1, 648]
	bl	FSP_SetRef
	ldr	x1, [x19, 3208]
	mov	w2, 0
	mov	x0, x20
	bl	OutputFrmToVO
	mov	w21, w0
	ldr	x0, [x19, 3208]
	cbz	x0, .L2927
	ldr	x1, [x19, 2352]
	mov	w2, w22
	ldr	w0, [x23, 1644]
	ldr	w1, [x1, 648]
	bl	FSP_ClearLogicFs
.L2927:
	str	xzr, [x19, 3208]
.L2984:
	mov	w0, w21
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L2899:
	ldr	x0, [x19, 2352]
	strb	wzr, [x0, 696]
	ldr	x1, [x19, 3208]
	cbz	x1, .L2972
	mov	w2, 0
	mov	x0, x20
	bl	OutputFrmToVO
	cbnz	w0, .L2983
.L2902:
	ldr	x0, [x19, 3208]
	cbz	x0, .L2972
	ldr	x0, [x19, 2352]
	add	x22, x20, 65536
	mov	w2, 1
	ldr	w1, [x0, 648]
	ldr	w0, [x22, 1644]
	bl	FSP_ClearLogicFs
.L2901:
	ldr	x0, [x19, 2352]
	mov	w3, 3
	str	x0, [x19, 3208]
	mov	x2, 632
	add	x1, x19, 1720
	str	x0, [x0, 736]
	ldr	x0, [x19, 3208]
	ldr	x4, [x19, 2352]
	str	x4, [x0, 784]
	ldr	x0, [x19, 3208]
	ldr	x4, [x19, 2352]
	str	x4, [x0, 832]
	ldr	x0, [x19, 3208]
	ldrb	w4, [x19, 1706]
	strb	w4, [x0]
	ldr	x0, [x19, 3208]
	strb	w3, [x0, 1]
	ldr	x0, [x19, 3208]
	strb	wzr, [x0, 2]
	ldr	x0, [x19, 3208]
	strb	wzr, [x0, 4]
	ldr	x0, [x19, 3208]
	str	wzr, [x0, 668]
	ldr	x0, [x19, 3208]
	add	x0, x0, 16
	bl	memcpy
	ldr	x1, [x19, 3208]
	mov	w0, 3
	ldr	w3, [x19, 2404]
	mov	w2, 0
	str	w3, [x1, 680]
	str	w3, [x1, 712]
	ldr	x1, [x19, 3208]
	strb	wzr, [x1, 696]
	ldr	x1, [x19, 3208]
	ldr	w3, [x19, 2396]
	str	w3, [x1, 676]
	ldr	x1, [x19, 3208]
	ldrb	w3, [x19, 1713]
	str	w3, [x1, 672]
	ldrb	w3, [x19, 1711]
	ldr	x1, [x19, 3208]
	cmp	w3, 1
	csel	w0, wzr, w0, ne
	strb	w0, [x1, 3]
.L2979:
	ldr	x1, [x19, 3208]
	ldr	w0, [x22, 1644]
	ldr	w1, [x1, 648]
	bl	FSP_SetRef
	ldr	x1, [x19, 3208]
	mov	w2, 0
	mov	x0, x20
	bl	OutputFrmToVO
	mov	w21, w0
	ldr	x0, [x19, 3208]
	cbz	x0, .L2927
	ldr	x1, [x19, 2352]
	mov	w2, 1
	ldr	w0, [x22, 1644]
	ldr	w1, [x1, 648]
	bl	FSP_ClearLogicFs
	str	xzr, [x19, 3208]
	b	.L2984
	.p2align 3
.L2898:
	ldr	x0, [x19, 2352]
	mov	w1, 3
	strb	w1, [x0, 696]
	ldrb	w0, [x19, 1705]
	cbnz	w0, .L2905
	ldr	x1, [x19, 3208]
	cbz	x1, .L2906
	mov	w2, 0
	mov	x0, x20
	bl	OutputFrmToVO
	mov	w21, w0
	cbnz	w0, .L2985
.L2907:
	ldr	x0, [x19, 2352]
	str	x0, [x19, 3208]
	str	x0, [x0, 784]
.L2908:
	ldr	x0, [x19, 3208]
	mov	w22, 1
	ldrb	w3, [x19, 1706]
	add	x1, x19, 1720
	mov	x2, 632
	add	x23, x20, 65536
	strb	w3, [x0]
	ldr	x0, [x19, 3208]
	strb	w22, [x0, 1]
	ldr	x0, [x19, 3208]
	strb	wzr, [x0, 4]
	ldr	x0, [x19, 3208]
	str	wzr, [x0, 668]
	ldr	x0, [x19, 3208]
	strb	wzr, [x0, 2]
	ldr	x0, [x19, 3208]
	ldr	w3, [x19, 2396]
	str	w3, [x0, 676]
	ldr	x0, [x19, 3208]
	str	wzr, [x0, 672]
	ldr	x0, [x19, 3208]
	add	x0, x0, 16
	bl	memcpy
	ldr	x0, [x19, 3208]
	ldr	w1, [x19, 2404]
	str	w1, [x0, 760]
	ldr	x0, [x19, 3208]
	ldr	w1, [x0, 760]
	str	w1, [x0, 680]
	str	w1, [x0, 712]
	ldr	x0, [x19, 3208]
	strb	w22, [x0, 744]
	ldrb	w1, [x19, 1711]
	ldr	x0, [x19, 3208]
	cmp	w1, 1
	cset	w1, eq
	strb	w1, [x0, 3]
	ldr	w22, [x23, 1576]
	cmp	w22, 1
	beq	.L2976
	mov	w0, w21
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L2916:
	ldr	x0, [x19, 3208]
	cbz	x0, .L2986
.L2922:
	ldr	x27, [x0, 600]
	mov	x2, 632
	ldp	w24, w23, [x0, 16]
	ldp	w22, w21, [x0, 24]
	ldr	x26, [x0, 608]
	add	x1, x19, 1720
	ldr	x25, [x0, 616]
	add	x0, x0, 16
	bl	memcpy
	ldr	x0, [x19, 2304]
	cmn	x0, #1
	ccmn	x27, #1, 4, eq
	beq	.L2923
	ldr	x0, [x19, 3208]
	str	x27, [x0, 600]
.L2923:
	ldr	x0, [x19, 2312]
	ldr	x1, [x19, 3208]
	cmp	x0, x26
	csel	x0, x0, x26, ls
	str	x0, [x1, 608]
	ldr	x0, [x19, 2320]
	ldr	x1, [x19, 3208]
	cmp	x0, x25
	csel	x0, x0, x25, ls
	str	x0, [x1, 616]
	ldr	w0, [x19, 1720]
	ldr	x1, [x19, 3208]
	cmp	w0, w24
	csel	w0, w0, w24, ls
	str	w0, [x1, 16]
	ldr	w0, [x19, 1724]
	ldr	x1, [x19, 3208]
	cmp	w0, w23
	csel	w0, w0, w23, ls
	str	w0, [x1, 20]
	ldr	w0, [x19, 1728]
	ldr	x1, [x19, 3208]
	cmp	w0, w22
	csel	w0, w0, w22, ls
	str	w0, [x1, 24]
	ldr	w0, [x19, 1732]
	ldr	x1, [x19, 3208]
	cmp	w0, w21
	csel	w0, w0, w21, ls
	str	w0, [x1, 28]
	ldr	x1, [x19, 3208]
	ldrb	w0, [x1]
	cbz	w0, .L2924
	ldrb	w0, [x19, 1706]
.L2924:
	strb	w0, [x1]
	mov	w4, 2
	mov	w3, 3
	ldr	x1, [x19, 3208]
	ldrb	w0, [x1, 1]
	orr	w0, w0, 2
	strb	w0, [x1, 1]
	ldr	x1, [x19, 3208]
	ldr	w0, [x19, 2396]
	ldr	w2, [x1, 676]
	cmp	w0, w2
	csel	w0, w0, w2, cs
	str	w0, [x1, 676]
	ldr	x0, [x19, 3208]
	strb	w4, [x0, 792]
	ldr	x0, [x19, 3208]
	strb	w3, [x0, 696]
	ldr	x0, [x19, 3208]
	ldr	w1, [x19, 2404]
	str	w1, [x0, 808]
	ldr	x1, [x19, 3208]
	ldr	w2, [x1, 760]
	ldr	w0, [x1, 808]
	add	w0, w2, w0
	lsr	w0, w0, 1
	str	w0, [x1, 712]
	ldr	x0, [x19, 3208]
	ldr	w1, [x0, 712]
	str	w1, [x0, 680]
	ldr	x0, [x19, 3208]
	ldr	x1, [x0, 832]
	str	x1, [x0, 736]
	ldrb	w0, [x19, 1711]
	ldr	x1, [x19, 3208]
	cmp	w0, 1
	beq	.L2987
.L2925:
	ldrb	w0, [x1, 3]
.L2926:
	strb	w0, [x1, 3]
	add	x22, x20, 65536
	mov	w2, 0
	b	.L2979
	.p2align 3
.L2905:
	ldr	x0, [x19, 3208]
	cbz	x0, .L2988
.L2910:
	ldr	x27, [x0, 600]
	mov	x2, 632
	ldp	w24, w23, [x0, 16]
	ldp	w22, w21, [x0, 24]
	ldr	x26, [x0, 608]
	add	x1, x19, 1720
	ldr	x25, [x0, 616]
	add	x0, x0, 16
	bl	memcpy
	ldr	x0, [x19, 2304]
	cmn	x0, #1
	ccmn	x27, #1, 4, eq
	beq	.L2911
	ldr	x0, [x19, 3208]
	str	x27, [x0, 600]
.L2911:
	ldr	x0, [x19, 2312]
	ldr	x1, [x19, 3208]
	cmp	x0, x26
	csel	x0, x0, x26, ls
	str	x0, [x1, 608]
	ldr	x0, [x19, 2320]
	ldr	x1, [x19, 3208]
	cmp	x0, x25
	csel	x0, x0, x25, ls
	str	x0, [x1, 616]
	ldr	w0, [x19, 1720]
	ldr	x1, [x19, 3208]
	cmp	w0, w24
	csel	w0, w0, w24, ls
	str	w0, [x1, 16]
	ldr	w0, [x19, 1724]
	ldr	x1, [x19, 3208]
	cmp	w0, w23
	csel	w0, w0, w23, ls
	str	w0, [x1, 20]
	ldr	w0, [x19, 1728]
	ldr	x1, [x19, 3208]
	cmp	w0, w22
	csel	w0, w0, w22, ls
	str	w0, [x1, 24]
	ldr	w0, [x19, 1732]
	ldr	x1, [x19, 3208]
	cmp	w0, w21
	csel	w0, w0, w21, ls
	str	w0, [x1, 28]
	ldr	x1, [x19, 3208]
	ldrb	w0, [x1]
	cbz	w0, .L2912
	ldrb	w0, [x19, 1706]
.L2912:
	strb	w0, [x1]
	mov	w4, 1
	mov	w3, 3
	ldr	x1, [x19, 3208]
	ldrb	w0, [x1, 1]
	orr	w0, w0, 1
	strb	w0, [x1, 1]
	ldr	x1, [x19, 3208]
	ldr	w0, [x19, 2396]
	ldr	w2, [x1, 676]
	cmp	w0, w2
	csel	w0, w0, w2, cs
	str	w0, [x1, 676]
	ldr	x0, [x19, 3208]
	strb	w4, [x0, 744]
	ldr	x0, [x19, 3208]
	strb	w3, [x0, 696]
	ldr	x0, [x19, 3208]
	ldr	w1, [x19, 2404]
	str	w1, [x0, 760]
	ldr	x1, [x19, 3208]
	ldr	w2, [x1, 760]
	ldr	w0, [x1, 808]
	add	w0, w2, w0
	lsr	w0, w0, w4
	str	w0, [x1, 712]
	ldr	x0, [x19, 3208]
	ldr	w1, [x0, 712]
	str	w1, [x0, 680]
	ldr	x0, [x19, 3208]
	ldr	x1, [x0, 784]
	str	x1, [x0, 736]
	ldrb	w0, [x19, 1711]
	ldr	x1, [x19, 3208]
	cmp	w0, 1
	bne	.L2925
	ldrb	w0, [x1, 3]
	orr	w0, w0, 1
	uxtb	w0, w0
	b	.L2926
	.p2align 3
.L2972:
	add	x22, x20, 65536
	b	.L2901
	.p2align 3
.L2983:
	ldr	x2, .LC793
	mov	w4, w0
	ldr	x1, .LC795
	mov	w3, 2628
	add	x2, x2, 248
	mov	w0, 22
	bl	dprint_vfmw
	b	.L2902
	.p2align 3
.L2987:
	ldrb	w0, [x1, 3]
	orr	w0, w0, 2
	uxtb	w0, w0
	b	.L2926
	.p2align 3
.L2906:
	ldr	x0, [x19, 2352]
	mov	w21, 0
	str	x0, [x19, 3208]
	str	x0, [x0, 784]
	b	.L2908
	.p2align 3
.L2917:
	ldr	x0, [x19, 2352]
	mov	w21, 0
	str	x0, [x19, 3208]
	str	x0, [x0, 832]
	b	.L2919
	.p2align 3
.L2985:
	ldr	x2, .LC793
	mov	w4, w0
	ldr	x1, .LC795
	mov	w3, 2680
	add	x2, x2, 248
	mov	w0, 22
	bl	dprint_vfmw
	b	.L2907
	.p2align 3
.L2982:
	ldr	x2, .LC793
	mov	w4, w0
	ldr	x1, .LC795
	mov	w3, 2796
	add	x2, x2, 248
	mov	w0, 22
	bl	dprint_vfmw
	b	.L2918
	.p2align 3
.L2986:
	ldr	x0, [x19, 2352]
	str	x0, [x19, 3208]
	str	x0, [x0, 832]
	ldr	x0, [x19, 3208]
	b	.L2922
	.p2align 3
.L2988:
	ldr	x0, [x19, 2352]
	str	x0, [x19, 3208]
	str	x0, [x0, 784]
	ldr	x0, [x19, 3208]
	b	.L2910
	.size	DirectOutput, .-DirectOutput
	.align	3
.LC793:
	.xword	.LANCHOR2
	.align	3
.LC795:
	.xword	.LC794
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264DEC_GetRemainImg
	.type	H264DEC_GetRemainImg, %function
H264DEC_GetRemainImg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	add	x20, x21, 24576
	mov	w19, 0
	bl	_mcount
	ldr	w0, [x20, 3708]
	cbnz	w0, .L3009
	b	.L2991
	.p2align 3
.L2992:
	ldr	w0, [x20, 3708]
	cmp	w0, w19
	bls	.L2991
.L3009:
	add	x0, x21, x19, uxtw 3
	add	w19, w19, 1
	ldr	x1, [x0, 27896]
	ldrb	w0, [x1, 2]
	cbz	w0, .L2992
	mov	x0, x21
	bl	UnMarkFrameStoreRef
	ldr	w0, [x20, 3708]
	cmp	w0, w19
	bhi	.L3009
	.p2align 2
.L2991:
	mov	x0, x21
	bl	RemoveUnUsedFrameStore
	cbnz	w0, .L2991
	mov	w23, -1
	.p2align 2
.L2995:
	ldr	w5, [x20, 3708]
	cbz	w5, .L3015
.L3001:
	ldr	w0, [x20, 3704]
	cmp	w5, w0
	bls	.L2996
	str	w0, [x20, 3708]
	cbz	w0, .L3003
	mov	w5, w0
.L2996:
	add	x1, x20, 3320
	mov	w4, 2147483647
	mov	w0, 0
	mov	w19, 0
	.p2align 2
.L2999:
	ldr	x3, [x1]
	add	x1, x1, 8
	ldr	w2, [x3, 664]
	cmp	w2, w4
	bge	.L2998
	ldrb	w3, [x3, 4]
	cmp	w3, wzr
	csel	w4, w4, w2, eq
	csel	w19, w19, w0, eq
.L2998:
	add	w0, w0, 1
	cmp	w5, w0
	bhi	.L2999
.L2997:
	add	x22, x21, x19, uxtw 3
	mov	x0, x21
	ldr	x1, [x22, 27896]
	strb	wzr, [x1, 4]
	ldr	w2, [x20, 3708]
	ldr	x1, [x22, 27896]
	bl	OutputFrmToVO
	mov	w23, w0
	ldr	x0, [x22, 27896]
	ldrb	w0, [x0, 2]
	cbnz	w0, .L2995
	mov	w1, w19
	mov	x0, x21
	bl	RemoveFrameStoreOutDPB
	ldr	w5, [x20, 3708]
	cbnz	w5, .L3001
.L3015:
	cbz	w23, .L3002
	add	x0, x21, 8
	bl	GetVoLastImageID
	mov	w23, w0
.L3002:
	mov	w0, w23
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L3003:
	mov	w19, 0
	b	.L2997
	.size	H264DEC_GetRemainImg, .-H264DEC_GetRemainImg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	InitDPB.part.15, %function
InitDPB.part.15:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	add	x23, x21, 24576
	add	x20, x21, 65536
	add	x19, x23, 3320
	add	x22, x23, 3448
	bl	_mcount
	.p2align 2
.L3020:
	ldr	x0, [x19]
	mov	w2, 1
	cbz	x0, .L3017
	ldr	w1, [x0, 648]
	ldr	w0, [x20, 1644]
	bl	FSP_ClearLogicFs
.L3017:
	ldr	x0, [x19, 128]
	mov	w2, 1
	cbz	x0, .L3018
	ldr	w1, [x0, 648]
	ldr	w0, [x20, 1644]
	bl	FSP_ClearLogicFs
.L3018:
	ldr	x0, [x19, 256]
	mov	w2, 1
	cbz	x0, .L3019
	ldr	w1, [x0, 648]
	ldr	w0, [x20, 1644]
	bl	FSP_ClearLogicFs
.L3019:
	str	xzr, [x19, 128]
	str	xzr, [x19, 256]
	str	xzr, [x19], 8
	cmp	x19, x22
	bne	.L3020
	add	x0, x21, 16384
	add	x1, x23, 3584
	add	x19, x21, 61440
	ldr	w0, [x0, 1864]
	stp	wzr, wzr, [x1, 128]
	sub	w0, w0, #1
	stp	w0, wzr, [x1, 120]
	str	wzr, [x23, 3720]
	ldr	x1, [x19, 3208]
	cbz	x1, .L3022
	ldr	w0, [x20, 1572]
	cmp	w0, 2
	beq	.L3052
.L3023:
	ldr	w0, [x20, 1644]
	mov	w2, 1
	ldr	w1, [x1, 648]
	bl	FSP_ClearLogicFs
	ldr	x0, [x19, 2352]
	cbz	x0, .L3026
	ldr	x2, [x19, 3208]
	ldr	w1, [x0, 648]
	ldr	w0, [x2, 648]
	cmp	w0, w1
	beq	.L3026
	ldr	w0, [x20, 1644]
	mov	w2, 1
	bl	FSP_ClearLogicFs
.L3026:
	str	xzr, [x19, 3208]
.L3022:
	ldr	x3, .LC798
	mov	x2, 392
	mov	w1, 0
	add	x0, x23, 3728
	ldr	x3, [x3, 96]
	blr	x3
	str	wzr, [x23, 3988]
	ldr	w0, [x23, 3704]
	str	w0, [x23, 3984]
	add	x0, x20, 232
	add	x20, x20, 300
	.p2align 2
.L3027:
	str	wzr, [x0], 4
	cmp	x0, x20
	bne	.L3027
	add	x2, x21, 28672
	add	x1, x2, 24
	add	x0, x2, 288
	.p2align 2
.L3028:
	str	xzr, [x1], 8
	cmp	x1, x0
	bne	.L3028
	add	x21, x21, 20480
	add	x1, x2, 552
	str	wzr, [x21, 1624]
	.p2align 2
.L3029:
	str	xzr, [x0], 8
	cmp	x1, x0
	bne	.L3029
	str	wzr, [x21, 1628]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L3052:
	mov	w2, 0
	mov	x0, x21
	bl	OutputFrmToVO
	cbnz	w0, .L3053
.L3024:
	ldr	x1, [x19, 3208]
	cbz	x1, .L3022
	b	.L3023
	.p2align 3
.L3053:
	ldr	x2, .LC796
	mov	w4, w0
	ldr	x1, .LC797
	mov	w3, 5433
	add	x2, x2, 264
	mov	w0, 22
	bl	dprint_vfmw
	b	.L3024
	.size	InitDPB.part.15, .-InitDPB.part.15
	.align	3
.LC796:
	.xword	.LANCHOR2
	.align	3
.LC797:
	.xword	.LC794
	.align	3
.LC798:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InitDPB
	.type	InitDPB, %function
InitDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L3056
	mov	x0, x19
	bl	ClearAllSlice
	mov	x0, x19
	bl	InitDPB.part.15
.L3055:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3056:
	mov	w0, -1
	b	.L3055
	.size	InitDPB, .-InitDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ClearDPB
	.type	ClearDPB, %function
ClearDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	FlushDPB
	cbz	w0, .L3058
	ldr	x1, .LC800
	mov	w3, w0
	mov	w2, 494
	mov	w0, 0
	bl	dprint_vfmw
.L3058:
	mov	x0, x19
	add	x19, x19, 65536
	bl	InitDPB
	str	wzr, [x19, 316]
	mov	w0, 0
	str	wzr, [x19, 1648]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ClearDPB, .-ClearDPB
	.align	3
.LC800:
	.xword	.LC799
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecVDM
	.type	DecVDM, %function
DecVDM:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	add	x21, x22, 61440
	bl	_mcount
	ldrb	w0, [x21, 1707]
	cbz	w0, .L3063
	ldrb	w0, [x21, 1705]
	add	x19, x22, 65536
	cmp	w0, 1
	beq	.L3063
.L3064:
	ldr	w20, [x19, 1632]
	ldr	w0, [x19, 1572]
	ubfx	x20, x20, 16, 3
	cmp	w20, w0
	beq	.L3065
	sub	w0, w0, #2
	cmp	w0, 1
	ccmp	w20, 2, 4, ls
	beq	.L3065
	cmp	w20, 1
	ccmp	w20, 4, 4, hi
	beq	.L3147
.L3065:
	cmp	w20, 2
	str	w20, [x19, 1572]
	beq	.L3068
	cmp	w20, 3
	beq	.L3069
	cmp	w20, 1
	beq	.L3148
	ldr	w0, [x19, 1568]
	cbz	w0, .L3072
	cmp	w20, 4
	ldr	w20, [x21, 2396]
	bne	.L3078
	cbnz	w20, .L3078
	ldr	w0, [x19, 320]
	cbnz	w0, .L3079
	mov	w0, 2
	str	w0, [x19, 320]
	b	.L3091
	.p2align 3
.L3063:
	add	x19, x22, 65536
	ldr	w0, [x19, 1668]
	ldr	w1, [x19, 1672]
	add	w0, w0, 1
	cmp	w0, w1
	csel	w0, w0, w1, ge
	str	w0, [x19, 1668]
	sub	w0, w0, w1
	ldr	x1, [x22]
	str	w0, [x1, 576]
	b	.L3064
	.p2align 3
.L3069:
	mov	x0, x22
	mov	w19, -1
	bl	ClearAllSlice
	add	x1, x22, 20480
	ldr	w4, [x22, 14948]
	add	x6, x1, 3072
	mov	w3, 23352
	movk	w3, 0x1, lsl 16
	mov	w2, 2
	strb	wzr, [x1, 3224]
	mov	w0, 7
	strb	w2, [x1, 3225]
	mov	w2, 262144
	str	w0, [x1, 3236]
	mov	w0, 32
	str	w4, [x1, 3232]
	str	w3, [x1, 3240]
	stp	w20, w19, [x6, 176]
	stp	wzr, wzr, [x6, 184]
	strb	w0, [x1, 3226]
	mov	x0, x22
	str	w2, [x1, 3264]
	bl	ClearDPB
	mov	w0, w19
.L3140:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3148:
	ldr	w20, [x21, 2396]
	cmp	w20, 2
	bne	.L3074
	ldr	w0, [x21, 2376]
	cbz	w0, .L3075
.L3074:
	ldr	w0, [x19, 1568]
	cbz	w0, .L3072
.L3078:
	cmp	w20, 2
	beq	.L3149
	cmp	w20, 1
	bne	.L3091
	str	w20, [x19, 320]
.L3091:
	ldr	w2, [x19, 1608]
	mov	w0, 2
	ldr	x1, .LC810
	ldrb	w3, [x21, 1707]
	sub	w2, w2, #1
	bl	dprint_vfmw
	ldr	w0, [x21, 2420]
	str	w0, [x19, 1108]
	mov	w0, 1
	strb	w0, [x19, 370]
	ldr	w2, [x19, 1568]
	ldr	w1, [x21, 2424]
	ldr	w0, [x19, 1608]
	str	w1, [x19, 1104]
	str	w2, [x19, 1308]
	cbz	w0, .L3082
	ldr	w4, [x21, 2396]
	cbnz	w4, .L3083
	ldr	x0, .LC805
	ldr	x5, [x0]
	cbz	x5, .L3084
	ldr	x1, [x19, 1312]
	cbz	x1, .L3085
	mov	w2, 0
	.p2align 2
.L3086:
	ldp	w3, w0, [x1, 8]
	ldr	x1, [x1, 4056]
	add	w0, w3, w0
	add	w0, w0, 7
	add	w2, w2, w0, lsr 3
	mov	w4, w2
	cbnz	x1, .L3086
.L3085:
	add	x2, x29, 64
	ldr	w0, [x19, 1644]
	mov	w1, 20
	mov	w3, 4
	str	w4, [x2, -8]!
	blr	x5
	ldr	x1, [x22]
.L3087:
	add	x2, x19, 368
	str	x2, [x22, 616]
	ldr	w0, [x1, 880]
	cmp	w0, 1
	beq	.L3150
	cmp	w0, 2
	beq	.L3151
.L3090:
	ldr	w2, [x1, 592]
	mov	w0, 0
	strb	w2, [x19, 372]
	ldr	w2, [x1, 600]
	str	w2, [x19, 376]
	ldr	w2, [x1, 604]
	str	w2, [x19, 380]
	ldr	w2, [x1, 596]
	strb	w2, [x19, 373]
	ldr	w1, [x1, 644]
	strb	w1, [x19, 384]
	ldr	w4, [x21, 2436]
	ldr	x3, [x21, 2352]
	ldr	w1, [x21, 2432]
	str	w4, [x21, 2432]
	sub	w1, w1, w4
	ldr	w2, [x3, 256]
	add	w2, w2, w1
	str	w2, [x3, 256]
	ldr	w2, [x21, 1960]
	add	w1, w2, w1
	str	w1, [x21, 1960]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3068:
	ldr	w0, [x21, 2396]
	cbnz	w0, .L3075
	ldr	w0, [x19, 1568]
	cbz	w0, .L3072
	ldr	x0, [x19, 1560]
	ldr	w0, [x0, 48]
	cbz	w0, .L3091
	mov	w1, 1
	mov	x0, x22
	strb	w1, [x21, 1711]
	mov	w19, -1
	bl	ClearAllSlice
	add	x2, x22, 20480
	mov	w3, 23352
	movk	w3, 0x1, lsl 16
	mov	w0, 7
	ldr	w4, [x22, 14948]
	ldr	x1, .LC804
	str	w0, [x2, 3236]
	mov	w0, 3
	str	w3, [x2, 3240]
	mov	w3, 32
	str	w0, [x2, 3248]
	mov	w0, 0
	strb	w3, [x2, 3226]
	mov	w3, 262144
	strb	wzr, [x2, 3224]
	strb	w20, [x2, 3225]
	str	w4, [x2, 3232]
	str	w19, [x2, 3252]
	str	wzr, [x2, 3256]
	str	wzr, [x2, 3260]
	str	w3, [x2, 3264]
	bl	dprint_vfmw
	mov	w0, w19
	b	.L3140
	.p2align 3
.L3072:
	mov	x0, x22
	mov	w20, -1
	bl	ClearAllSlice
	add	x0, x22, 20480
	mov	w5, 7
	ldr	w7, [x22, 14948]
	mov	w1, 23352
	ldr	x2, .LC805
	movk	w1, 0x1, lsl 16
	str	w5, [x0, 3236]
	add	x5, x0, 3072
	str	w1, [x0, 3240]
	mov	w6, 2
	strb	wzr, [x0, 3224]
	mov	w3, 32
	strb	w6, [x0, 3225]
	mov	w1, 262144
	strb	w3, [x0, 3226]
	str	w7, [x0, 3232]
	ldr	x4, [x2]
	mov	w2, 3
	stp	wzr, wzr, [x5, 184]
	stp	w2, w20, [x5, 176]
	str	w1, [x0, 3264]
	cbz	x4, .L3143
	ldr	w0, [x19, 1644]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3149:
	ldr	w0, [x19, 320]
	cmp	w0, 2
	bne	.L3091
	ldr	x0, [x22]
	ldr	w0, [x0, 24]
	cbnz	w0, .L3091
	ldr	x0, .LC806
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L3091
	ldr	x1, .LC808
	mov	w0, 1
	ldr	w3, [x21, 2376]
	ldr	w2, [x21, 2380]
	bl	dprint_vfmw
	mov	x0, x22
	bl	ClearAllSlice
	ldr	x3, .LC805
	add	x0, x22, 20480
	mov	w1, 23352
	ldr	w2, [x22, 14948]
	movk	w1, 0x1, lsl 16
	mov	w6, 7
	ldr	x4, [x3]
	mov	w5, 32
	mov	w3, 3
	str	w2, [x0, 3232]
	str	w1, [x0, 3240]
	mov	w2, -1
	mov	w1, 262144
	strb	wzr, [x0, 3224]
	strb	w20, [x0, 3225]
	strb	w5, [x0, 3226]
	str	w6, [x0, 3236]
	str	w3, [x0, 3248]
	str	wzr, [x0, 3256]
	str	wzr, [x0, 3260]
	str	w2, [x0, 3252]
	str	w1, [x0, 3264]
	cbz	x4, .L3081
	ldr	w0, [x19, 1644]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
.L3081:
	ldr	x1, [x21, 2352]
	mov	w2, 0
	ldr	w0, [x19, 1644]
	ldr	w1, [x1, 648]
	bl	FSP_SetDisplay
	.p2align 2
.L3143:
	mov	w0, -1
	b	.L3140
	.p2align 3
.L3082:
	ldr	x1, [x22]
	b	.L3090
	.p2align 3
.L3083:
	add	x0, x22, 24576
	ldr	w0, [x0, 3708]
	cbnz	w0, .L3084
	ldr	x1, [x22]
	ldr	w0, [x1, 24]
	cmp	w0, 2
	beq	.L3087
	ldr	x0, .LC805
	ldr	x4, [x0]
	cbz	x4, .L3088
	ldr	w0, [x19, 1644]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
.L3088:
	mov	x0, x22
.L3145:
	bl	ClearAllSlice
	add	x1, x22, 20480
	ldr	w8, [x22, 14948]
	mov	w7, 23352
	mov	w6, 2
	movk	w7, 0x1, lsl 16
	mov	w0, -1
	mov	w5, 7
	mov	w4, 32
	mov	w3, 3
	mov	w2, 262144
	strb	wzr, [x1, 3224]
	strb	w6, [x1, 3225]
	str	w8, [x1, 3232]
	str	w7, [x1, 3240]
	b	.L3142
	.p2align 3
.L3084:
	ldr	x1, [x22]
	b	.L3087
	.p2align 3
.L3150:
	cbz	x2, .L3090
	ldr	w20, [x21, 2396]
	cmp	w20, 2
	bne	.L3090
	str	xzr, [x22, 616]
	mov	w2, 0
	ldr	x1, [x21, 2352]
	ldr	w0, [x19, 1644]
	ldr	w1, [x1, 648]
	bl	FSP_SetDisplay
	mov	x0, x22
	b	.L3144
	.p2align 3
.L3151:
	ldr	w0, [x1, 884]
	cmp	w0, wzr
	ccmp	x2, xzr, 4, gt
	beq	.L3090
	ldr	w20, [x21, 2396]
	cmp	w20, 2
	bne	.L3090
	str	xzr, [x22, 616]
	mov	w2, 0
	ldr	x1, [x21, 2352]
	ldr	w0, [x19, 1644]
	ldr	w1, [x1, 648]
	bl	FSP_SetDisplay
	ldr	x2, [x22]
	mov	x0, x22
	ldr	w1, [x2, 884]
	sub	w1, w1, #1
	str	w1, [x2, 884]
.L3144:
	bl	ClearAllSlice
	add	x1, x22, 20480
	ldr	w7, [x22, 14948]
	mov	w6, 23352
	mov	w0, -1
	movk	w6, 0x1, lsl 16
	mov	w5, 7
	mov	w4, 32
	mov	w3, 3
	mov	w2, 262144
	strb	wzr, [x1, 3224]
	strb	w20, [x1, 3225]
	str	w7, [x1, 3232]
	str	w6, [x1, 3240]
	.p2align 2
.L3142:
	strb	w4, [x1, 3226]
	add	x4, x1, 3072
	str	w5, [x1, 3236]
	stp	w3, w0, [x4, 176]
	stp	wzr, wzr, [x4, 184]
	str	w2, [x1, 3264]
	b	.L3140
	.p2align 3
.L3079:
	mov	w0, 1
	str	w0, [x19, 320]
	b	.L3091
.L3147:
	ldr	x1, .LC802
	mov	w2, w20
	mov	w0, 2
	mov	w21, -1
	bl	dprint_vfmw
	str	w20, [x19, 1572]
	mov	x0, x22
	bl	ClearAllSlice
	add	x1, x22, 20480
	ldr	w4, [x22, 14948]
	add	x7, x1, 3072
	mov	w2, 2
	mov	w3, 23352
	mov	w0, 7
	strb	w2, [x1, 3225]
	movk	w3, 0x1, lsl 16
	str	w0, [x1, 3236]
	mov	w2, 32
	strb	wzr, [x1, 3224]
	mov	w0, 3
	strb	w2, [x1, 3226]
	mov	w2, 262144
	str	w4, [x1, 3232]
	str	w3, [x1, 3240]
	stp	w21, wzr, [x7, 180]
	stp	wzr, w2, [x7, 188]
	str	w0, [x1, 3248]
	mov	x0, x22
	bl	ClearDPB
	mov	w0, w21
	b	.L3140
.L3075:
	mov	w1, 1
	mov	x0, x22
	strb	w1, [x21, 1711]
	b	.L3145
	.size	DecVDM, .-DecVDM
	.align	3
.LC802:
	.xword	.LC801
	.align	3
.LC804:
	.xword	.LC803
	.align	3
.LC805:
	.xword	g_event_report
	.align	3
.LC806:
	.xword	g_allow_B_before_P
	.align	3
.LC808:
	.xword	.LC807
	.align	3
.LC810:
	.xword	.LC809
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_FlushDecoder
	.type	H264_FlushDecoder, %function
H264_FlushDecoder:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, 1
	bl	_mcount
	add	x1, x19, 20480
	mov	w2, 1
	mov	x0, x19
	strb	w2, [x1, 1589]
	str	wzr, [x1, 1632]
	str	w20, [x19, 624]
	bl	DecVDM
	cbz	w0, .L3152
	ldr	x1, .LC812
	mov	w0, w20
	bl	dprint_vfmw
.L3152:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	H264_FlushDecoder, .-H264_FlushDecoder
	.align	3
.LC812:
	.xword	.LC811
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_VES_Splitter
	.type	H264_VES_Splitter, %function
H264_VES_Splitter:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	add	x19, x21, 12288
	mov	w20, w1
	mov	w23, w2
	mov	w24, w3
	add	x19, x19, 2600
	bl	_mcount
	add	x22, x21, 61440
	mov	w1, 24
	mov	x0, x19
	str	xzr, [x29, 72]
	bl	BsSkip
	ldr	x0, [x22, 2152]
	str	x0, [x29, 72]
	cbz	w20, .L3159
	cmp	w20, 1
	beq	.L3160
	ldr	x1, .LC826
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
.L3244:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L3160:
	mov	w1, 16
	mov	x0, x19
	cbnz	w23, .L3173
	bl	BsGet
	mov	w20, w0
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	mov	w1, 31745
	cmp	w20, w1
	bne	.L3264
	and	w0, w0, 31
	cmp	w0, 25
	ccmp	w24, 1, 0, eq
	bne	.L3257
	ldr	x19, .LC813
	ldr	x4, [x19]
	cbz	x4, .L3177
	add	x0, x21, 65536
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	ldr	w0, [x0, 1644]
	blr	x4
.L3177:
	mov	x0, x21
	bl	DecVDM
	cbz	w0, .L3257
	b	.L3254
	.p2align 3
.L3159:
	cbnz	w23, .L3161
	mov	w1, 16
	mov	x0, x19
	mov	w23, 31745
	bl	BsGet
	mov	w20, w0
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	cmp	w20, w23
	beq	.L3162
	mov	w1, 24
	mov	x0, x19
	and	w20, w20, -513
	bl	BsBack
	mov	w1, 24
	mov	x0, x19
	bl	BsBack
	cmp	w20, w23
	bne	.L3247
.L3257:
	ldr	x1, [x21, 632]
	cbz	x1, .L3248
	add	x0, x21, 65536
	ldr	w0, [x0, 1644]
	bl	ReleaseNAL
	str	xzr, [x21, 632]
.L3248:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	mov	w0, -1
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L3173:
	bl	BsGet
	mov	w20, w0
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	mov	w1, 31745
	cmp	w20, w1
	beq	.L3181
	mov	w1, 24
	mov	x0, x19
	bl	BsBack
	mov	w1, 24
	mov	x0, x19
	bl	BsBack
	mov	w0, 32257
	cmp	w20, w0
	beq	.L3265
.L3247:
	mov	w0, 0
.L3267:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L3162:
	and	w0, w0, 31
	cmp	w0, 25
	bne	.L3257
	ldr	x19, .LC813
	ldr	x4, [x19]
	cbz	x4, .L3165
	add	x0, x21, 65536
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	ldr	w0, [x0, 1644]
	blr	x4
.L3165:
	mov	x0, x21
	bl	DecVDM
	cbz	w0, .L3266
.L3254:
	ldr	x4, [x19]
	cbz	x4, .L3248
	add	x21, x21, 65536
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	ldr	w0, [x21, 1644]
	blr	x4
	mov	w0, -1
	b	.L3244
	.p2align 3
.L3161:
	mov	w1, 24
	mov	x0, x19
	bl	BsBack
	mov	w0, 0
	b	.L3267
	.p2align 3
.L3264:
	mov	w1, 32
	mov	x0, x19
	bl	BsBack
	ldr	x0, [x21, 632]
	mov	w2, 32257
	mov	w1, 16
	cmp	w20, w2
	str	w1, [x0, 72]
	beq	.L3268
	mov	w1, 8
	mov	x0, x19
	bl	BsSkip
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	and	w0, w0, 31
	cmp	w0, 11
	bne	.L3257
	mov	x0, x21
	bl	H264_IsEosNal
	uxtb	w0, w0
	cmp	w0, 1
	bne	.L3257
	mov	w1, 32
	mov	x0, x19
	bl	BsBack
	mov	w1, 32
	mov	x0, x19
	bl	BsBack
	mov	w1, 32
	mov	x0, x19
	bl	BsBack
	mov	w0, 3
	b	.L3244
	.p2align 3
.L3181:
	and	w0, w0, 31
	cmp	w0, 25
	bne	.L3247
	ldr	x19, .LC813
	ldr	x4, [x19]
	cbz	x4, .L3183
	add	x0, x21, 65536
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	ldr	w0, [x0, 1644]
	blr	x4
.L3183:
	mov	x0, x21
	bl	DecVDM
	cbnz	w0, .L3254
	ldr	x0, [x21, 632]
	add	x23, x22, 2136
	add	x20, x21, 65536
	ldr	w1, [x23, 8]
	add	x2, x29, 72
	ldr	w4, [x0, 16]
	ldr	w3, [x0, 48]
	ldr	w0, [x20, 1644]
	add	w3, w4, w3
	sub	w3, w3, #1
	bl	MetadataMapToSec
	cbnz	w0, .L3269
	ldr	x19, .LC817
	mov	x2, 5
	ldr	x1, .LC818
	ldr	x0, [x29, 72]
	ldr	x3, [x19, 104]
	blr	x3
	ldr	x1, [x21, 632]
	ldr	x0, [x29, 72]
	ldr	x3, [x19, 104]
	ldr	w2, [x1, 16]
	add	x0, x0, 5
	sub	w2, w2, #6
	str	w2, [x23, 4]
	ldr	x1, [x1, 8]
	add	x1, x1, 6
	blr	x3
	ldr	w0, [x23, 4]
	add	w0, w0, 5
	str	w0, [x23, 4]
	ldr	x1, [x21, 632]
	ldr	w2, [x1, 48]
	cbnz	w2, .L3270
.L3186:
	ldr	x23, .LC819
	ldr	w0, [x20, 1644]
	ldr	x1, [x23, w0, sxtw 3]
	cbz	x1, .L3187
	ldr	x1, [x19, 32]
	mov	w0, 0
	blr	x1
	ldrsw	x2, [x20, 1644]
	ldr	w1, [x22, 2140]
	ldr	x3, [x19, 88]
	ldr	x2, [x23, x2, lsl 3]
	ldr	x0, [x29, 72]
	blr	x3
	ldr	x1, [x19, 24]
	mov	w0, 0
	blr	x1
	ldr	w0, [x20, 1644]
.L3187:
	ldr	x1, [x29, 72]
	bl	MetadataUnMapToSec
	cbnz	w0, .L3271
.L3188:
	ldr	x1, [x21, 632]
	cbz	x1, .L3248
	ldr	w0, [x20, 1644]
	bl	ReleaseNAL
	str	xzr, [x21, 632]
	mov	w0, -1
	b	.L3244
	.p2align 3
.L3265:
	ldr	x2, .LC814
	mov	w3, 12974
	ldr	x1, .LC824
	mov	w0, 0
	add	x2, x2, 272
	bl	dprint_vfmw
	b	.L3257
	.p2align 3
.L3268:
	add	x22, x21, 65536
	ldr	x20, .LC822
	ldrsw	x0, [x22, 1644]
	ldr	x0, [x20, x0, lsl 3]
	cbz	x0, .L3247
	ldr	x19, .LC817
	mov	w0, 0
	ldr	x1, [x19, 32]
	blr	x1
	ldr	x0, [x21, 632]
	ldrsw	x2, [x22, 1644]
	ldr	x3, [x19, 88]
	ldr	w1, [x0, 16]
	ldr	x2, [x20, x2, lsl 3]
	ldr	x0, [x0, 8]
	blr	x3
	ldr	x1, [x19, 24]
	mov	w0, 0
	blr	x1
	mov	w0, 0
	b	.L3244
	.p2align 3
.L3266:
	ldr	x0, [x21, 632]
	add	x23, x22, 2136
	add	x20, x21, 65536
	ldr	w1, [x23, 8]
	add	x2, x29, 72
	ldr	w4, [x0, 16]
	ldr	w3, [x0, 48]
	ldr	w0, [x20, 1644]
	add	w3, w4, w3
	sub	w3, w3, #1
	bl	MetadataMapToSec
	cbnz	w0, .L3272
	ldr	x19, .LC817
	mov	x2, 5
	ldr	x1, .LC818
	ldr	x0, [x29, 72]
	ldr	x3, [x19, 104]
	blr	x3
	ldr	x1, [x21, 632]
	ldr	x0, [x29, 72]
	ldr	x3, [x19, 104]
	ldr	w2, [x1, 16]
	add	x0, x0, 5
	sub	w2, w2, #6
	str	w2, [x23, 4]
	ldr	x1, [x1, 8]
	add	x1, x1, 6
	blr	x3
	ldr	w0, [x23, 4]
	add	w0, w0, 5
	str	w0, [x23, 4]
	ldr	x1, [x21, 632]
	ldr	w2, [x1, 48]
	cbnz	w2, .L3273
.L3169:
	ldr	x23, .LC819
	ldr	w0, [x20, 1644]
	ldr	x1, [x23, w0, sxtw 3]
	cbz	x1, .L3170
	ldr	x1, [x19, 32]
	mov	w0, 0
	blr	x1
	ldrsw	x2, [x20, 1644]
	ldr	w1, [x22, 2140]
	ldr	x3, [x19, 88]
	ldr	x2, [x23, x2, lsl 3]
	ldr	x0, [x29, 72]
	blr	x3
	ldr	x1, [x19, 24]
	mov	w0, 0
	blr	x1
	ldr	w0, [x20, 1644]
.L3170:
	ldr	x1, [x29, 72]
	bl	MetadataUnMapToSec
	cbz	w0, .L3188
	ldr	x2, .LC814
	mov	w3, 12803
	ldr	x1, .LC821
	mov	w0, 0
	add	x2, x2, 272
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3244
	.p2align 3
.L3273:
	ldr	x4, [x29, 72]
	uxtw	x2, w2
	ldr	x1, [x1, 40]
	ldr	x3, [x19, 104]
	add	x0, x4, x0, uxtw
	blr	x3
	ldr	x1, [x21, 632]
	ldr	w0, [x23, 4]
	ldr	w1, [x1, 48]
	add	w0, w1, w0
	str	w0, [x23, 4]
	b	.L3169
.L3270:
	ldr	x4, [x29, 72]
	uxtw	x2, w2
	ldr	x1, [x1, 40]
	ldr	x3, [x19, 104]
	add	x0, x4, x0, uxtw
	blr	x3
	ldr	x1, [x21, 632]
	ldr	w0, [x23, 4]
	ldr	w1, [x1, 48]
	add	w0, w1, w0
	str	w0, [x23, 4]
	b	.L3186
.L3272:
	ldr	x2, .LC814
	mov	w3, 12769
	ldr	x1, .LC816
	mov	w0, 0
	add	x2, x2, 272
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3244
.L3269:
	ldr	x2, .LC814
	mov	w3, 12932
	ldr	x1, .LC816
	mov	w0, 0
	add	x2, x2, 272
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3244
.L3271:
	ldr	x2, .LC814
	mov	w3, 12962
	ldr	x1, .LC821
	mov	w0, 0
	add	x2, x2, 272
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3244
	.size	H264_VES_Splitter, .-H264_VES_Splitter
	.align	3
.LC813:
	.xword	g_event_report
	.align	3
.LC814:
	.xword	.LANCHOR2
	.align	3
.LC816:
	.xword	.LC815
	.align	3
.LC817:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC818:
	.xword	g_RpuStartCode
	.align	3
.LC819:
	.xword	vfmw_save_metadata_file
	.align	3
.LC821:
	.xword	.LC820
	.align	3
.LC822:
	.xword	vfmw_save_el_file
	.align	3
.LC824:
	.xword	.LC823
	.align	3
.LC826:
	.xword	.LC825
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReceivePacket
	.type	ReceivePacket, %function
ReceivePacket:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	add	x21, x20, 65536
	bl	_mcount
	ldr	x1, .LC828
	mov	w0, 7
	ldp	w3, w4, [x19, 16]
	ldr	x2, [x19, 8]
	bl	dprint_vfmw
	str	wzr, [x21, 1676]
	ldr	x0, [x20]
	ldr	w1, [x0, 840]
	cmp	w1, 1
	beq	.L3344
.L3275:
	ldr	x0, [x20, 632]
	cbz	x0, .L3280
	ldrb	w1, [x19]
	cmp	w1, 1
	beq	.L3345
.L3278:
	ldr	x1, .LC830
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x20, 632]
	cbz	x1, .L3280
	ldr	w0, [x21, 1644]
	bl	ReleaseNAL
	str	xzr, [x20, 632]
.L3280:
	ldr	w0, [x19, 20]
	cmp	w0, wzr
	ble	.L3282
	ldr	x0, [x19, 8]
	cbz	x0, .L3282
	ldr	w0, [x19, 16]
	cbz	w0, .L3282
	ldrb	w0, [x20, 641]
	cbz	w0, .L3302
	add	x1, x20, 745
	mov	x0, 1
	b	.L3285
	.p2align 3
.L3284:
	add	w0, w0, 1
	cmp	w0, 137
	beq	.L3300
.L3285:
	ldrb	w2, [x1]
	add	x1, x1, 104
	cbnz	w2, .L3284
	mov	w2, w0
.L3283:
	lsl	x1, x0, 3
	mov	w3, 1
	sub	x1, x1, x0
	cmn	w2, #1
	lsl	x1, x1, x3
	sub	x0, x1, x0
	add	x0, x20, x0, lsl 3
	strb	w3, [x0, 641]
	beq	.L3300
	sxtw	x1, w2
	mov	w2, 1
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 1
	sub	x0, x0, x1
	lsl	x0, x0, 3
	add	x1, x0, 640
	add	x0, x20, x0
	add	x1, x20, x1
	str	x1, [x20, 632]
	ldr	x1, [x19, 8]
	str	x1, [x0, 648]
	ldr	w1, [x19, 20]
	str	w1, [x0, 656]
	ldr	w1, [x19, 16]
	str	w1, [x0, 660]
	ldr	x0, [x20, 632]
	str	wzr, [x0, 28]
	ldr	x0, [x20, 632]
	ldr	w1, [x19, 24]
	str	w1, [x0, 36]
	ldr	x0, [x20, 632]
	ldr	x1, [x19, 32]
	str	x1, [x0, 96]
	ldr	x0, [x20, 632]
	str	w2, [x0, 76]
	ldr	x0, [x20, 632]
	strb	wzr, [x0]
	ldr	x0, [x20, 632]
	ldrb	w1, [x19]
	strb	w1, [x0, 4]
	ldr	x0, [x20]
	ldrb	w0, [x0, 912]
	cmp	w0, w2
	beq	.L3341
	add	x0, x20, 61440
	ldr	w2, [x19, 20]
	ldr	w1, [x0, 2432]
	ldr	w3, [x0, 2436]
	add	w2, w1, w2
	str	w2, [x0, 2432]
	ldr	w1, [x19, 20]
	add	w1, w3, w1
	str	w1, [x0, 2436]
	ldr	x0, [x20, 632]
	b	.L3291
	.p2align 3
.L3345:
	ldr	w2, [x0, 76]
	cmp	w2, 1
	bhi	.L3278
	ldrb	w2, [x0, 4]
	cmp	w2, 1
	bne	.L3279
	b	.L3278
	.p2align 3
.L3344:
	ldr	w0, [x0, 888]
	cbz	w0, .L3275
	ldr	x0, [x20, 632]
	cbz	x0, .L3280
	ldrb	w1, [x19]
.L3279:
	strb	w1, [x0, 4]
	ldr	x0, [x20]
	ldr	w1, [x0, 840]
	cmp	w1, 1
	beq	.L3346
.L3293:
	ldr	w0, [x19, 20]
	cmp	w0, wzr
	ble	.L3294
	ldr	x1, [x19, 8]
	cbz	x1, .L3294
	ldr	w0, [x19, 16]
	cbz	w0, .L3294
	ldr	x0, [x20, 632]
	ldr	w2, [x0, 76]
	cmp	w2, 1
	bls	.L3347
.L3295:
	mov	w1, 1
	strb	w1, [x0, 4]
	ldr	w1, [x19, 24]
	ldr	w0, [x21, 1644]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC833
	ldr	x4, [x0]
	cbz	x4, .L3341
	ldr	w0, [x21, 1644]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L3341:
	ldr	x0, [x20, 632]
.L3291:
	ldrb	w0, [x0, 4]
	ldp	x19, x20, [sp, 16]
	cmp	w0, wzr
	csetm	w0, eq
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3282:
	ldr	x1, .LC835
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x19, 24]
	ldr	w0, [x21, 1644]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC833
	ldr	x4, [x0]
	cbz	x4, .L3343
.L3342:
	ldr	w0, [x21, 1644]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L3343:
	mov	w0, -1
.L3350:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3294:
	ldr	x0, [x20, 632]
	b	.L3295
	.p2align 3
.L3346:
	ldr	w0, [x0, 888]
	cbnz	w0, .L3341
	b	.L3293
	.p2align 3
.L3347:
	ubfiz	x2, x2, 5, 32
	add	x0, x0, x2
	str	x1, [x0, 8]
	ldr	x1, [x20, 632]
	ldr	w2, [x19, 20]
	ldr	w0, [x1, 76]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 16]
	ldr	x1, [x20, 632]
	ldr	w2, [x19, 16]
	ldr	w0, [x1, 76]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 20]
	ldr	x1, [x20, 632]
	ldr	w0, [x1, 76]
	add	x0, x1, x0, lsl 5
	str	wzr, [x0, 28]
	ldr	x1, [x20, 632]
	ldr	w2, [x19, 24]
	ldr	w0, [x1, 76]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 36]
	ldr	x1, [x20, 632]
	ldr	w0, [x1, 76]
	add	w0, w0, 1
	str	w0, [x1, 76]
	ldr	x0, [x20]
	ldrb	w0, [x0, 912]
	cmp	w0, 1
	beq	.L3296
	add	x0, x20, 61440
	ldr	w2, [x19, 20]
	ldr	w1, [x0, 2432]
	ldr	w3, [x0, 2436]
	add	w2, w1, w2
	str	w2, [x0, 2432]
	ldr	w1, [x19, 20]
	add	w1, w3, w1
	str	w1, [x0, 2436]
.L3296:
	ldr	x0, [x20, 632]
	ldr	w1, [x0, 16]
	cmp	w1, 4095
	bls	.L3348
.L3297:
	mov	w1, 1
	str	w1, [x21, 1676]
	b	.L3291
	.p2align 3
.L3348:
	mov	x0, x20
	bl	CombinePacket.part.13
	ldr	x0, [x20, 632]
	b	.L3297
.L3300:
	ldr	x1, .LC832
	mov	w0, 0
	add	x22, x20, 12288
	add	x19, x20, 640
	add	x22, x22, 2600
	bl	dprint_vfmw
	b	.L3287
	.p2align 3
.L3286:
	add	x19, x19, 104
	cmp	x22, x19
	beq	.L3349
.L3287:
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	bne	.L3286
	ldr	w0, [x21, 1644]
	mov	x1, x19
	bl	ReleaseNAL
	b	.L3286
.L3349:
	mov	x0, x20
	mov	w19, -1
	bl	ClearAllSlice
	add	x1, x20, 20480
	mov	w0, 7
	ldr	w4, [x20, 14948]
	mov	w2, 2
	mov	w3, 23352
	str	w0, [x1, 3236]
	add	x0, x1, 3072
	strb	w2, [x1, 3225]
	movk	w3, 0x1, lsl 16
	str	w4, [x1, 3232]
	mov	w2, 32
	strb	wzr, [x1, 3224]
	strb	w2, [x1, 3226]
	mov	w2, 262144
	str	w3, [x1, 3240]
	stp	w19, wzr, [x0, 180]
	stp	wzr, w2, [x0, 188]
	mov	w0, 3
	str	w0, [x1, 3248]
	mov	x0, x20
	bl	ClearDPB
	ldr	x0, .LC833
	ldr	x4, [x0]
	cbnz	x4, .L3342
	mov	w0, -1
	b	.L3350
.L3302:
	mov	w2, 0
	mov	x0, 0
	b	.L3283
	.size	ReceivePacket, .-ReceivePacket
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
.LC833:
	.xword	g_event_report
	.align	3
.LC835:
	.xword	.LC834
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ClearAll
	.type	ClearAll, %function
ClearAll:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	w22, w1
	mov	x0, x30
	add	x1, x20, 20480
	mov	x23, x1
	add	x19, x20, 640
	stp	x1, x20, [x29, 96]
	bl	_mcount
	add	x21, x20, 65536
	ldr	x1, .LC837
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x20
	bl	ClearAllSlice
	mov	x1, x20
	mov	w2, 23352
	movk	w2, 0x1, lsl 16
	mov	w0, 7
	add	x20, x20, 12288
	ldr	w3, [x1, 14948]
	mov	w1, 2
	str	w3, [x23, 3232]
	add	x20, x20, 2600
	strb	w1, [x23, 3225]
	mov	w3, 32
	mov	w1, -1
	str	w0, [x23, 3236]
	str	w2, [x23, 3240]
	mov	w0, 262144
	mov	w2, 3
	strb	wzr, [x23, 3224]
	str	w1, [x23, 3252]
	str	wzr, [x23, 3256]
	str	wzr, [x23, 3260]
	strb	w3, [x23, 3226]
	str	w2, [x23, 3248]
	str	w0, [x23, 3264]
	b	.L3353
	.p2align 3
.L3352:
	add	x19, x19, 104
	cmp	x19, x20
	beq	.L3381
.L3353:
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	bne	.L3352
	ldr	w0, [x21, 1644]
	mov	x1, x19
	add	x19, x19, 104
	bl	ReleaseNAL
	cmp	x19, x20
	bne	.L3353
.L3381:
	ldr	x19, [x29, 104]
	mov	x0, x19
	bl	InitDPB
	cbz	w22, .L3354
	ldr	w0, [x21, 1644]
	add	x1, x19, 8
	bl	FSP_ClearNotInVoQueue
.L3355:
	ldr	x0, [x29, 104]
	mov	w20, 0
	mov	w26, -1
	mov	w22, 1
	add	x2, x0, 28672
	mov	w25, 17
	mov	w24, 16
	mov	w23, 2
	add	x28, x2, 552
	.p2align 2
.L3358:
	add	x0, x28, 512
	strb	wzr, [x28]
	strb	wzr, [x28, 1]
	add	x27, x28, 560
	strb	wzr, [x28, 2]
	add	x19, x28, 592
	strb	wzr, [x28, 4]
	strb	wzr, [x28, 696]
	strb	w22, [x28, 744]
	strb	w23, [x28, 792]
	str	w20, [x28, 164]
	stp	wzr, w26, [x0, 140]
	stp	wzr, wzr, [x0, 148]
	str	w22, [x28, 668]
	str	w25, [x28, 684]
	str	w24, [x28, 688]
	str	x28, [x28, 736]
	str	x28, [x28, 784]
	str	x28, [x28, 832]
.L3357:
	ldr	x0, [x27]
	mov	x1, x0
	cbz	x0, .L3356
	ldr	w0, [x21, 1644]
	bl	FreeUsdByDec
	str	xzr, [x27]
.L3356:
	add	x27, x27, 8
	cmp	x27, x19
	bne	.L3357
	add	w20, w20, 1
	add	x28, x28, 848
	cmp	w20, 40
	bne	.L3358
	ldr	x0, [x29, 104]
	add	x22, x0, 61440
	add	x19, x22, 2264
	add	x20, x22, 2296
.L3360:
	ldr	x0, [x19]
	mov	x1, x0
	cbz	x0, .L3359
	ldr	w0, [x21, 1644]
	bl	FreeUsdByDec
	str	xzr, [x19]
.L3359:
	add	x19, x19, 8
	cmp	x20, x19
	bne	.L3360
	ldr	w0, [x21, 328]
	mov	w20, 0
	cbz	w0, .L3364
	.p2align 2
.L3371:
	ldr	x0, [x29, 104]
	add	x19, x0, x20, uxtw 3
	add	w20, w20, 1
	add	x19, x19, 65536
	ldr	x0, [x19, 336]
	mov	x1, x0
	cbz	x0, .L3362
	ldr	w0, [x21, 1644]
	bl	FreeUsdByDec
	str	xzr, [x19, 336]
.L3362:
	ldr	w0, [x21, 328]
	cmp	w0, w20
	bhi	.L3371
.L3364:
	ldp	x19, x1, [x29, 96]
	str	wzr, [x21, 308]
	mov	x2, 1640
	add	x0, x1, 24576
	str	wzr, [x21, 316]
	str	wzr, [x21, 320]
	str	wzr, [x21, 328]
	str	wzr, [x21, 1568]
	str	wzr, [x21, 1576]
	str	wzr, [x21, 1620]
	str	wzr, [x21, 1628]
	str	wzr, [x21, 1648]
	str	xzr, [x1, 632]
	ldr	x1, .LC838
	strb	wzr, [x0, 1176]
	str	wzr, [x0, 3180]
	strb	wzr, [x19, 3268]
	ldr	x3, [x1, 96]
	mov	w1, 0
	strb	wzr, [x0, 1177]
	add	x0, x19, 1584
	strb	wzr, [x19, 3269]
	blr	x3
	mov	w1, 2
	mov	w0, 1
	strb	w1, [x19, 1584]
	strb	w0, [x19, 1589]
	mov	w0, 256
	strb	wzr, [x22, 1704]
	str	w0, [x22, 3184]
	mov	w0, 0
	strb	wzr, [x22, 3176]
	str	wzr, [x22, 3180]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L3354:
	ldr	x0, [x29, 104]
	add	x0, x0, 8
	bl	ResetVoQueue
	ldr	w0, [x21, 1644]
	bl	FSP_EmptyInstance
	b	.L3355
	.size	ClearAll, .-ClearAll
	.align	3
.LC837:
	.xword	.LC836
	.align	3
.LC838:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InsertFrmInDPB
	.type	InsertFrmInDPB, %function
InsertFrmInDPB:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x23, x0
	mov	x0, x30
	mov	w20, w1
	mov	x19, x2
	bl	_mcount
	cmp	w20, 15
	bhi	.L3477
	ldrb	w21, [x19, 3]
	cmp	w21, 1
	beq	.L3386
	cbz	w21, .L3387
	cmp	w21, 2
	bne	.L3478
	ldr	x0, [x19, 648]
	mov	w1, 3
	uxtw	x22, w20
	strb	w1, [x0, 696]
	ldrb	w0, [x19, 1]
	cbz	w0, .L3405
	add	x20, x23, x22, lsl 3
	ldr	x0, [x20, 27896]
	cbz	x0, .L3405
	strb	w21, [x0, 792]
	ldr	x0, [x20, 27896]
	ldr	x1, [x19, 648]
	str	x1, [x0, 832]
	ldr	x0, [x20, 27896]
	ldrb	w1, [x19, 4]
	strb	w1, [x0, 793]
	ldr	x0, [x20, 27896]
	ldrb	w1, [x19, 5]
	strb	w1, [x0, 794]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 688]
	str	w1, [x0, 804]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 692]
	str	w1, [x0, 812]
	ldr	x1, [x19, 648]
	ldr	x0, [x20, 27896]
	ldr	w1, [x1, 824]
	str	w1, [x0, 824]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 700]
	str	w1, [x0, 808]
	ldr	x0, [x20, 27896]
	ldr	w2, [x0, 760]
	ldr	w1, [x0, 808]
	add	w1, w2, w1
	str	w1, [x0, 680]
	str	w1, [x0, 712]
	ldr	x1, [x20, 27896]
	ldrb	w0, [x1]
	cbz	w0, .L3411
	ldrb	w0, [x19, 2]
.L3411:
	strb	w0, [x1]
	ldr	x1, [x20, 27896]
	ldrb	w0, [x1, 1]
	orr	w0, w0, 2
	strb	w0, [x1, 1]
	ldrb	w0, [x19, 7]
	ldr	x1, [x20, 27896]
	cmp	w0, 1
	beq	.L3479
	ldrb	w0, [x1, 3]
.L3413:
	strb	w0, [x1, 3]
	mov	x2, 632
	add	x1, x19, 16
	ldr	x3, [x20, 27896]
	add	x0, x3, 16
	ldr	x4, [x3, 600]
	str	x4, [x29, 104]
	ldp	w26, w25, [x3, 16]
	ldp	w24, w21, [x3, 24]
	ldr	x28, [x3, 608]
	ldr	x27, [x3, 616]
	bl	memcpy
	ldr	x0, [x19, 600]
	ldr	x4, [x29, 104]
	cmn	x0, #1
	ccmn	x4, #1, 4, eq
	beq	.L3414
	ldr	x0, [x20, 27896]
	str	x4, [x0, 600]
.L3414:
	ldr	x0, [x19, 608]
	ldr	x1, [x20, 27896]
	cmp	x0, x28
	csel	x0, x0, x28, ls
	str	x0, [x1, 608]
	ldr	x0, [x19, 616]
	ldr	x1, [x20, 27896]
	cmp	x0, x27
	csel	x0, x0, x27, ls
	str	x0, [x1, 616]
	ldr	w0, [x19, 16]
	ldr	x1, [x20, 27896]
	cmp	w0, w26
	csel	w0, w0, w26, ls
	str	w0, [x1, 16]
	ldr	w0, [x19, 20]
	ldr	x1, [x20, 27896]
	cmp	w0, w25
	csel	w0, w0, w25, ls
	str	w0, [x1, 20]
	ldr	w0, [x19, 24]
	ldr	x1, [x20, 27896]
	cmp	w0, w24
	csel	w0, w0, w24, ls
	str	w0, [x1, 24]
	ldr	w0, [x19, 28]
	ldr	x1, [x20, 27896]
	cmp	w0, w21
	csel	w0, w0, w21, ls
	str	w0, [x1, 28]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	beq	.L3415
	ldrb	w0, [x19, 5]
	cmp	w0, 1
	beq	.L3415
.L3416:
	ldr	x1, [x20, 27896]
	ldr	w0, [x1, 764]
	ldr	w2, [x1, 812]
	cmp	w0, w2
	csel	w0, w0, w2, cs
	str	w0, [x1, 676]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 676]
	str	w1, [x0, 664]
	ldr	x0, [x20, 27896]
	bl	CombineFldsToFrm
	ldr	x1, [x20, 27896]
	ldr	w0, [x1, 688]
	ldr	w1, [x1, 804]
	add	x0, x0, 4096
	add	x0, x0, 3028
	str	w1, [x23, x0, lsl 2]
	b	.L3404
	.p2align 3
.L3387:
	uxtw	x22, w20
	ldr	x1, [x19, 648]
	mov	w2, 3
	mov	w0, 3
	add	x20, x23, x22, lsl 3
	str	x1, [x20, 27896]
	ldrb	w3, [x19, 2]
	strb	w3, [x1]
	ldr	x1, [x20, 27896]
	strb	w2, [x1, 1]
	ldr	x2, [x19, 648]
	ldr	x1, [x20, 27896]
	ldrb	w2, [x2, 4]
	strb	w2, [x1, 4]
	ldr	x2, [x19, 648]
	ldr	x1, [x20, 27896]
	ldr	w2, [x2, 668]
	str	w2, [x1, 668]
	ldrb	w2, [x19, 4]
	ldr	x1, [x20, 27896]
	cbz	w2, .L3480
.L3389:
	strb	w0, [x1, 2]
	mov	x2, 632
	add	x1, x19, 16
	mov	w21, 3
	ldr	x0, [x20, 27896]
	ldr	w3, [x19, 724]
	str	w3, [x0, 684]
	ldr	x0, [x20, 27896]
	add	x0, x0, 16
	bl	memcpy
	ldr	x0, [x20, 27896]
	mov	w3, 2
	ldr	w1, [x19, 700]
	mov	w6, 1
	str	w1, [x0, 680]
	str	w1, [x0, 712]
	ldr	x0, [x20, 27896]
	ldr	x1, [x19, 648]
	str	x1, [x0, 736]
	str	x1, [x0, 784]
	str	x1, [x0, 832]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 668]
	str	w1, [x0, 660]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 664]
	str	w1, [x0, 652]
	ldr	x0, [x20, 27896]
	strb	wzr, [x0, 696]
	ldr	x0, [x20, 27896]
	ldrb	w1, [x19, 4]
	strb	w1, [x0, 697]
	ldr	x0, [x20, 27896]
	ldrb	w1, [x19, 5]
	strb	w1, [x0, 698]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 692]
	str	w1, [x0, 676]
	str	w1, [x0, 716]
	ldr	x0, [x20, 27896]
	ldrb	w1, [x19, 9]
	str	w1, [x0, 672]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 676]
	str	w1, [x0, 664]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 680]
	str	w1, [x0, 708]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 684]
	str	w1, [x0, 756]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 688]
	str	w1, [x0, 804]
	ldrb	w1, [x19, 7]
	ldr	x0, [x20, 27896]
	cmp	w1, 1
	csel	w21, wzr, w21, ne
	strb	w21, [x0, 3]
	ldr	x1, [x19, 648]
	ldr	x0, [x20, 27896]
	ldr	w1, [x1, 728]
	str	w1, [x0, 728]
	ldr	x0, [x20, 27896]
	ldr	w2, [x0, 712]
	ldr	x1, [x0, 736]
	ldrb	w5, [x0, 697]
	ldrb	w4, [x0, 698]
	strb	w3, [x0, 792]
	ldr	w3, [x0, 716]
	str	w2, [x0, 760]
	str	x1, [x0, 784]
	str	w2, [x0, 808]
	mov	w2, 0
	strb	w5, [x0, 745]
	strb	w4, [x0, 746]
	strb	w6, [x0, 744]
	strb	w5, [x0, 793]
	strb	w4, [x0, 794]
	str	w3, [x0, 764]
	str	w3, [x0, 812]
	str	x1, [x0, 832]
	mov	x0, x23
	ldr	x1, [x19, 648]
	bl	GetAPC
	cbnz	w0, .L3481
.L3404:
	add	x3, x23, x22, lsl 3
	add	x0, x23, 65536
	mov	w2, 1
	ldr	x1, [x3, 27896]
	ldr	w0, [x0, 1644]
	ldr	w1, [x1, 648]
	bl	FSP_SetRef
	mov	w0, 0
.L3384:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3478:
	ldr	x1, .LC844
	mov	w2, w21
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x23
	bl	ClearAll
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3386:
	ldr	x0, [x19, 648]
	mov	w1, 3
	uxtw	x22, w20
	strb	w1, [x0, 696]
	ldrb	w0, [x19, 1]
	cbz	w0, .L3392
	add	x20, x23, x22, lsl 3
	ldr	x0, [x20, 27896]
	cbz	x0, .L3392
	strb	w21, [x0, 744]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 692]
	str	w1, [x0, 764]
	ldr	x0, [x20, 27896]
	ldrb	w1, [x19, 4]
	strb	w1, [x0, 745]
	ldr	x0, [x20, 27896]
	ldrb	w1, [x19, 5]
	strb	w1, [x0, 746]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 684]
	str	w1, [x0, 756]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 692]
	str	w1, [x0, 764]
	ldr	x1, [x19, 648]
	ldr	x0, [x20, 27896]
	ldr	w1, [x1, 776]
	str	w1, [x0, 776]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 700]
	str	w1, [x0, 760]
	ldr	x0, [x20, 27896]
	ldr	w2, [x0, 760]
	ldr	w1, [x0, 808]
	add	w1, w2, w1
	str	w1, [x0, 680]
	str	w1, [x0, 712]
	ldr	x1, [x20, 27896]
	ldrb	w0, [x1]
	cbz	w0, .L3397
	ldrb	w0, [x19, 2]
.L3397:
	strb	w0, [x1]
	ldr	x1, [x20, 27896]
	ldrb	w0, [x1, 1]
	orr	w0, w0, 1
	strb	w0, [x1, 1]
	ldrb	w0, [x19, 7]
	ldr	x1, [x20, 27896]
	cmp	w0, 1
	beq	.L3482
	ldrb	w0, [x1, 3]
.L3399:
	strb	w0, [x1, 3]
	mov	x2, 632
	add	x1, x19, 16
	ldr	x3, [x20, 27896]
	add	x0, x3, 16
	ldr	x4, [x3, 600]
	str	x4, [x29, 104]
	ldp	w26, w25, [x3, 16]
	ldp	w24, w21, [x3, 24]
	ldr	x28, [x3, 608]
	ldr	x27, [x3, 616]
	bl	memcpy
	ldr	x0, [x19, 600]
	ldr	x4, [x29, 104]
	cmn	x0, #1
	ccmn	x4, #1, 4, eq
	beq	.L3400
	ldr	x0, [x20, 27896]
	str	x4, [x0, 600]
.L3400:
	ldr	x0, [x19, 608]
	ldr	x1, [x20, 27896]
	cmp	x0, x28
	csel	x0, x0, x28, ls
	str	x0, [x1, 608]
	ldr	x0, [x19, 616]
	ldr	x1, [x20, 27896]
	cmp	x0, x27
	csel	x0, x0, x27, ls
	str	x0, [x1, 616]
	ldr	w0, [x19, 16]
	ldr	x1, [x20, 27896]
	cmp	w0, w26
	csel	w0, w0, w26, ls
	str	w0, [x1, 16]
	ldr	w0, [x19, 20]
	ldr	x1, [x20, 27896]
	cmp	w0, w25
	csel	w0, w0, w25, ls
	str	w0, [x1, 20]
	ldr	w0, [x19, 24]
	ldr	x1, [x20, 27896]
	cmp	w0, w24
	csel	w0, w0, w24, ls
	str	w0, [x1, 24]
	ldr	w0, [x19, 28]
	ldr	x1, [x20, 27896]
	cmp	w0, w21
	csel	w0, w0, w21, ls
	str	w0, [x1, 28]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	beq	.L3401
	ldrb	w0, [x19, 5]
	cmp	w0, 1
	beq	.L3401
.L3402:
	ldr	x1, [x20, 27896]
	ldr	w0, [x1, 764]
	ldr	w2, [x1, 812]
	cmp	w0, w2
	csel	w0, w0, w2, cs
	str	w0, [x1, 676]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 676]
	str	w1, [x0, 664]
	ldr	x0, [x20, 27896]
	bl	CombineFldsToFrm
	ldr	x1, [x20, 27896]
	ldr	w0, [x1, 688]
	ldr	w1, [x1, 756]
	add	x0, x0, 4096
	add	x0, x0, 3012
	str	w1, [x23, x0, lsl 2]
	b	.L3404
	.p2align 3
.L3392:
	add	x20, x23, x22, lsl 3
	ldr	x0, [x19, 648]
	mov	w1, 1
	str	x0, [x20, 27896]
	strb	w1, [x0, 744]
	ldr	x0, [x20, 27896]
	ldr	x2, [x19, 648]
	str	x2, [x0, 784]
	ldr	x0, [x20, 27896]
	ldrb	w2, [x19, 4]
	strb	w2, [x0, 745]
	ldr	x0, [x20, 27896]
	ldrb	w2, [x19, 5]
	strb	w2, [x0, 746]
	ldr	x0, [x20, 27896]
	ldr	w2, [x19, 684]
	str	w2, [x0, 756]
	ldr	x0, [x20, 27896]
	ldr	w2, [x19, 692]
	str	w2, [x0, 764]
	ldr	x2, [x19, 648]
	ldr	x0, [x20, 27896]
	ldr	w2, [x2, 776]
	str	w2, [x0, 776]
	ldr	x0, [x20, 27896]
	ldr	w2, [x19, 700]
	str	w2, [x0, 760]
	ldr	x0, [x20, 27896]
	ldr	w2, [x0, 760]
	str	w2, [x0, 680]
	str	w2, [x0, 712]
	ldr	x0, [x20, 27896]
	ldrb	w2, [x19, 2]
	strb	w2, [x0]
	ldr	x0, [x20, 27896]
	strb	w1, [x0, 1]
	ldr	x1, [x19, 648]
	ldr	x0, [x20, 27896]
	ldrb	w1, [x1, 4]
	strb	w1, [x0, 4]
	ldr	x1, [x19, 648]
	ldr	x0, [x20, 27896]
	ldr	w1, [x1, 668]
	str	w1, [x0, 668]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	beq	.L3394
	ldrb	w0, [x19, 5]
	cmp	w0, 1
	beq	.L3394
.L3395:
	ldr	x0, [x20, 27896]
	mov	x2, 632
	add	x1, x19, 16
	str	wzr, [x0, 672]
	ldr	x0, [x20, 27896]
	add	x0, x0, 16
	bl	memcpy
	ldr	x1, [x20, 27896]
	mov	w2, 1
	ldr	w3, [x19, 724]
	mov	x0, x23
	str	w3, [x1, 684]
	ldr	x1, [x20, 27896]
	ldr	w3, [x19, 664]
	str	w3, [x1, 652]
	ldr	x1, [x20, 27896]
	ldr	w3, [x19, 676]
	str	w3, [x1, 664]
	ldr	x1, [x20, 27896]
	ldr	w3, [x19, 692]
	str	w3, [x1, 676]
	ldrb	w3, [x19, 7]
	ldr	x1, [x20, 27896]
	cmp	w3, w2
	cset	w3, eq
	strb	w3, [x1, 3]
	ldr	x1, [x19, 648]
	bl	GetAPC
	cbz	w0, .L3404
	ldr	x1, .LC842
	mov	w3, w0
	mov	w2, 2374
	b	.L3475
	.p2align 3
.L3405:
	add	x20, x23, x22, lsl 3
	ldr	x0, [x19, 648]
	mov	w1, 2
	str	x0, [x20, 27896]
	strb	w1, [x0, 792]
	ldr	x0, [x20, 27896]
	ldr	x2, [x19, 648]
	str	x2, [x0, 832]
	ldr	x0, [x20, 27896]
	ldrb	w2, [x19, 4]
	strb	w2, [x0, 793]
	ldr	x0, [x20, 27896]
	ldrb	w2, [x19, 5]
	strb	w2, [x0, 794]
	ldr	x0, [x20, 27896]
	ldr	w2, [x19, 688]
	str	w2, [x0, 804]
	ldr	x0, [x20, 27896]
	ldr	w2, [x19, 692]
	str	w2, [x0, 812]
	ldr	x2, [x19, 648]
	ldr	x0, [x20, 27896]
	ldr	w2, [x2, 824]
	str	w2, [x0, 824]
	ldr	x0, [x20, 27896]
	ldr	w2, [x19, 700]
	str	w2, [x0, 808]
	ldr	x0, [x20, 27896]
	ldr	w2, [x0, 760]
	str	w2, [x0, 680]
	str	w2, [x0, 712]
	ldr	x0, [x20, 27896]
	ldrb	w2, [x19, 2]
	strb	w2, [x0]
	ldr	x0, [x20, 27896]
	strb	w1, [x0, 1]
	ldr	x1, [x19, 648]
	ldr	x0, [x20, 27896]
	ldrb	w1, [x1, 4]
	strb	w1, [x0, 4]
	ldr	x1, [x19, 648]
	ldr	x0, [x20, 27896]
	ldr	w1, [x1, 668]
	str	w1, [x0, 668]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	beq	.L3407
	ldrb	w0, [x19, 5]
	cmp	w0, 1
	beq	.L3407
.L3408:
	ldr	x0, [x20, 27896]
	mov	x2, 632
	add	x1, x19, 16
	str	wzr, [x0, 672]
	ldr	x0, [x20, 27896]
	add	x0, x0, 16
	bl	memcpy
	ldr	x1, [x20, 27896]
	mov	w2, 2
	ldr	w3, [x19, 724]
	mov	x0, x23
	str	w3, [x1, 684]
	ldr	x1, [x20, 27896]
	ldr	w3, [x19, 664]
	str	w3, [x1, 652]
	ldr	x1, [x20, 27896]
	ldr	w3, [x19, 676]
	str	w3, [x1, 664]
	ldr	x1, [x20, 27896]
	ldr	w3, [x19, 692]
	str	w3, [x1, 676]
	str	w3, [x1, 812]
	ldrb	w3, [x19, 7]
	ldr	x1, [x20, 27896]
	cmp	w3, 1
	csel	w21, w21, wzr, eq
	strb	w21, [x1, 3]
	ldr	x1, [x19, 648]
	bl	GetAPC
	cbz	w0, .L3404
	ldr	x1, .LC842
	mov	w3, w0
	mov	w2, 2497
.L3475:
	mov	w0, 0
	bl	dprint_vfmw
	mov	x0, x23
	bl	ClearDPB
	mov	w0, -1
	b	.L3384
	.p2align 3
.L3480:
	ldrb	w0, [x19, 5]
	mov	w2, 3
	cmp	w0, wzr
	csel	w0, w0, w2, eq
	b	.L3389
	.p2align 3
.L3407:
	ldr	x0, [x20, 27896]
	mov	w1, 2
	strb	w1, [x0, 2]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	bne	.L3408
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 668]
	str	w1, [x0, 660]
	b	.L3408
	.p2align 3
.L3394:
	ldr	x0, [x20, 27896]
	mov	w1, 1
	strb	w1, [x0, 2]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	bne	.L3395
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 668]
	str	w1, [x0, 660]
	b	.L3395
	.p2align 3
.L3415:
	ldr	x1, [x20, 27896]
	ldrb	w0, [x1, 2]
	orr	w0, w0, 2
	strb	w0, [x1, 2]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	bne	.L3416
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 668]
	str	w1, [x0, 660]
	b	.L3416
	.p2align 3
.L3401:
	ldr	x1, [x20, 27896]
	ldrb	w0, [x1, 2]
	orr	w0, w0, 1
	strb	w0, [x1, 2]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	bne	.L3402
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 668]
	str	w1, [x0, 660]
	b	.L3402
	.p2align 3
.L3479:
	ldrb	w0, [x1, 3]
	orr	w0, w0, 2
	uxtb	w0, w0
	b	.L3413
	.p2align 3
.L3482:
	ldrb	w0, [x1, 3]
	orr	w0, w0, 1
	uxtb	w0, w0
	b	.L3399
	.p2align 3
.L3477:
	ldr	x1, .LC840
	mov	w3, w20
	mov	w2, 2280
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3384
.L3481:
	ldr	x1, .LC842
	mov	w3, w0
	mov	w2, 2319
	b	.L3475
	.size	InsertFrmInDPB, .-InsertFrmInDPB
	.align	3
.LC840:
	.xword	.LC839
	.align	3
.LC842:
	.xword	.LC841
	.align	3
.LC844:
	.xword	.LC843
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	StorePicInDPB
	.type	StorePicInDPB, %function
StorePicInDPB:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 20480
	add	x24, x20, 61440
	bl	_mcount
	str	wzr, [x19, 728]
	ldrb	w1, [x24, 1707]
	cmp	w1, 2
	cset	w0, eq
	str	w0, [x19, 732]
	ldrb	w0, [x24, 1704]
	cbz	w0, .L3672
	add	x21, x20, 65536
	ldr	x0, .LC849
	ldrsw	x2, [x21, 1644]
	ldr	w3, [x21, 1656]
	str	w3, [x21, 1652]
	ldr	x0, [x0, x2, lsl 3]
	ldrsb	w2, [x0, 44]
	cmp	w2, 1
	beq	.L3673
.L3486:
	ldr	w0, [x21, 1572]
	cmp	w0, 2
	beq	.L3674
	ldr	x22, [x20]
	ldr	w0, [x22, 24]
	cbnz	w0, .L3493
	ldr	w2, [x21, 1648]
	cmp	w2, 2
	beq	.L3495
	ldrb	w2, [x24, 1706]
	cbnz	w2, .L3495
	sub	w2, w1, #1
	ldr	x25, [x24, 2352]
	uxtb	w2, w2
	cbnz	w1, .L3675
.L3497:
	cmp	w2, 1
	bls	.L3676
.L3653:
	cbz	w1, .L3502
	ldrb	w2, [x25, 1]
	cbnz	w2, .L3502
.L3496:
	cmp	w0, 2
	beq	.L3677
.L3495:
	ldr	w6, [x24, 2376]
	cbz	w6, .L3532
	ldr	w3, [x21, 1636]
	ldr	w2, [x24, 2404]
	cmp	w3, w2
	bcs	.L3533
	ldrb	w0, [x24, 1706]
	cbz	w0, .L3678
.L3533:
	mov	x0, x20
	bl	Marking
	cbz	w0, .L3535
	ldr	x1, .LC862
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, .LC848
	mov	w3, 3759
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x20, .LC858
	b	.L3578
.L3493:
	ldrb	w2, [x24, 1706]
	cbnz	w2, .L3496
	sub	w2, w1, #1
	ldr	x25, [x24, 2352]
	uxtb	w2, w2
	cbz	w1, .L3497
	b	.L3675
.L3672:
	ldr	x1, .LC846
	add	x21, x20, 65536
	bl	dprint_vfmw
	ldr	x1, .LC848
	mov	w3, 3519
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x20, .LC858
.L3578:
	ldr	x1, [x24, 2352]
	mov	w2, 1
	ldr	w0, [x21, 1644]
	mov	w19, -1
	ldr	w1, [x1, 648]
	bl	FSP_ClearLogicFs
	mov	w3, w19
	mov	w2, 3937
	mov	x1, x20
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, [x24, 2352]
	strb	wzr, [x0, 4]
	ldr	x0, [x24, 2352]
	strb	wzr, [x0, 1]
.L3575:
	strb	wzr, [x24, 1704]
	mov	w0, w19
.L3660:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L3673:
	ldr	w2, [x0, 156]
	cbnz	w2, .L3486
	ldr	w0, [x0, 160]
	cmp	w0, 1
	bne	.L3486
	add	x23, x20, 24576
	ldr	x6, [x20, 27840]
	ldr	x7, [x20, 27872]
	ldr	x8, [x20, 27880]
	ldr	w5, [x23, 3288]
	ldr	w4, [x23, 3292]
	cbz	w5, .L3580
	mov	w2, w5
	mov	w3, w4
	b	.L3488
.L3581:
	mov	w2, w0
.L3488:
	udiv	w0, w3, w2
	msub	w0, w0, w2, w3
	mov	w3, w2
	cbnz	w0, .L3581
.L3487:
	udiv	w0, w5, w2
	sub	x6, x6, x8
	lsl	w3, w6, 6
	sub	w3, w3, w6
	lsl	w3, w3, 1
	sub	w3, w3, w6
	lsl	w3, w3, 3
	udiv	w2, w4, w2
	mul	w0, w3, w0
	udiv	w0, w0, w2
	add	x0, x0, x7
	str	x0, [x24, 2304]
	b	.L3486
.L3675:
	ldrb	w3, [x25, 1]
	cmp	w3, wzr
	ccmp	w2, 1, 0, eq
	bls	.L3497
	cmp	w0, 2
	bne	.L3495
.L3677:
	ldr	w0, [x24, 2376]
	cbz	w0, .L3525
	ldrb	w0, [x24, 1710]
	cmp	w0, 5
	beq	.L3526
.L3530:
	mov	x0, x20
	add	x19, x20, 24576
	bl	SimpleSlideDPB
	ldr	w1, [x19, 3708]
	add	x2, x24, 1704
	mov	x0, x20
	bl	InsertFrmInDPB
	cbz	w0, .L3679
	ldr	x20, .LC858
	mov	w3, w0
	mov	w2, 3726
	mov	w0, 0
	mov	x1, x20
	bl	dprint_vfmw
	ldr	x1, .LC848
	mov	w3, 3727
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3578
.L3676:
	ldr	w2, [x21, 1648]
	cbnz	w2, .L3499
	mov	w0, 1
	mov	x2, 736
	str	w0, [x21, 1648]
	add	x1, x24, 1704
	add	x0, x24, 2440
	bl	memcpy
	ldr	w0, [x22, 24]
	b	.L3496
.L3502:
	add	x23, x24, 1704
.L3505:
	cbz	w1, .L3506
	ldrb	w0, [x23, 1]
	cmp	w0, 1
	beq	.L3680
.L3506:
	ldr	w0, [x23, 700]
	str	w0, [x25, 680]
.L3507:
	mov	x1, x25
	mov	x0, x20
	bl	GetImagePara
	ldr	w0, [x21, 1644]
	ldr	w1, [x25, 648]
	bl	FSP_GetFsImagePtr
	mov	x22, x0
	cbz	x0, .L3681
	ldrb	w0, [x23, 3]
	cbz	w0, .L3509
	ldrb	w0, [x23, 1]
	cmp	w0, 1
	beq	.L3682
.L3509:
	ldr	x0, [x23, 600]
.L3662:
	str	x0, [x22, 584]
.L3510:
	ldr	x0, [x23, 608]
	str	x0, [x22, 592]
	ldr	x0, [x23, 616]
	str	x0, [x22, 600]
	ldr	w0, [x23, 16]
	str	w0, [x22]
	ldr	w0, [x23, 20]
	str	w0, [x22, 4]
	ldr	w0, [x23, 24]
	str	w0, [x22, 8]
	ldr	w0, [x23, 28]
	str	w0, [x22, 12]
	ldr	w1, [x25, 680]
	str	w1, [x22, 152]
	ldr	w0, [x23, 440]
	str	w0, [x22, 424]
	ldr	w0, [x23, 436]
	str	w0, [x22, 420]
	ldr	x0, [x23, 448]
	str	x0, [x22, 432]
	cbz	w1, .L3516
	ldrb	w0, [x22, 64]
	and	w0, w0, 3
	cbz	w0, .L3683
.L3514:
	ldr	x0, [x20]
	ldr	w2, [x0, 4]
	cmp	w2, w1
	bcs	.L3516
	ldr	x0, .LC856
	ldr	x4, [x0]
	cbz	x4, .L3523
	ldr	w0, [x21, 1644]
	mov	w3, 8
	stp	w1, w2, [x29, 88]
	add	x2, x29, 88
	mov	w1, 104
	blr	x4
.L3523:
	ldr	w0, [x21, 1644]
	mov	w2, 0
	ldr	w1, [x25, 648]
	bl	FSP_SetDisplay
	ldr	x1, .LC848
	mov	w3, 3683
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x20, .LC858
	b	.L3578
.L3499:
	cmp	w2, 1
	bne	.L3653
	cmp	w1, 1
	add	x23, x24, 1704
	ldr	x25, [x24, 3088]
	beq	.L3684
	cmp	w1, 2
	bne	.L3505
	ldr	w0, [x24, 2392]
	str	w0, [x25, 804]
	ldrb	w1, [x23, 3]
	b	.L3505
	.p2align 3
.L3532:
	ldrb	w0, [x24, 1705]
	cmp	w0, 1
	beq	.L3537
	add	x23, x20, 24576
	ldr	w3, [x23, 3704]
.L3549:
	mov	w7, -1
	mov	w8, w7
	.p2align 2
.L3566:
	ldr	w1, [x23, 3708]
	cmp	w1, w3
	bcc	.L3685
	cmp	w1, w3
	mov	w19, w1
	bls	.L3556
	mov	w19, w3
	str	w3, [x23, 3708]
.L3556:
	cbz	w19, .L3587
	add	x1, x23, 3320
	mov	w5, 2147483647
	mov	w22, 0
	mov	w0, 0
	.p2align 2
.L3559:
	ldr	x4, [x1]
	add	x1, x1, 8
	ldr	w2, [x4, 664]
	cmp	w2, w5
	bge	.L3558
	ldrb	w4, [x4, 4]
	cmp	w4, wzr
	csel	w22, w22, w0, eq
	csel	w5, w5, w2, eq
.L3558:
	add	w0, w0, 1
	cmp	w0, w19
	bne	.L3559
.L3557:
	cbnz	w6, .L3560
	ldr	w0, [x24, 2380]
	cmp	w0, w5
	blt	.L3686
.L3560:
	cmp	w8, w22
	ccmp	w7, w19, 0, eq
	beq	.L3687
	mov	w1, w22
	mov	x0, x20
	bl	OutputFrmFromDPB
	cmn	w0, #1
	mov	w25, w0
	beq	.L3565
	mov	w7, w19
	mov	w8, w22
	ldr	w3, [x23, 3704]
	ldr	w6, [x24, 2376]
	b	.L3566
.L3587:
	mov	w5, 2147483647
	mov	w22, 0
	b	.L3557
.L3535:
	mov	x0, x20
	bl	UpdateReflist
	mov	x0, x20
	bl	UpdateLTReflist
	mov	x0, x20
	bl	RemoveUnUsedFrameStore
	cbz	w0, .L3525
	ldr	x1, .LC864
	mov	w0, 22
	bl	dprint_vfmw
.L3525:
	ldrb	w0, [x24, 1705]
	cmp	w0, 1
	beq	.L3537
	add	x23, x20, 24576
.L3541:
	ldr	w6, [x24, 2376]
	cbz	w6, .L3688
	ldr	w4, [x23, 3712]
	ldr	w5, [x23, 3716]
	ldr	w3, [x23, 3704]
	add	w0, w4, w5
	cmp	w3, w0
	bhi	.L3549
	ldr	x0, [x20]
	ldr	w0, [x0, 24]
	cmp	w0, 3
	beq	.L3550
	ldr	x0, .LC865
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L3550
	ldr	x1, .LC867
	mov	w2, 3838
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x20
	bl	ClearDPB
	ldr	x1, .LC848
	mov	w3, 3840
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x20, .LC858
	b	.L3578
.L3683:
	ldr	x1, .LC855
	mov	w2, 3659
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC856
	ldr	x4, [x0]
	cbz	x4, .L3515
	ldr	w0, [x21, 1644]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 111
	blr	x4
.L3515:
	ldr	w1, [x22, 152]
	cbnz	w1, .L3514
.L3516:
	ldr	w0, [x21, 1644]
	mov	w2, 1
	ldr	w1, [x25, 648]
	bl	FSP_SetDisplay
	ldr	w0, [x21, 1644]
	mov	x4, x22
	add	x3, x20, 8
	mov	x2, x20
	mov	w1, 0
	bl	InsertImgToVoQueue
	cmp	w0, 1
	beq	.L3689
	ldr	w0, [x21, 1644]
	mov	w2, 0
	ldr	w1, [x25, 648]
	bl	FSP_SetDisplay
.L3518:
	ldr	x0, [x20]
	ldr	w0, [x0, 612]
	add	w0, w0, 2047
	cmp	w0, 4095
	bhi	.L3690
	str	wzr, [x22, 16]
.L3520:
	ldr	w0, [x21, 1664]
	ldr	w1, [x21, 1648]
	add	w0, w0, 2
	str	w0, [x21, 1664]
	cmp	w1, 2
	beq	.L3522
	mov	w0, 1
	str	w0, [x25, 840]
.L3522:
	mov	w0, 2
	str	w0, [x21, 1648]
	ldr	x0, [x20]
	ldr	w0, [x0, 24]
	b	.L3496
.L3674:
	ldr	x1, .LC851
	bl	dprint_vfmw
	mov	x0, x20
	bl	DirectOutput
	mov	w19, w0
	ldr	w1, [x21, 304]
	ldr	w0, [x24, 2428]
	cmp	w0, w1
	beq	.L3490
	uxtw	x0, w0
	add	x0, x0, 16384
	add	x20, x20, x0, lsl 2
	str	wzr, [x20, 232]
	str	w1, [x24, 2428]
.L3490:
	cmp	w19, 1
	beq	.L3691
.L3491:
	ldr	x1, .LC848
	mov	w3, 3554
	mov	w2, w19
	mov	w0, 14
	bl	dprint_vfmw
.L3492:
	cmn	w19, #1
	bne	.L3575
	ldr	x20, .LC858
	b	.L3578
	.p2align 3
.L3537:
	ldr	x0, [x24, 3208]
	ldr	x3, [x24, 2352]
	cmp	x3, x0
	ccmp	x0, xzr, 4, eq
	beq	.L3692
	mov	x0, x20
	bl	DirectOutput
	cmn	w0, #1
	mov	w19, w0
	beq	.L3693
	cmp	w0, 1
	bne	.L3545
	ldr	x0, [x24, 2352]
	strb	wzr, [x0, 4]
	ldr	x0, [x24, 2352]
	strb	wzr, [x0, 1]
.L3545:
	ldr	x1, .LC848
	mov	w3, 3795
	mov	w2, w19
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3492
	.p2align 3
.L3685:
	cbz	w6, .L3568
	ldrb	w0, [x24, 1708]
	cbnz	w0, .L3568
	ldr	w0, [x23, 3712]
	cbz	w0, .L3568
	mov	w0, 0
	b	.L3573
	.p2align 3
.L3570:
	ldr	w1, [x23, 3712]
	cmp	w1, w0
	bls	.L3694
.L3573:
	add	x1, x20, x0, uxtw 3
	ldr	w3, [x24, 2368]
	add	w0, w0, 1
	ldr	x2, [x1, 28024]
	ldr	w4, [x2, 652]
	cmp	w4, w3
	bne	.L3570
	strb	wzr, [x2, 2]
	ldr	x2, [x1, 28024]
	ldrb	w3, [x2, 4]
	cmp	w3, 1
	beq	.L3695
.L3571:
	ldr	w1, [x2, 684]
	ldr	w3, [x21, 304]
	cmp	w1, w3
	uxtw	x1, w1
	add	x1, x1, 16384
	beq	.L3570
	add	x1, x20, x1, lsl 2
	str	wzr, [x1, 232]
	str	w3, [x2, 684]
	b	.L3570
.L3694:
	ldr	w1, [x23, 3708]
.L3568:
	add	x2, x24, 1704
	mov	x0, x20
	bl	InsertFrmInDPB
	ldr	w1, [x23, 3708]
	str	w1, [x24, 3200]
	cbz	w0, .L3574
	ldr	x20, .LC858
	mov	w3, w0
	mov	w2, 3923
	mov	w0, 1
	mov	x1, x20
	bl	dprint_vfmw
	ldr	x1, .LC848
	mov	w3, 3924
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3578
.L3565:
	ldr	x20, .LC858
	mov	w3, w0
	mov	w2, 3886
	mov	w0, 1
	mov	x1, x20
	bl	dprint_vfmw
	ldr	x1, .LC848
	mov	w3, 3887
	mov	w2, w25
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3578
.L3678:
	ldr	x1, .LC860
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC856
	ldr	x4, [x0]
	cbz	x4, .L3534
	ldr	w1, [x21, 1636]
	mov	w3, 8
	ldr	w2, [x24, 2404]
	ldr	w0, [x21, 1644]
	stp	w2, w1, [x29, 88]
	add	x2, x29, 88
	mov	w1, 104
	blr	x4
.L3534:
	mov	x0, x20
	mov	w22, -1
	bl	ClearAllSlice
	ldr	w0, [x20, 14948]
	mov	w1, 2
	str	w0, [x19, 3232]
	add	x0, x19, 3072
	strb	w1, [x19, 3225]
	mov	w1, 32
	strb	wzr, [x19, 3224]
	strb	w1, [x19, 3226]
	mov	w1, 262144
	stp	w22, wzr, [x0, 180]
	stp	wzr, w1, [x0, 188]
	mov	w0, 23352
	movk	w0, 0x1, lsl 16
	str	w0, [x19, 3240]
	mov	w0, 7
	str	w0, [x19, 3236]
	mov	w0, 3
	str	w0, [x19, 3248]
	mov	x0, x20
	bl	ClearDPB
	ldr	x1, .LC848
	mov	w3, 3751
	mov	w2, w22
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x20, .LC858
	b	.L3578
.L3679:
	ldr	w1, [x19, 3708]
	mov	x0, x20
	add	w1, w1, 1
	str	w1, [x19, 3708]
	mov	w19, 0
	bl	UpdateReflist
	mov	x0, x20
	bl	UpdateLTReflist
	ldr	x1, .LC848
	mov	w3, 3735
	mov	w2, 0
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3575
.L3550:
	ldr	w5, [x23, 3708]
	cmp	w5, w3
	bls	.L3552
	mov	w5, w3
	str	w3, [x23, 3708]
.L3552:
	cbz	w5, .L3584
	add	x2, x23, 3320
	mov	w1, 0
	mov	w0, 0
	mov	w4, 2147483647
	.p2align 2
.L3555:
	ldr	x3, [x2]
	add	x2, x2, 8
	ldr	w3, [x3, 664]
	cmp	w3, w4
	bge	.L3554
	mov	w1, w0
	mov	w4, w3
.L3554:
	add	w0, w0, 1
	cmp	w0, w5
	bne	.L3555
.L3553:
	mov	x0, x20
	bl	RemoveFrameStoreOutDPB
	mov	x0, x20
	bl	UpdateReflist
	mov	x0, x20
	bl	UpdateLTReflist
	ldr	w3, [x23, 3704]
	ldr	w6, [x24, 2376]
	b	.L3549
.L3682:
	ldr	x0, [x23, 600]
	cmn	x0, #1
	bne	.L3510
	ldr	x0, [x24, 3040]
	cmn	x0, #1
	bne	.L3662
	b	.L3510
	.p2align 3
.L3687:
	ldr	x2, .LC868
	mov	w3, w22
	ldr	x1, .LC870
	mov	w0, 1
	add	x2, x2, 296
	bl	dprint_vfmw
	ldr	x1, .LC848
	mov	w3, 3875
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x20, .LC858
	b	.L3578
.L3686:
	ldr	w0, [x21, 1572]
	cmp	w0, 2
	beq	.L3696
.L3561:
	mov	x0, x20
	bl	DirectOutput
	cmn	w0, #1
	mov	w19, w0
	beq	.L3697
	cmp	w0, 1
	bne	.L3563
	ldr	x0, [x24, 2352]
	strb	wzr, [x0, 4]
	ldr	x0, [x24, 2352]
	strb	wzr, [x0, 1]
.L3563:
	ldr	x1, .LC848
	mov	w3, 3868
	mov	w2, w19
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3492
.L3689:
	ldr	w0, [x21, 1672]
	add	w0, w0, 1
	str	w0, [x21, 1672]
	b	.L3518
.L3574:
	add	w1, w1, 1
	mov	x0, x20
	str	w1, [x23, 3708]
	mov	w19, 0
	bl	UpdateReflist
	mov	x0, x20
	bl	UpdateLTReflist
	b	.L3575
.L3692:
	add	x23, x20, 24576
	ldr	w4, [x23, 3708]
	cbz	w4, .L3541
	ldr	x0, [x20, 27896]
	cmp	x3, x0
	beq	.L3698
	add	x0, x23, 3328
	mov	w1, 0
	.p2align 2
.L3546:
	add	w1, w1, 1
	cmp	w1, w4
	beq	.L3541
	ldr	x2, [x0], 8
	cmp	x3, x2
	bne	.L3546
.L3542:
	add	x2, x24, 1704
	mov	x0, x20
	bl	InsertFrmInDPB
	cmn	w0, #1
	mov	w19, w0
	beq	.L3699
	mov	x0, x20
	mov	w19, 0
	bl	UpdateReflist
	mov	x0, x20
	bl	UpdateLTReflist
	ldr	x1, .LC848
	mov	w3, 3815
	mov	w2, 0
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3575
.L3688:
	ldr	w3, [x23, 3704]
	b	.L3549
.L3690:
	mov	x1, x22
	mov	x0, x20
	bl	SetFrmRepeatCount.part.3
	b	.L3520
.L3691:
	ldr	x0, [x24, 2352]
	strb	wzr, [x0, 4]
	ldr	x0, [x24, 2352]
	strb	wzr, [x0, 1]
	b	.L3491
.L3526:
	mov	x0, x20
	bl	IDRMemMarking
	cbz	w0, .L3530
	mov	w0, -1
	b	.L3660
	.p2align 3
.L3680:
	mov	w0, 3
	strb	w0, [x25, 1]
	ldr	w1, [x25, 680]
	ldr	w0, [x23, 700]
	add	w0, w1, w0
	str	w0, [x25, 680]
	b	.L3507
.L3695:
	str	w3, [x2, 668]
	ldr	x2, [x1, 28024]
	strb	wzr, [x2, 4]
	ldr	x2, [x1, 28024]
	b	.L3571
.L3699:
	ldr	x20, .LC858
	mov	w3, w0
	mov	w2, 3808
	mov	w0, 1
	mov	x1, x20
	bl	dprint_vfmw
	ldr	x1, .LC848
	mov	w3, 3809
	mov	w2, w19
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3578
.L3696:
	ldrb	w0, [x24, 1707]
	cbz	w0, .L3561
	ldr	x0, [x24, 2352]
	str	x0, [x24, 3216]
	b	.L3561
.L3681:
	ldr	x1, .LC853
	mov	w2, 3627
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x1, .LC848
	mov	w3, 3628
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x20, .LC858
	b	.L3578
.L3584:
	mov	w1, 0
	b	.L3553
.L3684:
	ldr	w0, [x24, 2388]
	str	w0, [x25, 756]
	ldrb	w1, [x23, 3]
	b	.L3505
.L3580:
	mov	w2, w4
	b	.L3487
.L3697:
	ldr	x1, .LC858
	mov	w3, w0
	mov	w2, 3859
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3563
.L3698:
	mov	w1, 0
	b	.L3542
.L3693:
	ldr	x1, .LC858
	mov	w3, w0
	mov	w2, 3785
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3545
	.size	StorePicInDPB, .-StorePicInDPB
	.align	3
.LC846:
	.xword	.LC845
	.align	3
.LC848:
	.xword	.LC847
	.align	3
.LC849:
	.xword	s_pstVfmwChan
	.align	3
.LC851:
	.xword	.LC850
	.align	3
.LC853:
	.xword	.LC852
	.align	3
.LC855:
	.xword	.LC854
	.align	3
.LC856:
	.xword	g_event_report
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
.LC865:
	.xword	g_apple_airplay_mirrorinig_flag
	.align	3
.LC867:
	.xword	.LC866
	.align	3
.LC868:
	.xword	.LANCHOR2
	.align	3
.LC870:
	.xword	.LC869
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AllocFrameStore
	.type	AllocFrameStore, %function
AllocFrameStore:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x26, x0
	mov	x0, x30
	add	x20, x26, 20480
	mov	w23, w1
	bl	_mcount
	ldrb	w0, [x20, 1585]
	cbz	w0, .L3701
	ldrb	w1, [x20, 1586]
	cbz	w1, .L3769
	add	x21, x26, 65536
	ldr	w22, [x21, 1572]
	cmp	w22, 2
	beq	.L3727
	add	x25, x26, 61440
	mov	w22, 2
	ldrb	w1, [x25, 3176]
	strb	wzr, [x25, 1705]
	cmp	w1, 1
	bne	.L3729
	b	.L3726
	.p2align 3
.L3701:
	add	x21, x26, 65536
	ldr	w0, [x21, 1572]
	cmp	w0, 2
	beq	.L3770
	add	x25, x26, 61440
	mov	w22, 0
	strb	wzr, [x25, 1705]
.L3729:
	strb	wzr, [x25, 1704]
	ldr	w3, [x21, 300]
	cbz	w3, .L3720
	add	x19, x26, 28672
	mov	x24, 0
	add	x19, x19, 552
	.p2align 2
.L3719:
	ldrb	w0, [x19, 1]
	cbnz	w0, .L3714
	cbz	x19, .L3715
	add	x0, x26, 24576
	ldr	w2, [x0, 3708]
	cbz	w2, .L3715
	ldr	x0, [x26, 27896]
	cmp	x0, x19
	beq	.L3714
	sub	w2, w2, #1
	mov	x0, x26
	add	x2, x26, x2, lsl 3
	b	.L3717
	.p2align 3
.L3718:
	ldr	x1, [x0, 27896]
	cmp	x1, x19
	beq	.L3714
.L3717:
	cmp	x0, x2
	add	x0, x0, 8
	bne	.L3718
.L3715:
	lsl	x1, x24, 3
	mov	w27, 1
	sub	x1, x1, x24
	str	x19, [x25, 2352]
	lsl	x1, x1, 2
	strb	w27, [x25, 1704]
	sub	x1, x1, x24
	mov	w3, 101
	lsl	x1, x1, x27
	mov	x2, 632
	sub	x24, x1, x24
	add	x0, x25, 1720
	add	x24, x26, x24, lsl 4
	add	x24, x24, 28672
	add	x1, x24, 568
	str	wzr, [x24, 1232]
	str	w3, [x25, 2404]
	bl	memcpy
	str	wzr, [x25, 1872]
	strb	wzr, [x24, 555]
	str	wzr, [x19, 668]
	ldr	x0, [x25, 2352]
	strb	wzr, [x0, 2]
	ldr	x0, [x25, 2352]
	strb	w27, [x0, 4]
	ldr	x0, [x25, 2352]
	str	wzr, [x0, 840]
	ldrb	w19, [x25, 1704]
	cmp	w19, 1
	bne	.L3720
	cmp	w23, wzr
	ldr	w0, [x21, 1644]
	cset	w1, eq
	bl	FSP_NewLogicFs
	mov	w23, w0
	mov	w1, w0
	ldr	w0, [x21, 1644]
	bl	FSP_GetLogicFs
	mov	x24, x0
	cmp	w23, wzr
	ccmp	x0, xzr, 4, ge
	beq	.L3721
	add	x1, x0, 48
	ldr	x0, [x26]
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L3771
.L3722:
	ldr	x19, .LC873
	mov	x2, 632
	ldr	x0, [x25, 2352]
	ldr	x3, [x19, 104]
	add	x0, x0, 16
	blr	x3
	ldr	x1, [x25, 2352]
	mov	x2, 632
	ldr	x3, [x19, 104]
	add	x0, x25, 1720
	add	x1, x1, 16
	blr	x3
	ldr	x0, [x25, 2352]
	mov	w4, w23
	str	w23, [x0, 648]
	ldrsb	w0, [x24, 4]
	str	w0, [x25, 2428]
	ldr	x3, [x25, 2352]
	ldrb	w0, [x20, 1585]
.L3711:
	cmp	w0, wzr
	uxtb	w1, w22
	mov	w2, 3
	strb	w1, [x25, 1707]
	csel	w0, w0, w2, eq
	strb	w0, [x3, 696]
	ldrb	w0, [x25, 1705]
	cmp	w0, 1
	beq	.L3772
	strb	w1, [x25, 3176]
	ldr	w0, [x20, 1600]
	str	w0, [x25, 3184]
	ldr	w0, [x20, 1612]
	str	w0, [x25, 3180]
	ldr	w0, [x21, 1656]
	str	w0, [x25, 3192]
	str	w4, [x25, 3196]
	cbnz	w22, .L3773
	strb	wzr, [x25, 3177]
	mov	w0, 0
.L3761:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L3769:
	add	x21, x26, 65536
	ldr	w1, [x21, 1572]
	cmp	w1, 2
	beq	.L3774
	add	x25, x26, 61440
	mov	w22, 1
	ldrb	w1, [x25, 3176]
	strb	wzr, [x25, 1705]
	cmp	w1, 2
	bne	.L3729
.L3726:
	ldr	w1, [x20, 1600]
	ldr	w2, [x25, 3184]
	cmp	w2, w1
	bne	.L3729
	ldr	w1, [x20, 1612]
	cbnz	w1, .L3705
	ldr	w1, [x25, 3180]
	cbnz	w1, .L3729
.L3706:
	ldr	w2, [x21, 1652]
	ldr	w1, [x21, 1656]
	sub	w1, w1, w2
	cmp	w1, 2
	bhi	.L3729
	ldr	x3, [x25, 2352]
	mov	w1, 1
	strb	w1, [x25, 1705]
	cbz	x3, .L3708
	cmp	w22, 2
	beq	.L3775
	cmp	w22, 1
	mov	w4, 0
	bne	.L3711
	ldrb	w1, [x3, 1]
	cmp	w1, 2
	beq	.L3711
.L3708:
	strb	wzr, [x25, 1705]
	b	.L3729
	.p2align 3
.L3770:
	mov	w22, 0
.L3727:
	add	x25, x26, 61440
	strb	wzr, [x25, 1705]
	b	.L3729
	.p2align 3
.L3714:
	add	w24, w24, 1
	add	x19, x19, 848
	cmp	w24, w3
	bne	.L3719
.L3720:
	ldr	x1, .LC872
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x26
	bl	ClearAll
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	mov	w0, -1
	ldp	x29, x30, [sp], 112
	ret
.L3773:
	mov	w1, 1
	strb	w1, [x25, 3177]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L3774:
	mov	w22, 1
	b	.L3727
.L3772:
	strb	wzr, [x25, 3176]
	mov	w0, 0
	ldr	w1, [x20, 1600]
	str	w1, [x25, 3184]
	ldr	w1, [x20, 1612]
	str	w1, [x25, 3180]
	ldr	w1, [x21, 1656]
	str	w1, [x25, 3192]
	strb	wzr, [x25, 3177]
	str	w4, [x25, 3196]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L3771:
	ldr	w2, [x26, 14936]
	ldr	w0, [x1, 112]
	lsl	w2, w2, 4
	ldr	w3, [x26, 14932]
	stp	wzr, wzr, [x1, 240]
	mul	w19, w2, w0
	ldr	w0, [x1, 36]
	lsl	w3, w3, 4
	stp	wzr, wzr, [x1, 248]
	stp	w3, w2, [x1, 68]
	add	w0, w19, w0
	str	wzr, [x1, 256]
	str	w0, [x1, 40]
	str	x1, [x29, 104]
	bl	MEM_Phy2Vir
	ldr	x1, [x29, 104]
	ldr	w2, [x1, 20]
	ldr	w3, [x1, 116]
	str	x0, [x1, 512]
	add	w0, w19, w2
	str	w0, [x1, 24]
	add	w0, w3, w0
	str	w0, [x1, 32]
	b	.L3722
.L3705:
	ldr	w1, [x25, 3180]
	cbz	w1, .L3729
	b	.L3706
.L3721:
	ldr	x2, [x25, 2352]
	mov	w0, 0
	strb	wzr, [x25, 1704]
	ldr	x1, .LC875
	strb	wzr, [x2, 4]
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	ClearAll
	mov	w0, -1
	b	.L3761
.L3775:
	ldrb	w0, [x3, 1]
	cmp	w0, 1
	bne	.L3708
	ldrb	w0, [x20, 1585]
	mov	w4, 0
	b	.L3711
	.size	AllocFrameStore, .-AllocFrameStore
	.align	3
.LC872:
	.xword	.LC871
	.align	3
.LC873:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC875:
	.xword	.LC874
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecGap
	.type	DecGap, %function
DecGap:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	add	x25, x19, 24576
	add	x20, x19, 20480
	bl	_mcount
	add	x28, x19, 16384
	add	x0, x19, 12288
	add	x27, x19, 61440
	ldr	w1, [x25, 3180]
	mov	w22, 2
	ldr	w2, [x20, 1600]
	ldrb	w0, [x0, 2705]
	ldr	w5, [x20, 1596]
	cmp	w0, 1
	lsl	x0, x1, 6
	sub	x0, x0, x1
	ldr	w21, [x28, 788]
	lsl	x0, x0, 2
	str	w2, [x29, 120]
	sub	x0, x0, x1
	lsl	x0, x0, 1
	sub	x0, x0, x1
	lsl	x0, x0, 2
	add	x1, x19, x0
	add	x0, x0, 20480
	add	x1, x1, 20480
	add	x0, x19, x0
	add	x0, x0, 3268
	ldrb	w1, [x1, 3271]
	str	w1, [x29, 104]
	ldr	w1, [x20, 752]
	str	w1, [x29, 112]
	ldr	w1, [x20, 756]
	str	x0, [x27, 2360]
	str	w1, [x29, 108]
	csel	w1, wzr, w22, ne
	ldr	w0, [x25, 3708]
	str	w1, [x29, 116]
	cbz	w0, .L3800
	mov	w0, 1
	add	w21, w21, 4
	add	w2, w5, 1
	lsl	w21, w0, w21
	ldr	x1, .LC879
	mov	w0, w22
	udiv	w5, w2, w21
	str	wzr, [x20, 752]
	str	wzr, [x20, 756]
	msub	w26, w5, w21, w2
	bl	dprint_vfmw
	ldr	x1, .LC881
	mov	w3, w26
	ldr	w2, [x29, 120]
	mov	w0, w22
	bl	dprint_vfmw
	ldr	w1, [x25, 3704]
	ldr	w0, [x25, 3708]
	cmp	w0, w1
	bhi	.L3801
.L3780:
	cbz	w0, .L3791
	sub	w3, w0, #1
	mov	w22, 0
	add	x3, x3, 3488
	add	x0, x25, 3320
	add	x3, x19, x3, lsl 3
	.p2align 2
.L3783:
	ldr	x2, [x0]
	add	x0, x0, 8
	ldr	w1, [x2, 664]
	cmp	w22, w1
	bge	.L3782
	ldrb	w2, [x2, 4]
	cmp	w2, wzr
	csel	w22, w22, w1, eq
.L3782:
	cmp	x0, x3
	bne	.L3783
.L3781:
	ldr	w0, [x29, 120]
	mov	w23, 1
	str	wzr, [x29, 124]
	mov	w24, w23
	cmp	w0, w26
	bne	.L3796
	b	.L3788
	.p2align 3
.L3786:
	mov	x1, 0
	mov	x0, x19
	strb	wzr, [x27, 1708]
	bl	StorePicInDPB
	add	w1, w26, 1
	cbnz	w0, .L3802
.L3787:
	sdiv	w0, w1, w21
	str	w26, [x20, 1596]
	msub	w26, w0, w21, w1
	ldr	w0, [x29, 120]
	cmp	w0, w26
	beq	.L3788
	ldr	w0, [x25, 3708]
	ldr	w1, [x29, 124]
	cmp	w1, w0
	bhi	.L3788
.L3796:
	mov	w1, 1
	mov	x0, x19
	bl	AllocFrameStore
	cbnz	w0, .L3803
	ldr	x1, .LC885
	mov	w0, 2
	bl	dprint_vfmw
	strb	w24, [x27, 1710]
	ldr	x0, [x27, 2352]
	str	w26, [x0, 652]
	str	w26, [x27, 2368]
	ldr	x0, [x27, 2352]
	str	w26, [x0, 704]
	ldr	w0, [x29, 116]
	str	w0, [x27, 2376]
	ldr	x0, [x27, 2352]
	str	wzr, [x0, 700]
	ldr	x0, [x27, 2352]
	str	w23, [x0, 668]
	ldr	x0, [x27, 2352]
	strb	wzr, [x0, 4]
	ldr	x0, [x27, 2352]
	strb	w23, [x0]
	strb	w24, [x27, 1706]
	ldr	x0, [x27, 2360]
	strb	wzr, [x0, 3]
	ldr	w0, [x28, 792]
	cbz	w0, .L3786
	mov	x0, x19
	str	w26, [x20, 768]
	bl	DecPOC
	ldr	w0, [x20, 748]
	str	w0, [x27, 2380]
	ldr	w0, [x20, 744]
	str	w0, [x27, 2384]
	ldr	w0, [x20, 736]
	str	w0, [x27, 2388]
	cmp	w0, w22
	ldr	w0, [x20, 740]
	str	w0, [x27, 2392]
	bls	.L3786
	cmp	w0, w22
	ldr	w0, [x29, 124]
	mov	x1, 0
	strb	wzr, [x27, 1708]
	csinc	w0, w0, w0, ls
	str	w0, [x29, 124]
	mov	x0, x19
	bl	StorePicInDPB
	add	w1, w26, 1
	cbz	w0, .L3787
.L3802:
	ldr	w1, [x29, 112]
	mov	w3, w0
	str	w1, [x20, 752]
	mov	w2, 6265
	ldr	w1, [x29, 108]
	mov	w0, 0
	str	w1, [x20, 756]
	ldrb	w5, [x29, 104]
	ldr	x4, [x27, 2360]
	ldr	x1, .LC887
	strb	w5, [x4, 3]
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L3801:
	mov	w0, w1
	str	w1, [x25, 3708]
	b	.L3780
	.p2align 3
.L3800:
	ldr	x1, .LC877
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L3788:
	ldr	w0, [x29, 112]
	str	w0, [x20, 752]
	ldr	w0, [x29, 108]
	str	w0, [x20, 756]
	mov	w0, 0
	ldrb	w2, [x29, 104]
	ldr	x1, [x27, 2360]
	strb	w2, [x1, 3]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L3803:
	ldr	w0, [x29, 112]
	str	w0, [x20, 752]
	ldr	w0, [x29, 108]
	str	w0, [x20, 756]
	mov	w0, 0
	ldrb	w3, [x29, 104]
	ldr	x2, [x27, 2360]
	ldr	x1, .LC883
	strb	w3, [x2, 3]
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L3791:
	mov	w22, 0
	b	.L3781
	.size	DecGap, .-DecGap
	.align	3
.LC877:
	.xword	.LC876
	.align	3
.LC879:
	.xword	.LC878
	.align	3
.LC881:
	.xword	.LC880
	.align	3
.LC883:
	.xword	.LC882
	.align	3
.LC885:
	.xword	.LC884
	.align	3
.LC887:
	.xword	.LC886
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264DEC_Init
	.type	H264DEC_Init, %function
H264DEC_Init:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	ldr	x22, .LC888
	mov	x2, 1696
	mov	w1, 0
	movk	x2, 0x1, lsl 16
	mov	x0, x20
	ldr	x3, [x22, 96]
	ldr	w19, [x20, 608]
	blr	x3
	str	w19, [x20, 608]
	add	x0, x20, 8
	bl	ResetVoQueue
	str	x21, [x20]
	str	xzr, [x20, 616]
	str	wzr, [x20, 624]
	ldr	w0, [x21, 28]
	cmp	w0, 25
	beq	.L3814
	mov	w2, 32
	mov	w1, 256
	mov	w0, 136
	str	w2, [x20, 14944]
	str	w0, [x20, 14940]
	str	w1, [x20, 14948]
.L3806:
	ldr	w0, [x21, 584]
	mov	w23, 2208
	add	x19, x20, 65536
	bl	MEM_Phy2Vir
	ldr	x1, [x20]
	mov	w2, 4000
	ldr	w4, [x20, 14944]
	ldr	w5, [x20, 14948]
	ldrsw	x3, [x1, 580]
	smull	x2, w4, w2
	add	x3, x0, x3
	str	x3, [x20, 14960]
	add	x1, x3, x2
	str	x1, [x20, 14968]
	cmp	x1, xzr
	smaddl	x0, w5, w23, x1
	ccmp	x3, xzr, 4, ne
	str	x0, [x19, 1560]
	ccmp	x0, xzr, 4, ne
	beq	.L3815
	ldr	w6, [x21, 616]
	cmp	w6, wzr
	ccmp	x3, xzr, 4, eq
	ccmp	x1, xzr, 4, ne
	beq	.L3809
	ldr	x4, [x22, 96]
	mov	w1, 0
	mov	x0, x3
	blr	x4
	ldr	w2, [x20, 14948]
	mov	w1, 0
	ldr	x0, [x20, 14968]
	ldr	x3, [x22, 96]
	smull	x2, w2, w23
	blr	x3
	ldr	w4, [x20, 14944]
	ldr	w5, [x20, 14948]
	ldr	x0, [x19, 1560]
.L3809:
	add	x2, x20, 16384
	ldr	x6, [x22, 96]
	mov	w1, 0
	str	w5, [x2, 2616]
	str	w4, [x20, 15012]
	ldrsw	x3, [x20, 14940]
	lsl	x2, x3, 7
	sub	x2, x2, x3
	lsl	x2, x2, 5
	blr	x6
	str	wzr, [x19, 308]
	mov	w0, 17
	str	w0, [x19, 304]
	add	x0, x19, 256
	mov	w1, 40
	str	w1, [x19, 300]
	add	x1, x19, 1536
	add	x2, x19, 1536
	stp	wzr, wzr, [x0, 60]
	stp	wzr, wzr, [x0, 68]
	stp	xzr, xzr, [x19, 336]
	stp	xzr, xzr, [x19, 352]
	str	wzr, [x19, 1580]
	mov	x0, x20
	stp	wzr, wzr, [x1, 52]
	stp	wzr, wzr, [x1, 60]
	stp	wzr, wzr, [x2, 68]
	stp	wzr, wzr, [x2, 76]
	str	wzr, [x19, 1648]
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x19, 1644]
	beq	.L3816
	mov	w1, 0
	mov	x0, x20
	bl	ClearAll
	mov	w0, 1
.L3808:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3814:
	ldr	w0, [x21, 700]
	str	w0, [x20, 14944]
	ldr	w0, [x21, 704]
	str	w0, [x20, 14948]
	ldr	w0, [x21, 692]
	str	w0, [x20, 14940]
	b	.L3806
.L3815:
	ldr	x2, .LC889
	mov	w3, 12616
	ldr	x1, .LC891
	mov	w0, 0
	add	x2, x2, 312
	bl	dprint_vfmw
	mov	w0, -20
	b	.L3808
	.p2align 3
.L3816:
	ldr	x1, .LC893
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L3808
	.size	H264DEC_Init, .-H264DEC_Init
	.align	3
.LC888:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC889:
	.xword	.LANCHOR2
	.align	3
.LC891:
	.xword	.LC890
	.align	3
.LC893:
	.xword	.LC892
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InitPic
	.type	InitPic, %function
InitPic:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	add	x22, x21, 20480
	mov	w25, 2208
	bl	_mcount
	add	x19, x21, 61440
	ldr	x0, [x21, 14968]
	mov	w20, 4000
	ldr	w1, [x22, 1592]
	add	x23, x21, 65536
	ldrb	w2, [x19, 1704]
	ldr	x3, [x21, 14960]
	umull	x1, w1, w25
	add	x25, x0, x1
	ldr	w0, [x25, 28]
	umull	x0, w0, w20
	add	x20, x3, x0
	cbz	w2, .L3818
	ldr	x0, [x19, 2352]
	cbz	x0, .L3819
	ldrb	w1, [x0, 1]
	cbz	w1, .L3923
	strb	wzr, [x19, 1704]
.L3818:
	add	x1, x29, 108
	mov	x0, x21
	bl	GetReRangeFlag
	mov	w24, w0
	ldr	w1, [x21, 15012]
	ldr	w0, [x20, 36]
	cmp	w1, w0
	beq	.L3924
.L3821:
	ldr	x1, .LC897
	add	x0, x21, 12288
	strb	wzr, [x20, 24]
	mov	x2, 4000
	add	x0, x0, 2688
	ldr	x3, [x1, 112]
	mov	x1, x20
	blr	x3
.L3822:
	ldr	w0, [x29, 108]
	cbnz	w0, .L3823
	ldr	x0, [x21]
	ldr	w0, [x0, 888]
	cmp	w0, 1
	beq	.L3823
	add	x24, x21, 16384
.L3824:
	ldr	w1, [x24, 2616]
	ldr	w0, [x25, 24]
	cmp	w1, w0
	bne	.L3834
	ldrb	w0, [x25, 20]
	cbnz	w0, .L3834
.L3835:
	ldr	w0, [x22, 728]
	ldr	w3, [x24, 788]
	cbz	w0, .L3836
	str	wzr, [x22, 1596]
	str	wzr, [x19, 3184]
.L3836:
	ldr	w0, [x23, 1572]
	cmp	w0, 2
	beq	.L3837
	ldr	x2, [x21]
	ldr	w0, [x2, 24]
	sub	w0, w0, #2
	cmp	w0, 1
	bls	.L3837
	ldr	w1, [x22, 1596]
	ldr	w4, [x22, 1600]
	cmp	w4, w1
	beq	.L3838
	mov	w0, 1
	add	w3, w3, 4
	lsl	w3, w0, w3
	add	w5, w1, w0
	udiv	w0, w5, w3
	msub	w0, w0, w3, w5
	cmp	w4, w0
	beq	.L3873
	ldr	w0, [x2, 608]
	cbnz	w0, .L3839
	ldr	x5, [x2, 648]
	mov	x0, 4294967296
	cmp	x5, x0
	beq	.L3925
.L3840:
	cmp	w4, w1
	bls	.L3841
	ldr	w0, [x24, 1864]
	sub	w1, w4, w1
	cmp	w0, w1
	bcs	.L3839
	ldrb	w0, [x22, 1584]
	cmp	w0, 2
	beq	.L3842
.L3847:
	ldr	w0, [x23, 1640]
	cbnz	w0, .L3839
	mov	x0, x21
	bl	ClearAllSlice
	ldr	x0, .LC905
	mov	w1, 23352
	ldr	w2, [x21, 14948]
	movk	w1, 0x1, lsl 16
	mov	w6, 2
	mov	w5, 7
	ldrb	w0, [x0]
	mov	w4, 32
	mov	w3, 3
	str	w2, [x22, 3232]
	str	w1, [x22, 3240]
	mov	w2, -1
	mov	w1, 262144
	strb	wzr, [x22, 3224]
	strb	w6, [x22, 3225]
	strb	w4, [x22, 3226]
	str	w5, [x22, 3236]
	str	w3, [x22, 3248]
	str	wzr, [x22, 3256]
	str	wzr, [x22, 3260]
	str	w2, [x22, 3252]
	str	w1, [x22, 3264]
	cbz	w0, .L3926
.L3848:
	ldr	w0, [x22, 1596]
	mov	w2, 6476
	ldr	w3, [x22, 1600]
	ldr	x1, .LC907
	ldr	w4, [x24, 1864]
	sub	w3, w3, w0
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L3828:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3823:
	ldr	w0, [x23, 1604]
	add	w0, w0, 1
	str	w0, [x23, 1604]
	cbnz	w24, .L3825
	ldr	x0, [x21]
	ldr	w0, [x0, 888]
	cmp	w0, 1
	beq	.L3825
	mov	x0, x21
	bl	FlushDPB
	cbnz	w0, .L3927
	cbz	x21, .L3871
.L3928:
	mov	x0, x21
	bl	ClearAllSlice
	mov	x0, x21
	bl	InitDPB.part.15
	cbnz	w0, .L3829
	cbnz	w24, .L3831
	ldr	x0, [x21]
	add	x24, x21, 16384
	ldr	w0, [x0, 888]
	cmp	w0, 1
	bne	.L3824
.L3831:
	add	x24, x21, 16384
	add	x1, x21, 12288
	add	x3, x23, 300
	ldr	w4, [x24, 1864]
	str	w4, [x23, 304]
	ldr	w0, [x24, 1844]
	ldrb	w26, [x1, 2706]
	mov	w1, 2
	add	w0, w0, 1
	ldr	w27, [x24, 1840]
	sub	w26, w1, w26
	lsl	w0, w0, 4
	add	w27, w27, 1
	mul	w26, w0, w26
	lsl	w27, w27, 4
	mov	x0, x21
	mov	w1, w27
	mov	w2, w26
	bl	H264_ArrangeVahbMem
	cmp	w0, 1
	beq	.L3833
	ldr	x1, [x21]
	mov	w0, -2
	ldr	w1, [x1, 888]
	cmp	w1, 1
	beq	.L3828
	ldr	x1, .LC904
	mov	w0, 0
	str	wzr, [x21, 14932]
	str	wzr, [x21, 14936]
	bl	dprint_vfmw
	mov	w1, 0
	mov	x0, x21
	bl	ClearAll
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	mov	w0, -1
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3834:
	ldr	x0, .LC897
	mov	x2, 2208
	strb	wzr, [x25, 20]
	mov	x1, x25
	ldr	x3, [x0, 112]
	add	x0, x24, 2592
	blr	x3
	b	.L3835
	.p2align 3
.L3825:
	ldr	x1, .LC899
	mov	w0, 22
	bl	dprint_vfmw
	cbnz	x21, .L3928
.L3871:
	mov	w0, -1
.L3829:
	ldr	x1, .LC902
	mov	w3, w0
	mov	w2, 6380
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3828
	.p2align 3
.L3873:
	mov	w1, w4
	.p2align 2
.L3838:
	ldr	w0, [x22, 1612]
	cbz	w0, .L3857
	str	w1, [x22, 1596]
.L3857:
	mov	x0, x21
	str	w1, [x22, 768]
	bl	DecPOC
	mov	w1, 0
	mov	x0, x21
	bl	AllocFrameStore
	cbnz	w0, .L3929
	strb	wzr, [x19, 1711]
	mov	w0, 1
	strb	w0, [x19, 1704]
	mov	w1, -1
	mov	w4, 1
	ldrb	w0, [x22, 1587]
	strb	w0, [x19, 1710]
	ldr	w5, [x22, 1600]
	str	w5, [x19, 2368]
	ldr	w3, [x22, 1612]
	str	w3, [x19, 2376]
	ldr	w0, [x22, 748]
	str	w0, [x19, 2380]
	ldr	w0, [x22, 744]
	str	w0, [x19, 2384]
	ldr	w0, [x22, 736]
	str	w0, [x19, 2388]
	ldr	w0, [x22, 740]
	str	w0, [x19, 2392]
	strb	wzr, [x19, 1706]
	strb	wzr, [x19, 1709]
	strb	wzr, [x19, 1708]
	str	w1, [x19, 2424]
	ldrb	w2, [x22, 1585]
	cbz	w2, .L3859
	strb	w4, [x22, 1585]
	mov	w2, w4
	mov	w4, 2
.L3859:
	add	x25, x21, 12288
	ldr	w6, [x24, 1844]
	mov	w1, 2
	ldrb	w0, [x25, 2706]
	sub	w0, w1, w0
	madd	w0, w6, w0, w0
	str	w0, [x19, 2416]
	udiv	w0, w0, w4
	str	w0, [x19, 2412]
	ldr	w1, [x24, 1840]
	add	w1, w1, 1
	str	w1, [x19, 2408]
	mul	w0, w0, w1
	str	w0, [x19, 2420]
	ldrb	w0, [x24, 2592]
	strb	w0, [x19, 1712]
	cbnz	w2, .L3875
	ldrb	w0, [x25, 2707]
	mov	w1, 0
	cbnz	w0, .L3930
.L3860:
	strb	w0, [x19, 1713]
	str	w1, [x23, 1552]
	cbz	w3, .L3861
	str	w5, [x22, 1596]
.L3861:
	add	x2, x21, 24576
	mov	x22, -1
	ldr	x1, .LC913
	mov	w0, 29
	mov	w26, 2
	ldr	w3, [x2, 3180]
	lsl	x2, x3, 6
	sub	x2, x2, x3
	lsl	x2, x2, 2
	sub	x2, x2, x3
	lsl	x2, x2, 1
	sub	x2, x2, x3
	add	x2, x21, x2, lsl 2
	add	x2, x2, 20480
	add	x2, x2, 3268
	str	x2, [x19, 2360]
	ldr	x2, [x21]
	ldr	x3, [x2, 56]
	str	x3, [x19, 2304]
	ldr	x3, [x2, 72]
	str	x3, [x19, 2312]
	ldr	x3, [x2, 88]
	str	x3, [x19, 2320]
	ldr	w3, [x2, 104]
	str	w3, [x19, 1720]
	ldr	w3, [x2, 108]
	str	w3, [x19, 1724]
	ldr	w3, [x2, 112]
	str	w3, [x19, 1728]
	ldr	w3, [x2, 128]
	str	w3, [x19, 1732]
	ldr	w3, [x20, 44]
	str	w3, [x19, 1888]
	ldr	w3, [x20, 48]
	str	w3, [x19, 1892]
	str	x22, [x2, 56]
	ldr	x2, [x19, 2304]
	bl	dprint_vfmw
	ldr	x1, .LC915
	mov	w0, 29
	ldr	x2, [x19, 2312]
	bl	dprint_vfmw
	ldr	w0, [x24, 1840]
	ldr	x1, .LC897
	add	w0, w0, 1
	lsl	w0, w0, 4
	str	w0, [x19, 1788]
	ldr	x3, [x1, 96]
	ldrb	w1, [x25, 2706]
	ldr	w2, [x24, 1844]
	sub	w0, w26, w1
	mov	w1, 0
	madd	w0, w2, w0, w0
	mov	x2, 4
	lsl	w0, w0, 4
	str	w0, [x19, 1792]
	ldr	w0, [x21, 15016]
	ldr	w25, [x24, 1908]
	cmp	w0, 1
	add	x0, x19, 1784
	cset	w27, ne
	and	w25, w25, 7
	blr	x3
	ldrb	w0, [x19, 1784]
	ldrb	w2, [x19, 1785]
	and	w0, w0, 252
	bfi	w0, w27, 2, 3
	strb	w0, [x19, 1784]
	bfi	w2, w26, 0, 2
	ldr	w1, [x24, 1912]
	and	w2, w2, -13
	bfi	w2, w26, 4, 2
	strb	w2, [x19, 1785]
	bfi	w0, w1, 5, 3
	strb	w0, [x19, 1784]
	mov	w1, w25
	add	x0, x19, 1720
	ldr	w2, [x19, 1784]
	bfi	w2, w25, 14, 3
	str	w2, [x19, 1784]
	bl	SetAspectRatio
	ldrb	w2, [x19, 1707]
	ldr	w1, [x23, 1604]
	cmp	w2, wzr
	ldr	x0, [x19, 2352]
	str	w1, [x19, 1876]
	cset	w1, ne
	str	w1, [x19, 1772]
	cbz	x0, .L3931
	ldr	w1, [x19, 1784]
	str	w1, [x0, 80]
	ldr	x0, [x19, 2352]
	ldr	w1, [x19, 1772]
	str	w1, [x0, 68]
	ldr	x0, [x19, 2352]
	ldr	w1, [x19, 1824]
	str	w1, [x0, 120]
	ldr	x0, [x19, 2352]
	ldr	w1, [x19, 1820]
	str	w1, [x0, 116]
	ldr	x0, [x19, 2352]
	ldr	w1, [x19, 1788]
	str	w1, [x0, 84]
	ldr	x0, [x19, 2352]
	ldr	w1, [x19, 1792]
	str	w1, [x0, 88]
	ldr	x1, [x19, 2352]
	ldr	w0, [x20, 3284]
	str	w0, [x1, 100]
	str	w0, [x19, 1804]
	ldr	x1, [x19, 2352]
	ldr	w0, [x20, 3288]
	str	w0, [x1, 104]
	str	w0, [x19, 1808]
	ldr	x1, [x19, 2352]
	ldr	w0, [x20, 3276]
	str	w0, [x1, 92]
	str	w0, [x19, 1796]
	ldr	x1, [x19, 2352]
	ldr	w0, [x20, 3280]
	str	w0, [x1, 96]
	str	w0, [x19, 1800]
	ldr	x1, [x19, 2352]
	ldr	w0, [x23, 1644]
	ldr	w1, [x1, 648]
	bl	FSP_GetDispPhyFs
	cbz	x0, .L3863
	ldr	w3, [x19, 1772]
	mov	w1, 0
	ldr	w2, [x0, 4]
	cmp	w3, wzr
	ldr	w0, [x23, 1644]
	cset	w3, ne
	bl	FSP_SetStoreType
.L3863:
	ldr	w1, [x23, 328]
	add	x2, x19, 2264
	add	x5, x19, 2296
.L3867:
	ldr	x0, [x2]
	cbz	x0, .L3932
.L3864:
	add	x2, x2, 8
	cmp	x5, x2
	bne	.L3867
	cbz	w1, .L3869
	cmp	w1, wzr
	ble	.L3869
	.p2align 2
.L3870:
	add	x22, x21, x1, sxtw 3
	sub	w20, w1, #1
	add	x22, x22, 65536
	ldr	w0, [x23, 1644]
	ldr	x1, [x22, 328]
	bl	FreeUsdByDec
	str	xzr, [x22, 328]
	mov	w1, w20
	cbnz	w20, .L3870
.L3869:
	str	wzr, [x23, 328]
	mov	x0, x21
	str	wzr, [x19, 2396]
	bl	CalcPicNum
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	mov	w0, 0
	ldp	x29, x30, [sp], 112
	ret
.L3842:
	cbnz	w4, .L3844
	sub	w3, w3, #1
.L3845:
	mov	x0, x21
	str	w3, [x22, 1596]
	bl	FlushDPB
	cbnz	w0, .L3933
	ldrb	w0, [x22, 1584]
	cmp	w0, 2
	bne	.L3847
	.p2align 2
.L3839:
	mov	x0, x21
	bl	DecGap
	cbnz	w0, .L3934
.L3837:
	ldr	w1, [x22, 1600]
	b	.L3838
	.p2align 3
.L3924:
	ldrb	w0, [x20, 24]
	cbz	w0, .L3822
	b	.L3821
	.p2align 3
.L3932:
	cbz	w1, .L3864
	ldr	x0, [x23, 336]
	subs	w1, w1, #1
	str	x0, [x2]
	beq	.L3865
	add	x4, x23, 336
	mov	w3, 0
	.p2align 2
.L3866:
	add	w0, w3, 1
	mov	x3, x0
	cmp	w0, w1
	add	x0, x0, 8192
	add	x0, x0, 42
	ldr	x0, [x21, x0, lsl 3]
	str	x0, [x4], 8
	bne	.L3866
.L3865:
	uxtw	x0, w1
	add	x0, x0, 8192
	add	x0, x0, 42
	str	xzr, [x21, x0, lsl 3]
	str	w1, [x23, 328]
	b	.L3864
	.p2align 3
.L3875:
	mov	w1, 0
	mov	w0, 0
	b	.L3860
	.p2align 3
.L3930:
	mov	w1, 1
	mov	w0, w1
	b	.L3860
	.p2align 3
.L3923:
	ldr	w1, [x0, 648]
	mov	w2, 1
	ldr	w0, [x23, 1644]
	bl	FSP_ClearLogicFs
	ldr	x0, [x19, 2352]
	strb	wzr, [x0, 1]
	ldr	x0, [x19, 2352]
	strb	wzr, [x0, 4]
	strb	wzr, [x19, 1704]
	b	.L3818
	.p2align 3
.L3833:
	lsr	w27, w27, 4
	lsr	w26, w26, 4
	str	w27, [x21, 14932]
	str	w26, [x21, 14936]
	b	.L3824
	.p2align 3
.L3841:
	sub	w0, w4, w1
	ldr	w1, [x24, 1864]
	add	w0, w0, w3
	cmp	w1, w0
	bcs	.L3839
	ldrb	w0, [x22, 1584]
	cmp	w0, 2
	beq	.L3849
.L3854:
	ldr	w0, [x23, 1640]
	cbnz	w0, .L3839
	mov	x0, x21
	bl	ClearAllSlice
	ldr	x0, .LC905
	mov	w1, 23352
	ldr	w2, [x21, 14948]
	movk	w1, 0x1, lsl 16
	mov	w6, 2
	mov	w5, 7
	ldrb	w0, [x0]
	mov	w4, 32
	mov	w3, 3
	str	w2, [x22, 3232]
	str	w1, [x22, 3240]
	mov	w2, -1
	mov	w1, 262144
	strb	wzr, [x22, 3224]
	strb	w6, [x22, 3225]
	strb	w4, [x22, 3226]
	str	w5, [x22, 3236]
	str	w3, [x22, 3248]
	str	wzr, [x22, 3256]
	str	wzr, [x22, 3260]
	str	w2, [x22, 3252]
	str	w1, [x22, 3264]
	cbz	w0, .L3935
.L3855:
	ldr	w0, [x22, 1596]
	mov	w2, 6509
	ldr	w3, [x22, 1600]
	ldr	x1, .LC907
	ldr	w4, [x24, 1864]
	sub	w3, w3, w0
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3828
	.p2align 3
.L3819:
	ldr	x2, .LC894
	mov	w3, 6343
	ldr	x1, .LC896
	mov	w0, 22
	add	x2, x2, 328
	bl	dprint_vfmw
	strb	wzr, [x19, 1704]
	b	.L3818
.L3927:
	ldr	x1, .LC900
	mov	w3, w0
	mov	w2, 6372
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3828
.L3934:
	ldr	x1, .LC909
	mov	w2, 6519
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3828
	.p2align 3
.L3925:
	ldr	w0, [x2, 656]
	cbnz	w0, .L3840
	ldr	w0, [x2, 612]
	add	w0, w0, 1024
	cmp	w0, 2048
	bhi	.L3839
	b	.L3840
.L3929:
	ldr	x1, .LC911
	mov	w2, 6538
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3828
.L3849:
	cbnz	w4, .L3851
	sub	w3, w3, #1
.L3852:
	mov	x0, x21
	str	w3, [x22, 1596]
	bl	FlushDPB
	cbnz	w0, .L3936
	ldrb	w0, [x22, 1584]
	cmp	w0, 2
	beq	.L3839
	b	.L3854
	.p2align 3
.L3931:
	ldr	x2, .LC894
	mov	w3, 6615
	ldr	x1, .LC917
	mov	w0, 22
	add	x2, x2, 328
	bl	dprint_vfmw
	mov	w0, w22
	b	.L3828
.L3844:
	sub	w3, w4, #1
	b	.L3845
.L3851:
	sub	w3, w4, #1
	b	.L3852
.L3933:
	ldr	x1, .LC900
	mov	w3, w0
	mov	w2, 6460
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3828
.L3936:
	ldr	x1, .LC900
	mov	w3, w0
	mov	w2, 6493
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3828
.L3935:
	mov	x0, x21
	bl	ClearDPB
	b	.L3855
.L3926:
	mov	x0, x21
	bl	ClearDPB
	b	.L3848
	.size	InitPic, .-InitPic
	.align	3
.LC894:
	.xword	.LANCHOR2
	.align	3
.LC896:
	.xword	.LC895
	.align	3
.LC897:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC899:
	.xword	.LC898
	.align	3
.LC900:
	.xword	.LC799
	.align	3
.LC902:
	.xword	.LC901
	.align	3
.LC904:
	.xword	.LC903
	.align	3
.LC905:
	.xword	g_apple_airplay_mirrorinig_flag
	.align	3
.LC907:
	.xword	.LC906
	.align	3
.LC909:
	.xword	.LC908
	.align	3
.LC911:
	.xword	.LC910
	.align	3
.LC913:
	.xword	.LC912
	.align	3
.LC915:
	.xword	.LC914
	.align	3
.LC917:
	.xword	.LC916
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_DecSlice
	.type	H264_DecSlice, %function
H264_DecSlice:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 65536
	add	x21, x19, 20480
	bl	_mcount
	ldr	x1, .LC918
	mov	w0, 22
	ldr	w2, [x20, 1588]
	sub	w2, w2, #1
	bl	dprint_vfmw
	ldr	x0, [x19, 632]
	ldr	x2, .LC919
	ldrb	w1, [x0, 2]
	strb	w1, [x21, 1587]
	ldr	w0, [x0, 84]
	str	w0, [x21, 1612]
	ldrsw	x0, [x20, 1644]
	ldr	x0, [x2, x0, lsl 3]
	ldrsb	w2, [x0, 44]
	cmp	w2, 1
	beq	.L3993
.L3938:
	mov	x0, x19
	bl	ProcessSliceHeaderFirstPart
	cbnz	w0, .L3992
	mov	x0, x19
	bl	ProcessSliceHeaderSecondPart
	cbnz	w0, .L3992
	ldr	w2, [x20, 1568]
	mov	w3, 0
	add	x22, x19, 61440
	cbz	w2, .L3945
	sub	w9, w2, #1
	add	x22, x19, 61440
	add	x9, x9, 4096
	add	x4, x22, 3240
	add	x9, x9, 3990
	mov	w10, 0
	mov	w3, 0
	mov	x0, 0
	add	x9, x19, x9, lsl 3
	.p2align 2
.L3953:
	ldr	x1, [x4]
	ldr	x6, [x1, 8]
	cbz	x6, .L3967
	ldr	x5, [x1, 40]
	ldr	w7, [x1, 16]
	cbz	x5, .L3968
.L3999:
	ldr	w1, [x1, 48]
.L3948:
	cbz	x0, .L3949
	cmp	x6, x0
	mov	w8, w7
	bls	.L3950
	sub	x0, x6, x0
	sub	w0, w0, w10
	add	w8, w0, w7
.L3950:
	add	w3, w1, w3
	add	w3, w8, w3
.L3951:
	cbz	x5, .L3970
	mov	x0, x5
	mov	w10, w1
.L3952:
	add	x4, x4, 8
	cmp	x9, x4
	bne	.L3953
.L3945:
	str	w3, [x20, 1628]
	ldr	w0, [x22, 2408]
	ldr	w4, [x22, 2412]
	mul	w4, w0, w4
	cmp	w4, 1620
	bgt	.L3994
	lsl	w0, w4, 2
	mov	w1, 32769
	sub	w4, w0, w4
	mov	w0, 16384
	lsl	w4, w4, 8
	cmp	w4, w1
	asr	w4, w4, 1
	csel	w4, w4, w0, gt
.L3955:
	ldr	w0, [x19, 14940]
	cmp	w0, w2
	bls	.L3956
	cmp	w4, w3
	bcc	.L3956
	ldrb	w0, [x21, 1589]
	cbz	w0, .L3959
	ldr	x1, .LC927
	mov	w0, 2
	bl	dprint_vfmw
	ldrb	w0, [x21, 1587]
	cmp	w0, 5
	ldr	w0, [x20, 1608]
	beq	.L3995
.L3961:
	add	w0, w0, 1
	str	wzr, [x20, 1624]
	str	w0, [x20, 1608]
	ldrb	w0, [x22, 1707]
	cbnz	w0, .L3962
	ldr	w0, [x20, 1612]
	add	w0, w0, 1
	str	w0, [x20, 1612]
.L3963:
	mov	x0, x19
	bl	InitPic
	cmn	w0, #2
	beq	.L3942
	cbnz	w0, .L3996
	mov	x0, x19
	bl	WritePicMsg
.L3959:
	mov	x0, x19
	bl	PicTypeStatistic
	mov	x0, x19
	bl	DecList
	cbnz	w0, .L3997
	mov	x0, x19
	bl	IsRefListWrong
	cbnz	w0, .L3998
	mov	x0, x19
	bl	ExitSlice
	mov	x0, x19
	bl	CalcStreamBits
	mov	x0, x19
	bl	WriteSliceMsg
	ldr	w1, [x20, 1624]
	mov	w2, 1
	mov	w0, 0
	str	w2, [x20, 308]
	add	w1, w1, w2
	str	w1, [x20, 1624]
.L3942:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3970:
	mov	x0, x6
	mov	w10, w7
	b	.L3952
	.p2align 3
.L3949:
	add	w3, w7, w3
	add	w3, w3, w1
	b	.L3951
	.p2align 3
.L3967:
	ldr	x5, [x1, 40]
	mov	w7, 0
	cbnz	x5, .L3999
	.p2align 2
.L3968:
	mov	w1, 0
	b	.L3948
	.p2align 3
.L3994:
	lsl	w4, w4, 8
	b	.L3955
	.p2align 3
.L3993:
	ldr	w2, [x0, 156]
	cbnz	w2, .L3938
	ldr	w0, [x0, 160]
	cmp	w0, 1
	ccmp	w1, 5, 0, eq
	bne	.L3938
	ldr	x0, [x19]
	ldr	x0, [x0, 56]
	cmn	x0, #1
	beq	.L3938
	ldr	x1, [x19, 27840]
	str	x0, [x19, 27872]
	str	x1, [x19, 27880]
	b	.L3938
	.p2align 3
.L3962:
	ldr	w0, [x20, 1616]
	add	w0, w0, 1
	str	w0, [x20, 1616]
	b	.L3963
	.p2align 3
.L3995:
	str	w0, [x20, 1620]
	b	.L3961
.L3992:
	ldr	x1, .LC920
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC921
	ldr	x4, [x0]
	cbz	x4, .L3990
	add	x2, x29, 64
	ldr	w0, [x20, 1644]
	mov	w5, -1
	mov	w3, 4
	mov	w1, 100
	str	w5, [x2, -8]!
	blr	x4
.L3990:
	mov	x0, x19
	bl	ClearCurrSlice
	mov	w0, -1
	b	.L3942
.L3956:
	ldr	x1, .LC923
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w1, [x19, 14940]
	ldr	w2, [x20, 1568]
	cmp	w2, w1
	bcc	.L3958
	ldr	x0, .LC921
	ldr	x4, [x0]
	cbz	x4, .L3958
	ldr	w0, [x20, 1644]
	mov	w3, 8
	stp	w2, w1, [x29, 56]
	add	x2, x29, 56
	mov	w1, 108
	blr	x4
.L3958:
	ldr	x1, .LC925
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	ClearAllSlice
	mov	w3, 32
	ldr	w7, [x19, 14948]
	strb	w3, [x21, 3226]
	add	x3, x21, 3072
	mov	w6, 23352
	strb	wzr, [x21, 3224]
	str	w7, [x21, 3232]
	movk	w6, 0x1, lsl 16
	mov	w5, 2
	str	w6, [x21, 3240]
	strb	w5, [x21, 3225]
	mov	w4, 7
	str	w4, [x21, 3236]
	mov	w0, -1
	mov	w2, 3
	mov	w1, 262144
	stp	w2, w0, [x3, 176]
	stp	wzr, wzr, [x3, 184]
	str	w1, [x21, 3264]
	b	.L3942
.L3997:
	ldr	x1, .LC931
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3942
.L3998:
	ldr	x1, .LC933
	mov	w0, 1
	ldr	w2, [x22, 2380]
	bl	dprint_vfmw
	b	.L3990
.L3996:
	ldr	x1, .LC929
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3942
	.size	H264_DecSlice, .-H264_DecSlice
	.align	3
.LC918:
	.xword	.LC774
	.align	3
.LC919:
	.xword	s_pstVfmwChan
	.align	3
.LC920:
	.xword	.LC776
	.align	3
.LC921:
	.xword	g_event_report
	.align	3
.LC923:
	.xword	.LC922
	.align	3
.LC925:
	.xword	.LC924
	.align	3
.LC927:
	.xword	.LC926
	.align	3
.LC929:
	.xword	.LC928
	.align	3
.LC931:
	.xword	.LC930
	.align	3
.LC933:
	.xword	.LC932
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_DecOneNal
	.type	H264_DecOneNal, %function
H264_DecOneNal:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	w21, w1
	add	x19, x20, 65536
	bl	_mcount
	ldr	x3, [x20, 632]
	ldr	w0, [x3, 76]
	cbz	w0, .L4005
	ldr	w2, [x19, 1628]
	mov	w0, 0
	.p2align 2
.L4004:
	ubfiz	x1, x0, 5, 32
	add	w0, w0, 1
	add	x1, x3, x1
	ldr	w1, [x1, 16]
	add	w2, w2, w1
	str	w2, [x19, 1628]
	ldr	w1, [x3, 76]
	cmp	w1, w0
	bhi	.L4004
.L4005:
	strb	wzr, [x3]
	ldr	x0, .LC934
	ldrsw	x1, [x19, 1644]
	ldr	x0, [x0, x1, lsl 3]
	ldrsb	w1, [x0, 44]
	cmp	w1, 1
	beq	.L4149
.L4003:
	add	x23, x20, 12288
	mov	w1, 32
	add	x0, x23, 2600
	bl	BsGet
	mov	w22, w0
	ldr	x1, [x20, 632]
	ldr	w0, [x1, 72]
	add	w0, w0, 32
	str	w0, [x1, 72]
.L4006:
	ldr	x4, [x20, 632]
	and	w0, w22, 31
	ubfx	x2, x22, 5, 2
	ubfx	x3, x22, 7, 1
	ldr	x1, .LC936
	strb	w0, [x4, 2]
	ldr	x0, [x20, 632]
	str	w2, [x0, 84]
	mov	w0, 22
	ldr	x2, [x20, 632]
	str	w3, [x2, 88]
	str	wzr, [x19, 1584]
	ldr	w2, [x19, 1588]
	ldr	x3, [x20, 632]
	ldrb	w3, [x3, 2]
	bl	dprint_vfmw
	ldr	w0, [x19, 1588]
	cmp	w0, 371
	beq	.L4150
	add	w0, w0, 1
	str	w0, [x19, 1588]
	ldr	x0, [x20, 632]
	ldrb	w2, [x0, 2]
	cmp	w2, 20
	beq	.L4151
.L4008:
	sub	w0, w2, #1
	cmp	w0, 29
	bls	.L4152
.L4014:
	ldr	x1, .LC979
	mov	w3, w22
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x2, [x20, 632]
	mov	w0, 0
	ldr	x1, .LC981
	ldrb	w2, [x2, 2]
	bl	dprint_vfmw
	ldr	x1, [x20, 632]
	cbz	x1, .L4041
	ldr	w0, [x19, 1644]
	bl	ReleaseNAL
	str	xzr, [x20, 632]
.L4041:
	ldr	x0, .LC950
	ldr	x4, [x0]
	cbz	x4, .L4135
.L4138:
	ldr	w0, [x19, 1644]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L4135:
	mov	w0, 0
.L4012:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4152:
	ldr	x1, .LC945
	ldrh	w0, [x1,w0,uxtw #1]
	adr	x1, .Lrtx4016
	add	x0, x1, w0, sxth #2
	br	x0
.Lrtx4016:
	.section	.rodata
	.align	0
	.align	2
.L4016:
	.2byte	(.L4015 - .Lrtx4016) / 4
	.2byte	(.L4014 - .Lrtx4016) / 4
	.2byte	(.L4014 - .Lrtx4016) / 4
	.2byte	(.L4014 - .Lrtx4016) / 4
	.2byte	(.L4015 - .Lrtx4016) / 4
	.2byte	(.L4017 - .Lrtx4016) / 4
	.2byte	(.L4018 - .Lrtx4016) / 4
	.2byte	(.L4019 - .Lrtx4016) / 4
	.2byte	(.L4020 - .Lrtx4016) / 4
	.2byte	(.L4021 - .Lrtx4016) / 4
	.2byte	(.L4022 - .Lrtx4016) / 4
	.2byte	(.L4023 - .Lrtx4016) / 4
	.2byte	(.L4024 - .Lrtx4016) / 4
	.2byte	(.L4014 - .Lrtx4016) / 4
	.2byte	(.L4018 - .Lrtx4016) / 4
	.2byte	(.L4014 - .Lrtx4016) / 4
	.2byte	(.L4014 - .Lrtx4016) / 4
	.2byte	(.L4014 - .Lrtx4016) / 4
	.2byte	(.L4025 - .Lrtx4016) / 4
	.2byte	(.L4015 - .Lrtx4016) / 4
	.2byte	(.L4014 - .Lrtx4016) / 4
	.2byte	(.L4014 - .Lrtx4016) / 4
	.2byte	(.L4014 - .Lrtx4016) / 4
	.2byte	(.L4014 - .Lrtx4016) / 4
	.2byte	(.L4014 - .Lrtx4016) / 4
	.2byte	(.L4014 - .Lrtx4016) / 4
	.2byte	(.L4014 - .Lrtx4016) / 4
	.2byte	(.L4014 - .Lrtx4016) / 4
	.2byte	(.L4014 - .Lrtx4016) / 4
	.2byte	(.L4026 - .Lrtx4016) / 4
	.text
	.p2align 3
.L4149:
	ldr	w1, [x0, 156]
	cbnz	w1, .L4003
	ldr	w1, [x0, 160]
	cmp	w1, 1
	bne	.L4003
	ldr	w0, [x0, 152]
	cmp	w0, 1
	ccmp	w21, wzr, 0, eq
	bne	.L4003
	add	x23, x20, 12288
	mov	w1, 40
	add	x22, x23, 2600
	mov	x0, x22
	bl	BsSkip
	mov	w1, 8
	mov	x0, x22
	bl	BsGet
	mov	w22, w0
	ldr	x1, [x20, 632]
	ldr	w0, [x1, 72]
	add	w0, w0, 48
	str	w0, [x1, 72]
	b	.L4006
	.p2align 3
.L4024:
	ldr	x1, .LC973
	mov	w2, 13
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x20, 632]
	cbz	x1, .L4135
.L4137:
	ldr	w0, [x19, 1644]
	bl	ReleaseNAL
	str	xzr, [x20, 632]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L4023:
	ldr	x1, .LC969
	mov	w2, 12
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x20, 632]
	cbnz	x1, .L4137
	b	.L4135
.L4022:
	ldr	x1, .LC971
	mov	w2, 11
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x20
	bl	H264_IsEosNal
	uxtb	w1, w0
	cmp	w1, 1
	beq	.L4153
.L4144:
	ldr	x1, [x20, 632]
	cbnz	x1, .L4137
	b	.L4135
.L4021:
	ldr	x1, .LC967
	mov	w2, 10
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x20, 632]
	cbnz	x1, .L4137
	b	.L4135
.L4026:
	ldr	x1, .LC977
	mov	w2, 30
	mov	w0, 22
	bl	dprint_vfmw
	cbnz	w21, .L4039
	ldr	x1, [x20, 632]
	cbz	x1, .L4039
	ldr	w0, [x19, 1644]
	bl	ReleaseNAL
	str	xzr, [x20, 632]
.L4039:
	add	x23, x23, 2600
	mov	w1, 32
	mov	x0, x23
	bl	BsGet
	mov	w21, w0
	mov	w1, 32
	mov	x0, x23
	bl	BsGet
	mov	w2, 20553
	mov	w1, 20036
	movk	w2, 0x4853, lsl 16
	movk	w1, 0x4345, lsl 16
	cmp	w21, w2
	ccmp	w0, w1, 0, eq
	bne	.L4135
	ldr	x21, .LC950
	ldr	x4, [x21]
	cbz	x4, .L4040
	ldr	w0, [x19, 1644]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L4040:
	mov	x0, x20
	str	wzr, [x20, 624]
	bl	DecVDM
	cbz	w0, .L4135
.L4146:
	ldr	x4, [x21]
	cbz	x4, .L4134
.L4136:
	ldr	w0, [x19, 1644]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	mov	w0, -1
	b	.L4012
.L4025:
	ldr	x1, .LC975
	mov	w2, 19
	mov	w0, 22
	bl	dprint_vfmw
	b	.L4144
.L4020:
	ldr	x1, .LC965
	mov	w2, 9
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x20, 632]
	cbnz	x1, .L4137
	b	.L4135
.L4019:
	ldr	x1, .LC952
	mov	w2, 8
	ldr	w3, [x19, 1596]
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x20
	bl	H264_DecPPS
	mov	w21, w0
	ldr	x1, [x20, 632]
	cbz	x1, .L4030
	ldr	w0, [x19, 1644]
	bl	ReleaseNAL
	str	xzr, [x20, 632]
.L4030:
	cbnz	w21, .L4154
	ldr	w1, [x19, 1596]
	mov	w0, 0
	add	w1, w1, 1
	str	w1, [x19, 1596]
	b	.L4012
.L4018:
	ldr	x1, .LC957
	mov	w0, 22
	ldr	w3, [x19, 1592]
	bl	dprint_vfmw
	mov	x0, x20
	bl	H264_DecSPS
	mov	w21, w0
	ldr	x1, [x20, 632]
	cbz	x1, .L4032
	ldr	w0, [x19, 1644]
	bl	ReleaseNAL
	str	xzr, [x20, 632]
.L4032:
	cbnz	w21, .L4155
	ldr	w1, [x19, 1592]
	mov	w0, 0
	add	w1, w1, 1
	str	w1, [x19, 1592]
	b	.L4012
.L4017:
	ldr	x1, .LC961
	mov	w2, 6
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x20
	bl	H264_DecSEI
	mov	w21, w0
	ldr	x1, [x20, 632]
	cbz	x1, .L4034
	ldr	w0, [x19, 1644]
	bl	ReleaseNAL
	str	xzr, [x20, 632]
.L4034:
	cbz	w21, .L4135
	ldr	x1, .LC963
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC950
	ldr	x4, [x0]
	cbnz	x4, .L4138
	b	.L4135
.L4015:
	ldr	x1, .LC947
	mov	w0, 22
	ldr	w3, [x19, 1600]
	bl	dprint_vfmw
	ldr	x2, [x20, 632]
	add	x1, x20, 20480
	mov	x0, x20
	ldrb	w3, [x2, 2]
	strb	w3, [x1, 1587]
	ldr	w2, [x2, 84]
	str	w2, [x1, 1612]
	bl	SliceCheck
	cbnz	w0, .L4156
	mov	x0, x20
	bl	H264_DecSlice
	cmn	w0, #2
	beq	.L4012
	cbz	w0, .L4135
	ldr	x0, .LC950
	ldr	x4, [x0]
	cbnz	x4, .L4136
.L4134:
	mov	w0, -1
.L4157:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4150:
	ldr	x1, .LC938
	mov	w0, 22
	bl	dprint_vfmw
	ldr	w0, [x19, 1588]
	add	w0, w0, 1
	str	w0, [x19, 1588]
	ldr	x0, [x20, 632]
	ldrb	w2, [x0, 2]
	cmp	w2, 20
	bne	.L4008
	.p2align 2
.L4151:
	mov	w1, 24
	add	x0, x23, 2600
	bl	BsGet
	mov	w22, w0
	ldr	x1, [x20, 632]
	ubfx	x2, x22, 23, 1
	add	x0, x20, 61440
	strb	w2, [x1, 3]
	ldr	x2, [x20, 632]
	ldrb	w1, [x2, 3]
	cbz	w1, .L4009
	ubfx	x1, x22, 16, 6
	strb	w1, [x0, 3225]
	ubfx	x1, x22, 12, 3
	ubfx	x3, x22, 22, 1
	strb	w1, [x0, 3227]
	ubfx	x1, x22, 5, 3
	ubfx	x4, x22, 15, 1
	strb	w3, [x0, 3224]
	strb	w1, [x0, 3229]
	ubfx	x3, x22, 8, 4
	ubfx	x1, x22, 3, 1
	strb	w4, [x0, 3226]
	strb	w3, [x0, 3228]
	ubfx	x4, x22, 4, 1
	ubfx	x3, x22, 2, 1
	strb	w1, [x0, 3231]
	strb	w4, [x0, 3230]
	and	w1, w22, 3
	strb	w3, [x0, 3232]
	strb	w1, [x0, 3233]
.L4009:
	mov	x1, 16711680
	ldr	x3, [x0, 3224]
	movk	x1, 0xff, lsl 32
	and	x1, x3, x1
	cmp	x1, 65536
	beq	.L4010
	ldrb	w3, [x0, 3226]
	ldrb	w2, [x0, 3228]
	mov	w0, 1
	ldr	x1, .LC940
	bl	dprint_vfmw
	ldr	x1, [x20, 632]
	cbz	x1, .L4134
	ldr	w0, [x19, 1644]
	bl	ReleaseNAL
	str	xzr, [x20, 632]
	mov	w0, -1
	b	.L4157
.L4010:
	ldrb	w1, [x0, 3224]
	cmp	w1, 1
	beq	.L4158
.L4013:
	ldrb	w4, [x0, 3229]
	ldrb	w3, [x0, 3227]
	ldrb	w2, [x0, 3228]
	mov	w0, 22
	ldr	x1, .LC942
	bl	dprint_vfmw
	ldr	x1, .LC944
	mov	w2, w22
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x20, 632]
	ldr	w0, [x1, 72]
	add	w0, w0, 24
	str	w0, [x1, 72]
	ldr	x0, [x20, 632]
	ldrb	w2, [x0, 2]
	b	.L4008
.L4156:
	ldr	x1, .LC949
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x20
	bl	ClearCurrSlice
	ldr	x0, .LC950
	ldr	x4, [x0]
	cbnz	x4, .L4136
	mov	w0, -1
	b	.L4157
.L4154:
	ldr	x2, .LC953
	mov	w0, 1
	ldr	x1, .LC955
	add	x2, x2, 336
	bl	dprint_vfmw
	ldr	x21, .LC950
	ldr	x4, [x21]
	cbz	x4, .L4134
.L4142:
	add	x2, x29, 80
	ldr	w0, [x19, 1644]
	mov	w20, -1
	mov	w3, 4
	mov	w1, 100
	str	w20, [x2, -8]!
	blr	x4
	ldr	x4, [x21]
	cbz	x4, .L4134
	ldr	w0, [x19, 1644]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	mov	w0, w20
	b	.L4012
.L4155:
	ldr	x1, .LC959
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x21, .LC950
	ldr	x4, [x21]
	cbnz	x4, .L4142
	mov	w0, -1
	b	.L4157
.L4158:
	mov	w1, 5
	strb	w1, [x2, 2]
	b	.L4013
.L4153:
	ldr	x21, .LC950
	strb	w0, [x23, 2640]
	ldr	x4, [x21]
	cbz	x4, .L4037
	ldr	w0, [x19, 1644]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 117
	blr	x4
.L4037:
	mov	x0, x20
	str	wzr, [x20, 624]
	bl	DecVDM
	cbz	w0, .L4144
	ldr	x1, [x20, 632]
	cbz	x1, .L4146
	ldr	w0, [x19, 1644]
	bl	ReleaseNAL
	str	xzr, [x20, 632]
	b	.L4146
	.size	H264_DecOneNal, .-H264_DecOneNal
	.align	3
.LC934:
	.xword	s_pstVfmwChan
	.align	3
.LC936:
	.xword	.LC935
	.align	3
.LC938:
	.xword	.LC937
	.align	3
.LC940:
	.xword	.LC939
	.align	3
.LC942:
	.xword	.LC941
	.align	3
.LC944:
	.xword	.LC943
	.align	3
.LC945:
	.xword	.L4016
	.align	3
.LC947:
	.xword	.LC946
	.align	3
.LC949:
	.xword	.LC948
	.align	3
.LC950:
	.xword	g_event_report
	.align	3
.LC952:
	.xword	.LC951
	.align	3
.LC953:
	.xword	.LANCHOR2
	.align	3
.LC955:
	.xword	.LC954
	.align	3
.LC957:
	.xword	.LC956
	.align	3
.LC959:
	.xword	.LC958
	.align	3
.LC961:
	.xword	.LC960
	.align	3
.LC963:
	.xword	.LC962
	.align	3
.LC965:
	.xword	.LC964
	.align	3
.LC967:
	.xword	.LC966
	.align	3
.LC969:
	.xword	.LC968
	.align	3
.LC971:
	.xword	.LC970
	.align	3
.LC973:
	.xword	.LC972
	.align	3
.LC975:
	.xword	.LC974
	.align	3
.LC977:
	.xword	.LC976
	.align	3
.LC979:
	.xword	.LC978
	.align	3
.LC981:
	.xword	.LC980
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264DEC_DecodePacket
	.type	H264DEC_DecodePacket, %function
H264DEC_DecodePacket:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	str	wzr, [x29, 84]
	stp	wzr, wzr, [x29, 76]
	cbz	x21, .L4211
	ldr	x0, [x20]
	add	x19, x20, 65536
	ldr	w2, [x0, 8]
	ldr	w1, [x19, 312]
	ubfiz	w2, w2, 16, 3
	str	w2, [x19, 1632]
	cmp	w1, 1
	ldr	w1, [x0]
	str	w1, [x19, 1636]
	ldr	w1, [x0, 4]
	str	w1, [x19, 1640]
	str	wzr, [x19, 1584]
	beq	.L4162
	ldr	w1, [x0, 840]
	cmp	w1, 1
	beq	.L4212
.L4163:
	mov	x1, x21
	mov	x0, x20
	bl	ReceivePacket
	mov	w1, w0
	ldr	x0, [x20, 632]
	str	x0, [x19, 1680]
.L4165:
	str	wzr, [x19, 312]
	mov	w0, 0
	cbz	w1, .L4213
.L4202:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L4212:
	ldr	w0, [x0, 888]
	cmp	w0, 1
	bne	.L4163
	ldr	w0, [x19, 1676]
	cmp	w0, 1
	bne	.L4163
	ldr	x0, [x19, 1680]
	str	x0, [x20, 632]
	str	wzr, [x19, 312]
	str	wzr, [x19, 1676]
	b	.L4164
	.p2align 3
.L4213:
	ldr	x0, [x20, 632]
.L4164:
	str	wzr, [x0, 72]
	add	x21, x20, 12288
	add	x21, x21, 2600
	ldr	x1, [x20, 632]
	mov	x0, x21
	ldr	w2, [x1, 16]
	ldr	x1, [x1, 8]
	bl	BsInit
	ldr	x0, .LC984
	ldrsw	x1, [x19, 1644]
	ldr	x0, [x0, x1, lsl 3]
	ldrsb	w22, [x0, 44]
	cmp	w22, 1
	beq	.L4166
.L4168:
	mov	w22, 0
.L4167:
	mov	w1, 32
	mov	x0, x21
	bl	BsGet
	uxtb	w0, w0
	ldr	x3, [x20, 632]
	and	w2, w0, 31
	mov	w1, 27
	and	w1, w0, w1
	ubfx	x0, x0, 5, 2
	strb	w2, [x3, 2]
	cmp	w1, 1
	ccmp	w2, 20, 4, ne
	ldr	x1, [x20, 632]
	str	w0, [x1, 84]
	beq	.L4214
.L4169:
	mov	x0, x20
	bl	FindTrailZeros
	cbnz	w0, .L4215
	ldr	x1, [x20, 632]
	mov	x0, x21
	str	wzr, [x1, 72]
	ldr	x1, [x20, 632]
	ldr	w2, [x1, 16]
	ldr	x1, [x1, 8]
	bl	BsInit
	mov	w1, w22
	mov	x0, x20
	bl	H264_DecOneNal
	cmn	w0, #2
	beq	.L4202
	cbnz	w0, .L4216
	add	x20, x20, 61440
	mov	w0, 0
	str	wzr, [x20, 2436]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L4162:
	ldr	x0, [x20, 632]
	cmp	x0, xzr
	csetm	w1, eq
	b	.L4165
	.p2align 3
.L4214:
	cmp	w2, 20
	beq	.L4217
.L4170:
	add	x2, x29, 92
	add	x1, x29, 88
	mov	x0, x20
	bl	InquireSliceProperty
	cbz	w0, .L4218
	ldr	x1, [x20, 632]
	cbz	x1, .L4181
	ldr	w0, [x19, 1644]
	bl	ReleaseNAL
	str	xzr, [x20, 632]
.L4181:
	ldr	x0, .LC987
	ldr	x4, [x0]
	cbz	x4, .L4209
	ldr	w0, [x19, 1644]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	mov	w0, -1
	b	.L4202
	.p2align 3
.L4218:
	ldr	w1, [x29, 88]
	ldr	w0, [x19, 1656]
	cmp	w1, 1
	csinc	w0, w0, w0, ne
	str	w0, [x19, 1656]
	beq	.L4219
.L4172:
	ldr	w0, [x29, 92]
	cmp	w0, 1
	bne	.L4169
	mov	x0, x20
	bl	FlushDPB
	cbnz	w0, .L4220
.L4179:
	ldr	w0, [x19, 1644]
	bl	FSP_GetFspType
	cbnz	w0, .L4169
	ldr	w0, [x19, 1644]
	add	x3, x29, 84
	add	x2, x29, 80
	add	x1, x29, 76
	bl	VCTRL_GetChanImgNum
	ldr	x0, [x20]
	ldr	w0, [x0, 724]
	cmp	w0, 1
	bne	.L4169
	ldr	w0, [x29, 84]
	cmp	w0, wzr
	ble	.L4221
	.p2align 2
.L4176:
	mov	w1, 1
	mov	w0, -2
	str	w1, [x19, 312]
	b	.L4202
	.p2align 3
.L4166:
	ldp	w1, w2, [x0, 152]
	ldr	w3, [x0, 160]
	mov	x0, x20
	bl	H264_VES_Splitter
	cmp	w0, 3
	beq	.L4167
	cbnz	w0, .L4202
	b	.L4168
	.p2align 3
.L4217:
	mov	x0, x20
	bl	InquireSliceExtProperty
	b	.L4170
.L4215:
	ldr	x1, .LC989
	mov	w0, 22
	bl	dprint_vfmw
.L4209:
	mov	w0, -1
	b	.L4202
	.p2align 3
.L4219:
	add	x23, x20, 20480
	ldrb	w0, [x23, 1585]
	cmp	w0, 1
	ldr	w0, [x19, 1660]
	beq	.L4222
	add	w0, w0, 2
	str	w0, [x19, 1660]
.L4174:
	ldr	w0, [x19, 1568]
	cbz	w0, .L4172
	ldr	x3, [x20, 632]
	mov	w2, 12
	ldr	x1, .LC985
	mov	x0, x21
	add	x1, x1, 432
	str	wzr, [x3, 72]
	bl	BsInit
	mov	w1, 1
	mov	x0, x20
	bl	H264_DecOneNal
	ldrb	w0, [x23, 1585]
	cmp	w0, 1
	ldr	w0, [x19, 1660]
	beq	.L4223
	sub	w0, w0, #2
	str	w0, [x19, 1660]
	b	.L4176
.L4222:
	add	w0, w0, 1
	str	w0, [x19, 1660]
	b	.L4174
.L4220:
	ldr	x1, .LC986
	mov	w3, w0
	mov	w2, 13318
	mov	w0, 0
	bl	dprint_vfmw
	b	.L4179
.L4211:
	ldr	x2, .LC982
	mov	w3, 13199
	ldr	x1, .LC983
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4202
.L4216:
	ldr	x1, .LC991
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4202
.L4223:
	sub	w0, w0, #1
	str	w0, [x19, 1660]
	b	.L4176
.L4221:
	ldr	w0, [x29, 80]
	cmp	w0, 32
	bgt	.L4176
	ldr	x0, [x20, 616]
	cbnz	x0, .L4176
	ldr	w0, [x19, 1608]
	cbz	w0, .L4169
	ldr	w0, [x20, 14932]
	cbz	w0, .L4169
	ldr	w2, [x19, 1688]
	ldr	w1, [x20, 14936]
	cmp	w1, w2
	beq	.L4169
	ldr	w2, [x19, 1692]
	cmp	w0, w2
	beq	.L4169
	ldr	x2, .LC987
	str	w1, [x19, 1688]
	str	w0, [x19, 1692]
	ldr	x4, [x2]
	cbz	x4, .L4169
	ldr	w0, [x19, 1644]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 120
	blr	x4
	b	.L4169
	.size	H264DEC_DecodePacket, .-H264DEC_DecodePacket
	.align	3
.LC982:
	.xword	.LC53
	.align	3
.LC983:
	.xword	.LC55
	.align	3
.LC984:
	.xword	s_pstVfmwChan
	.align	3
.LC985:
	.xword	.LANCHOR1
	.align	3
.LC986:
	.xword	.LC799
	.align	3
.LC987:
	.xword	g_event_report
	.align	3
.LC989:
	.xword	.LC988
	.align	3
.LC991:
	.xword	.LC990
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264DEC_VDMPostProc
	.type	H264DEC_VDMPostProc, %function
H264DEC_VDMPostProc:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 61440
	mov	w25, w1
	mov	x23, x3
	mov	w26, w4
	mov	w22, w5
	bl	_mcount
	ldr	x2, [x19, 616]
	ldr	x3, [x19]
	ldr	x0, [x20, 2352]
	ldrb	w1, [x2, 17]
	ldr	w24, [x3, 636]
	strb	w1, [x0, 5]
	ldrb	w1, [x2, 4]
	str	w1, [x0, 8]
	ldr	w21, [x19, 624]
	str	w25, [x20, 2404]
	cbnz	w21, .L4225
	cbz	w26, .L4226
	ldr	x5, .LC992
	sbfiz	x22, x22, 6, 32
	add	x22, x5, x22
	ldr	w0, [x22, 44]
	cmp	w0, 3
	beq	.L4256
	cmp	w0, 1
	beq	.L4226
	mov	x1, x23
	mov	x0, x19
	bl	StorePicInDPB
	cmp	w0, 1
	mov	w22, w0
	bls	.L4230
.L4259:
	ldr	x1, [x20, 2352]
	add	x0, x19, 65536
	mov	w2, 1
	mov	w23, -1
	mov	w21, w23
	ldr	w0, [x0, 1644]
	ldr	w1, [x1, 648]
	bl	FSP_ClearLogicFs
	ldr	x1, .LC994
	mov	w2, w22
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	ClearAllSlice
	add	x1, x19, 20480
	ldr	w4, [x19, 14948]
	add	x5, x1, 3072
	mov	w2, 2
	mov	w3, 23352
	mov	w0, 7
	strb	w2, [x1, 3225]
	movk	w3, 0x1, lsl 16
	str	w0, [x1, 3236]
	mov	w2, 32
	strb	wzr, [x1, 3224]
	mov	w0, 3
	strb	w2, [x1, 3226]
	mov	w2, 262144
	str	w4, [x1, 3232]
	str	w3, [x1, 3240]
	stp	w23, wzr, [x5, 180]
	stp	wzr, w2, [x5, 188]
	str	w0, [x1, 3248]
	mov	x0, x19
	bl	ClearDPB
	str	xzr, [x20, 2352]
.L4228:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4225:
	mov	x0, x19
	bl	ClearAllSlice
	mov	x1, x23
	mov	x0, x19
	bl	StorePicInDPB
	cbnz	w0, .L4257
.L4242:
	mov	x0, x19
	bl	FlushDPB
	cbnz	w0, .L4258
.L4243:
	add	x1, x19, 65536
	add	x0, x19, 20480
	mov	w4, 32
	mov	w7, 23352
	movk	w7, 0x1, lsl 16
	mov	w6, 2
	str	wzr, [x1, 308]
	mov	w5, 7
	mov	w3, 3
	mov	w2, -1
	ldr	w8, [x19, 14948]
	mov	w1, 262144
	strb	w4, [x0, 3226]
	add	x4, x0, 3072
	strb	wzr, [x0, 3224]
	mov	w21, 0
	strb	w6, [x0, 3225]
	str	w8, [x0, 3232]
	str	w5, [x0, 3236]
	str	w7, [x0, 3240]
	stp	w3, w2, [x4, 176]
	stp	wzr, wzr, [x4, 184]
	str	w1, [x0, 3264]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4226:
	mov	x0, x19
	bl	ClearAllSlice
	mov	x1, x23
	mov	x0, x19
	bl	StorePicInDPB
	cmp	w0, 1
	mov	w22, w0
	bhi	.L4259
.L4230:
	cmp	w24, 1
	beq	.L4260
.L4231:
	add	x19, x19, 65536
	mov	w0, 1
	str	w0, [x19, 308]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4258:
	ldr	x1, .LC1001
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	b	.L4243
	.p2align 3
.L4257:
	ldr	x1, .LC999
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	b	.L4242
	.p2align 3
.L4256:
	mov	x0, x19
	bl	ClearAllSlice
	b	.L4228
	.p2align 3
.L4260:
	ldr	x24, [x19, 616]
	ldr	w0, [x24, 316]
	add	x0, x24, x0, lsl 2
	ldr	w25, [x0, 584]
	mov	w0, w25
	bl	MEM_Phy2Vir
	mov	x23, x0
	ldr	w3, [x24, 36]
	mov	w1, w25
	ldr	w4, [x24, 44]
	ldr	x2, .LC995
	mul	w22, w4, w3
	ldr	x3, [x2, 280]
	lsl	w2, w22, 2
	blr	x3
	cbz	w22, .L4244
	mov	w4, 0
	mov	w8, 0
	mov	w7, 2147483647
	mov	w3, 0
	mov	w2, 0
	b	.L4239
	.p2align 3
.L4262:
	csel	w7, w7, w0, le
.L4238:
	add	w2, w2, 1
	add	w4, w4, w0
	cmp	w22, w2
	beq	.L4261
.L4239:
	ubfiz	x0, x2, 2, 30
	ldr	w0, [x23, x0]
	and	w1, w0, 16383
	and	w5, w0, 8191
	neg	w1, w1
	tbz	x0, 13, .L4234
	and	w5, w1, 8191
.L4234:
	asr	w0, w0, 14
	and	w6, w0, 4095
	and	w1, w0, 2047
	tbz	x0, 11, .L4236
	neg	w0, w6
	and	w1, w0, 2047
.L4236:
	add	w0, w5, w1
	cmp	w3, w0
	csel	w3, w3, w0, ge
	cmp	w7, w0
	cbnz	w0, .L4262
	add	w8, w8, 1
	b	.L4238
	.p2align 3
.L4261:
	lsl	w0, w8, 2
	sub	w0, w0, w8
	lsl	w1, w0, 5
	add	w0, w0, w1
	add	w8, w0, w8
.L4232:
	udiv	w8, w8, w22
	ldr	x1, [x20, 2352]
	cmp	w8, 100
	csel	w7, w7, wzr, ne
	udiv	w4, w4, w22
	cbz	x1, .L4241
	ldr	w0, [x1, 260]
	cmp	w0, w3
	csel	w3, w0, w3, cs
	str	w3, [x1, 260]
	ldr	x1, [x20, 2352]
	ldr	w0, [x1, 264]
	cmp	w0, w7
	csel	w7, w0, w7, cs
	str	w7, [x1, 264]
	ldr	x0, [x20, 2352]
	str	w4, [x0, 268]
	ldr	x0, [x20, 2352]
	str	w8, [x0, 272]
	ldr	x0, [x20, 2352]
	ldr	w1, [x0, 260]
	str	w1, [x20, 1964]
	ldr	w1, [x0, 264]
	str	w1, [x20, 1968]
	str	w4, [x20, 1972]
	ldr	w0, [x0, 272]
	str	w0, [x20, 1976]
	b	.L4231
.L4244:
	mov	w8, 0
	mov	w4, 0
	mov	w7, 2147483647
	mov	w3, 0
	b	.L4232
.L4241:
	ldr	x1, .LC997
	mov	w0, 0
	bl	dprint_vfmw
	b	.L4231
	.size	H264DEC_VDMPostProc, .-H264DEC_VDMPostProc
	.align	3
.LC992:
	.xword	g_VdmDrvParam
	.align	3
.LC994:
	.xword	.LC993
	.align	3
.LC995:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC997:
	.xword	.LC996
	.align	3
.LC999:
	.xword	.LC998
	.align	3
.LC1001:
	.xword	.LC1000
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264DEC_GetImageBuffer
	.type	H264DEC_GetImageBuffer, %function
H264DEC_GetImageBuffer:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	add	x19, x21, 65536
	bl	_mcount
	ldr	w0, [x19, 300]
	cbz	w0, .L4280
	sub	w0, w0, #1
	mov	w4, 848
	mov	x2, 30072
	add	x1, x21, 28672
	add	x1, x1, 552
	umaddl	x4, w0, w4, x2
	add	x4, x21, x4
	.p2align 2
.L4271:
	ldrb	w0, [x1, 1]
	cbnz	w0, .L4266
	cbz	x1, .L4267
	add	x23, x21, 24576
	ldr	w3, [x23, 3708]
	cbz	w3, .L4267
	ldr	x0, [x21, 27896]
	cmp	x0, x1
	beq	.L4266
	sub	w3, w3, #1
	mov	x0, x21
	add	x3, x21, x3, lsl 3
	b	.L4268
	.p2align 3
.L4269:
	ldr	x2, [x0, 27896]
	cmp	x2, x1
	beq	.L4266
.L4268:
	cmp	x3, x0
	add	x0, x0, 8
	bne	.L4269
.L4267:
	ldr	w0, [x19, 1644]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	beq	.L4280
	cmn	w0, #1
	beq	.L4301
.L4299:
	mov	w0, 0
.L4303:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4266:
	add	x1, x1, 848
	cmp	x1, x4
	bne	.L4271
	add	x2, x29, 76
	add	x1, x29, 72
	add	x0, x21, 8
	bl	GetQueueImgNum
	ldr	x1, .LC1003
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x1, .LC1005
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x19, 300]
	cbz	w0, .L4302
	ldr	x20, .LC1009
	mov	w22, 0
	add	x23, x21, 24576
	.p2align 2
.L4278:
	uxtw	x1, w22
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 1
	sub	x1, x0, x1
	lsl	x1, x1, 4
	add	x0, x21, x1
	add	x1, x1, 28672
	add	x0, x0, 28672
	add	x1, x21, x1
	adds	x1, x1, 552
	ldrb	w3, [x0, 553]
	ldrb	w4, [x0, 556]
	beq	.L4283
	ldr	w5, [x23, 3708]
	cbz	w5, .L4283
	ldr	x0, [x21, 27896]
	cmp	x1, x0
	beq	.L4285
	sub	w5, w5, #1
	mov	x0, x21
	add	x5, x21, x5, lsl 3
	b	.L4276
	.p2align 3
.L4277:
	ldr	x2, [x0, 27896]
	cmp	x1, x2
	beq	.L4285
.L4276:
	cmp	x5, x0
	add	x0, x0, 8
	bne	.L4277
.L4283:
	mov	w5, 1
.L4275:
	mov	w2, w22
	mov	x1, x20
	mov	w0, 0
	add	w22, w22, 1
	bl	dprint_vfmw
	ldr	w0, [x19, 300]
	cmp	w0, w22
	bhi	.L4278
.L4279:
	ldp	w2, w3, [x29, 72]
	ldr	x1, .LC1007
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x19, 300]
	ldr	w2, [x23, 3708]
	ldp	w3, w1, [x29, 72]
	sub	w0, w0, #2
	sub	w0, w0, w2
	add	w1, w3, w1
	cmp	w1, w0
	bge	.L4299
	ldr	x1, .LC1011
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x21
	bl	ClearAll
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, 0
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4280:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	mov	w0, 1
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4285:
	mov	w5, 0
	b	.L4275
.L4301:
	ldr	w0, [x19, 1644]
	add	x1, x21, 8
	bl	FSP_ClearNotInVoQueue
	mov	w0, 0
	b	.L4303
.L4302:
	add	x23, x21, 24576
	b	.L4279
	.size	H264DEC_GetImageBuffer, .-H264DEC_GetImageBuffer
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
	.global	H264DEC_GetImageWidth
	.type	H264DEC_GetImageWidth, %function
H264DEC_GetImageWidth:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 16384
	bl	_mcount
	ldr	w0, [x19, 1840]
	ldr	x19, [sp, 16]
	add	w0, w0, 1
	lsl	w0, w0, 4
	ldp	x29, x30, [sp], 32
	ret
	.size	H264DEC_GetImageWidth, .-H264DEC_GetImageWidth
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264DEC_GetImageHeight
	.type	H264DEC_GetImageHeight, %function
H264DEC_GetImageHeight:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 16384
	add	x19, x19, 12288
	mov	w0, 2
	ldr	w1, [x1, 1844]
	ldrb	w2, [x19, 2706]
	add	w1, w1, 1
	ldr	x19, [sp, 16]
	sub	w0, w0, w2
	lsl	w1, w1, 4
	ldp	x29, x30, [sp], 32
	mul	w0, w1, w0
	ret
	.size	H264DEC_GetImageHeight, .-H264DEC_GetImageHeight
	.global	TmpBuf
	.global	g_CabacMN
	.global	quant8_org
	.global	quant_org
	.global	quant8_inter_default
	.global	quant8_intra_default
	.global	quant_inter_default
	.global	quant_intra_default
	.global	g_ZZ_SCAN8
	.global	g_ZZ_SCAN
	.global	CalcZeroNum
	.global	g_AspecRatioIdc
	.global	g_NalTypeEOPIC
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.11626, %object
	.size	__func__.11626, 23
__func__.11626:
	.string	"RemoveFrameStoreOutDPB"
	.align	3
.LANCHOR2 = . + 0
	.type	g_ZZ_SCAN, %object
	.size	g_ZZ_SCAN, 16
g_ZZ_SCAN:
	.byte	0
	.byte	1
	.byte	4
	.byte	8
	.byte	5
	.byte	2
	.byte	3
	.byte	6
	.byte	9
	.byte	12
	.byte	13
	.byte	10
	.byte	7
	.byte	11
	.byte	14
	.byte	15
	.type	g_ZZ_SCAN8, %object
	.size	g_ZZ_SCAN8, 64
g_ZZ_SCAN8:
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
	.type	__func__.12633, %object
	.size	__func__.12633, 12
__func__.12633:
	.string	"H264_DecPPS"
	.zero	4
	.type	SarTable.12711, %object
	.size	SarTable.12711, 136
SarTable.12711:
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
	.type	__func__.12893, %object
	.size	__func__.12893, 12
__func__.12893:
	.string	"H264_DecSEI"
	.zero	4
	.type	__func__.11744, %object
	.size	__func__.11744, 13
__func__.11744:
	.string	"DirectOutput"
	.zero	3
	.type	__func__.12207, %object
	.size	__func__.12207, 8
__func__.12207:
	.string	"InitDPB"
	.type	__func__.13162, %object
	.size	__func__.13162, 18
__func__.13162:
	.string	"H264_VES_Splitter"
	.zero	6
	.type	__func__.11871, %object
	.size	__func__.11871, 14
__func__.11871:
	.string	"StorePicInDPB"
	.zero	2
	.type	__FUNCTION__.13131, %object
	.size	__FUNCTION__.13131, 13
__FUNCTION__.13131:
	.string	"H264DEC_Init"
	.zero	3
	.type	__FUNCTION__.12344, %object
	.size	__FUNCTION__.12344, 8
__FUNCTION__.12344:
	.string	"InitPic"
	.type	__func__.13036, %object
	.size	__func__.13036, 15
__func__.13036:
	.string	"H264_DecOneNal"
	.data
	.align	3
.LANCHOR1 = . + 0
	.type	quant_org, %object
	.size	quant_org, 16
quant_org:
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.type	quant8_org, %object
	.size	quant8_org, 64
quant8_org:
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.type	quant_intra_default, %object
	.size	quant_intra_default, 16
quant_intra_default:
	.word	471076102
	.word	538711053
	.word	622861332
	.word	707076124
	.type	quant_inter_default, %object
	.size	quant_inter_default, 16
quant_inter_default:
	.word	403967498
	.word	454562830
	.word	505092116
	.word	572398360
	.type	quant8_intra_default, %object
	.size	quant8_intra_default, 64
quant8_intra_default:
	.word	269289990
	.word	454629138
	.word	303041290
	.word	488315159
	.word	387059725
	.word	522001177
	.word	420942352
	.word	555687195
	.word	454629138
	.word	606150429
	.word	488315159
	.word	639901983
	.word	522001177
	.word	673588257
	.word	555687195
	.word	707274276
	.type	quant8_inter_default, %object
	.size	quant8_inter_default, 256
quant8_inter_default:
	.word	286199049
	.word	404100371
	.word	319884557
	.word	421008917
	.word	353571087
	.word	454629398
	.word	370479889
	.word	471537944
	.word	404100371
	.word	505158425
	.word	421008917
	.word	538844187
	.word	454629398
	.word	555752988
	.word	471537944
	.word	589373470
	.zero	192
	.type	g_NalTypeEOPIC, %object
	.size	g_NalTypeEOPIC, 12
g_NalTypeEOPIC:
	.byte	0
	.byte	0
	.byte	1
	.byte	30
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.zero	4
	.type	g_CabacMN, %object
	.size	g_CabacMN, 5120
g_CabacMN:
	.word	388044546
	.word	352326208
	.word	153820416
	.word	721207
	.word	4522025
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	521477919
	.word	422707200
	.word	0
	.word	0
	.word	87683918
	.word	-180289218
	.word	17367089
	.word	-613020375
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	21230414
	.word	-180289218
	.word	440602714
	.word	157864575
	.word	-328728576
	.word	0
	.word	0
	.word	0
	.word	204602441
	.word	288553558
	.word	-278922691
	.word	154007875
	.word	-78971830
	.word	-78579384
	.word	20578304
	.word	0
	.word	-45745583
	.word	-178256329
	.word	121895766
	.word	39321658
	.word	-45287842
	.word	87426117
	.word	-45023144
	.word	0
	.word	370745856
	.word	268442146
	.word	320219136
	.word	721207
	.word	4522025
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	521477919
	.word	422707200
	.word	0
	.word	0
	.word	37878343
	.word	-212925132
	.word	-32963543
	.word	-478802647
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	-62064057
	.word	-212925132
	.word	956442916
	.word	440783743
	.word	-245039104
	.word	0
	.word	0
	.word	0
	.word	154336582
	.word	171312709
	.word	-212205516
	.word	137101122
	.word	-11730618
	.word	-27854008
	.word	3997696
	.word	0
	.word	-28968110
	.word	-161480133
	.word	38534487
	.word	-43777736
	.word	-45417899
	.word	3931473
	.word	-111740065
	.word	0
	.word	487594240
	.word	234886184
	.word	336207104
	.word	721207
	.word	4522025
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	521477919
	.word	422707200
	.word	0
	.word	0
	.word	437320789
	.word	-395967175
	.word	-164364994
	.word	-446493399
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	-28640171
	.word	-395967175
	.word	905979178
	.word	207741055
	.word	-361431040
	.word	0
	.word	0
	.word	0
	.word	104460105
	.word	238680669
	.word	-229049812
	.word	70714167
	.word	-61866421
	.word	-194905806
	.word	20709376
	.word	0
	.word	-178654873
	.word	-344714439
	.word	339346516
	.word	106955071
	.word	-78253206
	.word	88016459
	.word	-44368027
	.word	0
	.word	388044546
	.word	352326208
	.word	153820416
	.word	3013710
	.word	-44040151
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	203950899
	.word	238747648
	.word	0
	.word	0
	.word	87683918
	.word	-180289218
	.word	17367089
	.word	-613020375
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	21230414
	.word	-180289218
	.word	440602714
	.word	157864575
	.word	-328728576
	.word	0
	.word	0
	.word	0
	.word	204602441
	.word	288553558
	.word	-278922691
	.word	154007875
	.word	-78971830
	.word	-78579384
	.word	20578304
	.word	0
	.word	-45745583
	.word	-178256329
	.word	121895766
	.word	39321658
	.word	-45287842
	.word	87426117
	.word	-45023144
	.word	0
	.word	370745856
	.word	268442146
	.word	320219136
	.word	219088691
	.word	38797353
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	421532977
	.word	355860480
	.word	0
	.word	0
	.word	37878343
	.word	-212925132
	.word	-32963543
	.word	-478802647
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	-62064057
	.word	-212925132
	.word	956442916
	.word	440783743
	.word	-245039104
	.word	0
	.word	0
	.word	0
	.word	154336582
	.word	171312709
	.word	-212205516
	.word	137101122
	.word	-11730618
	.word	-27854008
	.word	3997696
	.word	0
	.word	-28968110
	.word	-161480133
	.word	38534487
	.word	-43777736
	.word	-45417899
	.word	3931473
	.word	-111740065
	.word	0
	.word	487594240
	.word	234886184
	.word	336207104
	.word	119732056
	.word	-327221207
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	354489138
	.word	289210368
	.word	0
	.word	0
	.word	437320789
	.word	-395967175
	.word	-164364994
	.word	-446493399
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	-28640171
	.word	-395967175
	.word	905979178
	.word	207741055
	.word	-361431040
	.word	0
	.word	0
	.word	0
	.word	104460105
	.word	238680669
	.word	-229049812
	.word	70714167
	.word	-61866421
	.word	-194905806
	.word	20709376
	.word	0
	.word	-178654873
	.word	-344714439
	.word	339346516
	.word	106955071
	.word	-78253206
	.word	88016459
	.word	-44368027
	.word	0
	.word	-276827290
	.word	5437770
	.word	-345250433
	.word	-511711105
	.word	-295705217
	.word	-344792449
	.word	0
	.word	0
	.word	-277089165
	.word	-260377229
	.word	-45614550
	.word	-80544458
	.word	-29491142
	.word	20971080
	.word	-11864229
	.word	0
	.word	-111282857
	.word	-45221049
	.word	-62915516
	.word	-195757762
	.word	-113178563
	.word	87621186
	.word	20971581
	.word	-28442624
	.word	402657033
	.word	135859474
	.word	252251411
	.word	170200082
	.word	102568993
	.word	253625389
	.word	20578366
	.word	121438208
	.word	-94504364
	.word	-129040318
	.word	-12124098
	.word	-29557189
	.word	-78906050
	.word	-63244478
	.word	-11599801
	.word	54788096
	.word	252053011
	.word	118492174
	.word	302845195
	.word	219090704
	.word	202837271
	.word	252972570
	.word	237769000
	.word	288292864
	.word	-197132732
	.word	-246090904
	.word	-79430885
	.word	-47710676
	.word	3076160
	.word	-129698226
	.word	-95553962
	.word	0
	.word	20055860
	.word	170065964
	.word	187040045
	.word	3015980
	.word	521208115
	.word	120724499
	.word	270601790
	.word	0
	.word	203819821
	.word	254217002
	.word	220991533
	.word	204016177
	.word	505549354
	.word	171381043
	.word	288227417
	.word	0
	.word	170719550
	.word	254021160
	.word	270208029
	.word	19665956
	.word	304088362
	.word	19925566
	.word	288229696
	.word	0
	.word	403772693
	.word	420880155
	.word	371004195
	.word	238160441
	.word	121634381
	.word	-61670050
	.word	155579501
	.word	0
	.word	-45680547
	.word	-161815937
	.word	-195235529
	.word	-163775938
	.word	-62786487
	.word	-129173168
	.word	-145166482
	.word	0
	.word	-210964124
	.word	-211422373
	.word	-195103144
	.word	-262867370
	.word	-111938729
	.word	-312606394
	.word	4782922
	.word	305856512
	.word	451745519
	.word	451878631
	.word	485237225
	.word	635773417
	.word	686040815
	.word	569714929
	.word	704259585
	.word	688979968
	.word	-194448031
	.word	-262080168
	.word	-128583339
	.word	-145362088
	.word	71499085
	.word	-45286836
	.word	171638604
	.word	-11337728
	.word	618472670
	.word	551953890
	.word	752886510
	.word	586230001
	.word	569975803
	.word	553657858
	.word	554506019
	.word	221904896
	.word	-11863455
	.word	-111416193
	.word	-178131884
	.word	-179307959
	.word	-62196906
	.word	-211749535
	.word	-311099392
	.word	0
	.word	-127471260
	.word	6225920
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	519707395
	.word	437649408
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-110890401
	.word	39780352
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	503126528
	.word	371064832
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-63374510
	.word	-112399747
	.word	-129041631
	.word	-63898059
	.word	-46206137
	.word	-162532266
	.word	-212143519
	.word	0
	.word	-62193080
	.word	-179569337
	.word	254735173
	.word	4063297
	.word	354808136
	.word	154734646
	.word	4066376
	.word	0
	.word	636494844
	.word	653797117
	.word	620963333
	.word	704652048
	.word	655756848
	.word	455415100
	.word	205783649
	.word	0
	.word	5045066
	.word	4650315
	.word	21233729
	.word	-230096066
	.word	71237444
	.word	-213185737
	.word	88083526
	.word	0
	.word	536421361
	.word	587014659
	.word	620700165
	.word	537600773
	.word	571221771
	.word	505225754
	.word	489100098
	.word	0
	.word	0
	.word	0
	.word	-45351145
	.word	19005739
	.word	3604023
	.word	3998016
	.word	4519772
	.word	0
	.word	-277287824
	.word	-294455979
	.word	-245566887
	.word	-431492783
	.word	-229638076
	.word	-230234056
	.word	-381360078
	.word	-179699712
	.word	401808115
	.word	686895602
	.word	738405638
	.word	740434230
	.word	324141056
	.word	0
	.word	0
	.word	0
	.word	-227871903
	.word	-245697446
	.word	-296159671
	.word	-145755562
	.word	-162924986
	.word	-163185854
	.word	-146736326
	.word	37421056
	.word	368449781
	.word	486022399
	.word	486743305
	.word	588520740
	.word	239271936
	.word	0
	.word	0
	.word	0
	.word	-444668830
	.word	-412751549
	.word	-464327586
	.word	-262935954
	.word	-346296730
	.word	-211950721
	.word	0
	.word	0
	.word	-111346855
	.word	-111086740
	.word	-95617492
	.word	2949172
	.word	-46072261
	.word	-62456757
	.word	-128782490
	.word	0
	.word	-27919794
	.word	-11798195
	.word	37094706
	.word	-45874894
	.word	103480401
	.word	20970566
	.word	4391481
	.word	-28573696
	.word	186384936
	.word	53215281
	.word	3015212
	.word	36896815
	.word	69665342
	.word	103678006
	.word	53871162
	.word	71237632
	.word	-211095446
	.word	-162010254
	.word	-294718878
	.word	-361829526
	.word	-295179413
	.word	-378739088
	.word	-161418145
	.word	-77922304
	.word	235604750
	.word	151720459
	.word	352917502
	.word	552673521
	.word	585836521
	.word	719268321
	.word	786704116
	.word	354222080
	.word	-47251647
	.word	-12978339
	.word	-145947880
	.word	2752560
	.word	3668539
	.word	-112724909
	.word	-178789769
	.word	0
	.word	186844224
	.word	20777763
	.word	303631384
	.word	220007716
	.word	-161613495
	.word	-28766930
	.word	154270052
	.word	0
	.word	104007225
	.word	120915508
	.word	104270637
	.word	237242421
	.word	-11401417
	.word	-45215954
	.word	371195732
	.word	0
	.word	-144840098
	.word	-78247613
	.word	-61802923
	.word	-12187844
	.word	154797373
	.word	204607282
	.word	305205558
	.word	0
	.word	770192851
	.word	820396501
	.word	736962550
	.word	503910938
	.word	337313849
	.word	-229442741
	.word	-312353411
	.word	0
	.word	-45418660
	.word	-128456322
	.word	20643101
	.word	-14417626
	.word	36436535
	.word	3801152
	.word	-45418918
	.word	0
	.word	154468917
	.word	87424573
	.word	3670072
	.word	-213910724
	.word	-12712903
	.word	-96140231
	.word	237438003
	.word	222560256
	.word	419897081
	.word	469965828
	.word	536879871
	.word	503717382
	.word	537468691
	.word	437983774
	.word	622074914
	.word	289800192
	.word	170460974
	.word	-13433039
	.word	137627945
	.word	103744055
	.word	220793388
	.word	103941429
	.word	221316159
	.word	104857600
	.word	452992000
	.word	536615686
	.word	570957322
	.word	404103443
	.word	371202591
	.word	355015212
	.word	388960321
	.word	239534080
	.word	87426620
	.word	104531525
	.word	4652061
	.word	85919530
	.word	20708922
	.word	-45548207
	.word	-178192384
	.word	0
	.word	54526269
	.word	155123712
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	21169467
	.word	155385856
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-28967365
	.word	105250816
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	138151487
	.word	289472512
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-13631420
	.word	-62523304
	.word	3803141
	.word	168693266
	.word	219873832
	.word	3865926
	.word	-95422379
	.word	0
	.word	120721447
	.word	86770740
	.word	187759420
	.word	-12910533
	.word	371262764
	.word	237764430
	.word	3934533
	.word	0
	.word	270406176
	.word	304289309
	.word	404690726
	.word	304813097
	.word	188680507
	.word	155254622
	.word	-27658388
	.word	0
	.word	170658079
	.word	204145461
	.word	237111846
	.word	-46920408
	.word	287311660
	.word	119934258
	.word	171514411
	.word	0
	.word	353900308
	.word	437721888
	.word	471276568
	.word	388503584
	.word	471668522
	.word	322508341
	.word	373099350
	.word	0
	.word	0
	.word	0
	.word	-96274141
	.word	-114624467
	.word	-80677832
	.word	-96666818
	.word	-129828788
	.word	0
	.word	-61867705
	.word	-79300794
	.word	-129829308
	.word	-313920443
	.word	-263786173
	.word	-331420346
	.word	-264050111
	.word	-331415552
	.word	167647991
	.word	569845753
	.word	704523523
	.word	822684955
	.word	607846400
	.word	0
	.word	0
	.word	0
	.word	-78251439
	.word	-162662063
	.word	-279908791
	.word	-62196141
	.word	-146278589
	.word	-12715966
	.word	-230555589
	.word	37421056
	.word	368255474
	.word	670641918
	.word	855784454
	.word	1024538402
	.word	708706304
	.word	0
	.word	0
	.word	0
	.word	-645927333
	.word	-278862255
	.word	-580720538
	.word	-379460233
	.word	-396104850
	.word	-295248769
	.word	0
	.word	0
	.word	5307225
	.word	-111215524
	.word	-378474169
	.word	-113442763
	.word	-79497907
	.word	-145688748
	.word	-162013569
	.word	0
	.word	-211291301
	.word	-145100196
	.word	-129174441
	.word	-378607511
	.word	-162599824
	.word	-278678913
	.word	-1166029185
	.word	-763428864
	.word	70060572
	.word	169812469
	.word	886379023
	.word	469771242
	.word	652681728
	.word	669917428
	.word	1721892864
	.word	955318272
	.word	-344004228
	.word	-328276354
	.word	-411242647
	.word	-444996235
	.word	-278469003
	.word	-445325446
	.word	-161484188
	.word	-127991808
	.word	335155962
	.word	234887924
	.word	535831015
	.word	568993252
	.word	669133538
	.word	802565596
	.word	836643311
	.word	537460736
	.word	2555969
	.word	-246096513
	.word	-345637593
	.word	-80348867
	.word	-179572403
	.word	-279189653
	.word	-412097414
	.word	0
	.word	-62719154
	.word	-62392248
	.word	37486391
	.word	-112788917
	.word	-128328073
	.word	-45408236
	.word	504812671
	.word	0
	.word	570170634
	.word	637219811
	.word	670512350
	.word	1170621377
	.word	754655239
	.word	937631745
	.word	6948
	.word	0
	.word	-277879694
	.word	-94765488
	.word	-61671595
	.word	-128843960
	.word	88080707
	.word	154665029
	.word	21301061
	.word	0
	.word	1169768385
	.word	1119899062
	.word	920204509
	.word	703996928
	.word	687808014
	.word	471471909
	.word	204933953
	.word	0
	.word	-28707736
	.word	-144973441
	.word	-179505620
	.word	-164301255
	.word	-147132344
	.word	-112853947
	.word	-78973098
	.word	0
	.word	3603261
	.word	3866428
	.word	-46270397
	.word	-413863350
	.word	-79624908
	.word	37290045
	.word	-146410170
	.word	305594368
	.word	568795874
	.word	618931940
	.word	652550894
	.word	602940146
	.word	553133562
	.word	587210250
	.word	470948377
	.word	489226240
	.word	-112854461
	.word	-263324096
	.word	37616195
	.word	-46136775
	.word	-46006974
	.word	4065587
	.word	-12386745
	.word	-28639232
	.word	635381724
	.word	685450978
	.word	786377442
	.word	686305763
	.word	653535478
	.word	654126843
	.word	521411870
	.word	422313984
	.word	53937976
	.word	121047101
	.word	37943074
	.word	18877215
	.word	87359031
	.word	-29163447
	.word	-128385024
	.word	0
	.word	-62455750
	.word	121438208
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	4915784
	.word	139264000
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-12126392
	.word	238813184
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	204475185
	.word	439156736
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-46858172
	.word	-112527528
	.word	53741316
	.word	168300808
	.word	269681445
	.word	-12715191
	.word	-12125106
	.word	0
	.word	153686553
	.word	153093419
	.word	154075180
	.word	3342894
	.word	321322050
	.word	254151722
	.word	153223257
	.word	0
	.word	237179423
	.word	287511838
	.word	288166954
	.word	304945946
	.word	271976258
	.word	272108361
	.word	172226164
	.word	0
	.word	270860335
	.word	304286501
	.word	204016169
	.word	36703273
	.word	220790843
	.word	53613352
	.word	54661682
	.word	0
	.word	370546454
	.word	454369556
	.word	438050328
	.word	455217706
	.word	421990962
	.word	205919542
	.word	239536979
	.word	0
	.word	0
	.word	0
	.word	-79233000
	.word	-14352854
	.word	-30083271
	.word	-96469951
	.word	-62654126
	.word	0
	.word	-78251439
	.word	-162662063
	.word	-279908791
	.word	-62196141
	.word	-146278589
	.word	-12715966
	.word	-230555589
	.word	37421056
	.word	301342963
	.word	720843259
	.word	889208835
	.word	1141522971
	.word	792264704
	.word	0
	.word	0
	.word	0
	.word	-44958388
	.word	-112657842
	.word	-196545980
	.word	-45680052
	.word	-79496386
	.word	3800125
	.word	-147062474
	.word	37355520
	.word	301342963
	.word	720843259
	.word	889208835
	.word	1141522971
	.word	792264704
	.word	0
	.word	0
	.word	0
	.word	-595595429
	.word	-228595884
	.word	-413731751
	.word	-279191169
	.word	-229839257
	.word	-212149377
	.word	0
	.word	0
	.word	189793612
	.word	39060814
	.word	-395056558
	.word	-146931659
	.word	3928661
	.word	-212208802
	.word	-178461825
	.word	0
	.word	-61410216
	.word	-78447288
	.word	-62654392
	.word	-262539451
	.word	-12909246
	.word	70908999
	.word	-28900806
	.word	-11927552
	.word	69664810
	.word	119671581
	.word	136250917
	.word	120193832
	.word	136383787
	.word	220464175
	.word	53936698
	.word	104595456
	.word	-360716417
	.word	-411507329
	.word	-311236235
	.word	-411638155
	.word	-395189130
	.word	-512173188
	.word	-161549978
	.word	-161284096
	.word	301142263
	.word	301210603
	.word	635578840
	.word	718745809
	.word	669003480
	.word	885862103
	.word	886647789
	.word	537591808
	.word	-97057731
	.word	-229385345
	.word	-345705927
	.word	-196872889
	.word	-162665643
	.word	-262608536
	.word	-245179521
	.word	0
	.word	-64159931
	.word	4127027
	.word	-63964630
	.word	-47580619
	.word	139261774
	.word	-179107532
	.word	4455258
	.word	0
	.word	137104172
	.word	237635376
	.word	70779956
	.word	220530993
	.word	322570800
	.word	204275781
	.word	337709119
	.word	0
	.word	-211104129
	.word	-77852359
	.word	-78187682
	.word	-195297715
	.word	4718409
	.word	71366993
	.word	88084281
	.word	0
	.word	1036597458
	.word	1053708733
	.word	770450430
	.word	470753793
	.word	654384657
	.word	338039341
	.word	255197263
	.word	0
	.word	-78645912
	.word	-178527617
	.word	-162334672
	.word	-130156478
	.word	-112790965
	.word	-162531501
	.word	-195236244
	.word	0
	.word	21229896
	.word	-78907312
	.word	-346821824
	.word	-216012992
	.word	-480376501
	.word	289405002
	.word	-81527269
	.word	224067584
	.word	602808807
	.word	486348810
	.word	452993778
	.word	886319080
	.word	319889177
	.word	605886497
	.word	571416084
	.word	373882880
	.word	21168196
	.word	-163380924
	.word	5046848
	.word	4520782
	.word	121046331
	.word	37817910
	.word	254543164
	.word	38141952
	.word	619718130
	.word	636428289
	.word	571415823
	.word	404300310
	.word	521151250
	.word	521937193
	.word	605821743
	.word	356384768
	.word	4324943
	.word	4783196
	.word	-61871547
	.word	-263455174
	.word	20640590
	.word	-145490863
	.word	-211615744
	.word	0
	.word	54655301
	.word	139264000
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	337777439
	.word	455868416
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-28512682
	.word	205914112
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	304026394
	.word	605552640
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-96992444
	.word	-129502366
	.word	-212731354
	.word	-213976518
	.word	-29626295
	.word	-162729130
	.word	-145492393
	.word	0
	.word	-163445954
	.word	-45814703
	.word	1966343
	.word	-48764086
	.word	272820604
	.word	287649006
	.word	853469823
	.word	0
	.word	319819556
	.word	254022940
	.word	420814356
	.word	520887056
	.word	405405789
	.word	238554937
	.word	438757503
	.word	0
	.word	88142918
	.word	188155192
	.word	4522561
	.word	-95812298
	.word	121043532
	.word	-179110323
	.word	-28501718
	.word	0
	.word	404167440
	.word	404627229
	.word	371791402
	.word	272371508
	.word	238814030
	.word	-260369099
	.word	372775229
	.word	0
	.word	0
	.word	0
	.word	-146278107
	.word	-131271375
	.word	-164039621
	.word	-130025661
	.word	-96143793
	.word	0
	.word	-45156278
	.word	-146213304
	.word	-297012153
	.word	-180356282
	.word	-280235448
	.word	-263981003
	.word	-230951116
	.word	-180092928
	.word	167649014
	.word	536617471
	.word	554114828
	.word	622272294
	.word	339738624
	.word	0
	.word	0
	.word	0
	.word	-45156278
	.word	-146213304
	.word	-297012153
	.word	-180356282
	.word	-280235448
	.word	-263981003
	.word	-230951116
	.word	-180092928
	.word	167649014
	.word	536617471
	.word	554114828
	.word	622272294
	.word	339738624
	.word	0
	.word	0
	.word	0
	.type	CalcZeroNum, %object
	.size	CalcZeroNum, 256
CalcZeroNum:
	.byte	8
	.byte	7
	.byte	6
	.byte	6
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.type	g_AspecRatioIdc, %object
	.size	g_AspecRatioIdc, 112
g_AspecRatioIdc:
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
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC2:
	ASCII(.string	"list[%d][%d]: frame_num=%d, poc=%d\n" )
	.zero	4
.LC4:
	ASCII(.string	"L0: " )
	.zero	3
.LC6:
	ASCII(.string	"\n" )
	.zero	6
.LC8:
	ASCII(.string	"%d " )
	.zero	4
.LC10:
	ASCII(.string	"%dt " )
	.zero	3
.LC12:
	ASCII(.string	"%db " )
	.zero	3
.LC14:
	ASCII(.string	"L1:" )
	.zero	4
.LC16:
	ASCII(.string	"\n\nEND of the bit buffer, copy the first packet!\n\n" )
	.zero	6
.LC18:
	ASCII(.string	"0:phy:0x%x, 1:phy:0x%x; len0:%d len1:%d\n" )
	.zero	7
.LC21:
	ASCII(.string	"0:phy:0x%x, len0:%d\n" )
	.zero	3
.LC23:
	ASCII(.string	"%-50s%50d\n" )
	.zero	5
.LC31:
	ASCII(.string	"%s DPB.fs[%d] = NULL\n" )
	.zero	2
.LC33:
	ASCII(.string	"frame %d, state=%d, is already output\n" )
	.zero	1
.LC35:
	ASCII(.string	"plfs(fs=%p, eFoState=%d) is null, logic_fs_id = %d\n" )
	.zero	4
.LC37:
	ASCII(.string	"not used frame: (%d,%d)\n" )
	.zero	7
.LC39:
	ASCII(.string	"frame skip: is_used=%d,skip=%d\n" )
.LC41:
	ASCII(.string	"topfield skip: is_used=%d,skip=%d\n" )
	.zero	5
.LC43:
	ASCII(.string	"bottom field skip: is_used=%d,skip=%d\n" )
	.zero	1
.LC45:
	ASCII(.string	"err(%d) > out_thr(%d)\n" )
	.zero	1
.LC48:
	ASCII(.string	"exg_pts: %lld <-> %lld\n" )
.LC50:
	ASCII(.string	"stream frame packing type is %d! what can we do?\n" )
	.zero	6
.LC53:
	ASCII(.string	"../../core/syntax/h264.c" )
	.zero	7
.LC55:
	ASCII(.string	"NULL pointer: %s, L%d\n" )
	.zero	1
.LC57:
	ASCII(.string	"framestore %d allocate apc %d\n" )
	.zero	1
.LC59:
	ASCII(.string	"find APC, but logic_fs_id %d abnormal(ref=%d,plfs=%p, pdfs=%p)\n" )
.LC63:
	ASCII(.string	"pH264Ctx->DPB.fs[%d]: frame_num=%d poc=%d is_reference=%d\n" )
	.zero	5
.LC65:
	ASCII(.string	"pH264Ctx->DPB.fs_ref[%d]: frame_num=%d poc=%d is_reference=%d\n" )
	.zero	1
.LC67:
	ASCII(.string	"pH264Ctx->DPB.fs_ref[%d]: frame.poc=%d \n" )
	.zero	7
.LC71:
	ASCII(.string	"\n VFMW ** release streambuff=%p   bitstream_length=%d\n" )
	.zero	1
.LC73:
	ASCII(.string	"clear curr slice.\n" )
	.zero	5
.LC78:
	ASCII(.string	"image size abnormal(%dx%d)\n" )
	.zero	4
.LC80:
	ASCII(.string	"resolution error, ImageWidth=%d, ImageHeight=%d\n" )
	.zero	7
.LC82:
	ASCII(.string	"partition fs memory fail!\n" )
	.zero	5
.LC84:
	ASCII(.string	"ERROR: FSP_ConfigInstance fail!\n" )
	.zero	7
.LC86:
	ASCII(.string	"slice_type %d invalid, clear current slice.\n" )
	.zero	3
.LC88:
	ASCII(.string	"pRepairPic(%p)/found(%d) = 0, clear current slice.\n" )
	.zero	4
.LC90:
	ASCII(.string	"listXsize[%d] = %d, clear current slice.\n" )
	.zero	6
.LC98:
	ASCII(.string	"for P slice size of list equal 0.\n" )
	.zero	5
.LC104:
	ASCII(.string	"for B slice size of two list all equal 0.\n" )
	.zero	5
.LC107:
	ASCII(.string	"init list error.\n" )
	.zero	6
.LC109:
	ASCII(.string	"L0: list after init.\n" )
	.zero	2
.LC112:
	ASCII(.string	"L0: list after reorder.\n" )
	.zero	7
.LC115:
	ASCII(.string	"save pic yuv :  structure = %d;  idc = %d\n" )
	.zero	5
.LC117:
	ASCII(.string	"structure = %d pH264Ctx->CurrPic.pic_width_in_mb = %d pH264Ctx->CurrPic.pic_height_in_mb = %d\n" )
	.zero	1
.LC119:
	ASCII(.string	"nal_ref_idc=%d, structure=%d, image_id=%d, pmv_idc=%d\n" )
	.zero	1
.LC121:
	ASCII(.string	"logic frame id(=%d): get LogicFs error!\n" )
	.zero	7
.LC123:
	ASCII(.string	"phy fs is null: pstDecodeFs = %p, pstDispOutFs = %p\n" )
	.zero	3
.LC127:
	ASCII(.string	"line: %d pstLogicFs is null\n" )
	.zero	3
.LC129:
	ASCII(.string	"SH: first_mb_in_slice" )
	.zero	2
.LC131:
	ASCII(.string	"slicecheck first_mb_in_slice >= MAX_MB_NUM_IN_PIC error.\n" )
	.zero	6
.LC133:
	ASCII(.string	"SH: slice_type" )
	.zero	1
.LC135:
	ASCII(.string	"slice type = %d\n" )
	.zero	7
.LC138:
	ASCII(.string	"slice type = %d, err\n" )
	.zero	2
.LC140:
	ASCII(.string	"slice  pps id = %d\n" )
	.zero	4
.LC142:
	ASCII(.string	"pps with this pic_parameter_set_id = %d havn't decode\n" )
	.zero	1
.LC144:
	ASCII(.string	"sps with this pic_parameter_set_id = %d havn't decode\n" )
	.zero	1
.LC146:
	ASCII(.string	"tmp slice  pps id = %d\n" )
.LC148:
	ASCII(.string	"PPSSPSCheckTmpId: pps with this pic_parameter_set_id = %d havn't decode\n" )
	.zero	7
.LC150:
	ASCII(.string	"PPSSPSCheckTmpId: seq_parameter_set_id out of range.\n" )
	.zero	2
.LC152:
	ASCII(.string	"PPSSPSCheckTmpId: sps with this pic_parameter_set_id = %d havn't decode\n" )
	.zero	7
.LC154:
	ASCII(.string	"new pic flag = %d\n" )
	.zero	5
.LC156:
	ASCII(.string	"SH: ref_pic_list_reordering_flag_l0" )
	.zero	4
.LC158:
	ASCII(.string	"SH: reordering_of_pic_nums_idc_l0" )
	.zero	6
.LC160:
	ASCII(.string	"reorder idc l0 = %d, g_SeErrFlag=%d\n" )
	.zero	3
.LC162:
	ASCII(.string	"SH: abs_diff_pic_num_minus1_l0" )
	.zero	1
.LC164:
	ASCII(.string	"abs_diff_pic_num_minus1_l0 = %d, g_SeErrFlag=%d\n" )
	.zero	7
.LC166:
	ASCII(.string	"SH: long_term_pic_idx_l0" )
	.zero	7
.LC168:
	ASCII(.string	"num of idc l0 exceed\n" )
	.zero	2
.LC170:
	ASCII(.string	"SH: ref_pic_list_reordering_flag_l1" )
	.zero	4
.LC172:
	ASCII(.string	"SH: reordering_of_pic_nums_idc_l1" )
	.zero	6
.LC174:
	ASCII(.string	"reorder idc l1 = %d, g_SeErrFlag=%d\n" )
	.zero	3
.LC176:
	ASCII(.string	"SH: abs_diff_pic_num_minus1_l1" )
	.zero	1
.LC178:
	ASCII(.string	"abs_diff_pic_num_minus1_l1 = %d, g_SeErrFlag=%d\n" )
	.zero	7
.LC180:
	ASCII(.string	"SH: long_term_pic_idx_l1" )
	.zero	7
.LC182:
	ASCII(.string	"num of idc l1 exceed\n" )
	.zero	2
.LC184:
	ASCII(.string	"SH: luma_log2_weight_denom" )
	.zero	5
.LC186:
	ASCII(.string	"SH: chroma_log2_weight_denom" )
	.zero	3
.LC188:
	ASCII(.string	"WP log2 exceed  and err flag = %d\n" )
	.zero	5
.LC190:
	ASCII(.string	"SH: luma_weight_flag_l0" )
.LC192:
	ASCII(.string	"SH: luma_weight_l0" )
	.zero	5
.LC194:
	ASCII(.string	"SH: luma_offset_l0" )
	.zero	5
.LC196:
	ASCII(.string	"SH: chroma_weight_flag_l0" )
	.zero	6
.LC198:
	ASCII(.string	"SH: chroma_weight_l0" )
	.zero	3
.LC200:
	ASCII(.string	"SH: chroma_offset_l0" )
	.zero	3
.LC202:
	ASCII(.string	"SH: luma_weight_flag_l1" )
.LC204:
	ASCII(.string	"SH: luma_weight_l1" )
	.zero	5
.LC206:
	ASCII(.string	"SH: luma_offset_l1" )
	.zero	5
.LC208:
	ASCII(.string	"SH: chroma_weight_flag_l1" )
	.zero	6
.LC210:
	ASCII(.string	"SH: chroma_weight_l1" )
	.zero	3
.LC212:
	ASCII(.string	"SH: chroma_offset_l1" )
	.zero	3
.LC214:
	ASCII(.string	"overflow MAX_MMCO_LEN\n" )
	.zero	1
.LC216:
	ASCII(.string	"SH: memory_management_control_operation" )
.LC218:
	ASCII(.string	"SH: difference_of_pic_nums_minus1" )
	.zero	6
.LC220:
	ASCII(.string	"SH: long_term_pic_num" )
	.zero	2
.LC222:
	ASCII(.string	"SH: long_term_frame_idx" )
.LC224:
	ASCII(.string	"SH: max_long_term_frame_idx_plus1" )
	.zero	6
.LC226:
	ASCII(.string	"mmco exceed 6\n" )
	.zero	1
.LC228:
	ASCII(.string	"SH: no_output_of_prior_pics_flag" )
	.zero	7
.LC230:
	ASCII(.string	"SH: long_term_reference_flag" )
	.zero	3
.LC232:
	ASCII(.string	"IDR and no_output_of_prior_pics_flag = %d\n" )
	.zero	5
.LC234:
	ASCII(.string	"SH: adaptive_ref_pic_marking_mode_flag" )
	.zero	1
.LC236:
	ASCII(.string	"adaptive_ref_pic_marking_mode_flag = %d\n" )
	.zero	7
.LC238:
	ASCII(.string	"MMCO para would save dec err\n" )
	.zero	2
.LC240:
	ASCII(.string	"mulitislice diff no_out_of_prior_pics_flag, used first.\n" )
	.zero	7
.LC242:
	ASCII(.string	"mulitislice diff long_term_reference_flag, used first.\n" )
.LC244:
	ASCII(.string	"mulitislice diff adaptive_ref_pic_marking_mode_flag, used first.\n" )
	.zero	6
.LC246:
	ASCII(.string	"TotalPicNum=%d, SliceNumInPic=%d, TotalNal=%d\n" )
	.zero	1
.LC248:
	ASCII(.string	"SH: pic_parameter_set_id" )
	.zero	7
.LC250:
	ASCII(.string	"pps id:%d in sliceheader err\n" )
	.zero	2
.LC252:
	ASCII(.string	"PPS or SPS of this slice not valid\n" )
	.zero	4
.LC254:
	ASCII(.string	"recover point but isn't I_SLICE.\n" )
	.zero	6
.LC256:
	ASCII(.string	"SH: frame_num" )
	.zero	2
.LC258:
	ASCII(.string	"IDR NAL but frame_num!=0.\n" )
	.zero	5
.LC260:
	ASCII(.string	"SH: field_pic_flag" )
	.zero	5
.LC262:
	ASCII(.string	"SH: bottom_field_flag" )
	.zero	2
.LC264:
	ASCII(.string	"field first_mb_in_slice bigger than pic size\n" )
	.zero	2
.LC266:
	ASCII(.string	"frame first_mb_in_slice bigger than pic size\n" )
	.zero	2
.LC268:
	ASCII(.string	"SH: idr_pic_id" )
	.zero	1
.LC270:
	ASCII(.string	"idr_pic_id bigger than 65535\n" )
	.zero	2
.LC272:
	ASCII(.string	"SH: pic_order_cnt_lsb" )
	.zero	2
.LC274:
	ASCII(.string	"SH: delta_pic_order_cnt_bottom" )
	.zero	1
.LC276:
	ASCII(.string	"SH: delta_pic_order_cnt[0]" )
	.zero	5
.LC278:
	ASCII(.string	"SH: delta_pic_order_cnt[1]" )
	.zero	5
.LC280:
	ASCII(.string	"SH: redundant_pic_cnt" )
	.zero	2
.LC282:
	ASCII(.string	"redundant pic not support.\n" )
	.zero	4
.LC285:
	ASCII(.string	"first_mb_in_slice in currslice small than prevslice in same pic\n" )
	.zero	7
.LC289:
	ASCII(.string	"SH: direct_spatial_mv_pred_flag" )
.LC291:
	ASCII(.string	"SH: num_ref_idx_override_flag" )
	.zero	2
.LC293:
	ASCII(.string	"SH: num_ref_idx_l0_active_minus1" )
	.zero	7
.LC295:
	ASCII(.string	"SH: num_ref_idx_l1_active_minus1" )
	.zero	7
.LC297:
	ASCII(.string	"frame num_ref_idx_lx_active_minus1 exceed\n" )
	.zero	5
.LC299:
	ASCII(.string	"field num_ref_idx_lx_active_minus1 exceed\n" )
	.zero	5
.LC301:
	ASCII(.string	"reordering para dec err\n" )
	.zero	7
.LC303:
	ASCII(.string	"apply_weights_flag=%d\n" )
	.zero	1
.LC305:
	ASCII(.string	"wpt dec err\n" )
	.zero	3
.LC307:
	ASCII(.string	"mark para dec err\n" )
	.zero	5
.LC309:
	ASCII(.string	"SH: cabac_init_idc" )
	.zero	5
.LC311:
	ASCII(.string	"cabac_init_idc bigger than 3\n" )
	.zero	2
.LC313:
	ASCII(.string	"SH: slice_qp_delta" )
	.zero	5
.LC315:
	ASCII(.string	"SH: disable_deblocking_filter_idc" )
	.zero	6
.LC317:
	ASCII(.string	"disable_deblocking_filter_idc dec err\n" )
	.zero	1
.LC319:
	ASCII(.string	"SH: slice_alpha_c0_offset_div2" )
	.zero	1
.LC321:
	ASCII(.string	"slice_alpha_c0_offset_div2 dec err\n" )
	.zero	4
.LC323:
	ASCII(.string	"SH: slice_beta_offset_div2" )
	.zero	5
.LC325:
	ASCII(.string	"slice_beta_offset_div2 dec err\n" )
.LC327:
	ASCII(.string	"pH264Ctx->pCurrNal->nal_bitoffset = %d; code_len_byte = %d; bitstream_length = %d; pH264Ctx->pCurrNal->nal_trail_zero_bit_num = %d\n" )
	.zero	4
.LC329:
	ASCII(.string	"stream[%d]: bitsoffset = %d; valid_bitlen = %d; bytespos = %x\n" )
	.zero	1
.LC331:
	ASCII(.string	"nal_segment = %d is not expected value\n" )
.LC333:
	ASCII(.string	"stream[%d]: bitsoffset = %d; valid_bitlen = %d\n" )
.LC338:
	ASCII(.string	"   : delta_sl   " )
	.zero	7
.LC342:
	ASCII(.string	"PPS: entropy_coding_mode_flag" )
	.zero	2
.LC344:
	ASCII(.string	"PPS: pic_order_present_flag" )
	.zero	4
.LC346:
	ASCII(.string	"PPS: num_slice_groups_minus1" )
	.zero	3
.LC348:
	ASCII(.string	"Baseline stream with FMO, not support.\n" )
.LC351:
	ASCII(.string	"PPS: num_ref_idx_l0_active_minus1" )
	.zero	6
.LC353:
	ASCII(.string	"num_ref_idx_l0_active_minus1 out of range.\n" )
	.zero	4
.LC355:
	ASCII(.string	"PPS: num_ref_idx_l1_active_minus1" )
	.zero	6
.LC357:
	ASCII(.string	"num_ref_idx_l1_active_minus1 out of range.\n" )
	.zero	4
.LC359:
	ASCII(.string	"PPS: weighted prediction flag" )
	.zero	2
.LC361:
	ASCII(.string	"PPS: weighted_bipred_idc" )
	.zero	7
.LC363:
	ASCII(.string	"weighted_bipred_idc out of range\n" )
	.zero	6
.LC365:
	ASCII(.string	"PPS: pic_init_qp_minus26" )
	.zero	7
.LC367:
	ASCII(.string	"PPS: pic_init_qs_minus26" )
	.zero	7
.LC369:
	ASCII(.string	"PPS: chroma_qp_index_offset" )
	.zero	4
.LC371:
	ASCII(.string	"PPS: deblocking_filter_control_present_flag" )
	.zero	4
.LC373:
	ASCII(.string	"PPS: constrained_intra_pred_flag" )
	.zero	7
.LC375:
	ASCII(.string	"PPS: redundant_pic_cnt_present_flag" )
	.zero	4
.LC377:
	ASCII(.string	"redundant pic not support when find redundant slice later, exit\n" )
	.zero	7
.LC379:
	ASCII(.string	"PPS: transform_8x8_mode_flag" )
	.zero	3
.LC381:
	ASCII(.string	"PPS: pic_scaling_matrix_present_flag" )
	.zero	3
.LC383:
	ASCII(.string	"PPS: second_chroma_qp_index_offset" )
	.zero	5
.LC385:
	ASCII(.string	"SPS: seq_scaling_list_present_flag" )
	.zero	5
.LC388:
	ASCII(.string	"PPS: pic_scaling_list_present_flag" )
	.zero	5
.LC390:
	ASCII(.string	"second_chroma_qp_index_offset out of range.\n" )
	.zero	3
.LC394:
	ASCII(.string	"PPS: pic_parameter_set_id" )
	.zero	6
.LC396:
	ASCII(.string	"pic_parameter_set_id out of range.\n" )
	.zero	4
.LC399:
	ASCII(.string	"PPS: seq_parameter_set_id" )
	.zero	6
.LC401:
	ASCII(.string	"seq_parameter_set_id out of range.\n" )
	.zero	4
.LC403:
	ASCII(.string	"SPS haven't decode.\n" )
	.zero	3
.LC407:
	ASCII(.string	"%s: PPS decode error 1.\n" )
	.zero	7
.LC410:
	ASCII(.string	"%s: PPS decode error 2.\n" )
	.zero	7
.LC412:
	ASCII(.string	"VUI: aspect_ratio_info_present_flag" )
	.zero	4
.LC414:
	ASCII(.string	"VUI: aspect_ratio_idc" )
	.zero	2
.LC416:
	ASCII(.string	"VUI: sar_width" )
	.zero	1
.LC418:
	ASCII(.string	"VUI: sar_height" )
.LC420:
	ASCII(.string	"VUI: overscan_info_present_flag" )
.LC422:
	ASCII(.string	"VUI: overscan_appropriate_flag" )
	.zero	1
.LC424:
	ASCII(.string	"VUI: video_signal_type_present_flag" )
	.zero	4
.LC426:
	ASCII(.string	"VUI: video_format" )
	.zero	6
.LC428:
	ASCII(.string	"VUI: video_full_range_flag" )
	.zero	5
.LC430:
	ASCII(.string	"VUI: color_description_present_flag" )
	.zero	4
.LC432:
	ASCII(.string	"VUI: colour_primaries" )
	.zero	2
.LC434:
	ASCII(.string	"VUI: transfer_characteristics" )
	.zero	2
.LC436:
	ASCII(.string	"VUI: matrix_coefficients" )
	.zero	7
.LC438:
	ASCII(.string	"VUI: chroma_loc_info_present_flag" )
	.zero	6
.LC440:
	ASCII(.string	"VUI: chroma_sample_loc_type_top_field" )
	.zero	2
.LC442:
	ASCII(.string	"VUI: chroma_sample_loc_type_bottom_field" )
	.zero	7
.LC444:
	ASCII(.string	"VUI: timing_info_present_flag" )
	.zero	2
.LC446:
	ASCII(.string	"VUI: num_units_in_tick" )
	.zero	1
.LC448:
	ASCII(.string	"VUI: time_scale" )
.LC450:
	ASCII(.string	"VUI: fixed_frame_rate_flag" )
	.zero	5
.LC453:
	ASCII(.string	"VUI: nal_hrd_parameters_present_flag" )
	.zero	3
.LC455:
	ASCII(.string	"VUI: cpb_cnt_minus1" )
	.zero	4
.LC457:
	ASCII(.string	"VUI: bit_rate_scale" )
	.zero	4
.LC459:
	ASCII(.string	"VUI: cpb_size_scale" )
	.zero	4
.LC461:
	ASCII(.string	"hrd->cpb_cnt_minus1 out of range\n" )
	.zero	6
.LC463:
	ASCII(.string	"VUI: bit_rate_value_minus1" )
	.zero	5
.LC465:
	ASCII(.string	"VUI: cpb_size_value_minus1" )
	.zero	5
.LC467:
	ASCII(.string	"VUI: cbr_flag" )
	.zero	2
.LC469:
	ASCII(.string	"VUI: initial_cpb_removal_delay_length_minus1" )
	.zero	3
.LC471:
	ASCII(.string	"VUI: cpb_removal_delay_length_minus1" )
	.zero	3
.LC473:
	ASCII(.string	"VUI: dpb_output_delay_length_minus1" )
	.zero	4
.LC475:
	ASCII(.string	"VUI: time_offset_length" )
.LC477:
	ASCII(.string	"VUI: vcl_hrd_parameters_present_flag" )
	.zero	3
.LC479:
	ASCII(.string	"VUI: low_delay_hrd_flag" )
.LC481:
	ASCII(.string	"VUI: pic_struct_present_flag" )
	.zero	3
.LC483:
	ASCII(.string	"VUI: bitstream_restriction_flag" )
.LC485:
	ASCII(.string	"VUI: motion_vectors_over_pic_boundaries_flag" )
	.zero	3
.LC487:
	ASCII(.string	"VUI: max_bytes_per_pic_denom" )
	.zero	3
.LC489:
	ASCII(.string	"VUI: max_bits_per_mb_denom" )
	.zero	5
.LC491:
	ASCII(.string	"VUI: log2_max_mv_length_horizontal" )
	.zero	5
.LC493:
	ASCII(.string	"VUI: log2_max_mv_length_vertical" )
	.zero	7
.LC495:
	ASCII(.string	"VUI: num_reorder_frames" )
.LC497:
	ASCII(.string	"VUI: max_dec_frame_buffering" )
	.zero	3
.LC502:
	ASCII(.string	"dar=%d, final_dar=%d\n" )
	.zero	2
.LC508:
	ASCII(.string	"SPS: chroma_format_idc" )
	.zero	1
.LC510:
	ASCII(.string	"pSPS->chroma_format_idc = %d out of range.\n" )
	.zero	4
.LC512:
	ASCII(.string	"SPS: bit_depth_luma_minus8" )
	.zero	5
.LC514:
	ASCII(.string	"bit_depth_luma(%d) not equal 8.\n" )
	.zero	7
.LC517:
	ASCII(.string	"SPS: bit_depth_chroma_minus8" )
	.zero	3
.LC519:
	ASCII(.string	"bit_depth_chroma(%d) not equal 8.\n" )
	.zero	5
.LC521:
	ASCII(.string	"SPS: qpprime_y_zero_trans_bypass_flag" )
	.zero	2
.LC523:
	ASCII(.string	"qpprime_y_zero_trans_bypass_flag not equal 0.\n" )
	.zero	1
.LC525:
	ASCII(.string	"SPS: seq_scaling_matrix_present_flag" )
	.zero	3
.LC529:
	ASCII(.string	"SPS: log2_max_frame_num_minus4" )
	.zero	1
.LC531:
	ASCII(.string	"pSPS->log2_max_frame_num_minus4 out of range.\n" )
	.zero	1
.LC533:
	ASCII(.string	"SPS: pic_order_cnt_type" )
.LC535:
	ASCII(.string	"pSPS->pic_order_cnt_type out of range.\n" )
.LC537:
	ASCII(.string	"SPS: log2_max_pic_order_cnt_lsb_minus4" )
	.zero	1
.LC539:
	ASCII(.string	"pSPS->log2_max_pic_order_cnt_lsb_minus4 out of range.\n" )
	.zero	1
.LC541:
	ASCII(.string	"SPS: delta_pic_order_always_zero_flag" )
	.zero	2
.LC543:
	ASCII(.string	"SPS: offset_for_non_ref_pic" )
	.zero	4
.LC545:
	ASCII(.string	"SPS: offset_for_top_to_bottom_field" )
	.zero	4
.LC547:
	ASCII(.string	"SPS: num_ref_frames_in_pic_order_cnt_cycle" )
	.zero	5
.LC549:
	ASCII(.string	"pSPS->num_ref_frames_in_pic_order_cnt_cycle out of range.\n" )
	.zero	5
.LC551:
	ASCII(.string	"SPS: offset_for_ref_frame[i]" )
	.zero	3
.LC553:
	ASCII(.string	"SPS: gaps_in_frame_num_value_allowed_flag" )
	.zero	6
.LC555:
	ASCII(.string	"SPS: pic_width_in_mbs_minus1" )
	.zero	3
.LC557:
	ASCII(.string	"pSPS->pic_width_in_mbs_minus1 out of range(=%d).\n" )
	.zero	6
.LC559:
	ASCII(.string	"SPS: pic_height_in_map_units_minus1" )
	.zero	4
.LC561:
	ASCII(.string	"SPS: frame_mbs_only_flag" )
	.zero	7
.LC563:
	ASCII(.string	"pSPS->pic_height_in_map_units_minus1 out of range.\n" )
	.zero	4
.LC565:
	ASCII(.string	"pic size too large.\n" )
	.zero	3
.LC568:
	ASCII(.string	"level_idc %d not support.\n" )
	.zero	5
.LC570:
	ASCII(.string	"dpb size according level : %d\n" )
	.zero	1
.LC572:
	ASCII(.string	"pSPS->num_ref_frames(%d) > DPB size(%d), try to select the reasonable one.\n" )
	.zero	4
.LC574:
	ASCII(.string	"SPS: direct_8x8_inference_flag" )
	.zero	1
.LC576:
	ASCII(.string	"SPS: frame_cropping_flag" )
	.zero	7
.LC578:
	ASCII(.string	"SPS: frame_cropping_rect_left_offset" )
	.zero	3
.LC580:
	ASCII(.string	"SPS: frame_cropping_rect_right_offset" )
	.zero	2
.LC582:
	ASCII(.string	"SPS: frame_cropping_rect_top_offset" )
	.zero	4
.LC584:
	ASCII(.string	"SPS: frame_cropping_rect_bottom_offset" )
	.zero	1
.LC586:
	ASCII(.string	"SPS: vui_parameters_present_flag" )
	.zero	7
.LC588:
	ASCII(.string	"max_dec_frame_buffering(%d) > MaxDpbSize(%d)\n" )
	.zero	2
.LC590:
	ASCII(.string	"SPS: num_ref_frames" )
	.zero	4
.LC592:
	ASCII(.string	"SPS: mb_adaptive_frame_field_flag" )
	.zero	6
.LC594:
	ASCII(.string	"SPS_SVC_EXT: inter_layer_deblocking_filter_control_present_flag" )
.LC596:
	ASCII(.string	"inter_layer_present_flag:%d!\n" )
	.zero	2
.LC598:
	ASCII(.string	"SPS_SVC_EXT: extended_spatial_scalability_idc" )
	.zero	2
.LC600:
	ASCII(.string	"spatial scalability not support!!\n" )
	.zero	5
.LC602:
	ASCII(.string	"SPS_SVC_EXT: chroma_phase_x_plus1_flag" )
	.zero	1
.LC604:
	ASCII(.string	"chroma_phase_x_plus1_flag:%d!!\n" )
.LC606:
	ASCII(.string	"SPS_SVC_EXT: chroma_phase_y_plus1" )
	.zero	6
.LC608:
	ASCII(.string	"chroma_phase_y_plus1:%d!\n" )
	.zero	6
.LC610:
	ASCII(.string	"SPS_SVC_EXT: seq_tcoeff_level_prediction_flag" )
	.zero	2
.LC612:
	ASCII(.string	"SPS_SVC_EXT: adaptive_tcoeff_level_prediction_flag" )
	.zero	5
.LC614:
	ASCII(.string	"adaptive_tcoeff_level_prediction_flag:%d!\n" )
	.zero	5
.LC616:
	ASCII(.string	"SPS_SVC_EXT: slice_header_restriction_flag" )
	.zero	5
.LC618:
	ASCII(.string	"slice_header_restriction_flag error:%d,%x,%d\n" )
	.zero	2
.LC620:
	ASCII(.string	"SPS: profile_idc" )
	.zero	7
.LC622:
	ASCII(.string	"SPS: constrained_set0_flag" )
	.zero	5
.LC624:
	ASCII(.string	"SPS: constrained_set1_flag" )
	.zero	5
.LC626:
	ASCII(.string	"SPS: constrained_set2_flag" )
	.zero	5
.LC628:
	ASCII(.string	"SPS: constrained_set3_flag" )
	.zero	5
.LC630:
	ASCII(.string	"SPS: reserved_zero_4bits" )
	.zero	7
.LC632:
	ASCII(.string	"SPS: level_idc" )
	.zero	1
.LC634:
	ASCII(.string	"SPS: seq_parameter_set_id" )
	.zero	6
.LC639:
	ASCII(.string	"Baseline stream, try to decode, exit when FMO occurred.\n" )
	.zero	7
.LC641:
	ASCII(.string	"EXTENDED stream, try to decode, exit when datapartition occurred.\n" )
	.zero	5
.LC643:
	ASCII(.string	"others High profile stream, try to decode, exit when high profile not support occurred.\n" )
	.zero	7
.LC645:
	ASCII(.string	"profile_idc = %5d error, try to decode as main profile.\n" )
	.zero	7
.LC647:
	ASCII(.string	"level_idc = %5d error, try to decode as level_idc %d.\n" )
	.zero	1
.LC650:
	ASCII(.string	"Line %d: SPS[%d] decode error.\n" )
.LC653:
	ASCII(.string	"svc ext error:\n" )
.LC656:
	ASCII(.string	"SEI: frame_packing_arrangement_id" )
	.zero	6
.LC658:
	ASCII(.string	"SEI: frame_packing_arrangement_cancel_flag" )
	.zero	5
.LC660:
	ASCII(.string	"SEI: frame_packing_arrangement_type" )
	.zero	4
.LC662:
	ASCII(.string	"SEI: quincunx_sampling_flag" )
	.zero	4
.LC664:
	ASCII(.string	"SEI: content_interpretation_type" )
	.zero	7
.LC666:
	ASCII(.string	"SEI: spatial_flipping_flag" )
	.zero	5
.LC668:
	ASCII(.string	"SEI: frame0_flipped_flag" )
	.zero	7
.LC670:
	ASCII(.string	"SEI: field_views_flag" )
	.zero	2
.LC672:
	ASCII(.string	"SEI: current_frame_is_frame0_flag" )
	.zero	6
.LC674:
	ASCII(.string	"SEI: frame0_self_contained_flag" )
.LC676:
	ASCII(.string	"SEI: frame1_self_contained_flag" )
.LC678:
	ASCII(.string	"SEI: frame0_grid_position_x" )
	.zero	4
.LC680:
	ASCII(.string	"SEI: frame0_grid_position_y" )
	.zero	4
.LC682:
	ASCII(.string	"SEI: frame1_grid_position_x" )
	.zero	4
.LC684:
	ASCII(.string	"SEI: frame1_grid_position_y" )
	.zero	4
.LC686:
	ASCII(.string	"SEI: frame_packing_arrangement_reserved_byte" )
	.zero	3
.LC688:
	ASCII(.string	"SEI: frame_packing_arrangement_repetition_period" )
	.zero	7
.LC690:
	ASCII(.string	"SEI: frame_packing_arrangement_extension_flag" )
	.zero	2
.LC692:
	ASCII(.string	"DecPicTimingSEI but SPS is invalid.\n" )
	.zero	3
.LC694:
	ASCII(.string	"SEI: cpb_removal_delay" )
	.zero	1
.LC696:
	ASCII(.string	"SEI: dpb_output_delay" )
	.zero	2
.LC699:
	ASCII(.string	"pic_struct" )
	.zero	5
.LC702:
	ASCII(.string	"SEI nal dec payload type err\n" )
	.zero	2
.LC704:
	ASCII(.string	"SEI nal dec payloadSize err\n" )
	.zero	3
.LC707:
	ASCII(.string	"SEI_BUFFERING_PERIOD,offset = %d,payload_size = %d \n" )
	.zero	3
.LC710:
	ASCII(.string	"PassBytes err [%s][%d]\n" )
.LC712:
	ASCII(.string	"SEI_PIC_TIMING,offset = %d,payload_size = %d \n" )
	.zero	1
.LC714:
	ASCII(.string	"SEI_PAN_SCAN_RECT,offset = %d,payload_size = %d \n" )
	.zero	6
.LC716:
	ASCII(.string	"SEI_FILLER_PAYLOAD,offset = %d,payload_size = %d \n" )
	.zero	5
.LC718:
	ASCII(.string	"SEI_USER_DATA_REGISTERED_ITU_T_T35, offset = %d, payload_size = %d \n" )
	.zero	3
.LC720:
	ASCII(.string	"SEI_USER_DATA_UNREGISTERED, offset = %d, payload_size = %d \n" )
	.zero	3
.LC722:
	ASCII(.string	"SEI: itu_t_t35_country_code" )
	.zero	4
.LC724:
	ASCII(.string	"SEI: itu_t_t35_country_code_extension_byte" )
	.zero	5
.LC726:
	ASCII(.string	"SEI: itu_t_t35_provider_code" )
	.zero	3
.LC729:
	ASCII(.string	"len_tmp = %d cann't dec usrdata\n" )
	.zero	7
.LC731:
	ASCII(.string	"cann't dec usrdata\n" )
	.zero	4
.LC733:
	ASCII(.string	"SEI_RECOVERY_POINT,offset = %d,payload_size = %d \n" )
	.zero	5
.LC735:
	ASCII(.string	"SEI_DEC_REF_PIC_MARKING_REPETITION,offset = %d,payload_size = %d \n" )
	.zero	5
.LC737:
	ASCII(.string	"SEI_SPARE_PIC,offset = %d,payload_size = %d \n" )
	.zero	2
.LC739:
	ASCII(.string	"SEI_SCENE_INFO,offset = %d,payload_size = %d \n" )
	.zero	1
.LC741:
	ASCII(.string	"SEI_SUB_SEQ_INFO,offset = %d,payload_size = %d \n" )
	.zero	7
.LC743:
	ASCII(.string	"SEI_SUB_SEQ_LAYER_CHARACTERISTICS,offset = %d,payload_size = %d \n" )
	.zero	6
.LC745:
	ASCII(.string	"SEI_SUB_SEQ_CHARACTERISTICS,offset = %d,payload_size = %d \n" )
	.zero	4
.LC747:
	ASCII(.string	"SEI_FULL_FRAME_FREEZE,offset = %d,payload_size = %d \n" )
	.zero	2
.LC749:
	ASCII(.string	"SEI_FULL_FRAME_FREEZE_RELEASE,offset = %d,payload_size = %d \n" )
	.zero	2
.LC751:
	ASCII(.string	"SEI_FULL_FRAME_SNAPSHOT,offset = %d,payload_size = %d \n" )
.LC753:
	ASCII(.string	"SEI_PROGRESSIVE_REFINEMENT_SEGMENT_START,offset = %d,payload_size = %d \n" )
	.zero	7
.LC755:
	ASCII(.string	"SEI_PROGRESSIVE_REFINEMENT_SEGMENT_END,offset = %d,payload_size = %d \n" )
	.zero	1
.LC757:
	ASCII(.string	"SEI_MOTION_CONSTRAINED_SLICE_GROUP_SET,offset = %d,payload_size = %d \n" )
	.zero	1
.LC759:
	ASCII(.string	"SEI_FILM_GRAIN_CHARACTERISTICS,offset = %d,payload_size = %d \n" )
	.zero	1
.LC761:
	ASCII(.string	"SEI_DEBLOCKING_FILTER_DISPLAY_PREFERENCE,offset = %d,payload_size = %d \n" )
	.zero	7
.LC763:
	ASCII(.string	"SEI_STEREO_VIDEO_INFO,offset = %d,payload_size = %d \n" )
	.zero	2
.LC765:
	ASCII(.string	"too much usrdat, cann't dec SEI\n" )
	.zero	7
.LC769:
	ASCII(.string	"\nthe stream is error,len:%d\n" )
	.zero	3
.LC774:
	ASCII(.string	"\nSlice nal or IDR nal = %d\n" )
	.zero	4
.LC776:
	ASCII(.string	"sliceheader dec err\n" )
	.zero	3
.LC778:
	ASCII(.string	"H264Dec destroy\n" )
	.zero	7
.LC780:
	ASCII(.string	"H264 recycle image\n" )
	.zero	4
.LC782:
	ASCII(.string	"pH264Ctx is %p, pFrameStore is %p\n" )
	.zero	5
.LC784:
	ASCII(.string	"line; %d pstLogicFsImage is NULL!\n" )
	.zero	5
.LC786:
	ASCII(.string	"InsertVO err:%d, ClearAll\n" )
	.zero	5
.LC788:
	ASCII(.string	"H264.c line %d: frame para err(ret=%d), recycle image self\n" )
	.zero	4
.LC790:
	ASCII(.string	"line: %d pstLogicFsImage is NULL!\n" )
	.zero	5
.LC794:
	ASCII(.string	"[%s][%d] OutputFrmToVO return %d\n" )
	.zero	6
.LC799:
	ASCII(.string	"line %d: flush dpb return %d\n" )
	.zero	2
.LC801:
	ASCII(.string	"----------------- Imode -> %d ------------------\n" )
	.zero	6
.LC803:
	ASCII(.string	"I_MODE but first_mb_in_slice != 0\n" )
	.zero	5
.LC807:
	ASCII(.string	"Discard this B(poc=%d) befor P, is_ref_idc=%d.\n" )
.LC809:
	ASCII(.string	"***** VDM start, TotalPicNum=%d, pH264Ctx->CurrPic.structure=%d.\n" )
	.zero	6
.LC811:
	ASCII(.string	"DecVDM ERR\n" )
	.zero	4
.LC815:
	ASCII(.string	"%s:%d Metadata map failed\n" )
	.zero	5
.LC820:
	ASCII(.string	"%s:%d Metadata unmap failed\n" )
	.zero	3
.LC823:
	ASCII(.string	"*****[%s][%d],EL Codec can only dec EL stream in DV_DUAL_VES_IMP stream!!*****\n" )
.LC825:
	ASCII(.string	"***** VES Splitter: UNSUPPORT, HDR_capacity=%d*****\n" )
	.zero	3
.LC827:
	ASCII(.string	"\n receive streambuff=%p; phy_addr=0x%x; bitstream_length=%d\n" )
	.zero	3
.LC829:
	ASCII(.string	"nal_release_err\n" )
	.zero	7
.LC831:
	ASCII(.string	"cann't find slot for current nal\n" )
	.zero	6
.LC834:
	ASCII(.string	"receive a zero packet\n" )
	.zero	1
.LC836:
	ASCII(.string	"clear all dec para\n" )
	.zero	4
.LC839:
	ASCII(.string	"[%s %d], pos is %d out of range\n" )
	.zero	7
.LC841:
	ASCII(.string	"line %d, get APC error, ret %d\n" )
.LC843:
	ASCII(.string	"InserFrmInDPB: cur pic struct = %d!\n" )
	.zero	3
.LC845:
	ASCII(.string	"CurrPic.state is 'EMPTY'\n" )
	.zero	6
.LC847:
	ASCII(.string	"StorePicInDPB return(%d) from L%d\n" )
	.zero	5
.LC850:
	ASCII(.string	"directoutput mode\n" )
	.zero	5
.LC852:
	ASCII(.string	"line: %d pImg is NULL!\n" )
.LC854:
	ASCII(.string	"line %d, REPORT_IFRAME_ERR\n" )
	.zero	4
.LC857:
	ASCII(.string	"line %d, return %d\n" )
	.zero	4
.LC859:
	ASCII(.string	"err(%d) > ref_thr(%d)\n" )
	.zero	1
.LC861:
	ASCII(.string	"marking return %d\n" )
	.zero	5
.LC863:
	ASCII(.string	"return value is unexpeced!\n" )
	.zero	4
.LC866:
	ASCII(.string	"line %d: pH264Ctx->DPB.size = %d, ref %d, ltref %d\n" )
	.zero	4
.LC869:
	ASCII(.string	"%s: pos(%d) = pre_pos, force return.\n" )
	.zero	2
.LC871:
	ASCII(.string	"FS_ALLOC_ERR, ClearAll\n" )
.LC874:
	ASCII(.string	"Can not new logic fs! ClearAll\n" )
.LC876:
	ASCII(.string	"GAP found while DPB is empty!\n" )
	.zero	1
.LC878:
	ASCII(.string	"frame num gap try to fill it \n" )
	.zero	1
.LC880:
	ASCII(.string	"CurrFrameNum = %d  UnusedShortTermFrameNum = %d\n" )
	.zero	7
.LC882:
	ASCII(.string	"cann't allocate frame store when gap find\n" )
	.zero	5
.LC884:
	ASCII(.string	"allocate frame store when gap find\n" )
	.zero	4
.LC886:
	ASCII(.string	"line %d: store gap pic err, ret=%d\n" )
	.zero	4
.LC890:
	ASCII(.string	"%s %d unknow error!!\n" )
	.zero	2
.LC892:
	ASCII(.string	"-1 == VCTRL_GetChanIDByCtx() Err! \n" )
	.zero	4
.LC895:
	ASCII(.string	"%s %d frame_store is null!!\n" )
	.zero	3
.LC898:
	ASCII(.string	"get back frm\n" )
	.zero	2
.LC901:
	ASCII(.string	"line %d: init dpb return %d\n" )
	.zero	3
.LC903:
	ASCII(.string	"mem arrange err, ClearAll\n" )
	.zero	5
.LC906:
	ASCII(.string	"line %d: frame gap(=%d) > dpb size(=%d)\n" )
	.zero	7
.LC908:
	ASCII(.string	"line %d: dec gap failed\n" )
	.zero	7
.LC910:
	ASCII(.string	"line %d: alloc framestore failed\n" )
	.zero	6
.LC912:
	ASCII(.string	"dec_pts: %lld\n" )
	.zero	1
.LC914:
	ASCII(.string	"dec_usertag: %lld\n" )
	.zero	5
.LC916:
	ASCII(.string	"%s %d NULL == pH264Ctx->CurrPic.frame_store!!\n" )
	.zero	1
.LC922:
	ASCII(.string	"Start Reason: SliceParaNum, MaxBytesReceived = %d, %d(thr=%d)\n" )
	.zero	1
.LC924:
	ASCII(.string	"Too many slice or bitstream, err!\n" )
	.zero	5
.LC926:
	ASCII(.string	"Start Reason: new_pic_flag\n" )
	.zero	4
.LC928:
	ASCII(.string	"init pic err, find next recover point or next valid sps, pps, or exit\n" )
	.zero	1
.LC930:
	ASCII(.string	"DecList error, ret=%d\n" )
	.zero	1
.LC932:
	ASCII(.string	"dec list err, cur pic poc %d.\n" )
	.zero	1
.LC935:
	ASCII(.string	"pH264Ctx->TotalNal = %d, type:%d\n" )
	.zero	6
.LC937:
	ASCII(.string	"stop i want\n" )
	.zero	3
.LC939:
	ASCII(.string	"svc_extension_flag error:priority_id:%d, pred_flag%d\n" )
	.zero	2
.LC941:
	ASCII(.string	"%d,%d,%d\n" )
	.zero	6
.LC943:
	ASCII(.string	"svc stream,nal_header:%x\n" )
	.zero	6
.LC946:
	ASCII(.string	"***** NAL: IDR/Slice, nal_unit_type=%d, TotalSlice=%d\n" )
	.zero	1
.LC948:
	ASCII(.string	"SliceCheck failed, clear current slice.\n" )
	.zero	7
.LC951:
	ASCII(.string	"***** NAL: PPS, nal_unit_type=%d, TotalPPS=%d\n" )
	.zero	1
.LC954:
	ASCII(.string	"%s: PPS decode error.\n" )
	.zero	1
.LC956:
	ASCII(.string	"***** NAL: SPS, nal_unit_type=%d, TotalSPS=%d\n" )
	.zero	1
.LC958:
	ASCII(.string	"SPS decode error.\n" )
	.zero	5
.LC960:
	ASCII(.string	"***** NAL: SEI, nal_unit_type=%d\n" )
	.zero	6
.LC962:
	ASCII(.string	"SEI decode error.\n" )
	.zero	5
.LC964:
	ASCII(.string	"***** NAL: AUD, nal_unit_type=%d\n" )
	.zero	6
.LC966:
	ASCII(.string	"***** NAL: EOSEQ, nal_unit_type=%d\n" )
	.zero	4
.LC968:
	ASCII(.string	"***** NAL: FILL, nal_unit_type=%d\n" )
	.zero	5
.LC970:
	ASCII(.string	"***** NAL: EOSTREAM, nal_unit_type=%d\n" )
	.zero	1
.LC972:
	ASCII(.string	"***** NAL: SPSEXT, nal_unit_type=%d\n" )
	.zero	3
.LC974:
	ASCII(.string	"***** NAL: AUX, nal_unit_type=%d\n" )
	.zero	6
.LC976:
	ASCII(.string	"***** NAL: EOPIC, nal_unit_type=%d\n" )
	.zero	4
.LC978:
	ASCII(.string	"***** NAL: UNSUPPORT, nal_unit_type=%d,nalu header:%x\n" )
	.zero	1
.LC980:
	ASCII(.string	"***** NAL: UNSUPPORT, nal_unit_type=%d\n" )
.LC988:
	ASCII(.string	"FindTrailZeros ERR\n" )
	.zero	4
.LC990:
	ASCII(.string	"H264_DecOneNal ERR\n" )
	.zero	4
.LC993:
	ASCII(.string	"store pic err, ret = %d\n" )
	.zero	7
.LC996:
	ASCII(.string	"pH264Ctx->CurrPic.frame_store is null pointer\n" )
	.zero	1
.LC998:
	ASCII(.string	"imode nal store pic err, ret = %d\n" )
	.zero	5
.LC1000:
	ASCII(.string	"imode nal flush dpb err, ret = %d\n" )
	.zero	5
.LC1002:
	ASCII(.string	"cann't find FrameStore\n" )
.LC1004:
	ASCII(.string	"========== H264 FrameStore state(is_used, is_in_dpb, IsOutDPB) ========\n" )
	.zero	7
.LC1006:
	ASCII(.string	"ReadImgNum = %d, NewImgNum = %d\n" )
	.zero	7
.LC1008:
	ASCII(.string	"%02d: %d %d %d\n" )
.LC1010:
	ASCII(.string	"FrameStore leak, ClearAll\n" )
	.bss
	.align	3
.LANCHOR3 = . + 0
.LANCHOR4 = . + 4352
	.type	pps_tmp.12629, %object
	.size	pps_tmp.12629, 2208
pps_tmp.12629:
	.zero	2208
	.type	sps_tmp.12781, %object
	.size	sps_tmp.12781, 4000
sps_tmp.12781:
	.zero	4000
	.type	TmpBuf, %object
	.size	TmpBuf, 68
TmpBuf:
	.zero	68
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
