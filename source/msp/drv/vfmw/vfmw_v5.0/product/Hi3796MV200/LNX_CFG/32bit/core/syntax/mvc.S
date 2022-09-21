#include "hi_asm_define.h"
	.arch armv7-a
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"mvc.c"
	.text
	.align	2
	.global	MVC_IsSTRefFlg
	.type	MVC_IsSTRefFlg, %function
MVC_IsSTRefFlg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r0, [r0]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	sub	r0, r0, #65536
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_IsSTRefFlg, .-MVC_IsSTRefFlg
	.align	2
	.global	MVC_IsLTRefFlg
	.type	MVC_IsLTRefFlg, %function
MVC_IsLTRefFlg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r0, [r0]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	sub	r0, r0, #256
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_IsLTRefFlg, .-MVC_IsLTRefFlg
	.align	2
	.global	MVC_compare_pic_by_pic_num_desc
	.type	MVC_compare_pic_by_pic_num_desc, %function
MVC_compare_pic_by_pic_num_desc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r0]
	ldr	r3, [r1]
	ldr	r2, [r2, #12]
	ldr	r3, [r3, #12]
	cmp	r2, r3
	blt	.L5
	mvngt	r0, #0
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L5:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_compare_pic_by_pic_num_desc, .-MVC_compare_pic_by_pic_num_desc
	.align	2
	.global	MVC_compare_pic_by_lt_pic_num_asc
	.type	MVC_compare_pic_by_lt_pic_num_asc, %function
MVC_compare_pic_by_lt_pic_num_asc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r0]
	ldr	r3, [r1]
	ldr	r2, [r2, #8]
	ldr	r3, [r3, #8]
	cmp	r2, r3
	blt	.L9
	movgt	r0, #1
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L9:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_compare_pic_by_lt_pic_num_asc, .-MVC_compare_pic_by_lt_pic_num_asc
	.align	2
	.global	MVC_compare_fs_by_frame_num_desc
	.type	MVC_compare_fs_by_frame_num_desc, %function
MVC_compare_fs_by_frame_num_desc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r0]
	ldr	r3, [r1]
	ldr	r2, [r2, #24]
	ldr	r3, [r3, #24]
	cmp	r2, r3
	blt	.L12
	mvngt	r0, #0
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L12:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_compare_fs_by_frame_num_desc, .-MVC_compare_fs_by_frame_num_desc
	.align	2
	.global	MVC_compare_fs_by_lt_pic_idx_asc
	.type	MVC_compare_fs_by_lt_pic_idx_asc, %function
MVC_compare_fs_by_lt_pic_idx_asc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r0]
	ldr	r3, [r1]
	ldr	r2, [r2, #28]
	ldr	r3, [r3, #28]
	cmp	r2, r3
	bcc	.L15
	movhi	r0, #1
	movls	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L15:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_compare_fs_by_lt_pic_idx_asc, .-MVC_compare_fs_by_lt_pic_idx_asc
	.align	2
	.global	MVC_compare_pic_by_poc_asc
	.type	MVC_compare_pic_by_poc_asc, %function
MVC_compare_pic_by_poc_asc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r0]
	ldr	r3, [r1]
	ldr	r2, [r2, #16]
	ldr	r3, [r3, #16]
	cmp	r2, r3
	blt	.L18
	movgt	r0, #1
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L18:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_compare_pic_by_poc_asc, .-MVC_compare_pic_by_poc_asc
	.align	2
	.global	MVC_compare_pic_by_poc_desc
	.type	MVC_compare_pic_by_poc_desc, %function
MVC_compare_pic_by_poc_desc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r0]
	ldr	r3, [r1]
	ldr	r2, [r2, #16]
	ldr	r3, [r3, #16]
	cmp	r2, r3
	blt	.L21
	mvngt	r0, #0
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L21:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_compare_pic_by_poc_desc, .-MVC_compare_pic_by_poc_desc
	.align	2
	.global	MVC_compare_fs_by_poc_asc
	.type	MVC_compare_fs_by_poc_asc, %function
MVC_compare_fs_by_poc_asc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r0]
	ldr	r3, [r1]
	ldr	r2, [r2, #32]
	ldr	r3, [r3, #32]
	cmp	r2, r3
	blt	.L24
	movgt	r0, #1
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L24:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_compare_fs_by_poc_asc, .-MVC_compare_fs_by_poc_asc
	.align	2
	.global	MVC_compare_fs_by_poc_desc
	.type	MVC_compare_fs_by_poc_desc, %function
MVC_compare_fs_by_poc_desc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r0]
	ldr	r3, [r1]
	ldr	r2, [r2, #32]
	ldr	r3, [r3, #32]
	cmp	r2, r3
	blt	.L27
	mvngt	r0, #0
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L27:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_compare_fs_by_poc_desc, .-MVC_compare_fs_by_poc_desc
	.align	2
	.type	MVC_SetFrmRepeatCount.part.2, %function
MVC_SetFrmRepeatCount.part.2:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	ip, r0, #11075584
	ldr	lr, [r0, #136]
	add	ip, ip, #45056
	ldr	r3, [r0, #132]
	ldr	r2, [ip, #2888]
	mov	r3, r3, lsr #1
	add	r2, r2, lr, lsr #1
	add	ip, r2, #1
	cmp	r3, ip
	movcc	r3, #0
	strcc	r3, [r1, #16]
	ldmccfd	sp, {fp, sp, pc}
	sub	r3, r3, #1
	rsb	r3, r2, r3
	cmp	r3, #1
	movhi	r3, #2
	movls	r3, #1
	strhi	r3, [r1, #16]
	strls	r3, [r1, #16]
	ldrhi	r3, [r0, #136]
	ldrls	r3, [r0, #136]
	addhi	r3, r3, #4
	addls	r3, r3, #2
	str	r3, [r0, #136]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_SetFrmRepeatCount.part.2, .-MVC_SetFrmRepeatCount.part.2
	.align	2
	.type	MVC_CombinePacket.part.13, %function
MVC_CombinePacket.part.13:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	r1, .L33
	mov	r4, r0
	mov	r0, #7
	bl	dprint_vfmw
	ldr	ip, [r4, #232]
	ldr	r1, .L33+4
	mov	r0, #7
	mov	r5, #0
	ldr	lr, [ip, #40]
	ldr	r3, [ip, #44]
	ldr	r2, [ip, #16]
	str	lr, [sp, #4]
	ldr	ip, [ip, #12]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r4, #232]
	ldr	ip, .L33+8
	ldr	r2, [r3, #12]
	ldr	r0, [r3, #36]
	ldr	r1, [r3, #8]
	rsb	r0, r2, r0
	ldr	r3, [ip, #52]
	blx	r3
	ldr	r3, [r4, #232]
	mov	ip, #1
	ldr	r1, .L33+12
	mov	r0, #7
	ldr	r2, [r3, #60]
	ldr	r6, [r3, #32]
	str	r2, [r3, #32]
	ldr	r3, [r4, #232]
	str	r5, [r3, #24]
	ldr	r3, [r4, #232]
	ldr	lr, [r3, #12]
	ldr	r2, [r3, #36]
	rsb	r2, lr, r2
	str	r2, [r3, #8]
	ldr	r3, [r4, #232]
	ldr	lr, [r3, #12]
	ldr	r2, [r3, #44]
	rsb	r2, lr, r2
	str	r2, [r3, #16]
	ldr	r3, [r4, #232]
	ldr	lr, [r3, #40]
	ldr	r2, [r3, #12]
	add	r2, r2, lr
	str	r2, [r3, #12]
	ldr	r3, [r4, #232]
	str	ip, [r3, #68]
	ldr	r2, [r4, #232]
	ldr	r3, [r2, #12]
	ldr	r2, [r2, #16]
	bl	dprint_vfmw
	mov	r1, r6
	ldr	r0, [r4, #120]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #232]
	str	r5, [r3, #36]
	ldr	r3, [r4, #232]
	str	r5, [r3, #52]
	ldr	r3, [r4, #232]
	str	r5, [r3, #40]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L34:
	.align	2
.L33:
	.word	.LC0
	.word	.LC1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	UNWIND(.fnend)
	.size	MVC_CombinePacket.part.13, .-MVC_CombinePacket.part.13
	.align	2
	.global	mvc_ue_v
	.type	mvc_ue_v, %function
mvc_ue_v:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r8, r0, #548
	mov	r6, r0
	mov	r7, r1
	mov	r1, #32
	mov	r0, r8
	bl	BsShow
	mov	r5, r0
	bl	ZerosMS_32
	cmp	r0, #15
	mov	r4, r0
	bls	.L39
	cmp	r0, #31
	bls	.L40
	mvn	r5, #0
	mov	r8, #32
	mov	r3, #1
	strb	r3, [r6, #10]
.L37:
	ldr	r6, [r6, #232]
	mov	r2, r7
	mov	r3, r5
	ldr	r1, .L41
	mov	r0, #21
	ldr	lr, [r6, #64]
	add	r4, lr, r8
	str	r4, [r6, #64]
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L39:
	mov	r4, r0, asl #1
	mov	r0, r8
	add	r8, r4, #1
	rsb	r4, r4, #31
	mov	r4, r5, lsr r4
	mov	r1, r8
	sub	r5, r4, #1
	bl	BsSkip
	b	.L37
.L40:
	add	r5, r0, #1
	mov	r1, r0
	mov	r0, r8
	bl	BsSkip
	mov	r1, r5
	mov	r0, r8
	bl	BsShow
	mov	r1, r5
	sub	r5, r0, #1
	mov	r0, r8
	bl	BsSkip
	mov	ip, r4, asl #1
	add	r8, ip, #1
	b	.L37
.L42:
	.align	2
.L41:
	.word	.LC3
	UNWIND(.fnend)
	.size	mvc_ue_v, .-mvc_ue_v
	.align	2
	.global	mvc_se_v
	.type	mvc_se_v, %function
mvc_se_v:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r7, r0, #548
	mov	r8, r0
	mov	r6, r1
	mov	r1, #32
	mov	r0, r7
	bl	BsShow
	mov	r4, r0
	bl	ZerosMS_32
	cmp	r0, #15
	mov	r5, r0
	bhi	.L44
	mov	r5, r0, asl #1
	mov	r0, r7
	rsb	r3, r5, #31
	add	r5, r5, #1
	mov	r3, r4, lsr r3
	and	r2, r3, #1
	mov	r1, r5
	rsb	r4, r2, #0
	eor	r3, r4, r3, lsr #1
	add	r4, r3, r2
	bl	BsSkip
.L45:
	ldr	lr, [r8, #232]
	mov	r2, r6
	mov	r3, r4
	ldr	r1, .L48
	mov	r0, #21
	ldr	ip, [lr, #64]
	add	r5, ip, r5
	str	r5, [lr, #64]
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L44:
	cmp	r0, #31
	bls	.L47
	mov	r3, #1
	mvn	r4, #-2147483648
	mov	r5, #32
	strb	r3, [r8, #10]
	b	.L45
.L47:
	mov	r1, r0
	mov	r0, r7
	bl	BsSkip
	mov	r1, r5
	mov	r0, r7
	mov	r5, r5, asl #1
	bl	BsGet
	mov	r1, #1
	add	r5, r5, #1
	mov	r9, r0
	mov	r0, r7
	bl	BsGet
	and	r0, r0, #1
	rsb	r4, r0, #0
	eor	r9, r9, r4
	add	r4, r9, r0
	b	.L45
.L49:
	.align	2
.L48:
	.word	.LC3
	UNWIND(.fnend)
	.size	mvc_se_v, .-mvc_se_v
	.align	2
	.global	mvc_u_v
	.type	mvc_u_v, %function
mvc_u_v:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r5, r0
	add	r0, r0, #548
	mov	r6, r1
	mov	r7, r2
	bl	BsGet
	ldr	lr, [r5, #232]
	mov	r2, r7
	ldr	r1, .L51
	ldr	ip, [lr, #64]
	add	ip, ip, r6
	str	ip, [lr, #64]
	mov	r4, r0
	mov	r3, r0
	mov	r0, #21
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L52:
	.align	2
.L51:
	.word	.LC3
	UNWIND(.fnend)
	.size	mvc_u_v, .-mvc_u_v
	.align	2
	.global	mvc_u_1
	.type	mvc_u_1, %function
mvc_u_1:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r5, r0
	mov	r6, r1
	add	r0, r0, #548
	mov	r1, #1
	bl	BsGet
	ldr	lr, [r5, #232]
	mov	r2, r6
	ldr	r1, .L54
	ldr	ip, [lr, #64]
	add	ip, ip, #1
	str	ip, [lr, #64]
	mov	r4, r0
	mov	r3, r0
	mov	r0, #21
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L55:
	.align	2
.L54:
	.word	.LC3
	UNWIND(.fnend)
	.size	mvc_u_1, .-mvc_u_1
	.align	2
	.global	MVC_GetMinPOC
	.type	MVC_GetMinPOC, %function
MVC_GetMinPOC:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r10, r0, #11075584
	add	r10, r10, #45056
	mov	r9, r3
	mov	r8, r2
	mvn	r3, #-2147483648
	mvn	r2, #0
	str	r2, [r9]
	str	r3, [r8]
	mov	r6, r0
	ldr	r3, [r10, #2888]
	mov	r7, r1
	ldr	r2, [r10, #2892]
	cmp	r2, r3
	strhi	r3, [r10, #2892]
	cmp	r3, #0
	beq	.L63
	movw	r5, #47748
	mvn	r3, #0
	movt	r5, 169
	str	r3, [fp, #-48]
	add	r5, r0, r5
	mov	r4, #0
	b	.L62
.L60:
	ldr	r1, [r8]
	ldr	r2, [r3, #32]
	cmp	r1, r2
	ble	.L59
	ldrb	r1, [r3, #5]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L59
	ldrb	r1, [r0, #1]	@ zero_extendqisi2
	sub	r1, r1, #1
	cmp	r1, #1
	bls	.L78
.L59:
	ldr	r3, [r10, #2888]
	add	r4, r4, #1
	cmp	r3, r4
	bls	.L63
.L62:
	ldr	r3, [r5, #4]!
	cmp	r3, #0
	beq	.L59
	ldrsb	r1, [r3, #6]
	ldr	r0, [r6, #120]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L59
	cmn	r7, #1
	ldr	r3, [r5]
	bne	.L60
	ldrb	r2, [r3, #5]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L59
	ldrb	r2, [r0, #1]	@ zero_extendqisi2
	sub	r2, r2, #1
	cmp	r2, #1
	bhi	.L59
	ldr	r1, [r8]
	ldr	r2, [r3, #32]
	cmp	r1, r2
	ble	.L61
	str	r2, [r8]
	str	r4, [r9]
	add	r4, r4, #1
	ldr	r3, [r5]
	ldr	r3, [r3, #56]
	str	r3, [fp, #-48]
	ldr	r3, [r10, #2888]
	cmp	r3, r4
	bhi	.L62
.L63:
	ldr	r0, [r9]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L78:
	ldr	r3, [r3, #56]
	cmp	r7, r3
	streq	r2, [r8]
	streq	r4, [r9]
	b	.L59
.L61:
	bne	.L59
	ldr	r3, [r3, #56]
	ldr	r2, [fp, #-48]
	cmp	r3, r2
	strlt	r4, [r9]
	ldrlt	r3, [r5]
	ldrlt	r3, [r3, #56]
	strlt	r3, [fp, #-48]
	b	.L59
	UNWIND(.fnend)
	.size	MVC_GetMinPOC, .-MVC_GetMinPOC
	.align	2
	.global	MVC_FrameStoreRefFlg
	.type	MVC_FrameStoreRefFlg, %function
MVC_FrameStoreRefFlg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldrb	r0, [r0, #3]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_FrameStoreRefFlg, .-MVC_FrameStoreRefFlg
	.align	2
	.global	MVC_NonLongTermRefFlg
	.type	MVC_NonLongTermRefFlg, %function
MVC_NonLongTermRefFlg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldrb	r3, [r0, #3]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L95
	tst	r3, #1
	bne	.L96
.L84:
	and	r3, r3, #2
	ands	r3, r3, #255
	beq	.L88
.L85:
	ldrb	r0, [r0, #777]	@ zero_extendqisi2
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
.L88:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L96:
	ldrb	r2, [r0, #741]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L84
.L89:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L95:
	ldrb	r3, [r0, #705]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L89
	ldrb	r3, [r0, #741]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L85
	b	.L89
	UNWIND(.fnend)
	.size	MVC_NonLongTermRefFlg, .-MVC_NonLongTermRefFlg
	.align	2
	.global	MVC_ShortTermRefFlg
	.type	MVC_ShortTermRefFlg, %function
MVC_ShortTermRefFlg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldrb	r3, [r0, #3]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L112
	tst	r3, #1
	bne	.L113
.L101:
	and	r3, r3, #2
	ands	r3, r3, #255
	beq	.L105
.L102:
	ldr	r0, [r0, #776]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	sub	r0, r0, #65536
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
.L105:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L113:
	ldr	r2, [r0, #740]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #65536
	bne	.L101
.L106:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L112:
	ldr	r3, [r0, #704]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	beq	.L106
	ldr	r3, [r0, #740]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	bne	.L102
	b	.L106
	UNWIND(.fnend)
	.size	MVC_ShortTermRefFlg, .-MVC_ShortTermRefFlg
	.align	2
	.global	MVC_LongTermRefFlg
	.type	MVC_LongTermRefFlg, %function
MVC_LongTermRefFlg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldrb	r3, [r0, #3]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L129
	tst	r3, #1
	bne	.L130
.L118:
	and	r3, r3, #2
	ands	r3, r3, #255
	beq	.L122
.L119:
	ldr	r0, [r0, #776]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	sub	r0, r0, #256
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
.L122:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L130:
	ldr	r2, [r0, #740]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #256
	bne	.L118
.L123:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L129:
	ldr	r3, [r0, #704]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #256
	beq	.L123
	ldr	r3, [r0, #740]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #256
	bne	.L119
	b	.L123
	UNWIND(.fnend)
	.size	MVC_LongTermRefFlg, .-MVC_LongTermRefFlg
	.align	2
	.global	MVC_UpdateLTReflist
	.type	MVC_UpdateLTReflist, %function
MVC_UpdateLTReflist:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r3, r0, #11075584
	add	r3, r3, #45056
	mov	r7, r0
	str	r3, [fp, #-48]
	ldr	r10, [r3, #2888]
	cmp	r10, #0
	beq	.L132
	movw	r8, #47748
	add	r9, r0, #11141120
	movt	r8, 169
	mov	r4, #0
	add	r9, r9, #12288
	add	r8, r0, r8
	mov	r6, r4
.L134:
	ldr	r5, [r8, #4]!
	add	r6, r6, #1
	cmp	r5, #0
	mov	r0, r5
	beq	.L133
	bl	MVC_LongTermRefFlg
	cmp	r0, #0
	beq	.L133
	ldr	r2, [r9, #3856]
	ldr	r1, [r5, #56]
	cmp	r1, r2
	movweq	r2, #28354
	movteq	r2, 42
	addeq	r2, r4, r2
	addeq	r4, r4, #1
	streq	r5, [r7, r2, asl #2]
.L133:
	cmp	r6, r10
	bne	.L134
	ldr	r3, [fp, #-48]
	cmp	r4, r10
	str	r4, [r3, #2900]
	bcs	.L131
	movw	r0, #28353
	mov	r2, #0
	movt	r0, 42
	add	r0, r4, r0
	add	r0, r7, r0, lsl #2
.L137:
	add	r4, r4, #1
	str	r2, [r0, #4]!
	cmp	r4, r10
	bne	.L137
.L131:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L132:
	ldr	r3, [fp, #-48]
	str	r10, [r3, #2900]
	b	.L131
	UNWIND(.fnend)
	.size	MVC_UpdateLTReflist, .-MVC_UpdateLTReflist
	.align	2
	.global	MVC_UpdateReflist
	.type	MVC_UpdateReflist, %function
MVC_UpdateReflist:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r3, r0, #11075584
	add	r3, r3, #45056
	mov	r7, r0
	str	r3, [fp, #-48]
	ldr	r10, [r3, #2888]
	cmp	r10, #0
	beq	.L148
	movw	r8, #47748
	add	r9, r0, #11141120
	movt	r8, 169
	mov	r4, #0
	add	r9, r9, #12288
	add	r8, r0, r8
	mov	r6, r4
.L150:
	ldr	r5, [r8, #4]!
	add	r6, r6, #1
	cmp	r5, #0
	mov	r0, r5
	beq	.L149
	bl	MVC_ShortTermRefFlg
	cmp	r0, #0
	beq	.L149
	ldr	r2, [r9, #3856]
	ldr	r1, [r5, #56]
	cmp	r1, r2
	movweq	r2, #28338
	movteq	r2, 42
	addeq	r2, r4, r2
	addeq	r4, r4, #1
	streq	r5, [r7, r2, asl #2]
.L149:
	cmp	r6, r10
	bne	.L150
	ldr	r3, [fp, #-48]
	cmp	r4, r10
	str	r4, [r3, #2896]
	bcs	.L147
	movw	r0, #28337
	mov	r2, #0
	movt	r0, 42
	add	r0, r4, r0
	add	r0, r7, r0, lsl #2
.L153:
	add	r4, r4, #1
	str	r2, [r0, #4]!
	cmp	r4, r10
	bne	.L153
.L147:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L148:
	ldr	r3, [fp, #-48]
	str	r10, [r3, #2896]
	b	.L147
	UNWIND(.fnend)
	.size	MVC_UpdateReflist, .-MVC_UpdateReflist
	.align	2
	.global	MVC_GetPicNumX
	.type	MVC_GetPicNumX, %function
MVC_GetPicNumX:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldrb	r3, [r0, #3]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r0, #656]
	mvn	r0, r1
	movne	r3, r3, asl #1
	addne	r3, r3, #1
	add	r0, r0, r3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_GetPicNumX, .-MVC_GetPicNumX
	.align	2
	.global	MVC_UnMarkFrameStoreRef
	.type	MVC_UnMarkFrameStoreRef, %function
MVC_UnMarkFrameStoreRef:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldrb	r2, [r1, #2]	@ zero_extendqisi2
	mov	r3, r1
	tst	r2, #1
	beq	.L167
	ldrb	r1, [r1, #3]	@ zero_extendqisi2
	mov	ip, #0
	strb	ip, [r3, #741]
	and	r1, r1, #2
	strb	ip, [r3, #742]
	strb	r1, [r3, #3]
.L167:
	tst	r2, #2
	beq	.L168
	ldrb	r1, [r3, #3]	@ zero_extendqisi2
	mov	ip, #0
	strb	ip, [r3, #777]
	and	r1, r1, #1
	strb	ip, [r3, #778]
	strb	r1, [r3, #3]
.L168:
	cmp	r2, #3
	ldrsb	r1, [r3, #6]
	moveq	r2, #0
	streqb	r2, [r3, #706]
	streqb	r2, [r3, #705]
	mov	r2, #0
	strb	r2, [r3, #3]
	ldr	r0, [r0, #120]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	FSP_SetRef
	UNWIND(.fnend)
	.size	MVC_UnMarkFrameStoreRef, .-MVC_UnMarkFrameStoreRef
	.align	2
	.global	MVC_UnMarkLTFrmByFrmIdx
	.type	MVC_UnMarkLTFrmByFrmIdx, %function
MVC_UnMarkLTFrmByFrmIdx:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #11075584
	add	r3, r3, #45056
	ldr	r4, [r3, #2900]
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, r6, fp, sp, pc}
	movw	ip, #47876
	add	r6, r0, #11141120
	movt	ip, 169
	add	r6, r6, #12288
	add	ip, r0, ip
	mov	r3, #0
	b	.L179
.L178:
	cmp	r3, r4
	beq	.L184
.L179:
	ldr	r2, [ip, #4]!
	add	r3, r3, #1
	ldr	lr, [r2, #28]
	cmp	lr, r1
	bne	.L178
	ldr	r5, [r2, #56]
	ldr	lr, [r6, #3856]
	cmp	r5, lr
	bne	.L178
	mov	r1, r2
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	MVC_UnMarkFrameStoreRef
.L184:
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_UnMarkLTFrmByFrmIdx, .-MVC_UnMarkLTFrmByFrmIdx
	.align	2
	.global	MVC_UnMarkLTFldByFrmIdx
	.type	MVC_UnMarkLTFldByFrmIdx, %function
MVC_UnMarkLTFldByFrmIdx:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	ip, r0, #11075584
	add	ip, ip, #45056
	ldr	r6, [ip, #2900]
	cmp	r6, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	movw	r4, #47876
	add	r8, r0, #11141120
	movt	r4, 169
	add	r8, r8, #12288
	add	r4, r0, r4
	mov	ip, #0
	b	.L189
.L187:
	cmp	ip, r6
	beq	.L203
.L189:
	ldr	lr, [r4, #4]!
	add	ip, ip, #1
	ldr	r5, [lr, #28]
	cmp	r5, r3
	bne	.L187
	ldr	r7, [lr, #56]
	ldr	r5, [r8, #3856]
	cmp	r7, r5
	bne	.L187
	cmp	r2, #1
	ldreqb	r5, [lr, #777]	@ zero_extendqisi2
	beq	.L202
	cmp	r2, #2
	bne	.L187
	ldrb	r5, [lr, #741]	@ zero_extendqisi2
.L202:
	clz	r5, r5
	mov	r5, r5, lsr #5
	cmp	lr, r1
	orrne	r5, r5, #1
	cmp	r5, #0
	beq	.L187
	mov	r1, lr
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	MVC_UnMarkFrameStoreRef
.L203:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_UnMarkLTFldByFrmIdx, .-MVC_UnMarkLTFldByFrmIdx
	.align	2
	.global	MVC_UnMarkSTRef
	.type	MVC_UnMarkSTRef, %function
MVC_UnMarkSTRef:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L205
	add	ip, r0, #11075584
	ldr	r1, [r1, #656]
	add	ip, ip, #45056
	sub	r1, r1, #1
	ldr	r4, [ip, #2896]
	rsb	r2, r2, r1
	cmp	r4, #0
	beq	.L234
	movw	ip, #47812
	add	r5, r0, #11141120
	movt	ip, 169
	add	r5, r5, #12288
	add	ip, r0, ip
	b	.L211
.L210:
	cmp	r3, r4
	beq	.L235
.L211:
	ldr	r1, [ip, #4]!
	add	r3, r3, #1
	ldr	lr, [r1, #716]
	cmp	lr, r2
	bne	.L210
	ldrb	lr, [r1, #3]	@ zero_extendqisi2
	cmp	lr, #3
	bne	.L210
	ldr	lr, [r1, #704]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	bne	.L210
	ldr	r6, [r1, #56]
	ldr	lr, [r5, #3856]
	cmp	r6, lr
	bne	.L210
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	MVC_UnMarkFrameStoreRef
.L205:
	add	r3, r0, #11075584
	ldr	r1, [r1, #656]
	add	r3, r3, #45056
	ldr	r5, [r3, #2896]
	rsb	r2, r2, r1, lsl #1
	cmp	r5, #0
	beq	.L236
	movw	r4, #47812
	add	r7, r0, #11141120
	movt	r4, 169
	add	r7, r7, #12288
	add	r4, r0, r4
	mov	ip, #0
	b	.L216
.L212:
	tst	r3, #2
	beq	.L214
	ldr	r3, [r1, #776]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	beq	.L237
.L214:
	add	ip, ip, #1
	cmp	ip, r5
	beq	.L238
.L216:
	ldr	r1, [r4, #4]!
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	ands	r6, r3, #1
	beq	.L212
	ldr	lr, [r1, #740]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	bne	.L212
	ldr	r8, [r1, #56]
	ldr	lr, [r7, #3856]
	cmp	r8, lr
	bne	.L212
	ldr	lr, [r1, #752]
	cmp	lr, r2
	bne	.L212
	add	r2, r0, ip, lsl #2
	and	r3, r3, #2
	add	r2, r2, #11075584
	strb	r3, [r1, #3]
	add	r2, r2, #45056
	mov	r1, #0
	ldr	r3, [r2, #2760]
	strb	r1, [r3, #742]
	ldr	r3, [r2, #2760]
	ldrb	ip, [r3, #704]	@ zero_extendqisi2
	cmp	ip, #3
	cmpne	ip, r1
	streqb	r1, [r3, #706]
	ldreq	r3, [r2, #2760]
	streqb	r1, [r3, #705]
	ldreq	r3, [r2, #2760]
	ldrb	ip, [r3, #3]	@ zero_extendqisi2
	cmp	ip, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	ldr	r1, [r3, #48]
	mov	r2, ip
	add	r1, r0, r1, lsl #2
	str	ip, [r1, #148]
	ldrsb	r1, [r3, #6]
	b	.L231
.L237:
	ldr	lr, [r1, #56]
	ldr	r3, [r7, #3856]
	cmp	lr, r3
	bne	.L214
	ldr	r3, [r1, #788]
	cmp	r3, r2
	bne	.L214
	add	r3, r0, ip, lsl #2
	strb	r6, [r1, #3]
	add	r3, r3, #11075584
	mov	r2, #0
	add	r3, r3, #45056
	ldr	r1, [r3, #2760]
	strb	r2, [r1, #778]
	ldr	r1, [r3, #2760]
	ldrb	ip, [r1, #704]	@ zero_extendqisi2
	cmp	ip, #3
	cmpne	ip, r2
	streqb	r2, [r1, #706]
	ldreq	r1, [r3, #2760]
	streqb	r2, [r1, #705]
	ldreq	r1, [r3, #2760]
	ldrb	ip, [r1, #3]	@ zero_extendqisi2
	cmp	ip, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	ldr	r3, [r1, #48]
	mov	r2, ip
	add	r3, r0, r3, lsl #2
	str	ip, [r3, #148]
	ldrsb	r1, [r1, #6]
.L231:
	ldr	r0, [r0, #120]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	FSP_SetRef
.L238:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L235:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L234:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L236:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_UnMarkSTRef, .-MVC_UnMarkSTRef
	.align	2
	.global	MVC_UnMarkLTRef
	.type	MVC_UnMarkLTRef, %function
MVC_UnMarkLTRef:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L240
	add	r3, r0, #11075584
	add	r3, r3, #45056
	ldr	r5, [r3, #2900]
	cmp	r5, #0
	beq	.L269
	movw	r4, #47876
	add	r7, r0, #11141120
	movt	r4, 169
	add	r7, r7, #12288
	add	r4, r0, r4
	mov	ip, #0
	b	.L249
.L245:
	tst	r3, #2
	beq	.L247
	ldr	r3, [r1, #776]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #256
	beq	.L270
.L247:
	add	ip, ip, #1
	cmp	ip, r5
	beq	.L271
.L249:
	ldr	r1, [r4, #4]!
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	ands	r6, r3, #1
	beq	.L245
	ldr	lr, [r1, #740]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #256
	bne	.L245
	ldr	r8, [r1, #56]
	ldr	lr, [r7, #3856]
	cmp	r8, lr
	bne	.L245
	ldr	lr, [r1, #748]
	cmp	r2, lr
	bne	.L245
	add	r2, r0, ip, lsl #2
	and	r3, r3, #2
	add	r2, r2, #11075584
	strb	r3, [r1, #3]
	add	r2, r2, #45056
	mov	r1, #0
	ldr	r3, [r2, #2824]
	strb	r1, [r3, #741]
	ldr	r3, [r2, #2824]
	ldrb	ip, [r3, #704]	@ zero_extendqisi2
	cmp	ip, #3
	cmpne	ip, r1
	streqb	r1, [r3, #706]
	ldreq	r3, [r2, #2824]
	streqb	r1, [r3, #705]
	ldreq	r3, [r2, #2824]
	ldrb	ip, [r3, #3]	@ zero_extendqisi2
	cmp	ip, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	ldr	r1, [r3, #48]
	mov	r2, ip
	add	r1, r0, r1, lsl #2
	str	ip, [r1, #148]
	ldrsb	r1, [r3, #6]
	b	.L266
.L240:
	add	r1, r0, #11075584
	add	r1, r1, #45056
	ldr	r4, [r1, #2900]
	cmp	r4, #0
	beq	.L272
	movw	ip, #47876
	add	r5, r0, #11141120
	movt	ip, 169
	add	r5, r5, #12288
	add	ip, r0, ip
	b	.L251
.L250:
	cmp	r3, r4
	beq	.L273
.L251:
	ldr	r1, [ip, #4]!
	add	r3, r3, #1
	ldr	lr, [r1, #712]
	cmp	lr, r2
	bne	.L250
	ldrb	lr, [r1, #3]	@ zero_extendqisi2
	cmp	lr, #3
	bne	.L250
	ldr	lr, [r1, #704]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #256
	bne	.L250
	ldr	r6, [r1, #56]
	ldr	lr, [r5, #3856]
	cmp	r6, lr
	bne	.L250
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	MVC_UnMarkFrameStoreRef
.L270:
	ldr	lr, [r1, #56]
	ldr	r3, [r7, #3856]
	cmp	lr, r3
	bne	.L247
	ldr	r3, [r1, #784]
	cmp	r2, r3
	bne	.L247
	add	r3, r0, ip, lsl #2
	strb	r6, [r1, #3]
	add	r3, r3, #11075584
	mov	r2, #0
	add	r3, r3, #45056
	ldr	r1, [r3, #2824]
	strb	r2, [r1, #777]
	ldr	r1, [r3, #2824]
	ldrb	ip, [r1, #704]	@ zero_extendqisi2
	cmp	ip, #3
	cmpne	ip, r2
	streqb	r2, [r1, #706]
	ldreq	r1, [r3, #2824]
	streqb	r2, [r1, #705]
	ldreq	r1, [r3, #2824]
	ldrb	ip, [r1, #3]	@ zero_extendqisi2
	cmp	ip, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	ldr	r3, [r1, #48]
	mov	r2, ip
	add	r3, r0, r3, lsl #2
	str	ip, [r3, #148]
	ldrsb	r1, [r1, #6]
.L266:
	ldr	r0, [r0, #120]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	FSP_SetRef
.L273:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L271:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L272:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L269:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_UnMarkLTRef, .-MVC_UnMarkLTRef
	.align	2
	.global	MVC_MarkPicLTRef
	.type	MVC_MarkPicLTRef, %function
MVC_MarkPicLTRef:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldrb	r6, [r3, #3]	@ zero_extendqisi2
	add	r3, r0, #11075584
	add	r3, r3, #45056
	cmp	r6, #0
	beq	.L275
	ldr	r7, [r3, #2896]
	cmp	r7, #0
	beq	.L304
	movw	r5, #47812
	add	r8, r0, #11141120
	movt	r5, 169
	add	r8, r8, #12288
	add	r5, r0, r5
	mov	ip, #0
	b	.L289
.L281:
	tst	r4, #2
	beq	.L284
	ldr	lr, [r3, #776]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	beq	.L305
.L284:
	add	ip, ip, #1
	cmp	ip, r7
	beq	.L306
.L289:
	ldr	r3, [r5, #4]!
	ldrb	r4, [r3, #3]	@ zero_extendqisi2
	tst	r4, #1
	beq	.L281
	ldr	lr, [r3, #740]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	bne	.L281
	ldr	lr, [r3, #752]
	cmp	lr, r2
	bne	.L281
	ldr	r9, [r3, #56]
	ldr	lr, [r8, #3856]
	cmp	r9, lr
	bne	.L281
	ldrb	lr, [r3, #777]	@ zero_extendqisi2
	cmp	lr, #1
	bne	.L285
	ldr	lr, [r3, #28]
	cmp	lr, r1
	bne	.L284
.L285:
	add	r0, r0, ip, lsl #2
	str	r1, [r3, #28]
	add	r3, r0, #11075584
	sub	r6, r6, #1
	add	r3, r3, #45056
	clz	r6, r6
	mov	ip, #1
	mov	r0, #0
	ldr	r2, [r3, #2760]
	mov	r6, r6, lsr #5
	add	r1, r6, r1, lsl #1
	str	r1, [r2, #748]
	ldr	r2, [r3, #2760]
	strb	ip, [r2, #741]
	ldr	r2, [r3, #2760]
	strb	r0, [r2, #742]
	ldr	r2, [r3, #2760]
	ldrb	r1, [r2, #704]	@ zero_extendqisi2
	cmp	r1, #3
	cmpne	r1, r0
	bne	.L307
	ldrb	r1, [r2, #777]	@ zero_extendqisi2
	ldrb	r0, [r2, #741]	@ zero_extendqisi2
	cmp	r1, r0
	streqb	r1, [r2, #705]
	ldreq	r3, [r3, #2760]
	ldreqb	r2, [r3, #742]	@ zero_extendqisi2
	streqb	r2, [r3, #706]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L275:
	ldr	r4, [r3, #2896]
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	movw	ip, #47812
	add	r5, r0, #11141120
	movt	ip, 169
	add	r5, r5, #12288
	add	ip, r0, ip
	b	.L280
.L279:
	add	r6, r6, #1
	cmp	r6, r4
	beq	.L308
.L280:
	ldr	r3, [ip, #4]!
	ldrb	lr, [r3, #3]	@ zero_extendqisi2
	cmp	lr, #3
	bne	.L279
	ldr	lr, [r3, #704]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	bne	.L279
	ldr	lr, [r3, #716]
	cmp	lr, r2
	bne	.L279
	ldr	r7, [r3, #56]
	ldr	lr, [r5, #3856]
	cmp	r7, lr
	bne	.L279
	add	r6, r0, r6, lsl #2
	str	r1, [r3, #28]
	add	r3, r6, #11075584
	mov	r0, #1
	add	r3, r3, #45056
	mov	r2, #0
	ldr	ip, [r3, #2760]
	str	r1, [ip, #712]
	ldr	r1, [r3, #2760]
	strb	r0, [r1, #705]
	ldr	r1, [r3, #2760]
	strb	r0, [r1, #741]
	ldr	r1, [r3, #2760]
	strb	r0, [r1, #777]
	ldr	r1, [r3, #2760]
	strb	r2, [r1, #706]
	ldr	r1, [r3, #2760]
	strb	r2, [r1, #742]
	ldr	r3, [r3, #2760]
	strb	r2, [r3, #778]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L305:
	ldr	lr, [r3, #788]
	cmp	lr, r2
	bne	.L284
	ldr	r4, [r3, #56]
	ldr	lr, [r8, #3856]
	cmp	r4, lr
	bne	.L284
	ldrb	lr, [r3, #741]	@ zero_extendqisi2
	cmp	lr, #1
	bne	.L288
	ldr	lr, [r3, #28]
	cmp	lr, r1
	bne	.L284
.L288:
	add	r0, r0, ip, lsl #2
	str	r1, [r3, #28]
	add	r3, r0, #11075584
	sub	r6, r6, #2
	add	r3, r3, #45056
	clz	r6, r6
	mov	ip, #1
	mov	r0, #0
	ldr	r2, [r3, #2760]
	mov	r6, r6, lsr #5
	add	r1, r6, r1, lsl #1
	str	r1, [r2, #784]
	ldr	r2, [r3, #2760]
	strb	ip, [r2, #777]
	ldr	r2, [r3, #2760]
	strb	r0, [r2, #778]
	ldr	r2, [r3, #2760]
	ldrb	r1, [r2, #704]	@ zero_extendqisi2
	cmp	r1, #3
	cmpne	r1, r0
	bne	.L309
	ldrb	r1, [r2, #777]	@ zero_extendqisi2
	ldrb	r0, [r2, #741]	@ zero_extendqisi2
	cmp	r1, r0
	streqb	r1, [r2, #705]
	ldreq	r3, [r3, #2760]
	ldreqb	r2, [r3, #778]	@ zero_extendqisi2
	streqb	r2, [r3, #706]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L306:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L308:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L307:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L309:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L304:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_MarkPicLTRef, .-MVC_MarkPicLTRef
	.align	2
	.global	MVC_MarkSTToLTRef
	.type	MVC_MarkSTToLTRef, %function
MVC_MarkSTToLTRef:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r6, r1
	ldrb	r1, [r1, #3]	@ zero_extendqisi2
	mov	r8, r3
	mov	r7, r0
	cmp	r1, #0
	bne	.L311
	ldr	r5, [r6, #656]
	mov	r1, r3
	sub	r5, r5, #1
	rsb	r5, r2, r5
	bl	MVC_UnMarkLTFrmByFrmIdx
.L312:
	mov	r3, r6
	mov	r2, r5
	mov	r1, r8
	mov	r0, r7
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	MVC_MarkPicLTRef
.L311:
	add	r3, r0, #11075584
	ldr	r5, [r6, #656]
	add	r3, r3, #45056
	ldr	r1, [r3, #2896]
	rsb	r5, r2, r5, lsl #1
	cmp	r1, #0
	beq	.L312
	movw	r2, #47812
	add	r0, r0, #11141120
	movt	r2, 169
	add	r0, r0, #12288
	add	r2, r7, r2
	mov	lr, #0
	b	.L315
.L313:
	tst	r3, #2
	beq	.L314
	ldr	r3, [ip, #776]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	beq	.L326
.L314:
	cmp	lr, r1
	beq	.L312
.L315:
	ldr	ip, [r2, #4]!
	add	lr, lr, #1
	ldrb	r3, [ip, #3]	@ zero_extendqisi2
	tst	r3, #1
	beq	.L313
	ldr	r4, [ip, #740]
	bic	r4, r4, #-16777216
	bic	r4, r4, #255
	cmp	r4, #65536
	bne	.L313
	ldr	r4, [ip, #752]
	cmp	r4, r5
	bne	.L313
	ldr	r9, [ip, #56]
	ldr	r4, [r0, #3856]
	cmp	r9, r4
	bne	.L313
	mov	r1, ip
	mov	r3, r8
	mov	r2, #1
	mov	r0, r7
	bl	MVC_UnMarkLTFldByFrmIdx
	b	.L312
.L326:
	ldr	r3, [ip, #788]
	cmp	r3, r5
	bne	.L314
	ldr	r4, [ip, #56]
	ldr	r3, [r0, #3856]
	cmp	r4, r3
	bne	.L314
	mov	r1, ip
	mov	r3, r8
	mov	r2, #2
	mov	r0, r7
	bl	MVC_UnMarkLTFldByFrmIdx
	b	.L312
	UNWIND(.fnend)
	.size	MVC_MarkSTToLTRef, .-MVC_MarkSTToLTRef
	.align	2
	.global	MVC_UpdateMaxLTFrmIdx
	.type	MVC_UpdateMaxLTFrmIdx, %function
MVC_UpdateMaxLTFrmIdx:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r0, #11075584
	mov	r8, r0
	add	r5, r5, #45056
	ldr	r3, [r5, #2900]
	str	r1, [r5, #2904]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	movw	r6, #47876
	add	r7, r0, #11141120
	movt	r6, 169
	add	r7, r7, #12288
	add	r6, r0, r6
	mov	r3, r1
	mov	r4, #0
	b	.L331
.L329:
	ldr	r3, [r5, #2900]
	cmp	r3, r4
	ldmlsfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r3, [r5, #2904]
.L331:
	ldr	r1, [r6, #4]!
	add	r4, r4, #1
	ldr	r2, [r1, #28]
	cmp	r2, r3
	bcc	.L329
	ldr	r2, [r1, #56]
	ldr	r3, [r7, #3856]
	cmp	r2, r3
	bne	.L329
	mov	r0, r8
	bl	MVC_UnMarkFrameStoreRef
	b	.L329
	UNWIND(.fnend)
	.size	MVC_UpdateMaxLTFrmIdx, .-MVC_UpdateMaxLTFrmIdx
	.align	2
	.global	MVC_UnMarkAllSTRef
	.type	MVC_UnMarkAllSTRef, %function
MVC_UnMarkAllSTRef:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r6, r0, #11075584
	mov	r8, r0
	add	r6, r6, #45056
	ldr	r3, [r6, #2896]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	movw	r5, #47812
	add	r7, r0, #11141120
	movt	r5, 169
	add	r7, r7, #12288
	add	r5, r0, r5
	mov	r4, #0
	b	.L335
.L334:
	ldr	r3, [r6, #2896]
	cmp	r3, r4
	bls	.L338
.L335:
	ldr	r1, [r5, #4]!
	add	r4, r4, #1
	ldr	r3, [r7, #3856]
	ldr	r2, [r1, #56]
	cmp	r2, r3
	bne	.L334
	mov	r0, r8
	bl	MVC_UnMarkFrameStoreRef
	ldr	r3, [r6, #2896]
	cmp	r3, r4
	bhi	.L335
.L338:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_UnMarkAllSTRef, .-MVC_UnMarkAllSTRef
	.align	2
	.global	MVC_MarkCurrPicLT
	.type	MVC_MarkCurrPicLT, %function
MVC_MarkCurrPicLT:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r5, r2
	ldrb	r2, [r1, #3]	@ zero_extendqisi2
	mov	r4, r1
	cmp	r2, #0
	beq	.L342
	mov	r3, r5
	ldr	r1, [r1, #648]
	bl	MVC_UnMarkLTFldByFrmIdx
.L341:
	mov	r2, #1
	mov	r3, #0
	str	r5, [r4, #660]
	strb	r2, [r4, #4]
	strb	r3, [r4, #5]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L342:
	mov	r1, r5
	bl	MVC_UnMarkLTFrmByFrmIdx
	b	.L341
	UNWIND(.fnend)
	.size	MVC_MarkCurrPicLT, .-MVC_MarkCurrPicLT
	.align	2
	.global	MVC_RemoveFrameStoreOutDPB
	.type	MVC_RemoveFrameStoreOutDPB, %function
MVC_RemoveFrameStoreOutDPB:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r1, r0, r1, lsl #2
	mov	r5, r0
	add	r4, r1, #11075584
	add	r7, r4, #45056
	ldr	r2, [r7, #2696]
	cmp	r2, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r1, [r2, #52]
	movw	r3, #47960
	add	r6, r0, #11075584
	movt	r3, 169
	add	r1, r0, r1
	add	r0, r6, #45056
	add	r3, r1, r3
	mov	r1, #0
	strb	r1, [r3, #4]
	ldr	r3, [r0, #3120]
	cmp	r3, r1
	subne	r3, r3, #1
	str	r3, [r0, #3120]
	ldrsb	r1, [r2, #6]
	ldr	r0, [r5, #120]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L346
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	beq	.L347
	ldr	r3, [r7, #2696]
	mov	r2, #0
	ldr	r0, [r5, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetDisplay
.L347:
	ldr	r3, [r7, #2696]
	mov	r2, #0
	ldr	r0, [r5, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetRef
.L346:
	add	r1, r4, #45056
	mov	r3, #0
	add	r6, r6, #45056
	ldr	r2, [r1, #2696]
	strb	r3, [r2, #2]
	ldr	r2, [r1, #2696]
	strb	r3, [r2, #5]
	ldr	r2, [r1, #2696]
	strb	r3, [r2, #3]
	str	r3, [r1, #2696]
	ldr	r3, [r6, #2892]
	sub	r3, r3, #1
	str	r3, [r6, #2892]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_RemoveFrameStoreOutDPB, .-MVC_RemoveFrameStoreOutDPB
	.align	2
	.global	MVC_RemoveUnUsedFrameStore
	.type	MVC_RemoveUnUsedFrameStore, %function
MVC_RemoveUnUsedFrameStore:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #11075584
	mov	r8, r0
	add	r3, r3, #45056
	mov	r7, r1
	ldr	r6, [r3, #2888]
	cmp	r6, #0
	beq	.L375
	movw	r5, #47748
	mov	r4, #0
	movt	r5, 169
	add	r5, r0, r5
.L363:
	ldr	r3, [r5, #4]!
	cmp	r3, #0
	beq	.L362
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L362
	ldrb	r2, [r3, #5]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L362
	ldr	r1, [r3, #56]
	cmn	r7, #1
	cmpne	r1, r7
	beq	.L376
.L362:
	add	r4, r4, #1
	cmp	r4, r6
	bne	.L363
.L375:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L376:
	ldr	ip, [r3, #16]
	mov	r1, r4
	mov	r0, r8
	cmp	ip, #1
	beq	.L362
	strb	r2, [r3, #2]
	bl	MVC_RemoveFrameStoreOutDPB
	b	.L362
	UNWIND(.fnend)
	.size	MVC_RemoveUnUsedFrameStore, .-MVC_RemoveUnUsedFrameStore
	.align	2
	.global	MVC_CheckFrameStore
	.type	MVC_CheckFrameStore, %function
MVC_CheckFrameStore:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldrb	r3, [r0, #6]	@ zero_extendqisi2
	mov	r5, r0
	mov	r4, r1
	cmp	r3, #0
	bne	.L378
	ldrsb	r3, [r1, #8]
	cmp	r3, #1
	bne	.L390
	strb	r3, [r0, #6]
.L378:
	ldrsb	r1, [r4, #6]
	ldr	r0, [r5, #120]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L380
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	cmpne	r3, #0
	beq	.L400
	ldrb	r2, [r4, #2]	@ zero_extendqisi2
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L389
	cmp	r3, #1
	beq	.L389
	cmp	r2, #3
	beq	.L401
	cmp	r2, #1
	beq	.L402
	cmp	r2, #2
	beq	.L403
.L385:
	ldr	r3, [r5, #224]
	ldr	r2, [r0, #192]
	ldr	r3, [r3, #4]
	cmp	r2, r3
	movls	r0, #0
	bhi	.L404
.L398:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L400:
	ldrsb	r2, [r4, #6]
	mov	r0, #1
	ldr	r1, .L405
	bl	dprint_vfmw
.L382:
	ldr	r3, [r4, #16]
	cmp	r3, #1
	mvnne	r0, #2
	moveq	r3, #2
	mvneq	r0, #2
	streq	r3, [r4, #16]
	b	.L398
.L401:
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #3
	bne	.L385
	mov	r2, r3
	ldr	r1, .L405+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L398
.L402:
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	tst	r3, #1
	beq	.L385
	mov	r0, r2
	ldr	r1, .L405+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L398
.L403:
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	tst	r3, #2
	beq	.L385
	ldr	r1, .L405+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L398
.L390:
	mvn	r0, #0
	b	.L398
.L380:
	ldrsb	ip, [r4, #6]
	mov	r2, r4
	ldr	r3, [r4, #16]
	mov	r0, #1
	ldr	r1, .L405+16
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L382
.L389:
	ldr	r1, .L405+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L398
.L404:
	ldr	r1, .L405+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L398
.L406:
	.align	2
.L405:
	.word	.LC4
	.word	.LC7
	.word	.LC8
	.word	.LC9
	.word	.LC5
	.word	.LC6
	.word	.LC10
	UNWIND(.fnend)
	.size	MVC_CheckFrameStore, .-MVC_CheckFrameStore
	.align	2
	.global	MVC_ExchangePts
	.type	MVC_ExchangePts, %function
MVC_ExchangePts:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	add	r8, r1, #656
	mvn	r7, #0
	mvn	r6, #0
	ldrd	r2, [r8]
	mov	r5, r0
	cmp	r3, r7
	cmpeq	r2, r6
	beq	.L407
	add	r9, r0, #11075584
	add	r9, r9, #45056
	ldr	r3, [r9, #2888]
	cmp	r3, #0
	beq	.L407
	movw	r10, #47748
	mvn	r6, #1
	movt	r10, 169
	add	r10, r0, r10
	mvn	r7, #0
	mov	r4, #0
	mvn	r3, #0
	str	r3, [fp, #-48]
.L412:
	ldr	r3, [r10, #4]!
	cmp	r3, #0
	beq	.L411
	ldrsb	r1, [r3, #6]
	ldr	r0, [r5, #120]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L411
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	cmpne	r3, #0
	beq	.L411
	ldr	r3, [r10]
	add	r3, r3, #656
	ldrd	r0, [r3]
	cmp	r1, r7
	cmpeq	r0, r6
	strcc	r4, [fp, #-48]
	movcc	r6, r0
	movcc	r7, r1
.L411:
	ldr	r3, [r9, #2888]
	add	r4, r4, #1
	cmp	r4, r3
	bcc	.L412
	ldr	r3, [fp, #-48]
	cmn	r3, #1
	beq	.L407
	ldrd	r2, [r8]
	cmp	r3, r7
	cmpeq	r2, r6
	bhi	.L426
.L407:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L426:
	strd	r6, [sp]
	mov	r0, #29
	ldr	r1, .L427
	bl	dprint_vfmw
	ldr	r3, [fp, #-48]
	movw	r1, #28322
	movt	r1, 42
	add	r1, r3, r1
	ldrd	r2, [r8]
	ldr	r1, [r5, r1, asl #2]
	add	r1, r1, #656
	strd	r2, [r1]
	strd	r6, [r8]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L428:
	.align	2
.L427:
	.word	.LC11
	UNWIND(.fnend)
	.size	MVC_ExchangePts, .-MVC_ExchangePts
	.align	2
	.global	MVC_GetImagePara
	.type	MVC_GetImagePara, %function
MVC_GetImagePara:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #11075584
	ldr	r2, [r0, #252]
	add	ip, r3, #40960
	mov	r5, r0
	mov	lr, #2240
	mov	r4, r1
	ldr	r0, [ip, #1048]
	movw	r8, #3992
	ldrb	r7, [r1, #137]	@ zero_extendqisi2
	ldrb	r9, [r1, #15]	@ zero_extendqisi2
	mla	r1, lr, r0, r2
	ldrb	r10, [r4, #136]	@ zero_extendqisi2
	ldrb	r6, [r4, #138]	@ zero_extendqisi2
	bfc	r7, #0, #2
	ldrb	r0, [r4, #14]	@ zero_extendqisi2
	bfc	r10, #0, #2
	ldr	r2, [r5, #248]
	bfi	r6, r0, #1, #1
	ldrb	lr, [r4, #2]	@ zero_extendqisi2
	ldr	r0, [r1, #28]
	strb	r7, [r4, #137]
	strb	r10, [r4, #136]
	strb	r6, [r4, #138]
	str	r9, [r4, #192]
	ldr	r1, [r5, #56]
	mla	r2, r8, r0, r2
	str	r1, [r4, #180]
	cmp	lr, #3
	ldrls	pc, [pc, lr, asl #2]
	b	.L468
.L432:
	.word	.L431
	.word	.L433
	.word	.L434
	.word	.L431
.L434:
	ldrb	r1, [r4, #137]	@ zero_extendqisi2
	add	r3, r5, #11075584
	ldr	r6, [r4, #44]
	add	r3, r3, #45056
	ldrb	r0, [r4, #136]	@ zero_extendqisi2
	and	r1, r1, #240
	ldrb	lr, [r4]	@ zero_extendqisi2
	orr	r1, r1, #11
	str	r6, [r4, #224]
	bfi	r0, lr, #0, #2
	strb	r1, [r4, #137]
	strb	r0, [r4, #136]
.L430:
	ldrb	r1, [r2, #20]	@ zero_extendqisi2
	str	r1, [r4, #468]
	str	r1, [r4, #472]
	ldrb	r1, [r2, #24]	@ zero_extendqisi2
	cmp	r1, #0
	ldrne	r1, [r2, #68]
	mov	r2, #1
	str	r2, [r4, #476]
	str	r1, [r4, #480]
	ldrb	r2, [ip, #1043]	@ zero_extendqisi2
	cmp	r2, #1
	movne	r2, #0
	str	r2, [r4, #264]
	ldr	r2, [r5, #224]
	ldr	r2, [r2, #24]
	cmp	r2, #0
	beq	.L452
	ldrb	r2, [r4, #704]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L452
	ldrb	r1, [r4, #2]	@ zero_extendqisi2
	cmp	r1, #3
	ldreqb	r1, [r4, #137]	@ zero_extendqisi2
	bfieq	r1, r2, #0, #2
	streqb	r1, [r4, #137]
.L452:
	ldrb	r2, [r3, #2648]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L453
	ldr	r2, [r3, #2664]
	cmp	r2, #3
	moveq	r3, #1
	streq	r3, [r4, #348]
	beq	.L453
	cmp	r2, #4
	moveq	r3, #2
	streq	r3, [r4, #348]
	beq	.L453
	cmp	r2, #5
	moveq	r3, #3
	streq	r3, [r4, #348]
	beq	.L453
	mov	r0, #0
	ldr	r1, .L483
	str	r0, [r4, #348]
	ldr	r2, [r3, #2664]
	bl	dprint_vfmw
.L453:
	ldr	r0, [r5, #120]
	ldrsb	r1, [r4, #6]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldr	r3, .L483+4
	mov	r2, #632
	add	r1, r4, #72
	ldr	r3, [r3, #52]
	blx	r3
	mov	r3, #15
	str	r3, [r5, #296]
	mov	r2, #1
	ldrb	r3, [r4, #704]	@ zero_extendqisi2
	strb	r2, [r5, #291]
	cmp	r3, #0
	movne	r3, #4
	strb	r3, [r5, #284]
	ldr	r3, [r4, #732]
	strb	r2, [r5, #289]
	str	r3, [r5, #300]
	str	r3, [r5, #308]
	str	r3, [r5, #304]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L433:
	ldr	r6, [r4, #44]
	add	r3, r5, #11075584
	ldrb	r1, [r4, #137]	@ zero_extendqisi2
	add	r3, r3, #45056
	ldrb	r0, [r4, #136]	@ zero_extendqisi2
	ldrb	lr, [r4]	@ zero_extendqisi2
	orr	r1, r1, #3
	str	r6, [r4, #224]
	bfi	r0, lr, #0, #2
	strb	r1, [r4, #137]
	strb	r0, [r4, #136]
	b	.L430
.L431:
	ldrb	r1, [r4, #704]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L435
	ldr	r0, [r4, #40]
	ldr	r1, [r4, #44]
	cmp	r0, #0
	ldrb	r7, [r4]	@ zero_extendqisi2
	movne	lr, #3
	str	r1, [r4, #224]
	movne	r6, lr
	moveq	lr, #2
	moveq	r6, #3
.L436:
	ldr	r0, [r4, #756]
	ldr	r1, [r4, #792]
	cmp	r0, r1
	beq	.L480
	movle	r0, #1
	movgt	r0, #0
.L447:
	add	r3, r3, #45056
	ldrb	r1, [r3, #2684]	@ zero_extendqisi2
	cmp	r1, #3
	moveq	r0, #1
	beq	.L448
	cmp	r1, #4
	moveq	r0, #0
.L448:
	ldrb	r1, [r4, #137]	@ zero_extendqisi2
	ldrb	r8, [r4, #136]	@ zero_extendqisi2
	bfi	r1, r0, #4, #2
	bfi	r1, r6, #2, #2
	bfi	r8, r7, #0, #2
	bfi	r1, lr, #0, #2
	strb	r8, [r4, #136]
	strb	r1, [r4, #137]
	b	.L430
.L435:
	ldr	r0, [r4, #764]
	ldr	r1, [r5, #116]
	ldr	lr, [r4, #800]
	cmp	r0, r1
	bhi	.L481
	cmp	r1, lr
	bcc	.L440
.L438:
	ldr	r1, [r4, #44]
	mov	r6, #3
	ldrb	r7, [r4]	@ zero_extendqisi2
	ldrb	lr, [r4, #743]	@ zero_extendqisi2
	ldrb	r8, [r4, #779]	@ zero_extendqisi2
	str	r1, [r4, #224]
.L441:
	ldrb	r1, [r4, #4]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L482
	cmp	r1, #2
	streq	r0, [r4, #224]
	moveq	r7, lr
	moveq	r6, #1
.L443:
	str	lr, [r4, #128]
	mov	lr, #3
	str	r8, [r4, #132]
	b	.L436
.L440:
	ldrb	r7, [r4, #743]	@ zero_extendqisi2
	mov	r6, #1
	ldrb	r8, [r4, #779]	@ zero_extendqisi2
	str	r0, [r4, #224]
	mov	lr, r7
	b	.L441
.L480:
	ldr	r1, [r4, #140]
	cmp	r1, #720
	movne	r0, #1
	bne	.L447
	ldr	r0, [r4, #144]
	subs	r0, r0, #480
	movne	r0, #1
	b	.L447
.L481:
	cmp	r1, lr
	bcc	.L438
	ldrb	r7, [r4, #779]	@ zero_extendqisi2
	mov	r6, #2
	str	lr, [r4, #224]
	ldrb	lr, [r4, #743]	@ zero_extendqisi2
	mov	r8, r7
	b	.L441
.L482:
	ldr	r1, [r4, #800]
	mov	r7, r8
	mov	r6, #2
	str	r1, [r4, #224]
	b	.L443
.L468:
	add	r3, r5, #11075584
	add	r3, r3, #45056
	b	.L430
.L484:
	.align	2
.L483:
	.word	.LC12
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	MVC_GetImagePara, .-MVC_GetImagePara
	.align	2
	.global	MVC_SetFrmRepeatCount
	.type	MVC_SetFrmRepeatCount, %function
MVC_SetFrmRepeatCount:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #224]
	ldr	r3, [r3, #612]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r1, #16]
	ldmccfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MVC_SetFrmRepeatCount.part.2
	UNWIND(.fnend)
	.size	MVC_SetFrmRepeatCount, .-MVC_SetFrmRepeatCount
	.align	2
	.global	MVC_SplitFrmToFlds
	.type	MVC_SplitFrmToFlds, %function
MVC_SplitFrmToFlds:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldrb	lr, [r0, #705]	@ zero_extendqisi2
	mov	r5, #1
	ldrb	ip, [r0, #706]	@ zero_extendqisi2
	mov	r4, #2
	ldr	r1, [r0, #728]
	ldrb	r2, [r0, #707]	@ zero_extendqisi2
	ldr	r3, [r0, #708]
	strb	r5, [r0, #740]
	strb	r4, [r0, #776]
	strb	lr, [r0, #741]
	strb	lr, [r0, #777]
	strb	ip, [r0, #742]
	strb	ip, [r0, #778]
	str	r1, [r0, #764]
	str	r1, [r0, #800]
	strb	r2, [r0, #743]
	strb	r2, [r0, #779]
	str	r3, [r0, #744]
	str	r3, [r0, #780]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_SplitFrmToFlds, .-MVC_SplitFrmToFlds
	.align	2
	.global	MVC_CombineFldsToFrm
	.type	MVC_CombineFldsToFrm, %function
MVC_CombineFldsToFrm:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r0, #792]
	mov	lr, #3
	ldr	r1, [r0, #756]
	ldr	r3, [r0, #800]
	cmp	r2, r1
	ldr	r5, [r0, #764]
	ldrb	r4, [r0, #777]	@ zero_extendqisi2
	ldr	ip, [r0, #744]
	movge	r2, r1
	add	r3, r3, r5
	cmp	r4, #0
	strb	lr, [r0, #704]
	mov	r3, r3, lsr #1
	str	ip, [r0, #708]
	str	r2, [r0, #720]
	str	r2, [r0, #32]
	str	r3, [r0, #728]
	beq	.L489
	ldrb	r2, [r0, #741]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L490
.L489:
	ldr	r2, [r0, #776]
	mov	r1, #0
	strb	r1, [r0, #705]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, r1
	beq	.L494
	ldr	r2, [r0, #740]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #0
	movne	ip, #1
	bne	.L492
.L494:
	mov	ip, #0
.L492:
	ldrb	r2, [r0, #779]	@ zero_extendqisi2
	ldrb	r1, [r0, #743]	@ zero_extendqisi2
	str	r3, [r0, #44]
	cmp	r2, r1
	strb	ip, [r0, #706]
	movcs	r3, r2
	movcc	r3, r1
	strb	r3, [r0, #707]
	strb	r3, [r0]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L490:
	mov	r1, #1
	strb	r1, [r0, #705]
	b	.L494
	UNWIND(.fnend)
	.size	MVC_CombineFldsToFrm, .-MVC_CombineFldsToFrm
	.align	2
	.global	MVC_GetAPC
	.type	MVC_GetAPC, %function
MVC_GetAPC:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	subs	r6, r1, #0
	mov	r5, r0
	beq	.L525
	cmp	r2, #1
	beq	.L506
	cmp	r2, #2
	beq	.L507
	ldr	r9, [r6, #756]
	ldr	r10, [r6, #792]
.L508:
	add	r8, r5, #11075584
	add	r7, r8, #45056
	ldr	ip, [r7, #3116]
	cmp	ip, #0
	beq	.L517
	ldrb	r4, [r7, #2908]	@ zero_extendqisi2
	cmp	r4, #0
	movwne	r3, #47964
	movne	r4, #0
	movtne	r3, 169
	addne	r3, r5, r3
	bne	.L511
	b	.L509
.L515:
	ldrb	r2, [r3, #1]!	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L509
.L511:
	add	r4, r4, #1
	cmp	r4, ip
	bne	.L515
.L517:
	mvn	r0, #0
.L521:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L507:
	ldr	r9, [r6, #792]
	mov	r10, r9
	b	.L508
.L509:
	ldrsb	r1, [r6, #6]
	ldr	r0, [r5, #120]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L512
	ldr	r3, [r0, #28]
	cmp	r3, #0
	beq	.L512
	add	r2, r5, r4
	movw	r3, #47960
	movt	r3, 169
	add	r3, r2, r3
	mov	r2, #1
	add	r5, r5, r4, lsl #2
	strb	r2, [r3, #4]
	add	r5, r5, #11075584
	ldr	r3, [r0, #28]
	add	r5, r5, #45056
	add	r8, r8, #45056
	ldr	r1, .L526
	mov	r0, #13
	ldr	r3, [r3, #4]
	str	r9, [r5, #2988]
	str	r10, [r5, #3052]
	str	r3, [r5, #2924]
	ldr	r3, [r7, #3120]
	cmp	r3, #15
	addls	r2, r3, r2
	mov	r3, r4
	movhi	r2, #16
	str	r2, [r8, #3120]
	ldr	r2, [r6, #220]
	bl	dprint_vfmw
	mov	r0, #0
	str	r4, [r6, #52]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L506:
	ldr	r9, [r6, #756]
	mov	r10, r9
	b	.L508
.L512:
	mov	r1, #0
	ldrsb	r2, [r6, #6]
	ldrb	r3, [r6, #3]	@ zero_extendqisi2
	stmia	sp, {r0, r1}
	mov	r0, r1
	ldr	r1, .L526+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L521
.L525:
	mov	r0, r6
	movw	r3, #2054
	ldr	r2, .L526+8
	ldr	r1, .L526+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L521
.L527:
	.align	2
.L526:
	.word	.LC15
	.word	.LC16
	.word	.LC13
	.word	.LC14
	UNWIND(.fnend)
	.size	MVC_GetAPC, .-MVC_GetAPC
	.align	2
	.global	MVC_SlidingWinMark
	.type	MVC_SlidingWinMark, %function
MVC_SlidingWinMark:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r3, r0, #11075584
	ldr	r2, [r0, #236]
	add	r3, r3, #45056
	mov	r10, r0
	ldr	r0, [r3, #2900]
	ldr	r2, [r2, #3944]
	ldr	r1, [r3, #2896]
	rsb	r2, r0, r2
	cmp	r1, r2
	beq	.L553
.L528:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L553:
	ldr	r8, [r3, #2888]
	cmp	r8, #0
	beq	.L533
	movw	r6, #47748
	add	r1, r10, #11141120
	movt	r6, 169
	mov	r2, #0
	add	r1, r1, #12288
	add	r6, r10, r6
	mov	r5, r2
	mvn	r9, #-2147483648
.L532:
	ldr	r4, [r6, #4]!
	cmp	r4, #0
	beq	.L531
	ldr	r7, [r4, #64]
	cmp	r9, r7
	bls	.L531
	ldrb	r3, [r4, #3]	@ zero_extendqisi2
	mov	r0, r4
	cmp	r3, #0
	beq	.L531
	str	r1, [fp, #-52]
	str	r2, [fp, #-48]
	bl	MVC_NonLongTermRefFlg
	ldr	r2, [fp, #-48]
	ldr	r1, [fp, #-52]
	cmp	r0, #0
	beq	.L531
	ldr	r0, [r4, #56]
	ldr	r3, [r1, #3856]
	cmp	r0, r3
	moveq	r9, r7
	moveq	r2, r5
.L531:
	add	r5, r5, #1
	cmp	r5, r8
	bne	.L532
.L530:
	movw	r3, #28322
	movt	r3, 42
	add	r3, r2, r3
	ldr	r4, [r10, r3, asl #2]
	cmp	r4, #0
	beq	.L528
	ldrb	r3, [r4, #3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L528
	mov	r0, r4
	bl	MVC_NonLongTermRefFlg
	cmp	r0, #0
	beq	.L528
	add	r3, r10, #11141120
	ldr	r2, [r4, #56]
	add	r3, r3, #12288
	ldr	r3, [r3, #3856]
	cmp	r2, r3
	bne	.L528
	mov	r0, r10
	mov	r1, r4
	bl	MVC_UnMarkFrameStoreRef
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	MVC_UpdateReflist
.L533:
	mov	r2, r8
	b	.L530
	UNWIND(.fnend)
	.size	MVC_SlidingWinMark, .-MVC_SlidingWinMark
	.align	2
	.global	MVC_DumpDPB
	.type	MVC_DumpDPB, %function
MVC_DumpDPB:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldr	r3, .L564
	mov	r7, r0
	ldr	r3, [r3]
	tst	r3, #16384
	beq	.L554
	add	r6, r0, #11075584
	add	r6, r6, #45056
	ldr	r3, [r6, #2892]
	cmp	r3, #0
	movwne	r5, #47748
	movne	r4, #0
	movtne	r5, 169
	addne	r5, r0, r5
	beq	.L560
.L559:
	ldr	ip, [r5, #4]!
	mov	r2, r4
	ldr	r1, .L564+4
	mov	r0, #14
	add	r4, r4, #1
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	ldr	r3, [ip, #20]
	str	lr, [sp, #4]
	ldr	ip, [ip, #32]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r6, #2892]
	cmp	r3, r4
	bhi	.L559
.L560:
	ldr	r1, .L564+8
	mov	r0, #14
	bl	dprint_vfmw
	ldr	r3, [r6, #2896]
	cmp	r3, #0
	movwne	r5, #47812
	movne	r4, #0
	movtne	r5, 169
	addne	r5, r7, r5
	beq	.L558
.L561:
	ldr	ip, [r5, #4]!
	mov	r2, r4
	ldr	r1, .L564+12
	mov	r0, #14
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	ldr	r3, [ip, #20]
	str	lr, [sp, #4]
	ldr	ip, [ip, #32]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r5]
	mov	r2, r4
	ldr	r1, .L564+16
	mov	r0, #14
	add	r4, r4, #1
	ldr	r3, [r3, #720]
	bl	dprint_vfmw
	ldr	r3, [r6, #2896]
	cmp	r3, r4
	bhi	.L561
.L558:
	ldr	r1, .L564+8
	mov	r0, #14
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L554:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L565:
	.align	2
.L564:
	.word	g_PrintEnable
	.word	.LC18
	.word	.LC17
	.word	.LC19
	.word	.LC20
	UNWIND(.fnend)
	.size	MVC_DumpDPB, .-MVC_DumpDPB
	.align	2
	.global	MVC_UpdateCurrFrameInfo
	.type	MVC_UpdateCurrFrameInfo, %function
MVC_UpdateCurrFrameInfo:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r0, r0, #11141120
	add	r3, r0, #12288
	ldrb	r2, [r3, #3130]	@ zero_extendqisi2
	ldr	r4, [r3, #3776]
	strb	r2, [r4, #1]
	ldrb	r2, [r3, #3132]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r2, #3
	bne	.L567
	ldrb	r2, [r3, #3133]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r2, #3
.L567:
	strb	r2, [r4, #3]
	ldr	r2, [r3, #3784]
	str	r2, [r4, #20]
	ldr	r2, [r3, #3828]
	str	r2, [r4, #44]
	ldrb	r2, [r3, #3140]	@ zero_extendqisi2
	strb	r2, [r4]
	ldr	r2, [r3, #3796]
	str	r2, [r4, #32]
	ldr	r2, [r3, #3852]
	str	r2, [r4, #48]
	ldr	r2, [r3, #3788]
	str	r2, [r4, #28]
	ldrb	r2, [r3, #3137]	@ zero_extendqisi2
	str	r2, [r4, #40]
	ldrb	r2, [r3, #3135]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r1, #3
	movne	r1, #0
	strb	r1, [r4, #4]
	ldrb	r2, [r3, #3131]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L570
	bcc	.L571
	cmp	r2, #2
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	str	r4, [r4, #780]
	mov	ip, #1
	strb	ip, [r4, #776]
	mov	r6, #0
	ldrb	ip, [r3, #3132]	@ zero_extendqisi2
	strb	ip, [r4, #777]
	ldrb	ip, [r3, #3133]	@ zero_extendqisi2
	strb	ip, [r4, #778]
	ldr	ip, [r3, #3804]
	str	ip, [r4, #792]
	ldrb	ip, [r3, #3140]	@ zero_extendqisi2
	strb	ip, [r4, #779]
	ldr	lr, [r3, #3828]
	str	r6, [r4, #40]
	str	lr, [r4, #800]
	ldrb	r5, [r3, #3129]	@ zero_extendqisi2
	cmp	r5, r6
	beq	.L588
	ldr	r2, [r4, #764]
	mov	r5, #3
	strb	r5, [r4, #2]
	mvn	r7, #0
	add	lr, lr, r2
	str	lr, [r4, #44]
	str	lr, [r4, #728]
	ldrb	r3, [r3, #3135]	@ zero_extendqisi2
	cmp	r3, #1
	add	r3, r0, #16000
	orreq	r6, r1, #2
	strb	r6, [r4, #4]
	ldrd	r8, [r3, #16]
	mvn	r6, #0
	cmp	r9, r7
	cmpeq	r8, r6
	beq	.L579
	add	r1, r4, #656
	ldrd	r2, [r1]
	cmp	r3, r7
	cmpeq	r2, r6
	beq	.L589
.L579:
	ldrb	r3, [r4, #743]	@ zero_extendqisi2
.L586:
	add	r1, r0, #12288
	cmp	r3, ip
	mov	r0, r4
	movcc	r3, ip
	strb	r3, [r4]
	ldr	r3, [r1, #3796]
	str	r3, [r4, #32]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	MVC_CombineFldsToFrm
.L571:
	str	r4, [r4, #708]
	mov	r1, #3
	mov	r2, #0
	strb	r1, [r4, #2]
	strb	r2, [r4, #704]
	add	r1, r3, #3136
	ldrb	r5, [r3, #3132]	@ zero_extendqisi2
	mov	r2, #632
	add	r1, r1, #8
	add	r0, r4, #72
	strb	r5, [r4, #705]
	ldrb	r6, [r3, #3133]	@ zero_extendqisi2
	strb	r6, [r4, #706]
	ldr	ip, [r3, #3800]
	str	ip, [r4, #720]
	ldrb	r7, [r3, #3140]	@ zero_extendqisi2
	strb	r7, [r4, #707]
	ldr	r8, [r3, #3828]
	str	r8, [r4, #728]
	ldr	ip, [r3, #3804]
	str	ip, [r4, #756]
	ldr	r3, [r3, #3808]
	str	r3, [r4, #792]
	bl	memcpy
	mov	r2, #1
	mov	r3, #2
	str	r8, [r4, #764]
	str	r8, [r4, #800]
	strb	r7, [r4, #743]
	strb	r7, [r4, #779]
	strb	r6, [r4, #742]
	strb	r6, [r4, #778]
	strb	r5, [r4, #741]
	strb	r5, [r4, #777]
	str	r4, [r4, #744]
	str	r4, [r4, #780]
	strb	r2, [r4, #740]
	strb	r3, [r4, #776]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L570:
	strb	r2, [r4, #740]
	mov	r5, #0
	str	r4, [r4, #744]
	ldrb	ip, [r3, #3132]	@ zero_extendqisi2
	strb	ip, [r4, #741]
	ldrb	ip, [r3, #3133]	@ zero_extendqisi2
	strb	ip, [r4, #742]
	ldr	ip, [r3, #3804]
	str	ip, [r4, #756]
	ldrb	ip, [r3, #3140]	@ zero_extendqisi2
	strb	ip, [r4, #743]
	ldr	lr, [r3, #3828]
	str	r5, [r4, #40]
	str	lr, [r4, #764]
	ldrb	r6, [r3, #3129]	@ zero_extendqisi2
	cmp	r6, r5
	beq	.L590
	ldr	r2, [r4, #800]
	mov	r6, #3
	strb	r6, [r4, #2]
	mvn	r7, #0
	add	lr, lr, r2
	str	lr, [r4, #44]
	str	lr, [r4, #728]
	mvn	r6, #0
	ldrb	r3, [r3, #3135]	@ zero_extendqisi2
	cmp	r3, #1
	add	r3, r0, #16000
	orreq	r5, r1, #1
	strb	r5, [r4, #4]
	ldrd	r8, [r3, #16]
	cmp	r9, r7
	cmpeq	r8, r6
	beq	.L575
	add	r1, r4, #656
	ldrd	r2, [r1]
	cmp	r3, r7
	cmpeq	r2, r6
	streqd	r8, [r1]
.L575:
	ldrb	r3, [r4, #779]	@ zero_extendqisi2
	b	.L586
.L588:
	strb	r2, [r4, #2]
	add	r1, r0, #15424
	str	lr, [r4, #44]
	add	r1, r1, #8
	str	lr, [r4, #728]
	add	r0, r4, #72
	ldrb	r3, [r3, #3135]	@ zero_extendqisi2
	mov	r2, #632
	cmp	r3, #1
	moveq	r5, #2
	strb	r5, [r4, #4]
	bl	memcpy
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L590:
	strb	r2, [r4, #2]
	add	r1, r3, #3136
	str	lr, [r4, #44]
	add	r1, r1, #8
	str	lr, [r4, #728]
	add	r0, r4, #72
	ldrb	r3, [r3, #3135]	@ zero_extendqisi2
	mov	r2, #632
	sub	r3, r3, #1
	clz	r3, r3
	mov	r3, r3, lsr #5
	strb	r3, [r4, #4]
	bl	memcpy
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L589:
	strd	r8, [r1]
	b	.L579
	UNWIND(.fnend)
	.size	MVC_UpdateCurrFrameInfo, .-MVC_UpdateCurrFrameInfo
	.align	2
	.global	MVC_SimpleSlideDPB
	.type	MVC_SimpleSlideDPB, %function
MVC_SimpleSlideDPB:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #11075584
	mov	r7, r0
	add	r3, r3, #45056
	ldr	r5, [r3, #2888]
	ldr	r3, [r3, #2892]
	cmp	r3, r5
	addcc	r6, r0, #11141120
	bcc	.L592
	cmp	r5, #0
	beq	.L597
	movw	ip, #47748
	add	r6, r0, #11141120
	movt	ip, 169
	mov	r1, #0
	add	r8, r6, #12288
	add	ip, r0, ip
	mov	r3, r1
	mvn	r4, #-2147483648
.L595:
	ldr	r2, [ip, #4]!
	cmp	r2, #0
	beq	.L594
	ldr	lr, [r2, #64]
	cmp	r4, lr
	bls	.L594
	ldr	r0, [r2, #56]
	ldr	r2, [r8, #3856]
	cmp	r0, r2
	moveq	r4, lr
	moveq	r1, r3
.L594:
	add	r3, r3, #1
	cmp	r3, r5
	bne	.L595
	mov	r5, r1
.L593:
	movw	r3, #28322
	mov	r0, r7
	movt	r3, 42
	add	r3, r1, r3
	ldr	r1, [r7, r3, asl #2]
	bl	MVC_UnMarkFrameStoreRef
	mov	r1, r5
	mov	r0, r7
	bl	MVC_RemoveFrameStoreOutDPB
.L592:
	add	r3, r6, #12288
	mov	r1, #0
	ldr	r2, [r3, #3792]
	strb	r1, [r3, #3132]
	cmp	r2, r1
	movne	r2, #1
	strneb	r2, [r3, #3133]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L597:
	add	r6, r0, #11141120
	mov	r1, r5
	b	.L593
	UNWIND(.fnend)
	.size	MVC_SimpleSlideDPB, .-MVC_SimpleSlideDPB
	.align	2
	.global	MVC_ReleaseNAL
	.type	MVC_ReleaseNAL, %function
MVC_ReleaseNAL:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r5, r1, #0
	mov	r6, r0
	beq	.L615
	add	r7, r5, #56
	mov	r4, r5
	mov	r3, #0
	strb	r3, [r5, #1]
	strb	r3, [r5, #3]
.L610:
	ldr	r3, [r4, #8]
	mov	r0, r6
	cmp	r3, #0
	beq	.L609
	ldr	r1, [r4, #32]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #12]
	ldr	r2, [r4, #8]
	mov	r0, #7
	ldr	r1, .L616
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #8]
	str	r3, [r4, #24]
	str	r3, [r4, #12]
.L609:
	add	r4, r4, #28
	cmp	r4, r7
	bne	.L610
	mov	r3, #0
	strb	r3, [r5]
	str	r3, [r5, #68]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L615:
	mov	r0, r5
	movw	r3, #3967
	ldr	r2, .L616+4
	ldr	r1, .L616+8
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L617:
	.align	2
.L616:
	.word	.LC21
	.word	.LC13
	.word	.LC14
	UNWIND(.fnend)
	.size	MVC_ReleaseNAL, .-MVC_ReleaseNAL
	.align	2
	.global	MVC_ClearCurrNal
	.type	MVC_ClearCurrNal, %function
MVC_ClearCurrNal:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r1, [r0, #232]
	mov	r4, r0
	cmp	r1, #0
	beq	.L619
	ldr	r0, [r0, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L619:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_ClearCurrNal, .-MVC_ClearCurrNal
	.align	2
	.global	MVC_ClearCurrSlice
	.type	MVC_ClearCurrSlice, %function
MVC_ClearCurrSlice:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r1, .L628
	mov	r4, r0
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #232]
	cmp	r1, #0
	beq	.L624
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L624:
	ldr	r3, [r4, #80]
	mov	r0, #0
	add	r3, r3, #1
	str	r3, [r4, #80]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L629:
	.align	2
.L628:
	.word	.LC22
	UNWIND(.fnend)
	.size	MVC_ClearCurrSlice, .-MVC_ClearCurrSlice
	.align	2
	.global	MVC_ClearAllNal
	.type	MVC_ClearAllNal, %function
MVC_ClearAllNal:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r6, r0
	add	r4, r0, #936
	add	r5, r0, #12992
	b	.L632
.L631:
	add	r4, r4, #88
	cmp	r4, r5
	beq	.L634
.L632:
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L631
	mov	r1, r4
	ldr	r0, [r6, #120]
	add	r4, r4, #88
	bl	MVC_ReleaseNAL
	cmp	r4, r5
	bne	.L632
.L634:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_ClearAllNal, .-MVC_ClearAllNal
	.align	2
	.global	MVC_ClearAllSlice
	.type	MVC_ClearAllSlice, %function
MVC_ClearAllSlice:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	movw	r4, #16912
	movw	r5, #17456
	movt	r4, 170
	movt	r5, 170
	add	r4, r0, r4
	add	r5, r0, r5
	mov	r6, r0
	mov	r7, #0
.L637:
	ldr	r1, [r4, #4]!
	cmp	r1, #0
	beq	.L636
	ldr	r0, [r6, #120]
	bl	MVC_ReleaseNAL
	str	r7, [r4]
.L636:
	cmp	r4, r5
	bne	.L637
	mov	r0, #0
	str	r0, [r6, #64]
	str	r0, [r6, #104]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_ClearAllSlice, .-MVC_ClearAllSlice
	.align	2
	.global	MVC_ClearCurrPic
	.type	MVC_ClearCurrPic, %function
MVC_ClearCurrPic:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	bl	MVC_ClearAllSlice
	ldr	r0, [r4, #40]
	add	r3, r4, #11075584
	add	r3, r3, #40960
	mov	r2, #0
	movw	r1, #23352
	movt	r1, 1
	str	r0, [r3, #2700]
	str	r1, [r3, #2704]
	mov	r0, #2
	mov	r1, #7
	strb	r0, [r3, #2689]
	strb	r1, [r3, #2691]
	mov	r0, #32
	mov	r1, #3
	strb	r0, [r3, #2690]
	str	r1, [r3, #2712]
	mvn	r0, #0
	mov	r1, #262144
	str	r0, [r3, #2716]
	str	r1, [r3, #2728]
	mov	r0, r2
	strb	r2, [r3, #2688]
	str	r2, [r3, #2720]
	str	r2, [r3, #2724]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_ClearCurrPic, .-MVC_ClearCurrPic
	.align	2
	.global	MVC_ArrangeVahbMem
	.type	MVC_ArrangeVahbMem, %function
MVC_ArrangeVahbMem:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	mov	r6, r1
	sub	r3, r2, #32
	sub	r1, r1, #32
	movw	ip, #8160
	cmp	r3, ip
	cmpls	r1, ip
	mov	r5, r2
	mov	r4, r0
	movhi	r1, #1
	movls	r1, #0
	bhi	.L653
	ldr	r3, .L655
	mov	r2, #20
	sub	r0, fp, #48
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r4, #224]
	str	r6, [fp, #-44]
	str	r5, [fp, #-40]
	ldr	r3, [r3, #28]
	str	r6, [fp, #-36]
	cmp	r3, #24
	str	r5, [fp, #-32]
	beq	.L646
	add	r2, r4, #11075584
	ldrb	r3, [fp, #4]	@ zero_extendqisi2
	add	r2, r2, #45056
	mov	r1, #5
	strb	r1, [fp, #-46]
	ldr	r2, [r2, #2888]
	add	r2, r2, #3
	strb	r2, [fp, #-47]
.L651:
	sub	r1, fp, #48
	ldr	r0, [r4, #120]
	strb	r3, [fp, #-45]
	bl	FSP_ConfigInstance
	cmp	r0, #0
	bne	.L647
	ldr	r1, [r4, #224]
	sub	r3, fp, #52
	ldr	r0, [r4, #120]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #2
	beq	.L654
	cmp	r0, #0
	moveq	r0, #1
	bne	.L649
.L652:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L646:
	mov	r3, #1
	mov	r2, #5
	strb	r3, [fp, #-47]
	strb	r2, [fp, #-46]
	b	.L651
.L654:
	add	r0, r4, #584
	bl	ResetVoQueue
.L649:
	ldr	r1, .L655+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L652
.L653:
	mov	r3, r2
	ldr	r1, .L655+8
	mov	r2, r6
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #19
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L647:
	ldr	r1, .L655+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L652
.L656:
	.align	2
.L655:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC24
	.word	.LC23
	.word	.LC25
	UNWIND(.fnend)
	.size	MVC_ArrangeVahbMem, .-MVC_ArrangeVahbMem
	.align	2
	.global	MVC_RepairList
	.type	MVC_RepairList, %function
MVC_RepairList:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #11075584
	mov	r7, r0
	add	r3, r3, #40960
	ldrb	r3, [r3, #1032]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L659
	bcc	.L674
	cmp	r3, #2
	bne	.L680
.L675:
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L671:
	mov	r0, r7
.L680:
	bl	MVC_ClearCurrSlice
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L659:
	mov	r0, #2
.L660:
	movw	r6, #42036
	add	r8, r7, #11141120
	movt	r6, 169
	add	r6, r7, r6
	add	r8, r8, #12288
	add	r5, r7, #256
	ldr	r2, [r6, #4]!
	mov	lr, r7
	mov	r4, #0
	mov	r9, #1
	cmp	r2, #0
	beq	.L662
.L682:
	ldr	r10, [lr, #256]
	cmp	r10, #0
	bne	.L676
	mov	ip, r5
	mov	r3, r10
	b	.L664
.L665:
	ldr	r1, [ip, #4]!
	cmp	r1, #0
	bne	.L667
.L664:
	add	r3, r3, #1
	cmp	r3, r2
	bne	.L665
	ldr	r3, [r7, #224]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	bne	.L671
	ldr	r1, [r8, #3776]
	add	r1, r1, #704
.L667:
	mov	ip, r5
	mov	r3, #0
	b	.L673
.L669:
	ldr	r10, [ip, #4]!
.L673:
	add	r3, r3, #1
	cmp	r10, #0
	streq	r1, [ip]
	cmp	r3, r2
	bne	.L669
.L670:
	add	r4, r4, #1
	add	r5, r5, #132
	cmp	r0, r4
	add	lr, lr, #132
	bls	.L675
	ldr	r2, [r6, #4]!
	cmp	r2, #0
	bne	.L682
.L662:
	ldr	r3, [r7, #224]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	bne	.L671
	str	r9, [r6]
	ldr	r3, [r8, #3776]
	add	r3, r3, #704
	str	r3, [lr, #256]
	b	.L670
.L676:
	mov	r1, r10
	b	.L667
.L674:
	mov	r0, #1
	b	.L660
	UNWIND(.fnend)
	.size	MVC_RepairList, .-MVC_RepairList
	.align	2
	.global	MVC_GetShortTermPicPoint
	.type	MVC_GetShortTermPicPoint, %function
MVC_GetShortTermPicPoint:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #11075584
	add	r2, r3, #40960
	ldrb	r4, [r2, #1033]	@ zero_extendqisi2
	cmp	r4, #0
	beq	.L684
	ldrb	r2, [r2, #1034]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r4, #2
	moveq	r4, #1
.L684:
	add	r3, r3, #45056
	ldr	r5, [r3, #2896]
	cmp	r5, #0
	beq	.L692
	movw	r3, #47816
	mov	r2, #0
	movt	r3, 169
	add	r3, r0, r3
	b	.L689
.L702:
	ldrb	ip, [r0, #3]	@ zero_extendqisi2
	cmp	ip, #3
	beq	.L700
.L687:
	add	r2, r2, #1
	add	r3, r3, #4
	cmp	r2, r5
	beq	.L701
.L689:
	cmp	r4, #0
	ldr	r0, [r3]
	beq	.L702
	ldrb	lr, [r0, #3]	@ zero_extendqisi2
	tst	lr, #1
	beq	.L688
	ldr	ip, [r0, #740]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #65536
	beq	.L703
.L688:
	tst	lr, #2
	beq	.L687
	ldr	ip, [r0, #776]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #65536
	bne	.L687
	ldr	ip, [r0, #788]
	cmp	ip, r1
	bne	.L687
	add	r0, r0, #776
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L700:
	ldr	ip, [r0, #704]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #65536
	bne	.L687
	ldr	ip, [r0, #716]
	cmp	ip, r1
	bne	.L687
	add	r0, r0, #704
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L703:
	ldr	ip, [r0, #752]
	cmp	ip, r1
	bne	.L688
	add	r0, r0, #740
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L701:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L692:
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_GetShortTermPicPoint, .-MVC_GetShortTermPicPoint
	.align	2
	.global	MVC_GetLongTermPicPoint
	.type	MVC_GetLongTermPicPoint, %function
MVC_GetLongTermPicPoint:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #11075584
	add	r2, r3, #40960
	ldrb	r4, [r2, #1033]	@ zero_extendqisi2
	cmp	r4, #0
	beq	.L705
	ldrb	r2, [r2, #1034]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r4, #2
	moveq	r4, #1
.L705:
	add	r3, r3, #45056
	ldr	r5, [r3, #2900]
	cmp	r5, #0
	beq	.L713
	movw	r3, #47880
	mov	r2, #0
	movt	r3, 169
	add	r3, r0, r3
	b	.L710
.L723:
	ldrb	ip, [r0, #3]	@ zero_extendqisi2
	cmp	ip, #3
	beq	.L721
.L708:
	add	r2, r2, #1
	add	r3, r3, #4
	cmp	r2, r5
	beq	.L722
.L710:
	cmp	r4, #0
	ldr	r0, [r3]
	beq	.L723
	ldrb	lr, [r0, #3]	@ zero_extendqisi2
	tst	lr, #1
	beq	.L709
	ldr	ip, [r0, #740]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #256
	beq	.L724
.L709:
	tst	lr, #2
	beq	.L708
	ldr	ip, [r0, #776]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #256
	bne	.L708
	ldr	ip, [r0, #784]
	cmp	ip, r1
	bne	.L708
	add	r0, r0, #776
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L721:
	ldr	ip, [r0, #704]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #256
	bne	.L708
	ldr	ip, [r0, #712]
	cmp	ip, r1
	bne	.L708
	add	r0, r0, #704
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L724:
	ldr	ip, [r0, #748]
	cmp	ip, r1
	bne	.L709
	add	r0, r0, #740
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L722:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L713:
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_GetLongTermPicPoint, .-MVC_GetLongTermPicPoint
	.align	2
	.global	MVC_ReorderSTList
	.type	MVC_ReorderSTList, %function
MVC_ReorderSTList:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	ip, r1, asl #7
	ldr	r7, [fp, #4]
	add	r6, ip, r1, lsl #2
	mov	r1, r3
	add	r6, r6, #256
	mov	r5, r3
	mov	r8, r2
	add	r6, r0, r6
	bl	MVC_GetShortTermPicPoint
	ldr	r4, [r7]
	add	r3, r8, #1
	ldr	r1, [fp, #8]
	cmp	r3, r4
	ble	.L726
	add	lr, r6, r3, lsl #2
	mov	ip, r3
.L727:
	ldr	r4, [lr, #-4]!
	sub	ip, ip, #1
	str	r4, [lr, #4]
	ldr	r4, [r7]
	cmp	r4, ip
	blt	.L727
.L726:
	add	r2, r4, #1
	str	r2, [r7]
	str	r0, [r6, r4, asl #2]
	ldr	ip, [r7]
	cmp	r3, ip
	ldmltfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r2, r8, #2
	add	r4, r6, ip, lsl #2
	mov	lr, ip
	b	.L731
.L730:
	str	r0, [r6, lr, asl #2]
	add	lr, lr, #1
.L729:
	cmp	ip, r2
	beq	.L739
.L731:
	ldr	r0, [r4], #4
	add	ip, ip, #1
	cmp	r0, #0
	beq	.L729
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L730
	ldr	r3, [r0, #12]
	cmp	r3, r5
	bne	.L730
	ldr	r3, [r0, #4]
	ldr	r3, [r3, #56]
	cmp	r3, r1
	bne	.L730
	cmp	ip, r2
	bne	.L731
.L739:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_ReorderSTList, .-MVC_ReorderSTList
	.align	2
	.global	MVC_ReorderLTList
	.type	MVC_ReorderLTList, %function
MVC_ReorderLTList:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	ip, r1, asl #7
	ldr	r7, [fp, #4]
	add	r6, ip, r1, lsl #2
	mov	r1, r3
	add	r6, r6, #256
	mov	r5, r3
	mov	r8, r2
	add	r6, r0, r6
	bl	MVC_GetLongTermPicPoint
	ldr	r4, [r7]
	add	r3, r8, #1
	ldr	r1, [fp, #8]
	cmp	r3, r4
	ble	.L741
	add	lr, r6, r3, lsl #2
	mov	ip, r3
.L742:
	ldr	r4, [lr, #-4]!
	sub	ip, ip, #1
	str	r4, [lr, #4]
	ldr	r4, [r7]
	cmp	r4, ip
	blt	.L742
.L741:
	add	r2, r4, #1
	str	r2, [r7]
	str	r0, [r6, r4, asl #2]
	ldr	ip, [r7]
	cmp	r3, ip
	ldmltfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r2, r8, #2
	add	r4, r6, ip, lsl #2
	mov	lr, ip
	b	.L746
.L745:
	str	r0, [r6, lr, asl #2]
	add	lr, lr, #1
.L744:
	cmp	ip, r2
	beq	.L757
.L746:
	ldr	r0, [r4], #4
	add	ip, ip, #1
	cmp	r0, #0
	beq	.L744
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L745
	ldr	r3, [r0, #8]
	cmp	r3, r5
	bne	.L745
	ldr	r3, [r0, #4]
	ldr	r3, [r3, #56]
	cmp	r3, r1
	bne	.L745
	cmp	ip, r2
	bne	.L746
.L757:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_ReorderLTList, .-MVC_ReorderLTList
	.align	2
	.global	MVC_GetMaxViewIdx
	.type	MVC_GetMaxViewIdx, %function
MVC_GetMaxViewIdx:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	ip, r0, #10747904
	movw	lr, #22868
	add	ip, ip, #20480
	movt	lr, 164
	add	lr, r0, lr
	ldr	r5, [ip, #2384]
	adds	r5, r5, #1
	beq	.L765
	ldr	ip, [ip, #2388]
	cmp	r1, ip
	beq	.L766
	mov	r6, r5
	mov	ip, #0
	b	.L760
.L762:
	ldr	r4, [lr, #4]!
	cmp	r1, r4
	beq	.L768
.L760:
	add	ip, ip, #1
	cmp	ip, r5
	bne	.L762
	cmp	r6, #0
	blt	.L769
.L759:
	cmp	r2, #0
	add	r6, r6, r3, lsl #1
	movwne	r3, #5718
	movweq	r3, #5726
	movt	r3, 41
	add	r3, r6, r3
	add	r0, r0, r3, lsl #2
	ldr	r0, [r0, #4]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L768:
	mov	r6, ip
	cmp	r6, #0
	bge	.L759
.L769:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L765:
	mov	r6, r5
	b	.L759
.L766:
	mov	r6, #0
	b	.L759
	UNWIND(.fnend)
	.size	MVC_GetMaxViewIdx, .-MVC_GetMaxViewIdx
	.align	2
	.global	mvc_get_inter_view_pic
	.type	mvc_get_inter_view_pic, %function
mvc_get_inter_view_pic:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	movw	ip, #27294
	mov	r4, #1632
	movt	ip, 42
	add	ip, r3, ip
	mla	r3, r4, r3, r0
	ldr	lr, [r0, ip, asl #2]
	movw	ip, #31360
	cmp	lr, #0
	movt	ip, 169
	add	ip, r3, ip
	beq	.L776
	add	r4, r0, #11141120
	mov	r3, #0
	mov	r0, ip
	add	r4, r4, #12288
	b	.L775
.L772:
	cmp	r3, lr
	add	r0, r0, #816
	beq	.L778
.L775:
	ldr	ip, [r0, #56]
	add	r3, r3, #1
	cmp	ip, r1
	bne	.L772
	ldrb	ip, [r4, #3131]	@ zero_extendqisi2
	cmp	ip, #0
	bne	.L773
	ldr	ip, [r0, #724]
	cmp	ip, r2
	bne	.L772
	add	r0, r0, #704
	ldmfd	sp, {r4, fp, sp, pc}
.L773:
	cmp	ip, #1
	beq	.L779
	cmp	ip, #2
	bne	.L772
	ldr	ip, [r0, #796]
	cmp	ip, r2
	bne	.L772
	add	r0, r0, #776
	ldmfd	sp, {r4, fp, sp, pc}
.L779:
	ldr	ip, [r0, #760]
	cmp	ip, r2
	bne	.L772
	add	r0, r0, #740
	ldmfd	sp, {r4, fp, sp, pc}
.L778:
	mov	r0, #0
	ldmfd	sp, {r4, fp, sp, pc}
.L776:
	mov	r0, lr
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	mvc_get_inter_view_pic, .-mvc_get_inter_view_pic
	.align	2
	.global	mvc_reorder_interview
	.type	mvc_reorder_interview, %function
mvc_reorder_interview:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, [fp, #8]
	mov	r7, r2
	ldr	r6, [fp, #4]
	mov	r5, r3
	mov	r8, r1
	mov	r1, r3
	mov	r2, r4, asl #7
	mov	r3, r4
	add	r4, r2, r4, lsl #2
	mov	r2, r6
	add	r4, r4, #256
	add	r4, r0, r4
	bl	mvc_get_inter_view_pic
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r3, [r7]
	add	r1, r8, #1
	cmp	r1, r3
	bls	.L782
	add	lr, r4, r1, lsl #2
	mov	ip, r1
.L783:
	ldr	r3, [lr, #-4]!
	sub	ip, ip, #1
	str	r3, [lr, #4]
	ldr	r3, [r7]
	cmp	r3, ip
	bcc	.L783
.L782:
	add	r2, r3, #1
	str	r2, [r7]
	str	r0, [r4, r3, asl #2]
	ldr	ip, [r7]
	cmp	r1, ip
	ldmccfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r3, r4, ip, lsl #2
	mov	lr, ip
	b	.L787
.L785:
	cmp	r1, ip
	str	r0, [r4, lr, asl #2]
	add	lr, lr, #1
	bcc	.L794
.L787:
	ldr	r0, [r3], #4
	add	ip, ip, #1
	cmp	r0, #0
	beq	.L785
	ldr	r2, [r0, #4]
	ldr	r2, [r2, #56]
	cmp	r2, r5
	bne	.L785
	ldr	r2, [r0, #20]
	cmp	r2, r6
	bne	.L785
	cmp	r1, ip
	bcs	.L787
.L794:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	mvc_reorder_interview, .-mvc_reorder_interview
	.align	2
	.global	MVC_ReorderRefPiclist
	.type	MVC_ReorderRefPiclist, %function
MVC_ReorderRefPiclist:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #68)
	sub	sp, sp, #68
	add	r5, r0, #11075584
	add	r9, r5, #40960
	str	r2, [fp, #-64]
	mov	r2, #0
	mov	r6, r0
	ldrb	r3, [r9, #1033]	@ zero_extendqisi2
	mov	r10, r1
	str	r2, [fp, #-48]
	cmp	r3, r2
	beq	.L796
	ldrb	r3, [r9, #1034]	@ zero_extendqisi2
	cmp	r3, r2
	movne	r3, #2
	moveq	r3, #1
.L796:
	cmp	r10, #1
	bls	.L844
.L795:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L844:
	cmp	r10, #0
	beq	.L845
	movw	r1, #41076
	movw	r8, #41340
	movw	r5, #41860
	movt	r1, 169
	movt	r8, 169
	movt	r5, 169
	add	r1, r6, r1
	add	r8, r6, r8
	add	r5, r6, r5
	movw	r2, #41600
	movt	r2, 169
	add	r2, r6, r2
	str	r2, [fp, #-100]
.L799:
	ldr	r0, [r6, #236]
	cmp	r3, #0
	mov	r2, #1
	ldr	r3, [r0, #2896]
	add	r3, r3, #4
	mov	r3, r2, asl r3
	str	r3, [fp, #-88]
	ldr	r3, [r9, #1060]
	ldrne	r2, [fp, #-88]
	movne	r3, r3, asl #1
	addne	r3, r3, #1
	str	r3, [fp, #-92]
	ldr	r3, [fp, #-64]
	movne	r2, r2, asl #1
	strne	r2, [fp, #-88]
	adds	r3, r3, #2
	str	r3, [fp, #-72]
	beq	.L795
	ldr	r2, [r1]
	cmp	r2, #3
	beq	.L795
	movw	r3, #22868
	str	r9, [fp, #-68]
	mov	r0, r3
	mov	r3, #0
	mov	r4, r3
	str	r3, [fp, #-76]
	str	r3, [fp, #-80]
	mov	r7, r3
	ldr	r3, [fp, #-92]
	movt	r0, 164
	mov	r9, r1
	add	r0, r6, r0
	str	r0, [fp, #-96]
	str	r3, [fp, #-60]
	mov	r3, #1
	str	r3, [fp, #-84]
	b	.L803
.L804:
	cmp	r2, #2
	beq	.L846
	ldr	r3, [fp, #-84]
	cmp	r3, #1
	beq	.L810
	ldr	r3, [fp, #-68]
	ldrb	r3, [r3, #1041]	@ zero_extendqisi2
	str	r3, [fp, #-56]
	mov	r3, r10, asl #1
.L811:
	cmp	r2, #4
	ldr	r2, [r5]
	beq	.L847
	add	r2, r2, #1
	add	r4, r2, r4
	ldr	r2, [fp, #-76]
	cmp	r2, r4
	rsble	r4, r2, r4
.L821:
	ldr	r2, [fp, #-56]
	add	r0, r6, #11141120
	add	r0, r0, #12288
	ldr	r1, [fp, #-64]
	cmp	r2, #0
	ldr	r2, [fp, #-80]
	add	r3, r3, r2
	movwne	r2, #5722
	add	r3, r3, r4
	movweq	r2, #5730
	movt	r2, 41
	add	r2, r3, r2
	add	r2, r6, r2, lsl #2
	ldr	r3, [r2, #4]
	sub	r2, fp, #48
	str	r10, [sp, #4]
	ldr	ip, [r0, #3796]
	mov	r0, r6
	str	ip, [sp]
	bl	mvc_reorder_interview
.L808:
	ldr	r3, [fp, #-72]
	add	r7, r7, #1
	cmp	r7, r3
	beq	.L795
	ldr	r2, [r9, #4]!
	add	r5, r5, #4
	add	r8, r8, #4
	cmp	r2, #3
	beq	.L795
.L803:
	cmp	r2, #1
	bhi	.L804
	cmp	r2, #0
	ldr	r3, [r8]
	bne	.L805
	ldr	r2, [fp, #-60]
	mvn	r3, r3
	adds	r3, r2, r3
	str	r3, [fp, #-60]
	bmi	.L848
.L806:
	ldr	r2, [fp, #-60]
	mov	r1, r10
	ldr	r3, [fp, #-92]
	mov	r0, r6
	cmp	r3, r2
	movlt	r3, r2
	ldrlt	r2, [fp, #-88]
	ldrge	r3, [fp, #-60]
	rsblt	r3, r2, r3
	ldr	r2, [fp, #-68]
	ldr	ip, [r2, #2672]
	sub	r2, fp, #48
	str	r2, [sp]
	ldr	r2, [fp, #-64]
	str	ip, [sp, #4]
	bl	MVC_ReorderSTList
	b	.L808
.L845:
	movw	r1, #40944
	movw	r8, #41208
	add	r2, r5, #41472
	movt	r1, 169
	movt	r8, 169
	add	r1, r6, r1
	add	r8, r6, r8
	str	r2, [fp, #-100]
	add	r5, r5, #41728
	b	.L799
.L847:
	mvn	r2, r2
	adds	r4, r2, r4
	ldrmi	r2, [fp, #-76]
	addmi	r4, r4, r2
	b	.L821
.L810:
	add	r3, r6, #10747904
	ldr	r1, [fp, #-68]
	add	r3, r3, #20480
	ldr	ip, [r3, #2384]
	ldr	r1, [r1, #2672]
	adds	ip, ip, #1
	beq	.L812
	ldr	r3, [r3, #2388]
	cmp	r1, r3
	beq	.L813
	ldr	r0, [fp, #-96]
	mov	r3, #0
	str	ip, [fp, #-80]
	b	.L814
.L816:
	ldr	lr, [r0, #4]!
	cmp	r1, lr
	beq	.L830
.L814:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L816
.L815:
	ldr	r3, [fp, #-68]
	mov	r4, ip
	ldr	r0, [fp, #-96]
	ldrb	r3, [r3, #1041]	@ zero_extendqisi2
	str	r3, [fp, #-56]
	mov	r3, #0
	b	.L826
.L818:
	ldr	lr, [r0, #4]!
	cmp	r1, lr
	beq	.L831
.L826:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L818
	cmp	r4, #0
	blt	.L832
.L825:
	ldr	r3, [fp, #-56]
	cmp	r3, #0
	mov	r3, r10, asl #1
	beq	.L819
	add	r4, r3, r4
	movw	r1, #5718
	movt	r1, 41
	add	r1, r4, r1
	mov	r0, #0
	str	r0, [fp, #-84]
	add	r1, r6, r1, lsl #2
	mvn	r4, #0
	ldr	r1, [r1, #4]
	str	r1, [fp, #-76]
	b	.L811
.L805:
	ldr	r2, [fp, #-60]
	add	r3, r3, #1
	add	r3, r2, r3
	ldr	r2, [fp, #-88]
	str	r3, [fp, #-60]
	cmp	r2, r3
	rsble	r3, r2, r3
	strle	r3, [fp, #-60]
	b	.L806
.L846:
	ldr	r1, [fp, #-68]
	sub	r0, fp, #48
	ldr	r3, [fp, #-100]
	ldr	r2, [fp, #-64]
	ldr	ip, [r1, #2672]
	mov	r1, r10
	ldr	r3, [r3, r7, asl #2]
	str	r0, [sp]
	mov	r0, r6
	str	ip, [sp, #4]
	bl	MVC_ReorderLTList
	b	.L808
.L830:
	str	r3, [fp, #-80]
	b	.L815
.L831:
	mov	r4, r3
	cmp	r4, #0
	bge	.L825
.L832:
	mov	r3, #0
	mvn	r4, #0
	mov	r1, r3
	str	r3, [fp, #-84]
	str	r1, [fp, #-76]
	mov	r3, r10, asl #1
	b	.L811
.L819:
	add	r4, r3, r4
	movw	r1, #5726
	movt	r1, 41
	add	r1, r4, r1
	ldr	r0, [fp, #-56]
	mvn	r4, #0
	add	r1, r6, r1, lsl #2
	str	r0, [fp, #-84]
	ldr	r1, [r1, #4]
	str	r1, [fp, #-76]
	b	.L811
.L848:
	ldr	r2, [fp, #-88]
	add	r3, r3, r2
	str	r3, [fp, #-60]
	b	.L806
.L812:
	ldr	r3, [fp, #-68]
	mov	r4, ip
	str	ip, [fp, #-80]
	ldrb	r3, [r3, #1041]	@ zero_extendqisi2
	str	r3, [fp, #-56]
	b	.L825
.L813:
	ldr	r1, [fp, #-68]
	mov	r3, #0
	mov	r4, r3
	str	r3, [fp, #-80]
	ldrb	r1, [r1, #1041]	@ zero_extendqisi2
	str	r1, [fp, #-56]
	b	.L825
	UNWIND(.fnend)
	.size	MVC_ReorderRefPiclist, .-MVC_ReorderRefPiclist
	.align	2
	.global	MVC_ReorderListX
	.type	MVC_ReorderListX, %function
MVC_ReorderListX:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r4, r0, #11075584
	mov	r6, r0
	add	r5, r4, #40960
	ldrb	r1, [r5, #1032]	@ zero_extendqisi2
	cmp	r1, #2
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r7, r4, #36864
	ldrb	r3, [r7, #4076]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L861
.L852:
	ldr	r3, [r5, #1092]
	cmp	r1, #1
	add	r3, r3, #1
	str	r3, [r5, #1080]
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldrb	r3, [r7, #4077]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L862
.L854:
	add	r4, r4, #40960
	ldr	r3, [r4, #1096]
	add	r3, r3, #1
	str	r3, [r4, #1084]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L861:
	mov	r1, #0
	ldr	r2, [r5, #1092]
	bl	MVC_ReorderRefPiclist
	ldrb	r1, [r5, #1032]	@ zero_extendqisi2
	b	.L852
.L862:
	ldr	r2, [r5, #1096]
	mov	r0, r6
	bl	MVC_ReorderRefPiclist
	b	.L854
	UNWIND(.fnend)
	.size	MVC_ReorderListX, .-MVC_ReorderListX
	.align	2
	.global	MVC_GenPiclistfromFrmlist
	.type	MVC_GenPiclistfromFrmlist, %function
MVC_GenPiclistfromFrmlist:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	cmp	r2, #31
	ldr	r6, [fp, #8]
	mov	r7, r1
	ldr	lr, .L926
	movcc	r4, r2
	ldr	ip, .L926+4
	movcs	r4, #31
	cmp	r6, #0
	str	r3, [fp, #-52]
	movne	r6, lr
	moveq	r6, ip
	cmp	r0, #1
	moveq	r5, #0
	moveq	r10, r5
	beq	.L866
	cmp	r0, #2
	moveq	r5, #0
	moveq	r10, r5
	bne	.L874
.L875:
	cmp	r10, r4
	movcs	r3, #0
	movcc	r3, #1
	cmp	r5, r4
	str	r3, [fp, #-48]
	movcs	r2, #0
	movcc	r2, #1
	orrs	r3, r2, r3
	beq	.L874
	cmp	r2, #0
	beq	.L880
	add	r8, r7, r5, lsl #2
	b	.L879
.L876:
	add	r5, r5, #1
	cmp	r4, r5
	bls	.L880
.L879:
	mov	r9, r8
	ldr	r0, [r8], #4
	ldrb	ip, [r0, #2]	@ zero_extendqisi2
	tst	ip, #2
	beq	.L876
	add	r0, r0, #776
	blx	r6
	cmp	r0, #0
	beq	.L876
	ldr	r3, [fp, #4]
	add	r5, r5, #1
	ldr	r2, [r9]
	ldr	r0, [r3]
	add	r2, r2, #776
	ldr	r3, [fp, #-52]
	str	r2, [r3, r0, asl #2]
	ldr	r3, [fp, #4]
	ldr	r2, [r3]
	add	r2, r2, #1
	str	r2, [r3]
.L880:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	addne	r8, r7, r10, lsl #2
	bne	.L882
	b	.L875
.L881:
	add	r10, r10, #1
	cmp	r4, r10
	bls	.L875
.L882:
	mov	r9, r8
	ldr	r0, [r8], #4
	ldrb	r2, [r0, #2]	@ zero_extendqisi2
	tst	r2, #1
	beq	.L881
	add	r0, r0, #740
	blx	r6
	cmp	r0, #0
	beq	.L881
	ldr	r3, [fp, #4]
	add	r10, r10, #1
	ldr	r2, [r9]
	ldr	r0, [r3]
	add	r2, r2, #740
	ldr	r3, [fp, #-52]
	str	r2, [r3, r0, asl #2]
	ldr	r3, [fp, #4]
	ldr	r2, [r3]
	add	r2, r2, #1
	str	r2, [r3]
	b	.L875
.L925:
	add	r0, r0, #740
	blx	r6
	cmp	r0, #0
	beq	.L867
	ldr	r3, [fp, #4]
	add	r10, r10, #1
	ldr	r2, [r8]
	ldr	r0, [r3]
	add	r2, r2, #740
	ldr	r3, [fp, #-52]
	str	r2, [r3, r0, asl #2]
	ldr	r3, [fp, #4]
	ldr	r2, [r3]
	add	r2, r2, #1
	str	r2, [r3]
.L871:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	addne	r8, r7, r5, lsl #2
	bne	.L873
	b	.L866
.L872:
	add	r5, r5, #1
	cmp	r4, r5
	bls	.L866
.L873:
	mov	r9, r8
	ldr	r0, [r8], #4
	ldrb	r2, [r0, #2]	@ zero_extendqisi2
	tst	r2, #2
	beq	.L872
	add	r0, r0, #776
	blx	r6
	cmp	r0, #0
	beq	.L872
	ldr	r3, [fp, #4]
	add	r5, r5, #1
	ldr	r2, [r9]
	ldr	r0, [r3]
	add	r2, r2, #776
	ldr	r3, [fp, #-52]
	str	r2, [r3, r0, asl #2]
	ldr	r3, [fp, #4]
	ldr	r2, [r3]
	add	r2, r2, #1
	str	r2, [r3]
.L866:
	cmp	r10, r4
	movcs	r2, #0
	movcc	r2, #1
	cmp	r5, r4
	movcs	r3, #0
	movcc	r3, #1
	str	r3, [fp, #-48]
	orrs	r3, r3, r2
	beq	.L874
	cmp	r2, #0
	beq	.L871
	add	r9, r7, r10, lsl #2
	b	.L870
.L867:
	add	r10, r10, #1
	cmp	r4, r10
	bls	.L871
.L870:
	mov	r8, r9
	ldr	r0, [r9], #4
	ldrb	ip, [r0, #2]	@ zero_extendqisi2
	tst	ip, #1
	beq	.L867
	b	.L925
.L874:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L927:
	.align	2
.L926:
	.word	MVC_IsLTRefFlg
	.word	MVC_IsSTRefFlg
	UNWIND(.fnend)
	.size	MVC_GenPiclistfromFrmlist, .-MVC_GenPiclistfromFrmlist
	.align	2
	.global	MVC_GetBaseViewId
	.type	MVC_GetBaseViewId, %function
MVC_GetBaseViewId:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #12992
	mov	r2, #0
	add	r3, r3, #16
.L931:
	ldr	r1, [r3]
	cmp	r1, #0
	beq	.L929
	ldrb	r1, [r3, #-4]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L939
.L929:
	add	r2, r2, #1
	add	r3, r3, #335872
	cmp	r2, #32
	add	r3, r3, #308
	bne	.L931
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L939:
	movw	r3, #8500
	movt	r3, 5
	mla	r2, r3, r2, r0
	add	r2, r2, #12992
	ldr	r0, [r2, #20]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_GetBaseViewId, .-MVC_GetBaseViewId
	.align	2
	.global	MVC_GetVOIdx
	.type	MVC_GetVOIdx, %function
MVC_GetVOIdx:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #0
	beq	.L944
	ldr	r3, [r0]
	cmp	r3, r2
	beq	.L945
	mov	ip, r0
	mov	r3, #0
	mov	r0, r1
	b	.L942
.L943:
	ldr	lr, [ip, #4]!
	cmp	lr, r2
	beq	.L946
.L942:
	add	r3, r3, #1
	cmp	r3, r1
	bne	.L943
	ldmfd	sp, {fp, sp, pc}
.L946:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L944:
	mov	r0, r1
	ldmfd	sp, {fp, sp, pc}
.L945:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_GetVOIdx, .-MVC_GetVOIdx
	.align	2
	.global	MVC_is_view_id_in_ref_view_list
	.type	MVC_is_view_id_in_ref_view_list, %function
MVC_is_view_id_in_ref_view_list:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r2, #0
	beq	.L951
	ldr	r3, [r1]
	cmp	r3, r0
	beq	.L952
	mov	r3, #0
	b	.L949
.L950:
	ldr	ip, [r1, #4]!
	cmp	ip, r0
	beq	.L948
.L949:
	add	r3, r3, #1
	cmp	r3, r2
	mov	lr, r3
	bne	.L950
.L948:
	cmp	r2, #0
	cmpne	r2, lr
	movhi	r0, #1
	movls	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L951:
	mov	lr, r2
	b	.L948
.L952:
	mov	lr, #0
	b	.L948
	UNWIND(.fnend)
	.size	MVC_is_view_id_in_ref_view_list, .-MVC_is_view_id_in_ref_view_list
	.align	2
	.global	MVC_GenPiclistfromFrmlist_Interview
	.type	MVC_GenPiclistfromFrmlist_Interview, %function
MVC_GenPiclistfromFrmlist_Interview:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #1
	ldr	ip, [fp, #4]
	beq	.L969
	cmp	r0, #2
	ldmnefd	sp, {fp, sp, pc}
	cmp	r2, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r0, [ip]
	add	r1, r1, #776
	mov	lr, #0
.L960:
	add	lr, lr, #1
	str	r1, [r3, r0, asl #2]
	cmp	lr, r2
	ldr	r0, [ip]
	add	r1, r1, #816
	add	r0, r0, #1
	str	r0, [ip]
	bne	.L960
	ldmfd	sp, {fp, sp, pc}
.L969:
	cmp	r2, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r0, [ip]
	add	r1, r1, #740
	mov	lr, #0
.L956:
	add	lr, lr, #1
	str	r1, [r3, r0, asl #2]
	cmp	lr, r2
	ldr	r0, [ip]
	add	r1, r1, #816
	add	r0, r0, #1
	str	r0, [ip]
	bne	.L956
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_GenPiclistfromFrmlist_Interview, .-MVC_GenPiclistfromFrmlist_Interview
	.align	2
	.global	mvc_append_interview_list
	.type	mvc_append_interview_list, %function
mvc_append_interview_list:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	lr, r0, #10747904
	add	lr, lr, #20480
	add	ip, r0, #11075584
	add	r5, ip, #40960
	mov	r9, r0
	ldr	r6, [lr, #2384]
	movw	r0, #22868
	movt	r0, 164
	str	r2, [fp, #-48]
	adds	r6, r6, #1
	ldr	r7, [r5, #2672]
	add	r0, r9, r0
	beq	.L989
	ldr	r2, [lr, #2388]
	cmp	r7, r2
	beq	.L990
	mov	r2, #0
	b	.L972
.L973:
	ldr	lr, [r0, #4]!
	cmp	r7, lr
	beq	.L971
.L972:
	add	r2, r2, #1
	cmp	r2, r6
	mov	r4, r2
	bne	.L973
.L971:
	ldrb	r2, [r5, #1041]	@ zero_extendqisi2
	add	r4, r4, r1, lsl #1
	add	r6, r9, #11141120
	add	ip, ip, #45056
	cmp	r2, #0
	add	r6, r6, #12288
	movwne	r2, #5718
	movweq	r2, #5726
	movtne	r2, 41
	movteq	r2, 41
	addne	r2, r4, r2
	addeq	r2, r4, r2
	ldrb	r8, [r6, #3131]	@ zero_extendqisi2
	addne	r4, r9, r4, lsl #2
	add	r2, r9, r2, lsl #2
	movwne	r10, #22892
	addeq	r4, r9, r4, lsl #2
	movweq	r10, #22924
	ldr	r7, [r2, #4]
	sub	r8, r8, #2
	ldr	r2, [ip, #2888]
	movt	r10, 164
	clz	r8, r8
	add	r10, r4, r10
	subs	r4, r2, #1
	mov	r8, r8, lsr #5
	bmi	.L970
	movw	r5, #28322
	movt	r5, 42
	add	r5, r2, r5
	mov	r2, r3
	mov	r3, r9
	add	r5, r9, r5, lsl #2
	mov	r9, r2
	b	.L987
.L1013:
	ldrb	r2, [r1, #2]	@ zero_extendqisi2
	cmp	r2, #3
	ldreq	r0, [r1, #724]
	bne	.L977
.L979:
	add	r2, r1, r8
	ldrb	r2, [r2, #12]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L977
	ldr	r2, [r6, #3796]
	cmp	r2, r0
	beq	.L1012
.L977:
	subs	r4, r4, #1
	bmi	.L970
.L987:
	ldr	r1, [r5, #-4]!
	cmp	r1, #0
	beq	.L977
	ldrb	r2, [r6, #3131]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1013
	cmp	r2, #1
	beq	.L1014
	cmp	r2, #2
	bne	.L977
	ldrb	r0, [r6, #3129]	@ zero_extendqisi2
	ldrb	r2, [r1, #2]	@ zero_extendqisi2
	cmp	r0, #0
	ubfx	r2, r2, #1, #1
	beq	.L982
	ldr	r0, [r6, #3776]
	ldr	ip, [r1, #760]
	ldr	r0, [r0, #760]
	cmp	ip, r0
	movne	r2, #0
	andeq	r2, r2, #1
.L982:
	cmp	r2, #0
	ldrne	r0, [r1, #796]
	bne	.L979
	subs	r4, r4, #1
	bpl	.L987
.L970:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1014:
	ldrb	r0, [r6, #3129]	@ zero_extendqisi2
	ldrb	r2, [r1, #2]	@ zero_extendqisi2
	cmp	r0, #0
	and	r2, r2, #1
	beq	.L981
	ldr	r0, [r6, #3776]
	ldr	ip, [r1, #796]
	ldr	r0, [r0, #796]
	cmp	ip, r0
	movne	r2, #0
	andeq	r2, r2, #1
.L981:
	cmp	r2, #0
	ldrne	r0, [r1, #760]
	bne	.L979
	b	.L977
.L1012:
	cmp	r7, #0
	ldr	lr, [r1, #56]
	beq	.L977
	ldr	r2, [r10]
	cmp	lr, r2
	beq	.L983
	mov	r0, r10
	mov	r2, #0
.L984:
	add	r2, r2, #1
	cmp	r2, r7
	beq	.L977
	ldr	ip, [r0, #4]!
	cmp	lr, ip
	bne	.L984
.L983:
	str	r3, [fp, #-52]
	mov	r2, #816
	ldr	r3, .L1015
	ldr	r0, [r9]
	ldr	ip, [r3, #52]
	ldr	r3, [fp, #-48]
	mla	r0, r2, r0, r3
	blx	ip
	ldr	r2, [r9]
	ldr	r0, [fp, #-48]
	mov	r1, #816
	mov	ip, #816
	ldr	r3, [fp, #-52]
	mla	r2, r1, r2, r0
	str	r2, [r2, #780]
	str	r2, [r2, #744]
	str	r2, [r2, #708]
	ldr	r2, [r9]
	ldr	r1, [r3, #52]
	mla	r2, ip, r2, r0
	sub	r1, r1, #1
	str	r1, [r2, #48]
	ldr	r2, [r9]
	cmp	r2, r7
	beq	.L970
	add	r2, r2, #1
	str	r2, [r9]
	b	.L977
.L989:
	mov	r4, r6
	b	.L971
.L990:
	mov	r4, #0
	b	.L971
.L1016:
	.align	2
.L1015:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	mvc_append_interview_list, .-mvc_append_interview_list
	.align	2
	.global	MVC_InitListX
	.type	MVC_InitListX, %function
MVC_InitListX:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 208
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #220)
	sub	sp, sp, #220
	add	r2, r0, #11075584
	add	r5, r2, #40960
	add	r7, r0, #11141120
	mov	r3, #0
	add	r7, r7, #12288
	ldrb	r9, [r5, #1032]	@ zero_extendqisi2
	mov	r6, r0
	str	r3, [r5, #2684]
	cmp	r9, r3
	str	r3, [r5, #2680]
	ldrb	r4, [r7, #3131]	@ zero_extendqisi2
	bne	.L1018
	cmp	r4, r3
	add	r3, r2, #45056
	str	r3, [fp, #-240]
	bne	.L1176
	ldr	ip, [r3, #2896]
	cmp	ip, #0
	beq	.L1102
	movw	r1, #47812
	mov	r3, r4
	movt	r1, 169
	add	r1, r0, r1
	b	.L1024
.L1023:
	cmp	r3, ip
	beq	.L1022
.L1024:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #3]	@ zero_extendqisi2
	cmp	r0, #3
	bne	.L1023
	ldr	r0, [r2, #704]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	cmp	r0, #65536
	addeq	r0, r4, #64
	addeq	r2, r2, #704
	addeq	r4, r4, #1
	streq	r2, [r6, r0, asl #2]
	cmp	r3, ip
	bne	.L1024
.L1022:
	add	r3, r6, #256
	mov	r1, r4
	str	r3, [fp, #-244]
	mov	r2, #4
	mov	r0, r3
	ldr	r3, .L1186
	bl	qsort
	ldr	r3, [fp, #-240]
	str	r4, [r5, #1080]
	ldr	r1, [r3, #2900]
	cmp	r1, #0
	beq	.L1103
	movw	r0, #47876
	mov	r8, r4
	movt	r0, 169
	mov	r3, #0
	add	r0, r6, r0
	b	.L1027
.L1026:
	cmp	r3, r1
	beq	.L1177
.L1027:
	ldr	r2, [r0, #4]!
	add	r3, r3, #1
	ldrb	ip, [r2, #3]	@ zero_extendqisi2
	cmp	ip, #3
	bne	.L1026
	ldr	ip, [r2, #704]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #256
	addeq	ip, r8, #64
	addeq	r2, r2, #704
	addeq	r8, r8, #1
	streq	r2, [r6, ip, asl #2]
	cmp	r3, r1
	bne	.L1027
.L1177:
	rsb	r1, r4, r8
.L1025:
	add	r0, r4, #64
	ldr	r3, .L1186+4
	mov	r2, #4
	add	r0, r6, r0, lsl #2
	bl	qsort
	str	r8, [r5, #1080]
	b	.L1028
.L1018:
	cmp	r4, #0
	beq	.L1045
	add	r2, r2, #45056
	str	r2, [fp, #-240]
	ldr	ip, [r2, #2896]
	cmp	ip, #0
	beq	.L1178
	movw	r9, #47812
	mov	r4, r3
	movt	r9, 169
	add	r9, r0, r9
	mov	r1, r9
.L1064:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #2]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1063
	sub	r0, fp, #44
	ldr	lr, [r7, #3796]
	add	r8, r0, r4, lsl #2
	ldr	r0, [r2, #32]
	cmp	lr, r0
	strge	r2, [r8, #-192]
	addge	r4, r4, #1
.L1063:
	cmp	r3, ip
	bne	.L1064
	sub	r10, fp, #236
	ldr	r3, .L1186+8
	mov	r2, #4
	mov	r1, r4
	mov	r0, r10
	bl	qsort
	ldr	r3, [fp, #-240]
	ldr	r8, [r3, #2896]
	cmp	r8, #0
	beq	.L1173
.L1100:
	mov	r3, r9
	mov	r2, #0
	mov	r9, r4
.L1067:
	ldr	r1, [r3, #4]!
	add	r2, r2, #1
	ldrb	r0, [r1, #2]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1066
	sub	r0, fp, #44
	ldr	ip, [r7, #3796]
	add	lr, r0, r9, lsl #2
	ldr	r0, [r1, #32]
	cmp	ip, r0
	strlt	r1, [lr, #-192]
	addlt	r9, r9, #1
.L1066:
	cmp	r2, r8
	bne	.L1067
	rsb	r8, r4, r9
	mov	r3, r4, asl #2
	add	r0, r10, r3
	str	r3, [fp, #-244]
	mov	r1, r8
	ldr	r3, .L1186+12
	mov	r2, #4
	bl	qsort
	cmp	r4, #0
	subeq	ip, fp, #172
	beq	.L1068
.L1095:
	sub	ip, fp, #172
	mov	r2, r10
	add	r8, ip, r8, lsl #2
	mov	r3, #0
.L1069:
	add	r3, r3, #1
	ldr	r1, [r2], #4
	cmp	r3, r4
	str	r1, [r8], #4
	bcc	.L1069
.L1068:
	cmp	r9, r4
	bls	.L1070
	ldr	r3, [fp, #-244]
	add	r2, r10, r3
	mov	r3, ip
.L1071:
	add	r4, r4, #1
	ldr	r1, [r2], #4
	cmp	r4, r9
	str	r1, [r3], #4
	bne	.L1071
.L1070:
	movw	r8, #42040
	mov	r4, #0
	add	r3, r6, #256
	str	r4, [r5, #1080]
	str	r4, [r5, #1084]
	mov	r1, r10
	ldrb	r0, [r7, #3131]	@ zero_extendqisi2
	mov	r2, r9
	str	r4, [sp, #4]
	movt	r8, 169
	add	r8, r6, r8
	str	r8, [sp]
	str	ip, [fp, #-252]
	movw	r10, #42044
	str	r3, [fp, #-244]
	bl	MVC_GenPiclistfromFrmlist
	ldr	ip, [fp, #-252]
	add	r3, r6, #388
	ldrb	r0, [r7, #3131]	@ zero_extendqisi2
	mov	r2, r9
	str	r4, [sp, #4]
	movt	r10, 169
	mov	r1, ip
	add	r10, r6, r10
	str	r10, [sp]
	str	r3, [fp, #-248]
	bl	MVC_GenPiclistfromFrmlist
	ldr	r3, [fp, #-240]
	ldr	r9, [r3, #2900]
	cmp	r9, r4
	subeq	ip, fp, #108
	beq	.L1072
	movw	r3, #47876
	sub	ip, fp, #108
	movt	r3, 169
	add	r3, r6, r3
	mov	r2, ip
.L1073:
	add	r4, r4, #1
	ldr	r1, [r3, #4]!
	cmp	r4, r9
	str	r1, [r2], #4
	bne	.L1073
.L1072:
	mov	r0, ip
	ldr	r3, .L1186+16
	mov	r2, #4
	mov	r1, r9
	str	ip, [fp, #-240]
	bl	qsort
	ldr	ip, [fp, #-240]
	mov	r4, #1
	ldrb	r0, [r7, #3131]	@ zero_extendqisi2
	mov	r2, r9
	ldr	r3, [fp, #-244]
	mov	r1, ip
	str	r4, [sp, #4]
	str	r8, [sp]
	bl	MVC_GenPiclistfromFrmlist
	ldr	ip, [fp, #-240]
	ldrb	r0, [r7, #3131]	@ zero_extendqisi2
	mov	r2, r9
	str	r4, [sp, #4]
	ldr	r3, [fp, #-248]
	mov	r1, ip
	str	r10, [sp]
	bl	MVC_GenPiclistfromFrmlist
	ldr	r4, [r5, #1080]
	ldr	r3, [r5, #1084]
	rsb	r3, r3, r4
	clz	r3, r3
	mov	r3, r3, lsr #5
.L1062:
	cmp	r4, #1
	movls	r3, #0
	andhi	r3, r3, #1
	cmp	r3, #0
	beq	.L1074
	cmp	r4, #0
	beq	.L1075
	ldr	lr, [r6, #256]
	ldr	r3, [r6, #388]
	cmp	lr, r3
	bne	.L1074
	ldr	r1, [fp, #-244]
	add	r2, r6, #388
	mov	r3, #0
	b	.L1076
.L1077:
	ldr	ip, [r1, #4]!
	ldr	r0, [r2, #4]!
	cmp	ip, r0
	bne	.L1074
.L1076:
	add	r3, r3, #1
	cmp	r3, r4
	bne	.L1077
.L1078:
	ldr	r3, [r6, #392]
	str	lr, [r6, #392]
	str	r3, [r6, #388]
	ldrb	r3, [r5, #1044]	@ zero_extendqisi2
.L1096:
	cmp	r3, #0
	bne	.L1165
.L1079:
	movw	r4, #31360
	movw	r3, #43640
	movt	r4, 169
	add	r4, r6, r4
	mov	r0, r6
	movt	r3, 169
	mov	r1, #0
	mov	r2, r4
	add	r3, r6, r3
	bl	mvc_append_interview_list
	ldrb	r0, [r7, #3131]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L1179
	ldr	r1, [r5, #2680]
	ldr	ip, [r5, #1080]
	cmp	r1, #0
	beq	.L1081
	add	r2, ip, #63
	movw	r3, #32064
	movt	r3, 169
	add	r3, r6, r3
	add	r2, r6, r2, lsl #2
.L1082:
	add	r0, r0, #1
	str	r3, [r2, #4]!
	cmp	r0, r1
	add	r3, r3, #816
	bne	.L1082
	add	ip, ip, r0
.L1081:
	str	ip, [r5, #1080]
.L1083:
	ldrb	r1, [r5, #1032]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L1180
.L1166:
	ldr	r0, [r5, #1080]
.L1080:
	cmp	r1, #0
	bne	.L1038
	cmp	r0, #0
	ldreq	r1, .L1186+20
	beq	.L1167
.L1037:
	ldr	r2, [r5, #1092]
	ldr	r3, [r5, #1096]
	add	r2, r2, #1
	ldr	r1, [r5, #1084]
	cmp	r0, r2
	add	r3, r3, #1
	movcc	r2, r0
	cmp	r3, r1
	str	r2, [r5, #1080]
	movcs	r3, r1
	cmp	r2, #32
	str	r3, [r5, #1084]
	bhi	.L1089
.L1097:
	add	r1, r2, #63
	mov	r0, #0
	add	r1, r6, r1, lsl #2
.L1090:
	add	r2, r2, #1
	str	r0, [r1, #4]!
	cmp	r2, #32
	bls	.L1090
.L1089:
	cmp	r3, #32
	bhi	.L1093
	add	r3, r3, #96
	add	r1, r6, #516
	mov	r2, #0
	add	r6, r6, r3, lsl #2
.L1092:
	str	r2, [r6, #4]!
	cmp	r6, r1
	bne	.L1092
.L1093:
	mov	r0, #0
.L1159:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1045:
	add	r3, r2, #45056
	str	r3, [fp, #-240]
	ldr	r10, [r3, #2896]
	cmp	r10, #0
	beq	.L1048
	movw	r9, #47812
	mov	r3, r4
	movt	r9, 169
	add	r9, r0, r9
	mov	r1, r9
	b	.L1050
.L1049:
	cmp	r3, r10
	beq	.L1181
.L1050:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #3]	@ zero_extendqisi2
	cmp	r0, #3
	bne	.L1049
	ldr	r0, [r2, #720]
	add	lr, r4, #64
	ldr	ip, [r7, #3800]
	add	r2, r2, #704
	cmp	ip, r0
	strge	r2, [r6, lr, asl #2]
	addge	r4, r4, #1
	cmp	r3, r10
	bne	.L1050
.L1181:
	add	r3, r6, #256
	mov	r2, #4
	str	r3, [fp, #-244]
	mov	r1, r4
	mov	r0, r3
	ldr	r3, .L1186+24
	bl	qsort
	ldr	r3, [fp, #-240]
	ldr	r8, [r3, #2896]
	cmp	r8, #0
	beq	.L1172
.L1098:
	mov	r3, r9
	mov	r10, r4
	mov	r2, #0
	b	.L1053
.L1052:
	cmp	r2, r8
	beq	.L1182
.L1053:
	ldr	r1, [r3, #4]!
	add	r2, r2, #1
	ldrb	r0, [r1, #3]	@ zero_extendqisi2
	cmp	r0, #3
	bne	.L1052
	ldr	r0, [r1, #720]
	add	lr, r10, #64
	ldr	ip, [r7, #3800]
	add	r1, r1, #704
	cmp	ip, r0
	strlt	r1, [r6, lr, asl #2]
	addlt	r10, r10, #1
	cmp	r2, r8
	bne	.L1053
.L1182:
	rsb	r8, r4, r10
	add	r0, r4, #64
	ldr	r3, .L1186+28
	mov	r2, #4
	mov	r1, r8
	add	r0, r6, r0, lsl #2
	bl	qsort
	add	r9, r10, #64
	cmp	r4, #0
	add	r9, r6, r9, lsl #2
	beq	.L1055
.L1094:
	add	r8, r8, #96
	add	r2, r6, #252
	mov	r3, #0
	add	r8, r6, r8, lsl #2
.L1056:
	add	r3, r3, #1
	ldr	r1, [r2, #4]!
	cmp	r3, r4
	str	r1, [r8, #4]!
	bcc	.L1056
.L1055:
	cmp	r10, r4
	bls	.L1057
	add	r3, r4, #63
	add	r2, r6, #384
	add	r3, r6, r3, lsl #2
.L1058:
	add	r4, r4, #1
	ldr	r1, [r3, #4]!
	cmp	r4, r10
	str	r1, [r2, #4]!
	bne	.L1058
.L1057:
	ldr	r3, [fp, #-240]
	str	r10, [r5, #1084]
	str	r10, [r5, #1080]
	ldr	r1, [r3, #2900]
	cmp	r1, #0
	beq	.L1104
	movw	r0, #47876
	mov	r4, r10
	movt	r0, 169
	mov	r3, #0
	add	r0, r6, r0
	b	.L1061
.L1060:
	cmp	r3, r1
	beq	.L1183
.L1061:
	ldr	r2, [r0, #4]!
	add	r3, r3, #1
	ldrb	ip, [r2, #2]	@ zero_extendqisi2
	cmp	ip, #3
	bne	.L1060
	ldrb	ip, [r2, #705]	@ zero_extendqisi2
	cmp	ip, #1
	addeq	ip, r6, r4, lsl #2
	addeq	r2, r2, #704
	addeq	r4, r4, #1
	streq	r2, [ip, #256]
	streq	r2, [ip, #388]
	cmp	r3, r1
	bne	.L1061
.L1183:
	rsb	r1, r10, r4
.L1059:
	mov	r0, r9
	ldr	r3, .L1186+4
	mov	r2, #4
	bl	qsort
	ldr	r1, [r5, #1080]
	ldr	r3, .L1186+4
	mov	r2, #4
	add	r0, r1, #97
	rsb	r1, r1, r4
	add	r0, r6, r0, lsl #2
	bl	qsort
	str	r4, [r5, #1084]
	str	r4, [r5, #1080]
	mov	r3, #1
	b	.L1062
.L1176:
	ldr	lr, [r3, #2896]
	cmp	lr, #0
	moveq	r9, lr
	beq	.L1021
	movw	r1, #47812
	mov	r3, r9
	movt	r1, 169
	add	r1, r0, r1
.L1030:
	ldr	r2, [r1, #4]!
	sub	r0, fp, #44
	add	ip, r0, r9, lsl #2
	add	r3, r3, #1
	ldrb	r0, [r2, #3]	@ zero_extendqisi2
	cmp	r0, #0
	strne	r2, [ip, #-192]
	addne	r9, r9, #1
	cmp	r3, lr
	bne	.L1030
.L1021:
	mov	r1, r9
	ldr	r3, .L1186+32
	mov	r2, #4
	sub	r0, fp, #236
	movw	r8, #42040
	bl	qsort
	mov	r4, #0
	add	r3, r6, #256
	str	r4, [r5, #1080]
	mov	r2, r9
	ldrb	r0, [r7, #3131]	@ zero_extendqisi2
	sub	r1, fp, #236
	str	r4, [sp, #4]
	movt	r8, 169
	add	r8, r6, r8
	str	r8, [sp]
	str	r3, [fp, #-244]
	bl	MVC_GenPiclistfromFrmlist
	ldr	r3, [fp, #-240]
	ldr	r9, [r3, #2900]
	cmp	r9, r4
	subeq	ip, fp, #108
	beq	.L1031
	movw	r3, #47876
	sub	ip, fp, #108
	movt	r3, 169
	add	r3, r6, r3
	mov	r2, ip
.L1032:
	add	r4, r4, #1
	ldr	r1, [r3, #4]!
	cmp	r4, r9
	str	r1, [r2], #4
	bne	.L1032
.L1031:
	mov	r0, ip
	ldr	r3, .L1186+16
	mov	r2, #4
	mov	r1, r9
	str	ip, [fp, #-240]
	bl	qsort
	ldr	ip, [fp, #-240]
	mov	r3, #1
	ldrb	r0, [r7, #3131]	@ zero_extendqisi2
	mov	r2, r9
	str	r3, [sp, #4]
	str	r8, [sp]
	mov	r1, ip
	ldr	r3, [fp, #-244]
	bl	MVC_GenPiclistfromFrmlist
.L1028:
	ldrb	r3, [r5, #1044]	@ zero_extendqisi2
	mov	r2, #0
	str	r2, [r5, #1084]
	cmp	r3, r2
	beq	.L1079
	ldr	r0, [r5, #1080]
	cmp	r0, #0
	bne	.L1184
	ldr	r3, [r6, #224]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	bne	.L1039
	ldrb	r3, [r7, #3131]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1040
	ldr	r3, [r7, #3776]
	add	r3, r3, #704
	str	r3, [r6, #256]
.L1041:
	mov	r3, #1
	str	r3, [r5, #1080]
.L1165:
	ldrb	r1, [r5, #1032]	@ zero_extendqisi2
	b	.L1166
.L1184:
	ldrb	r3, [r5, #1032]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1037
.L1038:
	cmp	r0, #0
	bne	.L1037
	ldr	r1, [r5, #1084]
	cmp	r1, #0
	beq	.L1185
	ldr	r3, [r5, #1096]
	mov	r2, r0
	str	r0, [r5, #1080]
	add	r3, r3, #1
	cmp	r3, r1
	movcs	r3, r1
	str	r3, [r5, #1084]
	b	.L1097
.L1074:
	ldrb	r3, [r5, #1044]	@ zero_extendqisi2
	b	.L1096
.L1179:
	movw	ip, #42040
	ldr	r2, [r5, #2680]
	ldr	r3, [fp, #-244]
	mov	r1, r4
	movt	ip, 169
	add	ip, r6, ip
	str	ip, [sp]
	bl	MVC_GenPiclistfromFrmlist_Interview
	b	.L1083
.L1040:
	cmp	r3, #1
	ldr	r3, [r7, #3776]
	addeq	r3, r3, #740
	addne	r3, r3, #776
	str	r3, [r6, #256]
	b	.L1041
.L1075:
	ldr	lr, [r6, #388]
	b	.L1078
.L1180:
	movw	r4, #32992
	movw	r3, #43644
	movt	r4, 169
	add	r4, r6, r4
	mov	r0, r6
	movt	r3, 169
	mov	r2, r4
	add	r3, r6, r3
	bl	mvc_append_interview_list
	ldrb	r0, [r7, #3131]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L1085
	ldr	r1, [r5, #2684]
	ldr	ip, [r5, #1084]
	cmp	r1, #0
	beq	.L1086
	add	r2, ip, #96
	movw	r3, #33696
	movt	r3, 169
	add	r3, r6, r3
	add	r2, r6, r2, lsl #2
.L1087:
	add	r0, r0, #1
	str	r3, [r2, #4]!
	cmp	r0, r1
	add	r3, r3, #816
	bne	.L1087
	add	ip, ip, r0
.L1086:
	str	ip, [r5, #1084]
	ldrb	r1, [r5, #1032]	@ zero_extendqisi2
	ldr	r0, [r5, #1080]
	b	.L1080
.L1173:
	mov	r3, r4, asl #2
	mov	r1, r8
	str	r3, [fp, #-244]
	mov	r2, r3
	ldr	r3, .L1186+12
	add	r0, r10, r2
	mov	r2, #4
	bl	qsort
	subs	r9, r4, #0
	bne	.L1095
.L1168:
	sub	ip, fp, #172
	b	.L1070
.L1172:
	add	r9, r4, #64
	ldr	r3, .L1186+28
	mov	r2, #4
	mov	r1, r8
	add	r9, r6, r9, lsl #2
	mov	r0, r9
	bl	qsort
	subs	r10, r4, #0
	bne	.L1094
	b	.L1057
.L1102:
	mov	r4, ip
	b	.L1022
.L1103:
	mov	r8, r4
	b	.L1025
.L1104:
	mov	r4, r10
	b	.L1059
.L1178:
	sub	r10, fp, #236
	ldr	r3, .L1186+8
	mov	r1, ip
	mov	r2, #4
	mov	r0, r10
	str	ip, [fp, #-244]
	bl	qsort
	ldr	r3, [fp, #-240]
	ldr	ip, [fp, #-244]
	ldr	r8, [r3, #2896]
	cmp	r8, #0
	movwne	r9, #47812
	movne	r4, ip
	movtne	r9, 169
	addne	r9, r6, r9
	bne	.L1100
	ldr	r3, .L1186+12
	mov	r2, #4
	mov	r1, r8
	mov	r0, r10
	mov	r9, r8
	bl	qsort
	b	.L1168
.L1048:
	add	r3, r0, #256
	mov	r2, #4
	str	r3, [fp, #-244]
	mov	r1, r10
	mov	r0, r3
	ldr	r3, .L1186+24
	bl	qsort
	ldr	r3, [fp, #-240]
	ldr	r8, [r3, #2896]
	cmp	r8, #0
	movwne	r9, #47812
	movne	r4, r10
	movtne	r9, 169
	addne	r9, r6, r9
	bne	.L1098
	ldr	r9, [fp, #-244]
	mov	r2, #4
	ldr	r3, .L1186+28
	mov	r1, r8
	mov	r10, r8
	mov	r0, r9
	bl	qsort
	b	.L1057
.L1185:
	ldr	r1, .L1186+36
.L1167:
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r6
	bl	MVC_ClearCurrSlice
	mvn	r0, #0
	b	.L1159
.L1085:
	movw	ip, #42044
	ldr	r2, [r5, #2684]
	mov	r1, r4
	movt	ip, 169
	add	r3, r6, #388
	add	ip, r6, ip
	str	ip, [sp]
	bl	MVC_GenPiclistfromFrmlist_Interview
	b	.L1165
.L1039:
	ldr	r1, .L1186+40
	b	.L1167
.L1187:
	.align	2
.L1186:
	.word	MVC_compare_pic_by_pic_num_desc
	.word	MVC_compare_pic_by_lt_pic_num_asc
	.word	MVC_compare_fs_by_poc_desc
	.word	MVC_compare_fs_by_poc_asc
	.word	MVC_compare_fs_by_lt_pic_idx_asc
	.word	.LC27
	.word	MVC_compare_pic_by_poc_desc
	.word	MVC_compare_pic_by_poc_asc
	.word	MVC_compare_fs_by_frame_num_desc
	.word	.LC28
	.word	.LC26
	UNWIND(.fnend)
	.size	MVC_InitListX, .-MVC_InitListX
	.align	2
	.global	MVC_DumpList
	.type	MVC_DumpList, %function
MVC_DumpList:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	r3, .L1201
	ldr	r3, [r3]
	tst	r3, #8192
	beq	.L1188
	movw	r8, #42036
	add	r7, r0, #252
	movt	r8, 169
	add	r8, r0, r8
	mov	r6, #0
.L1190:
	ldr	r3, [r8, #4]!
	cmp	r3, #0
	movne	r5, r7
	movne	r4, #0
	beq	.L1192
.L1191:
	ldr	ip, [r5, #4]!
	mov	r3, r4
	mov	r2, r6
	ldr	r1, .L1201+4
	mov	r0, #13
	add	r4, r4, #1
	ldr	ip, [ip, #4]
	ldr	lr, [ip, #32]
	str	lr, [sp, #4]
	ldr	ip, [ip, #20]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r8]
	cmp	r3, r4
	bhi	.L1191
.L1192:
	add	r6, r6, #1
	add	r7, r7, #132
	cmp	r6, #2
	bne	.L1190
.L1188:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1202:
	.align	2
.L1201:
	.word	g_PrintEnable
	.word	.LC29
	UNWIND(.fnend)
	.size	MVC_DumpList, .-MVC_DumpList
	.align	2
	.global	MVC_FindNearestPOCPicId
	.type	MVC_FindNearestPOCPicId, %function
MVC_FindNearestPOCPicId:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #11075584
	add	r3, r3, #45056
	ldr	r2, [r3, #2892]
	cmp	r2, #0
	beq	.L1208
	ldr	r4, [r3, #2888]
	add	r3, r0, #11141120
	add	r3, r3, #12288
	cmp	r4, #0
	ldr	r5, [r3, #3796]
	beq	.L1209
	movw	ip, #47748
	mov	r6, #0
	movt	ip, 169
	add	ip, r0, ip
	mov	r1, r6
	mvn	lr, #-2147483648
.L1207:
	ldr	r2, [ip, #4]!
	add	r1, r1, #1
	cmp	r2, #0
	beq	.L1206
	ldr	r3, [r2, #32]
	rsb	r3, r3, r5
	cmp	r3, #0
	rsblt	r3, r3, #0
	cmp	r3, lr
	ldrlt	r6, [r2, #220]
	movlt	lr, r3
.L1206:
	cmp	r1, r4
	bne	.L1207
.L1205:
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1209:
	mov	r6, r4
	b	.L1205
.L1208:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_FindNearestPOCPicId, .-MVC_FindNearestPOCPicId
	.align	2
	.global	MVC_FindMinRefIdx
	.type	MVC_FindMinRefIdx, %function
MVC_FindMinRefIdx:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #11075584
	add	r3, r3, #40960
	ldrb	r2, [r3, #1032]	@ zero_extendqisi2
	cmp	r2, #2
	ldmeqfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	add	r2, r0, #11141120
	movw	r6, #48180
	add	r2, r2, #12288
	ldrb	lr, [r2, #3131]	@ zero_extendqisi2
	cmp	lr, #0
	bne	.L1244
	ldr	r4, [r3, #1080]
	movw	r5, #48184
	movt	r6, 169
	movt	r5, 169
	cmp	r4, #0
	add	r6, r0, r6
	add	r5, r0, r5
	mov	r7, lr
	beq	.L1222
.L1246:
	add	r2, r0, #252
	mov	ip, #32
	mov	r3, #0
	b	.L1220
.L1219:
	add	r3, r3, #1
	cmp	r3, r4
	beq	.L1245
.L1220:
	ldr	r1, [r2, #4]!
	ldr	r1, [r1, #4]
	ldr	r1, [r1, #52]
	cmp	r1, lr
	bne	.L1219
	cmp	ip, r3
	movcs	ip, r3
	add	r3, r3, #1
	cmp	r3, r4
	str	ip, [r5, #-4]
	str	ip, [r6, #4]
	bne	.L1220
.L1245:
	cmp	ip, #31
	bhi	.L1222
.L1221:
	add	lr, lr, #1
	add	r6, r6, #8
	cmp	lr, #16
	add	r5, r5, #8
	ldmeqfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	cmp	r4, #0
	bne	.L1246
.L1222:
	str	r7, [r5, #-4]
	str	r7, [r6, #4]
	b	.L1221
.L1244:
	ldr	r5, [r3, #1080]
	mov	lr, #0
	movt	r6, 169
	mov	r7, lr
	cmp	r5, #0
	add	r6, r0, r6
	beq	.L1226
.L1248:
	add	r1, r0, #252
	mov	r4, #32
	mov	r2, #0
	b	.L1224
.L1223:
	add	r2, r2, #1
	cmp	r2, r5
	beq	.L1247
.L1224:
	ldr	r3, [r1, #4]!
	ldr	r8, [r3, #4]
	ldrb	ip, [r3]	@ zero_extendqisi2
	ldr	r3, [r8, #52]
	mov	r3, r3, asl #1
	cmp	ip, #2
	orreq	r3, r3, #1
	cmp	r3, lr
	bne	.L1223
	cmp	r4, r2
	movcs	r4, r2
	add	r2, r2, #1
	cmp	r2, r5
	str	r4, [r6]
	bne	.L1224
.L1247:
	cmp	r4, #31
	bhi	.L1226
.L1225:
	add	lr, lr, #1
	add	r6, r6, #4
	cmp	lr, #32
	ldmeqfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	cmp	r5, #0
	bne	.L1248
.L1226:
	str	r7, [r6]
	b	.L1225
	UNWIND(.fnend)
	.size	MVC_FindMinRefIdx, .-MVC_FindMinRefIdx
	.align	2
	.global	MVC_DecList
	.type	MVC_DecList, %function
MVC_DecList:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	bl	MVC_FindNearestPOCPicId
	add	r5, r4, #11075584
	mvn	r6, #0
	add	r3, r5, #40960
	ldrb	r2, [r3, #1032]	@ zero_extendqisi2
	str	r6, [r3, #2664]
	cmp	r2, #2
	str	r0, [r3, #2668]
	beq	.L1256
	mov	r0, r4
	bl	MVC_InitListX
	cmp	r0, #0
	bne	.L1257
	mov	r0, r4
	bl	MVC_ReorderListX
	mov	r0, r4
	bl	MVC_RepairList
	cmp	r0, #0
	bne	.L1254
	mov	r0, r4
	add	r5, r5, #40960
	bl	MVC_FindMinRefIdx
	ldr	r3, [r4, #256]
	mov	r0, #0
	cmp	r3, #0
	ldrne	r3, [r3, #4]
	ldrne	r6, [r3, #220]
	str	r6, [r5, #2664]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1256:
	mov	r0, #0
	str	r0, [r3, #1080]
	str	r0, [r3, #1084]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1254:
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1257:
	ldr	r1, .L1258
	mov	r0, #13
	bl	dprint_vfmw
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1259:
	.align	2
.L1258:
	.word	.LC30
	UNWIND(.fnend)
	.size	MVC_DecList, .-MVC_DecList
	.align	2
	.global	MVC_NoPicOut
	.type	MVC_NoPicOut, %function
MVC_NoPicOut:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, [r0, #48]
	cmp	ip, #0
	beq	.L1267
	movw	r3, #48319
	mov	r2, #0
	movt	r3, 169
	mov	lr, r2
	add	r3, r0, r3
	b	.L1266
.L1275:
	ldrb	r1, [r3, #-2]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L1264
	cmp	r2, ip
	add	r3, r3, #816
	beq	.L1267
.L1266:
	ldrb	r1, [r3]	@ zero_extendqisi2
	add	r2, r2, #1
	cmp	r1, #1
	bne	.L1275
.L1264:
	cmp	r2, ip
	strb	lr, [r3, #-5]
	strb	lr, [r3, #-4]
	add	r3, r3, #816
	bne	.L1266
.L1267:
	ldr	r2, [r0, #52]
	cmp	r2, #0
	beq	.L1276
	mov	r3, #0
	add	r0, r0, #144
	mov	r1, r3
.L1268:
	add	r3, r3, #1
	str	r1, [r0, #4]!
	cmp	r3, r2
	bne	.L1268
	ldmfd	sp, {fp, sp, pc}
.L1276:
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_NoPicOut, .-MVC_NoPicOut
	.align	2
	.global	MVC_GetBackPicFromVOQueue
	.type	MVC_GetBackPicFromVOQueue, %function
MVC_GetBackPicFromVOQueue:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r8, r0
	ldr	r0, [r0, #120]
	bl	FSP_GetFspType
	cmp	r0, #0
	beq	.L1294
.L1278:
	ldr	r3, [r8, #48]
	cmp	r3, #0
	beq	.L1285
	movw	r5, #48952
	mov	r6, #0
	movt	r5, 169
	add	r5, r8, r5
	mov	r7, #0
	mov	r9, #0
.L1284:
	sub	r4, r5, #32
	mov	r3, #0
	strb	r3, [r5, #-638]
	strb	r3, [r5, #-637]
.L1283:
	ldrd	r2, [r4, #8]!
	orrs	r1, r2, r3
	bne	.L1295
.L1282:
	cmp	r4, r5
	bne	.L1283
	ldr	r3, [r8, #48]
	add	r9, r9, #1
	add	r5, r5, #816
	cmp	r3, r9
	bhi	.L1284
.L1285:
	ldr	r2, [r8, #52]
	cmp	r2, #0
	beq	.L1296
	mov	r3, #0
	add	r8, r8, #144
	mov	r1, r3
.L1286:
	add	r3, r3, #1
	str	r1, [r8, #4]!
	cmp	r3, r2
	bne	.L1286
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1295:
	mov	r1, r2
	ldr	r0, [r8, #120]
	bl	FreeUsdByDec
	strd	r6, [r4]
	b	.L1282
.L1294:
	add	r0, r8, #584
	bl	ResetVoQueue
	b	.L1278
.L1296:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_GetBackPicFromVOQueue, .-MVC_GetBackPicFromVOQueue
	.align	2
	.global	mvc_wait_vo
	.type	mvc_wait_vo, %function
mvc_wait_vo:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	mvc_wait_vo, .-mvc_wait_vo
	.align	2
	.global	MVC_RoundLog2
	.type	MVC_RoundLog2, %function
MVC_RoundLog2:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mul	r0, r0, r0
	mov	r3, #0
	mov	r2, #1
.L1299:
	add	r3, r3, #1
	cmp	r0, r2, asl r3
	bge	.L1299
	mov	r0, r3, asr #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_RoundLog2, .-MVC_RoundLog2
	.align	2
	.global	MVC_GetReRangeFlag
	.type	MVC_GetReRangeFlag, %function
MVC_GetReRangeFlag:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	ip, r0, #11075584
	add	r6, ip, #40960
	ldr	lr, [r0, #252]
	mov	r4, r0
	mov	r7, #2240
	ldrb	r0, [r6, #1044]	@ zero_extendqisi2
	mov	r5, r1
	ldr	r3, [r6, #1048]
	sxtb	r2, r0
	cmn	r2, #1
	mla	r3, r7, r3, lr
	beq	.L1318
	cmp	r0, #0
	bne	.L1304
	ldrb	r2, [r4, #2]	@ zero_extendqisi2
	ldr	r3, [r3, #28]
	cmp	r2, #1
	beq	.L1319
	ldr	r2, [r4, #28]
	cmp	r2, r3
	beq	.L1306
	ldr	r1, .L1321
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1304:
	ldr	r1, .L1321+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1318:
	ldr	r2, [r3, #28]
	movw	r7, #3992
	ldr	r3, [r4, #248]
	mla	r7, r7, r2, r3
.L1303:
	ldrb	r3, [r7, #20]	@ zero_extendqisi2
	ldr	r1, [r7, #3952]
	rsb	r3, r3, #2
	ldr	r2, [r7, #3948]
	ldr	lr, [r4, #12]
	mla	r3, r1, r3, r3
	ldr	r0, [r4, #16]
	add	r2, r2, #1
	cmp	r2, lr
	cmpeq	r3, r0
	movne	r8, #1
	moveq	r8, #0
	bne	.L1308
	add	r1, ip, #45056
	ldr	ip, [r7, #3972]
	ldr	r1, [r1, #2888]
	add	r1, r1, #1
	cmp	ip, r1
	movls	lr, r8
	bls	.L1309
.L1308:
	ldr	r1, .L1321+8
	ldr	ip, [r1]
	cmp	ip, #0
	moveq	lr, #1
	beq	.L1309
	mov	lr, lr, asl #4
	mov	r1, r3, asl #4
	mov	r0, r0, asl #4
	strh	lr, [fp, #-44]	@ movhi
	mov	r2, r2, asl #4
	strh	r0, [fp, #-42]	@ movhi
	strh	r2, [fp, #-40]	@ movhi
	mov	r3, #8
	strh	r1, [fp, #-38]	@ movhi
	sub	r2, fp, #44
	mov	r1, #2
	ldr	r0, [r4, #120]
	blx	ip
	mov	lr, #1
.L1309:
	ldrb	r3, [r6, #1043]	@ zero_extendqisi2
	cmp	r3, #1
	ldrne	ip, [r7, #3972]
	subne	ip, ip, #1
	beq	.L1320
.L1312:
	ldr	r3, [r4, #44]
	mov	r0, lr
	cmp	r3, ip
	orrne	lr, lr, #1
	str	lr, [r5]
	str	ip, [r4, #44]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1306:
	movw	r7, #35364
	movt	r7, 168
	add	r7, r4, r7
	b	.L1303
.L1320:
	movw	r1, #39336
	add	r3, r4, #290816
	movt	r1, 168
	add	r3, r3, #808
	add	r1, r4, r1
	mov	ip, #0
.L1311:
	ldr	r2, [r3]
	add	r3, r3, #335872
	add	r3, r3, #308
	cmp	r2, ip
	subhi	ip, r2, #1
	cmp	r3, r1
	bne	.L1311
	add	ip, ip, #1
	mov	ip, ip, asl #1
	cmp	ip, #16
	movcs	ip, #16
	b	.L1312
.L1319:
	movw	r7, #8500
	movt	r7, 5
	mla	r7, r7, r3, r4
	add	r7, r7, #286720
	add	r7, r7, #932
	b	.L1303
.L1322:
	.align	2
.L1321:
	.word	.LC31
	.word	.LC32
	.word	g_event_report
	UNWIND(.fnend)
	.size	MVC_GetReRangeFlag, .-MVC_GetReRangeFlag
	.global	__aeabi_uidiv
	.global	__aeabi_uidivmod
	.align	2
	.global	MVC_DecPOC
	.type	MVC_DecPOC, %function
MVC_DecPOC:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r6, r0, #11075584
	ldr	r5, [r0, #236]
	add	r7, r6, #40960
	mov	r2, #1
	ldrb	r1, [r7, #1035]	@ zero_extendqisi2
	ldr	ip, [r5, #2900]
	ldr	r3, [r5, #2896]
	sub	r1, r1, #5
	clz	r1, r1
	cmp	ip, r2
	add	r3, r3, #4
	ldr	lr, [r5, #2904]
	mov	r1, r1, lsr #5
	mov	r3, r2, asl r3
	beq	.L1325
	bcc	.L1326
	cmp	ip, #2
	ldmnefd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	cmp	r1, #0
	bne	.L1381
	add	r4, r6, #36864
	ldrb	r2, [r4, #3992]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1359
	ldr	r1, [r4, #4048]
	ldr	r0, [r4, #4044]
	ldr	r2, [r4, #4056]
	cmp	r1, r0
	addcc	r2, r2, r3
	strcc	r2, [r4, #4052]
	bcs	.L1361
.L1362:
	add	r3, r2, r1
	str	r3, [r4, #4040]
	ldrb	r0, [r7, #1040]	@ zero_extendqisi2
	mov	r3, r3, asl #1
	cmp	r0, #0
	subeq	r3, r3, #1
	str	r3, [r4, #4028]
	ldrb	r0, [r7, #1033]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L1365
	str	r3, [r4, #4024]
	str	r3, [r4, #4020]
	str	r3, [r4, #4016]
.L1358:
	add	r6, r6, #36864
	str	r1, [r6, #4044]
	str	r2, [r6, #4056]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1326:
	cmp	r1, #0
	add	lr, lr, #4
	mov	r2, r2, asl lr
	bne	.L1382
	add	r4, r6, #36864
	ldrb	r3, [r4, #3992]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1330
	ldr	lr, [r4, #4004]
	ldr	ip, [r4, #4008]
	mov	r1, lr
.L1331:
	ldr	r0, [r4, #3996]
	cmp	r0, ip
	bcs	.L1329
	rsb	r3, r0, ip
	cmp	r3, r2, lsr #1
	addcs	r1, r1, r2
	strcs	r1, [r4, #4012]
	bcs	.L1333
.L1329:
	cmp	r0, ip
	bls	.L1334
	rsb	r3, ip, r0
	cmp	r3, r2, lsr #1
	rsbhi	r1, r2, r1
	strhi	r1, [r4, #4012]
	bls	.L1334
.L1333:
	ldrb	r3, [r7, #1033]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1335
.L1384:
	ldr	r3, [r4, #4000]
	add	r1, r1, r0
	str	r1, [r4, #4016]
	add	r3, r1, r3
	str	r3, [r4, #4020]
	cmp	r3, r1
	movge	r3, r1
	str	r3, [r4, #4028]
.L1336:
	ldr	r2, [r4, #4048]
	str	r3, [r4, #4024]
	add	r3, r6, #40960
	ldr	r1, [r4, #4044]
	cmp	r2, r1
	strne	r2, [r4, #4044]
	ldrb	r3, [r3, #1040]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r6, r6, #36864
	ldrne	r2, [r6, #3996]
	ldrne	r3, [r6, #4012]
	strne	r2, [r6, #4008]
	strne	r3, [r6, #4004]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1325:
	cmp	r1, #0
	add	r4, r6, #36864
	movne	r3, #0
	strne	r3, [r4, #4052]
	bne	.L1340
	ldrb	r2, [r4, #3992]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1341
	mov	r3, r1
	str	r1, [r4, #4056]
	str	r1, [r4, #4044]
.L1342:
	str	r3, [r4, #4052]
.L1340:
	ldr	r3, [r5, #2916]
	cmp	r3, #0
	beq	.L1344
	ldr	r3, [r4, #4048]
	ldr	r0, [r4, #4052]
	add	r0, r3, r0
	str	r0, [r4, #4040]
	ldrb	r8, [r7, #1040]	@ zero_extendqisi2
	cmp	r8, #0
	bne	.L1346
	cmp	r0, #0
	beq	.L1347
	sub	r0, r0, #1
	str	r0, [r4, #4040]
.L1346:
	mov	r3, #0
	str	r3, [r4, #4072]
	ldr	r1, [r5, #2916]
	cmp	r1, r3
	bgt	.L1367
	cmp	r0, #0
	beq	.L1350
.L1383:
	sub	r9, r0, #1
	mov	r0, r9
	bl	__aeabi_uidiv
	mov	r10, r0
	mov	r0, r9
	str	r10, [r4, #4064]
	ldr	r1, [r5, #2916]
	bl	__aeabi_uidivmod
	ldr	r0, [r4, #4072]
	mul	r0, r0, r10
	str	r0, [r4, #4068]
	cmp	r1, #0
	str	r1, [r4, #4060]
	blt	.L1351
	add	r2, r5, #2912
	add	r1, r1, #1
	add	r2, r2, #4
	mov	r3, #0
.L1352:
	add	r3, r3, #1
	ldr	ip, [r2, #4]!
	cmp	r3, r1
	add	r0, r0, ip
	str	r0, [r4, #4068]
	bne	.L1352
.L1351:
	cmp	r8, #0
	ldreq	r3, [r5, #2908]
	addeq	r0, r0, r3
	streq	r0, [r4, #4068]
	ldrb	r3, [r7, #1033]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1354
	ldr	r2, [r4, #4032]
	ldr	r1, [r4, #4036]
	add	r2, r0, r2
	str	r2, [r4, #4016]
	ldr	r3, [r5, #2912]
	add	r3, r2, r3
	add	r0, r3, r1
	str	r0, [r4, #4020]
	cmp	r0, r2
	movge	r0, r2
	str	r0, [r4, #4028]
.L1355:
	add	r6, r6, #36864
	ldr	r2, [r6, #4048]
	ldr	r3, [r6, #4052]
	str	r0, [r6, #4024]
	str	r2, [r6, #4044]
	str	r3, [r6, #4056]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1344:
	str	r3, [r4, #4040]
	ldrb	r8, [r7, #1040]	@ zero_extendqisi2
.L1347:
	mov	r0, #0
	str	r0, [r4, #4072]
	ldr	r3, [r5, #2916]
	cmp	r3, r0
	ble	.L1350
.L1367:
	add	ip, r5, #2912
	mov	r3, #0
	add	ip, ip, #4
	mov	r2, r3
.L1349:
	ldr	r1, [ip, #4]!
	add	r2, r2, #1
	add	r3, r3, r1
	str	r3, [r4, #4072]
	ldr	r1, [r5, #2916]
	cmp	r1, r2
	bgt	.L1349
	cmp	r0, #0
	bne	.L1383
.L1350:
	mov	r0, #0
	str	r0, [r4, #4068]
	b	.L1351
.L1382:
	add	r4, r0, #11075584
	add	r4, r4, #36864
.L1332:
	mov	r3, #0
	ldr	r0, [r4, #3996]
	str	r3, [r4, #4004]
	mov	lr, r3
	str	r3, [r4, #4008]
	mov	r1, ip
	b	.L1329
.L1381:
	add	r3, r6, #36864
	mov	r1, #0
	mov	r2, r1
	str	r1, [r3, #4052]
	str	r1, [r3, #4020]
	str	r1, [r3, #4016]
	str	r1, [r3, #4024]
	str	r1, [r3, #4028]
	ldr	r1, [r3, #4048]
	b	.L1358
.L1334:
	str	lr, [r4, #4012]
	ldrb	r3, [r7, #1033]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1384
.L1335:
	ldrb	r3, [r7, #1034]	@ zero_extendqisi2
	cmp	r3, #0
	add	r3, r1, r0
	streq	r3, [r4, #4016]
	strne	r3, [r4, #4020]
	str	r3, [r4, #4028]
	b	.L1336
.L1354:
	ldrb	r3, [r7, #1034]	@ zero_extendqisi2
	cmp	r3, #0
	ldrne	r2, [r5, #2912]
	ldreq	r3, [r4, #4032]
	ldrne	r3, [r4, #4032]
	addne	r0, r0, r2
	addeq	r0, r0, r3
	streq	r0, [r4, #4016]
	addne	r0, r0, r3
	strne	r0, [r4, #4020]
	str	r0, [r4, #4028]
	b	.L1355
.L1330:
	movw	r3, #3993
	ldrsb	r3, [r4, r3]
	cmp	r3, #0
	bne	.L1332
	ldr	r0, [r4, #4016]
	mov	r1, ip
	mov	lr, r3
	str	r3, [r4, #4004]
	mov	ip, r0
	str	r0, [r4, #4008]
	b	.L1331
.L1341:
	ldr	r1, [r4, #4048]
	ldr	r2, [r4, #4044]
	cmp	r1, r2
	bcs	.L1343
	ldr	r2, [r4, #4056]
	add	r3, r3, r2
	str	r3, [r4, #4052]
	b	.L1340
.L1365:
	ldrb	r0, [r7, #1034]	@ zero_extendqisi2
	str	r3, [r4, #4024]
	cmp	r0, #0
	streq	r3, [r4, #4016]
	strne	r3, [r4, #4020]
	b	.L1358
.L1359:
	str	r1, [r4, #4044]
	mov	r2, r1
	str	r1, [r4, #4056]
	ldr	r1, [r4, #4048]
.L1361:
	str	r2, [r4, #4052]
	b	.L1362
.L1343:
	ldr	r3, [r4, #4056]
	b	.L1342
	UNWIND(.fnend)
	.size	MVC_DecPOC, .-MVC_DecPOC
	.align	2
	.global	MVC_CalcPicNum
	.type	MVC_CalcPicNum, %function
MVC_CalcPicNum:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r0, #11141120
	ldr	r3, [r0, #236]
	add	r5, r5, #12288
	mov	r6, #1
	ldrb	r2, [r5, #3131]	@ zero_extendqisi2
	ldr	r3, [r3, #2896]
	cmp	r2, #0
	add	r3, r3, #4
	mov	r6, r6, asl r3
	add	r3, r0, #11075584
	beq	.L1386
	add	r3, r3, #45056
	sub	r7, r2, #1
	sub	r2, r2, #2
	clz	r7, r7
	ldr	r1, [r3, #2896]
	clz	r2, r2
	mov	r7, r7, lsr #5
	cmp	r1, #0
	mov	r2, r2, lsr #5
	movwne	lr, #47812
	movne	r1, #0
	movtne	lr, 169
	addne	lr, r0, lr
	beq	.L1406
.L1405:
	ldr	ip, [lr, #4]!
	ldrb	r4, [ip, #3]	@ zero_extendqisi2
	cmp	r4, #0
	beq	.L1400
	ldr	r4, [ip, #20]
	ldr	r8, [r5, #3784]
	cmp	r4, r8
	rsbhi	r4, r6, r4
	str	r4, [ip, #24]
	ldr	ip, [lr]
	ldrb	r4, [ip, #3]	@ zero_extendqisi2
	tst	r4, #1
	beq	.L1403
	ldr	r8, [ip, #740]
	bic	r8, r8, #-16777216
	bic	r8, r8, #255
	cmp	r8, #65536
	ldreq	r4, [ip, #24]
	addeq	r4, r7, r4, lsl #1
	streq	r4, [ip, #752]
	ldreq	ip, [lr]
	ldreqb	r4, [ip, #3]	@ zero_extendqisi2
.L1403:
	tst	r4, #2
	beq	.L1400
	ldr	r4, [ip, #776]
	bic	r4, r4, #-16777216
	bic	r4, r4, #255
	cmp	r4, #65536
	ldreq	r4, [ip, #24]
	addeq	r4, r2, r4, lsl #1
	streq	r4, [ip, #788]
.L1400:
	ldr	ip, [r3, #2896]
	add	r1, r1, #1
	cmp	ip, r1
	bhi	.L1405
.L1406:
	ldr	r1, [r3, #2900]
	cmp	r1, #0
	beq	.L1430
	movw	r4, #47876
	mov	ip, #0
	movt	r4, 169
	add	r4, r0, r4
.L1411:
	ldr	lr, [r4, #4]!
	add	ip, ip, #1
	ldrb	r1, [lr, #3]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1408
	tst	r1, #1
	beq	.L1409
	ldr	r0, [lr, #740]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	cmp	r0, #256
	ldreq	r1, [lr, #28]
	addeq	r1, r7, r1, lsl #1
	streq	r1, [lr, #748]
	ldreq	lr, [r4]
	ldreqb	r1, [lr, #3]	@ zero_extendqisi2
.L1409:
	tst	r1, #2
	beq	.L1408
	ldr	r1, [lr, #776]
	bic	r1, r1, #-16777216
	bic	r1, r1, #255
	cmp	r1, #256
	ldreq	r1, [lr, #28]
	addeq	r1, r2, r1, lsl #1
	streq	r1, [lr, #784]
.L1408:
	ldr	r1, [r3, #2900]
	cmp	r1, ip
	bhi	.L1411
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1386:
	add	r3, r3, #45056
	ldr	r1, [r3, #2896]
	cmp	r1, #0
	movwne	lr, #47812
	movtne	lr, 169
	addne	lr, r0, lr
	bne	.L1395
.L1396:
	ldr	r2, [r3, #2900]
	cmp	r2, #0
	beq	.L1431
	movw	ip, #47876
	mov	r2, #0
	movt	ip, 169
	add	ip, r0, ip
	b	.L1398
.L1397:
	ldr	r1, [r3, #2900]
	cmp	r1, r2
	bls	.L1432
.L1398:
	ldr	r1, [ip, #4]!
	add	r2, r2, #1
	ldrb	r0, [r1, #3]	@ zero_extendqisi2
	cmp	r0, #3
	bne	.L1397
	ldr	r0, [r1, #704]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	cmp	r0, #256
	ldreq	r0, [r1, #28]
	streq	r0, [r1, #712]
	ldr	r1, [r3, #2900]
	cmp	r1, r2
	bhi	.L1398
.L1432:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1433:
	ldr	ip, [r1, #704]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #65536
	bne	.L1392
	ldr	ip, [r1, #20]
	ldr	r4, [r5, #3784]
	rsb	r7, r6, ip
	cmp	ip, r4
	strhi	r7, [r1, #24]
	strls	ip, [r1, #24]
	ldr	r1, [lr]
	ldr	ip, [r1, #24]
	str	ip, [r1, #716]
.L1392:
	ldr	r1, [r3, #2896]
	add	r2, r2, #1
	cmp	r1, r2
	bls	.L1396
.L1395:
	ldr	r1, [lr, #4]!
	ldrb	ip, [r1, #3]	@ zero_extendqisi2
	cmp	ip, #3
	bne	.L1392
	b	.L1433
.L1431:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1430:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_CalcPicNum, .-MVC_CalcPicNum
	.align	2
	.global	MVC_IsOutDPB
	.type	MVC_IsOutDPB, %function
MVC_IsOutDPB:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #0
	beq	.L1439
	add	r3, r0, #11075584
	add	r3, r3, #45056
	ldr	lr, [r3, #2888]
	cmp	lr, #0
	beq	.L1439
	ldr	r2, [r3, #2696]
	rsb	r3, r2, r1
	cmp	r2, #0
	clz	r3, r3
	mov	r3, r3, lsr #5
	moveq	r3, #0
	cmp	r3, #0
	bne	.L1441
	movw	ip, #47752
	movt	ip, 169
	add	ip, r0, ip
	b	.L1436
.L1437:
	ldr	r2, [ip, #4]!
	rsb	r0, r2, r1
	cmp	r2, #0
	clz	r0, r0
	mov	r0, r0, lsr #5
	moveq	r0, #0
	cmp	r0, #0
	bne	.L1441
.L1436:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L1437
.L1439:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1441:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_IsOutDPB, .-MVC_IsOutDPB
	.align	2
	.global	mvc_combine_scalinglist
	.type	mvc_combine_scalinglist, %function
mvc_combine_scalinglist:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r2, #0
	ldmlefd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	ldr	r6, .L1449
	mov	lr, #0
	mov	r5, #255
	sub	r7, r6, #16
.L1446:
	cmp	r2, #16
	ldreqb	ip, [lr, r7]	@ zero_extendqisi2
	ldrneb	ip, [lr, r6]	@ zero_extendqisi2
	add	lr, lr, #1
	cmp	lr, r2
	and	r3, ip, #3
	mov	r4, ip, lsr #2
	ldrb	r8, [r0, ip, asl #2]	@ zero_extendqisi2
	mov	r3, r3, asl #3
	ldr	ip, [r1, r4, asl #2]
	bic	ip, ip, r5, asl r3
	orr	r3, ip, r8, asl r3
	str	r3, [r1, r4, asl #2]
	bne	.L1446
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1450:
	.align	2
.L1449:
	.word	.LANCHOR0+16
	UNWIND(.fnend)
	.size	mvc_combine_scalinglist, .-mvc_combine_scalinglist
	.align	2
	.global	mvc_assign_quant_params
	.type	mvc_assign_quant_params, %function
mvc_assign_quant_params:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	subs	r3, r0, #0
	str	r1, [fp, #-48]
	str	r3, [fp, #-52]
	beq	.L1482
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	beq	.L1483
	ldr	r3, [fp, #-48]
	ldrb	r3, [r3, #18]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1471
	ldr	r3, [fp, #-48]
	mov	r4, #0
	ldr	r1, [fp, #-52]
	add	r2, r3, #2016
	add	r8, r3, #1728
	str	r2, [fp, #-56]
	add	r9, r1, #2384
	mov	r6, r2
	add	r7, r3, #1984
	add	r5, r3, #5
	ldr	r10, .L1488
	b	.L1456
.L1486:
	cmp	r4, #0
	beq	.L1484
	cmp	r4, #3
	beq	.L1485
	ldr	r3, [r10, #52]
	mov	r2, #16
	sub	r1, r6, #16
	mov	r0, r6
	blx	r3
.L1464:
	add	r4, r4, #1
	cmp	r4, #7
	bhi	.L1471
.L1470:
	add	r8, r8, #64
	add	r9, r9, #64
	add	r6, r6, #16
	add	r7, r7, #4
	add	r5, r5, #1
.L1456:
	cmp	r4, #5
	ldrsb	r3, [r5]
	bhi	.L1457
	cmp	r3, #0
	beq	.L1486
	ldr	r3, [r7]
	cmp	r3, #0
	beq	.L1464
	ldr	r1, .L1488+4
	cmp	r4, #2
	mov	r2, #16
	ldr	r3, [r10, #52]
	add	r0, r1, r2
	add	r4, r4, #1
	movhi	r1, r0
	mov	r0, r6
	blx	r3
	cmp	r4, #7
	bls	.L1470
.L1471:
	mov	r0, #0
.L1453:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1457:
	cmp	r3, #0
	bne	.L1466
	ldr	r3, [fp, #-52]
	mov	r2, #64
	ldrb	r3, [r3, #27]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r10, #52]
	bne	.L1487
.L1481:
	ldr	r1, .L1488+8
	cmp	r4, #6
	add	r0, r1, r2
	movne	r1, r0
	mov	r0, r8
	blx	r3
	b	.L1464
.L1466:
	ldr	r3, [r7]
	cmp	r3, #0
	beq	.L1464
	ldr	r3, [r10, #52]
	mov	r2, #64
	b	.L1481
.L1487:
	mov	r1, r9
	mov	r0, r8
	blx	r3
	b	.L1464
.L1482:
	movw	r3, #6887
	ldr	r2, .L1488+12
	ldr	r1, .L1488+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1453
.L1483:
	mov	r0, r3
	ldr	r2, .L1488+12
	movw	r3, #6888
	ldr	r1, .L1488+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1453
.L1485:
	ldr	r3, [fp, #-52]
	mov	r2, #16
	ldr	r0, [fp, #-48]
	mov	r4, #4
	ldrb	r3, [r3, #27]	@ zero_extendqisi2
	add	r0, r0, #2064
	cmp	r3, #0
	ldr	r3, [r10, #52]
	ldrne	r1, [fp, #-52]
	ldreq	r1, .L1488+20
	addne	r1, r1, #2720
	blx	r3
	b	.L1470
.L1484:
	ldr	r3, [fp, #-52]
	mov	r2, #16
	ldr	r0, [fp, #-56]
	mov	r4, #1
	ldrb	r3, [r3, #27]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r10, #52]
	ldrne	r1, [fp, #-52]
	ldreq	r1, .L1488+4
	addne	r1, r1, #2672
	blx	r3
	b	.L1470
.L1489:
	.align	2
.L1488:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1
	.word	.LANCHOR1+32
	.word	.LC13
	.word	.LC14
	.word	.LANCHOR1+16
	UNWIND(.fnend)
	.size	mvc_assign_quant_params, .-mvc_assign_quant_params
	.align	2
	.global	MVC_WriteCurrPicYUV
	.type	MVC_WriteCurrPicYUV, %function
MVC_WriteCurrPicYUV:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	add	r5, r0, #11141120
	add	r3, r5, #12288
	add	r5, r5, #12288
	ldr	r1, .L1493
	mov	r0, #2
	ldrb	r4, [r3, #3131]	@ zero_extendqisi2
	ldr	r3, [r3, #3776]
	mov	r2, r4
	ldr	r3, [r3, #220]
	bl	dprint_vfmw
	ldr	ip, [r5, #3836]
	cmp	r4, #3
	cmpne	r4, #0
	ldr	r3, [r5, #3832]
	addne	r2, r4, #1
	ldr	r1, .L1493+4
	moveq	r2, #1
	str	ip, [sp]
	mov	r0, #22
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1494:
	.align	2
.L1493:
	.word	.LC33
	.word	.LC34
	UNWIND(.fnend)
	.size	MVC_WriteCurrPicYUV, .-MVC_WriteCurrPicYUV
	.align	2
	.global	MVC_WritePicMsg
	.type	MVC_WritePicMsg, %function
MVC_WritePicMsg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	add	r9, r0, #11141120
	add	r5, r9, #12288
	mov	r6, r0
	ldr	r1, .L1531
	add	r7, r6, #11075584
	ldr	r10, [r5, #3852]
	mov	r0, #2
	ldr	lr, [r5, #3292]
	add	ip, r7, #32768
	ldrb	r3, [r5, #3131]	@ zero_extendqisi2
	add	r4, r9, #16384
	ldr	r2, [r5, #3792]
	add	r8, r7, #36864
	str	r10, [sp, #4]
	str	lr, [sp]
	str	ip, [fp, #-48]
	bl	dprint_vfmw
	movw	r3, #16016
	mov	r2, #0
	movt	r3, 170
	str	r2, [r6, #64]
	ldrd	r0, [r6, r3]
	movw	r3, #17488
	movt	r3, 170
	ldr	ip, [fp, #-48]
	strd	r0, [r6, r3]
	ldr	r3, [r6, #544]
	str	r3, [r4, #2024]
	ldr	r3, [r5, #3256]
	str	r3, [r4, #1800]
	ldr	r3, [r5, #3260]
	str	r3, [r4, #1804]
	ldr	r3, [r5, #3280]
	str	r3, [r4, #1808]
	ldr	r3, [r5, #3284]
	str	r3, [r4, #1812]
	ldr	r3, [r5, #3792]
	str	r3, [r4, #1112]
	ldrb	r3, [r5, #3131]	@ zero_extendqisi2
	strb	r3, [r4, #1080]
	ldr	r3, [r6, #236]
	ldrb	r2, [r3, #21]	@ zero_extendqisi2
	str	r2, [r4, #1128]
	ldr	r2, [r5, #3836]
	str	r2, [r4, #1116]
	ldr	r2, [r5, #3840]
	str	r2, [r4, #1120]
	ldr	r2, [r3, #3948]
	add	r2, r2, #1
	str	r2, [r4, #1124]
	ldrb	r2, [ip, #1876]	@ zero_extendqisi2
	strb	r2, [r4, #1083]
	ldr	r2, [r8, #1812]
	str	r2, [r4, #1132]
	ldrb	r2, [r8, #1752]	@ zero_extendqisi2
	str	r2, [r4, #1136]
	ldr	r3, [r3, #748]
	strb	r3, [r4, #1081]
	ldrb	r3, [r8, #1756]	@ zero_extendqisi2
	str	r3, [r4, #1140]
	ldr	r3, [r8, #4028]
	str	r3, [r4, #1144]
	ldr	r3, [r8, #4016]
	str	r3, [r4, #1148]
	ldr	r3, [r8, #4020]
	str	r3, [r4, #1152]
	ldr	r3, [r5, #3776]
	ldr	r0, [r6, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_GetLogicFs
	subs	r10, r0, #0
	beq	.L1529
	ldr	r2, [r10, #28]
	ldr	r3, [r10, #32]
	cmp	r2, #0
	beq	.L1499
	cmp	r3, #0
	beq	.L1499
	movw	r3, #17916
	movw	r2, #17788
	movw	r1, #18044
	ldr	r0, [r6, #120]
	movt	r3, 170
	movt	r2, 170
	add	r3, r6, r3
	add	r2, r6, r2
	movt	r1, 170
	add	r1, r6, r1
	bl	FSP_GetDecFsAddrTab
	ldr	r3, [r10, #28]
	movw	r2, #18048
	add	r1, r9, #18176
	movt	r2, 170
	add	r2, r6, r2
	ldr	r3, [r3, #4]
	add	r7, r7, #45056
	str	r3, [r4, #1388]
	ldr	r0, [r6, #120]
	bl	FSP_GetPmvAddrTab
	ldr	r3, [r5, #3852]
	str	r3, [r4, #1396]
	ldr	r3, [r10, #12]
	str	r3, [r4, #1796]
	ldr	r3, [r10, #32]
	ldr	r3, [r3, #8]
	str	r3, [r4, #1392]
	ldr	r3, [r10, #32]
	ldr	r3, [r3, #60]
	str	r3, [r4, #1400]
	ldr	r3, [r7, #3116]
	cmp	r3, #0
	str	r3, [fp, #-52]
	str	r3, [r4, #2016]
	beq	.L1505
	movw	r4, #47976
	movw	lr, #18204
	movw	ip, #48040
	movw	r0, #18268
	movw	r1, #48104
	movw	r2, #18332
	ldr	r9, [fp, #-52]
	movt	r4, 169
	movt	lr, 170
	movt	ip, 169
	movt	r0, 170
	movt	r1, 169
	movt	r2, 170
	add	r4, r6, r4
	add	lr, r6, lr
	add	ip, r6, ip
	add	r0, r6, r0
	add	r1, r6, r1
	add	r2, r6, r2
	mov	r3, #0
.L1504:
	ldr	r5, [r4, #4]!
	add	r3, r3, #1
	cmp	r3, r9
	str	r5, [lr, #4]!
	ldr	r5, [ip, #4]!
	str	r5, [r0, #4]!
	ldr	r5, [r1, #4]!
	str	r5, [r2, #4]!
	bne	.L1504
.L1505:
	ldr	r3, [fp, #-48]
	ldrb	r3, [r3, #1883]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1530
	ldrb	ip, [r8, #1770]	@ zero_extendqisi2
	cmp	ip, #0
	bne	.L1506
	movw	lr, #17536
	ldr	r0, .L1531+4
	movt	lr, 170
	add	lr, r6, lr
.L1507:
	and	r3, ip, #3
	add	ip, ip, #1
	cmp	ip, #24
	add	r3, r0, r3, lsl #2
	ldr	r3, [r3, #352]
	bic	r2, r3, #16711680
	ubfx	r1, r3, #8, #8
	bic	r2, r2, #65280
	mov	r3, r3, lsr #8
	orr	r2, r2, r1, asl #16
	and	r3, r3, #65280
	orr	r3, r2, r3
	str	r3, [lr, #4]!
	bne	.L1507
	movw	r8, #17636
	mov	r5, #0
	movt	r8, 170
	add	r8, r6, r8
.L1508:
	add	r3, r5, #1
	and	r2, r5, #14
	and	r3, r3, #15
	add	r5, r5, #2
	add	r2, r0, r2, lsl #2
	cmp	r5, #32
	add	r3, r0, r3, lsl #2
	ldr	r1, [r2, #368]
	ldr	ip, [r3, #368]
	ubfx	r3, r1, #8, #8
	mov	r2, r1, lsr #24
	uxtb	r9, r1
	uxtb	r4, ip
	mov	lr, ip, lsr #16
	orr	r3, r3, r2, asl #8
	mov	r1, r1, lsr #8
	mov	r4, r4, asl #16
	and	r2, ip, #-16777216
	orr	lr, r4, lr, asl #24
	ubfx	ip, ip, #8, #8
	orr	r3, r3, r2
	orr	lr, lr, r9
	and	r1, r1, #65280
	orr	r3, r3, ip, asl #16
	orr	r2, lr, r1
	stmia	r8, {r2, r3}
	add	r8, r8, #8
	bne	.L1508
.L1513:
	ldr	r3, [fp, #-52]
	cmp	r3, #0
	beq	.L1510
	movw	r4, #47980
	movw	r9, #18512
	movw	r8, #18576
	movt	r4, 169
	movt	r9, 170
	movt	r8, 170
	add	r4, r6, r4
	add	r9, r6, r9
	add	r8, r6, r8
	mov	r5, #0
.L1516:
	ldr	r2, [r4]
	mov	r1, #0
	ldr	r0, [r6, #120]
	add	r5, r5, #1
	bl	FSP_GetStoreType
	adds	r0, r0, #0
	movne	r0, #1
	str	r0, [r9, #4]!
	ldr	r3, [r4], #4
	str	r3, [r8, #4]!
	ldr	r3, [r7, #3116]
	cmp	r3, r5
	bhi	.L1516
.L1510:
	mov	r0, #0
.L1526:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1530:
	ldrb	ip, [r8, #1770]	@ zero_extendqisi2
.L1506:
	cmp	ip, #1
	movw	ip, #17536
	movt	ip, 170
	mov	r0, #0
	add	ip, r6, ip
	beq	.L1511
.L1514:
	movw	r3, #25708
	movt	r3, 42
	add	r3, r0, r3
	add	r0, r0, #1
	ldr	r3, [r6, r3, asl #2]
	cmp	r0, #24
	bic	r2, r3, #16711680
	ubfx	r1, r3, #8, #8
	bic	r2, r2, #65280
	mov	r3, r3, lsr #8
	orr	r2, r2, r1, asl #16
	and	r3, r3, #65280
	orr	r3, r2, r3
	str	r3, [ip, #4]!
	bne	.L1514
	movw	r9, #17636
	mov	r10, #1
	movt	r9, 170
	add	r9, r6, r9
	mov	r8, #0
.L1515:
	mov	r2, r8, lsr #3
	mov	r3, r8, asl #1
	and	r1, r3, #14
	and	r0, r10, #15
	mov	r3, r2, asl #4
	movw	r2, #25732
	add	r0, r3, r0
	add	r3, r3, r1
	mov	r1, r2
	movt	r2, 42
	movt	r1, 42
	add	r2, r0, r2
	add	r1, r3, r1
	add	r8, r8, #1
	ldr	r2, [r6, r2, asl #2]
	cmp	r8, #16
	ldr	r3, [r6, r1, asl #2]
	add	r10, r10, #2
	ubfx	r5, r2, #8, #8
	and	lr, r2, #-16777216
	mov	r0, r2, lsr #16
	uxtb	r1, r2
	mov	ip, r3, lsr #24
	uxtb	r4, r3
	mov	r2, r0, asl #24
	mov	r0, r3, lsr #8
	mov	ip, ip, asl #8
	orr	r2, r2, r1, asl #16
	orr	ip, ip, r5, asl #16
	orr	r1, r2, r4
	ubfx	r3, r3, #8, #8
	and	r2, r0, #65280
	orr	ip, ip, lr
	orr	r2, r1, r2
	orr	r3, ip, r3
	stmia	r9, {r2, r3}
	add	r9, r9, #8
	bne	.L1515
	b	.L1513
.L1511:
	movw	r3, #26542
	movt	r3, 42
	add	r3, r0, r3
	add	r0, r0, #1
	ldr	r3, [r6, r3, asl #2]
	cmp	r0, #24
	bic	r2, r3, #16711680
	ubfx	r1, r3, #8, #8
	bic	r2, r2, #65280
	mov	r3, r3, lsr #8
	orr	r2, r2, r1, asl #16
	and	r3, r3, #65280
	orr	r3, r2, r3
	str	r3, [ip, #4]!
	bne	.L1511
	movw	r9, #17636
	mov	r10, #1
	movt	r9, 170
	add	r9, r6, r9
	mov	r8, #0
.L1512:
	mov	r2, r8, lsr #3
	mov	r3, r8, asl #1
	and	r1, r3, #14
	and	r0, r10, #15
	mov	r3, r2, asl #4
	movw	r2, #26566
	add	r0, r3, r0
	add	r3, r3, r1
	mov	r1, r2
	movt	r2, 42
	movt	r1, 42
	add	r2, r0, r2
	add	r1, r3, r1
	add	r8, r8, #1
	ldr	r2, [r6, r2, asl #2]
	cmp	r8, #16
	ldr	r3, [r6, r1, asl #2]
	add	r10, r10, #2
	ubfx	r5, r2, #8, #8
	and	lr, r2, #-16777216
	mov	r0, r2, lsr #16
	uxtb	r1, r2
	mov	ip, r3, lsr #24
	uxtb	r4, r3
	mov	r2, r0, asl #24
	mov	r0, r3, lsr #8
	mov	ip, ip, asl #8
	orr	r2, r2, r1, asl #16
	orr	ip, ip, r5, asl #16
	orr	r1, r2, r4
	ubfx	r3, r3, #8, #8
	and	r2, r0, #65280
	orr	ip, ip, lr
	orr	r2, r1, r2
	orr	r3, ip, r3
	stmia	r9, {r2, r3}
	add	r9, r9, #8
	bne	.L1512
	b	.L1513
.L1499:
	ldr	r1, .L1531+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1526
.L1529:
	ldr	r3, [r5, #3776]
	ldr	r1, .L1531+12
	ldrsb	r2, [r3, #6]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1526
.L1532:
	.align	2
.L1531:
	.word	.LC35
	.word	.LANCHOR1
	.word	.LC37
	.word	.LC36
	UNWIND(.fnend)
	.size	MVC_WritePicMsg, .-MVC_WritePicMsg
	.align	2
	.global	MVC_UpdatePicQpInf
	.type	MVC_UpdatePicQpInf, %function
MVC_UpdatePicQpInf:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r1, #28]
	ldr	r3, [r1, #32]
	cmp	r2, r0
	movlt	r2, r0
	cmp	r3, r0
	str	r2, [r1, #28]
	movge	r3, r0
	str	r3, [r1, #32]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_UpdatePicQpInf, .-MVC_UpdatePicQpInf
	.align	2
	.global	MVC_WriteSliceMsg
	.type	MVC_WriteSliceMsg, %function
MVC_WriteSliceMsg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	ldr	r3, [r0, #64]
	movw	r1, #4060
	mov	r4, r0
	mov	ip, r3
	str	r3, [fp, #-48]
	mul	r1, r1, ip
	ldr	r3, [r0, #32]
	ldr	r0, [r0, #544]
	add	r2, ip, #1
	sub	r3, r3, #1
	str	r2, [r4, #64]
	cmp	ip, r3
	add	r6, r0, r1
	addcc	r3, r1, #4048
	addcc	r3, r3, #12
	movcs	r3, #0
	addcc	r3, r0, r3
	str	r3, [r6, #4056]
	ldr	r2, [r4, #232]
	ldrb	ip, [r2]	@ zero_extendqisi2
	ldr	r3, [r2, #68]
	cmp	ip, #1
	cmpls	ip, r3
	bcs	.L1537
	add	lr, ip, #3
	add	lr, r6, lr, lsl #2
.L1538:
	mov	r3, ip, asl #5
	sub	r3, r3, ip, asl #2
	add	ip, ip, #1
	add	r2, r2, r3
	ldr	r2, [r2, #24]
	str	r2, [lr, #4]!
	ldr	r2, [r4, #232]
	add	r2, r2, r3
	ldr	r2, [r2, #20]
	str	r2, [lr, #-8]
	ldr	r2, [r4, #232]
	add	r3, r2, r3
	ldr	r3, [r3, #28]
	str	r3, [lr, #8]
	ldr	r2, [r4, #232]
	ldr	r3, [r2, #68]
	cmp	r3, ip
	movhi	r5, #1
	movls	r5, #0
	cmp	ip, #1
	movhi	r5, #0
	cmp	r5, #0
	bne	.L1538
.L1537:
	cmp	r3, #1
	bhi	.L1543
	add	r3, r3, #3
	add	ip, r6, #20
	mov	r2, #0
	add	r3, r6, r3, lsl #2
.L1542:
	str	r2, [r3, #4]!
	cmp	r3, ip
	str	r2, [r3, #-8]
	str	r2, [r3, #8]
	bne	.L1542
.L1543:
	add	r3, r4, #11141120
	str	r3, [fp, #-52]
	add	r10, r3, #12288
	ldr	r3, [fp, #-48]
	add	r5, r4, #11075584
	cmp	r3, #0
	ldrb	r3, [r10, #3137]	@ zero_extendqisi2
	add	r8, r5, #36864
	add	r5, r5, #40960
	strb	r3, [r6, #1]
	ldr	r3, [r8, #1800]
	ldr	r2, [r5, #2648]
	add	r3, r3, #26
	add	r3, r3, r2
	str	r3, [r6, #32]
	bne	.L1639
	ldr	r2, [r10, #3776]
	str	r3, [r2, #732]
	ldr	r3, [r10, #3776]
	ldr	r2, [r6, #32]
	str	r2, [r3, #736]
.L1544:
	ldr	r3, [r5, #2644]
	str	r3, [r6, #36]
	ldr	r3, [r5, #1096]
	str	r3, [r6, #40]
	ldr	r3, [r5, #1092]
	str	r3, [r6, #44]
	ldrb	r3, [r5, #1032]	@ zero_extendqisi2
	strb	r3, [r0, r1]
	ldr	r3, [r5, #1088]
	str	r3, [r6, #48]
	ldrb	r3, [r5, #1038]	@ zero_extendqisi2
	strb	r3, [r6, #2]
	ldr	r3, [r4, #236]
	ldrb	r3, [r3, #22]	@ zero_extendqisi2
	strb	r3, [r6, #3]
	ldr	r3, [r5, #1080]
	str	r3, [r6, #52]
	ldr	r3, [r5, #1084]
	str	r3, [r6, #56]
	ldrb	r3, [r5, #1032]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r3, [r8, #1796]
	streqb	r3, [r6, #4]
	beq	.L1546
	cmp	r3, #0
	ldreqb	r3, [r8, #1754]	@ zero_extendqisi2
	movne	r3, #0
	strb	r3, [r6, #4]
.L1546:
	ldr	r3, [r8, #1804]
	str	r3, [r6, #60]
	ldr	r3, [r8, #1808]
	str	r3, [r6, #64]
	ldr	r3, [r5, #2656]
	str	r3, [r6, #68]
	ldr	r3, [r5, #2660]
	str	r3, [r6, #72]
	ldr	r3, [r5, #2652]
	str	r3, [r6, #76]
	ldrb	r3, [r5, #1032]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L1585
	ldr	r7, [r5, #1080]
	cmp	r7, #0
	beq	.L1588
	ldr	r3, [r4, #256]
	ldr	r2, [r3, #4]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r1, r4, #256
	movne	r3, #0
	bne	.L1553
	b	.L1551
.L1555:
	ldr	r2, [r1, #4]!
	ldr	r2, [r2, #4]
	ldrb	r0, [r2, #1]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1551
.L1553:
	add	r3, r3, #1
	cmp	r3, r7
	bne	.L1555
	mov	r3, #0
	str	r3, [fp, #-56]
.L1550:
	ldr	ip, [r5, #1084]
	cmp	ip, #0
	beq	.L1589
	ldr	r3, [r4, #388]
	ldr	r2, [r3, #4]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r1, r4, #388
	movne	r3, #0
	bne	.L1559
	b	.L1557
.L1561:
	ldr	r2, [r1, #4]!
	ldr	r2, [r2, #4]
	ldrb	r0, [r2, #1]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1557
.L1559:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L1561
	mov	r3, #0
	str	r3, [fp, #-60]
.L1556:
	ldrb	ip, [r10, #3131]	@ zero_extendqisi2
	ldr	r3, [r5, #1080]
	cmp	ip, #0
	beq	.L1562
	cmp	r3, #0
	beq	.L1577
	mov	r7, #0
	mov	r9, r6
	str	r6, [fp, #-64]
	add	r10, r4, #256
	mov	r6, r5
	mov	r5, r7
	ldr	r7, [fp, #-56]
	b	.L1576
.L1574:
	strb	r2, [r9, #1630]
	ldr	r2, [r10]
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	strb	r2, [r9, #1631]
	ldr	r2, [r10]
	ldr	r2, [r2, #16]
	str	r2, [r9, #1656]
.L1575:
	ldr	r2, [r6, #1080]
	add	r5, r5, #1
	add	r10, r10, #4
	add	r9, r9, #36
	cmp	r2, r5
	bls	.L1640
.L1576:
	ldr	r2, [r10]
	ldr	r0, [r4, #120]
	ldr	r2, [r2, #4]
	ldrsb	r1, [r2, #6]
	bl	FSP_GetLogicFs
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #48]
	str	r2, [r9, #1636]
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	strb	r2, [r9, #1625]
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r0, r7
	beq	.L1573
	cmp	r0, #0
	ldrne	r2, [r0, #28]
	ldrne	r0, [r2, #4]
.L1573:
	str	r0, [r9, #1640]
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #52]
	str	r2, [r9, #1644]
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #32]
	str	r2, [r9, #1632]
	ldr	r2, [r10]
	ldrb	r2, [r2]	@ zero_extendqisi2
	strb	r2, [r9, #1624]
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldrb	r2, [r2, #704]	@ zero_extendqisi2
	strb	r2, [r9, #1626]
	ldr	r2, [r10]
	ldrb	r2, [r2]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1574
	strb	r2, [r9, #1628]
	ldr	r2, [r10]
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	strb	r2, [r9, #1629]
	ldr	r2, [r10]
	ldr	r2, [r2, #16]
	str	r2, [r9, #1652]
	b	.L1575
.L1640:
	mov	r5, r6
	ldr	r6, [fp, #-64]
.L1577:
	ldrb	r3, [r5, #1032]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1641
.L1565:
	movw	r2, #48176
	add	r3, r6, #3920
	add	r0, r6, #4048
	movt	r2, 169
	add	r3, r3, #4
	add	r2, r4, r2
	add	r0, r0, #4
.L1582:
	ldr	r1, [r2, #4]!
	str	r1, [r3, #4]!
	cmp	r3, r0
	bne	.L1582
	ldr	r2, [fp, #-52]
	ldrb	r3, [r8, #1754]	@ zero_extendqisi2
	add	r9, r2, #16384
	cmp	r3, #0
	str	r3, [r9, #1380]
	ldr	r3, [r8, #1796]
	str	r3, [r9, #1384]
	beq	.L1583
	ldrb	r2, [r5, #1032]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1584
.L1583:
	cmp	r3, #1
	beq	.L1642
.L1585:
	ldr	r2, [fp, #-48]
	movw	r3, #36996
	movt	r3, 42
	ldr	r1, [r4, #232]
	add	r3, r2, r3
	mov	r2, #0
	add	r3, r4, r3, lsl #2
	str	r1, [r3, #4]
	str	r2, [r4, #232]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1639:
	ldr	r2, [r10, #3776]
	ldr	lr, [r2, #732]
	ldr	ip, [r2, #736]
	cmp	lr, r3
	movlt	lr, r3
	cmp	ip, r3
	str	lr, [r2, #732]
	movge	ip, r3
	str	ip, [r2, #736]
	b	.L1544
.L1551:
	ldrsb	r1, [r2, #6]
	ldr	r0, [r4, #120]
	bl	FSP_GetLogicFs
	subs	r3, r0, #0
	movweq	r3, #7939
	beq	.L1635
	ldr	r3, [r3, #28]
	ldr	r3, [r3, #4]
	str	r3, [fp, #-56]
	b	.L1550
.L1642:
	ldrb	r3, [r5, #1032]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1585
.L1584:
	ldr	r3, [r5, #1100]
	movw	r8, #42064
	movw	r7, #42192
	movw	lr, #42320
	movw	ip, #42832
	movw	r0, #42960
	str	r3, [r6, #80]
	movw	r1, #43088
	ldr	r10, [r5, #1104]
	movt	r8, 169
	movt	r7, 169
	movt	lr, 169
	movt	ip, 169
	movt	r0, 169
	movt	r1, 169
	add	r8, r4, r8
	add	r7, r4, r7
	add	lr, r4, lr
	add	ip, r4, ip
	add	r0, r4, r0
	add	r1, r4, r1
	mov	r9, r6
	mov	r3, r6
	mov	r2, #0
	str	r6, [fp, #-52]
	str	r10, [r9, #84]!
.L1586:
	ldr	r10, [r8, #4]!
	add	r2, r2, #1
	add	r3, r3, #4
	str	r10, [r9, #4]!
	ldr	r10, [r7, #4]!
	str	r10, [r3, #212]
	ldr	r10, [lr, #4]!
	str	r10, [r3, #340]
	ldr	r10, [ip, #4]!
	str	r10, [r3, #852]
	ldr	r10, [r0, #4]!
	str	r10, [r3, #980]
	ldr	r10, [r1, #4]!
	str	r10, [r3, #1108]
	ldr	r10, [r5, #1092]
	cmp	r10, r2
	bcs	.L1586
	ldrb	r3, [r5, #1032]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1585
	movw	r7, #42448
	movw	lr, #42576
	movw	ip, #42704
	movw	r0, #43216
	movw	r1, #43344
	movw	r2, #43472
	ldr	r8, [fp, #-52]
	movt	r7, 169
	movt	lr, 169
	movt	ip, 169
	movt	r0, 169
	movt	r1, 169
	movt	r2, 169
	add	r6, r6, #468
	add	r7, r4, r7
	add	lr, r4, lr
	add	ip, r4, ip
	add	r0, r4, r0
	add	r1, r4, r1
	add	r2, r4, r2
	mov	r3, #0
.L1587:
	ldr	r9, [r7, #4]!
	add	r3, r3, #1
	add	r8, r8, #4
	str	r9, [r6, #4]!
	ldr	r9, [lr, #4]!
	str	r9, [r8, #596]
	ldr	r9, [ip, #4]!
	str	r9, [r8, #724]
	ldr	r9, [r0, #4]!
	str	r9, [r8, #1236]
	ldr	r9, [r1, #4]!
	str	r9, [r8, #1364]
	ldr	r9, [r2, #4]!
	str	r9, [r8, #1492]
	ldr	r9, [r5, #1096]
	cmp	r9, r3
	bcs	.L1587
	b	.L1585
.L1562:
	cmp	r3, #0
	beq	.L1570
	ldr	r9, [fp, #-56]
	add	r10, r4, #256
	mov	r7, r6
	str	r6, [fp, #-64]
	mov	r6, r5
	mov	r5, ip
.L1569:
	ldr	r2, [r10]
	ldr	r0, [r4, #120]
	ldr	r2, [r2, #4]
	ldrsb	r1, [r2, #6]
	bl	FSP_GetLogicFs
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #48]
	str	r2, [r7, #1636]
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	strb	r2, [r7, #1625]
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r0, r9
	beq	.L1568
	cmp	r0, #0
	ldrne	r2, [r0, #28]
	ldrne	r0, [r2, #4]
.L1568:
	str	r0, [r7, #1640]
	mov	r3, #0
	ldr	r2, [r10]
	add	r5, r5, #1
	add	r7, r7, #36
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #52]
	str	r2, [r7, #1608]
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #32]
	str	r2, [r7, #1596]
	ldr	r2, [r10]
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	strb	r2, [r7, #1591]
	ldr	r2, [r10]
	ldrb	r2, [r2]	@ zero_extendqisi2
	strb	r2, [r7, #1590]
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #720]
	str	r2, [r7, #1612]
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #756]
	str	r2, [r7, #1616]
	ldr	r2, [r10], #4
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #792]
	strb	r3, [r7, #1588]
	str	r2, [r7, #1620]
	ldr	r2, [r6, #1080]
	cmp	r2, r5
	bhi	.L1569
	mov	r5, r6
	ldr	r6, [fp, #-64]
.L1570:
	ldrb	r3, [r5, #1032]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1565
	ldr	r3, [r5, #1084]
	cmp	r3, #0
	beq	.L1565
	mov	r9, #0
	mov	r10, r6
	str	r6, [fp, #-56]
	mov	r6, r5
	mov	r5, r9
	ldr	r9, [fp, #-60]
	add	r7, r4, #388
.L1572:
	ldr	r2, [r7]
	ldr	r0, [r4, #120]
	ldr	r2, [r2, #4]
	ldrsb	r1, [r2, #6]
	bl	FSP_GetLogicFs
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #48]
	str	r2, [r10, #2788]
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	strb	r2, [r10, #2777]
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r0, r9
	beq	.L1571
	cmp	r0, #0
	ldrne	r2, [r0, #28]
	ldrne	r0, [r2, #4]
.L1571:
	str	r0, [r10, #1640]
	mov	r3, #0
	ldr	r2, [r7]
	add	r5, r5, #1
	add	r10, r10, #36
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #52]
	str	r2, [r10, #2760]
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #32]
	str	r2, [r10, #2748]
	ldr	r2, [r7]
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	strb	r2, [r10, #2743]
	ldr	r2, [r7]
	ldrb	r2, [r2]	@ zero_extendqisi2
	strb	r2, [r10, #2742]
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #720]
	str	r2, [r10, #2764]
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #756]
	str	r2, [r10, #2768]
	ldr	r2, [r7], #4
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #792]
	strb	r3, [r10, #2740]
	str	r2, [r10, #2772]
	ldr	r2, [r6, #1084]
	cmp	r2, r5
	bhi	.L1572
.L1634:
	mov	r5, r6
	ldr	r6, [fp, #-56]
	b	.L1565
.L1557:
	ldrsb	r1, [r2, #6]
	ldr	r0, [r4, #120]
	bl	FSP_GetLogicFs
	subs	r3, r0, #0
	beq	.L1643
	ldr	r3, [r3, #28]
	ldr	r3, [r3, #4]
	str	r3, [fp, #-60]
	b	.L1556
.L1641:
	ldr	r3, [r5, #1084]
	cmp	r3, #0
	beq	.L1565
	mov	r3, #0
	mov	r10, r6
	str	r6, [fp, #-56]
	add	r7, r4, #388
	mov	r6, r5
	ldr	r9, [fp, #-60]
	mov	r5, r3
	b	.L1581
.L1579:
	strb	r2, [r10, #2782]
	ldr	r2, [r7]
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	strb	r2, [r10, #2783]
	ldr	r2, [r7]
	ldr	r2, [r2, #16]
	str	r2, [r10, #2808]
.L1580:
	ldr	r2, [r6, #1084]
	add	r5, r5, #1
	add	r7, r7, #4
	add	r10, r10, #36
	cmp	r2, r5
	bls	.L1634
.L1581:
	ldr	r2, [r7]
	ldr	r0, [r4, #120]
	ldr	r2, [r2, #4]
	ldrsb	r1, [r2, #6]
	bl	FSP_GetLogicFs
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #48]
	str	r2, [r10, #2788]
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	strb	r2, [r10, #2777]
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r0, r9
	beq	.L1578
	cmp	r0, #0
	ldrne	r2, [r0, #28]
	ldrne	r0, [r2, #4]
.L1578:
	str	r0, [r10, #2792]
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #52]
	str	r2, [r10, #2796]
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #32]
	str	r2, [r10, #2784]
	ldr	r2, [r7]
	ldrb	r2, [r2]	@ zero_extendqisi2
	strb	r2, [r10, #2776]
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldrb	r2, [r2, #704]	@ zero_extendqisi2
	strb	r2, [r10, #2778]
	ldr	r2, [r7]
	ldrb	r2, [r2]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1579
	strb	r2, [r10, #2780]
	ldr	r2, [r7]
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	strb	r2, [r10, #2781]
	ldr	r2, [r7]
	ldr	r2, [r2, #16]
	str	r2, [r10, #2804]
	b	.L1580
.L1643:
	movw	r3, #7960
.L1635:
	ldr	r2, .L1644
	ldr	r1, .L1644+4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L1588:
	str	r7, [fp, #-56]
	b	.L1550
.L1589:
	str	ip, [fp, #-60]
	b	.L1556
.L1645:
	.align	2
.L1644:
	.word	.LANCHOR0+80
	.word	.LC38
	UNWIND(.fnend)
	.size	MVC_WriteSliceMsg, .-MVC_WriteSliceMsg
	.align	2
	.global	MVC_StopPicNum
	.type	MVC_StopPicNum, %function
MVC_StopPicNum:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_StopPicNum, .-MVC_StopPicNum
	.align	2
	.global	MVC_GetPicStreamSize
	.type	MVC_GetPicStreamSize, %function
MVC_GetPicStreamSize:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r0, r0, #11141120
	add	r0, r0, #16384
	ldr	r2, [r0, #2024]
	cmp	r2, #0
	beq	.L1650
	mov	r0, #0
.L1649:
	ldr	r3, [r2, #8]
	ldr	r1, [r2, #12]
	ldr	r2, [r2, #4056]
	add	r3, r3, r1
	add	r3, r3, #7
	cmp	r2, #0
	add	r0, r0, r3, lsr #3
	bne	.L1649
	ldmfd	sp, {fp, sp, pc}
.L1650:
	mov	r0, r2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_GetPicStreamSize, .-MVC_GetPicStreamSize
	.align	2
	.global	MVC_SliceCheck
	.type	MVC_SliceCheck, %function
MVC_SliceCheck:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r1, .L1663
	mov	r4, r0
	add	r5, r0, #11075584
	bl	mvc_ue_v
	add	r5, r5, #40960
	str	r0, [r5, #1088]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1661
	cmp	r0, #262144
	bcs	.L1662
	ldr	r2, [r4, #12]
	ldr	r3, [r4, #16]
	mul	r3, r3, r2
	sub	r3, r3, #1
	cmp	r0, r3
	bhi	.L1661
	ldr	r1, .L1663+4
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L1663+8
	mov	r2, r0
	mov	r6, r0
	mov	r0, #19
	bl	dprint_vfmw
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1661
	cmp	r6, #9
	bhi	.L1657
	mov	r1, #1
	movw	r0, #297
	mov	r2, r1, asl r6
	and	r0, r0, r2
	cmp	r0, #0
	bne	.L1658
	ands	r3, r2, #660
	bne	.L1659
	tst	r2, #66
	beq	.L1657
	strb	r1, [r5, #1032]
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1658:
	strb	r3, [r5, #1032]
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1657:
	mov	r2, r6
	ldr	r1, .L1663+12
	mov	r0, #1
	bl	dprint_vfmw
.L1661:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1659:
	mov	r3, #2
	strb	r3, [r5, #1032]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1662:
	ldr	r1, .L1663+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1664:
	.align	2
.L1663:
	.word	.LC39
	.word	.LC41
	.word	.LC42
	.word	.LC43
	.word	.LC40
	UNWIND(.fnend)
	.size	MVC_SliceCheck, .-MVC_SliceCheck
	.align	2
	.global	MVC_PPSSPSCheck
	.type	MVC_PPSSPSCheck, %function
MVC_PPSSPSCheck:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r0, #11075584
	mov	r4, r0
	add	r5, r5, #40960
	ldr	r1, .L1677
	mov	r0, #19
	ldr	r2, [r5, #1048]
	bl	dprint_vfmw
	ldr	r3, [r4, #252]
	ldr	r2, [r5, #1048]
	mov	r1, #2240
	mla	r1, r1, r2, r3
	ldrb	r3, [r1, #19]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1675
	ldrb	r3, [r5, #1044]	@ zero_extendqisi2
	sxtb	r5, r3
	cmn	r5, #1
	beq	.L1676
	cmp	r3, #0
	bne	.L1670
	ldr	r2, [r1, #28]
	movw	r3, #8500
	movt	r3, 5
	mul	r3, r3, r2
	add	r0, r4, r3
	add	ip, r0, #12992
	add	r3, r0, #286720
	add	ip, ip, #8
	add	r3, r3, #932
	ldrb	ip, [ip, #4]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L1671
	add	r0, r0, #286720
	ldrb	r0, [r0, #957]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1671
.L1669:
	mov	r0, #0
	str	r1, [r4, #244]
	str	r3, [r4, #240]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1676:
	ldr	r0, [r4, #248]
	movw	r3, #3992
	ldr	r2, [r1, #28]
	mla	r3, r3, r2, r0
	ldrb	r0, [r3, #25]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L1669
	ldr	r1, .L1677+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1671:
	ldr	r1, .L1677+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1675:
	ldr	r1, .L1677+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1670:
	mov	r2, r5
	ldr	r1, .L1677+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1678:
	.align	2
.L1677:
	.word	.LC44
	.word	.LC46
	.word	.LC47
	.word	.LC45
	.word	.LC32
	UNWIND(.fnend)
	.size	MVC_PPSSPSCheck, .-MVC_PPSSPSCheck
	.align	2
	.global	MVC_PPSSPSCheckTmpId
	.type	MVC_PPSSPSCheckTmpId, %function
MVC_PPSSPSCheckTmpId:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r2, r1
	mov	r5, r1
	mov	r4, r0
	ldr	r1, .L1688
	mov	r0, #19
	bl	dprint_vfmw
	ldr	r2, [r4, #252]
	mov	r3, #2240
	mla	r3, r3, r5, r2
	ldrb	r2, [r3, #19]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1685
	ldr	r1, [r4, #36]
	ldr	r2, [r3, #28]
	sub	r3, r1, #1
	cmp	r2, r3
	bhi	.L1686
	add	r3, r4, #11075584
	movw	r1, #1044
	add	r3, r3, #40960
	ldrsb	r5, [r3, r1]
	cmn	r5, #1
	beq	.L1687
.L1684:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1687:
	ldr	r1, [r4, #248]
	movw	r3, #3992
	mla	r3, r3, r2, r1
	ldrb	r3, [r3, #25]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1684
	ldr	r1, .L1688+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1685:
	mov	r2, r5
	ldr	r1, .L1688+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1686:
	ldr	r1, .L1688+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1689:
	.align	2
.L1688:
	.word	.LC48
	.word	.LC51
	.word	.LC49
	.word	.LC50
	UNWIND(.fnend)
	.size	MVC_PPSSPSCheckTmpId, .-MVC_PPSSPSCheckTmpId
	.align	2
	.global	MVC_IsNewPic
	.type	MVC_IsNewPic, %function
MVC_IsNewPic:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	ip, r0, #11075584
	ldr	lr, [r0, #236]
	add	r3, ip, #40960
	ldr	r1, [lr, #744]
	ldr	r0, [r3, #2696]
	ldr	r2, [r3, #2700]
	ldr	r4, [r3, #1048]
	ldr	r6, [r3, #2704]
	cmp	r2, r4
	cmpeq	r0, r1
	ldr	r5, [r3, #1060]
	ldrb	r4, [r3, #2688]	@ zero_extendqisi2
	ldrb	r0, [r3, #1033]	@ zero_extendqisi2
	movne	r1, #1
	moveq	r1, #0
	cmp	r6, r5
	moveq	r2, r1
	orrne	r2, r1, #1
	cmp	r4, r0
	orrne	r2, r2, #1
	cmp	r4, #0
	cmpne	r0, #0
	beq	.L1692
	ldrb	r0, [r3, #2689]	@ zero_extendqisi2
	ldrb	r1, [r3, #1034]	@ zero_extendqisi2
	cmp	r0, r1
	orrne	r2, r2, #1
.L1692:
	ldrb	r1, [r3, #2691]	@ zero_extendqisi2
	ldrb	r0, [r3, #1040]	@ zero_extendqisi2
	cmp	r1, r0
	moveq	r1, #0
	beq	.L1693
	cmp	r0, #0
	cmpne	r1, #0
	moveq	r1, #1
	movne	r1, #0
.L1693:
	ldrb	r0, [r3, #2690]	@ zero_extendqisi2
	ldrb	r4, [r3, #1035]	@ zero_extendqisi2
	cmp	r0, r4
	orrne	r2, r2, #1
	cmp	r4, #5
	cmpeq	r0, #5
	orr	r2, r2, r1
	beq	.L1705
.L1694:
	ldr	r1, [lr, #2900]
	cmp	r1, #0
	bne	.L1695
	add	r1, ip, #36864
	ldr	r0, [r3, #2716]
	ldr	r4, [r3, #2712]
	ldr	r5, [r1, #4000]
	ldr	lr, [r1, #3996]
	cmp	r4, lr
	cmpeq	r0, r5
	movne	r1, #1
	moveq	r1, #0
	orr	r2, r2, r1
.L1696:
	ldrb	r1, [r3, #1043]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1697
	ldr	r1, [r3, #2732]
	ldrb	r0, [r3, #2692]	@ zero_extendqisi2
	ldrb	r6, [r3, #1041]	@ zero_extendqisi2
	ldr	r5, [r3, #2672]
	ldrb	r4, [r3, #2693]	@ zero_extendqisi2
	cmp	r1, r5
	cmpeq	r0, r6
	ldrb	lr, [r3, #1042]	@ zero_extendqisi2
	movne	r1, #1
	moveq	r1, #0
	cmp	r4, lr
	moveq	r3, r1
	orrne	r3, r1, #1
	orr	r2, r2, r3
.L1697:
	add	r3, ip, #40960
	ldr	r1, .L1706
	mov	r0, #19
	ldr	r4, [r3, #1088]
	cmp	r4, #0
	movne	r4, r2
	orreq	r4, r2, #1
	mov	r2, r4
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1695:
	cmp	r1, #1
	bne	.L1696
	add	r1, ip, #36864
	ldr	r0, [r3, #2724]
	ldr	r4, [r3, #2720]
	ldr	r5, [r1, #4036]
	ldr	lr, [r1, #4032]
	cmp	r4, lr
	cmpeq	r0, r5
	movne	r1, #1
	moveq	r1, #0
	orr	r2, r2, r1
	b	.L1696
.L1705:
	ldr	r0, [r3, #2708]
	ldr	r1, [r3, #1076]
	cmp	r0, r1
	orrne	r2, r2, #1
	b	.L1694
.L1707:
	.align	2
.L1706:
	.word	.LC52
	UNWIND(.fnend)
	.size	MVC_IsNewPic, .-MVC_IsNewPic
	.align	2
	.global	mvc_ref_pic_list_reordering
	.type	mvc_ref_pic_list_reordering, %function
mvc_ref_pic_list_reordering:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r0, #11075584
	ldr	r2, [r0, #240]
	add	r8, r5, #40960
	add	r5, r5, #36864
	mov	r3, #0
	mov	r6, #1
	ldrb	r1, [r8, #1043]	@ zero_extendqisi2
	mov	r4, r0
	strb	r3, [r5, #4076]
	cmp	r1, r3
	strb	r3, [r5, #4077]
	ldrb	r3, [r8, #1033]	@ zero_extendqisi2
	movne	r7, #5
	moveq	r7, #3
	cmp	r3, #0
	ldr	r3, [r2, #2896]
	addne	r3, r3, #5
	addeq	r3, r3, #4
	mov	r6, r6, asl r3
	ldrb	r3, [r8, #1032]	@ zero_extendqisi2
	cmp	r3, #1
	bls	.L1763
.L1762:
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
.L1729:
	adds	r3, r3, #0
	movne	r3, #1
	rsb	r0, r3, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1763:
	ldr	r1, .L1770
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #4076]
	cmp	r0, #0
	beq	.L1719
	ldr	r3, [r8, #1092]
	cmn	r3, #2
	beq	.L1745
	movw	r10, #40940
	mov	r9, #0
	movt	r10, 169
	add	r10, r4, r10
	b	.L1726
.L1720:
	cmp	r0, #2
	beq	.L1764
	sub	r0, r0, #4
	cmp	r0, #1
	bls	.L1765
.L1723:
	ldr	r3, [r8, #1092]
	add	r9, r9, #1
	add	r3, r3, #2
	cmp	r3, r9
	bls	.L1766
.L1726:
	ldr	r1, .L1770+4
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r7, r0
	str	r0, [r10, #4]!
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	bcc	.L1716
	cmp	r3, #0
	bne	.L1716
	cmp	r0, #3
	beq	.L1719
	cmp	r0, #1
	bhi	.L1720
	ldr	r1, .L1770+8
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r6, r0
	str	r0, [r10, #264]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	bls	.L1722
	cmp	r3, #0
	beq	.L1723
.L1722:
	mov	r2, r0
	ldr	r1, .L1770+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1719:
	ldrb	r3, [r8, #1032]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1762
	ldr	r1, .L1770+16
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #4077]
	cmp	r0, #0
	beq	.L1762
	ldr	r3, [r8, #1096]
	cmn	r3, #2
	beq	.L1762
	movw	r9, #41072
	mov	r5, #0
	movt	r9, 169
	add	r9, r4, r9
	b	.L1742
.L1741:
	add	r5, r5, #1
	cmp	r5, r3
	bcs	.L1762
.L1742:
	ldr	r1, .L1770+20
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r7, r0
	str	r0, [r9, #4]!
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	bcc	.L1733
	cmp	r3, #0
	bne	.L1733
	cmp	r0, #3
	beq	.L1729
	cmp	r0, #1
	bls	.L1767
	cmp	r0, #2
	beq	.L1768
	sub	r0, r0, #4
	cmp	r0, #1
	bls	.L1769
	ldr	r3, [r8, #1096]
	add	r3, r3, #2
	cmp	r3, r5
	bne	.L1741
.L1743:
	ldr	r1, .L1770+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1767:
	ldr	r1, .L1770+28
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r6, r0
	str	r0, [r9, #264]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	bls	.L1737
	cmp	r3, #0
	bne	.L1737
.L1738:
	ldr	r2, [r8, #1096]
	add	r3, r2, #2
	cmp	r3, r5
	bne	.L1741
	movw	r1, #26654
	movt	r1, 42
	add	r1, r2, r1
	add	r1, r4, r1, lsl #2
	ldr	r2, [r1, #4]
	cmp	r2, #3
	beq	.L1741
	b	.L1743
.L1764:
	ldr	r1, .L1770+32
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r10, #528]
	b	.L1723
.L1768:
	ldr	r1, .L1770+36
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r9, #524]
	b	.L1738
.L1765:
	ldr	r1, .L1770+40
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r10, #784]
	b	.L1723
.L1769:
	ldr	r1, .L1770+44
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r9, #784]
	b	.L1738
.L1716:
	mov	r2, r0
	ldr	r1, .L1770+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1733:
	mov	r2, r0
	ldr	r1, .L1770+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1766:
	cmp	r9, r3
	bne	.L1719
.L1714:
	movw	r2, #26618
	movt	r2, 42
	add	r2, r3, r2
	add	r2, r4, r2, lsl #2
	ldr	r3, [r2, #8]
	cmp	r3, #3
	beq	.L1719
	ldr	r1, .L1770+56
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1737:
	mov	r2, r0
	ldr	r1, .L1770+60
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1745:
	mov	r3, #0
	b	.L1714
.L1771:
	.align	2
.L1770:
	.word	.LC53
	.word	.LC54
	.word	.LC56
	.word	.LC57
	.word	.LC61
	.word	.LC62
	.word	.LC68
	.word	.LC64
	.word	.LC58
	.word	.LC66
	.word	.LC59
	.word	.LC67
	.word	.LC55
	.word	.LC63
	.word	.LC60
	.word	.LC65
	UNWIND(.fnend)
	.size	mvc_ref_pic_list_reordering, .-mvc_ref_pic_list_reordering
	.align	2
	.global	mvc_pred_weight_table
	.type	mvc_pred_weight_table, %function
mvc_pred_weight_table:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	r3, [r0, #244]
	ldr	r1, .L1802
	add	r6, r0, #11075584
	ldr	r7, [r0, #240]
	mov	r5, r0
	str	r3, [fp, #-48]
	bl	mvc_ue_v
	add	r6, r6, #40960
	mov	r4, #1
	str	r0, [r6, #1100]
	mov	r8, r4, asl r0
	ldr	r9, [r7, #748]
	cmp	r9, #0
	bne	.L1796
.L1773:
	cmp	r0, #7
	bhi	.L1776
	ldr	r3, [r6, #1104]
	cmp	r3, #7
	bhi	.L1776
	ldrb	r2, [r5, #10]	@ zero_extendqisi2
	cmp	r2, #0
	movweq	r10, #42196
	moveq	r4, r2
	movteq	r10, 169
	addeq	r10, r5, r10
	beq	.L1784
	b	.L1775
.L1780:
	ldr	r2, [r7, #748]
	cmp	r2, #0
	bne	.L1797
.L1781:
	str	r2, [r10]
	str	r2, [r10, #768]
	str	r2, [r10, #128]
	str	r2, [r10, #896]
.L1783:
	ldr	r2, [r6, #1092]
	add	r4, r4, #1
	add	r10, r10, #4
	cmp	r2, r4
	bcc	.L1798
.L1784:
	ldr	r1, .L1802+4
	mov	r0, r5
	bl	mvc_u_1
	cmp	r0, #0
	streq	r8, [r10, #-128]
	streq	r0, [r10, #640]
	beq	.L1780
	ldr	r1, .L1802+8
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1802+12
	str	r0, [r10, #-128]
	mov	r0, r5
	bl	mvc_se_v
	str	r0, [r10, #640]
	ldr	r2, [r7, #748]
	cmp	r2, #0
	beq	.L1781
.L1797:
	ldr	r1, .L1802+16
	mov	r0, r5
	bl	mvc_u_1
	cmp	r0, #0
	bne	.L1799
	str	r9, [r10]
	str	r0, [r10, #768]
	str	r9, [r10, #128]
	str	r0, [r10, #896]
	b	.L1783
.L1798:
	ldr	r3, [fp, #-48]
	ldr	r3, [r3, #44]
	cmp	r3, #1
	beq	.L1785
.L1786:
	ldrb	r0, [r5, #10]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
.L1778:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1799:
	ldr	r1, .L1802+20
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1802+24
	str	r0, [r10]
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1802+20
	str	r0, [r10, #768]
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1802+24
	str	r0, [r10, #128]
	mov	r0, r5
	bl	mvc_se_v
	str	r0, [r10, #896]
	b	.L1783
.L1796:
	ldr	r1, .L1802+28
	mov	r0, r5
	bl	mvc_ue_v
	mov	r3, r0
	ldr	r0, [r6, #1100]
	mov	r9, r4, asl r3
	str	r3, [r6, #1104]
	b	.L1773
.L1785:
	ldrb	r3, [r6, #1032]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1786
	movw	r4, #42580
	mov	r10, #0
	movt	r4, 169
	add	r4, r5, r4
	b	.L1792
.L1788:
	ldr	r3, [r7, #748]
	cmp	r3, #0
	bne	.L1800
.L1789:
	str	r3, [r4]
	str	r3, [r4, #768]
	str	r3, [r4, #128]
	str	r3, [r4, #896]
.L1791:
	ldr	r3, [r6, #1096]
	add	r10, r10, #1
	add	r4, r4, #4
	cmp	r3, r10
	bcc	.L1786
.L1792:
	ldr	r1, .L1802+32
	mov	r0, r5
	bl	mvc_u_1
	cmp	r0, #0
	streq	r8, [r4, #-128]
	streq	r0, [r4, #640]
	beq	.L1788
	ldr	r1, .L1802+36
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1802+40
	str	r0, [r4, #-128]
	mov	r0, r5
	bl	mvc_se_v
	str	r0, [r4, #640]
	ldr	r3, [r7, #748]
	cmp	r3, #0
	beq	.L1789
.L1800:
	ldr	r1, .L1802+44
	mov	r0, r5
	bl	mvc_u_1
	cmp	r0, #0
	bne	.L1801
	str	r9, [r4]
	str	r0, [r4, #768]
	str	r9, [r4, #128]
	str	r0, [r4, #896]
	b	.L1791
.L1776:
	ldrb	r2, [r5, #10]	@ zero_extendqisi2
.L1775:
	ldr	r1, .L1802+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1778
.L1801:
	ldr	r1, .L1802+52
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1802+56
	str	r0, [r4]
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1802+52
	str	r0, [r4, #768]
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1802+56
	str	r0, [r4, #128]
	mov	r0, r5
	bl	mvc_se_v
	str	r0, [r4, #896]
	b	.L1791
.L1803:
	.align	2
.L1802:
	.word	.LC69
	.word	.LC72
	.word	.LC73
	.word	.LC74
	.word	.LC75
	.word	.LC76
	.word	.LC77
	.word	.LC70
	.word	.LC78
	.word	.LC79
	.word	.LC80
	.word	.LC81
	.word	.LC71
	.word	.LC82
	.word	.LC83
	UNWIND(.fnend)
	.size	mvc_pred_weight_table, .-mvc_pred_weight_table
	.align	2
	.global	MVC_DecMMCO
	.type	MVC_DecMMCO, %function
MVC_DecMMCO:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #0
	mov	r4, r0
	moveq	r7, #100
	beq	.L1816
	mov	r9, #0
	b	.L1807
.L1838:
	ldr	r1, .L1844
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r5, #2
	beq	.L1836
.L1818:
	cmp	r5, #6
	orreq	r6, r6, #1
	cmp	r6, #0
	bne	.L1821
	cmp	r5, #4
	beq	.L1837
.L1822:
	cmp	r5, #6
	bhi	.L1814
.L1819:
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1814
	cmp	r5, #0
	beq	.L1824
.L1823:
	subs	r7, r7, #1
	beq	.L1825
.L1816:
	ldr	r1, .L1844+4
	mov	r0, r4
	bl	mvc_ue_v
	bic	r3, r0, #2
	sub	r6, r0, #3
	clz	r6, r6
	cmp	r3, #1
	mov	r5, r0
	mov	r6, r6, lsr #5
	beq	.L1838
	cmp	r5, #2
	bne	.L1818
.L1836:
	ldr	r1, .L1844+8
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r6, #0
	beq	.L1819
.L1821:
	ldr	r1, .L1844+12
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r5, #4
	bne	.L1822
.L1837:
	ldr	r1, .L1844+16
	mov	r0, r4
	bl	mvc_ue_v
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1823
.L1814:
	ldr	r1, .L1844+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1843:
	ldr	r1, .L1844
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r3, [r8, #4]
	cmp	r3, #2
	str	r0, [r8, #8]
	beq	.L1839
.L1810:
	cmp	r3, #3
	cmpne	r3, #6
	beq	.L1840
.L1811:
	cmp	r3, #4
	beq	.L1841
.L1812:
	cmp	r3, #6
	bhi	.L1814
	ldrb	r2, [r4, #10]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1814
	cmp	r3, #0
	add	r9, r9, #1
	beq	.L1824
	cmp	r9, #100
	beq	.L1842
.L1807:
	ldr	r1, .L1844+4
	mov	r0, r4
	ldrb	r5, [r4, #3]	@ zero_extendqisi2
	bl	mvc_ue_v
	mov	r6, r9, asl #2
	mov	r7, r9, asl #4
	add	r1, r6, r7
	movw	r2, #2004
	movw	r8, #43696
	mla	r2, r2, r5, r1
	movt	r8, 169
	add	r2, r4, r2
	add	r8, r2, r8
	mov	r3, r0
	bic	r0, r0, #2
	cmp	r0, #1
	str	r3, [r8, #4]
	beq	.L1843
	cmp	r3, #2
	bne	.L1810
.L1839:
	ldr	r1, .L1844+8
	mov	r0, r4
	bl	mvc_ue_v
	add	r3, r6, r7
	movw	r2, #2004
	movw	r1, #43704
	mla	r3, r2, r5, r3
	movw	r2, #43696
	movt	r1, 169
	movt	r2, 169
	add	r3, r4, r3
	add	r1, r3, r1
	add	r2, r3, r2
	str	r0, [r1, #4]
	ldr	r3, [r2, #4]
	cmp	r3, #3
	cmpne	r3, #6
	bne	.L1811
.L1840:
	ldr	r1, .L1844+12
	mov	r0, r4
	bl	mvc_ue_v
	add	r3, r6, r7
	movw	r2, #2004
	movw	r1, #43704
	mla	r3, r2, r5, r3
	movw	r2, #43696
	movt	r1, 169
	movt	r2, 169
	add	r3, r4, r3
	add	r1, r3, r1
	add	r2, r3, r2
	str	r0, [r1, #8]
	ldr	r3, [r2, #4]
	cmp	r3, #4
	bne	.L1812
.L1841:
	ldr	r1, .L1844+16
	mov	r0, r4
	bl	mvc_ue_v
	add	r6, r6, r7
	movw	r7, #2004
	movw	r2, #43712
	mla	r5, r7, r5, r6
	movw	r3, #43696
	movt	r2, 169
	movt	r3, 169
	add	r5, r4, r5
	add	r2, r5, r2
	add	r3, r5, r3
	str	r0, [r2, #4]
	ldr	r3, [r3, #4]
	b	.L1812
.L1824:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1842:
	ldr	r1, .L1844+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1825:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1845:
	.align	2
.L1844:
	.word	.LC86
	.word	.LC85
	.word	.LC87
	.word	.LC88
	.word	.LC89
	.word	.LC90
	.word	.LC84
	UNWIND(.fnend)
	.size	MVC_DecMMCO, .-MVC_DecMMCO
	.align	2
	.global	mvc_dec_ref_pic_marking
	.type	mvc_dec_ref_pic_marking, %function
mvc_dec_ref_pic_marking:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r3, r0, #11075584
	add	r3, r3, #40960
	mov	r4, r0
	ldrb	r7, [r0, #3]	@ zero_extendqisi2
	ldrb	r8, [r3, #1037]	@ zero_extendqisi2
	cmp	r8, #0
	beq	.L1847
	clz	r2, r7
	mov	r2, r2, lsr #5
	strb	r2, [r0, #3]
	mov	r6, r2
.L1856:
	ldrb	r3, [r3, #1035]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L1867
	ldr	r1, .L1871
	mov	r0, r4
	bl	mvc_u_1
	movw	r2, #2004
	mla	r6, r2, r6, r4
	movw	r5, #43696
	movt	r5, 169
	ldr	r1, .L1871+4
	add	r5, r6, r5
	mov	r3, r0
	uxtb	r2, r0
	strb	r3, [r5, #3]
	mov	r0, #16
	bl	dprint_vfmw
	ldrb	r3, [r5, #3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1850
.L1854:
	mov	r8, #0
.L1864:
	mov	r0, r8
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1847:
	movw	r2, #2004
	movw	r1, #43696
	mla	r2, r2, r7, r0
	movt	r1, 169
	movw	r5, #43696
	mov	r6, r7
	movt	r5, 169
	add	r5, r2, r5
	ldrb	r2, [r2, r1]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1856
	ldrb	r3, [r3, #1035]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L1868
	ldr	r1, .L1871
	ldrb	r6, [r5, #3]	@ zero_extendqisi2
	bl	mvc_u_1
	cmp	r6, r0
	bne	.L1869
	ldrb	r3, [r5, #3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1854
	mov	r1, r8
	mov	r0, r4
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	MVC_DecMMCO
.L1850:
	mov	r1, #1
	mov	r0, r4
	bl	MVC_DecMMCO
	cmn	r0, #1
	mov	r8, r0
	movne	r3, #1
	movne	r8, #0
	strneb	r3, [r5]
	bne	.L1864
	mov	r3, #0
	ldr	r1, .L1871+8
	strb	r3, [r5]
	mov	r0, #1
	strb	r7, [r4, #3]
	bl	dprint_vfmw
	b	.L1864
.L1868:
	ldr	r1, .L1871+12
	ldrb	r6, [r5, #1]	@ zero_extendqisi2
	bl	mvc_u_1
	cmp	r6, r0
	bne	.L1870
	mov	r0, r4
	ldr	r1, .L1871+16
	ldrb	r4, [r5, #2]	@ zero_extendqisi2
	bl	mvc_u_1
	cmp	r4, r0
	beq	.L1854
	ldr	r1, .L1871+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1864
.L1867:
	ldr	r1, .L1871+12
	mov	r0, r4
	bl	mvc_u_1
	movw	r2, #2004
	mla	r2, r2, r6, r4
	movw	r5, #43696
	movt	r5, 169
	ldr	r1, .L1871+16
	mov	r8, #0
	add	r5, r2, r5
	strb	r0, [r5, #1]
	mov	r0, r4
	bl	mvc_u_1
	ldrb	r2, [r5, #1]	@ zero_extendqisi2
	ldr	r1, .L1871+24
	strb	r0, [r5, #2]
	mov	r0, #16
	bl	dprint_vfmw
	mov	r0, r8
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1869:
	ldr	r1, .L1871+28
	mov	r0, #1
	bl	dprint_vfmw
	ldr	ip, [r4, #68]
	ldr	r3, [r4, #100]
	mov	r0, #1
	ldr	r2, [r4, #88]
	mvn	r8, #0
	ldr	r1, .L1871+32
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1864
.L1870:
	ldr	r1, .L1871+36
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1864
.L1872:
	.align	2
.L1871:
	.word	.LC94
	.word	.LC95
	.word	.LC96
	.word	.LC91
	.word	.LC92
	.word	.LC98
	.word	.LC93
	.word	.LC99
	.word	.LC100
	.word	.LC97
	UNWIND(.fnend)
	.size	mvc_dec_ref_pic_marking, .-mvc_dec_ref_pic_marking
	.align	2
	.global	MVC_ProcessSliceHeaderFirstPart
	.type	MVC_ProcessSliceHeaderFirstPart, %function
MVC_ProcessSliceHeaderFirstPart:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r1, .L1938
	mov	r4, r0
	bl	mvc_ue_v
	ldr	r3, [r4, #40]
	sub	r3, r3, #1
	cmp	r0, r3
	mov	r6, r0
	bhi	.L1874
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1874
	mov	r1, r0
	mov	r0, r4
	bl	MVC_PPSSPSCheckTmpId
	cmp	r0, #0
	bne	.L1929
	add	r7, r4, #11075584
	mov	r0, r4
	add	r5, r7, #40960
	str	r6, [r5, #1048]
	bl	MVC_PPSSPSCheck
	subs	r8, r0, #0
	bne	.L1930
	ldr	r6, [r4, #240]
	mov	r0, r4
	ldr	r2, .L1938+4
	ldr	r9, [r4, #244]
	ldr	r1, [r6, #2896]
	add	r1, r1, #4
	bl	mvc_u_v
	str	r0, [r5, #1060]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1927
	adds	r0, r0, #0
	ldrb	r3, [r5, #1035]	@ zero_extendqisi2
	movne	r0, #1
	cmp	r3, #5
	movne	r0, #0
	cmp	r0, #0
	bne	.L1931
.L1880:
	mov	r3, #0
	strb	r3, [r5, #1033]
	strb	r3, [r5, #1034]
	ldrb	r3, [r6, #20]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1932
	ldr	r2, [r6, #3948]
	ldr	r1, [r6, #3952]
	add	r3, r2, #1
	mla	r3, r1, r3, r3
.L1903:
	ldrb	r2, [r6, #21]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1886
	strb	r2, [r5, #1036]
.L1888:
	ldr	r2, [r5, #1088]
	cmp	r2, r3
	bcs	.L1933
.L1889:
	ldrb	r3, [r5, #1035]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L1934
.L1891:
	add	r10, r7, #36864
	mov	r3, #0
	str	r3, [r10, #3996]
	str	r3, [r10, #4000]
	ldr	r3, [r6, #2900]
	cmp	r3, #0
	beq	.L1935
.L1895:
	mov	r3, #0
	str	r3, [r10, #4032]
	str	r3, [r10, #4036]
	ldr	r3, [r6, #2900]
	cmp	r3, #1
	beq	.L1936
.L1898:
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1927
	ldrb	r3, [r9, #17]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1901
	ldr	r1, .L1938+8
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #0
	bne	.L1902
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1901
.L1902:
	ldr	r1, .L1938+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L1938+16
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L1927
	mov	r3, #0
	ldr	r0, [r4, #120]
	mov	r2, r3
	mov	r1, #102
	blx	ip
.L1927:
	mvn	r8, #0
.L1913:
	mov	r0, r8
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1932:
	ldr	r1, .L1938+20
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #1033]
	cmp	r0, #0
	bne	.L1937
	ldr	r2, [r6, #3948]
	ldrb	ip, [r6, #20]	@ zero_extendqisi2
	ldr	r1, [r6, #3952]
	add	r3, r2, #1
	cmp	ip, #0
	mla	r3, r1, r3, r3
	bne	.L1905
	mov	r3, r3, asl #1
	b	.L1903
.L1886:
	mov	r2, #1
	strb	r2, [r5, #1036]
.L1906:
	ldr	r2, [r5, #1088]
	cmp	r2, r3, lsr #1
	bcc	.L1889
	ldr	r1, .L1938+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1913
.L1937:
	ldr	r1, .L1938+28
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #1034]
	ldr	r2, [r6, #3948]
	ldrb	r0, [r6, #20]	@ zero_extendqisi2
	ldr	r1, [r6, #3952]
	add	r3, r2, #1
	cmp	r0, #0
	ldrb	r0, [r5, #1033]	@ zero_extendqisi2
	mla	r3, r1, r3, r3
	moveq	r2, #2
	beq	.L1884
.L1905:
	mov	r2, #1
.L1884:
	cmp	r0, #0
	mul	r3, r2, r3
	beq	.L1903
	cmp	r0, #1
	mov	r2, #0
	strb	r2, [r5, #1036]
	bne	.L1888
	b	.L1906
.L1901:
	mov	r0, r4
	add	r7, r7, #40960
	bl	MVC_IsNewPic
	uxtb	r0, r0
	strb	r0, [r7, #1037]
	cmp	r0, #0
	bne	.L1913
	ldr	r2, [r7, #1088]
	ldr	r3, [r7, #2728]
	cmp	r2, r3
	bhi	.L1913
	ldr	r1, .L1938+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1913
.L1935:
	ldr	r1, [r6, #2904]
	mov	r0, r4
	ldr	r2, .L1938+36
	add	r1, r1, #4
	bl	mvc_u_v
	str	r0, [r10, #3996]
	ldrb	r3, [r9, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1895
	ldrb	r3, [r5, #1033]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1895
	ldr	r1, .L1938+40
	mov	r0, r4
	bl	mvc_se_v
	str	r0, [r10, #4000]
	b	.L1895
.L1936:
	ldrb	r3, [r6, #18]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1898
	ldr	r1, .L1938+44
	mov	r0, r4
	bl	mvc_se_v
	str	r0, [r10, #4032]
	ldrb	r3, [r9, #1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1898
	ldrb	r3, [r5, #1033]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1898
	ldr	r1, .L1938+48
	mov	r0, r4
	bl	mvc_se_v
	str	r0, [r10, #4036]
	b	.L1898
.L1874:
	mov	r2, r6
	ldr	r1, .L1938+52
	mvn	r8, #0
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r8
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1934:
	ldr	r1, .L1938+56
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #65536
	str	r0, [r5, #1076]
	bcs	.L1892
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1891
.L1892:
	ldr	r1, .L1938+60
	mov	r0, #1
	bl	dprint_vfmw
	b	.L1891
.L1929:
	ldr	r1, .L1938+64
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1913
.L1930:
	ldr	r1, .L1938+68
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1913
.L1931:
	ldr	r3, [r5, #2672]
	cmp	r3, #0
	bgt	.L1880
	ldr	r1, .L1938+72
	mov	r0, #1
	bl	dprint_vfmw
	b	.L1880
.L1933:
	ldr	r1, .L1938+76
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1913
.L1939:
	.align	2
.L1938:
	.word	.LC101
	.word	.LC105
	.word	.LC117
	.word	.LC118
	.word	g_event_report
	.word	.LC107
	.word	.LC109
	.word	.LC108
	.word	.LC119
	.word	.LC113
	.word	.LC114
	.word	.LC115
	.word	.LC116
	.word	.LC102
	.word	.LC111
	.word	.LC112
	.word	.LC103
	.word	.LC104
	.word	.LC106
	.word	.LC110
	UNWIND(.fnend)
	.size	MVC_ProcessSliceHeaderFirstPart, .-MVC_ProcessSliceHeaderFirstPart
	.align	2
	.global	MVC_ProcessSliceHeaderSecondPart
	.type	MVC_ProcessSliceHeaderSecondPart, %function
MVC_ProcessSliceHeaderSecondPart:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r4, r0, #11075584
	ldr	r3, [r0, #40]
	add	r4, r4, #40960
	mov	r5, r0
	sub	r3, r3, #1
	ldr	r6, [r0, #244]
	ldr	r2, [r4, #1048]
	cmp	r3, r2
	bcc	.L1941
	ldrb	r7, [r0, #10]	@ zero_extendqisi2
	cmp	r7, #0
	bne	.L1941
	bl	MVC_PPSSPSCheck
	cmp	r0, #0
	bne	.L2023
	ldrb	r3, [r4, #1032]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L2024
.L1945:
	ldr	r2, [r6, #36]
	cmp	r3, #1
	str	r2, [r4, #1092]
	ldr	r2, [r6, #40]
	str	r2, [r4, #1096]
	bls	.L2025
	cmp	r3, #2
	beq	.L1972
.L1956:
	mov	r3, #32
	str	r3, [r4, #1096]
.L1957:
	mov	r0, r5
	bl	mvc_ref_pic_list_reordering
	subs	r8, r0, #0
	bne	.L2026
	ldrb	r3, [r6, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1959
	ldrb	r3, [r4, #1032]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r7, #1
	moveq	r2, r7
	beq	.L1960
.L1959:
	ldr	r3, [r6, #44]
	cmp	r3, #1
	beq	.L2027
.L1976:
	mov	r2, #0
.L1960:
	strb	r7, [r4, #1039]
	mov	r0, #19
	ldr	r1, .L2033
	bl	dprint_vfmw
	ldrb	r2, [r4, #1039]	@ zero_extendqisi2
	mov	r3, #0
	str	r3, [r4, #1100]
	cmp	r2, r3
	str	r3, [r4, #1104]
	bne	.L2028
.L1961:
	ldrb	r3, [r4, #1040]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2029
.L1962:
	mov	r3, #0
	str	r3, [r4, #2644]
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1963
	ldrb	r3, [r4, #1032]	@ zero_extendqisi2
	cmp	r3, #1
	bls	.L2030
.L1963:
	ldr	r1, .L2033+4
	mov	r0, r5
	bl	mvc_se_v
	mov	r3, #0
	str	r3, [r4, #2652]
	str	r3, [r4, #2656]
	str	r3, [r4, #2660]
	str	r0, [r4, #2648]
	ldrb	r3, [r6, #3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2031
.L1992:
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1972:
	mov	r3, #32
	str	r3, [r4, #1092]
	b	.L1956
.L2031:
	ldr	r1, .L2033+8
	mov	r0, r5
	bl	mvc_ue_v
	cmp	r0, #2
	str	r0, [r4, #2652]
	bhi	.L1966
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1966
	cmp	r0, #1
	beq	.L1992
	ldr	r1, .L2033+12
	mov	r0, r5
	bl	mvc_se_v
	add	r3, r0, #6
	str	r0, [r4, #2656]
	cmp	r3, #12
	bhi	.L1969
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1969
	ldr	r1, .L2033+16
	mov	r0, r5
	bl	mvc_se_v
	add	r3, r0, #6
	str	r0, [r4, #2660]
	cmp	r3, #12
	bhi	.L1971
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1992
.L1971:
	ldr	r1, .L2033+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1992
.L2028:
	mov	r0, r5
	bl	mvc_pred_weight_table
	cmp	r0, #0
	beq	.L1961
	ldr	r1, .L2033+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1992
.L2029:
	mov	r0, r5
	bl	mvc_dec_ref_pic_marking
	cmp	r0, #0
	beq	.L1962
	ldr	r1, .L2033+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1992
.L2027:
	ldrb	r3, [r4, #1032]	@ zero_extendqisi2
	cmp	r3, #1
	moveq	r7, r3
	moveq	r2, r7
	bne	.L1976
	b	.L1960
.L2024:
	ldr	r1, .L2033+32
	mov	r0, r5
	bl	mvc_u_1
	ldrb	r3, [r4, #1032]	@ zero_extendqisi2
	strb	r0, [r4, #1038]
	b	.L1945
.L2025:
	ldr	r1, .L2033+36
	mov	r0, r5
	bl	mvc_u_1
	cmp	r0, #0
	bne	.L1947
	ldr	r3, [r4, #1092]
.L1948:
	ldrb	r2, [r4, #1033]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1949
	cmp	r3, #15
	bhi	.L1950
	ldr	r3, [r4, #1096]
	cmp	r3, #15
	bhi	.L2032
.L1951:
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1950
.L1952:
	ldrb	r3, [r4, #1032]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L1972
	cmp	r3, #1
	bne	.L1956
	b	.L1957
.L1941:
	ldr	r1, .L2033+40
	mvn	r8, #0
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2030:
	ldr	r1, .L2033+44
	mov	r0, r5
	bl	mvc_ue_v
	cmp	r0, #2
	str	r0, [r4, #2644]
	bhi	.L1964
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1963
.L1964:
	ldr	r1, .L2033+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1992
.L1949:
	cmp	r3, #31
	bhi	.L1953
	ldr	r3, [r4, #1096]
	cmp	r3, #31
	bls	.L1954
	ldrb	r3, [r4, #1032]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1954
.L1953:
	ldr	r1, .L2033+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1992
.L1954:
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1952
	b	.L1953
.L2032:
	ldrb	r3, [r4, #1032]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1951
.L1950:
	ldr	r1, .L2033+56
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1992
.L1947:
	ldr	r1, .L2033+60
	mov	r0, r5
	bl	mvc_ue_v
	ldrb	r2, [r4, #1032]	@ zero_extendqisi2
	cmp	r2, #1
	mov	r3, r0
	str	r0, [r4, #1092]
	bne	.L1948
	ldr	r1, .L2033+64
	mov	r0, r5
	bl	mvc_ue_v
	ldr	r3, [r4, #1092]
	str	r0, [r4, #1096]
	b	.L1948
.L1969:
	ldr	r1, .L2033+68
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1992
.L1966:
	ldr	r1, .L2033+72
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1992
.L2023:
	ldr	r1, .L2033+76
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1992
.L2026:
	ldr	r1, .L2033+80
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1992
.L2034:
	.align	2
.L2033:
	.word	.LC127
	.word	.LC132
	.word	.LC133
	.word	.LC135
	.word	.LC137
	.word	.LC138
	.word	.LC128
	.word	.LC129
	.word	.LC120
	.word	.LC121
	.word	.LC102
	.word	.LC130
	.word	.LC131
	.word	.LC125
	.word	.LC124
	.word	.LC122
	.word	.LC123
	.word	.LC136
	.word	.LC134
	.word	.LC103
	.word	.LC126
	UNWIND(.fnend)
	.size	MVC_ProcessSliceHeaderSecondPart, .-MVC_ProcessSliceHeaderSecondPart
	.align	2
	.global	MVC_ExitSlice
	.type	MVC_ExitSlice, %function
MVC_ExitSlice:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r2, r0, #11075584
	ldr	ip, [r0, #236]
	add	r3, r2, #40960
	ldrb	r1, [r3, #1033]	@ zero_extendqisi2
	ldr	lr, [r3, #1048]
	cmp	r1, #0
	ldr	r5, [r3, #1088]
	str	lr, [r3, #2700]
	ldr	r4, [ip, #744]
	strb	r1, [r3, #2688]
	ldrneb	r1, [r3, #1034]	@ zero_extendqisi2
	ldr	lr, [r3, #1060]
	str	r5, [r3, #2728]
	strneb	r1, [r3, #2689]
	ldrb	r1, [r3, #1035]	@ zero_extendqisi2
	str	lr, [r3, #2704]
	cmp	r1, #5
	ldrb	lr, [r3, #1040]	@ zero_extendqisi2
	strb	r1, [r3, #2690]
	ldreq	r1, [r3, #1076]
	str	r4, [r3, #2696]
	strb	lr, [r3, #2691]
	streq	r1, [r3, #2708]
	ldr	r1, [ip, #2900]
	cmp	r1, #0
	bne	.L2038
	add	r1, r2, #36864
	ldr	lr, [r1, #3996]
	str	lr, [r3, #2712]
	ldr	r1, [r1, #4000]
	str	r1, [r3, #2716]
	ldr	r1, [ip, #2900]
.L2038:
	cmp	r1, #1
	addeq	r2, r2, #36864
	ldreq	r1, [r2, #4032]
	streq	r1, [r3, #2720]
	ldreq	r2, [r2, #4036]
	streq	r2, [r3, #2724]
	ldrb	r2, [r3, #1043]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L2040
	ldr	ip, [r3, #2672]
	ldrb	r1, [r3, #1041]	@ zero_extendqisi2
	ldrb	r2, [r3, #1042]	@ zero_extendqisi2
	str	ip, [r3, #2732]
	strb	r1, [r3, #2692]
	strb	r2, [r3, #2693]
.L2040:
	ldr	r3, [r0, #80]
	add	r3, r3, #1
	str	r3, [r0, #80]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_ExitSlice, .-MVC_ExitSlice
	.align	2
	.global	MVC_PicTypeStatistic
	.type	MVC_PicTypeStatistic, %function
MVC_PicTypeStatistic:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #11075584
	add	r3, r3, #40960
	ldrb	r2, [r3, #1032]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L2046
	bcc	.L2047
	cmp	r2, #2
	ldmnefd	sp, {fp, sp, pc}
	ldrb	r3, [r3, #1035]	@ zero_extendqisi2
	add	r0, r0, #11141120
	cmp	r3, #5
	beq	.L2056
.L2049:
	add	r0, r0, #12288
	mov	r3, #0
	strb	r3, [r0, #3141]
	ldmfd	sp, {fp, sp, pc}
.L2047:
	add	r0, r0, #11141120
	add	r3, r0, #12288
	ldrb	r2, [r3, #3140]	@ zero_extendqisi2
	cmp	r2, #2
	movne	r2, #1
	strneb	r2, [r3, #3140]
	b	.L2049
.L2046:
	add	r0, r0, #11141120
	mov	r2, #2
	add	r0, r0, #12288
	mov	r3, #0
	strb	r2, [r0, #3140]
	strb	r3, [r0, #3141]
	ldmfd	sp, {fp, sp, pc}
.L2056:
	add	r0, r0, #12288
	mov	r3, #1
	strb	r3, [r0, #3141]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_PicTypeStatistic, .-MVC_PicTypeStatistic
	.align	2
	.global	MVC_CalcStreamBits
	.type	MVC_CalcStreamBits, %function
MVC_CalcStreamBits:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r3, r0, #11075584
	add	r3, r3, #36864
	mov	r4, r0
	ldrb	r3, [r3, #1752]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2058
	ldr	r2, [r0, #232]
	ldr	r3, [r2, #64]
	add	r3, r3, #7
	bic	r3, r3, #7
	str	r3, [r2, #64]
	ldr	r2, [r0, #232]
	ldr	r3, [r2, #72]
	sub	r3, r3, #1
	str	r3, [r2, #72]
.L2058:
	ldr	r3, [r4, #232]
	ldrb	r6, [r3]	@ zero_extendqisi2
	cmp	r6, #0
	beq	.L2069
	mov	r1, #0
	mov	r0, r3
	mov	r5, r1
.L2060:
	add	r1, r1, #1
	ldr	ip, [r0, #12]
	cmp	r1, r6
	add	r0, r0, #28
	add	r5, r5, ip
	bne	.L2060
.L2059:
	mov	r7, r6, asl #5
	ldr	r0, [r3, #72]
	sub	r7, r7, r6, asl #2
	ldr	r2, [r3, #64]
	add	r1, r3, r7
	mov	r3, r5
	str	r0, [sp, #4]
	mov	r0, #7
	ldr	ip, [r1, #12]
	ldr	r1, .L2080
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r4, #232]
	mov	r2, r6
	mov	r0, #7
	ldr	r1, .L2080+4
	ldrb	r6, [r3]	@ zero_extendqisi2
	ldr	ip, [r3, #64]
	mov	lr, r6, asl #5
	and	ip, ip, r0
	sub	lr, lr, r6, asl #2
	add	r3, r3, lr
	str	ip, [r3, #24]
	ldr	r3, [r4, #232]
	ldrb	r6, [r3]	@ zero_extendqisi2
	ldr	r8, [r3, #64]
	mov	lr, r6, asl #5
	sub	lr, lr, r6, asl #2
	add	r3, r3, lr
	ldr	ip, [r3, #16]
	add	ip, ip, r8, lsr #3
	rsb	ip, r5, ip
	str	ip, [r3, #28]
	ldr	ip, [r4, #232]
	ldrb	r6, [ip]	@ zero_extendqisi2
	ldr	lr, [ip, #64]
	mov	r3, r6, asl #5
	sub	r3, r3, r6, asl #2
	add	ip, ip, r3
	ldr	r3, [ip, #12]
	add	r3, r5, r3
	rsb	r3, lr, r3, lsl #3
	str	r3, [ip, #20]
	ldr	ip, [r4, #232]
	ldrb	lr, [ip]	@ zero_extendqisi2
	mov	r3, lr, asl #5
	sub	r3, r3, lr, asl #2
	add	r3, ip, r3
	ldr	ip, [r3, #28]
	ldr	lr, [r3, #24]
	and	ip, ip, #3
	add	ip, lr, ip, lsl #3
	str	ip, [r3, #24]
	ldr	ip, [r4, #232]
	ldrb	lr, [ip]	@ zero_extendqisi2
	mov	r3, lr, asl #5
	sub	r3, r3, lr, asl #2
	add	r3, ip, r3
	ldr	ip, [r3, #28]
	bic	ip, ip, #3
	str	ip, [r3, #28]
	ldr	ip, [r4, #232]
	add	r7, ip, r7
	ldrb	r5, [ip]	@ zero_extendqisi2
	ldr	r3, [r7, #24]
	mov	lr, r5, asl #5
	sub	lr, lr, r5, asl #2
	add	ip, ip, lr
	ldr	ip, [ip, #28]
	str	ip, [sp, #4]
	ldr	ip, [r7, #20]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	ip, [r4, #232]
	ldr	r2, [ip, #68]
	sub	r3, r2, #1
	cmp	r3, #1
	bhi	.L2079
	ldrb	r6, [ip]	@ zero_extendqisi2
	add	r1, r6, #1
	cmp	r2, r1
	movhi	r2, #1
	movls	r2, #0
	cmp	r1, #1
	movhi	r2, #0
	cmp	r2, #0
	beq	.L2062
	add	r6, r6, #2
	mov	r5, #0
.L2063:
	sub	r3, r6, #1
	ldr	r1, .L2080+8
	mov	r0, #7
	mov	lr, r3, asl #5
	mov	r2, r3
	sub	r3, lr, r3, asl #2
	add	ip, ip, r3
	str	r5, [ip, #24]
	ldr	ip, [r4, #232]
	add	ip, ip, r3
	ldr	lr, [ip, #16]
	str	lr, [ip, #28]
	ldr	ip, [r4, #232]
	add	ip, ip, r3
	ldr	lr, [ip, #12]
	mov	lr, lr, asl #3
	str	lr, [ip, #20]
	ldr	ip, [r4, #232]
	add	ip, ip, r3
	ldr	lr, [ip, #28]
	ldr	r7, [ip, #24]
	and	lr, lr, #3
	add	lr, r7, lr, lsl #3
	str	lr, [ip, #24]
	ldr	ip, [r4, #232]
	add	ip, ip, r3
	ldr	lr, [ip, #28]
	bic	lr, lr, #3
	str	lr, [ip, #28]
	ldr	ip, [r4, #232]
	add	ip, ip, r3
	ldr	r3, [ip, #24]
	ldr	ip, [ip, #20]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	ip, [r4, #232]
	ldr	r3, [ip, #68]
	cmp	r6, #1
	cmpls	r6, r3
	add	r6, r6, #1
	movcc	r2, #1
	movcs	r2, #0
	cmp	r2, #0
	bne	.L2063
	sub	r3, r3, #1
.L2062:
	mov	r2, r3, asl #5
	ldr	r1, [ip, #72]
	sub	r3, r2, r3, asl #2
	add	ip, ip, r3
	ldr	r3, [ip, #20]
	rsb	r3, r1, r3
	str	r3, [ip, #20]
	ldr	ip, [r4, #232]
	ldrb	r1, [ip]	@ zero_extendqisi2
	ldr	r3, [ip, #68]
	cmp	r1, r3
	bcs	.L2057
	sxth	r3, r1
	add	r4, r4, #11141120
	add	r4, r4, #12288
	mov	r2, r3, asl #5
	sub	r3, r2, r3, asl #2
	add	r3, ip, r3
.L2067:
	ldr	r2, [r3, #28]
	add	r1, r1, #1
	ldr	r0, [r4, #3848]
	add	r3, r3, #28
	cmp	r2, r0
	strcc	r2, [r4, #3848]
	ldr	r2, [ip, #68]
	cmp	r2, r1
	bhi	.L2067
.L2057:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2079:
	ldr	r1, .L2080+12
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	dprint_vfmw
.L2069:
	mov	r5, r6
	b	.L2059
.L2081:
	.align	2
.L2080:
	.word	.LC139
	.word	.LC140
	.word	.LC142
	.word	.LC141
	UNWIND(.fnend)
	.size	MVC_CalcStreamBits, .-MVC_CalcStreamBits
	.align	2
	.global	MVC_Scaling_List
	.type	MVC_Scaling_List, %function
MVC_Scaling_List:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	subs	r7, r3, #0
	str	r0, [fp, #-52]
	mov	r6, r2
	ble	.L2082
	mov	r0, #8
	mov	r4, #0
	mov	r2, r7
	mov	r9, r6
	ldr	r8, .L2093
	mov	r10, #255
	mov	r7, r1
	mov	r6, r0
	mov	r5, r4
	b	.L2087
.L2086:
	mov	lr, r4, lsr #2
	and	r3, r4, #3
	str	r6, [r7, r4, asl #2]
	uxtb	r1, r6
	mov	r4, r3, asl #3
	ldr	r3, [r9, lr, asl #2]
	cmp	r5, r2
	bic	r3, r3, r10, asl r4
	orr	r1, r3, r1, asl r4
	str	r1, [r9, lr, asl #2]
	beq	.L2082
.L2087:
	cmp	r2, #16
	ldreq	r3, .L2093+4
	ldrneb	r4, [r5, r8]	@ zero_extendqisi2
	ldreqb	r4, [r5, r3]	@ zero_extendqisi2
	cmp	r0, #0
	add	r5, r5, #1
	beq	.L2086
	ldr	r1, .L2093+8
	ldr	r0, [fp, #-52]
	str	r2, [fp, #-48]
	bl	mvc_se_v
	ldr	r2, [fp, #4]
	add	r0, r6, r0
	ands	r0, r0, #255
	moveq	r3, #1
	movne	r3, #0
	cmp	r3, #0
	moveq	r6, r0
	cmp	r4, #0
	movne	r3, #0
	andeq	r3, r3, #1
	str	r3, [r2]
	ldr	r2, [fp, #-48]
	b	.L2086
.L2082:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2094:
	.align	2
.L2093:
	.word	.LANCHOR0+16
	.word	.LANCHOR0
	.word	.LC143
	UNWIND(.fnend)
	.size	MVC_Scaling_List, .-MVC_Scaling_List
	.align	2
	.global	MVC_ProcessPPS
	.type	MVC_ProcessPPS, %function
MVC_ProcessPPS:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #44)
	sub	sp, sp, #44
	mov	r5, r1
	ldr	r1, .L2153
	mov	r4, r0
	bl	mvc_u_1
	strb	r0, [r5]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2144
	ldr	r1, .L2153+4
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #1]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2144
	ldr	r1, .L2153+8
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #0
	str	r0, [r5, #32]
	bne	.L2099
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2100
.L2099:
	ldr	r1, .L2153+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2153+16
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L2144
	mov	r3, #0
	ldr	r0, [r4, #120]
	mov	r2, r3
	mov	r1, #102
	blx	ip
	mvn	r0, #0
.L2097:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2107:
	ldr	r1, .L2153+20
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2153+24
	str	r0, [r5, #60]
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #18]
	cmp	r0, #1
	beq	.L2108
.L2126:
	ldr	r1, .L2153+28
	mov	r0, r4
	bl	mvc_se_v
	add	r3, r0, #12
	str	r0, [r5, #56]
	cmp	r3, #24
	bhi	.L2109
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2127
.L2109:
	ldr	r1, .L2153+32
	mov	r0, #1
	bl	dprint_vfmw
.L2144:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2100:
	ldr	r1, .L2153+36
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #31
	str	r0, [r5, #36]
	bhi	.L2101
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2101
	ldr	r1, .L2153+40
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #31
	str	r0, [r5, #40]
	bhi	.L2103
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2103
	ldr	r1, .L2153+44
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #2]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2144
	ldr	r2, .L2153+48
	mov	r1, #2
	mov	r0, r4
	bl	mvc_u_v
	cmp	r0, #2
	str	r0, [r5, #44]
	bhi	.L2145
	ldr	r1, .L2153+52
	mov	r0, r4
	bl	mvc_se_v
	ldr	r1, .L2153+56
	str	r0, [r5, #48]
	mov	r0, r4
	bl	mvc_se_v
	ldr	r1, .L2153+60
	mov	r0, r4
	bl	mvc_se_v
	ldr	r1, .L2153+64
	str	r0, [r5, #52]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2153+68
	strb	r0, [r5, #3]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2153+72
	strb	r0, [r5, #4]
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #17]
	cmp	r0, #0
	bne	.L2146
.L2106:
	ldr	r3, [r5, #52]
	mov	r6, #0
	add	r0, r4, #548
	str	r6, [r5, #60]
	strb	r6, [r5, #18]
	str	r3, [r5, #56]
	bl	BsResidBits
	ldr	r3, [r4, #232]
	ldr	r3, [r3, #72]
	add	r3, r3, #3
	cmp	r0, r3
	bcs	.L2107
.L2127:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2146:
	ldr	r1, .L2153+76
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2106
.L2101:
	ldr	r1, .L2153+80
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2097
.L2103:
	ldr	r1, .L2153+84
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2097
.L2108:
	sub	r8, fp, #72
	add	r10, r5, #4
	add	r7, r5, #2016
	add	r9, r5, #64
	b	.L2117
.L2150:
	ldr	lr, [r5, #28]
	ldr	r3, [r4, #248]
	mla	r3, ip, lr, r3
	ldrb	ip, [r3, #27]	@ zero_extendqisi2
	cmp	ip, #1
	beq	.L2147
	ldr	r3, .L2153+88
	cmp	r1, #0
	add	ip, r3, #16
	moveq	r3, ip
	mov	r1, r3
	ldr	r3, .L2153+92
	ldr	r3, [r3, #52]
	blx	r3
.L2112:
	add	r6, r6, #1
	add	r7, r7, #16
	cmp	r6, #6
	add	r9, r9, #64
	beq	.L2148
.L2117:
	ldr	r1, .L2153+96
	mov	r0, r4
	bl	mvc_u_1
	movw	ip, #3992
	clz	r1, r6
	mov	r2, #16
	cmp	r0, #1
	mov	r3, r0
	mov	r0, r7
	str	r3, [r8, #4]!
	strb	r3, [r10, #1]!
	beq	.L2149
	cmp	r6, #0
	cmpne	r6, #3
	mov	r1, r1, lsr #5
	beq	.L2150
	ldr	r3, .L2153+92
	mov	r2, #16
	sub	r1, r7, #16
	mov	r0, r7
	ldr	r3, [r3, #52]
	blx	r3
	b	.L2112
.L2148:
	add	r8, r5, #2112
	add	r10, r5, #448
	sub	r7, fp, #76
	add	r9, r5, #11
	mov	r6, #0
.L2125:
	ldr	r2, [r5, #60]
	mov	r3, #0
	cmp	r2, #1
	strne	r3, [r7]
	strneb	r3, [r9]
	beq	.L2151
.L2120:
	ldr	r1, [r4, #248]
	movw	ip, #3992
	ldr	r3, [r5, #28]
	mov	r0, r8
	mov	r2, #64
	mla	r3, ip, r3, r1
	ldrb	r1, [r3, #27]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L2152
	ldr	r1, .L2153+100
	cmp	r6, #0
	ldr	r3, .L2153+92
	add	ip, r1, #64
	ldr	r3, [r3, #52]
	movne	r1, ip
	blx	r3
.L2121:
	add	r6, r6, #1
	add	r8, r8, #64
	cmp	r6, #2
	add	r10, r10, #256
	add	r7, r7, #4
	add	r9, r9, #1
	bne	.L2125
	b	.L2126
.L2149:
	mov	r3, r2
	str	r8, [sp]
	mov	r2, r7
	mov	r1, r9
	mov	r0, r4
	bl	MVC_Scaling_List
	ldr	r3, [r8]
	cmp	r3, #1
	bne	.L2112
	ldr	r1, .L2153+88
	mov	r2, #16
	ldr	r3, .L2153+92
	cmp	r6, #2
	add	r0, r1, r2
	ldr	r3, [r3, #52]
	movhi	r1, r0
	mov	r0, r7
	blx	r3
	b	.L2112
.L2147:
	ldr	r2, .L2153+92
	add	r1, r6, #167
	mov	r0, r7
	add	r1, r3, r1, lsl #4
	ldr	ip, [r2, #52]
	mov	r2, #16
	blx	ip
	b	.L2112
.L2145:
	ldr	r1, .L2153+104
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2097
.L2151:
	ldr	r1, .L2153+108
	mov	r0, r4
	bl	mvc_u_1
	mov	r2, r8
	mov	r1, r10
	mov	r3, #64
	mov	ip, r0
	cmp	ip, #1
	mov	r0, r4
	str	ip, [r7]
	strb	ip, [r9]
	bne	.L2120
	str	r7, [sp]
	bl	MVC_Scaling_List
	ldr	r3, [r7]
	cmp	r3, #1
	bne	.L2121
	ldr	r1, .L2153+100
	mov	r2, #64
	ldr	r3, .L2153+92
	cmp	r6, #0
	add	r0, r1, r2
	ldr	r3, [r3, #52]
	movne	r1, r0
	mov	r0, r8
	blx	r3
	b	.L2121
.L2152:
	add	r1, r3, r6, lsl #6
	ldr	r3, .L2153+92
	add	r1, r1, #2768
	ldr	ip, [r3, #52]
	blx	ip
	b	.L2121
.L2154:
	.align	2
.L2153:
	.word	.LC144
	.word	.LC145
	.word	.LC146
	.word	.LC147
	.word	g_event_report
	.word	.LC162
	.word	.LC163
	.word	.LC164
	.word	.LC167
	.word	.LC148
	.word	.LC150
	.word	.LC152
	.word	.LC153
	.word	.LC155
	.word	.LC156
	.word	.LC157
	.word	.LC158
	.word	.LC159
	.word	.LC160
	.word	.LC161
	.word	.LC149
	.word	.LC151
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC165
	.word	.LANCHOR1+32
	.word	.LC154
	.word	.LC166
	UNWIND(.fnend)
	.size	MVC_ProcessPPS, .-MVC_ProcessPPS
	.align	2
	.global	MVC_PPSEqual
	.type	MVC_PPSEqual, %function
MVC_PPSEqual:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	subs	r6, r0, #0
	beq	.L2182
	cmp	r1, #0
	beq	.L2183
	ldr	r2, [r1, #28]
	ldr	r0, [r6, #28]
	ldr	r3, [r6, #24]
	ldr	ip, [r1, #24]
	ldrb	lr, [r6]	@ zero_extendqisi2
	cmp	r0, r2
	cmpeq	r3, ip
	ldrb	r4, [r1]	@ zero_extendqisi2
	ldrb	ip, [r6, #1]	@ zero_extendqisi2
	ldrb	r5, [r1, #1]	@ zero_extendqisi2
	moveq	r2, #1
	movne	r2, #0
	ldr	r0, [r6, #36]
	cmp	lr, r4
	movne	r3, #0
	andeq	r3, r2, #1
	ldr	r4, [r1, #36]
	cmp	ip, r5
	movne	lr, #0
	andeq	lr, r3, #1
	ldr	r2, [r6, #40]
	ldr	r5, [r1, #40]
	cmp	r0, r4
	movne	ip, #0
	andeq	ip, lr, #1
	ldrb	r3, [r6, #2]	@ zero_extendqisi2
	ldrb	r4, [r1, #2]	@ zero_extendqisi2
	cmp	r2, r5
	movne	r0, #0
	andeq	r0, ip, #1
	ldr	lr, [r6, #44]
	ldr	r5, [r1, #44]
	cmp	r3, r4
	movne	r2, #0
	andeq	r2, r0, #1
	ldr	ip, [r6, #48]
	ldr	r4, [r1, #48]
	cmp	lr, r5
	movne	r3, #0
	andeq	r3, r2, #1
	ldr	r0, [r6, #52]
	ldr	r5, [r1, #52]
	cmp	ip, r4
	movne	lr, #0
	andeq	lr, r3, #1
	ldrb	r2, [r6, #3]	@ zero_extendqisi2
	ldrb	r4, [r1, #3]	@ zero_extendqisi2
	cmp	r0, r5
	movne	ip, #0
	andeq	ip, lr, #1
	ldrb	r3, [r6, #4]	@ zero_extendqisi2
	ldrb	lr, [r1, #4]	@ zero_extendqisi2
	cmp	r2, r4
	movne	r0, #0
	andeq	r0, ip, #1
	ldr	ip, [r6, #60]
	ldr	r4, [r1, #60]
	cmp	r3, lr
	movne	r2, #0
	andeq	r2, r0, #1
	ldrb	r0, [r6, #18]	@ zero_extendqisi2
	ldrb	lr, [r1, #18]	@ zero_extendqisi2
	cmp	ip, r4
	movne	r3, #0
	andeq	r3, r2, #1
	cmp	lr, r0
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r0, #0
	beq	.L2159
	mov	ip, ip, asl #1
	adds	r2, ip, #6
	str	r2, [fp, #-56]
	beq	.L2159
	add	r2, r6, #4
	sub	r9, r1, #1088
	str	r2, [fp, #-52]
	add	r2, r1, #4
	str	r2, [fp, #-48]
	add	r2, r1, #64
	sub	r9, r9, #4
	add	r7, r1, #1984
	add	r8, r6, #1984
	mov	r10, r6
	mov	r5, r6
	str	r6, [fp, #-60]
	mov	r0, #0
	mov	r6, r2
	str	r1, [fp, #-64]
.L2164:
	ldr	r1, [fp, #-52]
	ldrb	r2, [r1, #1]!	@ zero_extendqisi2
	str	r1, [fp, #-52]
	ldr	r1, [fp, #-48]
	ldrsb	ip, [r1, #1]!
	str	r1, [fp, #-48]
	sxtb	r1, r2
	cmp	ip, r1
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, #0
	beq	.L2181
	ldr	r2, [r8]
	ldr	r1, [r7]
	cmp	r2, r1
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r0, #5
	bhi	.L2161
	cmp	r2, #0
	add	r4, r10, #64
	bne	.L2160
	add	r10, r10, #128
	mov	r1, r6
	mov	r2, r4
.L2162:
	ldr	lr, [r2], #4
	ldr	ip, [r1], #4
	cmp	lr, ip
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, r10
	bne	.L2162
.L2160:
	ldr	r2, [fp, #-56]
	add	r0, r0, #1
	add	r8, r8, #4
	add	r7, r7, #4
	cmp	r0, r2
	add	r5, r5, #256
	add	r9, r9, #256
	mov	r10, r4
	add	r6, r6, #64
	bne	.L2164
	ldr	r6, [fp, #-60]
	ldr	r1, [fp, #-64]
.L2159:
	ldr	r0, [r6, #56]
	ldr	r2, [r1, #56]
	cmp	r0, r2
	movne	r0, #0
	andeq	r0, r3, #1
	eor	r0, r0, #1
	rsb	r0, r0, #0
.L2157:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2161:
	cmp	r2, #0
	bne	.L2181
	sub	r2, r5, #1088
	sub	r4, r5, #836
	sub	r2, r2, #4
	mov	r1, r9
.L2163:
	ldr	lr, [r2, #4]!
	ldr	ip, [r1, #4]!
	cmp	lr, ip
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, r4
	bne	.L2163
.L2181:
	add	r4, r10, #64
	b	.L2160
.L2183:
	mov	r0, r1
	movw	r3, #10172
	ldr	r2, .L2184
	ldr	r1, .L2184+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2157
.L2182:
	movw	r3, #10171
	ldr	r2, .L2184
	ldr	r1, .L2184+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2157
.L2185:
	.align	2
.L2184:
	.word	.LC13
	.word	.LC14
	UNWIND(.fnend)
	.size	MVC_PPSEqual, .-MVC_PPSEqual
	.align	2
	.global	MVC_DecPPS
	.type	MVC_DecPPS, %function
MVC_DecPPS:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	r1, .L2201
	mov	r4, r0
	bl	mvc_ue_v
	ldr	r3, [r4, #40]
	sub	r3, r3, #1
	cmp	r0, r3
	mov	r5, r0
	bls	.L2187
	mov	r2, r0
	ldr	r1, .L2201+4
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r4, #40]
	sub	r3, r2, #1
	cmp	r5, r3
	bls	.L2194
	ldr	r3, .L2201+8
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L2194
	str	r2, [fp, #-40]
	mov	r3, #8
	str	r5, [fp, #-44]
	sub	r2, fp, #44
	ldr	r0, [r4, #120]
	mov	r1, #110
	blx	ip
	mvn	r0, #0
.L2188:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2187:
	ldr	r1, .L2201+12
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r3, [r4, #36]
	sub	r3, r3, #1
	cmp	r0, r3
	mov	ip, r0
	bhi	.L2198
	mov	r8, #2240
	ldr	r3, [r4, #252]
	mul	r6, r8, r5
	add	r3, r3, r6
	ldrb	r7, [r3, #19]	@ zero_extendqisi2
	cmp	r7, #0
	beq	.L2190
	ldr	r7, .L2201+16
	mov	r0, r4
	mov	r1, r7
	str	r5, [r7, #24]
	str	ip, [r7, #28]
	bl	MVC_ProcessPPS
	subs	r5, r0, #0
	bne	.L2199
	ldr	r1, [r4, #252]
	mov	r0, r7
	add	r1, r1, r6
	bl	MVC_PPSEqual
	cmp	r0, #0
	beq	.L2188
	ldr	ip, .L2201+20
	mov	r3, #1
	ldr	r0, [r4, #252]
	mov	r2, r8
	mov	r1, r7
	strb	r3, [r7, #20]
	add	r0, r0, r6
	ldr	ip, [ip, #56]
	strb	r3, [r7, #19]
	blx	ip
	mov	r0, r5
	b	.L2188
.L2190:
	str	r5, [r3, #24]
	mov	r0, r4
	ldr	r3, [r4, #252]
	add	r3, r3, r6
	str	ip, [r3, #28]
	ldr	r1, [r4, #252]
	add	r1, r1, r6
	bl	MVC_ProcessPPS
	cmp	r0, #0
	bne	.L2200
	ldr	r3, [r4, #252]
	mov	r2, #1
	add	r3, r3, r6
	strb	r2, [r3, #20]
	ldr	r3, [r4, #252]
	add	r6, r3, r6
	strb	r2, [r6, #19]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2194:
	mvn	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2198:
	ldr	r1, .L2201+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2188
.L2199:
	movw	r2, #9935
	ldr	r1, .L2201+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2188
.L2200:
	movw	r2, #9955
	ldr	r1, .L2201+28
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r4, #252]
	mov	r2, #1
	mvn	r0, #0
	add	r3, r3, r6
	strb	r2, [r3, #20]
	ldr	r3, [r4, #252]
	add	r6, r3, r6
	strb	r7, [r6, #19]
	b	.L2188
.L2202:
	.align	2
.L2201:
	.word	.LC168
	.word	.LC169
	.word	g_event_report
	.word	.LC170
	.word	.LANCHOR2
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC171
	.word	.LC172
	UNWIND(.fnend)
	.size	MVC_DecPPS, .-MVC_DecPPS
	.align	2
	.global	mvc_vui_parameters
	.type	mvc_vui_parameters, %function
mvc_vui_parameters:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r5, r1
	ldr	r1, .L2251
	mov	r4, r0
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5]
	cmp	r0, #0
	streqb	r0, [r5, #15]
	bne	.L2245
.L2205:
	ldr	r1, .L2251+4
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #1]
	cmp	r0, #0
	bne	.L2246
.L2206:
	ldr	r1, .L2251+8
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #3]
	cmp	r0, #0
	moveq	r3, #5
	streq	r3, [r5, #28]
	bne	.L2247
.L2208:
	ldr	r1, .L2251+12
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #6]
	cmp	r0, #0
	bne	.L2248
.L2209:
	ldr	r1, .L2251+16
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #8]
	cmp	r0, #0
	bne	.L2249
.L2211:
	ldr	r1, .L2251+20
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #7]
	cmp	r0, #0
	beq	.L2213
	ldr	r1, .L2251+24
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r2, .L2251+28
	mov	r1, #4
	str	r0, [r5, #96]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2251+32
	mov	r1, #4
	strb	r0, [r5, #92]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r3, [r5, #96]
	cmp	r3, #31
	strb	r0, [r5, #93]
	bhi	.L2216
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L2216
	add	r7, r5, #96
	add	r8, r5, #59
.L2217:
	ldr	r1, .L2251+36
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2251+40
	add	r6, r6, #1
	str	r0, [r7, #4]!
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2251+44
	str	r0, [r7, #128]
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r8, #1]!
	ldr	r3, [r5, #96]
	cmp	r3, r6
	bcs	.L2217
	ldr	r2, .L2251+48
	mov	r1, #5
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2251+52
	mov	r1, #5
	str	r0, [r5, #356]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2251+56
	mov	r1, #5
	str	r0, [r5, #360]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2251+60
	mov	r1, #5
	str	r0, [r5, #364]
	mov	r0, r4
	bl	mvc_u_v
	str	r0, [r5, #368]
.L2213:
	ldr	r1, .L2251+64
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #10]
	cmp	r0, #0
	bne	.L2250
	ldrb	r3, [r5, #7]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2222
.L2221:
	ldr	r1, .L2251+68
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2251+72
	strb	r0, [r5, #11]
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #12]
	cmp	r0, #0
	bne	.L2223
	ldrb	r0, [r4, #10]	@ zero_extendqisi2
.L2224:
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2250:
	ldr	r1, .L2251+24
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r2, .L2251+28
	mov	r1, #4
	str	r0, [r5, #408]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2251+32
	mov	r1, #4
	strb	r0, [r5, #404]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r3, [r5, #408]
	cmp	r3, #31
	strb	r0, [r5, #405]
	bhi	.L2216
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L2216
	add	r8, r5, #368
	add	r7, r5, #408
	add	r8, r8, #3
.L2219:
	ldr	r1, .L2251+36
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2251+40
	add	r6, r6, #1
	str	r0, [r7, #4]!
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2251+44
	str	r0, [r7, #128]
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r8, #1]!
	ldr	r3, [r5, #408]
	cmp	r3, r6
	bcs	.L2219
	ldr	r2, .L2251+48
	mov	r1, #5
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2251+52
	mov	r1, #5
	str	r0, [r5, #668]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2251+56
	mov	r1, #5
	str	r0, [r5, #672]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2251+60
	mov	r1, #5
	str	r0, [r5, #676]
	mov	r0, r4
	bl	mvc_u_v
	ldrb	r3, [r5, #7]	@ zero_extendqisi2
	cmp	r3, #0
	str	r0, [r5, #680]
	bne	.L2222
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2221
.L2222:
	ldr	r1, .L2251+76
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #14]
	b	.L2221
.L2249:
	ldr	r2, .L2251+80
	mov	r1, #32
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2251+84
	mov	r1, #32
	str	r0, [r5, #52]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r1, .L2251+88
	str	r0, [r5, #56]
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #9]
	cmp	r0, #1
	bne	.L2211
	ldr	r1, [r5, #52]
	cmp	r1, #0
	beq	.L2211
	ldr	r3, [r5, #56]
	mov	r0, #1000
	mul	r0, r0, r3
	bl	__aeabi_uidiv
	mov	r0, r0, lsr #1
	str	r0, [r4, #56]
	b	.L2211
.L2248:
	ldr	r1, .L2251+92
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2251+96
	str	r0, [r5, #44]
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r5, #48]
	b	.L2209
.L2247:
	ldr	r2, .L2251+100
	mov	r1, #3
	mov	r0, r4
	bl	mvc_u_v
	ldr	r1, .L2251+104
	str	r0, [r5, #28]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2251+108
	strb	r0, [r5, #4]
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #5]
	cmp	r0, #0
	beq	.L2208
	ldr	r2, .L2251+112
	mov	r1, #8
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2251+116
	mov	r1, #8
	str	r0, [r5, #32]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2251+120
	mov	r1, #8
	str	r0, [r5, #36]
	mov	r0, r4
	bl	mvc_u_v
	str	r0, [r5, #40]
	b	.L2208
.L2246:
	ldr	r1, .L2251+124
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #2]
	b	.L2206
.L2245:
	ldr	r2, .L2251+128
	mov	r1, #8
	mov	r0, r4
	bl	mvc_u_v
	uxtb	r0, r0
	strb	r0, [r5, #15]
	cmp	r0, #255
	bne	.L2205
	ldr	r2, .L2251+132
	mov	r1, #16
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2251+136
	mov	r1, #16
	str	r0, [r5, #16]
	mov	r0, r4
	bl	mvc_u_v
	str	r0, [r5, #20]
	b	.L2205
.L2223:
	ldr	r1, .L2251+140
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2251+144
	strb	r0, [r5, #13]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2251+148
	str	r0, [r5, #684]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2251+152
	str	r0, [r5, #688]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2251+156
	str	r0, [r5, #696]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2251+160
	str	r0, [r5, #692]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2251+164
	str	r0, [r5, #700]
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r5, #704]
	ldrb	r0, [r4, #10]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L2224
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2216:
	ldr	r1, .L2251+168
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2252:
	.align	2
.L2251:
	.word	.LC173
	.word	.LC177
	.word	.LC179
	.word	.LC186
	.word	.LC189
	.word	.LC193
	.word	.LC194
	.word	.LC195
	.word	.LC196
	.word	.LC198
	.word	.LC199
	.word	.LC200
	.word	.LC201
	.word	.LC202
	.word	.LC203
	.word	.LC204
	.word	.LC205
	.word	.LC207
	.word	.LC208
	.word	.LC206
	.word	.LC190
	.word	.LC191
	.word	.LC192
	.word	.LC187
	.word	.LC188
	.word	.LC180
	.word	.LC181
	.word	.LC182
	.word	.LC183
	.word	.LC184
	.word	.LC185
	.word	.LC178
	.word	.LC174
	.word	.LC175
	.word	.LC176
	.word	.LC209
	.word	.LC210
	.word	.LC211
	.word	.LC212
	.word	.LC213
	.word	.LC214
	.word	.LC215
	.word	.LC197
	UNWIND(.fnend)
	.size	mvc_vui_parameters, .-mvc_vui_parameters
	.align	2
	.global	MVC_SPSEqual
	.type	MVC_SPSEqual, %function
MVC_SPSEqual:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	subs	r5, r0, #0
	beq	.L2285
	cmp	r1, #0
	beq	.L2286
	ldrb	lr, [r1]	@ zero_extendqisi2
	ldrb	r3, [r5]	@ zero_extendqisi2
	ldr	ip, [r5, #736]
	ldr	r2, [r1, #736]
	ldrb	r0, [r5, #1]	@ zero_extendqisi2
	cmp	r3, lr
	cmpeq	ip, r2
	ldrb	r6, [r1, #1]	@ zero_extendqisi2
	ldrb	r2, [r5, #2]	@ zero_extendqisi2
	ldrb	r4, [r1, #2]	@ zero_extendqisi2
	moveq	lr, #1
	movne	lr, #0
	ldr	r3, [r5, #740]
	cmp	r0, r6
	movne	ip, #0
	andeq	ip, lr, #1
	ldr	r6, [r1, #740]
	cmp	r2, r4
	movne	r0, #0
	andeq	r0, ip, #1
	ldr	lr, [r1, #744]
	ldr	r4, [r5, #744]
	cmp	r3, r6
	movne	r2, #0
	andeq	r2, r0, #1
	ldrb	ip, [r1, #27]	@ zero_extendqisi2
	ldrb	r0, [r5, #27]	@ zero_extendqisi2
	cmp	r4, lr
	movne	r3, #0
	andeq	r3, r2, #1
	cmp	ip, r0
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r0, #0
	beq	.L2257
	add	r0, r1, #5
	add	r2, r5, #5
	sub	r9, r1, #404
	add	r7, r1, #748
	mov	ip, r0
	mov	r8, r5
	mov	r6, r5
	str	r5, [fp, #-48]
	mov	r0, #0
	mov	r4, r2
	mov	r5, ip
	str	r1, [fp, #-52]
.L2262:
	ldrb	r2, [r4, #1]!	@ zero_extendqisi2
	ldrsb	ip, [r5, #1]!
	sxtb	r1, r2
	cmp	ip, r1
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, #0
	beq	.L2258
	cmp	r0, #5
	bhi	.L2259
	add	r2, r6, #748
	add	r10, r6, #812
	mov	r1, r7
.L2260:
	ldr	lr, [r2, #4]!
	ldr	ip, [r1, #4]!
	cmp	lr, ip
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, r10
	bne	.L2260
.L2258:
	add	r0, r0, #1
	add	r8, r8, #256
	cmp	r0, #8
	add	r9, r9, #256
	add	r6, r6, #64
	add	r7, r7, #64
	bne	.L2262
	ldr	r5, [fp, #-48]
	ldr	r1, [fp, #-52]
.L2257:
	ldr	r2, [r1, #2896]
	ldr	ip, [r5, #2900]
	ldr	r0, [r1, #2900]
	ldr	lr, [r5, #2896]
	cmp	ip, r0
	cmpeq	lr, r2
	moveq	r2, #1
	movne	r2, #0
	cmp	ip, #0
	and	r3, r3, r2
	beq	.L2264
	cmp	ip, #1
	bne	.L2263
	ldr	r0, [r1, #2908]
	ldr	ip, [r5, #2908]
	ldrb	r2, [r5, #18]	@ zero_extendqisi2
	ldrb	r6, [r1, #18]	@ zero_extendqisi2
	ldr	r4, [r5, #2912]
	cmp	ip, r0
	cmpeq	r2, r6
	ldr	lr, [r1, #2912]
	ldr	r6, [r5, #2916]
	ldr	ip, [r1, #2916]
	moveq	r0, #1
	movne	r0, #0
	cmp	r4, lr
	movne	r2, #0
	andeq	r2, r0, #1
	cmp	r6, ip
	movne	r2, #0
	andeq	r2, r2, #1
	cmp	r6, #0
	and	r3, r3, r2
	beq	.L2263
	add	ip, r5, #2912
	add	r0, r1, #2912
	add	ip, ip, #4
	add	r0, r0, #4
	mov	r2, #0
.L2266:
	ldr	r4, [ip, #4]!
	add	r2, r2, #1
	ldr	lr, [r0, #4]!
	cmp	r4, lr
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, r6
	bne	.L2266
.L2263:
	ldrb	ip, [r1, #19]	@ zero_extendqisi2
	ldrb	lr, [r5, #19]	@ zero_extendqisi2
	ldr	r0, [r5, #3944]
	ldr	r4, [r1, #3944]
	ldr	r2, [r5, #3948]
	cmp	lr, ip
	cmpeq	r0, r4
	ldr	r7, [r1, #3948]
	ldr	r6, [r5, #3952]
	ldr	r4, [r1, #3952]
	moveq	ip, #1
	movne	ip, #0
	ldrb	lr, [r1, #20]	@ zero_extendqisi2
	cmp	r2, r7
	movne	r0, #0
	andeq	r0, ip, #1
	ldrb	ip, [r5, #20]	@ zero_extendqisi2
	cmp	r6, r4
	movne	r2, #0
	andeq	r2, r0, #1
	cmp	lr, ip
	movne	r2, #0
	andeq	r2, r2, #1
	cmp	ip, #0
	and	r3, r3, r2
	bne	.L2267
	ldrb	r0, [r5, #21]	@ zero_extendqisi2
	ldrb	r2, [r1, #21]	@ zero_extendqisi2
	cmp	r0, r2
	movne	r3, #0
	andeq	r3, r3, #1
.L2267:
	ldrb	r2, [r1, #22]	@ zero_extendqisi2
	ldrb	ip, [r5, #23]	@ zero_extendqisi2
	ldrb	r0, [r1, #23]	@ zero_extendqisi2
	ldrb	lr, [r5, #22]	@ zero_extendqisi2
	cmp	r0, ip
	cmpeq	lr, r2
	moveq	r2, #1
	movne	r2, #0
	cmp	ip, #0
	and	r3, r3, r2
	bne	.L2287
.L2268:
	ldrb	r2, [r5, #24]	@ zero_extendqisi2
	ldr	r0, [r5, #52]
	ldr	ip, [r1, #52]
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	cmp	r0, ip
	cmpeq	r2, r1
	moveq	r2, #1
	movne	r2, #0
	tst	r3, r2
	mvneq	r0, #0
	movne	r0, #0
.L2255:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2287:
	ldr	ip, [r1, #3960]
	ldr	lr, [r5, #3960]
	ldr	r0, [r5, #3956]
	ldr	r4, [r1, #3956]
	ldr	r2, [r1, #3964]
	cmp	lr, ip
	cmpeq	r0, r4
	ldr	r6, [r5, #3964]
	ldr	r4, [r5, #3968]
	ldr	lr, [r1, #3968]
	moveq	ip, #1
	movne	ip, #0
	cmp	r6, r2
	movne	r0, #0
	andeq	r0, ip, #1
	cmp	r4, lr
	movne	r2, #0
	andeq	r2, r0, #1
	and	r3, r3, r2
	b	.L2268
.L2259:
	sub	r2, r8, #404
	sub	r10, r8, #148
	mov	r1, r9
.L2261:
	ldr	lr, [r2, #4]!
	ldr	ip, [r1, #4]!
	cmp	lr, ip
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, r10
	bne	.L2261
	b	.L2258
.L2264:
	ldr	r0, [r5, #2904]
	ldr	r2, [r1, #2904]
	cmp	r0, r2
	movne	r3, #0
	andeq	r3, r3, #1
	b	.L2263
.L2286:
	mov	r0, r1
	movw	r3, #10416
	ldr	r2, .L2288
	ldr	r1, .L2288+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2255
.L2285:
	movw	r3, #10415
	ldr	r2, .L2288
	ldr	r1, .L2288+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2255
.L2289:
	.align	2
.L2288:
	.word	.LC13
	.word	.LC14
	UNWIND(.fnend)
	.size	MVC_SPSEqual, .-MVC_SPSEqual
	.global	__aeabi_idiv
	.align	2
	.global	MVC_GetDar
	.type	MVC_GetDar, %function
MVC_GetDar:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r4, r0, #0
	beq	.L2313
	subs	ip, r4, #255
	movne	ip, #1
	cmp	r4, #16
	movle	lr, #0
	andgt	lr, ip, #1
	cmp	lr, #0
	bne	.L2302
	cmp	r2, #0
	cmpne	r1, #0
	moveq	r0, #1
	movne	r0, #0
	cmp	r4, #255
	movne	r0, #0
	andeq	r0, r0, #1
	cmp	r0, #0
	bne	.L2303
	cmp	r4, #1
	moveq	r2, r0
	moveq	r4, #5
	beq	.L2291
	cmp	ip, #0
	ldrne	r0, .L2314
	addne	r4, r0, r4, lsl #3
	ldrne	r1, [r4, #100]
	ldrne	r2, [r4, #104]
	mul	r0, r3, r1
	ldr	r3, [fp, #4]
	mul	r1, r3, r2
	mov	r0, r0, asl #10
	bl	__aeabi_idiv
	movw	r3, #2405
	movw	r1, #2262
	cmp	r0, r3
	mov	r2, r0
	rsble	r3, r0, #2400
	subgt	r3, r0, #2400
	addle	r3, r3, #6
	subgt	r3, r3, #6
	cmp	r0, r1
	bgt	.L2295
	rsb	r1, r0, #2256
	add	r1, r1, #7
	cmp	r3, r1
	bge	.L2296
.L2306:
	mov	r4, #4
	b	.L2291
.L2302:
	mov	r4, #0
.L2313:
	mov	r2, r4
.L2291:
	mov	r3, r4
	ldr	r1, .L2314+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2295:
	sub	r1, r0, #2256
	sub	r1, r1, #7
	cmp	r3, r1
	blt	.L2306
.L2296:
	movw	r3, #1819
	cmp	r2, r3
	bgt	.L2297
	rsb	r3, r2, #1808
	add	r3, r3, #12
	cmp	r1, r3
	blt	.L2308
.L2298:
	movw	r1, #1364
	cmp	r2, r1
	rsble	r4, r2, #1360
	subgt	r4, r2, #1360
	addle	r4, r4, #5
	subgt	r4, r4, #5
	cmp	r3, r4
	movlt	r4, #2
	movge	r4, #1
	b	.L2291
.L2303:
	mov	r4, lr
	mov	r2, lr
	b	.L2291
.L2297:
	sub	r3, r2, #1808
	sub	r3, r3, #12
	cmp	r1, r3
	bge	.L2298
.L2308:
	mov	r4, #3
	b	.L2291
.L2315:
	.align	2
.L2314:
	.word	.LANCHOR0
	.word	.LC216
	UNWIND(.fnend)
	.size	MVC_GetDar, .-MVC_GetDar
	.align	2
	.global	MVC_ProcessSPS
	.type	MVC_ProcessSPS, %function
MVC_ProcessSPS:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #52)
	sub	sp, sp, #52
	subs	r5, r1, #0
	mov	r4, r0
	beq	.L2429
	ldr	r3, [r5, #736]
	cmp	r3, #100
	cmpne	r3, #122
	bic	r1, r3, #16
	sub	r3, r3, #110
	moveq	r2, #1
	movne	r2, #0
	cmp	r1, #128
	orreq	r2, r2, #1
	bics	r3, r3, #8
	orreq	r3, r2, #1
	movne	r3, r2
	cmp	r3, #0
	streqb	r3, [r5, #27]
	moveq	r3, #1
	streq	r3, [r5, #748]
	bne	.L2430
.L2329:
	ldr	r1, .L2444
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #12
	str	r0, [r5, #2896]
	bhi	.L2342
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2342
	ldr	r1, .L2444+4
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #2
	str	r0, [r5, #2900]
	bhi	.L2344
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2344
	cmp	r0, #0
	beq	.L2431
	cmp	r0, #1
	beq	.L2432
.L2350:
	ldr	r1, .L2444+8
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r5, #3944]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2427
	ldr	r1, .L2444+12
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #19]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2427
	ldr	r1, .L2444+16
	mov	r0, r4
	bl	mvc_ue_v
	movw	r7, #509
	sub	r3, r0, #1
	str	r0, [r5, #3948]
	cmp	r3, r7
	bhi	.L2355
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2355
	ldr	r1, .L2444+20
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r5, #3952]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2427
	ldr	r1, .L2444+24
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #20]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2427
	cmp	r0, #0
	bne	.L2433
	ldr	r1, .L2444+28
	mov	r0, r4
	bl	mvc_u_1
	ldr	r6, [r5, #3952]
	add	r6, r6, #1
	cmp	r6, #255
	strb	r0, [r5, #21]
	bhi	.L2388
	ldr	r3, [r5, #3948]
	add	r3, r3, #1
	cmp	r6, #1
	cmphi	r3, #3
	movhi	r8, #2
	bhi	.L2359
.L2388:
	ldr	r1, .L2444+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2420
.L2430:
	ldr	r1, .L2444+36
	bl	mvc_ue_v
	cmp	r0, #1
	str	r0, [r5, #748]
	bhi	.L2320
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2320
	ldr	r1, .L2444+40
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #0
	bne	.L2322
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2323
.L2322:
	ldr	r1, .L2444+44
	mov	r0, #1
	bl	dprint_vfmw
.L2323:
	ldr	r1, .L2444+48
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #0
	bne	.L2324
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2325
.L2324:
	ldr	r1, .L2444+52
	mov	r0, #1
	bl	dprint_vfmw
.L2325:
	ldr	r1, .L2444+56
	mov	r0, r4
	bl	mvc_u_1
	cmp	r0, #0
	bne	.L2326
	ldrb	r10, [r4, #10]	@ zero_extendqisi2
	cmp	r10, #0
	bne	.L2326
	ldr	r1, .L2444+60
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #27]
	cmp	r0, #1
	bne	.L2329
	sub	r7, fp, #72
	add	r9, r5, #5
	add	r6, r5, #2672
	add	r8, r5, #752
	b	.L2335
.L2436:
	ldr	r3, .L2444+64
	cmp	r1, #0
	add	ip, r3, #16
	moveq	r3, ip
	mov	r1, r3
	ldr	r3, .L2444+68
	ldr	r3, [r3, #52]
	blx	r3
.L2331:
	add	r10, r10, #1
	add	r6, r6, #16
	cmp	r10, #6
	add	r8, r8, #64
	beq	.L2434
.L2335:
	ldr	r1, .L2444+72
	mov	r0, r4
	bl	mvc_u_1
	clz	r1, r10
	mov	r2, #16
	mov	r1, r1, lsr #5
	cmp	r0, #1
	mov	r3, r0
	mov	r0, r6
	str	r3, [r7, #4]!
	strb	r3, [r9, #1]!
	beq	.L2435
	cmp	r10, #0
	cmpne	r10, #3
	beq	.L2436
	ldr	r3, .L2444+68
	mov	r2, #16
	sub	r1, r6, #16
	mov	r0, r6
	ldr	r3, [r3, #52]
	blx	r3
	b	.L2331
.L2386:
	cmp	r1, r9
	cmpcs	r0, r6
	bcs	.L2385
	ldr	r3, .L2444+76
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L2427
	strh	r1, [fp, #-72]	@ movhi
	mov	r3, #8
	strh	r0, [fp, #-70]	@ movhi
	sub	r2, fp, #76
	strh	r9, [fp, #-76]	@ movhi
	mov	r1, #107
	strh	r6, [fp, #-74]	@ movhi
	ldr	r0, [r4, #120]
	blx	ip
.L2427:
	mvn	r0, #0
.L2420:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2433:
	ldr	r6, [r5, #3952]
	strb	r3, [r5, #21]
	sub	r3, r6, #1
	cmp	r3, r7
	bhi	.L2388
	ldr	r3, [r5, #3948]
	mov	r8, #1
	add	r6, r6, #1
	add	r3, r3, r8
.L2359:
	mul	r6, r6, r8
	mov	r9, r3, asl #4
	mov	r6, r6, asl #4
	mul	r1, r9, r6
	add	r1, r1, r1, lsr #1
	cmp	r1, #100663296
	bhi	.L2437
	ldr	r2, [r5, #740]
	sub	r3, r2, #10
	cmp	r3, #31
	ldrls	pc, [pc, r3, asl #2]
	b	.L2361
.L2363:
	.word	.L2362
	.word	.L2364
	.word	.L2395
	.word	.L2395
	.word	.L2361
	.word	.L2361
	.word	.L2361
	.word	.L2361
	.word	.L2361
	.word	.L2361
	.word	.L2395
	.word	.L2366
	.word	.L2368
	.word	.L2361
	.word	.L2361
	.word	.L2361
	.word	.L2361
	.word	.L2361
	.word	.L2361
	.word	.L2361
	.word	.L2368
	.word	.L2369
	.word	.L2370
	.word	.L2361
	.word	.L2361
	.word	.L2361
	.word	.L2361
	.word	.L2361
	.word	.L2361
	.word	.L2361
	.word	.L2372
	.word	.L2372
.L2431:
	ldr	r1, .L2444+80
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #12
	str	r0, [r5, #2904]
	bhi	.L2347
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2350
.L2347:
	ldr	r1, .L2444+84
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2420
.L2395:
	mov	r0, #60416
	movt	r0, 13
.L2365:
	bl	__aeabi_uidiv
	ldr	r1, .L2444+88
	cmp	r0, #16
	movcc	r7, r0
	movcs	r7, #16
	mov	r2, r7
	mov	r0, #21
	bl	dprint_vfmw
	ldr	r2, [r5, #3944]
	cmp	r2, r7
	bhi	.L2373
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2374
.L2373:
	mov	r3, r7
	ldr	r1, .L2444+92
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, [r5, #3944]
	cmp	r3, #16
	bhi	.L2424
	cmp	r7, r3
	movcc	r7, r3
.L2424:
	str	r7, [r5, #3944]
.L2374:
	ldr	r1, .L2444+96
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #22]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2427
	ldr	r1, .L2444+100
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #23]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2427
	cmp	r0, #0
	bne	.L2438
.L2376:
	mov	r2, r9, lsr #1
	mov	r3, r6, lsr #1
	str	r9, [r5, #3976]
	str	r6, [r5, #3980]
	str	r2, [r5, #3984]
	str	r3, [r5, #3988]
.L2378:
	ldr	r1, .L2444+104
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r3, r0
	strb	r3, [r5, #24]
	ldrb	r2, [r4, #10]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L2427
	cmp	r3, #0
	mov	r2, #2
	str	r2, [r5, #68]
	bne	.L2439
	mov	r0, r3
	strb	r3, [r5, #43]
	mov	r3, #5
	str	r3, [r5, #56]
.L2381:
	ldr	r2, [r5, #48]
	mov	r3, r9
	ldr	r1, [r5, #44]
	str	r6, [sp]
	bl	MVC_GetDar
	ldr	r3, [r5, #3944]
	cmp	r3, #0
	str	r0, [r5, #52]
	beq	.L2384
	cmp	r7, r3
	movcs	r7, r3
.L2384:
	ldr	r3, [r4, #224]
	cmp	r7, #16
	movcs	r7, #16
	ldr	r2, [r3, #28]
	cmp	r2, #25
	beq	.L2440
.L2385:
	cmp	r6, #1920
	bcc	.L2387
	cmp	r7, #4
	movcs	r7, #4
.L2387:
	add	r7, r7, #1
	mov	r0, #0
	str	r7, [r5, #3972]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2372:
	mov	r0, #12582912
	b	.L2365
.L2368:
	mov	r0, #30208
	movt	r0, 47
	b	.L2365
.L2434:
	sub	r7, fp, #88
	add	r9, r5, #11
	add	r6, r5, #2768
	add	r8, r5, #1136
	mov	r10, #0
.L2340:
	ldr	r1, .L2444+72
	mov	r0, r4
	bl	mvc_u_1
	mov	r2, #64
	mov	r3, r0
	cmp	r3, #1
	mov	r0, r6
	str	r3, [r7, #4]!
	strb	r3, [r9, #1]!
	beq	.L2441
	ldr	r1, .L2444+108
	cmp	r10, #0
	ldr	r3, .L2444+68
	add	ip, r1, #64
	ldr	r3, [r3, #52]
	movne	r1, ip
	blx	r3
.L2337:
	add	r10, r10, #1
	add	r6, r6, #64
	cmp	r10, #2
	add	r8, r8, #256
	bne	.L2340
	b	.L2329
.L2435:
	mov	r3, r2
	str	r7, [sp]
	mov	r2, r6
	mov	r1, r8
	mov	r0, r4
	bl	MVC_Scaling_List
	ldr	r3, [r7]
	cmp	r3, #1
	bne	.L2331
	ldr	r1, .L2444+64
	mov	r2, #16
	ldr	r3, .L2444+68
	cmp	r10, #2
	add	r0, r1, r2
	ldr	r3, [r3, #52]
	movhi	r1, r0
	mov	r0, r6
	blx	r3
	b	.L2331
.L2320:
	ldr	r1, .L2444+112
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2342:
	ldr	r1, .L2444+116
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2420
.L2438:
	ldr	r1, .L2444+120
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2444+124
	str	r0, [r5, #3956]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2444+128
	str	r0, [r5, #3960]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2444+132
	str	r0, [r5, #3964]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r3, [r5, #3964]
	ldr	r2, [r5, #3956]
	mov	r1, r8, asl #1
	ldr	ip, [r5, #3960]
	mov	r3, r3, asl #1
	mov	r2, r2, asl #1
	mul	r8, r8, r3
	rsb	r3, r2, r9
	sub	r3, r3, ip, asl #1
	rsb	ip, r8, r6
	str	r0, [r5, #3968]
	mls	r0, r0, r1, ip
	cmp	r3, #0
	cmpgt	r0, #0
	ble	.L2376
	add	r2, r2, r3, lsr #1
	add	r8, r8, r0, lsr #1
	str	r2, [r5, #3984]
	str	r8, [r5, #3988]
	str	r3, [r5, #3976]
	str	r0, [r5, #3980]
	b	.L2378
.L2439:
	add	r1, r5, #28
	mov	r0, r4
	bl	mvc_vui_parameters
	cmp	r0, #0
	bne	.L2426
	ldrb	r3, [r5, #40]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2426
	ldr	r2, [r5, #732]
	clz	r3, r2
	mov	r3, r3, lsr #5
	cmp	r7, r2
	orrcc	r3, r3, #1
	cmp	r3, #0
	bne	.L2442
	ldr	r3, [r5, #3944]
	ldrb	r0, [r5, #43]	@ zero_extendqisi2
	cmp	r2, r3
	movcs	r7, r2
	movcc	r7, r3
	b	.L2381
.L2442:
	mov	r3, r7
	ldr	r1, .L2444+136
	mov	r0, #1
	bl	dprint_vfmw
.L2426:
	ldrb	r0, [r5, #43]	@ zero_extendqisi2
	b	.L2381
.L2440:
	ldr	r2, [r3, #724]
	cmp	r2, #0
	bne	.L2385
	ldr	r2, [r3, #708]
	ldr	r1, [r3, #684]
	cmp	r7, r2
	ldr	r0, [r3, #688]
	bls	.L2386
	ldr	r3, .L2444+76
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L2427
	str	r2, [fp, #-72]
	mov	r3, #8
	str	r7, [fp, #-76]
	sub	r2, fp, #76
	ldr	r0, [r4, #120]
	mov	r1, #106
	blx	ip
	mvn	r0, #0
	b	.L2420
.L2326:
	ldr	r1, .L2444+140
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2420
.L2432:
	ldr	r1, .L2444+144
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #18]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2427
	ldr	r1, .L2444+148
	mov	r0, r4
	bl	mvc_se_v
	str	r0, [r5, #2908]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2427
	ldr	r1, .L2444+152
	mov	r0, r4
	bl	mvc_se_v
	str	r0, [r5, #2912]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2427
	ldr	r1, .L2444+156
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #255
	str	r0, [r5, #2916]
	bhi	.L2352
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L2352
	cmp	r0, #0
	addne	r7, r5, #2912
	addne	r7, r7, #4
	bne	.L2354
	b	.L2350
.L2443:
	ldr	r3, [r5, #2916]
	cmp	r3, r6
	bls	.L2350
.L2354:
	ldr	r1, .L2444+160
	mov	r0, r4
	bl	mvc_se_v
	add	r6, r6, #1
	str	r0, [r7, #4]!
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2443
	b	.L2427
.L2355:
	mov	r2, r0
	ldr	r1, .L2444+164
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2420
.L2369:
	mov	r0, #30720
	movt	r0, 105
	b	.L2365
.L2366:
	mov	r0, #55296
	movt	r0, 27
	b	.L2365
.L2370:
	mov	r0, #7864320
	b	.L2365
.L2364:
	mov	r0, #17920
	movt	r0, 5
	b	.L2365
.L2362:
	mov	r0, #20992
	movt	r0, 2
	b	.L2365
.L2361:
	ldr	r1, .L2444+168
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2420
.L2352:
	ldr	r1, .L2444+172
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2420
.L2441:
	mov	r3, r2
	str	r7, [sp]
	mov	r2, r6
	mov	r1, r8
	mov	r0, r4
	bl	MVC_Scaling_List
	ldr	r3, [r7]
	cmp	r3, #1
	bne	.L2337
	ldr	r1, .L2444+108
	mov	r2, #64
	ldr	r3, .L2444+68
	cmp	r10, #0
	add	r0, r1, r2
	ldr	r3, [r3, #52]
	movne	r1, r0
	mov	r0, r6
	blx	r3
	b	.L2337
.L2344:
	ldr	r1, .L2444+176
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2420
.L2437:
	ldr	r1, .L2444+180
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2420
.L2429:
	mov	r0, r5
	movw	r3, #10606
	ldr	r2, .L2444+184
	ldr	r1, .L2444+188
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2420
.L2445:
	.align	2
.L2444:
	.word	.LC226
	.word	.LC228
	.word	.LC231
	.word	.LC239
	.word	.LC240
	.word	.LC242
	.word	.LC243
	.word	.LC257
	.word	.LC244
	.word	.LC217
	.word	.LC219
	.word	.LC220
	.word	.LC221
	.word	.LC222
	.word	.LC223
	.word	.LC225
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC165
	.word	g_event_report
	.word	.LC230
	.word	.LC232
	.word	.LC247
	.word	.LC248
	.word	.LC249
	.word	.LC250
	.word	.LC255
	.word	.LANCHOR1+32
	.word	.LC218
	.word	.LC227
	.word	.LC251
	.word	.LC252
	.word	.LC253
	.word	.LC254
	.word	.LC256
	.word	.LC224
	.word	.LC233
	.word	.LC234
	.word	.LC235
	.word	.LC236
	.word	.LC238
	.word	.LC241
	.word	.LC246
	.word	.LC237
	.word	.LC229
	.word	.LC245
	.word	.LC13
	.word	.LC14
	UNWIND(.fnend)
	.size	MVC_ProcessSPS, .-MVC_ProcessSPS
	.align	2
	.global	MVC_DecSPS
	.type	MVC_DecSPS, %function
MVC_DecSPS:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	ldr	r2, .L2491
	mov	r1, #8
	mov	r4, r0
	bl	mvc_u_v
	ldr	r1, .L2491+4
	mov	r7, r0
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2491+8
	mov	r9, r0
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2491+12
	mov	r8, r0
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2491+16
	str	r0, [fp, #-56]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2491+20
	str	r0, [fp, #-60]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2491+24
	str	r0, [fp, #-64]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r2, .L2491+28
	mov	r1, #2
	str	r0, [fp, #-68]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2491+32
	mov	r1, #8
	mov	r0, r4
	bl	mvc_u_v
	ldr	r1, .L2491+36
	mov	r5, r0
	mov	r0, r4
	bl	mvc_ue_v
	ldrb	r2, [r4, #10]	@ zero_extendqisi2
	cmp	r2, #0
	mov	r6, r0
	bne	.L2484
	ldr	r2, [r4, #36]
	sub	r2, r2, #1
	cmp	r0, r2
	bhi	.L2486
	cmp	r7, #100
	mov	r10, r7
	beq	.L2452
	bhi	.L2453
	cmp	r7, #77
	beq	.L2452
	cmp	r7, #88
	beq	.L2454
	cmp	r7, #66
	bne	.L2451
	ldr	r1, .L2491+40
	mov	r0, #1
	bl	dprint_vfmw
.L2452:
	cmp	r5, #9
	mov	r2, r5
	bls	.L2483
.L2489:
	cmp	r5, #41
	bhi	.L2483
.L2458:
	movw	r1, #3992
	ldr	r3, [r4, #248]
	mul	r5, r1, r6
	add	r3, r3, r5
	ldrb	ip, [r3, #25]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L2459
	ldr	r3, .L2491+44
	mov	r0, r4
	ldrb	ip, [fp, #-56]	@ zero_extendqisi2
	add	r1, r3, #2240
	str	r10, [r3, #2976]
	strb	ip, [r3, #2242]
	ldrb	ip, [fp, #-60]	@ zero_extendqisi2
	strb	r9, [r3, #2240]
	strb	r8, [r3, #2241]
	strb	ip, [r3, #2243]
	ldrb	ip, [fp, #-64]	@ zero_extendqisi2
	str	r2, [r3, #2980]
	str	r6, [r3, #2984]
	strb	ip, [r3, #2244]
	ldrb	ip, [fp, #-68]	@ zero_extendqisi2
	str	r3, [fp, #-56]
	strb	ip, [r3, #2245]
	bl	MVC_ProcessSPS
	ldr	r3, [fp, #-56]
	subs	r7, r0, #0
	bne	.L2487
	ldr	r1, [r4, #248]
	add	r0, r3, #2240
	str	r3, [fp, #-56]
	add	r1, r1, r5
	bl	MVC_SPSEqual
	ldr	r3, [fp, #-56]
	cmp	r0, #0
	bne	.L2488
.L2448:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2453:
	cmp	r7, #122
	beq	.L2456
	cmp	r7, #144
	beq	.L2456
	cmp	r7, #110
	beq	.L2456
.L2451:
	mov	r2, r7
	ldr	r1, .L2491+48
	mov	r0, #1
	mov	r10, #100
	bl	dprint_vfmw
	cmp	r5, #9
	mov	r2, r5
	bhi	.L2489
.L2483:
	mov	r3, #41
	ldr	r1, .L2491+52
	mov	r0, #1
	bl	dprint_vfmw
	mov	r2, #41
	b	.L2458
.L2459:
	str	r10, [r3, #736]
	mov	r0, r4
	ldr	r3, [r4, #248]
	ldrb	r1, [fp, #-56]	@ zero_extendqisi2
	str	ip, [fp, #-72]
	strb	r9, [r3, r5]
	ldr	r3, [r4, #248]
	add	r3, r3, r5
	strb	r8, [r3, #1]
	ldr	r3, [r4, #248]
	add	r3, r3, r5
	strb	r1, [r3, #2]
	ldr	r3, [r4, #248]
	ldrb	r1, [fp, #-60]	@ zero_extendqisi2
	add	r3, r3, r5
	strb	r1, [r3, #3]
	ldr	r3, [r4, #248]
	ldrb	r1, [fp, #-64]	@ zero_extendqisi2
	add	r3, r3, r5
	strb	r1, [r3, #4]
	ldr	r3, [r4, #248]
	ldrb	r1, [fp, #-68]	@ zero_extendqisi2
	add	r3, r3, r5
	strb	r1, [r3, #5]
	ldr	r3, [r4, #248]
	add	r3, r3, r5
	str	r2, [r3, #740]
	ldr	r3, [r4, #248]
	add	r3, r3, r5
	str	r6, [r3, #744]
	ldr	r1, [r4, #248]
	add	r1, r1, r5
	bl	MVC_ProcessSPS
	ldr	ip, [fp, #-72]
	cmp	r0, #0
	bne	.L2490
	ldr	r3, [r4, #248]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #26]
	ldr	r3, [r4, #248]
	add	r5, r3, r5
	strb	r2, [r5, #25]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2486:
	ldr	r1, .L2491+56
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r4, #36]
	sub	r3, r2, #1
	cmp	r6, r3
	bls	.L2484
	ldr	r3, .L2491+60
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L2484
	str	r2, [fp, #-48]
	mov	r3, #8
	str	r6, [fp, #-52]
	sub	r2, fp, #52
	ldr	r0, [r4, #120]
	mov	r1, #109
	blx	ip
.L2484:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2456:
	ldr	r1, .L2491+64
	mov	r0, #1
	bl	dprint_vfmw
	cmp	r5, #9
	mov	r2, r5
	bhi	.L2489
	b	.L2483
.L2454:
	ldr	r1, .L2491+68
	mov	r0, #1
	bl	dprint_vfmw
	cmp	r5, #9
	mov	r2, r5
	bhi	.L2489
	b	.L2483
.L2488:
	ldr	lr, .L2491+72
	mov	ip, #1
	ldr	r0, [r4, #248]
	movw	r2, #3992
	add	r1, r3, #2240
	strb	ip, [r3, #2266]
	add	r0, r0, r5
	ldr	r4, [lr, #56]
	strb	ip, [r3, #2265]
	blx	r4
	mov	r0, r7
	b	.L2448
.L2487:
	mov	r3, r6
	movw	r2, #11150
	ldr	r1, .L2491+76
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2448
.L2490:
	mov	r3, r6
	movw	r2, #11177
	ldr	r1, .L2491+76
	mov	r0, #1
	str	ip, [fp, #-56]
	bl	dprint_vfmw
	ldr	r3, [r4, #248]
	mov	r2, #1
	ldr	ip, [fp, #-56]
	mvn	r0, #0
	add	r3, r3, r5
	strb	r2, [r3, #26]
	ldr	r3, [r4, #248]
	add	r5, r3, r5
	strb	ip, [r5, #25]
	b	.L2448
.L2492:
	.align	2
.L2491:
	.word	.LC258
	.word	.LC259
	.word	.LC260
	.word	.LC261
	.word	.LC262
	.word	.LC263
	.word	.LC264
	.word	.LC265
	.word	.LC266
	.word	.LC267
	.word	.LC268
	.word	.LANCHOR2
	.word	.LC271
	.word	.LC272
	.word	.LC171
	.word	g_event_report
	.word	.LC270
	.word	.LC269
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC273
	UNWIND(.fnend)
	.size	MVC_DecSPS, .-MVC_DecSPS
	.align	2
	.global	MVC_FreeMvcExtMem
	.type	MVC_FreeMvcExtMem, %function
MVC_FreeMvcExtMem:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_FreeMvcExtMem, .-MVC_FreeMvcExtMem
	.align	2
	.global	MVC_FreeMvcVuiExtMem
	.type	MVC_FreeMvcVuiExtMem, %function
MVC_FreeMvcVuiExtMem:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_FreeMvcVuiExtMem, .-MVC_FreeMvcVuiExtMem
	.align	2
	.global	MVC_ProcessSUBSPSMvcExt
	.type	MVC_ProcessSUBSPSMvcExt, %function
MVC_ProcessSUBSPSMvcExt:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	subs	r5, r1, #0
	mov	r4, r0
	beq	.L2557
	ldr	r1, .L2558
	bl	mvc_ue_v
	cmp	r0, #1
	str	r0, [r5, #4]
	bhi	.L2498
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	addeq	r7, r5, #4
	bne	.L2498
.L2500:
	ldr	r1, .L2558+4
	mov	r0, r4
	bl	mvc_ue_v
	add	r6, r6, #1
	str	r0, [r7, #4]!
	ldr	r3, [r5, #4]
	cmp	r3, r6
	bcs	.L2500
	cmp	r3, #0
	mov	r2, #0
	str	r2, [r5, #16]
	str	r2, [r5, #24]
	beq	.L2501
	add	r8, r5, #16
	mov	r7, #1
.L2511:
	ldr	r1, .L2558+8
	mov	r0, r4
	bl	mvc_ue_v
	add	r9, r8, #4
	str	r0, [r8, #4]
	ldr	r3, [r5, #4]
	cmp	r3, #15
	movcs	r3, #15
	cmp	r0, r3
	bhi	.L2502
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L2502
	cmp	r0, #0
	addne	r10, r8, #16
	beq	.L2507
.L2506:
	ldr	r1, .L2558+12
	mov	r0, r4
	bl	mvc_ue_v
	add	r6, r6, #1
	str	r0, [r10, #4]!
	ldr	r3, [r9]
	cmp	r6, r3
	bcc	.L2506
.L2507:
	ldr	r1, .L2558+16
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r9, #8]
	ldr	r3, [r5, #4]
	cmp	r3, #15
	movcc	r2, r3
	movcs	r2, #15
	cmp	r0, r2
	bhi	.L2504
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L2504
	cmp	r0, #0
	addne	r8, r8, #24
	beq	.L2509
.L2510:
	ldr	r1, .L2558+20
	mov	r0, r4
	bl	mvc_ue_v
	add	r6, r6, #1
	str	r0, [r8, #4]!
	ldr	r3, [r9, #8]
	cmp	r6, r3
	bcc	.L2510
	ldr	r3, [r5, #4]
.L2509:
	add	r7, r7, #1
	mov	r8, r9
	cmp	r7, r3
	bls	.L2511
	cmp	r3, #0
	mov	r3, #0
	addne	r8, r5, #48
	str	r3, [r5, #48]
	str	r3, [r5, #56]
	movne	r7, #1
	beq	.L2525
.L2524:
	ldr	r1, .L2558+24
	mov	r0, r4
	bl	mvc_ue_v
	add	r9, r8, #4
	str	r0, [r8, #4]
	ldr	r3, [r5, #4]
	cmp	r3, #15
	movcs	r3, #15
	cmp	r0, r3
	bhi	.L2515
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L2515
	cmp	r0, #0
	addne	r10, r8, #16
	beq	.L2520
.L2519:
	ldr	r1, .L2558+28
	mov	r0, r4
	bl	mvc_ue_v
	add	r6, r6, #1
	str	r0, [r10, #4]!
	ldr	r3, [r9]
	cmp	r6, r3
	bcc	.L2519
.L2520:
	ldr	r1, .L2558+32
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r9, #8]
	ldr	r3, [r5, #4]
	cmp	r3, #15
	movcc	r2, r3
	movcs	r2, #15
	cmp	r0, r2
	bhi	.L2517
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L2517
	cmp	r0, #0
	addne	r8, r8, #24
	beq	.L2522
.L2523:
	ldr	r1, .L2558+36
	mov	r0, r4
	bl	mvc_ue_v
	add	r6, r6, #1
	str	r0, [r8, #4]!
	ldr	r3, [r9, #8]
	cmp	r6, r3
	bcc	.L2523
	ldr	r3, [r5, #4]
.L2522:
	add	r7, r7, #1
	mov	r8, r9
	cmp	r7, r3
	bls	.L2524
.L2525:
	ldr	r1, .L2558+40
	mov	r0, r4
	bl	mvc_ue_v
	add	r3, r0, #1
	str	r0, [r5, #80]
	cmp	r3, #16
	str	r3, [fp, #-60]
	bhi	.L2513
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2513
	ldr	r2, [fp, #-60]
	cmp	r2, #0
	beq	.L2530
	add	r2, r5, #8384
	add	r1, r5, #80
	add	r2, r2, #16
	str	r1, [fp, #-72]
	str	r2, [fp, #-68]
	add	r2, r5, #212
	str	r3, [fp, #-56]
	str	r2, [fp, #-64]
	str	r5, [fp, #-76]
.L2529:
	ldr	r2, .L2558+44
	mov	r1, #8
	mov	r0, r4
	bl	mvc_u_v
	ldr	r3, [fp, #-72]
	ldr	r1, .L2558+48
	str	r0, [r3, #4]!
	mov	r0, r4
	mov	r5, r3
	str	r3, [fp, #-72]
	bl	mvc_ue_v
	add	r3, r0, #1
	str	r0, [r5, #64]
	str	r3, [fp, #-52]
	mov	r2, r3
	cmp	r2, #64
	bhi	.L2527
	ldrb	r7, [r4, #10]	@ zero_extendqisi2
	cmp	r7, #0
	bne	.L2527
	cmp	r2, #0
	beq	.L2537
	ldr	r3, [fp, #-64]
	movw	r10, #8188
	ldr	r2, [fp, #-68]
	movt	r10, 4
	add	r10, r3, r10
	mov	r8, r3
	str	r2, [fp, #-48]
.L2536:
	ldr	r2, .L2558+52
	mov	r1, #3
	mov	r0, r4
	bl	mvc_u_v
	ldr	r1, .L2558+56
	str	r0, [r8], #4
	mov	r0, r4
	bl	mvc_ue_v
	add	r6, r0, #1
	str	r0, [r8, #4092]
	cmp	r6, #64
	bhi	.L2531
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2531
	cmp	r6, #0
	movne	r5, r3
	ldrne	r9, [fp, #-48]
	beq	.L2535
.L2532:
	ldr	r1, .L2558+60
	mov	r0, r4
	bl	mvc_ue_v
	add	r5, r5, #1
	cmp	r6, r5
	str	r0, [r9, #4]!
	bne	.L2532
.L2535:
	ldr	r1, .L2558+64
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #1024
	str	r0, [r10, #4]!
	bcs	.L2533
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2533
	ldr	r3, [fp, #-48]
	add	r7, r7, #1
	add	r3, r3, #256
	str	r3, [fp, #-48]
	ldr	r3, [fp, #-52]
	cmp	r3, r7
	bne	.L2536
.L2537:
	ldr	r2, [fp, #-64]
	ldr	r3, [fp, #-56]
	add	r2, r2, #256
	str	r2, [fp, #-64]
	ldr	r2, [fp, #-60]
	add	r3, r3, #1
	str	r3, [fp, #-56]
	cmp	r2, r3
	ldr	r3, [fp, #-68]
	add	r3, r3, #16384
	str	r3, [fp, #-68]
	bne	.L2529
.L2530:
	mov	r0, #0
	b	.L2549
.L2502:
	mov	r2, r0
	ldr	r1, .L2558+68
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
.L2549:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2504:
	mov	r2, r0
	ldr	r1, .L2558+72
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2517:
	mov	r2, r0
	ldr	r1, .L2558+76
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2549
.L2515:
	mov	r2, r0
	ldr	r1, .L2558+80
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2549
.L2498:
	mov	r2, r0
	movw	r3, #65534
	ldr	r1, .L2558+84
	mov	r0, #1
	str	r3, [r5, #80]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2549
.L2501:
	str	r3, [r5, #48]
	str	r3, [r5, #56]
	b	.L2525
.L2533:
	mov	r2, r0
	ldr	r1, .L2558+88
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2549
.L2531:
	ldr	r3, [fp, #-56]
	movw	ip, #65534
	ldr	r5, [fp, #-76]
	mov	r2, r6
	ldr	r1, .L2558+92
	mov	r0, #1
	add	r3, r7, r3, lsl #6
	add	r3, r3, #1072
	add	r3, r3, #4
	add	r3, r5, r3, lsl #2
	str	ip, [r3, #4]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2549
.L2557:
	mov	r0, r5
	movw	r3, #11297
	ldr	r2, .L2558+96
	ldr	r1, .L2558+100
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2549
.L2513:
	movw	r3, #65534
	ldr	r2, [fp, #-60]
	ldr	r1, .L2558+104
	mov	r0, #1
	str	r3, [r5, #80]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2549
.L2527:
	ldr	r3, [fp, #-56]
	mov	r0, #1
	ldr	r5, [fp, #-76]
	ldr	r2, [fp, #-52]
	add	r5, r5, r3, lsl #2
	ldr	r1, .L2558+108
	movw	r3, #65534
	str	r3, [r5, #148]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2549
.L2559:
	.align	2
.L2558:
	.word	.LC274
	.word	.LC276
	.word	.LC277
	.word	.LC280
	.word	.LC278
	.word	.LC282
	.word	.LC284
	.word	.LC287
	.word	.LC285
	.word	.LC289
	.word	.LC283
	.word	.LC291
	.word	.LC292
	.word	.LC294
	.word	.LC295
	.word	.LC298
	.word	.LC296
	.word	.LC279
	.word	.LC281
	.word	.LC288
	.word	.LC286
	.word	.LC275
	.word	.LC299
	.word	.LC297
	.word	.LC13
	.word	.LC14
	.word	.LC290
	.word	.LC293
	UNWIND(.fnend)
	.size	MVC_ProcessSUBSPSMvcExt, .-MVC_ProcessSUBSPSMvcExt
	.align	2
	.global	MVC_ProcessSUBSPSMvcVuiExt
	.type	MVC_ProcessSUBSPSMvcVuiExt, %function
MVC_ProcessSUBSPSMvcVuiExt:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 72
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #76)
	sub	sp, sp, #76
	mov	r5, r1
	ldr	r1, .L2595
	mov	r4, r0
	bl	mvc_ue_v
	add	r3, r5, #278528
	cmp	r0, #1024
	str	r0, [r3, #560]
	bcs	.L2591
	adds	r6, r0, #1
	mov	r1, #0
	adc	r7, r1, #0
	strd	r6, [fp, #-116]
	orrs	r2, r6, r7
	beq	.L2579
	add	r1, r5, #294912
	add	r9, r5, #315392
	add	r9, r9, #856
	movw	r2, #16687
	mov	ip, r1
	movw	r6, #34136
	movw	r1, #16751
	movw	r0, #33844
	mov	r8, r5
	movt	r2, 4
	add	ip, ip, #820
	add	r2, r5, r2
	movt	r6, 4
	str	r2, [fp, #-104]
	movt	r1, 4
	add	r6, r5, r6
	add	r2, r5, r1
	movt	r0, 4
	str	r2, [fp, #-96]
	add	r2, r3, #111
	str	ip, [fp, #-76]
	str	r2, [fp, #-88]
	add	r2, r5, r0
	str	r6, [fp, #-48]
	str	r2, [fp, #-80]
	add	r2, r3, #560
	str	r2, [fp, #-92]
	add	r2, r3, #176
	str	r2, [fp, #-72]
	add	r2, r3, #432
	str	r2, [fp, #-52]
	add	r2, r3, #496
	str	r2, [fp, #-56]
	add	r2, r3, #240
	add	r3, r3, #816
	str	r2, [fp, #-84]
	str	r3, [fp, #-60]
	mov	r2, #1
	mov	r3, #0
	strd	r2, [fp, #-68]
	mov	r3, #0
	str	r3, [fp, #-100]
.L2578:
	ldr	r2, .L2595+4
	mov	r1, #3
	mov	r0, r4
	bl	mvc_u_v
	ldr	r3, [fp, #-88]
	ldr	r1, .L2595+8
	strb	r0, [r3, #1]!
	mov	r0, r4
	str	r3, [fp, #-88]
	bl	mvc_ue_v
	ldr	r3, [fp, #-92]
	cmp	r0, #1024
	str	r0, [r3, #4]!
	str	r3, [fp, #-92]
	bcs	.L2592
	adds	r5, r0, #1
	beq	.L2568
	ldr	r10, [fp, #-60]
	mov	r7, #0
	ldr	r6, [fp, #-48]
.L2565:
	ldr	r1, .L2595+12
	mov	r0, r4
	bl	mvc_ue_v
	add	r7, r7, #1
	cmp	r5, r7
	str	r0, [r10, #4]!
	bne	.L2565
	str	r6, [fp, #-48]
.L2568:
	ldr	r1, .L2595+16
	mov	r0, r4
	bl	mvc_u_1
	ldr	r3, [fp, #-96]
	uxtb	r0, r0
	strb	r0, [r3, #1]!
	cmp	r0, #0
	str	r3, [fp, #-96]
	bne	.L2593
.L2567:
	ldr	r1, .L2595+20
	mov	r0, r4
	bl	mvc_u_1
	ldr	r3, [fp, #-52]
	uxtb	r0, r0
	strb	r0, [r3]
	cmp	r0, #0
	beq	.L2569
	ldr	r1, .L2595+24
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r5, [fp, #-48]
	ldr	r2, .L2595+28
	mov	r1, #4
	str	r0, [r5]
	mov	r0, r4
	bl	mvc_u_v
	movw	r3, #34132
	movt	r3, 4
	add	r3, r8, r3
	ldr	r2, .L2595+32
	mov	r1, #4
	strb	r0, [r3]
	mov	r0, r4
	bl	mvc_u_v
	movw	r3, #34133
	movt	r3, 4
	add	r3, r8, r3
	strb	r0, [r3]
	ldr	r3, [r5]
	cmp	r3, #31
	bhi	.L2571
	ldrb	r5, [r4, #10]	@ zero_extendqisi2
	cmp	r5, #0
	bne	.L2571
	ldr	r6, [fp, #-48]
	movw	r10, #34099
	movt	r10, 4
	add	r10, r8, r10
	mov	r7, r6
.L2572:
	ldr	r1, .L2595+36
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2595+40
	add	r5, r5, #1
	str	r0, [r7, #4]!
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2595+44
	str	r0, [r7, #128]
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r10, #1]!
	ldr	r3, [r6]
	cmp	r3, r5
	bcs	.L2572
	ldr	r2, .L2595+48
	mov	r1, #5
	mov	r0, r4
	str	r6, [fp, #-48]
	bl	mvc_u_v
	movw	r3, #34396
	movt	r3, 4
	add	r3, r8, r3
	ldr	r2, .L2595+52
	mov	r1, #5
	str	r0, [r3]
	mov	r0, r4
	bl	mvc_u_v
	add	r3, r8, #294912
	ldr	r2, .L2595+56
	mov	r1, #5
	str	r0, [r3, #1632]
	mov	r0, r4
	bl	mvc_u_v
	movw	r3, #34404
	movt	r3, 4
	add	r3, r8, r3
	ldr	r2, .L2595+60
	mov	r1, #5
	str	r0, [r3]
	mov	r0, r4
	bl	mvc_u_v
	movw	r3, #34408
	movt	r3, 4
	add	r3, r8, r3
	str	r0, [r3]
.L2569:
	ldr	r1, .L2595+64
	mov	r0, r4
	bl	mvc_u_1
	ldr	r3, [fp, #-56]
	uxtb	r0, r0
	strb	r0, [r3]
	cmp	r0, #0
	bne	.L2594
	ldr	r3, [fp, #-52]
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2577
.L2576:
	ldr	r1, .L2595+68
	mov	r0, r4
	bl	mvc_u_1
	ldrd	r2, [fp, #-68]
	ldrd	r6, [fp, #-116]
	add	r8, r8, #312
	add	r9, r9, #312
	cmp	r7, r3
	ldr	r3, [fp, #-100]
	cmpeq	r6, r2
	add	r1, r3, #1
	ldr	r3, [fp, #-72]
	str	r1, [fp, #-100]
	add	r3, r3, #1
	str	r3, [fp, #-72]
	movhi	r3, #1
	movls	r3, #0
	cmp	r1, #63
	movhi	r1, #0
	andls	r1, r3, #1
	ldrd	r2, [fp, #-68]
	adds	r6, r2, #1
	adc	r7, r3, #0
	ldr	r3, [fp, #-52]
	cmp	r1, #0
	strd	r6, [fp, #-68]
	add	r3, r3, #1
	str	r3, [fp, #-52]
	ldr	r3, [fp, #-56]
	add	r3, r3, #1
	str	r3, [fp, #-56]
	ldr	r3, [fp, #-48]
	add	r3, r3, #312
	str	r3, [fp, #-48]
	ldr	r3, [fp, #-76]
	add	r3, r3, #4
	str	r3, [fp, #-76]
	ldr	r3, [fp, #-80]
	add	r3, r3, #4
	str	r3, [fp, #-80]
	ldr	r3, [fp, #-84]
	add	r3, r3, #1
	str	r3, [fp, #-84]
	ldr	r3, [fp, #-60]
	add	r3, r3, #256
	str	r3, [fp, #-60]
	ldr	r3, [fp, #-104]
	strb	r0, [r3, #1]!
	str	r3, [fp, #-104]
	bne	.L2578
.L2579:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2594:
	ldr	r1, .L2595+24
	mov	r0, r4
	bl	mvc_ue_v
	add	r3, r8, #315392
	ldr	r2, .L2595+28
	mov	r1, #4
	mov	r5, r3
	str	r3, [fp, #-108]
	str	r0, [r9]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2595+32
	mov	r1, #4
	strb	r0, [r5, #852]
	mov	r0, r4
	bl	mvc_u_v
	movw	r3, #54101
	movt	r3, 4
	add	r3, r8, r3
	strb	r0, [r3]
	ldr	r3, [r9]
	cmp	r3, #31
	bhi	.L2571
	ldrb	r5, [r4, #10]	@ zero_extendqisi2
	cmp	r5, #0
	bne	.L2571
	movw	r10, #54067
	ldr	r6, [fp, #-48]
	movt	r10, 4
	add	r10, r8, r10
	mov	r7, r9
.L2574:
	ldr	r1, .L2595+36
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2595+40
	add	r5, r5, #1
	str	r0, [r7, #4]!
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2595+44
	str	r0, [r7, #128]
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r10, #1]!
	ldr	r3, [r9]
	cmp	r3, r5
	bcs	.L2574
	ldr	r2, .L2595+48
	mov	r1, #5
	mov	r0, r4
	str	r6, [fp, #-48]
	bl	mvc_u_v
	movw	r3, #54364
	movt	r3, 4
	add	r3, r8, r3
	ldr	r2, .L2595+52
	mov	r1, #5
	str	r0, [r3]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r3, [fp, #-108]
	ldr	r2, .L2595+56
	mov	r1, #5
	str	r0, [r3, #1120]
	mov	r0, r4
	bl	mvc_u_v
	movw	r3, #54372
	movt	r3, 4
	add	r3, r8, r3
	ldr	r2, .L2595+60
	mov	r1, #5
	str	r0, [r3]
	mov	r0, r4
	bl	mvc_u_v
	movw	r3, #54376
	movt	r3, 4
	add	r3, r8, r3
	str	r0, [r3]
	ldr	r3, [fp, #-52]
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2577
	ldr	r3, [fp, #-56]
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2576
.L2577:
	ldr	r1, .L2595+72
	mov	r0, r4
	bl	mvc_u_1
	ldr	r3, [fp, #-72]
	strb	r0, [r3]
	b	.L2576
.L2593:
	ldr	r2, .L2595+76
	mov	r1, #32
	mov	r0, r4
	bl	mvc_u_v
	ldr	r3, [fp, #-76]
	ldr	r2, .L2595+80
	mov	r1, #32
	str	r0, [r3]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r3, [fp, #-80]
	ldr	r1, .L2595+84
	str	r0, [r3]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r3, [fp, #-84]
	strb	r0, [r3]
	b	.L2567
.L2571:
	ldr	r1, .L2595+88
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
.L2589:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2592:
	mov	r2, r0
	ldr	r1, .L2595+92
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2591:
	mov	r2, r0
	ldr	r1, .L2595+96
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2589
.L2596:
	.align	2
.L2595:
	.word	.LC300
	.word	.LC302
	.word	.LC303
	.word	.LC306
	.word	.LC305
	.word	.LC310
	.word	.LC311
	.word	.LC312
	.word	.LC313
	.word	.LC314
	.word	.LC315
	.word	.LC316
	.word	.LC317
	.word	.LC318
	.word	.LC319
	.word	.LC320
	.word	.LC321
	.word	.LC323
	.word	.LC322
	.word	.LC307
	.word	.LC308
	.word	.LC309
	.word	.LC197
	.word	.LC304
	.word	.LC301
	UNWIND(.fnend)
	.size	MVC_ProcessSUBSPSMvcVuiExt, .-MVC_ProcessSUBSPSMvcVuiExt
	.align	2
	.global	MVC_DecSubSPS
	.type	MVC_DecSubSPS, %function
MVC_DecSubSPS:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	ldr	r2, .L2625
	mov	r1, #8
	mov	r4, r0
	bl	mvc_u_v
	ldr	r1, .L2625+4
	mov	r7, r0
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2625+8
	mov	r10, r0
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2625+12
	str	r0, [fp, #-48]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2625+16
	str	r0, [fp, #-52]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2625+20
	str	r0, [fp, #-56]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2625+24
	str	r0, [fp, #-60]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r2, .L2625+28
	mov	r1, #2
	str	r0, [fp, #-64]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2625+32
	mov	r1, #8
	mov	r0, r4
	bl	mvc_u_v
	ldr	r1, .L2625+36
	mov	r8, r0
	mov	r0, r4
	bl	mvc_ue_v
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r5, r0
	bne	.L2610
	cmp	r0, #31
	bhi	.L2620
	sub	r3, r7, #66
	cmp	r3, #78
	ldrls	pc, [pc, r3, asl #2]
	b	.L2600
.L2602:
	.word	.L2601
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2603
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2604
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2603
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2605
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2603
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2605
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2603
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2600
	.word	.L2605
.L2601:
	ldr	r1, .L2625+40
	mov	r0, #1
	bl	dprint_vfmw
.L2603:
	cmp	r8, #41
	bhi	.L2621
.L2606:
	movw	r3, #8500
	movw	r2, #26248
	movt	r3, 5
	movt	r2, 4
	mul	r3, r3, r5
	mov	r0, r4
	add	r9, r4, r3
	add	r6, r9, #286720
	add	r2, r9, r2
	str	r3, [fp, #-68]
	add	r1, r6, #932
	ldrb	r3, [fp, #-48]	@ zero_extendqisi2
	str	r8, [r6, #1672]
	str	r7, [r6, #1668]
	strb	r3, [r6, #933]
	ldrb	r3, [fp, #-52]	@ zero_extendqisi2
	strb	r10, [r6, #932]
	strb	r3, [r6, #934]
	ldrb	r3, [fp, #-56]	@ zero_extendqisi2
	strb	r3, [r6, #935]
	ldrb	r3, [fp, #-60]	@ zero_extendqisi2
	strb	r3, [r6, #936]
	ldrb	r3, [fp, #-64]	@ zero_extendqisi2
	strb	r3, [r6, #937]
	str	r5, [r2, #4]
	bl	MVC_ProcessSPS
	ldr	r3, [fp, #-68]
	subs	r8, r0, #0
	bne	.L2622
	cmp	r7, #118
	cmpne	r7, #128
	mov	r10, #1
	strb	r10, [r6, #957]
	beq	.L2623
.L2608:
	movw	r3, #8500
	mov	r2, #1
	movt	r3, 5
	mla	r4, r3, r5, r4
	add	r4, r4, #12992
	strb	r2, [r4, #12]
.L2598:
	mov	r0, r8
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2621:
	mov	r2, r8
	ldr	r1, .L2625+44
	mov	r0, #1
	mov	r8, #41
	bl	dprint_vfmw
	b	.L2606
.L2623:
	ldr	r1, .L2625+48
	mov	r0, r4
	str	r3, [fp, #-48]
	bl	mvc_u_1
	ldr	r3, [fp, #-48]
	add	r9, r9, #12992
	add	r9, r9, #8
	add	r3, r4, r3
	add	r7, r3, #12992
	add	r7, r7, #12
	mov	r1, r7
	strb	r0, [r9, #5]
	mov	r0, r4
	bl	MVC_ProcessSUBSPSMvcExt
	cmp	r0, #0
	bne	.L2624
	ldr	r1, .L2625+52
	mov	r0, r4
	bl	mvc_u_1
	cmp	r0, #0
	str	r0, [r6, #928]
	beq	.L2608
	mov	r1, r7
	mov	r0, r4
	bl	MVC_ProcessSUBSPSMvcVuiExt
	cmp	r0, #0
	beq	.L2608
	mov	r0, r10
	ldr	r1, .L2625+56
	bl	dprint_vfmw
	strb	r8, [r9, #4]
	mvn	r8, #0
	b	.L2598
.L2605:
	ldr	r1, .L2625+60
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2603
.L2604:
	ldr	r1, .L2625+64
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2603
.L2600:
	mov	r2, r7
	ldr	r1, .L2625+68
	mov	r0, #1
	mvn	r8, #0
	bl	dprint_vfmw
	mov	r0, r8
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2610:
	mvn	r8, #0
	b	.L2598
.L2620:
	ldr	r1, .L2625+72
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L2598
.L2622:
	ldr	r1, .L2625+76
	mov	r0, #1
	bl	dprint_vfmw
	add	ip, r9, #12992
	mov	r3, #0
	mvn	r8, #0
	strb	r3, [ip, #12]
	strb	r3, [r6, #957]
	b	.L2598
.L2624:
	mov	r0, r10
	ldr	r1, .L2625+80
	bl	dprint_vfmw
	strb	r8, [r9, #4]
	mvn	r8, #0
	b	.L2598
.L2626:
	.align	2
.L2625:
	.word	.LC324
	.word	.LC325
	.word	.LC326
	.word	.LC327
	.word	.LC328
	.word	.LC329
	.word	.LC330
	.word	.LC331
	.word	.LC332
	.word	.LC333
	.word	.LC268
	.word	.LC335
	.word	.LC337
	.word	.LC339
	.word	.LC340
	.word	.LC270
	.word	.LC269
	.word	.LC334
	.word	.LC171
	.word	.LC336
	.word	.LC338
	UNWIND(.fnend)
	.size	MVC_DecSubSPS, .-MVC_DecSubSPS
	.align	2
	.global	MVC_PassBytes
	.type	MVC_PassBytes, %function
MVC_PassBytes:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, [r0, #232]
	cmp	ip, #0
	cmpne	r1, #0
	beq	.L2636
	ldrb	r3, [ip]	@ zero_extendqisi2
	mov	r2, r3, asl #2
	mov	r5, r3, asl #5
	rsb	r4, r2, r5
	add	r4, ip, r4
	add	r6, r4, #8
	ldr	lr, [r4, #8]
	cmp	lr, #0
	beq	.L2636
	ldr	lr, [ip, #68]
	cmp	r3, #1
	cmpls	lr, #2
	bhi	.L2636
	cmp	lr, r3
	bls	.L2636
	ldr	lr, [r4, #12]
	mov	r6, r2
	ldr	r4, [r4, #24]
	mov	lr, lr, asl #3
	add	r1, r4, r1, lsl #3
	cmp	r1, lr
	bhi	.L2631
	b	.L2629
.L2632:
	ldr	r4, [r2, #24]
	ldr	r2, [r2, #12]
	rsb	lr, lr, r4
	add	r1, r1, lr
	mov	lr, r2, asl #3
	cmp	r1, lr
	bls	.L2629
.L2631:
	rsb	r2, r6, r5
	add	r3, r3, #1
	add	ip, ip, r2
	mov	r6, r3, asl #2
	mov	r5, r3, asl #5
	str	lr, [ip, #24]
	rsb	r2, r6, r5
	ldr	ip, [r0, #232]
	ldrb	r4, [ip]	@ zero_extendqisi2
	add	r4, r4, #1
	strb	r4, [ip]
	ldr	ip, [r0, #232]
	add	r2, ip, r2
	ldr	r4, [ip, #68]
	cmp	r4, r3
	bhi	.L2632
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L2629:
	rsb	r2, r6, r5
	mov	r0, #1
	add	ip, ip, r2
	str	r1, [ip, #24]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L2636:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_PassBytes, .-MVC_PassBytes
	.align	2
	.global	MVC_GetBytes
	.type	MVC_GetBytes, %function
MVC_GetBytes:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #0
	beq	.L2652
	ldr	r3, [r0, #232]
	cmp	r3, #0
	cmpne	r2, #0
	beq	.L2652
	ldrb	r7, [r3]	@ zero_extendqisi2
	mov	ip, r7, asl #5
	sub	ip, ip, r7, asl #2
	add	ip, r3, ip
	ldr	ip, [ip, #8]
	cmp	ip, #0
	beq	.L2652
	ldr	ip, [r3, #68]
	cmp	r7, #1
	cmpls	ip, #2
	movhi	lr, #1
	movls	lr, #0
	bhi	.L2652
	cmp	ip, r7
	bls	.L2652
.L2647:
	mov	r5, r7, asl #5
	sub	r5, r5, r7, asl #2
	add	r3, r3, r5
	ldr	r4, [r3, #24]
	ldr	r8, [r3, #8]
	add	r4, r4, #7
	ldr	r6, [r3, #12]
	add	ip, r8, r4, lsr #3
	add	r6, r8, r6
	cmp	ip, r6
	bcs	.L2642
	ldrb	r3, [r8, r4, lsr #3]	@ zero_extendqisi2
	add	lr, lr, #1
	cmp	r2, lr
	add	r4, r1, #1
	add	ip, ip, #1
	strb	r3, [r1]
	b	.L2654
.L2645:
	cmp	ip, r6
	mov	r1, r4
	beq	.L2642
	ldrb	r3, [ip], #1	@ zero_extendqisi2
	add	lr, lr, #1
	cmp	r2, lr
	strb	r3, [r4], #1
.L2654:
	ldr	r3, [r0, #232]
	add	r3, r3, r5
	ldr	r1, [r3, #24]
	add	r1, r1, #8
	str	r1, [r3, #24]
	bhi	.L2645
	mov	r0, r2
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2642:
	ldr	ip, [r0, #232]
	add	r7, r7, #1
	ldrb	r3, [ip]	@ zero_extendqisi2
	add	r3, r3, #1
	strb	r3, [ip]
	ldr	r3, [r0, #232]
	ldr	ip, [r3, #68]
	cmp	ip, r7
	bhi	.L2647
	mov	r0, lr
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2652:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_GetBytes, .-MVC_GetBytes
	.align	2
	.global	MVC_DecFramePackingSEI
	.type	MVC_DecFramePackingSEI, %function
MVC_DecFramePackingSEI:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r1, .L2662
	mov	r4, r0
	bl	mvc_ue_v
	add	r6, r4, #11075584
	add	r5, r6, #45056
	ldr	r2, .L2662+4
	mov	r1, #1
	str	r0, [r5, #2672]
	mov	r0, r4
	bl	mvc_u_v
	uxtb	r0, r0
	strb	r0, [r5, #2649]
	cmp	r0, #0
	beq	.L2661
.L2656:
	mov	r0, r4
	ldr	r2, .L2662+8
	mov	r1, #1
	add	r6, r6, #45056
	bl	mvc_u_v
	mov	r3, #1
	strb	r3, [r6, #2648]
	strb	r0, [r6, #2650]
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2661:
	ldr	r2, .L2662+12
	mov	r1, #7
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2662+16
	mov	r1, #1
	str	r0, [r5, #2664]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2662+20
	mov	r1, #6
	strb	r0, [r5, #2651]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2662+24
	mov	r1, #1
	str	r0, [r5, #2668]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2662+28
	mov	r1, #1
	strb	r0, [r5, #2652]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2662+32
	mov	r1, #1
	strb	r0, [r5, #2653]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2662+36
	mov	r1, #1
	strb	r0, [r5, #2654]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2662+40
	mov	r1, #1
	strb	r0, [r5, #2655]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2662+44
	mov	r1, #1
	strb	r0, [r5, #2656]
	mov	r0, r4
	bl	mvc_u_v
	ldrb	r3, [r5, #2651]	@ zero_extendqisi2
	cmp	r3, #0
	strb	r0, [r5, #2657]
	bne	.L2657
	ldr	r3, [r5, #2664]
	cmp	r3, #5
	beq	.L2657
	ldr	r2, .L2662+48
	mov	r1, #1
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2662+52
	mov	r1, #1
	strb	r0, [r5, #2658]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2662+56
	mov	r1, #1
	strb	r0, [r5, #2659]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2662+60
	mov	r1, #1
	strb	r0, [r5, #2660]
	mov	r0, r4
	bl	mvc_u_v
	strb	r0, [r5, #2661]
.L2657:
	ldr	r2, .L2662+64
	mov	r1, #8
	mov	r0, r4
	bl	mvc_u_v
	ldr	r1, .L2662+68
	str	r0, [r5, #2676]
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r5, #2680]
	b	.L2656
.L2663:
	.align	2
.L2662:
	.word	.LC341
	.word	.LC342
	.word	.LC358
	.word	.LC343
	.word	.LC344
	.word	.LC345
	.word	.LC346
	.word	.LC347
	.word	.LC348
	.word	.LC349
	.word	.LC350
	.word	.LC351
	.word	.LC352
	.word	.LC353
	.word	.LC354
	.word	.LC355
	.word	.LC356
	.word	.LC357
	UNWIND(.fnend)
	.size	MVC_DecFramePackingSEI, .-MVC_DecFramePackingSEI
	.align	2
	.global	MVC_DecPicTimingSEI
	.type	MVC_DecPicTimingSEI, %function
MVC_DecPicTimingSEI:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r6, r0, #11075584
	ldr	r3, [r0, #248]
	add	r2, r6, #32768
	movw	r4, #3992
	mov	r5, r0
	ldr	r2, [r2, #2600]
	mla	r4, r4, r2, r3
	ldrb	r2, [r4, #25]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L2665
	ldr	ip, [r0, #36]
	cmp	ip, #0
	ble	.L2666
	ldrb	r2, [r3, #25]	@ zero_extendqisi2
	cmp	r2, #0
	addeq	r3, r3, #3984
	addeq	r3, r3, #8
	beq	.L2669
	b	.L2688
.L2670:
	ldrb	r1, [r3, #-3967]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L2667
.L2669:
	add	r2, r2, #1
	mov	r4, r3
	cmp	r2, ip
	add	r3, r3, #3984
	add	r3, r3, #8
	bne	.L2670
.L2666:
	ldr	r1, .L2690
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r3, #0
.L2671:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2688:
	mov	r4, r3
.L2667:
	cmp	r4, #0
	beq	.L2666
.L2665:
	ldrb	r3, [r4, #24]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2672
	ldrb	r3, [r4, #35]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2689
	ldr	r1, [r4, #388]
	ldr	r8, [r4, #392]
	add	r1, r1, #1
	add	r8, r8, #1
.L2675:
	ldr	r2, .L2690+4
	mov	r0, r5
	bl	mvc_u_v
	add	r7, r6, #45056
	mov	r1, r8
	ldr	r2, .L2690+8
	str	r0, [r7, #2688]
	mov	r0, r5
	bl	mvc_u_v
	str	r0, [r7, #2692]
.L2672:
	ldrb	r0, [r4, #39]	@ zero_extendqisi2
	cmp	r0, #0
	moveq	r3, r0
	beq	.L2671
	mov	r0, r5
	ldr	r2, .L2690+12
	mov	r1, #4
	add	r6, r6, #45056
	bl	mvc_u_v
	mov	r3, #0
	strb	r0, [r6, #2684]
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2689:
	ldrb	r3, [r4, #38]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2672
	ldr	r1, [r4, #700]
	ldr	r8, [r4, #704]
	add	r1, r1, #1
	add	r8, r8, #1
	b	.L2675
.L2691:
	.align	2
.L2690:
	.word	.LC359
	.word	.LC360
	.word	.LC361
	.word	.LC362
	UNWIND(.fnend)
	.size	MVC_DecPicTimingSEI, .-MVC_DecPicTimingSEI
	.align	2
	.global	MVC_DecSEI
	.type	MVC_DecSEI, %function
MVC_DecSEI:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	ldr	r2, [r0, #232]
	sub	r7, fp, #44
	mov	r3, #0
	mov	r1, #32
	mov	r4, r0
	add	r6, r0, #548
	mov	r8, r3
	strb	r3, [r7, #-1]!
	str	r1, [r2, #24]
	b	.L2695
.L2883:
	bl	BsSkip
	cmp	r5, #0
	ble	.L2694
	ldrb	r3, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L2882
.L2695:
	mov	r2, #1
	mov	r1, r7
	mov	r0, r4
	bl	MVC_GetBytes
	ldr	r3, [r4, #572]
	ldr	ip, [r4, #564]
	mov	r1, #8
	add	r3, r3, r1
	ldrb	r2, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, ip, asl #3
	add	r8, r8, r2
	mov	r5, r0
	mov	r0, r6
	bls	.L2883
.L2694:
	ldr	r1, .L2914
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2697
.L2882:
	mov	r3, #0
	str	r3, [fp, #-60]
.L2831:
	mov	r5, #0
	b	.L2701
.L2885:
	bl	BsSkip
	cmp	r9, #0
	ble	.L2699
	ldrb	r3, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L2884
.L2701:
	mov	r2, #1
	mov	r1, r7
	mov	r0, r4
	bl	MVC_GetBytes
	ldr	r3, [r4, #572]
	ldr	ip, [r4, #564]
	mov	r1, #8
	add	r3, r3, r1
	ldrb	r2, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, ip, asl #3
	add	r5, r5, r2
	mov	r9, r0
	mov	r0, r6
	bls	.L2885
.L2699:
	ldr	r1, .L2914+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2884:
	cmp	r5, #409600
	bgt	.L2699
	ldr	r3, [r4, #232]
	ldr	r2, [r3, #68]
	cmp	r2, #2
	ldreq	r2, [r3, #52]
	ldreq	r3, [r3, #24]
	ldrne	r2, [r3, #24]
	addeq	r2, r2, r3
	moveq	r2, r2, lsr #3
	cmp	r8, #45
	ldrls	pc, [pc, r8, asl #2]
	b	.L2704
.L2706:
	.word	.L2705
	.word	.L2707
	.word	.L2708
	.word	.L2709
	.word	.L2710
	.word	.L2711
	.word	.L2712
	.word	.L2713
	.word	.L2714
	.word	.L2715
	.word	.L2716
	.word	.L2717
	.word	.L2718
	.word	.L2719
	.word	.L2720
	.word	.L2721
	.word	.L2722
	.word	.L2723
	.word	.L2724
	.word	.L2725
	.word	.L2726
	.word	.L2727
	.word	.L2704
	.word	.L2704
	.word	.L2704
	.word	.L2704
	.word	.L2704
	.word	.L2704
	.word	.L2704
	.word	.L2704
	.word	.L2704
	.word	.L2704
	.word	.L2704
	.word	.L2704
	.word	.L2704
	.word	.L2704
	.word	.L2704
	.word	.L2704
	.word	.L2704
	.word	.L2704
	.word	.L2704
	.word	.L2704
	.word	.L2704
	.word	.L2704
	.word	.L2704
	.word	.L2728
.L2728:
	mov	r1, r5
	mov	r0, r4
	ldr	r8, [r4, #572]
	bl	MVC_DecFramePackingSEI
	ldr	r2, [r4, #572]
	mov	r9, r5, asl #3
	rsb	r3, r8, r2
	cmp	r3, r9
	bge	.L2817
	rsb	r9, r3, r9
	ldr	r3, [r4, #564]
	cmp	r9, #0
	add	r8, r9, #7
	movge	r8, r9
	mov	r8, r8, asr #3
	cmp	r8, #0
	movle	r3, r3, asl #3
	ble	.L2819
	add	r1, r2, #8
	mov	r3, r3, asl #3
	cmp	r1, r3
	bhi	.L2819
	mov	r10, #0
	b	.L2820
.L2821:
	add	r1, r2, #8
	cmp	r1, r3
	bhi	.L2819
.L2820:
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	add	r10, r10, #1
	ldr	r3, [r4, #564]
	cmp	r10, r8
	ldr	r2, [r4, #572]
	mov	r3, r3, asl #3
	bne	.L2821
.L2819:
	mov	r1, r9, asr #31
	mov	r0, r1, lsr #29
	add	r1, r9, r0
	and	r1, r1, #7
	rsb	r1, r0, r1
	add	r2, r2, r1
	cmp	r3, r2
	bcs	.L2886
.L2817:
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2887
.L2730:
	ldr	r3, [r4, #60]
	cmp	r3, #3
	bhi	.L2888
.L2826:
	mov	r8, #0
	b	.L2830
.L2828:
	bl	BsSkip
	cmp	r5, #0
	ble	.L2829
	ldrb	r3, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L2889
.L2830:
	mov	r2, #1
	mov	r1, r7
	mov	r0, r4
	bl	MVC_GetBytes
	ldr	r3, [r4, #572]
	ldr	ip, [r4, #564]
	mov	r1, #8
	add	r3, r3, r1
	ldrb	r2, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, ip, asl #3
	add	r8, r8, r2
	mov	r5, r0
	mov	r0, r6
	bls	.L2828
.L2829:
	mov	r0, #0
.L2697:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2727:
	mov	r3, r5
	ldr	r1, .L2914+8
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2890
.L2813:
	cmp	r5, #0
	ble	.L2730
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
	mov	r8, #0
	b	.L2814
.L2815:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
.L2814:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2815
	ldr	r3, [r4, #60]
	cmp	r3, #3
	bls	.L2826
.L2888:
	ldr	r1, .L2914+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2726:
	mov	r3, r5
	ldr	r1, .L2914+16
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2891
.L2810:
	cmp	r5, #0
	ble	.L2730
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
	mov	r8, #0
	b	.L2811
.L2812:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
.L2811:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2812
	b	.L2730
.L2725:
	mov	r3, r5
	ldr	r1, .L2914+20
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2892
.L2807:
	cmp	r5, #0
	ble	.L2730
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
	mov	r8, #0
	b	.L2808
.L2809:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
.L2808:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2809
	b	.L2730
.L2723:
	mov	r3, r5
	ldr	r1, .L2914+24
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2893
.L2801:
	cmp	r5, #0
	ble	.L2730
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
	mov	r8, #0
	b	.L2802
.L2803:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
.L2802:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2803
	b	.L2730
.L2724:
	mov	r3, r5
	ldr	r1, .L2914+28
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2894
.L2804:
	cmp	r5, #0
	ble	.L2730
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
	mov	r8, #0
	b	.L2805
.L2806:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
.L2805:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2806
	b	.L2730
.L2722:
	mov	r3, r5
	ldr	r1, .L2914+32
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2895
.L2798:
	cmp	r5, #0
	ble	.L2730
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
	mov	r8, #0
	b	.L2799
.L2800:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
.L2799:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2800
	b	.L2730
.L2721:
	mov	r3, r5
	ldr	r1, .L2914+36
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2896
.L2795:
	cmp	r5, #0
	ble	.L2730
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
	mov	r8, #0
	b	.L2796
.L2797:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
.L2796:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2797
	b	.L2730
.L2713:
	mov	r3, r5
	ldr	r1, .L2914+40
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2897
.L2771:
	cmp	r5, #0
	ble	.L2730
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
	mov	r8, #0
	b	.L2772
.L2773:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
.L2772:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2773
	b	.L2730
.L2717:
	mov	r3, r5
	ldr	r1, .L2914+44
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2898
.L2783:
	cmp	r5, #0
	ble	.L2730
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
	mov	r8, #0
	b	.L2784
.L2785:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
.L2784:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2785
	b	.L2730
.L2708:
	mov	r3, r5
	ldr	r1, .L2914+48
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2899
.L2740:
	cmp	r5, #0
	ble	.L2730
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
	mov	r8, #0
	b	.L2741
.L2742:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
.L2741:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2742
	b	.L2730
.L2719:
	mov	r3, r5
	ldr	r1, .L2914+52
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2900
.L2789:
	cmp	r5, #0
	ble	.L2730
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
	mov	r8, #0
	b	.L2790
.L2791:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
.L2790:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2791
	b	.L2730
.L2711:
	ldr	r3, [fp, #-60]
	cmp	r3, #0
	bne	.L2710
	mov	r3, r5
	ldr	r1, .L2914+56
	mov	r0, #20
	bl	dprint_vfmw
.L2747:
	ldr	r0, [r4, #120]
	ldr	r8, [r4, #60]
	bl	GetUsd
	add	r8, r8, #132
	str	r0, [r4, r8, asl #2]
	ldr	r3, [r4, #60]
	add	r3, r3, #132
	ldr	r1, [r4, r3, asl #2]
	cmp	r1, #0
	beq	.L2834
	ldr	r2, [r4, #232]
	cmp	r5, #1024
	movlt	r10, r5
	movge	r10, #1024
	ldrb	r0, [r2]	@ zero_extendqisi2
	ldr	ip, [r2, #68]
	cmp	r0, ip
	bcs	.L2835
	sxth	r3, r0
	mov	r8, #0
	mov	lr, r3, asl #5
	sub	r3, lr, r3, asl #2
	add	r2, r2, r3
.L2749:
	ldr	r3, [r2, #24]
	add	r0, r0, #1
	ldr	lr, [r2, #12]
	cmp	r0, ip
	add	r3, r3, #7
	add	r2, r2, #28
	sub	r3, lr, r3, lsr #3
	add	r8, r8, r3
	bne	.L2749
	mov	r3, r8
.L2748:
	cmp	r3, r10
	ldrsb	r9, [fp, #-60]
	movge	r8, r10
	cmp	r9, #1
	movne	r3, #0
	strne	r3, [fp, #-56]
	beq	.L2901
.L2751:
	rsb	r2, r3, r8
	mov	r0, r4
	bl	MVC_GetBytes
	subs	r8, r0, #0
	ble	.L2902
	ldr	r3, [fp, #-56]
	rsb	r3, r3, r10
	cmp	r8, r3
	ldr	r3, [r4, #60]
	blt	.L2903
	add	r3, r3, #132
	ldr	r2, [fp, #-56]
	cmp	r10, r5
	ldr	r3, [r4, r3, asl #2]
	rsb	r8, r2, r5
	str	r8, [r3, #1052]
	bcc	.L2904
.L2762:
	cmp	r8, #0
	ble	.L2757
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2757
	mov	r5, #0
	b	.L2764
.L2765:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2757
.L2764:
	add	r5, r5, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2765
.L2757:
	ldr	r3, [r4, #60]
	cmp	r9, #1
	ldr	r1, [r4, #224]
	add	r3, r3, #132
	moveq	r2, #8
	movne	r2, #9
.L2880:
	ldr	r3, [r4, r3, asl #2]
	ldrd	r0, [r1, #56]
	ldr	ip, .L2914+60
	add	r3, r3, #1056
	ldr	ip, [ip]
	strd	r0, [r3]
	ldr	r3, [r4, #60]
	cmp	ip, #0
	add	r3, r3, #132
	ldr	r3, [r4, r3, asl #2]
	str	r2, [r3, #1040]
	ldr	r3, [r4, #60]
	ldr	r2, [r4, #84]
	add	r3, r3, #132
	ldr	r3, [r4, r3, asl #2]
	str	r2, [r3, #1044]
	beq	.L2730
	ldr	r2, [r4, #60]
	movw	r3, #1064
	mov	r1, #6
	ldr	r0, [r4, #120]
	add	r2, r2, #132
	ldr	r2, [r4, r2, asl #2]
	blx	ip
	b	.L2730
.L2715:
	mov	r3, r5
	ldr	r1, .L2914+64
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2905
.L2777:
	cmp	r5, #0
	ble	.L2730
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
	mov	r8, #0
	b	.L2778
.L2779:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
.L2778:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2779
	b	.L2730
.L2714:
	mov	r3, r5
	ldr	r1, .L2914+68
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2906
.L2774:
	cmp	r5, #0
	ble	.L2730
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
	mov	r8, #0
	b	.L2775
.L2776:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
.L2775:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2776
	b	.L2730
.L2716:
	mov	r3, r5
	ldr	r1, .L2914+72
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2907
.L2780:
	cmp	r5, #0
	ble	.L2730
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
	mov	r8, #0
	b	.L2781
.L2782:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
.L2781:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2782
	b	.L2730
.L2705:
	mov	r3, r5
	ldr	r1, .L2914+76
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2908
.L2729:
	cmp	r5, #0
	ble	.L2730
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
	mov	r8, #0
	b	.L2731
.L2732:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
.L2731:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2732
	b	.L2730
.L2720:
	mov	r3, r5
	ldr	r1, .L2914+80
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2909
.L2792:
	cmp	r5, #0
	ble	.L2730
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
	mov	r8, #0
	b	.L2793
.L2794:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
.L2793:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2794
	b	.L2730
.L2712:
	mov	r3, r5
	ldr	r1, .L2914+84
	mov	r0, #20
	bl	dprint_vfmw
	cmp	r5, #0
	ble	.L2768
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2768
	mov	r8, #0
	b	.L2769
.L2770:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2768
.L2769:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2770
.L2768:
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	bge	.L2730
	movw	r3, #12344
	ldr	r2, .L2914+112
	ldr	r1, .L2914+116
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2730
.L2718:
	mov	r3, r5
	ldr	r1, .L2914+88
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2910
.L2786:
	cmp	r5, #0
	ble	.L2730
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
	mov	r8, #0
	b	.L2787
.L2788:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
.L2787:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2788
	b	.L2730
.L2707:
	mov	r3, r5
	ldr	r1, .L2914+92
	mov	r0, #20
	mov	r9, r5, asl #3
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	ldr	r8, [r4, #572]
	bl	MVC_DecPicTimingSEI
	ldr	r2, [r4, #572]
	rsb	r3, r8, r2
	cmp	r3, r9
	bge	.L2734
	rsb	r9, r3, r9
	ldr	r3, [r4, #564]
	cmp	r9, #0
	add	r8, r9, #7
	movge	r8, r9
	mov	r8, r8, asr #3
	cmp	r8, #0
	movle	r3, r3, asl #3
	ble	.L2736
	add	r1, r2, #8
	mov	r3, r3, asl #3
	cmp	r1, r3
	bhi	.L2736
	mov	r10, #0
	b	.L2737
.L2738:
	add	r1, r2, #8
	cmp	r1, r3
	bhi	.L2736
.L2737:
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	add	r10, r10, #1
	ldr	r3, [r4, #564]
	cmp	r10, r8
	ldr	r2, [r4, #572]
	mov	r3, r3, asl #3
	bne	.L2738
.L2736:
	mov	r1, r9, asr #31
	mov	r0, r1, lsr #29
	add	r1, r9, r0
	and	r1, r1, #7
	rsb	r1, r0, r1
	add	r2, r2, r1
	cmp	r3, r2
	bcs	.L2911
.L2734:
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	bge	.L2730
	movw	r3, #12125
	ldr	r2, .L2914+112
	ldr	r1, .L2914+116
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2730
.L2709:
	mov	r3, r5
	ldr	r1, .L2914+96
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2912
.L2743:
	cmp	r5, #0
	ble	.L2730
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
	mov	r8, #0
	b	.L2744
.L2745:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
.L2744:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2745
	b	.L2730
.L2704:
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2913
.L2823:
	cmp	r5, #0
	ble	.L2730
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
	mov	r8, #0
	b	.L2824
.L2825:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2730
.L2824:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2825
	b	.L2730
.L2889:
	cmp	r3, #128
	bne	.L2831
	b	.L2829
.L2710:
	mov	r3, r5
	ldr	r1, .L2914+100
	mov	r0, #20
	bl	dprint_vfmw
	mov	r3, #1
	str	r3, [fp, #-60]
	b	.L2747
.L2903:
	add	r3, r3, #132
	ldr	r3, [r4, r3, asl #2]
	str	r8, [r3, #1052]
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2757
	mov	r5, #0
	b	.L2758
.L2760:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2757
.L2758:
	add	r5, r5, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2760
	b	.L2757
.L2915:
	.align	2
.L2914:
	.word	.LC363
	.word	.LC364
	.word	.LC391
	.word	.LC392
	.word	.LC390
	.word	.LC389
	.word	.LC387
	.word	.LC388
	.word	.LC386
	.word	.LC385
	.word	.LC377
	.word	.LC381
	.word	.LC368
	.word	.LC383
	.word	.LC371
	.word	g_event_report
	.word	.LC379
	.word	.LC378
	.word	.LC380
	.word	.LC365
	.word	.LC384
	.word	.LC376
	.word	.LC382
	.word	.LC367
	.word	.LC369
	.word	.LC370
	.word	.LC372
	.word	.LC374
	.word	.LANCHOR0+236
	.word	.LC366
	.word	.LC373
	.word	.LC375
.L2901:
	strb	r9, [r1, #1026]
	mov	r0, r4
	ldr	r3, [r4, #60]
	mov	r1, #8
	ldr	r2, .L2914+104
	add	r3, r3, #132
	ldr	r3, [r4, r3, asl #2]
	str	r3, [fp, #-56]
	bl	mvc_u_v
	ldr	r3, [fp, #-56]
	strb	r0, [r3, #1027]
	ldr	r3, [r4, #60]
	add	r3, r3, #132
	ldr	ip, [r4, r3, asl #2]
	ldrb	r3, [ip, #1027]	@ zero_extendqisi2
	cmp	r3, #255
	beq	.L2752
	mov	r3, #3
	mov	r2, #0
	str	r3, [fp, #-56]
	strb	r2, [ip, #1028]
.L2753:
	ldr	ip, [r4, #60]
	mov	r1, #16
	ldr	r2, .L2914+108
	mov	r0, r4
	add	ip, ip, #132
	str	r3, [fp, #-64]
	ldr	ip, [r4, ip, asl #2]
	str	ip, [fp, #-68]
	bl	mvc_u_v
	ldr	ip, [fp, #-68]
	ldr	r3, [fp, #-64]
	add	ip, ip, #1024
	mov	r1, r3
	strh	r0, [ip, #6]	@ movhi
	mov	r0, r4
	bl	MVC_PassBytes
	ldr	r3, [fp, #-64]
	cmp	r8, r3
	beq	.L2754
	ldr	r2, [r4, #60]
	add	r2, r2, #132
	ldr	r1, [r4, r2, asl #2]
	b	.L2751
.L2896:
	movw	r3, #12564
	ldr	r2, .L2914+112
	ldr	r1, .L2914+116
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2795
.L2897:
	movw	r3, #12356
	ldr	r2, .L2914+112
	ldr	r1, .L2914+116
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2771
.L2898:
	movw	r3, #12460
	ldr	r2, .L2914+112
	ldr	r1, .L2914+116
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2783
.L2899:
	movw	r3, #12137
	ldr	r2, .L2914+112
	ldr	r1, .L2914+116
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2740
.L2900:
	movw	r3, #12512
	ldr	r2, .L2914+112
	ldr	r1, .L2914+116
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2789
.L2892:
	movw	r3, #12668
	ldr	r2, .L2914+112
	ldr	r1, .L2914+116
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2807
.L2893:
	movw	r3, #12616
	ldr	r2, .L2914+112
	ldr	r1, .L2914+116
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2801
.L2894:
	movw	r3, #12642
	ldr	r2, .L2914+112
	ldr	r1, .L2914+116
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2804
.L2895:
	movw	r3, #12590
	ldr	r2, .L2914+112
	ldr	r1, .L2914+116
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2798
.L2890:
	movw	r3, #12720
	ldr	r2, .L2914+112
	ldr	r1, .L2914+116
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2813
.L2891:
	movw	r3, #12694
	ldr	r2, .L2914+112
	ldr	r1, .L2914+116
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2810
.L2906:
	movw	r3, #12382
	ldr	r2, .L2914+112
	ldr	r1, .L2914+116
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2774
.L2907:
	movw	r3, #12434
	ldr	r2, .L2914+112
	ldr	r1, .L2914+116
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2780
.L2908:
	movw	r3, #12072
	ldr	r2, .L2914+112
	ldr	r1, .L2914+116
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2729
.L2909:
	movw	r3, #12538
	ldr	r2, .L2914+112
	ldr	r1, .L2914+116
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2792
.L2905:
	movw	r3, #12408
	ldr	r2, .L2914+112
	ldr	r1, .L2914+116
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2777
.L2910:
	movw	r3, #12486
	ldr	r2, .L2914+112
	ldr	r1, .L2914+116
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2786
.L2912:
	movw	r3, #12163
	ldr	r2, .L2914+112
	ldr	r1, .L2914+116
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2743
.L2887:
	movw	r3, #12772
	ldr	r2, .L2914+112
	ldr	r1, .L2914+116
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2730
.L2913:
	movw	r3, #12784
	ldr	r2, .L2914+112
	ldr	r1, .L2914+116
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2823
.L2911:
	mov	r0, r6
	bl	BsSkip
	b	.L2734
.L2886:
	mov	r0, r6
	bl	BsSkip
	b	.L2817
.L2904:
	rsb	r1, r10, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	bge	.L2762
	movw	r3, #12295
	ldr	r2, .L2914+112
	ldr	r1, .L2914+116
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2762
.L2835:
	mov	r3, #0
	mov	r8, r3
	b	.L2748
.L2754:
	ldr	r3, [r4, #60]
	mov	r2, #8
	ldr	r1, [r4, #224]
	add	r3, r3, #132
	b	.L2880
.L2752:
	ldr	r2, .L2914+120
	mov	r1, #8
	mov	r0, r4
	mov	r3, #4
	str	ip, [fp, #-64]
	str	r3, [fp, #-56]
	bl	mvc_u_v
	ldr	ip, [fp, #-64]
	ldr	r3, [fp, #-56]
	strb	r0, [ip, #1028]
	b	.L2753
.L2902:
	ldr	r1, .L2914+124
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r4, #60]
	ldr	r0, [r4, #120]
	add	r3, r3, #132
	ldr	r1, [r4, r3, asl #2]
	bl	FreeUsdByDec
	ldr	r3, [r4, #60]
	mov	r2, #0
	mvn	r0, #0
	add	r3, r3, #132
	str	r2, [r4, r3, asl #2]
	b	.L2697
.L2834:
	mvn	r0, #0
	b	.L2697
	UNWIND(.fnend)
	.size	MVC_DecSEI, .-MVC_DecSEI
	.align	2
	.global	MVC_InitOldSlice
	.type	MVC_InitOldSlice, %function
MVC_InitOldSlice:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r1, [r0, #40]
	add	r3, r0, #11075584
	add	r3, r3, #40960
	movw	r2, #23352
	movt	r2, 1
	mov	r0, #2
	str	r1, [r3, #2700]
	mov	r1, #7
	str	r2, [r3, #2704]
	mov	r2, #32
	strb	r1, [r3, #2691]
	mov	r1, #3
	strb	r2, [r3, #2690]
	mvn	r2, #0
	str	r1, [r3, #2712]
	mov	r1, #262144
	str	r2, [r3, #2716]
	mov	r2, #0
	strb	r0, [r3, #2689]
	str	r1, [r3, #2728]
	strb	r2, [r3, #2688]
	str	r2, [r3, #2720]
	str	r2, [r3, #2724]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_InitOldSlice, .-MVC_InitOldSlice
	.align	2
	.global	MVC_IsNewPicNal
	.type	MVC_IsNewPicNal, %function
MVC_IsNewPicNal:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	mov	r5, r0
	and	r3, r3, #31
	sub	r3, r3, #1
	cmp	r3, #7
	ldrls	pc, [pc, r3, asl #2]
	b	.L2925
.L2920:
	.word	.L2919
	.word	.L2925
	.word	.L2925
	.word	.L2925
	.word	.L2919
	.word	.L2925
	.word	.L2921
	.word	.L2921
.L2921:
	ldr	r3, [r0]
	mov	r2, #1
	str	r2, [r0]
	adds	r3, r3, #0
	movne	r3, #1
	rsb	r0, r3, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2919:
	ldr	r3, [r0]
	cmp	r3, #0
	beq	.L2922
.L2924:
	mvn	r0, #0
.L2923:
	mov	r2, #0
	str	r2, [r5]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2925:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2922:
	ldrb	ip, [r1, #5]	@ zero_extendqisi2
	ldrb	r3, [r1, #6]	@ zero_extendqisi2
	ldrb	r2, [r1, #7]	@ zero_extendqisi2
	mov	ip, ip, asl #16
	ldrb	r4, [r1, #4]	@ zero_extendqisi2
	orr	r3, ip, r3, asl #8
	orr	r3, r3, r2
	orr	r4, r3, r4, asl #24
	mov	r0, r4
	bl	ZerosMS_32
	cmp	r0, #15
	bhi	.L2924
	mov	r3, r0, asl #1
	rsb	r3, r3, #31
	mov	r3, r4, lsr r3
	subs	r0, r3, #1
	mvnne	r0, #0
	b	.L2923
	UNWIND(.fnend)
	.size	MVC_IsNewPicNal, .-MVC_IsNewPicNal
	.align	2
	.global	MVC_FindZeroBitsInSeg
	.type	MVC_FindZeroBitsInSeg, %function
MVC_FindZeroBitsInSeg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	cmp	r0, #0
	cmpne	r1, #0
	mov	r9, r0
	str	r1, [fp, #-48]
	movle	r4, #1
	movgt	r4, #0
	ble	.L2952
	ldr	r3, [fp, #-48]
	subs	r7, r3, #0
	add	r8, r3, #63
	movge	r8, r3
	ands	r3, r3, #63
	movne	r3, #1
	add	r8, r3, r8, asr #6
	cmp	r8, #0
	ble	.L2940
	ldr	r5, .L2953
	ldr	r10, .L2953+4
.L2938:
	cmp	r7, #64
	ldr	r3, [r10, #52]
	ldr	r0, .L2953
	movcc	r6, r7
	movcs	r6, #64
	mov	r2, r6
	rsb	r1, r6, r7
	sub	r6, r6, #1
	add	r1, r9, r1
	blx	r3
	add	r3, r5, r6
	ldrb	r2, [r5, r6]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L2930
	ldr	r2, .L2953
	add	r4, r4, #1
	cmp	r3, r2
	bne	.L2933
	b	.L2931
.L2934:
	cmp	r3, r5
	add	r4, r4, #1
	beq	.L2931
.L2933:
	ldrb	r2, [r3, #-1]!	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2934
.L2930:
	mov	r0, r4, asl #3
.L2929:
	ldr	r3, [fp, #-48]
	cmp	r4, r3
	bge	.L2942
	sub	r3, r3, #1
	rsb	r4, r4, r3
	ldrb	r2, [r9, r4]	@ zero_extendqisi2
	tst	r2, #1
	moveq	r2, r2, lsr #1
	moveq	r3, #1
	bne	.L2942
.L2937:
	tst	r2, #1
	mov	r2, r2, lsr #1
	bne	.L2935
	add	r3, r3, #1
	cmp	r3, #8
	bne	.L2937
	b	.L2935
.L2931:
	subs	r8, r8, #1
	sub	r7, r7, #64
	bne	.L2938
	b	.L2930
.L2942:
	mov	r3, #0
.L2935:
	add	r0, r3, r0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2952:
	mov	r2, r1
	mov	r0, #0
	ldr	r1, .L2953+8
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2940:
	mov	r0, r4
	b	.L2929
.L2954:
	.align	2
.L2953:
	.word	.LANCHOR3-1952
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC393
	UNWIND(.fnend)
	.size	MVC_FindZeroBitsInSeg, .-MVC_FindZeroBitsInSeg
	.align	2
	.global	MVC_FindTrailZeros
	.type	MVC_FindTrailZeros, %function
MVC_FindTrailZeros:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r4, r0, #0
	beq	.L2961
	ldr	r3, [r4, #232]
	ldr	r2, [r3, #68]
	cmp	r2, #1
	bls	.L2960
	ldr	r1, [r3, #40]
	ldr	r0, [r3, #36]
	bl	MVC_FindZeroBitsInSeg
	ldr	r3, [r4, #232]
	ldr	r2, [r3, #40]
	cmp	r0, r2, asl #3
	bcs	.L2964
	cmn	r0, #1
	beq	.L2960
.L2959:
	add	r0, r0, #1
	str	r0, [r3, #72]
	ldr	r3, [r4, #232]
	ldr	r2, [r3, #68]
	cmp	r2, #1
	bls	.L2963
	ldr	r1, [r3, #40]
	ldr	r2, [r3, #72]
	cmp	r2, r1, asl #3
	bcs	.L2965
.L2963:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2965:
	ldr	r1, [r3, #60]
	ldr	r0, [r4, #120]
	bl	SM_ReleaseStreamSeg
	ldr	r2, [r4, #232]
	mov	r3, #0
	mov	r1, #1
	mov	r0, r3
	str	r3, [r2, #36]
	ldr	r2, [r4, #232]
	str	r1, [r2, #68]
	ldr	r2, [r4, #232]
	str	r3, [r2, #72]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2964:
	ldr	r1, [r3, #60]
	ldr	r0, [r4, #120]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #232]
	mov	r1, #0
	mov	r2, #1
	str	r1, [r3, #36]
	ldr	r3, [r4, #232]
	str	r2, [r3, #68]
	ldr	r3, [r4, #232]
.L2960:
	ldr	r1, [r3, #12]
	ldr	r0, [r3, #8]
	bl	MVC_FindZeroBitsInSeg
	ldr	r3, [r4, #232]
	b	.L2959
.L2961:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_FindTrailZeros, .-MVC_FindTrailZeros
	.align	2
	.global	MVC_CombinePacket
	.type	MVC_CombinePacket, %function
MVC_CombinePacket:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #232]
	ldr	r3, [r3, #12]
	cmp	r3, #4096
	ldmcsfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MVC_CombinePacket.part.13
	UNWIND(.fnend)
	.size	MVC_CombinePacket, .-MVC_CombinePacket
	.align	2
	.global	MVC_FindNaluArraySlot
	.type	MVC_FindNaluArraySlot, %function
MVC_FindNaluArraySlot:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldrb	r2, [r0, #937]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2973
	mov	r2, r0
	mov	r3, #1
	b	.L2971
.L2970:
	add	r3, r3, #1
	cmp	r3, #137
	beq	.L2976
.L2971:
	ldrb	r1, [r2, #1025]	@ zero_extendqisi2
	add	r2, r2, #88
	cmp	r1, #0
	bne	.L2970
	mov	r2, r3
.L2969:
	mov	ip, #88
	mov	r1, #1
	mla	r3, ip, r3, r0
	mov	r0, r2
	strb	r1, [r3, #937]
	ldmfd	sp, {fp, sp, pc}
.L2976:
	mvn	r2, #0
	mov	r0, r2
	ldmfd	sp, {fp, sp, pc}
.L2973:
	mov	r3, r2
	b	.L2969
	UNWIND(.fnend)
	.size	MVC_FindNaluArraySlot, .-MVC_FindNaluArraySlot
	.align	2
	.global	MVC_InquireSliceProperty
	.type	MVC_InquireSliceProperty, %function
MVC_InquireSliceProperty:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #68]
	mov	r4, r0
	mov	r9, r1
	mov	r7, r2
	ldr	r1, .L3020
	sub	r2, r3, #1
	mov	r0, #22
	add	r6, r4, #11075584
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r7]
	add	r5, r6, #40960
	str	r3, [r9]
	add	r1, r4, #12288
	ldr	r2, [r4, #232]
	mvn	ip, #0
	ldrb	r0, [r2, #2]	@ zero_extendqisi2
	strb	r0, [r5, #1035]
	ldrb	lr, [r2, #4]	@ zero_extendqisi2
	strb	lr, [r5, #1040]
	ldrb	r2, [r2, #5]	@ zero_extendqisi2
	strb	r3, [r5, #1043]
	str	ip, [r5, #2672]
	strb	r2, [r5, #1044]
	ldrb	r3, [r1, #704]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3013
	cmp	r2, #255
	beq	.L3014
.L2979:
	mov	r0, r4
	bl	MVC_SliceCheck
	subs	r8, r0, #0
	bne	.L2995
	mov	r0, r4
	bl	MVC_ProcessSliceHeaderFirstPart
	cmp	r0, #0
	bne	.L3015
	ldrb	r3, [r5, #1037]	@ zero_extendqisi2
	mov	ip, #2240
	sub	r3, r3, #1
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r9]
	ldrb	r1, [r5, #1044]	@ zero_extendqisi2
	ldr	r3, [r5, #1048]
	ldr	r0, [r4, #252]
	sxtb	r2, r1
	cmn	r2, #1
	mla	r3, ip, r3, r0
	beq	.L3016
	cmp	r1, #0
	bne	.L2991
	ldrb	r2, [r4, #2]	@ zero_extendqisi2
	ldr	r3, [r3, #28]
	cmp	r2, #1
	beq	.L3017
	ldr	r2, [r4, #28]
	cmp	r2, r3
	movweq	r3, #35364
	movteq	r3, 168
	addeq	r3, r4, r3
	bne	.L3018
.L2990:
	ldrb	r2, [r3, #20]	@ zero_extendqisi2
	add	r6, r6, #45056
	ldr	r0, [r3, #3952]
	rsb	r1, r2, #2
	ldr	r2, [r3, #3948]
	ldr	ip, [r4, #16]
	mla	r1, r0, r1, r1
	ldr	r0, [r4, #12]
	add	r2, r2, #1
	cmp	r0, r2
	cmpeq	ip, r1
	movne	r2, #1
	strne	r2, [r7]
	ldr	r2, [r3, #3972]
	ldr	r3, [r6, #2888]
	add	r3, r3, #1
	cmp	r2, r3
	movhi	r3, #1
	strhi	r3, [r7]
.L2987:
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3013:
	strb	r3, [r5, #1043]
	ldr	r3, [r1, #712]
	str	r3, [r5, #2672]
	ldrb	r3, [r1, #708]	@ zero_extendqisi2
	strb	r3, [r5, #1041]
	ldrb	r3, [r1, #709]	@ zero_extendqisi2
	strb	r3, [r5, #1042]
	b	.L2979
.L3016:
	ldr	r3, [r3, #28]
	movw	r1, #3992
	ldr	r2, [r4, #248]
	mla	r3, r1, r3, r2
	b	.L2990
.L3014:
	ldr	r3, [r4, #20]
	cmp	r3, #0
	beq	.L2979
	add	r3, r4, #10747904
	add	r3, r3, #20480
	ldr	r2, [r3, #2384]
	cmp	r2, #0
	bne	.L2982
	ldrb	r2, [r3, #2380]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L2982
	add	r3, r4, #12992
	add	r3, r3, #16
.L2985:
	ldr	r1, [r3]
	cmp	r1, #0
	beq	.L2983
	ldrb	r1, [r3, #-4]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L3019
.L2983:
	add	r2, r2, #1
	add	r3, r3, #335872
	cmp	r2, #32
	add	r3, r3, #308
	bne	.L2985
	mvn	r3, #0
	b	.L3012
.L3017:
	movw	r2, #8500
	movt	r2, 5
	mla	r3, r2, r3, r4
	add	r3, r3, #286720
	add	r3, r3, #932
	b	.L2990
.L2982:
	ldr	r3, [r3, #2388]
.L3012:
	cmn	r3, #1
	str	r3, [r5, #2672]
	beq	.L2979
	sub	r0, r0, #5
	mov	r3, #1
	clz	r0, r0
	strb	r3, [r5, #1043]
	strb	r3, [r5, #1042]
	mov	r0, r0, lsr #5
	strb	r0, [r5, #1041]
	b	.L2979
.L2995:
	mvn	r8, #0
	b	.L2987
.L3018:
	ldr	r1, .L3020+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L2987
.L3015:
	ldr	r1, .L3020+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L2987
.L2991:
	ldr	r1, .L3020+12
	mov	r0, #1
	mvn	r8, #0
	bl	dprint_vfmw
	b	.L2987
.L3019:
	movw	r3, #8500
	movt	r3, 5
	mla	r3, r3, r2, r4
	add	r3, r3, #12992
	add	r3, r3, #16
	ldr	r3, [r3, #4]
	b	.L3012
.L3021:
	.align	2
.L3020:
	.word	.LC394
	.word	.LC31
	.word	.LC395
	.word	.LC396
	UNWIND(.fnend)
	.size	MVC_InquireSliceProperty, .-MVC_InquireSliceProperty
	.align	2
	.global	MVC_HaveSliceToDec
	.type	MVC_HaveSliceToDec, %function
MVC_HaveSliceToDec:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r0, [r0, #64]
	clz	r0, r0
	mov	r0, r0, lsr #5
	rsb	r0, r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_HaveSliceToDec, .-MVC_HaveSliceToDec
	.align	2
	.global	MVC_IsRefListWrong
	.type	MVC_IsRefListWrong, %function
MVC_IsRefListWrong:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r0, #11075584
	mov	r7, r0
	add	r5, r5, #40960
	ldr	r3, [r5, #1080]
	cmp	r3, #0
	beq	.L3024
	add	r6, r0, #252
	mov	r4, #0
	b	.L3028
.L3025:
	ldr	r3, [r0, #28]
	cmp	r3, #0
	beq	.L3027
	ldr	r3, [r5, #1080]
	cmp	r4, r3
	bcs	.L3050
.L3028:
	ldr	r3, [r6, #4]!
	add	r4, r4, #1
	ldr	r0, [r7, #120]
	ldr	r3, [r3, #4]
	ldrsb	r1, [r3, #6]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	bne	.L3025
.L3027:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3050:
	cmp	r3, #0
	beq	.L3024
	ldr	r3, [r5, #1084]
	cmp	r3, #0
	addne	r6, r7, #384
	movne	r4, #0
	bne	.L3031
	b	.L3024
.L3051:
	ldr	r3, [r0, #28]
	cmp	r3, #0
	beq	.L3027
	ldr	r3, [r5, #1084]
	cmp	r4, r3
	bcs	.L3024
.L3031:
	ldr	r3, [r6, #4]!
	add	r4, r4, #1
	ldr	r0, [r7, #120]
	ldr	r3, [r3, #4]
	ldrsb	r1, [r3, #6]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	bne	.L3051
	b	.L3027
.L3024:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_IsRefListWrong, .-MVC_IsRefListWrong
	.align	2
	.global	MVC_DEC_Destroy
	.type	MVC_DEC_Destroy, %function
MVC_DEC_Destroy:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r5, r0
	bl	MVC_ClearCurrPic
	mov	r0, r5
	bl	MVC_ClearAllNal
	ldr	r3, [r5, #60]
	cmp	r3, #0
	beq	.L3053
	mov	r4, #0
	add	r6, r5, #524
	mov	r7, r4
.L3055:
	ldr	r1, [r6, #4]!
	add	r4, r4, #1
	cmp	r1, #0
	beq	.L3054
	ldr	r0, [r5, #120]
	bl	FreeUsdByDec
	str	r7, [r6]
.L3054:
	ldr	r3, [r5, #60]
	cmp	r3, r4
	bhi	.L3055
.L3053:
	movw	r9, #48952
	movw	r8, #16056
	movt	r9, 169
	movt	r8, 170
	add	r9, r5, r9
	add	r8, r5, r8
	mov	r6, #0
	mov	r7, #0
.L3059:
	sub	r4, r9, #32
.L3057:
	ldrd	r2, [r4, #8]!
	orrs	r1, r2, r3
	bne	.L3071
.L3056:
	cmp	r4, r9
	bne	.L3057
	add	r9, r4, #816
	cmp	r9, r8
	bne	.L3059
	ldr	r1, .L3072
	mov	r0, #2
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L3071:
	mov	r1, r2
	ldr	r0, [r5, #120]
	bl	FreeUsdByDec
	strd	r6, [r4]
	b	.L3056
.L3073:
	.align	2
.L3072:
	.word	.LC397
	UNWIND(.fnend)
	.size	MVC_DEC_Destroy, .-MVC_DEC_Destroy
	.align	2
	.global	MVC_DEC_RecycleImage
	.type	MVC_DEC_RecycleImage, %function
MVC_DEC_RecycleImage:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r5, r0
	mov	r8, r1
	mov	r0, #2
	ldr	r1, .L3085
	bl	dprint_vfmw
	mov	r1, r8
	ldr	r0, [r5, #120]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L3079
	ldrsb	r3, [r0, #1]
	cmp	r3, #0
	beq	.L3079
	add	r4, r0, #576
	add	r9, r0, #608
	mov	r6, #0
	mov	r7, #0
.L3077:
	ldrd	r2, [r4, #8]!
	orrs	r1, r2, r3
	bne	.L3084
.L3076:
	cmp	r4, r9
	bne	.L3077
	ldr	r0, [r5, #120]
	mov	r1, r8
	mov	r2, #0
	bl	FSP_SetDisplay
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3084:
	mov	r1, r2
	ldr	r0, [r5, #120]
	bl	FreeUsdByDec
	strd	r6, [r4]
	b	.L3076
.L3079:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3086:
	.align	2
.L3085:
	.word	.LC398
	UNWIND(.fnend)
	.size	MVC_DEC_RecycleImage, .-MVC_DEC_RecycleImage
	.align	2
	.global	MVC_OutputFrmToVO
	.type	MVC_OutputFrmToVO, %function
MVC_OutputFrmToVO:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	clz	r5, r1
	mov	r7, r2
	mov	r6, r1
	mov	r5, r5, lsr #5
	mov	r4, r0
	cmp	r0, #0
	movne	ip, r5
	orreq	ip, r5, #1
	cmp	ip, #0
	bne	.L3124
	ldr	r3, [r0, #224]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	beq	.L3090
	ldrb	r3, [r0, #8]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L3090
	ldr	r3, [r0, #520]
	cmp	r3, #0
	strneb	ip, [r3, #2]
	movne	r0, #1
	strne	ip, [r4, #520]
	beq	.L3092
.L3123:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L3090:
	mov	r1, r6
	mov	r0, r4
	bl	MVC_CheckFrameStore
	cmn	r0, #3
	beq	.L3092
	ldr	r1, [r4, #520]
	cmp	r1, #0
	beq	.L3094
	mov	r0, r4
	bl	MVC_GetImagePara
	ldr	r1, [r4, #520]
	mov	r0, r4
	bl	MVC_CheckFrameStore
	subs	r8, r0, #0
	beq	.L3125
	cmn	r8, #3
	beq	.L3102
	mov	r3, r8
	movw	r2, #1879
	ldr	r1, .L3133
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r4, #520]
	mov	r0, r4
	sub	r8, r8, #1
	clz	r8, r8
	ldr	r1, [r3, #220]
	bl	MVC_DEC_RecycleImage
	mov	r8, r8, lsr #5
.L3101:
	ldr	r3, [r4, #520]
	tst	r8, r5
	mov	r0, #0
	strb	r0, [r3, #2]
	str	r0, [r4, #520]
	bne	.L3123
.L3094:
	mov	r1, r6
	mov	r0, r4
	bl	MVC_GetImagePara
	mov	r1, r6
	mov	r0, r4
	bl	MVC_CheckFrameStore
	subs	r3, r0, #0
	beq	.L3126
	movw	r2, #1928
	ldr	r1, .L3133
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r6, #220]
	mov	r0, r4
	bl	MVC_DEC_RecycleImage
	mov	r0, #2
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L3124:
	mov	r3, r1
	mov	r2, r0
	ldr	r1, .L3133+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #2
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L3126:
	mov	r2, #1
	ldrsb	r1, [r6, #6]
	ldr	r0, [r4, #120]
	bl	FSP_SetDisplay
	ldrsb	r1, [r6, #6]
	ldr	r0, [r4, #120]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L3127
	cmp	r7, #1
	add	r3, r4, #584
	streq	r7, [r5, #180]
	mov	r2, r4
	ldr	r0, [r4, #120]
	mov	r1, #15
	str	r5, [sp]
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L3128
	ldr	r3, [r4, #224]
	ldr	r3, [r3, #612]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r5, #16]
	bcs	.L3129
.L3109:
	ldr	r2, [r4, #144]
	mov	r0, #0
	ldr	r3, [r4, #136]
	add	r2, r2, #1
	str	r2, [r4, #144]
	add	r3, r3, #2
	str	r3, [r4, #136]
	b	.L3123
.L3092:
	mov	r0, #1
	b	.L3123
.L3102:
	ldr	r2, [r4, #520]
	mov	r3, #0
	strb	r3, [r2, #2]
	str	r3, [r4, #520]
	b	.L3094
.L3125:
	ldr	r3, [r4, #520]
	mov	r2, #1
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetDisplay
	ldr	r3, [r4, #520]
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L3130
	ldr	r3, [r4, #520]
	mov	r2, r4
	mov	r1, #15
	cmp	r6, r3
	cmpeq	r7, #1
	moveq	r3, #1
	streq	r3, [r8, #180]
	add	r3, r4, #584
	ldr	r0, [r4, #120]
	str	r8, [sp]
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L3131
	ldr	r3, [r4, #224]
	ldr	r3, [r3, #612]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r8, #16]
	bcs	.L3132
.L3100:
	ldr	r2, [r4, #144]
	mov	r8, #1
	ldr	r3, [r4, #136]
	add	r2, r2, r8
	str	r2, [r4, #144]
	add	r3, r3, #2
	str	r3, [r4, #136]
	b	.L3101
.L3129:
	mov	r1, r5
	mov	r0, r4
	bl	MVC_SetFrmRepeatCount.part.2
	b	.L3109
.L3132:
	mov	r1, r8
	mov	r0, r4
	bl	MVC_SetFrmRepeatCount.part.2
	b	.L3100
.L3128:
	mov	r2, r0
	ldr	r1, .L3133+8
	mov	r0, #0
	bl	dprint_vfmw
	ldrsb	r1, [r6, #6]
	mov	r2, #0
	ldr	r0, [r4, #120]
	bl	FSP_SetDisplay
	mov	r0, r4
	mov	r1, #1
	bl	MVC_ClearAll
	mvn	r0, #0
	b	.L3123
.L3131:
	mov	r2, r0
	ldr	r1, .L3133+8
	mov	r0, #0
	mov	r5, r0
	bl	dprint_vfmw
	ldr	r3, [r4, #520]
	mov	r2, r5
	strb	r5, [r3, #2]
	ldr	r3, [r4, #520]
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetDisplay
	str	r5, [r4, #520]
	mov	r0, r4
	mov	r1, #1
	bl	MVC_ClearAll
	mvn	r0, #0
	b	.L3123
.L3127:
	movw	r2, #1902
	ldr	r1, .L3133+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3123
.L3130:
	movw	r2, #1850
	ldr	r1, .L3133+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3123
.L3134:
	.align	2
.L3133:
	.word	.LC402
	.word	.LC399
	.word	.LC401
	.word	.LC400
	UNWIND(.fnend)
	.size	MVC_OutputFrmToVO, .-MVC_OutputFrmToVO
	.align	2
	.global	MVC_OutputFrmFromDPB
	.type	MVC_OutputFrmFromDPB, %function
MVC_OutputFrmFromDPB:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r4, r0, r1, lsl #2
	mov	r6, r1
	add	r4, r4, #11075584
	mov	r5, r0
	add	r4, r4, #45056
	ldr	r3, [r4, #2696]
	cmp	r3, #0
	moveq	r4, r3
	beq	.L3136
	mov	r2, #0
	strb	r2, [r3, #5]
	ldr	r1, [r4, #2696]
	bl	MVC_OutputFrmToVO
	ldr	r3, [r4, #2696]
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	cmn	r0, #1
	movne	r0, #0
	moveq	r0, #1
	cmp	r2, #0
	rsb	r4, r0, #0
	beq	.L3138
.L3136:
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3138:
	mov	r0, r5
	mov	r1, r6
	bl	MVC_RemoveFrameStoreOutDPB
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_OutputFrmFromDPB, .-MVC_OutputFrmFromDPB
	.align	2
	.global	MVC_FlushDPB
	.type	MVC_FlushDPB, %function
MVC_FlushDPB:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	subs	r5, r0, #0
	mov	r4, r1
	beq	.L3158
	add	r8, r5, #11075584
	add	r8, r8, #45056
	ldr	r3, [r8, #2888]
	cmp	r3, #0
	movwne	r7, #47748
	movne	r6, #0
	movtne	r7, 169
	addne	r7, r5, r7
	beq	.L3146
.L3145:
	ldr	r1, [r7, #4]!
	add	r6, r6, #1
	cmp	r1, #0
	beq	.L3144
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3144
	ldr	r3, [r1, #56]
	cmn	r4, #1
	cmpne	r3, r4
	bne	.L3144
	mov	r0, r5
	bl	MVC_UnMarkFrameStoreRef
.L3144:
	ldr	r3, [r8, #2888]
	cmp	r3, r6
	bhi	.L3145
.L3146:
	mov	r1, r4
	mov	r0, r5
	bl	MVC_RemoveUnUsedFrameStore
	ldr	r0, [r8, #2888]
	cmp	r0, #0
	beq	.L3143
	movw	r1, #47748
	mov	r7, #0
	movt	r1, 169
	add	r1, r5, r1
	mov	r2, r7
	mvn	r6, #0
.L3150:
	ldr	r3, [r1, #4]!
	add	r2, r2, #1
	cmp	r3, #0
	beq	.L3148
	ldr	r3, [r3, #56]
	cmn	r4, #1
	cmpne	r4, r3
	addeq	r7, r7, #1
	cmp	r4, r3
	cmnne	r4, #1
	movne	r6, r3
.L3148:
	cmp	r2, r0
	bne	.L3150
	cmp	r7, #0
	beq	.L3143
	adds	r8, r6, #1
	movne	r8, #1
	cmp	r4, r6
	movle	r9, #0
	andgt	r9, r8, #1
	b	.L3156
.L3157:
	subs	r7, r7, #1
	beq	.L3143
.L3156:
	cmp	r9, #0
	sub	r3, fp, #44
	sub	r2, fp, #40
	mov	r1, r6
	mov	r0, r5
	beq	.L3153
	bl	MVC_GetMinPOC
	ldr	r1, [fp, #-44]
	mov	r0, r5
	cmn	r1, #1
	beq	.L3143
	bl	MVC_OutputFrmFromDPB
	cmp	r0, #0
	bne	.L3158
.L3153:
	mov	r1, r4
	sub	r3, fp, #44
	sub	r2, fp, #40
	mov	r0, r5
	bl	MVC_GetMinPOC
	ldr	r1, [fp, #-44]
	mov	r0, r5
	cmn	r1, #1
	beq	.L3143
	bl	MVC_OutputFrmFromDPB
	cmp	r0, #0
	bne	.L3158
	cmp	r4, r6
	movge	r3, #0
	andlt	r3, r8, #1
	cmp	r3, #0
	beq	.L3157
	mov	r1, r6
	sub	r3, fp, #44
	sub	r2, fp, #40
	mov	r0, r5
	bl	MVC_GetMinPOC
	ldr	r1, [fp, #-44]
	mov	r0, r5
	cmn	r1, #1
	beq	.L3143
	bl	MVC_OutputFrmFromDPB
	cmp	r0, #0
	beq	.L3157
.L3158:
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3143:
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_FlushDPB, .-MVC_FlushDPB
	.align	2
	.global	MVC_AdaptiveMemMark
	.type	MVC_AdaptiveMemMark, %function
MVC_AdaptiveMemMark:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r9, r0, #11141120
	add	r8, r9, #12288
	add	r7, r0, #11075584
	movw	r6, #15416
	add	r7, r7, #36864
	ldr	ip, [r8, #3780]
	movt	r6, 170
	add	r6, r0, r6
	mov	r4, r0
	add	r5, ip, #2000
	add	r10, ip, #4
	add	r5, r5, #4
	add	r3, r0, #11075584
	str	r3, [fp, #-48]
.L3205:
	ldr	r3, [r10]
	cmp	r3, #6
	ldrls	pc, [pc, r3, asl #2]
	b	.L3196
.L3198:
	.word	.L3197
	.word	.L3199
	.word	.L3200
	.word	.L3201
	.word	.L3202
	.word	.L3203
	.word	.L3204
.L3204:
	ldr	r2, [r10, #12]
	mov	r1, r6
	mov	r0, r4
	bl	MVC_MarkCurrPicLT
.L3196:
	add	r10, r10, #20
	cmp	r10, r5
	bne	.L3205
.L3197:
	ldrb	r3, [r7, #3992]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r0, #0
	beq	.L3213
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3203:
	mov	r0, r4
	bl	MVC_UnMarkAllSTRef
	mov	r0, r4
	bl	MVC_UpdateReflist
	mov	r1, #0
	mov	r0, r4
	bl	MVC_UpdateMaxLTFrmIdx
	mov	r0, r4
	bl	MVC_UpdateLTReflist
	mov	r3, #1
	strb	r3, [r7, #3992]
	b	.L3196
.L3202:
	mov	r0, r4
	ldr	r1, [r10, #16]
	bl	MVC_UpdateMaxLTFrmIdx
	mov	r0, r4
	bl	MVC_UpdateLTReflist
	b	.L3196
.L3201:
	ldr	r3, [r10, #12]
	mov	r1, r6
	ldr	r2, [r10, #4]
	mov	r0, r4
	bl	MVC_MarkSTToLTRef
	mov	r0, r4
	bl	MVC_UpdateReflist
	mov	r0, r4
	bl	MVC_UpdateLTReflist
	b	.L3196
.L3200:
	mov	r0, r4
	ldr	r2, [r10, #8]
	mov	r1, r6
	bl	MVC_UnMarkLTRef
	mov	r0, r4
	bl	MVC_UpdateLTReflist
	b	.L3196
.L3199:
	mov	r0, r4
	ldr	r2, [r10, #4]
	mov	r1, r6
	bl	MVC_UnMarkSTRef
	mov	r0, r4
	bl	MVC_UpdateReflist
	b	.L3196
.L3213:
	ldr	r3, [fp, #-48]
	mov	r2, #0
	str	r2, [r8, #3784]
	add	r9, r9, #16384
	add	r10, r3, #40960
	movw	r3, #26886
	movt	r3, 42
	ldr	r1, [r10, #2676]
	add	r3, r1, r3
	add	r3, r4, r3, lsl #2
	str	r2, [r3, #4]
	str	r2, [r9, #512]
	ldrb	r3, [r8, #3131]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3208
	bcc	.L3209
	cmp	r3, #2
	streq	r2, [r8, #3808]
	streq	r2, [r8, #3796]
	streq	r2, [r7, #4020]
	streq	r2, [r7, #4028]
.L3207:
	ldr	r1, [r8, #3856]
	mov	r0, r4
	bl	MVC_FlushDPB
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3209:
	ldr	r1, [r8, #3796]
	ldr	r2, [r8, #3804]
	ldr	r3, [r8, #3808]
	rsb	r2, r1, r2
	str	r2, [r8, #3804]
	rsb	r3, r1, r3
	str	r3, [r8, #3808]
	cmp	r3, r2
	movge	r3, r2
	str	r3, [r8, #3800]
	str	r3, [r8, #3796]
	ldr	r1, [r7, #4028]
	ldr	r2, [r7, #4016]
	ldr	r3, [r7, #4020]
	rsb	r2, r1, r2
	str	r2, [r7, #4016]
	rsb	r3, r1, r3
	str	r3, [r7, #4020]
	cmp	r3, r2
	movge	r3, r2
	str	r3, [r7, #4024]
	str	r3, [r7, #4028]
	b	.L3207
.L3208:
	str	r2, [r8, #3804]
	str	r2, [r8, #3796]
	str	r2, [r7, #4016]
	str	r2, [r7, #4028]
	b	.L3207
	UNWIND(.fnend)
	.size	MVC_AdaptiveMemMark, .-MVC_AdaptiveMemMark
	.align	2
	.global	MVC_IDRMemMarking
	.type	MVC_IDRMemMarking, %function
MVC_IDRMemMarking:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r6, r0, #11141120
	add	r6, r6, #12288
	mov	r7, r0
	ldr	r3, [r6, #3780]
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3215
	ldr	lr, [r0, #52]
	cmp	lr, #0
	beq	.L3224
	movw	r1, #47748
	mov	r2, #0
	movt	r1, 169
	add	r0, r0, #148
	add	r1, r7, r1
	mov	r4, r2
.L3223:
	ldr	r3, [r1, #4]!
	add	r2, r2, #1
	cmp	r3, #0
	beq	.L3220
	ldr	ip, [r3, #16]
	cmp	ip, #1
	streqb	ip, [r7, #6]
	ldr	ip, [r3, #56]
	ldr	r3, [r6, #3856]
	cmp	ip, r3
	streq	r4, [r0]
.L3220:
	cmp	r2, lr
	add	r0, r0, #4
	bne	.L3223
.L3224:
	add	r9, r7, #11075584
	add	ip, r9, #45056
	ldr	r10, [ip, #2888]
	cmp	r10, #0
	beq	.L3218
	movw	r4, #47748
	mov	r5, #0
	movt	r4, 169
	mov	r8, r5
	add	r4, r7, r4
	b	.L3229
.L3227:
	cmp	r5, r10
	beq	.L3218
.L3229:
	ldr	r1, [r4, #4]!
	add	r5, r5, #1
	cmp	r1, #0
	beq	.L3227
	ldr	r0, [r1, #56]
	ldr	r2, [r6, #3856]
	cmp	r0, r2
	bne	.L3227
	strb	r8, [r1, #706]
	mov	r2, #0
	strb	r8, [r1, #705]
	ldr	r1, [r4]
	str	ip, [fp, #-48]
	strb	r8, [r1, #742]
	strb	r8, [r1, #741]
	ldr	r1, [r4]
	strb	r8, [r1, #778]
	strb	r8, [r1, #777]
	ldr	r1, [r4]
	strb	r8, [r1, #3]
	ldr	r1, [r4]
	ldr	r0, [r7, #120]
	ldrsb	r1, [r1, #6]
	bl	FSP_SetRef
	ldr	r1, [r4]
	mov	r3, #1
	movw	r2, #47960
	movt	r2, 169
	strb	r8, [r1, #2]
	ldr	r1, [r4]
	strb	r8, [r1, #5]
	ldr	r1, [r4]
	strb	r3, [r1, #7]
	ldr	r0, [r4]
	ldr	r1, [r0, #52]
	add	r1, r7, r1
	add	r2, r1, r2
	strb	r8, [r2, #4]
	ldrsb	r1, [r0, #6]
	ldr	r0, [r7, #120]
	bl	FSP_GetDisplay
	mov	r2, #0
	ldr	ip, [fp, #-48]
	cmp	r0, #3
	beq	.L3228
	ldr	r1, [r4]
	ldr	r0, [r7, #120]
	ldrsb	r1, [r1, #6]
	bl	FSP_SetDisplay
	ldr	ip, [fp, #-48]
.L3228:
	str	r8, [r4]
	cmp	r5, r10
	str	r8, [r4, #64]
	str	r8, [r4, #128]
	ldr	r2, [ip, #2892]
	sub	r2, r2, #1
	str	r2, [ip, #2892]
	bne	.L3229
.L3218:
	mov	r0, r7
	bl	MVC_UpdateReflist
	mov	r0, r7
	bl	MVC_UpdateLTReflist
	ldr	r3, [r6, #3780]
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3242
	add	r9, r9, #45056
	mov	r0, r3
	mov	r2, #1
	str	r3, [r9, #2904]
	strb	r3, [r6, #3132]
	strb	r2, [r6, #3133]
.L3230:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3242:
	add	r9, r9, #45056
	mov	r3, #0
	mov	r2, #1
	mov	r0, r3
	str	r2, [r9, #2904]
	strb	r2, [r6, #3132]
	str	r3, [r6, #3788]
	strb	r3, [r6, #3133]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3215:
	ldr	r1, [r6, #3856]
	bl	MVC_FlushDPB
	cmp	r0, #0
	addeq	r9, r7, #11075584
	beq	.L3218
.L3231:
	mvn	r0, #0
	b	.L3230
	UNWIND(.fnend)
	.size	MVC_IDRMemMarking, .-MVC_IDRMemMarking
	.align	2
	.global	MVC_Marking
	.type	MVC_Marking, %function
MVC_Marking:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #11075584
	add	r5, r0, #11141120
	add	r3, r3, #36864
	add	r4, r5, #12288
	mov	r2, #0
	mov	r6, r0
	strb	r2, [r3, #3992]
	ldrb	r2, [r4, #3131]	@ zero_extendqisi2
	sub	r2, r2, #2
	clz	r2, r2
	mov	r2, r2, lsr #5
	strb	r2, [r3, #3993]
	ldrb	r3, [r4, #3134]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L3244
	ldrb	r3, [r4, #3140]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3245
	ldr	r3, [r0, #224]
	ldr	r2, [r3, #652]
	cmp	r2, #1
	beq	.L3266
.L3245:
	ldr	r3, [r4, #3780]
	ldrb	r3, [r3, #3]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r4, #3792]
	beq	.L3267
	cmp	r3, #0
	bne	.L3268
.L3252:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3267:
	cmp	r3, #0
	beq	.L3252
.L3251:
	ldrb	r7, [r4, #3129]	@ zero_extendqisi2
	cmp	r7, #0
	beq	.L3269
.L3255:
	add	r5, r5, #12288
	mov	r0, #0
	ldrb	r3, [r5, #3132]	@ zero_extendqisi2
	clz	r3, r3
	mov	r3, r3, lsr #5
	strb	r3, [r5, #3133]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3266:
	ldr	r2, [r3, #648]
	cmp	r2, #0
	bne	.L3245
	ldr	r2, [r3, #656]
	cmp	r2, #0
	bne	.L3245
	ldr	r3, [r3, #612]
	add	r3, r3, #1024
	cmp	r3, #2048
	bls	.L3245
.L3244:
	mov	r0, r6
	bl	MVC_IDRMemMarking
	cmp	r0, #0
	bne	.L3246
.L3253:
	ldrb	r3, [r4, #3134]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L3248
	ldr	r3, [r4, #3792]
	cmp	r3, #0
	beq	.L3252
	ldr	r3, [r4, #3780]
	ldrb	r3, [r3, #3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3251
	b	.L3255
.L3269:
	mov	r0, r6
	bl	MVC_SlidingWinMark
	ldr	r3, [r4, #3780]
	strb	r7, [r3]
	strb	r7, [r4, #3132]
.L3248:
	ldr	r3, [r4, #3792]
	cmp	r3, #0
	bne	.L3255
	b	.L3252
.L3268:
	mov	r0, r6
	bl	MVC_AdaptiveMemMark
	ldr	r3, [r4, #3780]
	mov	r2, #0
	strb	r2, [r3]
	cmp	r0, r2
	beq	.L3253
.L3246:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_Marking, .-MVC_Marking
	.align	2
	.global	MVC_DirectOutput
	.type	MVC_DirectOutput, %function
MVC_DirectOutput:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	add	r5, r0, #11141120
	add	r5, r5, #12288
	mov	r4, r0
	ldrb	r6, [r5, #3131]	@ zero_extendqisi2
	cmp	r6, #1
	beq	.L3272
	bcc	.L3273
	cmp	r6, #2
	beq	.L3274
	mov	r6, #0
.L3271:
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3274:
	ldr	r3, [r5, #3776]
	mov	r2, #3
	strb	r2, [r3, #704]
	ldrb	r2, [r5, #3129]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3292
	ldr	r1, [r0, #520]
	cmp	r1, #0
	beq	.L3293
	bl	MVC_OutputFrmToVO
	ldr	r3, [r5, #3776]
	str	r3, [r4, #520]
	str	r3, [r3, #780]
	mov	r6, r0
.L3294:
	ldr	r3, [r4, #520]
	mov	r8, #2
	ldrb	r0, [r5, #3130]	@ zero_extendqisi2
	mov	r7, #0
	add	r1, r5, #3136
	mov	r2, #632
	add	r1, r1, #8
	strb	r0, [r3, #1]
	ldr	r3, [r4, #520]
	strb	r8, [r3, #2]
	ldr	r3, [r4, #520]
	strb	r7, [r3, #5]
	ldr	r3, [r4, #520]
	strb	r7, [r3, #7]
	ldr	r3, [r4, #520]
	strb	r7, [r3, #3]
	ldr	r3, [r4, #520]
	ldrb	r0, [r5, #3140]	@ zero_extendqisi2
	strb	r0, [r3]
	ldr	r3, [r4, #520]
	str	r7, [r3, #40]
	ldr	r0, [r4, #520]
	add	r0, r0, #72
	bl	memcpy
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #3828]
	str	r2, [r3, #800]
	ldr	r3, [r4, #520]
	ldr	r2, [r3, #800]
	str	r2, [r3, #728]
	str	r2, [r3, #44]
	ldr	r3, [r4, #520]
	strb	r8, [r3, #776]
	ldrb	r2, [r5, #3135]	@ zero_extendqisi2
	ldr	r3, [r4, #520]
	cmp	r2, #1
	movne	r2, r7
	moveq	r2, r8
	strb	r2, [r3, #4]
.L3351:
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #3796]
	str	r2, [r3, #32]
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #3856]
	str	r2, [r3, #56]
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #3860]
	str	r2, [r3, #60]
	ldrb	r8, [r4, #9]	@ zero_extendqisi2
	cmp	r8, #1
	bne	.L3271
	ldr	r3, [r4, #520]
	mov	r2, r7
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetRef
	mov	r2, r7
	ldr	r1, [r4, #520]
	mov	r0, r4
	bl	MVC_OutputFrmToVO
	ldr	r3, [r4, #520]
	cmp	r3, r7
	mov	r6, r0
	beq	.L3304
	ldr	r3, [r5, #3776]
	mov	r2, r8
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_ClearLogicFs
	b	.L3304
.L3273:
	ldr	r3, [r5, #3776]
	mov	r2, #0
	strb	r2, [r3, #704]
	ldr	r1, [r0, #520]
	cmp	r1, r2
	beq	.L3275
	bl	MVC_OutputFrmToVO
	cmp	r0, #0
	bne	.L3354
.L3276:
	ldr	r3, [r4, #520]
	cmp	r3, #0
	beq	.L3275
	ldr	r3, [r5, #3776]
	mov	r2, #1
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_ClearLogicFs
.L3275:
	ldr	r3, [r5, #3776]
	mov	r0, #3
	mov	r7, #0
	add	r1, r5, #3136
	add	r1, r1, #8
	mov	r2, #632
	str	r3, [r4, #520]
	str	r3, [r3, #708]
	ldr	r3, [r4, #520]
	ldr	ip, [r5, #3776]
	str	ip, [r3, #744]
	ldr	r3, [r4, #520]
	ldr	ip, [r5, #3776]
	str	ip, [r3, #780]
	ldrb	ip, [r5, #3130]	@ zero_extendqisi2
	ldr	r3, [r4, #520]
	strb	ip, [r3, #1]
	ldr	r3, [r4, #520]
	strb	r0, [r3, #2]
	ldr	r3, [r4, #520]
	strb	r7, [r3, #3]
	ldr	r3, [r4, #520]
	strb	r7, [r3, #5]
	ldr	r3, [r4, #520]
	strb	r7, [r3, #7]
	ldr	r0, [r4, #520]
	add	r0, r0, #72
	bl	memcpy
	ldr	r3, [r4, #520]
	ldr	r1, [r5, #3828]
	mov	r2, r7
	str	r1, [r3, #728]
	str	r1, [r3, #44]
	ldr	r3, [r4, #520]
	strb	r7, [r3, #704]
	ldr	r3, [r4, #520]
	ldrb	r1, [r5, #3140]	@ zero_extendqisi2
	strb	r1, [r3]
	ldr	r3, [r4, #520]
	ldrb	r1, [r5, #3137]	@ zero_extendqisi2
	str	r1, [r3, #40]
	ldrb	r1, [r5, #3135]	@ zero_extendqisi2
	ldr	r3, [r4, #520]
	cmp	r1, #1
	moveq	r6, #3
	strb	r6, [r3, #4]
	ldr	r3, [r4, #520]
	ldr	r1, [r5, #3796]
	str	r1, [r3, #32]
	ldr	r3, [r4, #520]
	ldr	r1, [r5, #3856]
	str	r1, [r3, #56]
	ldr	r3, [r4, #520]
	ldr	r1, [r5, #3860]
	str	r1, [r3, #60]
	ldr	r3, [r4, #520]
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetRef
	mov	r2, r7
	ldr	r1, [r4, #520]
	mov	r0, r4
	bl	MVC_OutputFrmToVO
	ldr	r3, [r4, #520]
	cmp	r3, r7
	mov	r6, r0
	beq	.L3304
.L3346:
	ldr	r3, [r5, #3776]
	mov	r2, #1
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_ClearLogicFs
.L3304:
	mov	r3, #0
	mov	r0, r6
	str	r3, [r4, #520]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3272:
	ldr	r3, [r5, #3776]
	mov	r2, #3
	strb	r2, [r3, #704]
	ldrb	r2, [r5, #3129]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3280
	ldr	r1, [r0, #520]
	cmp	r1, #0
	beq	.L3281
	bl	MVC_OutputFrmToVO
	ldr	r3, [r5, #3776]
	str	r3, [r4, #520]
	str	r3, [r3, #744]
	mov	r6, r0
.L3282:
	ldr	r3, [r4, #520]
	mov	r8, #1
	ldrb	r0, [r5, #3130]	@ zero_extendqisi2
	mov	r7, #0
	add	r1, r5, #3136
	mov	r2, #632
	add	r1, r1, #8
	strb	r0, [r3, #1]
	ldr	r3, [r4, #520]
	strb	r8, [r3, #2]
	ldr	r3, [r4, #520]
	strb	r7, [r3, #5]
	ldr	r3, [r4, #520]
	strb	r7, [r3, #7]
	ldr	r3, [r4, #520]
	strb	r7, [r3, #3]
	ldr	r3, [r4, #520]
	ldrb	r0, [r5, #3140]	@ zero_extendqisi2
	strb	r0, [r3]
	ldr	r3, [r4, #520]
	str	r7, [r3, #40]
	ldr	r0, [r4, #520]
	add	r0, r0, #72
	bl	memcpy
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #3828]
	str	r2, [r3, #764]
	ldr	r3, [r4, #520]
	ldr	r2, [r3, #764]
	str	r2, [r3, #728]
	str	r2, [r3, #44]
	ldr	r3, [r4, #520]
	strb	r8, [r3, #740]
	ldrb	r3, [r5, #3135]	@ zero_extendqisi2
	ldr	r2, [r4, #520]
	rsb	r3, r8, r3
	clz	r3, r3
	mov	r3, r3, lsr #5
	strb	r3, [r2, #4]
	b	.L3351
.L3292:
	ldr	r3, [r0, #520]
	add	r1, r5, #3136
	add	r1, r1, #8
	mov	r2, #632
	cmp	r3, #0
	ldreq	r3, [r5, #3776]
	streq	r3, [r0, #520]
	streq	r3, [r3, #780]
	ldreq	r3, [r0, #520]
	add	ip, r3, #672
	add	r0, r3, #72
	ldr	r10, [r3, #656]
	ldrd	r8, [ip, #-8]
	ldrd	r6, [ip]
	ldr	ip, [r3, #660]
	str	ip, [fp, #-48]
	bl	memcpy
	movw	r3, #16016
	ldr	ip, [fp, #-48]
	mov	r1, r3
	movt	r3, 170
	add	r3, r4, r3
	movt	r1, 170
	ldr	r1, [r4, r1]
	and	r2, r10, ip
	ldr	r3, [r3, #4]
	movw	r0, #16032
	movt	r0, 170
	and	r1, r1, r3
	adds	r3, r2, #1
	movne	r3, #1
	cmn	r1, #1
	movne	r3, #0
	cmp	r3, #0
	ldrne	r3, [r4, #520]
	strne	ip, [r3, #660]
	mov	ip, #2
	strne	r10, [r3, #656]
	movw	r3, #16032
	movt	r3, 170
	add	r3, r4, r3
	ldr	r1, [r4, #520]
	ldrd	r2, [r3, #-8]
	add	r1, r1, #672
	cmp	r3, r9
	cmpeq	r2, r8
	movhi	r2, r8
	movhi	r3, r9
	strd	r2, [r1, #-8]
	ldrd	r0, [r0, r4]
	ldr	r3, [r4, #520]
	cmp	r1, r7
	cmpeq	r0, r6
	add	r3, r3, #672
	movhi	r0, r6
	movhi	r1, r7
	strd	r0, [r3]
	mov	r0, #3
	ldr	r2, [r4, #520]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	cmp	r3, #0
	ldrneb	r3, [r5, #3130]	@ zero_extendqisi2
	strb	r3, [r2, #1]
	ldr	r2, [r4, #520]
	ldrb	r3, [r2, #2]	@ zero_extendqisi2
	orr	r3, r3, ip
	strb	r3, [r2, #2]
	ldr	r2, [r4, #520]
	ldrb	r1, [r5, #3140]	@ zero_extendqisi2
	ldrb	r3, [r2]	@ zero_extendqisi2
	cmp	r3, r1
	movcc	r3, r1
	strb	r3, [r2]
	ldr	r3, [r4, #520]
	strb	ip, [r3, #776]
	ldr	r3, [r4, #520]
	strb	r0, [r3, #704]
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #3828]
	str	r2, [r3, #800]
	ldr	r2, [r4, #520]
	ldr	r3, [r2, #800]
	ldr	r1, [r2, #764]
	add	r3, r3, r1
	mov	r3, r3, lsr #1
	str	r3, [r2, #728]
	ldr	r3, [r4, #520]
	ldr	r2, [r3, #728]
	str	r2, [r3, #44]
	ldr	r3, [r4, #520]
	ldr	r2, [r3, #780]
	str	r2, [r3, #708]
	ldrb	r3, [r5, #3135]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r4, #520]
	ldrb	r2, [r3, #4]	@ zero_extendqisi2
	beq	.L3352
.L3303:
	strb	r2, [r3, #4]
	mov	r2, #0
	ldr	r3, [r4, #520]
	ldr	r1, [r5, #3796]
	str	r1, [r3, #32]
	ldr	r3, [r4, #520]
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetRef
	mov	r2, #0
	ldr	r1, [r4, #520]
	mov	r0, r4
	bl	MVC_OutputFrmToVO
	ldr	r3, [r4, #520]
	cmp	r3, #0
	mov	r6, r0
	bne	.L3346
	b	.L3304
.L3280:
	ldr	r3, [r0, #520]
	add	r1, r5, #3136
	add	r1, r1, #8
	mov	r2, #632
	cmp	r3, #0
	ldreq	r3, [r5, #3776]
	streq	r3, [r0, #520]
	streq	r3, [r3, #744]
	ldreq	r3, [r0, #520]
	add	ip, r3, #672
	add	r0, r3, #72
	ldr	r10, [r3, #656]
	ldrd	r8, [ip, #-8]
	ldrd	r6, [ip]
	ldr	ip, [r3, #660]
	str	ip, [fp, #-48]
	bl	memcpy
	movw	r3, #16016
	ldr	ip, [fp, #-48]
	mov	r1, r3
	movt	r3, 170
	add	r3, r4, r3
	movt	r1, 170
	ldr	r1, [r4, r1]
	and	r2, r10, ip
	ldr	r3, [r3, #4]
	movw	r0, #16032
	movt	r0, 170
	and	r1, r1, r3
	adds	r3, r2, #1
	movne	r3, #1
	cmn	r1, #1
	movne	r3, #0
	cmp	r3, #0
	ldrne	r3, [r4, #520]
	strne	ip, [r3, #660]
	mov	ip, #1
	strne	r10, [r3, #656]
	movw	r3, #16032
	movt	r3, 170
	add	r3, r4, r3
	ldr	r1, [r4, #520]
	ldrd	r2, [r3, #-8]
	add	r1, r1, #672
	cmp	r3, r9
	cmpeq	r2, r8
	movhi	r2, r8
	movhi	r3, r9
	strd	r2, [r1, #-8]
	ldrd	r0, [r0, r4]
	ldr	r3, [r4, #520]
	cmp	r1, r7
	cmpeq	r0, r6
	add	r3, r3, #672
	movhi	r0, r6
	movhi	r1, r7
	strd	r0, [r3]
	mov	r0, #3
	ldr	r2, [r4, #520]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	cmp	r3, #0
	ldrneb	r3, [r5, #3130]	@ zero_extendqisi2
	strb	r3, [r2, #1]
	ldr	r2, [r4, #520]
	ldrb	r3, [r2, #2]	@ zero_extendqisi2
	orr	r3, r3, ip
	strb	r3, [r2, #2]
	ldr	r2, [r4, #520]
	ldrb	r1, [r5, #3140]	@ zero_extendqisi2
	ldrb	r3, [r2]	@ zero_extendqisi2
	cmp	r3, r1
	movcc	r3, r1
	strb	r3, [r2]
	ldr	r3, [r4, #520]
	strb	ip, [r3, #740]
	ldr	r3, [r4, #520]
	strb	r0, [r3, #704]
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #3828]
	str	r2, [r3, #764]
	ldr	r2, [r4, #520]
	ldr	r3, [r2, #800]
	ldr	r1, [r2, #764]
	add	r3, r3, r1
	mov	r3, r3, lsr ip
	str	r3, [r2, #728]
	ldr	r3, [r4, #520]
	ldr	r2, [r3, #728]
	str	r2, [r3, #44]
	ldr	r3, [r4, #520]
	ldr	r2, [r3, #744]
	str	r2, [r3, #708]
	ldrb	r3, [r5, #3135]	@ zero_extendqisi2
	cmp	r3, ip
	ldr	r3, [r4, #520]
	ldrb	r2, [r3, #4]	@ zero_extendqisi2
	bne	.L3303
.L3352:
	orr	r2, r2, ip
	b	.L3303
.L3354:
	str	r0, [sp]
	movw	r3, #2479
	ldr	r2, .L3355
	mov	r0, #22
	ldr	r1, .L3355+4
	bl	dprint_vfmw
	b	.L3276
.L3293:
	ldr	r3, [r5, #3776]
	mov	r6, r1
	str	r3, [r0, #520]
	str	r3, [r3, #780]
	b	.L3294
.L3281:
	ldr	r3, [r5, #3776]
	mov	r6, r1
	str	r3, [r0, #520]
	str	r3, [r3, #744]
	b	.L3282
.L3356:
	.align	2
.L3355:
	.word	.LANCHOR0+248
	.word	.LC403
	UNWIND(.fnend)
	.size	MVC_DirectOutput, .-MVC_DirectOutput
	.align	2
	.global	MVC_DEC_GetRemainImg
	.type	MVC_DEC_GetRemainImg, %function
MVC_DEC_GetRemainImg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	add	r6, r0, #11075584
	add	r6, r6, #45056
	mov	r5, r0
	ldr	r3, [r6, #2888]
	cmp	r3, #0
	beq	.L3371
	movw	r8, #47748
	mov	r4, #0
	movt	r8, 169
	add	r8, r0, r8
	mov	r7, r4
	mov	r9, r8
	b	.L3360
.L3359:
	ldr	r3, [r6, #2888]
	cmp	r3, r7
	bls	.L3398
.L3360:
	ldr	r3, [r9, #4]!
	add	r7, r7, #1
	cmp	r3, #0
	beq	.L3359
	ldrb	r2, [r3, #5]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L3359
	ldrsb	r1, [r3, #6]
	ldr	r0, [r5, #120]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L3359
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	sub	r3, r3, #1
	cmp	r3, #1
	ldr	r3, [r6, #2888]
	addls	r4, r4, #1
	cmp	r3, r7
	bhi	.L3360
.L3398:
	cmp	r4, #0
	beq	.L3361
	mvn	r7, #0
	b	.L3364
.L3362:
	ldr	r1, [r5, r3, asl #2]
	bl	MVC_OutputFrmToVO
	subs	r4, r4, #1
	mov	r7, r0
	beq	.L3396
.L3364:
	sub	r3, fp, #44
	sub	r2, fp, #40
	mvn	r1, #0
	mov	r0, r5
	bl	MVC_GetMinPOC
	ldr	r1, [fp, #-44]
	movw	r3, #28322
	mov	r2, r4
	cmn	r1, #1
	movt	r3, 42
	mov	r0, r5
	add	r3, r1, r3
	bne	.L3362
.L3396:
	ldr	r3, [r6, #2888]
	cmp	r3, #0
	beq	.L3358
.L3363:
	mov	r4, #0
	b	.L3367
.L3366:
	ldr	r3, [r6, #2888]
	cmp	r3, r4
	bls	.L3358
.L3367:
	ldr	r1, [r8, #4]!
	add	r4, r4, #1
	cmp	r1, #0
	beq	.L3366
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3366
	mov	r0, r5
	bl	MVC_UnMarkFrameStoreRef
	ldr	r3, [r6, #2888]
	cmp	r3, r4
	bhi	.L3367
.L3358:
	mvn	r1, #0
	mov	r0, r5
	bl	MVC_RemoveUnUsedFrameStore
	cmp	r7, #0
	bne	.L3369
	mov	r0, r7
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3361:
	cmp	r3, #0
	mvnne	r7, #0
	bne	.L3363
	mvn	r1, #0
	mov	r0, r5
	bl	MVC_RemoveUnUsedFrameStore
.L3369:
	add	r0, r5, #584
	bl	GetVoLastImageID
	mov	r7, r0
	mov	r0, r7
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3371:
	mvn	r7, #0
	b	.L3358
	UNWIND(.fnend)
	.size	MVC_DEC_GetRemainImg, .-MVC_DEC_GetRemainImg
	.align	2
	.global	MVC_InitDPB
	.type	MVC_InitDPB, %function
MVC_InitDPB:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	subs	r4, r0, #0
	beq	.L3416
	bl	MVC_ClearAllSlice
	movw	r7, #47752
	movw	r6, #47880
	movw	r5, #47816
	movt	r7, 169
	movt	r6, 169
	movt	r5, 169
	mov	r8, #0
	add	r7, r4, r7
	add	r6, r4, r6
	add	r5, r4, r5
	mov	r9, r8
.L3404:
	ldr	r3, [r7]
	mov	r2, #1
	add	r8, r8, r2
	cmp	r3, #0
	beq	.L3401
	ldrsb	r1, [r3, #6]
	ldr	r0, [r4, #120]
	bl	FSP_ClearLogicFs
.L3401:
	ldr	r3, [r5]
	mov	r2, #1
	cmp	r3, #0
	beq	.L3402
	ldrsb	r1, [r3, #6]
	ldr	r0, [r4, #120]
	bl	FSP_ClearLogicFs
.L3402:
	ldr	r3, [r6]
	mov	r2, #1
	cmp	r3, #0
	beq	.L3403
	ldrsb	r1, [r3, #6]
	ldr	r0, [r4, #120]
	bl	FSP_ClearLogicFs
.L3403:
	cmp	r8, #16
	str	r9, [r6], #4
	mov	r2, #0
	str	r9, [r5], #4
	str	r9, [r7], #4
	bne	.L3404
	ldr	r3, [r4, #44]
	add	r5, r4, #11075584
	add	r6, r5, #45056
	str	r3, [r6, #2888]
	str	r2, [r6, #2892]
	str	r2, [r6, #2896]
	str	r2, [r6, #2900]
	str	r2, [r6, #2904]
	ldr	r1, [r4, #520]
	cmp	r1, r2
	beq	.L3406
	ldrb	r3, [r4, #8]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L3407
.L3411:
	add	r3, r4, #11141120
	add	r3, r3, #12288
	ldr	r3, [r3, #3776]
	cmp	r3, #0
	beq	.L3409
	ldrsb	r1, [r3, #6]
	mov	r2, #1
	ldr	r0, [r4, #120]
	bl	FSP_ClearLogicFs
.L3409:
	mov	r3, #0
	str	r3, [r4, #520]
.L3406:
	ldr	r3, .L3434
	movw	r0, #47964
	mov	r2, #344
	mov	r1, #0
	movt	r0, 169
	add	r0, r4, r0
	ldr	r3, [r3, #48]
	blx	r3
	ldr	ip, [r6, #2888]
	mov	r0, #0
	add	r3, r4, #144
	add	r1, r4, #216
	mov	r2, r0
	str	ip, [r6, #3116]
	str	r0, [r6, #3120]
.L3413:
	str	r2, [r3, #4]!
	cmp	r3, r1
	bne	.L3413
	add	r2, r4, #252
	add	r3, r4, #384
	mov	r0, #0
.L3414:
	str	r0, [r2, #4]!
	cmp	r2, r3
	mov	r1, #0
	bne	.L3414
	add	r2, r5, #40960
	add	r4, r4, #516
	mov	r0, r1
	str	r1, [r2, #1080]
.L3415:
	str	r0, [r3, #4]!
	cmp	r3, r4
	mov	r2, #0
	bne	.L3415
	add	r5, r5, #40960
	mov	r0, r2
	str	r2, [r5, #1084]
.L3400:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3407:
	mov	r0, r4
	bl	MVC_OutputFrmToVO
	cmp	r0, #0
	bne	.L3433
.L3410:
	ldr	r3, [r4, #520]
	cmp	r3, #0
	bne	.L3411
	b	.L3406
.L3433:
	str	r0, [sp]
	movw	r3, #5891
	ldr	r2, .L3434+4
	mov	r0, #22
	ldr	r1, .L3434+8
	bl	dprint_vfmw
	b	.L3410
.L3416:
	mvn	r0, #0
	b	.L3400
.L3435:
	.align	2
.L3434:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+268
	.word	.LC404
	UNWIND(.fnend)
	.size	MVC_InitDPB, .-MVC_InitDPB
	.align	2
	.global	MVC_ClearDPB
	.type	MVC_ClearDPB, %function
MVC_ClearDPB:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	bl	MVC_FlushDPB
	cmp	r0, #0
	bne	.L3445
.L3437:
	mov	r0, r4
	bl	MVC_InitDPB
	cmp	r0, #0
	beq	.L3438
	mov	r3, #312
	ldr	r2, .L3446
	ldr	r1, .L3446+4
	mov	r0, #22
	bl	dprint_vfmw
.L3438:
	mov	r0, #0
	strb	r0, [r4, #6]
	str	r0, [r4, #220]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3445:
	movw	r3, #307
	ldr	r2, .L3446
	ldr	r1, .L3446+8
	mov	r0, #22
	bl	dprint_vfmw
	b	.L3437
.L3447:
	.align	2
.L3446:
	.word	.LANCHOR0+280
	.word	.LC406
	.word	.LC405
	UNWIND(.fnend)
	.size	MVC_ClearDPB, .-MVC_ClearDPB
	.align	2
	.global	MVC_DecVDM
	.type	MVC_DecVDM, %function
MVC_DecVDM:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	add	r5, r0, #11141120
	add	r6, r5, #12288
	mov	r4, r0
	ldrb	r3, [r6, #3131]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3449
	ldrb	r3, [r6, #3129]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3449
.L3450:
	ldr	r3, [r4, #108]
	ldrb	r2, [r4, #8]	@ zero_extendqisi2
	ubfx	r7, r3, #16, #2
	cmp	r7, r2
	beq	.L3451
	sub	r2, r2, #2
	cmp	r2, #1
	cmpls	r7, #1
	bls	.L3508
.L3451:
	uxtb	r3, r7
	strb	r3, [r4, #8]
	cmp	r3, #2
	beq	.L3454
	cmp	r3, #3
	beq	.L3455
	cmp	r3, #1
	beq	.L3509
	ldrb	r3, [r4, #11]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3510
.L3462:
	ldr	r3, [r4, #64]
.L3458:
	ldrb	r2, [r6, #3141]	@ zero_extendqisi2
	strb	r2, [r4, #11]
.L3463:
	cmp	r3, #0
	beq	.L3506
	ldrb	r3, [r6, #3140]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L3511
	cmp	r3, #1
	bne	.L3466
	ldr	r2, [r6, #3856]
	cmp	r2, #0
	streqb	r3, [r4, #7]
.L3466:
	ldr	r2, [r4, #88]
	mov	r0, #2
	ldrb	r3, [r6, #3131]	@ zero_extendqisi2
	sub	r2, r2, #1
	ldr	r1, .L3514
	bl	dprint_vfmw
	ldr	r1, [r6, #3844]
	add	r3, r5, #16384
	mov	r2, #1
	str	r1, [r3, #1820]
	strb	r2, [r3, #1082]
	ldr	r2, [r6, #3848]
	str	r2, [r3, #1816]
	ldr	r2, [r4, #64]
	str	r2, [r3, #2020]
	ldr	r2, [r4, #88]
	cmp	r2, #0
	beq	.L3467
	ldrb	r1, [r6, #3140]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L3512
	add	r3, r4, #11075584
	add	r3, r3, #45056
	ldr	r3, [r3, #2892]
	cmp	r3, #0
	bne	.L3469
	ldr	r3, [r4, #224]
	ldr	r2, [r3, #24]
	cmp	r2, #2
	bne	.L3506
.L3472:
	movw	r2, #17464
	movt	r2, 170
	add	r2, r4, r2
	str	r2, [r4, #228]
	ldr	r1, [r3, #880]
	cmp	r1, #1
	beq	.L3513
	cmp	r1, #2
	bne	.L3475
	ldr	r1, [r3, #884]
	cmp	r2, #0
	cmpne	r1, #0
	ble	.L3475
	ldrb	r2, [r6, #3140]	@ zero_extendqisi2
	cmp	r2, #2
	bne	.L3475
	mov	r2, #0
	str	r2, [r4, #228]
	ldr	r3, [r6, #3776]
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetDisplay
	ldr	r2, [r4, #224]
	mov	r0, r4
	ldr	r3, [r2, #884]
	sub	r3, r3, #1
	str	r3, [r2, #884]
	bl	MVC_ClearCurrPic
	mvn	r0, #0
	b	.L3503
.L3449:
	ldr	r3, [r4, #140]
	ldr	r2, [r4, #144]
	add	r3, r3, #1
	ldr	r1, [r4, #224]
	cmp	r3, r2
	movlt	r3, r2
	str	r3, [r4, #140]
	rsb	r3, r2, r3
	str	r3, [r1, #576]
	b	.L3450
.L3508:
	mov	r2, r7
	ldr	r1, .L3514+4
	mov	r0, #2
	bl	dprint_vfmw
	strb	r7, [r4, #8]
.L3455:
	mov	r0, r4
	bl	MVC_ClearCurrPic
	mov	r0, r4
	mvn	r1, #0
	bl	MVC_ClearDPB
	mvn	r0, #0
.L3503:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3467:
	ldr	r3, [r4, #224]
.L3475:
	ldr	r2, [r3, #592]
	add	r5, r5, #16384
	mov	r0, #0
	strb	r2, [r5, #1084]
	ldr	r2, [r3, #596]
	strb	r2, [r5, #1085]
	ldr	r2, [r3, #600]
	str	r2, [r5, #1088]
	ldr	r2, [r3, #604]
	str	r2, [r5, #1092]
	ldr	r3, [r3, #644]
	strb	r3, [r5, #1096]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3509:
	ldrb	r3, [r6, #3140]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L3462
	ldr	r3, [r6, #3792]
	cmp	r3, #0
	beq	.L3459
	ldrb	r3, [r4, #11]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L3462
.L3476:
	ldrb	r2, [r6, #3141]	@ zero_extendqisi2
	ldr	r3, [r4, #64]
	strb	r2, [r4, #11]
	b	.L3463
.L3454:
	ldrb	r3, [r6, #3140]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3459
	ldr	r3, [r4, #64]
	cmp	r3, #0
	beq	.L3458
	ldr	r2, [r4, #544]
	ldr	r2, [r2, #48]
	cmp	r2, #0
	beq	.L3458
.L3459:
	mov	r3, #1
	mov	r0, r4
	strb	r3, [r6, #3135]
	bl	MVC_ClearCurrPic
	mvn	r0, #0
	b	.L3503
.L3510:
	ldrb	r3, [r6, #3140]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L3462
	b	.L3476
.L3511:
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L3466
	ldr	r3, [r4, #224]
	ldr	r7, [r3, #24]
	cmp	r7, #0
	bne	.L3466
	ldr	r3, [r6, #3792]
	mov	r0, #1
	ldr	r2, [r6, #3796]
	ldr	r1, .L3514+8
	bl	dprint_vfmw
	mov	r0, r4
	bl	MVC_ClearCurrPic
	ldr	r3, [r6, #3776]
	ldr	r0, [r4, #120]
	mov	r2, r7
	ldrsb	r1, [r3, #6]
	bl	FSP_SetDisplay
	mvn	r0, #0
	b	.L3503
.L3512:
	ldr	r2, .L3514+12
	ldr	ip, [r2]
	cmp	ip, #0
	beq	.L3469
	ldr	r2, [r3, #2024]
	cmp	r2, #0
	beq	.L3477
.L3471:
	ldr	r3, [r2, #8]
	ldr	r0, [r2, #12]
	ldr	r2, [r2, #4056]
	add	r3, r3, r0
	add	r3, r3, #7
	cmp	r2, #0
	add	r1, r1, r3, lsr #3
	bne	.L3471
.L3470:
	sub	r2, fp, #28
	mov	r3, #4
	ldr	r0, [r4, #120]
	str	r1, [r2, #-4]!
	mov	r1, #20
	blx	ip
	ldr	r3, [r4, #224]
	b	.L3472
.L3469:
	ldr	r3, [r4, #224]
	b	.L3472
.L3513:
	cmp	r2, #0
	beq	.L3475
	ldrb	r2, [r6, #3140]	@ zero_extendqisi2
	cmp	r2, #2
	bne	.L3475
	mov	r2, #0
	str	r2, [r4, #228]
	ldr	r3, [r6, #3776]
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetDisplay
.L3506:
	mov	r0, r4
	bl	MVC_ClearCurrPic
	mvn	r0, #0
	b	.L3503
.L3477:
	mov	r1, r2
	b	.L3470
.L3515:
	.align	2
.L3514:
	.word	.LC409
	.word	.LC407
	.word	.LC408
	.word	g_event_report
	UNWIND(.fnend)
	.size	MVC_DecVDM, .-MVC_DecVDM
	.align	2
	.global	MVC_FlushDecoder
	.type	MVC_FlushDecoder, %function
MVC_FlushDecoder:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #11075584
	mov	r1, #1
	add	r3, r3, #40960
	mov	ip, #0
	strb	r1, [r3, #1037]
	str	ip, [r3, #1088]
	strb	r1, [r0]
	bl	MVC_DecVDM
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	movw	r3, #12883
	ldr	r2, .L3518
	ldr	r1, .L3518+4
	mov	r0, #22
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L3519:
	.align	2
.L3518:
	.word	.LANCHOR0+296
	.word	.LC410
	UNWIND(.fnend)
	.size	MVC_FlushDecoder, .-MVC_FlushDecoder
	.align	2
	.global	MVC_ReceivePacket
	.type	MVC_ReceivePacket, %function
MVC_ReceivePacket:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	ip, [r1, #12]
	ldr	r3, [r1, #8]
	mov	r4, r0
	ldr	r2, [r1, #4]
	mov	r5, r1
	mov	r0, #7
	add	r6, r4, #11141120
	ldr	r1, .L3583
	str	ip, [sp]
	bl	dprint_vfmw
	add	r3, r6, #16384
	mov	r2, #0
	str	r2, [r3, #2272]
	ldr	r3, [r4, #224]
	ldr	r2, [r3, #840]
	cmp	r2, #1
	beq	.L3578
.L3521:
	ldr	r3, [r4, #232]
	cmp	r3, #0
	beq	.L3541
	ldrb	r2, [r5]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L3579
.L3524:
	ldr	r1, .L3583+4
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #232]
	cmp	r1, #0
	beq	.L3541
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L3541:
	ldr	r3, [r5, #12]
	cmp	r3, #0
	ble	.L3528
	ldr	r3, [r5, #4]
	cmp	r3, #0
	beq	.L3528
	ldr	r3, [r5, #8]
	cmp	r3, #0
	beq	.L3528
	ldrb	r3, [r4, #937]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3544
	mov	r2, r4
	mov	r3, #1
	b	.L3531
.L3530:
	add	r3, r3, #1
	cmp	r3, #137
	beq	.L3542
.L3531:
	ldrb	r1, [r2, #1025]	@ zero_extendqisi2
	add	r2, r2, #88
	cmp	r1, #0
	bne	.L3530
	mov	r1, r3
.L3529:
	mov	r2, #88
	cmn	r1, #1
	mla	r3, r2, r3, r4
	mov	r0, #1
	strb	r0, [r3, #937]
	beq	.L3542
	mul	r3, r2, r1
	mov	r1, #0
	add	r2, r3, #936
	add	r3, r4, r3
	add	r2, r4, r2
	str	r2, [r4, #232]
	ldr	r2, [r5, #4]
	str	r2, [r3, #944]
	ldr	r2, [r5, #12]
	str	r2, [r3, #948]
	ldr	r2, [r5, #8]
	str	r2, [r3, #952]
	ldr	r3, [r4, #232]
	str	r1, [r3, #24]
	ldr	r3, [r4, #232]
	ldr	r2, [r5, #16]
	str	r2, [r3, #32]
	ldrd	r2, [r5, #24]
	ldr	ip, [r4, #232]
	strd	r2, [ip, #80]
	ldr	r3, [r4, #232]
	str	r0, [r3, #68]
	ldr	r3, [r4, #232]
	strb	r1, [r3]
	ldr	r3, [r4, #232]
	ldrb	r2, [r5]	@ zero_extendqisi2
	strb	r2, [r3, #3]
	ldr	r3, [r4, #232]
	b	.L3534
.L3579:
	ldr	r1, [r3, #68]
	cmp	r1, #1
	bhi	.L3524
	ldrb	r1, [r3, #3]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L3525
	b	.L3524
.L3578:
	ldr	r3, [r3, #888]
	cmp	r3, #0
	beq	.L3521
	ldr	r3, [r4, #232]
	cmp	r3, #0
	ldrneb	r2, [r5]	@ zero_extendqisi2
	beq	.L3541
.L3525:
	strb	r2, [r3, #3]
	ldr	r3, [r4, #224]
	ldr	r2, [r3, #840]
	cmp	r2, #1
	beq	.L3580
.L3536:
	ldr	r3, [r5, #12]
	cmp	r3, #0
	ble	.L3537
	ldr	r2, [r5, #4]
	cmp	r2, #0
	beq	.L3537
	ldr	r3, [r5, #8]
	cmp	r3, #0
	beq	.L3537
	ldr	r3, [r4, #232]
	ldr	r1, [r3, #68]
	cmp	r1, #1
	bls	.L3581
.L3538:
	mov	r2, #1
	strb	r2, [r3, #3]
	ldr	r1, [r5, #16]
	ldr	r0, [r4, #120]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L3583+8
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3575
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #120]
	blx	ip
.L3575:
	ldr	r3, [r4, #232]
.L3534:
	ldrb	r0, [r3, #3]	@ zero_extendqisi2
	clz	r0, r0
	mov	r0, r0, lsr #5
	rsb	r0, r0, #0
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L3528:
	ldr	r1, .L3583+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r5, #16]
	ldr	r0, [r4, #120]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L3583+8
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3577
.L3576:
	mov	r3, #0
	ldr	r0, [r4, #120]
	mov	r2, r3
	mov	r1, #113
	blx	ip
.L3577:
	mvn	r0, #0
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L3537:
	ldr	r3, [r4, #232]
	b	.L3538
.L3580:
	ldr	r3, [r3, #888]
	cmp	r3, #0
	bne	.L3575
	b	.L3536
.L3581:
	mov	ip, r1, asl #5
	mov	r0, #0
	sub	r1, ip, r1, asl #2
	add	r3, r3, r1
	str	r2, [r3, #8]
	ldr	r3, [r4, #232]
	ldr	ip, [r5, #12]
	ldr	r1, [r3, #68]
	mov	r2, r1, asl #5
	sub	r2, r2, r1, asl #2
	add	r3, r3, r2
	str	ip, [r3, #12]
	ldr	r3, [r4, #232]
	ldr	ip, [r5, #8]
	ldr	r1, [r3, #68]
	mov	r2, r1, asl #5
	sub	r2, r2, r1, asl #2
	add	r3, r3, r2
	str	ip, [r3, #16]
	ldr	r3, [r4, #232]
	ldr	r1, [r3, #68]
	mov	r2, r1, asl #5
	sub	r2, r2, r1, asl #2
	add	r3, r3, r2
	str	r0, [r3, #24]
	ldr	r3, [r4, #232]
	ldr	r0, [r5, #16]
	ldr	r1, [r3, #68]
	mov	r2, r1, asl #5
	sub	r2, r2, r1, asl #2
	add	r3, r3, r2
	str	r0, [r3, #32]
	ldr	r2, [r4, #232]
	ldr	r3, [r2, #68]
	add	r3, r3, #1
	str	r3, [r2, #68]
	ldr	r3, [r4, #232]
	ldr	r2, [r3, #12]
	cmp	r2, #4096
	bcc	.L3582
.L3539:
	add	r6, r6, #16384
	mov	r2, #1
	str	r2, [r6, #2272]
	b	.L3534
.L3582:
	mov	r0, r4
	bl	MVC_CombinePacket.part.13
	ldr	r3, [r4, #232]
	b	.L3539
.L3542:
	ldr	r1, .L3583+16
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r4
	bl	MVC_ClearAllNal
	mov	r0, r4
	bl	MVC_ClearCurrPic
	mvn	r1, #0
	mov	r0, r4
	bl	MVC_ClearDPB
	ldr	r3, .L3583+8
	ldr	ip, [r3]
	cmp	ip, #0
	bne	.L3576
	b	.L3577
.L3544:
	mov	r1, r3
	b	.L3529
.L3584:
	.align	2
.L3583:
	.word	.LC411
	.word	.LC412
	.word	g_event_report
	.word	.LC414
	.word	.LC413
	UNWIND(.fnend)
	.size	MVC_ReceivePacket, .-MVC_ReceivePacket
	.align	2
	.global	MVC_ClearAll
	.type	MVC_ClearAll, %function
MVC_ClearAll:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r8, r0
	mov	r4, r1
	mov	r0, #22
	ldr	r1, .L3618
	bl	dprint_vfmw
	mov	r0, r8
	bl	MVC_ClearCurrPic
	mov	r0, r8
	bl	MVC_ClearAllNal
	mov	r0, r8
	bl	MVC_InitDPB
	cmp	r0, #0
	bne	.L3615
.L3586:
	cmp	r4, #0
	beq	.L3587
	add	r1, r8, #584
	ldr	r0, [r8, #120]
	bl	FSP_ClearNotInVoQueue
.L3588:
	movw	r4, #48312
	mov	r10, #0
	movt	r4, 169
	add	r4, r8, r4
	mov	r6, #0
	mov	r7, #0
.L3591:
	add	r5, r4, #608
	add	r9, r4, #640
	mov	r3, #0
	mov	r2, #1
	mvn	lr, #0
	mov	ip, #18
	mov	r0, #16
	mov	r1, #2
	str	r10, [r4, #220]
	str	r4, [r4, #780]
	str	r4, [r4, #744]
	str	r4, [r4, #708]
	strb	r3, [r4, #1]
	strb	r3, [r4, #2]
	strb	r3, [r4, #3]
	str	r3, [r4, #28]
	str	r3, [r4, #20]
	str	r3, [r4, #32]
	strb	r3, [r4, #5]
	strb	r3, [r4, #704]
	str	lr, [r4, #24]
	strb	r2, [r4, #7]
	strb	r2, [r4, #740]
	str	ip, [r4, #48]
	str	r0, [r4, #52]
	strb	r1, [r4, #776]
.L3590:
	ldrd	r2, [r5, #8]!
	orrs	r1, r2, r3
	bne	.L3616
.L3589:
	cmp	r5, r9
	bne	.L3590
	add	r10, r10, #1
	add	r4, r4, #816
	cmp	r10, #40
	bne	.L3591
	movw	r4, #15968
	add	r6, r8, #11141120
	movt	r4, 170
	add	r5, r6, #16000
	add	r4, r8, r4
.L3593:
	ldrd	r2, [r4, #8]!
	orrs	r1, r2, r3
	bne	.L3617
.L3592:
	cmp	r4, r5
	bne	.L3593
	ldr	r3, [r8, #60]
	cmp	r3, #0
	beq	.L3597
	mov	r4, #0
	add	r5, r8, #524
	mov	r7, r4
.L3596:
	ldr	r1, [r5, #4]!
	add	r4, r4, #1
	cmp	r1, #0
	beq	.L3595
	ldr	r0, [r8, #120]
	bl	FreeUsdByDec
	str	r7, [r5]
.L3595:
	ldr	r3, [r8, #60]
	cmp	r3, r4
	bhi	.L3596
.L3597:
	add	r5, r8, #11075584
	ldr	ip, .L3618+4
	add	r3, r5, #45056
	add	r5, r5, #40960
	mov	r4, #0
	movw	r0, #41992
	strb	r4, [r8, #4]
	mov	r1, r4
	strb	r4, [r8, #9]
	movw	r2, #1656
	strb	r4, [r8, #6]
	movt	r0, 169
	strb	r4, [r8, #7]
	add	r0, r8, r0
	strb	r4, [r8, #3]
	str	r4, [r8, #60]
	str	r4, [r8, #64]
	str	r4, [r8, #104]
	str	r4, [r8, #220]
	str	r4, [r8, #232]
	ldr	ip, [ip, #48]
	strb	r4, [r3, #644]
	strb	r4, [r5, #2736]
	strb	r4, [r3, #645]
	strb	r4, [r5, #2737]
	blx	ip
	add	r2, r6, #12288
	add	r6, r6, #16384
	mov	r1, #2
	mov	r3, #1
	strb	r1, [r5, #1032]
	strb	r3, [r5, #1037]
	mov	r0, r4
	strb	r4, [r2, #3128]
	mov	r3, #256
	strb	r4, [r6, #504]
	str	r4, [r6, #508]
	str	r3, [r6, #512]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3616:
	mov	r1, r2
	ldr	r0, [r8, #120]
	bl	FreeUsdByDec
	strd	r6, [r5]
	b	.L3589
.L3617:
	mov	r1, r2
	ldr	r0, [r8, #120]
	bl	FreeUsdByDec
	mov	r2, #0
	mov	r3, #0
	strd	r2, [r4]
	b	.L3592
.L3587:
	add	r0, r8, #584
	bl	ResetVoQueue
	ldr	r0, [r8, #120]
	bl	FSP_EmptyInstance
	b	.L3588
.L3615:
	movw	r3, #337
	ldr	r2, .L3618+8
	ldr	r1, .L3618+12
	mov	r0, #22
	bl	dprint_vfmw
	b	.L3586
.L3619:
	.align	2
.L3618:
	.word	.LC415
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+316
	.word	.LC406
	UNWIND(.fnend)
	.size	MVC_ClearAll, .-MVC_ClearAll
	.align	2
	.global	MVC_InsertFrmInDPB
	.type	MVC_InsertFrmInDPB, %function
MVC_InsertFrmInDPB:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	add	r3, r0, #11075584
	add	r3, r3, #45056
	mov	r4, r2
	ldrb	r7, [r4, #3]	@ zero_extendqisi2
	mov	r6, r0
	ldr	r3, [r3, #2892]
	str	r1, [fp, #-48]
	cmp	r3, #0
	ldreq	r2, .L3721
	streq	r3, [r2, #-1884]
	cmp	r7, #1
	beq	.L3623
	bcc	.L3624
	cmp	r7, #2
	beq	.L3625
	mov	r2, r7
	ldr	r1, .L3721+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r6
	mov	r1, #1
	bl	MVC_ClearAll
	mov	r0, #0
.L3629:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3625:
	ldr	r3, [r4, #648]
	mov	r2, #3
	strb	r2, [r3, #704]
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [fp, #-48]
	mov	r3, r3, asl #2
	beq	.L3645
	add	r8, r0, r3
	add	r2, r8, #11075584
	str	r2, [fp, #-52]
	add	r5, r2, #45056
	ldr	r2, [r5, #2696]
	cmp	r2, #0
	beq	.L3645
	strb	r7, [r2, #776]
	ldr	r3, [r5, #2696]
	ldr	r2, [r4, #648]
	str	r2, [r3, #780]
	ldr	r3, [r5, #2696]
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	strb	r2, [r3, #777]
	ldr	r3, [r5, #2696]
	ldrb	r2, [r4, #5]	@ zero_extendqisi2
	strb	r2, [r3, #778]
	ldr	r3, [r5, #2696]
	ldr	r2, [r4, #680]
	str	r2, [r3, #792]
	ldr	r3, [r5, #2696]
	ldrb	r2, [r4, #12]	@ zero_extendqisi2
	strb	r2, [r3, #779]
	ldr	r3, [r5, #2696]
	ldr	r2, [r4, #700]
	str	r2, [r3, #800]
	ldr	r3, [r5, #2696]
	ldr	r1, [r3, #764]
	ldr	r2, [r3, #800]
	add	r2, r2, r1
	str	r2, [r3, #728]
	str	r2, [r3, #44]
	add	r1, r4, #16
	ldr	r2, [r5, #2696]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	cmp	r3, #0
	ldrneb	r3, [r4, #2]	@ zero_extendqisi2
	strb	r3, [r2, #1]
	ldr	r2, [r5, #2696]
	ldrb	r3, [r2, #2]	@ zero_extendqisi2
	orr	r3, r3, #2
	strb	r3, [r2, #2]
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r5, #2696]
	ldrb	r2, [r3, #4]	@ zero_extendqisi2
	orreq	r2, r2, #2
	strb	r2, [r3, #4]
	mov	r2, #632
	ldr	r3, [r5, #2696]
	add	ip, r3, #672
	add	r0, r3, #72
	ldr	r10, [r3, #656]
	ldrd	r8, [ip, #-8]
	ldr	r7, [r3, #660]
	strd	r8, [fp, #-60]
	ldrd	r8, [ip]
	strd	r8, [fp, #-68]
	bl	memcpy
	add	r3, r4, #608
	and	r2, r10, r7
	adds	r2, r2, #1
	ldrd	r8, [fp, #-60]
	ldmdb	r3, {r0, r1}
	movne	r2, #1
	and	r1, r1, r0
	add	r0, r4, #624
	cmn	r1, #1
	movne	r2, #0
	cmp	r2, #0
	ldrne	r2, [r5, #2696]
	strne	r10, [r2, #656]
	strne	r7, [r2, #660]
	ldrd	r2, [r3]
	ldr	r1, [r5, #2696]
	cmp	r3, r9
	cmpeq	r2, r8
	add	r1, r1, #672
	movhi	r2, r8
	movhi	r3, r9
	ldrd	r8, [fp, #-68]
	strd	r2, [r1, #-8]
	ldrd	r2, [r0, #-8]
	ldr	r1, [r5, #2696]
	cmp	r3, r9
	cmpeq	r2, r8
	add	r1, r1, #672
	movhi	r3, r9
	movhi	r2, r8
	strd	r2, [r1]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3657
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3657
.L3658:
	ldr	r3, [fp, #-52]
	add	r8, r3, #45056
	ldr	r2, [r8, #2696]
	ldrb	r3, [r2, #779]	@ zero_extendqisi2
	ldrb	r1, [r2, #743]	@ zero_extendqisi2
	cmp	r3, r1
	movcc	r3, r1
	strb	r3, [r2]
	ldr	r3, [r8, #2696]
	ldr	r2, [r4, #696]
	str	r2, [r3, #796]
	ldr	r2, [r8, #2696]
	ldr	r3, [r2, #796]
	ldr	r1, [r2, #760]
	cmp	r3, r1
	movge	r3, r1
	str	r3, [r2, #36]
	ldr	r0, [r8, #2696]
	bl	MVC_CombineFldsToFrm
	ldr	r2, [r8, #2696]
	ldrb	r1, [r4, #11]	@ zero_extendqisi2
	movw	r3, #28410
	movt	r3, 42
	strb	r1, [r2, #13]
	ldrb	r1, [r4, #10]	@ zero_extendqisi2
	ldr	r2, [r8, #2696]
	strb	r1, [r2, #11]
	ldr	r2, [r8, #2696]
	ldr	r1, [r2, #52]
	ldr	r2, [r2, #792]
	add	r3, r1, r3
	add	r3, r6, r3, lsl #2
	str	r2, [r3, #4]
	b	.L3644
.L3624:
	ldr	r3, [fp, #-48]
	ldr	r2, [r4, #648]
	add	r3, r0, r3, lsl #2
	add	r10, r3, #11075584
	mov	r3, #3
	add	r5, r10, #45056
	str	r2, [r5, #2696]
	ldrb	r1, [r4, #2]	@ zero_extendqisi2
	strb	r1, [r2, #1]
	ldr	r2, [r5, #2696]
	strb	r3, [r2, #2]
	ldr	r1, [r4, #648]
	ldr	r2, [r5, #2696]
	ldrb	r1, [r1, #5]	@ zero_extendqisi2
	strb	r1, [r2, #5]
	ldr	r1, [r4, #648]
	ldr	r2, [r5, #2696]
	ldrb	r1, [r1, #7]	@ zero_extendqisi2
	strb	r1, [r2, #7]
	ldrb	r1, [r4, #4]	@ zero_extendqisi2
	ldr	r2, [r5, #2696]
	cmp	r1, #0
	beq	.L3720
.L3626:
	strb	r3, [r2, #3]
	add	r1, r4, #16
	ldr	r3, [r5, #2696]
	mov	r2, #632
	ldr	r0, [r4, #724]
	mov	r8, #0
	str	r0, [r3, #48]
	ldr	r0, [r5, #2696]
	add	r0, r0, #72
	bl	memcpy
	ldr	r1, [r5, #2696]
	ldr	ip, [r4, #700]
	add	r3, r10, #45056
	mov	lr, #1
	ldr	r10, .L3721
	mov	r2, r8
	mov	r0, r6
	str	ip, [r1, #728]
	str	ip, [r1, #44]
	ldr	r1, [r5, #2696]
	ldr	ip, [r4, #648]
	str	ip, [r1, #780]
	str	ip, [r1, #744]
	str	ip, [r1, #708]
	ldr	r1, [r5, #2696]
	ldr	ip, [r4, #660]
	str	ip, [r1, #28]
	ldr	r1, [r5, #2696]
	ldr	ip, [r4, #656]
	str	ip, [r1, #20]
	ldr	r1, [r5, #2696]
	strb	r8, [r1, #704]
	ldr	r1, [r5, #2696]
	ldrb	ip, [r4, #4]	@ zero_extendqisi2
	strb	ip, [r1, #705]
	ldr	r1, [r5, #2696]
	ldrb	ip, [r4, #5]	@ zero_extendqisi2
	strb	ip, [r1, #706]
	ldr	r1, [r5, #2696]
	ldrb	ip, [r4, #12]	@ zero_extendqisi2
	strb	ip, [r1, #707]
	strb	ip, [r1]
	ldr	r1, [r5, #2696]
	ldrb	ip, [r4, #9]	@ zero_extendqisi2
	str	ip, [r1, #40]
	ldr	r1, [r5, #2696]
	ldr	ip, [r4, #668]
	str	ip, [r1, #32]
	ldr	r1, [r5, #2696]
	ldr	ip, [r4, #672]
	str	ip, [r1, #720]
	ldr	r1, [r5, #2696]
	ldr	ip, [r4, #676]
	str	ip, [r1, #756]
	ldr	r1, [r5, #2696]
	ldr	ip, [r4, #680]
	str	ip, [r1, #792]
	ldr	r1, [r5, #2696]
	ldr	ip, [r4, #684]
	str	ip, [r1, #36]
	ldr	r1, [r5, #2696]
	ldr	ip, [r4, #688]
	str	ip, [r1, #724]
	ldr	r1, [r5, #2696]
	ldr	ip, [r4, #692]
	str	ip, [r1, #760]
	ldr	r1, [r5, #2696]
	ldr	ip, [r4, #696]
	str	ip, [r1, #796]
	ldrb	r1, [r4, #7]	@ zero_extendqisi2
	ldr	ip, [r5, #2696]
	cmp	r1, lr
	moveq	r7, #3
	strb	r7, [ip, #4]
	ldr	r1, [r3, #2696]
	ldr	ip, [r4, #728]
	str	ip, [r1, #56]
	ldr	r1, [r3, #2696]
	ldr	ip, [r4, #732]
	str	ip, [r1, #60]
	ldr	r1, [r3, #2696]
	ldrb	ip, [r4, #11]	@ zero_extendqisi2
	strb	ip, [r1, #13]
	strb	ip, [r1, #12]
	ldrb	r5, [r4, #10]	@ zero_extendqisi2
	ldr	ip, [r3, #2696]
	ldr	r1, [r10, #-1884]
	strb	r5, [ip, #11]
	add	r7, r1, lr
	strb	r5, [ip, #10]
	ldr	ip, [r3, #2696]
	str	r7, [r10, #-1884]
	str	r1, [ip, #64]
	ldr	r3, [r3, #2696]
	ldr	r1, [r3, #708]
	ldrb	r10, [r3, #705]	@ zero_extendqisi2
	ldrb	r7, [r3, #706]	@ zero_extendqisi2
	ldr	r5, [r3, #728]
	ldrb	ip, [r3, #707]	@ zero_extendqisi2
	strb	lr, [r3, #740]
	mov	lr, #2
	strb	r10, [r3, #741]
	strb	lr, [r3, #776]
	strb	r10, [r3, #777]
	strb	r7, [r3, #742]
	strb	r7, [r3, #778]
	str	r5, [r3, #764]
	str	r5, [r3, #800]
	strb	ip, [r3, #743]
	strb	ip, [r3, #779]
	str	r1, [r3, #744]
	str	r1, [r3, #780]
	ldr	r1, [r4, #648]
	bl	MVC_GetAPC
	cmp	r0, #0
	movne	r3, r0
	movwne	r2, #2174
	movne	r0, r8
	bne	.L3718
.L3644:
	ldr	r2, [fp, #-48]
	movw	r3, #28322
	movt	r3, 42
	add	r3, r2, r3
	ldr	r3, [r6, r3, asl #2]
	ldrb	r0, [r3, #3]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L3629
	ldr	r0, [r6, #120]
	mov	r2, #1
	ldrsb	r1, [r3, #6]
	bl	FSP_SetRef
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3623:
	ldr	r3, [r4, #648]
	mov	r2, #3
	strb	r2, [r3, #704]
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [fp, #-48]
	mov	r3, r3, asl #2
	beq	.L3630
	add	r8, r0, r3
	add	r2, r8, #11075584
	str	r2, [fp, #-52]
	add	r5, r2, #45056
	ldr	r2, [r5, #2696]
	cmp	r2, #0
	beq	.L3630
	strb	r7, [r2, #740]
	ldr	r3, [r5, #2696]
	ldrb	r2, [r4, #12]	@ zero_extendqisi2
	strb	r2, [r3, #743]
	ldr	r3, [r5, #2696]
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	strb	r2, [r3, #741]
	ldr	r3, [r5, #2696]
	ldrb	r2, [r4, #5]	@ zero_extendqisi2
	strb	r2, [r3, #742]
	ldr	r3, [r5, #2696]
	ldr	r2, [r4, #676]
	str	r2, [r3, #756]
	ldr	r3, [r5, #2696]
	ldrb	r2, [r4, #12]	@ zero_extendqisi2
	strb	r2, [r3, #743]
	ldr	r3, [r5, #2696]
	ldr	r2, [r4, #700]
	str	r2, [r3, #764]
	ldr	r3, [r5, #2696]
	ldr	r1, [r3, #764]
	ldr	r2, [r3, #800]
	add	r2, r2, r1
	str	r2, [r3, #728]
	str	r2, [r3, #44]
	add	r1, r4, #16
	ldr	r2, [r5, #2696]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	cmp	r3, #0
	ldrneb	r3, [r4, #2]	@ zero_extendqisi2
	strb	r3, [r2, #1]
	ldr	r2, [r5, #2696]
	ldrb	r3, [r2, #2]	@ zero_extendqisi2
	orr	r3, r3, #1
	strb	r3, [r2, #2]
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r5, #2696]
	ldrb	r2, [r3, #4]	@ zero_extendqisi2
	orreq	r2, r2, #1
	strb	r2, [r3, #4]
	mov	r2, #632
	ldr	r3, [r5, #2696]
	add	ip, r3, #672
	add	r0, r3, #72
	ldr	r10, [r3, #656]
	ldrd	r8, [ip, #-8]
	ldr	r7, [r3, #660]
	strd	r8, [fp, #-60]
	ldrd	r8, [ip]
	strd	r8, [fp, #-68]
	bl	memcpy
	add	r3, r4, #608
	and	r2, r10, r7
	adds	r2, r2, #1
	ldrd	r8, [fp, #-60]
	ldmdb	r3, {r0, r1}
	movne	r2, #1
	and	r1, r1, r0
	add	r0, r4, #624
	cmn	r1, #1
	movne	r2, #0
	cmp	r2, #0
	ldrne	r2, [r5, #2696]
	strne	r10, [r2, #656]
	strne	r7, [r2, #660]
	ldrd	r2, [r3]
	ldr	r1, [r5, #2696]
	cmp	r3, r9
	cmpeq	r2, r8
	add	r1, r1, #672
	movhi	r2, r8
	movhi	r3, r9
	ldrd	r8, [fp, #-68]
	strd	r2, [r1, #-8]
	ldrd	r2, [r0, #-8]
	ldr	r1, [r5, #2696]
	cmp	r3, r9
	cmpeq	r2, r8
	add	r1, r1, #672
	movhi	r3, r9
	movhi	r2, r8
	strd	r2, [r1]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3641
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3641
.L3642:
	ldr	r3, [fp, #-52]
	add	r8, r3, #45056
	ldr	r2, [r8, #2696]
	ldrb	r3, [r2, #779]	@ zero_extendqisi2
	ldrb	r1, [r2, #743]	@ zero_extendqisi2
	cmp	r3, r1
	movcc	r3, r1
	strb	r3, [r2]
	ldr	r3, [r8, #2696]
	ldr	r2, [r4, #692]
	str	r2, [r3, #760]
	ldr	r2, [r8, #2696]
	ldr	r3, [r2, #796]
	ldr	r1, [r2, #760]
	cmp	r3, r1
	movge	r3, r1
	str	r3, [r2, #36]
	ldr	r3, [r8, #2696]
	ldrb	r2, [r4, #11]	@ zero_extendqisi2
	strb	r2, [r3, #12]
	ldrb	r2, [r4, #10]	@ zero_extendqisi2
	ldr	r3, [r8, #2696]
	strb	r2, [r3, #10]
	ldr	r0, [r8, #2696]
	bl	MVC_CombineFldsToFrm
	ldr	r2, [r8, #2696]
	movw	r3, #28394
	movt	r3, 42
	ldr	r1, [r2, #52]
	ldr	r2, [r2, #756]
	add	r3, r1, r3
	add	r3, r6, r3, lsl #2
	str	r2, [r3, #4]
	b	.L3644
.L3630:
	add	r5, r6, r3
	ldr	r2, [r4, #648]
	add	r5, r5, #11075584
	mov	r1, #1
	add	r3, r5, #45056
	str	r2, [r3, #2696]
	strb	r1, [r2, #740]
	ldr	r2, [r3, #2696]
	ldr	r0, [r4, #648]
	str	r0, [r2, #744]
	ldr	r2, [r3, #2696]
	ldrb	r0, [r4, #4]	@ zero_extendqisi2
	strb	r0, [r2, #741]
	ldr	r2, [r3, #2696]
	ldrb	r0, [r4, #5]	@ zero_extendqisi2
	strb	r0, [r2, #742]
	ldr	r2, [r3, #2696]
	ldr	r0, [r4, #676]
	str	r0, [r2, #756]
	ldr	r2, [r3, #2696]
	ldrb	r0, [r4, #12]	@ zero_extendqisi2
	strb	r0, [r2, #743]
	ldr	r2, [r3, #2696]
	ldr	r0, [r4, #700]
	str	r0, [r2, #764]
	ldr	r2, [r3, #2696]
	ldr	r0, [r2, #764]
	str	r0, [r2, #728]
	str	r0, [r2, #44]
	ldr	r2, [r3, #2696]
	ldrb	r0, [r4, #2]	@ zero_extendqisi2
	strb	r0, [r2, #1]
	ldr	r2, [r3, #2696]
	strb	r1, [r2, #2]
	ldr	r1, [r4, #648]
	ldr	r2, [r3, #2696]
	ldrb	r1, [r1, #5]	@ zero_extendqisi2
	strb	r1, [r2, #5]
	ldr	r1, [r4, #648]
	ldr	r2, [r3, #2696]
	ldrb	r1, [r1, #7]	@ zero_extendqisi2
	strb	r1, [r2, #7]
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L3632
	ldrb	r2, [r4, #5]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L3632
.L3633:
	add	r5, r5, #45056
	mov	r7, #0
	mov	r2, #632
	add	r1, r4, #16
	ldr	r3, [r5, #2696]
	str	r7, [r3, #40]
	ldr	r0, [r5, #2696]
	add	r0, r0, #72
	bl	memcpy
	ldr	r1, [r5, #2696]
	ldr	ip, [r4, #724]
	mov	r2, #1
	ldr	r3, .L3721
	mov	r0, r6
	str	ip, [r1, #48]
	ldr	ip, [r5, #2696]
	ldr	lr, [r4, #656]
	ldr	r1, [r3, #-1884]
	str	lr, [ip, #20]
	add	ip, r1, r2
	ldr	lr, [r5, #2696]
	ldr	r8, [r4, #668]
	str	r8, [lr, #32]
	ldr	lr, [r5, #2696]
	ldr	r8, [r4, #684]
	str	r8, [lr, #36]
	ldr	lr, [r5, #2696]
	ldrb	r8, [r4, #12]	@ zero_extendqisi2
	strb	r8, [lr]
	ldr	lr, [r5, #2696]
	ldr	r8, [r4, #692]
	str	r8, [lr, #760]
	ldr	lr, [r5, #2696]
	ldr	r8, [r4, #728]
	str	r8, [lr, #56]
	ldr	lr, [r5, #2696]
	ldr	r8, [r4, #732]
	str	r8, [lr, #60]
	ldr	lr, [r5, #2696]
	ldrb	r8, [r4, #11]	@ zero_extendqisi2
	strb	r8, [lr, #12]
	ldr	lr, [r5, #2696]
	ldrb	r8, [r4, #10]	@ zero_extendqisi2
	strb	r8, [lr, #10]
	ldr	lr, [r5, #2696]
	str	r1, [lr, #64]
	str	ip, [r3, #-1884]
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	ldr	r1, [r5, #2696]
	rsb	r3, r2, r3
	clz	r3, r3
	mov	r3, r3, lsr #5
	strb	r3, [r1, #4]
	ldr	r1, [r4, #648]
	bl	MVC_GetAPC
	cmp	r0, #0
	beq	.L3644
	mov	r3, r0
	movw	r2, #2237
	mov	r0, r7
.L3718:
	ldr	r1, .L3721+8
	bl	dprint_vfmw
	mov	r0, r6
	mvn	r1, #0
	bl	MVC_ClearDPB
	mvn	r0, #0
	b	.L3629
.L3645:
	add	r5, r6, r3
	ldr	r2, [r4, #648]
	add	r5, r5, #11075584
	mov	r1, #2
	add	r3, r5, #45056
	str	r2, [r3, #2696]
	strb	r1, [r2, #776]
	ldr	r2, [r3, #2696]
	ldr	r0, [r4, #648]
	str	r0, [r2, #780]
	ldr	r2, [r3, #2696]
	ldrb	r0, [r4, #4]	@ zero_extendqisi2
	strb	r0, [r2, #777]
	ldr	r2, [r3, #2696]
	ldrb	r0, [r4, #5]	@ zero_extendqisi2
	strb	r0, [r2, #778]
	ldr	r2, [r3, #2696]
	ldr	r0, [r4, #680]
	str	r0, [r2, #792]
	ldr	r2, [r3, #2696]
	ldrb	r0, [r4, #12]	@ zero_extendqisi2
	strb	r0, [r2, #779]
	ldr	r2, [r3, #2696]
	ldr	r0, [r4, #700]
	str	r0, [r2, #800]
	ldr	r2, [r3, #2696]
	ldr	r0, [r2, #764]
	str	r0, [r2, #728]
	str	r0, [r2, #44]
	ldr	r2, [r3, #2696]
	ldrb	r0, [r4, #2]	@ zero_extendqisi2
	strb	r0, [r2, #1]
	ldr	r2, [r3, #2696]
	strb	r1, [r2, #2]
	ldr	r1, [r4, #648]
	ldr	r2, [r3, #2696]
	ldrb	r1, [r1, #5]	@ zero_extendqisi2
	strb	r1, [r2, #5]
	ldr	r1, [r4, #648]
	ldr	r2, [r3, #2696]
	ldrb	r1, [r1, #7]	@ zero_extendqisi2
	strb	r1, [r2, #7]
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L3647
	ldrb	r2, [r4, #5]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L3647
.L3648:
	add	r5, r5, #45056
	mov	r8, #0
	mov	r2, #632
	add	r1, r4, #16
	ldr	r3, [r5, #2696]
	str	r8, [r3, #40]
	ldr	r0, [r5, #2696]
	add	r0, r0, #72
	bl	memcpy
	ldr	r1, [r5, #2696]
	ldr	ip, [r4, #724]
	mov	r2, #2
	ldr	r3, .L3721
	mov	r0, r6
	str	ip, [r1, #48]
	ldr	ip, [r5, #2696]
	ldr	lr, [r4, #656]
	ldr	r1, [r3, #-1884]
	str	lr, [ip, #20]
	add	r7, r1, #1
	ldr	ip, [r5, #2696]
	ldr	lr, [r4, #668]
	str	lr, [ip, #32]
	ldr	ip, [r5, #2696]
	ldr	lr, [r4, #684]
	str	lr, [ip, #36]
	ldr	ip, [r5, #2696]
	ldrb	lr, [r4, #12]	@ zero_extendqisi2
	strb	lr, [ip, #779]
	strb	lr, [ip]
	ldr	ip, [r5, #2696]
	ldr	lr, [r4, #696]
	str	lr, [ip, #796]
	ldr	ip, [r5, #2696]
	ldr	lr, [r4, #728]
	str	lr, [ip, #56]
	ldr	ip, [r5, #2696]
	ldr	lr, [r4, #732]
	str	lr, [ip, #60]
	ldr	ip, [r5, #2696]
	ldrb	lr, [r4, #11]	@ zero_extendqisi2
	strb	lr, [ip, #13]
	ldr	ip, [r5, #2696]
	ldrb	lr, [r4, #10]	@ zero_extendqisi2
	strb	lr, [ip, #11]
	ldr	ip, [r5, #2696]
	str	r1, [ip, #64]
	ldrb	ip, [r4, #7]	@ zero_extendqisi2
	ldr	r1, [r5, #2696]
	cmp	ip, #1
	str	r7, [r3, #-1884]
	moveq	r7, r2
	movne	r7, r8
	strb	r7, [r1, #4]
	ldr	r1, [r4, #648]
	bl	MVC_GetAPC
	cmp	r0, #0
	movne	r3, r0
	movwne	r2, #2362
	movne	r0, r8
	beq	.L3644
	b	.L3718
.L3720:
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r3, #3
	b	.L3626
.L3647:
	ldr	r2, [r3, #2696]
	mov	r1, #2
	strb	r1, [r2, #3]
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	cmp	r2, #1
	ldreq	r3, [r3, #2696]
	ldreq	r2, [r4, #660]
	streq	r2, [r3, #28]
	b	.L3648
.L3632:
	ldr	r2, [r3, #2696]
	mov	r1, #1
	strb	r1, [r2, #3]
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	cmp	r2, r1
	ldreq	r3, [r3, #2696]
	ldreq	r2, [r4, #660]
	streq	r2, [r3, #28]
	b	.L3633
.L3641:
	ldr	r2, [r5, #2696]
	ldrb	r3, [r2, #3]	@ zero_extendqisi2
	orr	r3, r3, #1
	strb	r3, [r2, #3]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r3, [r5, #2696]
	ldreq	r2, [r4, #660]
	streq	r2, [r3, #28]
	b	.L3642
.L3657:
	ldr	r2, [r5, #2696]
	ldrb	r3, [r2, #3]	@ zero_extendqisi2
	orr	r3, r3, #2
	strb	r3, [r2, #3]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r3, [r5, #2696]
	ldreq	r2, [r4, #660]
	streq	r2, [r3, #28]
	b	.L3658
.L3722:
	.align	2
.L3721:
	.word	.LANCHOR3
	.word	.LC417
	.word	.LC416
	UNWIND(.fnend)
	.size	MVC_InsertFrmInDPB, .-MVC_InsertFrmInDPB
	.align	2
	.global	MVC_AllocFrameStore
	.type	MVC_AllocFrameStore, %function
MVC_AllocFrameStore:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	add	r9, r0, #11075584
	add	r7, r9, #40960
	mov	r6, r0
	str	r1, [fp, #-52]
	ldrb	r5, [r7, #1033]	@ zero_extendqisi2
	cmp	r5, #0
	beq	.L3724
	ldrb	r3, [r7, #1034]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r5, #2
	moveq	r5, #1
.L3724:
	ldr	r3, [fp, #-52]
	cmp	r3, #1
	ldrb	r3, [r6, #8]	@ zero_extendqisi2
	beq	.L3725
	cmp	r3, #2
	beq	.L3807
	add	r3, r6, #11141120
	str	r3, [fp, #-56]
	mov	r2, r3
	sub	r3, r5, #1
	add	r4, r2, #12288
	cmp	r3, #1
	mov	r3, #0
	strb	r3, [r4, #3129]
	bls	.L3808
.L3747:
	mov	r8, #0
	strb	r8, [r4, #3128]
	ldr	r10, [r6, #48]
	cmp	r10, r8
	beq	.L3754
	movw	ip, #48312
	add	r9, r9, #45056
	movt	ip, 169
	add	ip, r6, ip
	movw	r3, #47752
	movt	r3, 169
	add	r3, r6, r3
	str	r3, [fp, #-48]
.L3753:
	ldrb	r3, [ip, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3749
	cmp	ip, #0
	beq	.L3766
	ldr	lr, [r9, #2888]
	cmp	lr, #0
	beq	.L3766
	ldr	r2, [r9, #2696]
	rsb	r3, ip, r2
	cmp	r2, #0
	clz	r3, r3
	mov	r3, r3, lsr #5
	moveq	r3, #0
	cmp	r3, #0
	bne	.L3749
	ldr	r1, [fp, #-48]
	b	.L3751
.L3752:
	ldr	r2, [r1, #4]!
	rsb	r0, ip, r2
	cmp	r2, #0
	clz	r0, r0
	mov	r0, r0, lsr #5
	moveq	r0, #0
	cmp	r0, #0
	bne	.L3749
.L3751:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L3752
.L3766:
	mov	r3, #816
	movw	r2, #48352
	mla	r8, r3, r8, r6
	movt	r2, 169
	add	r0, r4, #3136
	mov	r9, #0
	mov	r3, #1
	str	ip, [r4, #3776]
	add	r2, r8, r2
	add	r1, r8, #11075584
	strb	r3, [r4, #3128]
	add	r1, r1, #48384
	str	r9, [r2, #4]
	add	r0, r0, #8
	mov	r2, #101
	str	r2, [r4, #3828]
	mov	r2, #632
	mov	r10, ip
	str	r3, [fp, #-48]
	bl	memcpy
	movw	r2, #48312
	str	r9, [r4, #3296]
	movt	r2, 169
	add	r2, r8, r2
	ldr	r3, [fp, #-48]
	strb	r9, [r2, #4]
	strb	r9, [r10, #7]
	ldr	r2, [r4, #3776]
	strb	r9, [r2, #3]
	ldr	r2, [r4, #3776]
	strb	r3, [r2, #5]
	ldr	r3, [r4, #3776]
	str	r9, [r3, #16]
	ldrb	r3, [r4, #3128]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L3754
	str	r3, [fp, #-48]
	ldr	r3, [fp, #-52]
	ldr	r0, [r6, #120]
	clz	r1, r3
	mov	r1, r1, lsr #5
	bl	FSP_NewLogicFs
	mov	r8, r0
	mov	r1, r0
	ldr	r0, [r6, #120]
	bl	FSP_GetLogicFs
	mvn	r2, r8
	mov	r2, r2, lsr #31
	ldr	r3, [fp, #-48]
	cmp	r0, #0
	mov	r10, r0
	moveq	r2, #0
	cmp	r2, #0
	beq	.L3755
	ldr	r3, [r6, #224]
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L3809
.L3756:
	ldr	r9, .L3816
	mov	r2, #632
	ldr	r0, [r4, #3776]
	add	r1, r10, #40
	ldr	r3, [r9, #52]
	add	r0, r0, #72
	blx	r3
	ldr	r1, [r4, #3776]
	movw	r0, #15432
	ldr	r3, [r9, #52]
	movt	r0, 170
	add	r1, r1, #72
	add	r0, r6, r0
	mov	r2, #632
	blx	r3
	ldr	r3, [r4, #3776]
	strb	r8, [r3, #6]
	ldrsb	r3, [r10, #4]
	str	r3, [r4, #3852]
.L3746:
	ldr	r3, [fp, #-52]
	uxtb	r2, r5
	strb	r2, [r4, #3131]
	cmp	r3, #1
	moveq	r0, #0
	beq	.L3800
	ldrb	r3, [r7, #1033]	@ zero_extendqisi2
	ldr	r1, [r4, #3776]
	cmp	r3, #0
	movne	r3, #3
	strb	r3, [r1, #704]
	ldrb	r3, [r4, #3129]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [fp, #-56]
	add	r3, r3, #16384
	beq	.L3810
	strb	r2, [r3, #504]
	cmp	r5, #0
	ldr	r2, [r7, #1060]
	movne	r0, #0
	moveq	r0, r5
	str	r2, [r3, #512]
	ldrb	r2, [r7, #1040]	@ zero_extendqisi2
	str	r2, [r3, #508]
	ldr	r2, [r6, #128]
	str	r2, [r3, #516]
	ldr	r2, [r7, #2672]
	str	r8, [r3, #520]
	streqb	r5, [r3, #505]
	str	r2, [r3, #528]
	movne	r2, #1
	strneb	r2, [r3, #505]
.L3800:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3749:
	add	r8, r8, #1
	add	ip, ip, #816
	cmp	r8, r10
	bne	.L3753
.L3754:
	ldr	r1, .L3816+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r6
	mov	r1, #1
	bl	MVC_ClearAll
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3807:
	add	r4, r6, #11141120
	str	r4, [fp, #-56]
	add	r4, r4, #12288
.L3744:
	mov	r3, #0
	strb	r3, [r4, #3129]
	b	.L3747
.L3725:
	cmp	r3, #2
	beq	.L3811
	add	r3, r6, #11141120
	str	r3, [fp, #-56]
	mov	r2, r3
	add	r4, r2, #12288
	mov	r3, #0
	mov	r5, r3
	strb	r3, [r4, #3129]
	b	.L3747
.L3809:
	ldr	r3, [r6, #16]
	ldr	r1, [r0, #152]
	ldr	r2, [r6, #12]
	mov	r3, r3, asl #4
	ldr	r0, [r0, #76]
	str	r3, [r10, #112]
	mul	r3, r1, r3
	mov	r2, r2, asl #4
	str	r2, [r10, #108]
	add	r0, r3, r0
	str	r0, [r10, #80]
	str	r3, [fp, #-48]
	bl	MEM_Phy2Vir
	ldr	r1, [r10, #60]
	ldr	r3, [fp, #-48]
	ldr	r2, [r10, #156]
	add	r3, r3, r1
	str	r9, [r10, #556]
	str	r3, [r10, #64]
	add	r3, r3, r2
	str	r3, [r10, #72]
	str	r0, [r10, #552]
	b	.L3756
.L3808:
	add	r3, r2, #16384
	ldrb	r2, [r3, #504]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L3728
	ldr	r0, [r3, #528]
	ldr	r1, [r7, #2672]
	cmp	r0, r1
	beq	.L3729
.L3728:
	add	r3, r9, #45056
	ldr	r1, [r3, #2888]
	subs	r3, r1, #1
	bmi	.L3747
	movw	r2, #28322
	movt	r2, 42
	add	r2, r1, r2
	add	r2, r6, r2, lsl #2
	b	.L3740
.L3731:
	cmp	r5, #2
	beq	.L3812
.L3730:
	subs	r3, r3, #1
	bmi	.L3747
.L3740:
	ldr	r8, [r2, #-4]!
	cmp	r8, #0
	beq	.L3730
	cmp	r5, #1
	bne	.L3731
	ldrb	r1, [r8, #2]	@ zero_extendqisi2
	cmp	r1, #2
	bne	.L3730
.L3732:
	ldr	r0, [r7, #1060]
	ldr	r1, [r8, #20]
	cmp	r0, r1
	bne	.L3730
	ldr	r0, [r7, #2672]
	ldr	r1, [r8, #56]
	cmp	r0, r1
	bne	.L3730
	ldrb	r1, [r7, #1040]	@ zero_extendqisi2
	cmp	r1, #0
	ldrb	r1, [r8, #3]	@ zero_extendqisi2
	beq	.L3813
	cmp	r1, #0
	beq	.L3730
.L3736:
	add	r0, r4, #3136
	mov	r3, #1
	mov	r2, #632
	strb	r3, [r4, #3129]
	add	r1, r8, #72
	str	r8, [r4, #3776]
	add	r0, r0, #8
	bl	memcpy
	ldrsb	r1, [r8, #6]
	ldr	r0, [r6, #120]
	bl	FSP_GetLogicFs
	subs	r3, r0, #0
	beq	.L3814
	ldrb	r2, [r4, #3129]	@ zero_extendqisi2
	ldrsb	r3, [r3, #4]
	cmp	r2, #0
	str	r3, [r4, #3852]
	beq	.L3747
	ldr	r3, [r4, #3776]
	cmp	r3, #0
	beq	.L3747
.L3804:
	mov	r8, #0
	b	.L3746
.L3812:
	ldrb	r1, [r8, #2]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L3730
	b	.L3732
.L3810:
	mov	r2, #0
	strb	r2, [r3, #504]
	ldr	r1, [r7, #1060]
	mov	r0, r2
	str	r1, [r3, #512]
	ldrb	r1, [r7, #1040]	@ zero_extendqisi2
	str	r1, [r3, #508]
	ldr	r1, [r6, #128]
	str	r8, [r3, #520]
	strb	r2, [r3, #505]
	str	r1, [r3, #516]
	ldr	r2, [r7, #2672]
	str	r2, [r3, #528]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3811:
	add	r4, r6, #11141120
	mov	r5, #0
	str	r4, [fp, #-56]
	add	r4, r4, #12288
	b	.L3744
.L3813:
	cmp	r1, #0
	bne	.L3730
	b	.L3736
.L3729:
	sub	r8, r5, #2
	cmp	r2, #1
	cmpeq	r5, #2
	clz	r8, r8
	mov	r8, r8, lsr #5
	beq	.L3741
	cmp	r5, #1
	cmpeq	r2, #2
	bne	.L3747
.L3741:
	ldr	r1, [r3, #512]
	ldr	r2, [r7, #1060]
	cmp	r1, r2
	bne	.L3747
	ldrb	r2, [r7, #1040]	@ zero_extendqisi2
	ldr	r3, [r3, #508]
	cmp	r2, #0
	bne	.L3742
	cmp	r3, #0
	bne	.L3747
.L3743:
	ldr	r3, [r6, #128]
	ldr	r2, [r6, #124]
	rsb	r3, r2, r3
	cmp	r3, #2
	bhi	.L3747
	ldr	r3, [r4, #3776]
	mov	r2, #1
	strb	r2, [r4, #3129]
	cmp	r3, #0
	beq	.L3744
	cmp	r8, #0
	bne	.L3815
	cmp	r5, #1
	bne	.L3746
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L3744
	b	.L3746
.L3755:
	ldr	ip, [r4, #3776]
	mov	r0, r2
	strb	r2, [r4, #3128]
	ldr	r1, .L3816+8
	strb	r2, [ip, #5]
	str	r3, [fp, #-48]
	bl	dprint_vfmw
	ldr	r3, [fp, #-48]
	mov	r0, r6
	mov	r1, r3
	bl	MVC_ClearAll
	mvn	r0, #0
	b	.L3800
.L3814:
	movw	r2, #6560
	ldr	r1, .L3816+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3800
.L3815:
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	cmp	r3, r2
	bne	.L3744
	b	.L3804
.L3742:
	cmp	r3, #0
	beq	.L3747
	b	.L3743
.L3817:
	.align	2
.L3816:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC419
	.word	.LC420
	.word	.LC418
	UNWIND(.fnend)
	.size	MVC_AllocFrameStore, .-MVC_AllocFrameStore
	.align	2
	.global	MVC_DEC_Init
	.type	MVC_DEC_Init, %function
MVC_DEC_Init:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r8, .L3830
	movw	r2, #18672
	ldr	r4, [r0, #928]
	mov	r6, r0
	mov	r5, r1
	movt	r2, 170
	mov	r1, #0
	ldr	r3, [r8, #48]
	blx	r3
	str	r4, [r6, #928]
	add	r0, r6, #584
	mov	r4, #2240
	bl	ResetVoQueue
	str	r5, [r6, #224]
	mov	r3, #0
	str	r3, [r6, #228]
	strb	r3, [r6]
	ldr	r3, [r5, #28]
	cmp	r3, #25
	ldreq	r3, [r5, #700]
	movne	r3, #32
	movne	r2, #256
	strne	r3, [r6, #36]
	movne	r3, #136
	streq	r3, [r6, #36]
	ldreq	r3, [r5, #704]
	streq	r3, [r6, #40]
	ldreq	r3, [r5, #692]
	str	r3, [r6, #32]
	strne	r2, [r6, #40]
	ldr	r0, [r5, #584]
	bl	MEM_Phy2Vir
	ldr	ip, [r6, #36]
	ldr	r3, [r6, #224]
	movw	r2, #3992
	ldr	lr, [r6, #40]
	mul	r2, r2, ip
	ldr	r3, [r3, #580]
	add	r3, r0, r3
	str	r3, [r6, #248]
	add	r0, r3, r2
	str	r0, [r6, #252]
	cmp	r3, #0
	cmpne	r0, #0
	mla	r0, r4, lr, r0
	moveq	r1, #1
	movne	r1, #0
	cmp	r0, #0
	orreq	r1, r1, #1
	cmp	r1, #0
	str	r0, [r6, #544]
	bne	.L3827
	ldr	r5, [r5, #616]
	cmp	r5, #0
	beq	.L3828
.L3823:
	add	r3, r6, #11075584
	movw	r2, #4060
	add	r1, r3, #36864
	add	r3, r3, #32768
	ldr	r9, [r8, #48]
	add	r4, r6, #12992
	str	lr, [r1, #1776]
	mov	r1, #0
	str	ip, [r3, #2600]
	mov	r5, r1
	ldr	r3, [r6, #32]
	add	r4, r4, #12
	movw	r7, #22860
	movt	r7, 164
	add	r7, r6, r7
	mul	r2, r2, r3
	blx	r9
	ldr	r3, [r6, #108]
	mov	r2, #9856
	mov	ip, #40
	strb	r5, [r6, #4]
	ubfx	r3, r3, #16, #2
	str	ip, [r6, #48]
	mov	r1, r5
	strb	r3, [r6, #8]
	movt	r2, 164
	strb	r5, [r6, #6]
	mov	r3, #18
	strb	r5, [r6, #7]
	mov	r0, r4
	str	r3, [r6, #52]
	str	r5, [r6, #68]
	ldr	r3, [r8, #48]
	str	r5, [r6, #72]
	str	r5, [r6, #76]
	str	r5, [r6, #80]
	str	r5, [r6, #84]
	str	r5, [r6, #88]
	str	r5, [r6, #92]
	str	r5, [r6, #96]
	str	r5, [r6, #60]
	str	r5, [r6, #528]
	str	r5, [r6, #532]
	str	r5, [r6, #536]
	str	r5, [r6, #540]
	str	r5, [r6, #220]
	str	r5, [r6, #56]
	blx	r3
	movw	r2, #8500
	ldr	r3, [r8, #48]
	movt	r2, 5
	mov	r0, r7
	mov	r1, r5
	blx	r3
	mov	r3, r4
	mov	r2, r5
.L3824:
	strb	r2, [r3]
	add	ip, r3, #274432
	add	r3, r3, #335872
	mov	r4, #0
	add	r3, r3, #308
	strb	r2, [ip, #241]
	cmp	r3, r7
	bne	.L3824
	add	r2, r6, #12288
	movw	r3, #34624
	mov	r1, #32
	movt	r3, 169
	strb	r4, [r2, #704]
	add	r3, r6, r3
	mov	r0, r6
	str	r3, [r6, #236]
	str	r4, [r6, #20]
	strb	r4, [r6, #2]
	str	r1, [r6, #24]
	str	r1, [r6, #28]
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r6, #120]
	beq	.L3829
	mov	r1, r4
	mov	r0, r6
	bl	MVC_ClearAll
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3828:
	mov	r0, r3
	mov	r1, r5
	ldr	r3, [r8, #48]
	blx	r3
	ldr	r2, [r6, #40]
	mov	r1, r5
	ldr	r3, [r8, #48]
	ldr	r0, [r6, #252]
	mul	r2, r4, r2
	blx	r3
	ldr	lr, [r6, #40]
	ldr	ip, [r6, #36]
	ldr	r0, [r6, #544]
	b	.L3823
.L3827:
	movw	r3, #13812
	ldr	r2, .L3830+4
	ldr	r1, .L3830+8
	mov	r0, #22
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3829:
	mov	r0, r4
	ldr	r1, .L3830+12
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3831:
	.align	2
.L3830:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+332
	.word	.LC421
	.word	.LC422
	UNWIND(.fnend)
	.size	MVC_DEC_Init, .-MVC_DEC_Init
	.align	2
	.global	MVC_StorePicInDpb
	.type	MVC_StorePicInDpb, %function
MVC_StorePicInDpb:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	add	r4, r0, #11075584
	add	r7, r0, #11141120
	add	r2, r4, #36864
	add	r6, r7, #12288
	mov	r8, #0
	strb	r8, [r2, #3992]
	mov	r5, r0
	ldrb	r3, [r6, #3131]	@ zero_extendqisi2
	sub	r3, r3, #2
	clz	r3, r3
	mov	r3, r3, lsr #5
	strb	r3, [r2, #3993]
	ldrb	r3, [r6, #3128]	@ zero_extendqisi2
	cmp	r3, r8
	beq	.L4000
	ldr	r3, [r0, #128]
	str	r3, [r0, #124]
	ldrb	r3, [r6, #3141]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3835
	ldr	r3, [r6, #3780]
	ldrb	r9, [r3, #1]	@ zero_extendqisi2
	cmp	r9, #0
	beq	.L3836
	bl	MVC_InitDPB
	cmp	r0, #0
	bne	.L4001
.L3835:
	ldrb	r0, [r5, #8]	@ zero_extendqisi2
	cmp	r0, #2
	beq	.L4002
	ldr	r9, [r5, #224]
	ldr	r3, [r9, #24]
	cmp	r3, #0
	bne	.L3840
	ldr	r2, [r5, #220]
	cmp	r2, #2
	beq	.L3842
	ldrb	r2, [r6, #3130]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3842
.L3912:
	ldrb	r1, [r6, #3131]	@ zero_extendqisi2
	ldr	r8, [r6, #3776]
	sub	r2, r1, #1
	cmp	r2, #1
	movhi	r2, #0
	movls	r2, #1
	cmp	r1, #0
	beq	.L3844
	ldrb	r0, [r8, #2]	@ zero_extendqisi2
	cmp	r0, #0
	moveq	ip, r2
	orrne	ip, r2, #1
	cmp	ip, #0
	beq	.L3843
	cmp	r2, #0
	beq	.L4003
.L3917:
	ldr	r2, [r5, #220]
	cmp	r2, #0
	bne	.L3847
	add	r1, r6, #3120
	add	r0, r6, #3856
	mov	r3, #1
	add	r1, r1, #8
	str	r3, [r5, #220]
	add	r0, r0, #8
	mov	r2, #736
	bl	memcpy
	ldr	r3, [r9, #24]
.L3843:
	cmp	r3, #2
	beq	.L4004
.L3842:
	ldr	r3, [r6, #3792]
	cmp	r3, #0
	beq	.L3874
	ldr	r3, [r5, #112]
	ldr	r2, [r6, #3828]
	cmp	r3, r2
	bcs	.L3875
	ldrb	r1, [r6, #3130]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L4005
.L3875:
	mov	r0, r5
	bl	MVC_Marking
	cmp	r0, #0
	bne	.L4006
	mov	r0, r5
	bl	MVC_UpdateReflist
	mov	r0, r5
	bl	MVC_UpdateLTReflist
	ldr	r1, [r6, #3856]
	mov	r0, r5
	bl	MVC_RemoveUnUsedFrameStore
.L3868:
	ldrb	r3, [r6, #3129]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3878
	add	r4, r4, #45056
	ldr	ip, [r4, #2888]
.L3879:
	ldr	r3, [r6, #3792]
	cmp	r3, #0
	beq	.L3888
	ldr	r2, [r4, #2896]
	ldr	r3, [r4, #2900]
	add	r1, r3, r2
	cmp	r1, ip
	bcs	.L3914
.L3888:
	mvn	r9, #0
	mov	r8, r9
	b	.L3897
.L3892:
	ldr	r3, [r6, #3792]
	mov	r1, r8
	mov	r0, r5
	mov	r9, r2
	cmp	r3, #0
	bne	.L3893
	ldr	r2, [r6, #3796]
	ldr	r3, [fp, #-56]
	cmp	r2, r3
	blt	.L4007
.L3893:
	bl	MVC_OutputFrmFromDPB
	cmn	r0, #1
	mov	r10, r0
	beq	.L3896
	ldr	ip, [r4, #2888]
.L3897:
	ldr	lr, [r4, #2892]
	sub	r3, fp, #52
	sub	r2, fp, #56
	mvn	r1, #0
	cmp	lr, ip
	mov	r0, r5
	bcc	.L3890
	bl	MVC_GetMinPOC
	cmp	r0, #0
	blt	.L4008
	ldr	r2, [r4, #2892]
	cmp	r2, r9
	ldrne	r8, [fp, #-52]
	bne	.L3892
	ldr	r3, [fp, #-52]
	cmp	r3, r8
	beq	.L4009
	mov	r8, r3
	b	.L3892
.L3840:
	ldrb	r2, [r6, #3130]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3843
	b	.L3912
.L3874:
	ldrb	r3, [r6, #3129]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3878
	add	r4, r4, #45056
	ldr	ip, [r4, #2888]
	b	.L3888
.L4004:
	ldr	r3, [r6, #3792]
	cmp	r3, #0
	beq	.L3868
	add	r4, r4, #45056
	mov	r0, r5
	bl	MVC_SimpleSlideDPB
	ldr	r1, [r4, #2888]
	cmp	r1, #0
	beq	.L3869
	ldr	r3, [r4, #2696]
	cmp	r3, #0
	beq	.L3922
	movw	r2, #47752
	mov	r3, #0
	movt	r2, 169
	add	r2, r5, r2
	b	.L3870
.L3871:
	ldr	r0, [r2, #4]!
	cmp	r0, #0
	beq	.L3922
.L3870:
	add	r3, r3, #1
	cmp	r3, r1
	bne	.L3871
.L3869:
	movw	r2, #15416
	mov	r0, r5
	movt	r2, 170
	add	r2, r5, r2
	bl	MVC_InsertFrmInDPB
	subs	r8, r0, #0
	bne	.L4010
	ldr	r1, [r4, #2892]
	mov	r0, r5
	add	r1, r1, #1
	str	r1, [r4, #2892]
	bl	MVC_UpdateReflist
	mov	r0, r5
	bl	MVC_UpdateLTReflist
	mov	r2, r8
	movw	r3, #3742
	ldr	r1, .L4023
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3873
.L3844:
	cmp	r2, #0
	bne	.L3917
.L3850:
	cmp	r3, #0
	beq	.L3920
	movw	r3, #15416
	mov	r9, r8
	movt	r3, 170
	add	r3, r5, r3
.L3853:
	cmp	r1, #0
	bne	.L4011
.L3855:
	ldr	r2, [r3, #700]
	str	r2, [r9, #44]
.L3856:
	mov	r1, r9
	mov	r0, r5
	str	r3, [fp, #-64]
	bl	MVC_GetImagePara
	ldrsb	r1, [r9, #6]
	ldr	r0, [r5, #120]
	bl	FSP_GetFsImagePtr
	ldr	r3, [fp, #-64]
	subs	r10, r0, #0
	beq	.L4012
	add	lr, r3, #608
	add	r1, r3, #624
	add	r0, r10, #592
	add	ip, r10, #608
	ldrd	r2, [lr, #-8]
	strd	r2, [r0, #-8]
	ldrd	r2, [lr]
	strd	r2, [r0]
	ldrd	r2, [r1, #-8]
	strd	r2, [ip, #-8]
	ldr	r2, [r9, #44]
	cmp	r2, #0
	str	r2, [r10, #152]
	bne	.L3858
.L3863:
	mov	r2, #1
	ldrsb	r1, [r9, #6]
	ldr	r0, [r5, #120]
	bl	FSP_SetDisplay
	ldr	r0, [r5, #120]
	add	r3, r5, #584
	str	r10, [sp]
	mov	r2, r5
	mov	r1, #15
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L3860
	mov	r2, #0
	ldrsb	r1, [r9, #6]
	ldr	r0, [r5, #120]
	bl	FSP_SetDisplay
.L3860:
	ldr	r3, [r5, #224]
	ldr	r3, [r3, #612]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r10, #16]
	bcs	.L4013
.L3866:
	ldr	r3, [r5, #136]
	add	r3, r3, #2
	str	r3, [r5, #136]
.L3854:
	ldr	r3, [r5, #220]
	cmp	r3, #2
	beq	.L3867
.L3852:
	mov	r3, #1
	str	r3, [r9, #16]
	strb	r3, [r8, #8]
.L3867:
	ldr	r3, [r5, #224]
	mov	r2, #2
	str	r2, [r5, #220]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	bne	.L3842
	b	.L4004
.L3878:
	ldr	r3, [r5, #520]
	ldr	lr, [r6, #3776]
	cmp	r3, #0
	rsb	r2, r3, lr
	clz	r2, r2
	mov	r2, r2, lsr #5
	moveq	r2, #0
	cmp	r2, #0
	beq	.L4014
	mov	r0, r5
	bl	MVC_DirectOutput
	cmn	r0, #1
	mov	r4, r0
	beq	.L4015
.L3884:
	movw	r3, #3794
	mov	r2, r4
	ldr	r1, .L4023
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3839
.L4008:
	ldr	r1, .L4023+4
	movw	r2, #3844
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r1, #0
	mov	r0, r5
	bl	MVC_ClearDPB
.L3890:
	ldr	r3, [r6, #3792]
	cmp	r3, #0
	beq	.L3902
	ldrb	r3, [r6, #3132]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3902
	ldr	r2, [r4, #2896]
	cmp	r2, #0
	beq	.L3902
	movw	ip, #47812
	mov	lr, r3
	movt	ip, 169
	add	ip, r5, ip
	b	.L3907
.L3904:
	ldr	r2, [r4, #2896]
	cmp	r2, r3
	bls	.L3902
.L3907:
	ldr	r2, [ip, #4]!
	add	r3, r3, #1
	ldr	r1, [r6, #3784]
	ldr	r0, [r2, #20]
	cmp	r0, r1
	bne	.L3904
	ldr	r0, [r2, #56]
	ldr	r1, [r6, #3856]
	cmp	r0, r1
	bne	.L3904
	strb	lr, [r2, #3]
	ldr	r1, [ip]
	ldrb	r2, [r1, #5]	@ zero_extendqisi2
	cmp	r2, #1
	streqb	r2, [r1, #7]
	ldreq	r2, [ip]
	streqb	lr, [r2, #5]
	ldreq	r1, [ip]
	ldr	r0, [r5, #52]
	ldr	r2, [r1, #48]
	cmp	r2, r0
	add	r2, r5, r2, lsl #2
	strne	lr, [r2, #148]
	strne	r0, [r1, #48]
	b	.L3904
.L3902:
	ldr	r1, [r4, #2888]
	cmp	r1, #0
	beq	.L3901
	ldr	r3, [r4, #2696]
	cmp	r3, #0
	beq	.L3926
	movw	r2, #47752
	mov	r3, #0
	movt	r2, 169
	add	r2, r5, r2
	b	.L3908
.L3909:
	ldr	r0, [r2, #4]!
	cmp	r0, #0
	beq	.L3926
.L3908:
	add	r3, r3, #1
	cmp	r3, r1
	bne	.L3909
.L3901:
	movw	r2, #15416
	mov	r0, r5
	movt	r2, 170
	add	r2, r5, r2
	bl	MVC_InsertFrmInDPB
	cmp	r0, #0
	bne	.L4016
	ldr	r3, [r4, #2892]
	mov	r0, r5
	add	r3, r3, #1
	str	r3, [r4, #2892]
	bl	MVC_UpdateReflist
	mov	r0, r5
	bl	MVC_UpdateLTReflist
.L3873:
	mov	r4, #0
.L3911:
	add	r7, r7, #12288
	mov	r3, #0
	mov	r0, r4
	strb	r3, [r7, #3128]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3836:
	mvn	r1, #0
	bl	MVC_FlushDPB
	cmp	r0, #0
	beq	.L3835
	mov	r0, r9
	ldr	r1, .L4023+8
	bl	dprint_vfmw
	movw	r3, #3571
	mvn	r2, #0
	ldr	r1, .L4023
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3916
.L4014:
	add	r4, r4, #45056
	ldr	ip, [r4, #2888]
	cmp	ip, #0
	beq	.L3881
	ldr	r3, [r4, #2696]
	adds	r1, r3, #0
	movne	r1, #1
	cmp	lr, r3
	movne	r1, #0
	cmp	r1, #0
	movweq	r2, #47752
	movteq	r2, 169
	addeq	r2, r5, r2
	bne	.L4017
.L3885:
	add	r1, r1, #1
	cmp	r1, ip
	beq	.L3879
	ldr	r3, [r2, #4]!
	adds	r0, r3, #0
	movne	r0, #1
	cmp	lr, r3
	movne	r0, #0
	cmp	r0, #0
	beq	.L3885
.L3882:
	movw	r2, #15416
	mov	r0, r5
	movt	r2, 170
	add	r2, r5, r2
	bl	MVC_InsertFrmInDPB
	cmn	r0, #1
	mov	r4, r0
	beq	.L4018
	mov	r0, r5
	bl	MVC_UpdateReflist
	mov	r0, r5
	bl	MVC_UpdateLTReflist
	movw	r3, #3820
	mov	r2, #0
	ldr	r1, .L4023
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3873
.L4003:
	cmp	r0, #0
	beq	.L3843
	b	.L3850
.L3926:
	mov	r1, r3
	b	.L3901
.L3896:
	mov	r3, r0
	movw	r2, #3884
	ldr	r1, .L4023+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r2, r10
	movw	r3, #3885
	ldr	r1, .L4023
	mov	r0, #14
	bl	dprint_vfmw
.L3916:
	ldr	r3, [r6, #3776]
	mov	r2, #1
	ldr	r0, [r5, #120]
	mvn	r4, #0
	ldrsb	r1, [r3, #6]
	bl	FSP_ClearLogicFs
	mov	r3, r4
	movw	r2, #3943
	ldr	r1, .L4023+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r6, #3776]
	mov	r3, #0
	strb	r3, [r2, #5]
	ldr	r2, [r6, #3776]
	strb	r3, [r2, #2]
	b	.L3911
.L4002:
	ldr	r1, .L4023+16
	bl	dprint_vfmw
	mov	r0, r5
	bl	MVC_DirectOutput
	ldr	r3, [r6, #3852]
	ldr	r2, [r5, #52]
	cmp	r3, r2
	addne	r3, r3, #36
	movne	r1, #0
	addne	r3, r5, r3, lsl #2
	mov	r4, r0
	strne	r1, [r3, #4]
	strne	r2, [r6, #3852]
	movw	r3, #3590
	mov	r2, r0
	ldr	r1, .L4023
	mov	r0, #14
	bl	dprint_vfmw
.L3839:
	cmn	r4, #1
	bne	.L3911
	b	.L3916
.L3847:
	cmp	r2, #1
	beq	.L4019
	cmp	r1, #0
	beq	.L3850
	ldrb	r2, [r8, #2]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3850
	b	.L3843
.L4007:
	ldrb	r3, [r5, #8]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L4020
.L3894:
	mov	r0, r5
	bl	MVC_DirectOutput
	cmn	r0, #1
	mov	r4, r0
	beq	.L4021
.L3895:
	movw	r3, #3876
	mov	r2, r4
	ldr	r1, .L4023
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3839
.L3920:
	mov	r9, r8
	b	.L3854
.L4011:
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L3855
	mov	r1, #3
	ldr	r2, [r9, #44]
	strb	r1, [r9, #2]
	ldr	r1, [r3, #700]
	add	r2, r2, r1
	str	r2, [r9, #44]
	b	.L3856
.L3858:
	ldrb	r3, [r10, #64]	@ zero_extendqisi2
	ands	r3, r3, #3
	beq	.L4022
.L3861:
	ldr	r3, [r5, #224]
	ldr	r3, [r3, #4]
	cmp	r3, r2
	bcs	.L3863
	ldrsb	r1, [r9, #6]
	mov	r2, #0
	ldr	r0, [r5, #120]
	bl	FSP_SetDisplay
	movw	r3, #3690
	mvn	r2, #0
	ldr	r1, .L4023
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3916
.L4001:
	mov	r0, r8
	ldr	r1, .L4023+20
	bl	dprint_vfmw
	movw	r3, #3561
	mvn	r2, #0
	ldr	r1, .L4023
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3916
.L4009:
	mov	r3, r8
	ldr	r2, .L4023+24
	ldr	r1, .L4023+28
	mov	r0, #1
	bl	dprint_vfmw
	movw	r3, #3853
	mvn	r2, #0
	ldr	r1, .L4023
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3916
.L3922:
	mov	r1, r3
	b	.L3869
.L4020:
	ldrb	r3, [r6, #3131]	@ zero_extendqisi2
	cmp	r3, #0
	ldrne	r3, [r6, #3776]
	strne	r3, [r5, #524]
	b	.L3894
.L4019:
	cmp	r3, #0
	add	r3, r7, #16384
	ldr	r9, [r3, #416]
	beq	.L3852
	movw	r3, #16152
	ldrb	r1, [r6, #3867]	@ zero_extendqisi2
	movt	r3, 170
	add	r3, r5, r3
	b	.L3853
.L4013:
	mov	r1, r10
	mov	r0, r5
	bl	MVC_SetFrmRepeatCount.part.2
	b	.L3866
.L4000:
	mov	r0, r3
	ldr	r1, .L4023+32
	bl	dprint_vfmw
	movw	r3, #3547
	mvn	r2, #0
	ldr	r1, .L4023
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3916
.L4021:
	mov	r3, r0
	movw	r2, #3873
	ldr	r1, .L4023+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3895
.L4006:
	mov	r2, r0
	ldr	r1, .L4023+36
	mov	r0, #1
	bl	dprint_vfmw
	movw	r3, #3767
	mvn	r2, #0
	ldr	r1, .L4023
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3916
.L4022:
	movw	r2, #3671
	ldr	r1, .L4023+40
	mov	r0, #1
	str	r3, [fp, #-64]
	bl	dprint_vfmw
	ldr	r2, .L4023+44
	ldr	ip, [r2]
	cmp	ip, #0
	beq	.L3862
	ldr	r3, [fp, #-64]
	mov	r1, #111
	ldr	r0, [r5, #120]
	mov	r2, r3
	blx	ip
.L3862:
	ldr	r2, [r10, #152]
	cmp	r2, #0
	bne	.L3861
	b	.L3863
.L4016:
	mov	r3, r0
	movw	r2, #3929
	ldr	r1, .L4023+12
	mov	r0, #1
	bl	dprint_vfmw
	movw	r3, #3930
	mvn	r2, #0
	ldr	r1, .L4023
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3916
.L4017:
	mov	r1, r2
	b	.L3882
.L3881:
	ldr	r3, [r6, #3792]
	cmp	r3, #0
	beq	.L3888
	ldr	r2, [r4, #2896]
	ldr	r3, [r4, #2900]
.L3914:
	str	r3, [sp, #4]
	mov	r0, #1
	mov	r3, ip
	str	r2, [sp]
	ldr	r1, .L4023+48
	movw	r2, #3833
	bl	dprint_vfmw
	mvn	r1, #0
	mov	r0, r5
	bl	MVC_ClearDPB
	movw	r3, #3836
	mvn	r2, #0
	ldr	r1, .L4023
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3916
.L4005:
	ldr	r1, .L4023+52
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L4023+44
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3876
	ldr	r4, [r6, #3828]
	mov	r3, #8
	ldr	lr, [r5, #112]
	sub	r2, fp, #52
	mov	r1, #104
	ldr	r0, [r5, #120]
	str	r4, [fp, #-52]
	str	lr, [fp, #-48]
	blx	ip
.L3876:
	mov	r0, r5
	bl	MVC_ClearCurrPic
	mvn	r1, #0
	mov	r0, r5
	bl	MVC_ClearDPB
	movw	r3, #3758
	mvn	r2, #0
	ldr	r1, .L4023
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3916
.L4015:
	mov	r3, r0
	movw	r2, #3790
	ldr	r1, .L4023+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3884
.L4010:
	mov	r3, r8
	movw	r2, #3733
	ldr	r1, .L4023+12
	mov	r0, #0
	bl	dprint_vfmw
	movw	r3, #3734
	mvn	r2, #0
	ldr	r1, .L4023
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3916
.L4018:
	mov	r3, r0
	movw	r2, #3813
	ldr	r1, .L4023+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r2, r4
	movw	r3, #3814
	ldr	r1, .L4023
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3916
.L4012:
	movw	r3, #3660
	mvn	r2, #0
	ldr	r1, .L4023
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3916
.L4024:
	.align	2
.L4023:
	.word	.LC424
	.word	.LC433
	.word	.LC426
	.word	.LC429
	.word	.LC427
	.word	.LC425
	.word	.LANCHOR0+348
	.word	.LC434
	.word	.LC423
	.word	.LC431
	.word	.LC428
	.word	g_event_report
	.word	.LC432
	.word	.LC430
	UNWIND(.fnend)
	.size	MVC_StorePicInDpb, .-MVC_StorePicInDpb
	.global	__aeabi_idivmod
	.align	2
	.global	MVC_DecGap
	.type	MVC_DecGap, %function
MVC_DecGap:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #44)
	sub	sp, sp, #44
	ldrb	r1, [r0, #3]	@ zero_extendqisi2
	add	r3, r0, #11075584
	movw	lr, #2004
	add	r7, r3, #40960
	mov	r5, r0
	mul	lr, lr, r1
	ldr	r2, [r7, #2676]
	ldr	r1, [r0, #236]
	add	r0, r0, #11141120
	mov	ip, r3
	str	r3, [fp, #-80]
	movw	r3, #26886
	mov	r4, r0
	movt	r3, 42
	str	r0, [fp, #-76]
	add	r3, r2, r3
	add	r0, r5, lr
	movw	r2, #43696
	add	r8, ip, #36864
	movt	r2, 169
	add	r2, r0, r2
	ldrb	r0, [r1, #19]	@ zero_extendqisi2
	add	r6, r5, r3, lsl #2
	ldrb	r2, [r2, #3]	@ zero_extendqisi2
	movw	r3, #43696
	cmp	r0, #1
	add	r4, r4, #12288
	add	ip, ip, #45056
	movt	r3, 169
	str	r2, [fp, #-72]
	add	r3, lr, r3
	ldr	r2, [r7, #1060]
	add	r3, r5, r3
	ldr	lr, [r6, #4]
	str	r2, [fp, #-52]
	ldr	r2, [r8, #4032]
	str	r2, [fp, #-64]
	moveq	r2, #2
	movne	r2, #0
	str	r2, [fp, #-56]
	ldr	r2, [r8, #4036]
	str	r2, [fp, #-68]
	ldr	r2, [r1, #2896]
	str	r3, [r4, #3780]
	ldr	r6, [ip, #2892]
	cmp	r6, #0
	beq	.L4040
	add	r2, r2, #4
	mov	r6, #1
	mov	r3, r6, asl r2
	add	r0, lr, r6
	str	r3, [fp, #-60]
	mov	r1, r3
	bl	__aeabi_uidivmod
	mov	r3, #0
	mov	r0, #2
	str	r3, [r8, #4036]
	str	r3, [r8, #4032]
	mov	r10, r1
	ldr	r1, .L4043
	bl	dprint_vfmw
	ldr	r9, [fp, #-52]
	mov	r3, r10
	ldr	r1, .L4043+4
	mov	r0, #2
	mov	r2, r9
	bl	dprint_vfmw
	cmp	r9, r10
	mov	r3, r9
	movgt	r3, r4
	movgt	r4, r10
	movgt	r10, r3
	bgt	.L4033
	b	.L4034
.L4031:
	strb	r9, [r10, #3132]
	mov	r0, r5
	bl	MVC_StorePicInDpb
	movw	lr, #26886
	movt	lr, 42
	ldr	r1, [fp, #-60]
	subs	r3, r0, #0
	add	r0, r4, #1
	bne	.L4041
	ldr	r3, [r7, #2676]
	add	lr, r3, lr
	add	lr, r5, lr, lsl #2
	str	r4, [lr, #4]
	bl	__aeabi_idivmod
	ldr	r3, [fp, #-52]
	cmp	r3, r1
	mov	r4, r1
	ble	.L4034
.L4033:
	mov	r1, #1
	mov	r0, r5
	bl	MVC_AllocFrameStore
	mov	r9, #0
	ldr	r1, .L4043+8
	subs	r3, r0, #0
	mov	r0, #2
	bne	.L4042
	str	r3, [fp, #-48]
	bl	dprint_vfmw
	ldr	r1, [r10, #3776]
	strb	r6, [r10, #3134]
	ldr	r3, [fp, #-56]
	str	r4, [r1, #20]
	ldr	r1, [r10, #3776]
	str	r4, [r10, #3784]
	str	r4, [r1, #716]
	str	r3, [r10, #3792]
	ldr	r1, [r10, #3776]
	ldr	r3, [fp, #-48]
	str	r3, [r1, #712]
	ldr	r1, [r10, #3776]
	strb	r6, [r1, #7]
	ldr	r1, [r10, #3776]
	strb	r3, [r1, #5]
	ldr	r1, [r10, #3776]
	strb	r6, [r1, #1]
	strb	r6, [r10, #3130]
	ldr	r1, [r10, #3780]
	ldr	r0, [r7, #2672]
	str	r0, [r10, #3856]
	strb	r3, [r1, #3]
	ldr	r3, [r5, #236]
	ldr	r3, [r3, #2900]
	cmp	r3, #0
	beq	.L4031
	str	r4, [r8, #4048]
	mov	r0, r5
	bl	MVC_DecPOC
	ldr	r3, [r8, #4028]
	str	r3, [r10, #3796]
	ldr	r3, [r8, #4024]
	str	r3, [r10, #3800]
	ldr	r3, [r8, #4016]
	str	r3, [r10, #3804]
	ldr	r3, [r8, #4020]
	str	r3, [r10, #3808]
	b	.L4031
.L4040:
	ldr	r1, .L4043+12
	mov	r0, r6
	bl	dprint_vfmw
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4034:
	ldr	r2, [fp, #-64]
	mov	r0, #0
	ldr	r3, [fp, #-76]
	str	r2, [r8, #4032]
	add	r3, r3, #12288
	ldr	r2, [fp, #-68]
	str	r2, [r8, #4036]
	ldrb	r2, [fp, #-72]	@ zero_extendqisi2
	ldr	r3, [r3, #3780]
	strb	r2, [r3, #3]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4042:
	ldr	r2, [fp, #-64]
	mov	r0, r9
	ldr	r3, [fp, #-76]
	ldr	r1, .L4043+16
	str	r2, [r8, #4032]
	add	r3, r3, #12288
	ldr	r2, [fp, #-68]
	str	r2, [r8, #4036]
	ldrb	r2, [fp, #-72]	@ zero_extendqisi2
	ldr	r3, [r3, #3780]
	strb	r2, [r3, #3]
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4041:
	ldr	r2, [fp, #-80]
	mov	r0, r9
	ldr	ip, [fp, #-64]
	add	r1, r2, #36864
	ldrb	lr, [fp, #-72]	@ zero_extendqisi2
	movw	r2, #6828
	str	ip, [r1, #4032]
	ldr	ip, [fp, #-68]
	str	ip, [r1, #4036]
	ldr	ip, [r10, #3780]
	ldr	r1, .L4043+20
	strb	lr, [ip, #3]
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4044:
	.align	2
.L4043:
	.word	.LC436
	.word	.LC437
	.word	.LC439
	.word	.LC435
	.word	.LC438
	.word	.LC440
	UNWIND(.fnend)
	.size	MVC_DecGap, .-MVC_DecGap
	.align	2
	.global	MVC_InitPic
	.type	MVC_InitPic, %function
MVC_InitPic:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	add	r3, r0, #11141120
	add	r5, r3, #12288
	str	r3, [fp, #-60]
	add	r3, r0, #11075584
	mov	r4, r0
	add	r6, r3, #40960
	str	r3, [fp, #-56]
	ldr	r3, [r0, #252]
	mov	r1, #0
	ldrb	r0, [r5, #3128]	@ zero_extendqisi2
	mov	r9, #2240
	ldr	r2, [r6, #1048]
	cmp	r0, r1
	str	r1, [fp, #-48]
	mla	r9, r9, r2, r3
	beq	.L4046
	ldr	r3, [r5, #3776]
	cmp	r3, r1
	beq	.L4047
	ldrb	r7, [r3, #2]	@ zero_extendqisi2
	cmp	r7, r1
	beq	.L4205
.L4047:
	mov	r3, #0
	strb	r3, [r5, #3128]
.L4046:
	sub	r1, fp, #48
	mov	r0, r4
	bl	MVC_GetReRangeFlag
	ldrb	r3, [r6, #1044]	@ zero_extendqisi2
	cmp	r3, #255
	mov	r10, r0
	beq	.L4206
.L4048:
	cmp	r3, #0
	bne	.L4051
	ldrb	r2, [r4, #2]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L4207
	ldr	r3, [r9, #28]
	ldr	r2, [r4, #28]
	cmp	r2, r3
	movweq	r3, #35364
	movteq	r3, 168
	addeq	r3, r4, r3
	streq	r3, [r4, #236]
	bne	.L4208
.L4051:
	ldr	r3, [fp, #-56]
	add	r7, r3, #36864
	ldr	r3, [r9, #24]
	ldr	r2, [r7, #1776]
	cmp	r2, r3
	beq	.L4209
.L4055:
	mov	r3, #0
	mov	r1, r9
	strb	r3, [r9, #20]
	ldr	r0, [r4, #236]
	bl	mvc_assign_quant_params
	ldr	r3, .L4223
	movw	r0, #38616
	mov	r2, #2240
	movt	r0, 169
	mov	r1, r9
	add	r0, r4, r0
	ldr	r3, [r3, #56]
	blx	r3
.L4056:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	ldr	r3, [r4, #224]
	bne	.L4210
	ldr	r3, [r3, #888]
	cmp	r3, #1
	beq	.L4058
.L4067:
	ldr	r2, [r7, #1776]
	ldr	r3, [r9, #24]
	cmp	r2, r3
	bne	.L4076
	ldrb	r3, [r9, #20]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4076
.L4077:
	ldrb	r3, [r6, #1044]	@ zero_extendqisi2
	cmp	r3, #255
	moveq	r3, #0
	streq	r3, [r6, #2676]
	beq	.L4079
	cmp	r3, #0
	bne	.L4079
	add	r1, r4, #10747904
	movw	r2, #22868
	add	r1, r1, #20480
	movt	r2, 164
	ldr	ip, [r6, #2672]
	add	r2, r4, r2
	ldr	r0, [r1, #2384]
	adds	r0, r0, #1
	beq	.L4080
	ldr	r1, [r1, #2388]
	cmp	ip, r1
	beq	.L4121
	mov	lr, r0
	ldr	r8, [fp, #-56]
	b	.L4081
.L4082:
	ldr	r1, [r2, #4]!
	cmp	ip, r1
	beq	.L4197
.L4081:
	add	r3, r3, #1
	cmp	r3, lr
	mov	r0, r3
	bne	.L4082
.L4197:
	str	r8, [fp, #-56]
.L4080:
	str	r0, [r6, #2676]
.L4079:
	ldrb	r2, [r6, #1035]	@ zero_extendqisi2
	ldr	r3, [r4, #236]
	cmp	r2, #5
	ldreq	r2, [r6, #2676]
	ldr	r9, [r3, #2896]
	movweq	r3, #26886
	movteq	r3, 42
	addeq	r3, r2, r3
	ldreq	r10, [r6, #1060]
	addeq	r3, r4, r3, lsl #2
	ldrne	r10, [r6, #1060]
	streq	r10, [r3, #4]
	ldrb	r3, [r4, #8]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L4085
	ldr	r2, [r4, #224]
	ldr	r3, [r2, #24]
	str	r2, [fp, #-64]
	cmp	r3, #2
	beq	.L4085
	ldr	r1, [r6, #2676]
	movw	r3, #26886
	movt	r3, 42
	add	r3, r1, r3
	add	r3, r4, r3, lsl #2
	ldr	r0, [r3, #4]
	cmp	r0, r10
	beq	.L4085
	mov	r3, #1
	add	r9, r9, #4
	mov	r9, r3, asl r9
	add	r0, r0, r3
	str	r3, [fp, #-68]
	mov	r1, r9
	bl	__aeabi_uidivmod
	cmp	r1, r10
	beq	.L4085
	ldr	r3, [fp, #-68]
	ldr	r2, [fp, #-64]
	str	r3, [r2, #608]
	ldr	r3, [r4, #224]
	ldr	r2, [r3, #608]
	cmp	r2, #0
	beq	.L4211
.L4086:
	ldr	r3, [fp, #-56]
	add	r3, r3, #32768
	ldrb	r3, [r3, #1875]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4095
	ldr	r1, .L4223+4
	mov	r0, #2
	bl	dprint_vfmw
	ldr	r3, [r4, #224]
	ldr	r3, [r3, #612]
	bics	r3, r3, #1024
	bne	.L4202
	ldr	r2, [r6, #2672]
	cmp	r2, #0
	bne	.L4202
	ldr	r0, [r6, #2676]
	movw	r3, #26886
	movt	r3, 42
	mov	r1, r9
	add	r3, r0, r3
	str	r2, [fp, #-64]
	ldr	r10, [r6, #1060]
	add	r3, r4, r3, lsl #2
	ldr	r0, [r3, #4]
	add	r0, r0, #1
	bl	__aeabi_uidivmod
	ldr	r2, [fp, #-64]
	cmp	r10, r1
	bcs	.L4085
	ldrb	r3, [r6, #1032]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L4085
	mov	r0, r4
	str	r2, [fp, #-56]
	bl	MVC_ClearCurrPic
	mvn	r1, #0
	mov	r0, r4
	bl	MVC_ClearDPB
	ldr	r3, [r6, #2676]
	movw	r0, #26886
	mov	r1, r9
	movt	r0, 42
	add	r0, r3, r0
	ldr	r5, [r6, #1060]
	add	r0, r4, r0, lsl #2
	ldr	r0, [r0, #4]
	add	r0, r0, #1
	bl	__aeabi_uidivmod
	ldr	r2, [fp, #-56]
	mov	r3, r5
	mov	r0, r2
	movw	r2, #7350
	str	r1, [sp]
	ldr	r1, .L4223+8
	bl	dprint_vfmw
	mvn	r0, #0
.L4193:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4210:
	ldr	r2, [r3, #724]
	cmp	r2, #0
	bne	.L4058
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L4212
.L4058:
	ldr	r3, [r4, #84]
	cmp	r10, #0
	add	r3, r3, #1
	str	r3, [r4, #84]
	bne	.L4068
	ldr	r3, [r4, #224]
	ldr	r3, [r3, #888]
	cmp	r3, #1
	beq	.L4069
	mvn	r1, #0
	mov	r0, r4
	bl	MVC_FlushDPB
	cmp	r0, #0
	bne	.L4213
.L4201:
	mov	r0, r4
	bl	MVC_InitDPB
	cmp	r0, #0
	bne	.L4119
	ldr	r3, [r4, #224]
	ldr	r3, [r3, #888]
	cmp	r3, #1
	bne	.L4067
.L4073:
	ldr	r1, [r7, #1732]
	mov	r0, r4
	ldr	r3, [fp, #-56]
	mov	r1, r1, asl #1
	add	ip, r3, #32768
	str	r1, [r4, #52]
	add	r3, r4, #48
	ldr	r2, [r7, #1712]
	ldrb	r10, [ip, #1876]	@ zero_extendqisi2
	add	r2, r2, #1
	ldr	ip, [r7, #1708]
	rsb	r10, r10, #2
	str	r1, [sp]
	mov	r2, r2, asl #4
	add	ip, ip, #1
	mul	r10, r10, r2
	mov	ip, ip, asl #4
	str	ip, [fp, #-64]
	mov	r1, ip
	mov	r2, r10
	bl	MVC_ArrangeVahbMem
	ldr	ip, [fp, #-64]
	cmp	r0, #1
	beq	.L4214
.L4199:
	ldr	r3, [r4, #224]
	ldr	r3, [r3, #888]
	cmp	r3, #1
	mvneq	r0, #1
	beq	.L4193
	mov	r5, #0
	ldr	r1, .L4223+12
	str	r5, [r4, #12]
	mov	r0, r5
	str	r5, [r4, #16]
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_ClearAll
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4076:
	ldr	r3, .L4223
	movw	r0, #38616
	mov	r2, #0
	movt	r0, 169
	strb	r2, [r9, #20]
	add	r0, r4, r0
	mov	r1, r9
	ldr	r3, [r3, #56]
	mov	r2, #2240
	blx	r3
	b	.L4077
.L4095:
	mov	r0, r4
	bl	MVC_DecGap
	cmp	r0, #0
	bne	.L4098
.L4202:
	ldr	r10, [r6, #1060]
.L4085:
	ldrb	r3, [r6, #1040]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4099
	ldr	r2, [r6, #2676]
	movw	r3, #26886
	movt	r3, 42
	add	r3, r2, r3
	add	r3, r4, r3, lsl #2
	str	r10, [r3, #4]
.L4099:
	mov	r0, r4
	str	r10, [r7, #4048]
	bl	MVC_DecPOC
	mov	r1, #0
	mov	r0, r4
	bl	MVC_AllocFrameStore
	cmp	r0, #0
	bne	.L4215
	strb	r0, [r5, #3135]
	mov	r1, #1
	strb	r1, [r5, #3128]
	mvn	lr, #0
	ldrb	r3, [r6, #1035]	@ zero_extendqisi2
	strb	r3, [r5, #3134]
	ldr	r10, [r6, #1060]
	str	r10, [r5, #3784]
	ldrb	r9, [r6, #1040]	@ zero_extendqisi2
	str	r9, [r5, #3792]
	ldr	ip, [r7, #4028]
	str	ip, [r5, #3796]
	ldr	r3, [r7, #4024]
	str	r3, [r5, #3800]
	ldr	r2, [r7, #4016]
	str	r2, [r5, #3804]
	ldr	r8, [r7, #4020]
	str	ip, [r5, #3812]
	str	r2, [r5, #3820]
	str	r8, [r5, #3824]
	str	r8, [r5, #3808]
	str	r3, [r5, #3816]
	strb	r0, [r5, #3130]
	strb	r0, [r5, #3133]
	strb	r0, [r5, #3132]
	str	lr, [r5, #3848]
	ldrb	r3, [r6, #1033]	@ zero_extendqisi2
	cmp	r3, #0
	strneb	r1, [r6, #1033]
	ldr	r2, [r4, #236]
	movne	r3, r1
	movne	r1, #2
	str	r3, [fp, #-68]
	ldrb	r0, [r2, #20]	@ zero_extendqisi2
	ldr	ip, [r2, #3952]
	rsb	r0, r0, #2
	str	r2, [fp, #-64]
	mla	r0, ip, r0, r0
	bl	__aeabi_uidiv
	ldr	r2, [fp, #-64]
	ldr	r3, [fp, #-68]
	cmp	r3, #0
	str	r0, [r5, #3836]
	ldrb	r1, [r2, #20]	@ zero_extendqisi2
	ldr	ip, [r2, #3952]
	rsb	r3, r1, #2
	mla	r3, ip, r3, r3
	str	r3, [r5, #3840]
	ldr	r1, [r2, #3948]
	add	r3, r1, #1
	str	r3, [r5, #3832]
	mul	r3, r3, r0
	str	r3, [r5, #3844]
	ldrb	r3, [r7, #1752]	@ zero_extendqisi2
	strb	r3, [r5, #3136]
	movne	r3, #0
	bne	.L4102
	ldrb	r3, [r2, #21]	@ zero_extendqisi2
	adds	r3, r3, #0
	movne	r3, #1
.L4102:
	cmp	r9, #0
	strb	r3, [r5, #3137]
	beq	.L4103
	ldr	r2, [r6, #2676]
	movw	r3, #26886
	movt	r3, 42
	add	r3, r2, r3
	add	r3, r4, r3, lsl #2
	str	r10, [r3, #4]
.L4103:
	ldr	r3, [r5, #3776]
	cmp	r3, #0
	ldrneb	r2, [r6, #1044]	@ zero_extendqisi2
	strneb	r2, [r3, #9]
	mvn	r3, #0
	str	r3, [r5, #3856]
	ldrb	r3, [r6, #1043]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4105
	ldr	r3, [r6, #2672]
	str	r3, [r5, #3856]
	ldrb	r3, [r6, #1041]	@ zero_extendqisi2
	strb	r3, [r5, #3138]
	ldrb	r3, [r6, #1042]	@ zero_extendqisi2
	strb	r3, [r5, #3139]
.L4105:
	ldr	r1, [r6, #2676]
	movw	ip, #2004
	movw	r3, #43696
	movw	r2, #16016
	movt	r3, 169
	movt	r2, 170
	str	r1, [r5, #3860]
	movw	r7, #16032
	ldrb	r1, [r4, #3]	@ zero_extendqisi2
	movt	r7, 170
	add	r7, r4, r7
	movw	lr, #16032
	movt	lr, 170
	mov	r0, #29
	mla	ip, ip, r1, r4
	ldr	r1, .L4223+16
	add	r3, ip, r3
	str	r3, [r5, #3780]
	ldr	r3, [r4, #224]
	ldrd	r8, [r3, #56]
	strd	r8, [r4, r2]
	ldrd	r8, [r3, #72]
	strd	r8, [r7, #-8]
	ldrd	r8, [r3, #88]
	strd	r8, [r4, lr]
	mvn	r8, #0
	mvn	r9, #0
	strd	r8, [r3, #56]
	ldrd	r2, [r2, r4]
	bl	dprint_vfmw
	ldrd	r2, [r7, #-8]
	ldr	r1, .L4223+20
	mov	r0, #29
	bl	dprint_vfmw
	ldr	ip, [r4, #236]
	ldr	r3, [fp, #-56]
	mov	r2, #4
	ldr	r1, .L4223
	movw	r0, #15496
	add	r8, r3, #32768
	ldr	r3, [ip, #3948]
	movt	r0, 170
	add	r0, r4, r0
	add	r3, r3, #1
	ldr	r7, [r1, #48]
	mov	r1, #0
	mov	r3, r3, asl r2
	str	r3, [r5, #3212]
	ldrb	lr, [ip, #20]	@ zero_extendqisi2
	ldr	r9, [ip, #3952]
	rsb	r3, lr, #2
	mla	r3, r9, r3, r3
	mov	r3, r3, asl r2
	str	r3, [r5, #3216]
	ldr	r9, [r8, #1908]
	ldr	r8, [ip, #748]
	and	r9, r9, #7
	subs	r8, r8, #1
	movne	r8, #1
	blx	r7
	ldrb	r2, [r5, #3208]	@ zero_extendqisi2
	mov	ip, #2
	ldrb	r3, [r5, #3209]	@ zero_extendqisi2
	movw	r0, #15432
	and	r2, r2, #252
	mov	r1, r9
	bfi	r2, r8, #2, #3
	strb	r2, [r5, #3208]
	ldr	r2, [r4, #236]
	bfi	r3, ip, #0, #2
	and	r3, r3, #243
	ldrb	lr, [r5, #3208]	@ zero_extendqisi2
	bfi	r3, ip, #4, #2
	movt	r0, 170
	ldr	ip, [r2, #56]
	add	r0, r4, r0
	strb	r3, [r5, #3209]
	bfi	lr, ip, #5, #3
	strb	lr, [r5, #3208]
	ldr	r2, [r2, #52]
	ldr	r3, [r5, #3208]
	bfi	r3, r2, #14, #3
	str	r3, [r5, #3208]
	bl	SetAspectRatio
	ldr	r0, [r5, #3776]
	ldr	r3, [r4, #84]
	cmp	r0, #0
	str	r3, [r5, #3300]
	beq	.L4216
	ldr	r3, [r4, #236]
	ldr	r3, [r3, #3984]
	str	r3, [r0, #156]
	str	r3, [r5, #3228]
	ldr	r3, [r4, #236]
	ldr	r2, [r5, #3776]
	ldr	r3, [r3, #3988]
	str	r3, [r2, #160]
	str	r3, [r5, #3232]
	ldr	r3, [r4, #236]
	ldr	r2, [r5, #3776]
	ldr	r3, [r3, #3976]
	str	r3, [r2, #148]
	str	r3, [r5, #3220]
	ldr	r2, [r4, #236]
	ldr	r3, [r5, #3776]
	ldr	r2, [r2, #3980]
	str	r2, [r3, #152]
	ldrb	r3, [r5, #3131]	@ zero_extendqisi2
	ldr	r1, [r5, #3776]
	ldr	r0, [r5, #3208]
	adds	r3, r3, #0
	str	r2, [r5, #3224]
	movne	r3, #1
	str	r3, [r5, #3196]
	str	r0, [r1, #136]
	ldr	r2, [r5, #3196]
	ldr	r3, [r5, #3776]
	str	r2, [r3, #124]
	ldr	r3, [r6, #1060]
	ldr	r2, [r5, #3776]
	str	r3, [r5, #3320]
	ldr	r1, [r6, #2672]
	str	r1, [r5, #3328]
	str	r3, [r2, #248]
	ldr	r3, [r5, #3776]
	ldr	r2, [r6, #2672]
	str	r2, [r3, #256]
	ldr	r3, [r5, #3776]
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_GetDispPhyFs
	cmp	r0, #0
	beq	.L4107
	ldr	r3, [r5, #3196]
	mov	r1, #0
	ldr	r2, [r0, #4]
	subs	r3, r3, r1
	ldr	r0, [r4, #120]
	movne	r3, #1
	bl	FSP_SetStoreType
.L4107:
	ldr	r3, [fp, #-60]
	movw	ip, #15968
	movt	ip, 170
	add	ip, r4, ip
	add	lr, r3, #16000
	ldr	r3, [r4, #60]
	mov	r6, #0
.L4111:
	ldrd	r0, [ip, #8]!
	orrs	r2, r0, r1
	bne	.L4108
	cmp	r3, #0
	beq	.L4108
	ldr	r2, [r4, #528]
	subs	r3, r3, #1
	stmia	ip, {r2, r6}
	beq	.L4109
	add	r1, r4, #528
	mov	r2, #0
.L4110:
	add	r2, r2, #1
	ldr	r0, [r1, #4]!
	cmp	r2, r3
	str	r0, [r1, #-4]
	bne	.L4110
.L4109:
	add	r2, r3, #132
	str	r6, [r4, r2, asl #2]
	str	r3, [r4, #60]
.L4108:
	cmp	ip, lr
	bne	.L4111
	cmp	r3, #0
	beq	.L4113
	mov	r6, r3
	ble	.L4113
	add	r7, r3, #132
	mov	r8, #0
	add	r7, r4, r7, lsl #2
.L4114:
	ldr	r1, [r7, #-4]!
	sub	r6, r6, #1
	ldr	r0, [r4, #120]
	bl	FreeUsdByDec
	cmp	r6, #0
	str	r8, [r7]
	bne	.L4114
.L4113:
	mov	r6, #0
	mov	r0, r4
	str	r6, [r4, #60]
	strb	r6, [r5, #3140]
	bl	MVC_UpdateReflist
	mov	r0, r4
	bl	MVC_UpdateLTReflist
	mov	r0, r4
	bl	MVC_CalcPicNum
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4209:
	ldrb	r3, [r9, #20]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4056
	b	.L4055
.L4206:
	mov	r2, #1
	strb	r2, [r4, #2]
	ldr	r2, [r9, #28]
	movw	ip, #3992
	ldr	r0, [r4, #248]
	movw	r7, #34624
	ldr	r1, [fp, #-56]
	str	r2, [r4, #24]
	ldr	r2, [r9, #28]
	add	r1, r1, #32768
	ldr	r1, [r1, #2600]
	mla	r2, ip, r2, r0
	ldr	r0, [r2, #744]
	cmp	r1, r0
	beq	.L4217
.L4049:
	ldr	r3, .L4223
	movt	r7, 169
	ldr	r0, [r4, #84]
	add	r7, r4, r7
	mov	ip, #0
	mov	r1, r2
	add	r0, r0, #1
	str	r0, [r4, #84]
	strb	ip, [r2, #26]
	mov	r0, r7
	ldr	r3, [r3, #56]
	movw	r2, #3992
	blx	r3
	ldrb	r3, [r6, #1044]	@ zero_extendqisi2
.L4050:
	str	r7, [r4, #236]
	b	.L4048
.L4069:
	ldr	r1, .L4223+24
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	bl	MVC_GetBackPicFromVOQueue
	b	.L4201
.L4217:
	ldrb	r1, [r2, #26]	@ zero_extendqisi2
	cmp	r1, #0
	movteq	r7, 169
	addeq	r7, r4, r7
	beq	.L4050
	b	.L4049
.L4205:
	ldrsb	r1, [r3, #6]
	mov	r2, #1
	ldr	r0, [r4, #120]
	bl	FSP_ClearLogicFs
	ldr	r3, [r5, #3776]
	strb	r7, [r3, #2]
	ldr	r3, [r5, #3776]
	strb	r7, [r3, #5]
	b	.L4047
.L4211:
	ldr	r2, [r3, #652]
	cmp	r2, #1
	beq	.L4218
.L4087:
	ldr	r3, [r6, #2676]
	ldr	r1, [r6, #1060]
	add	r3, r4, r3, lsl #2
	add	r3, r3, #11075584
	add	r2, r3, #40960
	ldr	r2, [r2, #1052]
	cmp	r1, r2
	bls	.L4088
	ldr	ip, [r7, #1732]
	rsb	r0, r2, r1
	cmp	r2, #0
	cmpne	ip, r0
	bcs	.L4086
	ldrb	r2, [r6, #1032]	@ zero_extendqisi2
	cmp	r2, #2
	bne	.L4219
	add	r3, r3, #40960
	cmp	r1, #0
	subne	r2, r1, #1
	subeq	r2, r9, #1
	mvn	r1, #0
	str	r2, [r3, #1052]
	mov	r0, r4
	bl	MVC_FlushDPB
	subs	r3, r0, #0
	beq	.L4086
	movw	r2, #7300
	ldr	r1, .L4223+28
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4193
.L4212:
	ldr	r3, [r4, #84]
	cmp	r10, #0
	add	r3, r3, #1
	str	r3, [r4, #84]
	beq	.L4059
	mvn	r1, #0
	mov	r0, r4
	str	r2, [fp, #-64]
	bl	MVC_FlushDPB
	ldr	r2, [fp, #-64]
	subs	r3, r0, #0
	bne	.L4220
	mov	r0, r4
	bl	MVC_InitDPB
	subs	r3, r0, #0
	bne	.L4116
	ldr	r2, [fp, #-56]
	ldr	r3, [r7, #1712]
	add	r2, r2, #32768
	ldr	r10, [r7, #1708]
	add	r3, r3, #1
	ldrb	ip, [r2, #1876]	@ zero_extendqisi2
	add	r10, r10, #1
	ldr	r2, [r4, #12]
	mov	r3, r3, asl #4
	rsb	ip, ip, #2
	mov	r10, r10, asl #4
	cmp	r2, #0
	mul	ip, ip, r3
	bne	.L4065
	ldr	r3, [r7, #1732]
	ldr	r0, [r4, #224]
	mov	r3, r3, asl #1
	str	r3, [r4, #52]
	ldr	r1, [r0, #684]
	cmp	r1, r10
	bcc	.L4061
	ldr	r2, [r0, #688]
	cmp	r2, ip
	bcc	.L4061
	ldr	lr, [fp, #-56]
	ldr	r8, [r0, #708]
	add	lr, lr, #45056
	ldr	lr, [lr, #2888]
	cmp	r8, lr
	bcc	.L4221
	ldr	lr, [r0, #712]
	str	ip, [fp, #-64]
	cmp	lr, #0
	moveq	r3, #1
	streq	r3, [r4, #52]
	ldreq	r1, [r0, #684]
	ldreq	r2, [r0, #688]
	mov	r0, r4
	str	r3, [sp]
	add	r3, r4, #48
	bl	MVC_ArrangeVahbMem
	ldr	ip, [fp, #-64]
	cmp	r0, #1
	bne	.L4199
	b	.L4065
.L4207:
	strb	r3, [r4, #2]
	movw	r1, #8500
	ldr	r3, [r9, #28]
	movt	r1, 5
	mov	r2, r1
	ldr	ip, .L4223
	movw	r0, #22860
	mla	r1, r1, r3, r4
	movt	r0, 164
	ldr	r3, [ip, #56]
	add	r0, r4, r0
	add	r1, r1, #12992
	add	r1, r1, #12
	blx	r3
	add	r2, r4, #11010048
	add	r2, r2, #32768
	movw	r3, #35364
	movt	r3, 168
	add	r3, r4, r3
	str	r3, [r4, #236]
	ldr	r3, [r2, #3340]
	str	r3, [r4, #28]
	b	.L4051
.L4068:
	ldr	r1, .L4223+24
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	bl	MVC_GetBackPicFromVOQueue
	mov	r0, r4
	bl	MVC_InitDPB
	cmp	r0, #0
	beq	.L4073
.L4119:
	mov	r3, r0
	movw	r2, #7189
	ldr	r1, .L4223+32
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4193
.L4214:
	mov	ip, ip, lsr #4
	mov	r10, r10, lsr #4
	str	ip, [r4, #12]
	str	r10, [r4, #16]
	b	.L4067
.L4088:
	rsb	r0, r2, r1
	ldr	ip, [r7, #1732]
	add	r0, r0, r9
	cmp	r2, #0
	cmpne	ip, r0
	bcs	.L4086
	ldrb	r2, [r6, #1032]	@ zero_extendqisi2
	cmp	r2, #2
	bne	.L4222
	add	r3, r3, #40960
	cmp	r1, #0
	subne	r2, r1, #1
	subeq	r2, r9, #1
	mvn	r1, #0
	str	r2, [r3, #1052]
	mov	r0, r4
	bl	MVC_FlushDPB
	subs	r3, r0, #0
	beq	.L4086
	movw	r2, #7327
	ldr	r1, .L4223+28
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4193
.L4059:
	mov	r0, r4
	bl	MVC_InitDPB
	subs	r3, r0, #0
	bne	.L4116
	ldr	r2, [fp, #-56]
	ldr	r3, [r7, #1712]
	add	r2, r2, #32768
	ldr	r10, [r7, #1708]
	add	r3, r3, #1
	ldrb	ip, [r2, #1876]	@ zero_extendqisi2
	add	r10, r10, #1
	mov	r3, r3, asl #4
	rsb	ip, ip, #2
	mov	r10, r10, asl #4
	mul	ip, ip, r3
.L4065:
	mov	r10, r10, lsr #4
	mov	ip, ip, lsr #4
	str	r10, [r4, #12]
	str	ip, [r4, #16]
	b	.L4067
.L4208:
	ldr	r1, .L4223+36
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4193
.L4098:
	movw	r2, #7374
	ldr	r1, .L4223+40
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4193
.L4218:
	ldr	r2, [r3, #648]
	cmp	r2, #0
	bne	.L4087
	ldr	r2, [r3, #656]
	cmp	r2, #0
	bne	.L4087
	ldr	r3, [r3, #612]
	add	r3, r3, #1024
	cmp	r3, #2048
	bhi	.L4086
	b	.L4087
.L4121:
	mov	r0, r3
	b	.L4080
.L4215:
	movw	r2, #7394
	ldr	r1, .L4223+44
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4193
.L4216:
	movw	r2, #7498
	ldr	r1, .L4223+48
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4193
.L4213:
	mov	r3, r0
	movw	r2, #7180
	mov	r0, r10
	ldr	r1, .L4223+28
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4193
.L4219:
	mov	r0, r4
	bl	MVC_ClearCurrPic
	mvn	r1, #0
	mov	r0, r4
	bl	MVC_ClearDPB
	ldr	r2, [r6, #2676]
	ldr	r3, [r7, #1732]
	movw	r1, #26886
	ldr	ip, [r6, #1060]
	movt	r1, 42
	add	r1, r2, r1
	movw	r2, #7289
.L4203:
	add	r4, r4, r1, lsl #2
	str	r3, [sp]
	ldr	r1, .L4223+52
	mov	r0, #0
	ldr	r3, [r4, #4]
	rsb	r3, r3, ip
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4193
.L4116:
	movw	r2, #7105
	ldr	r1, .L4223+32
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4193
.L4222:
	mov	r0, r4
	bl	MVC_ClearCurrPic
	mvn	r1, #0
	mov	r0, r4
	bl	MVC_ClearDPB
	ldr	r2, [r6, #2676]
	movw	r1, #26886
	ldr	r3, [r7, #1732]
	movt	r1, 42
	ldr	ip, [r6, #1060]
	add	r1, r2, r1
	movw	r2, #7316
	b	.L4203
.L4061:
	ldr	r1, .L4223+56
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4193
.L4220:
	mov	r0, r2
	ldr	r1, .L4223+28
	movw	r2, #7096
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4193
.L4221:
	ldr	r1, .L4223+60
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4193
.L4224:
	.align	2
.L4223:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC447
	.word	.LC448
	.word	.LC445
	.word	.LC451
	.word	.LC452
	.word	.LC454
	.word	.LC441
	.word	.LC442
	.word	.LC31
	.word	.LC449
	.word	.LC450
	.word	.LC453
	.word	.LC446
	.word	.LC443
	.word	.LC444
	UNWIND(.fnend)
	.size	MVC_InitPic, .-MVC_InitPic
	.align	2
	.global	MVC_DecSlice
	.type	MVC_DecSlice, %function
MVC_DecSlice:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #16)
	sub	sp, sp, #16
	ldr	r2, [r0, #68]
	mov	r5, r0
	ldr	r1, .L4277
	sub	r2, r2, #1
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r3, [r5, #232]
	add	r4, r5, #11075584
	mov	r0, r5
	add	r4, r4, #40960
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	strb	r2, [r4, #1035]
	ldrb	r3, [r3, #4]	@ zero_extendqisi2
	strb	r3, [r4, #1040]
	bl	MVC_ProcessSliceHeaderFirstPart
	cmp	r0, #0
	bne	.L4270
	mov	r0, r5
	bl	MVC_ProcessSliceHeaderSecondPart
	cmp	r0, #0
	bne	.L4270
	ldr	r2, [r5, #64]
	cmp	r2, #0
	moveq	r3, r2
	beq	.L4232
	mov	r1, r0
	movw	r8, #16912
	movt	r8, 170
	mov	r3, r1
	add	r8, r5, r8
	mov	r6, r1
	b	.L4240
.L4271:
	cmp	lr, r1
	add	r3, r7, r3
	rsbhi	r1, r1, lr
	rsbhi	r0, r0, r9
	addhi	r1, r1, r0
	movls	r1, r9
	add	r3, r3, r1
.L4238:
	cmp	ip, #0
	add	r6, r6, #1
	movne	r1, ip
	movne	r0, r7
	moveq	r1, lr
	moveq	r0, r9
	cmp	r6, r2
	beq	.L4232
.L4240:
	ldr	r7, [r8, #4]!
	ldr	lr, [r7, #8]
	ldr	ip, [r7, #36]
	cmp	lr, #0
	ldrne	r9, [r7, #12]
	moveq	r9, lr
	cmp	ip, #0
	ldrne	r7, [r7, #40]
	moveq	r7, ip
	cmp	r1, #0
	bne	.L4271
	add	r3, r9, r3
	add	r3, r3, r7
	b	.L4238
.L4232:
	add	r6, r5, #11141120
	str	r3, [r5, #104]
	add	r6, r6, #12288
	movw	r0, #1620
	ldr	ip, [r6, #3836]
	ldr	r1, [r6, #3832]
	mul	r1, r1, ip
	cmp	r1, r0
	movgt	r1, r1, asl #7
	ble	.L4272
.L4242:
	ldr	r0, [r5, #32]
	cmp	r0, r2
	bls	.L4243
	cmp	r1, r3
	bcc	.L4243
	ldrb	r3, [r4, #1037]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4273
.L4246:
	mov	r0, r5
	bl	MVC_PicTypeStatistic
	mov	r0, r5
	bl	MVC_DecList
	cmp	r0, #0
	bne	.L4274
	mov	r0, r5
	bl	MVC_IsRefListWrong
	subs	r4, r0, #0
	bne	.L4275
	mov	r0, r5
	bl	MVC_CalcStreamBits
	mov	r0, r5
	bl	MVC_WriteSliceMsg
	mov	r0, r5
	bl	MVC_ExitSlice
	ldr	r3, [r5, #100]
	mov	r0, r4
	mov	r2, #1
	add	r3, r3, r2
	strb	r2, [r5, #4]
	str	r3, [r5, #100]
.L4229:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4272:
	mov	r0, r1, asl #9
	sub	r1, r0, r1, asl #7
	cmp	r1, #16384
	movlt	r1, #16384
	b	.L4242
.L4273:
	ldr	r1, .L4277+4
	mov	r0, #2
	bl	dprint_vfmw
	ldr	r3, [r5, #88]
	mov	r2, #0
	str	r2, [r5, #100]
	add	r3, r3, #1
	str	r3, [r5, #88]
	ldrb	r3, [r6, #3131]	@ zero_extendqisi2
	mov	r0, r5
	cmp	r3, r2
	ldreq	r3, [r5, #92]
	ldrne	r3, [r5, #96]
	addeq	r3, r3, #1
	addne	r3, r3, #1
	streq	r3, [r5, #92]
	strne	r3, [r5, #96]
	bl	MVC_InitPic
	cmn	r0, #2
	beq	.L4229
	cmp	r0, #0
	bne	.L4276
	mov	r0, r5
	bl	MVC_WritePicMsg
	b	.L4246
.L4270:
	ldr	r1, .L4277+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L4277+12
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L4268
	sub	r2, fp, #36
	mvn	r1, #0
	mov	r3, #4
	str	r1, [r2, #-8]!
	mov	r1, #100
	ldr	r0, [r5, #120]
	blx	ip
.L4268:
	mov	r0, r5
	bl	MVC_ClearCurrSlice
	mvn	r0, #0
	b	.L4229
.L4243:
	str	r1, [sp]
	mov	r0, #0
	ldr	r1, .L4277+16
	bl	dprint_vfmw
	ldr	r3, [r5, #64]
	ldr	r2, [r5, #32]
	cmp	r3, r2
	bcc	.L4245
	ldr	r1, .L4277+12
	ldr	ip, [r1]
	cmp	ip, #0
	beq	.L4245
	str	r3, [fp, #-44]
	mov	r1, #108
	str	r2, [fp, #-40]
	mov	r3, #8
	sub	r2, fp, #44
	ldr	r0, [r5, #120]
	blx	ip
.L4245:
	ldr	r1, .L4277+20
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	bl	MVC_ClearCurrPic
	mvn	r0, #0
	b	.L4229
.L4274:
	mov	r2, r0
	ldr	r1, .L4277+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4229
.L4275:
	ldr	r1, .L4277+28
	mov	r0, #1
	bl	dprint_vfmw
	b	.L4268
.L4276:
	ldr	r1, .L4277+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4229
.L4278:
	.align	2
.L4277:
	.word	.LC394
	.word	.LC457
	.word	.LC395
	.word	g_event_report
	.word	.LC455
	.word	.LC456
	.word	.LC459
	.word	.LC460
	.word	.LC458
	UNWIND(.fnend)
	.size	MVC_DecSlice, .-MVC_DecSlice
	.align	2
	.global	MVC_DecOneNal
	.type	MVC_DecOneNal, %function
MVC_DecOneNal:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	lr, [r0, #232]
	mov	r4, r0
	mov	r5, r1
	ldr	r3, [lr, #68]
	cmp	r3, #0
	ldrne	ip, [r0, #104]
	movne	r2, lr
	movne	r3, #0
	beq	.L4284
.L4283:
	ldr	r0, [r2, #12]
	add	r3, r3, #1
	add	r2, r2, #28
	add	ip, ip, r0
	str	ip, [r4, #104]
	ldr	r0, [lr, #68]
	cmp	r0, r3
	bhi	.L4283
.L4284:
	add	r7, r4, #548
	mov	r8, #0
	mov	r1, #32
	strb	r8, [lr]
	mov	r0, r7
	bl	BsGet
	ldr	r3, [r4, #232]
	mvn	r1, #0
	and	ip, r0, #31
	strb	ip, [r3, #2]
	ldr	r3, [r4, #232]
	mov	r6, r0
	ubfx	r0, r0, #5, #2
	ubfx	r2, r6, #7, #1
	strb	r0, [r3, #4]
	ldr	r3, [r4, #232]
	str	r2, [r3, #76]
	ldr	r2, [r4, #232]
	ldr	r3, [r2, #64]
	add	r3, r3, #32
	str	r3, [r2, #64]
	ldr	r3, [r4, #232]
	strb	r8, [r4, #10]
	strb	r1, [r3, #5]
	ldr	r3, [r4, #232]
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	cmp	r3, #14
	cmpne	r3, #20
	beq	.L4465
.L4282:
	ldr	r2, [r4, #68]
	mov	r0, #22
	ldr	r1, .L4476
	bl	dprint_vfmw
	ldr	r3, [r4, #68]
	movw	r2, #371
	cmp	r3, r2
	beq	.L4466
.L4287:
	ldr	r2, [r4, #232]
	add	r3, r3, #1
	str	r3, [r4, #68]
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	sub	r3, r2, #1
	cmp	r3, #29
	ldrls	pc, [pc, r3, asl #2]
	b	.L4288
.L4290:
	.word	.L4289
	.word	.L4288
	.word	.L4288
	.word	.L4288
	.word	.L4289
	.word	.L4291
	.word	.L4292
	.word	.L4293
	.word	.L4294
	.word	.L4295
	.word	.L4296
	.word	.L4297
	.word	.L4298
	.word	.L4299
	.word	.L4300
	.word	.L4288
	.word	.L4288
	.word	.L4288
	.word	.L4301
	.word	.L4288
	.word	.L4288
	.word	.L4288
	.word	.L4288
	.word	.L4288
	.word	.L4288
	.word	.L4288
	.word	.L4288
	.word	.L4288
	.word	.L4288
	.word	.L4302
.L4465:
	mov	r1, #24
	mov	r0, r7
	bl	BsGet
	ldr	r3, [r4, #232]
	ubfx	r2, r0, #23, #1
	strb	r2, [r3, #5]
	ldr	r3, [r4, #232]
	mov	r6, r0
	ldrsb	r2, [r3, #5]
	cmp	r2, #0
	bne	.L4285
	add	r2, r4, #12288
	mov	r1, #1
	ubfx	r0, r0, #16, #6
	ubfx	ip, r6, #2, #1
	strb	r1, [r2, #704]
	ubfx	lr, r6, #6, #10
	ubfx	r1, r6, #3, #3
	strb	r0, [r2, #706]
	strb	r1, [r2, #707]
	ubfx	r0, r6, #1, #1
	strb	ip, [r2, #708]
	and	r1, r6, #1
	str	lr, [r2, #712]
	ubfx	ip, r6, #22, #1
	strb	r0, [r2, #709]
	strb	r1, [r2, #710]
	strb	ip, [r2, #705]
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	cmp	r2, #20
	beq	.L4467
.L4285:
	ldr	r2, [r3, #64]
	add	r2, r2, #24
	str	r2, [r3, #64]
	ldr	r3, [r4, #232]
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	b	.L4282
.L4289:
	ldr	r3, [r4, #80]
	mov	r0, #22
	ldr	r1, .L4476+4
	bl	dprint_vfmw
	ldr	r3, [r4, #232]
	add	r0, r4, #11075584
	add	r2, r4, #12288
	add	r0, r0, #40960
	mvn	lr, #0
	ldrb	ip, [r3, #2]	@ zero_extendqisi2
	mov	r1, #0
	strb	ip, [r0, #1035]
	ldrb	r5, [r3, #4]	@ zero_extendqisi2
	strb	r5, [r0, #1040]
	ldrb	r3, [r3, #5]	@ zero_extendqisi2
	str	lr, [r0, #2672]
	strb	r1, [r0, #1043]
	strb	r3, [r0, #1044]
	ldrb	lr, [r2, #704]	@ zero_extendqisi2
	cmp	lr, #1
	beq	.L4468
	cmp	r3, #255
	beq	.L4469
.L4304:
	ldr	r2, [r4, #88]
	mov	r0, #21
	ldr	r1, .L4476+8
	bl	dprint_vfmw
	mov	r0, r4
	bl	MVC_SliceCheck
	subs	r5, r0, #0
	mov	r0, r4
	bne	.L4470
	bl	MVC_DecSlice
	cmn	r0, #2
	beq	.L4315
	cmp	r0, #0
	beq	.L4446
	ldr	r3, .L4476+12
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L4445
	ldr	r0, [r4, #120]
	mov	r3, r5
	mov	r2, r5
	mov	r1, #113
	blx	ip
.L4445:
	mvn	r0, #0
	b	.L4315
.L4291:
	ldr	r1, .L4476+16
	mov	r2, #6
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	bl	MVC_DecSEI
	ldr	r1, [r4, #232]
	cmp	r1, #0
	mov	r5, r0
	beq	.L4322
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L4322:
	cmp	r5, #0
	bne	.L4471
.L4446:
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L4292:
	ldr	r1, .L4476+20
	mov	r2, #7
	ldr	r3, [r4, #72]
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	bl	MVC_DecSPS
	ldr	r1, [r4, #232]
	cmp	r1, #0
	mov	r5, r0
	beq	.L4320
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L4320:
	cmp	r5, #0
	bne	.L4472
	ldr	r3, [r4, #72]
	mov	r0, r5
	add	r3, r3, #1
	str	r3, [r4, #72]
	b	.L4315
.L4294:
	ldr	r1, .L4476+24
	mov	r2, #9
.L4453:
	mov	r0, #22
	bl	dprint_vfmw
.L4458:
	ldr	r1, [r4, #232]
	cmp	r1, #0
	beq	.L4446
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #232]
.L4315:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L4295:
	mov	r2, #10
	ldr	r1, .L4476+28
	b	.L4453
.L4293:
	ldr	r1, .L4476+32
	mov	r2, #8
	ldr	r3, [r4, #76]
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	bl	MVC_DecPPS
	ldr	r1, [r4, #232]
	cmp	r1, #0
	mov	r5, r0
	beq	.L4318
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L4318:
	cmp	r5, #0
	bne	.L4473
	ldr	r3, [r4, #76]
	mov	r0, r5
	add	r3, r3, #1
	str	r3, [r4, #76]
	b	.L4315
.L4296:
	mov	r2, #11
	ldr	r1, .L4476+36
	mov	r0, #22
	bl	dprint_vfmw
	mov	r1, #32
	mov	r0, r7
	bl	BsGet
	mov	r1, #32
	mov	r5, r0
	mov	r0, r7
	bl	BsGet
	movw	r2, #20036
	movw	r3, #20553
	movt	r2, 17221
	movt	r3, 18515
	cmp	r0, r2
	cmpeq	r5, r3
	bne	.L4458
	ldr	r5, .L4476+12
	mov	r3, #1
	strb	r3, [r4, #1]
	ldr	ip, [r5]
	cmp	ip, #0
	beq	.L4325
	mov	r3, #0
	mov	r1, #112
	mov	r2, r3
	ldr	r0, [r4, #120]
	blx	ip
.L4325:
	mov	r6, #0
	mov	r0, r4
	strb	r6, [r4]
	bl	MVC_DecVDM
	cmp	r0, r6
	beq	.L4458
	b	.L4461
.L4297:
	mov	r2, #12
	ldr	r1, .L4476+40
	b	.L4453
.L4298:
	mov	r2, #13
	ldr	r1, .L4476+44
	b	.L4453
.L4299:
	mov	r2, #14
	ldr	r1, .L4476+48
	b	.L4453
.L4300:
	ldr	r1, .L4476+52
	mov	r2, #15
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	bl	MVC_DecSubSPS
	ldr	r1, [r4, #232]
	cmp	r1, #0
	mov	r5, r0
	beq	.L4326
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L4326:
	cmp	r5, #0
	bne	.L4474
	ldr	r3, [r4, #20]
	mov	r0, r5
	add	r3, r3, #1
	str	r3, [r4, #20]
	b	.L4315
.L4301:
	mov	r2, #19
	ldr	r1, .L4476+56
	b	.L4453
.L4302:
	mov	r2, #30
	ldr	r1, .L4476+60
	mov	r0, #22
	bl	dprint_vfmw
	cmp	r5, #0
	bne	.L4328
	ldr	r1, [r4, #232]
	cmp	r1, #0
	beq	.L4328
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	str	r5, [r4, #232]
.L4328:
	mov	r1, #32
	mov	r0, r7
	bl	BsGet
	mov	r1, #32
	mov	r5, r0
	mov	r0, r7
	bl	BsGet
	ldr	r3, .L4476+64
	rev	r5, r5
	ldr	r2, [r3, #440]
	ldr	r3, [r3, #436]
	rev	r0, r0
	cmp	r0, r2
	cmpeq	r5, r3
	bne	.L4446
	ldr	r5, .L4476+12
	ldr	ip, [r5]
	cmp	ip, #0
	beq	.L4329
	mov	r3, #0
	mov	r1, #112
	mov	r2, r3
	ldr	r0, [r4, #120]
	blx	ip
.L4329:
	mov	r6, #0
	mov	r0, r4
	strb	r6, [r4]
	bl	MVC_DecVDM
	cmp	r0, r6
	beq	.L4446
.L4461:
	ldr	ip, [r5]
	cmp	ip, r6
	beq	.L4445
	ldr	r0, [r4, #120]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #113
	blx	ip
	mvn	r0, #0
	b	.L4315
.L4288:
	mov	r3, r6
	ldr	r1, .L4476+68
	mov	r0, #22
	bl	dprint_vfmw
	cmp	r6, #256
	beq	.L4330
	ldr	r1, .L4476+72
	mov	r0, #1
	bl	dprint_vfmw
.L4330:
	ldr	r1, [r4, #232]
	cmp	r1, #0
	beq	.L4331
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L4331:
	ldr	r3, .L4476+12
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L4446
.L4450:
	mov	r3, #0
	ldr	r0, [r4, #120]
	mov	r2, r3
	mov	r1, #113
	blx	ip
	b	.L4446
.L4466:
	ldr	r1, .L4476+76
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r3, [r4, #68]
	b	.L4287
.L4467:
	cmp	ip, #0
	movne	r2, #1
	moveq	r2, #5
	strb	r2, [r3, #2]
	ldr	r3, [r4, #232]
	b	.L4285
.L4470:
	bl	MVC_ClearCurrSlice
	ldr	r3, .L4476+12
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L4445
.L4314:
	mov	r3, #0
	ldr	r0, [r4, #120]
	mov	r2, r3
	mov	r1, #113
	blx	ip
	mvn	r0, #0
	b	.L4315
.L4473:
	ldr	r5, .L4476+12
	mov	r0, #1
	ldr	r1, .L4476+80
	bl	dprint_vfmw
	ldr	ip, [r5]
	cmp	ip, #0
	beq	.L4445
.L4463:
	sub	r2, fp, #36
	mvn	r6, #0
	mov	r3, #4
	mov	r1, #100
	str	r6, [r2, #-4]!
	ldr	r0, [r4, #120]
	blx	ip
	ldr	ip, [r5]
	cmp	ip, #0
	bne	.L4314
	b	.L4445
.L4474:
	ldr	r1, .L4476+84
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L4476+12
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L4445
	sub	r2, fp, #36
	ldr	r0, [r4, #120]
	mov	r3, #4
	mvn	r4, #0
	mov	r1, #100
	str	r4, [r2, #-4]!
	blx	ip
	mov	r0, r4
	b	.L4315
.L4472:
	ldr	r5, .L4476+12
	mov	r0, #1
	ldr	r1, .L4476+88
	bl	dprint_vfmw
	ldr	ip, [r5]
	cmp	ip, #0
	bne	.L4463
	b	.L4445
.L4471:
	ldr	r1, .L4476+92
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L4476+12
	ldr	ip, [r3]
	cmp	ip, #0
	bne	.L4450
	b	.L4446
.L4469:
	ldr	r3, [r4, #20]
	cmp	r3, #0
	beq	.L4304
	add	r3, r4, #10747904
	add	r3, r3, #20480
	ldr	r2, [r3, #2384]
	cmp	r2, #0
	beq	.L4307
	ldrb	r2, [r3, #2380]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L4308
.L4307:
	add	r3, r4, #12992
	mov	r2, #0
	add	r3, r3, #16
.L4311:
	ldr	r1, [r3]
	cmp	r1, #0
	beq	.L4309
	ldrb	r1, [r3, #-4]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L4475
.L4309:
	add	r2, r2, #1
	add	r3, r3, #335872
	cmp	r2, #32
	add	r3, r3, #308
	bne	.L4311
	mvn	r3, #0
.L4444:
	cmn	r3, #1
	str	r3, [r0, #2672]
	beq	.L4304
	sub	ip, ip, #5
	mov	r3, #1
	clz	ip, ip
	strb	r3, [r0, #1043]
	strb	r3, [r0, #1042]
	mov	ip, ip, lsr #5
	strb	ip, [r0, #1041]
	b	.L4304
.L4468:
	strb	lr, [r0, #1043]
	ldr	r3, [r2, #712]
	str	r3, [r0, #2672]
	ldrb	r3, [r2, #708]	@ zero_extendqisi2
	strb	r3, [r0, #1041]
	ldrb	r3, [r2, #709]	@ zero_extendqisi2
	strb	r3, [r0, #1042]
	strb	r1, [r2, #704]
	b	.L4304
.L4475:
	movw	r3, #8500
	movt	r3, 5
	mla	r3, r3, r2, r4
	add	r3, r3, #12992
	add	r3, r3, #16
	ldr	r3, [r3, #4]
	b	.L4444
.L4308:
	ldr	r3, [r3, #2388]
	b	.L4444
.L4477:
	.align	2
.L4476:
	.word	.LC461
	.word	.LC463
	.word	.LC464
	.word	g_event_report
	.word	.LC469
	.word	.LC467
	.word	.LC471
	.word	.LC472
	.word	.LC465
	.word	.LC474
	.word	.LC473
	.word	.LC475
	.word	.LC476
	.word	.LC477
	.word	.LC478
	.word	.LC479
	.word	.LANCHOR1
	.word	.LC480
	.word	.LC481
	.word	.LC462
	.word	.LC466
	.word	.LC336
	.word	.LC468
	.word	.LC470
	UNWIND(.fnend)
	.size	MVC_DecOneNal, .-MVC_DecOneNal
	.align	2
	.global	MVC_DEC_DecodePacket
	.type	MVC_DEC_DecodePacket, %function
MVC_DEC_DecodePacket:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #44)
	sub	sp, sp, #44
	cmp	r1, #0
	mov	ip, #0
	mov	r4, r0
	str	ip, [fp, #-40]
	str	ip, [fp, #-44]
	str	ip, [fp, #-48]
	beq	.L4541
	ldr	r2, [r0, #224]
	ldrb	lr, [r0, #5]	@ zero_extendqisi2
	ldr	r3, [r2, #8]
	cmp	lr, #1
	mov	r3, r3, asl #16
	and	r3, r3, #196608
	str	r3, [r0, #108]
	ldr	r3, [r2]
	str	r3, [r0, #112]
	ldr	r3, [r2, #4]
	strb	ip, [r0, #10]
	str	r3, [r0, #116]
	beq	.L4481
	ldr	r3, [r2, #840]
	cmp	r3, #1
	addne	r5, r0, #11141120
	addne	r5, r5, #16384
	beq	.L4542
.L4482:
	mov	r0, r4
	bl	MVC_ReceivePacket
	ldr	r3, [r4, #232]
	str	r3, [r5, #2276]
.L4484:
	cmp	r0, #0
	mov	r3, #0
	strb	r3, [r4, #5]
	beq	.L4485
.L4504:
	mov	r0, #0
.L4536:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L4542:
	ldr	r3, [r2, #888]
	add	r5, r0, #11141120
	add	r5, r5, #16384
	cmp	r3, #1
	bne	.L4482
	ldr	r3, [r5, #2272]
	cmp	r3, #1
	bne	.L4482
	ldr	r3, [r5, #2276]
	str	r3, [r0, #232]
	str	ip, [r5, #2272]
	strb	ip, [r0, #5]
	b	.L4483
.L4485:
	ldr	r3, [r4, #232]
.L4483:
	mov	r2, #0
	str	r2, [r3, #64]
	ldr	r3, [r4, #232]
	add	r6, r4, #548
	mov	r0, r6
	ldr	r2, [r3, #12]
	ldr	r1, [r3, #8]
	bl	BsInit
	mov	r1, #32
	mov	r0, r6
	bl	BsGet
	ldr	r3, [r4, #232]
	mvn	r2, #0
	mov	r5, r0
	and	r0, r0, #31
	strb	r0, [r3, #2]
	ubfx	r1, r5, #5, #2
	ldr	r3, [r4, #232]
	strb	r1, [r3, #4]
	ldr	r3, [r4, #232]
	strb	r2, [r3, #5]
	ldr	r3, [r4, #232]
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	cmp	r3, #20
	beq	.L4543
.L4539:
	and	r5, r5, #27
	mov	r3, #0
	cmp	r5, #1
	strb	r3, [r4, #10]
	beq	.L4490
.L4491:
	mov	r0, r4
	bl	MVC_FindTrailZeros
	cmp	r0, #0
	bne	.L4544
.L4503:
	ldr	r3, [r4, #232]
	mov	r5, #0
	mov	r0, r6
	str	r5, [r3, #64]
	ldr	r3, [r4, #232]
	ldr	r1, [r3, #8]
	ldr	r2, [r3, #12]
	bl	BsInit
	mov	r1, r5
	mov	r0, r4
	bl	MVC_DecOneNal
	cmn	r0, #2
	beq	.L4536
	cmp	r0, r5
	beq	.L4504
	ldr	r3, .L4548
	ldr	ip, [r3]
	cmp	ip, r5
	beq	.L4540
	ldr	r0, [r4, #120]
	mov	r3, r5
	mov	r2, r5
	mov	r1, #113
	blx	ip
.L4540:
	mvn	r0, #0
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L4481:
	ldr	r0, [r0, #232]
	clz	r0, r0
	mov	r0, r0, lsr #5
	rsb	r0, r0, #0
	b	.L4484
.L4543:
	mov	r1, #24
	mov	r0, r6
	bl	BsGet
	ldr	r3, [r4, #232]
	ubfx	r2, r0, #23, #1
	strb	r2, [r3, #5]
	ldr	r1, [r4, #232]
	ldrsb	r2, [r1, #5]
	cmp	r2, #0
	bne	.L4539
	ubfx	ip, r0, #22, #1
	add	r3, r4, #12288
	cmp	ip, #0
	mov	r5, #1
	strb	ip, [r3, #705]
	ubfx	lr, r0, #6, #10
	ubfx	ip, r0, #2, #1
	strb	r5, [r3, #704]
	strb	ip, [r3, #708]
	ubfx	r0, r0, #1, #1
	str	lr, [r3, #712]
	movne	ip, r5
	strb	r0, [r3, #709]
	moveq	ip, #5
	strb	ip, [r1, #2]
	strb	r2, [r4, #10]
.L4490:
	sub	r2, fp, #32
	sub	r1, fp, #36
	mov	r0, r4
	bl	MVC_InquireSliceProperty
	cmp	r0, #0
	bne	.L4492
	ldr	r3, [fp, #-36]
	ldr	r2, [r4, #128]
	sub	r3, r3, #1
	clz	r3, r3
	mov	r3, r3, lsr #5
	cmp	r3, #0
	add	r3, r2, r3
	str	r3, [r4, #128]
	bne	.L4545
.L4493:
	ldr	r3, [fp, #-32]
	cmp	r3, #1
	bne	.L4491
	mvn	r1, #0
	mov	r0, r4
	bl	MVC_FlushDPB
	cmp	r0, #0
	bne	.L4546
.L4500:
	ldr	r0, [r4, #120]
	bl	FSP_GetFspType
	cmp	r0, #0
	bne	.L4491
	sub	r3, fp, #40
	sub	r2, fp, #44
	sub	r1, fp, #48
	ldr	r0, [r4, #120]
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r4, #224]
	ldr	r2, [r3, #724]
	cmp	r2, #1
	bne	.L4491
	ldr	r3, [fp, #-40]
	cmp	r3, #0
	ble	.L4547
.L4497:
	mov	r3, #1
	mvn	r0, #1
	strb	r3, [r4, #5]
	b	.L4536
.L4492:
	ldr	r1, [r4, #232]
	cmp	r1, #0
	beq	.L4502
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L4502:
	ldr	r3, .L4548
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L4540
	mov	r3, #0
	ldr	r0, [r4, #120]
	mov	r2, r3
	mov	r1, #113
	blx	ip
	mvn	r0, #0
	b	.L4536
.L4544:
	ldr	r1, .L4548+4
	mov	r0, #22
	bl	dprint_vfmw
	b	.L4503
.L4545:
	add	r5, r4, #11075584
	add	r5, r5, #40960
	ldrb	r3, [r5, #1033]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r4, #132]
	addeq	r3, r3, #1
	addne	r3, r3, #2
	str	r3, [r4, #132]
	ldr	r3, [r4, #64]
	cmp	r3, #0
	beq	.L4493
	ldr	r3, [r4, #232]
	mov	ip, #0
	mov	r0, r6
	mov	r2, #12
	ldr	r1, .L4548+8
	str	ip, [r3, #64]
	bl	BsInit
	mov	r1, #1
	mov	r0, r4
	bl	MVC_DecOneNal
	ldrb	r3, [r5, #1033]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r4, #132]
	subeq	r3, r3, #1
	subne	r3, r3, #2
	str	r3, [r4, #132]
	b	.L4497
.L4546:
	mov	r3, #0
	movw	r2, #14061
	ldr	r1, .L4548+12
	mov	r0, #22
	bl	dprint_vfmw
	b	.L4500
.L4541:
	mov	r0, r1
	movw	r3, #13945
	ldr	r2, .L4548+16
	ldr	r1, .L4548+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4536
.L4547:
	ldr	r3, [fp, #-44]
	cmp	r3, #32
	bgt	.L4497
	ldr	r3, [r4, #228]
	cmp	r3, #0
	bne	.L4497
	ldr	r3, [r4, #88]
	cmp	r3, #0
	beq	.L4491
	ldr	r1, [r4, #12]
	cmp	r1, #0
	beq	.L4491
	add	r5, r4, #11141120
	ldr	lr, [r4, #16]
	add	r5, r5, #16384
	ldr	r0, [r5, #2280]
	cmp	lr, r0
	beq	.L4491
	ldr	ip, [r5, #2284]
	cmp	r1, ip
	beq	.L4491
	stmib	sp, {r0, r1, lr}
	mov	r0, r2
	str	ip, [sp]
	ldr	r1, .L4548+24
	bl	dprint_vfmw
	ldr	r2, .L4548
	ldr	r3, [r4, #16]
	ldr	ip, [r2]
	str	r3, [r5, #2280]
	ldr	r3, [r4, #12]
	cmp	ip, #0
	str	r3, [r5, #2284]
	beq	.L4491
	mov	r3, #0
	mov	r1, #120
	mov	r2, r3
	ldr	r0, [r4, #120]
	blx	ip
	b	.L4491
.L4549:
	.align	2
.L4548:
	.word	g_event_report
	.word	.LC483
	.word	.LANCHOR1+432
	.word	.LC441
	.word	.LC13
	.word	.LC14
	.word	.LC482
	UNWIND(.fnend)
	.size	MVC_DEC_DecodePacket, .-MVC_DEC_DecodePacket
	.align	2
	.global	MVC_DEC_VDMPostProc
	.type	MVC_DEC_VDMPostProc, %function
MVC_DEC_VDMPostProc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r0, #228]
	add	r5, r0, #11141120
	add	r5, r5, #12288
	mov	r4, r0
	ldrb	ip, [r2, #17]	@ zero_extendqisi2
	ldr	r3, [r5, #3776]
	strb	ip, [r3, #14]
	ldrb	r2, [r2, #4]	@ zero_extendqisi2
	strb	r2, [r3, #15]
	ldrb	r7, [r0]	@ zero_extendqisi2
	str	r1, [r5, #3828]
	cmp	r7, #0
	bne	.L4551
	bl	MVC_ClearAllSlice
	mov	r0, r4
	bl	MVC_StorePicInDpb
	subs	r6, r0, #0
	bne	.L4562
	mov	r3, #1
	mov	r0, r6
	strb	r3, [r4, #4]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4551:
	bl	MVC_ClearAllSlice
	mov	r0, r4
	bl	MVC_StorePicInDpb
	subs	r2, r0, #0
	bne	.L4563
.L4554:
	mvn	r1, #0
	mov	r0, r4
	bl	MVC_FlushDPB
	subs	r2, r0, #0
	bne	.L4564
.L4555:
	ldr	ip, [r4, #40]
	add	r3, r4, #11075584
	add	r3, r3, #40960
	mov	r1, #0
	movw	r2, #23352
	strb	r1, [r4, #4]
	mov	r0, r1
	movt	r2, 1
	str	ip, [r3, #2700]
	mov	r5, #2
	strb	r1, [r3, #2688]
	mov	r4, #7
	str	r1, [r3, #2720]
	mov	lr, #32
	str	r1, [r3, #2724]
	mov	ip, #3
	str	r2, [r3, #2704]
	mvn	r1, #0
	mov	r2, #262144
	strb	r5, [r3, #2689]
	strb	r4, [r3, #2691]
	strb	lr, [r3, #2690]
	str	ip, [r3, #2712]
	str	r1, [r3, #2716]
	str	r2, [r3, #2728]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4562:
	ldr	r3, [r5, #3776]
	mov	r2, #1
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_ClearLogicFs
	mov	r2, r6
	ldr	r1, .L4565
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	MVC_ClearCurrPic
	mov	r0, r4
	mvn	r1, #0
	bl	MVC_ClearDPB
	str	r7, [r5, #3776]
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4564:
	ldr	r1, .L4565+4
	mov	r0, #1
	bl	dprint_vfmw
	b	.L4555
.L4563:
	ldr	r1, .L4565+8
	mov	r0, #1
	bl	dprint_vfmw
	b	.L4554
.L4566:
	.align	2
.L4565:
	.word	.LC484
	.word	.LC486
	.word	.LC485
	UNWIND(.fnend)
	.size	MVC_DEC_VDMPostProc, .-MVC_DEC_VDMPostProc
	.align	2
	.global	MVC_DEC_GetImageBuffer
	.type	MVC_DEC_GetImageBuffer, %function
MVC_DEC_GetImageBuffer:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #16)
	sub	sp, sp, #16
	ldr	r7, [r0, #48]
	mov	r5, r0
	cmp	r7, #0
	beq	.L4583
	movw	r4, #48312
	movw	r9, #47752
	movt	r4, 169
	add	r8, r0, #11075584
	add	r4, r0, r4
	movt	r9, 169
	add	r8, r8, #45056
	add	r9, r0, r9
	mov	ip, r4
	mov	r6, #0
.L4575:
	ldrb	r3, [ip, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4570
	cmp	ip, #0
	beq	.L4571
	ldr	lr, [r8, #2888]
	cmp	lr, #0
	beq	.L4571
	ldr	r2, [r8, #2696]
	rsb	r3, ip, r2
	cmp	r2, #0
	clz	r3, r3
	mov	r3, r3, lsr #5
	moveq	r3, #0
	cmp	r3, #0
	bne	.L4570
	mov	r1, r9
	b	.L4572
.L4573:
	ldr	r2, [r1, #4]!
	rsb	r0, ip, r2
	cmp	r2, #0
	clz	r0, r0
	mov	r0, r0, lsr #5
	moveq	r0, #0
	cmp	r0, #0
	bne	.L4570
.L4572:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L4573
.L4571:
	ldr	r0, [r5, #120]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	beq	.L4583
	ldr	r0, [r5, #120]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	bne	.L4603
	add	r1, r5, #584
	ldr	r0, [r5, #120]
	bl	FSP_ClearNotInVoQueue
	b	.L4603
.L4570:
	add	r6, r6, #1
	add	ip, ip, #816
	cmp	r6, r7
	bne	.L4575
	sub	r2, fp, #40
	sub	r1, fp, #44
	add	r0, r5, #584
	bl	GetQueueImgNum
	ldr	r1, .L4607
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r1, .L4607+4
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, [r5, #48]
	cmp	r3, #0
	beq	.L4605
	movw	r7, #47752
	add	r8, r5, #11075584
	movt	r7, 169
	add	r8, r8, #45056
	add	r7, r5, r7
	mov	r6, #0
.L4576:
	cmp	r4, #0
	ldrb	r3, [r4, #2]	@ zero_extendqisi2
	ldrb	r9, [r4, #5]	@ zero_extendqisi2
	beq	.L4587
	ldr	lr, [r8, #2888]
	cmp	lr, #0
	beq	.L4587
	ldr	r2, [r8, #2696]
	rsb	r1, r4, r2
	cmp	r2, #0
	clz	r1, r1
	mov	r1, r1, lsr #5
	moveq	r1, #0
	cmp	r1, #0
	bne	.L4589
	mov	r2, r7
	b	.L4580
.L4581:
	ldr	ip, [r2, #4]!
	rsb	r0, r4, ip
	cmp	ip, #0
	clz	r0, r0
	mov	r0, r0, lsr #5
	moveq	r0, #0
	cmp	r0, #0
	bne	.L4589
.L4580:
	add	r1, r1, #1
	cmp	r1, lr
	bne	.L4581
.L4587:
	mov	r2, #1
.L4579:
	str	r2, [sp, #4]
	mov	r0, #0
	mov	r2, r6
	str	r9, [sp]
	ldr	r1, .L4607+8
	add	r6, r6, #1
	bl	dprint_vfmw
	ldr	r3, [r5, #48]
	add	r4, r4, #816
	cmp	r3, r6
	bhi	.L4576
.L4582:
	ldr	r3, [fp, #-40]
	mov	r0, #0
	ldr	r2, [fp, #-44]
	ldr	r1, .L4607+12
	bl	dprint_vfmw
	ldr	r3, [r5, #48]
	ldr	r0, [r8, #2892]
	ldr	r2, [fp, #-44]
	sub	r3, r3, #2
	ldr	r1, [fp, #-40]
	rsb	r3, r0, r3
	add	r2, r2, r1
	cmp	r2, r3
	blt	.L4606
.L4603:
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4583:
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4589:
	mov	r2, #0
	b	.L4579
.L4606:
	ldr	r1, .L4607+16
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r5
	mov	r1, #1
	bl	MVC_ClearAll
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4605:
	add	r8, r5, #11075584
	add	r8, r8, #45056
	b	.L4582
.L4608:
	.align	2
.L4607:
	.word	.LC487
	.word	.LC488
	.word	.LC490
	.word	.LC489
	.word	.LC491
	UNWIND(.fnend)
	.size	MVC_DEC_GetImageBuffer, .-MVC_DEC_GetImageBuffer
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
	.align	2
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
	.type	__FUNCTION__.15741, %object
	.size	__FUNCTION__.15741, 18
__FUNCTION__.15741:
	.ascii	"MVC_WriteSliceMsg\000"
	.space	2
	.type	MVC_SarTable.16034, %object
	.size	MVC_SarTable.16034, 136
MVC_SarTable.16034:
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
	.type	__func__.16268, %object
	.size	__func__.16268, 11
__func__.16268:
	.ascii	"MVC_DecSEI\000"
	.space	1
	.type	__func__.14921, %object
	.size	__func__.14921, 17
__func__.14921:
	.ascii	"MVC_DirectOutput\000"
	.space	3
	.type	__func__.15501, %object
	.size	__func__.15501, 12
__func__.15501:
	.ascii	"MVC_InitDPB\000"
	.type	__FUNCTION__.14641, %object
	.size	__FUNCTION__.14641, 13
__FUNCTION__.14641:
	.ascii	"MVC_ClearDPB\000"
	.space	3
	.type	__func__.16379, %object
	.size	__func__.16379, 17
__func__.16379:
	.ascii	"MVC_FlushDecoder\000"
	.space	3
	.type	__FUNCTION__.14649, %object
	.size	__FUNCTION__.14649, 13
__FUNCTION__.14649:
	.ascii	"MVC_ClearAll\000"
	.space	3
	.type	__FUNCTION__.16506, %object
	.size	__FUNCTION__.16506, 13
__FUNCTION__.16506:
	.ascii	"MVC_DEC_Init\000"
	.space	3
	.type	__func__.15071, %object
	.size	__func__.15071, 18
__func__.15071:
	.ascii	"MVC_StorePicInDpb\000"
	.data
	.align	2
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
	.space	192
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
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"\012\012END of the bit buffer, copy the first packe" )
	ASCII(.ascii	"t!\012\012\000" )
	.space	2
.LC1:
	ASCII(.ascii	"0:phy:0x%x, 1:phy:0x%x; len0:%d len1:%d\012\000" )
	.space	3
.LC2:
	ASCII(.ascii	"0:phy:0x%x, len0:%d\012\000" )
	.space	3
.LC3:
	ASCII(.ascii	"%-50s%50d\012\000" )
	.space	1
.LC4:
	ASCII(.ascii	"MVC_FRAME %d, state=%d, is already output\012\000" )
	.space	1
.LC5:
	ASCII(.ascii	"plfs(fs=%p, eFoState=%d) is null, logic_fs_id = %d\012" )
	ASCII(.ascii	"\000" )
.LC6:
	ASCII(.ascii	"not used MVC_FRAME: (%d,%d)\012\000" )
	.space	3
.LC7:
	ASCII(.ascii	"MVC_FRAME skip: is_used=%d,skip=%d\012\000" )
.LC8:
	ASCII(.ascii	"topfield skip\012\000" )
	.space	1
.LC9:
	ASCII(.ascii	"bottom field skip\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"err(%d) > out_thr(%d)\012\000" )
	.space	1
.LC11:
	ASCII(.ascii	"exg_pts: %lld <-> %lld\012\000" )
.LC12:
	ASCII(.ascii	"stream MVC_FRAME packing type is %d! what can we do" )
	ASCII(.ascii	"?\012\000" )
	.space	2
.LC13:
	ASCII(.ascii	"../../core/syntax/mvc.c\000" )
.LC14:
	ASCII(.ascii	"NULL pointer: %s, L%d\012\000" )
	.space	1
.LC15:
	ASCII(.ascii	"framestore %d allocate apc %d\012\000" )
	.space	1
.LC16:
	ASCII(.ascii	"find APC, but logic_fs_id %d abnormal(ref=%d,plfs=%" )
	ASCII(.ascii	"p, pdfs=%p)\012\000" )
.LC17:
	ASCII(.ascii	"\012\000" )
	.space	2
.LC18:
	ASCII(.ascii	"pMvcCtx->DPB.fs[%d]: frame_num=%d poc=%d is_referen" )
	ASCII(.ascii	"ce=%d\012\000" )
	.space	2
.LC19:
	ASCII(.ascii	"pMvcCtx->DPB.fs_ref[%d]: frame_num=%d poc=%d is_ref" )
	ASCII(.ascii	"erence=%d\012\000" )
	.space	2
.LC20:
	ASCII(.ascii	"pMvcCtx->DPB.fs_ref[%d]: MVC_FRAME.poc=%d \012\000" )
.LC21:
	ASCII(.ascii	"\012 VFMW ** release streambuff=%p   bitstream_leng" )
	ASCII(.ascii	"th=%d\012\000" )
	.space	1
.LC22:
	ASCII(.ascii	"clear curr slice.\012\000" )
	.space	1
.LC23:
	ASCII(.ascii	"image size abnormal(%dx%d)\012\000" )
.LC24:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC25:
	ASCII(.ascii	"ERROR: FSP_ConfigInstance fail!\012\000" )
	.space	3
.LC26:
	ASCII(.ascii	"for P slice size of list equal 0(1st).\012\000" )
.LC27:
	ASCII(.ascii	"for P slice size of list equal 0(2nd).\012\000" )
.LC28:
	ASCII(.ascii	"for B slice size of two list all equal 0.\012\000" )
	.space	1
.LC29:
	ASCII(.ascii	"list[%d][%d]: frame_num=%d, poc=%d\012\000" )
.LC30:
	ASCII(.ascii	"init list error.\012\000" )
	.space	2
.LC31:
	ASCII(.ascii	"In one access unit,all non-base view should have th" )
	ASCII(.ascii	"e same subsps!\012\000" )
	.space	1
.LC32:
	ASCII(.ascii	"sps but mvc flag %d is wrong\012\000" )
	.space	2
.LC33:
	ASCII(.ascii	"save pic yuv :  structure = %d;  idc = %d\012\000" )
	.space	1
.LC34:
	ASCII(.ascii	"structure = %d pMvcCtx->CurrPic.pic_width_in_mb = %" )
	ASCII(.ascii	"d pMvcCtx->CurrPic.pic_height_in_mb = %d\012\000" )
	.space	3
.LC35:
	ASCII(.ascii	"nal_ref_idc=%d, structure=%d, image_id=%d, pmv_idc=" )
	ASCII(.ascii	"%d\012\000" )
	.space	1
.LC36:
	ASCII(.ascii	"logic MVC_FRAME id(=%d): get LogicFs error!\012\000" )
	.space	3
.LC37:
	ASCII(.ascii	"phy fs is null: pstDecodeFs = %p, pstDispOutFs = %p" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC38:
	ASCII(.ascii	"fuction return value is null,%s %d unknow error!!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC39:
	ASCII(.ascii	"SH: first_mb_in_slice\000" )
	.space	2
.LC40:
	ASCII(.ascii	"MVC_SliceCheck first_mb_in_slice >= MAX_MB_NUM_IN_P" )
	ASCII(.ascii	"IC error.\012\000" )
	.space	2
.LC41:
	ASCII(.ascii	"SH: slice_type\000" )
	.space	1
.LC42:
	ASCII(.ascii	"slice type = %d\012\000" )
	.space	3
.LC43:
	ASCII(.ascii	"slice type = %d, err\012\000" )
	.space	2
.LC44:
	ASCII(.ascii	"slice  pps id = %d\012\000" )
.LC45:
	ASCII(.ascii	"pps with this pic_parameter_set_id = %d havn't deco" )
	ASCII(.ascii	"de\012\000" )
	.space	1
.LC46:
	ASCII(.ascii	"sps with this pic_parameter_set_id havn't decode\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC47:
	ASCII(.ascii	"subsps with this seq_parameter_set_id = %d havn't d" )
	ASCII(.ascii	"ecoded\012\000" )
	.space	1
.LC48:
	ASCII(.ascii	"tmp slice  pps id = %d\012\000" )
.LC49:
	ASCII(.ascii	"MVC_PPSSPSCheckTmpId: pps with this pic_parameter_s" )
	ASCII(.ascii	"et_id = %d havn't decode\012\000" )
	.space	3
.LC50:
	ASCII(.ascii	"MVC_PPSSPSCheckTmpId: seq_parameter_set_id out of r" )
	ASCII(.ascii	"ange.\012\000" )
	.space	2
.LC51:
	ASCII(.ascii	"MVC_PPSSPSCheckTmpId: sps with this pic_parameter_s" )
	ASCII(.ascii	"et_id = %d havn't decode\012\000" )
	.space	3
.LC52:
	ASCII(.ascii	"new pic flag = %d\012\000" )
	.space	1
.LC53:
	ASCII(.ascii	"SH: ref_pic_list_reordering_flag_l0\000" )
.LC54:
	ASCII(.ascii	"SH: reordering_of_pic_nums_idc_l0\000" )
	.space	2
.LC55:
	ASCII(.ascii	"reorder idc l0 = %d, g_SeErrFlag=%d\012\000" )
	.space	3
.LC56:
	ASCII(.ascii	"SH: abs_diff_pic_num_minus1_l0\000" )
	.space	1
.LC57:
	ASCII(.ascii	"abs_diff_pic_num_minus1_l0 = %d, g_SeErrFlag=%d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC58:
	ASCII(.ascii	"SH: long_term_pic_idx_l0\000" )
	.space	3
.LC59:
	ASCII(.ascii	"SH: abs_diff_view_idx_minus1_l0\000" )
.LC60:
	ASCII(.ascii	"num of idc l0 exceed\012\000" )
	.space	2
.LC61:
	ASCII(.ascii	"SH: ref_pic_list_reordering_flag_l1\000" )
.LC62:
	ASCII(.ascii	"SH: reordering_of_pic_nums_idc_l1\000" )
	.space	2
.LC63:
	ASCII(.ascii	"reorder idc l1 = %d, g_SeErrFlag=%d\012\000" )
	.space	3
.LC64:
	ASCII(.ascii	"SH: abs_diff_pic_num_minus1_l1\000" )
	.space	1
.LC65:
	ASCII(.ascii	"abs_diff_pic_num_minus1_l1 = %d, g_SeErrFlag=%d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC66:
	ASCII(.ascii	"SH: long_term_pic_idx_l1\000" )
	.space	3
.LC67:
	ASCII(.ascii	"SH: abs_diff_view_idx_minus1_l1\000" )
.LC68:
	ASCII(.ascii	"num of idc l1 exceed\012\000" )
	.space	2
.LC69:
	ASCII(.ascii	"SH: luma_log2_weight_denom\000" )
	.space	1
.LC70:
	ASCII(.ascii	"SH: chroma_log2_weight_denom\000" )
	.space	3
.LC71:
	ASCII(.ascii	"WP log2 exceed  and err flag = %d\012\000" )
	.space	1
.LC72:
	ASCII(.ascii	"SH: luma_weight_flag_l0\000" )
.LC73:
	ASCII(.ascii	"SH: luma_weight_l0\000" )
	.space	1
.LC74:
	ASCII(.ascii	"SH: luma_offset_l0\000" )
	.space	1
.LC75:
	ASCII(.ascii	"SH: chroma_weight_flag_l0\000" )
	.space	2
.LC76:
	ASCII(.ascii	"SH: chroma_weight_l0\000" )
	.space	3
.LC77:
	ASCII(.ascii	"SH: chroma_offset_l0\000" )
	.space	3
.LC78:
	ASCII(.ascii	"SH: luma_weight_flag_l1\000" )
.LC79:
	ASCII(.ascii	"SH: luma_weight_l1\000" )
	.space	1
.LC80:
	ASCII(.ascii	"SH: luma_offset_l1\000" )
	.space	1
.LC81:
	ASCII(.ascii	"SH: chroma_weight_flag_l1\000" )
	.space	2
.LC82:
	ASCII(.ascii	"SH: chroma_weight_l1\000" )
	.space	3
.LC83:
	ASCII(.ascii	"SH: chroma_offset_l1\000" )
	.space	3
.LC84:
	ASCII(.ascii	"overflow MVC_MAX_MMCO_LEN\012\000" )
	.space	1
.LC85:
	ASCII(.ascii	"SH: memory_management_control_operation\000" )
.LC86:
	ASCII(.ascii	"SH: difference_of_pic_nums_minus1\000" )
	.space	2
.LC87:
	ASCII(.ascii	"SH: long_term_pic_num\000" )
	.space	2
.LC88:
	ASCII(.ascii	"SH: long_term_frame_idx\000" )
.LC89:
	ASCII(.ascii	"SH: max_long_term_frame_idx_plus1\000" )
	.space	2
.LC90:
	ASCII(.ascii	"mmco exceed 6\012\000" )
	.space	1
.LC91:
	ASCII(.ascii	"SH: no_output_of_prior_pics_flag\000" )
	.space	3
.LC92:
	ASCII(.ascii	"SH: long_term_reference_flag\000" )
	.space	3
.LC93:
	ASCII(.ascii	"IDR and no_output_of_prior_pics_flag = %d\012\000" )
	.space	1
.LC94:
	ASCII(.ascii	"SH: adaptive_ref_pic_marking_mode_flag\000" )
	.space	1
.LC95:
	ASCII(.ascii	"adaptive_ref_pic_marking_mode_flag = %d\012\000" )
	.space	3
.LC96:
	ASCII(.ascii	"MMCO para would save dec err\012\000" )
	.space	2
.LC97:
	ASCII(.ascii	"mulitislice diff no_out_of_prior_pics_flag, used fi" )
	ASCII(.ascii	"rst.\012\000" )
	.space	3
.LC98:
	ASCII(.ascii	"mulitislice diff long_term_reference_flag, used fir" )
	ASCII(.ascii	"st.\012\000" )
.LC99:
	ASCII(.ascii	"mulitislice diff adaptive_ref_pic_marking_mode_flag" )
	ASCII(.ascii	", used first.\012\000" )
	.space	2
.LC100:
	ASCII(.ascii	"TotalPicNum=%d, SliceNumInPic=%d, TotalNal=%d\012\000" )
	.space	1
.LC101:
	ASCII(.ascii	"SH: pic_parameter_set_id\000" )
	.space	3
.LC102:
	ASCII(.ascii	"pps id:%d in sliceheader err\012\000" )
	.space	2
.LC103:
	ASCII(.ascii	"PPS or SPS of this slice not valid\012\000" )
.LC104:
	ASCII(.ascii	"MVC_PPSSPSCheck failed, PPS or SPS of this slice no" )
	ASCII(.ascii	"t valid\012\000" )
.LC105:
	ASCII(.ascii	"SH: frame_num\000" )
	.space	2
.LC106:
	ASCII(.ascii	"IDR NAL but frame_num!=0.\012\000" )
	.space	1
.LC107:
	ASCII(.ascii	"SH: field_pic_flag\000" )
	.space	1
.LC108:
	ASCII(.ascii	"SH: bottom_field_flag\000" )
	.space	2
.LC109:
	ASCII(.ascii	"field first_mb_in_slice bigger than pic size\012\000" )
	.space	2
.LC110:
	ASCII(.ascii	"MVC_FRAME first_mb_in_slice bigger than pic size\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC111:
	ASCII(.ascii	"SH: idr_pic_id\000" )
	.space	1
.LC112:
	ASCII(.ascii	"idr_pic_id bigger than 65535\012\000" )
	.space	2
.LC113:
	ASCII(.ascii	"SH: pic_order_cnt_lsb\000" )
	.space	2
.LC114:
	ASCII(.ascii	"SH: delta_pic_order_cnt_bottom\000" )
	.space	1
.LC115:
	ASCII(.ascii	"SH: delta_pic_order_cnt[0]\000" )
	.space	1
.LC116:
	ASCII(.ascii	"SH: delta_pic_order_cnt[1]\000" )
	.space	1
.LC117:
	ASCII(.ascii	"SH: redundant_pic_cnt\000" )
	.space	2
.LC118:
	ASCII(.ascii	"redundant pic not support.\012\000" )
.LC119:
	ASCII(.ascii	"first_mb_in_slice in currslice small than prevslice" )
	ASCII(.ascii	" in same pic\012\000" )
	.space	3
.LC120:
	ASCII(.ascii	"SH: direct_spatial_mv_pred_flag\000" )
.LC121:
	ASCII(.ascii	"SH: num_ref_idx_override_flag\000" )
	.space	2
.LC122:
	ASCII(.ascii	"SH: num_ref_idx_l0_active_minus1\000" )
	.space	3
.LC123:
	ASCII(.ascii	"SH: num_ref_idx_l1_active_minus1\000" )
	.space	3
.LC124:
	ASCII(.ascii	"MVC_FRAME num_ref_idx_lx_active_minus1 exceed\012\000" )
	.space	1
.LC125:
	ASCII(.ascii	"field num_ref_idx_lx_active_minus1 exceed\012\000" )
	.space	1
.LC126:
	ASCII(.ascii	"reordering para dec err\012\000" )
	.space	3
.LC127:
	ASCII(.ascii	"apply_weights_flag=%d\012\000" )
	.space	1
.LC128:
	ASCII(.ascii	"wpt dec err\012\000" )
	.space	3
.LC129:
	ASCII(.ascii	"mark para dec err\012\000" )
	.space	1
.LC130:
	ASCII(.ascii	"SH: cabac_init_idc\000" )
	.space	1
.LC131:
	ASCII(.ascii	"cabac_init_idc bigger than 3\012\000" )
	.space	2
.LC132:
	ASCII(.ascii	"SH: slice_qp_delta\000" )
	.space	1
.LC133:
	ASCII(.ascii	"SH: disable_deblocking_filter_idc\000" )
	.space	2
.LC134:
	ASCII(.ascii	"disable_deblocking_filter_idc dec err\012\000" )
	.space	1
.LC135:
	ASCII(.ascii	"SH: slice_alpha_c0_offset_div2\000" )
	.space	1
.LC136:
	ASCII(.ascii	"slice_alpha_c0_offset_div2 dec err\012\000" )
.LC137:
	ASCII(.ascii	"SH: slice_beta_offset_div2\000" )
	.space	1
.LC138:
	ASCII(.ascii	"slice_beta_offset_div2 dec err\012\000" )
.LC139:
	ASCII(.ascii	"pMvcCtx->pCurrNal->nal_bitoffset = %d; code_len_byt" )
	ASCII(.ascii	"e = %d; bitstream_length = %d; pMvcCtx->pCurrNal->n" )
	ASCII(.ascii	"al_trail_zero_bit_num = %d\012\000" )
	.space	2
.LC140:
	ASCII(.ascii	"stream[%d]: bitsoffset = %d; valid_bitlen = %d; byt" )
	ASCII(.ascii	"espos = %x\012\000" )
	.space	1
.LC141:
	ASCII(.ascii	"nal_segment = %d is not expected value\012\000" )
.LC142:
	ASCII(.ascii	"stream[%d]: bitsoffset = %d; valid_bitlen = %d\012\000" )
.LC143:
	ASCII(.ascii	"   : delta_sl   \000" )
	.space	3
.LC144:
	ASCII(.ascii	"PPS: entropy_coding_mode_flag\000" )
	.space	2
.LC145:
	ASCII(.ascii	"PPS: pic_order_present_flag\000" )
.LC146:
	ASCII(.ascii	"PPS: num_slice_groups_minus1\000" )
	.space	3
.LC147:
	ASCII(.ascii	"MVC_BASELINE stream with FMO, not support.\012\000" )
.LC148:
	ASCII(.ascii	"PPS: num_ref_idx_l0_active_minus1\000" )
	.space	2
.LC149:
	ASCII(.ascii	"num_ref_idx_l0_active_minus1 out of range.\012\000" )
.LC150:
	ASCII(.ascii	"PPS: num_ref_idx_l1_active_minus1\000" )
	.space	2
.LC151:
	ASCII(.ascii	"num_ref_idx_l1_active_minus1 out of range.\012\000" )
.LC152:
	ASCII(.ascii	"PPS: weighted prediction flag\000" )
	.space	2
.LC153:
	ASCII(.ascii	"PPS: weighted_bipred_idc\000" )
	.space	3
.LC154:
	ASCII(.ascii	"weighted_bipred_idc out of range\012\000" )
	.space	2
.LC155:
	ASCII(.ascii	"PPS: pic_init_qp_minus26\000" )
	.space	3
.LC156:
	ASCII(.ascii	"PPS: pic_init_qs_minus26\000" )
	.space	3
.LC157:
	ASCII(.ascii	"PPS: chroma_qp_index_offset\000" )
.LC158:
	ASCII(.ascii	"PPS: deblocking_filter_control_present_flag\000" )
.LC159:
	ASCII(.ascii	"PPS: constrained_intra_pred_flag\000" )
	.space	3
.LC160:
	ASCII(.ascii	"PPS: redundant_pic_cnt_present_flag\000" )
.LC161:
	ASCII(.ascii	"redundant pic not support when find redundant slice" )
	ASCII(.ascii	" later, exit\012\000" )
	.space	3
.LC162:
	ASCII(.ascii	"PPS: transform_8x8_mode_flag\000" )
	.space	3
.LC163:
	ASCII(.ascii	"PPS: pic_scaling_matrix_present_flag\000" )
	.space	3
.LC164:
	ASCII(.ascii	"PPS: second_chroma_qp_index_offset\000" )
	.space	1
.LC165:
	ASCII(.ascii	"SPS: seq_scaling_list_present_flag\000" )
	.space	1
.LC166:
	ASCII(.ascii	"PPS: pic_scaling_list_present_flag\000" )
	.space	1
.LC167:
	ASCII(.ascii	"second_chroma_qp_index_offset out of range.\012\000" )
	.space	3
.LC168:
	ASCII(.ascii	"PPS: pic_parameter_set_id\000" )
	.space	2
.LC169:
	ASCII(.ascii	"pic_parameter_set_id(%d) out of range.\012\000" )
.LC170:
	ASCII(.ascii	"PPS: seq_parameter_set_id\000" )
	.space	2
.LC171:
	ASCII(.ascii	"seq_parameter_set_id out of range.\012\000" )
.LC172:
	ASCII(.ascii	"PPS decode error line: %d.\012\000" )
.LC173:
	ASCII(.ascii	"VUI: aspect_ratio_info_present_flag\000" )
.LC174:
	ASCII(.ascii	"VUI: aspect_ratio_idc\000" )
	.space	2
.LC175:
	ASCII(.ascii	"VUI: sar_width\000" )
	.space	1
.LC176:
	ASCII(.ascii	"VUI: sar_height\000" )
.LC177:
	ASCII(.ascii	"VUI: overscan_info_present_flag\000" )
.LC178:
	ASCII(.ascii	"VUI: overscan_appropriate_flag\000" )
	.space	1
.LC179:
	ASCII(.ascii	"VUI: video_signal_type_present_flag\000" )
.LC180:
	ASCII(.ascii	"VUI: video_format\000" )
	.space	2
.LC181:
	ASCII(.ascii	"VUI: video_full_range_flag\000" )
	.space	1
.LC182:
	ASCII(.ascii	"VUI: color_description_present_flag\000" )
.LC183:
	ASCII(.ascii	"VUI: colour_primaries\000" )
	.space	2
.LC184:
	ASCII(.ascii	"VUI: transfer_characteristics\000" )
	.space	2
.LC185:
	ASCII(.ascii	"VUI: matrix_coefficients\000" )
	.space	3
.LC186:
	ASCII(.ascii	"VUI: chroma_loc_info_present_flag\000" )
	.space	2
.LC187:
	ASCII(.ascii	"VUI: chroma_sample_loc_type_top_field\000" )
	.space	2
.LC188:
	ASCII(.ascii	"VUI: chroma_sample_loc_type_bottom_field\000" )
	.space	3
.LC189:
	ASCII(.ascii	"VUI: timing_info_present_flag\000" )
	.space	2
.LC190:
	ASCII(.ascii	"VUI: num_units_in_tick\000" )
	.space	1
.LC191:
	ASCII(.ascii	"VUI: time_scale\000" )
.LC192:
	ASCII(.ascii	"VUI: fixed_frame_rate_flag\000" )
	.space	1
.LC193:
	ASCII(.ascii	"VUI: nal_hrd_parameters_present_flag\000" )
	.space	3
.LC194:
	ASCII(.ascii	"VUI: cpb_cnt_minus1\000" )
.LC195:
	ASCII(.ascii	"VUI: bit_rate_scale\000" )
.LC196:
	ASCII(.ascii	"VUI: cpb_size_scale\000" )
.LC197:
	ASCII(.ascii	"hrd->cpb_cnt_minus1 out of range\012\000" )
	.space	2
.LC198:
	ASCII(.ascii	"VUI: bit_rate_value_minus1\000" )
	.space	1
.LC199:
	ASCII(.ascii	"VUI: cpb_size_value_minus1\000" )
	.space	1
.LC200:
	ASCII(.ascii	"VUI: cbr_flag\000" )
	.space	2
.LC201:
	ASCII(.ascii	"VUI: initial_cpb_removal_delay_length_minus1\000" )
	.space	3
.LC202:
	ASCII(.ascii	"VUI: cpb_removal_delay_length_minus1\000" )
	.space	3
.LC203:
	ASCII(.ascii	"VUI: dpb_output_delay_length_minus1\000" )
.LC204:
	ASCII(.ascii	"VUI: time_offset_length\000" )
.LC205:
	ASCII(.ascii	"VUI: vcl_hrd_parameters_present_flag\000" )
	.space	3
.LC206:
	ASCII(.ascii	"VUI: low_delay_hrd_flag\000" )
.LC207:
	ASCII(.ascii	"VUI: pic_struct_present_flag\000" )
	.space	3
.LC208:
	ASCII(.ascii	"VUI: bitstream_restriction_flag\000" )
.LC209:
	ASCII(.ascii	"VUI: motion_vectors_over_pic_boundaries_flag\000" )
	.space	3
.LC210:
	ASCII(.ascii	"VUI: max_bytes_per_pic_denom\000" )
	.space	3
.LC211:
	ASCII(.ascii	"VUI: max_bits_per_mb_denom\000" )
	.space	1
.LC212:
	ASCII(.ascii	"VUI: log2_max_mv_length_horizontal\000" )
	.space	1
.LC213:
	ASCII(.ascii	"VUI: log2_max_mv_length_vertical\000" )
	.space	3
.LC214:
	ASCII(.ascii	"VUI: num_reorder_frames\000" )
.LC215:
	ASCII(.ascii	"VUI: max_dec_frame_buffering\000" )
	.space	3
.LC216:
	ASCII(.ascii	"dar=%d, final_dar=%d\012\000" )
	.space	2
.LC217:
	ASCII(.ascii	"SPS: chroma_format_idc\000" )
	.space	1
.LC218:
	ASCII(.ascii	"pSPS->chroma_format_idc out of range.\012\000" )
	.space	1
.LC219:
	ASCII(.ascii	"SPS: bit_depth_luma_minus8\000" )
	.space	1
.LC220:
	ASCII(.ascii	"bit_depth_luma_minus8 not equal 0.\012\000" )
.LC221:
	ASCII(.ascii	"SPS: bit_depth_chroma_minus8\000" )
	.space	3
.LC222:
	ASCII(.ascii	"bit_depth_chroma_minus8 not equal 0.\012\000" )
	.space	2
.LC223:
	ASCII(.ascii	"SPS: qpprime_y_zero_trans_bypass_flag\000" )
	.space	2
.LC224:
	ASCII(.ascii	"qpprime_y_zero_trans_bypass_flag not equal 0.\012\000" )
	.space	1
.LC225:
	ASCII(.ascii	"SPS: seq_scaling_matrix_present_flag\000" )
	.space	3
.LC226:
	ASCII(.ascii	"SPS: log2_max_frame_num_minus4\000" )
	.space	1
.LC227:
	ASCII(.ascii	"pSPS->log2_max_frame_num_minus4 out of range.\012\000" )
	.space	1
.LC228:
	ASCII(.ascii	"SPS: pic_order_cnt_type\000" )
.LC229:
	ASCII(.ascii	"pSPS->pic_order_cnt_type out of range.\012\000" )
.LC230:
	ASCII(.ascii	"SPS: log2_max_pic_order_cnt_lsb_minus4\000" )
	.space	1
.LC231:
	ASCII(.ascii	"SPS: num_ref_frames\000" )
.LC232:
	ASCII(.ascii	"pSPS->log2_max_pic_order_cnt_lsb_minus4 out of rang" )
	ASCII(.ascii	"e.\012\000" )
	.space	1
.LC233:
	ASCII(.ascii	"SPS: delta_pic_order_always_zero_flag\000" )
	.space	2
.LC234:
	ASCII(.ascii	"SPS: offset_for_non_ref_pic\000" )
.LC235:
	ASCII(.ascii	"SPS: offset_for_top_to_bottom_field\000" )
.LC236:
	ASCII(.ascii	"SPS: num_ref_frames_in_pic_order_cnt_cycle\000" )
	.space	1
.LC237:
	ASCII(.ascii	"pSPS->num_ref_frames_in_pic_order_cnt_cycle out of " )
	ASCII(.ascii	"range.\012\000" )
	.space	1
.LC238:
	ASCII(.ascii	"SPS: offset_for_ref_frame[i]\000" )
	.space	3
.LC239:
	ASCII(.ascii	"SPS: gaps_in_frame_num_value_allowed_flag\000" )
	.space	2
.LC240:
	ASCII(.ascii	"SPS: pic_width_in_mbs_minus1\000" )
	.space	3
.LC241:
	ASCII(.ascii	"pSPS->pic_width_in_mbs_minus1 out of range(=%d).\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC242:
	ASCII(.ascii	"SPS: pic_height_in_map_units_minus1\000" )
.LC243:
	ASCII(.ascii	"SPS: frame_mbs_only_flag\000" )
	.space	3
.LC244:
	ASCII(.ascii	"pSPS->pic_height_in_map_units_minus1 out of range.\012" )
	ASCII(.ascii	"\000" )
.LC245:
	ASCII(.ascii	"pic size too large.\012\000" )
	.space	3
.LC246:
	ASCII(.ascii	"level_idc %d not support.\012\000" )
	.space	1
.LC247:
	ASCII(.ascii	"dpb size according level : %d\012\000" )
	.space	1
.LC248:
	ASCII(.ascii	"pSPS->num_ref_frames(%d) > DPB size(%d), try to sel" )
	ASCII(.ascii	"ect the reasonable one.\012\000" )
.LC249:
	ASCII(.ascii	"SPS: direct_8x8_inference_flag\000" )
	.space	1
.LC250:
	ASCII(.ascii	"SPS: frame_cropping_flag\000" )
	.space	3
.LC251:
	ASCII(.ascii	"SPS: frame_cropping_rect_left_offset\000" )
	.space	3
.LC252:
	ASCII(.ascii	"SPS: frame_cropping_rect_right_offset\000" )
	.space	2
.LC253:
	ASCII(.ascii	"SPS: frame_cropping_rect_top_offset\000" )
.LC254:
	ASCII(.ascii	"SPS: frame_cropping_rect_bottom_offset\000" )
	.space	1
.LC255:
	ASCII(.ascii	"SPS: vui_parameters_present_flag\000" )
	.space	3
.LC256:
	ASCII(.ascii	"max_dec_frame_buffering(%d) > MaxDpbSize(%d)\012\000" )
	.space	2
.LC257:
	ASCII(.ascii	"SPS: mb_adaptive_frame_field_flag\000" )
	.space	2
.LC258:
	ASCII(.ascii	"SPS: profile_idc\000" )
	.space	3
.LC259:
	ASCII(.ascii	"SPS: constrained_set0_flag\000" )
	.space	1
.LC260:
	ASCII(.ascii	"SPS: constrained_set1_flag\000" )
	.space	1
.LC261:
	ASCII(.ascii	"SPS: constrained_set2_flag\000" )
	.space	1
.LC262:
	ASCII(.ascii	"SPS: constrained_set3_flag\000" )
	.space	1
.LC263:
	ASCII(.ascii	"SPS: constrained_set4_flag\000" )
	.space	1
.LC264:
	ASCII(.ascii	"SPS: constrained_set5_flag\000" )
	.space	1
.LC265:
	ASCII(.ascii	"SPS: reserved_zero_2bits\000" )
	.space	3
.LC266:
	ASCII(.ascii	"SPS: level_idc\000" )
	.space	1
.LC267:
	ASCII(.ascii	"SPS: seq_parameter_set_id\000" )
	.space	2
.LC268:
	ASCII(.ascii	"MVC_BASELINE stream, try to decode, exit when FMO o" )
	ASCII(.ascii	"ccurred.\012\000" )
	.space	3
.LC269:
	ASCII(.ascii	"MVC_EXTENDED stream, try to decode, exit when datap" )
	ASCII(.ascii	"artition occurred.\012\000" )
	.space	1
.LC270:
	ASCII(.ascii	"others High profile stream, try to decode, exit whe" )
	ASCII(.ascii	"n high profile not support occurred.\012\000" )
	.space	3
.LC271:
	ASCII(.ascii	"profile_idc = %5d error, try to decode as main prof" )
	ASCII(.ascii	"ile.\012\000" )
	.space	3
.LC272:
	ASCII(.ascii	"level_idc = %5d error, try to decode as level_idc %" )
	ASCII(.ascii	"d.\012\000" )
	.space	1
.LC273:
	ASCII(.ascii	"Line %d: SPS[%d] decode error.\012\000" )
.LC274:
	ASCII(.ascii	"SUBSPS: num_views_minus1\000" )
	.space	3
.LC275:
	ASCII(.ascii	"pSubsps->num_views_minus1(%d) out of range.\012\000" )
	.space	3
.LC276:
	ASCII(.ascii	"SUBSPS: view_id[]\000" )
	.space	2
.LC277:
	ASCII(.ascii	"SUBSPS: num_anchor_refs_l0[]\000" )
	.space	3
.LC278:
	ASCII(.ascii	"SUBSPS: num_anchor_refs_l1[]\000" )
	.space	3
.LC279:
	ASCII(.ascii	"pSubsps->num_anchor_refs_l0(%d) out of range.\012\000" )
	.space	1
.LC280:
	ASCII(.ascii	"SUBSPS: anchor_ref_l0[][]\000" )
	.space	2
.LC281:
	ASCII(.ascii	"pSubsps->num_anchor_refs_l1(%d) out of range.\012\000" )
	.space	1
.LC282:
	ASCII(.ascii	"SUBSPS: anchor_ref_l1[][]\000" )
	.space	2
.LC283:
	ASCII(.ascii	"SUBSPS: num_level_values_signalled_minus1\000" )
	.space	2
.LC284:
	ASCII(.ascii	"SUBSPS: num_non_anchor_refs_l0[]\000" )
	.space	3
.LC285:
	ASCII(.ascii	"SUBSPS: num_non_anchor_refs_l1[]\000" )
	.space	3
.LC286:
	ASCII(.ascii	"pSubsps->num_non_anchor_refs_l0(%d) out of range.\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC287:
	ASCII(.ascii	"SUBSPS: non_anchor_ref_l0[][]\000" )
	.space	2
.LC288:
	ASCII(.ascii	"pSubsps->num_non_anchor_refs_l1(%d) out of range.\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC289:
	ASCII(.ascii	"SUBSPS: non_anchor_ref_l1[][]\000" )
	.space	2
.LC290:
	ASCII(.ascii	"num_level(%d) out of range.\012\000" )
	.space	3
.LC291:
	ASCII(.ascii	"SUBSPS: level_idc[]\000" )
.LC292:
	ASCII(.ascii	"SUBSPS: num_applicable_ops_minus1\000" )
	.space	2
.LC293:
	ASCII(.ascii	"num_ops(%d) out of range.\012\000" )
	.space	1
.LC294:
	ASCII(.ascii	"SUBSPS: applicable_op_temporal_id[][]\000" )
	.space	2
.LC295:
	ASCII(.ascii	"SUBSPS: applicable_op_num_target_views_minus1[][]\000" )
	.space	2
.LC296:
	ASCII(.ascii	"SUBSPS: applicable_op_num_views_minus1\000" )
	.space	1
.LC297:
	ASCII(.ascii	"applicable_op_num_target_views(%d) out of range.\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC298:
	ASCII(.ascii	"SUBSPS: applicable_op_target_view_id[][][]\000" )
	.space	1
.LC299:
	ASCII(.ascii	"pSubsps->applicable_op_num_views_minus1(%d) out of " )
	ASCII(.ascii	"range.\012\000" )
	.space	1
.LC300:
	ASCII(.ascii	"MVC VUI: vui_mvc_num_ops_minus1\000" )
.LC301:
	ASCII(.ascii	"vui_mvc_num_ops_minus1 %d out of range\012\000" )
.LC302:
	ASCII(.ascii	"MVC VUI: vui_mvc_temporal_id[]\000" )
	.space	1
.LC303:
	ASCII(.ascii	"SUBSPS VUI: vui_mvc_num_target_output_views_minus1[" )
	ASCII(.ascii	"]\000" )
	.space	3
.LC304:
	ASCII(.ascii	"vui_mvc_num_target_output_views_minus1 %d out of ra" )
	ASCII(.ascii	"nge\012\000" )
.LC305:
	ASCII(.ascii	"MVC VUI: vui_mvc_timing_info_present_flag\000" )
	.space	2
.LC306:
	ASCII(.ascii	"MVC VUI: vui_mvc_view_id[][]\000" )
	.space	3
.LC307:
	ASCII(.ascii	"MVC VUI: vui_mvc_num_units_in_tick\000" )
	.space	1
.LC308:
	ASCII(.ascii	"MVC VUI: vui_mvc_time_scale[]\000" )
	.space	2
.LC309:
	ASCII(.ascii	"MVC VUI: vui_mvc_fixed_frame_rate_flag\000" )
	.space	1
.LC310:
	ASCII(.ascii	"MVC VUI: vui_mvc_nal_hrd_parameters_present_flag[]\000" )
	.space	1
.LC311:
	ASCII(.ascii	"MVC VUI: cpb_cnt_minus1\000" )
.LC312:
	ASCII(.ascii	"MVC VUI: bit_rate_scale\000" )
.LC313:
	ASCII(.ascii	"MVC VUI: cpb_size_scale\000" )
.LC314:
	ASCII(.ascii	"MVC VUI: bit_rate_value_minus1\000" )
	.space	1
.LC315:
	ASCII(.ascii	"MVC VUI: cpb_size_value_minus1\000" )
	.space	1
.LC316:
	ASCII(.ascii	"MVC VUI: cbr_flag\000" )
	.space	2
.LC317:
	ASCII(.ascii	"MVC VUI: initial_cpb_removal_delay_length_minus1\000" )
	.space	3
.LC318:
	ASCII(.ascii	"MVC VUI: cpb_removal_delay_length_minus1\000" )
	.space	3
.LC319:
	ASCII(.ascii	"MVC VUI: dpb_output_delay_length_minus1\000" )
.LC320:
	ASCII(.ascii	"MVC VUI: time_offset_length\000" )
.LC321:
	ASCII(.ascii	"MVC VUI: vui_mvc_vcl_hrd_parameters_present_flag[]\000" )
	.space	1
.LC322:
	ASCII(.ascii	"MVC VUI: vui_mvc_low_delay_hrd_flag[]\000" )
	.space	2
.LC323:
	ASCII(.ascii	"MVC VUI: vui_mvc_pic_struct_present_flag[]\000" )
	.space	1
.LC324:
	ASCII(.ascii	"SUBSPS: profile_idc\000" )
.LC325:
	ASCII(.ascii	"SUBSPS: constrained_set0_flag\000" )
	.space	2
.LC326:
	ASCII(.ascii	"SUBSPS: constrained_set1_flag\000" )
	.space	2
.LC327:
	ASCII(.ascii	"SUBSPS: constrained_set2_flag\000" )
	.space	2
.LC328:
	ASCII(.ascii	"SUBSPS: constrained_set3_flag\000" )
	.space	2
.LC329:
	ASCII(.ascii	"SUBSPS: constrained_set4_flag\000" )
	.space	2
.LC330:
	ASCII(.ascii	"SUBSPS: constrained_set5_flag\000" )
	.space	2
.LC331:
	ASCII(.ascii	"SUBSPS: reserved_zero_2bits\000" )
.LC332:
	ASCII(.ascii	"SUBSPS: level_idc\000" )
	.space	2
.LC333:
	ASCII(.ascii	"SUBSPS: seq_parameter_set_id\000" )
	.space	3
.LC334:
	ASCII(.ascii	"profile_idc = %5d error\012\000" )
	.space	3
.LC335:
	ASCII(.ascii	"level_idc = %5d error, try to decode as level_idc 4" )
	ASCII(.ascii	"1.\012\000" )
	.space	1
.LC336:
	ASCII(.ascii	"SUBSPS decode error.\012\000" )
	.space	2
.LC337:
	ASCII(.ascii	"SUBSPS: bit_equal_to_one\000" )
	.space	3
.LC338:
	ASCII(.ascii	"SUBSPS Mvc Ext decode error.\012\000" )
	.space	2
.LC339:
	ASCII(.ascii	"SUBSPS: mvc_vui_parameters_present_flag\000" )
.LC340:
	ASCII(.ascii	"SUBSPS Mvc Vui Ext decode error.\012\000" )
	.space	2
.LC341:
	ASCII(.ascii	"SEI: frame_packing_arrangement_id\000" )
	.space	2
.LC342:
	ASCII(.ascii	"SEI: frame_packing_arrangement_cancel_flag\000" )
	.space	1
.LC343:
	ASCII(.ascii	"SEI: frame_packing_arrangement_type\000" )
.LC344:
	ASCII(.ascii	"SEI: quincunx_sampling_flag\000" )
.LC345:
	ASCII(.ascii	"SEI: content_interpretation_type\000" )
	.space	3
.LC346:
	ASCII(.ascii	"SEI: spatial_flipping_flag\000" )
	.space	1
.LC347:
	ASCII(.ascii	"SEI: frame0_flipped_flag\000" )
	.space	3
.LC348:
	ASCII(.ascii	"SEI: field_views_flag\000" )
	.space	2
.LC349:
	ASCII(.ascii	"SEI: current_frame_is_frame0_flag\000" )
	.space	2
.LC350:
	ASCII(.ascii	"SEI: frame0_self_contained_flag\000" )
.LC351:
	ASCII(.ascii	"SEI: frame1_self_contained_flag\000" )
.LC352:
	ASCII(.ascii	"SEI: frame0_grid_position_x\000" )
.LC353:
	ASCII(.ascii	"SEI: frame0_grid_position_y\000" )
.LC354:
	ASCII(.ascii	"SEI: frame1_grid_position_x\000" )
.LC355:
	ASCII(.ascii	"SEI: frame1_grid_position_y\000" )
.LC356:
	ASCII(.ascii	"SEI: frame_packing_arrangement_reserved_byte\000" )
	.space	3
.LC357:
	ASCII(.ascii	"SEI: frame_packing_arrangement_repetition_period\000" )
	.space	3
.LC358:
	ASCII(.ascii	"SEI: frame_packing_arrangement_extension_flag\000" )
	.space	2
.LC359:
	ASCII(.ascii	"DecPicTimingSEI but SPS is invalid.\012\000" )
	.space	3
.LC360:
	ASCII(.ascii	"SEI: cpb_removal_delay\000" )
	.space	1
.LC361:
	ASCII(.ascii	"SEI: dpb_output_delay\000" )
	.space	2
.LC362:
	ASCII(.ascii	"pic_struct\000" )
	.space	1
.LC363:
	ASCII(.ascii	"SEI nal dec payload type err\012\000" )
	.space	2
.LC364:
	ASCII(.ascii	"SEI nal dec payloadSize err\012\000" )
	.space	3
.LC365:
	ASCII(.ascii	"MVC_SEI_BUFFERING_PERIOD,offset = %d,payload_size =" )
	ASCII(.ascii	" %d \012\000" )
	.space	3
.LC366:
	ASCII(.ascii	"MVC_PassBytes err [%s][%d]\012\000" )
.LC367:
	ASCII(.ascii	"MVC_SEI_PIC_TIMING,offset = %d,payload_size = %d \012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC368:
	ASCII(.ascii	"MVC_SEI_PAN_SCAN_RECT,offset = %d,payload_size = %d" )
	ASCII(.ascii	" \012\000" )
	.space	2
.LC369:
	ASCII(.ascii	"MVC_SEI_FILLER_PAYLOAD,offset = %d,payload_size = %" )
	ASCII(.ascii	"d \012\000" )
	.space	1
.LC370:
	ASCII(.ascii	"MVC_SEI_USER_DATA_REGISTERED_ITU_T_T35, offset = %d" )
	ASCII(.ascii	", payload_size = %d \012\000" )
	.space	3
.LC371:
	ASCII(.ascii	"MVC_SEI_USER_DATA_UNREGISTERED, offset = %d, payloa" )
	ASCII(.ascii	"d_size = %d \012\000" )
	.space	3
.LC372:
	ASCII(.ascii	"SEI: itu_t_t35_country_code\000" )
.LC373:
	ASCII(.ascii	"SEI: itu_t_t35_country_code_extension_byte\000" )
	.space	1
.LC374:
	ASCII(.ascii	"SEI: itu_t_t35_provider_code\000" )
	.space	3
.LC375:
	ASCII(.ascii	"cann't dec usrdata\012\000" )
.LC376:
	ASCII(.ascii	"MVC_SEI_RECOVERY_POINT,offset = %d,payload_size = %" )
	ASCII(.ascii	"d \012\000" )
	.space	1
.LC377:
	ASCII(.ascii	"MVC_SEI_DEC_REF_PIC_MARKING_REPETITION,offset = %d," )
	ASCII(.ascii	"payload_size = %d \012\000" )
	.space	1
.LC378:
	ASCII(.ascii	"MVC_SEI_SPARE_PIC,offset = %d,payload_size = %d \012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC379:
	ASCII(.ascii	"MVC_SEI_SCENE_INFO,offset = %d,payload_size = %d \012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC380:
	ASCII(.ascii	"MVC_SEI_SUB_SEQ_INFO,offset = %d,payload_size = %d " )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC381:
	ASCII(.ascii	"MVC_SEI_SUB_SEQ_LAYER_CHARACTERISTICS,offset = %d,p" )
	ASCII(.ascii	"ayload_size = %d \012\000" )
	.space	2
.LC382:
	ASCII(.ascii	"MVC_SEI_SUB_SEQ_CHARACTERISTICS,offset = %d,payload" )
	ASCII(.ascii	"_size = %d \012\000" )
.LC383:
	ASCII(.ascii	"MVC_SEI_FULL_FRAME_FREEZE,offset = %d,payload_size " )
	ASCII(.ascii	"= %d \012\000" )
	.space	2
.LC384:
	ASCII(.ascii	"MVC_SEI_FULL_FRAME_FREEZE_RELEASE,offset = %d,paylo" )
	ASCII(.ascii	"ad_size = %d \012\000" )
	.space	2
.LC385:
	ASCII(.ascii	"MVC_SEI_FULL_FRAME_SNAPSHOT,offset = %d,payload_siz" )
	ASCII(.ascii	"e = %d \012\000" )
.LC386:
	ASCII(.ascii	"MVC_SEI_PROGRESSIVE_REFINEMENT_SEGMENT_START,offset" )
	ASCII(.ascii	" = %d,payload_size = %d \012\000" )
	.space	3
.LC387:
	ASCII(.ascii	"MVC_SEI_PROGRESSIVE_REFINEMENT_SEGMENT_END,offset =" )
	ASCII(.ascii	" %d,payload_size = %d \012\000" )
	.space	1
.LC388:
	ASCII(.ascii	"MVC_SEI_MOTION_CONSTRAINED_SLICE_GROUP_SET,offset =" )
	ASCII(.ascii	" %d,payload_size = %d \012\000" )
	.space	1
.LC389:
	ASCII(.ascii	"MVC_SEI_FILM_GRAIN_CHARACTERISTICS,offset = %d,payl" )
	ASCII(.ascii	"oad_size = %d \012\000" )
	.space	1
.LC390:
	ASCII(.ascii	"MVC_SEI_DEBLOCKING_FILTER_DISPLAY_PREFERENCE,offset" )
	ASCII(.ascii	" = %d,payload_size = %d \012\000" )
	.space	3
.LC391:
	ASCII(.ascii	"MVC_SEI_STEREO_VIDEO_INFO,offset = %d,payload_size " )
	ASCII(.ascii	"= %d \012\000" )
	.space	2
.LC392:
	ASCII(.ascii	"too much usrdat, cann't dec SEI\012\000" )
	.space	3
.LC393:
	ASCII(.ascii	"\012 mvc the stream is error,len:%d\012\000" )
	.space	2
.LC394:
	ASCII(.ascii	"\012Slice nal or IDR nal = %d\012\000" )
.LC395:
	ASCII(.ascii	"sliceheader dec err\012\000" )
	.space	3
.LC396:
	ASCII(.ascii	"MVC_InquireSliceProperty mvc flag %d is wrong\012\000" )
	.space	1
.LC397:
	ASCII(.ascii	"MvcDec destroy\012\000" )
.LC398:
	ASCII(.ascii	"MVC recycle image\012\000" )
	.space	1
.LC399:
	ASCII(.ascii	"pH264Ctx is %#x, pFrameStore is %#x\012\000" )
	.space	3
.LC400:
	ASCII(.ascii	"line: %d, pstLogicFsImage is NULL\012\000" )
	.space	1
.LC401:
	ASCII(.ascii	"InsertVO err:%d, MVC_ClearAll\012\000" )
	.space	1
.LC402:
	ASCII(.ascii	"mvc.c line %d: MVC_FRAME para err(ret=%d), recycle " )
	ASCII(.ascii	"image self\012\000" )
	.space	1
.LC403:
	ASCII(.ascii	"[%s][%d] MVC_OutputFrmToVO return %d !\012\000" )
.LC404:
	ASCII(.ascii	"[%s][%d] MVC_OutputFrmToVO return %d\012\000" )
	.space	2
.LC405:
	ASCII(.ascii	"%s %d MVC_OK != MVC_FlushDPB!!\012\000" )
.LC406:
	ASCII(.ascii	"%s %d MVC_OK != MVC_InitDPB!!\012\000" )
	.space	1
.LC407:
	ASCII(.ascii	"----------------- MVC_IMODE -> %d -----------------" )
	ASCII(.ascii	"-\012\000" )
	.space	2
.LC408:
	ASCII(.ascii	"Discard this B(poc=%d) befor P, is_ref_idc=%d.\012\000" )
.LC409:
	ASCII(.ascii	"***** VDM start, TotalPicNum=%d, pMvcCtx->CurrPic.s" )
	ASCII(.ascii	"tructure=%d.\012\000" )
	.space	3
.LC410:
	ASCII(.ascii	"MVC_DecVDM fail [%s][%d]\012\000" )
	.space	2
.LC411:
	ASCII(.ascii	"\012 receive streambuff=%p; phy_addr=0x%x; bitstrea" )
	ASCII(.ascii	"m_length=%d\012\000" )
	.space	3
.LC412:
	ASCII(.ascii	"nal_releaMVC_SE_ERR\012\000" )
	.space	3
.LC413:
	ASCII(.ascii	"cann't find slot for current nal\012\000" )
	.space	2
.LC414:
	ASCII(.ascii	"receive a zero packet\012\000" )
	.space	1
.LC415:
	ASCII(.ascii	"clear all dec para\012\000" )
.LC416:
	ASCII(.ascii	"line %d, get APC error, ret %d\012\000" )
.LC417:
	ASCII(.ascii	"InserFrmInDPB: cur pic struct = %d!\012\000" )
	.space	3
.LC418:
	ASCII(.ascii	"line: %d, pImage is NULL!\012\000" )
	.space	1
.LC419:
	ASCII(.ascii	"FS_ALLOC_ERR, MVC_ClearAll\012\000" )
.LC420:
	ASCII(.ascii	"Can not new logic fs! MVC_ClearAll\012\000" )
.LC421:
	ASCII(.ascii	"%s %d NULL== pMvcCtx->SPS || NULL == pMvcCtx->PPS |" )
	ASCII(.ascii	"| NULL == pMvcCtx->DecSlicePara!!\012\000" )
	.space	2
.LC422:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC423:
	ASCII(.ascii	"CurrPic.state is 'MVC_EMPTY'\012\000" )
	.space	2
.LC424:
	ASCII(.ascii	"MVC_StorePicInDpb return(%d) from L%d\012\000" )
	.space	1
.LC425:
	ASCII(.ascii	"Is IDR, but init DPB failed!\012\000" )
	.space	2
.LC426:
	ASCII(.ascii	"Is IDR, but FlushDPB failed!\012\000" )
	.space	2
.LC427:
	ASCII(.ascii	"MVC_DirectOutput mode\012\000" )
	.space	1
.LC428:
	ASCII(.ascii	"line %d, REPORT_IFRAME_ERR\012\000" )
.LC429:
	ASCII(.ascii	"line %d, return %d\012\000" )
.LC430:
	ASCII(.ascii	"err(%d) > ref_thr(%d)\012\000" )
	.space	1
.LC431:
	ASCII(.ascii	"MVC_Marking return %d\012\000" )
	.space	1
.LC432:
	ASCII(.ascii	"line %d: pMvcCtx->DPB.size = %d, ref %d, ltref %d\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC433:
	ASCII(.ascii	"line %d, MVC_GetMinPOC failed\012\000" )
	.space	1
.LC434:
	ASCII(.ascii	"%s: pos(%d) = pre_pos, force return.\012\000" )
	.space	2
.LC435:
	ASCII(.ascii	"GAP found while DPB is MVC_EMPTY!\012\000" )
	.space	1
.LC436:
	ASCII(.ascii	"MVC_FRAME num gap try to fill it \012\000" )
	.space	1
.LC437:
	ASCII(.ascii	"CurrFrameNum = %d  UnusedShortTermFrameNum = %d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC438:
	ASCII(.ascii	"cann't allocate MVC_FRAME store when gap find\012\000" )
	.space	1
.LC439:
	ASCII(.ascii	"allocate MVC_FRAME store when gap find\012\000" )
.LC440:
	ASCII(.ascii	"line %d: store gap pic err, ret=%d\012\000" )
.LC441:
	ASCII(.ascii	"line %d: flush dpb return %d\012\000" )
	.space	2
.LC442:
	ASCII(.ascii	"line %d: init dpb return %d\012\000" )
	.space	3
.LC443:
	ASCII(.ascii	"resolution error, the CAP_LEVEL_USER_DEFINE_WITH_OP" )
	ASCII(.ascii	"TION channel with s32ReRangeEn == 0 can't support s" )
	ASCII(.ascii	"uch bitstream.\012\000" )
	.space	2
.LC444:
	ASCII(.ascii	"s32MaxRefFrameNum < pMvcCtx->DPB.size, the CAP_LEVE" )
	ASCII(.ascii	"L_USER_DEFINE_WITH_OPTION channel can't support suc" )
	ASCII(.ascii	"h bitstream.\012\000" )
.LC445:
	ASCII(.ascii	"mem arrange err, MVC_ClearAll\012\000" )
	.space	1
.LC446:
	ASCII(.ascii	"line %d: MVC_FRAME gap(=%d) > dpb size(=%d)\012\000" )
	.space	3
.LC447:
	ASCII(.ascii	"MVC_FRAME num gap don't allowed but gap find\012\000" )
	.space	2
.LC448:
	ASCII(.ascii	"line %d: frame num(%d/%d) find gap in NON-I slice b" )
	ASCII(.ascii	"ut here gap is not allowed\012\000" )
	.space	1
.LC449:
	ASCII(.ascii	"line %d: dec gap failed\012\000" )
	.space	3
.LC450:
	ASCII(.ascii	"line %d: alloc framestore failed\012\000" )
	.space	2
.LC451:
	ASCII(.ascii	"dec_pts: %lld\012\000" )
	.space	1
.LC452:
	ASCII(.ascii	"dec_usertag: %lld\012\000" )
	.space	1
.LC453:
	ASCII(.ascii	"line %d: CurrPic.frame_store is NULL\012\000" )
	.space	2
.LC454:
	ASCII(.ascii	"get back frm\012\000" )
	.space	2
.LC455:
	ASCII(.ascii	"Start Reason: SliceParaNum, MaxBytesReceived = %d, " )
	ASCII(.ascii	"%d(thr=%d)\012\000" )
	.space	1
.LC456:
	ASCII(.ascii	"Too many slice or bitstream, err!\012\000" )
	.space	1
.LC457:
	ASCII(.ascii	"Start Reason: new_pic_flag\012\000" )
.LC458:
	ASCII(.ascii	"init pic err, find next recover point or next valid" )
	ASCII(.ascii	" sps, pps, or exit\012\000" )
	.space	1
.LC459:
	ASCII(.ascii	"MVC_DecList error, ret=%d\012\000" )
	.space	1
.LC460:
	ASCII(.ascii	"dec list err.\012\000" )
	.space	1
.LC461:
	ASCII(.ascii	"pMvcCtx->TotalNal = %d, type:%d\012\000" )
	.space	3
.LC462:
	ASCII(.ascii	"stop i want\012\000" )
	.space	3
.LC463:
	ASCII(.ascii	"***** NAL: IDR/Slice, nal_unit_type=%d, TotalSlice=" )
	ASCII(.ascii	"%d\012\000" )
	.space	1
.LC464:
	ASCII(.ascii	"*******TotalPicNum=%d********\012\000" )
	.space	1
.LC465:
	ASCII(.ascii	"***** NAL: PPS, nal_unit_type=%d, TotalPPS=%d\012\000" )
	.space	1
.LC466:
	ASCII(.ascii	"PPS decode error.\012\000" )
	.space	1
.LC467:
	ASCII(.ascii	"***** NAL: SPS, nal_unit_type=%d, TotalSPS=%d\012\000" )
	.space	1
.LC468:
	ASCII(.ascii	"SPS decode error.\012\000" )
	.space	1
.LC469:
	ASCII(.ascii	"***** NAL: SEI, nal_unit_type=%d\012\000" )
	.space	2
.LC470:
	ASCII(.ascii	"SEI decode error.\012\000" )
	.space	1
.LC471:
	ASCII(.ascii	"***** NAL: AUD, nal_unit_type=%d\012\000" )
	.space	2
.LC472:
	ASCII(.ascii	"***** NAL: EOSEQ, nal_unit_type=%d\012\000" )
.LC473:
	ASCII(.ascii	"***** NAL: FILL, nal_unit_type=%d\012\000" )
	.space	1
.LC474:
	ASCII(.ascii	"***** NAL: EOSTREAM, nal_unit_type=%d\012\000" )
	.space	1
.LC475:
	ASCII(.ascii	"***** NAL: SPSEXT, nal_unit_type=%d\012\000" )
	.space	3
.LC476:
	ASCII(.ascii	"***** NAL: PREFIX, nal_unit_type=%d\012\000" )
	.space	3
.LC477:
	ASCII(.ascii	"***** NAL: SUBSPS, nal_unit_type=%d\012\000" )
	.space	3
.LC478:
	ASCII(.ascii	"***** NAL: AUX, nal_unit_type=%d\012\000" )
	.space	2
.LC479:
	ASCII(.ascii	"***** NAL: EOPIC, nal_unit_type=%d\012\000" )
.LC480:
	ASCII(.ascii	"***** NAL: UNSUPPORT, nal_unit_type=%d,nalu header:" )
	ASCII(.ascii	"%x\012\000" )
	.space	1
.LC481:
	ASCII(.ascii	"nal_header != 0x00000100 not support.\012\000" )
	.space	1
.LC482:
	ASCII(.ascii	"IsSizeChanged = %d,TotalPicNum = %d,old w/h = %d/%d" )
	ASCII(.ascii	",new w/h = %d/%d\012\000" )
	.space	3
.LC483:
	ASCII(.ascii	"MVC_FindTrailZeros ERR\012\000" )
.LC484:
	ASCII(.ascii	"store pic err, ret = %d\012\000" )
	.space	3
.LC485:
	ASCII(.ascii	"MVC_IMODE nal store pic err, ret = %d\012\000" )
	.space	1
.LC486:
	ASCII(.ascii	"MVC_IMODE nal flush dpb err, ret = %d\012\000" )
	.space	1
.LC487:
	ASCII(.ascii	"cann't find FrameStore\012\000" )
.LC488:
	ASCII(.ascii	"========== MVC FrameStore state(is_used, is_in_dpb," )
	ASCII(.ascii	" MVC_IsOutDPB) ========\012\000" )
.LC489:
	ASCII(.ascii	"ReadImgNum = %d, NewImgNum = %d\012\000" )
	.space	3
.LC490:
	ASCII(.ascii	"%02d: %d %d %d\012\000" )
.LC491:
	ASCII(.ascii	"FrameStore leak, MVC_ClearAll\012\000" )
	.bss
	.align	2
.LANCHOR2 = . + 0
.LANCHOR3 = . + 8184
	.type	pps_tmp.15954, %object
	.size	pps_tmp.15954, 2240
pps_tmp.15954:
	.space	2240
	.type	sps_tmp.16090, %object
	.size	sps_tmp.16090, 3992
sps_tmp.16090:
	.space	3992
	.type	MvcTmpBuf, %object
	.size	MvcTmpBuf, 68
MvcTmpBuf:
	.space	68
	.type	cnt.14907, %object
	.size	cnt.14907, 4
cnt.14907:
	.space	4
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
