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
	.file	"vfmw_write_yuv.c"
	.text
	.align	2
	.global	YUV_DumpFrame_Cmp
	.type	YUV_DumpFrame_Cmp, %function
YUV_DumpFrame_Cmp:
	UNWIND(.fnstart)
	@ args = 44, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, .L2
	mov	r0, #32
	ldr	r1, .L2+4
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L3:
	.align	2
.L2:
	.word	.LANCHOR0
	.word	.LC0
	UNWIND(.fnend)
	.size	YUV_DumpFrame_Cmp, .-YUV_DumpFrame_Cmp
	.align	2
	.global	YUV_DumpFrame_Tile
	.type	YUV_DumpFrame_Tile, %function
YUV_DumpFrame_Tile:
	UNWIND(.fnstart)
	@ args = 32, pretend = 0, frame = 72
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #100)
	sub	sp, sp, #100
	cmp	r0, #0
	mov	r6, r2
	mov	r8, r3
	str	r0, [fp, #-112]
	mov	r7, r1
	ldr	r3, [fp, #20]
	ldr	lr, [fp, #28]
	ldr	r2, [fp, #32]
	beq	.L4
	sub	r1, r3, #1
	cmp	r1, #16
	bhi	.L6
	mov	r0, #1
	movw	ip, #7683
	mov	r1, r0, asl r1
	and	ip, ip, r1
	cmp	ip, #0
	bne	.L7
	tst	r1, #65536
	bne	.L8
.L6:
	cmp	r3, #16
	add	r1, r8, #255
	bic	r1, r1, #255
	beq	.L60
	sub	r3, r3, #17
	cmp	r3, #1
	bls	.L61
	ldr	r3, [fp, #4]
	mov	r9, #0
	mov	r4, r9
	add	r3, r3, #31
	bic	r3, r3, #31
.L10:
	ldr	r0, [r2, #168]
	str	r7, [fp, #-80]
	cmp	r0, #10
	str	r6, [fp, #-72]
	muleq	r3, r3, r1
	movne	r5, #0
	movne	ip, r5
	ldrb	r1, [r2, #66]	@ zero_extendqisi2
	eor	r1, r1, #2
	addeq	r3, r3, r3, lsl #1
	addeq	ip, r7, r3, asr #1
	sub	r3, fp, #96
	str	ip, [fp, #-76]
	mlaeq	r5, r9, r4, ip
	cmp	r0, #0
	ldr	r4, .L64
	moveq	r0, #8
	ldr	r9, .L64+4
	cmp	r0, lr
	str	r0, [fp, #-64]
	ldr	r10, [r4]
	sub	r0, fp, #80
	movge	r4, lr
	ldr	lr, [r2, #112]
	ldr	r2, [r2, #144]
	movlt	r4, #8
	ldr	r9, [r9]
	add	ip, r10, #9437184
	str	lr, [fp, #-52]
	ubfx	lr, r1, #1, #1
	str	r2, [fp, #-48]
	mov	r1, r8
	ldr	r2, [fp, #4]
	str	r4, [fp, #-60]
	add	r4, r9, #9437184
	str	r5, [fp, #-68]
	str	r10, [fp, #-96]
	str	ip, [fp, #-88]
	str	r9, [fp, #-92]
	str	r4, [fp, #-84]
	str	lr, [fp, #-56]
	bl	IMAGE_ConvertTo2D
	ldr	r3, [fp, #-60]
	cmp	r3, #10
	beq	.L62
	ldr	r3, [fp, #4]
	ldr	r0, [fp, #-96]
	mul	r3, r8, r3
	str	r3, [fp, #-108]
.L19:
	ldr	r3, .L64+8
	ldr	r2, [fp, #-112]
	ldr	r1, [fp, #-108]
	str	r3, [fp, #-116]
	ldr	r3, [r3, #44]
	blx	r3
.L20:
	ldr	r0, [fp, #-60]
	cmp	r0, #10
	beq	.L63
	ldr	r3, [fp, #4]
	ldr	r9, [fp, #-88]
	movs	r10, r3, lsr #1
	ldreq	r6, .L64+12
	ldreq	r5, .L64+16
	beq	.L26
.L24:
	ldr	r6, .L64+12
	mov	r1, #0
	ldr	r5, .L64+16
	mov	r3, r8, lsr #1
	mov	r2, r8, asl #1
	str	r2, [fp, #-104]
	mov	r2, r1
.L34:
	cmp	r0, #10
	beq	.L27
	cmp	r3, #0
	movne	r0, r1, lsr #1
	addne	ip, r9, #1
	addne	r7, r3, r0
	beq	.L29
.L33:
	ldrb	r4, [ip, #-1]	@ zero_extendqisi2
	ldr	lr, [r6]
	strb	r4, [lr, r0]
	ldrb	r4, [ip], #2	@ zero_extendqisi2
	ldr	lr, [r5]
	strb	r4, [lr, r0]
	add	r0, r0, #1
	cmp	r0, r7
	bne	.L33
	ldr	r0, [fp, #-60]
.L29:
	add	r9, r9, r8
.L32:
	add	r2, r2, #1
	add	r1, r1, r8
	cmp	r2, r10
	bcc	.L34
.L25:
	cmp	r0, #10
	beq	.L36
.L26:
	ldr	r3, [fp, #-108]
	mov	r4, r3, lsr #2
.L58:
	ldr	r7, [fp, #-112]
	mov	r1, r4
	ldr	r0, [r5]
	ldr	r5, [fp, #-116]
	mov	r2, r7
	ldr	r3, [r5, #44]
	blx	r3
	mov	r1, r4
	mov	r2, r7
	ldr	r3, [r5, #44]
	ldr	r0, [r6]
	blx	r3
	ldr	ip, [fp, #16]
	ldr	r0, [fp, #-60]
	mov	r2, r8
	ldr	r1, [fp, #-64]
	str	ip, [sp, #8]
	ldr	ip, [fp, #8]
	ldr	r3, [fp, #4]
	str	ip, [sp, #4]
	ldr	ip, [fp, #12]
	str	ip, [sp]
	ldr	ip, [fp, #-116]
	ldr	ip, [ip, #64]
	str	r0, [sp, #16]
	str	r1, [sp, #12]
	ldr	r0, .L64+20
	ldr	r1, .L64+24
	blx	ip
.L4:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L27:
	cmp	r3, #0
	beq	.L30
	bic	ip, r1, #1
	mov	r0, r9
	mov	lr, #0
.L31:
	ldrh	r7, [r0]
	add	lr, lr, #1
	ldr	r4, [r6]
	cmp	lr, r3
	add	r0, r0, #4
	strh	r7, [r4, ip]	@ movhi
	ldrh	r7, [r0, #-2]
	ldr	r4, [r5]
	strh	r7, [r4, ip]	@ movhi
	add	ip, ip, #2
	bne	.L31
	ldr	r0, [fp, #-60]
.L30:
	ldr	ip, [fp, #-104]
	add	r9, r9, ip
	b	.L32
.L60:
	ldr	r3, [fp, #24]
	cmp	r3, #8
	ldr	r3, [fp, #4]
	ble	.L38
	cmp	r1, #0
	add	r4, r1, #3
	add	r5, r3, #31
	movge	r4, r1
	bic	r9, r5, #31
	mov	r4, r4, asr #2
	b	.L10
.L38:
	mov	r9, #0
	mov	r4, r9
	b	.L10
.L63:
	ldr	r1, [fp, #-108]
	cmp	r1, #0
	beq	.L22
	ldr	r2, .L64+28
	mov	ip, #2
	mov	r3, #0
	mov	r0, r1
.L23:
	ldr	lr, [fp, #-88]
	mov	r4, r3, asl #1
	ldr	r1, [fp, #-84]
	ldr	r5, [r2]
	ldrb	r6, [lr, r3]	@ zero_extendqisi2
	ldrb	r1, [r1, r3, lsr #2]	@ zero_extendqisi2
	ldr	lr, .L64+28
	and	r1, r1, #3
	add	r1, r1, r6, lsl #2
	strh	r1, [r5, r4]	@ movhi
	ldr	r1, [fp, #-88]
	ldr	r6, [fp, #-84]
	add	r1, r1, r3
	ldr	r4, [r2]
	ldrb	r5, [r1, #1]	@ zero_extendqisi2
	ldrb	r1, [r6, r3, lsr #2]	@ zero_extendqisi2
	ubfx	r1, r1, #2, #2
	add	r1, r1, r5, lsl #2
	strh	r1, [r4, ip]	@ movhi
	ldr	r1, [fp, #-88]
	ldr	r6, [fp, #-84]
	add	r1, r1, r3
	ldr	r4, [r2]
	ldrb	r5, [r1, #2]	@ zero_extendqisi2
	add	r4, r4, ip
	ldrb	r1, [r6, r3, lsr #2]	@ zero_extendqisi2
	ubfx	r1, r1, #4, #2
	add	r1, r1, r5, lsl #2
	strh	r1, [r4, #2]	@ movhi
	ldr	r5, [fp, #-88]
	ldr	r1, [fp, #-84]
	add	r5, r5, r3
	ldr	r4, [r2]
	ldrb	r1, [r1, r3, lsr #2]	@ zero_extendqisi2
	add	r3, r3, #4
	ldrb	r5, [r5, #3]	@ zero_extendqisi2
	add	r4, r4, ip
	cmp	r3, r0
	add	ip, ip, #8
	mov	r1, r1, lsr #6
	add	r1, r1, r5, lsl #2
	strh	r1, [r4, #4]	@ movhi
	bcc	.L23
	ldr	r3, [fp, #4]
	ldr	r9, [lr]
	ldr	r0, [fp, #-60]
	movs	r10, r3, lsr #1
	ldreq	r6, .L64+12
	ldreq	r5, .L64+16
	bne	.L24
	b	.L25
.L62:
	ldr	r3, [fp, #4]
	ldr	r2, .L64+28
	mul	r3, r8, r3
	cmp	r3, #0
	mov	r0, r3
	str	r3, [fp, #-108]
	beq	.L16
	mov	ip, #2
	mov	r3, #0
.L17:
	ldr	lr, [fp, #-96]
	mov	r4, r3, asl #1
	ldr	r1, [fp, #-92]
	ldr	r5, [r2]
	ldrb	r6, [lr, r3]	@ zero_extendqisi2
	ldrb	r1, [r1, r3, lsr #2]	@ zero_extendqisi2
	ldr	lr, .L64+28
	and	r1, r1, #3
	add	r1, r1, r6, lsl #2
	strh	r1, [r5, r4]	@ movhi
	ldr	r1, [fp, #-96]
	ldr	r6, [fp, #-92]
	add	r1, r1, r3
	ldr	r4, [r2]
	ldrb	r5, [r1, #1]	@ zero_extendqisi2
	ldrb	r1, [r6, r3, lsr #2]	@ zero_extendqisi2
	ubfx	r1, r1, #2, #2
	add	r1, r1, r5, lsl #2
	strh	r1, [r4, ip]	@ movhi
	ldr	r1, [fp, #-96]
	ldr	r6, [fp, #-92]
	add	r1, r1, r3
	ldr	r4, [r2]
	ldrb	r5, [r1, #2]	@ zero_extendqisi2
	add	r4, r4, ip
	ldrb	r1, [r6, r3, lsr #2]	@ zero_extendqisi2
	ubfx	r1, r1, #4, #2
	add	r1, r1, r5, lsl #2
	strh	r1, [r4, #2]	@ movhi
	ldr	r5, [fp, #-96]
	ldr	r1, [fp, #-92]
	add	r5, r5, r3
	ldr	r4, [r2]
	ldrb	r1, [r1, r3, lsr #2]	@ zero_extendqisi2
	add	r3, r3, #4
	ldrb	r5, [r5, #3]	@ zero_extendqisi2
	add	r4, r4, ip
	cmp	r3, r0
	add	ip, ip, #8
	mov	r1, r1, lsr #6
	add	r1, r1, r5, lsl #2
	strh	r1, [r4, #4]	@ movhi
	bcc	.L17
	ldr	r3, [fp, #-60]
	ldr	r0, [lr]
	cmp	r3, #10
	bne	.L19
.L18:
	ldr	r3, .L64+8
	ldr	r1, [fp, #-108]
	ldr	r2, [fp, #-112]
	str	r3, [fp, #-116]
	mov	r1, r1, asl #1
	ldr	r3, [r3, #44]
	blx	r3
	b	.L20
.L7:
	ldr	r1, [fp, #4]
	add	r8, r8, #15
	bic	r8, r8, #15
	add	r1, r1, #15
	bic	r1, r1, #15
	str	r1, [fp, #4]
	b	.L6
.L61:
	ldr	r3, [fp, #24]
	cmp	r3, #8
	ldr	r3, [fp, #4]
	add	r3, r3, #63
	bic	r3, r3, #63
	ble	.L38
	cmp	r1, #0
	add	r4, r1, #3
	mov	r9, r3
	movge	r4, r1
	mov	r4, r4, asr #2
	b	.L10
.L8:
	ldr	r1, [fp, #4]
	add	r8, r8, #7
	bic	r8, r8, #7
	add	r1, r1, #7
	bic	r1, r1, #7
	str	r1, [fp, #4]
	b	.L6
.L22:
	ldr	r2, [fp, #4]
	ldr	r3, .L64+28
	movs	r10, r2, lsr #1
	ldr	r9, [r3]
	ldreq	r6, .L64+12
	ldreq	r5, .L64+16
	bne	.L24
.L36:
	ldr	r3, [fp, #-108]
	mov	r4, r3, lsr #1
	b	.L58
.L16:
	ldr	r0, [r2]
	b	.L18
.L65:
	.align	2
.L64:
	.word	pY
	.word	pY_2bit
	.word	vfmw_Osal_Func_Ptr_S
	.word	pVl
	.word	pUl
	.word	.LC1
	.word	.LANCHOR0+20
	.word	pPixelArray
	UNWIND(.fnend)
	.size	YUV_DumpFrame_Tile, .-YUV_DumpFrame_Tile
	.align	2
	.global	YUV_DumpImage
	.type	YUV_DumpImage, %function
YUV_DumpImage:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #56)
	sub	sp, sp, #56
	ldr	r9, .L94
	mov	r3, #0
	mov	r5, r0
	mov	r4, r1
	str	r3, [fp, #-60]
	ldr	r2, [r9, r0, asl #2]
	str	r3, [fp, #-56]
	cmp	r2, r3
	str	r3, [fp, #-52]
	str	r3, [fp, #-48]
	str	r3, [fp, #-44]
	str	r3, [fp, #-40]
	beq	.L68
	add	r3, r1, #512
	ldrb	r8, [r1, #64]	@ zero_extendqisi2
	ldrd	r6, [r3, #-8]
	orrs	r2, r6, r7
	beq	.L69
	ldrd	r2, [r3]
	orrs	r1, r2, r3
	bne	.L72
.L69:
	ldr	r2, [r4, #20]
	sub	r0, fp, #60
	ldr	r3, .L94+4
	str	r2, [fp, #-52]
	ldr	r3, [r3, #160]
	blx	r3
	subs	r6, r0, #0
	beq	.L92
	ldr	r3, [r4, #24]
	ldr	r2, [r4, #20]
	rsb	r2, r2, r3
	add	r2, r6, r2
.L72:
	cmp	r2, #0
	cmpne	r6, #0
	beq	.L68
	ldr	r3, .L94+8
	ldr	lr, [r3, r5, asl #2]
	ldr	ip, [lr, #1136]
	cmp	ip, #0
	beq	.L74
	ldr	r2, .L94+12
	mov	r0, #32
	ldr	r1, .L94+16
	bl	dprint_vfmw
.L75:
	ldr	r3, .L94+4
	mov	r0, r6
	ldr	r3, [r3, #164]
	blx	r3
.L68:
	ldr	r3, .L94+20
	ldr	r2, [r3, r5, asl #2]
	cmp	r2, #0
	beq	.L76
	add	r3, r4, #432
	ldrd	r0, [r3]
	orrs	r3, r0, r1
	beq	.L76
	ldr	r3, [r4, #420]
	cmp	r3, #0
	bne	.L93
.L76:
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L93:
	ldr	ip, .L94+4
	mov	r1, r3
	ldr	r3, [ip, #44]
	blx	r3
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L74:
	ldr	r3, .L94+24
	tst	r8, #28
	ldr	r7, [r4, #168]
	mov	r1, r6
	str	r4, [sp, #28]
	moveq	r8, #1
	ldr	r3, [r3]
	movne	r8, #0
	ldr	r0, [r9, r5, asl #2]
	str	r7, [sp, #20]
	str	r3, [sp, #24]
	ldr	r9, [lr, #52]
	ldr	r7, [r4, #112]
	ldr	lr, [r4, #72]
	ldr	r3, [r4, #68]
	str	r9, [sp, #16]
	str	ip, [sp, #4]
	str	r8, [sp, #12]
	str	r7, [sp, #8]
	str	lr, [sp]
	bl	YUV_DumpFrame_Tile
	b	.L75
.L92:
	ldr	r1, .L94+28
	mov	r0, #32
	bl	dprint_vfmw
	b	.L68
.L95:
	.align	2
.L94:
	.word	vfmw_save_yuv_file
	.word	vfmw_Osal_Func_Ptr_S
	.word	s_pstVfmwChan
	.word	.LANCHOR0
	.word	.LC0
	.word	vfmw_save_metadata_reorder_file
	.word	g_SaveYUVBitWidth
	.word	.LC2
	UNWIND(.fnend)
	.size	YUV_DumpImage, .-YUV_DumpImage
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.14051, %object
	.size	__func__.14051, 18
__func__.14051:
	.ascii	"YUV_DumpFrame_Cmp\000"
	.space	2
	.type	__func__.14108, %object
	.size	__func__.14108, 19
__func__.14108:
	.ascii	"YUV_DumpFrame_Tile\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"%s not support now.\012\000" )
	.space	3
.LC1:
	ASCII(.ascii	"%s: Width=%d, Height=%d, Stride=%d, PicStructure=%d" )
	ASCII(.ascii	", ChromaIDC=%d, RealBitDepth=%d, SaveBitDepth=%d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC2:
	ASCII(.ascii	" luma_vir_addr MAP return error\012\000" )
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
