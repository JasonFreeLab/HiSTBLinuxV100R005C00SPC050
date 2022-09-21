#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"mvc.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	MVC_IsSTRefFlg
	.type	MVC_IsSTRefFlg, %function
MVC_IsSTRefFlg:
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
	.size	MVC_IsSTRefFlg, .-MVC_IsSTRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_IsLTRefFlg
	.type	MVC_IsLTRefFlg, %function
MVC_IsLTRefFlg:
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
	.size	MVC_IsLTRefFlg, .-MVC_IsLTRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_compare_pic_by_pic_num_desc
	.type	MVC_compare_pic_by_pic_num_desc, %function
MVC_compare_pic_by_pic_num_desc:
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
	ldr	w1, [x0, 20]
	ldr	w2, [x2, 20]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	csetm	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	MVC_compare_pic_by_pic_num_desc, .-MVC_compare_pic_by_pic_num_desc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_compare_pic_by_lt_pic_num_asc
	.type	MVC_compare_pic_by_lt_pic_num_asc, %function
MVC_compare_pic_by_lt_pic_num_asc:
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
	ldr	w1, [x0, 16]
	ldr	w2, [x2, 16]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	cset	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	MVC_compare_pic_by_lt_pic_num_asc, .-MVC_compare_pic_by_lt_pic_num_asc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_compare_fs_by_frame_num_desc
	.type	MVC_compare_fs_by_frame_num_desc, %function
MVC_compare_fs_by_frame_num_desc:
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
	ldr	w1, [x0, 24]
	ldr	w2, [x2, 24]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	csetm	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	MVC_compare_fs_by_frame_num_desc, .-MVC_compare_fs_by_frame_num_desc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_compare_fs_by_lt_pic_idx_asc
	.type	MVC_compare_fs_by_lt_pic_idx_asc, %function
MVC_compare_fs_by_lt_pic_idx_asc:
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
	ldr	w1, [x0, 28]
	ldr	w2, [x2, 28]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	cset	w0, hi
	csel	w0, w0, w3, cs
	ret
	.size	MVC_compare_fs_by_lt_pic_idx_asc, .-MVC_compare_fs_by_lt_pic_idx_asc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_compare_pic_by_poc_asc
	.type	MVC_compare_pic_by_poc_asc, %function
MVC_compare_pic_by_poc_asc:
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
	ldr	w1, [x0, 24]
	ldr	w2, [x2, 24]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	cset	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	MVC_compare_pic_by_poc_asc, .-MVC_compare_pic_by_poc_asc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_compare_pic_by_poc_desc
	.type	MVC_compare_pic_by_poc_desc, %function
MVC_compare_pic_by_poc_desc:
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
	ldr	w1, [x0, 24]
	ldr	w2, [x2, 24]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	csetm	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	MVC_compare_pic_by_poc_desc, .-MVC_compare_pic_by_poc_desc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_compare_fs_by_poc_asc
	.type	MVC_compare_fs_by_poc_asc, %function
MVC_compare_fs_by_poc_asc:
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
	ldr	w1, [x0, 32]
	ldr	w2, [x2, 32]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	cset	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	MVC_compare_fs_by_poc_asc, .-MVC_compare_fs_by_poc_asc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_compare_fs_by_poc_desc
	.type	MVC_compare_fs_by_poc_desc, %function
MVC_compare_fs_by_poc_desc:
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
	ldr	w1, [x0, 32]
	ldr	w2, [x2, 32]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	csetm	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	MVC_compare_fs_by_poc_desc, .-MVC_compare_fs_by_poc_desc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	MVC_SetFrmRepeatCount.part.2, %function
MVC_SetFrmRepeatCount.part.2:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	add	x3, x19, 11124736
	ldp	w0, w2, [x19, 132]
	ldr	w3, [x3, 792]
	lsr	w0, w0, 1
	add	w2, w3, w2, lsr 1
	add	w3, w2, 1
	cmp	w0, w3
	bcc	.L28
	sub	w0, w0, #1
	sub	w0, w0, w2
	cmp	w0, 1
	bls	.L29
	mov	w0, 2
	str	w0, [x20, 16]
	ldr	w0, [x19, 136]
	add	w0, w0, 4
	str	w0, [x19, 136]
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
	ldr	w0, [x19, 136]
	add	w0, w0, 2
	str	w0, [x19, 136]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_SetFrmRepeatCount.part.2, .-MVC_SetFrmRepeatCount.part.2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	MVC_CombinePacket.part.13, %function
MVC_CombinePacket.part.13:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC1
	mov	w0, 7
	bl	dprint_vfmw
	ldr	x2, [x19, 240]
	mov	w0, 7
	ldr	x1, .LC3
	ldp	w5, w3, [x2, 48]
	ldr	w4, [x2, 16]
	ldr	w2, [x2, 20]
	bl	dprint_vfmw
	ldr	x1, [x19, 240]
	ldr	x3, .LC4
	ldr	w2, [x1, 16]
	ldr	x0, [x1, 40]
	ldr	x3, [x3, 104]
	ldr	x1, [x1, 8]
	sub	x0, x0, x2
	blr	x3
	ldr	x2, [x19, 240]
	mov	w4, 1
	ldr	x1, .LC6
	mov	w0, 7
	ldr	w3, [x2, 68]
	ldr	w20, [x2, 36]
	str	w3, [x2, 36]
	ldr	x2, [x19, 240]
	str	wzr, [x2, 28]
	ldr	x2, [x19, 240]
	ldr	w5, [x2, 16]
	ldr	x3, [x2, 40]
	sub	x3, x3, x5
	str	x3, [x2, 8]
	ldr	x2, [x19, 240]
	ldr	w5, [x2, 16]
	ldr	w3, [x2, 52]
	sub	w3, w3, w5
	str	w3, [x2, 20]
	ldr	x2, [x19, 240]
	ldr	w5, [x2, 16]
	ldr	w3, [x2, 48]
	add	w3, w5, w3
	str	w3, [x2, 16]
	ldr	x2, [x19, 240]
	str	w4, [x2, 76]
	ldr	x2, [x19, 240]
	ldp	w3, w2, [x2, 16]
	bl	dprint_vfmw
	ldr	w0, [x19, 120]
	mov	w1, w20
	bl	SM_ReleaseStreamSeg
	ldr	x0, [x19, 240]
	str	xzr, [x0, 40]
	ldr	x0, [x19, 240]
	str	wzr, [x0, 60]
	ldr	x0, [x19, 240]
	str	wzr, [x0, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_CombinePacket.part.13, .-MVC_CombinePacket.part.13
	.align	3
.LC1:
	.xword	.LC0
	.align	3
.LC3:
	.xword	.LC2
	.align	3
.LC4:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC6:
	.xword	.LC5
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_ue_v
	.type	mvc_ue_v, %function
mvc_ue_v:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	x22, x1
	add	x23, x21, 872
	bl	_mcount
	mov	w1, 32
	mov	x0, x23
	bl	BsShow
	mov	w20, w0
	bl	ZerosMS_32
	cmp	w0, 15
	mov	w19, w0
	bls	.L37
	cmp	w0, 31
	bls	.L38
	mov	w0, 1
	mov	w20, -1
	strb	w0, [x21, 10]
	mov	w19, 32
.L35:
	ldr	x4, [x21, 240]
	mov	w3, w20
	ldr	x1, .LC8
	mov	x2, x22
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
.L37:
	lsl	w19, w0, 1
	mov	w2, 32
	add	w19, w19, 1
	mov	x0, x23
	sub	w2, w2, w19
	mov	w1, w19
	lsr	w20, w20, w2
	sub	w20, w20, #1
	bl	BsSkip
	b	.L35
	.p2align 3
.L38:
	mov	w1, w0
	mov	x0, x23
	add	w24, w19, 1
	lsl	w19, w19, 1
	bl	BsSkip
	add	w19, w19, 1
	mov	w1, w24
	mov	x0, x23
	bl	BsShow
	sub	w20, w0, #1
	mov	w1, w24
	mov	x0, x23
	bl	BsSkip
	b	.L35
	.size	mvc_ue_v, .-mvc_ue_v
	.align	3
.LC8:
	.xword	.LC7
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_se_v
	.type	mvc_se_v, %function
mvc_se_v:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	x22, x1
	add	x23, x21, 872
	bl	_mcount
	mov	w1, 32
	mov	x0, x23
	bl	BsShow
	mov	w20, w0
	bl	ZerosMS_32
	cmp	w0, 15
	mov	w19, w0
	bhi	.L40
	lsl	w19, w0, 1
	mov	w2, 32
	add	w19, w19, 1
	mov	x0, x23
	sub	w2, w2, w19
	mov	w1, w19
	lsr	w20, w20, w2
	and	w2, w20, 1
	lsr	w20, w20, 1
	cmp	w2, wzr
	csneg	w20, w20, w20, eq
	bl	BsSkip
.L42:
	ldr	x4, [x21, 240]
	mov	w3, w20
	ldr	x1, .LC9
	mov	x2, x22
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
.L40:
	cmp	w0, 31
	bls	.L49
	mov	w0, 1
	mov	w20, 2147483647
	strb	w0, [x21, 10]
	mov	w19, 32
	b	.L42
	.p2align 3
.L49:
	mov	w1, w0
	mov	x0, x23
	bl	BsSkip
	mov	w1, w19
	mov	x0, x23
	lsl	w19, w19, 1
	bl	BsGet
	mov	w20, w0
	mov	w1, 1
	mov	x0, x23
	add	w19, w19, 1
	bl	BsGet
	and	w0, w0, 1
	cmp	w0, wzr
	csneg	w20, w20, w20, eq
	b	.L42
	.size	mvc_se_v, .-mvc_se_v
	.align	3
.LC9:
	.xword	.LC7
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_u_v
	.type	mvc_u_v, %function
mvc_u_v:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x22, x2
	mov	w19, w1
	bl	_mcount
	mov	w1, w19
	add	x0, x21, 872
	bl	BsGet
	mov	w20, w0
	ldr	x4, [x21, 240]
	mov	w3, w0
	ldr	x1, .LC10
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
	.size	mvc_u_v, .-mvc_u_v
	.align	3
.LC10:
	.xword	.LC7
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_u_1
	.type	mvc_u_1, %function
mvc_u_1:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	mov	w1, 1
	add	x0, x20, 872
	bl	BsGet
	mov	w19, w0
	ldr	x5, [x20, 240]
	mov	w3, w0
	ldr	x1, .LC11
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
	.size	mvc_u_1, .-mvc_u_1
	.align	3
.LC11:
	.xword	.LC7
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetMinPOC
	.type	MVC_GetMinPOC, %function
MVC_GetMinPOC:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x24, x3
	mov	x21, x0
	mov	x0, x30
	mov	x23, x2
	mov	w22, w1
	add	x26, x21, 11124736
	bl	_mcount
	mov	w0, -1
	str	w0, [x24]
	mov	w0, 2147483647
	str	w0, [x23]
	ldr	w0, [x26, 792]
	ldr	w1, [x26, 796]
	cmp	w1, w0
	bls	.L53
	str	w0, [x26, 796]
.L53:
	mov	w25, -1
	mov	w20, 0
	cbnz	w0, .L68
	b	.L59
	.p2align 3
.L56:
	ldr	w2, [x1, 32]
	ldr	w3, [x23]
	cmp	w3, w2
	ble	.L55
	ldrb	w3, [x1, 5]
	cbz	w3, .L55
	ldrb	w0, [x0, 1]
	sub	w0, w0, #1
	uxtb	w0, w0
	cmp	w0, 1
	bls	.L75
	.p2align 2
.L55:
	ldr	w0, [x26, 792]
	add	w20, w20, 1
	cmp	w0, w20
	bls	.L59
.L68:
	add	x19, x21, x20, uxtw 3
	add	x19, x19, 11124736
	ldr	x0, [x19, 408]
	cbz	x0, .L55
	ldrsb	w1, [x0, 6]
	ldr	w0, [x21, 120]
	bl	FSP_GetLogicFs
	cbz	x0, .L55
	cmn	w22, #1
	ldr	x1, [x19, 408]
	bne	.L56
	ldrb	w2, [x1, 5]
	cbz	w2, .L55
	ldrb	w0, [x0, 1]
	sub	w0, w0, #1
	uxtb	w0, w0
	cmp	w0, 1
	bhi	.L55
	ldr	w0, [x1, 32]
	ldr	w2, [x23]
	cmp	w2, w0
	ble	.L57
	str	w0, [x23]
	str	w20, [x24]
	add	w20, w20, 1
	ldr	x0, [x19, 408]
	ldr	w25, [x0, 56]
	ldr	w0, [x26, 792]
	cmp	w0, w20
	bhi	.L68
.L59:
	ldr	w0, [x24]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x25, x26, [sp, 64]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L75:
	ldr	w0, [x1, 56]
	cmp	w22, w0
	bne	.L55
	str	w2, [x23]
	str	w20, [x24]
	b	.L55
	.p2align 3
.L57:
	bne	.L55
	ldr	w0, [x1, 56]
	cmp	w0, w25
	bge	.L55
	str	w20, [x24]
	ldr	x0, [x19, 408]
	ldr	w25, [x0, 56]
	b	.L55
	.size	MVC_GetMinPOC, .-MVC_GetMinPOC
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_FrameStoreRefFlg
	.type	MVC_FrameStoreRefFlg, %function
MVC_FrameStoreRefFlg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x19, 3]
	ldr	x19, [sp, 16]
	cmp	w0, wzr
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_FrameStoreRefFlg, .-MVC_FrameStoreRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_NonLongTermRefFlg
	.type	MVC_NonLongTermRefFlg, %function
MVC_NonLongTermRefFlg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w1, [x19, 3]
	cmp	w1, 3
	beq	.L96
	tbnz	x1, 0, .L97
	mov	w0, 0
	tbnz	x1, 1, .L82
.L89:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L97:
	ldrb	w2, [x19, 753]
	mov	w0, 1
	cbz	w2, .L89
	mov	w0, 0
	tbz	x1, 1, .L89
	b	.L82
	.p2align 3
.L96:
	ldrb	w1, [x19, 705]
	mov	w0, 1
	cbz	w1, .L89
	ldrb	w1, [x19, 753]
	cbz	w1, .L89
.L82:
	ldrb	w0, [x19, 801]
	ldr	x19, [sp, 16]
	cmp	w0, wzr
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_NonLongTermRefFlg, .-MVC_NonLongTermRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ShortTermRefFlg
	.type	MVC_ShortTermRefFlg, %function
MVC_ShortTermRefFlg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w1, [x19, 3]
	cmp	w1, 3
	beq	.L114
	tbnz	x1, 0, .L115
.L102:
	mov	w0, 0
	tbnz	x1, 1, .L103
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L115:
	ldr	w0, [x19, 752]
	and	w0, w0, 16776960
	cmp	w0, 65536
	bne	.L102
.L107:
	mov	w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L114:
	ldr	w0, [x19, 704]
	and	w0, w0, 16776960
	cmp	w0, 65536
	beq	.L107
	ldr	w0, [x19, 752]
	and	w0, w0, 16776960
	cmp	w0, 65536
	beq	.L107
.L103:
	ldr	w0, [x19, 800]
	ldr	x19, [sp, 16]
	and	w0, w0, 16776960
	cmp	w0, 65536
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_ShortTermRefFlg, .-MVC_ShortTermRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_LongTermRefFlg
	.type	MVC_LongTermRefFlg, %function
MVC_LongTermRefFlg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w1, [x19, 3]
	cmp	w1, 3
	beq	.L132
	tbnz	x1, 0, .L133
.L120:
	mov	w0, 0
	tbnz	x1, 1, .L121
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L133:
	ldr	w0, [x19, 752]
	and	w0, w0, 16776960
	cmp	w0, 256
	bne	.L120
.L125:
	mov	w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L132:
	ldr	w0, [x19, 704]
	and	w0, w0, 16776960
	cmp	w0, 256
	beq	.L125
	ldr	w0, [x19, 752]
	and	w0, w0, 16776960
	cmp	w0, 256
	beq	.L125
.L121:
	ldr	w0, [x19, 800]
	ldr	x19, [sp, 16]
	and	w0, w0, 16776960
	cmp	w0, 256
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_LongTermRefFlg, .-MVC_LongTermRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_UpdateLTReflist
	.type	MVC_UpdateLTReflist, %function
MVC_UpdateLTReflist:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x23, x0
	mov	x0, x30
	add	x26, x23, 11124736
	bl	_mcount
	ldr	w24, [x26, 792]
	cbz	w24, .L135
	sub	w22, w24, #1
	add	x20, x26, 408
	add	x22, x22, 1388544
	mov	w19, 0
	add	x22, x22, 2100
	add	x25, x23, 11157504
	add	x22, x23, x22, lsl 3
	b	.L137
	.p2align 3
.L136:
	cmp	x22, x20
	beq	.L151
.L137:
	ldr	x21, [x20]
	add	x20, x20, 8
	mov	x0, x21
	cbz	x21, .L136
	bl	MVC_LongTermRefFlg
	cbz	w0, .L136
	ldr	w1, [x21, 56]
	ldr	w0, [x25, 3048]
	cmp	w1, w0
	bne	.L136
	uxtw	x0, w19
	cmp	x22, x20
	add	x0, x0, 1388544
	add	w19, w19, 1
	add	x0, x23, x0, lsl 3
	str	x21, [x0, 17048]
	bne	.L137
	.p2align 2
.L151:
	cmp	w19, w24
	str	w19, [x26, 804]
	bcs	.L134
	.p2align 2
.L146:
	uxtw	x0, w19
	add	w19, w19, 1
	add	x0, x0, 1388544
	cmp	w19, w24
	add	x0, x23, x0, lsl 3
	str	xzr, [x0, 17048]
	bne	.L146
.L134:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L135:
	str	wzr, [x26, 804]
	b	.L134
	.size	MVC_UpdateLTReflist, .-MVC_UpdateLTReflist
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_UpdateReflist
	.type	MVC_UpdateReflist, %function
MVC_UpdateReflist:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x23, x0
	mov	x0, x30
	add	x26, x23, 11124736
	bl	_mcount
	ldr	w24, [x26, 792]
	cbz	w24, .L153
	sub	w22, w24, #1
	add	x20, x26, 408
	add	x22, x22, 1388544
	mov	w19, 0
	add	x22, x22, 2100
	add	x25, x23, 11157504
	add	x22, x23, x22, lsl 3
	b	.L155
	.p2align 3
.L154:
	cmp	x22, x20
	beq	.L169
.L155:
	ldr	x21, [x20]
	add	x20, x20, 8
	mov	x0, x21
	cbz	x21, .L154
	bl	MVC_ShortTermRefFlg
	cbz	w0, .L154
	ldr	w1, [x21, 56]
	ldr	w0, [x25, 3048]
	cmp	w1, w0
	bne	.L154
	uxtw	x0, w19
	cmp	x22, x20
	add	x0, x0, 1388544
	add	w19, w19, 1
	add	x0, x23, x0, lsl 3
	str	x21, [x0, 16920]
	bne	.L155
	.p2align 2
.L169:
	cmp	w19, w24
	str	w19, [x26, 800]
	bcs	.L152
	.p2align 2
.L164:
	uxtw	x0, w19
	add	w19, w19, 1
	add	x0, x0, 1388544
	cmp	w19, w24
	add	x0, x23, x0, lsl 3
	str	xzr, [x0, 16920]
	bne	.L164
.L152:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L153:
	str	wzr, [x26, 800]
	b	.L152
	.size	MVC_UpdateReflist, .-MVC_UpdateReflist
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetPicNumX
	.type	MVC_GetPicNumX, %function
MVC_GetPicNumX:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldrb	w0, [x20, 3]
	ldr	w2, [x20, 664]
	cbz	w0, .L172
	lsl	w2, w2, 1
	add	w2, w2, 1
.L172:
	mvn	w0, w19
	add	w0, w0, w2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_GetPicNumX, .-MVC_GetPicNumX
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_UnMarkFrameStoreRef
	.type	MVC_UnMarkFrameStoreRef, %function
MVC_UnMarkFrameStoreRef:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x19, 2]
	tbz	x0, 0, .L174
	ldrb	w1, [x19, 3]
	strb	wzr, [x19, 753]
	and	w1, w1, 2
	strb	wzr, [x19, 754]
	strb	w1, [x19, 3]
.L174:
	tbz	x0, 1, .L175
	ldrb	w1, [x19, 3]
	strb	wzr, [x19, 801]
	and	w1, w1, 1
	strb	wzr, [x19, 802]
	strb	w1, [x19, 3]
.L175:
	cmp	w0, 3
	bne	.L176
	strb	wzr, [x19, 706]
	strb	wzr, [x19, 705]
.L176:
	strb	wzr, [x19, 3]
	mov	w2, 0
	ldrsb	w1, [x19, 6]
	ldr	w0, [x20, 120]
	bl	FSP_SetRef
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_UnMarkFrameStoreRef, .-MVC_UnMarkFrameStoreRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	MVC_SlidingWinMark.part.3, %function
MVC_SlidingWinMark.part.3:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 11124736
	ldr	w5, [x1, 792]
	cbz	w5, .L200
	add	x1, x1, 408
	mov	w7, 0
	mov	w6, 2147483647
	mov	w2, 0
	add	x8, x19, 11157504
	.p2align 2
.L190:
	ldr	x0, [x1]
	cbz	x0, .L185
	ldr	w3, [x0, 64]
	cmp	w3, w6
	bcs	.L185
	ldrb	w4, [x0, 3]
	cbz	w4, .L185
	cmp	w4, 3
	beq	.L256
	tbnz	x4, 0, .L257
.L189:
	tbnz	x4, 1, .L198
	.p2align 2
.L185:
	add	w2, w2, 1
	add	x1, x1, 8
	cmp	w2, w5
	bne	.L190
.L184:
	sxtw	x0, w7
	add	x0, x0, 1388544
	add	x0, x19, x0, lsl 3
	ldr	x1, [x0, 16792]
	cbz	x1, .L183
	ldrb	w0, [x1, 3]
	cbz	w0, .L183
	cmp	w0, 3
	beq	.L258
	tbnz	x0, 0, .L259
.L195:
	tbnz	x0, 1, .L199
.L183:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L257:
	ldrb	w9, [x0, 753]
	cbnz	w9, .L189
.L187:
	ldr	w4, [x0, 56]
	ldr	w0, [x8, 3048]
	cmp	w4, w0
	csel	w6, w6, w3, ne
	csel	w7, w7, w2, ne
	b	.L185
	.p2align 3
.L256:
	ldrb	w4, [x0, 705]
	cbz	w4, .L187
	ldrb	w4, [x0, 753]
	cbz	w4, .L187
.L198:
	ldrb	w4, [x0, 801]
	cbnz	w4, .L185
	ldr	w4, [x0, 56]
	ldr	w0, [x8, 3048]
	cmp	w4, w0
	csel	w6, w6, w3, ne
	csel	w7, w7, w2, ne
	b	.L185
	.p2align 3
.L259:
	ldrb	w2, [x1, 753]
	cbnz	w2, .L195
.L193:
	add	x0, x19, 11157504
	ldr	w2, [x1, 56]
	ldr	w0, [x0, 3048]
	cmp	w2, w0
	bne	.L183
	mov	x0, x19
	bl	MVC_UnMarkFrameStoreRef
	mov	x0, x19
	bl	MVC_UpdateReflist
	b	.L183
	.p2align 3
.L258:
	ldrb	w0, [x1, 705]
	cbz	w0, .L193
	ldrb	w0, [x1, 753]
	cbz	w0, .L193
.L199:
	ldrb	w0, [x1, 801]
	cbz	w0, .L193
	b	.L183
.L200:
	mov	w7, 0
	b	.L184
	.size	MVC_SlidingWinMark.part.3, .-MVC_SlidingWinMark.part.3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_UnMarkLTFrmByFrmIdx
	.type	MVC_UnMarkLTFrmByFrmIdx, %function
MVC_UnMarkLTFrmByFrmIdx:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	add	x0, x20, 11124736
	ldr	w2, [x0, 804]
	cbz	w2, .L260
	sub	w4, w2, #1
	add	x0, x0, 664
	add	x4, x4, 1388544
	add	x5, x20, 11157504
	add	x4, x4, 2132
	add	x4, x20, x4, lsl 3
	b	.L263
	.p2align 3
.L262:
	cmp	x0, x4
	beq	.L260
.L263:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldr	w3, [x1, 28]
	cmp	w3, w19
	bne	.L262
	ldr	w3, [x1, 56]
	ldr	w2, [x5, 3048]
	cmp	w3, w2
	bne	.L262
	mov	x0, x20
	bl	MVC_UnMarkFrameStoreRef
.L260:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_UnMarkLTFrmByFrmIdx, .-MVC_UnMarkLTFrmByFrmIdx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_UnMarkLTFldByFrmIdx
	.type	MVC_UnMarkLTFldByFrmIdx, %function
MVC_UnMarkLTFldByFrmIdx:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x22, x1
	mov	w20, w2
	mov	w19, w3
	bl	_mcount
	add	x0, x21, 11124736
	ldr	w4, [x0, 804]
	cbz	w4, .L268
	sub	w6, w4, #1
	add	x0, x0, 664
	add	x6, x6, 1388544
	add	x7, x21, 11157504
	add	x6, x6, 2132
	add	x6, x21, x6, lsl 3
	b	.L272
	.p2align 3
.L270:
	cmp	x0, x6
	beq	.L268
.L272:
	ldr	x4, [x0]
	add	x0, x0, 8
	ldr	w5, [x4, 28]
	cmp	w5, w19
	bne	.L270
	ldr	w5, [x4, 56]
	ldr	w3, [x7, 3048]
	cmp	w5, w3
	bne	.L270
	cmp	w20, 1
	beq	.L284
	cmp	w20, 2
	bne	.L270
	ldrb	w1, [x4, 753]
	cmp	w1, wzr
	ccmp	x4, x22, 0, ne
	beq	.L270
.L283:
	mov	x1, x4
	mov	x0, x21
	bl	MVC_UnMarkFrameStoreRef
.L268:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L284:
	ldrb	w1, [x4, 801]
	cmp	w1, wzr
	ccmp	x4, x22, 0, ne
	beq	.L270
	b	.L283
	.size	MVC_UnMarkLTFldByFrmIdx, .-MVC_UnMarkLTFldByFrmIdx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_UnMarkSTRef
	.type	MVC_UnMarkSTRef, %function
MVC_UnMarkSTRef:
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
	cbnz	w0, .L286
	add	x0, x19, 11124736
	ldr	w3, [x20, 664]
	sub	w3, w3, #1
	ldr	w1, [x0, 800]
	sub	w2, w3, w21
	cbz	w1, .L285
	sub	w4, w1, #1
	add	x0, x0, 536
	add	x4, x4, 1388544
	add	x5, x19, 11157504
	add	x4, x4, 2116
	add	x4, x19, x4, lsl 3
	b	.L292
	.p2align 3
.L291:
	cmp	x0, x4
	beq	.L285
.L292:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldr	w3, [x1, 724]
	cmp	w3, w2
	bne	.L291
	ldrb	w3, [x1, 3]
	cmp	w3, 3
	bne	.L291
	ldr	w3, [x1, 704]
	and	w3, w3, 16776960
	cmp	w3, 65536
	bne	.L291
	ldr	w6, [x1, 56]
	ldr	w3, [x5, 3048]
	cmp	w6, w3
	bne	.L291
	mov	x0, x19
	bl	MVC_UnMarkFrameStoreRef
.L285:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L286:
	add	x1, x19, 11124736
	ldr	w0, [x20, 664]
	add	x4, x1, 536
	mov	w3, 0
	lsl	w0, w0, 1
	add	x8, x19, 11157504
	ldr	w6, [x1, 800]
	sub	w2, w0, w21
	cbz	w6, .L285
	.p2align 2
.L306:
	ldr	x1, [x4]
	add	x4, x4, 8
	ldrb	w0, [x1, 3]
	and	w7, w0, 1
	tbz	x0, 0, .L293
	ldr	w5, [x1, 752]
	and	w5, w5, 16776960
	cmp	w5, 65536
	beq	.L313
.L293:
	tbz	x0, 1, .L295
	ldr	w0, [x1, 800]
	and	w0, w0, 16776960
	cmp	w0, 65536
	beq	.L314
.L295:
	add	w3, w3, 1
	cmp	w3, w6
	bne	.L306
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L313:
	ldr	w9, [x1, 56]
	ldr	w5, [x8, 3048]
	cmp	w9, w5
	bne	.L293
	ldr	w5, [x1, 772]
	cmp	w5, w2
	bne	.L293
	add	x2, x19, x3, uxtw 3
	and	w0, w0, 2
	add	x2, x2, 11124736
	strb	w0, [x1, 3]
	ldr	x0, [x2, 536]
	strb	wzr, [x0, 754]
	ldr	x0, [x2, 536]
	ldrb	w1, [x0, 704]
	cmp	w1, 3
	ccmp	w1, wzr, 4, ne
	bne	.L294
	strb	wzr, [x0, 706]
	ldr	x0, [x2, 536]
	strb	wzr, [x0, 705]
	ldr	x0, [x2, 536]
.L294:
	ldrb	w1, [x0, 3]
	cbnz	w1, .L285
	ldr	w1, [x0, 48]
	mov	w2, 0
	add	x1, x19, x1, lsl 2
	str	wzr, [x1, 148]
	ldrsb	w1, [x0, 6]
	ldr	w0, [x19, 120]
	bl	FSP_SetRef
	b	.L285
	.p2align 3
.L314:
	ldr	w5, [x1, 56]
	ldr	w0, [x8, 3048]
	cmp	w5, w0
	bne	.L295
	ldr	w0, [x1, 820]
	cmp	w0, w2
	bne	.L295
	add	x0, x19, x3, uxtw 3
	strb	w7, [x1, 3]
	add	x0, x0, 11124736
	ldr	x1, [x0, 536]
	strb	wzr, [x1, 802]
	ldr	x1, [x0, 536]
	ldrb	w2, [x1, 704]
	cmp	w2, 3
	ccmp	w2, wzr, 4, ne
	bne	.L296
	strb	wzr, [x1, 706]
	ldr	x1, [x0, 536]
	strb	wzr, [x1, 705]
	ldr	x1, [x0, 536]
.L296:
	ldrb	w0, [x1, 3]
	cbnz	w0, .L285
	ldr	w0, [x1, 48]
	mov	w2, 0
	add	x0, x19, x0, lsl 2
	str	wzr, [x0, 148]
	ldrsb	w1, [x1, 6]
	ldr	w0, [x19, 120]
	bl	FSP_SetRef
	b	.L285
	.size	MVC_UnMarkSTRef, .-MVC_UnMarkSTRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_UnMarkLTRef
	.type	MVC_UnMarkLTRef, %function
MVC_UnMarkLTRef:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x1
	mov	x19, x0
	mov	x0, x30
	mov	w20, w2
	bl	_mcount
	ldrb	w0, [x21, 3]
	cbz	w0, .L316
	add	x0, x19, 11124736
	mov	w3, 0
	add	x4, x0, 664
	add	x2, x19, 11157504
	ldr	w6, [x0, 804]
	cbz	w6, .L315
	.p2align 2
.L336:
	ldr	x1, [x4]
	add	x4, x4, 8
	ldrb	w0, [x1, 3]
	and	w7, w0, 1
	tbz	x0, 0, .L321
	ldr	w5, [x1, 752]
	and	w5, w5, 16776960
	cmp	w5, 256
	beq	.L343
.L321:
	tbz	x0, 1, .L323
	ldr	w0, [x1, 800]
	and	w0, w0, 16776960
	cmp	w0, 256
	beq	.L344
.L323:
	add	w3, w3, 1
	cmp	w3, w6
	bne	.L336
.L315:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L343:
	ldr	w8, [x1, 56]
	ldr	w5, [x2, 3048]
	cmp	w8, w5
	bne	.L321
	ldr	w5, [x1, 768]
	cmp	w20, w5
	bne	.L321
	add	x2, x19, x3, uxtw 3
	and	w0, w0, 2
	add	x2, x2, 11124736
	strb	w0, [x1, 3]
	ldr	x0, [x2, 664]
	strb	wzr, [x0, 753]
	ldr	x0, [x2, 664]
	ldrb	w1, [x0, 704]
	cmp	w1, 3
	ccmp	w1, wzr, 4, ne
	bne	.L322
	strb	wzr, [x0, 706]
	ldr	x0, [x2, 664]
	strb	wzr, [x0, 705]
	ldr	x0, [x2, 664]
.L322:
	ldrb	w1, [x0, 3]
	cbnz	w1, .L315
	ldr	w1, [x0, 48]
	mov	w2, 0
	add	x1, x19, x1, lsl 2
	str	wzr, [x1, 148]
	ldrsb	w1, [x0, 6]
	ldr	w0, [x19, 120]
	bl	FSP_SetRef
	b	.L315
	.p2align 3
.L344:
	ldr	w5, [x1, 56]
	ldr	w0, [x2, 3048]
	cmp	w5, w0
	bne	.L323
	ldr	w0, [x1, 816]
	cmp	w20, w0
	bne	.L323
	add	x0, x19, x3, uxtw 3
	strb	w7, [x1, 3]
	add	x0, x0, 11124736
	ldr	x1, [x0, 664]
	strb	wzr, [x1, 801]
	ldr	x1, [x0, 664]
	ldrb	w2, [x1, 704]
	cmp	w2, 3
	ccmp	w2, wzr, 4, ne
	bne	.L324
	strb	wzr, [x1, 706]
	ldr	x1, [x0, 664]
	strb	wzr, [x1, 705]
	ldr	x1, [x0, 664]
.L324:
	ldrb	w0, [x1, 3]
	cbnz	w0, .L315
	ldr	w0, [x1, 48]
	mov	w2, 0
	add	x0, x19, x0, lsl 2
	str	wzr, [x0, 148]
	ldrsb	w1, [x1, 6]
	ldr	w0, [x19, 120]
	bl	FSP_SetRef
	b	.L315
	.p2align 3
.L316:
	add	x0, x19, 11124736
	ldr	w1, [x0, 804]
	cbz	w1, .L315
	sub	w4, w1, #1
	add	x0, x0, 664
	add	x4, x4, 1388544
	add	x5, x19, 11157504
	add	x4, x4, 2132
	add	x4, x19, x4, lsl 3
	b	.L327
	.p2align 3
.L326:
	cmp	x0, x4
	beq	.L315
.L327:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldr	w3, [x1, 720]
	cmp	w3, w20
	bne	.L326
	ldrb	w2, [x1, 3]
	cmp	w2, 3
	bne	.L326
	ldr	w2, [x1, 704]
	and	w2, w2, 16776960
	cmp	w2, 256
	bne	.L326
	ldr	w3, [x1, 56]
	ldr	w2, [x5, 3048]
	cmp	w3, w2
	bne	.L326
	mov	x0, x19
	bl	MVC_UnMarkFrameStoreRef
	b	.L315
	.size	MVC_UnMarkLTRef, .-MVC_UnMarkLTRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_MarkPicLTRef
	.type	MVC_MarkPicLTRef, %function
MVC_MarkPicLTRef:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x3
	mov	x21, x0
	mov	x0, x30
	mov	w20, w2
	mov	w19, w1
	bl	_mcount
	ldrb	w2, [x22, 3]
	add	x0, x21, 11124736
	cbz	w2, .L346
	ldr	w7, [x0, 800]
	mov	w3, 0
	add	x4, x0, 536
	add	x8, x21, 11157504
	cbz	w7, .L345
	.p2align 2
.L367:
	ldr	x0, [x4]
	ldrb	w5, [x0, 3]
	tbz	x5, 0, .L352
	ldr	w6, [x0, 752]
	and	w6, w6, 16776960
	cmp	w6, 65536
	beq	.L373
.L352:
	tbz	x5, 1, .L355
	ldr	w1, [x0, 800]
	and	w1, w1, 16776960
	cmp	w1, 65536
	beq	.L374
.L355:
	add	w3, w3, 1
	add	x4, x4, 8
	cmp	w3, w7
	bne	.L367
.L345:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L373:
	ldr	w1, [x0, 772]
	cmp	w20, w1
	bne	.L352
	ldr	w6, [x0, 56]
	ldr	w1, [x8, 3048]
	cmp	w6, w1
	bne	.L352
	ldrb	w1, [x0, 801]
	cmp	w1, 1
	bne	.L356
	ldr	w1, [x0, 28]
	cmp	w19, w1
	bne	.L355
.L356:
	add	x3, x21, x3, uxtw 3
	str	w19, [x0, 28]
	add	x0, x3, 11124736
	cmp	w2, 1
	lsl	w1, w19, 1
	mov	w2, 1
	csinc	w1, w1, w1, ne
	ldr	x3, [x0, 536]
	str	w1, [x3, 768]
	ldr	x1, [x0, 536]
	strb	w2, [x1, 753]
	ldr	x1, [x0, 536]
	strb	wzr, [x1, 754]
	ldr	x1, [x0, 536]
	ldrb	w2, [x1, 704]
	cmp	w2, 3
	ccmp	w2, wzr, 4, ne
	bne	.L345
	ldrb	w3, [x1, 753]
	ldrb	w2, [x1, 801]
	cmp	w2, w3
	bne	.L345
	strb	w2, [x1, 705]
	ldr	x0, [x0, 536]
	ldrb	w1, [x0, 754]
	strb	w1, [x0, 706]
	b	.L345
	.p2align 3
.L374:
	ldr	w1, [x0, 820]
	cmp	w1, w20
	bne	.L355
	ldr	w5, [x0, 56]
	ldr	w1, [x8, 3048]
	cmp	w5, w1
	bne	.L355
	ldrb	w1, [x0, 753]
	cmp	w1, 1
	bne	.L359
	ldr	w1, [x0, 28]
	cmp	w1, w19
	bne	.L355
.L359:
	add	x3, x21, x3, uxtw 3
	str	w19, [x0, 28]
	add	x0, x3, 11124736
	cmp	w2, 2
	lsl	w1, w19, 1
	mov	w2, 1
	csinc	w1, w1, w1, ne
	ldr	x3, [x0, 536]
	str	w1, [x3, 816]
	ldr	x1, [x0, 536]
	strb	w2, [x1, 801]
	ldr	x1, [x0, 536]
	strb	wzr, [x1, 802]
	ldr	x1, [x0, 536]
	ldrb	w2, [x1, 704]
	cmp	w2, 3
	ccmp	w2, wzr, 4, ne
	bne	.L345
	ldrb	w3, [x1, 753]
	ldrb	w2, [x1, 801]
	cmp	w2, w3
	bne	.L345
	strb	w2, [x1, 705]
	ldr	x0, [x0, 536]
	ldrb	w1, [x0, 802]
	strb	w1, [x0, 706]
	b	.L345
	.p2align 3
.L346:
	ldr	w6, [x0, 800]
	cbz	w6, .L345
	add	x0, x0, 536
	mov	w1, 0
	add	x3, x21, 11157504
	b	.L351
	.p2align 3
.L350:
	add	w1, w1, 1
	cmp	w1, w6
	beq	.L345
.L351:
	ldr	x4, [x0]
	add	x0, x0, 8
	ldrb	w5, [x4, 3]
	cmp	w5, 3
	bne	.L350
	ldr	w5, [x4, 704]
	and	w5, w5, 16776960
	cmp	w5, 65536
	bne	.L350
	ldr	w2, [x4, 724]
	cmp	w20, w2
	bne	.L350
	ldr	w2, [x3, 3048]
	ldr	w5, [x4, 56]
	cmp	w5, w2
	bne	.L350
	add	x0, x21, x1, uxtw 3
	str	w19, [x4, 28]
	add	x0, x0, 11124736
	mov	w1, 1
	ldr	x2, [x0, 536]
	str	w19, [x2, 720]
	ldr	x2, [x0, 536]
	strb	w1, [x2, 705]
	ldr	x2, [x0, 536]
	strb	w1, [x2, 753]
	ldr	x2, [x0, 536]
	strb	w1, [x2, 801]
	ldr	x1, [x0, 536]
	strb	wzr, [x1, 706]
	ldr	x1, [x0, 536]
	strb	wzr, [x1, 754]
	ldr	x0, [x0, 536]
	strb	wzr, [x0, 802]
	b	.L345
	.size	MVC_MarkPicLTRef, .-MVC_MarkPicLTRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_MarkSTToLTRef
	.type	MVC_MarkSTToLTRef, %function
MVC_MarkSTToLTRef:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x1
	mov	x21, x0
	mov	x0, x30
	mov	w20, w2
	mov	w19, w3
	bl	_mcount
	ldrb	w0, [x22, 3]
	cbnz	w0, .L376
	ldr	w2, [x22, 664]
	mov	w1, w19
	mov	x0, x21
	sub	w2, w2, #1
	sub	w20, w2, w20
	bl	MVC_UnMarkLTFrmByFrmIdx
.L377:
	mov	x3, x22
	mov	w2, w20
	mov	w1, w19
	mov	x0, x21
	bl	MVC_MarkPicLTRef
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L376:
	add	x0, x21, 11124736
	ldr	w3, [x22, 664]
	lsl	w3, w3, 1
	ldr	w1, [x0, 800]
	sub	w20, w3, w20
	cbz	w1, .L377
	sub	w5, w1, #1
	add	x0, x0, 536
	add	x5, x5, 1388544
	add	x6, x21, 11157504
	add	x5, x5, 2116
	add	x5, x21, x5, lsl 3
	.p2align 2
.L380:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w3, [x1, 3]
	tbz	x3, 0, .L378
	ldr	w4, [x1, 752]
	and	w4, w4, 16776960
	cmp	w4, 65536
	beq	.L391
.L378:
	tbz	x3, 1, .L379
	ldr	w3, [x1, 800]
	and	w3, w3, 16776960
	cmp	w3, 65536
	beq	.L392
.L379:
	cmp	x0, x5
	bne	.L380
	b	.L377
	.p2align 3
.L391:
	ldr	w2, [x1, 772]
	cmp	w2, w20
	bne	.L378
	ldr	w4, [x1, 56]
	ldr	w2, [x6, 3048]
	cmp	w4, w2
	bne	.L378
	mov	w3, w19
	mov	w2, 1
	mov	x0, x21
	bl	MVC_UnMarkLTFldByFrmIdx
	b	.L377
	.p2align 3
.L392:
	ldr	w2, [x1, 820]
	cmp	w2, w20
	bne	.L379
	ldr	w3, [x1, 56]
	ldr	w2, [x6, 3048]
	cmp	w3, w2
	bne	.L379
	mov	w3, w19
	mov	w2, 2
	mov	x0, x21
	bl	MVC_UnMarkLTFldByFrmIdx
	b	.L377
	.size	MVC_MarkSTToLTRef, .-MVC_MarkSTToLTRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_UpdateMaxLTFrmIdx
	.type	MVC_UpdateMaxLTFrmIdx, %function
MVC_UpdateMaxLTFrmIdx:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	add	x21, x22, 11124736
	mov	w20, w1
	bl	_mcount
	ldr	w0, [x21, 804]
	str	w20, [x21, 808]
	cbz	w0, .L393
	mov	w2, w20
	mov	w19, 0
	add	x20, x22, 11157504
	b	.L395
	.p2align 3
.L401:
	ldr	w2, [x21, 808]
.L395:
	uxtw	x0, w19
	add	w19, w19, 1
	add	x0, x0, 1388544
	add	x0, x22, x0, lsl 3
	ldr	x1, [x0, 17048]
	ldr	w0, [x1, 28]
	cmp	w0, w2
	bcc	.L396
	ldr	w2, [x1, 56]
	ldr	w0, [x20, 3048]
	cmp	w2, w0
	beq	.L400
.L396:
	ldr	w0, [x21, 804]
	cmp	w0, w19
	bhi	.L401
.L393:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L400:
	mov	x0, x22
	bl	MVC_UnMarkFrameStoreRef
	b	.L396
	.size	MVC_UpdateMaxLTFrmIdx, .-MVC_UpdateMaxLTFrmIdx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_UnMarkAllSTRef
	.type	MVC_UnMarkAllSTRef, %function
MVC_UnMarkAllSTRef:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x21, x20, 11124736
	mov	w19, 0
	bl	_mcount
	add	x22, x20, 11157504
	ldr	w0, [x21, 800]
	cbnz	w0, .L407
	b	.L402
	.p2align 3
.L404:
	ldr	w0, [x21, 800]
	cmp	w0, w19
	bls	.L402
.L407:
	uxtw	x0, w19
	ldr	w2, [x22, 3048]
	add	x0, x0, 1388544
	add	w19, w19, 1
	add	x0, x20, x0, lsl 3
	ldr	x1, [x0, 16920]
	ldr	w0, [x1, 56]
	cmp	w0, w2
	bne	.L404
	mov	x0, x20
	bl	MVC_UnMarkFrameStoreRef
	ldr	w0, [x21, 800]
	cmp	w0, w19
	bhi	.L407
.L402:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	MVC_UnMarkAllSTRef, .-MVC_UnMarkAllSTRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_MarkCurrPicLT
	.type	MVC_MarkCurrPicLT, %function
MVC_MarkCurrPicLT:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x1
	mov	x21, x0
	mov	x0, x30
	mov	w20, w2
	bl	_mcount
	ldrb	w2, [x19, 3]
	cbz	w2, .L412
	ldr	x1, [x19, 648]
	mov	w3, w20
	mov	x0, x21
	bl	MVC_UnMarkLTFldByFrmIdx
	strb	wzr, [x19, 5]
	str	w20, [x19, 668]
	mov	w0, 1
	strb	w0, [x19, 4]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L412:
	mov	w1, w20
	mov	x0, x21
	bl	MVC_UnMarkLTFrmByFrmIdx
	strb	wzr, [x19, 5]
	str	w20, [x19, 668]
	mov	w0, 1
	strb	w0, [x19, 4]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	MVC_MarkCurrPicLT, .-MVC_MarkCurrPicLT
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_RemoveFrameStoreOutDPB
	.type	MVC_RemoveFrameStoreOutDPB, %function
MVC_RemoveFrameStoreOutDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w1
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, x19, uxtw 3
	add	x19, x19, 11124736
	bl	_mcount
	ldr	x1, [x19, 408]
	cbz	x1, .L413
	ldr	w0, [x1, 52]
	add	x21, x20, 11124736
	add	x0, x20, x0
	add	x0, x0, 11124736
	strb	wzr, [x0, 816]
	ldr	w0, [x21, 1028]
	cmp	w0, wzr
	cset	w2, ne
	sub	w0, w0, w2
	str	w0, [x21, 1028]
	ldrsb	w1, [x1, 6]
	ldr	w0, [x20, 120]
	bl	FSP_GetLogicFs
	cbz	x0, .L416
	ldrsb	w0, [x0, 1]
	cmp	w0, 3
	beq	.L417
	ldr	x1, [x19, 408]
	mov	w2, 0
	ldr	w0, [x20, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_SetDisplay
.L417:
	ldr	x1, [x19, 408]
	mov	w2, 0
	ldr	w0, [x20, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_SetRef
.L416:
	ldr	x0, [x19, 408]
	strb	wzr, [x0, 2]
	ldr	x0, [x19, 408]
	strb	wzr, [x0, 5]
	ldr	x0, [x19, 408]
	strb	wzr, [x0, 3]
	str	xzr, [x19, 408]
	ldr	w0, [x21, 796]
	sub	w0, w0, #1
	str	w0, [x21, 796]
.L413:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	MVC_RemoveFrameStoreOutDPB, .-MVC_RemoveFrameStoreOutDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_RemoveUnUsedFrameStore
	.type	MVC_RemoveUnUsedFrameStore, %function
MVC_RemoveUnUsedFrameStore:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x23, x0
	mov	x0, x30
	mov	w22, w1
	mov	w19, 0
	bl	_mcount
	add	x0, x23, 11124736
	add	x20, x0, 408
	ldr	w21, [x0, 792]
	cbz	w21, .L445
	.p2align 2
.L440:
	ldr	x2, [x20]
	add	x20, x20, 8
	cbz	x2, .L431
	ldrb	w0, [x2, 3]
	cbnz	w0, .L431
	ldrb	w0, [x2, 5]
	cbnz	w0, .L431
	ldr	w0, [x2, 56]
	cmp	w0, w22
	ccmn	w22, #1, 4, ne
	beq	.L446
	.p2align 2
.L431:
	add	w19, w19, 1
	cmp	w21, w19
	bne	.L440
.L445:
	mov	w0, 0
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L446:
	ldr	w3, [x2, 16]
	mov	w1, w19
	mov	x0, x23
	cmp	w3, 1
	beq	.L431
	strb	wzr, [x2, 2]
	bl	MVC_RemoveFrameStoreOutDPB
	b	.L431
	.size	MVC_RemoveUnUsedFrameStore, .-MVC_RemoveUnUsedFrameStore
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_CheckFrameStore
	.type	MVC_CheckFrameStore, %function
MVC_CheckFrameStore:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldrb	w0, [x20, 6]
	cbnz	w0, .L448
	ldrsb	w0, [x19, 8]
	cmp	w0, 1
	bne	.L460
	strb	w0, [x20, 6]
.L448:
	ldrsb	w1, [x19, 6]
	ldr	w0, [x20, 120]
	bl	FSP_GetLogicFs
	cbz	x0, .L450
	ldrsb	w3, [x0, 1]
	cmp	w3, 3
	ccmp	w3, wzr, 4, ne
	beq	.L469
	ldrb	w2, [x19, 2]
	ldrb	w3, [x19, 1]
	cbz	w2, .L459
	cmp	w3, 1
	beq	.L459
	mov	x1, 16711680
	ldr	x4, [x19]
	movk	x1, 0xff, lsl 32
	mov	x3, 196608
	movk	x3, 0x3, lsl 32
	and	x1, x4, x1
	cmp	x1, x3
	beq	.L470
	cmp	w2, 1
	beq	.L471
	cmp	w2, 2
	beq	.L472
.L456:
	ldr	x1, [x20, 224]
	ldr	w2, [x0, 200]
	mov	w0, 0
	ldr	w3, [x1, 4]
	cmp	w2, w3
	bhi	.L473
.L466:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L469:
	ldrsb	w2, [x19, 6]
	mov	w0, 1
	ldr	x1, .LC15
	bl	dprint_vfmw
.L452:
	ldr	w0, [x19, 16]
	cmp	w0, 1
	beq	.L457
	mov	w0, -3
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L471:
	ldrb	w3, [x19, 4]
	tbz	x3, 0, .L456
	ldr	x1, .LC23
	mov	w0, w2
	bl	dprint_vfmw
	mov	w0, -1
	b	.L466
	.p2align 3
.L472:
	ldrb	w3, [x19, 4]
	tbz	x3, 1, .L456
	ldr	x1, .LC25
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L466
	.p2align 3
.L457:
	mov	w1, 2
	mov	w0, -3
	str	w1, [x19, 16]
	b	.L466
	.p2align 3
.L460:
	mov	w0, -1
	b	.L466
	.p2align 3
.L450:
	ldrsb	w4, [x19, 6]
	mov	x2, x19
	ldr	x1, .LC17
	mov	w0, 1
	ldr	w3, [x19, 16]
	bl	dprint_vfmw
	b	.L452
	.p2align 3
.L459:
	ldr	x1, .LC19
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L466
	.p2align 3
.L473:
	ldr	x1, .LC27
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L466
.L470:
	ldrb	w3, [x19, 4]
	mov	w0, 1
	ldr	x1, .LC21
	bl	dprint_vfmw
	mov	w0, -1
	b	.L466
	.size	MVC_CheckFrameStore, .-MVC_CheckFrameStore
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ExchangePts
	.type	MVC_ExchangePts, %function
MVC_ExchangePts:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x24, x1
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x24, 656]
	cmn	x0, #1
	beq	.L474
	add	x25, x21, 11124736
	ldr	w0, [x25, 792]
	cbz	w0, .L474
	mov	w23, -1
	mov	w20, 0
	mov	x22, -2
	.p2align 2
.L479:
	add	x19, x21, x20, sxtw 3
	add	x19, x19, 11124736
	ldr	x0, [x19, 408]
	cbz	x0, .L478
	ldrsb	w1, [x0, 6]
	ldr	w0, [x21, 120]
	bl	FSP_GetLogicFs
	cbz	x0, .L478
	ldrsb	w0, [x0, 1]
	cmp	w0, 3
	ccmp	w0, wzr, 4, ne
	beq	.L478
	ldr	x0, [x19, 408]
	ldr	x0, [x0, 656]
	cmp	x0, x22
	bcs	.L478
	mov	w23, w20
	mov	x22, x0
	.p2align 2
.L478:
	ldr	w0, [x25, 792]
	add	w20, w20, 1
	cmp	w0, w20
	bhi	.L479
	cmn	w23, #1
	beq	.L474
	ldr	x2, [x24, 656]
	cmp	x22, x2
	bcc	.L493
.L474:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L493:
	ldr	x1, .LC29
	mov	x3, x22
	mov	w0, 29
	bl	dprint_vfmw
	sxtw	x0, w23
	ldr	x1, [x24, 656]
	add	x0, x0, 1388544
	add	x21, x21, x0, lsl 3
	ldr	x0, [x21, 16792]
	str	x1, [x0, 656]
	str	x22, [x24, 656]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	MVC_ExchangePts, .-MVC_ExchangePts
	.align	3
.LC29:
	.xword	.LC28
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetImagePara
	.type	MVC_GetImagePara, %function
MVC_GetImagePara:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	add	x5, x20, 11116544
	mov	w2, 2240
	ldp	x7, x1, [x20, 272]
	ldrb	w6, [x19, 138]
	ldr	w3, [x5, 2856]
	ldrb	w8, [x19, 14]
	ldrb	w4, [x19, 137]
	umull	x2, w3, w2
	ldrb	w0, [x19, 136]
	bfi	w6, w8, 1, 1
	add	x2, x1, x2
	and	w3, w4, -4
	and	w0, w0, -4
	mov	w1, 3992
	mov	w4, w3
	ldr	w2, [x2, 28]
	strb	w6, [x19, 138]
	ldrb	w6, [x19, 15]
	strb	w3, [x19, 137]
	str	w6, [x19, 192]
	add	x6, x20, 11124736
	strb	w0, [x19, 136]
	ldrb	w3, [x19, 2]
	umull	x1, w2, w1
	ldr	w2, [x20, 56]
	cmp	w3, 3
	str	w2, [x19, 180]
	add	x1, x7, x1
	bhi	.L495
	ldr	x2, .LC30
	ldrb	w2, [x2,w3,uxtw]
	adr	x6, .Lrtx497
	add	x2, x6, w2, sxtb #2
	br	x2
.Lrtx497:
	.section	.rodata
	.align	0
	.align	2
.L497:
	.byte	(.L496 - .Lrtx497) / 4
	.byte	(.L498 - .Lrtx497) / 4
	.byte	(.L499 - .Lrtx497) / 4
	.byte	(.L496 - .Lrtx497) / 4
	.text
	.p2align 3
.L499:
	mov	w2, 2
	bfi	w4, w2, 2, 2
.L498:
	ldrb	w7, [x19]
	orr	w2, w4, 3
	ldr	w6, [x19, 44]
	mov	w4, w2
	bfi	w0, w7, 0, 2
	str	w6, [x19, 224]
	strb	w2, [x19, 137]
	add	x6, x20, 11124736
	strb	w0, [x19, 136]
.L495:
	ldrb	w2, [x1, 20]
	mov	w0, 0
	str	w2, [x19, 468]
	str	w2, [x19, 472]
	ldrb	w2, [x1, 24]
	cbz	w2, .L514
	ldr	w0, [x1, 68]
.L514:
	str	w0, [x19, 480]
	mov	w0, 1
	str	w0, [x19, 476]
	ldrb	w0, [x5, 2851]
	cmp	w0, 1
	csel	w0, w0, wzr, eq
	str	w0, [x19, 264]
	ldr	x0, [x20, 224]
	ldr	w0, [x0, 24]
	cbz	w0, .L517
	ldrb	w0, [x19, 704]
	cbz	w0, .L543
.L517:
	ldrsb	w0, [x6, 360]
	cbz	w0, .L518
	ldr	w0, [x6, 376]
	cmp	w0, 3
	beq	.L544
	cmp	w0, 4
	beq	.L545
	cmp	w0, 5
	beq	.L546
	str	wzr, [x19, 348]
	mov	w0, 0
	ldr	x1, .LC32
	ldr	w2, [x6, 376]
	bl	dprint_vfmw
	.p2align 2
.L518:
	ldr	w0, [x20, 120]
	ldrsb	w1, [x19, 6]
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L494
	ldr	x3, .LC33
	mov	x2, 632
	add	x1, x19, 72
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 15
	str	w0, [x20, 296]
	mov	w2, 4
	mov	w1, 1
	ldrb	w0, [x19, 704]
	strb	w1, [x20, 291]
	cmp	w0, wzr
	csel	w0, w0, w2, eq
	strb	w0, [x20, 284]
	ldr	w0, [x19, 740]
	str	w0, [x20, 300]
	strb	w1, [x20, 289]
	str	w0, [x20, 304]
	str	w0, [x20, 308]
.L494:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L543:
	cmp	w3, 3
	bne	.L517
	and	w0, w4, -4
	strb	w0, [x19, 137]
	b	.L517
	.p2align 3
.L496:
	ldrb	w2, [x19, 704]
	cbnz	w2, .L500
	ldp	w2, w6, [x19, 40]
	str	w6, [x19, 224]
	ldrb	w9, [x19]
	cbnz	w2, .L524
	mov	w10, 2
	mov	w7, 3
.L501:
	ldr	w6, [x19, 776]
	ldr	w2, [x19, 824]
	cmp	w6, w2
	beq	.L547
	cset	w2, le
.L512:
	add	x6, x20, 11124736
	ldrb	w8, [x6, 396]
	cmp	w8, 3
	beq	.L526
	cmp	w8, 4
	mov	w8, 0
	csel	w2, w2, w8, ne
.L513:
	bfi	w4, w2, 4, 2
	bfi	w0, w9, 0, 2
	bfi	w4, w7, 2, 2
	strb	w0, [x19, 136]
	mov	w0, w4
	bfi	w0, w10, 0, 2
	strb	w0, [x19, 137]
	mov	w4, w0
	b	.L495
	.p2align 3
.L544:
	mov	w0, 1
	str	w0, [x19, 348]
	b	.L518
	.p2align 3
.L546:
	mov	w0, 3
	str	w0, [x19, 348]
	b	.L518
	.p2align 3
.L500:
	ldr	w6, [x19, 784]
	ldr	w2, [x20, 116]
	ldr	w11, [x19, 832]
	cmp	w6, w2
	bhi	.L548
	cmp	w2, w11
	bcc	.L505
.L503:
	ldr	w2, [x19, 44]
	mov	w7, 3
	ldrb	w9, [x19]
	ldrb	w8, [x19, 803]
	ldrb	w10, [x19, 755]
	str	w2, [x19, 224]
.L506:
	ldrb	w2, [x19, 4]
	cmp	w2, 1
	beq	.L549
	cmp	w2, 2
	beq	.L550
.L508:
	stp	w10, w8, [x19, 128]
	mov	w10, 3
	b	.L501
	.p2align 3
.L505:
	ldrb	w9, [x19, 755]
	mov	w7, 1
	ldrb	w8, [x19, 803]
	mov	w10, w9
	str	w6, [x19, 224]
	b	.L506
	.p2align 3
.L545:
	mov	w0, 2
	str	w0, [x19, 348]
	b	.L518
	.p2align 3
.L526:
	mov	w2, 1
	b	.L513
	.p2align 3
.L547:
	ldr	w2, [x19, 140]
	cmp	w2, 720
	mov	w2, 1
	bne	.L512
	ldr	w2, [x19, 144]
	cmp	w2, 480
	cset	w2, ne
	b	.L512
	.p2align 3
.L548:
	cmp	w2, w11
	bcc	.L503
	ldrb	w9, [x19, 803]
	mov	w7, 2
	ldrb	w10, [x19, 755]
	mov	w8, w9
	str	w11, [x19, 224]
	b	.L506
	.p2align 3
.L524:
	mov	w10, 3
	mov	w7, w10
	b	.L501
	.p2align 3
.L549:
	mov	w9, w8
	mov	w7, 2
	str	w11, [x19, 224]
	b	.L508
	.p2align 3
.L550:
	mov	w9, w10
	mov	w7, 1
	str	w6, [x19, 224]
	b	.L508
	.size	MVC_GetImagePara, .-MVC_GetImagePara
	.align	3
.LC30:
	.xword	.L497
	.align	3
.LC32:
	.xword	.LC31
	.align	3
.LC33:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_SetFrmRepeatCount
	.type	MVC_SetFrmRepeatCount, %function
MVC_SetFrmRepeatCount:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 652]
	add	w0, w0, 2047
	cmp	w0, 4095
	bls	.L552
	mov	x1, x20
	mov	x0, x19
	bl	MVC_SetFrmRepeatCount.part.2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L552:
	str	wzr, [x20, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_SetFrmRepeatCount, .-MVC_SetFrmRepeatCount
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_SplitFrmToFlds
	.type	MVC_SplitFrmToFlds, %function
MVC_SplitFrmToFlds:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w4, [x19, 705]
	mov	w6, 1
	ldrb	w3, [x19, 706]
	mov	w5, 2
	ldrb	w1, [x19, 707]
	ldr	w2, [x19, 736]
	ldr	x0, [x19, 712]
	strb	w4, [x19, 753]
	strb	w3, [x19, 754]
	strb	w6, [x19, 752]
	strb	w1, [x19, 755]
	strb	w4, [x19, 801]
	strb	w3, [x19, 802]
	strb	w5, [x19, 800]
	strb	w1, [x19, 803]
	str	x0, [x19, 760]
	str	w2, [x19, 784]
	str	x0, [x19, 808]
	str	w2, [x19, 832]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_SplitFrmToFlds, .-MVC_SplitFrmToFlds
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_CombineFldsToFrm
	.type	MVC_CombineFldsToFrm, %function
MVC_CombineFldsToFrm:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x19, 776]
	mov	w5, 3
	ldr	w3, [x19, 784]
	ldr	w2, [x19, 824]
	ldr	w0, [x19, 832]
	cmp	w1, w2
	ldr	x4, [x19, 760]
	add	w0, w3, w0
	ldrb	w3, [x19, 801]
	csel	w1, w1, w2, le
	lsr	w0, w0, 1
	strb	w5, [x19, 704]
	str	w1, [x19, 32]
	str	x4, [x19, 712]
	str	w1, [x19, 728]
	str	w0, [x19, 736]
	cbz	w3, .L556
	ldrb	w1, [x19, 753]
	cbz	w1, .L556
	mov	w1, 1
	strb	w1, [x19, 705]
.L558:
	mov	w3, 0
.L559:
	ldrb	w2, [x19, 803]
	ldrb	w1, [x19, 755]
	str	w0, [x19, 44]
	cmp	w1, w2, uxtb
	strb	w3, [x19, 706]
	csel	w0, w1, w2, cs
	strb	w0, [x19, 707]
	strb	w0, [x19]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L556:
	ldr	w1, [x19, 800]
	strb	wzr, [x19, 705]
	tst	w1, 16776960
	beq	.L558
	ldr	w1, [x19, 752]
	mov	w3, 1
	tst	w1, 16776960
	bne	.L559
	b	.L558
	.size	MVC_CombineFldsToFrm, .-MVC_CombineFldsToFrm
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetAPC
	.type	MVC_GetAPC, %function
MVC_GetAPC:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x21, x1
	mov	x0, x30
	mov	w19, w2
	bl	_mcount
	cbz	x21, .L592
	cmp	w19, 1
	beq	.L572
	cmp	w19, 2
	beq	.L573
	ldr	w23, [x21, 776]
	ldr	w24, [x21, 824]
.L574:
	add	x20, x22, 11124736
	ldr	w2, [x20, 1024]
	cbz	w2, .L583
	ldrb	w0, [x20, 816]
	cbz	w0, .L593
	add	x0, x20, 817
	mov	w19, 0
	b	.L577
	.p2align 3
.L581:
	ldrb	w1, [x0], 1
	cbz	w1, .L575
.L577:
	add	w19, w19, 1
	cmp	w19, w2
	bne	.L581
.L583:
	mov	w0, -1
.L587:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L573:
	ldr	w23, [x21, 824]
	mov	w24, w23
	b	.L574
.L593:
	mov	w19, 0
	.p2align 2
.L575:
	ldrsb	w1, [x21, 6]
	ldr	w0, [x22, 120]
	bl	FSP_GetLogicFs
	cbz	x0, .L578
	ldr	x1, [x0, 32]
	cbz	x1, .L578
	uxtw	x1, w19
	mov	w2, 1
	add	x3, x22, x1
	mov	w4, 16
	add	x3, x3, 11124736
	add	x1, x22, x1, lsl 2
	add	x1, x1, 11124736
	strb	w2, [x3, 816]
	mov	w3, w19
	ldr	x0, [x0, 32]
	ldr	w0, [x0, 4]
	str	w0, [x1, 832]
	mov	w0, 13
	str	w23, [x1, 896]
	str	w24, [x1, 960]
	ldr	x1, .LC41
	ldr	w2, [x20, 1028]
	cmp	w2, 15
	csinc	w2, w4, w2, hi
	str	w2, [x20, 1028]
	ldr	w2, [x21, 220]
	bl	dprint_vfmw
	str	w19, [x21, 52]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L572:
	ldr	w23, [x21, 776]
	mov	w24, w23
	b	.L574
.L578:
	ldrsb	w2, [x21, 6]
	mov	x4, x0
	ldrb	w3, [x21, 3]
	mov	x5, 0
	ldr	x1, .LC43
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L587
.L592:
	ldr	x2, .LC37
	mov	w3, 2054
	ldr	x1, .LC39
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L587
	.size	MVC_GetAPC, .-MVC_GetAPC
	.align	3
.LC37:
	.xword	.LC36
	.align	3
.LC39:
	.xword	.LC38
	.align	3
.LC41:
	.xword	.LC40
	.align	3
.LC43:
	.xword	.LC42
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_SlidingWinMark
	.type	MVC_SlidingWinMark, %function
MVC_SlidingWinMark:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 11124736
	ldr	x0, [x19, 248]
	ldr	w2, [x1, 804]
	ldr	w0, [x0, 3944]
	ldr	w1, [x1, 800]
	sub	w0, w0, w2
	cmp	w1, w0
	bne	.L594
	mov	x0, x19
	bl	MVC_SlidingWinMark.part.3
.L594:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_SlidingWinMark, .-MVC_SlidingWinMark
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DumpDPB
	.type	MVC_DumpDPB, %function
MVC_DumpDPB:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC44
	ldr	w0, [x0]
	tbz	x0, 14, .L596
	add	x22, x21, 11124736
	ldr	w0, [x22, 796]
	cbz	w0, .L602
	ldr	x20, .LC48
	mov	w19, 0
	.p2align 2
.L601:
	uxtw	x3, w19
	mov	w2, w19
	add	x3, x3, 1388544
	mov	x1, x20
	mov	w0, 14
	add	w19, w19, 1
	add	x3, x21, x3, lsl 3
	ldr	x3, [x3, 16792]
	ldrb	w5, [x3, 3]
	ldr	w4, [x3, 32]
	ldr	w3, [x3, 20]
	bl	dprint_vfmw
	ldr	w0, [x22, 796]
	cmp	w0, w19
	bhi	.L601
.L602:
	ldr	x25, .LC46
	mov	w0, 14
	mov	x1, x25
	bl	dprint_vfmw
	ldr	w0, [x22, 800]
	cbz	w0, .L600
	ldr	x24, .LC50
	mov	w19, 0
	ldr	x23, .LC52
	.p2align 2
.L603:
	add	x20, x21, x19, uxtw 3
	mov	w2, w19
	add	x20, x20, 11124736
	mov	x1, x24
	mov	w0, 14
	ldr	x3, [x20, 536]
	ldrb	w5, [x3, 3]
	ldr	w4, [x3, 32]
	ldr	w3, [x3, 20]
	bl	dprint_vfmw
	ldr	x3, [x20, 536]
	mov	w2, w19
	mov	x1, x23
	mov	w0, 14
	add	w19, w19, 1
	ldr	w3, [x3, 728]
	bl	dprint_vfmw
	ldr	w0, [x22, 800]
	cmp	w0, w19
	bhi	.L603
.L600:
	mov	x1, x25
	mov	w0, 14
	bl	dprint_vfmw
.L596:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	MVC_DumpDPB, .-MVC_DumpDPB
	.align	3
.LC44:
	.xword	g_PrintEnable
	.align	3
.LC46:
	.xword	.LC45
	.align	3
.LC48:
	.xword	.LC47
	.align	3
.LC50:
	.xword	.LC49
	.align	3
.LC52:
	.xword	.LC51
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_UpdateCurrFrameInfo
	.type	MVC_UpdateCurrFrameInfo, %function
MVC_UpdateCurrFrameInfo:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 11157504
	mov	w2, 3
	ldr	x19, [x1, 2960]
	ldrb	w3, [x1, 2314]
	strb	w3, [x19, 1]
	ldrb	w3, [x1, 2316]
	cbnz	w3, .L610
	ldrb	w2, [x1, 2317]
	mov	w0, 3
	cmp	w2, wzr
	csel	w2, w2, w0, eq
.L610:
	add	x3, x1, 2312
	strb	w2, [x19, 3]
	mov	w2, 3
	ldr	w0, [x3, 664]
	str	w0, [x19, 20]
	ldr	w0, [x3, 708]
	str	w0, [x19, 44]
	ldrb	w0, [x3, 12]
	strb	w0, [x19]
	ldr	w0, [x3, 676]
	str	w0, [x19, 32]
	ldr	w0, [x3, 732]
	str	w0, [x19, 48]
	ldr	w0, [x3, 668]
	str	w0, [x19, 28]
	ldrb	w0, [x3, 9]
	str	w0, [x19, 40]
	ldrb	w0, [x3, 7]
	cmp	w0, 1
	csel	w0, w2, wzr, eq
	strb	w0, [x19, 4]
	ldrb	w4, [x3, 3]
	cmp	w4, 1
	beq	.L613
	cbz	w4, .L614
	cmp	w4, 2
	bne	.L609
	str	x19, [x19, 808]
	mov	w5, 1
	strb	w5, [x19, 800]
	ldrb	w5, [x3, 4]
	strb	w5, [x19, 801]
	ldrb	w5, [x3, 5]
	strb	w5, [x19, 802]
	ldr	w5, [x3, 684]
	str	w5, [x19, 824]
	ldrb	w6, [x3, 12]
	strb	w6, [x19, 803]
	ldr	w5, [x3, 708]
	str	w5, [x19, 832]
	str	wzr, [x19, 40]
	ldrb	w7, [x3, 1]
	cbz	w7, .L636
	ldr	w4, [x19, 784]
	orr	w0, w0, 2
	strb	w2, [x19, 2]
	mov	w2, 0
	add	w5, w5, w4
	str	w5, [x19, 44]
	str	w5, [x19, 736]
	ldrb	w3, [x3, 7]
	cmp	w3, 1
	csel	w0, w0, w2, eq
	strb	w0, [x19, 4]
	ldr	x0, [x1, 2912]
	cmn	x0, #1
	beq	.L622
	ldr	x2, [x19, 656]
	cmn	x2, #1
	beq	.L637
.L622:
	ldrb	w2, [x19, 755]
.L640:
	cmp	w2, w6
	mov	x0, x19
	csel	w6, w2, w6, cs
	strb	w6, [x19]
	ldr	w1, [x1, 2988]
	str	w1, [x19, 32]
	bl	MVC_CombineFldsToFrm
.L609:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L614:
	strb	w2, [x19, 2]
	add	x1, x1, 2328
	strb	wzr, [x19, 704]
	mov	x2, 632
	str	x19, [x19, 712]
	add	x0, x19, 72
	ldrb	w23, [x3, 4]
	strb	w23, [x19, 705]
	ldrb	w22, [x3, 5]
	strb	w22, [x19, 706]
	ldr	w4, [x3, 680]
	str	w4, [x19, 728]
	ldrb	w20, [x3, 12]
	strb	w20, [x19, 707]
	ldr	w21, [x3, 708]
	str	w21, [x19, 736]
	ldr	w4, [x3, 684]
	str	w4, [x19, 776]
	ldr	w3, [x3, 688]
	str	w3, [x19, 824]
	bl	memcpy
	strb	w23, [x19, 753]
	strb	w22, [x19, 754]
	mov	w1, 1
	strb	w20, [x19, 755]
	mov	w0, 2
	strb	w1, [x19, 752]
	strb	w23, [x19, 801]
	strb	w22, [x19, 802]
	strb	w0, [x19, 800]
	strb	w20, [x19, 803]
	str	x19, [x19, 760]
	str	w21, [x19, 784]
	str	x19, [x19, 808]
	str	w21, [x19, 832]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L613:
	strb	w4, [x19, 752]
	str	x19, [x19, 760]
	ldrb	w5, [x3, 4]
	strb	w5, [x19, 753]
	ldrb	w5, [x3, 5]
	strb	w5, [x19, 754]
	ldr	w5, [x3, 684]
	str	w5, [x19, 776]
	ldrb	w6, [x3, 12]
	strb	w6, [x19, 755]
	ldr	w5, [x3, 708]
	str	w5, [x19, 784]
	str	wzr, [x19, 40]
	ldrb	w7, [x3, 1]
	cbz	w7, .L638
	ldr	w4, [x19, 832]
	orr	w0, w0, 1
	strb	w2, [x19, 2]
	mov	w2, 0
	add	w5, w5, w4
	str	w5, [x19, 44]
	str	w5, [x19, 736]
	ldrb	w3, [x3, 7]
	cmp	w3, 1
	csel	w0, w0, w2, eq
	strb	w0, [x19, 4]
	ldr	x0, [x1, 2912]
	cmn	x0, #1
	beq	.L618
	ldr	x2, [x19, 656]
	cmn	x2, #1
	beq	.L639
.L618:
	ldrb	w2, [x19, 803]
	mov	x0, x19
	cmp	w2, w6
	csel	w6, w2, w6, cs
	strb	w6, [x19]
	ldr	w1, [x1, 2988]
	str	w1, [x19, 32]
	bl	MVC_CombineFldsToFrm
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L636:
	strb	w4, [x19, 2]
	mov	x2, 632
	str	w5, [x19, 44]
	add	x1, x1, 2328
	str	w5, [x19, 736]
	add	x0, x19, 72
	ldrb	w3, [x3, 7]
	cmp	w3, 1
	csel	w7, wzr, w4, ne
	strb	w7, [x19, 4]
	bl	memcpy
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L638:
	strb	w4, [x19, 2]
	mov	x2, 632
	str	w5, [x19, 44]
	add	x1, x1, 2328
	str	w5, [x19, 736]
	add	x0, x19, 72
	ldrb	w3, [x3, 7]
	cmp	w3, 1
	cset	w3, eq
	strb	w3, [x19, 4]
	bl	memcpy
	b	.L609
	.p2align 3
.L639:
	str	x0, [x19, 656]
	b	.L618
	.p2align 3
.L637:
	str	x0, [x19, 656]
	ldrb	w2, [x19, 755]
	b	.L640
	.size	MVC_UpdateCurrFrameInfo, .-MVC_UpdateCurrFrameInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_SimpleSlideDPB
	.type	MVC_SimpleSlideDPB, %function
MVC_SimpleSlideDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	add	x20, x21, 11157504
	bl	_mcount
	add	x0, x21, 11124736
	ldr	w19, [x0, 792]
	ldr	w1, [x0, 796]
	cmp	w1, w19
	bcc	.L642
	cbz	w19, .L647
	add	x0, x0, 408
	mov	w5, 0
	mov	w4, 2147483647
	mov	w1, 0
	.p2align 2
.L645:
	ldr	x2, [x0]
	add	x0, x0, 8
	cbz	x2, .L644
	ldr	w3, [x2, 64]
	cmp	w3, w4
	bcs	.L644
	ldr	w6, [x2, 56]
	ldr	w2, [x20, 3048]
	cmp	w6, w2
	csel	w4, w4, w3, ne
	csel	w5, w5, w1, ne
.L644:
	add	w1, w1, 1
	cmp	w19, w1
	bne	.L645
	mov	w19, w5
.L643:
	sxtw	x1, w5
	mov	x0, x21
	add	x1, x1, 1388544
	add	x1, x21, x1, lsl 3
	ldr	x1, [x1, 16792]
	bl	MVC_UnMarkFrameStoreRef
	mov	w1, w19
	mov	x0, x21
	bl	MVC_RemoveFrameStoreOutDPB
.L642:
	ldr	w0, [x20, 2984]
	strb	wzr, [x20, 2316]
	cbz	w0, .L641
	mov	w0, 1
	strb	w0, [x20, 2317]
.L641:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L647:
	mov	w5, 0
	b	.L643
	.size	MVC_SimpleSlideDPB, .-MVC_SimpleSlideDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ReleaseNAL
	.type	MVC_ReleaseNAL, %function
MVC_ReleaseNAL:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w21, w0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L665
	ldr	x23, .LC58
	add	x19, x20, 8
	strb	wzr, [x20, 1]
	add	x22, x20, 72
	strb	wzr, [x20, 3]
.L660:
	ldr	x1, [x19]
	mov	w0, w21
	cbz	x1, .L659
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
.L659:
	add	x19, x19, 32
	cmp	x19, x22
	bne	.L660
	strb	wzr, [x20]
	str	wzr, [x20, 76]
.L656:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L665:
	ldr	x2, .LC55
	mov	w3, 3967
	ldr	x1, .LC56
	mov	w0, 0
	bl	dprint_vfmw
	b	.L656
	.size	MVC_ReleaseNAL, .-MVC_ReleaseNAL
	.align	3
.LC55:
	.xword	.LC36
	.align	3
.LC56:
	.xword	.LC38
	.align	3
.LC58:
	.xword	.LC57
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ClearCurrNal
	.type	MVC_ClearCurrNal, %function
MVC_ClearCurrNal:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, [x19, 240]
	cbz	x1, .L667
	ldr	w0, [x19, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19, 240]
.L667:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_ClearCurrNal, .-MVC_ClearCurrNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ClearCurrSlice
	.type	MVC_ClearCurrSlice, %function
MVC_ClearCurrSlice:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC60
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 240]
	cbz	x1, .L672
	ldr	w0, [x19, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19, 240]
.L672:
	ldr	w1, [x19, 80]
	mov	w0, 0
	add	w1, w1, 1
	str	w1, [x19, 80]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_ClearCurrSlice, .-MVC_ClearCurrSlice
	.align	3
.LC60:
	.xword	.LC59
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ClearAllNal
	.type	MVC_ClearAllNal, %function
MVC_ClearAllNal:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	add	x20, x21, 12288
	add	x19, x21, 1520
	bl	_mcount
	add	x20, x20, 2384
	b	.L678
	.p2align 3
.L677:
	add	x19, x19, 96
	cmp	x19, x20
	beq	.L680
.L678:
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	bne	.L677
	ldr	w0, [x21, 120]
	mov	x1, x19
	add	x19, x19, 96
	bl	MVC_ReleaseNAL
	cmp	x19, x20
	bne	.L678
.L680:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	MVC_ClearAllNal, .-MVC_ClearAllNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ClearAllSlice
	.type	MVC_ClearAllSlice, %function
MVC_ClearAllSlice:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	add	x19, x21, 11157504
	add	x20, x21, 11161600
	add	x19, x19, 3832
	add	x20, x20, 824
	bl	_mcount
	.p2align 2
.L683:
	ldr	x0, [x19]
	mov	x1, x0
	cbz	x0, .L682
	ldr	w0, [x21, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19]
.L682:
	add	x19, x19, 8
	cmp	x19, x20
	bne	.L683
	str	wzr, [x21, 64]
	mov	w0, 0
	str	wzr, [x21, 104]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	MVC_ClearAllSlice, .-MVC_ClearAllSlice
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ClearCurrPic
	.type	MVC_ClearCurrPic, %function
MVC_ClearCurrPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	MVC_ClearAllSlice
	add	x0, x19, 11120640
	mov	w4, 32
	ldr	w8, [x19, 40]
	mov	w7, 23352
	movk	w7, 0x1, lsl 16
	mov	w6, 2
	strb	w4, [x0, 402]
	add	x4, x0, 256
	strb	wzr, [x0, 400]
	mov	w5, 7
	strb	w6, [x0, 401]
	mov	w3, 3
	strb	w5, [x0, 403]
	mov	w2, -1
	str	w8, [x0, 412]
	mov	w1, 262144
	str	w7, [x0, 416]
	stp	w3, w2, [x4, 168]
	stp	wzr, wzr, [x4, 176]
	str	w1, [x0, 440]
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_ClearCurrPic, .-MVC_ClearCurrPic
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ArrangeVahbMem
	.type	MVC_ArrangeVahbMem, %function
MVC_ArrangeVahbMem:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w2
	mov	w20, w1
	mov	w22, w4
	bl	_mcount
	mov	w0, 8160
	sub	w2, w21, #32
	sub	w1, w20, #32
	cmp	w2, w0
	ccmp	w1, w0, 2, ls
	bhi	.L690
	ldr	x3, .LC61
	mov	x2, 20
	mov	w1, 0
	add	x0, x29, 56
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x0, [x19, 224]
	stp	w20, w21, [x29, 60]
	stp	w20, w21, [x29, 68]
	ldr	w0, [x0, 28]
	cmp	w0, 24
	beq	.L703
	add	x0, x19, 11124736
	mov	w1, 5
	sxtb	w4, w22
	strb	w1, [x29, 58]
	ldr	w0, [x0, 792]
	add	w0, w0, 3
	strb	w0, [x29, 57]
.L698:
	ldr	w0, [x19, 120]
	add	x1, x29, 56
	strb	w4, [x29, 59]
	bl	FSP_ConfigInstance
	cbnz	w0, .L694
	ldr	x1, [x19, 224]
	add	x3, x29, 52
	ldr	w0, [x19, 120]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
	cmp	w0, 2
	mov	w1, w0
	beq	.L704
	mov	w0, 1
	cbnz	w1, .L696
.L699:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L703:
	mov	w1, 1
	mov	w0, 5
	strb	w1, [x29, 57]
	mov	w4, 1
	strb	w0, [x29, 58]
	b	.L698
	.p2align 3
.L704:
	add	x0, x19, 912
	bl	ResetVoQueue
.L696:
	ldr	x1, .LC65
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L699
	.p2align 3
.L690:
	ldr	x1, .LC63
	mov	w3, w21
	mov	w2, w20
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L694:
	ldr	x1, .LC67
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L699
	.size	MVC_ArrangeVahbMem, .-MVC_ArrangeVahbMem
	.align	3
.LC61:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC63:
	.xword	.LC62
	.align	3
.LC65:
	.xword	.LC64
	.align	3
.LC67:
	.xword	.LC66
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_RepairList
	.type	MVC_RepairList, %function
MVC_RepairList:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x6, x19, 11116544
	ldrb	w0, [x6, 2840]
	cmp	w0, 1
	beq	.L723
	cbz	w0, .L708
	cmp	w0, 2
	mov	w0, 0
	bne	.L719
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L719:
	mov	x0, x19
	bl	MVC_ClearCurrSlice
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
.L723:
	mov	w10, 2
.L707:
	add	x6, x6, 2888
	add	x5, x19, 288
	mov	x8, 0
	mov	w7, 0
	mov	w12, 1
	add	x11, x19, 11157504
	.p2align 2
.L720:
	ldr	w0, [x6]
	cbz	w0, .L710
	ldr	x1, [x5]
	cbnz	x1, .L734
	sub	w3, w0, #1
	add	x9, x8, 37
	add	x0, x5, 8
	add	x4, x9, x3, uxtw
	add	x4, x19, x4, lsl 3
	b	.L713
	.p2align 3
.L714:
	ldr	x2, [x0], 8
	cbnz	x2, .L721
.L713:
	cmp	x0, x4
	bne	.L714
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L719
	ldr	x2, [x11, 2960]
	add	x2, x2, 704
.L721:
	add	x3, x9, x3, uxtw
	mov	x0, x5
	add	x3, x19, x3, lsl 3
	cbz	x1, .L735
	.p2align 2
.L716:
	add	x0, x0, 8
	cmp	x3, x0
	beq	.L717
.L736:
	ldr	x1, [x0]
	cbnz	x1, .L716
.L735:
	str	x2, [x0]
	add	x0, x0, 8
	cmp	x3, x0
	bne	.L736
	.p2align 2
.L717:
	add	w7, w7, 1
	add	x6, x6, 4
	cmp	w7, w10
	add	x5, x5, 264
	add	x8, x8, 33
	bcc	.L720
.L737:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L710:
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L719
	str	w12, [x6]
	add	w7, w7, 1
	cmp	w7, w10
	add	x6, x6, 4
	ldr	x0, [x11, 2960]
	add	x8, x8, 33
	add	x0, x0, 704
	str	x0, [x5]
	add	x5, x5, 264
	bcc	.L720
	b	.L737
.L734:
	sub	w3, w0, #1
	mov	x2, x1
	add	x9, x8, 37
	b	.L721
.L708:
	mov	w10, 1
	b	.L707
	.size	MVC_RepairList, .-MVC_RepairList
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetShortTermPicPoint
	.type	MVC_GetShortTermPicPoint, %function
MVC_GetShortTermPicPoint:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	add	x0, x20, 11116544
	mov	w5, 0
	ldrb	w1, [x0, 2841]
	cbz	w1, .L739
	ldrb	w0, [x0, 2842]
	mov	w5, 2
	cmp	w0, wzr
	csinc	w5, w5, wzr, ne
.L739:
	add	x0, x20, 11124736
	ldr	w2, [x0, 800]
	cbz	w2, .L747
	sub	w2, w2, #1
	add	x0, x0, 536
	add	x2, x2, 1388544
	add	x2, x2, 2116
	add	x4, x20, x2, lsl 3
	b	.L744
	.p2align 3
.L757:
	cmp	w3, 3
	beq	.L756
.L742:
	add	x0, x0, 8
	cmp	x0, x4
	beq	.L747
.L744:
	ldr	x2, [x0]
	ldrb	w3, [x2, 3]
	cbz	w5, .L757
	tbz	x3, 0, .L743
	ldr	w6, [x2, 752]
	and	w6, w6, 16776960
	cmp	w6, 65536
	beq	.L758
.L743:
	tbz	x3, 1, .L742
	ldr	w3, [x2, 800]
	and	w3, w3, 16776960
	cmp	w3, 65536
	bne	.L742
	ldr	w1, [x2, 820]
	cmp	w19, w1
	bne	.L742
	add	x0, x2, 800
	b	.L740
	.p2align 3
.L758:
	ldr	w1, [x2, 772]
	cmp	w1, w19
	bne	.L743
	add	x0, x2, 752
	b	.L740
	.p2align 3
.L756:
	ldr	w3, [x2, 704]
	and	w3, w3, 16776960
	cmp	w3, 65536
	bne	.L742
	ldr	w1, [x2, 724]
	cmp	w19, w1
	bne	.L742
	add	x0, x2, 704
	b	.L740
	.p2align 3
.L747:
	mov	x0, 0
.L740:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_GetShortTermPicPoint, .-MVC_GetShortTermPicPoint
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetLongTermPicPoint
	.type	MVC_GetLongTermPicPoint, %function
MVC_GetLongTermPicPoint:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	add	x0, x20, 11116544
	mov	w5, 0
	ldrb	w1, [x0, 2841]
	cbz	w1, .L760
	ldrb	w0, [x0, 2842]
	mov	w5, 2
	cmp	w0, wzr
	csinc	w5, w5, wzr, ne
.L760:
	add	x0, x20, 11124736
	ldr	w2, [x0, 804]
	cbz	w2, .L768
	sub	w2, w2, #1
	add	x0, x0, 664
	add	x2, x2, 1388544
	add	x2, x2, 2132
	add	x4, x20, x2, lsl 3
	b	.L765
	.p2align 3
.L778:
	cmp	w3, 3
	beq	.L777
.L763:
	add	x0, x0, 8
	cmp	x0, x4
	beq	.L768
.L765:
	ldr	x2, [x0]
	ldrb	w3, [x2, 3]
	cbz	w5, .L778
	tbz	x3, 0, .L764
	ldr	w6, [x2, 752]
	and	w6, w6, 16776960
	cmp	w6, 256
	beq	.L779
.L764:
	tbz	x3, 1, .L763
	ldr	w3, [x2, 800]
	and	w3, w3, 16776960
	cmp	w3, 256
	bne	.L763
	ldr	w1, [x2, 816]
	cmp	w19, w1
	bne	.L763
	add	x0, x2, 800
	b	.L761
	.p2align 3
.L779:
	ldr	w1, [x2, 768]
	cmp	w1, w19
	bne	.L764
	add	x0, x2, 752
	b	.L761
	.p2align 3
.L777:
	ldr	w3, [x2, 704]
	and	w3, w3, 16776960
	cmp	w3, 256
	bne	.L763
	ldr	w1, [x2, 720]
	cmp	w19, w1
	bne	.L763
	add	x0, x2, 704
	b	.L761
	.p2align 3
.L768:
	mov	x0, 0
.L761:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_GetLongTermPicPoint, .-MVC_GetLongTermPicPoint
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ReorderSTList
	.type	MVC_ReorderSTList, %function
MVC_ReorderSTList:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	mov	w21, w2
	mov	w23, w3
	mov	x22, x4
	mov	w24, w5
	bl	_mcount
	uxtw	x6, w20
	mov	x0, x19
	lsl	x2, x6, 8
	mov	w1, w23
	add	x6, x2, x6, lsl 3
	add	x6, x6, 288
	add	x19, x19, x6
	bl	MVC_GetShortTermPicPoint
	ldr	w6, [x22]
	add	w2, w21, 1
	cmp	w2, w6
	ble	.L781
	mov	w1, w2
	.p2align 2
.L782:
	add	x6, x19, x1, sxtw 3
	ldr	x6, [x6, -8]
	str	x6, [x19, w1, sxtw 3]
	sub	w1, w1, #1
	ldr	w6, [x22]
	cmp	w6, w1
	blt	.L782
.L781:
	add	w1, w6, 1
	str	w1, [x22]
	str	x0, [x19, w6, sxtw 3]
	ldr	w0, [x22]
	cmp	w2, w0
	mov	w4, w0
	bge	.L790
	b	.L780
	.p2align 3
.L785:
	str	x1, [x19, w4, sxtw 3]
	add	w4, w4, 1
.L784:
	cmp	w2, w0
	blt	.L780
.L790:
	ldr	x1, [x19, w0, sxtw 3]
	add	w0, w0, 1
	cbz	x1, .L784
	ldrb	w6, [x1, 1]
	cbnz	w6, .L785
	ldr	w6, [x1, 20]
	cmp	w23, w6
	bne	.L785
	ldr	x3, [x1, 8]
	ldr	w3, [x3, 56]
	cmp	w3, w24
	bne	.L785
	cmp	w2, w0
	bge	.L790
.L780:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	MVC_ReorderSTList, .-MVC_ReorderSTList
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ReorderLTList
	.type	MVC_ReorderLTList, %function
MVC_ReorderLTList:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	mov	w21, w2
	mov	w23, w3
	mov	x22, x4
	mov	w24, w5
	bl	_mcount
	uxtw	x6, w20
	mov	x0, x19
	lsl	x2, x6, 8
	mov	w1, w23
	add	x6, x2, x6, lsl 3
	add	x6, x6, 288
	add	x19, x19, x6
	bl	MVC_GetLongTermPicPoint
	ldr	w6, [x22]
	add	w2, w21, 1
	cmp	w2, w6
	ble	.L796
	mov	w1, w2
	.p2align 2
.L797:
	add	x6, x19, x1, sxtw 3
	ldr	x6, [x6, -8]
	str	x6, [x19, w1, sxtw 3]
	sub	w1, w1, #1
	ldr	w6, [x22]
	cmp	w6, w1
	blt	.L797
.L796:
	add	w1, w6, 1
	str	w1, [x22]
	str	x0, [x19, w6, sxtw 3]
	ldr	w0, [x22]
	cmp	w2, w0
	mov	w4, w0
	bge	.L807
	b	.L795
	.p2align 3
.L800:
	str	x1, [x19, w4, sxtw 3]
	add	w4, w4, 1
.L799:
	cmp	w2, w0
	blt	.L795
.L807:
	ldr	x1, [x19, w0, sxtw 3]
	add	w0, w0, 1
	cbz	x1, .L799
	ldrb	w6, [x1, 1]
	cbz	w6, .L800
	ldr	w6, [x1, 16]
	cmp	w23, w6
	bne	.L800
	ldr	x3, [x1, 8]
	ldr	w3, [x3, 56]
	cmp	w3, w24
	bne	.L800
	cmp	w2, w0
	bge	.L807
.L795:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	MVC_ReorderLTList, .-MVC_ReorderLTList
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetMaxViewIdx
	.type	MVC_GetMaxViewIdx, %function
MVC_GetMaxViewIdx:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w19, w1
	mov	w22, w2
	mov	w20, w3
	bl	_mcount
	add	x0, x21, 10768384
	add	x1, x0, 4068
	ldr	w5, [x0, 4064]
	adds	w5, w5, 1
	beq	.L821
	ldr	w0, [x0, 4068]
	cmp	w19, w0
	beq	.L821
	mov	w6, w5
	mov	w0, 0
	b	.L815
	.p2align 3
.L817:
	ldr	w4, [x1, w0, sxtw 2]
	cmp	w19, w4
	beq	.L823
.L815:
	add	w0, w0, 1
	cmp	w0, w5
	bne	.L817
.L818:
	mov	w0, 0
	tbnz	w6, #31, .L816
.L814:
	sbfiz	x0, x20, 1, 32
	add	x0, x0, x6, sxtw
	cbnz	w22, .L824
	add	x0, x21, x0, lsl 2
	add	x0, x0, 10772480
	ldr	w0, [x0, 12]
.L816:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L824:
	add	x0, x0, 2691072
	ldp	x19, x20, [sp, 16]
	add	x0, x21, x0, lsl 2
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ldr	w0, [x0, 8172]
	ret
	.p2align 3
.L823:
	mov	w6, w0
	b	.L818
.L821:
	mov	w6, 0
	b	.L814
	.size	MVC_GetMaxViewIdx, .-MVC_GetMaxViewIdx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_get_inter_view_pic
	.type	mvc_get_inter_view_pic, %function
mvc_get_inter_view_pic:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w22, w3
	mov	w19, w1
	mov	w21, w2
	bl	_mcount
	uxtw	x1, w22
	lsl	x0, x1, 3
	add	x2, x1, 2777088
	sub	x0, x0, x1
	lsl	x0, x0, 2
	add	x2, x20, x2, lsl 2
	sub	x0, x0, x1
	lsl	x0, x0, 1
	sub	x0, x0, x1
	ldr	w1, [x2, 12680]
	lsl	x0, x0, 5
	add	x0, x0, 11108352
	add	x0, x0, 272
	add	x0, x20, x0
	cbz	w1, .L831
	sub	w4, w1, #1
	add	x5, x20, 11157504
	add	x4, x4, 1
	lsl	x3, x4, 3
	sub	x3, x3, x4
	lsl	x3, x3, 2
	sub	x3, x3, x4
	lsl	x3, x3, 1
	sub	x4, x3, x4
	add	x4, x0, x4, lsl 4
	b	.L830
	.p2align 3
.L827:
	add	x0, x0, 848
	cmp	x0, x4
	beq	.L831
.L830:
	ldr	w3, [x0, 56]
	cmp	w3, w19
	bne	.L827
	ldrb	w1, [x5, 2315]
	cmp	w1, 1
	cbnz	w1, .L828
	ldr	w1, [x0, 732]
	cmp	w21, w1
	bne	.L827
	add	x0, x0, 704
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L828:
	bne	.L829
	ldr	w1, [x0, 780]
	cmp	w1, w21
	bne	.L827
	add	x0, x0, 752
	b	.L826
	.p2align 3
.L829:
	cmp	w1, 2
	bne	.L827
	ldr	w1, [x0, 828]
	cmp	w21, w1
	bne	.L827
	add	x0, x0, 800
	b	.L826
	.p2align 3
.L831:
	mov	x0, 0
.L826:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	mvc_get_inter_view_pic, .-mvc_get_inter_view_pic
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_reorder_interview
	.type	mvc_reorder_interview, %function
mvc_reorder_interview:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	w24, w5
	mov	w22, w3
	mov	w23, w4
	mov	w20, w1
	mov	x21, x2
	bl	_mcount
	uxtw	x0, w24
	mov	w3, w24
	lsl	x5, x0, 8
	mov	w2, w23
	add	x5, x5, x0, lsl 3
	mov	w1, w22
	mov	x0, x19
	add	x5, x5, 288
	add	x19, x19, x5
	bl	mvc_get_inter_view_pic
	cbz	x0, .L833
	ldr	w3, [x21]
	add	w1, w20, 1
	cmp	w1, w3
	bls	.L835
	mov	w2, w1
	uxtw	x5, w1
	.p2align 2
.L836:
	sub	w2, w2, #1
	lsl	x3, x5, 3
	uxtw	x5, w2
	ldr	x6, [x19, w2, uxtw 3]
	str	x6, [x19, x3]
	ldr	w3, [x21]
	cmp	w3, w2
	bcc	.L836
.L835:
	add	w2, w3, 1
	str	w2, [x21]
	str	x0, [x19, w3, uxtw 3]
	ldr	w0, [x21]
	cmp	w1, w0
	bcc	.L833
	mov	w3, w0
	b	.L840
	.p2align 3
.L838:
	str	x2, [x19, w3, uxtw 3]
	cmp	w1, w0
	add	w3, w3, 1
	bcc	.L833
.L840:
	ldr	x2, [x19, w0, uxtw 3]
	add	w0, w0, 1
	cbz	x2, .L838
	ldr	x5, [x2, 8]
	ldr	w5, [x5, 56]
	cmp	w22, w5
	bne	.L838
	ldr	w5, [x2, 28]
	cmp	w23, w5
	bne	.L838
	cmp	w1, w0
	bcs	.L840
.L833:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	mvc_reorder_interview, .-mvc_reorder_interview
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ReorderRefPiclist
	.type	MVC_ReorderRefPiclist, %function
MVC_ReorderRefPiclist:
	stp	x29, x30, [sp, -192]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x27, x0
	mov	x0, x30
	add	x20, x27, 11116544
	mov	w19, w1
	mov	w21, w2
	bl	_mcount
	str	wzr, [x29, 188]
	mov	w0, 0
	ldrb	w1, [x20, 2841]
	cbz	w1, .L848
	ldrb	w1, [x20, 2842]
	mov	w0, 2
	cmp	w1, wzr
	csinc	w0, w0, wzr, ne
.L848:
	cmp	w19, 1
	bls	.L904
.L847:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 192
	ret
	.p2align 3
.L904:
	cbz	w19, .L905
	add	x1, x20, 1924
	str	x1, [x29, 168]
	add	x1, x20, 2188
	str	x1, [x29, 120]
	add	x1, x20, 2448
	str	x1, [x29, 104]
	ldr	x1, [x27, 248]
	add	x28, x20, 2708
	ldr	w25, [x1, 2896]
	add	w1, w25, 4
	mov	w25, 1
	lsl	w1, w25, w1
	str	w1, [x29, 148]
	cbnz	w0, .L852
.L910:
	ldr	w0, [x20, 2868]
	str	w0, [x29, 144]
.L853:
	cmn	w21, #2
	beq	.L847
	ldr	x0, [x29, 168]
	ldr	w1, [x0]
	cmp	w1, 3
	beq	.L847
	add	w23, w21, 1
	mov	w2, 1
	lsl	x0, x23, 2
	str	x0, [x29, 160]
	stp	w2, wzr, [x29, 152]
	add	x0, x27, 10768384
	add	x2, x27, 11157504
	mov	x23, 0
	str	x2, [x29, 136]
	mov	w22, 0
	ubfiz	x2, x19, 1, 32
	mov	w26, 0
	ldr	w24, [x29, 144]
	add	x25, x0, 4068
	str	x0, [x29, 112]
	str	x2, [x29, 128]
	b	.L856
	.p2align 3
.L909:
	ldr	w3, [x0, 8188]
.L879:
	ldr	x0, [x29, 136]
	mov	w5, w19
	add	x2, x29, 188
	mov	w1, w21
	ldr	w4, [x0, 2988]
	mov	x0, x27
	bl	mvc_reorder_interview
.L861:
	ldr	x0, [x29, 160]
	cmp	x0, x23
	beq	.L847
	add	x23, x23, 4
	ldr	x0, [x29, 168]
	ldr	w1, [x0, x23]
	cmp	w1, 3
	beq	.L847
.L856:
	cmp	w1, 1
	bls	.L906
	cmp	w1, 2
	beq	.L907
	ldr	w0, [x29, 152]
	cbnz	w0, .L863
	ldrb	w5, [x20, 2849]
	mov	w6, w26
.L864:
	cmp	w1, 4
	ldr	w0, [x28, x23]
	beq	.L908
	add	w0, w0, 1
	add	w26, w0, w6
	cmp	w22, w26
	sub	w0, w26, w22
	csel	w26, w0, w26, le
.L877:
	ldr	w1, [x29, 156]
	ldr	x0, [x29, 128]
	add	x0, x0, x26, sxtw
	add	x0, x0, x1, sxtw
	add	x0, x0, 2691072
	add	x0, x27, x0, lsl 2
	cbnz	w5, .L909
	ldr	w3, [x0, 8220]
	b	.L879
	.p2align 3
.L905:
	add	x1, x20, 1792
	str	x1, [x29, 168]
	add	x1, x20, 2056
	str	x1, [x29, 120]
	add	x1, x20, 2320
	str	x1, [x29, 104]
	ldr	x1, [x27, 248]
	add	x28, x20, 2576
	ldr	w25, [x1, 2896]
	add	w1, w25, 4
	mov	w25, 1
	lsl	w1, w25, w1
	str	w1, [x29, 148]
	cbz	w0, .L910
.L852:
	ldr	w0, [x20, 2868]
	ldr	w1, [x29, 148]
	lsl	w0, w0, 1
	add	w0, w0, 1
	lsl	w1, w1, 1
	stp	w0, w1, [x29, 144]
	b	.L853
	.p2align 3
.L906:
	ldr	x0, [x29, 120]
	ldr	w0, [x0, x23]
	cbnz	w1, .L858
	mvn	w0, w0
	add	w24, w24, w0
	ldr	w0, [x29, 148]
	cmp	w24, wzr
	add	w0, w24, w0
	csel	w24, w0, w24, lt
.L859:
	ldr	w0, [x29, 144]
	add	x4, x29, 188
	mov	w2, w21
	mov	w1, w19
	cmp	w0, w24
	add	x0, x27, 11120640
	ldr	w5, [x0, 384]
	ldr	w0, [x29, 148]
	sub	w3, w24, w0
	mov	x0, x27
	csel	w3, w3, w24, lt
	bl	MVC_ReorderSTList
	b	.L861
	.p2align 3
.L908:
	mvn	w0, w0
	add	w26, w0, w6
	cmp	w26, wzr
	add	w0, w26, w22
	csel	w26, w0, w26, lt
	b	.L877
	.p2align 3
.L863:
	ldr	x4, [x29, 112]
	add	x0, x27, 11120640
	ldr	w2, [x4, 4064]
	ldr	w3, [x0, 384]
	adds	w2, w2, 1
	beq	.L866
	ldr	w0, [x4, 4068]
	cmp	w3, w0
	beq	.L866
	mov	w0, 0
	str	w2, [x29, 156]
	b	.L869
	.p2align 3
.L870:
	ldr	w4, [x25, w0, sxtw 2]
	cmp	w3, w4
	beq	.L911
.L869:
	add	w0, w0, 1
	cmp	w2, w0
	bne	.L870
.L901:
	ldrb	w5, [x20, 2849]
	mov	w6, w2
	mov	w0, 0
	b	.L873
	.p2align 3
.L874:
	ldr	w4, [x25, w0, sxtw 2]
	cmp	w3, w4
	beq	.L903
.L873:
	add	w0, w0, 1
	cmp	w0, w2
	bne	.L874
	tbnz	w6, #31, .L887
.L881:
	sbfiz	x0, x19, 1, 32
	add	x0, x0, x6, sxtw
	cbz	w5, .L875
	add	x0, x0, 2691072
	mov	w6, -1
	str	wzr, [x29, 152]
	add	x0, x27, x0, lsl 2
	ldr	w22, [x0, 8172]
	b	.L864
	.p2align 3
.L858:
	add	w0, w0, 1
	add	w24, w24, w0
	ldr	w0, [x29, 148]
	cmp	w0, w24
	sub	w0, w24, w0
	csel	w24, w0, w24, le
	b	.L859
	.p2align 3
.L907:
	add	x0, x27, 11120640
	add	x4, x29, 188
	mov	w2, w21
	mov	w1, w19
	ldr	w5, [x0, 384]
	ldr	x0, [x29, 104]
	ldr	w3, [x0, x23]
	mov	x0, x27
	bl	MVC_ReorderLTList
	b	.L861
	.p2align 3
.L903:
	mov	w6, w0
	tbz	w6, #31, .L881
.L887:
	mov	w6, -1
	mov	w22, 0
	str	wzr, [x29, 152]
	b	.L864
	.p2align 3
.L911:
	str	w0, [x29, 156]
	b	.L901
	.p2align 3
.L875:
	add	x0, x27, x0, lsl 2
	mov	w6, -1
	add	x0, x0, 10772480
	str	wzr, [x29, 152]
	ldr	w22, [x0, 12]
	b	.L864
.L866:
	ldrb	w5, [x20, 2849]
	mov	w6, 0
	str	wzr, [x29, 156]
	b	.L881
	.size	MVC_ReorderRefPiclist, .-MVC_ReorderRefPiclist
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ReorderListX
	.type	MVC_ReorderListX, %function
MVC_ReorderListX:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 11116544
	bl	_mcount
	ldrb	w1, [x19, 2840]
	cmp	w1, 2
	beq	.L912
	ldrb	w0, [x19, 1788]
	cbnz	w0, .L924
.L915:
	ldr	w0, [x19, 2900]
	cmp	w1, 1
	add	w0, w0, 1
	str	w0, [x19, 2888]
	bne	.L912
	ldrb	w0, [x19, 1789]
	cbnz	w0, .L925
.L917:
	ldr	w0, [x19, 2904]
	add	w0, w0, 1
	str	w0, [x19, 2892]
.L912:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L924:
	ldr	w2, [x19, 2900]
	mov	w1, 0
	mov	x0, x20
	bl	MVC_ReorderRefPiclist
	ldrb	w1, [x19, 2840]
	b	.L915
	.p2align 3
.L925:
	ldr	w2, [x19, 2904]
	mov	x0, x20
	bl	MVC_ReorderRefPiclist
	b	.L917
	.size	MVC_ReorderListX, .-MVC_ReorderListX
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GenPiclistfromFrmlist
	.type	MVC_GenPiclistfromFrmlist, %function
MVC_GenPiclistfromFrmlist:
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
	cbnz	w23, .L948
	cmp	w21, 1
	ldr	x23, .LC69
	beq	.L988
.L928:
	cmp	w21, 2
	bne	.L937
	mov	w21, 0
	mov	w20, 0
	.p2align 2
.L939:
	cmp	w20, w22
	ccmp	w21, w22, 0, cs
	bcs	.L937
.L989:
	cmp	w21, w22
	bcc	.L972
	b	.L944
	.p2align 3
.L940:
	add	w21, w21, 1
	cmp	w22, w21
	bls	.L944
.L972:
	ldr	x0, [x19, w21, uxtw 3]
	add	x26, x19, x21, uxtw 3
	ldrb	w1, [x0, 2]
	tbz	x1, 1, .L940
	add	x0, x0, 800
	blr	x23
	cbz	w0, .L940
	ldr	w1, [x24]
	add	w21, w21, 1
	ldr	x0, [x26]
	add	x0, x0, 800
	str	x0, [x25, w1, uxtw 3]
	ldr	w0, [x24]
	add	w0, w0, 1
	str	w0, [x24]
.L944:
	cmp	w20, w22
	bcc	.L971
	b	.L939
	.p2align 3
.L945:
	add	w20, w20, 1
	cmp	w22, w20
	bls	.L939
.L971:
	ldr	x0, [x19, w20, uxtw 3]
	add	x26, x19, x20, uxtw 3
	ldrb	w1, [x0, 2]
	tbz	x1, 0, .L945
	add	x0, x0, 752
	blr	x23
	cbz	w0, .L945
	ldr	w1, [x24]
	add	w20, w20, 1
	ldr	x0, [x26]
	cmp	w20, w22
	ccmp	w21, w22, 0, cs
	add	x0, x0, 752
	str	x0, [x25, w1, uxtw 3]
	ldr	w0, [x24]
	add	w0, w0, 1
	str	w0, [x24]
	bcc	.L989
.L937:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L948:
	cmp	w21, 1
	ldr	x23, .LC68
	bne	.L928
.L988:
	mov	w21, 0
	mov	w20, 0
	.p2align 2
.L929:
	cmp	w20, w22
	ccmp	w21, w22, 0, cs
	bcs	.L937
	cmp	w20, w22
	bcc	.L970
	b	.L987
	.p2align 3
.L930:
	add	w20, w20, 1
	cmp	w20, w22
	bcs	.L987
.L970:
	ldr	x0, [x19, w20, uxtw 3]
	add	x26, x19, x20, uxtw 3
	ldrb	w1, [x0, 2]
	tbz	x1, 0, .L930
	add	x0, x0, 752
	blr	x23
	cbz	w0, .L930
	ldr	w1, [x24]
	add	w20, w20, 1
	ldr	x0, [x26]
	add	x0, x0, 752
	str	x0, [x25, w1, uxtw 3]
	ldr	w0, [x24]
	add	w0, w0, 1
	str	w0, [x24]
	.p2align 2
.L987:
	cmp	w21, w22
	bcs	.L929
	ldr	x0, [x19, w21, uxtw 3]
	add	x26, x19, x21, uxtw 3
	ldrb	w1, [x0, 2]
	tbnz	x1, 1, .L990
.L935:
	add	w21, w21, 1
	b	.L987
	.p2align 3
.L990:
	add	x0, x0, 800
	blr	x23
	cbz	w0, .L935
	ldr	w1, [x24]
	add	w21, w21, 1
	ldr	x0, [x26]
	add	x0, x0, 800
	str	x0, [x25, w1, uxtw 3]
	ldr	w0, [x24]
	add	w0, w0, 1
	str	w0, [x24]
	b	.L929
	.size	MVC_GenPiclistfromFrmlist, .-MVC_GenPiclistfromFrmlist
	.align	3
.LC68:
	.xword	MVC_IsLTRefFlg
	.align	3
.LC69:
	.xword	MVC_IsSTRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetBaseViewId
	.type	MVC_GetBaseViewId, %function
MVC_GetBaseViewId:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 12288
	mov	x1, 0
	add	x0, x0, 2400
	.p2align 2
.L994:
	ldr	w2, [x0]
	add	x3, x0, 335872
	cbz	w2, .L992
	ldrb	w0, [x0, -4]
	cbnz	w0, .L1002
.L992:
	add	w1, w1, 1
	add	x0, x3, 308
	cmp	w1, 32
	bne	.L994
	mov	w0, -1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1002:
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 4
	sub	x1, x0, x1
	lsl	x0, x1, 2
	sub	x1, x0, x1
	lsl	x0, x1, 6
	add	x0, x1, x0
	add	x0, x19, x0, lsl 2
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ldr	w0, [x0, 14692]
	ret
	.size	MVC_GetBaseViewId, .-MVC_GetBaseViewId
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetVOIdx
	.type	MVC_GetVOIdx, %function
MVC_GetVOIdx:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	w19, w1
	mov	x0, x30
	mov	w21, w2
	bl	_mcount
	cbz	w19, .L1008
	ldr	w0, [x20]
	cmp	w21, w0
	beq	.L1008
	mov	w0, w19
	mov	w3, 0
	b	.L1005
	.p2align 3
.L1006:
	ldr	w4, [x20, w3, sxtw 2]
	cmp	w4, w21
	beq	.L1009
.L1005:
	add	w3, w3, 1
	cmp	w3, w19
	bne	.L1006
.L1004:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1009:
	mov	w0, w3
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L1008:
	mov	w0, 0
	b	.L1004
	.size	MVC_GetVOIdx, .-MVC_GetVOIdx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_is_view_id_in_ref_view_list
	.type	MVC_is_view_id_in_ref_view_list, %function
MVC_is_view_id_in_ref_view_list:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	w19, w2
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	cbz	w19, .L1015
	ldr	w0, [x21]
	cmp	w20, w0
	beq	.L1015
	mov	w0, 0
	b	.L1012
	.p2align 3
.L1013:
	ldr	w3, [x21, w0, sxtw 2]
	cmp	w3, w20
	beq	.L1011
.L1012:
	add	w0, w0, 1
	cmp	w0, w19
	mov	w1, w0
	bne	.L1013
.L1011:
	cmp	w19, wzr
	ldr	x21, [sp, 32]
	ccmp	w19, w1, 0, ne
	cset	w0, hi
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L1015:
	mov	w1, 0
	b	.L1011
	.size	MVC_is_view_id_in_ref_view_list, .-MVC_is_view_id_in_ref_view_list
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GenPiclistfromFrmlist_Interview
	.type	MVC_GenPiclistfromFrmlist_Interview, %function
MVC_GenPiclistfromFrmlist_Interview:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w22, w0
	mov	x0, x30
	mov	x23, x1
	mov	w20, w2
	mov	x21, x3
	mov	x19, x4
	bl	_mcount
	cmp	w22, 1
	beq	.L1030
	cmp	w22, 2
	bne	.L1016
	cbz	w20, .L1016
	sub	w2, w20, #1
	mov	x1, 1648
	mov	w20, 848
	ldr	w0, [x19]
	add	x5, x23, 800
	umaddl	x20, w2, w20, x1
	add	x1, x23, x20
	.p2align 2
.L1021:
	str	x5, [x21, w0, uxtw 3]
	add	x5, x5, 848
	cmp	x5, x1
	ldr	w0, [x19]
	add	w0, w0, 1
	str	w0, [x19]
	bne	.L1021
.L1016:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1030:
	cbz	w20, .L1016
	sub	w2, w20, #1
	mov	x1, 1600
	mov	w20, 848
	ldr	w0, [x19]
	add	x4, x23, 752
	umaddl	x20, w2, w20, x1
	add	x1, x23, x20
	.p2align 2
.L1019:
	str	x4, [x21, w0, uxtw 3]
	add	x4, x4, 848
	cmp	x1, x4
	ldr	w0, [x19]
	add	w0, w0, 1
	str	w0, [x19]
	bne	.L1019
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	MVC_GenPiclistfromFrmlist_Interview, .-MVC_GenPiclistfromFrmlist_Interview
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_append_interview_list
	.type	mvc_append_interview_list, %function
mvc_append_interview_list:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x22, x0
	mov	x0, x30
	mov	w19, w1
	mov	x21, x2
	mov	x24, x3
	bl	_mcount
	add	x0, x22, 10768384
	add	x1, x22, 11120640
	add	x6, x0, 4068
	ldr	w2, [x0, 4064]
	ldr	w3, [x1, 384]
	adds	w2, w2, 1
	beq	.L1032
	ldr	w0, [x0, 4068]
	cmp	w3, w0
	beq	.L1050
	mov	w5, w2
	mov	w0, 0
	b	.L1033
	.p2align 3
.L1034:
	ldr	w4, [x6, w0, sxtw 2]
	cmp	w3, w4
	beq	.L1032
.L1033:
	add	w0, w0, 1
	cmp	w0, w5
	mov	w2, w0
	bne	.L1034
.L1032:
	add	x0, x22, 11116544
	ldrb	w0, [x0, 2849]
	cbz	w0, .L1035
	ubfiz	x0, x19, 1, 32
	add	x0, x0, x2, uxtw
	add	x0, x0, 2691072
	add	x23, x0, 2044
	add	x0, x22, x0, lsl 2
	add	x23, x22, x23, lsl 2
	add	x23, x23, 12
	ldr	w25, [x0, 8172]
.L1036:
	add	x20, x22, 11157504
	add	x0, x22, 11124736
	ldrb	w1, [x20, 2315]
	ldr	w19, [x0, 792]
	cmp	w1, 2
	cset	w26, eq
	subs	w19, w19, #1
	bmi	.L1031
	ldr	x28, .LC70
	mov	w27, 848
	b	.L1067
	.p2align 3
.L1078:
	ldrb	w0, [x1, 2]
	cmp	w0, 3
	beq	.L1077
.L1038:
	subs	w19, w19, #1
	bmi	.L1031
.L1067:
	sxtw	x0, w19
	add	x0, x0, 1388544
	add	x0, x22, x0, lsl 3
	ldr	x1, [x0, 16792]
	cbz	x1, .L1038
	ldrb	w0, [x20, 2315]
	cbz	w0, .L1078
	cmp	w0, 1
	beq	.L1079
	cmp	w0, 2
	bne	.L1038
	ldrb	w2, [x20, 2313]
	ldrb	w0, [x1, 2]
	ubfx	x0, x0, 1, 1
	cbz	w2, .L1044
	ldr	x2, [x20, 2960]
	ldr	w3, [x2, 780]
	ldr	w2, [x1, 780]
	cmp	w3, w2
	cset	w2, eq
	and	w0, w0, w2
.L1044:
	cbz	w0, .L1038
	ldr	w2, [x1, 828]
	.p2align 2
.L1040:
	add	x0, x1, x26
	ldrb	w0, [x0, 12]
	cbz	w0, .L1038
	ldr	w0, [x20, 2988]
	cmp	w0, w2
	bne	.L1038
	ldr	w3, [x1, 56]
	cbz	w25, .L1038
	ldr	w0, [x23]
	cmp	w3, w0
	beq	.L1045
	mov	w0, 0
	.p2align 2
.L1046:
	add	w0, w0, 1
	cmp	w25, w0
	beq	.L1038
	ldr	w2, [x23, w0, sxtw 2]
	cmp	w3, w2
	bne	.L1046
.L1045:
	ldr	w0, [x24]
	mov	x2, 848
	ldr	x3, [x28, 104]
	umull	x0, w0, w27
	add	x0, x21, x0
	blr	x3
	ldr	w0, [x24]
	umull	x0, w0, w27
	add	x0, x21, x0
	str	x0, [x0, 712]
	str	x0, [x0, 760]
	str	x0, [x0, 808]
	ldr	w0, [x24]
	ldr	w1, [x22, 52]
	umull	x0, w0, w27
	sub	w1, w1, #1
	add	x0, x21, x0
	str	w1, [x0, 48]
	ldr	w0, [x24]
	cmp	w25, w0
	beq	.L1031
	add	w0, w0, 1
	subs	w19, w19, #1
	str	w0, [x24]
	bpl	.L1067
.L1031:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1079:
	ldrb	w2, [x20, 2313]
	ldrb	w0, [x1, 2]
	and	w0, w0, 1
	cbz	w2, .L1042
	ldr	x3, [x20, 2960]
	ldr	w2, [x1, 828]
	ldr	w3, [x3, 828]
	cmp	w3, w2
	cset	w2, eq
	and	w0, w0, w2
.L1042:
	cbz	w0, .L1038
	ldr	w2, [x1, 780]
	b	.L1040
	.p2align 3
.L1077:
	ldr	w2, [x1, 732]
	b	.L1040
	.p2align 3
.L1035:
	ubfiz	x0, x19, 1, 32
	add	x0, x0, x2, uxtw
	add	x0, x0, 2691072
	add	x23, x0, 2052
	add	x0, x22, x0, lsl 2
	add	x23, x22, x23, lsl 2
	add	x23, x23, 12
	ldr	w25, [x0, 8204]
	b	.L1036
.L1050:
	mov	w2, 0
	b	.L1032
	.size	mvc_append_interview_list, .-mvc_append_interview_list
	.align	3
.LC70:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_InitListX
	.type	MVC_InitListX, %function
MVC_InitListX:
	stp	x29, x30, [sp, -480]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 11120640
	add	x20, x19, 11116544
	bl	_mcount
	add	x26, x19, 11157504
	str	wzr, [x21, 392]
	str	wzr, [x21, 396]
	ldrb	w0, [x20, 2840]
	cbnz	w0, .L1081
	ldrb	w0, [x26, 2315]
	add	x27, x19, 11124736
	cbnz	w0, .L1224
	ldr	w0, [x27, 800]
	cbz	w0, .L1161
	sub	w3, w0, #1
	mov	w23, 0
	add	x3, x3, 1388544
	add	x0, x27, 536
	add	x3, x3, 2116
	add	x3, x19, x3, lsl 3
	b	.L1087
	.p2align 3
.L1086:
	cmp	x0, x3
	beq	.L1085
.L1087:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 3]
	cmp	w2, 3
	bne	.L1086
	ldr	w2, [x1, 704]
	and	w2, w2, 16776960
	cmp	w2, 65536
	bne	.L1086
	add	x2, x19, x23, uxtw 3
	add	x1, x1, 704
	cmp	x0, x3
	add	w23, w23, 1
	str	x1, [x2, 288]
	bne	.L1087
	.p2align 2
.L1085:
	add	x22, x19, 288
	ldr	x3, .LC71
	mov	w1, w23
	mov	w2, 8
	mov	x0, x22
	bl	qsort
	str	w23, [x20, 2888]
	ldr	w1, [x27, 804]
	cbz	w1, .L1162
	sub	w2, w1, #1
	add	x0, x27, 664
	add	x2, x2, 1388544
	mov	w24, w23
	add	x2, x2, 2132
	add	x2, x19, x2, lsl 3
	b	.L1090
	.p2align 3
.L1089:
	cmp	x2, x0
	beq	.L1225
.L1090:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w3, [x1, 3]
	cmp	w3, 3
	bne	.L1089
	ldr	w3, [x1, 704]
	and	w3, w3, 16776960
	cmp	w3, 256
	bne	.L1089
	add	x3, x19, x24, uxtw 3
	add	x1, x1, 704
	cmp	x2, x0
	add	w24, w24, 1
	str	x1, [x3, 288]
	bne	.L1090
	.p2align 2
.L1225:
	sub	w1, w24, w23
.L1088:
	uxtw	x0, w23
	ldr	x3, .LC72
	add	x0, x0, 36
	mov	w2, 8
	add	x0, x19, x0, lsl 3
	bl	qsort
	str	w24, [x20, 2888]
	ldrsb	w0, [x20, 2852]
	str	wzr, [x20, 2892]
	cbnz	w0, .L1096
.L1140:
	add	x23, x19, 11108352
	mov	x0, x19
	add	x24, x23, 272
	add	x3, x21, 392
	mov	w1, 0
	mov	x2, x24
	bl	mvc_append_interview_list
	ldrb	w0, [x26, 2315]
	cbnz	w0, .L1226
	ldr	w3, [x21, 392]
	ldr	w0, [x20, 2888]
	cbz	w3, .L1165
	add	x1, x23, 976
	add	w3, w0, w3
	.p2align 2
.L1143:
	add	x2, x19, x0, uxtw 3
	add	w0, w0, 1
	cmp	w3, w0
	str	x1, [x2, 288]
	add	x1, x1, 848
	bne	.L1143
.L1142:
	str	w3, [x20, 2888]
.L1144:
	ldrb	w1, [x20, 2840]
	cmp	w1, 1
	beq	.L1227
.L1141:
	cbnz	w1, .L1148
.L1230:
	ldr	w2, [x20, 2888]
	cbz	w2, .L1228
.L1149:
	ldr	w1, [x20, 2900]
	ldr	w0, [x20, 2904]
	ldr	w3, [x20, 2892]
	add	w1, w1, 1
	add	w0, w0, 1
	cmp	w1, w2
	csel	w1, w1, w2, ls
	cmp	w0, w3
	csel	w0, w0, w3, ls
	str	w1, [x20, 2888]
	cmp	w1, 32
	str	w0, [x20, 2892]
	bhi	.L1155
	.p2align 2
.L1187:
	add	x2, x19, x1, uxtw 3
	add	w1, w1, 1
	cmp	w1, 33
	str	xzr, [x2, 288]
	bne	.L1187
.L1155:
	cmp	w0, 32
	bhi	.L1153
	.p2align 2
.L1186:
	add	x1, x19, x0, uxtw 3
	add	w0, w0, 1
	cmp	w0, 33
	str	xzr, [x1, 552]
	bne	.L1186
.L1153:
	mov	w0, 0
.L1214:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 480
	ret
	.p2align 3
.L1081:
	ldrb	w0, [x26, 2315]
	add	x27, x19, 11124736
	cbz	w0, .L1105
	ldr	w0, [x27, 800]
	cbz	w0, .L1229
	sub	w3, w0, #1
	mov	w22, 0
	add	x3, x3, 1388544
	add	x0, x27, 536
	add	x3, x3, 2116
	add	x3, x19, x3, lsl 3
	.p2align 2
.L1124:
	ldr	x2, [x0]
	add	x0, x0, 8
	ldrb	w1, [x2, 2]
	cbz	w1, .L1123
	ldr	w4, [x2, 32]
	add	x1, x29, 480
	ldr	w5, [x26, 2988]
	add	x1, x1, x22, uxtw 3
	sub	x1, x1, #4096
	cmp	w5, w4
	blt	.L1123
	add	w22, w22, 1
	str	x2, [x1, 3712]
.L1123:
	cmp	x0, x3
	bne	.L1124
	add	x24, x29, 96
	ldr	x3, .LC79
	mov	w2, 8
	mov	w1, w22
	mov	x0, x24
	bl	qsort
	ldr	w23, [x27, 800]
	cbz	w23, .L1125
.L1159:
	sub	w1, w23, #1
	add	x0, x27, 536
	add	x1, x1, 1388544
	mov	w28, w22
	add	x1, x1, 2116
	add	x1, x19, x1, lsl 3
	.p2align 2
.L1127:
	ldr	x3, [x0]
	add	x0, x0, 8
	ldrb	w2, [x3, 2]
	cbz	w2, .L1126
	ldr	w4, [x3, 32]
	add	x2, x29, 480
	ldr	w5, [x26, 2988]
	add	x2, x2, x28, uxtw 3
	sub	x2, x2, #4096
	cmp	w5, w4
	bge	.L1126
	add	w28, w28, 1
	str	x3, [x2, 3712]
.L1126:
	cmp	x0, x1
	bne	.L1127
	sub	w23, w28, w22
	ldr	x3, .LC80
	mov	w2, 8
	mov	w1, w23
	add	x0, x24, x22, uxtw 3
	bl	qsort
	cbz	w22, .L1128
.L1158:
	mov	x0, 0
	.p2align 2
.L1129:
	add	w1, w23, w0
	add	x3, x29, 480
	ldr	x2, [x24, x0, lsl 3]
	add	x0, x0, 1
	add	x1, x3, x1, lsl 3
	cmp	w22, w0
	str	x2, [x1, -256]
	bhi	.L1129
.L1128:
	cmp	w28, w22
	bls	.L1130
	mov	w0, w22
	.p2align 2
.L1131:
	add	x2, x29, 480
	sub	w1, w0, w22
	add	x2, x2, x0, uxtw 3
	add	x3, x29, 480
	sub	x2, x2, #4096
	add	x1, x3, x1, lsl 3
	add	w0, w0, 1
	cmp	w28, w0
	ldr	x2, [x2, 3712]
	str	x2, [x1, -256]
	bne	.L1131
.L1130:
	str	wzr, [x20, 2888]
	add	x22, x19, 288
	str	wzr, [x20, 2892]
	add	x25, x20, 2888
	mov	x1, x24
	mov	w2, w28
	ldrb	w0, [x26, 2315]
	mov	w5, 0
	mov	x4, x25
	mov	x3, x22
	add	x23, x19, 552
	add	x24, x20, 2892
	bl	MVC_GenPiclistfromFrmlist
	ldrb	w0, [x26, 2315]
	mov	w2, w28
	mov	w5, 0
	mov	x4, x24
	mov	x3, x23
	add	x1, x29, 224
	bl	MVC_GenPiclistfromFrmlist
	ldr	w28, [x27, 804]
	add	x27, x29, 352
	cbz	w28, .L1132
	mov	x1, 0
	add	x27, x29, 352
	.p2align 2
.L1133:
	lsl	x0, x1, 3
	add	x0, x0, 11124736
	add	x0, x0, 664
	ldr	x0, [x19, x0]
	str	x0, [x27, x1, lsl 3]
	add	x1, x1, 1
	cmp	w28, w1
	bhi	.L1133
.L1132:
	ldr	x3, .LC74
	mov	w2, 8
	mov	w1, w28
	mov	x0, x27
	bl	qsort
	ldrb	w0, [x26, 2315]
	mov	x4, x25
	mov	w5, 1
	mov	x3, x22
	mov	w2, w28
	mov	x1, x27
	bl	MVC_GenPiclistfromFrmlist
	ldrb	w0, [x26, 2315]
	mov	x3, x23
	mov	x1, x27
	mov	w5, 1
	mov	x4, x24
	mov	w2, w28
	bl	MVC_GenPiclistfromFrmlist
	ldr	w23, [x20, 2888]
	ldr	w0, [x20, 2892]
	cmp	w0, w23
	cset	w1, eq
.L1122:
	cmp	w23, 1
	cset	w0, hi
	tst	w1, w0
	beq	.L1134
	cbz	w23, .L1135
	ldr	x4, [x19, 288]
	ldr	x0, [x19, 552]
	cmp	x4, x0
	bne	.L1134
	sub	w23, w23, #1
	mov	x1, x19
	add	x0, x19, x23, lsl 3
.L1137:
	cmp	x0, x1
	beq	.L1139
	ldr	x3, [x1, 296]
	add	x1, x1, 8
	ldr	x2, [x1, 552]
	cmp	x3, x2
	beq	.L1137
	.p2align 2
.L1134:
	ldrsb	w0, [x20, 2852]
	cbz	w0, .L1140
.L1219:
	ldrb	w1, [x20, 2840]
.L1233:
	cbz	w1, .L1230
.L1148:
	ldr	x0, [x20, 2888]
	cbz	x0, .L1150
	ldr	w2, [x20, 2888]
	b	.L1149
	.p2align 3
.L1105:
	ldr	w0, [x27, 800]
	cbz	w0, .L1163
	sub	w3, w0, #1
	mov	w23, 0
	add	x3, x3, 1388544
	add	x0, x27, 536
	add	x3, x3, 2116
	add	x3, x19, x3, lsl 3
	b	.L1110
	.p2align 3
.L1109:
	cmp	x0, x3
	beq	.L1108
.L1110:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 3]
	cmp	w2, 3
	bne	.L1109
	ldr	w2, [x1, 728]
	add	x5, x19, x23, uxtw 3
	ldr	w4, [x26, 2992]
	add	x1, x1, 704
	cmp	w4, w2
	blt	.L1109
	str	x1, [x5, 288]
	cmp	x0, x3
	add	w23, w23, 1
	bne	.L1110
	.p2align 2
.L1108:
	add	x22, x19, 288
	ldr	x3, .LC77
	mov	w2, 8
	mov	w1, w23
	mov	x0, x22
	bl	qsort
	ldr	w24, [x27, 800]
	cbz	w24, .L1111
	sub	w1, w24, #1
	add	x0, x27, 536
	add	x1, x1, 1388544
	mov	w25, w23
	add	x1, x1, 2116
	add	x1, x19, x1, lsl 3
	b	.L1113
	.p2align 3
.L1112:
	cmp	x0, x1
	beq	.L1231
.L1113:
	ldr	x2, [x0]
	add	x0, x0, 8
	ldrb	w3, [x2, 3]
	cmp	w3, 3
	bne	.L1112
	ldr	w3, [x2, 728]
	add	x5, x19, x25, uxtw 3
	ldr	w4, [x26, 2992]
	add	x2, x2, 704
	cmp	w4, w3
	bge	.L1112
	str	x2, [x5, 288]
	cmp	x0, x1
	add	w25, w25, 1
	bne	.L1113
	.p2align 2
.L1231:
	uxtw	x0, w23
	sub	w24, w25, w23
	add	x0, x0, 36
	ldr	x3, .LC78
	uxtw	x28, w25
	mov	w2, 8
	add	x0, x19, x0, lsl 3
	mov	w1, w24
	add	x28, x28, 36
	bl	qsort
	add	x28, x19, x28, lsl 3
	cbz	w23, .L1115
.L1157:
	mov	x2, x22
	mov	w0, 0
	.p2align 2
.L1116:
	add	w1, w24, w0
	ldr	x3, [x2], 8
	add	x1, x1, 69
	add	w0, w0, 1
	cmp	w0, w23
	str	x3, [x19, x1, lsl 3]
	bcc	.L1116
.L1115:
	cmp	w25, w23
	bls	.L1117
	mov	w0, w23
	.p2align 2
.L1118:
	sub	w1, w0, w23
	add	x2, x19, x0, uxtw 3
	add	x1, x1, 69
	add	w0, w0, 1
	cmp	w0, w25
	ldr	x2, [x2, 288]
	str	x2, [x19, x1, lsl 3]
	bne	.L1118
.L1117:
	str	w25, [x20, 2888]
	str	w25, [x20, 2892]
	ldr	w1, [x27, 804]
	cbz	w1, .L1164
	sub	w2, w1, #1
	add	x0, x27, 664
	add	x2, x2, 1388544
	mov	w23, w25
	add	x2, x2, 2132
	add	x2, x19, x2, lsl 3
	b	.L1121
	.p2align 3
.L1120:
	cmp	x0, x2
	beq	.L1232
.L1121:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w3, [x1, 2]
	cmp	w3, 3
	bne	.L1120
	ldrb	w3, [x1, 705]
	cmp	w3, 1
	bne	.L1120
	add	x3, x19, x23, uxtw 3
	add	x1, x1, 704
	cmp	x0, x2
	add	w23, w23, 1
	str	x1, [x3, 288]
	str	x1, [x3, 552]
	bne	.L1121
	.p2align 2
.L1232:
	sub	w1, w23, w25
.L1119:
	ldr	x24, .LC72
	mov	x0, x28
	mov	w2, 8
	mov	x3, x24
	bl	qsort
	ldr	w0, [x20, 2888]
	mov	x3, x24
	mov	w2, 8
	sub	w1, w23, w0
	uxtw	x0, w0
	add	x0, x0, 69
	add	x0, x19, x0, lsl 3
	bl	qsort
	str	w23, [x20, 2888]
	mov	w1, 1
	str	w23, [x20, 2892]
	b	.L1122
	.p2align 3
.L1224:
	ldr	w0, [x27, 800]
	mov	w24, 0
	cbz	w0, .L1084
	sub	w4, w0, #1
	mov	w24, 0
	add	x4, x4, 1388544
	add	x0, x27, 536
	add	x4, x4, 2116
	add	x4, x19, x4, lsl 3
	.p2align 2
.L1093:
	ldr	x2, [x0]
	add	x1, x29, 480
	add	x1, x1, x24, uxtw 3
	add	x0, x0, 8
	sub	x1, x1, #4096
	cmp	x4, x0
	ldrb	w3, [x2, 3]
	cbz	w3, .L1092
	add	w24, w24, 1
	str	x2, [x1, 3712]
.L1092:
	bne	.L1093
.L1084:
	ldr	x3, .LC73
	mov	w1, w24
	mov	w2, 8
	add	x0, x29, 96
	add	x22, x19, 288
	add	x23, x20, 2888
	bl	qsort
	str	wzr, [x20, 2888]
	mov	w2, w24
	mov	w5, 0
	ldrb	w0, [x26, 2315]
	add	x1, x29, 96
	mov	x4, x23
	mov	x3, x22
	bl	MVC_GenPiclistfromFrmlist
	ldr	w24, [x27, 804]
	add	x27, x29, 352
	cbz	w24, .L1094
	mov	x1, 0
	add	x27, x29, 352
	.p2align 2
.L1095:
	lsl	x0, x1, 3
	add	x0, x0, 11124736
	add	x0, x0, 664
	ldr	x0, [x19, x0]
	str	x0, [x27, x1, lsl 3]
	add	x1, x1, 1
	cmp	w24, w1
	bhi	.L1095
.L1094:
	ldr	x3, .LC74
	mov	w2, 8
	mov	w1, w24
	mov	x0, x27
	bl	qsort
	ldrb	w0, [x26, 2315]
	mov	w5, 1
	mov	x4, x23
	mov	x3, x22
	mov	w2, w24
	mov	x1, x27
	bl	MVC_GenPiclistfromFrmlist
	str	wzr, [x20, 2892]
	ldrsb	w0, [x20, 2852]
	cbz	w0, .L1140
.L1096:
	ldr	w0, [x20, 2888]
	cbnz	w0, .L1219
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L1100
	ldrb	w0, [x26, 2315]
	cbnz	w0, .L1101
	ldr	x0, [x26, 2960]
	add	x0, x0, 704
	str	x0, [x19, 288]
.L1102:
	mov	w0, 1
	ldrb	w1, [x20, 2840]
	str	w0, [x20, 2888]
	b	.L1233
.L1226:
	ldr	w2, [x21, 392]
	add	x4, x20, 2888
	mov	x3, x22
	mov	x1, x24
	bl	MVC_GenPiclistfromFrmlist_Interview
	b	.L1144
.L1135:
	ldr	x4, [x19, 552]
.L1139:
	ldr	x0, [x19, 560]
	str	x0, [x19, 552]
	str	x4, [x19, 560]
	b	.L1134
.L1101:
	cmp	w0, 1
	ldr	x0, [x26, 2960]
	beq	.L1234
	add	x0, x0, 800
	str	x0, [x19, 288]
	b	.L1102
.L1227:
	add	x22, x23, 1968
	mov	x0, x19
	add	x3, x21, 396
	mov	x2, x22
	bl	mvc_append_interview_list
	ldrb	w0, [x26, 2315]
	cbnz	w0, .L1145
	ldr	w3, [x21, 396]
	ldr	w1, [x20, 2892]
	cbz	w3, .L1166
	add	x0, x23, 2672
	add	w3, w3, w1
	.p2align 2
.L1147:
	add	x2, x19, x1, uxtw 3
	add	w1, w1, 1
	cmp	w3, w1
	str	x0, [x2, 552]
	add	x0, x0, 848
	bne	.L1147
.L1146:
	ldrb	w1, [x20, 2840]
	str	w3, [x20, 2892]
	b	.L1141
.L1165:
	mov	w3, w0
	b	.L1142
.L1234:
	add	x0, x0, 752
	str	x0, [x19, 288]
	b	.L1102
.L1162:
	mov	w24, w23
	b	.L1088
.L1111:
	uxtw	x28, w23
	ldr	x3, .LC78
	add	x28, x28, 36
	mov	w2, 8
	mov	w1, 0
	mov	w25, w23
	add	x28, x19, x28, lsl 3
	mov	x0, x28
	bl	qsort
	cbnz	w23, .L1157
	b	.L1117
	.p2align 3
.L1164:
	mov	w23, w25
	b	.L1119
.L1161:
	mov	w23, 0
	b	.L1085
.L1229:
	add	x24, x29, 96
	ldr	x3, .LC79
	mov	w2, 8
	mov	w1, 0
	mov	x0, x24
	mov	w22, 0
	bl	qsort
	ldr	w23, [x27, 800]
	cbnz	w23, .L1159
	ldr	x3, .LC80
	mov	w2, 8
	mov	w1, 0
	mov	x0, x24
	mov	w28, 0
	bl	qsort
	b	.L1130
	.p2align 3
.L1163:
	mov	w23, 0
	b	.L1108
.L1125:
	ldr	x3, .LC80
	mov	w2, 8
	mov	w1, 0
	add	x0, x24, x22, uxtw 3
	mov	w28, w22
	bl	qsort
	cbnz	w22, .L1158
	b	.L1130
	.p2align 3
.L1145:
	ldr	w2, [x21, 396]
	mov	x1, x22
	add	x4, x20, 2892
	add	x3, x19, 552
	bl	MVC_GenPiclistfromFrmlist_Interview
	ldrb	w1, [x20, 2840]
	b	.L1233
.L1150:
	ldr	x1, .LC84
.L1220:
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	MVC_ClearCurrSlice
	mov	w0, -1
	b	.L1214
.L1228:
	ldr	x1, .LC82
	b	.L1220
.L1100:
	ldr	x1, .LC76
	b	.L1220
.L1166:
	mov	w3, w1
	b	.L1146
	.size	MVC_InitListX, .-MVC_InitListX
	.align	3
.LC71:
	.xword	MVC_compare_pic_by_pic_num_desc
	.align	3
.LC72:
	.xword	MVC_compare_pic_by_lt_pic_num_asc
	.align	3
.LC73:
	.xword	MVC_compare_fs_by_frame_num_desc
	.align	3
.LC74:
	.xword	MVC_compare_fs_by_lt_pic_idx_asc
	.align	3
.LC76:
	.xword	.LC75
	.align	3
.LC77:
	.xword	MVC_compare_pic_by_poc_desc
	.align	3
.LC78:
	.xword	MVC_compare_pic_by_poc_asc
	.align	3
.LC79:
	.xword	MVC_compare_fs_by_poc_desc
	.align	3
.LC80:
	.xword	MVC_compare_fs_by_poc_asc
	.align	3
.LC82:
	.xword	.LC81
	.align	3
.LC84:
	.xword	.LC83
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DumpList
	.type	MVC_DumpList, %function
MVC_DumpList:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC85
	ldr	w0, [x0]
	tbz	x0, 13, .L1235
	add	x24, x22, 11116544
	ldr	x23, .LC87
	mov	w20, 0
	add	x24, x24, 2888
.L1237:
	ldr	w0, [x24]
	cbz	w0, .L1240
	uxtw	x0, w20
	mov	w19, 0
	lsl	x21, x0, 5
	add	x21, x21, x0
	.p2align 2
.L1238:
	add	x4, x21, x19, uxtw
	mov	w3, w19
	add	x4, x4, 36
	mov	w2, w20
	mov	x1, x23
	mov	w0, 13
	add	w19, w19, 1
	ldr	x4, [x22, x4, lsl 3]
	ldr	x4, [x4, 8]
	ldr	w5, [x4, 32]
	ldr	w4, [x4, 20]
	bl	dprint_vfmw
	ldr	w0, [x24]
	cmp	w0, w19
	bhi	.L1238
.L1240:
	add	w20, w20, 1
	add	x24, x24, 4
	cmp	w20, 2
	bne	.L1237
.L1235:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	MVC_DumpList, .-MVC_DumpList
	.align	3
.LC85:
	.xword	g_PrintEnable
	.align	3
.LC87:
	.xword	.LC86
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_FindNearestPOCPicId
	.type	MVC_FindNearestPOCPicId, %function
MVC_FindNearestPOCPicId:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x2, x19, 11124736
	ldr	w0, [x2, 796]
	cbz	w0, .L1252
	add	x1, x19, 11157504
	ldr	w0, [x2, 792]
	ldr	w7, [x1, 2988]
	cbz	w0, .L1253
	sub	w1, w0, #1
	add	x2, x2, 408
	add	x1, x1, 1388544
	mov	w6, 2147483647
	add	x1, x1, 2100
	mov	w0, 0
	add	x5, x19, x1, lsl 3
	.p2align 2
.L1251:
	ldr	x3, [x2]
	add	x2, x2, 8
	cbz	x3, .L1250
	ldr	w1, [x3, 32]
	sub	w1, w7, w1
	sxtw	x1, w1
	eor	x4, x1, x1, asr 63
	sub	x4, x4, x1, asr 63
	cmp	w4, w6
	bge	.L1250
	ldr	w0, [x3, 220]
	mov	w6, w4
.L1250:
	cmp	x2, x5
	bne	.L1251
.L1249:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1253:
	mov	w0, 0
	b	.L1249
.L1252:
	mov	w0, -1
	b	.L1249
	.size	MVC_FindNearestPOCPicId, .-MVC_FindNearestPOCPicId
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_FindMinRefIdx
	.type	MVC_FindMinRefIdx, %function
MVC_FindMinRefIdx:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 11116544
	ldrb	w1, [x0, 2840]
	cmp	w1, 2
	beq	.L1258
	add	x1, x19, 11157504
	ldrb	w1, [x1, 2315]
	cbnz	w1, .L1288
	add	x6, x19, 11124736
	ldr	w5, [x0, 2888]
	add	x6, x6, 1032
	mov	w4, 0
	.p2align 2
.L1262:
	cbz	w5, .L1266
	add	x1, x19, 288
	mov	w3, 32
	mov	w0, 0
	b	.L1264
	.p2align 3
.L1263:
	add	w0, w0, 1
	cmp	w0, w5
	beq	.L1289
.L1264:
	ldr	x2, [x1]
	add	x1, x1, 8
	ldr	x2, [x2, 8]
	ldr	w2, [x2, 52]
	cmp	w2, w4
	bne	.L1263
	cmp	w3, w0
	csel	w3, w3, w0, ls
	add	w0, w0, 1
	stp	w3, w3, [x6]
	cmp	w0, w5
	bne	.L1264
.L1289:
	cmp	w3, 31
	bhi	.L1266
.L1265:
	add	w4, w4, 1
	add	x6, x6, 8
	cmp	w4, 16
	bne	.L1262
.L1258:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1288:
	ldr	w6, [x0, 2888]
	add	x7, x19, 11124736
	add	x7, x7, 1032
	mov	w4, 0
	cbz	w6, .L1270
	.p2align 2
.L1291:
	add	x2, x19, 288
	mov	w5, 32
	mov	w1, 0
	b	.L1268
	.p2align 3
.L1267:
	add	w1, w1, 1
	cmp	w1, w6
	beq	.L1290
.L1268:
	ldr	x0, [x2]
	add	x2, x2, 8
	ldr	x3, [x0, 8]
	ldrb	w0, [x0]
	cmp	w0, 2
	ldr	w0, [x3, 52]
	cset	w3, eq
	orr	w0, w3, w0, lsl 1
	cmp	w0, w4
	bne	.L1267
	cmp	w5, w1
	csel	w5, w5, w1, ls
	add	w1, w1, 1
	str	w5, [x7]
	cmp	w1, w6
	bne	.L1268
.L1290:
	cmp	w5, 31
	bhi	.L1270
.L1269:
	add	w4, w4, 1
	add	x7, x7, 4
	cmp	w4, 32
	beq	.L1258
	cbnz	w6, .L1291
	.p2align 2
.L1270:
	str	wzr, [x7]
	b	.L1269
	.p2align 3
.L1266:
	stp	wzr, wzr, [x6]
	b	.L1265
	.size	MVC_FindMinRefIdx, .-MVC_FindMinRefIdx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecList
	.type	MVC_DecList, %function
MVC_DecList:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 11124736
	mov	w6, -1
	ldr	w0, [x1, 796]
	cbz	w0, .L1293
	add	x2, x19, 11157504
	ldr	w0, [x1, 792]
	ldr	w7, [x2, 2988]
	cbz	w0, .L1301
	add	w4, w0, w6
	add	x1, x1, 408
	add	x4, x4, 1388544
	mov	w6, 0
	add	x4, x4, 2100
	mov	w5, 2147483647
	add	x4, x19, x4, lsl 3
	.p2align 2
.L1295:
	ldr	x2, [x1]
	add	x1, x1, 8
	cbz	x2, .L1294
	ldr	w0, [x2, 32]
	sub	w0, w7, w0
	sxtw	x0, w0
	eor	x3, x0, x0, asr 63
	sub	x3, x3, x0, asr 63
	cmp	w3, w5
	bge	.L1294
	ldr	w6, [x2, 220]
	mov	w5, w3
.L1294:
	cmp	x1, x4
	bne	.L1295
.L1293:
	add	x21, x19, 11120640
	add	x0, x19, 11116544
	mov	w20, -1
	str	w6, [x21, 380]
	str	w20, [x21, 376]
	ldrb	w1, [x0, 2840]
	cmp	w1, 2
	beq	.L1309
	mov	x0, x19
	bl	MVC_InitListX
	cbnz	w0, .L1310
	mov	x0, x19
	bl	MVC_ReorderListX
	mov	x0, x19
	bl	MVC_RepairList
	cbnz	w0, .L1302
	mov	x0, x19
	bl	MVC_FindMinRefIdx
	ldr	x0, [x19, 288]
	cbz	x0, .L1299
	ldr	x0, [x0, 8]
	ldr	w20, [x0, 220]
.L1299:
	mov	w0, 0
	str	w20, [x21, 376]
.L1297:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1309:
	str	wzr, [x0, 2888]
	str	wzr, [x0, 2892]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1302:
	mov	w0, w20
	b	.L1297
.L1301:
	mov	w6, 0
	b	.L1293
.L1310:
	ldr	x1, .LC89
	mov	w0, 13
	bl	dprint_vfmw
	mov	w0, w20
	b	.L1297
	.size	MVC_DecList, .-MVC_DecList
	.align	3
.LC89:
	.xword	.LC88
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_NoPicOut
	.type	MVC_NoPicOut, %function
MVC_NoPicOut:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 48]
	cbz	w0, .L1318
	mov	x1, 51167
	sub	w3, w0, #1
	mov	w2, 848
	movk	x1, 0xa9, lsl 16
	add	x0, x19, 11124736
	umaddl	x2, w3, w2, x1
	add	x0, x0, 1167
	add	x2, x19, x2
	b	.L1317
	.p2align 3
.L1325:
	ldrb	w3, [x0, -2]
	cmp	w3, 1
	beq	.L1315
	add	x0, x0, 848
	cmp	x0, x2
	beq	.L1318
.L1317:
	ldrb	w1, [x0]
	cmp	w1, 1
	bne	.L1325
.L1315:
	strb	wzr, [x0, -5]
	strb	wzr, [x0, -4]
	add	x0, x0, 848
	cmp	x0, x2
	bne	.L1317
.L1318:
	ldr	w0, [x19, 52]
	cbz	w0, .L1311
	sub	w1, w0, #1
	add	x0, x19, 148
	add	x1, x1, 38
	add	x1, x19, x1, lsl 2
	.p2align 2
.L1319:
	str	wzr, [x0], 4
	cmp	x0, x1
	bne	.L1319
.L1311:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_NoPicOut, .-MVC_NoPicOut
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetBackPicFromVOQueue
	.type	MVC_GetBackPicFromVOQueue, %function
MVC_GetBackPicFromVOQueue:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x22, 120]
	bl	FSP_GetFspType
	cbz	w0, .L1343
.L1327:
	ldr	w0, [x22, 48]
	mov	w23, 0
	mov	w20, 848
	cbz	w0, .L1334
	.p2align 2
.L1338:
	uxtw	x1, w23
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 1
	sub	x0, x0, x1
	umull	x21, w23, w20
	add	x0, x22, x0, lsl 4
	add	x0, x0, 11124736
	add	x21, x21, 11124736
	add	x19, x21, 1776
	add	x21, x21, 1808
	add	x19, x22, x19
	add	x21, x22, x21
	strb	wzr, [x0, 1162]
	strb	wzr, [x0, 1163]
.L1332:
	ldr	x1, [x19]
	cbnz	x1, .L1344
.L1331:
	add	x19, x19, 8
	cmp	x19, x21
	bne	.L1332
	ldr	w0, [x22, 48]
	add	w23, w23, 1
	cmp	w0, w23
	bhi	.L1338
.L1334:
	ldr	w0, [x22, 52]
	cbz	w0, .L1326
	sub	w1, w0, #1
	add	x0, x22, 148
	add	x1, x1, 38
	add	x22, x22, x1, lsl 2
	.p2align 2
.L1335:
	str	wzr, [x0], 4
	cmp	x0, x22
	bne	.L1335
.L1326:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1344:
	ldr	w0, [x22, 120]
	bl	FreeUsdByDec
	str	xzr, [x19]
	b	.L1331
.L1343:
	add	x0, x22, 912
	bl	ResetVoQueue
	b	.L1327
	.size	MVC_GetBackPicFromVOQueue, .-MVC_GetBackPicFromVOQueue
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_wait_vo
	.type	mvc_wait_vo, %function
mvc_wait_vo:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	mvc_wait_vo, .-mvc_wait_vo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_RoundLog2
	.type	MVC_RoundLog2, %function
MVC_RoundLog2:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	mul	w2, w19, w19
	mov	w0, 0
	mov	w3, 1
	.p2align 2
.L1347:
	add	w0, w0, 1
	lsl	w1, w3, w0
	cmp	w2, w1
	bge	.L1347
	asr	w0, w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_RoundLog2, .-MVC_RoundLog2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetReRangeFlag
	.type	MVC_GetReRangeFlag, %function
MVC_GetReRangeFlag:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x22, x20, 11116544
	mov	x19, x1
	bl	_mcount
	mov	w0, 2240
	ldr	x3, [x20, 280]
	ldr	w1, [x22, 2856]
	ldrsb	w2, [x22, 2852]
	umull	x0, w1, w0
	cmn	w2, #1
	add	x0, x3, x0
	beq	.L1366
	cbnz	w2, .L1352
	ldrb	w1, [x20, 2]
	cmp	w1, 1
	beq	.L1367
	ldr	w0, [x0, 28]
	ldr	w1, [x20, 28]
	cmp	w1, w0
	beq	.L1354
	ldr	x1, .LC91
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1352:
	ldr	x1, .LC93
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1366:
	ldr	w0, [x0, 28]
	mov	w21, 3992
	ldr	x1, [x20, 272]
	umull	x0, w0, w21
	add	x21, x1, x0
.L1351:
	ldrb	w0, [x21, 20]
	mov	w2, 2
	ldr	w1, [x21, 3952]
	sub	w0, w2, w0
	ldr	w3, [x21, 3948]
	ldp	w6, w5, [x20, 12]
	madd	w1, w1, w0, w0
	add	w2, w3, 1
	cmp	w6, w2
	ccmp	w5, w1, 0, eq
	bne	.L1356
	add	x0, x20, 11124736
	ldr	w3, [x21, 3972]
	mov	w4, 0
	ldr	w0, [x0, 792]
	add	w0, w0, 1
	cmp	w3, w0
	bhi	.L1356
.L1357:
	ldrb	w0, [x22, 2851]
	cmp	w0, 1
	beq	.L1368
.L1361:
	ldr	w1, [x21, 3972]
	sub	w1, w1, #1
.L1360:
	ldr	w2, [x20, 44]
	mov	w0, w4
	cmp	w2, w1
	cset	w2, ne
	orr	w4, w2, w4
	str	w4, [x19]
	str	w1, [x20, 44]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1356:
	ldr	x0, .LC94
	ldr	x4, [x0]
	cbz	x4, .L1363
	ubfiz	w2, w2, 4, 12
	ubfiz	w1, w1, 4, 12
	ldr	w0, [x20, 120]
	ubfiz	w6, w6, 4, 12
	ubfiz	w5, w5, 4, 12
	strh	w2, [x29, 60]
	strh	w1, [x29, 62]
	mov	w3, 8
	strh	w6, [x29, 56]
	add	x2, x29, 56
	strh	w5, [x29, 58]
	mov	w1, 2
	blr	x4
	ldrb	w0, [x22, 2851]
	mov	w4, 1
	cmp	w0, 1
	bne	.L1361
.L1368:
	add	x0, x20, 290816
	add	x3, x20, 11051008
	add	x0, x0, 2488
	add	x3, x3, 56
	mov	w2, 0
	.p2align 2
.L1359:
	ldr	w1, [x0]
	add	x0, x0, 335872
	add	x0, x0, 308
	cmp	w1, w2
	sub	w1, w1, #1
	csel	w2, w1, w2, hi
	cmp	x0, x3
	bne	.L1359
	add	w0, w2, 1
	mov	w1, 16
	lsl	w0, w0, 1
	cmp	w0, w1
	csel	w1, w0, w1, cc
	b	.L1360
	.p2align 3
.L1354:
	add	x21, x20, 11046912
	add	x21, x21, 180
	b	.L1351
	.p2align 3
.L1367:
	ldr	w1, [x0, 28]
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 4
	sub	x0, x0, x1
	lsl	x21, x0, 2
	sub	x21, x21, x0
	lsl	x1, x21, 6
	add	x21, x21, x1
	add	x21, x20, x21, lsl 2
	add	x21, x21, 286720
	add	x21, x21, 2612
	b	.L1351
	.p2align 3
.L1363:
	mov	w4, 1
	b	.L1357
	.size	MVC_GetReRangeFlag, .-MVC_GetReRangeFlag
	.align	3
.LC91:
	.xword	.LC90
	.align	3
.LC93:
	.xword	.LC92
	.align	3
.LC94:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecPOC
	.type	MVC_DecPOC, %function
MVC_DecPOC:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x2, [x19, 248]
	mov	w4, 1
	add	x0, x19, 11116544
	ldr	w3, [x2, 2900]
	ldr	w1, [x2, 2896]
	cmp	w3, w4
	ldrb	w5, [x0, 2843]
	add	w1, w1, 4
	lsl	w1, w4, w1
	beq	.L1371
	cbz	w3, .L1372
	cmp	w3, 2
	bne	.L1369
	cmp	w5, 5
	beq	.L1426
	ldrsb	w2, [x0, 1704]
	cbz	w2, .L1405
	ldr	w3, [x0, 1760]
	mov	w2, 0
	mov	w1, 0
	str	wzr, [x0, 1756]
	str	wzr, [x0, 1768]
.L1406:
	str	w1, [x0, 1764]
.L1408:
	ldrb	w4, [x0, 2848]
	add	w1, w3, w1
	str	w1, [x0, 1752]
	lsl	w1, w1, 1
	cbnz	w4, .L1409
	sub	w1, w1, #1
	str	w1, [x0, 1740]
.L1410:
	ldrb	w3, [x0, 2841]
	cbnz	w3, .L1411
	str	w1, [x0, 1728]
	str	w1, [x0, 1732]
	str	w1, [x0, 1736]
.L1404:
	ldr	w1, [x0, 1760]
	str	w1, [x0, 1756]
	str	w2, [x0, 1768]
.L1369:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1372:
	ldr	w1, [x2, 2904]
	cmp	w5, 5
	add	w1, w1, 4
	lsl	w4, w4, w1
	beq	.L1378
	ldrsb	w1, [x0, 1704]
	cbnz	w1, .L1376
	ldr	w5, [x0, 1716]
	ldr	w3, [x0, 1720]
	mov	w2, w5
.L1377:
	ldr	w1, [x0, 1708]
	cmp	w1, w3
	bcs	.L1375
	sub	w6, w3, w1
	cmp	w6, w4, lsr 1
	bcc	.L1375
	add	w2, w2, w4
	str	w2, [x0, 1724]
.L1379:
	ldrb	w3, [x0, 2841]
	cbnz	w3, .L1381
.L1429:
	ldr	w3, [x0, 1712]
	add	w1, w1, w2
	str	w1, [x0, 1728]
	add	w2, w1, w3
	str	w2, [x0, 1732]
	cmp	w1, w2
	csel	w1, w1, w2, le
	str	w1, [x0, 1740]
.L1382:
	ldr	w3, [x0, 1756]
	ldr	w2, [x0, 1760]
	str	w1, [x0, 1736]
	cmp	w2, w3
	beq	.L1384
	str	w2, [x0, 1756]
.L1384:
	ldrb	w1, [x0, 2848]
	cbz	w1, .L1369
	ldr	w2, [x0, 1708]
	ldr	w1, [x0, 1724]
	str	w1, [x0, 1716]
	str	w2, [x0, 1720]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1371:
	cmp	w5, 5
	beq	.L1427
	ldrsb	w3, [x0, 1704]
	cbz	w3, .L1387
	mov	w1, 0
	str	wzr, [x0, 1756]
	str	wzr, [x0, 1768]
.L1388:
	str	w1, [x0, 1764]
.L1386:
	ldr	w1, [x2, 2916]
	cbz	w1, .L1390
	ldr	w1, [x0, 1760]
	ldr	w5, [x0, 1764]
	ldrb	w6, [x0, 2848]
	add	w5, w5, w1
	str	w5, [x0, 1752]
	cbnz	w6, .L1392
	cbz	w5, .L1393
	sub	w5, w5, #1
	str	w5, [x0, 1752]
.L1392:
	str	wzr, [x0, 1784]
	ldr	w1, [x2, 2916]
	cmp	w1, wzr
	ble	.L1394
.L1413:
	mov	w4, 0
	mov	w3, 0
	.p2align 2
.L1395:
	add	x1, x2, x3, sxtw 2
	add	w3, w3, 1
	ldr	w1, [x1, 2920]
	add	w4, w4, w1
	str	w4, [x0, 1784]
	ldr	w1, [x2, 2916]
	cmp	w1, w3
	bgt	.L1395
.L1394:
	cbz	w5, .L1396
	sub	w5, w5, #1
	ldr	w7, [x0, 1784]
	udiv	w1, w5, w1
	str	w1, [x0, 1776]
	ldr	w4, [x2, 2916]
	udiv	w3, w5, w4
	mul	w1, w1, w7
	str	w1, [x0, 1780]
	msub	w5, w3, w4, w5
	str	w5, [x0, 1772]
	tbnz	w5, #31, .L1397
	mov	w3, 0
	.p2align 2
.L1398:
	add	x4, x2, x3, sxtw 2
	add	w3, w3, 1
	cmp	w5, w3
	ldr	w4, [x4, 2920]
	add	w1, w1, w4
	str	w1, [x0, 1780]
	bge	.L1398
.L1397:
	cbnz	w6, .L1399
	ldr	w3, [x2, 2908]
	add	w1, w1, w3
	str	w1, [x0, 1780]
.L1399:
	ldrb	w3, [x0, 2841]
	cbnz	w3, .L1400
	ldr	w3, [x0, 1744]
	ldr	w4, [x0, 1748]
	add	w1, w1, w3
	str	w1, [x0, 1728]
	ldr	w2, [x2, 2912]
	add	w2, w1, w2
	add	w2, w2, w4
	str	w2, [x0, 1732]
	cmp	w1, w2
	csel	w1, w1, w2, le
	str	w1, [x0, 1740]
.L1401:
	ldr	w3, [x0, 1760]
	ldr	w2, [x0, 1764]
	str	w1, [x0, 1736]
	str	w3, [x0, 1756]
	str	w2, [x0, 1768]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1376:
	ldrsb	w1, [x0, 1705]
	cbz	w1, .L1428
.L1378:
	ldr	w1, [x0, 1708]
	mov	w2, 0
	mov	w5, 0
	str	wzr, [x0, 1716]
	str	wzr, [x0, 1720]
.L1375:
	cmp	w1, w3
	bls	.L1380
	sub	w3, w1, w3
	cmp	w3, w4, lsr 1
	bls	.L1380
	sub	w2, w2, w4
	str	w2, [x0, 1724]
	b	.L1379
	.p2align 3
.L1426:
	add	x1, x0, 1536
	mov	w2, 0
	stp	wzr, wzr, [x1, 192]
	stp	wzr, wzr, [x1, 200]
	str	wzr, [x0, 1764]
	b	.L1404
	.p2align 3
.L1427:
	str	wzr, [x0, 1764]
	b	.L1386
	.p2align 3
.L1380:
	ldrb	w3, [x0, 2841]
	str	w5, [x0, 1724]
	cbz	w3, .L1429
.L1381:
	ldrb	w3, [x0, 2842]
	add	w1, w1, w2
	cbnz	w3, .L1383
	str	w1, [x0, 1728]
	str	w1, [x0, 1740]
	b	.L1382
	.p2align 3
.L1390:
	ldrb	w6, [x0, 2848]
	str	wzr, [x0, 1752]
.L1393:
	str	wzr, [x0, 1784]
	mov	w5, 0
	ldr	w1, [x2, 2916]
	cmp	w1, wzr
	bgt	.L1413
	.p2align 2
.L1396:
	mov	w1, 0
	str	wzr, [x0, 1780]
	b	.L1397
	.p2align 3
.L1400:
	ldrb	w3, [x0, 2842]
	cbnz	w3, .L1402
	ldr	w2, [x0, 1744]
	add	w1, w1, w2
	str	w1, [x0, 1728]
	str	w1, [x0, 1740]
	b	.L1401
	.p2align 3
.L1405:
	ldr	w2, [x0, 1756]
	ldr	w3, [x0, 1760]
	cmp	w3, w2
	ldr	w2, [x0, 1768]
	bcs	.L1407
	add	w1, w1, w2
	str	w1, [x0, 1764]
	mov	w2, w1
	b	.L1408
	.p2align 3
.L1387:
	ldr	w3, [x0, 1756]
	ldr	w4, [x0, 1760]
	cmp	w4, w3
	bcs	.L1389
	ldr	w3, [x0, 1768]
	add	w1, w3, w1
	str	w1, [x0, 1764]
	b	.L1386
	.p2align 3
.L1411:
	ldrb	w3, [x0, 2842]
	str	w1, [x0, 1736]
	cbnz	w3, .L1412
	str	w1, [x0, 1728]
	b	.L1404
	.p2align 3
.L1409:
	str	w1, [x0, 1740]
	b	.L1410
	.p2align 3
.L1383:
	str	w1, [x0, 1732]
	str	w1, [x0, 1740]
	b	.L1382
	.p2align 3
.L1402:
	ldr	w3, [x2, 2912]
	ldr	w2, [x0, 1744]
	add	w1, w1, w3
	add	w1, w1, w2
	str	w1, [x0, 1732]
	str	w1, [x0, 1740]
	b	.L1401
	.p2align 3
.L1428:
	ldr	w3, [x0, 1728]
	mov	w2, 0
	mov	w5, 0
	str	wzr, [x0, 1716]
	str	w3, [x0, 1720]
	b	.L1377
	.p2align 3
.L1412:
	str	w1, [x0, 1732]
	b	.L1404
.L1389:
	ldr	w1, [x0, 1768]
	b	.L1388
.L1407:
	mov	w1, w2
	b	.L1406
	.size	MVC_DecPOC, .-MVC_DecPOC
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_CalcPicNum
	.type	MVC_CalcPicNum, %function
MVC_CalcPicNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x8, x19, 11157504
	ldr	x0, [x19, 248]
	mov	w9, 1
	add	x1, x19, 11124736
	ldr	w0, [x0, 2896]
	ldrb	w2, [x8, 2315]
	add	w0, w0, 4
	lsl	w9, w9, w0
	cbz	w2, .L1431
	ldr	w0, [x1, 800]
	cmp	w2, 1
	cset	w6, eq
	cmp	w2, 2
	cset	w7, eq
	mov	w2, 0
	cbz	w0, .L1451
	.p2align 2
.L1468:
	add	x0, x19, x2, uxtw 3
	add	x0, x0, 11124736
	ldr	x3, [x0, 536]
	ldrb	w4, [x3, 3]
	cbz	w4, .L1445
	ldr	w4, [x3, 20]
	ldr	w5, [x8, 2976]
	cmp	w4, w5
	bls	.L1446
	sub	w4, w4, w9
	str	w4, [x3, 24]
.L1447:
	ldr	x3, [x0, 536]
	ldrb	w4, [x3, 3]
	tbz	x4, 0, .L1448
	ldr	w5, [x3, 752]
	and	w5, w5, 16776960
	cmp	w5, 65536
	beq	.L1478
.L1448:
	tbz	x4, 1, .L1445
	ldr	w0, [x3, 800]
	and	w0, w0, 16776960
	cmp	w0, 65536
	beq	.L1479
	.p2align 2
.L1445:
	ldr	w0, [x1, 800]
	add	w2, w2, 1
	cmp	w0, w2
	bhi	.L1468
.L1451:
	ldr	w0, [x1, 804]
	mov	w2, 0
	cbz	w0, .L1430
	.p2align 2
.L1467:
	add	x0, x19, x2, uxtw 3
	add	w2, w2, 1
	add	x0, x0, 11124736
	ldr	x4, [x0, 664]
	ldrb	w3, [x4, 3]
	cbz	w3, .L1453
	tbz	x3, 0, .L1454
	ldr	w5, [x4, 752]
	and	w5, w5, 16776960
	cmp	w5, 256
	beq	.L1480
.L1454:
	tbz	x3, 1, .L1453
	ldr	w0, [x4, 800]
	and	w0, w0, 16776960
	cmp	w0, 256
	beq	.L1481
	.p2align 2
.L1453:
	ldr	w0, [x1, 804]
	cmp	w0, w2
	bhi	.L1467
.L1430:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1446:
	str	w4, [x3, 24]
	b	.L1447
	.p2align 3
.L1431:
	ldr	w2, [x1, 800]
	mov	w0, 0
	cbnz	w2, .L1466
	.p2align 2
.L1441:
	ldr	w0, [x1, 804]
	mov	w2, 0
	cbz	w0, .L1430
	uxtw	x0, w2
	add	w2, w2, 1
	add	x0, x0, 1388544
	add	x0, x19, x0, lsl 3
	ldr	x0, [x0, 17048]
	ldrb	w3, [x0, 3]
	cmp	w3, 3
	beq	.L1482
	.p2align 2
.L1442:
	ldr	w0, [x1, 804]
	cmp	w0, w2
	bls	.L1430
	uxtw	x0, w2
	add	w2, w2, 1
	add	x0, x0, 1388544
	add	x0, x19, x0, lsl 3
	ldr	x0, [x0, 17048]
	ldrb	w3, [x0, 3]
	cmp	w3, 3
	bne	.L1442
.L1482:
	ldr	w3, [x0, 704]
	and	w3, w3, 16776960
	cmp	w3, 256
	bne	.L1442
	ldr	w3, [x0, 28]
	str	w3, [x0, 720]
	b	.L1442
	.p2align 3
.L1484:
	ldr	w4, [x3, 704]
	and	w4, w4, 16776960
	cmp	w4, 65536
	bne	.L1437
	ldr	w4, [x3, 20]
	ldr	w5, [x8, 2976]
	cmp	w4, w5
	sub	w5, w4, w9
	bhi	.L1483
	str	w4, [x3, 24]
.L1439:
	ldr	x2, [x2, 536]
	ldr	w3, [x2, 24]
	str	w3, [x2, 724]
	.p2align 2
.L1437:
	ldr	w2, [x1, 800]
	add	w0, w0, 1
	cmp	w2, w0
	bls	.L1441
.L1466:
	add	x2, x19, x0, uxtw 3
	add	x2, x2, 11124736
	ldr	x3, [x2, 536]
	ldrb	w4, [x3, 3]
	cmp	w4, 3
	bne	.L1437
	b	.L1484
	.p2align 3
.L1480:
	ldr	w3, [x4, 28]
	add	w3, w6, w3, lsl 1
	str	w3, [x4, 768]
	ldr	x4, [x0, 664]
	ldrb	w3, [x4, 3]
	b	.L1454
	.p2align 3
.L1478:
	ldr	w4, [x3, 24]
	add	w4, w6, w4, lsl 1
	str	w4, [x3, 772]
	ldr	x3, [x0, 536]
	ldrb	w4, [x3, 3]
	b	.L1448
	.p2align 3
.L1481:
	ldr	w0, [x4, 28]
	add	w0, w7, w0, lsl 1
	str	w0, [x4, 816]
	b	.L1453
	.p2align 3
.L1479:
	ldr	w0, [x3, 24]
	add	w0, w7, w0, lsl 1
	str	w0, [x3, 820]
	b	.L1445
	.p2align 3
.L1483:
	str	w5, [x3, 24]
	b	.L1439
	.size	MVC_CalcPicNum, .-MVC_CalcPicNum
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_IsOutDPB
	.type	MVC_IsOutDPB, %function
MVC_IsOutDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L1490
	add	x2, x20, 11124736
	ldr	w0, [x2, 792]
	cbz	w0, .L1490
	ldr	x1, [x2, 408]
	cmp	x19, x1
	ccmp	x1, xzr, 4, eq
	bne	.L1492
	sub	w0, w0, #1
	add	x2, x2, 416
	add	x0, x0, 1388544
	add	x0, x0, 2100
	add	x0, x20, x0, lsl 3
	b	.L1487
	.p2align 3
.L1488:
	ldr	x3, [x2], 8
	cmp	x19, x3
	ccmp	x3, xzr, 4, eq
	bne	.L1492
.L1487:
	cmp	x2, x0
	bne	.L1488
.L1490:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1492:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_IsOutDPB, .-MVC_IsOutDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_combine_scalinglist
	.type	mvc_combine_scalinglist, %function
mvc_combine_scalinglist:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w19, w2
	mov	x20, x1
	bl	_mcount
	cmp	w19, wzr
	ble	.L1493
	ldr	x1, .LC97
	mov	x5, 0
	mov	w2, 255
	b	.L1497
	.p2align 3
.L1495:
	ldrb	w3, [x5, x0]
.L1496:
	lsr	w6, w3, 2
	ldr	w4, [x21, w3, uxtw 2]
	ubfiz	w7, w3, 3, 2
	add	x5, x5, 1
	lsl	w3, w2, w7
	and	w4, w4, 255
	ldr	w0, [x20, w6, uxtw 2]
	lsl	w4, w4, w7
	cmp	w19, w5
	bic	w0, w0, w3
	orr	w0, w4, w0
	str	w0, [x20, w6, uxtw 2]
	ble	.L1493
.L1497:
	cmp	w19, 16
	add	x0, x1, 16
	bne	.L1495
	ldrb	w3, [x1, x5]
	b	.L1496
	.p2align 3
.L1493:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	mvc_combine_scalinglist, .-mvc_combine_scalinglist
	.align	3
.LC97:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_assign_quant_params
	.type	mvc_assign_quant_params, %function
mvc_assign_quant_params:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cbz	x20, .L1531
	cbz	x19, .L1532
	ldrb	w0, [x19, 18]
	cbz	w0, .L1520
	ldr	x21, .LC102
	add	x0, x19, 2016
	ldr	x22, .LC99
	add	x24, x19, 5
	mov	x26, x0
	add	x25, x19, 1984
	mov	w27, 1
	mov	w28, 0
	mov	x23, x21
	str	x0, [x29, 104]
	b	.L1505
	.p2align 3
.L1535:
	cbz	w28, .L1533
	cmp	w28, 3
	beq	.L1534
	ldr	x8, .LC102
	sub	w1, w28, #1
	add	x1, x1, 126
	mov	x2, 16
	mov	x0, x26
	ldr	x8, [x8, 104]
	add	x1, x19, x1, lsl 4
	blr	x8
.L1513:
	cmp	w27, 7
	bhi	.L1520
.L1519:
	add	w28, w28, 1
	add	w27, w27, 1
	add	x24, x24, 1
	add	x26, x26, 16
	add	x25, x25, 4
.L1505:
	cmp	w28, 5
	ldrsb	w0, [x24]
	bhi	.L1506
	cbz	w0, .L1535
	ldr	w0, [x25]
	cbz	w0, .L1513
	cmp	w28, 2
	ldr	x1, .LC99
	ldr	x8, [x23, 104]
	bls	.L1514
	add	x1, x1, 16
.L1514:
	mov	x2, 16
	mov	x0, x26
	blr	x8
	cmp	w27, 7
	bls	.L1519
	.p2align 2
.L1520:
	mov	w0, 0
.L1502:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1506:
	cbnz	w0, .L1515
	ldrb	w0, [x20, 27]
	cbnz	w0, .L1516
	ldr	x1, .LC102
	sub	w0, w28, #6
	add	x0, x0, 33
	cmp	w28, 6
	ldr	x8, [x1, 104]
	add	x0, x19, x0, lsl 6
	ldr	x1, .LC99
	beq	.L1530
	add	x1, x1, 96
.L1518:
	mov	x2, 64
	blr	x8
	b	.L1513
	.p2align 3
.L1515:
	sub	w0, w28, #6
	add	x1, x19, x0, lsl 2
	ldr	w1, [x1, 2008]
	cbz	w1, .L1513
	add	x0, x0, 33
	cmp	w28, 6
	ldr	x8, [x21, 104]
	add	x0, x19, x0, lsl 6
	beq	.L1523
	add	x1, x22, 96
	b	.L1518
	.p2align 3
.L1516:
	ldr	x0, .LC102
	sub	w1, w28, #6
	mov	x2, 64
	ldr	x8, [x0, 104]
	add	x0, x1, 33
	add	x1, x20, x1, lsl 6
	add	x1, x1, 2768
	add	x0, x19, x0, lsl 6
	blr	x8
	b	.L1513
.L1531:
	ldr	x2, .LC100
	mov	w3, 6887
	ldr	x1, .LC101
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1502
.L1532:
	ldr	x2, .LC100
	mov	w3, 6888
	ldr	x1, .LC101
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1502
.L1533:
	ldrb	w0, [x20, 27]
	cbnz	w0, .L1509
	ldr	x0, .LC102
	mov	x2, 16
	ldr	x1, .LC99
	ldr	x8, [x0, 104]
	ldr	x0, [x29, 104]
	blr	x8
	b	.L1519
.L1534:
	ldrb	w0, [x20, 27]
	cbnz	w0, .L1512
	ldr	x0, .LC102
	mov	x2, 16
	ldr	x1, .LC103
	ldr	x8, [x0, 104]
	add	x0, x19, 2064
	blr	x8
	b	.L1519
.L1509:
	ldr	x0, .LC102
	mov	x2, 16
	add	x1, x20, 2672
	ldr	x8, [x0, 104]
	ldr	x0, [x29, 104]
	blr	x8
	b	.L1519
.L1512:
	ldr	x0, .LC102
	mov	x2, 16
	add	x1, x20, 2720
	ldr	x8, [x0, 104]
	add	x0, x19, 2064
	blr	x8
	b	.L1519
.L1523:
	ldr	x1, .LC99
.L1530:
	add	x1, x1, 32
	b	.L1518
	.size	mvc_assign_quant_params, .-mvc_assign_quant_params
	.align	3
.LC99:
	.xword	.LANCHOR1
	.align	3
.LC100:
	.xword	.LC36
	.align	3
.LC101:
	.xword	.LC38
	.align	3
.LC102:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC103:
	.xword	.LANCHOR1+16
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_WriteCurrPicYUV
	.type	MVC_WriteCurrPicYUV, %function
MVC_WriteCurrPicYUV:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 11157504
	bl	_mcount
	ldr	x1, .LC105
	mov	w0, 2
	ldr	x3, [x19, 2960]
	ldrb	w20, [x19, 2315]
	ldr	w3, [x3, 220]
	mov	w2, w20
	bl	dprint_vfmw
	cmp	w20, 3
	ldr	w3, [x19, 3024]
	ccmp	w20, wzr, 4, ne
	ldr	w4, [x19, 3028]
	cset	w0, eq
	ldr	x1, .LC107
	cmp	w0, wzr
	mov	w2, 1
	csinc	w2, w2, w20, ne
	mov	w0, 22
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_WriteCurrPicYUV, .-MVC_WriteCurrPicYUV
	.align	3
.LC105:
	.xword	.LC104
	.align	3
.LC107:
	.xword	.LC106
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_WritePicMsg
	.type	MVC_WritePicMsg, %function
MVC_WritePicMsg:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	add	x23, x20, 11157504
	add	x19, x20, 11161600
	bl	_mcount
	add	x22, x20, 11108352
	ldr	x1, .LC109
	mov	w0, 2
	ldrb	w3, [x23, 2315]
	add	x25, x20, 11112448
	ldr	w4, [x23, 2476]
	ldr	w2, [x23, 2984]
	ldr	w5, [x23, 3044]
	bl	dprint_vfmw
	str	wzr, [x20, 64]
	add	x0, x20, 11116544
	ldr	x1, [x23, 2912]
	str	x1, [x19, 848]
	ldr	x1, [x20, 864]
	str	x1, [x19, 1768]
	ldr	w1, [x23, 2440]
	str	w1, [x19, 1544]
	ldr	w1, [x23, 2444]
	str	w1, [x19, 1548]
	ldr	w1, [x23, 2464]
	str	w1, [x19, 1552]
	ldr	w1, [x23, 2468]
	str	w1, [x19, 1556]
	ldr	w1, [x23, 2984]
	str	w1, [x19, 856]
	ldrb	w1, [x23, 2315]
	strb	w1, [x19, 824]
	ldr	x1, [x20, 248]
	ldrb	w2, [x1, 21]
	str	w2, [x19, 872]
	ldr	w2, [x23, 3028]
	str	w2, [x19, 860]
	ldr	w2, [x23, 3032]
	str	w2, [x19, 864]
	ldr	w2, [x1, 3948]
	add	w2, w2, 1
	str	w2, [x19, 868]
	ldrb	w2, [x22, 3684]
	strb	w2, [x19, 827]
	ldr	w2, [x25, 3620]
	str	w2, [x19, 876]
	ldrb	w2, [x25, 3560]
	str	w2, [x19, 880]
	ldr	w1, [x1, 748]
	strb	w1, [x19, 825]
	ldrb	w1, [x25, 3564]
	str	w1, [x19, 884]
	ldr	w1, [x0, 1740]
	str	w1, [x19, 888]
	ldr	w1, [x0, 1728]
	str	w1, [x19, 892]
	ldr	w0, [x0, 1732]
	str	w0, [x19, 896]
	ldr	x1, [x23, 2960]
	ldr	w0, [x20, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_GetLogicFs
	mov	x24, x0
	cbz	x0, .L1573
	ldp	x2, x3, [x0, 32]
	cbz	x2, .L1543
	cbz	x3, .L1543
	ldr	w0, [x20, 120]
	add	x3, x19, 1276
	add	x2, x19, 1148
	add	x1, x19, 1404
	add	x21, x20, 11124736
	bl	FSP_GetDecFsAddrTab
	ldr	x0, [x24, 32]
	add	x2, x19, 1408
	add	x1, x19, 1536
	ldr	w0, [x0, 4]
	str	w0, [x19, 1132]
	ldr	w0, [x20, 120]
	bl	FSP_GetPmvAddrTab
	ldr	w0, [x23, 3044]
	str	w0, [x19, 1140]
	ldr	w0, [x24, 12]
	str	w0, [x19, 1540]
	ldr	x0, [x24, 40]
	ldr	w0, [x0, 8]
	str	w0, [x19, 1136]
	ldr	x0, [x24, 40]
	ldr	w0, [x0, 60]
	str	w0, [x19, 1144]
	ldr	w4, [x21, 1024]
	str	w4, [x19, 1760]
	cbz	w4, .L1549
	sub	w3, w4, #1
	add	x0, x21, 832
	add	x3, x3, 2781184
	add	x1, x19, 1568
	add	x3, x3, 209
	add	x3, x20, x3, lsl 2
	.p2align 2
.L1548:
	ldr	w2, [x0]
	add	x0, x0, 4
	str	w2, [x1]
	add	x1, x1, 4
	cmp	x3, x0
	ldr	w2, [x0, 60]
	str	w2, [x1, 60]
	ldr	w2, [x0, 124]
	str	w2, [x1, 124]
	bne	.L1548
.L1549:
	ldrb	w0, [x22, 3691]
	cbnz	w0, .L1574
	ldrb	w0, [x25, 3578]
	cbnz	w0, .L1550
	ldr	x9, .LC114
	add	x5, x19, 900
	mov	w1, 0
	.p2align 2
.L1551:
	and	w2, w1, 3
	add	x0, x9, 352
	add	w1, w1, 1
	cmp	w1, 24
	ldr	w0, [x0, w2, uxtw 2]
	ubfx	x3, x0, 8, 8
	lsr	w2, w0, 16
	ubfiz	w2, w2, 8, 8
	and	w0, w0, -16776961
	orr	w2, w2, w3, lsl 16
	orr	w0, w2, w0
	str	w0, [x5], 4
	bne	.L1551
	add	x19, x19, 996
	mov	w5, 0
	.p2align 2
.L1552:
	add	w0, w5, 1
	and	w2, w5, 14
	add	x1, x9, 368
	and	w0, w0, 15
	add	x19, x19, 8
	add	w5, w5, 2
	cmp	w5, 32
	ldr	w0, [x1, w0, uxtw 2]
	ldr	w1, [x1, w2, uxtw 2]
	lsr	w7, w0, 16
	ubfx	x2, x0, 8, 8
	lsr	w3, w1, 16
	lsr	w6, w1, 24
	ubfiz	w10, w0, 16, 8
	ubfiz	w8, w3, 8, 8
	and	w0, w0, -16777216
	and	w3, w1, 255
	ubfx	x1, x1, 8, 8
	orr	w0, w0, w2, lsl 16
	orr	w7, w10, w7, lsl 24
	orr	w3, w8, w3
	orr	w1, w1, w6, lsl 8
	orr	w2, w7, w3
	orr	w0, w1, w0
	stp	w2, w0, [x19, -8]
	bne	.L1552
.L1558:
	mov	w22, 0
	cbz	w4, .L1554
	.p2align 2
.L1562:
	add	x19, x20, x22, uxtw 2
	ldr	w0, [x20, 120]
	add	x23, x19, 11124736
	mov	w1, 0
	add	x19, x19, 11161600
	add	w22, w22, 1
	ldr	w2, [x23, 832]
	bl	FSP_GetStoreType
	cmp	w0, wzr
	cset	w0, ne
	str	w0, [x19, 1880]
	ldr	w0, [x23, 832]
	str	w0, [x19, 1944]
	ldr	w0, [x21, 1024]
	cmp	w0, w22
	bhi	.L1562
.L1554:
	mov	w0, 0
.L1541:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1574:
	ldrb	w0, [x25, 3578]
.L1550:
	cmp	w0, 1
	add	x5, x19, 900
	mov	w1, 0
	beq	.L1556
	.p2align 2
.L1559:
	uxtw	x0, w1
	add	w1, w1, 1
	add	x0, x0, 2777088
	cmp	w1, 24
	add	x0, x0, 1584
	ldr	w0, [x20, x0, lsl 2]
	ubfx	x3, x0, 8, 8
	lsr	w2, w0, 16
	ubfiz	w2, w2, 8, 8
	and	w0, w0, -16776961
	orr	w2, w2, w3, lsl 16
	orr	w0, w2, w0
	str	w0, [x5], 4
	bne	.L1559
	add	x19, x19, 996
	mov	w9, 1
	mov	w5, 0
	.p2align 2
.L1560:
	ubfx	x1, x5, 3, 29
	ubfiz	x0, x5, 1, 3
	and	x2, x9, 15
	lsl	x1, x1, 4
	add	x2, x1, x2
	add	x1, x1, x0
	add	x1, x1, 2777088
	add	x0, x2, 2777088
	add	x0, x0, 1608
	add	x1, x1, 1608
	add	x19, x19, 8
	add	w5, w5, 1
	cmp	w5, 16
	add	w9, w9, 2
	ldr	w0, [x20, x0, lsl 2]
	ldr	w1, [x20, x1, lsl 2]
	lsr	w3, w0, 16
	ubfx	x7, x0, 8, 8
	lsr	w8, w1, 16
	lsr	w6, w1, 24
	ubfiz	w10, w8, 8, 8
	ubfiz	w11, w0, 16, 8
	and	w8, w1, 255
	ubfx	x2, x1, 8, 8
	lsl	w6, w6, 8
	and	w1, w0, -16777216
	orr	w0, w2, w1
	orr	w8, w10, w8
	orr	w3, w11, w3, lsl 24
	orr	w6, w6, w7, lsl 16
	orr	w1, w8, w3
	orr	w0, w6, w0
	stp	w1, w0, [x19, -8]
	bne	.L1560
	b	.L1558
	.p2align 3
.L1556:
	uxtw	x0, w1
	add	w1, w1, 1
	add	x0, x0, 2777088
	cmp	w1, 24
	add	x0, x20, x0, lsl 2
	ldr	w0, [x0, 9672]
	ubfx	x3, x0, 8, 8
	lsr	w2, w0, 16
	ubfiz	w2, w2, 8, 8
	and	w0, w0, -16776961
	orr	w2, w2, w3, lsl 16
	orr	w0, w2, w0
	str	w0, [x5], 4
	bne	.L1556
	add	x19, x19, 996
	mov	w9, 1
	mov	w5, 0
	.p2align 2
.L1557:
	ubfx	x1, x5, 3, 29
	ubfiz	x0, x5, 1, 3
	and	x2, x9, 15
	lsl	x1, x1, 4
	add	x2, x1, x2
	add	x1, x1, x0
	add	x1, x1, 2777088
	add	x0, x2, 2777088
	add	x19, x19, 8
	add	w5, w5, 1
	add	x0, x20, x0, lsl 2
	add	x1, x20, x1, lsl 2
	cmp	w5, 16
	add	w9, w9, 2
	ldr	w0, [x0, 9768]
	ldr	w1, [x1, 9768]
	lsr	w8, w0, 16
	ubfx	x7, x0, 8, 8
	lsr	w3, w1, 16
	lsr	w6, w1, 24
	ubfiz	w11, w0, 16, 8
	ubfiz	w10, w3, 8, 8
	ubfx	x2, x1, 8, 8
	and	w3, w1, 255
	lsl	w6, w6, 8
	and	w1, w0, -16777216
	orr	w0, w2, w1
	orr	w8, w11, w8, lsl 24
	orr	w3, w10, w3
	orr	w6, w6, w7, lsl 16
	orr	w1, w8, w3
	orr	w0, w6, w0
	stp	w1, w0, [x19, -8]
	bne	.L1557
	b	.L1558
.L1543:
	ldr	x1, .LC113
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1541
.L1573:
	ldr	x2, [x23, 2960]
	mov	w0, 0
	ldr	x1, .LC111
	ldrsb	w2, [x2, 6]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1541
	.size	MVC_WritePicMsg, .-MVC_WritePicMsg
	.align	3
.LC109:
	.xword	.LC108
	.align	3
.LC111:
	.xword	.LC110
	.align	3
.LC113:
	.xword	.LC112
	.align	3
.LC114:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_UpdatePicQpInf
	.type	MVC_UpdatePicQpInf, %function
MVC_UpdatePicQpInf:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	ldp	w1, w0, [x19, 36]
	cmp	w1, w20
	csel	w1, w1, w20, ge
	cmp	w0, w20
	csel	w0, w0, w20, le
	stp	w1, w0, [x19, 36]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_UpdatePicQpInf, .-MVC_UpdatePicQpInf
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_WriteSliceMsg
	.type	MVC_WriteSliceMsg, %function
MVC_WriteSliceMsg:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w5, [x19, 64]
	ldr	w1, [x19, 32]
	add	w0, w5, 1
	ldr	x6, [x19, 864]
	uxtw	x21, w5
	sub	w1, w1, #1
	lsl	x4, x21, 7
	cmp	w5, w1
	sub	x4, x4, x21
	str	w0, [x19, 64]
	lsl	x4, x4, 5
	add	x22, x6, x4
	bcs	.L1577
	lsl	x1, x0, 7
	sub	x0, x1, x0
	add	x0, x6, x0, lsl 5
	str	x0, [x22, 4056]
.L1578:
	ldr	x3, [x19, 240]
	ldrb	w2, [x3]
	ldr	w0, [x3, 76]
	cmp	w2, 1
	ccmp	w2, w0, 2, ls
	bcs	.L1579
	.p2align 2
.L1580:
	uxtw	x0, w2
	add	w2, w2, 1
	lsl	x1, x0, 5
	add	x3, x3, x1
	add	x0, x22, x0, lsl 2
	ldr	w3, [x3, 28]
	str	w3, [x0, 16]
	ldr	x3, [x19, 240]
	add	x3, x3, x1
	ldr	w3, [x3, 24]
	str	w3, [x0, 8]
	ldr	x3, [x19, 240]
	add	x1, x3, x1
	ldr	w1, [x1, 32]
	str	w1, [x0, 24]
	ldr	x3, [x19, 240]
	ldr	w0, [x3, 76]
	cmp	w0, w2
	ccmp	w2, 1, 2, hi
	bls	.L1580
.L1579:
	cmp	w0, 1
	bhi	.L1585
	.p2align 2
.L1656:
	add	x1, x22, x0, uxtw 2
	add	w0, w0, 1
	cmp	w0, 2
	str	wzr, [x1, 8]
	str	wzr, [x1, 16]
	str	wzr, [x1, 24]
	bne	.L1656
.L1585:
	add	x20, x19, 11157504
	add	x23, x19, 11112448
	add	x1, x19, 11120640
	ldrb	w0, [x20, 2321]
	strb	w0, [x22, 1]
	ldr	w0, [x23, 3608]
	add	w2, w0, 26
	ldr	w0, [x1, 360]
	add	w0, w2, w0
	str	w0, [x22, 32]
	cbnz	w5, .L1681
	ldr	x2, [x20, 2960]
	str	w0, [x2, 740]
	ldr	x0, [x20, 2960]
	ldr	w2, [x22, 32]
	str	w2, [x0, 744]
.L1586:
	ldr	w0, [x1, 356]
	add	x27, x19, 11116544
	str	w0, [x22, 36]
	ldr	w0, [x27, 2904]
	str	w0, [x22, 40]
	ldr	w0, [x27, 2900]
	str	w0, [x22, 44]
	ldrb	w0, [x27, 2840]
	strb	w0, [x6, x4]
	ldr	w0, [x27, 2896]
	str	w0, [x22, 48]
	ldrb	w0, [x27, 2846]
	strb	w0, [x22, 2]
	ldr	x0, [x19, 248]
	ldrb	w0, [x0, 22]
	strb	w0, [x22, 3]
	ldr	w0, [x27, 2888]
	str	w0, [x22, 52]
	ldr	w0, [x27, 2892]
	str	w0, [x22, 56]
	ldrb	w0, [x27, 2840]
	cmp	w0, 1
	beq	.L1682
	cbz	w0, .L1683
	strb	wzr, [x22, 4]
.L1588:
	ldr	w0, [x23, 3612]
	str	w0, [x22, 60]
	ldr	w0, [x23, 3616]
	str	w0, [x22, 64]
	ldr	w0, [x1, 368]
	str	w0, [x22, 68]
	ldr	w0, [x1, 372]
	str	w0, [x22, 72]
	ldr	w0, [x1, 364]
	str	w0, [x22, 76]
	ldrb	w0, [x27, 2840]
	cmp	w0, 2
	beq	.L1627
	ldr	w0, [x27, 2888]
	cbz	w0, .L1630
	ldr	x1, [x19, 288]
	ldr	x1, [x1, 8]
	ldrb	w2, [x1, 1]
	cbz	w2, .L1593
	sub	w3, w0, #1
	mov	x0, x19
	add	x3, x19, x3, lsl 3
	b	.L1595
	.p2align 3
.L1597:
	ldr	x1, [x0, 296]
	add	x0, x0, 8
	ldr	x1, [x1, 8]
	ldrb	w2, [x1, 1]
	cbz	w2, .L1593
.L1595:
	cmp	x3, x0
	bne	.L1597
.L1630:
	mov	w24, 0
.L1592:
	ldr	w0, [x27, 2892]
	cbz	w0, .L1631
	ldr	x1, [x19, 552]
	ldr	x1, [x1, 8]
	ldrb	w2, [x1, 1]
	cbz	w2, .L1599
	sub	w3, w0, #1
	mov	x0, x19
	add	x3, x19, x3, lsl 3
	b	.L1601
	.p2align 3
.L1603:
	ldr	x1, [x0, 560]
	add	x0, x0, 8
	ldr	x1, [x1, 8]
	ldrb	w2, [x1, 1]
	cbz	w2, .L1599
.L1601:
	cmp	x3, x0
	bne	.L1603
.L1631:
	mov	w25, 0
.L1598:
	ldrb	w0, [x20, 2315]
	cbz	w0, .L1604
	ldr	w0, [x27, 2888]
	mov	w28, 0
	cbnz	w0, .L1655
	b	.L1620
	.p2align 3
.L1685:
	cbz	x0, .L1637
	ldr	x0, [x0, 32]
	ldr	w1, [x0, 4]
.L1616:
	lsl	x0, x20, 5
	add	x0, x0, x20, lsl 2
	add	x0, x22, x0
	str	w1, [x0, 1640]
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 52]
	str	w1, [x0, 1644]
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 32]
	str	w1, [x0, 1632]
	ldr	x1, [x26, 288]
	ldrb	w1, [x1]
	strb	w1, [x0, 1624]
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldrb	w1, [x1, 704]
	strb	w1, [x0, 1626]
	ldr	x1, [x26, 288]
	ldrb	w1, [x1]
	cmp	w1, 1
	beq	.L1684
	strb	w1, [x0, 1630]
	add	w28, w28, 1
	ldr	x1, [x26, 288]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 1631]
	ldr	x1, [x26, 288]
	ldr	w1, [x1, 24]
	str	w1, [x0, 1656]
	ldr	w0, [x27, 2888]
	cmp	w0, w28
	bls	.L1620
.L1655:
	uxtw	x20, w28
	ldr	w0, [x19, 120]
	add	x26, x19, x20, lsl 3
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldrsb	w1, [x1, 6]
	bl	FSP_GetLogicFs
	ldr	x2, [x26, 288]
	lsl	x1, x20, 5
	add	x1, x1, x20, lsl 2
	add	x1, x22, x1
	ldr	x2, [x2, 8]
	ldr	w2, [x2, 48]
	str	w2, [x1, 1636]
	ldr	x2, [x26, 288]
	ldr	x2, [x2, 8]
	ldrb	w2, [x2, 2]
	strb	w2, [x1, 1625]
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldrb	w1, [x1, 1]
	cmp	w1, 1
	bne	.L1685
	mov	w1, w24
	b	.L1616
	.p2align 3
.L1577:
	str	xzr, [x22, 4056]
	b	.L1578
	.p2align 3
.L1681:
	ldr	x2, [x20, 2960]
	ldr	w3, [x2, 740]
	cmp	w3, w0
	csel	w3, w3, w0, ge
	str	w3, [x2, 740]
	ldr	w3, [x2, 744]
	cmp	w3, w0
	csel	w0, w3, w0, le
	str	w0, [x2, 744]
	b	.L1586
	.p2align 3
.L1683:
	ldrb	w0, [x23, 3562]
	strb	w0, [x22, 4]
	b	.L1588
	.p2align 3
.L1684:
	strb	w1, [x0, 1628]
	add	w28, w28, 1
	ldr	x1, [x26, 288]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 1629]
	ldr	x1, [x26, 288]
	ldr	w1, [x1, 24]
	str	w1, [x0, 1652]
	ldr	w0, [x27, 2888]
	cmp	w0, w28
	bhi	.L1655
.L1620:
	ldrb	w0, [x27, 2840]
	cmp	w0, 1
	beq	.L1686
.L1607:
	add	x1, x19, 11124736
	add	x0, x22, 3928
	add	x1, x1, 1032
	add	x3, x22, 4056
	.p2align 2
.L1613:
	ldr	w2, [x1], 4
	str	w2, [x0], 4
	cmp	x3, x0
	bne	.L1613
	add	x0, x19, 11161600
	ldrb	w1, [x23, 3562]
	str	w1, [x0, 1124]
	ldr	w2, [x23, 3604]
	str	w2, [x0, 1128]
	cbz	w1, .L1625
	ldrb	w0, [x27, 2840]
	cbnz	w0, .L1625
.L1626:
	ldr	w0, [x27, 2908]
	mov	w2, 0
	str	w0, [x22, 80]
	ldr	w0, [x27, 2912]
	str	w0, [x22, 84]
	.p2align 2
.L1628:
	ubfiz	x0, x2, 2, 32
	add	w2, w2, 1
	add	x1, x19, x0
	add	x0, x22, x0
	add	x1, x1, 11116544
	ldr	w3, [x1, 2916]
	str	w3, [x0, 88]
	ldr	w3, [x1, 3044]
	str	w3, [x0, 216]
	ldr	w3, [x1, 3172]
	str	w3, [x0, 344]
	ldr	w3, [x1, 3684]
	str	w3, [x0, 856]
	ldr	w3, [x1, 3812]
	str	w3, [x0, 984]
	ldr	w1, [x1, 3940]
	str	w1, [x0, 1112]
	ldr	w0, [x27, 2900]
	cmp	w0, w2
	bcs	.L1628
	ldrb	w0, [x27, 2840]
	cmp	w0, 1
	beq	.L1687
	.p2align 2
.L1627:
	add	x21, x21, 1392640
	ldr	x0, [x19, 240]
	add	x21, x19, x21, lsl 3
	str	x0, [x21, 20216]
	str	xzr, [x19, 240]
.L1576:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1637:
	mov	w1, 0
	b	.L1616
	.p2align 3
.L1593:
	ldrsb	w1, [x1, 6]
	ldr	w0, [x19, 120]
	bl	FSP_GetLogicFs
	cbz	x0, .L1688
	ldr	x0, [x0, 32]
	ldr	w24, [x0, 4]
	b	.L1592
	.p2align 3
.L1625:
	cmp	w2, 1
	bne	.L1627
	ldrb	w0, [x27, 2840]
	cmp	w0, 1
	bne	.L1627
	b	.L1626
	.p2align 3
.L1604:
	ldr	w0, [x27, 2888]
	mov	w28, 0
	cbnz	w0, .L1654
	b	.L1612
	.p2align 3
.L1689:
	cbz	x0, .L1633
	ldr	x0, [x0, 32]
	ldr	w1, [x0, 4]
.L1610:
	lsl	x0, x20, 5
	add	w28, w28, 1
	add	x0, x0, x20, lsl 2
	add	x0, x22, x0
	str	w1, [x0, 1640]
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 52]
	str	w1, [x0, 1644]
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 32]
	str	w1, [x0, 1632]
	ldr	x1, [x26, 288]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 1627]
	ldr	x1, [x26, 288]
	ldrb	w1, [x1]
	strb	w1, [x0, 1626]
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 728]
	str	w1, [x0, 1648]
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 776]
	str	w1, [x0, 1652]
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 824]
	str	w1, [x0, 1656]
	strb	wzr, [x0, 1624]
	ldr	w0, [x27, 2888]
	cmp	w0, w28
	bls	.L1612
.L1654:
	uxtw	x20, w28
	ldr	w0, [x19, 120]
	add	x26, x19, x20, lsl 3
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldrsb	w1, [x1, 6]
	bl	FSP_GetLogicFs
	ldr	x2, [x26, 288]
	lsl	x1, x20, 5
	add	x1, x1, x20, lsl 2
	add	x1, x22, x1
	ldr	x2, [x2, 8]
	ldr	w2, [x2, 48]
	str	w2, [x1, 1636]
	ldr	x2, [x26, 288]
	ldr	x2, [x2, 8]
	ldrb	w2, [x2, 2]
	strb	w2, [x1, 1625]
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldrb	w1, [x1, 1]
	cmp	w1, 1
	bne	.L1689
	mov	w1, w24
	b	.L1610
	.p2align 3
.L1633:
	mov	w1, 0
	b	.L1610
	.p2align 3
.L1612:
	ldrb	w0, [x27, 2840]
	cmp	w0, 1
	bne	.L1607
	ldr	w0, [x27, 2892]
	cbz	w0, .L1607
	mov	w26, 0
	b	.L1615
	.p2align 3
.L1690:
	cbz	x0, .L1635
	ldr	x0, [x0, 32]
	ldr	w1, [x0, 4]
.L1614:
	lsl	x0, x20, 5
	add	w26, w26, 1
	add	x0, x0, x20, lsl 2
	add	x0, x22, x0
	str	w1, [x0, 1640]
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 52]
	str	w1, [x0, 2796]
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 32]
	str	w1, [x0, 2784]
	ldr	x1, [x24, 552]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 2779]
	ldr	x1, [x24, 552]
	ldrb	w1, [x1]
	strb	w1, [x0, 2778]
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 728]
	str	w1, [x0, 2800]
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 776]
	str	w1, [x0, 2804]
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 824]
	str	w1, [x0, 2808]
	strb	wzr, [x0, 2776]
	ldr	w0, [x27, 2892]
	cmp	w0, w26
	bls	.L1607
.L1615:
	uxtw	x20, w26
	ldr	w0, [x19, 120]
	add	x24, x19, x20, lsl 3
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldrsb	w1, [x1, 6]
	bl	FSP_GetLogicFs
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldr	w2, [x1, 48]
	lsl	x1, x20, 5
	add	x1, x1, x20, lsl 2
	add	x1, x22, x1
	str	w2, [x1, 2788]
	ldr	x2, [x24, 552]
	ldr	x2, [x2, 8]
	ldrb	w2, [x2, 2]
	strb	w2, [x1, 2777]
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldrb	w1, [x1, 1]
	cmp	w1, 1
	bne	.L1690
	mov	w1, w25
	b	.L1614
	.p2align 3
.L1599:
	ldrsb	w1, [x1, 6]
	ldr	w0, [x19, 120]
	bl	FSP_GetLogicFs
	cbz	x0, .L1691
	ldr	x0, [x0, 32]
	ldr	w25, [x0, 4]
	b	.L1598
	.p2align 3
.L1682:
	ldr	w0, [x23, 3604]
	strb	w0, [x22, 4]
	b	.L1588
.L1687:
	mov	w3, 0
	.p2align 2
.L1629:
	ubfiz	x0, x3, 2, 32
	add	w3, w3, 1
	add	x1, x19, x0
	add	x0, x22, x0
	add	x2, x1, 11116544
	add	x1, x1, 11120640
	ldr	w4, [x2, 3300]
	str	w4, [x0, 472]
	ldr	w4, [x2, 3428]
	str	w4, [x0, 600]
	ldr	w4, [x2, 3556]
	str	w4, [x0, 728]
	ldr	w2, [x2, 4068]
	str	w2, [x0, 1240]
	ldr	w2, [x1, 100]
	str	w2, [x0, 1368]
	ldr	w1, [x1, 228]
	str	w1, [x0, 1496]
	ldr	w0, [x27, 2904]
	cmp	w0, w3
	bcs	.L1629
	b	.L1627
.L1635:
	mov	w1, 0
	b	.L1614
.L1686:
	ldr	w0, [x27, 2892]
	cbz	w0, .L1607
	mov	w26, 0
	b	.L1624
	.p2align 3
.L1693:
	cbz	x0, .L1639
	ldr	x0, [x0, 32]
	ldr	w1, [x0, 4]
.L1621:
	lsl	x0, x20, 5
	add	x0, x0, x20, lsl 2
	add	x0, x22, x0
	str	w1, [x0, 2792]
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 52]
	str	w1, [x0, 2796]
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 32]
	str	w1, [x0, 2784]
	ldr	x1, [x24, 552]
	ldrb	w1, [x1]
	strb	w1, [x0, 2776]
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldrb	w1, [x1, 704]
	strb	w1, [x0, 2778]
	ldr	x1, [x24, 552]
	ldrb	w1, [x1]
	cmp	w1, 1
	beq	.L1692
	strb	w1, [x0, 2782]
	ldr	x1, [x24, 552]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 2783]
	ldr	x1, [x24, 552]
	ldr	w1, [x1, 24]
	str	w1, [x0, 2808]
.L1623:
	ldr	w0, [x27, 2892]
	add	w26, w26, 1
	cmp	w0, w26
	bls	.L1607
.L1624:
	uxtw	x20, w26
	ldr	w0, [x19, 120]
	add	x24, x19, x20, lsl 3
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldrsb	w1, [x1, 6]
	bl	FSP_GetLogicFs
	ldr	x2, [x24, 552]
	lsl	x1, x20, 5
	add	x1, x1, x20, lsl 2
	add	x1, x22, x1
	ldr	x2, [x2, 8]
	ldr	w2, [x2, 48]
	str	w2, [x1, 2788]
	ldr	x2, [x24, 552]
	ldr	x2, [x2, 8]
	ldrb	w2, [x2, 2]
	strb	w2, [x1, 2777]
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldrb	w1, [x1, 1]
	cmp	w1, 1
	bne	.L1693
	mov	w1, w25
	b	.L1621
	.p2align 3
.L1692:
	strb	w1, [x0, 2780]
	ldr	x1, [x24, 552]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 2781]
	ldr	x1, [x24, 552]
	ldr	w1, [x1, 24]
	str	w1, [x0, 2804]
	b	.L1623
.L1639:
	mov	w1, 0
	b	.L1621
.L1688:
	ldr	x2, .LC117
	mov	w3, 7939
	ldr	x1, .LC119
	add	x2, x2, 80
	bl	dprint_vfmw
	b	.L1576
.L1691:
	ldr	x2, .LC117
	mov	w3, 7960
	ldr	x1, .LC119
	add	x2, x2, 80
	bl	dprint_vfmw
	b	.L1576
	.size	MVC_WriteSliceMsg, .-MVC_WriteSliceMsg
	.align	3
.LC117:
	.xword	.LANCHOR0
	.align	3
.LC119:
	.xword	.LC118
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_StopPicNum
	.type	MVC_StopPicNum, %function
MVC_StopPicNum:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	MVC_StopPicNum, .-MVC_StopPicNum
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetPicStreamSize
	.type	MVC_GetPicStreamSize, %function
MVC_GetPicStreamSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 11161600
	bl	_mcount
	mov	w0, 0
	ldr	x2, [x19, 1768]
	cbz	x2, .L1696
	.p2align 2
.L1697:
	ldp	w3, w1, [x2, 8]
	ldr	x2, [x2, 4056]
	add	w1, w3, w1
	add	w1, w1, 7
	add	w0, w0, w1, lsr 3
	cbnz	x2, .L1697
.L1696:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_GetPicStreamSize, .-MVC_GetPicStreamSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_SliceCheck
	.type	MVC_SliceCheck, %function
MVC_SliceCheck:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 11116544
	bl	_mcount
	ldr	x1, .LC121
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x21, 2896]
	ldrb	w1, [x19, 10]
	cbnz	w1, .L1710
	mov	w1, 262143
	cmp	w0, w1
	bhi	.L1711
	ldp	w1, w2, [x19, 12]
	mul	w1, w1, w2
	sub	w1, w1, #1
	cmp	w0, w1
	bhi	.L1710
	ldr	x1, .LC125
	mov	x0, x19
	bl	mvc_ue_v
	mov	w2, w0
	ldr	x1, .LC127
	mov	w20, w0
	mov	w0, 19
	bl	dprint_vfmw
	ldrb	w0, [x19, 10]
	cbnz	w0, .L1710
	cmp	w20, 9
	bls	.L1712
	ldr	x1, .LC130
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
.L1710:
	mov	w0, -1
.L1702:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1712:
	ldr	x0, .LC128
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx1707
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx1707:
	.section	.rodata
	.align	0
	.align	2
.L1707:
	.byte	(.L1706 - .Lrtx1707) / 4
	.byte	(.L1708 - .Lrtx1707) / 4
	.byte	(.L1709 - .Lrtx1707) / 4
	.byte	(.L1706 - .Lrtx1707) / 4
	.byte	(.L1709 - .Lrtx1707) / 4
	.byte	(.L1706 - .Lrtx1707) / 4
	.byte	(.L1708 - .Lrtx1707) / 4
	.byte	(.L1709 - .Lrtx1707) / 4
	.byte	(.L1706 - .Lrtx1707) / 4
	.byte	(.L1709 - .Lrtx1707) / 4
	.text
	.p2align 3
.L1706:
	strb	wzr, [x21, 2840]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1709:
	mov	w1, 2
	strb	w1, [x21, 2840]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1708:
	mov	w1, 1
	strb	w1, [x21, 2840]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1711:
	ldr	x1, .LC123
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1702
	.size	MVC_SliceCheck, .-MVC_SliceCheck
	.align	3
.LC121:
	.xword	.LC120
	.align	3
.LC123:
	.xword	.LC122
	.align	3
.LC125:
	.xword	.LC124
	.align	3
.LC127:
	.xword	.LC126
	.align	3
.LC128:
	.xword	.L1707
	.align	3
.LC130:
	.xword	.LC129
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_PPSSPSCheck
	.type	MVC_PPSSPSCheck, %function
MVC_PPSSPSCheck:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 11116544
	bl	_mcount
	ldr	x1, .LC132
	mov	w0, 19
	ldr	w2, [x19, 2856]
	bl	dprint_vfmw
	ldr	w2, [x19, 2856]
	mov	w0, 2240
	ldr	x3, [x20, 280]
	umull	x0, w2, w0
	add	x3, x3, x0
	ldrb	w0, [x3, 19]
	cbz	w0, .L1723
	ldrsb	w19, [x19, 2852]
	cmn	w19, #1
	beq	.L1724
	cbnz	w19, .L1718
	ldr	w2, [x3, 28]
	uxtw	x1, w2
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 4
	sub	x0, x0, x1
	lsl	x1, x0, 2
	sub	x1, x1, x0
	lsl	x0, x1, 6
	add	x1, x1, x0
	lsl	x1, x1, 2
	add	x0, x20, x1
	add	x1, x1, 286720
	add	x4, x0, 12288
	add	x1, x20, x1
	add	x1, x1, 2612
	ldrb	w4, [x4, 2396]
	cbz	w4, .L1719
	add	x0, x0, 286720
	ldrb	w0, [x0, 2637]
	cbz	w0, .L1719
.L1717:
	mov	w0, 0
	stp	x1, x3, [x20, 256]
.L1715:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1724:
	ldr	w2, [x3, 28]
	mov	w1, 3992
	ldr	x0, [x20, 272]
	umull	x1, w2, w1
	add	x1, x0, x1
	ldrb	w0, [x1, 25]
	cbnz	w0, .L1717
	ldr	x1, .LC136
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w19
	b	.L1715
	.p2align 3
.L1719:
	ldr	x1, .LC138
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1715
	.p2align 3
.L1723:
	ldr	x1, .LC134
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1715
	.p2align 3
.L1718:
	ldr	x1, .LC139
	mov	w2, w19
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1715
	.size	MVC_PPSSPSCheck, .-MVC_PPSSPSCheck
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
.LC138:
	.xword	.LC137
	.align	3
.LC139:
	.xword	.LC92
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_PPSSPSCheckTmpId
	.type	MVC_PPSSPSCheckTmpId, %function
MVC_PPSSPSCheckTmpId:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	x1, .LC141
	mov	w2, w20
	mov	w0, 19
	bl	dprint_vfmw
	mov	w0, 2240
	ldr	x1, [x19, 280]
	umull	x0, w20, w0
	add	x0, x1, x0
	ldrb	w1, [x0, 19]
	cbz	w1, .L1731
	ldr	w1, [x19, 36]
	ldr	w2, [x0, 28]
	sub	w0, w1, #1
	cmp	w2, w0
	bhi	.L1732
	add	x1, x19, 11116544
	mov	w0, 0
	ldrsb	w20, [x1, 2852]
	cmn	w20, #1
	beq	.L1733
.L1727:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1733:
	mov	w1, 3992
	ldr	x3, [x19, 272]
	umull	x1, w2, w1
	add	x1, x3, x1
	ldrb	w1, [x1, 25]
	cbnz	w1, .L1727
	ldr	x1, .LC147
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w20
	b	.L1727
	.p2align 3
.L1731:
	ldr	x1, .LC143
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1727
	.p2align 3
.L1732:
	ldr	x1, .LC145
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1727
	.size	MVC_PPSSPSCheckTmpId, .-MVC_PPSSPSCheckTmpId
	.align	3
.LC141:
	.xword	.LC140
	.align	3
.LC143:
	.xword	.LC142
	.align	3
.LC145:
	.xword	.LC144
	.align	3
.LC147:
	.xword	.LC146
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_IsNewPic
	.type	MVC_IsNewPic, %function
MVC_IsNewPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 11120640
	add	x3, x19, 11116544
	ldr	x4, [x19, 248]
	ldr	w5, [x3, 2856]
	ldr	w8, [x1, 412]
	ldr	w6, [x1, 408]
	ldr	w2, [x4, 744]
	cmp	w8, w5
	ldr	w0, [x3, 2868]
	ldr	w7, [x1, 416]
	ccmp	w6, w2, 0, eq
	ldrb	w5, [x1, 400]
	cset	w2, ne
	ldrb	w6, [x3, 2841]
	cmp	w7, w0
	ccmp	w5, w6, 0, eq
	cset	w0, ne
	cmp	w6, wzr
	ccmp	w5, wzr, 4, ne
	orr	w0, w2, w0
	beq	.L1736
	ldrb	w2, [x3, 2842]
	ldrb	w5, [x1, 401]
	cmp	w5, w2
	cset	w2, ne
	orr	w0, w0, w2
.L1736:
	ldrb	w2, [x1, 403]
	ldrb	w5, [x3, 2848]
	cmp	w2, w5
	beq	.L1742
	cmp	w5, wzr
	ccmp	w2, wzr, 4, ne
	cset	w7, eq
.L1737:
	ldrb	w6, [x1, 402]
	ldrb	w5, [x3, 2843]
	cmp	w6, w5
	cset	w2, ne
	cmp	w6, 5
	ccmp	w5, 5, 0, eq
	orr	w0, w2, w0
	orr	w2, w0, w7
	beq	.L1749
.L1738:
	ldr	w0, [x4, 2900]
	cbnz	w0, .L1739
	ldr	w6, [x1, 424]
	ldr	w5, [x3, 1708]
	ldr	w0, [x3, 1712]
	ldr	w4, [x1, 428]
	cmp	w6, w5
	ccmp	w4, w0, 0, eq
	cset	w0, ne
	orr	w2, w2, w0
.L1740:
	ldrb	w0, [x3, 2851]
	cbz	w0, .L1741
	ldr	w4, [x1, 384]
	ldr	w5, [x1, 444]
	ldrb	w6, [x1, 404]
	ldrb	w0, [x3, 2849]
	cmp	w5, w4
	ldrb	w5, [x1, 405]
	cset	w1, ne
	ldrb	w4, [x3, 2850]
	cmp	w6, w0
	cset	w0, ne
	cmp	w5, w4
	orr	w0, w1, w0
	cset	w1, ne
	orr	w0, w1, w0
	orr	w2, w2, w0
.L1741:
	ldr	w3, [x3, 2896]
	mov	w0, 19
	ldr	x1, .LC149
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
.L1739:
	cmp	w0, 1
	bne	.L1740
	ldr	w6, [x1, 432]
	ldr	w5, [x3, 1744]
	ldr	w0, [x3, 1748]
	ldr	w4, [x1, 436]
	cmp	w6, w5
	ccmp	w4, w0, 0, eq
	cset	w0, ne
	orr	w2, w2, w0
	b	.L1740
	.p2align 3
.L1742:
	mov	w7, 0
	b	.L1737
	.p2align 3
.L1749:
	ldr	w0, [x3, 2884]
	ldr	w5, [x1, 420]
	cmp	w5, w0
	cset	w0, ne
	orr	w2, w2, w0
	b	.L1738
	.size	MVC_IsNewPic, .-MVC_IsNewPic
	.align	3
.LC149:
	.xword	.LC148
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_ref_pic_list_reordering
	.type	mvc_ref_pic_list_reordering, %function
mvc_ref_pic_list_reordering:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 11116544
	mov	w21, 3
	bl	_mcount
	mov	w22, 1
	ldr	x0, [x19, 256]
	mov	w2, 5
	ldrb	w3, [x20, 2851]
	ldrb	w1, [x20, 2841]
	strb	wzr, [x20, 1788]
	cmp	w3, wzr
	strb	wzr, [x20, 1789]
	csel	w21, w21, w2, eq
	ldr	w0, [x0, 2896]
	cbz	w1, .L1752
	add	w0, w0, w2
	lsl	w22, w22, w0
	ldrb	w0, [x20, 2840]
	cmp	w0, 1
	bls	.L1805
.L1804:
	ldrb	w3, [x19, 10]
.L1771:
	cmp	w3, wzr
	csetm	w0, ne
.L1803:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1752:
	add	w0, w0, 4
	lsl	w22, w22, w0
	ldrb	w0, [x20, 2840]
	cmp	w0, 1
	bhi	.L1804
.L1805:
	ldr	x1, .LC151
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 1788]
	cbz	w0, .L1761
	ldr	w0, [x20, 2900]
	cmn	w0, #2
	beq	.L1787
	ldr	x23, .LC153
	mov	w28, 0
	ldr	x26, .LC163
	ldr	x25, .LC161
	ldr	x24, .LC157
	b	.L1768
	.p2align 3
.L1762:
	cmp	w0, 2
	beq	.L1806
	sub	w0, w0, #4
	cmp	w0, 1
	bls	.L1807
.L1765:
	ldr	w0, [x20, 2900]
	add	w28, w28, 1
	add	w0, w0, 2
	cmp	w0, w28
	bls	.L1808
.L1768:
	add	x27, x19, x28, uxtw 2
	mov	x1, x23
	add	x27, x27, 11116544
	mov	x0, x19
	bl	mvc_ue_v
	cmp	w21, w0
	str	w0, [x27, 1792]
	ldrb	w3, [x19, 10]
	bcc	.L1758
	cbnz	w3, .L1758
	cmp	w0, 3
	beq	.L1761
	cmp	w0, 1
	bhi	.L1762
	mov	x1, x24
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x27, 2056]
	cmp	w22, w0
	ldrb	w3, [x19, 10]
	bls	.L1764
	cbz	w3, .L1765
.L1764:
	ldr	x1, .LC159
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1803
	.p2align 3
.L1761:
	ldrb	w0, [x20, 2840]
	cmp	w0, 1
	bne	.L1804
	ldr	x1, .LC167
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 1789]
	cbz	w0, .L1804
	ldr	w0, [x20, 2904]
	cmn	w0, #2
	beq	.L1804
	ldr	x23, .LC169
	mov	w27, 0
	ldr	x26, .LC179
	ldr	x25, .LC177
	ldr	x24, .LC173
	b	.L1784
	.p2align 3
.L1777:
	cmp	w0, 2
	beq	.L1809
	sub	w0, w0, #4
	cmp	w0, 1
	bls	.L1810
	ldr	w0, [x20, 2904]
	add	w0, w0, 2
	cmp	w27, w0
	beq	.L1785
.L1783:
	add	w27, w27, 1
	cmp	w27, w0
	bcs	.L1804
.L1784:
	add	x28, x19, x27, uxtw 2
	mov	x1, x23
	add	x28, x28, 11116544
	mov	x0, x19
	bl	mvc_ue_v
	cmp	w21, w0
	str	w0, [x28, 1924]
	ldrb	w3, [x19, 10]
	bcc	.L1775
	cbnz	w3, .L1775
	cmp	w0, 3
	beq	.L1771
	cmp	w0, 1
	bhi	.L1777
	mov	x1, x24
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x28, 2188]
	cmp	w22, w0
	ldrb	w3, [x19, 10]
	bls	.L1779
	cbnz	w3, .L1779
.L1780:
	ldr	w0, [x20, 2904]
	add	w0, w0, 2
	cmp	w0, w27
	bne	.L1783
	ldr	w1, [x28, 1924]
	cmp	w1, 3
	beq	.L1783
.L1785:
	ldr	x1, .LC181
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1803
	.p2align 3
.L1806:
	mov	x1, x25
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x27, 2320]
	b	.L1765
	.p2align 3
.L1809:
	mov	x1, x25
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x28, 2448]
	b	.L1780
	.p2align 3
.L1807:
	mov	x1, x26
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x27, 2576]
	b	.L1765
	.p2align 3
.L1810:
	mov	x1, x26
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x28, 2708]
	b	.L1780
	.p2align 3
.L1758:
	ldr	x1, .LC155
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1803
	.p2align 3
.L1775:
	ldr	x1, .LC171
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1803
	.p2align 3
.L1808:
	bne	.L1761
.L1756:
	uxtw	x0, w28
	add	x0, x0, 2777088
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 9984]
	cmp	w0, 3
	beq	.L1761
	ldr	x1, .LC165
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1803
.L1779:
	ldr	x1, .LC175
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1803
.L1787:
	mov	w28, 0
	b	.L1756
	.size	mvc_ref_pic_list_reordering, .-mvc_ref_pic_list_reordering
	.align	3
.LC151:
	.xword	.LC150
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_pred_weight_table
	.type	mvc_pred_weight_table, %function
mvc_pred_weight_table:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x28, x0
	mov	x0, x30
	add	x20, x28, 11116544
	mov	w19, 1
	bl	_mcount
	mov	w24, 0
	ldp	x21, x2, [x28, 256]
	ldr	x1, .LC183
	mov	x0, x28
	str	x2, [x29, 104]
	bl	mvc_ue_v
	str	w0, [x20, 2908]
	lsl	w23, w19, w0
	ldr	w1, [x21, 748]
	cbnz	w1, .L1836
.L1812:
	cmp	w0, 7
	bhi	.L1815
	ldr	w0, [x20, 2912]
	cmp	w0, 7
	bhi	.L1815
	ldrb	w2, [x28, 10]
	cbnz	w2, .L1814
	ldr	x22, .LC189
	mov	w25, 0
	ldr	x27, .LC191
	b	.L1823
	.p2align 3
.L1818:
	str	w23, [x1, 2916]
	add	x0, x28, x19, lsl 2
	str	wzr, [x1, 3684]
	add	x0, x0, 11116544
	ldr	w1, [x21, 748]
	cbnz	w1, .L1837
.L1820:
	str	wzr, [x0, 3044]
	str	wzr, [x0, 3172]
	str	wzr, [x0, 3812]
	str	wzr, [x0, 3940]
.L1822:
	ldr	w0, [x20, 2900]
	add	w25, w25, 1
	cmp	w0, w25
	bcc	.L1838
.L1823:
	mov	x1, x22
	mov	x0, x28
	uxtw	x19, w25
	bl	mvc_u_1
	add	x1, x28, x19, lsl 2
	add	x1, x1, 11116544
	cbz	w0, .L1818
	mov	x1, x27
	mov	x0, x28
	bl	mvc_se_v
	add	x4, x28, x19, lsl 2
	ldr	x1, .LC193
	add	x26, x4, 11116544
	str	w0, [x26, 2916]
	mov	x0, x28
	bl	mvc_se_v
	str	w0, [x26, 3684]
	add	x0, x28, x19, lsl 2
	ldr	w1, [x21, 748]
	add	x0, x0, 11116544
	cbz	w1, .L1820
.L1837:
	ldr	x1, .LC195
	mov	x0, x28
	bl	mvc_u_1
	add	x1, x28, x19, lsl 2
	add	x1, x1, 11116544
	cbnz	w0, .L1839
	str	w24, [x1, 3044]
	add	w25, w25, 1
	str	w24, [x1, 3172]
	str	wzr, [x1, 3812]
	str	wzr, [x1, 3940]
	ldr	w0, [x20, 2900]
	cmp	w0, w25
	bcs	.L1823
.L1838:
	ldr	x0, [x29, 104]
	ldr	w0, [x0, 44]
	cmp	w0, 1
	beq	.L1824
.L1825:
	ldrb	w0, [x28, 10]
	cmp	w0, wzr
	csetm	w0, ne
.L1817:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1839:
	ldr	x1, .LC197
	mov	x0, x28
	add	x19, x28, x19, lsl 2
	add	x19, x19, 11116544
	bl	mvc_se_v
	ldr	x1, .LC199
	str	w0, [x19, 3044]
	mov	x0, x28
	bl	mvc_se_v
	str	w0, [x19, 3812]
	ldr	x1, .LC197
	mov	x0, x28
	bl	mvc_se_v
	str	w0, [x19, 3172]
	ldr	x1, .LC199
	mov	x0, x28
	bl	mvc_se_v
	str	w0, [x19, 3940]
	b	.L1822
	.p2align 3
.L1836:
	ldr	x1, .LC185
	mov	x0, x28
	bl	mvc_ue_v
	mov	w24, w0
	ldr	w0, [x20, 2908]
	str	w24, [x20, 2912]
	lsl	w24, w19, w24
	b	.L1812
	.p2align 3
.L1824:
	ldrb	w0, [x20, 2840]
	cmp	w0, 1
	bne	.L1825
	ldr	x22, .LC201
	mov	w25, 0
	ldr	x27, .LC203
	b	.L1831
	.p2align 3
.L1826:
	add	x0, x28, x19, lsl 2
	add	x0, x0, 11116544
	str	w23, [x0, 3300]
	str	wzr, [x0, 4068]
	add	x0, x28, x19, lsl 2
	ldr	w1, [x21, 748]
	cbnz	w1, .L1840
.L1828:
	add	x1, x0, 11116544
	add	x0, x0, 11120640
	str	wzr, [x1, 3428]
	str	wzr, [x0, 100]
	str	wzr, [x1, 3556]
	str	wzr, [x0, 228]
.L1830:
	ldr	w0, [x20, 2904]
	add	w25, w25, 1
	cmp	w0, w25
	bcc	.L1825
.L1831:
	mov	x1, x22
	mov	x0, x28
	uxtw	x19, w25
	bl	mvc_u_1
	cbz	w0, .L1826
	mov	x1, x27
	mov	x0, x28
	bl	mvc_se_v
	add	x4, x28, x19, lsl 2
	ldr	x1, .LC205
	add	x26, x4, 11116544
	str	w0, [x26, 3300]
	mov	x0, x28
	bl	mvc_se_v
	str	w0, [x26, 4068]
	add	x0, x28, x19, lsl 2
	ldr	w1, [x21, 748]
	cbz	w1, .L1828
.L1840:
	ldr	x1, .LC207
	mov	x0, x28
	bl	mvc_u_1
	cbnz	w0, .L1841
	add	x0, x28, x19, lsl 2
	add	x1, x0, 11116544
	add	x0, x0, 11120640
	str	w24, [x1, 3428]
	str	wzr, [x0, 100]
	str	w24, [x1, 3556]
	str	wzr, [x0, 228]
	b	.L1830
.L1815:
	ldrb	w2, [x28, 10]
.L1814:
	ldr	x1, .LC187
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1817
.L1841:
	add	x19, x28, x19, lsl 2
	ldr	x1, .LC209
	add	x0, x19, 11116544
	add	x19, x19, 11120640
	mov	x26, x0
	mov	x0, x28
	bl	mvc_se_v
	ldr	x1, .LC211
	str	w0, [x26, 3428]
	mov	x0, x28
	bl	mvc_se_v
	str	w0, [x19, 100]
	ldr	x1, .LC209
	mov	x0, x28
	bl	mvc_se_v
	str	w0, [x26, 3556]
	ldr	x1, .LC211
	mov	x0, x28
	bl	mvc_se_v
	str	w0, [x19, 228]
	b	.L1830
	.size	mvc_pred_weight_table, .-mvc_pred_weight_table
	.align	3
.LC183:
	.xword	.LC182
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecMMCO
	.type	MVC_DecMMCO, %function
MVC_DecMMCO:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x26, x0
	mov	w19, w1
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L1843
	mov	w21, 100
	ldr	x20, .LC215
	ldr	x23, .LC217
	ldr	x25, .LC223
	ldr	x22, .LC221
	ldr	x24, .LC219
	b	.L1854
	.p2align 3
.L1855:
	cmp	w19, 2
	beq	.L1868
.L1856:
	cmp	w19, 6
	cset	w0, eq
	orr	w0, w27, w0
	cbnz	w0, .L1859
	cmp	w19, 4
	beq	.L1869
.L1860:
	cmp	w19, 6
	bhi	.L1852
	ldrb	w0, [x26, 10]
	cbnz	w0, .L1852
.L1870:
	cbz	w19, .L1862
.L1861:
	subs	w21, w21, #1
	beq	.L1863
.L1854:
	mov	x1, x20
	mov	x0, x26
	bl	mvc_ue_v
	cmp	w0, 3
	mov	w19, w0
	and	w0, w0, -3
	cset	w27, eq
	cmp	w0, 1
	bne	.L1855
	mov	x1, x23
	mov	x0, x26
	bl	mvc_ue_v
	cmp	w19, 2
	bne	.L1856
.L1868:
	mov	x1, x24
	mov	x0, x26
	bl	mvc_ue_v
	ldrb	w0, [x26, 10]
	cbz	w0, .L1870
	.p2align 2
.L1852:
	ldr	x1, .LC225
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L1846:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1859:
	mov	x1, x22
	mov	x0, x26
	bl	mvc_ue_v
	cmp	w19, 4
	bne	.L1860
.L1869:
	mov	x1, x25
	mov	x0, x26
	bl	mvc_ue_v
	ldrb	w0, [x26, 10]
	cbz	w0, .L1861
	b	.L1852
	.p2align 3
.L1843:
	ldr	x20, .LC215
	mov	w28, 0
	ldr	x22, .LC217
	ldr	x24, .LC219
	ldr	x21, .LC221
	ldr	x23, .LC223
	b	.L1845
	.p2align 3
.L1847:
	cmp	w1, 2
	beq	.L1871
.L1848:
	cmp	w1, 3
	ccmp	w1, 6, 4, ne
	beq	.L1872
.L1849:
	cmp	w1, 4
	beq	.L1873
.L1850:
	cmp	w1, 6
	bhi	.L1852
	ldrb	w0, [x26, 10]
	cbnz	w0, .L1852
	add	w28, w28, 1
	cbz	w1, .L1862
	cmp	w28, 100
	beq	.L1874
.L1845:
	mov	x1, x20
	mov	x0, x26
	ldrb	w25, [x26, 3]
	uxtw	x27, w28
	bl	mvc_ue_v
	mov	w1, w0
	lsl	x0, x25, 6
	lsl	x19, x27, 4
	sub	x0, x0, x25
	add	x19, x19, x27, lsl 2
	lsl	x0, x0, 2
	and	w2, w1, -3
	sub	x0, x0, x25
	cmp	w2, 1
	lsl	x0, x0, 1
	sub	x0, x0, x25
	add	x19, x19, x0, lsl 2
	add	x19, x26, x19
	add	x19, x19, 11120640
	str	w1, [x19, 452]
	bne	.L1847
	mov	x1, x22
	mov	x0, x26
	bl	mvc_ue_v
	str	w0, [x19, 456]
	ldr	w1, [x19, 452]
	cmp	w1, 2
	bne	.L1848
.L1871:
	mov	x1, x24
	mov	x0, x26
	bl	mvc_ue_v
	lsl	x1, x25, 6
	sub	x1, x1, x25
	lsl	x1, x1, 2
	sub	x1, x1, x25
	lsl	x1, x1, 1
	sub	x2, x1, x25
	lsl	x1, x27, 4
	add	x1, x1, x27, lsl 2
	add	x1, x1, x2, lsl 2
	add	x1, x26, x1
	add	x1, x1, 11120640
	str	w0, [x1, 460]
	ldr	w1, [x1, 452]
	cmp	w1, 3
	ccmp	w1, 6, 4, ne
	bne	.L1849
	.p2align 2
.L1872:
	mov	x1, x21
	mov	x0, x26
	bl	mvc_ue_v
	lsl	x1, x25, 6
	lsl	x2, x27, 4
	sub	x1, x1, x25
	add	x2, x2, x27, lsl 2
	lsl	x1, x1, 2
	sub	x1, x1, x25
	lsl	x1, x1, 1
	sub	x1, x1, x25
	add	x2, x2, x1, lsl 2
	add	x2, x26, x2
	add	x2, x2, 11120640
	ldr	w1, [x2, 452]
	str	w0, [x2, 464]
	cmp	w1, 4
	bne	.L1850
.L1873:
	mov	x1, x23
	mov	x0, x26
	bl	mvc_ue_v
	lsl	x1, x25, 6
	sub	x1, x1, x25
	lsl	x1, x1, 2
	sub	x1, x1, x25
	lsl	x1, x1, 1
	sub	x25, x1, x25
	lsl	x1, x27, 4
	add	x27, x1, x27, lsl 2
	add	x27, x27, x25, lsl 2
	add	x27, x26, x27
	add	x27, x27, 11120640
	ldr	w1, [x27, 452]
	str	w0, [x27, 468]
	b	.L1850
	.p2align 3
.L1862:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L1874:
	ldr	x1, .LC213
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1846
.L1863:
	mov	w0, -1
	b	.L1846
	.size	MVC_DecMMCO, .-MVC_DecMMCO
	.align	3
.LC213:
	.xword	.LC212
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_dec_ref_pic_marking
	.type	mvc_dec_ref_pic_marking, %function
mvc_dec_ref_pic_marking:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x21, 11116544
	ldrb	w22, [x21, 3]
	ldrb	w0, [x1, 2845]
	cbz	w0, .L1876
	cmp	w22, wzr
	cset	w19, eq
	strb	w19, [x21, 3]
.L1885:
	ldrb	w0, [x1, 2843]
	cmp	w0, 5
	beq	.L1896
	ldr	x1, .LC233
	mov	x0, x21
	sxtw	x19, w19
	bl	mvc_u_1
	mov	w4, w0
	lsl	x3, x19, 6
	ldr	x1, .LC235
	sub	x3, x3, x19
	uxtb	w2, w0
	lsl	x3, x3, 2
	mov	w0, 16
	sub	x3, x3, x19
	lsl	x3, x3, 1
	sub	x19, x3, x19
	add	x19, x21, x19, lsl 2
	add	x19, x19, 11120640
	strb	w4, [x19, 451]
	bl	dprint_vfmw
	ldrb	w0, [x19, 451]
	cbnz	w0, .L1879
.L1883:
	mov	w20, 0
.L1893:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1876:
	sxtw	x20, w22
	mov	w19, w22
	lsl	x0, x20, 6
	sub	x0, x0, x20
	lsl	x0, x0, 2
	sub	x0, x0, x20
	lsl	x0, x0, 1
	sub	x20, x0, x20
	add	x20, x21, x20, lsl 2
	add	x20, x20, 11120640
	ldrb	w0, [x20, 448]
	cbz	w0, .L1885
	ldrb	w0, [x1, 2843]
	cmp	w0, 5
	beq	.L1897
	ldr	x1, .LC233
	mov	x0, x21
	ldrb	w19, [x20, 451]
	bl	mvc_u_1
	cmp	w19, w0
	bne	.L1898
	ldrb	w0, [x20, 451]
	cbz	w0, .L1883
	mov	w1, 0
	mov	x0, x21
	bl	MVC_DecMMCO
	mov	w20, w0
	b	.L1893
	.p2align 3
.L1879:
	mov	w1, 1
	mov	x0, x21
	bl	MVC_DecMMCO
	cmn	w0, #1
	mov	w20, w0
	beq	.L1899
	mov	w0, 1
	strb	w0, [x19, 448]
	mov	w20, 0
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1897:
	ldr	x1, .LC227
	mov	x0, x21
	ldrb	w19, [x20, 449]
	bl	mvc_u_1
	cmp	w19, w0
	bne	.L1900
	ldr	x1, .LC229
	mov	x0, x21
	ldrb	w19, [x20, 450]
	bl	mvc_u_1
	cmp	w19, w0
	beq	.L1883
	ldr	x1, .LC241
	mov	w0, 1
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1893
	.p2align 3
.L1896:
	ldr	x1, .LC227
	mov	x0, x21
	sxtw	x19, w19
	mov	w20, 0
	bl	mvc_u_1
	lsl	x2, x19, 6
	ldr	x1, .LC229
	sub	x2, x2, x19
	lsl	x2, x2, 2
	sub	x2, x2, x19
	lsl	x2, x2, 1
	sub	x19, x2, x19
	add	x19, x21, x19, lsl 2
	add	x19, x19, 11120640
	strb	w0, [x19, 449]
	mov	x0, x21
	bl	mvc_u_1
	strb	w0, [x19, 450]
	ldrb	w2, [x19, 449]
	mov	w0, 16
	ldr	x1, .LC231
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1898:
	ldr	x1, .LC243
	mov	w0, 1
	mov	w20, -1
	bl	dprint_vfmw
	ldr	x1, .LC245
	mov	w0, 1
	ldr	w4, [x21, 68]
	ldr	w2, [x21, 88]
	ldr	w3, [x21, 100]
	bl	dprint_vfmw
	b	.L1893
.L1900:
	ldr	x1, .LC239
	mov	w0, 1
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1893
.L1899:
	strb	wzr, [x19, 448]
	mov	w0, 1
	ldr	x1, .LC237
	strb	w22, [x21, 3]
	bl	dprint_vfmw
	b	.L1893
	.size	mvc_dec_ref_pic_marking, .-mvc_dec_ref_pic_marking
	.align	3
.LC227:
	.xword	.LC226
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ProcessSliceHeaderFirstPart
	.type	MVC_ProcessSliceHeaderFirstPart, %function
MVC_ProcessSliceHeaderFirstPart:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC247
	mov	x0, x19
	bl	mvc_ue_v
	mov	w21, w0
	ldr	w0, [x19, 40]
	sub	w0, w0, #1
	cmp	w21, w0
	bhi	.L1902
	ldrb	w0, [x19, 10]
	cbnz	w0, .L1902
	mov	w1, w21
	mov	x0, x19
	bl	MVC_PPSSPSCheckTmpId
	cbnz	w0, .L1956
	add	x20, x19, 11116544
	mov	x0, x19
	str	w21, [x20, 2856]
	bl	MVC_PPSSPSCheck
	mov	w22, w0
	cbnz	w0, .L1957
	ldp	x21, x23, [x19, 256]
	ldr	x2, .LC255
	mov	x0, x19
	ldr	w1, [x21, 2896]
	add	w1, w1, 4
	bl	mvc_u_v
	str	w0, [x20, 2868]
	ldrb	w1, [x19, 10]
	cbnz	w1, .L1928
	ldrb	w1, [x20, 2843]
	cmp	w1, 5
	ccmp	w0, wzr, 4, eq
	bne	.L1958
.L1908:
	strb	wzr, [x20, 2841]
	strb	wzr, [x20, 2842]
	ldrb	w0, [x21, 20]
	cbz	w0, .L1959
	ldr	w1, [x21, 3952]
	ldr	w2, [x21, 3948]
	add	w0, w1, 1
	madd	w0, w2, w0, w0
.L1931:
	ldrb	w1, [x21, 21]
	cbnz	w1, .L1914
	strb	wzr, [x20, 2844]
.L1916:
	ldr	w1, [x20, 2896]
	cmp	w1, w0
	bcs	.L1960
.L1917:
	ldrb	w0, [x20, 2843]
	cmp	w0, 5
	beq	.L1961
.L1919:
	str	wzr, [x20, 1708]
	str	wzr, [x20, 1712]
	ldr	w0, [x21, 2900]
	cbz	w0, .L1962
.L1923:
	str	wzr, [x20, 1744]
	str	wzr, [x20, 1748]
	ldr	w0, [x21, 2900]
	cmp	w0, 1
	beq	.L1963
.L1926:
	ldrb	w0, [x19, 10]
	cbnz	w0, .L1928
	ldrb	w0, [x23, 17]
	cbz	w0, .L1929
	ldr	x1, .LC279
	mov	x0, x19
	bl	mvc_ue_v
	cbnz	w0, .L1930
	ldrb	w0, [x19, 10]
	cbz	w0, .L1929
.L1930:
	ldr	x1, .LC281
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC282
	ldr	x4, [x0]
	cbz	x4, .L1928
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	mov	w22, -1
	blr	x4
.L1940:
	mov	w0, w22
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1959:
	ldr	x1, .LC259
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 2841]
	cbnz	w0, .L1964
	ldr	w2, [x21, 3952]
	ldr	w1, [x21, 3948]
	add	w0, w2, 1
	ldrb	w3, [x21, 20]
	madd	w1, w1, w0, w0
	lsl	w0, w1, 1
	cbz	w3, .L1931
.L1911:
	ldrb	w2, [x20, 2841]
	mov	w0, 1
	b	.L1912
	.p2align 3
.L1914:
	mov	w1, 1
	strb	w1, [x20, 2844]
.L1933:
	ldr	w1, [x20, 2896]
	cmp	w1, w0, lsr 1
	bcc	.L1917
	ldr	x1, .LC263
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1940
	.p2align 3
.L1964:
	ldr	x1, .LC261
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 2842]
	ldr	w0, [x21, 3952]
	ldr	w1, [x21, 3948]
	ldrb	w2, [x21, 20]
	add	w0, w0, 1
	madd	w1, w1, w0, w0
	cbnz	w2, .L1911
	ldrb	w2, [x20, 2841]
	mov	w0, 2
.L1912:
	mul	w0, w0, w1
	cbz	w2, .L1931
	strb	wzr, [x20, 2844]
	cmp	w2, 1
	bne	.L1916
	b	.L1933
	.p2align 3
.L1929:
	mov	x0, x19
	bl	MVC_IsNewPic
	uxtb	w0, w0
	strb	w0, [x20, 2845]
	cbnz	w0, .L1940
	add	x19, x19, 11120640
	ldr	w1, [x20, 2896]
	ldr	w0, [x19, 440]
	cmp	w1, w0
	bhi	.L1940
	ldr	x1, .LC284
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1940
	.p2align 3
.L1962:
	ldr	w1, [x21, 2904]
	mov	x0, x19
	ldr	x2, .LC271
	add	w1, w1, 4
	bl	mvc_u_v
	str	w0, [x20, 1708]
	ldrb	w0, [x23, 1]
	cbz	w0, .L1923
	ldrb	w0, [x20, 2841]
	cbnz	w0, .L1923
	ldr	x1, .LC273
	mov	x0, x19
	bl	mvc_se_v
	str	w0, [x20, 1712]
	b	.L1923
	.p2align 3
.L1963:
	ldrb	w0, [x21, 18]
	cbnz	w0, .L1926
	ldr	x1, .LC275
	mov	x0, x19
	bl	mvc_se_v
	str	w0, [x20, 1744]
	ldrb	w0, [x23, 1]
	cmp	w0, 1
	bne	.L1926
	ldrb	w0, [x20, 2841]
	cbnz	w0, .L1926
	ldr	x1, .LC277
	mov	x0, x19
	bl	mvc_se_v
	str	w0, [x20, 1748]
	b	.L1926
	.p2align 3
.L1928:
	mov	w22, -1
	ldr	x23, [sp, 48]
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1902:
	ldr	x1, .LC249
	mov	w2, w21
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1961:
	ldr	x1, .LC267
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 2884]
	mov	w1, 65535
	cmp	w0, w1
	bhi	.L1920
	ldrb	w0, [x19, 10]
	cbz	w0, .L1919
.L1920:
	ldr	x1, .LC269
	mov	w0, 1
	bl	dprint_vfmw
	b	.L1919
	.p2align 3
.L1956:
	ldr	x1, .LC251
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1940
	.p2align 3
.L1957:
	ldr	x1, .LC253
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1940
	.p2align 3
.L1958:
	add	x0, x19, 11120640
	ldr	w0, [x0, 384]
	cmp	w0, wzr
	bgt	.L1908
	ldr	x1, .LC257
	mov	w0, 1
	bl	dprint_vfmw
	b	.L1908
.L1960:
	ldr	x1, .LC265
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1940
	.size	MVC_ProcessSliceHeaderFirstPart, .-MVC_ProcessSliceHeaderFirstPart
	.align	3
.LC247:
	.xword	.LC246
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
.LC282:
	.xword	g_event_report
	.align	3
.LC284:
	.xword	.LC283
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ProcessSliceHeaderSecondPart
	.type	MVC_ProcessSliceHeaderSecondPart, %function
MVC_ProcessSliceHeaderSecondPart:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 11116544
	bl	_mcount
	ldr	w0, [x20, 40]
	ldr	w2, [x19, 2856]
	sub	w0, w0, #1
	ldr	x21, [x20, 264]
	cmp	w0, w2
	bcc	.L1966
	ldrb	w22, [x20, 10]
	cbnz	w22, .L1966
	mov	x0, x20
	bl	MVC_PPSSPSCheck
	cbnz	w0, .L2048
	ldrb	w1, [x19, 2840]
	cmp	w1, 1
	beq	.L2049
	ldr	w0, [x21, 36]
	cmp	w1, 1
	str	w0, [x19, 2900]
	ldr	w0, [x21, 40]
	str	w0, [x19, 2904]
	bls	.L2050
.L1971:
	cmp	w1, 2
	beq	.L1997
.L1981:
	mov	w0, 32
	str	w0, [x19, 2904]
.L1982:
	mov	x0, x20
	bl	mvc_ref_pic_list_reordering
	mov	w23, w0
	cbnz	w0, .L2051
	ldrb	w0, [x21, 2]
	cbz	w0, .L1984
	ldrb	w0, [x19, 2840]
	cbnz	w0, .L1984
	mov	w22, 1
	mov	w2, w22
.L1985:
	ldr	x1, .LC302
	mov	w0, 19
	strb	w22, [x19, 2847]
	bl	dprint_vfmw
	str	wzr, [x19, 2908]
	ldrb	w0, [x19, 2847]
	str	wzr, [x19, 2912]
	cbnz	w0, .L2052
.L1986:
	ldrb	w0, [x19, 2848]
	cbnz	w0, .L2053
.L1987:
	add	x22, x20, 11120640
	str	wzr, [x22, 356]
	ldrb	w0, [x21]
	cbz	w0, .L1988
	ldrb	w0, [x19, 2840]
	cmp	w0, 1
	bls	.L2054
.L1988:
	ldr	x1, .LC312
	mov	x0, x20
	bl	mvc_se_v
	add	x1, x22, 256
	stp	w0, wzr, [x1, 104]
	stp	wzr, wzr, [x1, 112]
	ldrb	w0, [x21, 3]
	cbnz	w0, .L2055
.L2017:
	mov	w0, w23
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1984:
	ldr	w0, [x21, 44]
	mov	w2, 0
	cmp	w0, 1
	bne	.L1985
	ldrb	w0, [x19, 2840]
	cmp	w0, 1
	bne	.L1985
	mov	w22, w0
	mov	w2, w0
	b	.L1985
	.p2align 3
.L2055:
	ldr	x1, .LC314
	mov	x0, x20
	bl	mvc_ue_v
	cmp	w0, 2
	str	w0, [x22, 364]
	bhi	.L1991
	ldrb	w1, [x20, 10]
	cbnz	w1, .L1991
	cmp	w0, 1
	beq	.L2017
	ldr	x1, .LC318
	mov	x0, x20
	bl	mvc_se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x22, 368]
	bhi	.L1994
	ldrb	w0, [x20, 10]
	cbnz	w0, .L1994
	ldr	x1, .LC322
	mov	x0, x20
	bl	mvc_se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x22, 372]
	bhi	.L1996
	ldrb	w0, [x20, 10]
	cbz	w0, .L2017
.L1996:
	ldr	x1, .LC324
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L2017
	.p2align 3
.L2052:
	mov	x0, x20
	bl	mvc_pred_weight_table
	cbz	w0, .L1986
	ldr	x1, .LC304
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L2017
	.p2align 3
.L2053:
	mov	x0, x20
	bl	mvc_dec_ref_pic_marking
	cbz	w0, .L1987
	ldr	x1, .LC306
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L2017
	.p2align 3
.L1997:
	mov	w0, 32
	str	w0, [x19, 2900]
	b	.L1981
	.p2align 3
.L2049:
	ldr	x1, .LC288
	mov	x0, x20
	bl	mvc_u_1
	strb	w0, [x19, 2846]
	ldrb	w1, [x19, 2840]
	ldr	w0, [x21, 36]
	str	w0, [x19, 2900]
	cmp	w1, 1
	ldr	w0, [x21, 40]
	str	w0, [x19, 2904]
	bhi	.L1971
	.p2align 2
.L2050:
	ldr	x1, .LC290
	mov	x0, x20
	bl	mvc_u_1
	cbnz	w0, .L1972
	ldr	w1, [x19, 2900]
.L1973:
	ldrb	w0, [x19, 2841]
	cbnz	w0, .L1974
	cmp	w1, 15
	bhi	.L1975
	ldr	w0, [x19, 2904]
	cmp	w0, 15
	bhi	.L2056
.L1976:
	ldrb	w0, [x20, 10]
	cbnz	w0, .L1975
.L1977:
	ldrb	w0, [x19, 2840]
	cmp	w0, 2
	beq	.L1997
	cmp	w0, 1
	beq	.L1982
	b	.L1981
	.p2align 3
.L1966:
	ldr	x1, .LC285
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	mov	w0, w23
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2054:
	ldr	x1, .LC308
	mov	x0, x20
	bl	mvc_ue_v
	cmp	w0, 2
	str	w0, [x22, 356]
	bhi	.L1989
	ldrb	w0, [x20, 10]
	cbz	w0, .L1988
.L1989:
	ldr	x1, .LC310
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L2017
	.p2align 3
.L1974:
	cmp	w1, 31
	bhi	.L1978
	ldr	w0, [x19, 2904]
	cmp	w0, 31
	bls	.L1979
	ldrb	w0, [x19, 2840]
	cmp	w0, 1
	bne	.L1979
.L1978:
	ldr	x1, .LC298
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L2017
	.p2align 3
.L1979:
	ldrb	w0, [x20, 10]
	cbz	w0, .L1977
	b	.L1978
	.p2align 3
.L2056:
	ldrb	w0, [x19, 2840]
	cmp	w0, 1
	bne	.L1976
.L1975:
	ldr	x1, .LC296
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L2017
	.p2align 3
.L1972:
	ldr	x1, .LC292
	mov	x0, x20
	bl	mvc_ue_v
	mov	w1, w0
	ldrb	w0, [x19, 2840]
	str	w1, [x19, 2900]
	cmp	w0, 1
	bne	.L1973
	ldr	x1, .LC294
	mov	x0, x20
	bl	mvc_ue_v
	str	w0, [x19, 2904]
	ldr	w1, [x19, 2900]
	b	.L1973
	.p2align 3
.L1994:
	ldr	x1, .LC320
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L2017
	.p2align 3
.L1991:
	ldr	x1, .LC316
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L2017
	.p2align 3
.L2048:
	ldr	x1, .LC286
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L2017
	.p2align 3
.L2051:
	ldr	x1, .LC300
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L2017
	.size	MVC_ProcessSliceHeaderSecondPart, .-MVC_ProcessSliceHeaderSecondPart
	.align	3
.LC285:
	.xword	.LC248
	.align	3
.LC286:
	.xword	.LC250
	.align	3
.LC288:
	.xword	.LC287
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ExitSlice
	.type	MVC_ExitSlice, %function
MVC_ExitSlice:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 11116544
	add	x0, x19, 11120640
	ldr	x3, [x19, 248]
	ldr	w2, [x1, 2856]
	str	w2, [x0, 412]
	ldr	w2, [x3, 744]
	str	w2, [x0, 408]
	ldr	w2, [x1, 2896]
	str	w2, [x0, 440]
	ldr	w2, [x1, 2868]
	str	w2, [x0, 416]
	ldrb	w2, [x1, 2841]
	strb	w2, [x0, 400]
	cbz	w2, .L2058
	ldrb	w2, [x1, 2842]
	strb	w2, [x0, 401]
.L2058:
	ldrb	w2, [x1, 2848]
	strb	w2, [x0, 403]
	ldrb	w2, [x1, 2843]
	strb	w2, [x0, 402]
	cmp	w2, 5
	beq	.L2066
.L2059:
	ldr	w2, [x3, 2900]
	cbnz	w2, .L2060
	ldr	w2, [x1, 1708]
	str	w2, [x0, 424]
	ldr	w2, [x1, 1712]
	str	w2, [x0, 428]
	ldr	w2, [x3, 2900]
.L2060:
	cmp	w2, 1
	beq	.L2067
.L2061:
	ldrb	w2, [x1, 2851]
	cmp	w2, 1
	bne	.L2062
	ldr	w2, [x0, 384]
	str	w2, [x0, 444]
	ldrb	w2, [x1, 2849]
	strb	w2, [x0, 404]
	ldrb	w1, [x1, 2850]
	strb	w1, [x0, 405]
.L2062:
	ldr	w0, [x19, 80]
	add	w0, w0, 1
	str	w0, [x19, 80]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2067:
	ldr	w2, [x1, 1744]
	str	w2, [x0, 432]
	ldr	w2, [x1, 1748]
	str	w2, [x0, 436]
	b	.L2061
	.p2align 3
.L2066:
	ldr	w2, [x1, 2884]
	str	w2, [x0, 420]
	b	.L2059
	.size	MVC_ExitSlice, .-MVC_ExitSlice
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_PicTypeStatistic
	.type	MVC_PicTypeStatistic, %function
MVC_PicTypeStatistic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 11116544
	ldrb	w0, [x1, 2840]
	cmp	w0, 1
	beq	.L2070
	cbz	w0, .L2071
	cmp	w0, 2
	bne	.L2068
	ldrb	w0, [x1, 2843]
	add	x19, x19, 11157504
	cmp	w0, 5
	beq	.L2078
.L2073:
	strb	wzr, [x19, 2325]
.L2068:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2071:
	add	x19, x19, 11157504
	ldrb	w0, [x19, 2324]
	cmp	w0, 2
	beq	.L2073
	mov	w0, 1
	strb	wzr, [x19, 2325]
	strb	w0, [x19, 2324]
	b	.L2068
	.p2align 3
.L2070:
	add	x19, x19, 11157504
	mov	w0, 2
	strb	wzr, [x19, 2325]
	strb	w0, [x19, 2324]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2078:
	mov	w0, 1
	strb	w0, [x19, 2325]
	b	.L2068
	.size	MVC_PicTypeStatistic, .-MVC_PicTypeStatistic
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_CalcStreamBits
	.type	MVC_CalcStreamBits, %function
MVC_CalcStreamBits:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 11112448
	ldrb	w0, [x0, 3560]
	cbz	w0, .L2080
	ldr	x1, [x19, 240]
	ldr	w0, [x1, 72]
	add	w0, w0, 7
	and	w0, w0, -8
	str	w0, [x1, 72]
	ldr	x1, [x19, 240]
	ldr	w0, [x1, 80]
	sub	w0, w0, #1
	str	w0, [x1, 80]
.L2080:
	ldr	x3, [x19, 240]
	ldrb	w21, [x3]
	cbz	w21, .L2091
	sub	w1, w21, #1
	mov	w4, 32
	mov	x2, 48
	add	x0, x3, 16
	mov	w20, 0
	umaddl	x2, w1, w4, x2
	add	x2, x3, x2
	.p2align 2
.L2082:
	ldr	w1, [x0], 32
	cmp	x0, x2
	add	w20, w20, w1
	bne	.L2082
.L2081:
	sbfiz	x4, x21, 5, 32
	ldr	w2, [x3, 72]
	add	x4, x3, x4
	ldr	w5, [x3, 80]
	ldr	x1, .LC326
	mov	w3, w20
	mov	w0, 7
	ldr	w4, [x4, 16]
	bl	dprint_vfmw
	ldr	x2, [x19, 240]
	ubfiz	x3, x21, 5, 8
	ldrb	w0, [x2]
	ldr	w1, [x2, 72]
	add	x0, x2, x0, lsl 5
	and	w1, w1, 7
	str	w1, [x0, 28]
	ldr	x2, [x19, 240]
	ldrb	w1, [x2]
	ldr	w0, [x2, 72]
	add	x1, x2, x1, lsl 5
	ldr	w2, [x1, 20]
	add	w0, w2, w0, lsr 3
	mov	w2, w21
	sub	w0, w0, w20
	str	w0, [x1, 32]
	ldr	x4, [x19, 240]
	ldrb	w1, [x4]
	ldr	w0, [x4, 72]
	add	x4, x4, x1, lsl 5
	ldr	w1, [x4, 16]
	add	w20, w20, w1
	lsl	w20, w20, 3
	sub	w0, w20, w0
	str	w0, [x4, 24]
	ldr	x1, [x19, 240]
	ldrb	w0, [x1]
	add	x0, x1, x0, lsl 5
	ldp	w4, w1, [x0, 28]
	ubfiz	w1, w1, 3, 2
	add	w1, w1, w4
	str	w1, [x0, 28]
	ldr	x1, .LC328
	ldr	x4, [x19, 240]
	ldrb	w0, [x4]
	add	x4, x4, x0, lsl 5
	mov	w0, 7
	ldr	w5, [x4, 32]
	and	w5, w5, -4
	str	w5, [x4, 32]
	ldr	x6, [x19, 240]
	add	x3, x6, x3
	ldrb	w5, [x6]
	ldp	w4, w3, [x3, 24]
	add	x5, x6, x5, lsl 5
	ldr	w5, [x5, 32]
	bl	dprint_vfmw
	ldr	x0, [x19, 240]
	ldr	w2, [x0, 76]
	sub	w1, w2, #1
	cmp	w1, 1
	bhi	.L2102
	ldrb	w20, [x0]
	add	w3, w20, 1
	cmp	w3, 1
	ccmp	w2, w3, 0, ls
	bls	.L2085
	ldr	x21, .LC332
	add	w20, w20, 2
	.p2align 2
.L2086:
	sub	w2, w20, #1
	mov	x1, x21
	ubfiz	x3, x2, 5, 32
	add	x4, x0, x3
	mov	w0, 7
	str	wzr, [x4, 28]
	ldr	x4, [x19, 240]
	add	x4, x4, x3
	ldr	w5, [x4, 20]
	str	w5, [x4, 32]
	ldr	x4, [x19, 240]
	add	x4, x4, x3
	ldr	w5, [x4, 16]
	lsl	w5, w5, 3
	str	w5, [x4, 24]
	ldr	x4, [x19, 240]
	add	x4, x4, x3
	ldp	w6, w5, [x4, 28]
	ubfiz	w5, w5, 3, 2
	add	w5, w5, w6
	str	w5, [x4, 28]
	ldr	x4, [x19, 240]
	add	x4, x4, x3
	ldr	w5, [x4, 32]
	and	w5, w5, -4
	str	w5, [x4, 32]
	ldr	x4, [x19, 240]
	add	x3, x4, x3
	ldp	w4, w3, [x3, 24]
	bl	dprint_vfmw
	ldr	x0, [x19, 240]
	cmp	w20, 1
	cset	w3, ls
	ldr	w1, [x0, 76]
	cmp	w1, w20
	add	w20, w20, 1
	cset	w2, hi
	tst	w3, w2
	bne	.L2086
	sub	w1, w1, #1
.L2085:
	ubfiz	x1, x1, 5, 32
	ldr	w2, [x0, 80]
	add	x0, x0, x1
	add	x5, x19, 11157504
	ldr	w1, [x0, 24]
	sub	w1, w1, w2
	str	w1, [x0, 24]
	ldr	x3, [x19, 240]
	ldrb	w0, [x3]
	ldr	w4, [x3, 76]
	cmp	w0, w4
	bcs	.L2079
	.p2align 2
.L2096:
	ubfiz	x1, x0, 5, 32
	ldr	w2, [x5, 3040]
	add	x1, x3, x1
	add	w0, w0, 1
	ldr	w1, [x1, 32]
	cmp	w1, w2
	bcs	.L2088
	str	w1, [x5, 3040]
	ldr	w4, [x3, 76]
.L2088:
	cmp	w4, w0
	bhi	.L2096
.L2079:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2102:
	ldr	x1, .LC330
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L2091:
	mov	w20, 0
	b	.L2081
	.size	MVC_CalcStreamBits, .-MVC_CalcStreamBits
	.align	3
.LC326:
	.xword	.LC325
	.align	3
.LC328:
	.xword	.LC327
	.align	3
.LC330:
	.xword	.LC329
	.align	3
.LC332:
	.xword	.LC331
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_Scaling_List
	.type	MVC_Scaling_List, %function
MVC_Scaling_List:
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
	ble	.L2103
	sub	w26, w27, #1
	mov	w0, 8
	ldr	x21, .LC333
	add	x26, x26, 1
	mov	x20, 0
	mov	w24, w0
	mov	w23, 255
	b	.L2108
	.p2align 3
.L2107:
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
	beq	.L2103
.L2108:
	cmp	w27, 16
	add	x1, x21, 16
	beq	.L2116
	ldrb	w19, [x20, x1]
.L2106:
	add	x20, x20, 1
	cbz	w0, .L2107
	ldr	x1, .LC335
	ldr	x0, [x29, 104]
	bl	mvc_se_v
	add	w0, w0, w24
	and	w0, w0, 255
	cmp	w19, wzr
	ccmp	w0, wzr, 0, eq
	cset	w1, eq
	cmp	w0, wzr
	csel	w24, w24, w0, eq
	str	w1, [x22]
	b	.L2107
	.p2align 3
.L2116:
	ldrb	w19, [x21, x20]
	b	.L2106
	.p2align 3
.L2103:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.size	MVC_Scaling_List, .-MVC_Scaling_List
	.align	3
.LC333:
	.xword	.LANCHOR0
	.align	3
.LC335:
	.xword	.LC334
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ProcessPPS
	.type	MVC_ProcessPPS, %function
MVC_ProcessPPS:
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
	bl	_mcount
	ldr	x1, .LC339
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20]
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2166
	ldr	x1, .LC341
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 1]
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2166
	ldr	x1, .LC343
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 32]
	cbnz	w0, .L2121
	ldrb	w0, [x19, 10]
	cbz	w0, .L2122
.L2121:
	ldr	x1, .LC345
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC346
	ldr	x4, [x0]
	cbz	x4, .L2166
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
	mov	w0, -1
.L2119:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L2122:
	ldr	x1, .LC348
	mov	x0, x19
	bl	mvc_ue_v
	cmp	w0, 31
	str	w0, [x20, 36]
	bhi	.L2123
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2123
	ldr	x1, .LC352
	mov	x0, x19
	bl	mvc_ue_v
	cmp	w0, 31
	str	w0, [x20, 40]
	bhi	.L2125
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2125
	ldr	x1, .LC356
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 2]
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2166
	ldr	x2, .LC358
	mov	w1, 2
	mov	x0, x19
	bl	mvc_u_v
	cmp	w0, 2
	str	w0, [x20, 44]
	bhi	.L2167
	ldr	x1, .LC362
	mov	x0, x19
	bl	mvc_se_v
	str	w0, [x20, 48]
	ldr	x1, .LC364
	mov	x0, x19
	bl	mvc_se_v
	ldr	x1, .LC366
	mov	x0, x19
	bl	mvc_se_v
	str	w0, [x20, 52]
	ldr	x1, .LC368
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 3]
	ldr	x1, .LC370
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 4]
	ldr	x1, .LC372
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 17]
	cbnz	w0, .L2168
.L2128:
	ldr	w0, [x20, 52]
	stp	w0, wzr, [x20, 56]
	strb	wzr, [x20, 18]
	add	x0, x19, 872
	bl	BsResidBits
	ldr	x1, [x19, 240]
	ldr	w1, [x1, 80]
	add	w1, w1, 3
	cmp	w0, w1
	bcc	.L2149
	ldr	x1, .LC376
	mov	x0, x19
	bl	mvc_u_1
	str	w0, [x20, 60]
	ldr	x1, .LC378
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x20, 18]
	beq	.L2130
.L2148:
	ldr	x1, .LC380
	mov	x0, x19
	bl	mvc_se_v
	add	w1, w0, 12
	cmp	w1, 24
	str	w0, [x20, 56]
	bhi	.L2131
	ldrb	w0, [x19, 10]
	cbz	w0, .L2149
.L2131:
	ldr	x1, .LC387
	mov	w0, 1
	bl	dprint_vfmw
.L2166:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, -1
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L2149:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, 0
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L2168:
	ldr	x1, .LC374
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2128
	.p2align 3
.L2123:
	ldr	x1, .LC350
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2119
	.p2align 3
.L2125:
	ldr	x1, .LC354
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2119
	.p2align 3
.L2130:
	ldr	x27, .LC383
	add	x21, x29, 120
	ldr	x25, .LC382
	add	x23, x20, 5
	add	x22, x20, 2016
	add	x24, x20, 64
	mov	w26, 0
	mov	x28, x27
	b	.L2139
	.p2align 3
.L2172:
	ldr	w0, [x20, 28]
	mov	x2, 16
	umull	x0, w0, w3
	ldr	x3, [x19, 272]
	add	x3, x3, x0
	ldr	x0, .LC337
	add	x1, x0, 16
	mov	x0, x22
	ldrb	w4, [x3, 27]
	cmp	w4, 1
	beq	.L2169
	ldr	x4, .LC337
	cmp	w26, wzr
	ldr	x3, [x28, 104]
	csel	x1, x1, x4, ne
	blr	x3
.L2134:
	add	w26, w26, 1
	add	x21, x21, 4
	cmp	w26, 6
	add	x23, x23, 1
	add	x22, x22, 16
	add	x24, x24, 64
	beq	.L2170
.L2139:
	mov	x1, x25
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x23]
	cmp	w0, 1
	str	w0, [x21]
	mov	w3, 3992
	beq	.L2171
	cmp	w26, wzr
	ccmp	w26, 3, 4, ne
	beq	.L2172
	sub	w1, w26, #1
	ldr	x3, [x27, 104]
	add	x1, x1, 126
	mov	x0, x22
	mov	x2, 16
	add	x1, x20, x1, lsl 4
	blr	x3
	b	.L2134
	.p2align 3
.L2170:
	ldr	x21, .LC383
	add	x26, x20, 2112
	ldr	x23, .LC337
	add	x28, x20, 448
	mov	x27, 0
	add	x22, x29, 112
	mov	w24, 3992
	mov	x25, x21
.L2147:
	ldr	w0, [x20, 60]
	mov	w8, w27
	cmp	w0, 1
	beq	.L2173
	add	x0, x20, x27
	str	wzr, [x22, x27, lsl 2]
	strb	wzr, [x0, 11]
.L2142:
	ldr	w0, [x20, 28]
	ldr	x1, [x19, 272]
	umull	x0, w0, w24
	add	x0, x1, x0
	ldrb	w1, [x0, 27]
	cmp	w1, 1
	beq	.L2174
	add	x1, x23, 96
	ldr	x3, [x21, 104]
	cbz	w8, .L2175
.L2146:
	mov	x2, 64
	mov	x0, x26
	blr	x3
.L2143:
	add	x27, x27, 1
	add	x26, x26, 64
	cmp	x27, 2
	add	x28, x28, 256
	bne	.L2147
	b	.L2148
	.p2align 3
.L2171:
	mov	x0, x19
	mov	x4, x21
	mov	x2, x22
	mov	x1, x24
	mov	w3, 16
	bl	MVC_Scaling_List
	ldr	w0, [x21]
	cmp	w0, 1
	bne	.L2134
	ldr	x0, .LC337
	cmp	w26, 2
	mov	x2, 16
	add	x1, x0, 16
	csel	x1, x0, x1, ls
	ldr	x0, .LC383
	ldr	x3, [x0, 104]
	mov	x0, x22
	blr	x3
	b	.L2134
.L2169:
	uxtw	x1, w26
	ldr	x0, .LC383
	add	x1, x1, 167
	add	x1, x3, x1, lsl 4
	ldr	x3, [x0, 104]
	mov	x0, x22
	blr	x3
	b	.L2134
.L2167:
	ldr	x1, .LC360
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2119
.L2173:
	ldr	x1, .LC385
	mov	x0, x19
	str	w27, [x29, 108]
	bl	mvc_u_1
	cmp	w0, 1
	add	x1, x20, x27
	str	w0, [x22, x27, lsl 2]
	ldr	w8, [x29, 108]
	strb	w0, [x1, 11]
	bne	.L2142
	mov	x0, x19
	add	x4, x22, x27, lsl 2
	mov	w3, 64
	mov	x2, x26
	mov	x1, x28
	str	w8, [x29, 108]
	bl	MVC_Scaling_List
	ldr	w0, [x22, x27, lsl 2]
	ldr	w8, [x29, 108]
	cmp	w0, 1
	bne	.L2143
	ldr	x0, .LC383
	ldr	x3, [x0, 104]
	ldr	x0, .LC337
	add	x1, x0, 96
	cbnz	w8, .L2146
	add	x1, x0, 32
	b	.L2146
	.p2align 3
.L2174:
	ubfiz	x1, x8, 6, 32
	ldr	x3, [x25, 104]
	add	x1, x1, 2768
	mov	x2, 64
	add	x1, x0, x1
	mov	x0, x26
	blr	x3
	b	.L2143
.L2175:
	ldr	x1, .LC337
	add	x1, x1, 32
	b	.L2146
	.size	MVC_ProcessPPS, .-MVC_ProcessPPS
	.align	3
.LC337:
	.xword	.LANCHOR1
	.align	3
.LC339:
	.xword	.LC338
	.align	3
.LC341:
	.xword	.LC340
	.align	3
.LC343:
	.xword	.LC342
	.align	3
.LC345:
	.xword	.LC344
	.align	3
.LC346:
	.xword	g_event_report
	.align	3
.LC348:
	.xword	.LC347
	.align	3
.LC350:
	.xword	.LC349
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
.LC383:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC385:
	.xword	.LC384
	.align	3
.LC387:
	.xword	.LC386
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_PPSEqual
	.type	MVC_PPSEqual, %function
MVC_PPSEqual:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cbz	x19, .L2198
	cbz	x20, .L2199
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
	ldr	w12, [x19, 60]
	cmp	w5, w4
	ldrb	w5, [x20, 2]
	ccmp	w3, w0, 0, eq
	ldr	w3, [x19, 44]
	cset	w4, eq
	cmp	w7, w5
	ldp	w0, w5, [x20, 44]
	ldr	w7, [x19, 52]
	and	w1, w1, w2
	ccmp	w3, w0, 0, eq
	ldr	w3, [x20, 52]
	cset	w0, eq
	cmp	w6, w5
	ldrb	w5, [x20, 3]
	and	w1, w4, w1
	ldrb	w6, [x19, 3]
	ccmp	w7, w3, 0, eq
	cset	w3, eq
	and	w0, w0, w1
	cmp	w6, w5
	ldrb	w1, [x20, 4]
	ldrb	w5, [x19, 4]
	and	w0, w3, w0
	ldr	w4, [x20, 60]
	ccmp	w5, w1, 0, eq
	ldrb	w2, [x19, 18]
	ldrb	w3, [x20, 18]
	cset	w1, eq
	cmp	w4, w12
	and	w0, w1, w0
	ccmp	w3, w2, 0, eq
	cset	w1, eq
	and	w0, w1, w0
	cbz	w2, .L2180
	lsl	w12, w12, 1
	cmn	w12, #6
	beq	.L2180
	add	x10, x19, 1984
	add	x9, x20, 1984
	mov	x11, x20
	add	x7, x19, 64
	mov	w8, -6
	mov	x1, 0
	.p2align 2
.L2185:
	add	x3, x19, x1
	add	x2, x20, x1
	ldrsb	w3, [x3, 5]
	ldrsb	w2, [x2, 5]
	cmp	w2, w3
	cset	w2, eq
	and	w0, w0, w2
	cbz	w3, .L2181
	cmp	w1, 5
	bhi	.L2182
	ldr	w3, [x9]
	ldr	w2, [x10]
	cmp	w3, w2
	cset	w3, eq
	and	w0, w0, w3
	cbnz	w2, .L2181
	sub	x2, x7, #64
	mov	x3, x11
	.p2align 2
.L2183:
	ldr	w5, [x2, 64]
	add	x2, x2, 4
	ldr	w4, [x3, 64]
	add	x3, x3, 4
	cmp	w5, w4
	cset	w4, eq
	cmp	x7, x2
	and	w0, w0, w4
	bne	.L2183
	.p2align 2
.L2181:
	add	w8, w8, 1
	add	x1, x1, 1
	cmp	w8, w12
	add	x10, x10, 4
	add	x9, x9, 4
	add	x11, x11, 64
	add	x7, x7, 64
	bne	.L2185
.L2180:
	ldr	w1, [x20, 56]
	ldr	w2, [x19, 56]
	cmp	w2, w1
	cset	w1, eq
	tst	w1, w0
	csetm	w0, eq
.L2178:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2182:
	uxtw	x2, w8
	add	x3, x2, 500
	lsl	x3, x3, 2
	add	x4, x19, x3
	add	x3, x20, x3
	ldr	w4, [x4, 8]
	ldr	w3, [x3, 8]
	cmp	w3, w4
	cset	w3, eq
	and	w0, w0, w3
	cbnz	w4, .L2181
	lsl	x2, x2, 8
	add	x3, x2, 448
	add	x2, x2, 704
	add	x6, x19, x2
	add	x2, x19, x3
	add	x3, x20, x3
	.p2align 2
.L2184:
	ldr	w5, [x2], 4
	ldr	w4, [x3], 4
	cmp	w5, w4
	cset	w4, eq
	cmp	x6, x2
	and	w0, w0, w4
	bne	.L2184
	add	w8, w8, 1
	add	x1, x1, 1
	cmp	w8, w12
	add	x10, x10, 4
	add	x9, x9, 4
	add	x11, x11, 64
	add	x7, x7, 64
	bne	.L2185
	b	.L2180
.L2199:
	ldr	x2, .LC388
	mov	w3, 10172
	ldr	x1, .LC389
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2178
.L2198:
	ldr	x2, .LC388
	mov	w3, 10171
	ldr	x1, .LC389
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2178
	.size	MVC_PPSEqual, .-MVC_PPSEqual
	.align	3
.LC388:
	.xword	.LC36
	.align	3
.LC389:
	.xword	.LC38
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecPPS
	.type	MVC_DecPPS, %function
MVC_DecPPS:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC391
	mov	x0, x19
	bl	mvc_ue_v
	mov	w20, w0
	ldr	w0, [x19, 40]
	sub	w0, w0, #1
	cmp	w20, w0
	bls	.L2201
	ldr	x1, .LC393
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x19, 40]
	sub	w0, w1, #1
	cmp	w20, w0
	bls	.L2208
	ldr	x0, .LC394
	ldr	x4, [x0]
	cbz	x4, .L2208
	ldr	w0, [x19, 120]
	mov	w3, 8
	stp	w20, w1, [x29, 56]
	add	x2, x29, 56
	mov	w1, 110
	blr	x4
	mov	w0, -1
.L2202:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2201:
	ldr	x1, .LC396
	mov	x0, x19
	bl	mvc_ue_v
	mov	w2, w0
	ldr	w0, [x19, 36]
	sub	w0, w0, #1
	cmp	w2, w0
	bhi	.L2212
	mov	w21, 2240
	ldr	x0, [x19, 280]
	umull	x21, w20, w21
	add	x0, x0, x21
	ldrb	w1, [x0, 19]
	cbz	w1, .L2204
	ldr	x22, .LC399
	mov	x0, x19
	mov	x1, x22
	stp	w20, w2, [x22, 24]
	bl	MVC_ProcessPPS
	cbnz	w0, .L2213
	ldr	x1, [x19, 280]
	mov	x0, x22
	add	x1, x1, x21
	bl	MVC_PPSEqual
	cbz	w0, .L2202
	ldr	x3, .LC402
	mov	w1, 1
	ldr	x0, [x19, 280]
	mov	x2, 2240
	strb	w1, [x22, 20]
	ldr	x3, [x3, 112]
	add	x0, x0, x21
	strb	w1, [x22, 19]
	mov	x1, x22
	blr	x3
	mov	w0, 0
	b	.L2202
	.p2align 3
.L2204:
	str	w20, [x0, 24]
	mov	x0, x19
	ldr	x1, [x19, 280]
	add	x1, x1, x21
	str	w2, [x1, 28]
	ldr	x1, [x19, 280]
	add	x1, x1, x21
	bl	MVC_ProcessPPS
	cbnz	w0, .L2214
	ldr	x1, [x19, 280]
	mov	w2, 1
	add	x1, x1, x21
	strb	w2, [x1, 20]
	ldr	x1, [x19, 280]
	add	x21, x1, x21
	strb	w2, [x21, 19]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2208:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, -1
	ldp	x29, x30, [sp], 64
	ret
.L2212:
	ldr	x1, .LC398
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2202
.L2213:
	ldr	x1, .LC401
	mov	w2, 9935
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2202
.L2214:
	ldr	x1, .LC401
	mov	w2, 9955
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 280]
	mov	w2, 1
	mov	w0, -1
	add	x1, x1, x21
	strb	w2, [x1, 20]
	ldr	x1, [x19, 280]
	add	x21, x1, x21
	strb	wzr, [x21, 19]
	b	.L2202
	.size	MVC_DecPPS, .-MVC_DecPPS
	.align	3
.LC391:
	.xword	.LC390
	.align	3
.LC393:
	.xword	.LC392
	.align	3
.LC394:
	.xword	g_event_report
	.align	3
.LC396:
	.xword	.LC395
	.align	3
.LC398:
	.xword	.LC397
	.align	3
.LC399:
	.xword	.LANCHOR2
	.align	3
.LC401:
	.xword	.LC400
	.align	3
.LC402:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_vui_parameters
	.type	mvc_vui_parameters, %function
mvc_vui_parameters:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x1, .LC404
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20]
	cbnz	w0, .L2257
	strb	wzr, [x20, 15]
.L2217:
	ldr	x1, .LC412
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 1]
	cbnz	w0, .L2258
.L2218:
	ldr	x1, .LC416
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 3]
	cbnz	w0, .L2259
	mov	w0, 5
	str	w0, [x20, 28]
.L2220:
	ldr	x1, .LC430
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 6]
	cbnz	w0, .L2260
.L2221:
	ldr	x1, .LC436
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 8]
	cbnz	w0, .L2261
.L2223:
	ldr	x1, .LC444
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 7]
	cbz	w0, .L2225
	ldr	x1, .LC446
	mov	x0, x19
	add	x24, x20, 60
	bl	mvc_ue_v
	ldr	x2, .LC448
	mov	w1, 4
	str	w0, [x24, 36]
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x24, 32]
	ldr	x2, .LC450
	mov	w1, 4
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x24, 33]
	ldr	w1, [x24, 36]
	cmp	w1, 31
	bhi	.L2228
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2228
	ldr	x27, .LC454
	mov	w21, 0
	ldr	x26, .LC456
	ldr	x25, .LC458
	.p2align 2
.L2229:
	uxtw	x22, w21
	mov	x1, x27
	mov	x0, x19
	add	w21, w21, 1
	add	x23, x20, x22, lsl 2
	bl	mvc_ue_v
	mov	x1, x26
	str	w0, [x23, 100]
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x23, 228]
	mov	x1, x25
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x24, x22]
	ldr	w0, [x24, 36]
	cmp	w0, w21
	bcs	.L2229
	ldr	x2, .LC460
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x24, 296]
	ldr	x2, .LC462
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x24, 300]
	ldr	x2, .LC464
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x24, 304]
	ldr	x2, .LC466
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x24, 308]
.L2225:
	ldr	x1, .LC468
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 10]
	cbnz	w0, .L2262
	ldrb	w0, [x20, 7]
	cbz	w0, .L2233
.L2234:
	ldr	x1, .LC470
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 14]
.L2233:
	ldr	x1, .LC472
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 11]
	ldr	x1, .LC474
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 12]
	cbnz	w0, .L2235
	ldrb	w0, [x19, 10]
.L2236:
	cmp	w0, wzr
	csetm	w0, ne
.L2256:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L2261:
	ldr	x2, .LC438
	mov	w1, 32
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 52]
	ldr	x2, .LC440
	mov	w1, 32
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 56]
	ldr	x1, .LC442
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x20, 9]
	bne	.L2223
	ldr	w2, [x20, 52]
	cbz	w2, .L2223
	ldr	w0, [x20, 56]
	lsl	w1, w0, 6
	sub	w1, w1, w0
	lsl	w1, w1, 1
	sub	w0, w1, w0
	lsl	w0, w0, 3
	udiv	w0, w0, w2
	lsr	w0, w0, 1
	str	w0, [x19, 56]
	b	.L2223
	.p2align 3
.L2260:
	ldr	x1, .LC432
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 44]
	ldr	x1, .LC434
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 48]
	b	.L2221
	.p2align 3
.L2259:
	ldr	x2, .LC418
	mov	w1, 3
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 28]
	ldr	x1, .LC420
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 4]
	ldr	x1, .LC422
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 5]
	cbz	w0, .L2220
	ldr	x2, .LC424
	mov	w1, 8
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 32]
	ldr	x2, .LC426
	mov	w1, 8
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 36]
	ldr	x2, .LC428
	mov	w1, 8
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 40]
	b	.L2220
	.p2align 3
.L2258:
	ldr	x1, .LC414
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 2]
	b	.L2218
	.p2align 3
.L2257:
	ldr	x2, .LC406
	mov	w1, 8
	mov	x0, x19
	bl	mvc_u_v
	uxtb	w0, w0
	cmp	w0, 255
	strb	w0, [x20, 15]
	bne	.L2217
	ldr	x2, .LC408
	mov	w1, 16
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 16]
	ldr	x2, .LC410
	mov	w1, 16
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 20]
	b	.L2217
	.p2align 3
.L2262:
	ldr	x1, .LC446
	mov	x0, x19
	add	x24, x20, 372
	bl	mvc_ue_v
	ldr	x2, .LC448
	mov	w1, 4
	str	w0, [x24, 36]
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x24, 32]
	ldr	x2, .LC450
	mov	w1, 4
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x24, 33]
	ldr	w1, [x24, 36]
	cmp	w1, 31
	bhi	.L2228
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2228
	ldr	x27, .LC454
	mov	w21, 0
	ldr	x26, .LC456
	ldr	x25, .LC458
	.p2align 2
.L2231:
	uxtw	x22, w21
	mov	x1, x27
	mov	x0, x19
	add	w21, w21, 1
	add	x23, x20, x22, lsl 2
	bl	mvc_ue_v
	mov	x1, x26
	str	w0, [x23, 412]
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x23, 540]
	mov	x1, x25
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x24, x22]
	ldr	w0, [x24, 36]
	cmp	w0, w21
	bcs	.L2231
	ldr	x2, .LC460
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x24, 296]
	ldr	x2, .LC462
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x24, 300]
	ldr	x2, .LC464
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x24, 304]
	ldr	x2, .LC466
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x24, 308]
	ldrb	w0, [x20, 7]
	cbnz	w0, .L2234
	ldrb	w0, [x20, 10]
	cbnz	w0, .L2234
	b	.L2233
	.p2align 3
.L2235:
	ldr	x1, .LC476
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 13]
	ldr	x1, .LC478
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 684]
	ldr	x1, .LC480
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 688]
	ldr	x1, .LC482
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 696]
	ldr	x1, .LC484
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 692]
	ldr	x1, .LC486
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 700]
	ldr	x1, .LC488
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 704]
	ldrb	w0, [x19, 10]
	cbz	w0, .L2236
	mov	w0, -1
	b	.L2256
.L2228:
	ldr	x1, .LC452
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2256
	.size	mvc_vui_parameters, .-mvc_vui_parameters
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_SPSEqual
	.type	MVC_SPSEqual, %function
MVC_SPSEqual:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cbz	x19, .L2295
	cbz	x20, .L2296
	ldr	w3, [x19, 736]
	ldr	w2, [x20, 736]
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
	ldr	w6, [x19, 740]
	ccmp	w1, w0, 0, eq
	ldr	w5, [x20, 740]
	cset	w0, eq
	ldr	w2, [x20, 744]
	ldr	w4, [x19, 744]
	and	w0, w3, w0
	ldrb	w1, [x19, 27]
	cmp	w6, w5
	ldrb	w3, [x20, 27]
	ccmp	w4, w2, 0, eq
	cset	w2, eq
	cmp	w3, w1
	and	w0, w2, w0
	cset	w2, eq
	and	w0, w2, w0
	cbz	w1, .L2267
	mov	x2, x19
	mov	x8, x20
	mov	w9, -6
	mov	x1, 0
	.p2align 2
.L2272:
	add	x4, x19, x1
	add	x3, x20, x1
	add	x6, x2, 64
	ldrsb	w3, [x3, 6]
	ldrsb	w4, [x4, 6]
	cmp	w3, w4
	cset	w3, eq
	and	w0, w0, w3
	cbz	w4, .L2268
	cmp	w1, 5
	bhi	.L2269
	mov	x3, x8
	.p2align 2
.L2270:
	ldr	w5, [x2, 752]
	add	x2, x2, 4
	ldr	w4, [x3, 752]
	add	x3, x3, 4
	cmp	w5, w4
	cset	w4, eq
	cmp	x2, x6
	and	w0, w0, w4
	bne	.L2270
.L2268:
	add	x1, x1, 1
	add	w9, w9, 1
	cmp	x1, 8
	mov	x2, x6
	add	x8, x8, 64
	bne	.L2272
.L2267:
	ldr	w4, [x19, 2896]
	ldr	w3, [x20, 2896]
	ldr	w2, [x20, 2900]
	ldr	w1, [x19, 2900]
	cmp	w4, w3
	ccmp	w2, w1, 0, eq
	cset	w2, eq
	and	w0, w2, w0
	cbz	w1, .L2274
	cmp	w1, 1
	bne	.L2273
	ldrb	w4, [x19, 18]
	ldrb	w3, [x20, 18]
	ldr	w2, [x19, 2908]
	ldr	w1, [x20, 2908]
	cmp	w4, w3
	ldr	w5, [x19, 2912]
	ldr	w4, [x20, 2912]
	ccmp	w2, w1, 0, eq
	ldr	w2, [x20, 2916]
	cset	w3, eq
	ldr	w1, [x19, 2916]
	cmp	w5, w4
	ccmp	w2, w1, 0, eq
	cset	w2, eq
	and	w2, w3, w2
	and	w0, w0, w2
	cbz	w1, .L2273
	sub	w5, w1, #1
	add	x2, x20, 2920
	add	x5, x5, 731
	add	x1, x19, 2920
	add	x5, x19, x5, lsl 2
	.p2align 2
.L2276:
	ldr	w4, [x1], 4
	ldr	w3, [x2], 4
	cmp	w4, w3
	cset	w3, eq
	cmp	x1, x5
	and	w0, w0, w3
	bne	.L2276
.L2273:
	ldr	w4, [x19, 3944]
	ldr	w3, [x20, 3944]
	ldrb	w2, [x19, 19]
	ldrb	w1, [x20, 19]
	cmp	w4, w3
	ldr	w6, [x19, 3948]
	ldr	w4, [x20, 3948]
	ccmp	w2, w1, 0, eq
	ldr	w5, [x19, 3952]
	cset	w2, eq
	ldr	w1, [x20, 3952]
	cmp	w6, w4
	ldrb	w3, [x19, 20]
	ldrb	w4, [x20, 20]
	ccmp	w5, w1, 0, eq
	cset	w1, eq
	cmp	w4, w3
	and	w2, w2, w1
	cset	w1, eq
	and	w1, w2, w1
	and	w0, w1, w0
	cbnz	w3, .L2277
	ldrb	w1, [x20, 21]
	ldrb	w2, [x19, 21]
	cmp	w2, w1
	cset	w1, eq
	and	w0, w0, w1
.L2277:
	ldrb	w4, [x19, 22]
	ldrb	w3, [x20, 22]
	ldrb	w2, [x20, 23]
	ldrb	w1, [x19, 23]
	cmp	w4, w3
	ccmp	w2, w1, 0, eq
	cset	w2, eq
	and	w0, w2, w0
	cbnz	w1, .L2297
.L2278:
	ldrb	w4, [x19, 24]
	ldrb	w3, [x20, 24]
	ldr	w1, [x20, 52]
	ldr	w2, [x19, 52]
	cmp	w4, w3
	ccmp	w2, w1, 0, eq
	cset	w1, eq
	tst	w1, w0
	csetm	w0, eq
.L2265:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2297:
	ldr	w4, [x19, 3964]
	ldr	w3, [x20, 3964]
	ldr	w2, [x19, 3968]
	ldr	w1, [x20, 3968]
	cmp	w4, w3
	ldr	w5, [x19, 3956]
	ldr	w4, [x20, 3956]
	ccmp	w2, w1, 0, eq
	ldr	w3, [x19, 3960]
	cset	w2, eq
	ldr	w1, [x20, 3960]
	cmp	w5, w4
	ccmp	w3, w1, 0, eq
	cset	w1, eq
	and	w1, w2, w1
	and	w0, w0, w1
	b	.L2278
	.p2align 3
.L2269:
	ubfiz	x3, x9, 8, 32
	add	x4, x3, 1136
	add	x7, x3, 1392
	add	x7, x19, x7
	add	x3, x19, x4
	add	x4, x20, x4
	.p2align 2
.L2271:
	ldr	w6, [x3], 4
	ldr	w5, [x4], 4
	cmp	w6, w5
	cset	w5, eq
	cmp	x3, x7
	and	w0, w0, w5
	bne	.L2271
	add	x1, x1, 1
	add	x6, x2, 64
	cmp	x1, 8
	add	w9, w9, 1
	mov	x2, x6
	add	x8, x8, 64
	bne	.L2272
	b	.L2267
	.p2align 3
.L2274:
	ldr	w1, [x20, 2904]
	ldr	w2, [x19, 2904]
	cmp	w2, w1
	cset	w1, eq
	and	w0, w0, w1
	b	.L2273
.L2296:
	ldr	x2, .LC489
	mov	w3, 10416
	ldr	x1, .LC490
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2265
.L2295:
	ldr	x2, .LC489
	mov	w3, 10415
	ldr	x1, .LC490
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2265
	.size	MVC_SPSEqual, .-MVC_SPSEqual
	.align	3
.LC489:
	.xword	.LC36
	.align	3
.LC490:
	.xword	.LC38
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetDar
	.type	MVC_GetDar, %function
MVC_GetDar:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	mov	w21, w2
	mov	w23, w3
	mov	w22, w4
	bl	_mcount
	cbz	w20, .L2309
	mov	w0, 255
	cmp	w20, 16
	ccmp	w20, w0, 4, gt
	bne	.L2309
	cmp	w19, wzr
	ccmp	w21, wzr, 4, ne
	ccmp	w20, w0, 0, eq
	beq	.L2309
	cmp	w20, 1
	beq	.L2310
	cmp	w20, w0
	beq	.L2300
	ldr	x0, .LC491
	sbfiz	x20, x20, 3, 32
	add	x0, x0, 104
	add	x1, x0, x20
	ldr	w19, [x0, x20]
	ldr	w21, [x1, 4]
.L2300:
	mul	w19, w19, w23
	mul	w2, w21, w22
	lsl	w19, w19, 10
	sdiv	w2, w19, w2
	subs	w1, w2, #2406
	bmi	.L2320
.L2301:
	subs	w0, w2, #2263
	bmi	.L2321
	cmp	w1, w0
	mov	w19, 4
	blt	.L2299
.L2305:
	subs	w1, w2, #1820
	bmi	.L2322
	cmp	w0, w1
	mov	w19, 3
	blt	.L2299
.L2306:
	subs	w0, w2, #1365
	bmi	.L2323
.L2304:
	mov	w19, 2
	cmp	w1, w0
	csinc	w19, w19, wzr, lt
	b	.L2299
	.p2align 3
.L2309:
	mov	w19, 0
	mov	w2, 0
.L2299:
	ldr	x1, .LC493
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
.L2310:
	mov	w19, 5
	mov	w2, 0
	b	.L2299
	.p2align 3
.L2321:
	mov	w0, 2263
	mov	w19, 4
	sub	w0, w0, w2
	cmp	w1, w0
	blt	.L2299
	b	.L2305
	.p2align 3
.L2320:
	mov	w1, 2406
	sub	w1, w1, w2
	b	.L2301
	.p2align 3
.L2322:
	mov	w1, 1820
	mov	w19, 3
	sub	w1, w1, w2
	cmp	w0, w1
	blt	.L2299
	b	.L2306
.L2323:
	mov	w0, 1365
	sub	w0, w0, w2
	b	.L2304
	.size	MVC_GetDar, .-MVC_GetDar
	.align	3
.LC491:
	.xword	.LANCHOR0
	.align	3
.LC493:
	.xword	.LC492
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ProcessSPS
	.type	MVC_ProcessSPS, %function
MVC_ProcessSPS:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L2443
	ldr	w0, [x20, 736]
	mov	w3, 128
	mov	w2, 100
	sub	w1, w0, #110
	and	w4, w0, -17
	and	w1, w1, -9
	cmp	w1, wzr
	ccmp	w4, w3, 4, ne
	cset	w1, eq
	cmp	w0, 122
	ccmp	w0, w2, 4, ne
	cset	w0, eq
	orr	w0, w1, w0
	cbnz	w0, .L2444
	mov	w0, 1
	strb	wzr, [x20, 27]
	str	w0, [x20, 748]
.L2337:
	ldr	x1, .LC519
	mov	x0, x19
	bl	mvc_ue_v
	cmp	w0, 12
	str	w0, [x20, 2896]
	bhi	.L2350
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2350
	ldr	x1, .LC523
	mov	x0, x19
	bl	mvc_ue_v
	cmp	w0, 2
	str	w0, [x20, 2900]
	bhi	.L2352
	ldrb	w1, [x19, 10]
	cbnz	w1, .L2352
	cbz	w0, .L2445
	cmp	w0, 1
	beq	.L2446
.L2356:
	ldr	x1, .LC581
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 3944]
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2441
	ldr	x1, .LC543
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 19]
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2441
	ldr	x1, .LC545
	mov	x0, x19
	bl	mvc_ue_v
	sub	w1, w0, #1
	cmp	w1, 509
	str	w0, [x20, 3948]
	bhi	.L2363
	ldrb	w1, [x19, 10]
	cbnz	w1, .L2363
	ldr	x1, .LC549
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 3952]
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2441
	ldr	x1, .LC551
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 20]
	ldrb	w1, [x19, 10]
	cbnz	w1, .L2441
	cbnz	w0, .L2447
	ldr	x1, .LC583
	mov	x0, x19
	bl	mvc_u_1
	ldr	w22, [x20, 3952]
	strb	w0, [x20, 21]
	add	w22, w22, 1
	cmp	w22, 255
	bhi	.L2397
	ldr	w3, [x20, 3948]
	cmp	w22, 1
	mov	w23, 2
	add	w3, w3, 1
	ccmp	w3, 3, 0, hi
	cset	w0, ls
	cbz	w0, .L2367
.L2397:
	ldr	x1, .LC553
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2433
	.p2align 3
.L2444:
	ldr	x1, .LC499
	mov	x0, x19
	bl	mvc_ue_v
	cmp	w0, 1
	str	w0, [x20, 748]
	bhi	.L2328
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2328
	ldr	x1, .LC503
	mov	x0, x19
	bl	mvc_ue_v
	cbnz	w0, .L2330
	ldrb	w0, [x19, 10]
	cbz	w0, .L2331
.L2330:
	ldr	x1, .LC505
	mov	w0, 1
	bl	dprint_vfmw
.L2331:
	ldr	x1, .LC507
	mov	x0, x19
	bl	mvc_ue_v
	cbnz	w0, .L2332
	ldrb	w0, [x19, 10]
	cbz	w0, .L2333
.L2332:
	ldr	x1, .LC509
	mov	w0, 1
	bl	dprint_vfmw
.L2333:
	ldr	x1, .LC511
	mov	x0, x19
	bl	mvc_u_1
	cbnz	w0, .L2334
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2334
	ldr	x1, .LC515
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x20, 27]
	bne	.L2337
	ldr	x25, .LC495
	add	x21, x29, 120
	ldr	x26, .LC516
	add	x23, x20, 6
	add	x22, x20, 2672
	add	x24, x20, 752
	mov	w28, 0
	ldr	x27, .LC517
	b	.L2343
	.p2align 3
.L2450:
	ldr	x0, .LC495
	cmp	w28, wzr
	ldr	x3, [x27, 104]
	mov	x2, 16
	csel	x1, x0, x1, eq
	mov	x0, x22
	blr	x3
.L2339:
	add	w28, w28, 1
	add	x21, x21, 4
	cmp	w28, 6
	add	x23, x23, 1
	add	x22, x22, 16
	add	x24, x24, 64
	beq	.L2448
.L2343:
	mov	x1, x26
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x23]
	cmp	w0, 1
	str	w0, [x21]
	add	x1, x25, 16
	beq	.L2449
	cmp	w28, wzr
	ccmp	w28, 3, 4, ne
	beq	.L2450
	ldr	x0, .LC517
	sub	w1, w28, #1
	add	x1, x1, 167
	mov	x2, 16
	add	w28, w28, 1
	add	x21, x21, 4
	ldr	x3, [x0, 104]
	add	x1, x20, x1, lsl 4
	mov	x0, x22
	add	x23, x23, 1
	add	x22, x22, 16
	add	x24, x24, 64
	blr	x3
	cmp	w28, 6
	bne	.L2343
.L2448:
	ldr	x24, .LC517
	add	x21, x20, 2768
	ldr	x23, .LC495
	add	x22, x20, 1136
	mov	x27, 0
	add	x25, x29, 104
	mov	x28, x24
.L2348:
	mov	x1, x26
	mov	x0, x19
	bl	mvc_u_1
	cmp	w0, 1
	add	x2, x20, x27
	str	w0, [x25, x27, lsl 2]
	add	x1, x23, 96
	strb	w0, [x2, 12]
	beq	.L2451
	ldr	x3, [x24, 104]
	cbz	w27, .L2452
.L2347:
	mov	x0, x21
	mov	x2, 64
.L2437:
	blr	x3
.L2345:
	add	x27, x27, 1
	add	x21, x21, 64
	cmp	x27, 2
	add	x22, x22, 256
	bne	.L2348
	b	.L2337
	.p2align 3
.L2394:
	ldr	w2, [x0, 724]
	ldr	w1, [x0, 728]
	cmp	w24, w2
	ccmp	w22, w1, 2, ls
	bls	.L2393
	ldr	x0, .LC579
	ldr	x4, [x0]
	cbz	x4, .L2441
	ldr	w0, [x19, 120]
	mov	w3, 8
	strh	w2, [x29, 116]
	add	x2, x29, 112
	strh	w1, [x29, 118]
	mov	w1, 107
	strh	w24, [x29, 112]
	strh	w22, [x29, 114]
	blr	x4
	.p2align 2
.L2441:
	mov	w0, -1
.L2433:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L2447:
	ldr	w22, [x20, 3952]
	strb	wzr, [x20, 21]
	sub	w0, w22, #1
	cmp	w0, 509
	bhi	.L2397
	ldr	w3, [x20, 3948]
	mov	w23, 1
	add	w22, w22, 1
	add	w3, w3, w23
.L2367:
	mul	w22, w23, w22
	lsl	w24, w3, 4
	mov	w1, 100663296
	lsl	w22, w22, 4
	mul	w0, w24, w22
	lsr	w0, w0, 1
	lsl	w21, w0, 2
	sub	w0, w21, w0
	cmp	w0, w1
	bhi	.L2453
	ldr	w2, [x20, 740]
	sub	w1, w2, #10
	cmp	w1, 31
	bls	.L2454
.L2369:
	ldr	x1, .LC558
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2433
	.p2align 3
.L2445:
	ldr	x1, .LC527
	mov	x0, x19
	bl	mvc_ue_v
	cmp	w0, 12
	str	w0, [x20, 2904]
	bhi	.L2355
	ldrb	w0, [x19, 10]
	cbz	w0, .L2356
.L2355:
	ldr	x1, .LC529
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2433
	.p2align 3
.L2454:
	ldr	x3, .LC556
	ldrh	w1, [x3,w1,uxtw #1]
	adr	x3, .Lrtx2371
	add	x1, x3, w1, sxth #2
	br	x1
.Lrtx2371:
	.section	.rodata
	.align	0
	.align	2
.L2371:
	.2byte	(.L2370 - .Lrtx2371) / 4
	.2byte	(.L2404 - .Lrtx2371) / 4
	.2byte	(.L2373 - .Lrtx2371) / 4
	.2byte	(.L2373 - .Lrtx2371) / 4
	.2byte	(.L2369 - .Lrtx2371) / 4
	.2byte	(.L2369 - .Lrtx2371) / 4
	.2byte	(.L2369 - .Lrtx2371) / 4
	.2byte	(.L2369 - .Lrtx2371) / 4
	.2byte	(.L2369 - .Lrtx2371) / 4
	.2byte	(.L2369 - .Lrtx2371) / 4
	.2byte	(.L2373 - .Lrtx2371) / 4
	.2byte	(.L2374 - .Lrtx2371) / 4
	.2byte	(.L2376 - .Lrtx2371) / 4
	.2byte	(.L2369 - .Lrtx2371) / 4
	.2byte	(.L2369 - .Lrtx2371) / 4
	.2byte	(.L2369 - .Lrtx2371) / 4
	.2byte	(.L2369 - .Lrtx2371) / 4
	.2byte	(.L2369 - .Lrtx2371) / 4
	.2byte	(.L2369 - .Lrtx2371) / 4
	.2byte	(.L2369 - .Lrtx2371) / 4
	.2byte	(.L2376 - .Lrtx2371) / 4
	.2byte	(.L2377 - .Lrtx2371) / 4
	.2byte	(.L2378 - .Lrtx2371) / 4
	.2byte	(.L2369 - .Lrtx2371) / 4
	.2byte	(.L2369 - .Lrtx2371) / 4
	.2byte	(.L2369 - .Lrtx2371) / 4
	.2byte	(.L2369 - .Lrtx2371) / 4
	.2byte	(.L2369 - .Lrtx2371) / 4
	.2byte	(.L2369 - .Lrtx2371) / 4
	.2byte	(.L2369 - .Lrtx2371) / 4
	.2byte	(.L2380 - .Lrtx2371) / 4
	.2byte	(.L2380 - .Lrtx2371) / 4
	.text
	.p2align 3
.L2373:
	mov	w21, 60416
	movk	w21, 0xd, lsl 16
.L2372:
	udiv	w21, w21, w0
	mov	w2, 16
	ldr	x1, .LC560
	mov	w0, 21
	cmp	w21, w2
	csel	w21, w21, w2, ls
	mov	w2, w21
	bl	dprint_vfmw
	ldr	w2, [x20, 3944]
	cmp	w2, w21
	bhi	.L2381
	ldrb	w0, [x19, 10]
	cbz	w0, .L2382
.L2381:
	ldr	x1, .LC562
	mov	w3, w21
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x20, 3944]
	cmp	w0, 16
	bhi	.L2438
	cmp	w21, w0
	csel	w21, w21, w0, cs
.L2438:
	str	w21, [x20, 3944]
.L2382:
	ldr	x1, .LC564
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 22]
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2441
	ldr	x1, .LC566
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 23]
	ldrb	w1, [x19, 10]
	cbnz	w1, .L2441
	cbnz	w0, .L2455
.L2384:
	add	x2, x20, 3840
	lsr	w1, w24, 1
	lsr	w0, w22, 1
	stp	w24, w22, [x2, 136]
	stp	w1, w0, [x2, 144]
.L2386:
	ldr	x1, .LC576
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 24]
	ldrb	w1, [x19, 10]
	cbnz	w1, .L2441
	mov	w1, 2
	str	w1, [x20, 68]
	cbnz	w0, .L2456
	mov	w0, 5
	strb	wzr, [x20, 43]
	str	w0, [x20, 56]
	mov	w0, 0
.L2389:
	ldp	w1, w2, [x20, 44]
	mov	w4, w22
	mov	w3, w24
	bl	MVC_GetDar
	str	w0, [x20, 52]
	ldr	w1, [x20, 3944]
	cbz	w1, .L2392
	cmp	w21, w1
	csel	w21, w21, w1, ls
.L2392:
	ldr	x0, [x19, 224]
	cmp	w21, 16
	mov	w1, 16
	csel	w21, w21, w1, ls
	ldr	w1, [x0, 28]
	cmp	w1, 25
	beq	.L2457
.L2393:
	cmp	w22, 1919
	bls	.L2395
	mov	w0, 4
	cmp	w21, w0
	csel	w21, w21, w0, ls
.L2395:
	add	w21, w21, 1
	str	w21, [x20, 3972]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L2380:
	mov	w21, 12582912
	b	.L2372
	.p2align 3
.L2376:
	mov	w21, 30208
	movk	w21, 0x2f, lsl 16
	b	.L2372
	.p2align 3
.L2449:
	mov	x0, x19
	mov	x4, x21
	mov	x2, x22
	mov	x1, x24
	mov	w3, 16
	bl	MVC_Scaling_List
	ldr	w0, [x21]
	cmp	w0, 1
	bne	.L2339
	ldr	x0, .LC495
	cmp	w28, 2
	mov	x2, 16
	add	x1, x0, 16
	csel	x1, x0, x1, ls
	ldr	x0, .LC517
	ldr	x3, [x0, 104]
	mov	x0, x22
	blr	x3
	b	.L2339
	.p2align 3
.L2328:
	ldr	x1, .LC501
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L2350:
	ldr	x1, .LC521
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2433
	.p2align 3
.L2455:
	ldr	x1, .LC568
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 3956]
	ldr	x1, .LC570
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 3960]
	ldr	x1, .LC572
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 3964]
	ldr	x1, .LC574
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 3968]
	ldr	w1, [x20, 3964]
	ldr	w2, [x20, 3956]
	lsl	w1, w1, 1
	ldr	w3, [x20, 3960]
	lsl	w2, w2, 1
	mul	w1, w1, w23
	sub	w4, w24, w2
	lsl	w23, w23, 1
	sub	w3, w4, w3, lsl 1
	sub	w4, w22, w1
	cmp	w3, wzr
	msub	w0, w23, w0, w4
	ccmp	w0, wzr, 4, gt
	ble	.L2384
	add	x4, x20, 3840
	add	w2, w2, w3, lsr 1
	add	w1, w1, w0, lsr 1
	stp	w3, w0, [x4, 136]
	stp	w2, w1, [x4, 144]
	b	.L2386
	.p2align 3
.L2456:
	add	x1, x20, 28
	mov	x0, x19
	bl	mvc_vui_parameters
	cbnz	w0, .L2440
	ldrb	w0, [x20, 40]
	cbz	w0, .L2440
	ldr	w2, [x20, 732]
	cmp	w2, wzr
	ccmp	w21, w2, 0, ne
	bcc	.L2458
	ldr	w21, [x20, 3944]
	ldrb	w0, [x20, 43]
	cmp	w21, w2
	csel	w21, w21, w2, cs
	b	.L2389
.L2458:
	ldr	x1, .LC578
	mov	w3, w21
	mov	w0, 1
	bl	dprint_vfmw
	.p2align 2
.L2440:
	ldrb	w0, [x20, 43]
	b	.L2389
	.p2align 3
.L2457:
	ldr	w1, [x0, 764]
	cbnz	w1, .L2393
	ldr	w1, [x0, 748]
	cmp	w21, w1
	bls	.L2394
	ldr	x0, .LC579
	ldr	x4, [x0]
	cbz	x4, .L2441
	ldr	w0, [x19, 120]
	mov	w3, 8
	stp	w21, w1, [x29, 112]
	add	x2, x29, 112
	mov	w1, 106
	blr	x4
	mov	w0, -1
	b	.L2433
	.p2align 3
.L2334:
	ldr	x1, .LC513
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2433
	.p2align 3
.L2446:
	ldr	x1, .LC531
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 18]
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2441
	ldr	x1, .LC533
	mov	x0, x19
	bl	mvc_se_v
	str	w0, [x20, 2908]
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2441
	ldr	x1, .LC535
	mov	x0, x19
	bl	mvc_se_v
	str	w0, [x20, 2912]
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2441
	ldr	x1, .LC537
	mov	x0, x19
	bl	mvc_ue_v
	cmp	w0, 255
	str	w0, [x20, 2916]
	bhi	.L2359
	ldrb	w1, [x19, 10]
	cbnz	w1, .L2359
	cbz	w0, .L2356
	ldr	x22, .LC541
	mov	w21, 0
	b	.L2362
	.p2align 3
.L2459:
	ldr	w0, [x20, 2916]
	cmp	w0, w21
	bls	.L2356
.L2362:
	mov	x1, x22
	mov	x0, x19
	bl	mvc_se_v
	add	x1, x20, x21, uxtw 2
	add	w21, w21, 1
	str	w0, [x1, 2920]
	ldrb	w0, [x19, 10]
	cbz	w0, .L2459
	b	.L2441
	.p2align 3
.L2363:
	ldr	x1, .LC547
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2433
	.p2align 3
.L2404:
	mov	w21, 17920
	movk	w21, 0x5, lsl 16
	b	.L2372
	.p2align 3
.L2377:
	mov	w21, 30720
	movk	w21, 0x69, lsl 16
	b	.L2372
	.p2align 3
.L2374:
	mov	w21, 55296
	movk	w21, 0x1b, lsl 16
	b	.L2372
	.p2align 3
.L2370:
	mov	w21, 20992
	movk	w21, 0x2, lsl 16
	b	.L2372
	.p2align 3
.L2378:
	mov	w21, 7864320
	b	.L2372
.L2359:
	ldr	x1, .LC539
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2433
	.p2align 3
.L2451:
	mov	x0, x19
	add	x4, x25, x27, lsl 2
	mov	x2, x21
	mov	x1, x22
	mov	w3, 64
	bl	MVC_Scaling_List
	ldr	w0, [x25, x27, lsl 2]
	cmp	w0, 1
	bne	.L2345
	ldr	x1, .LC495
	mov	x2, 64
	mov	x0, x21
	ldr	x3, [x28, 104]
	add	x1, x1, 96
	cbnz	w27, .L2437
	ldr	x1, .LC495
	add	x1, x1, 32
	b	.L2437
	.p2align 3
.L2352:
	ldr	x1, .LC525
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2433
.L2453:
	ldr	x1, .LC555
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2433
.L2443:
	ldr	x2, .LC496
	mov	w3, 10606
	ldr	x1, .LC497
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2433
.L2452:
	ldr	x1, .LC495
	add	x1, x1, 32
	b	.L2347
	.size	MVC_ProcessSPS, .-MVC_ProcessSPS
	.align	3
.LC495:
	.xword	.LANCHOR1
	.align	3
.LC496:
	.xword	.LC36
	.align	3
.LC497:
	.xword	.LC38
	.align	3
.LC499:
	.xword	.LC498
	.align	3
.LC501:
	.xword	.LC500
	.align	3
.LC503:
	.xword	.LC502
	.align	3
.LC505:
	.xword	.LC504
	.align	3
.LC507:
	.xword	.LC506
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
	.xword	.LC381
	.align	3
.LC517:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC519:
	.xword	.LC518
	.align	3
.LC521:
	.xword	.LC520
	.align	3
.LC523:
	.xword	.LC522
	.align	3
.LC525:
	.xword	.LC524
	.align	3
.LC527:
	.xword	.LC526
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
.LC547:
	.xword	.LC546
	.align	3
.LC549:
	.xword	.LC548
	.align	3
.LC551:
	.xword	.LC550
	.align	3
.LC553:
	.xword	.LC552
	.align	3
.LC555:
	.xword	.LC554
	.align	3
.LC556:
	.xword	.L2371
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
.LC568:
	.xword	.LC567
	.align	3
.LC570:
	.xword	.LC569
	.align	3
.LC572:
	.xword	.LC571
	.align	3
.LC574:
	.xword	.LC573
	.align	3
.LC576:
	.xword	.LC575
	.align	3
.LC578:
	.xword	.LC577
	.align	3
.LC579:
	.xword	g_event_report
	.align	3
.LC581:
	.xword	.LC580
	.align	3
.LC583:
	.xword	.LC582
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecSPS
	.type	MVC_DecSPS, %function
MVC_DecSPS:
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
	ldr	x2, .LC585
	mov	w1, 8
	mov	x0, x19
	bl	mvc_u_v
	mov	w21, w0
	ldr	x1, .LC587
	mov	x0, x19
	bl	mvc_u_1
	mov	w27, w0
	ldr	x1, .LC589
	mov	x0, x19
	bl	mvc_u_1
	mov	w26, w0
	ldr	x1, .LC591
	mov	x0, x19
	bl	mvc_u_1
	mov	w25, w0
	ldr	x1, .LC593
	mov	x0, x19
	bl	mvc_u_1
	mov	w24, w0
	ldr	x1, .LC595
	mov	x0, x19
	bl	mvc_u_1
	mov	w23, w0
	ldr	x1, .LC597
	mov	x0, x19
	bl	mvc_u_1
	str	w0, [x29, 108]
	ldr	x2, .LC599
	mov	w1, 2
	mov	x0, x19
	bl	mvc_u_v
	ldr	x2, .LC601
	mov	w1, 8
	mov	x0, x19
	bl	mvc_u_v
	mov	w20, w0
	ldr	x1, .LC603
	mov	x0, x19
	bl	mvc_ue_v
	mov	w22, w0
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2498
	ldr	w0, [x19, 36]
	sub	w0, w0, #1
	cmp	w22, w0
	bhi	.L2500
	cmp	w21, 100
	mov	w28, w21
	beq	.L2466
	bgt	.L2467
	cmp	w21, 77
	beq	.L2466
	cmp	w21, 88
	beq	.L2468
	cmp	w21, 66
	bne	.L2465
	ldr	x1, .LC607
	mov	w0, 1
	bl	dprint_vfmw
.L2466:
	cmp	w20, 9
	mov	w2, w20
	bls	.L2497
.L2503:
	cmp	w20, 41
	bhi	.L2497
	mov	w20, 3992
	ldr	x0, [x19, 272]
	umull	x20, w22, w20
	add	x0, x0, x20
	ldrb	w1, [x0, 25]
	cbz	w1, .L2473
.L2504:
	ldr	x21, .LC616
	mov	x0, x19
	ldrb	w3, [x29, 108]
	add	x21, x21, 2240
	strb	w27, [x21]
	str	w28, [x21, 736]
	mov	x1, x21
	strb	w26, [x21, 1]
	strb	w25, [x21, 2]
	strb	w24, [x21, 3]
	strb	w23, [x21, 4]
	strb	w3, [x21, 5]
	str	w2, [x21, 740]
	str	w22, [x21, 744]
	bl	MVC_ProcessSPS
	cbnz	w0, .L2501
	ldr	x1, [x19, 272]
	mov	x0, x21
	add	x1, x1, x20
	bl	MVC_SPSEqual
	cbnz	w0, .L2502
.L2462:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2467:
	cmp	w21, 122
	beq	.L2470
	cmp	w21, 144
	beq	.L2470
	cmp	w21, 110
	beq	.L2470
.L2465:
	ldr	x1, .LC613
	mov	w2, w21
	mov	w0, 1
	mov	w28, 100
	bl	dprint_vfmw
	cmp	w20, 9
	mov	w2, w20
	bhi	.L2503
	.p2align 2
.L2497:
	ldr	x1, .LC615
	mov	w3, 41
	mov	w0, 1
	mov	w20, 3992
	bl	dprint_vfmw
	umull	x20, w22, w20
	ldr	x0, [x19, 272]
	mov	w2, 41
	add	x0, x0, x20
	ldrb	w1, [x0, 25]
	cbnz	w1, .L2504
.L2473:
	str	w28, [x0, 736]
	mov	x0, x19
	ldrb	w3, [x29, 108]
	ldr	x1, [x19, 272]
	strb	w27, [x1, x20]
	ldr	x1, [x19, 272]
	add	x1, x1, x20
	strb	w26, [x1, 1]
	ldr	x1, [x19, 272]
	add	x1, x1, x20
	strb	w25, [x1, 2]
	ldr	x1, [x19, 272]
	add	x1, x1, x20
	strb	w24, [x1, 3]
	ldr	x1, [x19, 272]
	add	x1, x1, x20
	strb	w23, [x1, 4]
	ldr	x1, [x19, 272]
	add	x1, x1, x20
	strb	w3, [x1, 5]
	ldr	x1, [x19, 272]
	add	x1, x1, x20
	str	w2, [x1, 740]
	ldr	x1, [x19, 272]
	add	x1, x1, x20
	str	w22, [x1, 744]
	ldr	x1, [x19, 272]
	add	x1, x1, x20
	bl	MVC_ProcessSPS
	cbnz	w0, .L2505
	ldr	x1, [x19, 272]
	mov	w2, 1
	add	x1, x1, x20
	strb	w2, [x1, 26]
	ldr	x1, [x19, 272]
	add	x20, x1, x20
	strb	w2, [x20, 25]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2500:
	ldr	x1, .LC604
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x19, 36]
	sub	w0, w1, #1
	cmp	w22, w0
	bls	.L2498
	ldr	x0, .LC605
	ldr	x5, [x0]
	cbz	x5, .L2498
	ldr	w0, [x19, 120]
	mov	w3, 8
	stp	w22, w1, [x29, 120]
	add	x2, x29, 120
	mov	w1, 109
	blr	x5
.L2498:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, -1
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2470:
	ldr	x1, .LC611
	mov	w0, 1
	bl	dprint_vfmw
	cmp	w20, 9
	mov	w2, w20
	bhi	.L2503
	b	.L2497
	.p2align 3
.L2468:
	ldr	x1, .LC609
	mov	w0, 1
	bl	dprint_vfmw
	cmp	w20, 9
	mov	w2, w20
	bhi	.L2503
	b	.L2497
	.p2align 3
.L2502:
	ldr	x3, .LC619
	mov	w1, 1
	ldr	x0, [x19, 272]
	mov	x2, 3992
	strb	w1, [x21, 26]
	ldr	x3, [x3, 112]
	add	x0, x0, x20
	strb	w1, [x21, 25]
	mov	x1, x21
	blr	x3
	mov	w0, 0
	b	.L2462
	.p2align 3
.L2501:
	ldr	x1, .LC618
	mov	w3, w22
	mov	w2, 11150
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2462
.L2505:
	ldr	x1, .LC618
	mov	w2, 11177
	mov	w3, w22
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 272]
	mov	w2, 1
	mov	w0, -1
	add	x1, x1, x20
	strb	w2, [x1, 26]
	ldr	x1, [x19, 272]
	add	x20, x1, x20
	strb	wzr, [x20, 25]
	b	.L2462
	.size	MVC_DecSPS, .-MVC_DecSPS
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
.LC604:
	.xword	.LC397
	.align	3
.LC605:
	.xword	g_event_report
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
.LC616:
	.xword	.LANCHOR2
	.align	3
.LC618:
	.xword	.LC617
	.align	3
.LC619:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_FreeMvcExtMem
	.type	MVC_FreeMvcExtMem, %function
MVC_FreeMvcExtMem:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	MVC_FreeMvcExtMem, .-MVC_FreeMvcExtMem
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_FreeMvcVuiExtMem
	.type	MVC_FreeMvcVuiExtMem, %function
MVC_FreeMvcVuiExtMem:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	MVC_FreeMvcVuiExtMem, .-MVC_FreeMvcVuiExtMem
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ProcessSUBSPSMvcExt
	.type	MVC_ProcessSUBSPSMvcExt, %function
MVC_ProcessSUBSPSMvcExt:
	stp	x29, x30, [sp, -160]!
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
	cbz	x19, .L2568
	ldr	x1, .LC624
	mov	x0, x20
	bl	mvc_ue_v
	cmp	w0, 1
	str	w0, [x19, 4]
	bhi	.L2511
	ldrb	w1, [x20, 10]
	cbnz	w1, .L2511
	ldr	x22, .LC628
	mov	w21, 0
	.p2align 2
.L2513:
	mov	x1, x22
	mov	x0, x20
	bl	mvc_ue_v
	add	x1, x19, x21, uxtw 2
	add	w21, w21, 1
	str	w0, [x1, 8]
	ldr	w0, [x19, 4]
	cmp	w0, w21
	bcs	.L2513
	str	wzr, [x19, 16]
	str	wzr, [x19, 24]
	cbz	w0, .L2514
	ldr	x27, .LC630
	mov	w25, 1
	ldr	x23, .LC636
	mov	w26, 15
	ldr	x24, .LC640
	.p2align 2
.L2524:
	uxtw	x22, w25
	mov	x1, x27
	mov	x0, x20
	add	x21, x19, x22, lsl 2
	bl	mvc_ue_v
	str	w0, [x21, 16]
	ldr	w1, [x19, 4]
	cmp	w1, 15
	csel	w1, w1, w26, ls
	cmp	w0, w1
	bhi	.L2515
	ldrb	w1, [x20, 10]
	cbnz	w1, .L2515
	mov	w28, 0
	cbz	w0, .L2520
	.p2align 2
.L2519:
	mov	x1, x23
	mov	x0, x20
	bl	mvc_ue_v
	add	x1, x22, x28, uxtw
	add	w28, w28, 1
	add	x1, x1, 8
	str	w0, [x19, x1, lsl 2]
	ldr	w0, [x21, 16]
	cmp	w28, w0
	bcc	.L2519
.L2520:
	ldr	x1, .LC632
	mov	x0, x20
	bl	mvc_ue_v
	str	w0, [x21, 24]
	ldr	w1, [x19, 4]
	cmp	w1, 15
	csel	w2, w1, w26, ls
	cmp	w0, w2
	bhi	.L2517
	ldrb	w2, [x20, 10]
	cbnz	w2, .L2517
	mov	w28, 0
	cbz	w0, .L2522
	.p2align 2
.L2523:
	mov	x1, x24
	mov	x0, x20
	bl	mvc_ue_v
	add	x1, x22, x28, uxtw
	add	w28, w28, 1
	add	x1, x1, 10
	str	w0, [x19, x1, lsl 2]
	ldr	w0, [x21, 24]
	cmp	w28, w0
	bcc	.L2523
	ldr	w1, [x19, 4]
.L2522:
	add	w25, w25, 1
	cmp	w1, w25
	bcs	.L2524
	str	wzr, [x19, 48]
	str	wzr, [x19, 56]
	cbz	w1, .L2538
	ldr	x27, .LC644
	mov	w25, 1
	ldr	x23, .LC650
	mov	w26, 15
	ldr	x24, .LC654
	.p2align 2
.L2537:
	uxtw	x22, w25
	mov	x1, x27
	mov	x0, x20
	add	x21, x19, x22, lsl 2
	bl	mvc_ue_v
	str	w0, [x21, 48]
	ldr	w1, [x19, 4]
	cmp	w1, 15
	csel	w1, w1, w26, ls
	cmp	w0, w1
	bhi	.L2528
	ldrb	w1, [x20, 10]
	cbnz	w1, .L2528
	mov	w28, 0
	cbz	w0, .L2533
	.p2align 2
.L2532:
	mov	x1, x23
	mov	x0, x20
	bl	mvc_ue_v
	add	x1, x22, x28, uxtw
	add	w28, w28, 1
	add	x1, x1, 16
	str	w0, [x19, x1, lsl 2]
	ldr	w0, [x21, 48]
	cmp	w28, w0
	bcc	.L2532
.L2533:
	ldr	x1, .LC646
	mov	x0, x20
	bl	mvc_ue_v
	str	w0, [x21, 56]
	ldr	w1, [x19, 4]
	cmp	w1, 15
	csel	w2, w1, w26, ls
	cmp	w0, w2
	bhi	.L2530
	ldrb	w2, [x20, 10]
	cbnz	w2, .L2530
	mov	w28, 0
	cbz	w0, .L2535
	.p2align 2
.L2536:
	mov	x1, x24
	mov	x0, x20
	bl	mvc_ue_v
	add	x1, x22, x28, uxtw
	add	w28, w28, 1
	add	x1, x1, 18
	str	w0, [x19, x1, lsl 2]
	ldr	w0, [x21, 56]
	cmp	w28, w0
	bcc	.L2536
	ldr	w1, [x19, 4]
.L2535:
	add	w25, w25, 1
	cmp	w25, w1
	bls	.L2537
.L2538:
	ldr	x1, .LC642
	mov	x0, x20
	bl	mvc_ue_v
	add	w1, w0, 1
	cmp	w1, 16
	str	w0, [x19, 80]
	str	w1, [x29, 140]
	bhi	.L2526
	ldrb	w0, [x20, 10]
	cbnz	w0, .L2526
	ldr	w0, [x29, 140]
	cbz	w0, .L2543
	add	x0, x19, 8192
	ldr	x22, .LC672
	add	x1, x19, 84
	add	x0, x0, 212
	stp	x1, x19, [x29, 120]
	stp	xzr, x0, [x29, 104]
	str	wzr, [x29, 144]
.L2542:
	ldr	x2, .LC658
	mov	w1, 8
	mov	x0, x20
	bl	mvc_u_v
	ldr	x21, [x29, 120]
	ldr	x1, .LC660
	str	w0, [x21]
	mov	x0, x20
	bl	mvc_ue_v
	add	w27, w0, 1
	cmp	w27, 64
	str	w0, [x21, 64]
	bhi	.L2540
	ldrb	w0, [x20, 10]
	cbnz	w0, .L2540
	cbz	w27, .L2551
	ldp	x26, x25, [x29, 104]
	ldr	x23, [x29, 128]
	mov	w24, 0
.L2541:
	ldr	x2, .LC664
	mov	w1, 3
	mov	x0, x20
	bl	mvc_u_v
	str	w0, [x23, 212]
	ldr	x1, .LC666
	mov	x0, x20
	bl	mvc_ue_v
	add	w2, w0, 1
	cmp	w2, 64
	str	w0, [x23, 4308]
	bhi	.L2544
	ldrb	w1, [x20, 10]
	cbnz	w1, .L2544
	cbz	w2, .L2549
	add	x21, x26, x0, uxtw
	mov	x28, x25
	add	x21, x21, 2102
	add	x21, x19, x21, lsl 2
	.p2align 2
.L2548:
	mov	x1, x22
	mov	x0, x20
	bl	mvc_ue_v
	str	w0, [x28], 4
	cmp	x28, x21
	bne	.L2548
.L2549:
	ldr	x1, .LC668
	mov	x0, x20
	bl	mvc_ue_v
	cmp	w0, 1023
	add	x1, x23, 270336
	str	w0, [x1, 212]
	bhi	.L2546
	ldrb	w1, [x20, 10]
	cbnz	w1, .L2546
	add	w24, w24, 1
	add	x23, x23, 4
	cmp	w27, w24
	add	x25, x25, 256
	add	x26, x26, 64
	bne	.L2541
.L2551:
	ldr	x1, [x29, 120]
	ldr	w0, [x29, 144]
	add	x1, x1, 4
	str	x1, [x29, 120]
	ldr	w1, [x29, 140]
	add	w0, w0, 1
	str	w0, [x29, 144]
	cmp	w1, w0
	ldr	x0, [x29, 128]
	add	x0, x0, 256
	str	x0, [x29, 128]
	ldr	x0, [x29, 112]
	add	x0, x0, 16384
	str	x0, [x29, 112]
	ldr	x0, [x29, 104]
	add	x0, x0, 4096
	str	x0, [x29, 104]
	bne	.L2542
.L2543:
	mov	w0, 0
	b	.L2563
	.p2align 3
.L2515:
	ldr	x1, .LC634
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L2563:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
.L2517:
	ldr	x1, .LC638
	mov	w2, w0
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
.L2528:
	ldr	x1, .LC648
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2563
.L2511:
	ldr	x1, .LC626
	mov	w3, 65534
	mov	w2, w0
	str	w3, [x19, 80]
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2563
.L2530:
	ldr	x1, .LC652
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2563
.L2514:
	str	wzr, [x19, 48]
	str	wzr, [x19, 56]
	b	.L2538
.L2546:
	ldr	x1, .LC674
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2563
.L2544:
	ldr	x0, [x29, 144]
	mov	w3, 65534
	ldr	x1, .LC670
	ubfiz	x28, x0, 6, 32
	mov	w0, 1
	add	x24, x28, x24, uxtw
	add	x19, x19, x24, lsl 2
	str	w3, [x19, 4308]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2563
.L2568:
	ldr	x2, .LC621
	mov	w3, 11297
	ldr	x1, .LC622
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2563
.L2526:
	mov	w0, 65534
	ldr	x1, .LC656
	ldr	w2, [x29, 140]
	str	w0, [x19, 80]
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2563
.L2540:
	ldr	x0, [x29, 144]
	mov	w3, 65534
	ldr	x1, .LC662
	mov	w2, w27
	add	x19, x19, x0, uxtw 2
	mov	w0, 1
	str	w3, [x19, 148]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2563
	.size	MVC_ProcessSUBSPSMvcExt, .-MVC_ProcessSUBSPSMvcExt
	.align	3
.LC621:
	.xword	.LC36
	.align	3
.LC622:
	.xword	.LC38
	.align	3
.LC624:
	.xword	.LC623
	.align	3
.LC626:
	.xword	.LC625
	.align	3
.LC628:
	.xword	.LC627
	.align	3
.LC630:
	.xword	.LC629
	.align	3
.LC632:
	.xword	.LC631
	.align	3
.LC634:
	.xword	.LC633
	.align	3
.LC636:
	.xword	.LC635
	.align	3
.LC638:
	.xword	.LC637
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
.LC650:
	.xword	.LC649
	.align	3
.LC652:
	.xword	.LC651
	.align	3
.LC654:
	.xword	.LC653
	.align	3
.LC656:
	.xword	.LC655
	.align	3
.LC658:
	.xword	.LC657
	.align	3
.LC660:
	.xword	.LC659
	.align	3
.LC662:
	.xword	.LC661
	.align	3
.LC664:
	.xword	.LC663
	.align	3
.LC666:
	.xword	.LC665
	.align	3
.LC668:
	.xword	.LC667
	.align	3
.LC670:
	.xword	.LC669
	.align	3
.LC672:
	.xword	.LC671
	.align	3
.LC674:
	.xword	.LC673
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ProcessSUBSPSMvcVuiExt
	.type	MVC_ProcessSUBSPSMvcVuiExt, %function
MVC_ProcessSUBSPSMvcVuiExt:
	stp	x29, x30, [sp, -224]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	mov	x27, x1
	bl	_mcount
	add	x0, x27, 278528
	ldr	x1, .LC676
	mov	x20, x0
	mov	x0, x19
	str	x20, [x29, 120]
	bl	mvc_ue_v
	cmp	w0, 1023
	str	w0, [x20, 560]
	bhi	.L2602
	ldr	x2, [x29, 120]
	uxtw	x0, w0
	add	x0, x0, 1
	add	x1, x27, 294912
	str	x0, [x29, 128]
	add	x0, x2, 432
	ldr	x26, .LC688
	add	x25, x1, 1368
	str	x0, [x29, 184]
	add	x0, x2, 820
	str	x27, [x29, 152]
	stp	x27, x27, [x29, 168]
	str	xzr, [x29, 192]
	str	x0, [x29, 160]
	.p2align 2
.L2588:
	ldr	x3, [x29, 168]
	mov	w1, 3
	ldr	x2, .LC680
	mov	x0, x19
	add	x3, x3, 278528
	mov	x20, x3
	ldr	w3, [x29, 192]
	str	w3, [x29, 148]
	str	x20, [x29, 200]
	bl	mvc_u_v
	strb	w0, [x20, 112]
	ldr	x1, .LC682
	mov	x0, x19
	bl	mvc_ue_v
	cmp	w0, 1023
	ldr	x1, [x29, 176]
	add	x1, x1, 278528
	str	w0, [x1, 564]
	bhi	.L2603
	cmn	w0, #1
	beq	.L2578
	uxtw	x20, w0
	ldr	x0, [x29, 192]
	ldr	x21, [x29, 160]
	add	x20, x20, x0, lsl 6
	add	x20, x20, 69632
	add	x20, x20, 206
	add	x20, x27, x20, lsl 2
	.p2align 2
.L2577:
	mov	x1, x26
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x21], 4
	cmp	x20, x21
	bne	.L2577
.L2578:
	ldr	x1, .LC686
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	ldr	x1, [x29, 200]
	strb	w0, [x1, 368]
	cbnz	w0, .L2604
.L2576:
	ldr	x1, .LC696
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	ldr	x1, [x29, 184]
	strb	w0, [x1]
	cbz	w0, .L2579
	ldr	x2, [x29, 152]
	mov	x0, x19
	ldr	x1, .LC698
	add	x2, x2, 294912
	str	x2, [x29, 136]
	mov	x20, x2
	bl	mvc_ue_v
	str	w0, [x25]
	ldr	x2, .LC700
	mov	w1, 4
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 1364]
	ldr	x2, .LC702
	mov	w1, 4
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 1365]
	ldr	w0, [x25]
	cmp	w0, 31
	bhi	.L2581
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2581
	ldr	x0, [x29, 192]
	mov	w28, 0
	ldr	w23, [x29, 148]
	and	x24, x0, 4294967295
	ldr	x22, .LC705
	lsl	x1, x24, 3
	lsl	x0, x23, 3
	sub	x1, x1, x24
	sub	x0, x0, x23
	lsl	x1, x1, 1
	lsl	x0, x0, 1
	sub	x1, x1, x24
	sub	x0, x0, x23
	lsl	x24, x1, 2
	lsl	x23, x0, 2
	sub	x24, x24, x1
	sub	x0, x23, x0
	lsl	x1, x24, 1
	str	x1, [x29, 216]
	ldr	x1, [x29, 120]
	mov	w24, w28
	ldr	x21, .LC707
	mov	x28, x25
	add	x23, x1, 112
	ldr	x20, .LC709
	add	x0, x23, x0, lsl 3
	str	x0, [x29, 208]
	.p2align 2
.L2582:
	mov	x1, x22
	mov	x0, x19
	uxtw	x23, w24
	add	w24, w24, 1
	bl	mvc_ue_v
	ldr	x1, [x29, 216]
	add	x1, x1, x23
	add	x1, x27, x1, lsl 2
	add	x25, x1, 294912
	mov	x1, x21
	str	w0, [x25, 1372]
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x25, 1500]
	mov	x1, x20
	mov	x0, x19
	bl	mvc_u_1
	ldr	x1, [x29, 208]
	add	x23, x1, x23
	add	x23, x23, 16384
	strb	w0, [x23, 1220]
	ldr	w0, [x28]
	cmp	w0, w24
	bcs	.L2582
	ldr	x2, .LC711
	mov	w1, 5
	mov	x0, x19
	mov	x25, x28
	bl	mvc_u_v
	ldr	x20, [x29, 136]
	ldr	x2, .LC713
	mov	w1, 5
	str	w0, [x20, 1628]
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 1632]
	ldr	x2, .LC715
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 1636]
	ldr	x2, .LC717
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 1640]
.L2579:
	ldr	x20, [x29, 200]
	mov	x0, x19
	ldr	x1, .LC719
	add	x2, x20, 496
	str	x2, [x29, 136]
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 496]
	cbnz	w0, .L2605
	ldr	x0, [x29, 184]
	ldrb	w0, [x0]
	cbz	w0, .L2586
.L2587:
	ldr	x1, .LC721
	mov	x0, x19
	bl	mvc_u_1
	ldr	x1, [x29, 200]
	strb	w0, [x1, 176]
.L2586:
	ldr	x2, [x29, 192]
	mov	x0, x19
	ldr	x1, .LC723
	add	x25, x25, 312
	add	x2, x2, 1
	mov	x20, x2
	ldr	x2, [x29, 168]
	str	x20, [x29, 192]
	add	x2, x2, 1
	str	x2, [x29, 168]
	ldr	x2, [x29, 176]
	add	x2, x2, 4
	str	x2, [x29, 176]
	ldr	x2, [x29, 152]
	add	x2, x2, 312
	str	x2, [x29, 152]
	bl	mvc_u_1
	ldr	w1, [x29, 148]
	add	w1, w1, 1
	cmp	w1, 63
	ldr	x1, [x29, 200]
	strb	w0, [x1, 304]
	ldr	x0, [x29, 128]
	ccmp	x0, x20, 0, ls
	ldr	x0, [x29, 184]
	add	x0, x0, 1
	str	x0, [x29, 184]
	ldr	x0, [x29, 160]
	add	x0, x0, 256
	str	x0, [x29, 160]
	bhi	.L2588
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, 0
	ldp	x29, x30, [sp], 224
	ret
	.p2align 3
.L2604:
	ldr	x0, [x29, 176]
	mov	w1, 32
	ldr	x2, .LC690
	add	x20, x0, 294912
	mov	x0, x19
	bl	mvc_u_v
	ldr	x2, .LC692
	mov	w1, 32
	str	w0, [x20, 820]
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 1076]
	ldr	x1, .LC694
	mov	x0, x19
	bl	mvc_u_1
	ldr	x1, [x29, 200]
	strb	w0, [x1, 240]
	b	.L2576
	.p2align 3
.L2605:
	ldr	x1, .LC698
	mov	x0, x19
	bl	mvc_ue_v
	ldr	x1, [x29, 152]
	ldr	x2, .LC700
	add	x1, x1, 315392
	mov	x20, x1
	str	x20, [x29, 112]
	str	w0, [x1, 856]
	mov	w1, 4
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 852]
	ldr	x2, .LC702
	mov	w1, 4
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 853]
	ldr	w0, [x20, 856]
	add	x5, x20, 856
	cmp	w0, 31
	bhi	.L2581
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2581
	ldr	x0, [x29, 192]
	ldr	w23, [x29, 148]
	and	x24, x0, 4294967295
	ldr	x22, .LC705
	lsl	x1, x24, 3
	lsl	x0, x23, 3
	sub	x1, x1, x24
	sub	x0, x0, x23
	lsl	x1, x1, 1
	lsl	x0, x0, 1
	sub	x1, x1, x24
	sub	x0, x0, x23
	lsl	x24, x1, 2
	lsl	x23, x0, 2
	sub	x24, x24, x1
	sub	x0, x23, x0
	lsl	x1, x24, 1
	str	x1, [x29, 216]
	ldr	x1, [x29, 120]
	ldr	x21, .LC707
	add	x23, x1, 112
	ldr	x20, .LC709
	add	x0, x23, x0, lsl 3
	mov	w23, 0
	str	x25, [x29, 104]
	mov	w25, w23
	str	x0, [x29, 208]
	mov	x23, x5
	.p2align 2
.L2584:
	mov	x1, x22
	mov	x0, x19
	uxtw	x24, w25
	add	w25, w25, 1
	bl	mvc_ue_v
	ldr	x1, [x29, 216]
	add	x2, x1, x24
	mov	x1, x21
	add	x2, x27, x2, lsl 2
	add	x28, x2, 315392
	str	w0, [x28, 860]
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x28, 988]
	mov	x1, x20
	mov	x0, x19
	bl	mvc_u_1
	ldr	x1, [x29, 208]
	add	x24, x1, x24
	add	x24, x24, 36864
	strb	w0, [x24, 708]
	ldr	w0, [x23]
	cmp	w0, w25
	bcs	.L2584
	ldr	x2, .LC711
	mov	w1, 5
	mov	x0, x19
	ldr	x25, [x29, 104]
	bl	mvc_u_v
	ldr	x20, [x29, 112]
	ldr	x2, .LC713
	mov	w1, 5
	str	w0, [x20, 1116]
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 1120]
	ldr	x2, .LC715
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 1124]
	ldr	x2, .LC717
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 1128]
	ldr	x0, [x29, 184]
	ldrb	w0, [x0]
	cbnz	w0, .L2587
	ldr	x0, [x29, 136]
	ldrb	w0, [x0]
	cbnz	w0, .L2587
	b	.L2586
	.p2align 3
.L2581:
	ldr	x1, .LC703
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L2598:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 224
	ret
.L2603:
	ldr	x1, .LC684
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 224
	ret
.L2602:
	ldr	x1, .LC678
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2598
	.size	MVC_ProcessSUBSPSMvcVuiExt, .-MVC_ProcessSUBSPSMvcVuiExt
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
.LC682:
	.xword	.LC681
	.align	3
.LC684:
	.xword	.LC683
	.align	3
.LC686:
	.xword	.LC685
	.align	3
.LC688:
	.xword	.LC687
	.align	3
.LC690:
	.xword	.LC689
	.align	3
.LC692:
	.xword	.LC691
	.align	3
.LC694:
	.xword	.LC693
	.align	3
.LC696:
	.xword	.LC695
	.align	3
.LC698:
	.xword	.LC697
	.align	3
.LC700:
	.xword	.LC699
	.align	3
.LC702:
	.xword	.LC701
	.align	3
.LC703:
	.xword	.LC451
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecSubSPS
	.type	MVC_DecSubSPS, %function
MVC_DecSubSPS:
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
	ldr	x2, .LC725
	mov	w1, 8
	mov	x0, x19
	bl	mvc_u_v
	mov	w20, w0
	ldr	x1, .LC727
	mov	x0, x19
	bl	mvc_u_1
	mov	w27, w0
	ldr	x1, .LC729
	mov	x0, x19
	bl	mvc_u_1
	mov	w26, w0
	ldr	x1, .LC731
	mov	x0, x19
	bl	mvc_u_1
	mov	w25, w0
	ldr	x1, .LC733
	mov	x0, x19
	bl	mvc_u_1
	str	w0, [x29, 120]
	ldr	x1, .LC735
	mov	x0, x19
	bl	mvc_u_1
	str	w0, [x29, 116]
	ldr	x1, .LC737
	mov	x0, x19
	bl	mvc_u_1
	mov	w22, w0
	ldr	x2, .LC739
	mov	w1, 2
	mov	x0, x19
	bl	mvc_u_v
	ldr	x2, .LC741
	mov	w1, 8
	mov	x0, x19
	bl	mvc_u_v
	mov	w21, w0
	ldr	x1, .LC743
	mov	x0, x19
	bl	mvc_ue_v
	mov	w4, w0
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2619
	cmp	w4, 31
	bhi	.L2629
	sub	w0, w20, #66
	cmp	w0, 78
	bls	.L2630
.L2609:
	ldr	x1, .LC750
	mov	w2, w20
	mov	w0, 1
	mov	w21, -1
	bl	dprint_vfmw
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2630:
	ldr	x1, .LC745
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx2611
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx2611:
	.section	.rodata
	.align	0
	.align	2
.L2611:
	.byte	(.L2610 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2612 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2613 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2612 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2614 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2612 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2614 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2612 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2609 - .Lrtx2611) / 4
	.byte	(.L2614 - .Lrtx2611) / 4
	.text
	.p2align 3
.L2610:
	ldr	x1, .LC746
	mov	w0, 1
	str	w4, [x29, 104]
	bl	dprint_vfmw
	ldr	w4, [x29, 104]
.L2612:
	cmp	w21, 41
	bhi	.L2631
.L2615:
	uxtw	x23, w4
	mov	x0, x19
	lsl	x1, x23, 3
	sub	x1, x1, x23
	lsl	x1, x1, 2
	sub	x1, x1, x23
	lsl	x1, x1, 4
	sub	x1, x1, x23
	lsl	x2, x1, 2
	sub	x1, x2, x1
	lsl	x2, x1, 6
	add	x2, x1, x2
	lsl	x24, x2, 2
	ldrb	w2, [x29, 120]
	add	x5, x19, x24
	add	x1, x24, 286720
	add	x28, x5, 286720
	add	x1, x19, x1
	add	x1, x1, 2612
	str	x5, [x29, 104]
	strb	w2, [x28, 2615]
	ldrb	w2, [x29, 116]
	str	w21, [x28, 3352]
	strb	w27, [x28, 2612]
	strb	w26, [x28, 2613]
	strb	w25, [x28, 2614]
	strb	w2, [x28, 2616]
	strb	w22, [x28, 2617]
	str	w20, [x28, 3348]
	str	w4, [x28, 3356]
	bl	MVC_ProcessSPS
	mov	w21, w0
	ldr	x5, [x29, 104]
	cbnz	w0, .L2632
	mov	w1, 128
	cmp	w20, 118
	mov	w0, 1
	ccmp	w20, w1, 4, ne
	strb	w0, [x28, 2637]
	beq	.L2633
.L2617:
	lsl	x0, x23, 3
	mov	w2, 1
	sub	x0, x0, x23
	lsl	x0, x0, 2
	sub	x0, x0, x23
	lsl	x0, x0, 4
	sub	x0, x0, x23
	lsl	x1, x0, 2
	sub	x0, x1, x0
	lsl	x1, x0, 6
	add	x0, x0, x1
	add	x19, x19, x0, lsl 2
	add	x19, x19, 12288
	strb	w2, [x19, 2396]
.L2607:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2631:
	ldr	x1, .LC752
	mov	w2, w21
	mov	w0, 1
	str	w4, [x29, 104]
	mov	w21, 41
	bl	dprint_vfmw
	ldr	w4, [x29, 104]
	b	.L2615
	.p2align 3
.L2633:
	ldr	x1, .LC756
	add	x22, x5, 12288
	mov	x0, x19
	add	x20, x24, 12288
	add	x20, x19, x20
	bl	mvc_u_1
	add	x20, x20, 2396
	strb	w0, [x22, 2397]
	mov	x1, x20
	mov	x0, x19
	bl	MVC_ProcessSUBSPSMvcExt
	cbnz	w0, .L2634
	ldr	x1, .LC760
	mov	x0, x19
	bl	mvc_u_1
	str	w0, [x28, 2608]
	cbz	w0, .L2617
	mov	x1, x20
	mov	x0, x19
	bl	MVC_ProcessSUBSPSMvcVuiExt
	cbz	w0, .L2617
	ldr	x1, .LC762
	mov	w0, 1
	mov	w21, -1
	bl	dprint_vfmw
	strb	wzr, [x22, 2396]
	b	.L2607
	.p2align 3
.L2614:
	ldr	x1, .LC748
	mov	w0, 1
	str	w4, [x29, 104]
	bl	dprint_vfmw
	ldr	w4, [x29, 104]
	b	.L2612
	.p2align 3
.L2613:
	ldr	x1, .LC747
	mov	w0, 1
	str	w4, [x29, 104]
	bl	dprint_vfmw
	ldr	w4, [x29, 104]
	b	.L2612
	.p2align 3
.L2619:
	mov	w21, -1
	b	.L2607
	.p2align 3
.L2629:
	ldr	x1, .LC744
	mov	w0, 1
	mov	w21, -1
	bl	dprint_vfmw
	b	.L2607
	.p2align 3
.L2632:
	ldr	x1, .LC754
	mov	w0, 1
	str	x5, [x29, 120]
	mov	w21, -1
	bl	dprint_vfmw
	ldr	x5, [x29, 120]
	add	x5, x5, 12288
	strb	wzr, [x5, 2396]
	strb	wzr, [x28, 2637]
	b	.L2607
.L2634:
	ldr	x1, .LC758
	mov	w0, 1
	mov	w21, -1
	bl	dprint_vfmw
	strb	wzr, [x22, 2396]
	b	.L2607
	.size	MVC_DecSubSPS, .-MVC_DecSubSPS
	.align	3
.LC725:
	.xword	.LC724
	.align	3
.LC727:
	.xword	.LC726
	.align	3
.LC729:
	.xword	.LC728
	.align	3
.LC731:
	.xword	.LC730
	.align	3
.LC733:
	.xword	.LC732
	.align	3
.LC735:
	.xword	.LC734
	.align	3
.LC737:
	.xword	.LC736
	.align	3
.LC739:
	.xword	.LC738
	.align	3
.LC741:
	.xword	.LC740
	.align	3
.LC743:
	.xword	.LC742
	.align	3
.LC744:
	.xword	.LC397
	.align	3
.LC745:
	.xword	.L2611
	.align	3
.LC746:
	.xword	.LC606
	.align	3
.LC747:
	.xword	.LC608
	.align	3
.LC748:
	.xword	.LC610
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_PassBytes
	.type	MVC_PassBytes, %function
MVC_PassBytes:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldr	x0, [x20, 240]
	cmp	w19, wzr
	ccmp	x0, xzr, 4, ne
	beq	.L2644
	ldrb	w2, [x0]
	sbfiz	x1, x2, 5, 32
	add	x1, x0, x1
	ldr	x1, [x1, 8]
	cbz	x1, .L2644
	ldr	w1, [x0, 76]
	cmp	w2, 1
	ccmp	w1, 2, 2, ls
	bhi	.L2644
	cmp	w1, w2
	bls	.L2644
	uxtw	x5, w2
	add	x3, x0, x5, lsl 5
	ldr	w1, [x3, 28]
	ldr	w3, [x3, 16]
	add	w1, w1, w19, lsl 3
	lsl	w3, w3, 3
	cmp	w1, w3
	bhi	.L2639
	b	.L2637
	.p2align 3
.L2640:
	ldr	w4, [x6, 28]
	ldr	w6, [x6, 16]
	sub	w4, w4, w3
	add	w1, w1, w4
	lsl	w3, w6, 3
	cmp	w1, w3
	bls	.L2637
.L2639:
	add	x0, x0, x5, lsl 5
	add	w5, w2, 1
	mov	x2, x5
	str	w3, [x0, 28]
	ldr	x0, [x20, 240]
	ldrb	w4, [x0]
	add	w4, w4, 1
	strb	w4, [x0]
	ldr	x0, [x20, 240]
	add	x6, x0, x5, lsl 5
	ldr	w4, [x0, 76]
	cmp	w4, w5
	bhi	.L2640
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2637:
	add	x5, x0, x5, lsl 5
	mov	w0, 1
	str	w1, [x5, 28]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2644:
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_PassBytes, .-MVC_PassBytes
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetBytes
	.type	MVC_GetBytes, %function
MVC_GetBytes:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x19, x1
	mov	x0, x30
	mov	w20, w2
	bl	_mcount
	cbz	x19, .L2660
	ldr	x1, [x21, 240]
	cmp	x1, xzr
	ccmp	w20, wzr, 4, ne
	beq	.L2660
	ldrb	w2, [x1]
	sbfiz	x0, x2, 5, 32
	add	x0, x1, x0
	ldr	x0, [x0, 8]
	cbz	x0, .L2660
	ldr	w0, [x1, 76]
	cmp	w2, 1
	ccmp	w0, 2, 2, ls
	bhi	.L2660
	cmp	w0, w2
	bls	.L2660
	mov	w6, 0
.L2655:
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
	bcs	.L2650
	ldrb	w0, [x4, x0]
	add	w6, w6, 1
	strb	w0, [x19]
	cmp	w20, w6
	add	x19, x19, 1
	add	x5, x5, 1
	ldr	x0, [x21, 240]
	add	x0, x0, x7
	ldr	w3, [x0, 28]
	add	w3, w3, 8
	str	w3, [x0, 28]
	bhi	.L2653
	b	.L2652
	.p2align 3
.L2654:
	ldrb	w1, [x5], 1
	add	w6, w6, 1
	strb	w1, [x19], 1
	cmp	w20, w6
	ldr	x3, [x21, 240]
	add	x3, x3, x7
	ldr	w4, [x3, 28]
	add	w4, w4, 8
	str	w4, [x3, 28]
	bls	.L2652
.L2653:
	cmp	x8, x5
	bne	.L2654
	ldr	x1, [x21, 240]
.L2650:
	ldrb	w0, [x1]
	add	w2, w2, 1
	add	w0, w0, 1
	strb	w0, [x1]
	ldr	x1, [x21, 240]
	ldr	w0, [x1, 76]
	cmp	w0, w2
	bhi	.L2655
	mov	w0, w6
	b	.L2649
	.p2align 3
.L2652:
	mov	w0, w20
.L2649:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2660:
	mov	w0, -1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	MVC_GetBytes, .-MVC_GetBytes
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecFramePackingSEI
	.type	MVC_DecFramePackingSEI, %function
MVC_DecFramePackingSEI:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 11124736
	bl	_mcount
	add	x20, x21, 360
	ldr	x1, .LC764
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 24]
	ldr	x2, .LC766
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	sxtb	w0, w0
	strb	w0, [x20, 1]
	cbz	w0, .L2668
.L2663:
	ldr	x2, .LC798
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x21, 362]
	mov	w1, 1
	strb	w1, [x21, 360]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2668:
	ldr	x2, .LC768
	mov	w1, 7
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 16]
	ldr	x2, .LC770
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 3]
	ldr	x2, .LC772
	mov	w1, 6
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 20]
	ldr	x2, .LC774
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 4]
	ldr	x2, .LC776
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 5]
	ldr	x2, .LC778
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 6]
	ldr	x2, .LC780
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 7]
	ldr	x2, .LC782
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 8]
	ldr	x2, .LC784
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 9]
	ldrsb	w1, [x20, 3]
	cbnz	w1, .L2664
	ldr	w0, [x20, 16]
	cmp	w0, 5
	beq	.L2664
	ldr	x2, .LC786
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 10]
	ldr	x2, .LC788
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 11]
	ldr	x2, .LC790
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 12]
	ldr	x2, .LC792
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 13]
.L2664:
	ldr	x2, .LC794
	mov	w1, 8
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x21, 388]
	ldr	x1, .LC796
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x21, 392]
	b	.L2663
	.size	MVC_DecFramePackingSEI, .-MVC_DecFramePackingSEI
	.align	3
.LC764:
	.xword	.LC763
	.align	3
.LC766:
	.xword	.LC765
	.align	3
.LC768:
	.xword	.LC767
	.align	3
.LC770:
	.xword	.LC769
	.align	3
.LC772:
	.xword	.LC771
	.align	3
.LC774:
	.xword	.LC773
	.align	3
.LC776:
	.xword	.LC775
	.align	3
.LC778:
	.xword	.LC777
	.align	3
.LC780:
	.xword	.LC779
	.align	3
.LC782:
	.xword	.LC781
	.align	3
.LC784:
	.xword	.LC783
	.align	3
.LC786:
	.xword	.LC785
	.align	3
.LC788:
	.xword	.LC787
	.align	3
.LC790:
	.xword	.LC789
	.align	3
.LC792:
	.xword	.LC791
	.align	3
.LC794:
	.xword	.LC793
	.align	3
.LC796:
	.xword	.LC795
	.align	3
.LC798:
	.xword	.LC797
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecPicTimingSEI
	.type	MVC_DecPicTimingSEI, %function
MVC_DecPicTimingSEI:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, 3992
	bl	_mcount
	add	x0, x20, 11112448
	ldr	x3, [x20, 272]
	ldr	w0, [x0, 312]
	umull	x19, w0, w19
	add	x19, x3, x19
	ldrb	w0, [x19, 25]
	cbnz	w0, .L2670
	ldr	w0, [x20, 36]
	cmp	w0, wzr
	ble	.L2671
	ldrb	w1, [x3, 25]
	cbnz	w1, .L2689
	sub	w1, w0, #1
	add	x0, x3, 3992
	add	x1, x1, 1
	lsl	x2, x1, 6
	sub	x2, x2, x1
	lsl	x2, x2, 1
	sub	x2, x2, x1
	lsl	x2, x2, 2
	sub	x1, x2, x1
	add	x1, x3, x1, lsl 3
	b	.L2674
	.p2align 3
.L2675:
	ldrb	w2, [x2]
	cbnz	w2, .L2672
.L2674:
	cmp	x0, x1
	mov	x19, x0
	add	x0, x0, 3992
	sub	x2, x0, #3967
	bne	.L2675
.L2671:
	ldr	x1, .LC800
	mov	w0, 1
	mov	w19, -1
	bl	dprint_vfmw
.L2676:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L2689:
	mov	x19, x3
	.p2align 2
.L2672:
	cbz	x19, .L2671
.L2670:
	ldrb	w0, [x19, 24]
	cbz	w0, .L2677
	ldrb	w0, [x19, 35]
	cbz	w0, .L2690
	ldr	w1, [x19, 388]
	ldr	w22, [x19, 392]
	add	w1, w1, 1
	add	w22, w22, 1
.L2680:
	ldr	x2, .LC802
	mov	x0, x20
	add	x21, x20, 11124736
	bl	mvc_u_v
	ldr	x2, .LC804
	mov	w1, w22
	str	w0, [x21, 400]
	mov	x0, x20
	bl	mvc_u_v
	str	w0, [x21, 404]
.L2677:
	ldrb	w0, [x19, 39]
	mov	w19, 0
	cbz	w0, .L2676
	ldr	x2, .LC806
	mov	x0, x20
	add	x20, x20, 11124736
	mov	w1, 4
	bl	mvc_u_v
	strb	w0, [x20, 396]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2690:
	ldrb	w0, [x19, 38]
	cbz	w0, .L2677
	ldr	w1, [x19, 700]
	ldr	w22, [x19, 704]
	add	w1, w1, 1
	add	w22, w22, 1
	b	.L2680
	.size	MVC_DecPicTimingSEI, .-MVC_DecPicTimingSEI
	.align	3
.LC800:
	.xword	.LC799
	.align	3
.LC802:
	.xword	.LC801
	.align	3
.LC804:
	.xword	.LC803
	.align	3
.LC806:
	.xword	.LC805
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecSEI
	.type	MVC_DecSEI, %function
MVC_DecSEI:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x26, x0
	mov	x0, x30
	add	x21, x29, 128
	mov	w23, 0
	bl	_mcount
	add	x20, x26, 872
	ldr	x0, [x26, 240]
	mov	w1, 32
	strb	wzr, [x21, -1]!
	str	w1, [x0, 28]
	b	.L2694
	.p2align 3
.L2858:
	mov	w1, 8
	mov	x0, x20
	bl	BsSkip
	cmp	w19, wzr
	ble	.L2693
	ldrb	w0, [x29, 127]
	cmp	w0, 255
	bne	.L2857
.L2694:
	mov	w2, 1
	mov	x1, x21
	mov	x0, x26
	bl	MVC_GetBytes
	mov	w19, w0
	ldr	w2, [x26, 896]
	ldr	w0, [x26, 904]
	ldrb	w1, [x29, 127]
	add	w0, w0, 8
	cmp	w0, w2, lsl 3
	add	w23, w23, w1
	bls	.L2858
.L2693:
	ldr	x1, .LC808
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2696
	.p2align 3
.L2857:
	ldr	x25, .LC814
	mov	w24, 0
	ldr	x22, .LC811
	add	x0, x25, 240
	str	x0, [x29, 104]
	.p2align 2
.L2831:
	mov	w19, 0
	b	.L2700
	.p2align 3
.L2860:
	mov	w1, 8
	mov	x0, x20
	bl	BsSkip
	cmp	w28, wzr
	ble	.L2698
	ldrb	w0, [x29, 127]
	cmp	w0, 255
	bne	.L2859
.L2700:
	mov	w2, 1
	mov	x1, x21
	mov	x0, x26
	bl	MVC_GetBytes
	mov	w28, w0
	ldr	w2, [x26, 896]
	ldr	w0, [x26, 904]
	ldrb	w1, [x29, 127]
	add	w0, w0, 8
	cmp	w0, w2, lsl 3
	add	w19, w19, w1
	bls	.L2860
.L2698:
	ldr	x1, .LC810
	mov	w0, 1
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
.L2859:
	cmp	w19, 409600
	bgt	.L2698
	ldr	x0, [x26, 240]
	ldr	w1, [x0, 76]
	ldr	w2, [x0, 28]
	cmp	w1, 2
	beq	.L2861
.L2702:
	cmp	w23, 45
	bls	.L2862
.L2703:
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2863
.L2823:
	cmp	w19, wzr
	ble	.L2729
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
	mov	w23, 0
	b	.L2824
	.p2align 3
.L2825:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
.L2824:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2825
	.p2align 2
.L2729:
	ldr	w0, [x26, 60]
	cmp	w0, 3
	bhi	.L2864
.L2826:
	mov	w23, 0
	b	.L2830
	.p2align 3
.L2828:
	mov	w1, 8
	mov	x0, x20
	bl	BsSkip
	cmp	w19, wzr
	ble	.L2829
	ldrb	w0, [x29, 127]
	cmp	w0, 255
	bne	.L2865
.L2830:
	mov	w2, 1
	mov	x1, x21
	mov	x0, x26
	bl	MVC_GetBytes
	mov	w19, w0
	ldr	w2, [x26, 896]
	ldr	w0, [x26, 904]
	ldrb	w1, [x29, 127]
	add	w0, w0, 8
	cmp	w0, w2, lsl 3
	add	w23, w23, w1
	bls	.L2828
.L2829:
	mov	w0, 0
.L2696:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2865:
	cmp	w0, 128
	bne	.L2831
	b	.L2829
	.p2align 3
.L2862:
	ldrh	w0, [x22,w23,uxtw #1]
	adr	x1, .Lrtx2705
	add	x0, x1, w0, sxth #2
	br	x0
.Lrtx2705:
	.section	.rodata
	.align	0
	.align	2
.L2705:
	.2byte	(.L2704 - .Lrtx2705) / 4
	.2byte	(.L2706 - .Lrtx2705) / 4
	.2byte	(.L2707 - .Lrtx2705) / 4
	.2byte	(.L2708 - .Lrtx2705) / 4
	.2byte	(.L2709 - .Lrtx2705) / 4
	.2byte	(.L2710 - .Lrtx2705) / 4
	.2byte	(.L2711 - .Lrtx2705) / 4
	.2byte	(.L2712 - .Lrtx2705) / 4
	.2byte	(.L2713 - .Lrtx2705) / 4
	.2byte	(.L2714 - .Lrtx2705) / 4
	.2byte	(.L2715 - .Lrtx2705) / 4
	.2byte	(.L2716 - .Lrtx2705) / 4
	.2byte	(.L2717 - .Lrtx2705) / 4
	.2byte	(.L2718 - .Lrtx2705) / 4
	.2byte	(.L2719 - .Lrtx2705) / 4
	.2byte	(.L2720 - .Lrtx2705) / 4
	.2byte	(.L2721 - .Lrtx2705) / 4
	.2byte	(.L2722 - .Lrtx2705) / 4
	.2byte	(.L2723 - .Lrtx2705) / 4
	.2byte	(.L2724 - .Lrtx2705) / 4
	.2byte	(.L2725 - .Lrtx2705) / 4
	.2byte	(.L2726 - .Lrtx2705) / 4
	.2byte	(.L2703 - .Lrtx2705) / 4
	.2byte	(.L2703 - .Lrtx2705) / 4
	.2byte	(.L2703 - .Lrtx2705) / 4
	.2byte	(.L2703 - .Lrtx2705) / 4
	.2byte	(.L2703 - .Lrtx2705) / 4
	.2byte	(.L2703 - .Lrtx2705) / 4
	.2byte	(.L2703 - .Lrtx2705) / 4
	.2byte	(.L2703 - .Lrtx2705) / 4
	.2byte	(.L2703 - .Lrtx2705) / 4
	.2byte	(.L2703 - .Lrtx2705) / 4
	.2byte	(.L2703 - .Lrtx2705) / 4
	.2byte	(.L2703 - .Lrtx2705) / 4
	.2byte	(.L2703 - .Lrtx2705) / 4
	.2byte	(.L2703 - .Lrtx2705) / 4
	.2byte	(.L2703 - .Lrtx2705) / 4
	.2byte	(.L2703 - .Lrtx2705) / 4
	.2byte	(.L2703 - .Lrtx2705) / 4
	.2byte	(.L2703 - .Lrtx2705) / 4
	.2byte	(.L2703 - .Lrtx2705) / 4
	.2byte	(.L2703 - .Lrtx2705) / 4
	.2byte	(.L2703 - .Lrtx2705) / 4
	.2byte	(.L2703 - .Lrtx2705) / 4
	.2byte	(.L2703 - .Lrtx2705) / 4
	.2byte	(.L2727 - .Lrtx2705) / 4
	.text
.L2727:
	mov	w1, w19
	mov	x0, x26
	ldr	w28, [x26, 904]
	bl	MVC_DecFramePackingSEI
	ldr	w3, [x26, 904]
	sub	w0, w3, w28
	lsl	w28, w19, 3
	cmp	w0, w28
	bge	.L2817
	sub	w28, w28, w0
	ldr	w0, [x26, 896]
	cmp	w28, wzr
	add	w23, w28, 7
	csel	w23, w23, w28, lt
	lsl	w0, w0, 3
	asr	w23, w23, 3
	cmp	w23, wzr
	ble	.L2819
	add	w1, w3, 8
	cmp	w1, w0
	bhi	.L2819
	mov	w27, 0
	b	.L2820
	.p2align 3
.L2821:
	ldr	w0, [x26, 896]
	ldr	w3, [x26, 904]
	lsl	w0, w0, 3
	add	w1, w3, 8
	cmp	w1, w0
	bhi	.L2819
.L2820:
	mov	w1, 8
	mov	x0, x20
	add	w27, w27, 1
	bl	BsSkip
	cmp	w27, w23
	bne	.L2821
	ldr	w0, [x26, 896]
	ldr	w3, [x26, 904]
	lsl	w0, w0, 3
.L2819:
	asr	w1, w28, 31
	lsr	w2, w1, 29
	add	w1, w28, w2
	and	w1, w1, 7
	sub	w1, w1, w2
	add	w3, w1, w3
	cmp	w3, w0
	bls	.L2866
.L2817:
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbz	w0, #31, .L2729
	ldr	x1, .LC816
	mov	w3, 12772
	ldr	x2, .LC870
	mov	w0, 20
	bl	dprint_vfmw
	b	.L2729
.L2726:
	ldr	x1, .LC867
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2867
.L2813:
	cmp	w19, wzr
	ble	.L2729
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
	mov	w23, 0
	b	.L2814
	.p2align 3
.L2815:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
.L2814:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2815
	ldr	w0, [x26, 60]
	cmp	w0, 3
	bls	.L2826
.L2864:
	ldr	x1, .LC869
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L2725:
	ldr	x1, .LC865
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2868
.L2810:
	cmp	w19, wzr
	ble	.L2729
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
	mov	w23, 0
	b	.L2811
	.p2align 3
.L2812:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
.L2811:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2812
	b	.L2729
.L2724:
	ldr	x1, .LC863
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2869
.L2807:
	cmp	w19, wzr
	ble	.L2729
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
	mov	w23, 0
	b	.L2808
	.p2align 3
.L2809:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
.L2808:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2809
	b	.L2729
.L2723:
	ldr	x1, .LC861
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2870
.L2804:
	cmp	w19, wzr
	ble	.L2729
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
	mov	w23, 0
	b	.L2805
	.p2align 3
.L2806:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
.L2805:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2806
	b	.L2729
.L2722:
	ldr	x1, .LC859
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2871
.L2801:
	cmp	w19, wzr
	ble	.L2729
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
	mov	w23, 0
	b	.L2802
	.p2align 3
.L2803:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
.L2802:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2803
	b	.L2729
.L2721:
	ldr	x1, .LC857
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2872
.L2798:
	cmp	w19, wzr
	ble	.L2729
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
	mov	w23, 0
	b	.L2799
	.p2align 3
.L2800:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
.L2799:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2800
	b	.L2729
.L2720:
	ldr	x1, .LC855
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2873
.L2795:
	cmp	w19, wzr
	ble	.L2729
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
	mov	w23, 0
	b	.L2796
	.p2align 3
.L2797:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
.L2796:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2797
	b	.L2729
.L2719:
	ldr	x1, .LC853
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2874
.L2792:
	cmp	w19, wzr
	ble	.L2729
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
	mov	w23, 0
	b	.L2793
	.p2align 3
.L2794:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
.L2793:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2794
	b	.L2729
.L2718:
	ldr	x1, .LC851
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2875
.L2789:
	cmp	w19, wzr
	ble	.L2729
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
	mov	w23, 0
	b	.L2790
	.p2align 3
.L2791:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
.L2790:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2791
	b	.L2729
.L2717:
	ldr	x1, .LC849
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2876
.L2786:
	cmp	w19, wzr
	ble	.L2729
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
	mov	w23, 0
	b	.L2787
	.p2align 3
.L2788:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
.L2787:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2788
	b	.L2729
.L2716:
	ldr	x1, .LC847
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2877
.L2783:
	cmp	w19, wzr
	ble	.L2729
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
	mov	w23, 0
	b	.L2784
	.p2align 3
.L2785:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
.L2784:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2785
	b	.L2729
.L2715:
	ldr	x1, .LC845
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2878
.L2780:
	cmp	w19, wzr
	ble	.L2729
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
	mov	w23, 0
	b	.L2781
	.p2align 3
.L2782:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
.L2781:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2782
	b	.L2729
.L2714:
	ldr	x1, .LC843
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2879
.L2777:
	cmp	w19, wzr
	ble	.L2729
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
	mov	w23, 0
	b	.L2778
	.p2align 3
.L2779:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
.L2778:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2779
	b	.L2729
.L2713:
	ldr	x1, .LC841
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2880
.L2774:
	cmp	w19, wzr
	ble	.L2729
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
	mov	w23, 0
	b	.L2775
	.p2align 3
.L2776:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
.L2775:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2776
	b	.L2729
.L2712:
	ldr	x1, .LC839
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2881
.L2771:
	cmp	w19, wzr
	ble	.L2729
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
	mov	w23, 0
	b	.L2772
	.p2align 3
.L2773:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
.L2772:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2773
	b	.L2729
.L2711:
	ldr	x1, .LC837
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	cmp	w19, wzr
	ble	.L2768
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2768
	mov	w23, 0
	b	.L2769
	.p2align 3
.L2770:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2768
.L2769:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2770
.L2768:
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbz	w0, #31, .L2729
	ldr	x2, .LC814
	mov	w3, 12344
	ldr	x1, .LC816
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2729
.L2710:
	cbnz	w24, .L2709
	ldr	x1, .LC826
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
.L2746:
	ldr	w23, [x26, 60]
	ldr	w0, [x26, 120]
	add	x23, x26, x23, uxtw 3
	bl	GetUsd
	str	x0, [x23, 832]
	ldr	w0, [x26, 60]
	add	x0, x0, 104
	ldr	x1, [x26, x0, lsl 3]
	cbz	x1, .L2834
	ldr	x5, [x26, 240]
	cmp	w19, 1024
	mov	w7, 1024
	csel	w27, w19, w7, le
	ldrb	w3, [x5]
	ldr	w6, [x5, 76]
	cmp	w3, w6
	bcs	.L2835
	mov	w28, 0
	.p2align 2
.L2748:
	ubfiz	x2, x3, 5, 32
	add	w3, w3, 1
	add	x2, x5, x2
	cmp	w3, w6
	ldr	w0, [x2, 28]
	ldr	w2, [x2, 16]
	add	w0, w0, 7
	sub	w0, w2, w0, lsr 3
	add	w28, w28, w0
	bne	.L2748
	mov	w0, w28
.L2747:
	cmp	w27, w0
	csel	w28, w28, w27, gt
	cbnz	w24, .L2882
	mov	w23, 0
	mov	w25, 0
.L2750:
	sub	w2, w28, w23
	mov	x0, x26
	bl	MVC_GetBytes
	cmp	w0, wzr
	mov	w28, w0
	ble	.L2883
	sub	w0, w27, w25
	cmp	w28, w0
	blt	.L2884
	ldr	w0, [x26, 60]
	sub	w23, w19, w25
	cmp	w27, w19
	add	x0, x0, 104
	ldr	x0, [x26, x0, lsl 3]
	str	w23, [x0, 1052]
	bcc	.L2885
.L2762:
	cmp	w23, wzr
	ble	.L2756
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2756
	mov	w19, 0
	b	.L2764
	.p2align 3
.L2765:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2756
.L2764:
	mov	w1, 8
	mov	x0, x20
	add	w19, w19, 1
	bl	BsSkip
	cmp	w23, w19
	bne	.L2765
.L2756:
	ldr	w0, [x26, 60]
	cmp	w24, 1
	ldr	x1, [x26, 224]
	mov	w2, 9
	add	x0, x0, 104
	ldr	x1, [x1, 56]
	ldr	x0, [x26, x0, lsl 3]
	str	x1, [x0, 1056]
	ldr	w0, [x26, 60]
	add	x0, x0, 104
	ldr	x1, [x26, x0, lsl 3]
	mov	w0, 8
	csel	w0, w0, w2, eq
	str	w0, [x1, 1040]
.L2855:
	ldr	w0, [x26, 60]
	ldr	x1, .LC833
	add	x0, x0, 104
	ldr	x5, [x1]
	ldr	x0, [x26, x0, lsl 3]
	ldr	w1, [x26, 84]
	str	w1, [x0, 1044]
	cbz	x5, .L2729
	ldr	w0, [x26, 60]
	mov	w3, 1064
	mov	w1, 6
	add	x0, x0, 104
	ldr	x2, [x26, x0, lsl 3]
	ldr	w0, [x26, 120]
	blr	x5
	b	.L2729
.L2708:
	ldr	x1, .LC822
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2886
.L2742:
	cmp	w19, wzr
	ble	.L2729
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
	mov	w23, 0
	b	.L2743
	.p2align 3
.L2744:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
.L2743:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2744
	b	.L2729
.L2707:
	ldr	x1, .LC820
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2887
.L2739:
	cmp	w19, wzr
	ble	.L2729
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
	mov	w23, 0
	b	.L2740
	.p2align 3
.L2741:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
.L2740:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2741
	b	.L2729
.L2706:
	ldr	x1, .LC818
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	ldr	w28, [x26, 904]
	mov	w1, w19
	mov	x0, x26
	bl	MVC_DecPicTimingSEI
	ldr	w3, [x26, 904]
	sub	w0, w3, w28
	lsl	w28, w19, 3
	cmp	w0, w28
	bge	.L2733
	sub	w28, w28, w0
	ldr	w0, [x26, 896]
	cmp	w28, wzr
	add	w23, w28, 7
	csel	w23, w23, w28, lt
	lsl	w0, w0, 3
	asr	w23, w23, 3
	cmp	w23, wzr
	ble	.L2735
	add	w1, w3, 8
	cmp	w1, w0
	bhi	.L2735
	mov	w25, 0
	b	.L2736
	.p2align 3
.L2737:
	ldr	w0, [x26, 896]
	ldr	w3, [x26, 904]
	lsl	w0, w0, 3
	add	w1, w3, 8
	cmp	w1, w0
	bhi	.L2735
.L2736:
	mov	w1, 8
	mov	x0, x20
	add	w25, w25, 1
	bl	BsSkip
	cmp	w25, w23
	bne	.L2737
	ldr	w0, [x26, 896]
	ldr	w3, [x26, 904]
	lsl	w0, w0, 3
.L2735:
	asr	w1, w28, 31
	lsr	w2, w1, 29
	add	w1, w28, w2
	and	w1, w1, 7
	sub	w1, w1, w2
	add	w3, w1, w3
	cmp	w3, w0
	bls	.L2888
.L2733:
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbz	w0, #31, .L2729
	ldr	x2, .LC814
	mov	w3, 12125
	ldr	x1, .LC816
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2729
.L2704:
	ldr	x1, .LC813
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2889
.L2728:
	cmp	w19, wzr
	ble	.L2729
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
	mov	w23, 0
	b	.L2730
	.p2align 3
.L2731:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2729
.L2730:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2731
	b	.L2729
	.p2align 3
.L2861:
	ldr	w0, [x0, 60]
	add	w2, w2, w0
	lsr	w2, w2, 3
	b	.L2702
.L2884:
	ldr	w0, [x26, 60]
	add	x0, x0, 104
	ldr	x0, [x26, x0, lsl 3]
	str	w28, [x0, 1052]
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2756
	mov	w19, 0
	b	.L2757
	.p2align 3
.L2760:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2756
.L2757:
	mov	w1, 8
	mov	x0, x20
	add	w19, w19, 1
	bl	BsSkip
	cmp	w28, w19
	bne	.L2760
	b	.L2756
.L2709:
	ldr	x1, .LC824
	mov	w3, w19
	mov	w0, 20
	mov	w24, 1
	bl	dprint_vfmw
	b	.L2746
.L2882:
	strb	w24, [x1, 1026]
	mov	x0, x26
	ldr	x2, .LC828
	mov	w1, 8
	ldr	w3, [x26, 60]
	add	x3, x3, 104
	ldr	x23, [x26, x3, lsl 3]
	bl	mvc_u_v
	strb	w0, [x23, 1027]
	ldr	w0, [x26, 60]
	add	x0, x0, 104
	ldr	x23, [x26, x0, lsl 3]
	ldrb	w0, [x23, 1027]
	cmp	w0, 255
	beq	.L2751
	strb	wzr, [x23, 1028]
	mov	w23, 3
	mov	w25, w23
.L2752:
	ldr	w0, [x26, 60]
	mov	w1, 16
	ldr	x2, .LC832
	add	x0, x0, 104
	ldr	x5, [x26, x0, lsl 3]
	mov	x0, x26
	str	x5, [x29, 96]
	bl	mvc_u_v
	ldr	x5, [x29, 96]
	mov	w1, w23
	strh	w0, [x5, 1030]
	mov	x0, x26
	bl	MVC_PassBytes
	ldr	w0, [x26, 60]
	cmp	w28, w23
	add	x0, x0, 104
	beq	.L2753
	ldr	x1, [x26, x0, lsl 3]
	b	.L2750
.L2879:
	ldr	x2, .LC814
	mov	w3, 12408
	ldr	x1, .LC816
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2777
.L2887:
	ldr	x2, .LC814
	mov	w3, 12137
	ldr	x1, .LC816
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2739
.L2889:
	ldr	x2, .LC814
	mov	w3, 12072
	ldr	x1, .LC816
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2728
.L2871:
	ldr	x2, .LC814
	mov	w3, 12616
	ldr	x1, .LC816
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2801
.L2876:
	ldr	x2, .LC814
	mov	w3, 12486
	ldr	x1, .LC816
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2786
.L2877:
	ldr	x2, .LC814
	mov	w3, 12460
	ldr	x1, .LC816
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2783
.L2874:
	ldr	x2, .LC814
	mov	w3, 12538
	ldr	x1, .LC816
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2792
.L2875:
	ldr	x2, .LC814
	mov	w3, 12512
	ldr	x1, .LC816
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2789
.L2880:
	ldr	x2, .LC814
	mov	w3, 12382
	ldr	x1, .LC816
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2774
.L2881:
	ldr	x2, .LC814
	mov	w3, 12356
	ldr	x1, .LC816
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2771
.L2878:
	ldr	x2, .LC814
	mov	w3, 12434
	ldr	x1, .LC816
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2780
.L2866:
	mov	x0, x20
	bl	BsSkip
	b	.L2817
.L2888:
	mov	x0, x20
	bl	BsSkip
	b	.L2733
.L2868:
	ldr	x2, .LC814
	mov	w3, 12694
	ldr	x1, .LC816
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2810
.L2869:
	ldr	x2, .LC814
	mov	w3, 12668
	ldr	x1, .LC816
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2807
.L2863:
	ldr	x1, .LC816
	mov	w3, 12784
	ldr	x2, [x29, 104]
	mov	w0, 20
	bl	dprint_vfmw
	b	.L2823
.L2867:
	ldr	x1, .LC816
	mov	w3, 12720
	ldr	x2, .LC870
	mov	w0, 20
	bl	dprint_vfmw
	b	.L2813
.L2886:
	ldr	x2, .LC814
	mov	w3, 12163
	ldr	x1, .LC816
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2742
.L2872:
	ldr	x2, .LC814
	mov	w3, 12590
	ldr	x1, .LC816
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2798
.L2873:
	ldr	x2, .LC814
	mov	w3, 12564
	ldr	x1, .LC816
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2795
.L2870:
	ldr	x2, .LC814
	mov	w3, 12642
	ldr	x1, .LC816
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2804
.L2885:
	sub	w1, w19, w27
	mov	x0, x26
	bl	MVC_PassBytes
	tbz	w0, #31, .L2762
	ldr	x2, .LC814
	mov	w3, 12295
	ldr	x1, .LC816
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2762
.L2835:
	mov	w0, 0
	mov	w28, 0
	b	.L2747
.L2753:
	ldr	x1, [x26, 224]
	ldr	x0, [x26, x0, lsl 3]
	ldr	x1, [x1, 56]
	str	x1, [x0, 1056]
	mov	w1, 8
	ldr	w0, [x26, 60]
	add	x0, x0, 104
	ldr	x0, [x26, x0, lsl 3]
	str	w1, [x0, 1040]
	b	.L2855
.L2751:
	ldr	x2, .LC830
	mov	w1, 8
	mov	x0, x26
	bl	mvc_u_v
	strb	w0, [x23, 1028]
	mov	w23, 4
	mov	w25, w23
	b	.L2752
.L2834:
	mov	w0, -1
	b	.L2696
.L2883:
	ldr	x1, .LC835
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x26, 60]
	ldr	w0, [x26, 120]
	add	x1, x1, 104
	ldr	x1, [x26, x1, lsl 3]
	bl	FreeUsdByDec
	ldr	w1, [x26, 60]
	mov	w0, -1
	add	x1, x1, 104
	str	xzr, [x26, x1, lsl 3]
	b	.L2696
	.size	MVC_DecSEI, .-MVC_DecSEI
	.align	3
.LC808:
	.xword	.LC807
	.align	3
.LC810:
	.xword	.LC809
	.align	3
.LC811:
	.xword	.L2705
	.align	3
.LC813:
	.xword	.LC812
	.align	3
.LC814:
	.xword	.LANCHOR0
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
.LC833:
	.xword	g_event_report
	.align	3
.LC835:
	.xword	.LC834
	.align	3
.LC837:
	.xword	.LC836
	.align	3
.LC839:
	.xword	.LC838
	.align	3
.LC841:
	.xword	.LC840
	.align	3
.LC843:
	.xword	.LC842
	.align	3
.LC845:
	.xword	.LC844
	.align	3
.LC847:
	.xword	.LC846
	.align	3
.LC849:
	.xword	.LC848
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
.LC857:
	.xword	.LC856
	.align	3
.LC859:
	.xword	.LC858
	.align	3
.LC861:
	.xword	.LC860
	.align	3
.LC863:
	.xword	.LC862
	.align	3
.LC865:
	.xword	.LC864
	.align	3
.LC867:
	.xword	.LC866
	.align	3
.LC869:
	.xword	.LC868
	.align	3
.LC870:
	.xword	.LANCHOR0+240
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_InitOldSlice
	.type	MVC_InitOldSlice, %function
MVC_InitOldSlice:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 11120640
	mov	w4, 32
	ldr	w8, [x19, 40]
	mov	w7, 23352
	movk	w7, 0x1, lsl 16
	mov	w6, 2
	strb	w4, [x0, 402]
	add	x4, x0, 256
	strb	wzr, [x0, 400]
	mov	w5, 7
	strb	w6, [x0, 401]
	mov	w3, 3
	strb	w5, [x0, 403]
	mov	w2, -1
	str	w8, [x0, 412]
	mov	w1, 262144
	str	w7, [x0, 416]
	stp	w3, w2, [x4, 168]
	stp	wzr, wzr, [x4, 176]
	str	w1, [x0, 440]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_InitOldSlice, .-MVC_InitOldSlice
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_IsNewPicNal
	.type	MVC_IsNewPicNal, %function
MVC_IsNewPicNal:
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
	bls	.L2900
.L2899:
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2900:
	ldr	x1, .LC871
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx2894
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx2894:
	.section	.rodata
	.align	0
	.align	2
.L2894:
	.byte	(.L2893 - .Lrtx2894) / 4
	.byte	(.L2899 - .Lrtx2894) / 4
	.byte	(.L2899 - .Lrtx2894) / 4
	.byte	(.L2899 - .Lrtx2894) / 4
	.byte	(.L2893 - .Lrtx2894) / 4
	.byte	(.L2899 - .Lrtx2894) / 4
	.byte	(.L2895 - .Lrtx2894) / 4
	.byte	(.L2895 - .Lrtx2894) / 4
	.text
	.p2align 3
.L2895:
	ldr	w0, [x19]
	mov	w1, 1
	str	w1, [x19]
	cmp	w0, wzr
	csetm	w0, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2893:
	ldr	w0, [x19]
	cbz	w0, .L2896
.L2898:
	mov	w0, -1
	str	wzr, [x19]
.L2901:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2896:
	ldr	w20, [x20, 4]
	rev	w20, w20
	mov	w0, w20
	bl	ZerosMS_32
	cmp	w0, 15
	bhi	.L2898
	mov	w1, 31
	str	wzr, [x19]
	sub	w0, w1, w0, lsl 1
	lsr	w20, w20, w0
	cmp	w20, 1
	csetm	w0, ne
	b	.L2901
	.size	MVC_IsNewPicNal, .-MVC_IsNewPicNal
	.align	3
.LC871:
	.xword	.L2894
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_FindZeroBitsInSeg
	.type	MVC_FindZeroBitsInSeg, %function
MVC_FindZeroBitsInSeg:
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
	ble	.L2922
	and	w1, w23, 63
	add	w0, w23, 63
	cmp	w1, wzr
	cset	w26, ne
	cmp	w23, wzr
	csel	w0, w0, w23, lt
	add	w26, w26, w0, asr 6
	cmp	w26, wzr
	ble	.L2915
	ldr	x20, .LC875
	mov	w25, w23
	ldr	x27, .LC874
	mov	w19, 0
	mov	w24, 64
	add	x20, x20, 1880
	.p2align 2
.L2914:
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
	cbnz	w1, .L2906
	cmp	x0, x20
	add	w19, w19, 1
	bne	.L2909
	b	.L2907
	.p2align 3
.L2910:
	add	w19, w19, 1
	beq	.L2907
.L2909:
	ldrb	w1, [x0, -1]!
	cmp	x0, x20
	cbz	w1, .L2910
.L2906:
	lsl	w0, w19, 3
.L2905:
	cmp	w19, w23
	mov	w1, 0
	bge	.L2911
	sxtw	x2, w23
	sub	x2, x2, #1
	sub	x19, x2, x19, sxtw
	ldrb	w2, [x22, x19]
	tbnz	x2, 0, .L2911
	lsr	w2, w2, 1
	mov	w1, 1
	.p2align 2
.L2913:
	tbnz	x2, 0, .L2911
	add	w1, w1, 1
	lsr	w2, w2, 1
	cmp	w1, 8
	bne	.L2913
.L2911:
	add	w0, w1, w0
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L2907:
	subs	w26, w26, #1
	sub	w25, w25, #64
	bne	.L2914
	b	.L2906
.L2922:
	ldr	x1, .LC873
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
.L2915:
	mov	w0, 0
	mov	w19, 0
	b	.L2905
	.size	MVC_FindZeroBitsInSeg, .-MVC_FindZeroBitsInSeg
	.align	3
.LC873:
	.xword	.LC872
	.align	3
.LC874:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC875:
	.xword	.LANCHOR3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_FindTrailZeros
	.type	MVC_FindTrailZeros, %function
MVC_FindTrailZeros:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L2929
	ldr	x2, [x19, 240]
	ldr	w0, [x2, 76]
	cmp	w0, 1
	bls	.L2928
	ldr	w1, [x2, 48]
	ldr	x0, [x2, 40]
	bl	MVC_FindZeroBitsInSeg
	ldr	x2, [x19, 240]
	ldr	w1, [x2, 48]
	cmp	w0, w1, lsl 3
	bcs	.L2932
	cmn	w0, #1
	beq	.L2928
	add	w0, w0, 1
	str	w0, [x2, 80]
	ldr	x0, [x19, 240]
	ldr	w1, [x0, 76]
	cmp	w1, 1
	bls	.L2930
.L2933:
	ldr	w2, [x0, 48]
	mov	w20, 0
	ldr	w1, [x0, 80]
	cmp	w1, w2, lsl 3
	bcc	.L2924
	ldr	w1, [x0, 68]
	ldr	w0, [x19, 120]
	bl	SM_ReleaseStreamSeg
	ldr	x0, [x19, 240]
	mov	w1, 1
	str	xzr, [x0, 40]
	ldr	x0, [x19, 240]
	str	w1, [x0, 76]
	ldr	x0, [x19, 240]
	str	wzr, [x0, 80]
.L2924:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2932:
	ldr	w1, [x2, 68]
	ldr	w0, [x19, 120]
	bl	SM_ReleaseStreamSeg
	ldr	x0, [x19, 240]
	mov	w1, 1
	str	xzr, [x0, 40]
	ldr	x0, [x19, 240]
	str	w1, [x0, 76]
	ldr	x2, [x19, 240]
.L2928:
	ldr	w1, [x2, 16]
	ldr	x0, [x2, 8]
	bl	MVC_FindZeroBitsInSeg
	add	w0, w0, 1
	ldr	x2, [x19, 240]
	str	w0, [x2, 80]
	ldr	x0, [x19, 240]
	ldr	w1, [x0, 76]
	cmp	w1, 1
	bhi	.L2933
.L2930:
	mov	w20, 0
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L2929:
	mov	w20, -1
	b	.L2924
	.size	MVC_FindTrailZeros, .-MVC_FindTrailZeros
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_CombinePacket
	.type	MVC_CombinePacket, %function
MVC_CombinePacket:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 240]
	ldr	w0, [x0, 16]
	cmp	w0, 4095
	bhi	.L2934
	mov	x0, x19
	bl	MVC_CombinePacket.part.13
.L2934:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_CombinePacket, .-MVC_CombinePacket
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_FindNaluArraySlot
	.type	MVC_FindNaluArraySlot, %function
MVC_FindNaluArraySlot:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x19, 1521]
	cbz	w0, .L2941
	add	x0, x19, 1617
	mov	x1, 1
	b	.L2939
	.p2align 3
.L2938:
	add	w1, w1, 1
	cmp	w1, 137
	beq	.L2944
.L2939:
	ldrb	w2, [x0]
	add	x0, x0, 96
	cbnz	w2, .L2938
	mov	w0, w1
.L2937:
	lsl	x2, x1, 2
	mov	w3, 1
	sub	x1, x2, x1
	add	x1, x19, x1, lsl 5
	strb	w3, [x1, 1521]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2944:
	mov	w0, -1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L2941:
	mov	w0, 0
	mov	x1, 0
	b	.L2937
	.size	MVC_FindNaluArraySlot, .-MVC_FindNaluArraySlot
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_InquireSliceProperty
	.type	MVC_InquireSliceProperty, %function
MVC_InquireSliceProperty:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x23, x1
	mov	x21, x2
	bl	_mcount
	add	x20, x19, 11116544
	ldr	w2, [x19, 68]
	mov	w0, 22
	ldr	x1, .LC878
	sub	w2, w2, #1
	bl	dprint_vfmw
	str	wzr, [x21]
	str	wzr, [x23]
	add	x2, x19, 11120640
	add	x0, x19, 12288
	mov	w3, -1
	ldr	x1, [x19, 240]
	ldrb	w4, [x1, 2]
	strb	w4, [x20, 2843]
	ldrb	w5, [x1, 4]
	strb	w5, [x20, 2848]
	ldrsb	w1, [x1, 5]
	strb	w1, [x20, 2852]
	strb	wzr, [x20, 2851]
	str	w3, [x2, 384]
	ldrb	w3, [x0, 2384]
	cmp	w3, 1
	beq	.L2981
	cmn	w1, #1
	beq	.L2982
.L2947:
	mov	x0, x19
	bl	MVC_SliceCheck
	mov	w22, w0
	cbnz	w0, .L2963
	mov	x0, x19
	bl	MVC_ProcessSliceHeaderFirstPart
	cbnz	w0, .L2983
	ldrb	w1, [x20, 2845]
	mov	w0, 2240
	cmp	w1, 1
	cset	w1, eq
	str	w1, [x23]
	ldr	w1, [x20, 2856]
	ldrsb	w2, [x20, 2852]
	ldr	x3, [x19, 280]
	umull	x0, w1, w0
	cmn	w2, #1
	add	x0, x3, x0
	beq	.L2984
	cbnz	w2, .L2959
	ldrb	w1, [x19, 2]
	cmp	w1, 1
	beq	.L2985
	ldr	w1, [x0, 28]
	add	x0, x19, 11046912
	ldr	w2, [x19, 28]
	add	x0, x0, 180
	cmp	w2, w1
	bne	.L2986
.L2958:
	ldrb	w1, [x0, 20]
	mov	w2, 2
	ldr	w5, [x0, 3952]
	sub	w1, w2, w1
	ldr	w2, [x0, 3948]
	ldp	w3, w4, [x19, 12]
	madd	w1, w5, w1, w1
	add	w2, w2, 1
	cmp	w1, w4
	ccmp	w2, w3, 0, eq
	beq	.L2962
	mov	w1, 1
	str	w1, [x21]
.L2962:
	add	x19, x19, 11124736
	ldr	w1, [x0, 3972]
	ldr	w0, [x19, 792]
	add	w0, w0, 1
	cmp	w1, w0
	bls	.L2955
	mov	w0, 1
	str	w0, [x21]
.L2955:
	mov	w0, w22
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2981:
	strb	w3, [x20, 2851]
	ldr	w1, [x19, 14680]
	str	w1, [x2, 384]
	ldrb	w1, [x0, 2388]
	strb	w1, [x20, 2849]
	ldrb	w0, [x0, 2389]
	strb	w0, [x20, 2850]
	b	.L2947
	.p2align 3
.L2984:
	ldr	w1, [x0, 28]
	mov	w0, 3992
	ldr	x2, [x19, 272]
	umull	x0, w1, w0
	add	x0, x2, x0
	b	.L2958
	.p2align 3
.L2982:
	ldr	w1, [x19, 20]
	cbz	w1, .L2947
	add	x1, x19, 10768384
	ldr	w3, [x1, 4064]
	cbnz	w3, .L2950
	ldrb	w3, [x1, 4060]
	cbnz	w3, .L2950
	add	x0, x0, 2400
	mov	x1, 0
	.p2align 2
.L2953:
	ldr	w3, [x0]
	add	x5, x0, 335872
	cbz	w3, .L2951
	ldrb	w0, [x0, -4]
	cbnz	w0, .L2987
.L2951:
	add	w1, w1, 1
	add	x0, x5, 308
	cmp	w1, 32
	bne	.L2953
	mov	w0, -1
	b	.L2980
	.p2align 3
.L2985:
	ldr	w1, [x0, 28]
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 4
	sub	x0, x0, x1
	lsl	x1, x0, 2
	sub	x1, x1, x0
	lsl	x0, x1, 6
	add	x0, x1, x0
	add	x0, x19, x0, lsl 2
	add	x0, x0, 286720
	add	x0, x0, 2612
	b	.L2958
	.p2align 3
.L2950:
	ldr	w0, [x1, 4068]
.L2980:
	cmn	w0, #1
	str	w0, [x2, 384]
	beq	.L2947
	cmp	w4, 5
	mov	w0, 1
	cset	w1, eq
	strb	w0, [x20, 2851]
	strb	w0, [x20, 2850]
	strb	w1, [x20, 2849]
	b	.L2947
	.p2align 3
.L2963:
	mov	w22, -1
	b	.L2955
	.p2align 3
.L2986:
	ldr	x1, .LC881
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L2955
	.p2align 3
.L2983:
	ldr	x1, .LC880
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L2955
	.p2align 3
.L2959:
	ldr	x1, .LC883
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L2955
	.p2align 3
.L2987:
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 4
	sub	x1, x0, x1
	lsl	x0, x1, 2
	sub	x1, x0, x1
	lsl	x0, x1, 6
	add	x0, x1, x0
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 14692]
	b	.L2980
	.size	MVC_InquireSliceProperty, .-MVC_InquireSliceProperty
	.align	3
.LC878:
	.xword	.LC877
	.align	3
.LC880:
	.xword	.LC879
	.align	3
.LC881:
	.xword	.LC90
	.align	3
.LC883:
	.xword	.LC882
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_HaveSliceToDec
	.type	MVC_HaveSliceToDec, %function
MVC_HaveSliceToDec:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 64]
	ldr	x19, [sp, 16]
	cmp	w0, wzr
	csetm	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_HaveSliceToDec, .-MVC_HaveSliceToDec
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_IsRefListWrong
	.type	MVC_IsRefListWrong, %function
MVC_IsRefListWrong:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x21, x20, 11116544
	bl	_mcount
	ldr	w0, [x21, 2888]
	cbz	w0, .L2990
	mov	w19, 0
	b	.L2994
	.p2align 3
.L2991:
	ldr	x0, [x0, 32]
	cbz	x0, .L2993
	ldr	w0, [x21, 2888]
	cmp	w0, w19
	bls	.L3018
.L2994:
	add	x1, x20, x19, sxtw 3
	ldr	w0, [x20, 120]
	add	w19, w19, 1
	ldr	x1, [x1, 288]
	ldr	x1, [x1, 8]
	ldrsb	w1, [x1, 6]
	bl	FSP_GetLogicFs
	cbnz	x0, .L2991
.L2993:
	mov	w0, -1
.L3020:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2990:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3018:
	cbz	w0, .L2990
	ldr	w0, [x21, 2892]
	mov	w19, 0
	cbnz	w0, .L3007
	b	.L2990
	.p2align 3
.L3019:
	ldr	x0, [x0, 32]
	cbz	x0, .L2993
	ldr	w0, [x21, 2892]
	cmp	w0, w19
	bls	.L2990
.L3007:
	add	x1, x20, x19, sxtw 3
	ldr	w0, [x20, 120]
	add	w19, w19, 1
	ldr	x1, [x1, 552]
	ldr	x1, [x1, 8]
	ldrsb	w1, [x1, 6]
	bl	FSP_GetLogicFs
	cbnz	x0, .L3019
	mov	w0, -1
	b	.L3020
	.size	MVC_IsRefListWrong, .-MVC_IsRefListWrong
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DEC_Destroy
	.type	MVC_DEC_Destroy, %function
MVC_DEC_Destroy:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	add	x20, x21, 12288
	add	x19, x21, 1520
	bl	_mcount
	add	x20, x20, 2384
	mov	x0, x21
	bl	MVC_ClearAllSlice
	add	x0, x21, 11120640
	mov	w1, 23352
	ldr	w2, [x21, 40]
	movk	w1, 0x1, lsl 16
	mov	w6, 2
	mov	w5, 7
	mov	w4, 32
	mov	w3, 3
	str	w2, [x0, 412]
	mov	w2, -1
	str	w1, [x0, 416]
	mov	w1, 262144
	strb	wzr, [x0, 400]
	strb	w6, [x0, 401]
	strb	w5, [x0, 403]
	strb	w4, [x0, 402]
	str	w3, [x0, 424]
	str	wzr, [x0, 432]
	str	wzr, [x0, 436]
	str	w2, [x0, 428]
	str	w1, [x0, 440]
	b	.L3023
	.p2align 3
.L3022:
	add	x19, x19, 96
	cmp	x20, x19
	beq	.L3042
.L3023:
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	bne	.L3022
	ldr	w0, [x21, 120]
	mov	x1, x19
	add	x19, x19, 96
	bl	MVC_ReleaseNAL
	cmp	x20, x19
	bne	.L3023
.L3042:
	ldr	w2, [x21, 60]
	mov	w19, 0
	cbz	w2, .L3028
	.p2align 2
.L3036:
	add	x20, x21, x19, uxtw 3
	add	w19, w19, 1
	ldr	x0, [x20, 832]
	mov	x1, x0
	cbz	x0, .L3026
	ldr	w0, [x21, 120]
	bl	FreeUsdByDec
	str	xzr, [x20, 832]
	ldr	w2, [x21, 60]
.L3026:
	cmp	w2, w19
	bhi	.L3036
.L3028:
	add	x20, x21, 11124736
	add	x22, x21, 11157504
	add	x20, x20, 1808
	add	x22, x22, 2960
	.p2align 2
.L3025:
	sub	x19, x20, #32
.L3030:
	ldr	x1, [x19]
	cbnz	x1, .L3043
.L3029:
	add	x19, x19, 8
	cmp	x19, x20
	bne	.L3030
	add	x20, x19, 848
	cmp	x20, x22
	bne	.L3025
	ldr	x1, .LC885
	mov	w0, 2
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3043:
	ldr	w0, [x21, 120]
	bl	FreeUsdByDec
	str	xzr, [x19]
	b	.L3029
	.size	MVC_DEC_Destroy, .-MVC_DEC_Destroy
	.align	3
.LC885:
	.xword	.LC884
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DEC_RecycleImage
	.type	MVC_DEC_RecycleImage, %function
MVC_DEC_RecycleImage:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w22, w1
	bl	_mcount
	ldr	x1, .LC887
	mov	w0, 2
	bl	dprint_vfmw
	ldr	w0, [x21, 120]
	mov	w1, w22
	bl	FSP_GetLogicFs
	cbz	x0, .L3049
	ldrsb	w1, [x0, 1]
	cbz	w1, .L3049
	add	x19, x0, 592
	add	x20, x0, 624
.L3047:
	ldr	x1, [x19]
	cbnz	x1, .L3054
.L3046:
	add	x19, x19, 8
	cmp	x19, x20
	bne	.L3047
	ldr	w0, [x21, 120]
	mov	w2, 0
	mov	w1, w22
	bl	FSP_SetDisplay
	mov	w0, 0
.L3045:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3054:
	ldr	w0, [x21, 120]
	bl	FreeUsdByDec
	str	xzr, [x19]
	b	.L3046
	.p2align 3
.L3049:
	mov	w0, -1
	b	.L3045
	.size	MVC_DEC_RecycleImage, .-MVC_DEC_RecycleImage
	.align	3
.LC887:
	.xword	.LC886
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_OutputFrmToVO
	.type	MVC_OutputFrmToVO, %function
MVC_OutputFrmToVO:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	w22, w2
	bl	_mcount
	cmp	x20, xzr
	cset	w21, eq
	cmp	x19, xzr
	cset	w0, eq
	orr	w0, w21, w0
	cbnz	w0, .L3092
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 24]
	cbz	w0, .L3058
	ldrb	w0, [x19, 8]
	cmp	w0, 2
	beq	.L3058
	ldr	x0, [x19, 816]
	cbz	x0, .L3060
	strb	wzr, [x0, 2]
	mov	w0, 1
	str	xzr, [x19, 816]
.L3091:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3058:
	mov	x1, x20
	mov	x0, x19
	bl	MVC_CheckFrameStore
	cmn	w0, #3
	beq	.L3060
	ldr	x1, [x19, 816]
	cbz	x1, .L3062
	mov	x0, x19
	bl	MVC_GetImagePara
	ldr	x1, [x19, 816]
	mov	x0, x19
	bl	MVC_CheckFrameStore
	mov	w23, w0
	cbz	w0, .L3093
	cmn	w0, #3
	beq	.L3070
	ldr	x1, .LC895
	mov	w3, w0
	mov	w2, 1879
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 816]
	mov	x0, x19
	ldr	w1, [x1, 220]
	bl	MVC_DEC_RecycleImage
	cmp	w23, 1
	cset	w1, eq
.L3069:
	ldr	x0, [x19, 816]
	tst	w21, w1
	strb	wzr, [x0, 2]
	str	xzr, [x19, 816]
	bne	.L3078
.L3062:
	mov	x1, x20
	mov	x0, x19
	bl	MVC_GetImagePara
	mov	x1, x20
	mov	x0, x19
	bl	MVC_CheckFrameStore
	cbz	w0, .L3094
	ldr	x1, .LC895
	mov	w3, w0
	mov	w2, 1928
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x20, 220]
	mov	x0, x19
	bl	MVC_DEC_RecycleImage
	ldr	x23, [sp, 48]
	mov	w0, 2
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3092:
	ldr	x1, .LC889
	mov	x3, x20
	mov	x2, x19
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, 2
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3094:
	ldrsb	w1, [x20, 6]
	mov	w2, 1
	ldr	w0, [x19, 120]
	bl	FSP_SetDisplay
	ldrsb	w1, [x20, 6]
	ldr	w0, [x19, 120]
	bl	FSP_GetFsImagePtr
	mov	x21, x0
	cbz	x0, .L3095
	cmp	w22, 1
	beq	.L3096
.L3074:
	ldr	w0, [x19, 120]
	mov	x4, x21
	add	x3, x19, 912
	mov	x2, x19
	mov	w1, 15
	bl	InsertImgToVoQueue
	cmp	w0, 1
	bne	.L3097
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 652]
	add	w0, w0, 2047
	cmp	w0, 4095
	bhi	.L3098
	str	wzr, [x21, 16]
.L3077:
	ldr	w1, [x19, 136]
	mov	w0, 0
	ldr	w2, [x19, 144]
	add	w1, w1, 2
	str	w1, [x19, 136]
	add	w2, w2, 1
	str	w2, [x19, 144]
	b	.L3091
	.p2align 3
.L3060:
	mov	w0, 1
	b	.L3091
	.p2align 3
.L3070:
	ldr	x0, [x19, 816]
	strb	wzr, [x0, 2]
	str	xzr, [x19, 816]
	b	.L3062
	.p2align 3
.L3093:
	ldr	x1, [x19, 816]
	mov	w2, 1
	ldr	w0, [x19, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_SetDisplay
	ldr	x1, [x19, 816]
	ldr	w0, [x19, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_GetFsImagePtr
	mov	x23, x0
	cbz	x0, .L3099
	ldr	x0, [x19, 816]
	cmp	x0, x20
	ccmp	w22, 1, 0, eq
	beq	.L3100
.L3065:
	ldr	w0, [x19, 120]
	mov	x4, x23
	add	x3, x19, 912
	mov	x2, x19
	mov	w1, 15
	bl	InsertImgToVoQueue
	cmp	w0, 1
	bne	.L3101
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 652]
	add	w0, w0, 2047
	cmp	w0, 4095
	bhi	.L3102
	str	wzr, [x23, 16]
.L3068:
	ldr	w0, [x19, 136]
	mov	w1, 1
	ldr	w2, [x19, 144]
	add	w0, w0, 2
	str	w0, [x19, 136]
	add	w2, w2, w1
	str	w2, [x19, 144]
	b	.L3069
	.p2align 3
.L3078:
	mov	w0, 0
	b	.L3091
	.p2align 3
.L3096:
	str	w22, [x0, 180]
	b	.L3074
	.p2align 3
.L3098:
	mov	x1, x21
	mov	x0, x19
	bl	MVC_SetFrmRepeatCount.part.2
	b	.L3077
	.p2align 3
.L3102:
	mov	x1, x23
	mov	x0, x19
	bl	MVC_SetFrmRepeatCount.part.2
	b	.L3068
	.p2align 3
.L3100:
	mov	w0, 1
	str	w0, [x23, 180]
	b	.L3065
.L3097:
	ldr	x1, .LC893
	mov	w2, w0
	mov	w0, 0
	bl	dprint_vfmw
	ldrsb	w1, [x20, 6]
	mov	w2, 0
	ldr	w0, [x19, 120]
	bl	FSP_SetDisplay
	mov	w1, 1
	mov	x0, x19
	bl	MVC_ClearAll
	mov	w0, -1
	b	.L3091
.L3101:
	ldr	x1, .LC893
	mov	w2, w0
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x0, [x19, 816]
	mov	w2, 0
	strb	wzr, [x0, 2]
	ldr	x1, [x19, 816]
	ldr	w0, [x19, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_SetDisplay
	str	xzr, [x19, 816]
	mov	w1, 1
	mov	x0, x19
	bl	MVC_ClearAll
	mov	w0, -1
	b	.L3091
.L3095:
	ldr	x1, .LC891
	mov	w2, 1902
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3091
.L3099:
	ldr	x1, .LC891
	mov	w2, 1850
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3091
	.size	MVC_OutputFrmToVO, .-MVC_OutputFrmToVO
	.align	3
.LC889:
	.xword	.LC888
	.align	3
.LC891:
	.xword	.LC890
	.align	3
.LC893:
	.xword	.LC892
	.align	3
.LC895:
	.xword	.LC894
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_OutputFrmFromDPB
	.type	MVC_OutputFrmFromDPB, %function
MVC_OutputFrmFromDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w1
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, x21, uxtw 3
	add	x19, x19, 11124736
	bl	_mcount
	ldr	x0, [x19, 408]
	cbz	x0, .L3105
	strb	wzr, [x0, 5]
	mov	w2, 0
	mov	x0, x20
	ldr	x1, [x19, 408]
	bl	MVC_OutputFrmToVO
	cmn	w0, #1
	ldr	x1, [x19, 408]
	csetm	w19, eq
	ldrb	w0, [x1, 3]
	cbz	w0, .L3106
	mov	w0, w19
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3106:
	mov	w1, w21
	mov	x0, x20
	bl	MVC_RemoveFrameStoreOutDPB
	ldr	x21, [sp, 32]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3105:
	mov	w19, 0
	ldr	x21, [sp, 32]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	MVC_OutputFrmFromDPB, .-MVC_OutputFrmFromDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_FlushDPB
	.type	MVC_FlushDPB, %function
MVC_FlushDPB:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cbz	x20, .L3126
	add	x21, x20, 11124736
	mov	w22, 0
	ldr	w0, [x21, 792]
	cbz	w0, .L3114
	.p2align 2
.L3148:
	uxtw	x0, w22
	add	w22, w22, 1
	add	x0, x0, 1388544
	add	x0, x20, x0, lsl 3
	ldr	x1, [x0, 16792]
	cbz	x1, .L3112
	ldrb	w0, [x1, 3]
	cbz	w0, .L3112
	ldr	w0, [x1, 56]
	cmp	w0, w19
	ccmn	w19, #1, 4, ne
	bne	.L3112
	mov	x0, x20
	bl	MVC_UnMarkFrameStoreRef
	.p2align 2
.L3112:
	ldr	w0, [x21, 792]
	cmp	w0, w22
	bhi	.L3148
.L3114:
	mov	w1, w19
	mov	x0, x20
	bl	MVC_RemoveUnUsedFrameStore
	ldr	w0, [x21, 792]
	cbz	w0, .L3111
	sub	w2, w0, #1
	mov	w22, -1
	add	x2, x2, 1388544
	add	x0, x21, 408
	add	x2, x2, 2100
	mov	w21, 0
	add	x2, x20, x2, lsl 3
	.p2align 2
.L3118:
	ldr	x1, [x0]
	cmn	w19, #1
	add	x0, x0, 8
	cbz	x1, .L3116
	ldr	w1, [x1, 56]
	ccmp	w19, w1, 4, ne
	csinc	w21, w21, w21, ne
	cmp	w19, w1
	ccmn	w19, #1, 4, ne
	csel	w22, w22, w1, eq
.L3116:
	cmp	x2, x0
	bne	.L3118
	cbz	w21, .L3111
	cmn	w22, #1
	cset	w24, ne
	cmp	w19, w22
	cset	w23, gt
	and	w23, w24, w23
	b	.L3124
	.p2align 3
.L3125:
	subs	w21, w21, #1
	beq	.L3111
.L3124:
	add	x3, x29, 72
	add	x2, x29, 76
	mov	w1, w22
	mov	x0, x20
	cbz	w23, .L3121
	bl	MVC_GetMinPOC
	ldr	w1, [x29, 72]
	mov	x0, x20
	cmn	w1, #1
	beq	.L3111
	bl	MVC_OutputFrmFromDPB
	cbnz	w0, .L3126
.L3121:
	mov	w1, w19
	add	x3, x29, 72
	add	x2, x29, 76
	mov	x0, x20
	bl	MVC_GetMinPOC
	ldr	w1, [x29, 72]
	mov	x0, x20
	cmn	w1, #1
	beq	.L3111
	bl	MVC_OutputFrmFromDPB
	cbnz	w0, .L3126
	cmp	w19, w22
	cset	w0, lt
	tst	w24, w0
	beq	.L3125
	mov	w1, w22
	add	x3, x29, 72
	add	x2, x29, 76
	mov	x0, x20
	bl	MVC_GetMinPOC
	ldr	w1, [x29, 72]
	mov	x0, x20
	cmn	w1, #1
	beq	.L3111
	bl	MVC_OutputFrmFromDPB
	cbz	w0, .L3125
.L3126:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	mov	w0, -1
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L3111:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	mov	w0, 0
	ldp	x29, x30, [sp], 80
	ret
	.size	MVC_FlushDPB, .-MVC_FlushDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_AdaptiveMemMark
	.type	MVC_AdaptiveMemMark, %function
MVC_AdaptiveMemMark:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	add	x24, x20, 11157504
	add	x25, x20, 11116544
	bl	_mcount
	ldr	x22, .LC896
	add	x23, x24, 2312
	mov	w26, 1
	ldr	x21, [x24, 2968]
	add	x19, x21, 8
	add	x21, x21, 2008
	.p2align 2
.L3172:
	ldr	w0, [x19, -4]
	cmp	w0, 6
	bhi	.L3163
	ldrb	w0, [x22,w0,uxtw]
	adr	x1, .Lrtx3165
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx3165:
	.section	.rodata
	.align	0
	.align	2
.L3165:
	.byte	(.L3164 - .Lrtx3165) / 4
	.byte	(.L3166 - .Lrtx3165) / 4
	.byte	(.L3167 - .Lrtx3165) / 4
	.byte	(.L3168 - .Lrtx3165) / 4
	.byte	(.L3169 - .Lrtx3165) / 4
	.byte	(.L3170 - .Lrtx3165) / 4
	.byte	(.L3171 - .Lrtx3165) / 4
	.text
	.p2align 3
.L3170:
	mov	x0, x20
	bl	MVC_UnMarkAllSTRef
	mov	x0, x20
	bl	MVC_UpdateReflist
	mov	w1, 0
	mov	x0, x20
	bl	MVC_UpdateMaxLTFrmIdx
	mov	x0, x20
	bl	MVC_UpdateLTReflist
	strb	w26, [x25, 1704]
	.p2align 2
.L3163:
	add	x19, x19, 20
	cmp	x19, x21
	bne	.L3172
	.p2align 2
.L3164:
	ldrsb	w1, [x25, 1704]
	mov	w0, 0
	cmp	w1, 1
	beq	.L3180
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L3169:
	ldr	w1, [x19, 12]
	mov	x0, x20
	bl	MVC_UpdateMaxLTFrmIdx
	mov	x0, x20
	bl	MVC_UpdateLTReflist
	b	.L3163
	.p2align 3
.L3168:
	ldr	w2, [x19]
	mov	x1, x23
	ldr	w3, [x19, 8]
	mov	x0, x20
	bl	MVC_MarkSTToLTRef
	mov	x0, x20
	bl	MVC_UpdateReflist
	mov	x0, x20
	bl	MVC_UpdateLTReflist
	b	.L3163
	.p2align 3
.L3167:
	ldr	w2, [x19, 4]
	mov	x0, x20
	mov	x1, x23
	bl	MVC_UnMarkLTRef
	mov	x0, x20
	bl	MVC_UpdateLTReflist
	b	.L3163
	.p2align 3
.L3166:
	ldr	w2, [x19]
	mov	x0, x20
	mov	x1, x23
	bl	MVC_UnMarkSTRef
	mov	x0, x20
	bl	MVC_UpdateReflist
	b	.L3163
	.p2align 3
.L3171:
	ldr	w2, [x19, 8]
	mov	x1, x23
	mov	x0, x20
	bl	MVC_MarkCurrPicLT
	b	.L3163
	.p2align 3
.L3180:
	add	x0, x20, 11120640
	str	wzr, [x24, 2976]
	ldr	w0, [x0, 388]
	add	x0, x0, 2777088
	add	x0, x20, x0, lsl 2
	str	wzr, [x0, 11052]
	str	wzr, [x24, 3808]
	ldrb	w0, [x24, 2315]
	cmp	w0, 1
	beq	.L3175
	cbz	w0, .L3176
	cmp	w0, 2
	bne	.L3174
	str	wzr, [x24, 2988]
	str	wzr, [x24, 3000]
	str	wzr, [x25, 1732]
	str	wzr, [x25, 1740]
.L3174:
	ldr	w1, [x24, 3048]
	mov	x0, x20
	bl	MVC_FlushDPB
	cmp	w0, wzr
	csetm	w0, ne
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L3176:
	ldr	w2, [x24, 2988]
	ldr	w0, [x24, 2996]
	ldr	w1, [x24, 3000]
	sub	w0, w0, w2
	str	w0, [x24, 2996]
	sub	w1, w1, w2
	str	w1, [x24, 3000]
	cmp	w0, w1
	csel	w0, w0, w1, le
	str	w0, [x24, 2988]
	str	w0, [x24, 2992]
	ldr	w2, [x25, 1740]
	ldr	w0, [x25, 1728]
	ldr	w1, [x25, 1732]
	sub	w0, w0, w2
	str	w0, [x25, 1728]
	sub	w1, w1, w2
	str	w1, [x25, 1732]
	cmp	w0, w1
	csel	w0, w0, w1, le
	str	w0, [x25, 1736]
	str	w0, [x25, 1740]
	b	.L3174
.L3175:
	str	wzr, [x24, 2988]
	str	wzr, [x24, 2996]
	str	wzr, [x25, 1728]
	str	wzr, [x25, 1740]
	b	.L3174
	.size	MVC_AdaptiveMemMark, .-MVC_AdaptiveMemMark
	.align	3
.LC896:
	.xword	.L3165
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_IDRMemMarking
	.type	MVC_IDRMemMarking, %function
MVC_IDRMemMarking:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x20, x22, 11157504
	bl	_mcount
	ldr	x0, [x20, 2968]
	ldrb	w0, [x0, 1]
	cbz	w0, .L3182
	ldr	w0, [x22, 52]
	cbz	w0, .L3209
	sub	w4, w0, #1
	add	x24, x22, 11124736
	add	x4, x4, 38
	add	x2, x24, 408
	add	x1, x22, 148
	add	x4, x22, x4, lsl 2
	b	.L3190
	.p2align 3
.L3188:
	ldr	w3, [x0, 56]
	ldr	w0, [x20, 3048]
	cmp	w3, w0
	beq	.L3210
.L3187:
	add	x1, x1, 4
	cmp	x1, x4
	beq	.L3191
.L3190:
	ldr	x0, [x2]
	add	x2, x2, 8
	cbz	x0, .L3187
	ldr	w3, [x0, 16]
	cmp	w3, 1
	bne	.L3188
	strb	w3, [x22, 6]
	ldr	w3, [x0, 56]
	ldr	w0, [x20, 3048]
	cmp	w3, w0
	bne	.L3187
.L3210:
	str	wzr, [x1]
	add	x1, x1, 4
	cmp	x1, x4
	bne	.L3190
.L3191:
	ldr	w0, [x24, 792]
	cbz	w0, .L3185
	sub	w21, w0, #1
	add	x19, x24, 408
	add	x21, x21, 1388544
	mov	w23, 1
	add	x21, x21, 2100
	add	x21, x22, x21, lsl 3
	b	.L3196
	.p2align 3
.L3194:
	add	x19, x19, 8
	cmp	x19, x21
	beq	.L3185
.L3196:
	ldr	x0, [x19]
	cbz	x0, .L3194
	ldr	w2, [x0, 56]
	ldr	w1, [x20, 3048]
	cmp	w2, w1
	bne	.L3194
	strb	wzr, [x0, 706]
	mov	w2, 0
	strb	wzr, [x0, 705]
	ldr	x0, [x19]
	strb	wzr, [x0, 754]
	strb	wzr, [x0, 753]
	ldr	x0, [x19]
	strb	wzr, [x0, 802]
	strb	wzr, [x0, 801]
	ldr	x0, [x19]
	strb	wzr, [x0, 3]
	ldr	x1, [x19]
	ldr	w0, [x22, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_SetRef
	ldr	x0, [x19]
	strb	wzr, [x0, 2]
	ldr	x0, [x19]
	strb	wzr, [x0, 5]
	ldr	x0, [x19]
	strb	w23, [x0, 7]
	ldr	x1, [x19]
	ldr	w0, [x1, 52]
	add	x0, x22, x0
	add	x0, x0, 11124736
	strb	wzr, [x0, 816]
	ldrsb	w1, [x1, 6]
	ldr	w0, [x22, 120]
	bl	FSP_GetDisplay
	cmp	w0, 3
	mov	w2, 0
	beq	.L3195
	ldr	x1, [x19]
	ldr	w0, [x22, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_SetDisplay
.L3195:
	str	xzr, [x19]
	add	x19, x19, 8
	str	xzr, [x19, 120]
	str	xzr, [x19, 248]
	cmp	x19, x21
	ldr	w0, [x24, 796]
	sub	w0, w0, #1
	str	w0, [x24, 796]
	bne	.L3196
	.p2align 2
.L3185:
	mov	x0, x22
	bl	MVC_UpdateReflist
	mov	x0, x22
	bl	MVC_UpdateLTReflist
	ldr	x0, [x20, 2968]
	ldrb	w0, [x0, 2]
	cbnz	w0, .L3211
	mov	w0, 1
	str	wzr, [x24, 808]
	strb	w0, [x20, 2317]
	mov	w0, 0
	strb	wzr, [x20, 2316]
.L3197:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3211:
	mov	w0, 1
	str	w0, [x24, 808]
	strb	w0, [x20, 2316]
	mov	w0, 0
	strb	wzr, [x20, 2317]
	str	wzr, [x20, 2980]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3182:
	ldr	w1, [x20, 3048]
	mov	x0, x22
	bl	MVC_FlushDPB
	cbnz	w0, .L3198
	add	x24, x22, 11124736
	b	.L3185
.L3209:
	add	x24, x22, 11124736
	b	.L3191
.L3198:
	mov	w0, -1
	b	.L3197
	.size	MVC_IDRMemMarking, .-MVC_IDRMemMarking
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_Marking
	.type	MVC_Marking, %function
MVC_Marking:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 11157504
	bl	_mcount
	add	x0, x20, 11116544
	strb	wzr, [x0, 1704]
	ldrb	w1, [x19, 2315]
	cmp	w1, 2
	cset	w1, eq
	strb	w1, [x0, 1705]
	ldrb	w0, [x19, 2318]
	cmp	w0, 5
	beq	.L3213
	ldrb	w0, [x19, 2324]
	cbnz	w0, .L3214
	ldr	x0, [x20, 224]
	mov	x1, 4294967296
	ldr	x2, [x0, 688]
	cmp	x2, x1
	beq	.L3238
.L3214:
	ldr	x0, [x19, 2968]
	ldrb	w1, [x0, 3]
	cbz	w1, .L3239
	ldr	w0, [x19, 2984]
	cbnz	w0, .L3240
.L3221:
	mov	w0, 0
.L3236:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3239:
	ldr	w1, [x19, 2984]
	cbz	w1, .L3221
.L3224:
	ldrb	w1, [x19, 2313]
	cbnz	w1, .L3225
	add	x1, x20, 11124736
	ldr	x2, [x20, 248]
	ldr	w4, [x1, 804]
	ldr	w2, [x2, 3944]
	ldr	w3, [x1, 800]
	sub	w1, w2, w4
	cmp	w3, w1
	beq	.L3241
.L3226:
	strb	wzr, [x0]
	strb	wzr, [x19, 2316]
.L3217:
	ldr	w0, [x19, 2984]
	cbz	w0, .L3221
.L3225:
	ldrb	w1, [x19, 2316]
	mov	w0, 0
	cmp	w1, wzr
	cset	w1, eq
	strb	w1, [x19, 2317]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3238:
	ldr	w1, [x0, 696]
	cbnz	w1, .L3214
	ldr	w0, [x0, 652]
	add	w0, w0, 1024
	cmp	w0, 2048
	bls	.L3214
	.p2align 2
.L3213:
	mov	x0, x20
	bl	MVC_IDRMemMarking
	cbz	w0, .L3222
.L3215:
	mov	w0, -1
	b	.L3236
	.p2align 3
.L3240:
	mov	x0, x20
	bl	MVC_AdaptiveMemMark
	ldr	x1, [x19, 2968]
	strb	wzr, [x1]
	cbnz	w0, .L3215
.L3222:
	ldrb	w0, [x19, 2318]
	cmp	w0, 5
	beq	.L3217
	ldr	w0, [x19, 2984]
	cbz	w0, .L3221
	ldr	x0, [x19, 2968]
	ldrb	w1, [x0, 3]
	cbnz	w1, .L3225
	b	.L3224
	.p2align 3
.L3241:
	mov	x0, x20
	bl	MVC_SlidingWinMark.part.3
	ldr	x0, [x19, 2968]
	b	.L3226
	.size	MVC_Marking, .-MVC_Marking
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DirectOutput
	.type	MVC_DirectOutput, %function
MVC_DirectOutput:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 11157504
	bl	_mcount
	ldrb	w0, [x20, 2315]
	cmp	w0, 1
	beq	.L3244
	cbz	w0, .L3245
	cmp	w0, 2
	beq	.L3246
	mov	w21, 0
.L3243:
	mov	w0, w21
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3246:
	ldr	x0, [x20, 2960]
	mov	w1, 3
	strb	w1, [x0, 704]
	ldrb	w0, [x20, 2313]
	cbnz	w0, .L3261
	ldr	x1, [x19, 816]
	cbz	x1, .L3262
	mov	w2, 0
	mov	x0, x19
	bl	MVC_OutputFrmToVO
	mov	w21, w0
	ldr	x0, [x20, 2960]
	str	x0, [x19, 816]
	str	x0, [x0, 808]
.L3263:
	ldr	x0, [x19, 816]
	mov	w22, 2
	ldrb	w3, [x20, 2314]
	mov	x2, 632
	add	x1, x20, 2328
	strb	w3, [x0, 1]
	ldr	x0, [x19, 816]
	strb	w22, [x0, 2]
	ldr	x0, [x19, 816]
	strb	wzr, [x0, 5]
	ldr	x0, [x19, 816]
	strb	wzr, [x0, 7]
	ldr	x0, [x19, 816]
	strb	wzr, [x0, 3]
	ldr	x0, [x19, 816]
	ldrb	w3, [x20, 2324]
	strb	w3, [x0]
	ldr	x0, [x19, 816]
	str	wzr, [x0, 40]
	ldr	x0, [x19, 816]
	add	x0, x0, 72
	bl	memcpy
	ldr	x1, [x19, 816]
	mov	w0, 2
	ldr	w2, [x20, 3020]
	str	w2, [x1, 832]
	ldr	x1, [x19, 816]
	ldr	w2, [x1, 832]
	str	w2, [x1, 44]
	str	w2, [x1, 736]
	ldr	x1, [x19, 816]
	strb	w22, [x1, 800]
	ldrb	w2, [x20, 2319]
	ldr	x1, [x19, 816]
	cmp	w2, 1
	csel	w0, wzr, w0, ne
	strb	w0, [x1, 4]
.L3318:
	ldr	x0, [x19, 816]
	ldr	w1, [x20, 2988]
	str	w1, [x0, 32]
	ldr	x0, [x19, 816]
	ldr	w1, [x20, 3048]
	str	w1, [x0, 56]
	ldr	x0, [x19, 816]
	ldr	w1, [x20, 3052]
	str	w1, [x0, 60]
	ldrb	w22, [x19, 9]
	cmp	w22, 1
	bne	.L3243
	ldr	x1, [x19, 816]
	mov	w2, 0
	ldr	w0, [x19, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_SetRef
	ldr	x1, [x19, 816]
	mov	w2, 0
	mov	x0, x19
	bl	MVC_OutputFrmToVO
	mov	w21, w0
	ldr	x0, [x19, 816]
	cbz	x0, .L3271
	ldr	x1, [x20, 2960]
	mov	w2, w22
	ldr	w0, [x19, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_ClearLogicFs
.L3271:
	str	xzr, [x19, 816]
.L3321:
	mov	w0, w21
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3245:
	ldr	x0, [x20, 2960]
	strb	wzr, [x0, 704]
	ldr	x1, [x19, 816]
	cbz	x1, .L3247
	mov	w2, 0
	mov	x0, x19
	bl	MVC_OutputFrmToVO
	cbnz	w0, .L3320
.L3248:
	ldr	x0, [x19, 816]
	cbz	x0, .L3247
	ldr	x1, [x20, 2960]
	mov	w2, 1
	ldr	w0, [x19, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_ClearLogicFs
.L3247:
	ldr	x0, [x20, 2960]
	mov	w3, 3
	str	x0, [x19, 816]
	mov	x2, 632
	add	x1, x20, 2328
	str	x0, [x0, 712]
	ldr	x0, [x19, 816]
	ldr	x4, [x20, 2960]
	str	x4, [x0, 760]
	ldr	x0, [x19, 816]
	ldr	x4, [x20, 2960]
	str	x4, [x0, 808]
	ldr	x0, [x19, 816]
	ldrb	w4, [x20, 2314]
	strb	w4, [x0, 1]
	ldr	x0, [x19, 816]
	strb	w3, [x0, 2]
	ldr	x0, [x19, 816]
	strb	wzr, [x0, 3]
	ldr	x0, [x19, 816]
	strb	wzr, [x0, 5]
	ldr	x0, [x19, 816]
	strb	wzr, [x0, 7]
	ldr	x0, [x19, 816]
	add	x0, x0, 72
	bl	memcpy
	ldr	x1, [x19, 816]
	mov	w0, 3
	ldr	w3, [x20, 3020]
	mov	w2, 0
	str	w3, [x1, 44]
	str	w3, [x1, 736]
	ldr	x1, [x19, 816]
	strb	wzr, [x1, 704]
	ldr	x1, [x19, 816]
	ldrb	w3, [x20, 2324]
	strb	w3, [x1]
	ldr	x1, [x19, 816]
	ldrb	w3, [x20, 2321]
	str	w3, [x1, 40]
	ldrb	w3, [x20, 2319]
	ldr	x1, [x19, 816]
	cmp	w3, 1
	csel	w0, wzr, w0, ne
	strb	w0, [x1, 4]
	ldr	x0, [x19, 816]
	ldr	w1, [x20, 2988]
	str	w1, [x0, 32]
	ldr	x0, [x19, 816]
	ldr	w1, [x20, 3048]
	str	w1, [x0, 56]
	ldr	x0, [x19, 816]
	ldr	w1, [x20, 3052]
	str	w1, [x0, 60]
.L3316:
	ldr	x1, [x19, 816]
	ldr	w0, [x19, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_SetRef
	ldr	x1, [x19, 816]
	mov	w2, 0
	mov	x0, x19
	bl	MVC_OutputFrmToVO
	mov	w21, w0
	ldr	x0, [x19, 816]
	cbz	x0, .L3271
	ldr	x1, [x20, 2960]
	mov	w2, 1
	ldr	w0, [x19, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_ClearLogicFs
	str	xzr, [x19, 816]
	b	.L3321
	.p2align 3
.L3244:
	ldr	x0, [x20, 2960]
	mov	w1, 3
	strb	w1, [x0, 704]
	ldrb	w0, [x20, 2313]
	cbnz	w0, .L3251
	ldr	x1, [x19, 816]
	cbz	x1, .L3252
	mov	w2, 0
	mov	x0, x19
	bl	MVC_OutputFrmToVO
	mov	w21, w0
	ldr	x0, [x20, 2960]
	str	x0, [x19, 816]
	str	x0, [x0, 760]
.L3253:
	ldr	x0, [x19, 816]
	mov	w22, 1
	ldrb	w3, [x20, 2314]
	add	x1, x20, 2328
	mov	x2, 632
	strb	w3, [x0, 1]
	ldr	x0, [x19, 816]
	strb	w22, [x0, 2]
	ldr	x0, [x19, 816]
	strb	wzr, [x0, 5]
	ldr	x0, [x19, 816]
	strb	wzr, [x0, 7]
	ldr	x0, [x19, 816]
	strb	wzr, [x0, 3]
	ldr	x0, [x19, 816]
	ldrb	w3, [x20, 2324]
	strb	w3, [x0]
	ldr	x0, [x19, 816]
	str	wzr, [x0, 40]
	ldr	x0, [x19, 816]
	add	x0, x0, 72
	bl	memcpy
	ldr	x0, [x19, 816]
	ldr	w1, [x20, 3020]
	str	w1, [x0, 784]
	ldr	x0, [x19, 816]
	ldr	w1, [x0, 784]
	str	w1, [x0, 44]
	str	w1, [x0, 736]
	ldr	x0, [x19, 816]
	strb	w22, [x0, 752]
	ldrb	w1, [x20, 2319]
	ldr	x0, [x19, 816]
	cmp	w1, 1
	cset	w1, eq
	strb	w1, [x0, 4]
	b	.L3318
	.p2align 3
.L3261:
	ldr	x3, [x19, 816]
	cbz	x3, .L3322
.L3266:
	mov	x2, 632
	add	x1, x20, 2328
	add	x0, x3, 72
	ldr	x23, [x3, 656]
	ldr	x22, [x3, 664]
	ldr	x21, [x3, 672]
	bl	memcpy
	ldr	x0, [x20, 2912]
	cmn	x0, #1
	ccmn	x23, #1, 4, eq
	beq	.L3267
	ldr	x0, [x19, 816]
	str	x23, [x0, 656]
.L3267:
	ldr	x0, [x20, 2920]
	ldr	x1, [x19, 816]
	cmp	x0, x22
	csel	x0, x0, x22, ls
	str	x0, [x1, 664]
	ldr	x0, [x20, 2928]
	ldr	x1, [x19, 816]
	cmp	x0, x21
	csel	x0, x0, x21, ls
	str	x0, [x1, 672]
	ldr	x1, [x19, 816]
	ldrb	w0, [x1, 1]
	cbz	w0, .L3268
	ldrb	w0, [x20, 2314]
.L3268:
	strb	w0, [x1, 1]
	mov	w4, 2
	mov	w3, 3
	ldr	x1, [x19, 816]
	ldrb	w0, [x1, 2]
	orr	w0, w0, 2
	strb	w0, [x1, 2]
	ldr	x1, [x19, 816]
	ldrb	w0, [x20, 2324]
	ldrb	w2, [x1]
	cmp	w0, w2, uxtb
	csel	w0, w0, w2, cs
	strb	w0, [x1]
	ldr	x0, [x19, 816]
	strb	w4, [x0, 800]
	ldr	x0, [x19, 816]
	strb	w3, [x0, 704]
	ldr	x0, [x19, 816]
	ldr	w1, [x20, 3020]
	str	w1, [x0, 832]
	ldr	x1, [x19, 816]
	ldr	w2, [x1, 784]
	ldr	w0, [x1, 832]
	add	w0, w2, w0
	lsr	w0, w0, 1
	str	w0, [x1, 736]
	ldr	x0, [x19, 816]
	ldr	w1, [x0, 736]
	str	w1, [x0, 44]
	ldr	x0, [x19, 816]
	ldr	x1, [x0, 808]
	str	x1, [x0, 712]
	ldrb	w0, [x20, 2319]
	ldr	x1, [x19, 816]
	cmp	w0, 1
	beq	.L3323
.L3269:
	ldrb	w0, [x1, 4]
.L3270:
	strb	w0, [x1, 4]
	mov	w2, 0
	ldr	x0, [x19, 816]
	ldr	w1, [x20, 2988]
	str	w1, [x0, 32]
	b	.L3316
	.p2align 3
.L3251:
	ldr	x3, [x19, 816]
	cbz	x3, .L3324
.L3255:
	mov	x2, 632
	add	x1, x20, 2328
	add	x0, x3, 72
	ldr	x23, [x3, 656]
	ldr	x22, [x3, 664]
	ldr	x21, [x3, 672]
	bl	memcpy
	ldr	x0, [x20, 2912]
	cmn	x0, #1
	ccmn	x23, #1, 4, eq
	beq	.L3256
	ldr	x0, [x19, 816]
	str	x23, [x0, 656]
.L3256:
	ldr	x0, [x20, 2920]
	ldr	x1, [x19, 816]
	cmp	x0, x22
	csel	x0, x0, x22, ls
	str	x0, [x1, 664]
	ldr	x0, [x20, 2928]
	ldr	x1, [x19, 816]
	cmp	x0, x21
	csel	x0, x0, x21, ls
	str	x0, [x1, 672]
	ldr	x1, [x19, 816]
	ldrb	w0, [x1, 1]
	cbz	w0, .L3257
	ldrb	w0, [x20, 2314]
.L3257:
	strb	w0, [x1, 1]
	mov	w4, 1
	mov	w3, 3
	ldr	x1, [x19, 816]
	ldrb	w0, [x1, 2]
	orr	w0, w0, 1
	strb	w0, [x1, 2]
	ldr	x1, [x19, 816]
	ldrb	w0, [x20, 2324]
	ldrb	w2, [x1]
	cmp	w0, w2, uxtb
	csel	w0, w0, w2, cs
	strb	w0, [x1]
	ldr	x0, [x19, 816]
	strb	w4, [x0, 752]
	ldr	x0, [x19, 816]
	strb	w3, [x0, 704]
	ldr	x0, [x19, 816]
	ldr	w1, [x20, 3020]
	str	w1, [x0, 784]
	ldr	x1, [x19, 816]
	ldr	w2, [x1, 784]
	ldr	w0, [x1, 832]
	add	w0, w2, w0
	lsr	w0, w0, w4
	str	w0, [x1, 736]
	ldr	x0, [x19, 816]
	ldr	w1, [x0, 736]
	str	w1, [x0, 44]
	ldr	x0, [x19, 816]
	ldr	x1, [x0, 760]
	str	x1, [x0, 712]
	ldrb	w0, [x20, 2319]
	ldr	x1, [x19, 816]
	cmp	w0, 1
	bne	.L3269
	ldrb	w0, [x1, 4]
	orr	w0, w0, 1
	uxtb	w0, w0
	b	.L3270
	.p2align 3
.L3320:
	ldr	x2, .LC897
	mov	w4, w0
	ldr	x1, .LC899
	mov	w3, 2479
	add	x2, x2, 256
	mov	w0, 22
	bl	dprint_vfmw
	b	.L3248
	.p2align 3
.L3323:
	ldrb	w0, [x1, 4]
	orr	w0, w0, 2
	uxtb	w0, w0
	b	.L3270
	.p2align 3
.L3252:
	ldr	x0, [x20, 2960]
	mov	w21, 0
	str	x0, [x19, 816]
	str	x0, [x0, 760]
	b	.L3253
	.p2align 3
.L3262:
	ldr	x0, [x20, 2960]
	mov	w21, 0
	str	x0, [x19, 816]
	str	x0, [x0, 808]
	b	.L3263
	.p2align 3
.L3322:
	ldr	x0, [x20, 2960]
	str	x0, [x19, 816]
	str	x0, [x0, 808]
	ldr	x3, [x19, 816]
	b	.L3266
	.p2align 3
.L3324:
	ldr	x0, [x20, 2960]
	str	x0, [x19, 816]
	str	x0, [x0, 760]
	ldr	x3, [x19, 816]
	b	.L3255
	.size	MVC_DirectOutput, .-MVC_DirectOutput
	.align	3
.LC897:
	.xword	.LANCHOR0
	.align	3
.LC899:
	.xword	.LC898
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DEC_GetRemainImg
	.type	MVC_DEC_GetRemainImg, %function
MVC_DEC_GetRemainImg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	add	x19, x22, 11124736
	bl	_mcount
	ldr	w0, [x19, 792]
	cbz	w0, .L3339
	mov	w20, 0
	mov	w21, 0
	b	.L3328
	.p2align 3
.L3327:
	ldr	w0, [x19, 792]
	cmp	w0, w21
	bls	.L3366
.L3328:
	uxtw	x0, w21
	add	w21, w21, 1
	add	x0, x0, 1388544
	add	x0, x22, x0, lsl 3
	ldr	x0, [x0, 16792]
	cbz	x0, .L3327
	ldrb	w1, [x0, 5]
	cbz	w1, .L3327
	ldrsb	w1, [x0, 6]
	ldr	w0, [x22, 120]
	bl	FSP_GetLogicFs
	cbz	x0, .L3327
	ldrb	w0, [x0, 1]
	sub	w0, w0, #1
	uxtb	w0, w0
	cmp	w0, 1
	ldr	w0, [x19, 792]
	csinc	w20, w20, w20, hi
	cmp	w0, w21
	bhi	.L3328
.L3366:
	mov	w21, -1
	cbnz	w20, .L3332
	b	.L3329
	.p2align 3
.L3330:
	add	x1, x22, x1, lsl 3
	ldr	x1, [x1, 16792]
	bl	MVC_OutputFrmToVO
	mov	w21, w0
	subs	w20, w20, #1
	beq	.L3364
.L3332:
	add	x2, x29, 60
	mov	w1, -1
	add	x3, x29, 56
	mov	x0, x22
	bl	MVC_GetMinPOC
	ldr	w1, [x29, 56]
	mov	w2, w20
	mov	x0, x22
	cmn	w1, #1
	uxtw	x1, w1
	add	x1, x1, 1388544
	bne	.L3330
.L3364:
	ldr	w0, [x19, 792]
	cbz	w0, .L3326
.L3331:
	mov	w20, 0
	b	.L3335
	.p2align 3
.L3334:
	ldr	w0, [x19, 792]
	cmp	w0, w20
	bls	.L3326
.L3335:
	uxtw	x0, w20
	add	w20, w20, 1
	add	x0, x0, 1388544
	add	x0, x22, x0, lsl 3
	ldr	x1, [x0, 16792]
	cbz	x1, .L3334
	ldrb	w0, [x1, 3]
	cbz	w0, .L3334
	mov	x0, x22
	bl	MVC_UnMarkFrameStoreRef
	ldr	w0, [x19, 792]
	cmp	w0, w20
	bhi	.L3335
.L3326:
	mov	w1, -1
	mov	x0, x22
	bl	MVC_RemoveUnUsedFrameStore
	cbnz	w21, .L3337
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L3329:
	cbnz	w0, .L3331
	mov	w1, w21
	mov	x0, x22
	bl	MVC_RemoveUnUsedFrameStore
.L3337:
	add	x0, x22, 912
	bl	GetVoLastImageID
	mov	w21, w0
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L3339:
	mov	w21, -1
	b	.L3326
	.size	MVC_DEC_GetRemainImg, .-MVC_DEC_GetRemainImg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	MVC_InitDPB.part.16, %function
MVC_InitDPB.part.16:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x22, x20, 11124736
	add	x19, x22, 408
	add	x21, x22, 536
	bl	_mcount
	.p2align 2
.L3371:
	ldr	x0, [x19]
	mov	w2, 1
	cbz	x0, .L3368
	ldrsb	w1, [x0, 6]
	ldr	w0, [x20, 120]
	bl	FSP_ClearLogicFs
.L3368:
	ldr	x0, [x19, 128]
	mov	w2, 1
	cbz	x0, .L3369
	ldrsb	w1, [x0, 6]
	ldr	w0, [x20, 120]
	bl	FSP_ClearLogicFs
.L3369:
	ldr	x0, [x19, 256]
	mov	w2, 1
	cbz	x0, .L3370
	ldrsb	w1, [x0, 6]
	ldr	w0, [x20, 120]
	bl	FSP_ClearLogicFs
.L3370:
	str	xzr, [x19, 128]
	str	xzr, [x19, 256]
	str	xzr, [x19], 8
	cmp	x19, x21
	bne	.L3371
	add	x1, x22, 768
	ldr	w0, [x20, 44]
	stp	w0, wzr, [x1, 24]
	stp	wzr, wzr, [x1, 32]
	str	wzr, [x22, 808]
	ldr	x1, [x20, 816]
	cbz	x1, .L3373
	ldrb	w0, [x20, 8]
	cmp	w0, 2
	beq	.L3374
.L3378:
	add	x0, x20, 11157504
	ldr	x0, [x0, 2960]
	cbz	x0, .L3376
	ldrsb	w1, [x0, 6]
	mov	w2, 1
	ldr	w0, [x20, 120]
	bl	FSP_ClearLogicFs
.L3376:
	str	xzr, [x20, 816]
.L3373:
	ldr	x3, .LC903
	mov	w1, 0
	mov	x2, 344
	add	x0, x22, 816
	ldr	x3, [x3, 96]
	blr	x3
	str	wzr, [x22, 1028]
	ldr	w0, [x22, 792]
	add	x1, x20, 220
	str	w0, [x22, 1024]
	add	x0, x20, 148
	.p2align 2
.L3380:
	str	wzr, [x0], 4
	cmp	x0, x1
	bne	.L3380
	add	x1, x20, 288
	add	x0, x20, 552
	.p2align 2
.L3381:
	str	xzr, [x1], 8
	cmp	x1, x0
	bne	.L3381
	add	x1, x20, 11116544
	add	x20, x20, 816
	str	wzr, [x1, 2888]
	.p2align 2
.L3382:
	str	xzr, [x0], 8
	cmp	x20, x0
	bne	.L3382
	str	wzr, [x1, 2892]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L3374:
	mov	w2, 0
	mov	x0, x20
	bl	MVC_OutputFrmToVO
	cbnz	w0, .L3399
.L3377:
	ldr	x0, [x20, 816]
	cbnz	x0, .L3378
	b	.L3373
	.p2align 3
.L3399:
	ldr	x2, .LC900
	mov	w4, w0
	ldr	x1, .LC902
	mov	w3, 5891
	add	x2, x2, 280
	mov	w0, 22
	bl	dprint_vfmw
	b	.L3377
	.size	MVC_InitDPB.part.16, .-MVC_InitDPB.part.16
	.align	3
.LC900:
	.xword	.LANCHOR0
	.align	3
.LC902:
	.xword	.LC901
	.align	3
.LC903:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_InitDPB
	.type	MVC_InitDPB, %function
MVC_InitDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L3402
	mov	x0, x19
	bl	MVC_ClearAllSlice
	mov	x0, x19
	bl	MVC_InitDPB.part.16
.L3401:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3402:
	mov	w0, -1
	b	.L3401
	.size	MVC_InitDPB, .-MVC_InitDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ClearDPB
	.type	MVC_ClearDPB, %function
MVC_ClearDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	mov	w1, w20
	mov	x0, x19
	bl	MVC_FlushDPB
	cbnz	w0, .L3411
	cbz	x19, .L3407
.L3405:
	mov	x0, x19
	bl	MVC_ClearAllSlice
	mov	x0, x19
	bl	MVC_InitDPB.part.16
	cbnz	w0, .L3407
	strb	wzr, [x19, 6]
	mov	w0, 0
	str	wzr, [x19, 220]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3411:
	ldr	x2, .LC904
	mov	w3, 307
	ldr	x1, .LC906
	mov	w0, 22
	add	x2, x2, 296
	bl	dprint_vfmw
	cbnz	x19, .L3405
.L3407:
	ldr	x2, .LC904
	mov	w3, 312
	ldr	x1, .LC908
	mov	w0, 22
	add	x2, x2, 296
	bl	dprint_vfmw
	strb	wzr, [x19, 6]
	str	wzr, [x19, 220]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_ClearDPB, .-MVC_ClearDPB
	.align	3
.LC904:
	.xword	.LANCHOR0
	.align	3
.LC906:
	.xword	.LC905
	.align	3
.LC908:
	.xword	.LC907
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecVDM
	.type	MVC_DecVDM, %function
MVC_DecVDM:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 11157504
	bl	_mcount
	ldrb	w0, [x21, 2315]
	cbz	w0, .L3413
	ldrb	w0, [x21, 2313]
	cmp	w0, 1
	beq	.L3413
.L3414:
	ldr	w20, [x19, 108]
	ldrb	w0, [x19, 8]
	ubfx	x20, x20, 16, 2
	cmp	w20, w0
	beq	.L3415
	sub	w0, w0, #2
	uxtb	w0, w0
	cmp	w0, 1
	ccmp	w20, 1, 2, ls
	bls	.L3479
.L3415:
	uxtb	w20, w20
	strb	w20, [x19, 8]
	cmp	w20, 2
	beq	.L3418
	cmp	w20, 3
	beq	.L3419
	cmp	w20, 1
	beq	.L3480
	ldrb	w0, [x19, 11]
	cmp	w0, 1
	beq	.L3481
.L3426:
	ldr	w0, [x19, 64]
.L3439:
	ldrb	w1, [x21, 2325]
	strb	w1, [x19, 11]
.L3427:
	cbz	w0, .L3477
	ldrb	w0, [x21, 2324]
	cmp	w0, 2
	beq	.L3482
	cmp	w0, 1
	beq	.L3483
.L3430:
	ldr	w2, [x19, 88]
	mov	w0, 2
	ldrb	w3, [x21, 2315]
	add	x20, x19, 11161600
	ldr	x1, .LC914
	sub	w2, w2, #1
	bl	dprint_vfmw
	ldr	w0, [x21, 3036]
	str	w0, [x20, 1564]
	mov	w0, 1
	strb	w0, [x20, 826]
	ldr	w0, [x21, 3040]
	str	w0, [x20, 1560]
	ldr	w0, [x19, 64]
	str	w0, [x20, 1764]
	ldr	w0, [x19, 88]
	cbz	w0, .L3431
	ldrb	w0, [x21, 2324]
	cbz	w0, .L3484
	add	x0, x19, 11124736
	ldr	w0, [x0, 796]
	cbnz	w0, .L3433
	ldr	x2, [x19, 224]
	ldr	w0, [x2, 24]
	cmp	w0, 2
	bne	.L3477
.L3436:
	add	x1, x20, 824
	str	x1, [x19, 232]
	ldr	w0, [x2, 920]
	cmp	w0, 1
	beq	.L3485
.L3437:
	cmp	w0, 2
	bne	.L3438
	ldr	w0, [x2, 924]
	cmp	w0, wzr
	ccmp	x1, xzr, 4, gt
	beq	.L3438
	ldrb	w22, [x21, 2324]
	cmp	w22, 2
	bne	.L3438
	str	xzr, [x19, 232]
	mov	w2, 0
	ldr	w0, [x19, 120]
	ldr	x1, [x21, 2960]
	ldrsb	w1, [x1, 6]
	bl	FSP_SetDisplay
	ldr	x2, [x19, 224]
	mov	x0, x19
	ldr	w1, [x2, 924]
	sub	w1, w1, #1
	str	w1, [x2, 924]
	b	.L3473
	.p2align 3
.L3413:
	ldp	w0, w1, [x19, 140]
	ldr	x2, [x19, 224]
	add	w0, w0, 1
	cmp	w0, w1
	csel	w0, w0, w1, ge
	str	w0, [x19, 140]
	sub	w0, w0, w1
	str	w0, [x2, 616]
	b	.L3414
	.p2align 3
.L3419:
	mov	x0, x19
	mov	w21, -1
	bl	MVC_ClearAllSlice
	add	x0, x19, 11120640
	ldr	w4, [x19, 40]
	mov	w1, 7
	mov	w3, 23352
	movk	w3, 0x1, lsl 16
	mov	w2, 2
	strb	w1, [x0, 403]
	mov	w1, 32
	strb	wzr, [x0, 400]
	strb	w2, [x0, 401]
	strb	w1, [x0, 402]
	str	w4, [x0, 412]
	str	w3, [x0, 416]
	str	w20, [x0, 424]
.L3474:
	add	x6, x0, 256
	mov	w2, 262144
	mov	w1, w21
	mov	x0, x19
	stp	w21, wzr, [x6, 172]
	stp	wzr, w2, [x6, 180]
	bl	MVC_ClearDPB
	mov	w0, w21
.L3470:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3431:
	ldr	x2, [x19, 224]
.L3438:
	ldr	w1, [x2, 632]
	mov	w0, 0
	strb	w1, [x20, 828]
	ldr	w1, [x2, 636]
	strb	w1, [x20, 829]
	ldr	w1, [x2, 640]
	str	w1, [x20, 832]
	ldr	w1, [x2, 644]
	str	w1, [x20, 836]
	ldr	w1, [x2, 684]
	strb	w1, [x20, 840]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3480:
	ldrb	w0, [x21, 2324]
	cmp	w0, 2
	bne	.L3426
	ldr	w0, [x21, 2984]
	cbz	w0, .L3423
	ldrb	w0, [x19, 11]
	cmp	w0, 1
	bne	.L3426
.L3440:
	ldrb	w1, [x21, 2325]
	strb	w1, [x19, 11]
	ldr	w0, [x19, 64]
	b	.L3427
	.p2align 3
.L3418:
	ldrb	w0, [x21, 2324]
	cbnz	w0, .L3423
	ldr	w0, [x19, 64]
	cbz	w0, .L3439
	ldr	x1, [x19, 864]
	ldr	w1, [x1, 48]
	cbz	w1, .L3439
.L3423:
	mov	w1, 1
	mov	x0, x19
	strb	w1, [x21, 2319]
.L3476:
	bl	MVC_ClearAllSlice
	add	x1, x19, 11120640
	ldr	w8, [x19, 40]
	mov	w7, 23352
	mov	w6, 2
	movk	w7, 0x1, lsl 16
	mov	w0, -1
	mov	w5, 7
	mov	w4, 32
	mov	w3, 3
	mov	w2, 262144
	strb	wzr, [x1, 400]
	strb	w6, [x1, 401]
	str	w8, [x1, 412]
	str	w7, [x1, 416]
.L3475:
	strb	w4, [x1, 402]
	add	x4, x1, 256
	strb	w5, [x1, 403]
	stp	w3, w0, [x4, 168]
	stp	wzr, wzr, [x4, 176]
	str	w2, [x1, 440]
	b	.L3470
	.p2align 3
.L3482:
	ldrb	w22, [x19, 7]
	cmp	w22, 2
	bne	.L3430
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 24]
	cbnz	w0, .L3430
	ldr	x1, .LC912
	mov	w0, 1
	ldr	w3, [x21, 2984]
	mov	w20, -1
	ldr	w2, [x21, 2988]
	bl	dprint_vfmw
	mov	x0, x19
	bl	MVC_ClearAllSlice
	add	x0, x19, 11120640
	ldr	w4, [x19, 40]
	add	x5, x0, 256
	mov	w3, 23352
	movk	w3, 0x1, lsl 16
	mov	w2, 7
	strb	wzr, [x0, 400]
	mov	w1, 32
	strb	w2, [x0, 403]
	mov	w2, 3
	strb	w1, [x0, 402]
	mov	w1, 262144
	strb	w22, [x0, 401]
	str	w4, [x0, 412]
	str	w3, [x0, 416]
	stp	w2, w20, [x5, 168]
	stp	wzr, wzr, [x5, 176]
	str	w1, [x0, 440]
	mov	w2, 0
	ldr	x1, [x21, 2960]
	ldr	w0, [x19, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_SetDisplay
	mov	w0, w20
	b	.L3470
	.p2align 3
.L3483:
	ldr	w1, [x21, 3048]
	cbnz	w1, .L3430
	strb	w0, [x19, 7]
	b	.L3430
	.p2align 3
.L3484:
	ldr	x0, .LC915
	ldr	x5, [x0]
	cbz	x5, .L3433
	ldr	x1, [x20, 1768]
	cbz	x1, .L3441
	mov	w2, 0
	.p2align 2
.L3435:
	ldp	w3, w0, [x1, 8]
	ldr	x1, [x1, 4056]
	add	w0, w3, w0
	add	w0, w0, 7
	add	w2, w2, w0, lsr 3
	mov	w4, w2
	cbnz	x1, .L3435
.L3434:
	add	x2, x29, 64
	ldr	w0, [x19, 120]
	mov	w1, 20
	mov	w3, 4
	str	w4, [x2, -8]!
	blr	x5
	ldr	x2, [x19, 224]
	add	x1, x20, 824
	str	x1, [x19, 232]
	ldr	w0, [x2, 920]
	cmp	w0, 1
	bne	.L3437
.L3485:
	cbz	x1, .L3438
	ldrb	w22, [x21, 2324]
	cmp	w22, 2
	bne	.L3438
	str	xzr, [x19, 232]
	mov	w2, 0
	ldr	w0, [x19, 120]
	ldr	x1, [x21, 2960]
	ldrsb	w1, [x1, 6]
	bl	FSP_SetDisplay
	mov	x0, x19
.L3473:
	bl	MVC_ClearAllSlice
	add	x1, x19, 11120640
	ldr	w7, [x19, 40]
	mov	w6, 23352
	mov	w0, -1
	movk	w6, 0x1, lsl 16
	mov	w5, 7
	mov	w4, 32
	mov	w3, 3
	mov	w2, 262144
	strb	wzr, [x1, 400]
	strb	w22, [x1, 401]
	str	w7, [x1, 412]
	str	w6, [x1, 416]
	b	.L3475
	.p2align 3
.L3481:
	ldrb	w0, [x21, 2324]
	cmp	w0, 2
	beq	.L3440
	b	.L3426
	.p2align 3
.L3433:
	ldr	x2, [x19, 224]
	b	.L3436
	.p2align 3
.L3477:
	mov	x0, x19
	b	.L3476
.L3441:
	mov	w4, 0
	b	.L3434
.L3479:
	ldr	x1, .LC910
	mov	w2, w20
	mov	w0, 2
	mov	w21, -1
	bl	dprint_vfmw
	strb	w20, [x19, 8]
	mov	x0, x19
	bl	MVC_ClearAllSlice
	add	x0, x19, 11120640
	ldr	w4, [x19, 40]
	mov	w2, 2
	mov	w1, 7
	mov	w3, 23352
	movk	w3, 0x1, lsl 16
	strb	w2, [x0, 401]
	strb	w1, [x0, 403]
	mov	w2, 32
	mov	w1, 3
	strb	wzr, [x0, 400]
	strb	w2, [x0, 402]
	str	w4, [x0, 412]
	str	w3, [x0, 416]
	str	w1, [x0, 424]
	b	.L3474
	.size	MVC_DecVDM, .-MVC_DecVDM
	.align	3
.LC910:
	.xword	.LC909
	.align	3
.LC912:
	.xword	.LC911
	.align	3
.LC914:
	.xword	.LC913
	.align	3
.LC915:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_FlushDecoder
	.type	MVC_FlushDecoder, %function
MVC_FlushDecoder:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x2, x19, 11116544
	mov	w1, 1
	mov	x0, x19
	strb	w1, [x2, 2845]
	str	wzr, [x2, 2896]
	strb	w1, [x19]
	bl	MVC_DecVDM
	cbz	w0, .L3486
	ldr	x2, .LC916
	mov	w3, 12883
	ldr	x1, .LC918
	mov	w0, 22
	add	x2, x2, 312
	bl	dprint_vfmw
.L3486:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_FlushDecoder, .-MVC_FlushDecoder
	.align	3
.LC916:
	.xword	.LANCHOR0
	.align	3
.LC918:
	.xword	.LC917
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ReceivePacket
	.type	MVC_ReceivePacket, %function
MVC_ReceivePacket:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 11161600
	bl	_mcount
	ldr	x1, .LC920
	mov	w0, 7
	ldp	w3, w4, [x20, 16]
	ldr	x2, [x20, 8]
	bl	dprint_vfmw
	str	wzr, [x21, 2016]
	ldr	x0, [x19, 224]
	ldr	w1, [x0, 880]
	cmp	w1, 1
	beq	.L3556
.L3492:
	ldr	x0, [x19, 240]
	cbz	x0, .L3497
	ldrb	w1, [x20]
	cmp	w1, 1
	beq	.L3557
.L3495:
	ldr	x1, .LC922
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 240]
	cbz	x1, .L3497
	ldr	w0, [x19, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19, 240]
.L3497:
	ldr	w0, [x20, 20]
	cmp	w0, wzr
	ble	.L3499
	ldr	x0, [x20, 8]
	cbz	x0, .L3499
	ldr	w0, [x20, 16]
	cbz	w0, .L3499
	ldrb	w0, [x19, 1521]
	cbz	w0, .L3517
	add	x1, x19, 1617
	mov	x0, 1
	b	.L3502
	.p2align 3
.L3501:
	add	w0, w0, 1
	cmp	w0, 137
	beq	.L3515
.L3502:
	ldrb	w2, [x1]
	add	x1, x1, 96
	cbnz	w2, .L3501
	sxtw	x1, w0
.L3500:
	lsl	x2, x0, 2
	mov	w3, 1
	sub	x0, x2, x0
	cmn	w1, #1
	add	x0, x19, x0, lsl 5
	strb	w3, [x0, 1521]
	beq	.L3515
	lsl	x0, x1, 2
	mov	w2, 1
	sub	x0, x0, x1
	lsl	x0, x0, 5
	add	x1, x0, 1520
	add	x0, x19, x0
	add	x1, x19, x1
	str	x1, [x19, 240]
	ldr	x1, [x20, 8]
	str	x1, [x0, 1528]
	ldr	w1, [x20, 20]
	str	w1, [x0, 1536]
	ldr	w1, [x20, 16]
	str	w1, [x0, 1540]
	ldr	x0, [x19, 240]
	str	wzr, [x0, 28]
	ldr	x0, [x19, 240]
	ldr	w1, [x20, 24]
	str	w1, [x0, 36]
	ldr	x0, [x19, 240]
	ldr	x1, [x20, 32]
	str	x1, [x0, 88]
	ldr	x0, [x19, 240]
	str	w2, [x0, 76]
	ldr	x0, [x19, 240]
	strb	wzr, [x0]
	ldr	x0, [x19, 240]
	ldrb	w1, [x20]
	strb	w1, [x0, 3]
	ldr	x0, [x19, 240]
	b	.L3507
	.p2align 3
.L3557:
	ldr	w2, [x0, 76]
	cmp	w2, 1
	bhi	.L3495
	ldrb	w2, [x0, 3]
	cmp	w2, 1
	bne	.L3496
	b	.L3495
	.p2align 3
.L3556:
	ldr	w0, [x0, 928]
	cbz	w0, .L3492
	ldr	x0, [x19, 240]
	cbz	x0, .L3497
	ldrb	w1, [x20]
.L3496:
	strb	w1, [x0, 3]
	ldr	x0, [x19, 224]
	ldr	w1, [x0, 880]
	cmp	w1, 1
	beq	.L3558
.L3509:
	ldr	w0, [x20, 20]
	cmp	w0, wzr
	ble	.L3510
	ldr	x1, [x20, 8]
	cbz	x1, .L3510
	ldr	w0, [x20, 16]
	cbz	w0, .L3510
	ldr	x0, [x19, 240]
	ldr	w2, [x0, 76]
	cmp	w2, 1
	bls	.L3559
.L3511:
	mov	w1, 1
	strb	w1, [x0, 3]
	ldr	w0, [x19, 120]
	ldr	w1, [x20, 24]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC925
	ldr	x4, [x0]
	cbz	x4, .L3553
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L3553:
	ldr	x0, [x19, 240]
.L3507:
	ldrb	w0, [x0, 3]
	ldp	x19, x20, [sp, 16]
	cmp	w0, wzr
	ldr	x21, [sp, 32]
	csetm	w0, eq
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3499:
	ldr	x1, .LC927
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x19, 120]
	ldr	w1, [x20, 24]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC925
	ldr	x4, [x0]
	cbz	x4, .L3555
.L3554:
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L3555:
	mov	w0, -1
.L3562:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3510:
	ldr	x0, [x19, 240]
	b	.L3511
	.p2align 3
.L3558:
	ldr	w0, [x0, 928]
	cbnz	w0, .L3553
	b	.L3509
	.p2align 3
.L3559:
	ubfiz	x2, x2, 5, 32
	add	x0, x0, x2
	str	x1, [x0, 8]
	ldr	x1, [x19, 240]
	ldr	w2, [x20, 20]
	ldr	w0, [x1, 76]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 16]
	ldr	x1, [x19, 240]
	ldr	w2, [x20, 16]
	ldr	w0, [x1, 76]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 20]
	ldr	x1, [x19, 240]
	ldr	w0, [x1, 76]
	add	x0, x1, x0, lsl 5
	str	wzr, [x0, 28]
	ldr	x1, [x19, 240]
	ldr	w2, [x20, 24]
	ldr	w0, [x1, 76]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 36]
	ldr	x1, [x19, 240]
	ldr	w0, [x1, 76]
	add	w0, w0, 1
	str	w0, [x1, 76]
	ldr	x0, [x19, 240]
	ldr	w1, [x0, 16]
	cmp	w1, 4095
	bls	.L3560
.L3512:
	mov	w1, 1
	str	w1, [x21, 2016]
	b	.L3507
	.p2align 3
.L3560:
	mov	x0, x19
	bl	MVC_CombinePacket.part.13
	ldr	x0, [x19, 240]
	b	.L3512
.L3515:
	ldr	x1, .LC924
	mov	w0, 0
	add	x21, x19, 12288
	add	x20, x19, 1520
	add	x21, x21, 2384
	bl	dprint_vfmw
	b	.L3504
	.p2align 3
.L3503:
	add	x20, x20, 96
	cmp	x21, x20
	beq	.L3561
.L3504:
	ldrb	w0, [x20, 1]
	cmp	w0, 1
	bne	.L3503
	ldr	w0, [x19, 120]
	mov	x1, x20
	bl	MVC_ReleaseNAL
	b	.L3503
.L3561:
	mov	x0, x19
	mov	w20, -1
	bl	MVC_ClearAllSlice
	add	x0, x19, 11120640
	mov	w3, 23352
	movk	w3, 0x1, lsl 16
	ldr	w4, [x19, 40]
	mov	w2, 2
	mov	w1, 7
	str	w3, [x0, 416]
	add	x3, x0, 256
	strb	w2, [x0, 401]
	mov	w2, 32
	strb	w1, [x0, 403]
	mov	w1, 3
	strb	w2, [x0, 402]
	mov	w2, 262144
	str	w4, [x0, 412]
	strb	wzr, [x0, 400]
	stp	w1, w20, [x3, 168]
	stp	wzr, wzr, [x3, 176]
	str	w2, [x0, 440]
	mov	w1, w20
	mov	x0, x19
	bl	MVC_ClearDPB
	ldr	x0, .LC925
	ldr	x4, [x0]
	cbnz	x4, .L3554
	mov	w0, -1
	b	.L3562
.L3517:
	mov	x1, 0
	mov	x0, 0
	b	.L3500
	.size	MVC_ReceivePacket, .-MVC_ReceivePacket
	.align	3
.LC920:
	.xword	.LC919
	.align	3
.LC922:
	.xword	.LC921
	.align	3
.LC924:
	.xword	.LC923
	.align	3
.LC925:
	.xword	g_event_report
	.align	3
.LC927:
	.xword	.LC926
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ClearAll
	.type	MVC_ClearAll, %function
MVC_ClearAll:
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
	add	x1, x20, 11120640
	mov	x23, x1
	str	x1, [x29, 104]
	bl	_mcount
	add	x21, x20, 12288
	ldr	x1, .LC929
	mov	w0, 22
	add	x19, x20, 1520
	add	x21, x21, 2384
	bl	dprint_vfmw
	mov	x0, x20
	bl	MVC_ClearAllSlice
	mov	w1, 23352
	ldr	w2, [x20, 40]
	movk	w1, 0x1, lsl 16
	mov	w0, 7
	mov	w4, 2
	mov	w3, 32
	strb	w0, [x23, 403]
	mov	w0, 262144
	str	w2, [x23, 412]
	mov	w2, 3
	str	w1, [x23, 416]
	mov	w1, -1
	strb	wzr, [x23, 400]
	strb	w4, [x23, 401]
	strb	w3, [x23, 402]
	str	wzr, [x23, 432]
	str	wzr, [x23, 436]
	str	w0, [x23, 440]
	str	w2, [x23, 424]
	str	w1, [x23, 428]
	b	.L3565
	.p2align 3
.L3564:
	add	x19, x19, 96
	cmp	x19, x21
	beq	.L3596
.L3565:
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	bne	.L3564
	ldr	w0, [x20, 120]
	mov	x1, x19
	add	x19, x19, 96
	bl	MVC_ReleaseNAL
	cmp	x19, x21
	bne	.L3565
.L3596:
	cbz	x20, .L3568
	mov	x0, x20
	bl	MVC_ClearAllSlice
	mov	x0, x20
	bl	MVC_InitDPB.part.16
	cbnz	w0, .L3568
.L3567:
	cbz	w22, .L3569
	ldr	w0, [x20, 120]
	add	x1, x20, 912
	bl	FSP_ClearNotInVoQueue
.L3570:
	mov	x25, x20
	mov	w28, 0
	mov	w26, -1
	mov	w21, 1
	mov	w24, 18
	mov	w23, 16
	mov	w22, 2
	.p2align 2
.L3573:
	add	x0, x25, 11124736
	add	x2, x0, 1024
	add	x1, x0, 1160
	add	x19, x0, 1776
	add	x27, x0, 1808
	strb	wzr, [x0, 1161]
	strb	wzr, [x0, 1162]
	strb	wzr, [x0, 1163]
	strb	wzr, [x0, 1165]
	strb	w21, [x0, 1167]
	strb	wzr, [x0, 1864]
	strb	w21, [x0, 1912]
	strb	w22, [x0, 1960]
	stp	wzr, w26, [x2, 156]
	stp	wzr, wzr, [x2, 164]
	str	w24, [x0, 1208]
	str	w23, [x0, 1212]
	str	w28, [x0, 1380]
	str	x1, [x0, 1872]
	str	x1, [x0, 1920]
	str	x1, [x0, 1968]
.L3572:
	ldr	x1, [x19]
	cbnz	x1, .L3597
.L3571:
	add	x19, x19, 8
	cmp	x19, x27
	bne	.L3572
	add	w28, w28, 1
	add	x25, x25, 848
	cmp	w28, 40
	bne	.L3573
	add	x22, x20, 11157504
	add	x19, x22, 2872
	add	x21, x22, 2904
.L3575:
	ldr	x1, [x19]
	cbnz	x1, .L3598
.L3574:
	add	x19, x19, 8
	cmp	x21, x19
	bne	.L3575
	ldr	w2, [x20, 60]
	mov	w19, 0
	cbz	w2, .L3579
	.p2align 2
.L3586:
	add	x21, x20, x19, uxtw 3
	add	w19, w19, 1
	ldr	x0, [x21, 832]
	mov	x1, x0
	cbz	x0, .L3577
	ldr	w0, [x20, 120]
	bl	FreeUsdByDec
	str	xzr, [x21, 832]
	ldr	w2, [x20, 60]
.L3577:
	cmp	w2, w19
	bhi	.L3586
.L3579:
	ldr	x0, .LC932
	mov	x2, 1656
	strb	wzr, [x20, 4]
	mov	w1, 0
	strb	wzr, [x20, 9]
	strb	wzr, [x20, 6]
	strb	wzr, [x20, 7]
	strb	wzr, [x20, 3]
	stp	wzr, wzr, [x20, 60]
	str	wzr, [x20, 104]
	ldr	x3, [x0, 96]
	ldr	x0, [x29, 104]
	str	wzr, [x20, 220]
	str	xzr, [x20, 240]
	add	x20, x20, 11116544
	strb	wzr, [x0, 2452]
	strb	wzr, [x0, 448]
	strb	wzr, [x0, 2453]
	strb	wzr, [x0, 449]
	add	x0, x20, 2840
	blr	x3
	mov	w1, 2
	mov	w0, 1
	strb	w1, [x20, 2840]
	strb	w0, [x20, 2845]
	mov	w0, 256
	strb	wzr, [x22, 2312]
	str	w0, [x22, 3808]
	mov	w0, 0
	strb	wzr, [x22, 3800]
	str	wzr, [x22, 3804]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3597:
	ldr	w0, [x20, 120]
	bl	FreeUsdByDec
	str	xzr, [x19]
	b	.L3571
.L3598:
	ldr	w0, [x20, 120]
	bl	FreeUsdByDec
	str	xzr, [x19]
	b	.L3574
.L3569:
	add	x0, x20, 912
	bl	ResetVoQueue
	ldr	w0, [x20, 120]
	bl	FSP_EmptyInstance
	b	.L3570
.L3568:
	ldr	x2, .LC930
	mov	w3, 337
	ldr	x1, .LC931
	mov	w0, 22
	add	x2, x2, 336
	bl	dprint_vfmw
	b	.L3567
	.size	MVC_ClearAll, .-MVC_ClearAll
	.align	3
.LC929:
	.xword	.LC928
	.align	3
.LC930:
	.xword	.LANCHOR0
	.align	3
.LC931:
	.xword	.LC907
	.align	3
.LC932:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_InsertFrmInDPB
	.type	MVC_InsertFrmInDPB, %function
MVC_InsertFrmInDPB:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x23, x0
	mov	x0, x30
	uxtw	x21, w1
	mov	x19, x2
	bl	_mcount
	add	x0, x23, 11124736
	ldr	w0, [x0, 796]
	cbnz	w0, .L3600
	ldr	x0, .LC933
	str	wzr, [x0, 1948]
.L3600:
	ldrb	w22, [x19, 3]
	cmp	w22, 1
	beq	.L3602
	cbz	w22, .L3603
	cmp	w22, 2
	beq	.L3604
	ldr	x1, .LC937
	mov	w2, w22
	mov	w0, 0
	mov	w19, 0
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x23
	bl	MVC_ClearAll
.L3608:
	mov	w0, w19
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L3604:
	ldr	x0, [x19, 648]
	mov	w1, 3
	strb	w1, [x0, 704]
	ldrb	w0, [x19, 1]
	cbz	w0, .L3622
	add	x20, x23, x21, lsl 3
	add	x20, x20, 11124736
	ldr	x0, [x20, 408]
	cbz	x0, .L3622
	strb	w22, [x0, 800]
	ldr	x0, [x20, 408]
	ldr	x1, [x19, 648]
	str	x1, [x0, 808]
	ldr	x0, [x20, 408]
	ldrb	w1, [x19, 4]
	strb	w1, [x0, 801]
	ldr	x0, [x20, 408]
	ldrb	w1, [x19, 5]
	strb	w1, [x0, 802]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 688]
	str	w1, [x0, 824]
	ldr	x0, [x20, 408]
	ldrb	w1, [x19, 12]
	strb	w1, [x0, 803]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 708]
	str	w1, [x0, 832]
	ldr	x0, [x20, 408]
	ldr	w2, [x0, 784]
	ldr	w1, [x0, 832]
	add	w1, w2, w1
	str	w1, [x0, 44]
	str	w1, [x0, 736]
	ldr	x1, [x20, 408]
	ldrb	w0, [x1, 1]
	cbz	w0, .L3628
	ldrb	w0, [x19, 2]
.L3628:
	strb	w0, [x1, 1]
	ldr	x1, [x20, 408]
	ldrb	w0, [x1, 2]
	orr	w0, w0, 2
	strb	w0, [x1, 2]
	ldrb	w0, [x19, 7]
	ldr	x1, [x20, 408]
	cmp	w0, 1
	beq	.L3696
	ldrb	w0, [x1, 4]
.L3630:
	strb	w0, [x1, 4]
	mov	x2, 632
	add	x1, x19, 16
	ldr	x0, [x20, 408]
	add	x0, x0, 72
	ldr	x25, [x0, 584]
	ldr	x24, [x0, 592]
	ldr	x22, [x0, 600]
	bl	memcpy
	ldr	x0, [x19, 600]
	cmn	x0, #1
	ccmn	x25, #1, 4, eq
	beq	.L3631
	ldr	x0, [x20, 408]
	str	x25, [x0, 656]
.L3631:
	ldr	x0, [x19, 608]
	ldr	x1, [x20, 408]
	cmp	x0, x24
	csel	x0, x0, x24, ls
	str	x0, [x1, 664]
	ldr	x0, [x19, 616]
	ldr	x1, [x20, 408]
	cmp	x0, x22
	csel	x0, x0, x22, ls
	str	x0, [x1, 672]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	beq	.L3632
	ldrb	w0, [x19, 5]
	cmp	w0, 1
	beq	.L3632
.L3633:
	ldr	x1, [x20, 408]
	ldrb	w2, [x1, 803]
	ldrb	w0, [x1, 755]
	cmp	w0, w2, uxtb
	csel	w0, w0, w2, cs
	strb	w0, [x1]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 704]
	str	w1, [x0, 828]
	ldr	x1, [x20, 408]
	ldr	w0, [x1, 780]
	ldr	w2, [x1, 828]
	cmp	w0, w2
	csel	w0, w0, w2, le
	str	w0, [x1, 36]
	ldr	x0, [x20, 408]
	bl	MVC_CombineFldsToFrm
	ldr	x0, [x20, 408]
	ldrb	w1, [x19, 11]
	strb	w1, [x0, 13]
	ldr	x0, [x20, 408]
	ldrb	w1, [x19, 10]
	strb	w1, [x0, 11]
	ldr	x1, [x20, 408]
	ldr	w0, [x1, 52]
	ldr	w1, [x1, 824]
	add	x0, x0, 2781184
	add	x0, x0, 240
	str	w1, [x23, x0, lsl 2]
	b	.L3621
	.p2align 3
.L3603:
	add	x20, x23, x21, lsl 3
	ldr	x1, [x19, 648]
	add	x20, x20, 11124736
	mov	w2, 3
	mov	w0, 3
	str	x1, [x20, 408]
	ldrb	w3, [x19, 2]
	strb	w3, [x1, 1]
	ldr	x1, [x20, 408]
	strb	w2, [x1, 2]
	ldr	x2, [x19, 648]
	ldr	x1, [x20, 408]
	ldrb	w2, [x2, 5]
	strb	w2, [x1, 5]
	ldr	x2, [x19, 648]
	ldr	x1, [x20, 408]
	ldrb	w2, [x2, 7]
	strb	w2, [x1, 7]
	ldrb	w2, [x19, 4]
	ldr	x1, [x20, 408]
	cbz	w2, .L3697
.L3605:
	strb	w0, [x1, 3]
	mov	x2, 632
	add	x1, x19, 16
	mov	w22, 3
	ldr	x0, [x20, 408]
	ldr	w3, [x19, 732]
	str	w3, [x0, 48]
	ldr	x0, [x20, 408]
	add	x0, x0, 72
	bl	memcpy
	ldr	x0, [x20, 408]
	mov	w6, 1
	ldr	w1, [x19, 708]
	str	w1, [x0, 44]
	str	w1, [x0, 736]
	ldr	x0, [x20, 408]
	ldr	x1, [x19, 648]
	str	x1, [x0, 712]
	str	x1, [x0, 760]
	str	x1, [x0, 808]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 668]
	str	w1, [x0, 28]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 664]
	str	w1, [x0, 20]
	ldr	x0, [x20, 408]
	strb	wzr, [x0, 704]
	ldr	x0, [x20, 408]
	ldrb	w1, [x19, 4]
	strb	w1, [x0, 705]
	ldr	x0, [x20, 408]
	ldrb	w1, [x19, 5]
	strb	w1, [x0, 706]
	ldr	x0, [x20, 408]
	ldrb	w1, [x19, 12]
	strb	w1, [x0, 707]
	strb	w1, [x0]
	ldr	x0, [x20, 408]
	ldrb	w1, [x19, 9]
	str	w1, [x0, 40]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 676]
	str	w1, [x0, 32]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 680]
	str	w1, [x0, 728]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 684]
	str	w1, [x0, 776]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 688]
	str	w1, [x0, 824]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 692]
	str	w1, [x0, 36]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 696]
	str	w1, [x0, 732]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 700]
	str	w1, [x0, 780]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 704]
	str	w1, [x0, 828]
	ldrb	w1, [x19, 7]
	ldr	x0, [x20, 408]
	cmp	w1, 1
	csel	w22, wzr, w22, ne
	strb	w22, [x0, 4]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 736]
	str	w1, [x0, 56]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 740]
	str	w1, [x0, 60]
	ldr	x0, [x20, 408]
	ldrb	w1, [x19, 11]
	strb	w1, [x0, 13]
	strb	w1, [x0, 12]
	ldr	x1, .LC933
	ldr	x2, [x20, 408]
	ldrb	w3, [x19, 10]
	ldr	w0, [x1, 1948]
	strb	w3, [x2, 11]
	strb	w3, [x2, 10]
	add	w2, w0, 1
	str	w2, [x1, 1948]
	ldr	x1, [x20, 408]
	str	w0, [x1, 64]
	ldr	x0, [x20, 408]
	ldrb	w2, [x0, 707]
	ldr	x1, [x0, 712]
	ldrb	w4, [x0, 705]
	ldrb	w3, [x0, 706]
	ldr	w5, [x0, 736]
	strb	w2, [x0, 755]
	strb	w2, [x0, 803]
	mov	w2, 0
	str	x1, [x0, 760]
	str	x1, [x0, 808]
	mov	w1, 2
	strb	w4, [x0, 753]
	strb	w3, [x0, 754]
	strb	w6, [x0, 752]
	strb	w4, [x0, 801]
	strb	w3, [x0, 802]
	str	w5, [x0, 784]
	str	w5, [x0, 832]
	strb	w1, [x0, 800]
	mov	x0, x23
	ldr	x1, [x19, 648]
	bl	MVC_GetAPC
	cbnz	w0, .L3698
.L3621:
	add	x21, x21, 1388544
	mov	w19, 0
	add	x21, x23, x21, lsl 3
	ldr	x0, [x21, 16792]
	ldrb	w1, [x0, 3]
	cbz	w1, .L3608
	ldrsb	w1, [x0, 6]
	mov	w2, 1
	ldr	w0, [x23, 120]
	bl	FSP_SetRef
	ldr	x25, [sp, 64]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L3602:
	ldr	x0, [x19, 648]
	mov	w1, 3
	strb	w1, [x0, 704]
	ldrb	w0, [x19, 1]
	cbz	w0, .L3609
	add	x20, x23, x21, lsl 3
	add	x20, x20, 11124736
	ldr	x0, [x20, 408]
	cbz	x0, .L3609
	strb	w22, [x0, 752]
	ldr	x0, [x20, 408]
	ldrb	w1, [x19, 12]
	strb	w1, [x0, 755]
	ldr	x0, [x20, 408]
	ldrb	w1, [x19, 4]
	strb	w1, [x0, 753]
	ldr	x0, [x20, 408]
	ldrb	w1, [x19, 5]
	strb	w1, [x0, 754]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 684]
	str	w1, [x0, 776]
	ldr	x0, [x20, 408]
	ldrb	w1, [x19, 12]
	strb	w1, [x0, 755]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 708]
	str	w1, [x0, 784]
	ldr	x0, [x20, 408]
	ldr	w2, [x0, 784]
	ldr	w1, [x0, 832]
	add	w1, w2, w1
	str	w1, [x0, 44]
	str	w1, [x0, 736]
	ldr	x1, [x20, 408]
	ldrb	w0, [x1, 1]
	cbz	w0, .L3614
	ldrb	w0, [x19, 2]
.L3614:
	strb	w0, [x1, 1]
	ldr	x1, [x20, 408]
	ldrb	w0, [x1, 2]
	orr	w0, w0, 1
	strb	w0, [x1, 2]
	ldrb	w0, [x19, 7]
	ldr	x1, [x20, 408]
	cmp	w0, 1
	beq	.L3699
	ldrb	w0, [x1, 4]
.L3616:
	strb	w0, [x1, 4]
	mov	x2, 632
	add	x1, x19, 16
	ldr	x0, [x20, 408]
	add	x0, x0, 72
	ldr	x25, [x0, 584]
	ldr	x24, [x0, 592]
	ldr	x22, [x0, 600]
	bl	memcpy
	ldr	x0, [x19, 600]
	cmn	x0, #1
	ccmn	x25, #1, 4, eq
	beq	.L3617
	ldr	x0, [x20, 408]
	str	x25, [x0, 656]
.L3617:
	ldr	x0, [x19, 608]
	ldr	x1, [x20, 408]
	cmp	x0, x24
	csel	x0, x0, x24, ls
	str	x0, [x1, 664]
	ldr	x0, [x19, 616]
	ldr	x1, [x20, 408]
	cmp	x0, x22
	csel	x0, x0, x22, ls
	str	x0, [x1, 672]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	beq	.L3618
	ldrb	w0, [x19, 5]
	cmp	w0, 1
	beq	.L3618
.L3619:
	ldr	x1, [x20, 408]
	ldrb	w2, [x1, 803]
	ldrb	w0, [x1, 755]
	cmp	w0, w2, uxtb
	csel	w0, w0, w2, cs
	strb	w0, [x1]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 700]
	str	w1, [x0, 780]
	ldr	x1, [x20, 408]
	ldr	w0, [x1, 780]
	ldr	w2, [x1, 828]
	cmp	w0, w2
	csel	w0, w0, w2, le
	str	w0, [x1, 36]
	ldr	x0, [x20, 408]
	ldrb	w1, [x19, 11]
	strb	w1, [x0, 12]
	ldr	x0, [x20, 408]
	ldrb	w1, [x19, 10]
	strb	w1, [x0, 10]
	ldr	x0, [x20, 408]
	bl	MVC_CombineFldsToFrm
	ldr	x1, [x20, 408]
	ldr	w0, [x1, 52]
	ldr	w1, [x1, 776]
	add	x0, x0, 2781184
	add	x0, x0, 224
	str	w1, [x23, x0, lsl 2]
	b	.L3621
	.p2align 3
.L3609:
	add	x20, x23, x21, lsl 3
	ldr	x0, [x19, 648]
	add	x20, x20, 11124736
	mov	w1, 1
	str	x0, [x20, 408]
	strb	w1, [x0, 752]
	ldr	x0, [x20, 408]
	ldr	x2, [x19, 648]
	str	x2, [x0, 760]
	ldr	x0, [x20, 408]
	ldrb	w2, [x19, 4]
	strb	w2, [x0, 753]
	ldr	x0, [x20, 408]
	ldrb	w2, [x19, 5]
	strb	w2, [x0, 754]
	ldr	x0, [x20, 408]
	ldr	w2, [x19, 684]
	str	w2, [x0, 776]
	ldr	x0, [x20, 408]
	ldrb	w2, [x19, 12]
	strb	w2, [x0, 755]
	ldr	x0, [x20, 408]
	ldr	w2, [x19, 708]
	str	w2, [x0, 784]
	ldr	x0, [x20, 408]
	ldr	w2, [x0, 784]
	str	w2, [x0, 44]
	str	w2, [x0, 736]
	ldr	x0, [x20, 408]
	ldrb	w2, [x19, 2]
	strb	w2, [x0, 1]
	ldr	x0, [x20, 408]
	strb	w1, [x0, 2]
	ldr	x1, [x19, 648]
	ldr	x0, [x20, 408]
	ldrb	w1, [x1, 5]
	strb	w1, [x0, 5]
	ldr	x1, [x19, 648]
	ldr	x0, [x20, 408]
	ldrb	w1, [x1, 7]
	strb	w1, [x0, 7]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	beq	.L3611
	ldrb	w0, [x19, 5]
	cmp	w0, 1
	beq	.L3611
.L3612:
	ldr	x0, [x20, 408]
	mov	x2, 632
	add	x1, x19, 16
	str	wzr, [x0, 40]
	ldr	x0, [x20, 408]
	add	x0, x0, 72
	bl	memcpy
	ldr	x0, [x20, 408]
	mov	w2, 1
	ldr	w1, [x19, 732]
	ldr	x3, .LC933
	str	w1, [x0, 48]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 664]
	str	w1, [x0, 20]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 676]
	str	w1, [x0, 32]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 692]
	str	w1, [x0, 36]
	ldr	x0, [x20, 408]
	ldrb	w1, [x19, 12]
	strb	w1, [x0]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 700]
	str	w1, [x0, 780]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 736]
	str	w1, [x0, 56]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 740]
	str	w1, [x0, 60]
	ldr	x0, [x20, 408]
	ldrb	w1, [x19, 11]
	strb	w1, [x0, 12]
	ldr	x0, [x20, 408]
	ldrb	w1, [x19, 10]
	strb	w1, [x0, 10]
	mov	x0, x23
	ldr	x4, [x20, 408]
	ldr	w1, [x3, 1948]
	str	w1, [x4, 64]
	add	w5, w1, w2
	str	w5, [x3, 1948]
	ldr	x1, [x20, 408]
	ldrb	w3, [x19, 7]
	cmp	w3, w2
	cset	w3, eq
	strb	w3, [x1, 4]
	ldr	x1, [x19, 648]
	bl	MVC_GetAPC
	cbz	w0, .L3621
	ldr	x1, .LC935
	mov	w3, w0
	mov	w2, 2237
	b	.L3694
	.p2align 3
.L3622:
	add	x20, x23, x21, lsl 3
	ldr	x0, [x19, 648]
	add	x20, x20, 11124736
	mov	w1, 2
	str	x0, [x20, 408]
	strb	w1, [x0, 800]
	ldr	x0, [x20, 408]
	ldr	x2, [x19, 648]
	str	x2, [x0, 808]
	ldr	x0, [x20, 408]
	ldrb	w2, [x19, 4]
	strb	w2, [x0, 801]
	ldr	x0, [x20, 408]
	ldrb	w2, [x19, 5]
	strb	w2, [x0, 802]
	ldr	x0, [x20, 408]
	ldr	w2, [x19, 688]
	str	w2, [x0, 824]
	ldr	x0, [x20, 408]
	ldrb	w2, [x19, 12]
	strb	w2, [x0, 803]
	ldr	x0, [x20, 408]
	ldr	w2, [x19, 708]
	str	w2, [x0, 832]
	ldr	x0, [x20, 408]
	ldr	w2, [x0, 784]
	str	w2, [x0, 44]
	str	w2, [x0, 736]
	ldr	x0, [x20, 408]
	ldrb	w2, [x19, 2]
	strb	w2, [x0, 1]
	ldr	x0, [x20, 408]
	strb	w1, [x0, 2]
	ldr	x1, [x19, 648]
	ldr	x0, [x20, 408]
	ldrb	w1, [x1, 5]
	strb	w1, [x0, 5]
	ldr	x1, [x19, 648]
	ldr	x0, [x20, 408]
	ldrb	w1, [x1, 7]
	strb	w1, [x0, 7]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	beq	.L3624
	ldrb	w0, [x19, 5]
	cmp	w0, 1
	beq	.L3624
.L3625:
	ldr	x0, [x20, 408]
	mov	x2, 632
	add	x1, x19, 16
	str	wzr, [x0, 40]
	ldr	x0, [x20, 408]
	add	x0, x0, 72
	bl	memcpy
	ldr	x0, [x20, 408]
	mov	w2, 2
	ldr	w1, [x19, 732]
	str	w1, [x0, 48]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 664]
	str	w1, [x0, 20]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 676]
	str	w1, [x0, 32]
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 692]
	str	w1, [x0, 36]
	ldr	x0, [x20, 408]
	ldrb	w1, [x19, 12]
	strb	w1, [x0, 803]
	strb	w1, [x0]
	mov	x0, x23
	ldr	x1, [x20, 408]
	ldr	w3, [x19, 704]
	str	w3, [x1, 828]
	ldr	x1, [x20, 408]
	ldr	w3, [x19, 736]
	str	w3, [x1, 56]
	ldr	x1, [x20, 408]
	ldr	w3, [x19, 740]
	str	w3, [x1, 60]
	ldr	x1, [x20, 408]
	ldrb	w3, [x19, 11]
	strb	w3, [x1, 13]
	ldr	x1, [x20, 408]
	ldrb	w3, [x19, 10]
	strb	w3, [x1, 11]
	ldr	x4, [x20, 408]
	ldr	x3, .LC933
	ldr	w1, [x3, 1948]
	str	w1, [x4, 64]
	add	w1, w1, 1
	str	w1, [x3, 1948]
	ldrb	w3, [x19, 7]
	ldr	x1, [x20, 408]
	cmp	w3, 1
	csel	w22, w22, wzr, eq
	strb	w22, [x1, 4]
	ldr	x1, [x19, 648]
	bl	MVC_GetAPC
	cbz	w0, .L3621
	ldr	x1, .LC935
	mov	w3, w0
	mov	w2, 2362
.L3694:
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x23
	bl	MVC_ClearDPB
	b	.L3608
	.p2align 3
.L3697:
	ldrb	w0, [x19, 5]
	mov	w2, 3
	cmp	w0, wzr
	csel	w0, w0, w2, eq
	b	.L3605
	.p2align 3
.L3611:
	ldr	x0, [x20, 408]
	mov	w1, 1
	strb	w1, [x0, 3]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	bne	.L3612
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 668]
	str	w1, [x0, 28]
	b	.L3612
	.p2align 3
.L3624:
	ldr	x0, [x20, 408]
	mov	w1, 2
	strb	w1, [x0, 3]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	bne	.L3625
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 668]
	str	w1, [x0, 28]
	b	.L3625
	.p2align 3
.L3632:
	ldr	x1, [x20, 408]
	ldrb	w0, [x1, 3]
	orr	w0, w0, 2
	strb	w0, [x1, 3]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	bne	.L3633
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 668]
	str	w1, [x0, 28]
	b	.L3633
	.p2align 3
.L3618:
	ldr	x1, [x20, 408]
	ldrb	w0, [x1, 3]
	orr	w0, w0, 1
	strb	w0, [x1, 3]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	bne	.L3619
	ldr	x0, [x20, 408]
	ldr	w1, [x19, 668]
	str	w1, [x0, 28]
	b	.L3619
	.p2align 3
.L3696:
	ldrb	w0, [x1, 4]
	orr	w0, w0, 2
	uxtb	w0, w0
	b	.L3630
	.p2align 3
.L3699:
	ldrb	w0, [x1, 4]
	orr	w0, w0, 1
	uxtb	w0, w0
	b	.L3616
.L3698:
	ldr	x1, .LC935
	mov	w3, w0
	mov	w2, 2174
	b	.L3694
	.size	MVC_InsertFrmInDPB, .-MVC_InsertFrmInDPB
	.align	3
.LC933:
	.xword	.LANCHOR3
	.align	3
.LC935:
	.xword	.LC934
	.align	3
.LC937:
	.xword	.LC936
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_AllocFrameStore
	.type	MVC_AllocFrameStore, %function
MVC_AllocFrameStore:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x24, x0
	mov	x0, x30
	add	x20, x24, 11116544
	mov	w21, w1
	bl	_mcount
	mov	w25, 0
	ldrb	w0, [x20, 2841]
	cbz	w0, .L3701
	ldrb	w0, [x20, 2842]
	mov	w25, 2
	cmp	w0, wzr
	csinc	w25, w25, wzr, ne
.L3701:
	cmp	w21, 1
	ldrb	w0, [x24, 8]
	beq	.L3702
	cmp	w0, 2
	add	x23, x24, 11157504
	beq	.L3792
	sub	w0, w25, #1
	strb	wzr, [x23, 2313]
	cmp	w0, 1
	bls	.L3796
.L3704:
	strb	wzr, [x23, 2312]
	ldr	w4, [x24, 48]
	cbz	w4, .L3728
	add	x3, x24, 11124736
	mov	x22, 0
	add	x19, x3, 1160
	.p2align 2
.L3727:
	ldrb	w0, [x19, 2]
	cbnz	w0, .L3722
	cbz	x19, .L3723
	ldr	w0, [x3, 792]
	cbz	w0, .L3723
	ldr	x1, [x3, 408]
	cmp	x1, x19
	ccmp	x1, xzr, 4, eq
	bne	.L3722
	sub	w2, w0, #1
	add	x0, x3, 416
	add	x2, x2, 1388544
	add	x2, x2, 2100
	add	x2, x24, x2, lsl 3
	b	.L3725
	.p2align 3
.L3726:
	ldr	x1, [x0], 8
	cmp	x1, x19
	ccmp	x1, xzr, 4, eq
	bne	.L3722
.L3725:
	cmp	x2, x0
	bne	.L3726
.L3723:
	lsl	x1, x22, 3
	mov	w26, 1
	sub	x1, x1, x22
	str	x19, [x23, 2960]
	lsl	x1, x1, 2
	strb	w26, [x23, 2312]
	sub	x1, x1, x22
	mov	w3, 101
	lsl	x1, x1, x26
	mov	x2, 632
	sub	x22, x1, x22
	add	x0, x23, 2328
	add	x22, x24, x22, lsl 4
	add	x22, x22, 11124736
	add	x1, x22, 1232
	str	wzr, [x22, 1204]
	str	w3, [x23, 3020]
	bl	memcpy
	str	wzr, [x23, 2480]
	strb	wzr, [x22, 1164]
	strb	wzr, [x19, 7]
	ldr	x0, [x23, 2960]
	strb	wzr, [x0, 3]
	ldr	x0, [x23, 2960]
	strb	w26, [x0, 5]
	ldr	x0, [x23, 2960]
	str	wzr, [x0, 16]
	ldrb	w19, [x23, 2312]
	cmp	w19, 1
	bne	.L3728
	cmp	w21, wzr
	ldr	w0, [x24, 120]
	cset	w1, eq
	bl	FSP_NewLogicFs
	mov	w22, w0
	mov	w1, w0
	ldr	w0, [x24, 120]
	bl	FSP_GetLogicFs
	mov	x26, x0
	cmp	w22, wzr
	ccmp	x0, xzr, 4, ge
	beq	.L3729
	add	x1, x0, 48
	ldr	x0, [x24, 224]
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L3797
.L3730:
	ldr	x19, .LC942
	mov	x2, 632
	ldr	x0, [x23, 2960]
	ldr	x3, [x19, 104]
	add	x0, x0, 72
	blr	x3
	ldr	x1, [x23, 2960]
	mov	x2, 632
	ldr	x3, [x19, 104]
	add	x0, x23, 2328
	add	x1, x1, 72
	blr	x3
	ldr	x0, [x23, 2960]
	strb	w22, [x0, 6]
	ldrsb	w0, [x26, 4]
	str	w0, [x23, 3044]
.L3721:
	uxtb	w1, w25
	cmp	w21, 1
	strb	w1, [x23, 2315]
	beq	.L3740
.L3804:
	ldrb	w0, [x20, 2841]
	mov	w3, 3
	ldr	x2, [x23, 2960]
	cmp	w0, wzr
	csel	w0, w0, w3, eq
	strb	w0, [x2, 704]
	ldrb	w0, [x23, 2313]
	cmp	w0, 1
	beq	.L3798
	strb	w1, [x23, 3800]
	add	x0, x24, 11120640
	ldr	w1, [x20, 2868]
	str	w1, [x23, 3808]
	ldrb	w1, [x20, 2848]
	str	w1, [x23, 3804]
	ldr	w1, [x24, 128]
	str	w1, [x23, 3812]
	ldr	w0, [x0, 384]
	str	w0, [x23, 3824]
	str	w22, [x23, 3816]
	cbnz	w25, .L3799
	strb	wzr, [x23, 3801]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L3722:
	add	w22, w22, 1
	add	x19, x19, 848
	cmp	w22, w4
	bne	.L3727
.L3728:
	ldr	x1, .LC941
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x24
	bl	MVC_ClearAll
	mov	w0, -1
.L3787:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L3799:
	mov	w1, 1
	strb	w1, [x23, 3801]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L3702:
	cmp	w0, 2
	beq	.L3800
	add	x23, x24, 11157504
	mov	w25, 0
.L3792:
	strb	wzr, [x23, 2313]
	b	.L3704
.L3796:
	ldrb	w0, [x23, 3800]
	cbz	w0, .L3705
	add	x1, x24, 11120640
	ldr	w2, [x23, 3824]
	ldr	w1, [x1, 384]
	cmp	w2, w1
	beq	.L3706
.L3705:
	add	x0, x24, 11124736
	ldr	w1, [x0, 792]
	subs	w1, w1, #1
	bmi	.L3704
	add	x3, x24, 11120640
	b	.L3715
	.p2align 3
.L3708:
	cmp	w25, 2
	beq	.L3801
.L3707:
	subs	w1, w1, #1
	bmi	.L3704
.L3715:
	sxtw	x0, w1
	add	x0, x0, 1388544
	add	x0, x24, x0, lsl 3
	ldr	x19, [x0, 16792]
	cbz	x19, .L3707
	cmp	w25, 1
	bne	.L3708
	ldrb	w0, [x19, 2]
	cmp	w0, 2
	bne	.L3707
.L3709:
	ldr	w0, [x19, 20]
	ldr	w2, [x20, 2868]
	cmp	w2, w0
	bne	.L3707
	ldr	w2, [x3, 384]
	ldr	w0, [x19, 56]
	cmp	w2, w0
	bne	.L3707
	ldrb	w0, [x20, 2848]
	cbz	w0, .L3802
	ldrb	w0, [x19, 3]
	cbz	w0, .L3707
.L3711:
	mov	w0, 1
	add	x1, x19, 72
	strb	w0, [x23, 2313]
	mov	x2, 632
	add	x0, x23, 2328
	str	x19, [x23, 2960]
	bl	memcpy
	ldrsb	w1, [x19, 6]
	ldr	w0, [x24, 120]
	bl	FSP_GetLogicFs
	cbz	x0, .L3803
	ldrsb	w1, [x0, 4]
	ldrb	w0, [x23, 2313]
	str	w1, [x23, 3044]
	cbz	w0, .L3704
	ldr	x0, [x23, 2960]
	cbz	x0, .L3704
.L3791:
	uxtb	w1, w25
	cmp	w21, 1
	strb	w1, [x23, 2315]
	mov	w22, 0
	bne	.L3804
.L3740:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	mov	w0, 0
	ldp	x29, x30, [sp], 96
	ret
.L3797:
	ldp	w3, w2, [x24, 12]
	ldr	w0, [x1, 112]
	lsl	w2, w2, 4
	str	w2, [x1, 72]
	str	x1, [x29, 88]
	mul	w19, w2, w0
	ldr	w0, [x1, 36]
	lsl	w2, w3, 4
	str	w2, [x1, 68]
	add	w0, w19, w0
	str	w0, [x1, 40]
	bl	MEM_Phy2Vir
	ldr	x1, [x29, 88]
	str	x0, [x1, 512]
	ldr	w0, [x1, 20]
	ldr	w2, [x1, 116]
	add	w0, w19, w0
	str	w0, [x1, 24]
	add	w0, w2, w0
	str	w0, [x1, 32]
	b	.L3730
	.p2align 3
.L3801:
	ldrb	w0, [x19, 2]
	cmp	w0, 1
	bne	.L3707
	b	.L3709
.L3798:
	strb	wzr, [x23, 3800]
	add	x1, x24, 11120640
	mov	w0, 0
	ldr	w2, [x20, 2868]
	str	w2, [x23, 3808]
	ldrb	w2, [x20, 2848]
	str	w2, [x23, 3804]
	ldr	w2, [x24, 128]
	str	w2, [x23, 3812]
	strb	wzr, [x23, 3801]
	str	w22, [x23, 3816]
	ldr	w1, [x1, 384]
	str	w1, [x23, 3824]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L3800:
	add	x23, x24, 11157504
	mov	w25, 0
	strb	wzr, [x23, 2313]
	b	.L3704
.L3802:
	ldrb	w0, [x19, 3]
	cbnz	w0, .L3707
	b	.L3711
	.p2align 3
.L3706:
	cmp	w0, 1
	ccmp	w25, 2, 0, eq
	beq	.L3716
	cmp	w0, 2
	ccmp	w25, 1, 0, eq
	bne	.L3704
.L3716:
	ldr	w0, [x20, 2868]
	ldr	w1, [x23, 3808]
	cmp	w1, w0
	bne	.L3704
	ldrb	w0, [x20, 2848]
	cbnz	w0, .L3717
	ldr	w0, [x23, 3804]
	cbnz	w0, .L3704
.L3718:
	ldp	w1, w0, [x24, 124]
	sub	w0, w0, w1
	cmp	w0, 2
	bhi	.L3704
	ldr	x0, [x23, 2960]
	mov	w1, 1
	strb	w1, [x23, 2313]
	cbz	x0, .L3792
	cmp	w25, 2
	beq	.L3805
	cmp	w25, 1
	mov	w22, 0
	bne	.L3721
	ldrb	w0, [x0, 2]
	cmp	w0, 2
	beq	.L3721
	strb	wzr, [x23, 2313]
	b	.L3704
	.p2align 3
.L3729:
	ldr	x2, [x23, 2960]
	mov	w0, 0
	strb	wzr, [x23, 2312]
	ldr	x1, .LC944
	strb	wzr, [x2, 5]
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x24
	bl	MVC_ClearAll
	mov	w0, -1
	b	.L3787
.L3803:
	ldr	x1, .LC939
	mov	w2, 6560
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3787
.L3805:
	ldrb	w0, [x0, 2]
	cmp	w0, 1
	beq	.L3791
	strb	wzr, [x23, 2313]
	b	.L3704
.L3717:
	ldr	w0, [x23, 3804]
	cbz	w0, .L3704
	b	.L3718
	.size	MVC_AllocFrameStore, .-MVC_AllocFrameStore
	.align	3
.LC939:
	.xword	.LC938
	.align	3
.LC941:
	.xword	.LC940
	.align	3
.LC942:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC944:
	.xword	.LC943
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DEC_Init
	.type	MVC_DEC_Init, %function
MVC_DEC_Init:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x22, .LC945
	mov	x2, 22520
	mov	w1, 0
	movk	x2, 0xaa, lsl 16
	mov	x0, x20
	ldr	x3, [x22, 96]
	ldr	w21, [x20, 1512]
	blr	x3
	str	w21, [x20, 1512]
	add	x0, x20, 912
	bl	ResetVoQueue
	strb	wzr, [x20]
	stp	x19, xzr, [x20, 224]
	ldr	w0, [x19, 28]
	cmp	w0, 25
	beq	.L3815
	mov	w2, 32
	mov	w1, 256
	mov	w0, 136
	str	w1, [x20, 40]
	stp	w0, w2, [x20, 32]
.L3808:
	ldr	w0, [x19, 624]
	mov	w21, 2240
	bl	MEM_Phy2Vir
	ldr	x1, [x20, 224]
	mov	w2, 3992
	ldp	w4, w5, [x20, 36]
	ldrsw	x3, [x1, 620]
	smull	x2, w4, w2
	add	x3, x0, x3
	add	x1, x3, x2
	cmp	x1, xzr
	smaddl	x0, w5, w21, x1
	ccmp	x3, xzr, 4, ne
	str	x0, [x20, 864]
	ccmp	x0, xzr, 4, ne
	stp	x3, x1, [x20, 272]
	beq	.L3816
	ldr	w1, [x19, 656]
	cbz	w1, .L3817
.L3811:
	add	x2, x20, 11112448
	ldr	x6, [x22, 96]
	mov	w1, 0
	add	x23, x20, 12288
	add	x19, x23, 2396
	add	x21, x20, 10768384
	str	w4, [x2, 312]
	add	x21, x21, 4060
	str	w5, [x2, 3584]
	ldrsw	x3, [x20, 32]
	lsl	x2, x3, 7
	sub	x2, x2, x3
	lsl	x2, x2, 5
	blr	x6
	strb	wzr, [x20, 4]
	ldr	w0, [x20, 108]
	mov	w1, 40
	strb	wzr, [x20, 6]
	mov	x2, 9856
	ubfx	x0, x0, 16, 2
	strb	w0, [x20, 8]
	mov	w0, 18
	strb	wzr, [x20, 7]
	stp	w1, w0, [x20, 48]
	add	x0, x20, 512
	str	wzr, [x20, 220]
	stp	wzr, wzr, [x20, 56]
	stp	wzr, wzr, [x20, 68]
	stp	wzr, wzr, [x20, 76]
	stp	wzr, wzr, [x20, 84]
	stp	wzr, wzr, [x20, 92]
	stp	xzr, xzr, [x0, 320]
	stp	xzr, xzr, [x0, 336]
	movk	x2, 0xa4, lsl 16
	mov	w1, 0
	ldr	x3, [x22, 96]
	mov	x0, x19
	blr	x3
	mov	x2, 8500
	ldr	x3, [x22, 96]
	mov	w1, 0
	movk	x2, 0x5, lsl 16
	mov	x0, x21
	blr	x3
	mov	x0, x19
	.p2align 2
.L3812:
	add	x1, x0, 274432
	add	x2, x0, 335872
	strb	wzr, [x0]
	add	x0, x2, 308
	cmp	x21, x0
	strb	wzr, [x1, 241]
	bne	.L3812
	add	x0, x20, 11108352
	strb	wzr, [x23, 2384]
	add	x0, x0, 3664
	mov	w1, 32
	str	x0, [x20, 248]
	mov	x0, x20
	strb	wzr, [x20, 2]
	stp	wzr, w1, [x20, 20]
	str	w1, [x20, 28]
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x20, 120]
	beq	.L3818
	mov	w1, 0
	mov	x0, x20
	bl	MVC_ClearAll
	mov	w0, 1
.L3810:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L3817:
	ldr	x4, [x22, 96]
	mov	x0, x3
	blr	x4
	ldr	w2, [x20, 40]
	mov	w1, 0
	ldr	x0, [x20, 280]
	ldr	x3, [x22, 96]
	smull	x2, w2, w21
	blr	x3
	ldp	w4, w5, [x20, 36]
	ldr	x0, [x20, 864]
	b	.L3811
.L3815:
	ldr	w0, [x19, 740]
	str	w0, [x20, 36]
	ldr	w0, [x19, 744]
	str	w0, [x20, 40]
	ldr	w0, [x19, 732]
	str	w0, [x20, 32]
	b	.L3808
.L3816:
	ldr	x2, .LC946
	mov	w3, 13812
	ldr	x1, .LC948
	mov	w0, 22
	add	x2, x2, 352
	bl	dprint_vfmw
	mov	w0, -20
	b	.L3810
.L3818:
	ldr	x1, .LC950
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L3810
	.size	MVC_DEC_Init, .-MVC_DEC_Init
	.align	3
.LC945:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC946:
	.xword	.LANCHOR0
	.align	3
.LC948:
	.xword	.LC947
	.align	3
.LC950:
	.xword	.LC949
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_StorePicInDpb
	.type	MVC_StorePicInDpb, %function
MVC_StorePicInDpb:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 11157504
	bl	_mcount
	add	x0, x19, 11116544
	strb	wzr, [x0, 1704]
	ldrb	w1, [x21, 2315]
	cmp	w1, 2
	cset	w1, eq
	strb	w1, [x0, 1705]
	ldrb	w0, [x21, 2312]
	cbz	w0, .L3994
	ldr	w0, [x19, 128]
	str	w0, [x19, 124]
	ldrb	w0, [x21, 2325]
	cbz	w0, .L3822
	ldr	x0, [x21, 2968]
	ldrb	w0, [x0, 1]
	cbz	w0, .L3823
	cbz	x19, .L3825
	mov	x0, x19
	bl	MVC_ClearAllSlice
	mov	x0, x19
	bl	MVC_InitDPB.part.16
	cbnz	w0, .L3825
.L3822:
	ldrb	w0, [x19, 8]
	cmp	w0, 2
	beq	.L3995
	ldr	x20, [x19, 224]
	ldr	w0, [x20, 24]
	cbz	w0, .L3996
	ldrb	w1, [x21, 2314]
	cbnz	w1, .L3832
.L3902:
	ldrb	w2, [x21, 2315]
	ldr	x22, [x21, 2960]
	sub	w1, w2, #1
	uxtb	w1, w1
	cbnz	w2, .L3997
.L3833:
	cmp	w1, 1
	bls	.L3998
.L3978:
	cbnz	w2, .L3999
.L3838:
	cbz	w0, .L3908
	add	x24, x21, 2312
	mov	x20, x22
.L3841:
	cbz	w2, .L3843
	ldrb	w0, [x24, 1]
	cmp	w0, 1
	beq	.L4000
.L3843:
	ldr	w0, [x24, 708]
	str	w0, [x20, 44]
.L3844:
	mov	x1, x20
	mov	x0, x19
	bl	MVC_GetImagePara
	ldrsb	w1, [x20, 6]
	ldr	w0, [x19, 120]
	bl	FSP_GetFsImagePtr
	mov	x23, x0
	cbz	x0, .L4001
	ldr	x0, [x24, 600]
	str	x0, [x23, 584]
	ldr	x0, [x24, 608]
	str	x0, [x23, 592]
	ldr	x0, [x24, 616]
	str	x0, [x23, 600]
	ldr	w0, [x20, 44]
	str	w0, [x23, 152]
	cbz	w0, .L3851
	ldrb	w1, [x23, 64]
	and	w1, w1, 3
	cbz	w1, .L4002
.L3849:
	ldr	x1, [x19, 224]
	ldr	w1, [x1, 4]
	cmp	w1, w0
	bcc	.L4003
.L3851:
	ldrsb	w1, [x20, 6]
	mov	w2, 1
	ldr	w0, [x19, 120]
	bl	FSP_SetDisplay
	ldr	w0, [x19, 120]
	mov	x4, x23
	add	x3, x19, 912
	mov	x2, x19
	mov	w1, 15
	bl	InsertImgToVoQueue
	cmp	w0, 1
	beq	.L3848
	ldrsb	w1, [x20, 6]
	mov	w2, 0
	ldr	w0, [x19, 120]
	bl	FSP_SetDisplay
.L3848:
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 652]
	add	w0, w0, 2047
	cmp	w0, 4095
	bhi	.L4004
	str	wzr, [x23, 16]
.L3854:
	ldr	w0, [x19, 136]
	add	w0, w0, 2
	str	w0, [x19, 136]
.L3842:
	ldr	w0, [x19, 220]
	cmp	w0, 2
	beq	.L3855
.L3840:
	mov	w0, 1
	str	w0, [x20, 16]
	strb	w0, [x22, 8]
.L3855:
	ldr	x0, [x19, 224]
	mov	w1, 2
	str	w1, [x19, 220]
	ldr	w0, [x0, 24]
.L3832:
	cmp	w0, 2
	bne	.L3831
	ldr	w0, [x21, 2984]
	cbz	w0, .L3856
	add	x20, x19, 11124736
	mov	x0, x19
	bl	MVC_SimpleSlideDPB
	ldr	w1, [x20, 792]
	cbz	w1, .L3857
	ldr	x0, [x20, 408]
	cbz	x0, .L4005
	add	x2, x20, 416
	mov	w0, 0
	b	.L3859
	.p2align 3
.L3860:
	ldr	x3, [x2], 8
	cbz	x3, .L4006
.L3859:
	add	w0, w0, 1
	cmp	w0, w1
	bne	.L3860
.L3857:
	add	x2, x21, 2312
	mov	x0, x19
	bl	MVC_InsertFrmInDPB
	cbnz	w0, .L4007
	ldr	w1, [x20, 796]
	mov	x0, x19
	add	w1, w1, 1
	str	w1, [x20, 796]
	bl	MVC_UpdateReflist
	mov	x0, x19
	bl	MVC_UpdateLTReflist
	ldr	x1, .LC954
	mov	w3, 3742
	mov	w2, 0
	mov	w0, 14
	bl	dprint_vfmw
	.p2align 2
.L3862:
	mov	w20, 0
.L3901:
	strb	wzr, [x21, 2312]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L3996:
	ldr	w1, [x19, 220]
	cmp	w1, 2
	beq	.L3831
	ldrb	w1, [x21, 2314]
	cbz	w1, .L3902
.L3831:
	ldr	w0, [x21, 2984]
	cbz	w0, .L3863
	ldr	w3, [x19, 112]
	ldr	w2, [x21, 3020]
	cmp	w3, w2
	bcs	.L3864
	ldrb	w0, [x21, 2314]
	cbz	w0, .L4008
.L3864:
	mov	x0, x19
	bl	MVC_Marking
	cbnz	w0, .L4009
	mov	x0, x19
	bl	MVC_UpdateReflist
	mov	x0, x19
	bl	MVC_UpdateLTReflist
	ldr	w1, [x21, 3048]
	mov	x0, x19
	bl	MVC_RemoveUnUsedFrameStore
.L3856:
	ldrb	w0, [x21, 2313]
	cmp	w0, 1
	beq	.L3867
	add	x20, x19, 11124736
	ldr	w0, [x20, 792]
.L3868:
	ldr	w1, [x21, 2984]
	cbz	w1, .L3877
	ldr	w4, [x20, 800]
	ldr	w5, [x20, 804]
	add	w1, w4, w5
	cmp	w1, w0
	bcs	.L3904
.L3877:
	mov	w23, -1
	mov	w22, w23
	b	.L3886
	.p2align 3
.L3880:
	ldr	w22, [x29, 72]
.L3881:
	ldr	w3, [x21, 2984]
	mov	w1, w22
	mov	x0, x19
	mov	w23, w2
	cbnz	w3, .L3882
	ldr	w3, [x21, 2988]
	ldr	w2, [x29, 68]
	cmp	w3, w2
	blt	.L4010
.L3882:
	bl	MVC_OutputFrmFromDPB
	cmn	w0, #1
	mov	w24, w0
	beq	.L3885
	ldr	w0, [x20, 792]
.L3886:
	ldr	w4, [x20, 796]
	add	x3, x29, 72
	add	x2, x29, 68
	mov	w1, -1
	cmp	w4, w0
	mov	x0, x19
	bcc	.L3879
	bl	MVC_GetMinPOC
	tbnz	w0, #31, .L4011
	ldr	w2, [x20, 796]
	cmp	w23, w2
	bne	.L3880
	ldr	w0, [x29, 72]
	cmp	w22, w0
	beq	.L4012
	mov	w22, w0
	b	.L3881
	.p2align 3
.L4011:
	ldr	x1, .LC973
	mov	w2, 3844
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	mov	x0, x19
	bl	MVC_ClearDPB
.L3879:
	ldr	w0, [x21, 2984]
	cbz	w0, .L3891
	ldrb	w0, [x21, 2316]
	cbnz	w0, .L3891
	ldr	w0, [x20, 800]
	cbz	w0, .L3891
	mov	w1, 0
	b	.L3896
	.p2align 3
.L3893:
	ldr	w0, [x20, 800]
	cmp	w0, w1
	bls	.L3891
.L3896:
	add	x0, x19, x1, uxtw 3
	ldr	w3, [x21, 2976]
	add	x0, x0, 11124736
	add	w1, w1, 1
	ldr	x2, [x0, 536]
	ldr	w4, [x2, 20]
	cmp	w4, w3
	bne	.L3893
	ldr	w4, [x2, 56]
	ldr	w3, [x21, 3048]
	cmp	w4, w3
	bne	.L3893
	strb	wzr, [x2, 3]
	ldr	x2, [x0, 536]
	ldrb	w3, [x2, 5]
	cmp	w3, 1
	beq	.L4013
.L3895:
	ldr	w0, [x2, 48]
	ldr	w3, [x19, 52]
	cmp	w0, w3
	add	x0, x19, x0, uxtw 2
	beq	.L3893
	str	wzr, [x0, 148]
	str	w3, [x2, 48]
	b	.L3893
	.p2align 3
.L3891:
	ldr	w1, [x20, 792]
	cbz	w1, .L3890
	ldr	x0, [x20, 408]
	cbz	x0, .L4014
	add	x2, x20, 416
	mov	w0, 0
	b	.L3898
	.p2align 3
.L3899:
	ldr	x3, [x2], 8
	cbz	x3, .L4015
.L3898:
	add	w0, w0, 1
	cmp	w0, w1
	bne	.L3899
.L3890:
	add	x2, x21, 2312
	mov	x0, x19
	bl	MVC_InsertFrmInDPB
	cbnz	w0, .L4016
	ldr	w1, [x20, 796]
	mov	x0, x19
	add	w1, w1, 1
	str	w1, [x20, 796]
	bl	MVC_UpdateReflist
	mov	x0, x19
	bl	MVC_UpdateLTReflist
	b	.L3862
	.p2align 3
.L3863:
	ldrb	w0, [x21, 2313]
	cmp	w0, 1
	beq	.L3867
	add	x20, x19, 11124736
	ldr	w0, [x20, 792]
	b	.L3877
	.p2align 3
.L3867:
	ldr	x0, [x19, 816]
	ldr	x4, [x21, 2960]
	cmp	x0, xzr
	ccmp	x4, x0, 0, ne
	bne	.L4017
	mov	x0, x19
	bl	MVC_DirectOutput
	cmn	w0, #1
	mov	w20, w0
	beq	.L4018
.L3873:
	ldr	x1, .LC954
	mov	w3, 3794
	mov	w2, w20
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3828
	.p2align 3
.L3997:
	ldrb	w3, [x22, 2]
	cmp	w3, wzr
	ccmp	w1, 1, 0, eq
	bhi	.L3832
	b	.L3833
	.p2align 3
.L3999:
	ldrb	w1, [x22, 2]
	cbz	w1, .L3832
	b	.L3838
.L3998:
	ldr	w1, [x19, 220]
	cbnz	w1, .L3835
	mov	w0, 1
	mov	x2, 744
	str	w0, [x19, 220]
	add	x1, x21, 2312
	add	x0, x21, 3056
	bl	memcpy
	ldr	w0, [x20, 24]
	b	.L3832
.L4017:
	add	x20, x19, 11124736
	ldr	w0, [x20, 792]
	cbz	w0, .L3870
	ldr	x1, [x20, 408]
	add	x3, x20, 416
	cmp	x4, x1
	ccmp	x1, xzr, 4, eq
	mov	w1, 0
	bne	.L4019
	.p2align 2
.L3874:
	add	w1, w1, 1
	cmp	w1, w0
	beq	.L3868
	ldr	x2, [x3], 8
	cmp	x4, x2
	ccmp	x2, xzr, 4, eq
	beq	.L3874
.L3871:
	add	x2, x21, 2312
	mov	x0, x19
	bl	MVC_InsertFrmInDPB
	cmn	w0, #1
	mov	w20, w0
	beq	.L4020
	mov	x0, x19
	bl	MVC_UpdateReflist
	mov	x0, x19
	bl	MVC_UpdateLTReflist
	ldr	x1, .LC954
	mov	w3, 3820
	mov	w2, 0
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3862
.L3835:
	cmp	w1, 1
	bne	.L3978
	ldr	x20, [x21, 3704]
	cbz	w0, .L3840
	add	x24, x21, 3056
	ldrb	w2, [x24, 3]
	b	.L3841
	.p2align 3
.L3885:
	ldr	x22, .LC965
	mov	w3, w0
	mov	w2, 3884
	mov	w0, 1
	mov	x1, x22
	bl	dprint_vfmw
	ldr	x1, .LC954
	mov	w3, 3885
	mov	w2, w24
	mov	w0, 14
	bl	dprint_vfmw
.L3906:
	ldr	x1, [x21, 2960]
	mov	w2, 1
	ldr	w0, [x19, 120]
	mov	w20, -1
	ldrsb	w1, [x1, 6]
	bl	FSP_ClearLogicFs
	mov	w3, w20
	mov	x1, x22
	mov	w2, 3943
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, [x21, 2960]
	strb	wzr, [x0, 5]
	ldr	x0, [x21, 2960]
	strb	wzr, [x0, 2]
	mov	w0, w20
	strb	wzr, [x21, 2312]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4015:
	mov	w1, w0
	b	.L3890
	.p2align 3
.L3823:
	mov	w1, -1
	mov	x0, x19
	bl	MVC_FlushDPB
	cbz	w0, .L3822
	ldr	x1, .LC958
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x1, .LC954
	mov	w3, 3571
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x22, .LC965
	b	.L3906
	.p2align 3
.L3995:
	ldr	x1, .LC960
	bl	dprint_vfmw
	mov	x0, x19
	bl	MVC_DirectOutput
	mov	w20, w0
	ldr	w1, [x19, 52]
	ldr	w0, [x21, 3044]
	cmp	w0, w1
	beq	.L3827
	add	x0, x19, x0, uxtw 2
	str	wzr, [x0, 148]
	str	w1, [x21, 3044]
.L3827:
	ldr	x1, .LC954
	mov	w3, 3590
	mov	w2, w20
	mov	w0, 14
	bl	dprint_vfmw
.L3828:
	cmn	w20, #1
	bne	.L3901
	ldr	x22, .LC965
	b	.L3906
	.p2align 3
.L4010:
	ldrb	w0, [x19, 8]
	cmp	w0, 2
	beq	.L4021
.L3883:
	mov	x0, x19
	bl	MVC_DirectOutput
	cmn	w0, #1
	mov	w20, w0
	beq	.L4022
.L3884:
	ldr	x1, .LC954
	mov	w3, 3876
	mov	w2, w20
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3828
	.p2align 3
.L3825:
	ldr	x1, .LC956
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x1, .LC954
	mov	w3, 3561
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x22, .LC965
	b	.L3906
	.p2align 3
.L3908:
	mov	x20, x22
	b	.L3842
.L4013:
	strb	w3, [x2, 7]
	ldr	x2, [x0, 536]
	strb	wzr, [x2, 5]
	ldr	x2, [x0, 536]
	b	.L3895
.L4000:
	mov	w0, 3
	strb	w0, [x20, 2]
	ldr	w1, [x20, 44]
	ldr	w0, [x24, 708]
	add	w0, w1, w0
	str	w0, [x20, 44]
	b	.L3844
.L4002:
	ldr	x1, .LC962
	mov	w2, 3671
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC963
	ldr	x4, [x0]
	cbz	x4, .L3850
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 111
	blr	x4
.L3850:
	ldr	w0, [x23, 152]
	cbnz	w0, .L3849
	b	.L3851
	.p2align 3
.L4012:
	ldr	x2, .LC974
	mov	w3, w22
	ldr	x1, .LC976
	mov	w0, 1
	add	x2, x2, 368
	bl	dprint_vfmw
	ldr	x1, .LC954
	mov	w3, 3853
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x22, .LC965
	b	.L3906
.L4021:
	ldrb	w0, [x21, 2315]
	cbz	w0, .L3883
	ldr	x0, [x21, 2960]
	str	x0, [x19, 824]
	b	.L3883
.L4006:
	mov	w1, w0
	b	.L3857
.L4004:
	mov	x1, x23
	mov	x0, x19
	bl	MVC_SetFrmRepeatCount.part.2
	b	.L3854
.L3994:
	ldr	x1, .LC952
	bl	dprint_vfmw
	ldr	x1, .LC954
	mov	w3, 3547
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x22, .LC965
	b	.L3906
.L4022:
	ldr	x1, .LC965
	mov	w3, w0
	mov	w2, 3873
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3884
.L4009:
	ldr	x1, .LC969
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, .LC954
	mov	w3, 3767
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x22, .LC965
	b	.L3906
.L4014:
	mov	w1, 0
	b	.L3890
.L4016:
	ldr	x22, .LC965
	mov	w3, w0
	mov	w2, 3929
	mov	w0, 1
	mov	x1, x22
	bl	dprint_vfmw
	ldr	x1, .LC954
	mov	w3, 3930
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3906
.L3870:
	ldr	w1, [x21, 2984]
	cbz	w1, .L3877
	ldr	w4, [x20, 800]
	ldr	w5, [x20, 804]
.L3904:
	ldr	x1, .LC971
	mov	w3, w0
	mov	w2, 3833
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, -1
	mov	x0, x19
	bl	MVC_ClearDPB
	ldr	x1, .LC954
	mov	w3, 3836
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x22, .LC965
	b	.L3906
.L4008:
	ldr	x1, .LC967
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC963
	ldr	x4, [x0]
	cbz	x4, .L3865
	ldr	w1, [x19, 112]
	mov	w3, 8
	ldr	w2, [x21, 3020]
	ldr	w0, [x19, 120]
	stp	w2, w1, [x29, 72]
	add	x2, x29, 72
	mov	w1, 104
	blr	x4
.L3865:
	mov	x0, x19
	mov	w20, -1
	bl	MVC_ClearAllSlice
	add	x3, x19, 11120640
	mov	w2, 23352
	movk	w2, 0x1, lsl 16
	ldr	w4, [x19, 40]
	mov	w0, 2
	mov	w1, w20
	str	w2, [x3, 416]
	add	x2, x3, 256
	strb	w0, [x3, 401]
	mov	w0, 32
	str	w4, [x3, 412]
	strb	w0, [x3, 402]
	mov	w0, 3
	strb	wzr, [x3, 400]
	stp	w0, w20, [x2, 168]
	stp	wzr, wzr, [x2, 176]
	mov	w2, 7
	mov	x0, x19
	strb	w2, [x3, 403]
	mov	w2, 262144
	str	w2, [x3, 440]
	bl	MVC_ClearDPB
	ldr	x1, .LC954
	mov	w3, 3758
	mov	w2, w20
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x22, .LC965
	b	.L3906
.L4005:
	mov	w1, 0
	b	.L3857
.L4018:
	ldr	x1, .LC965
	mov	w3, w0
	mov	w2, 3790
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3873
.L4019:
	mov	w1, 0
	b	.L3871
.L4007:
	ldr	x22, .LC965
	mov	w3, w0
	mov	w2, 3733
	mov	w0, 0
	mov	x1, x22
	bl	dprint_vfmw
	ldr	x1, .LC954
	mov	w3, 3734
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3906
.L4020:
	ldr	x22, .LC965
	mov	w3, w0
	mov	w2, 3813
	mov	w0, 1
	mov	x1, x22
	bl	dprint_vfmw
	ldr	x1, .LC954
	mov	w3, 3814
	mov	w2, w20
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3906
.L4003:
	ldrsb	w1, [x20, 6]
	mov	w2, 0
	ldr	w0, [x19, 120]
	bl	FSP_SetDisplay
	ldr	x1, .LC954
	mov	w3, 3690
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x22, .LC965
	b	.L3906
.L4001:
	ldr	x1, .LC954
	mov	w3, 3660
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x22, .LC965
	b	.L3906
	.size	MVC_StorePicInDpb, .-MVC_StorePicInDpb
	.align	3
.LC952:
	.xword	.LC951
	.align	3
.LC954:
	.xword	.LC953
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
.LC962:
	.xword	.LC961
	.align	3
.LC963:
	.xword	g_event_report
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
.LC974:
	.xword	.LANCHOR0
	.align	3
.LC976:
	.xword	.LC975
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecGap
	.type	MVC_DecGap, %function
MVC_DecGap:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	add	x22, x19, 11116544
	add	x23, x19, 11120640
	bl	_mcount
	add	x27, x19, 11157504
	ldrb	w2, [x19, 3]
	mov	w26, 2
	ldr	w0, [x22, 1744]
	str	w0, [x29, 108]
	lsl	x0, x2, 6
	sub	x0, x0, x2
	ldr	x3, [x19, 248]
	lsl	x0, x0, 2
	ldr	w1, [x23, 388]
	sub	x0, x0, x2
	ldr	w24, [x22, 2868]
	lsl	x0, x0, 1
	add	x1, x1, 2777088
	sub	x0, x0, x2
	ldrb	w2, [x3, 19]
	lsl	x0, x0, 2
	add	x1, x19, x1, lsl 2
	cmp	w2, 1
	add	x2, x19, x0
	add	x2, x2, 11120640
	add	x0, x0, 11120640
	ldr	w5, [x1, 11052]
	add	x0, x0, 448
	add	x0, x19, x0
	ldr	w21, [x3, 2896]
	ldrb	w1, [x2, 451]
	csel	w25, w26, wzr, eq
	ldr	w2, [x22, 1748]
	stp	w1, w2, [x29, 100]
	add	x1, x19, 11124736
	str	x0, [x27, 2968]
	ldr	w0, [x1, 796]
	cbz	w0, .L4039
	add	w21, w21, 4
	mov	w20, 1
	add	w2, w5, 1
	lsl	w21, w20, w21
	ldr	x1, .LC980
	mov	w0, w26
	udiv	w5, w2, w21
	str	wzr, [x22, 1744]
	str	wzr, [x22, 1748]
	msub	w28, w5, w21, w2
	bl	dprint_vfmw
	ldr	x1, .LC982
	mov	w3, w28
	mov	w2, w24
	mov	w0, w26
	bl	dprint_vfmw
	cmp	w24, w28
	ble	.L4032
	ldr	x26, .LC986
	b	.L4036
	.p2align 3
.L4029:
	strb	wzr, [x27, 2316]
	mov	x0, x19
	bl	MVC_StorePicInDpb
	add	w1, w28, 1
	cbnz	w0, .L4040
.L4030:
	sdiv	w2, w1, w21
	ldr	w0, [x23, 388]
	add	x0, x0, 2777088
	add	x0, x19, x0, lsl 2
	str	w28, [x0, 11052]
	msub	w28, w2, w21, w1
	cmp	w24, w28
	ble	.L4032
.L4036:
	mov	w1, 1
	mov	x0, x19
	bl	MVC_AllocFrameStore
	cbnz	w0, .L4041
	mov	x1, x26
	mov	w0, 2
	bl	dprint_vfmw
	strb	w20, [x27, 2318]
	ldr	x0, [x27, 2960]
	str	w28, [x0, 20]
	str	w28, [x27, 2976]
	ldr	x0, [x27, 2960]
	str	w28, [x0, 724]
	str	w25, [x27, 2984]
	ldr	x0, [x27, 2960]
	str	wzr, [x0, 720]
	ldr	x0, [x27, 2960]
	strb	w20, [x0, 7]
	ldr	x0, [x27, 2960]
	strb	wzr, [x0, 5]
	ldr	x0, [x27, 2960]
	strb	w20, [x0, 1]
	strb	w20, [x27, 2314]
	ldr	x0, [x27, 2968]
	ldr	w1, [x23, 384]
	str	w1, [x27, 3048]
	strb	wzr, [x0, 3]
	ldr	x0, [x19, 248]
	ldr	w0, [x0, 2900]
	cbz	w0, .L4029
	mov	x0, x19
	str	w28, [x22, 1760]
	bl	MVC_DecPOC
	ldr	w0, [x22, 1740]
	str	w0, [x27, 2988]
	ldr	w0, [x22, 1736]
	str	w0, [x27, 2992]
	ldr	w0, [x22, 1728]
	str	w0, [x27, 2996]
	ldr	w0, [x22, 1732]
	str	w0, [x27, 3000]
	mov	x0, x19
	strb	wzr, [x27, 2316]
	bl	MVC_StorePicInDpb
	add	w1, w28, 1
	cbz	w0, .L4030
.L4040:
	ldr	w1, [x29, 108]
	mov	w3, w0
	str	w1, [x22, 1744]
	mov	w2, 6828
	ldr	w1, [x29, 104]
	mov	w0, 0
	str	w1, [x22, 1748]
	ldrb	w5, [x29, 100]
	ldr	x4, [x27, 2968]
	ldr	x1, .LC988
	strb	w5, [x4, 3]
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
.L4039:
	ldr	x1, .LC978
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L4032:
	ldr	w0, [x29, 108]
	str	w0, [x22, 1744]
	ldr	w0, [x29, 104]
	str	w0, [x22, 1748]
	mov	w0, 0
	ldrb	w2, [x29, 100]
	ldr	x1, [x27, 2968]
	strb	w2, [x1, 3]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L4041:
	ldr	w0, [x29, 108]
	str	w0, [x22, 1744]
	ldr	w0, [x29, 104]
	str	w0, [x22, 1748]
	mov	w0, 0
	ldrb	w3, [x29, 100]
	ldr	x2, [x27, 2968]
	ldr	x1, .LC984
	strb	w3, [x2, 3]
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.size	MVC_DecGap, .-MVC_DecGap
	.align	3
.LC978:
	.xword	.LC977
	.align	3
.LC980:
	.xword	.LC979
	.align	3
.LC982:
	.xword	.LC981
	.align	3
.LC984:
	.xword	.LC983
	.align	3
.LC986:
	.xword	.LC985
	.align	3
.LC988:
	.xword	.LC987
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_InitPic
	.type	MVC_InitPic, %function
MVC_InitPic:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 11116544
	add	x20, x19, 11157504
	bl	_mcount
	mov	w22, 2240
	ldr	x2, [x19, 280]
	ldr	w0, [x21, 2856]
	ldrb	w1, [x20, 2312]
	str	wzr, [x29, 92]
	umull	x0, w0, w22
	add	x22, x2, x0
	cbz	w1, .L4043
	ldr	x0, [x20, 2960]
	cbz	x0, .L4044
	ldrb	w1, [x0, 2]
	cbz	w1, .L4205
.L4044:
	strb	wzr, [x20, 2312]
.L4043:
	add	x1, x29, 92
	mov	x0, x19
	bl	MVC_GetReRangeFlag
	mov	w23, w0
	ldrsb	w0, [x21, 2852]
	cmn	w0, #1
	beq	.L4206
.L4045:
	cbnz	w0, .L4048
	ldrb	w0, [x19, 2]
	cmp	w0, 1
	beq	.L4207
	ldr	w1, [x19, 28]
	ldr	w0, [x22, 28]
	cmp	w1, w0
	bne	.L4208
	add	x0, x19, 11046912
	add	x0, x0, 180
	str	x0, [x19, 248]
.L4048:
	add	x24, x19, 11112448
	ldr	w0, [x22, 24]
	ldr	w1, [x24, 3584]
	cmp	w1, w0
	beq	.L4209
.L4052:
	strb	wzr, [x22, 20]
	mov	x1, x22
	ldr	x0, [x19, 248]
	bl	mvc_assign_quant_params
	ldr	x3, .LC989
	mov	x2, 2240
	mov	x1, x22
	add	x0, x24, 3560
	ldr	x3, [x3, 112]
	blr	x3
.L4053:
	ldr	w0, [x29, 92]
	cbnz	w0, .L4210
	ldr	x0, [x19, 224]
	ldr	w1, [x0, 928]
	cmp	w1, 1
	beq	.L4055
.L4065:
	ldr	w0, [x22, 24]
	ldr	w1, [x24, 3584]
	cmp	w1, w0
	bne	.L4075
	ldrb	w0, [x22, 20]
	cbnz	w0, .L4075
	ldrsb	w0, [x21, 2852]
	cmn	w0, #1
	beq	.L4211
.L4077:
	cbnz	w0, .L4078
	add	x0, x19, 10768384
	add	x23, x19, 11120640
	add	x5, x0, 4068
	ldr	w2, [x0, 4064]
	ldr	w3, [x23, 384]
	adds	w2, w2, 1
	beq	.L4079
	ldr	w0, [x0, 4068]
	cmp	w3, w0
	beq	.L4212
	mov	w4, w2
	mov	w0, 0
	b	.L4081
	.p2align 3
.L4082:
	ldr	w1, [x5, w0, sxtw 2]
	cmp	w3, w1
	beq	.L4079
.L4081:
	add	w0, w0, 1
	cmp	w0, w4
	mov	w2, w0
	bne	.L4082
.L4079:
	str	w2, [x23, 388]
.L4078:
	ldrb	w1, [x21, 2843]
	ldr	x0, [x19, 248]
	cmp	w1, 5
	ldr	w2, [x0, 2896]
	beq	.L4083
.L4220:
	ldrb	w0, [x19, 8]
	ldr	w1, [x21, 2868]
	cmp	w0, 2
	beq	.L4085
.L4221:
	ldr	x3, [x19, 224]
	ldr	w0, [x3, 24]
	cmp	w0, 2
	beq	.L4085
	add	x23, x19, 11120640
	ldr	w0, [x23, 388]
	add	x0, x0, 2777088
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 11052]
	cmp	w0, w1
	beq	.L4085
	add	w2, w2, 4
	mov	w4, 1
	lsl	w25, w4, w2
	add	w0, w0, w4
	udiv	w2, w0, w25
	msub	w0, w2, w25, w0
	cmp	w0, w1
	beq	.L4085
	str	w4, [x3, 648]
	ldr	x0, [x19, 224]
	ldr	w1, [x0, 648]
	cbnz	w1, .L4086
	ldr	x2, [x0, 688]
	mov	x1, 4294967296
	cmp	x2, x1
	beq	.L4213
.L4087:
	ldr	w0, [x23, 388]
	ldr	w1, [x21, 2868]
	add	x0, x19, x0, lsl 2
	add	x0, x0, 11116544
	ldr	w2, [x0, 2860]
	cmp	w1, w2
	sub	w3, w1, w2
	bls	.L4088
	ldr	w4, [x24, 3540]
	cmp	w4, w3
	ccmp	w2, wzr, 4, cc
	beq	.L4086
	ldrb	w2, [x21, 2840]
	cmp	w2, 2
	bne	.L4214
	cbnz	w1, .L4090
	sub	w1, w25, #1
.L4091:
	str	w1, [x0, 2860]
	mov	w1, -1
	mov	x0, x19
	bl	MVC_FlushDPB
	cbz	w0, .L4086
	ldr	x1, .LC992
	mov	w3, w0
	mov	w2, 7300
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4051
	.p2align 3
.L4210:
	ldr	x0, [x19, 224]
	ldr	w1, [x0, 764]
	cbnz	w1, .L4055
	ldr	w1, [x0, 28]
	cmp	w1, 25
	beq	.L4215
.L4055:
	ldr	w1, [x19, 84]
	add	w1, w1, 1
	str	w1, [x19, 84]
	cbnz	w23, .L4066
	ldr	w0, [x0, 928]
	cmp	w0, 1
	beq	.L4066
	mov	w1, -1
	mov	x0, x19
	bl	MVC_FlushDPB
	cbnz	w0, .L4216
	cbz	x19, .L4116
.L4224:
	mov	x0, x19
	bl	MVC_ClearAllSlice
	mov	x0, x19
	bl	MVC_InitDPB.part.16
	cbnz	w0, .L4069
	cbnz	w23, .L4071
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 928]
	cmp	w0, 1
	bne	.L4065
.L4071:
	ldr	w4, [x24, 3540]
	add	x2, x19, 11108352
	mov	w1, 2
	add	x3, x19, 48
	lsl	w4, w4, 1
	str	w4, [x19, 52]
	ldr	w0, [x24, 3520]
	ldrb	w23, [x2, 3684]
	add	w0, w0, 1
	ldr	w25, [x24, 3516]
	sub	w23, w1, w23
	lsl	w0, w0, 4
	add	w25, w25, 1
	mul	w23, w0, w23
	lsl	w25, w25, 4
	mov	x0, x19
	mov	w2, w23
	mov	w1, w25
	bl	MVC_ArrangeVahbMem
	cmp	w0, 1
	beq	.L4217
.L4201:
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 928]
	cmp	w0, 1
	beq	.L4218
	ldr	x1, .LC1000
	mov	w0, 0
	stp	wzr, wzr, [x19, 12]
	bl	dprint_vfmw
	mov	w1, 0
	mov	x0, x19
	bl	MVC_ClearAll
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L4206:
	mov	w1, 1
	strb	w1, [x19, 2]
	mov	w1, 3992
	ldr	x4, [x19, 272]
	ldr	w2, [x22, 28]
	add	x3, x19, 11112448
	str	w2, [x19, 24]
	ldr	w2, [x22, 28]
	ldr	w3, [x3, 312]
	umull	x1, w2, w1
	add	x1, x4, x1
	ldr	w2, [x1, 744]
	cmp	w3, w2
	beq	.L4219
.L4046:
	ldr	w0, [x19, 84]
	add	x24, x19, 11108352
	ldr	x3, .LC989
	add	x24, x24, 3664
	add	w0, w0, 1
	str	w0, [x19, 84]
	strb	wzr, [x1, 26]
	mov	x2, 3992
	mov	x0, x24
	ldr	x3, [x3, 112]
	blr	x3
	ldrsb	w0, [x21, 2852]
	str	x24, [x19, 248]
	b	.L4045
	.p2align 3
.L4075:
	ldr	x3, .LC989
	mov	x2, 2240
	strb	wzr, [x22, 20]
	mov	x1, x22
	add	x0, x24, 3560
	ldr	x3, [x3, 112]
	blr	x3
	ldrsb	w0, [x21, 2852]
	cmn	w0, #1
	bne	.L4077
.L4211:
	add	x23, x19, 11120640
	str	wzr, [x23, 388]
	ldrb	w1, [x21, 2843]
	ldr	x0, [x19, 248]
	cmp	w1, 5
	ldr	w2, [x0, 2896]
	bne	.L4220
.L4083:
	add	x23, x19, 11120640
	ldr	w1, [x21, 2868]
	ldr	w0, [x23, 388]
	add	x0, x0, 2777088
	add	x0, x19, x0, lsl 2
	str	w1, [x0, 11052]
	ldrb	w0, [x19, 8]
	cmp	w0, 2
	bne	.L4221
	.p2align 2
.L4085:
	ldrb	w0, [x21, 2848]
	cbz	w0, .L4099
	add	x23, x19, 11120640
	ldr	w0, [x23, 388]
	add	x0, x0, 2777088
	add	x0, x19, x0, lsl 2
	str	w1, [x0, 11052]
.L4099:
	mov	x0, x19
	str	w1, [x21, 1760]
	bl	MVC_DecPOC
	mov	w1, 0
	mov	x0, x19
	bl	MVC_AllocFrameStore
	cbnz	w0, .L4222
	strb	wzr, [x20, 2319]
	mov	w0, 1
	strb	w0, [x20, 2312]
	add	x4, x20, 2816
	mov	w6, 1
	ldrb	w0, [x21, 2843]
	strb	w0, [x20, 2318]
	ldr	w8, [x21, 2868]
	str	w8, [x20, 2976]
	ldrb	w7, [x21, 2848]
	str	w7, [x20, 2984]
	ldr	w3, [x21, 1740]
	str	w3, [x20, 2988]
	ldr	w2, [x21, 1736]
	str	w2, [x20, 2992]
	ldr	w1, [x21, 1728]
	str	w1, [x20, 2996]
	ldr	w0, [x21, 1732]
	strb	wzr, [x20, 2314]
	strb	wzr, [x20, 2317]
	strb	wzr, [x20, 2316]
	stp	w0, w3, [x4, 184]
	stp	w2, w1, [x4, 192]
	str	w0, [x20, 3016]
	mov	w0, -1
	str	w0, [x20, 3040]
	ldrb	w5, [x21, 2841]
	cbz	w5, .L4101
	strb	w6, [x21, 2841]
	mov	w5, w6
	mov	w6, 2
.L4101:
	ldr	x4, [x19, 248]
	mov	w3, 2
	ldrb	w2, [x4, 20]
	ldr	w0, [x4, 3952]
	sub	w1, w3, w2
	mov	w2, 0
	madd	w1, w0, w1, w1
	udiv	w0, w1, w6
	str	w0, [x20, 3028]
	ldrb	w1, [x4, 20]
	sub	w1, w3, w1
	ldr	w3, [x4, 3952]
	madd	w1, w3, w1, w1
	str	w1, [x20, 3032]
	ldr	w1, [x4, 3948]
	add	w1, w1, 1
	str	w1, [x20, 3024]
	mul	w0, w0, w1
	str	w0, [x20, 3036]
	ldrb	w0, [x24, 3560]
	strb	w0, [x20, 2320]
	cbnz	w5, .L4102
	ldrb	w0, [x4, 21]
	cmp	w0, wzr
	cset	w2, ne
.L4102:
	strb	w2, [x20, 2321]
	add	x23, x19, 11120640
	cbz	w7, .L4103
	ldr	w0, [x23, 388]
	add	x0, x0, 2777088
	add	x0, x19, x0, lsl 2
	str	w8, [x0, 11052]
.L4103:
	ldr	x0, [x20, 2960]
	cbz	x0, .L4104
	ldrsb	w1, [x21, 2852]
	strb	w1, [x0, 9]
.L4104:
	mov	w0, -1
	str	w0, [x20, 3048]
	ldrb	w0, [x21, 2851]
	cbz	w0, .L4105
	ldr	w0, [x23, 384]
	str	w0, [x20, 3048]
	ldrb	w0, [x21, 2849]
	strb	w0, [x20, 2322]
	ldrb	w0, [x21, 2850]
	strb	w0, [x20, 2323]
.L4105:
	ldr	w0, [x23, 388]
	mov	x22, -1
	str	w0, [x20, 3052]
	mov	w0, 29
	ldr	x1, .LC1014
	mov	w24, 2
	ldrb	w3, [x19, 3]
	lsl	x2, x3, 6
	sub	x2, x2, x3
	lsl	x2, x2, 2
	sub	x2, x2, x3
	lsl	x2, x2, 1
	sub	x2, x2, x3
	lsl	x2, x2, 2
	add	x2, x2, 11120640
	add	x2, x2, 448
	add	x2, x19, x2
	str	x2, [x20, 2968]
	ldr	x2, [x19, 224]
	ldr	x3, [x2, 56]
	str	x3, [x20, 2912]
	ldr	x3, [x2, 72]
	str	x3, [x20, 2920]
	ldr	x3, [x2, 88]
	str	x3, [x20, 2928]
	str	x22, [x2, 56]
	ldr	x2, [x20, 2912]
	bl	dprint_vfmw
	ldr	x1, .LC1016
	mov	w0, 29
	ldr	x2, [x20, 2920]
	bl	dprint_vfmw
	ldr	x4, [x19, 248]
	add	x5, x19, 11108352
	ldr	x1, .LC989
	mov	x2, 4
	ldr	w0, [x4, 3948]
	ldr	x6, [x1, 96]
	mov	w1, 0
	add	w0, w0, 1
	lsl	w0, w0, 4
	str	w0, [x20, 2396]
	add	x0, x20, 2392
	ldrb	w3, [x4, 20]
	ldr	w7, [x4, 3952]
	sub	w3, w24, w3
	madd	w3, w7, w3, w3
	lsl	w3, w3, 4
	str	w3, [x20, 2400]
	ldr	w3, [x4, 748]
	ldr	w25, [x5, 3716]
	cmp	w3, 1
	cset	w26, ne
	and	w25, w25, 7
	blr	x6
	ldrb	w0, [x20, 2392]
	mov	w1, w25
	and	w0, w0, 252
	bfi	w0, w26, 2, 3
	strb	w0, [x20, 2392]
	ldr	x3, [x19, 248]
	ldr	w2, [x3, 56]
	bfi	w0, w2, 5, 3
	ldrb	w2, [x20, 2393]
	strb	w0, [x20, 2392]
	bfi	w2, w24, 0, 2
	and	w0, w2, -13
	bfi	w0, w24, 4, 2
	strb	w0, [x20, 2393]
	add	x0, x20, 2328
	ldr	w3, [x3, 52]
	ldr	w2, [x20, 2392]
	bfi	w2, w3, 14, 3
	str	w2, [x20, 2392]
	bl	SetAspectRatio
	ldr	w0, [x19, 84]
	ldr	x1, [x20, 2960]
	str	w0, [x20, 2484]
	cbz	x1, .L4223
	ldr	x0, [x19, 248]
	ldr	w0, [x0, 3984]
	str	w0, [x1, 156]
	str	w0, [x20, 2412]
	ldr	x1, [x20, 2960]
	ldr	x0, [x19, 248]
	ldr	w0, [x0, 3988]
	str	w0, [x1, 160]
	str	w0, [x20, 2416]
	ldr	x1, [x20, 2960]
	ldr	x0, [x19, 248]
	ldr	w0, [x0, 3976]
	str	w0, [x1, 148]
	str	w0, [x20, 2404]
	ldr	x1, [x20, 2960]
	ldr	x0, [x19, 248]
	ldr	w0, [x0, 3980]
	str	w0, [x1, 152]
	str	w0, [x20, 2408]
	ldrb	w2, [x20, 2315]
	ldr	x0, [x20, 2960]
	cmp	w2, wzr
	ldr	w1, [x20, 2392]
	cset	w2, ne
	str	w2, [x20, 2380]
	str	w1, [x0, 136]
	ldr	x0, [x20, 2960]
	ldr	w1, [x20, 2380]
	str	w1, [x0, 124]
	ldr	w0, [x21, 2868]
	str	w0, [x20, 2504]
	ldr	x1, [x20, 2960]
	ldr	w2, [x23, 384]
	str	w2, [x20, 2512]
	str	w0, [x1, 248]
	ldr	x0, [x20, 2960]
	ldr	w1, [x23, 384]
	str	w1, [x0, 256]
	ldr	x1, [x20, 2960]
	ldr	w0, [x19, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_GetDispPhyFs
	cbz	x0, .L4107
	ldr	w3, [x20, 2380]
	mov	w1, 0
	ldr	w2, [x0, 4]
	cmp	w3, wzr
	ldr	w0, [x19, 120]
	cset	w3, ne
	bl	FSP_SetStoreType
.L4107:
	ldr	w1, [x19, 60]
	add	x4, x20, 2872
	add	x5, x20, 2904
.L4111:
	ldr	x0, [x4]
	cbnz	x0, .L4108
	cbz	w1, .L4108
	ldr	x0, [x19, 832]
	subs	w1, w1, #1
	str	x0, [x4]
	beq	.L4109
	add	x2, x19, 832
	mov	w0, 0
	.p2align 2
.L4110:
	add	w0, w0, 1
	cmp	w0, w1
	add	x3, x19, x0, uxtw 3
	ldr	x3, [x3, 832]
	str	x3, [x2], 8
	bne	.L4110
.L4109:
	add	x0, x19, x1, uxtw 3
	str	xzr, [x0, 832]
	str	w1, [x19, 60]
.L4108:
	add	x4, x4, 8
	cmp	x5, x4
	bne	.L4111
	cbz	w1, .L4113
	cmp	w1, wzr
	ble	.L4113
	.p2align 2
.L4114:
	add	x22, x19, x1, sxtw 3
	sub	w21, w1, #1
	ldr	w0, [x19, 120]
	ldr	x1, [x22, 824]
	bl	FreeUsdByDec
	str	xzr, [x22, 824]
	mov	w1, w21
	cbnz	w21, .L4114
.L4113:
	str	wzr, [x19, 60]
	mov	x0, x19
	strb	wzr, [x20, 2324]
	bl	MVC_UpdateReflist
	mov	x0, x19
	bl	MVC_UpdateLTReflist
	mov	x0, x19
	bl	MVC_CalcPicNum
	mov	w0, 0
.L4051:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L4213:
	ldr	w1, [x0, 696]
	cbnz	w1, .L4087
	ldr	w0, [x0, 652]
	add	w0, w0, 1024
	cmp	w0, 2048
	bls	.L4087
	.p2align 2
.L4086:
	add	x0, x19, 11108352
	ldrb	w0, [x0, 3683]
	cbnz	w0, .L4095
	ldr	x1, .LC1006
	mov	w0, 2
	bl	dprint_vfmw
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 652]
	tst	w0, -1025
	bne	.L4202
	ldr	w0, [x23, 384]
	cbnz	w0, .L4202
	ldr	w0, [x23, 388]
	ldr	w1, [x21, 2868]
	add	x0, x0, 2777088
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 11052]
	add	w0, w0, 1
	udiv	w2, w0, w25
	msub	w0, w2, w25, w0
	cmp	w1, w0
	bcs	.L4085
	ldrb	w0, [x21, 2840]
	cmp	w0, 2
	beq	.L4085
	mov	x0, x19
	mov	w22, -1
	bl	MVC_ClearAllSlice
	add	x5, x23, 256
	ldr	w0, [x19, 40]
	mov	w2, 2
	str	w0, [x23, 412]
	strb	w2, [x23, 401]
	mov	w0, 23352
	strb	wzr, [x23, 400]
	mov	w2, 32
	strb	w2, [x23, 402]
	movk	w0, 0x1, lsl 16
	stp	w22, wzr, [x5, 172]
	mov	w2, 262144
	mov	w1, w22
	stp	wzr, w2, [x5, 180]
	str	w0, [x23, 416]
	mov	w0, 7
	strb	w0, [x23, 403]
	mov	w0, 3
	str	w0, [x23, 424]
	mov	x0, x19
	bl	MVC_ClearDPB
	ldr	w4, [x23, 388]
	mov	w2, 7350
	ldr	x1, .LC1008
	mov	w0, 0
	add	x4, x4, 2777088
	ldr	w3, [x21, 2868]
	add	x19, x19, x4, lsl 2
	ldr	w4, [x19, 11052]
	add	w4, w4, 1
	udiv	w5, w4, w25
	msub	w4, w5, w25, w4
	bl	dprint_vfmw
	mov	w0, w22
	b	.L4051
	.p2align 3
.L4209:
	ldrb	w0, [x22, 20]
	cbz	w0, .L4053
	b	.L4052
	.p2align 3
.L4066:
	ldr	x1, .LC1002
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x19
	bl	MVC_GetBackPicFromVOQueue
	cbnz	x19, .L4224
.L4116:
	mov	w0, -1
.L4069:
	ldr	x1, .LC994
	mov	w3, w0
	mov	w2, 7189
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4051
	.p2align 3
.L4219:
	ldrb	w2, [x1, 26]
	cbnz	w2, .L4046
	add	x24, x19, 11108352
	add	x24, x24, 3664
	str	x24, [x19, 248]
	b	.L4045
	.p2align 3
.L4205:
	ldrsb	w1, [x0, 6]
	mov	w2, 1
	ldr	w0, [x19, 120]
	bl	FSP_ClearLogicFs
	ldr	x0, [x20, 2960]
	strb	wzr, [x0, 2]
	ldr	x0, [x20, 2960]
	strb	wzr, [x0, 5]
	b	.L4044
	.p2align 3
.L4218:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	mov	w0, -2
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L4095:
	mov	x0, x19
	bl	MVC_DecGap
	cbnz	w0, .L4098
.L4202:
	ldr	w1, [x21, 2868]
	b	.L4085
.L4215:
	ldr	w0, [x19, 84]
	add	w0, w0, 1
	str	w0, [x19, 84]
	cbnz	w23, .L4225
.L4056:
	cbz	x19, .L4115
	mov	x0, x19
	bl	MVC_ClearAllSlice
	mov	x0, x19
	bl	MVC_InitDPB.part.16
	mov	w3, w0
	cbnz	w0, .L4057
	add	x2, x19, 11108352
	ldr	w1, [x24, 3520]
	ldr	w26, [x24, 3516]
	add	w1, w1, 1
	ldrb	w25, [x2, 3684]
	mov	w2, 2
	lsl	w1, w1, 4
	add	w26, w26, 1
	sub	w25, w2, w25
	lsl	w26, w26, 4
	mul	w25, w1, w25
	cbz	w23, .L4059
	ldr	w1, [x19, 12]
	cbnz	w1, .L4059
	ldr	w4, [x24, 3540]
	ldr	x3, [x19, 224]
	lsl	w4, w4, 1
	str	w4, [x19, 52]
	ldr	w1, [x3, 724]
	cmp	w26, w1
	bhi	.L4060
	ldr	w2, [x3, 728]
	cmp	w25, w2
	bhi	.L4060
	add	x5, x19, 11124736
	ldr	w6, [x3, 748]
	ldr	w5, [x5, 792]
	cmp	w6, w5
	bcc	.L4226
	ldr	w0, [x3, 752]
	cbnz	w0, .L4063
	mov	w4, 1
	str	w4, [x19, 52]
	ldr	w1, [x3, 724]
	ldr	w2, [x3, 728]
.L4063:
	add	x3, x19, 48
	mov	x0, x19
	bl	MVC_ArrangeVahbMem
	cmp	w0, 1
	bne	.L4201
.L4059:
	lsr	w26, w26, 4
	lsr	w25, w25, 4
	stp	w26, w25, [x19, 12]
	b	.L4065
.L4207:
	strb	wzr, [x19, 2]
	ldr	x0, .LC989
	ldr	w1, [x22, 28]
	ldr	x3, [x0, 112]
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 4
	sub	x1, x0, x1
	add	x0, x19, 10768384
	lsl	x2, x1, 2
	add	x0, x0, 4060
	sub	x1, x2, x1
	lsl	x2, x1, 6
	add	x1, x1, x2
	mov	x2, 8500
	movk	x2, 0x5, lsl 16
	add	x1, x19, x1, lsl 2
	add	x1, x1, 12288
	add	x1, x1, 2396
	blr	x3
	add	x0, x19, 11046912
	add	x0, x0, 180
	str	x0, [x19, 248]
	ldr	w0, [x0, 744]
	str	w0, [x19, 28]
	b	.L4048
	.p2align 3
.L4217:
	lsr	w25, w25, 4
	lsr	w23, w23, 4
	stp	w25, w23, [x19, 12]
	b	.L4065
.L4088:
	ldr	w4, [x24, 3540]
	add	w3, w3, w25
	cmp	w4, w3
	ccmp	w2, wzr, 4, cc
	beq	.L4086
	ldrb	w2, [x21, 2840]
	cmp	w2, 2
	bne	.L4227
	cbnz	w1, .L4093
	sub	w1, w25, #1
.L4094:
	str	w1, [x0, 2860]
	mov	w1, -1
	mov	x0, x19
	bl	MVC_FlushDPB
	cbz	w0, .L4086
	ldr	x1, .LC992
	mov	w3, w0
	mov	w2, 7327
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4051
	.p2align 3
.L4115:
	mov	w3, -1
.L4057:
	ldr	x1, .LC994
	mov	w2, 7105
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4051
	.p2align 3
.L4225:
	mov	w1, -1
	mov	x0, x19
	bl	MVC_FlushDPB
	cbz	w0, .L4056
	ldr	x1, .LC992
	mov	w3, w0
	mov	w2, 7096
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4051
	.p2align 3
.L4216:
	ldr	x1, .LC992
	mov	w3, w0
	mov	w2, 7180
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4051
.L4098:
	ldr	x1, .LC1010
	mov	w2, 7374
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4051
	.p2align 3
.L4208:
	ldr	x1, .LC990
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4051
.L4212:
	mov	w2, 0
	b	.L4079
.L4222:
	ldr	x1, .LC1012
	mov	w2, 7394
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4051
.L4223:
	ldr	x1, .LC1018
	mov	w2, 7498
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, w22
	b	.L4051
.L4090:
	sub	w1, w1, #1
	b	.L4091
.L4093:
	sub	w1, w1, #1
	b	.L4094
.L4214:
	mov	x0, x19
	mov	w22, -1
	bl	MVC_ClearAllSlice
	add	x7, x23, 256
	ldr	w0, [x19, 40]
	mov	w2, 2
	str	w0, [x23, 412]
	strb	w2, [x23, 401]
	mov	w0, 23352
	strb	wzr, [x23, 400]
	mov	w2, 32
	strb	w2, [x23, 402]
	movk	w0, 0x1, lsl 16
	stp	w22, wzr, [x7, 172]
	mov	w2, 262144
	mov	w1, w22
	stp	wzr, w2, [x7, 180]
	str	w0, [x23, 416]
	mov	w0, 7
	strb	w0, [x23, 403]
	mov	w0, 3
	str	w0, [x23, 424]
	mov	x0, x19
	bl	MVC_ClearDPB
	ldr	w5, [x23, 388]
	mov	w2, 7289
	ldr	x1, .LC1004
	ldr	w6, [x21, 2868]
	add	x5, x5, 2777088
	ldr	w4, [x24, 3540]
.L4203:
	add	x19, x19, x5, lsl 2
	mov	w0, 0
	ldr	w3, [x19, 11052]
	sub	w3, w6, w3
	bl	dprint_vfmw
	mov	w0, w22
	b	.L4051
.L4227:
	mov	x0, x19
	mov	w22, -1
	bl	MVC_ClearAllSlice
	add	x6, x23, 256
	ldr	w0, [x19, 40]
	mov	w2, 2
	str	w0, [x23, 412]
	strb	w2, [x23, 401]
	mov	w0, 23352
	strb	wzr, [x23, 400]
	mov	w2, 32
	strb	w2, [x23, 402]
	movk	w0, 0x1, lsl 16
	stp	w22, wzr, [x6, 172]
	mov	w2, 262144
	mov	w1, w22
	stp	wzr, w2, [x6, 180]
	str	w0, [x23, 416]
	mov	w0, 7
	strb	w0, [x23, 403]
	mov	w0, 3
	str	w0, [x23, 424]
	mov	x0, x19
	bl	MVC_ClearDPB
	ldr	w5, [x23, 388]
	mov	w2, 7316
	ldr	x1, .LC1004
	ldr	w6, [x21, 2868]
	add	x5, x5, 2777088
	ldr	w4, [x24, 3540]
	b	.L4203
.L4060:
	ldr	x1, .LC996
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4051
.L4226:
	ldr	x1, .LC998
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4051
	.size	MVC_InitPic, .-MVC_InitPic
	.align	3
.LC989:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC990:
	.xword	.LC90
	.align	3
.LC992:
	.xword	.LC991
	.align	3
.LC994:
	.xword	.LC993
	.align	3
.LC996:
	.xword	.LC995
	.align	3
.LC998:
	.xword	.LC997
	.align	3
.LC1000:
	.xword	.LC999
	.align	3
.LC1002:
	.xword	.LC1001
	.align	3
.LC1004:
	.xword	.LC1003
	.align	3
.LC1006:
	.xword	.LC1005
	.align	3
.LC1008:
	.xword	.LC1007
	.align	3
.LC1010:
	.xword	.LC1009
	.align	3
.LC1012:
	.xword	.LC1011
	.align	3
.LC1014:
	.xword	.LC1013
	.align	3
.LC1016:
	.xword	.LC1015
	.align	3
.LC1018:
	.xword	.LC1017
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecSlice
	.type	MVC_DecSlice, %function
MVC_DecSlice:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 11116544
	bl	_mcount
	ldr	w2, [x20, 68]
	mov	w0, 22
	ldr	x1, .LC1019
	sub	w2, w2, #1
	bl	dprint_vfmw
	ldr	x1, [x20, 240]
	mov	x0, x20
	ldrb	w2, [x1, 2]
	strb	w2, [x19, 2843]
	ldrb	w1, [x1, 4]
	strb	w1, [x19, 2848]
	bl	MVC_ProcessSliceHeaderFirstPart
	cbnz	w0, .L4274
	mov	x0, x20
	bl	MVC_ProcessSliceHeaderSecondPart
	cbnz	w0, .L4274
	ldr	w2, [x20, 64]
	mov	w3, 0
	add	x21, x20, 11157504
	cbz	w2, .L4235
	sub	w9, w2, #1
	add	x21, x20, 11157504
	add	x9, x9, 1392640
	add	x4, x21, 3832
	add	x9, x9, 2528
	mov	x0, 0
	mov	w10, 0
	mov	w3, 0
	add	x9, x20, x9, lsl 3
	.p2align 2
.L4243:
	ldr	x1, [x4]
	ldr	x6, [x1, 8]
	cbz	x6, .L4255
	ldr	x5, [x1, 40]
	ldr	w7, [x1, 16]
	cbz	x5, .L4256
.L4279:
	ldr	w1, [x1, 48]
.L4238:
	cbz	x0, .L4239
	cmp	x6, x0
	mov	w8, w7
	bls	.L4240
	sub	x0, x6, x0
	sub	w0, w0, w10
	add	w8, w0, w7
.L4240:
	add	w3, w1, w3
	add	w3, w8, w3
.L4241:
	cbz	x5, .L4258
	mov	x0, x5
	mov	w10, w1
.L4242:
	add	x4, x4, 8
	cmp	x9, x4
	bne	.L4243
.L4235:
	str	w3, [x20, 104]
	ldr	w0, [x21, 3024]
	ldr	w4, [x21, 3028]
	mul	w4, w0, w4
	cmp	w4, 1620
	bgt	.L4275
	lsl	w1, w4, 2
	mov	w5, 32769
	sub	w1, w1, w4
	mov	w4, 16384
	lsl	w1, w1, 8
	asr	w0, w1, 1
	cmp	w1, w5
	csel	w4, w0, w4, gt
.L4245:
	ldr	w0, [x20, 32]
	cmp	w0, w2
	bls	.L4246
	cmp	w4, w3
	bcc	.L4246
	ldrb	w0, [x19, 2845]
	cbz	w0, .L4249
	ldr	x1, .LC1027
	mov	w0, 2
	bl	dprint_vfmw
	str	wzr, [x20, 100]
	ldr	w0, [x20, 88]
	add	w0, w0, 1
	str	w0, [x20, 88]
	ldrb	w0, [x21, 2315]
	cbnz	w0, .L4250
	ldr	w0, [x20, 92]
	add	w0, w0, 1
	str	w0, [x20, 92]
.L4251:
	mov	x0, x20
	bl	MVC_InitPic
	cmn	w0, #2
	beq	.L4232
	cbnz	w0, .L4276
	mov	x0, x20
	bl	MVC_WritePicMsg
.L4249:
	mov	x0, x20
	bl	MVC_PicTypeStatistic
	mov	x0, x20
	bl	MVC_DecList
	cbnz	w0, .L4277
	mov	x0, x20
	bl	MVC_IsRefListWrong
	cbnz	w0, .L4278
	mov	x0, x20
	bl	MVC_CalcStreamBits
	mov	x0, x20
	bl	MVC_WriteSliceMsg
	mov	x0, x20
	bl	MVC_ExitSlice
	ldr	w1, [x20, 100]
	mov	w2, 1
	mov	w0, 0
	strb	w2, [x20, 4]
	add	w1, w1, 1
	str	w1, [x20, 100]
.L4232:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L4258:
	mov	x0, x6
	mov	w10, w7
	b	.L4242
	.p2align 3
.L4239:
	add	w3, w7, w3
	add	w3, w3, w1
	b	.L4241
	.p2align 3
.L4255:
	ldr	x5, [x1, 40]
	mov	w7, 0
	cbnz	x5, .L4279
	.p2align 2
.L4256:
	mov	w1, 0
	b	.L4238
	.p2align 3
.L4275:
	lsl	w4, w4, 7
	b	.L4245
	.p2align 3
.L4250:
	ldr	w0, [x20, 96]
	add	w0, w0, 1
	str	w0, [x20, 96]
	b	.L4251
.L4274:
	ldr	x1, .LC1020
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC1021
	ldr	x4, [x0]
	cbz	x4, .L4272
	add	x2, x29, 64
	ldr	w0, [x20, 120]
	mov	w5, -1
	mov	w3, 4
	mov	w1, 100
	str	w5, [x2, -8]!
	blr	x4
.L4272:
	mov	x0, x20
	bl	MVC_ClearCurrSlice
	mov	w0, -1
	b	.L4232
.L4246:
	ldr	x1, .LC1023
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w1, [x20, 32]
	ldr	w2, [x20, 64]
	cmp	w2, w1
	bcc	.L4248
	ldr	x0, .LC1021
	ldr	x4, [x0]
	cbz	x4, .L4248
	ldr	w0, [x20, 120]
	mov	w3, 8
	stp	w2, w1, [x29, 56]
	add	x2, x29, 56
	mov	w1, 108
	blr	x4
.L4248:
	ldr	x1, .LC1025
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x20
	bl	MVC_ClearAllSlice
	add	x1, x20, 11120640
	mov	w4, 32
	ldr	w8, [x20, 40]
	mov	w7, 23352
	movk	w7, 0x1, lsl 16
	mov	w6, 2
	strb	w4, [x1, 402]
	add	x4, x1, 256
	strb	wzr, [x1, 400]
	mov	w5, 7
	strb	w6, [x1, 401]
	mov	w0, -1
	strb	w5, [x1, 403]
	mov	w3, 3
	str	w8, [x1, 412]
	mov	w2, 262144
	str	w7, [x1, 416]
	stp	w3, w0, [x4, 168]
	stp	wzr, wzr, [x4, 176]
	str	w2, [x1, 440]
	b	.L4232
.L4277:
	ldr	x1, .LC1031
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4232
.L4278:
	ldr	x1, .LC1033
	mov	w0, 1
	bl	dprint_vfmw
	b	.L4272
.L4276:
	ldr	x1, .LC1029
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4232
	.size	MVC_DecSlice, .-MVC_DecSlice
	.align	3
.LC1019:
	.xword	.LC877
	.align	3
.LC1020:
	.xword	.LC879
	.align	3
.LC1021:
	.xword	g_event_report
	.align	3
.LC1023:
	.xword	.LC1022
	.align	3
.LC1025:
	.xword	.LC1024
	.align	3
.LC1027:
	.xword	.LC1026
	.align	3
.LC1029:
	.xword	.LC1028
	.align	3
.LC1031:
	.xword	.LC1030
	.align	3
.LC1033:
	.xword	.LC1032
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecOneNal
	.type	MVC_DecOneNal, %function
MVC_DecOneNal:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	ldr	x3, [x19, 240]
	ldr	w0, [x3, 76]
	cbz	w0, .L4285
	ldr	w2, [x19, 104]
	mov	w0, 0
	.p2align 2
.L4284:
	ubfiz	x1, x0, 5, 32
	add	w0, w0, 1
	add	x1, x3, x1
	ldr	w1, [x1, 16]
	add	w2, w2, w1
	str	w2, [x19, 104]
	ldr	w1, [x3, 76]
	cmp	w1, w0
	bhi	.L4284
.L4285:
	add	x22, x19, 872
	strb	wzr, [x3]
	mov	w1, 32
	mov	x0, x22
	bl	BsGet
	mov	w20, w0
	and	w4, w0, 31
	ldr	x0, [x19, 240]
	ubfx	x3, x20, 5, 2
	ubfx	x1, x20, 7, 1
	mov	w2, -1
	strb	w4, [x0, 2]
	ldr	x0, [x19, 240]
	strb	w3, [x0, 4]
	ldr	x0, [x19, 240]
	str	w1, [x0, 84]
	ldr	x1, [x19, 240]
	ldr	w0, [x1, 72]
	add	w0, w0, 32
	str	w0, [x1, 72]
	strb	wzr, [x19, 10]
	ldr	x0, [x19, 240]
	strb	w2, [x0, 5]
	ldr	x0, [x19, 240]
	ldrb	w3, [x0, 2]
	cmp	w3, 14
	ccmp	w3, 20, 4, ne
	beq	.L4462
	ldr	x1, .LC1035
	mov	w0, 22
	ldr	w2, [x19, 68]
	bl	dprint_vfmw
	ldr	w0, [x19, 68]
	cmp	w0, 371
	beq	.L4463
.L4288:
	ldr	x1, [x19, 240]
	add	w0, w0, 1
	str	w0, [x19, 68]
	ldrb	w2, [x1, 2]
	sub	w0, w2, #1
	cmp	w0, 29
	bls	.L4464
.L4289:
	ldr	x1, .LC1077
	mov	w3, w20
	mov	w0, 22
	bl	dprint_vfmw
	cmp	w20, 256
	beq	.L4331
	ldr	x1, .LC1079
	mov	w0, 1
	bl	dprint_vfmw
.L4331:
	ldr	x1, [x19, 240]
	cbz	x1, .L4332
	ldr	w0, [x19, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19, 240]
.L4332:
	ldr	x0, .LC1043
	ldr	x4, [x0]
	cbz	x4, .L4447
.L4451:
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L4447:
	mov	w0, 0
.L4316:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L4464:
	ldr	x1, .LC1038
	ldrh	w0, [x1,w0,uxtw #1]
	adr	x1, .Lrtx4291
	add	x0, x1, w0, sxth #2
	br	x0
.Lrtx4291:
	.section	.rodata
	.align	0
	.align	2
.L4291:
	.2byte	(.L4290 - .Lrtx4291) / 4
	.2byte	(.L4289 - .Lrtx4291) / 4
	.2byte	(.L4289 - .Lrtx4291) / 4
	.2byte	(.L4289 - .Lrtx4291) / 4
	.2byte	(.L4290 - .Lrtx4291) / 4
	.2byte	(.L4292 - .Lrtx4291) / 4
	.2byte	(.L4293 - .Lrtx4291) / 4
	.2byte	(.L4294 - .Lrtx4291) / 4
	.2byte	(.L4295 - .Lrtx4291) / 4
	.2byte	(.L4296 - .Lrtx4291) / 4
	.2byte	(.L4297 - .Lrtx4291) / 4
	.2byte	(.L4298 - .Lrtx4291) / 4
	.2byte	(.L4299 - .Lrtx4291) / 4
	.2byte	(.L4300 - .Lrtx4291) / 4
	.2byte	(.L4301 - .Lrtx4291) / 4
	.2byte	(.L4289 - .Lrtx4291) / 4
	.2byte	(.L4289 - .Lrtx4291) / 4
	.2byte	(.L4289 - .Lrtx4291) / 4
	.2byte	(.L4302 - .Lrtx4291) / 4
	.2byte	(.L4289 - .Lrtx4291) / 4
	.2byte	(.L4289 - .Lrtx4291) / 4
	.2byte	(.L4289 - .Lrtx4291) / 4
	.2byte	(.L4289 - .Lrtx4291) / 4
	.2byte	(.L4289 - .Lrtx4291) / 4
	.2byte	(.L4289 - .Lrtx4291) / 4
	.2byte	(.L4289 - .Lrtx4291) / 4
	.2byte	(.L4289 - .Lrtx4291) / 4
	.2byte	(.L4289 - .Lrtx4291) / 4
	.2byte	(.L4289 - .Lrtx4291) / 4
	.2byte	(.L4303 - .Lrtx4291) / 4
	.text
	.p2align 3
.L4462:
	mov	w1, 24
	mov	x0, x22
	bl	BsGet
	mov	w20, w0
	ldr	x0, [x19, 240]
	ubfx	x1, x20, 23, 1
	strb	w1, [x0, 5]
	ldr	x1, [x19, 240]
	ldrsb	w0, [x1, 5]
	cbnz	w0, .L4286
	add	x0, x19, 12288
	ubfx	x4, x20, 16, 6
	ubfx	x2, x20, 6, 10
	mov	w5, 1
	ubfx	x3, x20, 22, 1
	strb	w4, [x0, 2386]
	ubfx	x4, x20, 3, 3
	strb	w5, [x0, 2384]
	strb	w3, [x0, 2385]
	str	w2, [x19, 14680]
	ubfx	x2, x20, 2, 1
	strb	w4, [x0, 2387]
	ubfx	x4, x20, 1, 1
	strb	w2, [x0, 2388]
	and	w2, w20, 1
	strb	w4, [x0, 2389]
	strb	w2, [x0, 2390]
	ldrb	w0, [x1, 2]
	cmp	w0, 20
	beq	.L4465
.L4286:
	ldr	w0, [x1, 72]
	add	w0, w0, 24
	str	w0, [x1, 72]
	ldr	x1, .LC1035
	ldr	x0, [x19, 240]
	ldr	w2, [x19, 68]
	ldrb	w3, [x0, 2]
	mov	w0, 22
	bl	dprint_vfmw
	ldr	w0, [x19, 68]
	cmp	w0, 371
	bne	.L4288
.L4463:
	ldr	x1, .LC1037
	mov	w0, 22
	bl	dprint_vfmw
	ldr	w0, [x19, 68]
	b	.L4288
.L4290:
	ldr	x1, .LC1040
	mov	w0, 22
	ldr	w3, [x19, 80]
	bl	dprint_vfmw
	ldr	x1, [x19, 240]
	add	x2, x19, 11116544
	add	x5, x19, 11120640
	add	x0, x19, 12288
	mov	w3, -1
	ldrb	w6, [x1, 2]
	strb	w6, [x2, 2843]
	ldrb	w4, [x1, 4]
	strb	w4, [x2, 2848]
	ldrsb	w1, [x1, 5]
	strb	w1, [x2, 2852]
	strb	wzr, [x2, 2851]
	str	w3, [x5, 384]
	ldrb	w3, [x0, 2384]
	cmp	w3, 1
	beq	.L4466
	cmn	w1, #1
	beq	.L4467
.L4305:
	ldr	x1, .LC1042
	mov	w0, 21
	ldr	w2, [x19, 88]
	bl	dprint_vfmw
	mov	x0, x19
	bl	MVC_SliceCheck
	cbnz	w0, .L4468
	mov	x0, x19
	bl	MVC_DecSlice
	cmn	w0, #2
	beq	.L4316
	cbz	w0, .L4447
	ldr	x0, .LC1043
	ldr	x4, [x0]
	cbnz	x4, .L4448
.L4446:
	mov	w0, -1
.L4472:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L4292:
	ldr	x1, .LC1053
	mov	w2, 6
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x19
	bl	MVC_DecSEI
	mov	w20, w0
	ldr	x1, [x19, 240]
	cbz	x1, .L4323
	ldr	w0, [x19, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19, 240]
.L4323:
	cbz	w20, .L4447
	ldr	x1, .LC1055
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC1043
	ldr	x4, [x0]
	cbnz	x4, .L4451
	b	.L4447
.L4293:
	ldr	x1, .LC1049
	mov	w2, 7
	ldr	w3, [x19, 72]
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x19
	bl	MVC_DecSPS
	mov	w20, w0
	ldr	x1, [x19, 240]
	cbz	x1, .L4321
	ldr	w0, [x19, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19, 240]
.L4321:
	cbnz	w20, .L4469
	ldr	w1, [x19, 72]
	mov	w0, 0
	add	w1, w1, 1
	str	w1, [x19, 72]
	b	.L4316
.L4294:
	ldr	x1, .LC1045
	mov	w2, 8
	ldr	w3, [x19, 76]
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x19
	bl	MVC_DecPPS
	mov	w20, w0
	ldr	x1, [x19, 240]
	cbz	x1, .L4319
	ldr	w0, [x19, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19, 240]
.L4319:
	cbnz	w20, .L4470
	ldr	w1, [x19, 76]
	mov	w0, 0
	add	w1, w1, 1
	str	w1, [x19, 76]
	b	.L4316
.L4295:
	ldr	x1, .LC1057
	mov	w2, 9
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x19, 240]
	cbz	x1, .L4447
.L4450:
	ldr	w0, [x19, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19, 240]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L4296:
	ldr	x1, .LC1059
	mov	w2, 10
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x19, 240]
	cbnz	x1, .L4450
	b	.L4447
.L4297:
	ldr	x1, .LC1063
	mov	w2, 11
	mov	w0, 22
	bl	dprint_vfmw
	mov	w1, 32
	mov	x0, x22
	bl	BsGet
	mov	w20, w0
	mov	w1, 32
	mov	x0, x22
	bl	BsGet
	mov	w2, 20553
	mov	w1, 20036
	movk	w2, 0x4853, lsl 16
	movk	w1, 0x4345, lsl 16
	cmp	w20, w2
	ccmp	w0, w1, 0, eq
	bne	.L4456
	ldr	x20, .LC1043
	mov	w0, 1
	strb	w0, [x19, 1]
	ldr	x4, [x20]
	cbz	x4, .L4326
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L4326:
	strb	wzr, [x19]
	mov	x0, x19
	bl	MVC_DecVDM
	cbz	w0, .L4456
	b	.L4458
.L4298:
	ldr	x1, .LC1061
	mov	w2, 12
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x19, 240]
	cbnz	x1, .L4450
	b	.L4447
.L4299:
	ldr	x1, .LC1065
	mov	w2, 13
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x19, 240]
	cbnz	x1, .L4450
	b	.L4447
.L4300:
	ldr	x1, .LC1067
	mov	w2, 14
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x19, 240]
	cbnz	x1, .L4450
	b	.L4447
.L4301:
	ldr	x1, .LC1069
	mov	w2, 15
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x19
	bl	MVC_DecSubSPS
	mov	w20, w0
	ldr	x1, [x19, 240]
	cbz	x1, .L4327
	ldr	w0, [x19, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19, 240]
.L4327:
	cbnz	w20, .L4471
	ldr	w1, [x19, 20]
	mov	w0, 0
	add	w1, w1, 1
	str	w1, [x19, 20]
	b	.L4316
.L4302:
	ldr	x1, .LC1072
	mov	w2, 19
	mov	w0, 22
	bl	dprint_vfmw
.L4456:
	ldr	x1, [x19, 240]
	cbnz	x1, .L4450
	b	.L4447
.L4303:
	ldr	x1, .LC1074
	mov	w2, 30
	mov	w0, 22
	bl	dprint_vfmw
	cbnz	w21, .L4329
	ldr	x1, [x19, 240]
	cbz	x1, .L4329
	ldr	w0, [x19, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19, 240]
.L4329:
	mov	w1, 32
	mov	x0, x22
	bl	BsGet
	mov	w20, w0
	mov	w1, 32
	mov	x0, x22
	rev	w20, w20
	bl	BsGet
	rev	w0, w0
	ldr	x1, .LC1075
	add	x1, x1, 432
	ldr	w2, [x1, 4]
	ldr	w1, [x1, 8]
	cmp	w2, w20
	ccmp	w1, w0, 0, eq
	bne	.L4447
	ldr	x20, .LC1043
	ldr	x4, [x20]
	cbz	x4, .L4330
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L4330:
	strb	wzr, [x19]
	mov	x0, x19
	bl	MVC_DecVDM
	cbz	w0, .L4447
.L4458:
	ldr	x4, [x20]
	cbz	x4, .L4446
.L4448:
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	mov	w0, -1
	b	.L4472
.L4465:
	mov	w0, 5
	cmp	w3, wzr
	csinc	w0, w0, wzr, eq
	strb	w0, [x1, 2]
	ldr	x1, [x19, 240]
	b	.L4286
.L4468:
	mov	x0, x19
	bl	MVC_ClearCurrSlice
	ldr	x0, .LC1043
	ldr	x4, [x0]
	cbnz	x4, .L4448
	mov	w0, -1
	b	.L4472
.L4471:
	ldr	x1, .LC1070
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC1043
	ldr	x4, [x0]
	cbz	x4, .L4446
	add	x2, x29, 64
	ldr	w0, [x19, 120]
	mov	w20, -1
	mov	w3, 4
	mov	w1, 100
	str	w20, [x2, -8]!
	blr	x4
	mov	w0, w20
	b	.L4316
.L4470:
	ldr	x1, .LC1047
.L4460:
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x21, .LC1043
	ldr	x4, [x21]
	cbz	x4, .L4446
	add	x2, x29, 64
	ldr	w0, [x19, 120]
	mov	w20, -1
	mov	w3, 4
	mov	w1, 100
	str	w20, [x2, -8]!
	blr	x4
	ldr	x4, [x21]
	cbz	x4, .L4446
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	mov	w0, w20
	b	.L4316
.L4469:
	ldr	x1, .LC1051
	b	.L4460
.L4467:
	ldr	w1, [x19, 20]
	cbz	w1, .L4305
	add	x1, x19, 10768384
	ldr	w3, [x1, 4064]
	cbz	w3, .L4308
	ldrb	w3, [x1, 4060]
	cmp	w3, 1
	beq	.L4309
.L4308:
	add	x0, x0, 2400
	mov	x1, 0
	.p2align 2
.L4312:
	ldr	w4, [x0]
	add	x3, x0, 335872
	cbz	w4, .L4310
	ldrb	w0, [x0, -4]
	cbnz	w0, .L4473
.L4310:
	add	w1, w1, 1
	add	x0, x3, 308
	cmp	w1, 32
	bne	.L4312
	mov	w0, -1
.L4445:
	cmn	w0, #1
	str	w0, [x5, 384]
	beq	.L4305
	cmp	w6, 5
	mov	w0, 1
	cset	w1, eq
	strb	w0, [x2, 2851]
	strb	w0, [x2, 2850]
	strb	w1, [x2, 2849]
	b	.L4305
.L4466:
	strb	w3, [x2, 2851]
	ldr	w1, [x19, 14680]
	str	w1, [x5, 384]
	ldrb	w1, [x0, 2388]
	strb	w1, [x2, 2849]
	ldrb	w1, [x0, 2389]
	strb	w1, [x2, 2850]
	strb	wzr, [x0, 2384]
	b	.L4305
.L4473:
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 4
	sub	x1, x0, x1
	lsl	x0, x1, 2
	sub	x1, x0, x1
	lsl	x0, x1, 6
	add	x0, x1, x0
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 14692]
	b	.L4445
.L4309:
	ldr	w0, [x1, 4068]
	b	.L4445
	.size	MVC_DecOneNal, .-MVC_DecOneNal
	.align	3
.LC1035:
	.xword	.LC1034
	.align	3
.LC1037:
	.xword	.LC1036
	.align	3
.LC1038:
	.xword	.L4291
	.align	3
.LC1040:
	.xword	.LC1039
	.align	3
.LC1042:
	.xword	.LC1041
	.align	3
.LC1043:
	.xword	g_event_report
	.align	3
.LC1045:
	.xword	.LC1044
	.align	3
.LC1047:
	.xword	.LC1046
	.align	3
.LC1049:
	.xword	.LC1048
	.align	3
.LC1051:
	.xword	.LC1050
	.align	3
.LC1053:
	.xword	.LC1052
	.align	3
.LC1055:
	.xword	.LC1054
	.align	3
.LC1057:
	.xword	.LC1056
	.align	3
.LC1059:
	.xword	.LC1058
	.align	3
.LC1061:
	.xword	.LC1060
	.align	3
.LC1063:
	.xword	.LC1062
	.align	3
.LC1065:
	.xword	.LC1064
	.align	3
.LC1067:
	.xword	.LC1066
	.align	3
.LC1069:
	.xword	.LC1068
	.align	3
.LC1070:
	.xword	.LC753
	.align	3
.LC1072:
	.xword	.LC1071
	.align	3
.LC1074:
	.xword	.LC1073
	.align	3
.LC1075:
	.xword	.LANCHOR1
	.align	3
.LC1077:
	.xword	.LC1076
	.align	3
.LC1079:
	.xword	.LC1078
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DEC_DecodePacket
	.type	MVC_DEC_DecodePacket, %function
MVC_DEC_DecodePacket:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	str	wzr, [x29, 68]
	stp	wzr, wzr, [x29, 60]
	cbz	x20, .L4536
	ldr	x0, [x19, 224]
	ldrb	w1, [x19, 5]
	ldr	w2, [x0, 8]
	cmp	w1, 1
	ubfiz	w2, w2, 16, 2
	str	w2, [x19, 108]
	ldr	w1, [x0]
	str	w1, [x19, 112]
	ldr	w1, [x0, 4]
	str	w1, [x19, 116]
	strb	wzr, [x19, 10]
	beq	.L4477
	ldr	w1, [x0, 880]
	add	x21, x19, 11161600
	cmp	w1, 1
	beq	.L4537
.L4478:
	mov	x1, x20
	mov	x0, x19
	bl	MVC_ReceivePacket
	ldr	x1, [x19, 240]
	str	x1, [x21, 2024]
.L4480:
	strb	wzr, [x19, 5]
	cbz	w0, .L4481
.L4500:
	mov	w0, 0
.L4529:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4481:
	ldr	x0, [x19, 240]
.L4479:
	str	wzr, [x0, 72]
	add	x21, x19, 872
	mov	x0, x21
	ldr	x1, [x19, 240]
	ldr	w2, [x1, 16]
	ldr	x1, [x1, 8]
	bl	BsInit
	mov	w1, 32
	mov	x0, x21
	bl	BsGet
	mov	w20, w0
	and	w3, w0, 31
	ldr	x0, [x19, 240]
	ubfx	x2, x20, 5, 2
	mov	w1, -1
	strb	w3, [x0, 2]
	ldr	x0, [x19, 240]
	strb	w2, [x0, 4]
	ldr	x0, [x19, 240]
	strb	w1, [x0, 5]
	ldr	x0, [x19, 240]
	ldrb	w0, [x0, 2]
	cmp	w0, 20
	beq	.L4538
.L4530:
	mov	w0, 27
	strb	wzr, [x19, 10]
	and	w20, w20, w0
	cmp	w20, 1
	beq	.L4486
.L4487:
	mov	x0, x19
	bl	MVC_FindTrailZeros
	cbnz	w0, .L4539
.L4499:
	ldr	x1, [x19, 240]
	mov	x0, x21
	str	wzr, [x1, 72]
	ldr	x1, [x19, 240]
	ldr	w2, [x1, 16]
	ldr	x1, [x1, 8]
	bl	BsInit
	mov	w1, 0
	mov	x0, x19
	bl	MVC_DecOneNal
	cmn	w0, #2
	beq	.L4529
	cbz	w0, .L4500
.L4534:
	ldr	x0, .LC1087
	ldr	x4, [x0]
	cbz	x4, .L4532
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L4532:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4537:
	ldr	w0, [x0, 928]
	cmp	w0, 1
	bne	.L4478
	ldr	w0, [x21, 2016]
	cmp	w0, 1
	bne	.L4478
	ldr	x0, [x21, 2024]
	str	x0, [x19, 240]
	str	wzr, [x21, 2016]
	strb	wzr, [x19, 5]
	b	.L4479
	.p2align 3
.L4477:
	ldr	x0, [x19, 240]
	cmp	x0, xzr
	csetm	w0, eq
	b	.L4480
	.p2align 3
.L4538:
	mov	w1, 24
	mov	x0, x21
	bl	BsGet
	ubfx	x2, x0, 23, 1
	ldr	x1, [x19, 240]
	strb	w2, [x1, 5]
	ldr	x2, [x19, 240]
	ldrsb	w1, [x2, 5]
	cbnz	w1, .L4530
	add	x1, x19, 12288
	ubfx	x4, x0, 22, 1
	mov	w6, 1
	ubfx	x3, x0, 6, 10
	ubfx	x5, x0, 2, 1
	cmp	w4, wzr
	strb	w6, [x1, 2384]
	ubfx	x0, x0, 1, 1
	strb	w4, [x1, 2385]
	str	w3, [x19, 14680]
	mov	w3, 5
	strb	w0, [x1, 2389]
	csinc	w0, w3, wzr, eq
	strb	w5, [x1, 2388]
	strb	w0, [x2, 2]
	strb	wzr, [x19, 10]
	.p2align 2
.L4486:
	add	x2, x29, 76
	add	x1, x29, 72
	mov	x0, x19
	bl	MVC_InquireSliceProperty
	cbnz	w0, .L4488
	ldr	w1, [x29, 72]
	ldr	w0, [x19, 128]
	cmp	w1, 1
	csinc	w0, w0, w0, ne
	str	w0, [x19, 128]
	beq	.L4540
.L4489:
	ldr	w0, [x29, 76]
	cmp	w0, 1
	bne	.L4487
	mov	w1, -1
	mov	x0, x19
	bl	MVC_FlushDPB
	cbnz	w0, .L4541
.L4496:
	ldr	w0, [x19, 120]
	bl	FSP_GetFspType
	cbnz	w0, .L4487
	ldr	w0, [x19, 120]
	add	x2, x29, 64
	add	x3, x29, 68
	add	x1, x29, 60
	bl	VCTRL_GetChanImgNum
	ldr	x0, [x19, 224]
	ldr	w2, [x0, 764]
	cmp	w2, 1
	bne	.L4487
	ldr	w0, [x29, 68]
	cmp	w0, wzr
	ble	.L4542
.L4493:
	mov	w1, 1
	mov	w0, -2
	strb	w1, [x19, 5]
	b	.L4529
	.p2align 3
.L4488:
	ldr	x1, [x19, 240]
	cbz	x1, .L4534
	ldr	w0, [x19, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19, 240]
	b	.L4534
	.p2align 3
.L4539:
	ldr	x1, .LC1089
	mov	w0, 22
	bl	dprint_vfmw
	b	.L4499
	.p2align 3
.L4540:
	add	x20, x19, 11116544
	ldrb	w0, [x20, 2841]
	cmp	w0, 1
	ldr	w0, [x19, 132]
	beq	.L4543
	add	w0, w0, 2
	str	w0, [x19, 132]
.L4491:
	ldr	w0, [x19, 64]
	cbz	w0, .L4489
	ldr	x3, [x19, 240]
	mov	w2, 12
	ldr	x1, .LC1083
	mov	x0, x21
	add	x1, x1, 432
	str	wzr, [x3, 72]
	bl	BsInit
	mov	w1, 1
	mov	x0, x19
	bl	MVC_DecOneNal
	ldrb	w0, [x20, 2841]
	cmp	w0, 1
	ldr	w0, [x19, 132]
	beq	.L4544
	sub	w0, w0, #2
	str	w0, [x19, 132]
	b	.L4493
.L4543:
	add	w0, w0, 1
	str	w0, [x19, 132]
	b	.L4491
.L4541:
	ldr	x1, .LC1084
	mov	w3, 0
	mov	w2, 14061
	mov	w0, 22
	bl	dprint_vfmw
	b	.L4496
.L4536:
	ldr	x2, .LC1081
	mov	w3, 13945
	ldr	x1, .LC1082
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4529
.L4544:
	sub	w0, w0, #1
	str	w0, [x19, 132]
	b	.L4493
.L4542:
	ldr	w0, [x29, 64]
	cmp	w0, 32
	bgt	.L4493
	ldr	x0, [x19, 232]
	cbnz	x0, .L4493
	ldr	w3, [x19, 88]
	cbz	w3, .L4487
	ldr	w6, [x19, 12]
	cbz	w6, .L4487
	add	x20, x19, 11161600
	ldr	w7, [x19, 16]
	ldr	w5, [x20, 2032]
	cmp	w7, w5
	beq	.L4487
	ldr	w4, [x20, 2036]
	cmp	w6, w4
	beq	.L4487
	ldr	x1, .LC1086
	mov	w0, w2
	bl	dprint_vfmw
	ldr	w0, [x19, 16]
	ldr	x1, .LC1087
	str	w0, [x20, 2032]
	ldr	x4, [x1]
	ldr	w0, [x19, 12]
	str	w0, [x20, 2036]
	cbz	x4, .L4487
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 120
	blr	x4
	b	.L4487
	.size	MVC_DEC_DecodePacket, .-MVC_DEC_DecodePacket
	.align	3
.LC1081:
	.xword	.LC36
	.align	3
.LC1082:
	.xword	.LC38
	.align	3
.LC1083:
	.xword	.LANCHOR1
	.align	3
.LC1084:
	.xword	.LC991
	.align	3
.LC1086:
	.xword	.LC1085
	.align	3
.LC1087:
	.xword	g_event_report
	.align	3
.LC1089:
	.xword	.LC1088
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DEC_VDMPostProc
	.type	MVC_DEC_VDMPostProc, %function
MVC_DEC_VDMPostProc:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 11157504
	mov	w21, w1
	bl	_mcount
	ldr	x2, [x19, 232]
	ldr	x0, [x20, 2960]
	ldrb	w1, [x2, 17]
	strb	w1, [x0, 14]
	ldrb	w1, [x2, 4]
	strb	w1, [x0, 15]
	ldrb	w0, [x19]
	str	w21, [x20, 3020]
	cbnz	w0, .L4546
	mov	x0, x19
	bl	MVC_ClearAllSlice
	mov	x0, x19
	bl	MVC_StorePicInDpb
	mov	w22, w0
	cbnz	w0, .L4557
	mov	w1, 1
	strb	w1, [x19, 4]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4546:
	mov	x0, x19
	bl	MVC_ClearAllSlice
	mov	x0, x19
	bl	MVC_StorePicInDpb
	cbnz	w0, .L4558
	mov	w1, -1
	mov	x0, x19
	bl	MVC_FlushDPB
	cbnz	w0, .L4559
.L4550:
	add	x0, x19, 11120640
	strb	wzr, [x19, 4]
	mov	w4, 32
	ldr	w8, [x19, 40]
	mov	w7, 23352
	mov	w6, 2
	strb	w4, [x0, 402]
	add	x4, x0, 256
	strb	wzr, [x0, 400]
	movk	w7, 0x1, lsl 16
	strb	w6, [x0, 401]
	mov	w5, 7
	str	w8, [x0, 412]
	mov	w3, 3
	strb	w5, [x0, 403]
	mov	w2, -1
	str	w7, [x0, 416]
	mov	w1, 262144
	stp	w3, w2, [x4, 168]
	stp	wzr, wzr, [x4, 176]
	str	w1, [x0, 440]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4557:
	ldr	x1, [x20, 2960]
	mov	w2, 1
	ldr	w0, [x19, 120]
	mov	w21, -1
	ldrsb	w1, [x1, 6]
	bl	FSP_ClearLogicFs
	ldr	x1, .LC1091
	mov	w2, w22
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	MVC_ClearAllSlice
	add	x0, x19, 11120640
	ldr	w4, [x19, 40]
	add	x5, x0, 256
	mov	w2, 2
	mov	w3, 23352
	mov	w1, 7
	strb	w2, [x0, 401]
	movk	w3, 0x1, lsl 16
	strb	w1, [x0, 403]
	mov	w2, 32
	str	w4, [x0, 412]
	mov	w1, 3
	strb	w2, [x0, 402]
	mov	w2, 262144
	str	w3, [x0, 416]
	strb	wzr, [x0, 400]
	stp	w1, w21, [x5, 168]
	stp	wzr, wzr, [x5, 176]
	str	w2, [x0, 440]
	mov	w1, w21
	mov	x0, x19
	bl	MVC_ClearDPB
	str	xzr, [x20, 2960]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4559:
	ldr	x1, .LC1095
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	b	.L4550
	.p2align 3
.L4558:
	ldr	x1, .LC1093
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, -1
	mov	x0, x19
	bl	MVC_FlushDPB
	cbz	w0, .L4550
	b	.L4559
	.size	MVC_DEC_VDMPostProc, .-MVC_DEC_VDMPostProc
	.align	3
.LC1091:
	.xword	.LC1090
	.align	3
.LC1093:
	.xword	.LC1092
	.align	3
.LC1095:
	.xword	.LC1094
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DEC_GetImageBuffer
	.type	MVC_DEC_GetImageBuffer, %function
MVC_DEC_GetImageBuffer:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x20, 48]
	cbz	w0, .L4577
	mov	x1, 51160
	sub	w0, w0, #1
	mov	w4, 848
	movk	x1, 0xa9, lsl 16
	add	x21, x20, 11124736
	umaddl	x4, w0, w4, x1
	add	x2, x21, 1160
	add	x4, x20, x4
	.p2align 2
.L4568:
	ldrb	w0, [x2, 2]
	cbnz	w0, .L4563
	cbz	x2, .L4564
	ldr	w0, [x21, 792]
	cbz	w0, .L4564
	ldr	x1, [x21, 408]
	cmp	x1, x2
	ccmp	x1, xzr, 4, eq
	bne	.L4563
	sub	w3, w0, #1
	add	x0, x21, 416
	add	x3, x3, 1388544
	add	x3, x3, 2100
	add	x3, x20, x3, lsl 3
	b	.L4565
	.p2align 3
.L4566:
	ldr	x1, [x0], 8
	cmp	x1, xzr
	ccmp	x1, x2, 0, ne
	beq	.L4563
.L4565:
	cmp	x0, x3
	bne	.L4566
.L4564:
	ldr	w0, [x20, 120]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	beq	.L4577
	ldr	w0, [x20, 120]
	bl	FSP_IsNewFsAvalible
	cmn	w0, #1
	beq	.L4598
.L4596:
	mov	w0, 0
.L4599:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L4563:
	add	x2, x2, 848
	cmp	x2, x4
	bne	.L4568
	add	x2, x29, 60
	add	x1, x29, 56
	add	x0, x20, 912
	bl	GetQueueImgNum
	ldr	x1, .LC1097
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x1, .LC1099
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x20, 48]
	cbz	w0, .L4576
	ldr	x19, .LC1103
	mov	w22, 0
	.p2align 2
.L4575:
	uxtw	x1, w22
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 1
	sub	x0, x0, x1
	lsl	x0, x0, 4
	add	x1, x20, x0
	add	x0, x0, 11124736
	add	x1, x1, 11124736
	add	x0, x20, x0
	adds	x0, x0, 1160
	ldrb	w3, [x1, 1162]
	ldrb	w4, [x1, 1165]
	beq	.L4580
	ldr	w1, [x21, 792]
	cbz	w1, .L4580
	ldr	x2, [x21, 408]
	cmp	x0, x2
	ccmp	x2, xzr, 4, eq
	bne	.L4582
	sub	w5, w1, #1
	add	x1, x21, 416
	add	x5, x5, 1388544
	add	x5, x5, 2100
	add	x5, x20, x5, lsl 3
	b	.L4573
	.p2align 3
.L4574:
	ldr	x2, [x1], 8
	cmp	x0, x2
	ccmp	x2, xzr, 4, eq
	bne	.L4582
.L4573:
	cmp	x5, x1
	bne	.L4574
.L4580:
	mov	w5, 1
.L4572:
	mov	w2, w22
	mov	x1, x19
	mov	w0, 0
	add	w22, w22, 1
	bl	dprint_vfmw
	ldr	w0, [x20, 48]
	cmp	w0, w22
	bhi	.L4575
.L4576:
	ldp	w2, w3, [x29, 56]
	ldr	x1, .LC1101
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x20, 48]
	ldr	w2, [x21, 796]
	ldp	w3, w1, [x29, 56]
	sub	w0, w0, #2
	sub	w0, w0, w2
	add	w1, w3, w1
	cmp	w1, w0
	bge	.L4596
	ldr	x1, .LC1105
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x20
	bl	MVC_ClearAll
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L4577:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, 1
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L4582:
	mov	w5, 0
	b	.L4572
.L4598:
	ldr	w0, [x20, 120]
	add	x1, x20, 912
	bl	FSP_ClearNotInVoQueue
	mov	w0, 0
	b	.L4599
	.size	MVC_DEC_GetImageBuffer, .-MVC_DEC_GetImageBuffer
	.align	3
.LC1097:
	.xword	.LC1096
	.align	3
.LC1099:
	.xword	.LC1098
	.align	3
.LC1101:
	.xword	.LC1100
	.align	3
.LC1103:
	.xword	.LC1102
	.align	3
.LC1105:
	.xword	.LC1104
	.global	MvcTmpBuf
	.global	MVC_quant8_org
	.global	MVC_quant_org
	.global	MVC_quant8_inter_default
	.global	MVC_quant8_intra_default
	.global	MVC_quant_inter_default
	.global	MVC_quant_intra_default
	.global	MVC_g_ZZ_SCAN8
	.global	MVC_g_ZZ_SCAN
	.global	MVC_CalcZeroNum
	.global	MVC_g_AspecRatioIdc
	.global	MVC_g_NalTypeEOPIC
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	MVC_g_ZZ_SCAN, %object
	.size	MVC_g_ZZ_SCAN, 16
MVC_g_ZZ_SCAN:
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
	.type	MVC_g_ZZ_SCAN8, %object
	.size	MVC_g_ZZ_SCAN8, 64
MVC_g_ZZ_SCAN8:
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
	.type	__FUNCTION__.13072, %object
	.size	__FUNCTION__.13072, 18
__FUNCTION__.13072:
	.string	"MVC_WriteSliceMsg"
	.zero	6
	.type	MVC_SarTable.13365, %object
	.size	MVC_SarTable.13365, 136
MVC_SarTable.13365:
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
	.type	__func__.13599, %object
	.size	__func__.13599, 11
__func__.13599:
	.string	"MVC_DecSEI"
	.zero	5
	.type	__func__.12252, %object
	.size	__func__.12252, 17
__func__.12252:
	.string	"MVC_DirectOutput"
	.zero	7
	.type	__func__.12832, %object
	.size	__func__.12832, 12
__func__.12832:
	.string	"MVC_InitDPB"
	.zero	4
	.type	__FUNCTION__.11972, %object
	.size	__FUNCTION__.11972, 13
__FUNCTION__.11972:
	.string	"MVC_ClearDPB"
	.zero	3
	.type	__func__.13710, %object
	.size	__func__.13710, 17
__func__.13710:
	.string	"MVC_FlushDecoder"
	.zero	7
	.type	__FUNCTION__.11980, %object
	.size	__FUNCTION__.11980, 13
__FUNCTION__.11980:
	.string	"MVC_ClearAll"
	.zero	3
	.type	__FUNCTION__.13837, %object
	.size	__FUNCTION__.13837, 13
__FUNCTION__.13837:
	.string	"MVC_DEC_Init"
	.zero	3
	.type	__func__.12402, %object
	.size	__func__.12402, 18
__func__.12402:
	.string	"MVC_StorePicInDpb"
	.data
	.align	3
.LANCHOR1 = . + 0
	.type	MVC_quant_intra_default, %object
	.size	MVC_quant_intra_default, 16
MVC_quant_intra_default:
	.word	471076102
	.word	538711053
	.word	622861332
	.word	707076124
	.type	MVC_quant_inter_default, %object
	.size	MVC_quant_inter_default, 16
MVC_quant_inter_default:
	.word	403967498
	.word	454562830
	.word	505092116
	.word	572398360
	.type	MVC_quant8_intra_default, %object
	.size	MVC_quant8_intra_default, 64
MVC_quant8_intra_default:
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
	.type	MVC_quant8_inter_default, %object
	.size	MVC_quant8_inter_default, 256
MVC_quant8_inter_default:
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
	.type	MVC_quant_org, %object
	.size	MVC_quant_org, 16
MVC_quant_org:
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.type	MVC_quant8_org, %object
	.size	MVC_quant8_org, 64
MVC_quant8_org:
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
	.type	MVC_g_NalTypeEOPIC, %object
	.size	MVC_g_NalTypeEOPIC, 12
MVC_g_NalTypeEOPIC:
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
	.type	MVC_CalcZeroNum, %object
	.size	MVC_CalcZeroNum, 256
MVC_CalcZeroNum:
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
	.type	MVC_g_AspecRatioIdc, %object
	.size	MVC_g_AspecRatioIdc, 112
MVC_g_AspecRatioIdc:
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
.LC0:
	ASCII(.string	"\n\nEND of the bit buffer, copy the first packet!\n\n" )
	.zero	6
.LC2:
	ASCII(.string	"0:phy:0x%x, 1:phy:0x%x; len0:%d len1:%d\n" )
	.zero	7
.LC5:
	ASCII(.string	"0:phy:0x%x, len0:%d\n" )
	.zero	3
.LC7:
	ASCII(.string	"%-50s%50d\n" )
	.zero	5
.LC14:
	ASCII(.string	"MVC_FRAME %d, state=%d, is already output\n" )
	.zero	5
.LC16:
	ASCII(.string	"plfs(fs=%p, eFoState=%d) is null, logic_fs_id = %d\n" )
	.zero	4
.LC18:
	ASCII(.string	"not used MVC_FRAME: (%d,%d)\n" )
	.zero	3
.LC20:
	ASCII(.string	"MVC_FRAME skip: is_used=%d,skip=%d\n" )
	.zero	4
.LC22:
	ASCII(.string	"topfield skip\n" )
	.zero	1
.LC24:
	ASCII(.string	"bottom field skip\n" )
	.zero	5
.LC26:
	ASCII(.string	"err(%d) > out_thr(%d)\n" )
	.zero	1
.LC28:
	ASCII(.string	"exg_pts: %lld <-> %lld\n" )
.LC31:
	ASCII(.string	"stream MVC_FRAME packing type is %d! what can we do?\n" )
	.zero	2
.LC36:
	ASCII(.string	"../../core/syntax/mvc.c" )
.LC38:
	ASCII(.string	"NULL pointer: %s, L%d\n" )
	.zero	1
.LC40:
	ASCII(.string	"framestore %d allocate apc %d\n" )
	.zero	1
.LC42:
	ASCII(.string	"find APC, but logic_fs_id %d abnormal(ref=%d,plfs=%p, pdfs=%p)\n" )
.LC45:
	ASCII(.string	"\n" )
	.zero	6
.LC47:
	ASCII(.string	"pMvcCtx->DPB.fs[%d]: frame_num=%d poc=%d is_reference=%d\n" )
	.zero	6
.LC49:
	ASCII(.string	"pMvcCtx->DPB.fs_ref[%d]: frame_num=%d poc=%d is_reference=%d\n" )
	.zero	2
.LC51:
	ASCII(.string	"pMvcCtx->DPB.fs_ref[%d]: MVC_FRAME.poc=%d \n" )
	.zero	4
.LC57:
	ASCII(.string	"\n VFMW ** release streambuff=%p   bitstream_length=%d\n" )
	.zero	1
.LC59:
	ASCII(.string	"clear curr slice.\n" )
	.zero	5
.LC62:
	ASCII(.string	"image size abnormal(%dx%d)\n" )
	.zero	4
.LC64:
	ASCII(.string	"partition fs memory fail!\n" )
	.zero	5
.LC66:
	ASCII(.string	"ERROR: FSP_ConfigInstance fail!\n" )
	.zero	7
.LC75:
	ASCII(.string	"for P slice size of list equal 0(1st).\n" )
.LC81:
	ASCII(.string	"for P slice size of list equal 0(2nd).\n" )
.LC83:
	ASCII(.string	"for B slice size of two list all equal 0.\n" )
	.zero	5
.LC86:
	ASCII(.string	"list[%d][%d]: frame_num=%d, poc=%d\n" )
	.zero	4
.LC88:
	ASCII(.string	"init list error.\n" )
	.zero	6
.LC90:
	ASCII(.string	"In one access unit,all non-base view should have the same subsps!\n" )
	.zero	5
.LC92:
	ASCII(.string	"sps but mvc flag %d is wrong\n" )
	.zero	2
.LC104:
	ASCII(.string	"save pic yuv :  structure = %d;  idc = %d\n" )
	.zero	5
.LC106:
	ASCII(.string	"structure = %d pMvcCtx->CurrPic.pic_width_in_mb = %d pMvcCtx->CurrPic.pic_height_in_mb = %d\n" )
	.zero	3
.LC108:
	ASCII(.string	"nal_ref_idc=%d, structure=%d, image_id=%d, pmv_idc=%d\n" )
	.zero	1
.LC110:
	ASCII(.string	"logic MVC_FRAME id(=%d): get LogicFs error!\n" )
	.zero	3
.LC112:
	ASCII(.string	"phy fs is null: pstDecodeFs = %p, pstDispOutFs = %p\n" )
	.zero	3
.LC118:
	ASCII(.string	"fuction return value is null,%s %d unknow error!!\n" )
	.zero	5
.LC120:
	ASCII(.string	"SH: first_mb_in_slice" )
	.zero	2
.LC122:
	ASCII(.string	"MVC_SliceCheck first_mb_in_slice >= MAX_MB_NUM_IN_PIC error.\n" )
	.zero	2
.LC124:
	ASCII(.string	"SH: slice_type" )
	.zero	1
.LC126:
	ASCII(.string	"slice type = %d\n" )
	.zero	7
.LC129:
	ASCII(.string	"slice type = %d, err\n" )
	.zero	2
.LC131:
	ASCII(.string	"slice  pps id = %d\n" )
	.zero	4
.LC133:
	ASCII(.string	"pps with this pic_parameter_set_id = %d havn't decode\n" )
	.zero	1
.LC135:
	ASCII(.string	"sps with this pic_parameter_set_id havn't decode\n" )
	.zero	6
.LC137:
	ASCII(.string	"subsps with this seq_parameter_set_id = %d havn't decoded\n" )
	.zero	5
.LC140:
	ASCII(.string	"tmp slice  pps id = %d\n" )
.LC142:
	ASCII(.string	"MVC_PPSSPSCheckTmpId: pps with this pic_parameter_set_id = %d havn't decode\n" )
	.zero	3
.LC144:
	ASCII(.string	"MVC_PPSSPSCheckTmpId: seq_parameter_set_id out of range.\n" )
	.zero	6
.LC146:
	ASCII(.string	"MVC_PPSSPSCheckTmpId: sps with this pic_parameter_set_id = %d havn't decode\n" )
	.zero	3
.LC148:
	ASCII(.string	"new pic flag = %d\n" )
	.zero	5
.LC150:
	ASCII(.string	"SH: ref_pic_list_reordering_flag_l0" )
	.zero	4
.LC152:
	ASCII(.string	"SH: reordering_of_pic_nums_idc_l0" )
	.zero	6
.LC154:
	ASCII(.string	"reorder idc l0 = %d, g_SeErrFlag=%d\n" )
	.zero	3
.LC156:
	ASCII(.string	"SH: abs_diff_pic_num_minus1_l0" )
	.zero	1
.LC158:
	ASCII(.string	"abs_diff_pic_num_minus1_l0 = %d, g_SeErrFlag=%d\n" )
	.zero	7
.LC160:
	ASCII(.string	"SH: long_term_pic_idx_l0" )
	.zero	7
.LC162:
	ASCII(.string	"SH: abs_diff_view_idx_minus1_l0" )
.LC164:
	ASCII(.string	"num of idc l0 exceed\n" )
	.zero	2
.LC166:
	ASCII(.string	"SH: ref_pic_list_reordering_flag_l1" )
	.zero	4
.LC168:
	ASCII(.string	"SH: reordering_of_pic_nums_idc_l1" )
	.zero	6
.LC170:
	ASCII(.string	"reorder idc l1 = %d, g_SeErrFlag=%d\n" )
	.zero	3
.LC172:
	ASCII(.string	"SH: abs_diff_pic_num_minus1_l1" )
	.zero	1
.LC174:
	ASCII(.string	"abs_diff_pic_num_minus1_l1 = %d, g_SeErrFlag=%d\n" )
	.zero	7
.LC176:
	ASCII(.string	"SH: long_term_pic_idx_l1" )
	.zero	7
.LC178:
	ASCII(.string	"SH: abs_diff_view_idx_minus1_l1" )
.LC180:
	ASCII(.string	"num of idc l1 exceed\n" )
	.zero	2
.LC182:
	ASCII(.string	"SH: luma_log2_weight_denom" )
	.zero	5
.LC184:
	ASCII(.string	"SH: chroma_log2_weight_denom" )
	.zero	3
.LC186:
	ASCII(.string	"WP log2 exceed  and err flag = %d\n" )
	.zero	5
.LC188:
	ASCII(.string	"SH: luma_weight_flag_l0" )
.LC190:
	ASCII(.string	"SH: luma_weight_l0" )
	.zero	5
.LC192:
	ASCII(.string	"SH: luma_offset_l0" )
	.zero	5
.LC194:
	ASCII(.string	"SH: chroma_weight_flag_l0" )
	.zero	6
.LC196:
	ASCII(.string	"SH: chroma_weight_l0" )
	.zero	3
.LC198:
	ASCII(.string	"SH: chroma_offset_l0" )
	.zero	3
.LC200:
	ASCII(.string	"SH: luma_weight_flag_l1" )
.LC202:
	ASCII(.string	"SH: luma_weight_l1" )
	.zero	5
.LC204:
	ASCII(.string	"SH: luma_offset_l1" )
	.zero	5
.LC206:
	ASCII(.string	"SH: chroma_weight_flag_l1" )
	.zero	6
.LC208:
	ASCII(.string	"SH: chroma_weight_l1" )
	.zero	3
.LC210:
	ASCII(.string	"SH: chroma_offset_l1" )
	.zero	3
.LC212:
	ASCII(.string	"overflow MVC_MAX_MMCO_LEN\n" )
	.zero	5
.LC214:
	ASCII(.string	"SH: memory_management_control_operation" )
.LC216:
	ASCII(.string	"SH: difference_of_pic_nums_minus1" )
	.zero	6
.LC218:
	ASCII(.string	"SH: long_term_pic_num" )
	.zero	2
.LC220:
	ASCII(.string	"SH: long_term_frame_idx" )
.LC222:
	ASCII(.string	"SH: max_long_term_frame_idx_plus1" )
	.zero	6
.LC224:
	ASCII(.string	"mmco exceed 6\n" )
	.zero	1
.LC226:
	ASCII(.string	"SH: no_output_of_prior_pics_flag" )
	.zero	7
.LC228:
	ASCII(.string	"SH: long_term_reference_flag" )
	.zero	3
.LC230:
	ASCII(.string	"IDR and no_output_of_prior_pics_flag = %d\n" )
	.zero	5
.LC232:
	ASCII(.string	"SH: adaptive_ref_pic_marking_mode_flag" )
	.zero	1
.LC234:
	ASCII(.string	"adaptive_ref_pic_marking_mode_flag = %d\n" )
	.zero	7
.LC236:
	ASCII(.string	"MMCO para would save dec err\n" )
	.zero	2
.LC238:
	ASCII(.string	"mulitislice diff no_out_of_prior_pics_flag, used first.\n" )
	.zero	7
.LC240:
	ASCII(.string	"mulitislice diff long_term_reference_flag, used first.\n" )
.LC242:
	ASCII(.string	"mulitislice diff adaptive_ref_pic_marking_mode_flag, used first.\n" )
	.zero	6
.LC244:
	ASCII(.string	"TotalPicNum=%d, SliceNumInPic=%d, TotalNal=%d\n" )
	.zero	1
.LC246:
	ASCII(.string	"SH: pic_parameter_set_id" )
	.zero	7
.LC248:
	ASCII(.string	"pps id:%d in sliceheader err\n" )
	.zero	2
.LC250:
	ASCII(.string	"PPS or SPS of this slice not valid\n" )
	.zero	4
.LC252:
	ASCII(.string	"MVC_PPSSPSCheck failed, PPS or SPS of this slice not valid\n" )
	.zero	4
.LC254:
	ASCII(.string	"SH: frame_num" )
	.zero	2
.LC256:
	ASCII(.string	"IDR NAL but frame_num!=0.\n" )
	.zero	5
.LC258:
	ASCII(.string	"SH: field_pic_flag" )
	.zero	5
.LC260:
	ASCII(.string	"SH: bottom_field_flag" )
	.zero	2
.LC262:
	ASCII(.string	"field first_mb_in_slice bigger than pic size\n" )
	.zero	2
.LC264:
	ASCII(.string	"MVC_FRAME first_mb_in_slice bigger than pic size\n" )
	.zero	6
.LC266:
	ASCII(.string	"SH: idr_pic_id" )
	.zero	1
.LC268:
	ASCII(.string	"idr_pic_id bigger than 65535\n" )
	.zero	2
.LC270:
	ASCII(.string	"SH: pic_order_cnt_lsb" )
	.zero	2
.LC272:
	ASCII(.string	"SH: delta_pic_order_cnt_bottom" )
	.zero	1
.LC274:
	ASCII(.string	"SH: delta_pic_order_cnt[0]" )
	.zero	5
.LC276:
	ASCII(.string	"SH: delta_pic_order_cnt[1]" )
	.zero	5
.LC278:
	ASCII(.string	"SH: redundant_pic_cnt" )
	.zero	2
.LC280:
	ASCII(.string	"redundant pic not support.\n" )
	.zero	4
.LC283:
	ASCII(.string	"first_mb_in_slice in currslice small than prevslice in same pic\n" )
	.zero	7
.LC287:
	ASCII(.string	"SH: direct_spatial_mv_pred_flag" )
.LC289:
	ASCII(.string	"SH: num_ref_idx_override_flag" )
	.zero	2
.LC291:
	ASCII(.string	"SH: num_ref_idx_l0_active_minus1" )
	.zero	7
.LC293:
	ASCII(.string	"SH: num_ref_idx_l1_active_minus1" )
	.zero	7
.LC295:
	ASCII(.string	"MVC_FRAME num_ref_idx_lx_active_minus1 exceed\n" )
	.zero	1
.LC297:
	ASCII(.string	"field num_ref_idx_lx_active_minus1 exceed\n" )
	.zero	5
.LC299:
	ASCII(.string	"reordering para dec err\n" )
	.zero	7
.LC301:
	ASCII(.string	"apply_weights_flag=%d\n" )
	.zero	1
.LC303:
	ASCII(.string	"wpt dec err\n" )
	.zero	3
.LC305:
	ASCII(.string	"mark para dec err\n" )
	.zero	5
.LC307:
	ASCII(.string	"SH: cabac_init_idc" )
	.zero	5
.LC309:
	ASCII(.string	"cabac_init_idc bigger than 3\n" )
	.zero	2
.LC311:
	ASCII(.string	"SH: slice_qp_delta" )
	.zero	5
.LC313:
	ASCII(.string	"SH: disable_deblocking_filter_idc" )
	.zero	6
.LC315:
	ASCII(.string	"disable_deblocking_filter_idc dec err\n" )
	.zero	1
.LC317:
	ASCII(.string	"SH: slice_alpha_c0_offset_div2" )
	.zero	1
.LC319:
	ASCII(.string	"slice_alpha_c0_offset_div2 dec err\n" )
	.zero	4
.LC321:
	ASCII(.string	"SH: slice_beta_offset_div2" )
	.zero	5
.LC323:
	ASCII(.string	"slice_beta_offset_div2 dec err\n" )
.LC325:
	ASCII(.string	"pMvcCtx->pCurrNal->nal_bitoffset = %d; code_len_byte = %d; bitstream_length = %d; pMvcCtx->pCurrNal->nal_trail_zero_bit_num = %d\n" )
	.zero	6
.LC327:
	ASCII(.string	"stream[%d]: bitsoffset = %d; valid_bitlen = %d; bytespos = %x\n" )
	.zero	1
.LC329:
	ASCII(.string	"nal_segment = %d is not expected value\n" )
.LC331:
	ASCII(.string	"stream[%d]: bitsoffset = %d; valid_bitlen = %d\n" )
.LC334:
	ASCII(.string	"   : delta_sl   " )
	.zero	7
.LC338:
	ASCII(.string	"PPS: entropy_coding_mode_flag" )
	.zero	2
.LC340:
	ASCII(.string	"PPS: pic_order_present_flag" )
	.zero	4
.LC342:
	ASCII(.string	"PPS: num_slice_groups_minus1" )
	.zero	3
.LC344:
	ASCII(.string	"MVC_BASELINE stream with FMO, not support.\n" )
	.zero	4
.LC347:
	ASCII(.string	"PPS: num_ref_idx_l0_active_minus1" )
	.zero	6
.LC349:
	ASCII(.string	"num_ref_idx_l0_active_minus1 out of range.\n" )
	.zero	4
.LC351:
	ASCII(.string	"PPS: num_ref_idx_l1_active_minus1" )
	.zero	6
.LC353:
	ASCII(.string	"num_ref_idx_l1_active_minus1 out of range.\n" )
	.zero	4
.LC355:
	ASCII(.string	"PPS: weighted prediction flag" )
	.zero	2
.LC357:
	ASCII(.string	"PPS: weighted_bipred_idc" )
	.zero	7
.LC359:
	ASCII(.string	"weighted_bipred_idc out of range\n" )
	.zero	6
.LC361:
	ASCII(.string	"PPS: pic_init_qp_minus26" )
	.zero	7
.LC363:
	ASCII(.string	"PPS: pic_init_qs_minus26" )
	.zero	7
.LC365:
	ASCII(.string	"PPS: chroma_qp_index_offset" )
	.zero	4
.LC367:
	ASCII(.string	"PPS: deblocking_filter_control_present_flag" )
	.zero	4
.LC369:
	ASCII(.string	"PPS: constrained_intra_pred_flag" )
	.zero	7
.LC371:
	ASCII(.string	"PPS: redundant_pic_cnt_present_flag" )
	.zero	4
.LC373:
	ASCII(.string	"redundant pic not support when find redundant slice later, exit\n" )
	.zero	7
.LC375:
	ASCII(.string	"PPS: transform_8x8_mode_flag" )
	.zero	3
.LC377:
	ASCII(.string	"PPS: pic_scaling_matrix_present_flag" )
	.zero	3
.LC379:
	ASCII(.string	"PPS: second_chroma_qp_index_offset" )
	.zero	5
.LC381:
	ASCII(.string	"SPS: seq_scaling_list_present_flag" )
	.zero	5
.LC384:
	ASCII(.string	"PPS: pic_scaling_list_present_flag" )
	.zero	5
.LC386:
	ASCII(.string	"second_chroma_qp_index_offset out of range.\n" )
	.zero	3
.LC390:
	ASCII(.string	"PPS: pic_parameter_set_id" )
	.zero	6
.LC392:
	ASCII(.string	"pic_parameter_set_id(%d) out of range.\n" )
.LC395:
	ASCII(.string	"PPS: seq_parameter_set_id" )
	.zero	6
.LC397:
	ASCII(.string	"seq_parameter_set_id out of range.\n" )
	.zero	4
.LC400:
	ASCII(.string	"PPS decode error line: %d.\n" )
	.zero	4
.LC403:
	ASCII(.string	"VUI: aspect_ratio_info_present_flag" )
	.zero	4
.LC405:
	ASCII(.string	"VUI: aspect_ratio_idc" )
	.zero	2
.LC407:
	ASCII(.string	"VUI: sar_width" )
	.zero	1
.LC409:
	ASCII(.string	"VUI: sar_height" )
.LC411:
	ASCII(.string	"VUI: overscan_info_present_flag" )
.LC413:
	ASCII(.string	"VUI: overscan_appropriate_flag" )
	.zero	1
.LC415:
	ASCII(.string	"VUI: video_signal_type_present_flag" )
	.zero	4
.LC417:
	ASCII(.string	"VUI: video_format" )
	.zero	6
.LC419:
	ASCII(.string	"VUI: video_full_range_flag" )
	.zero	5
.LC421:
	ASCII(.string	"VUI: color_description_present_flag" )
	.zero	4
.LC423:
	ASCII(.string	"VUI: colour_primaries" )
	.zero	2
.LC425:
	ASCII(.string	"VUI: transfer_characteristics" )
	.zero	2
.LC427:
	ASCII(.string	"VUI: matrix_coefficients" )
	.zero	7
.LC429:
	ASCII(.string	"VUI: chroma_loc_info_present_flag" )
	.zero	6
.LC431:
	ASCII(.string	"VUI: chroma_sample_loc_type_top_field" )
	.zero	2
.LC433:
	ASCII(.string	"VUI: chroma_sample_loc_type_bottom_field" )
	.zero	7
.LC435:
	ASCII(.string	"VUI: timing_info_present_flag" )
	.zero	2
.LC437:
	ASCII(.string	"VUI: num_units_in_tick" )
	.zero	1
.LC439:
	ASCII(.string	"VUI: time_scale" )
.LC441:
	ASCII(.string	"VUI: fixed_frame_rate_flag" )
	.zero	5
.LC443:
	ASCII(.string	"VUI: nal_hrd_parameters_present_flag" )
	.zero	3
.LC445:
	ASCII(.string	"VUI: cpb_cnt_minus1" )
	.zero	4
.LC447:
	ASCII(.string	"VUI: bit_rate_scale" )
	.zero	4
.LC449:
	ASCII(.string	"VUI: cpb_size_scale" )
	.zero	4
.LC451:
	ASCII(.string	"hrd->cpb_cnt_minus1 out of range\n" )
	.zero	6
.LC453:
	ASCII(.string	"VUI: bit_rate_value_minus1" )
	.zero	5
.LC455:
	ASCII(.string	"VUI: cpb_size_value_minus1" )
	.zero	5
.LC457:
	ASCII(.string	"VUI: cbr_flag" )
	.zero	2
.LC459:
	ASCII(.string	"VUI: initial_cpb_removal_delay_length_minus1" )
	.zero	3
.LC461:
	ASCII(.string	"VUI: cpb_removal_delay_length_minus1" )
	.zero	3
.LC463:
	ASCII(.string	"VUI: dpb_output_delay_length_minus1" )
	.zero	4
.LC465:
	ASCII(.string	"VUI: time_offset_length" )
.LC467:
	ASCII(.string	"VUI: vcl_hrd_parameters_present_flag" )
	.zero	3
.LC469:
	ASCII(.string	"VUI: low_delay_hrd_flag" )
.LC471:
	ASCII(.string	"VUI: pic_struct_present_flag" )
	.zero	3
.LC473:
	ASCII(.string	"VUI: bitstream_restriction_flag" )
.LC475:
	ASCII(.string	"VUI: motion_vectors_over_pic_boundaries_flag" )
	.zero	3
.LC477:
	ASCII(.string	"VUI: max_bytes_per_pic_denom" )
	.zero	3
.LC479:
	ASCII(.string	"VUI: max_bits_per_mb_denom" )
	.zero	5
.LC481:
	ASCII(.string	"VUI: log2_max_mv_length_horizontal" )
	.zero	5
.LC483:
	ASCII(.string	"VUI: log2_max_mv_length_vertical" )
	.zero	7
.LC485:
	ASCII(.string	"VUI: num_reorder_frames" )
.LC487:
	ASCII(.string	"VUI: max_dec_frame_buffering" )
	.zero	3
.LC492:
	ASCII(.string	"dar=%d, final_dar=%d\n" )
	.zero	2
.LC498:
	ASCII(.string	"SPS: chroma_format_idc" )
	.zero	1
.LC500:
	ASCII(.string	"pSPS->chroma_format_idc out of range.\n" )
	.zero	1
.LC502:
	ASCII(.string	"SPS: bit_depth_luma_minus8" )
	.zero	5
.LC504:
	ASCII(.string	"bit_depth_luma_minus8 not equal 0.\n" )
	.zero	4
.LC506:
	ASCII(.string	"SPS: bit_depth_chroma_minus8" )
	.zero	3
.LC508:
	ASCII(.string	"bit_depth_chroma_minus8 not equal 0.\n" )
	.zero	2
.LC510:
	ASCII(.string	"SPS: qpprime_y_zero_trans_bypass_flag" )
	.zero	2
.LC512:
	ASCII(.string	"qpprime_y_zero_trans_bypass_flag not equal 0.\n" )
	.zero	1
.LC514:
	ASCII(.string	"SPS: seq_scaling_matrix_present_flag" )
	.zero	3
.LC518:
	ASCII(.string	"SPS: log2_max_frame_num_minus4" )
	.zero	1
.LC520:
	ASCII(.string	"pSPS->log2_max_frame_num_minus4 out of range.\n" )
	.zero	1
.LC522:
	ASCII(.string	"SPS: pic_order_cnt_type" )
.LC524:
	ASCII(.string	"pSPS->pic_order_cnt_type out of range.\n" )
.LC526:
	ASCII(.string	"SPS: log2_max_pic_order_cnt_lsb_minus4" )
	.zero	1
.LC528:
	ASCII(.string	"pSPS->log2_max_pic_order_cnt_lsb_minus4 out of range.\n" )
	.zero	1
.LC530:
	ASCII(.string	"SPS: delta_pic_order_always_zero_flag" )
	.zero	2
.LC532:
	ASCII(.string	"SPS: offset_for_non_ref_pic" )
	.zero	4
.LC534:
	ASCII(.string	"SPS: offset_for_top_to_bottom_field" )
	.zero	4
.LC536:
	ASCII(.string	"SPS: num_ref_frames_in_pic_order_cnt_cycle" )
	.zero	5
.LC538:
	ASCII(.string	"pSPS->num_ref_frames_in_pic_order_cnt_cycle out of range.\n" )
	.zero	5
.LC540:
	ASCII(.string	"SPS: offset_for_ref_frame[i]" )
	.zero	3
.LC542:
	ASCII(.string	"SPS: gaps_in_frame_num_value_allowed_flag" )
	.zero	6
.LC544:
	ASCII(.string	"SPS: pic_width_in_mbs_minus1" )
	.zero	3
.LC546:
	ASCII(.string	"pSPS->pic_width_in_mbs_minus1 out of range(=%d).\n" )
	.zero	6
.LC548:
	ASCII(.string	"SPS: pic_height_in_map_units_minus1" )
	.zero	4
.LC550:
	ASCII(.string	"SPS: frame_mbs_only_flag" )
	.zero	7
.LC552:
	ASCII(.string	"pSPS->pic_height_in_map_units_minus1 out of range.\n" )
	.zero	4
.LC554:
	ASCII(.string	"pic size too large.\n" )
	.zero	3
.LC557:
	ASCII(.string	"level_idc %d not support.\n" )
	.zero	5
.LC559:
	ASCII(.string	"dpb size according level : %d\n" )
	.zero	1
.LC561:
	ASCII(.string	"pSPS->num_ref_frames(%d) > DPB size(%d), try to select the reasonable one.\n" )
	.zero	4
.LC563:
	ASCII(.string	"SPS: direct_8x8_inference_flag" )
	.zero	1
.LC565:
	ASCII(.string	"SPS: frame_cropping_flag" )
	.zero	7
.LC567:
	ASCII(.string	"SPS: frame_cropping_rect_left_offset" )
	.zero	3
.LC569:
	ASCII(.string	"SPS: frame_cropping_rect_right_offset" )
	.zero	2
.LC571:
	ASCII(.string	"SPS: frame_cropping_rect_top_offset" )
	.zero	4
.LC573:
	ASCII(.string	"SPS: frame_cropping_rect_bottom_offset" )
	.zero	1
.LC575:
	ASCII(.string	"SPS: vui_parameters_present_flag" )
	.zero	7
.LC577:
	ASCII(.string	"max_dec_frame_buffering(%d) > MaxDpbSize(%d)\n" )
	.zero	2
.LC580:
	ASCII(.string	"SPS: num_ref_frames" )
	.zero	4
.LC582:
	ASCII(.string	"SPS: mb_adaptive_frame_field_flag" )
	.zero	6
.LC584:
	ASCII(.string	"SPS: profile_idc" )
	.zero	7
.LC586:
	ASCII(.string	"SPS: constrained_set0_flag" )
	.zero	5
.LC588:
	ASCII(.string	"SPS: constrained_set1_flag" )
	.zero	5
.LC590:
	ASCII(.string	"SPS: constrained_set2_flag" )
	.zero	5
.LC592:
	ASCII(.string	"SPS: constrained_set3_flag" )
	.zero	5
.LC594:
	ASCII(.string	"SPS: constrained_set4_flag" )
	.zero	5
.LC596:
	ASCII(.string	"SPS: constrained_set5_flag" )
	.zero	5
.LC598:
	ASCII(.string	"SPS: reserved_zero_2bits" )
	.zero	7
.LC600:
	ASCII(.string	"SPS: level_idc" )
	.zero	1
.LC602:
	ASCII(.string	"SPS: seq_parameter_set_id" )
	.zero	6
.LC606:
	ASCII(.string	"MVC_BASELINE stream, try to decode, exit when FMO occurred.\n" )
	.zero	3
.LC608:
	ASCII(.string	"MVC_EXTENDED stream, try to decode, exit when datapartition occurred.\n" )
	.zero	1
.LC610:
	ASCII(.string	"others High profile stream, try to decode, exit when high profile not support occurred.\n" )
	.zero	7
.LC612:
	ASCII(.string	"profile_idc = %5d error, try to decode as main profile.\n" )
	.zero	7
.LC614:
	ASCII(.string	"level_idc = %5d error, try to decode as level_idc %d.\n" )
	.zero	1
.LC617:
	ASCII(.string	"Line %d: SPS[%d] decode error.\n" )
.LC623:
	ASCII(.string	"SUBSPS: num_views_minus1" )
	.zero	7
.LC625:
	ASCII(.string	"pSubsps->num_views_minus1(%d) out of range.\n" )
	.zero	3
.LC627:
	ASCII(.string	"SUBSPS: view_id[]" )
	.zero	6
.LC629:
	ASCII(.string	"SUBSPS: num_anchor_refs_l0[]" )
	.zero	3
.LC631:
	ASCII(.string	"SUBSPS: num_anchor_refs_l1[]" )
	.zero	3
.LC633:
	ASCII(.string	"pSubsps->num_anchor_refs_l0(%d) out of range.\n" )
	.zero	1
.LC635:
	ASCII(.string	"SUBSPS: anchor_ref_l0[][]" )
	.zero	6
.LC637:
	ASCII(.string	"pSubsps->num_anchor_refs_l1(%d) out of range.\n" )
	.zero	1
.LC639:
	ASCII(.string	"SUBSPS: anchor_ref_l1[][]" )
	.zero	6
.LC641:
	ASCII(.string	"SUBSPS: num_level_values_signalled_minus1" )
	.zero	6
.LC643:
	ASCII(.string	"SUBSPS: num_non_anchor_refs_l0[]" )
	.zero	7
.LC645:
	ASCII(.string	"SUBSPS: num_non_anchor_refs_l1[]" )
	.zero	7
.LC647:
	ASCII(.string	"pSubsps->num_non_anchor_refs_l0(%d) out of range.\n" )
	.zero	5
.LC649:
	ASCII(.string	"SUBSPS: non_anchor_ref_l0[][]" )
	.zero	2
.LC651:
	ASCII(.string	"pSubsps->num_non_anchor_refs_l1(%d) out of range.\n" )
	.zero	5
.LC653:
	ASCII(.string	"SUBSPS: non_anchor_ref_l1[][]" )
	.zero	2
.LC655:
	ASCII(.string	"num_level(%d) out of range.\n" )
	.zero	3
.LC657:
	ASCII(.string	"SUBSPS: level_idc[]" )
	.zero	4
.LC659:
	ASCII(.string	"SUBSPS: num_applicable_ops_minus1" )
	.zero	6
.LC661:
	ASCII(.string	"num_ops(%d) out of range.\n" )
	.zero	5
.LC663:
	ASCII(.string	"SUBSPS: applicable_op_temporal_id[][]" )
	.zero	2
.LC665:
	ASCII(.string	"SUBSPS: applicable_op_num_target_views_minus1[][]" )
	.zero	6
.LC667:
	ASCII(.string	"SUBSPS: applicable_op_num_views_minus1" )
	.zero	1
.LC669:
	ASCII(.string	"applicable_op_num_target_views(%d) out of range.\n" )
	.zero	6
.LC671:
	ASCII(.string	"SUBSPS: applicable_op_target_view_id[][][]" )
	.zero	5
.LC673:
	ASCII(.string	"pSubsps->applicable_op_num_views_minus1(%d) out of range.\n" )
	.zero	5
.LC675:
	ASCII(.string	"MVC VUI: vui_mvc_num_ops_minus1" )
.LC677:
	ASCII(.string	"vui_mvc_num_ops_minus1 %d out of range\n" )
.LC679:
	ASCII(.string	"MVC VUI: vui_mvc_temporal_id[]" )
	.zero	1
.LC681:
	ASCII(.string	"SUBSPS VUI: vui_mvc_num_target_output_views_minus1[]" )
	.zero	3
.LC683:
	ASCII(.string	"vui_mvc_num_target_output_views_minus1 %d out of range\n" )
.LC685:
	ASCII(.string	"MVC VUI: vui_mvc_timing_info_present_flag" )
	.zero	6
.LC687:
	ASCII(.string	"MVC VUI: vui_mvc_view_id[][]" )
	.zero	3
.LC689:
	ASCII(.string	"MVC VUI: vui_mvc_num_units_in_tick" )
	.zero	5
.LC691:
	ASCII(.string	"MVC VUI: vui_mvc_time_scale[]" )
	.zero	2
.LC693:
	ASCII(.string	"MVC VUI: vui_mvc_fixed_frame_rate_flag" )
	.zero	1
.LC695:
	ASCII(.string	"MVC VUI: vui_mvc_nal_hrd_parameters_present_flag[]" )
	.zero	5
.LC697:
	ASCII(.string	"MVC VUI: cpb_cnt_minus1" )
.LC699:
	ASCII(.string	"MVC VUI: bit_rate_scale" )
.LC701:
	ASCII(.string	"MVC VUI: cpb_size_scale" )
.LC704:
	ASCII(.string	"MVC VUI: bit_rate_value_minus1" )
	.zero	1
.LC706:
	ASCII(.string	"MVC VUI: cpb_size_value_minus1" )
	.zero	1
.LC708:
	ASCII(.string	"MVC VUI: cbr_flag" )
	.zero	6
.LC710:
	ASCII(.string	"MVC VUI: initial_cpb_removal_delay_length_minus1" )
	.zero	7
.LC712:
	ASCII(.string	"MVC VUI: cpb_removal_delay_length_minus1" )
	.zero	7
.LC714:
	ASCII(.string	"MVC VUI: dpb_output_delay_length_minus1" )
.LC716:
	ASCII(.string	"MVC VUI: time_offset_length" )
	.zero	4
.LC718:
	ASCII(.string	"MVC VUI: vui_mvc_vcl_hrd_parameters_present_flag[]" )
	.zero	5
.LC720:
	ASCII(.string	"MVC VUI: vui_mvc_low_delay_hrd_flag[]" )
	.zero	2
.LC722:
	ASCII(.string	"MVC VUI: vui_mvc_pic_struct_present_flag[]" )
	.zero	5
.LC724:
	ASCII(.string	"SUBSPS: profile_idc" )
	.zero	4
.LC726:
	ASCII(.string	"SUBSPS: constrained_set0_flag" )
	.zero	2
.LC728:
	ASCII(.string	"SUBSPS: constrained_set1_flag" )
	.zero	2
.LC730:
	ASCII(.string	"SUBSPS: constrained_set2_flag" )
	.zero	2
.LC732:
	ASCII(.string	"SUBSPS: constrained_set3_flag" )
	.zero	2
.LC734:
	ASCII(.string	"SUBSPS: constrained_set4_flag" )
	.zero	2
.LC736:
	ASCII(.string	"SUBSPS: constrained_set5_flag" )
	.zero	2
.LC738:
	ASCII(.string	"SUBSPS: reserved_zero_2bits" )
	.zero	4
.LC740:
	ASCII(.string	"SUBSPS: level_idc" )
	.zero	6
.LC742:
	ASCII(.string	"SUBSPS: seq_parameter_set_id" )
	.zero	3
.LC749:
	ASCII(.string	"profile_idc = %5d error\n" )
	.zero	7
.LC751:
	ASCII(.string	"level_idc = %5d error, try to decode as level_idc 41.\n" )
	.zero	1
.LC753:
	ASCII(.string	"SUBSPS decode error.\n" )
	.zero	2
.LC755:
	ASCII(.string	"SUBSPS: bit_equal_to_one" )
	.zero	7
.LC757:
	ASCII(.string	"SUBSPS Mvc Ext decode error.\n" )
	.zero	2
.LC759:
	ASCII(.string	"SUBSPS: mvc_vui_parameters_present_flag" )
.LC761:
	ASCII(.string	"SUBSPS Mvc Vui Ext decode error.\n" )
	.zero	6
.LC763:
	ASCII(.string	"SEI: frame_packing_arrangement_id" )
	.zero	6
.LC765:
	ASCII(.string	"SEI: frame_packing_arrangement_cancel_flag" )
	.zero	5
.LC767:
	ASCII(.string	"SEI: frame_packing_arrangement_type" )
	.zero	4
.LC769:
	ASCII(.string	"SEI: quincunx_sampling_flag" )
	.zero	4
.LC771:
	ASCII(.string	"SEI: content_interpretation_type" )
	.zero	7
.LC773:
	ASCII(.string	"SEI: spatial_flipping_flag" )
	.zero	5
.LC775:
	ASCII(.string	"SEI: frame0_flipped_flag" )
	.zero	7
.LC777:
	ASCII(.string	"SEI: field_views_flag" )
	.zero	2
.LC779:
	ASCII(.string	"SEI: current_frame_is_frame0_flag" )
	.zero	6
.LC781:
	ASCII(.string	"SEI: frame0_self_contained_flag" )
.LC783:
	ASCII(.string	"SEI: frame1_self_contained_flag" )
.LC785:
	ASCII(.string	"SEI: frame0_grid_position_x" )
	.zero	4
.LC787:
	ASCII(.string	"SEI: frame0_grid_position_y" )
	.zero	4
.LC789:
	ASCII(.string	"SEI: frame1_grid_position_x" )
	.zero	4
.LC791:
	ASCII(.string	"SEI: frame1_grid_position_y" )
	.zero	4
.LC793:
	ASCII(.string	"SEI: frame_packing_arrangement_reserved_byte" )
	.zero	3
.LC795:
	ASCII(.string	"SEI: frame_packing_arrangement_repetition_period" )
	.zero	7
.LC797:
	ASCII(.string	"SEI: frame_packing_arrangement_extension_flag" )
	.zero	2
.LC799:
	ASCII(.string	"DecPicTimingSEI but SPS is invalid.\n" )
	.zero	3
.LC801:
	ASCII(.string	"SEI: cpb_removal_delay" )
	.zero	1
.LC803:
	ASCII(.string	"SEI: dpb_output_delay" )
	.zero	2
.LC805:
	ASCII(.string	"pic_struct" )
	.zero	5
.LC807:
	ASCII(.string	"SEI nal dec payload type err\n" )
	.zero	2
.LC809:
	ASCII(.string	"SEI nal dec payloadSize err\n" )
	.zero	3
.LC812:
	ASCII(.string	"MVC_SEI_BUFFERING_PERIOD,offset = %d,payload_size = %d \n" )
	.zero	7
.LC815:
	ASCII(.string	"MVC_PassBytes err [%s][%d]\n" )
	.zero	4
.LC817:
	ASCII(.string	"MVC_SEI_PIC_TIMING,offset = %d,payload_size = %d \n" )
	.zero	5
.LC819:
	ASCII(.string	"MVC_SEI_PAN_SCAN_RECT,offset = %d,payload_size = %d \n" )
	.zero	2
.LC821:
	ASCII(.string	"MVC_SEI_FILLER_PAYLOAD,offset = %d,payload_size = %d \n" )
	.zero	1
.LC823:
	ASCII(.string	"MVC_SEI_USER_DATA_REGISTERED_ITU_T_T35, offset = %d, payload_size = %d \n" )
	.zero	7
.LC825:
	ASCII(.string	"MVC_SEI_USER_DATA_UNREGISTERED, offset = %d, payload_size = %d \n" )
	.zero	7
.LC827:
	ASCII(.string	"SEI: itu_t_t35_country_code" )
	.zero	4
.LC829:
	ASCII(.string	"SEI: itu_t_t35_country_code_extension_byte" )
	.zero	5
.LC831:
	ASCII(.string	"SEI: itu_t_t35_provider_code" )
	.zero	3
.LC834:
	ASCII(.string	"cann't dec usrdata\n" )
	.zero	4
.LC836:
	ASCII(.string	"MVC_SEI_RECOVERY_POINT,offset = %d,payload_size = %d \n" )
	.zero	1
.LC838:
	ASCII(.string	"MVC_SEI_DEC_REF_PIC_MARKING_REPETITION,offset = %d,payload_size = %d \n" )
	.zero	1
.LC840:
	ASCII(.string	"MVC_SEI_SPARE_PIC,offset = %d,payload_size = %d \n" )
	.zero	6
.LC842:
	ASCII(.string	"MVC_SEI_SCENE_INFO,offset = %d,payload_size = %d \n" )
	.zero	5
.LC844:
	ASCII(.string	"MVC_SEI_SUB_SEQ_INFO,offset = %d,payload_size = %d \n" )
	.zero	3
.LC846:
	ASCII(.string	"MVC_SEI_SUB_SEQ_LAYER_CHARACTERISTICS,offset = %d,payload_size = %d \n" )
	.zero	2
.LC848:
	ASCII(.string	"MVC_SEI_SUB_SEQ_CHARACTERISTICS,offset = %d,payload_size = %d \n" )
.LC850:
	ASCII(.string	"MVC_SEI_FULL_FRAME_FREEZE,offset = %d,payload_size = %d \n" )
	.zero	6
.LC852:
	ASCII(.string	"MVC_SEI_FULL_FRAME_FREEZE_RELEASE,offset = %d,payload_size = %d \n" )
	.zero	6
.LC854:
	ASCII(.string	"MVC_SEI_FULL_FRAME_SNAPSHOT,offset = %d,payload_size = %d \n" )
	.zero	4
.LC856:
	ASCII(.string	"MVC_SEI_PROGRESSIVE_REFINEMENT_SEGMENT_START,offset = %d,payload_size = %d \n" )
	.zero	3
.LC858:
	ASCII(.string	"MVC_SEI_PROGRESSIVE_REFINEMENT_SEGMENT_END,offset = %d,payload_size = %d \n" )
	.zero	5
.LC860:
	ASCII(.string	"MVC_SEI_MOTION_CONSTRAINED_SLICE_GROUP_SET,offset = %d,payload_size = %d \n" )
	.zero	5
.LC862:
	ASCII(.string	"MVC_SEI_FILM_GRAIN_CHARACTERISTICS,offset = %d,payload_size = %d \n" )
	.zero	5
.LC864:
	ASCII(.string	"MVC_SEI_DEBLOCKING_FILTER_DISPLAY_PREFERENCE,offset = %d,payload_size = %d \n" )
	.zero	3
.LC866:
	ASCII(.string	"MVC_SEI_STEREO_VIDEO_INFO,offset = %d,payload_size = %d \n" )
	.zero	6
.LC868:
	ASCII(.string	"too much usrdat, cann't dec SEI\n" )
	.zero	7
.LC872:
	ASCII(.string	"\n mvc the stream is error,len:%d\n" )
	.zero	6
.LC877:
	ASCII(.string	"\nSlice nal or IDR nal = %d\n" )
	.zero	4
.LC879:
	ASCII(.string	"sliceheader dec err\n" )
	.zero	3
.LC882:
	ASCII(.string	"MVC_InquireSliceProperty mvc flag %d is wrong\n" )
	.zero	1
.LC884:
	ASCII(.string	"MvcDec destroy\n" )
.LC886:
	ASCII(.string	"MVC recycle image\n" )
	.zero	5
.LC888:
	ASCII(.string	"pH264Ctx is %#x, pFrameStore is %#x\n" )
	.zero	3
.LC890:
	ASCII(.string	"line: %d, pstLogicFsImage is NULL\n" )
	.zero	5
.LC892:
	ASCII(.string	"InsertVO err:%d, MVC_ClearAll\n" )
	.zero	1
.LC894:
	ASCII(.string	"mvc.c line %d: MVC_FRAME para err(ret=%d), recycle image self\n" )
	.zero	1
.LC898:
	ASCII(.string	"[%s][%d] MVC_OutputFrmToVO return %d !\n" )
.LC901:
	ASCII(.string	"[%s][%d] MVC_OutputFrmToVO return %d\n" )
	.zero	2
.LC905:
	ASCII(.string	"%s %d MVC_OK != MVC_FlushDPB!!\n" )
.LC907:
	ASCII(.string	"%s %d MVC_OK != MVC_InitDPB!!\n" )
	.zero	1
.LC909:
	ASCII(.string	"----------------- MVC_IMODE -> %d ------------------\n" )
	.zero	2
.LC911:
	ASCII(.string	"Discard this B(poc=%d) befor P, is_ref_idc=%d.\n" )
.LC913:
	ASCII(.string	"***** VDM start, TotalPicNum=%d, pMvcCtx->CurrPic.structure=%d.\n" )
	.zero	7
.LC917:
	ASCII(.string	"MVC_DecVDM fail [%s][%d]\n" )
	.zero	6
.LC919:
	ASCII(.string	"\n receive streambuff=%p; phy_addr=0x%x; bitstream_length=%d\n" )
	.zero	3
.LC921:
	ASCII(.string	"nal_releaMVC_SE_ERR\n" )
	.zero	3
.LC923:
	ASCII(.string	"cann't find slot for current nal\n" )
	.zero	6
.LC926:
	ASCII(.string	"receive a zero packet\n" )
	.zero	1
.LC928:
	ASCII(.string	"clear all dec para\n" )
	.zero	4
.LC934:
	ASCII(.string	"line %d, get APC error, ret %d\n" )
.LC936:
	ASCII(.string	"InserFrmInDPB: cur pic struct = %d!\n" )
	.zero	3
.LC938:
	ASCII(.string	"line: %d, pImage is NULL!\n" )
	.zero	5
.LC940:
	ASCII(.string	"FS_ALLOC_ERR, MVC_ClearAll\n" )
	.zero	4
.LC943:
	ASCII(.string	"Can not new logic fs! MVC_ClearAll\n" )
	.zero	4
.LC947:
	ASCII(.string	"%s %d NULL== pMvcCtx->SPS || NULL == pMvcCtx->PPS || NULL == pMvcCtx->DecSlicePara!!\n" )
	.zero	2
.LC949:
	ASCII(.string	"-1 == VCTRL_GetChanIDByCtx() Err! \n" )
	.zero	4
.LC951:
	ASCII(.string	"CurrPic.state is 'MVC_EMPTY'\n" )
	.zero	2
.LC953:
	ASCII(.string	"MVC_StorePicInDpb return(%d) from L%d\n" )
	.zero	1
.LC955:
	ASCII(.string	"Is IDR, but init DPB failed!\n" )
	.zero	2
.LC957:
	ASCII(.string	"Is IDR, but FlushDPB failed!\n" )
	.zero	2
.LC959:
	ASCII(.string	"MVC_DirectOutput mode\n" )
	.zero	1
.LC961:
	ASCII(.string	"line %d, REPORT_IFRAME_ERR\n" )
	.zero	4
.LC964:
	ASCII(.string	"line %d, return %d\n" )
	.zero	4
.LC966:
	ASCII(.string	"err(%d) > ref_thr(%d)\n" )
	.zero	1
.LC968:
	ASCII(.string	"MVC_Marking return %d\n" )
	.zero	1
.LC970:
	ASCII(.string	"line %d: pMvcCtx->DPB.size = %d, ref %d, ltref %d\n" )
	.zero	5
.LC972:
	ASCII(.string	"line %d, MVC_GetMinPOC failed\n" )
	.zero	1
.LC975:
	ASCII(.string	"%s: pos(%d) = pre_pos, force return.\n" )
	.zero	2
.LC977:
	ASCII(.string	"GAP found while DPB is MVC_EMPTY!\n" )
	.zero	5
.LC979:
	ASCII(.string	"MVC_FRAME num gap try to fill it \n" )
	.zero	5
.LC981:
	ASCII(.string	"CurrFrameNum = %d  UnusedShortTermFrameNum = %d\n" )
	.zero	7
.LC983:
	ASCII(.string	"cann't allocate MVC_FRAME store when gap find\n" )
	.zero	1
.LC985:
	ASCII(.string	"allocate MVC_FRAME store when gap find\n" )
.LC987:
	ASCII(.string	"line %d: store gap pic err, ret=%d\n" )
	.zero	4
.LC991:
	ASCII(.string	"line %d: flush dpb return %d\n" )
	.zero	2
.LC993:
	ASCII(.string	"line %d: init dpb return %d\n" )
	.zero	3
.LC995:
	ASCII(.string	"resolution error, the CAP_LEVEL_USER_DEFINE_WITH_OPTION channel with s32ReRangeEn == 0 can't support such bitstream.\n" )
	.zero	2
.LC997:
	ASCII(.string	"s32MaxRefFrameNum < pMvcCtx->DPB.size, the CAP_LEVEL_USER_DEFINE_WITH_OPTION channel can't support such bitstream.\n" )
	.zero	4
.LC999:
	ASCII(.string	"mem arrange err, MVC_ClearAll\n" )
	.zero	1
.LC1001:
	ASCII(.string	"get back frm\n" )
	.zero	2
.LC1003:
	ASCII(.string	"line %d: MVC_FRAME gap(=%d) > dpb size(=%d)\n" )
	.zero	3
.LC1005:
	ASCII(.string	"MVC_FRAME num gap don't allowed but gap find\n" )
	.zero	2
.LC1007:
	ASCII(.string	"line %d: frame num(%d/%d) find gap in NON-I slice but here gap is not allowed\n" )
	.zero	1
.LC1009:
	ASCII(.string	"line %d: dec gap failed\n" )
	.zero	7
.LC1011:
	ASCII(.string	"line %d: alloc framestore failed\n" )
	.zero	6
.LC1013:
	ASCII(.string	"dec_pts: %lld\n" )
	.zero	1
.LC1015:
	ASCII(.string	"dec_usertag: %lld\n" )
	.zero	5
.LC1017:
	ASCII(.string	"line %d: CurrPic.frame_store is NULL\n" )
	.zero	2
.LC1022:
	ASCII(.string	"Start Reason: SliceParaNum, MaxBytesReceived = %d, %d(thr=%d)\n" )
	.zero	1
.LC1024:
	ASCII(.string	"Too many slice or bitstream, err!\n" )
	.zero	5
.LC1026:
	ASCII(.string	"Start Reason: new_pic_flag\n" )
	.zero	4
.LC1028:
	ASCII(.string	"init pic err, find next recover point or next valid sps, pps, or exit\n" )
	.zero	1
.LC1030:
	ASCII(.string	"MVC_DecList error, ret=%d\n" )
	.zero	5
.LC1032:
	ASCII(.string	"dec list err.\n" )
	.zero	1
.LC1034:
	ASCII(.string	"pMvcCtx->TotalNal = %d, type:%d\n" )
	.zero	7
.LC1036:
	ASCII(.string	"stop i want\n" )
	.zero	3
.LC1039:
	ASCII(.string	"***** NAL: IDR/Slice, nal_unit_type=%d, TotalSlice=%d\n" )
	.zero	1
.LC1041:
	ASCII(.string	"*******TotalPicNum=%d********\n" )
	.zero	1
.LC1044:
	ASCII(.string	"***** NAL: PPS, nal_unit_type=%d, TotalPPS=%d\n" )
	.zero	1
.LC1046:
	ASCII(.string	"PPS decode error.\n" )
	.zero	5
.LC1048:
	ASCII(.string	"***** NAL: SPS, nal_unit_type=%d, TotalSPS=%d\n" )
	.zero	1
.LC1050:
	ASCII(.string	"SPS decode error.\n" )
	.zero	5
.LC1052:
	ASCII(.string	"***** NAL: SEI, nal_unit_type=%d\n" )
	.zero	6
.LC1054:
	ASCII(.string	"SEI decode error.\n" )
	.zero	5
.LC1056:
	ASCII(.string	"***** NAL: AUD, nal_unit_type=%d\n" )
	.zero	6
.LC1058:
	ASCII(.string	"***** NAL: EOSEQ, nal_unit_type=%d\n" )
	.zero	4
.LC1060:
	ASCII(.string	"***** NAL: FILL, nal_unit_type=%d\n" )
	.zero	5
.LC1062:
	ASCII(.string	"***** NAL: EOSTREAM, nal_unit_type=%d\n" )
	.zero	1
.LC1064:
	ASCII(.string	"***** NAL: SPSEXT, nal_unit_type=%d\n" )
	.zero	3
.LC1066:
	ASCII(.string	"***** NAL: PREFIX, nal_unit_type=%d\n" )
	.zero	3
.LC1068:
	ASCII(.string	"***** NAL: SUBSPS, nal_unit_type=%d\n" )
	.zero	3
.LC1071:
	ASCII(.string	"***** NAL: AUX, nal_unit_type=%d\n" )
	.zero	6
.LC1073:
	ASCII(.string	"***** NAL: EOPIC, nal_unit_type=%d\n" )
	.zero	4
.LC1076:
	ASCII(.string	"***** NAL: UNSUPPORT, nal_unit_type=%d,nalu header:%x\n" )
	.zero	1
.LC1078:
	ASCII(.string	"nal_header != 0x00000100 not support.\n" )
	.zero	1
.LC1085:
	ASCII(.string	"IsSizeChanged = %d,TotalPicNum = %d,old w/h = %d/%d,new w/h = %d/%d\n" )
	.zero	3
.LC1088:
	ASCII(.string	"MVC_FindTrailZeros ERR\n" )
.LC1090:
	ASCII(.string	"store pic err, ret = %d\n" )
	.zero	7
.LC1092:
	ASCII(.string	"MVC_IMODE nal store pic err, ret = %d\n" )
	.zero	1
.LC1094:
	ASCII(.string	"MVC_IMODE nal flush dpb err, ret = %d\n" )
	.zero	1
.LC1096:
	ASCII(.string	"cann't find FrameStore\n" )
.LC1098:
	ASCII(.string	"========== MVC FrameStore state(is_used, is_in_dpb, MVC_IsOutDPB) ========\n" )
	.zero	4
.LC1100:
	ASCII(.string	"ReadImgNum = %d, NewImgNum = %d\n" )
	.zero	7
.LC1102:
	ASCII(.string	"%02d: %d %d %d\n" )
.LC1104:
	ASCII(.string	"FrameStore leak, MVC_ClearAll\n" )
	.bss
	.align	3
.LANCHOR2 = . + 0
.LANCHOR3 = . + 4352
	.type	pps_tmp.13285, %object
	.size	pps_tmp.13285, 2240
pps_tmp.13285:
	.zero	2240
	.type	sps_tmp.13421, %object
	.size	sps_tmp.13421, 3992
sps_tmp.13421:
	.zero	3992
	.type	MvcTmpBuf, %object
	.size	MvcTmpBuf, 68
MvcTmpBuf:
	.zero	68
	.type	cnt.12238, %object
	.size	cnt.12238, 4
cnt.12238:
	.zero	4
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
