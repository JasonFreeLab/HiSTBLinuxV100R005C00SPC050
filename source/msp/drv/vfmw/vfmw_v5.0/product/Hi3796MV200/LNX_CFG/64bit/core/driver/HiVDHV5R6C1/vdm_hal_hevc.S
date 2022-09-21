#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vdm_hal_hevc.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	HEVCWriteCabacTab
	.type	HEVCWriteCabacTab, %function
HEVCWriteCabacTab:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	ldr	x19, .LC3
	ldr	x8, .LC2
	mov	w2, 16
	mov	w3, 153
	mov	w4, 0
	mov	w9, 0
	mov	w11, w2
	mov	x10, x8
.L2:
	sxtw	x0, w9
	lsl	x7, x0, 7
	add	x7, x7, x0, lsl 5
	b	.L12
	.p2align 3
.L5:
	strb	w0, [x19, x5]
	add	w2, w2, 1
	strb	w1, [x6, 1]
	cmp	w2, 159
	add	w4, w4, 1
	add	x0, x7, x2, sxtw
	bgt	.L17
.L7:
	ldr	w3, [x8, x0, lsl 2]
.L12:
	asr	w0, w3, 4
	and	w1, w3, 15
	cmn	w3, #1
	sbfiz	x5, x4, 1, 32
	add	w0, w0, w0, lsl 2
	ubfiz	w1, w1, 3, 5
	add	x6, x19, x5
	sub	w0, w0, #45
	sub	w1, w1, #16
	bne	.L5
	add	w2, w2, 1
	strb	wzr, [x19, x5]
	strb	wzr, [x6, 1]
	cmp	w2, 159
	add	w4, w4, 1
	add	x0, x7, x2, sxtw
	ble	.L7
.L17:
	add	w9, w9, 1
	cmp	w9, 3
	beq	.L18
	sxtw	x0, w9
	cmp	w9, wzr
	csel	w2, w11, wzr, eq
	lsl	x1, x0, 7
	add	x0, x1, x0, lsl 5
	add	x0, x0, x2, sxtw
	ldr	w3, [x10, x0, lsl 2]
	b	.L2
.L18:
	mov	w0, w20
	bl	MEM_Phy2Vir
	mov	x1, x19
	add	x3, x19, 928
	cbz	x0, .L19
	.p2align 2
.L13:
	ldrsb	w2, [x1]
	add	x1, x1, 2
	strb	w2, [x0, 1]
	cmp	x3, x1
	ldrsb	w2, [x1, -1]
	strb	w2, [x0], 2
	bne	.L13
	mov	w0, 0
.L15:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L19:
	ldr	x2, .LC2
	ldr	x3, .LC5
	ldr	x1, .LC7
	add	x2, x2, 1920
	bl	dprint_vfmw
	mov	w0, -1
	b	.L15
	.size	HEVCWriteCabacTab, .-HEVCWriteCabacTab
	.align	3
.LC2:
	.xword	.LANCHOR0
	.align	3
.LC3:
	.xword	.LANCHOR1
	.align	3
.LC5:
	.xword	.LC4
	.align	3
.LC7:
	.xword	.LC6
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCHAL_V5R6C1_InitHal
	.type	HEVCHAL_V5R6C1_InitHal, %function
HEVCHAL_V5R6C1_InitHal:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 1124]
	bl	HEVCWriteCabacTab
	cbnz	w0, .L25
.L21:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L25:
	ldr	x1, .LC10
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L21
	.size	HEVCHAL_V5R6C1_InitHal, .-HEVCHAL_V5R6C1_InitHal
	.align	3
.LC10:
	.xword	.LC9
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCGet_V5R6C1_VirAddr
	.type	HEVCGet_V5R6C1_VirAddr, %function
HEVCGet_V5R6C1_VirAddr:
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
	.size	HEVCGet_V5R6C1_VirAddr, .-HEVCGet_V5R6C1_VirAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCGet_V5R6C1_PhyAddr
	.type	HEVCGet_V5R6C1_PhyAddr, %function
HEVCGet_V5R6C1_PhyAddr:
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
	.size	HEVCGet_V5R6C1_PhyAddr, .-HEVCGet_V5R6C1_PhyAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCHAL_V5R6C1_CutSliceChain
	.type	HEVCHAL_V5R6C1_CutSliceChain, %function
HEVCHAL_V5R6C1_CutSliceChain:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	mov	w0, w19
	bl	MEM_Phy2Vir
	cbz	x0, .L31
	str	wzr, [x0, 252]
	mov	w0, 0
.L30:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L31:
	ldr	x2, .LC13
	ldr	x3, .LC12
	ldr	x1, .LC14
	add	x2, x2, 1944
	bl	dprint_vfmw
	mov	w0, -1
	b	.L30
	.size	HEVCHAL_V5R6C1_CutSliceChain, .-HEVCHAL_V5R6C1_CutSliceChain
	.align	3
.LC12:
	.xword	.LC11
	.align	3
.LC13:
	.xword	.LANCHOR0
	.align	3
.LC14:
	.xword	.LC6
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_WriteQmatrix
	.type	HEVC_WriteQmatrix, %function
HEVC_WriteQmatrix:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w19, w1
	mov	x20, x3
	bl	_mcount
	mov	x0, 0
	cbz	w19, .L32
	.p2align 2
.L36:
	ldr	w2, [x21, x0, lsl 2]
	str	w2, [x20, x0, lsl 2]
	add	x0, x0, 1
	cmp	w19, w0
	bhi	.L36
.L32:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_WriteQmatrix, .-HEVC_WriteQmatrix
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_WriteTileInfo
	.type	HEVC_WriteTileInfo, %function
HEVC_WriteTileInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x20, 1128]
	bl	MEM_Phy2Vir
	cbz	x0, .L39
	add	x10, x19, 1742
	add	x11, x0, 1024
	mov	x8, x0
.L40:
	add	x3, x8, 4
	add	x9, x8, 516
	mov	x2, x10
	mov	x1, 0
	b	.L44
	.p2align 3
.L56:
	ldrb	w7, [x2, 1]
	add	x3, x3, 4
	ldrb	w6, [x2]
	cmp	x9, x3
	ldrb	w5, [x2, -1]
	add	x2, x2, 4
	ldrb	w4, [x2, -6]
	lsl	w6, w6, 16
	orr	w6, w6, w7, lsl 24
	orr	w4, w4, w5, lsl 8
	orr	w4, w6, w4
	str	w4, [x8, x1]
	add	x1, x1, 4
	beq	.L55
.L44:
	add	w4, w1, 3
	cmp	w4, 255
	ble	.L56
	add	x3, x3, 4
	str	wzr, [x8, x1]
	cmp	x9, x3
	add	x1, x1, 4
	add	x2, x2, 4
	bne	.L44
.L55:
	add	x8, x8, 512
	add	x10, x10, 256
	cmp	x11, x8
	bne	.L40
	add	x3, x0, 1028
	add	x2, x19, 2256
	mov	w1, 0
	b	.L48
	.p2align 3
.L58:
	ldp	w5, w4, [x2, -4]
	add	w1, w1, 1
	add	x3, x3, 4
	cmp	w1, 20
	add	x2, x2, 8
	orr	w4, w5, w4, lsl 16
	str	w4, [x3, -8]
	beq	.L57
.L48:
	cmp	w1, 9
	ble	.L58
	add	w1, w1, 1
	str	wzr, [x3, -4]
	cmp	w1, 20
	add	x3, x3, 4
	add	x2, x2, 8
	bne	.L48
.L57:
	add	x1, x0, 1108
	add	x2, x19, 2336
	mov	w0, 0
	b	.L51
	.p2align 3
.L60:
	ldp	w4, w3, [x2, -4]
	add	w0, w0, 1
	add	x1, x1, 4
	cmp	w0, 22
	add	x2, x2, 8
	orr	w3, w4, w3, lsl 16
	str	w3, [x1, -8]
	beq	.L59
.L51:
	cmp	w0, 10
	ble	.L60
	add	w0, w0, 1
	str	wzr, [x1, -4]
	cmp	w0, 22
	add	x1, x1, 4
	add	x2, x2, 8
	bne	.L51
.L59:
	mov	w0, 0
.L41:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L39:
	ldr	x2, .LC19
	mov	w0, 0
	ldr	x3, .LC18
	ldr	x1, .LC20
	add	x2, x2, 1976
	bl	dprint_vfmw
	mov	w0, -1
	b	.L41
	.size	HEVC_WriteTileInfo, .-HEVC_WriteTileInfo
	.align	3
.LC18:
	.xword	.LC17
	.align	3
.LC19:
	.xword	.LANCHOR0
	.align	3
.LC20:
	.xword	.LC6
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCHAL_V5R6C1_SetPicMsg
	.type	HEVCHAL_V5R6C1_SetPicMsg, %function
HEVCHAL_V5R6C1_SetPicMsg:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	mov	w25, w2
	mov	x24, x1
	mov	w26, w3
	bl	_mcount
	mov	w0, w25
	bl	MEM_Phy2Vir
	mov	x22, x0
	cbz	x0, .L80
	ldr	x3, .LC25
	mov	x2, 1280
	mov	w1, 0
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x1, .LC27
	mov	w0, 4
	bl	dprint_vfmw
	ldrb	w1, [x19, 8]
	ldrb	w3, [x19, 6]
	ldrb	w5, [x19, 7]
	ldrb	w0, [x19, 9]
	ldrb	w2, [x19, 10]
	lsl	w5, w5, 24
	lsl	w0, w0, 22
	orr	w3, w5, w3, lsl 25
	orr	w0, w0, w1, lsl 23
	ldr	w4, [x19, 12]
	orr	w0, w3, w0
	orr	w3, w0, w2, lsl 21
	ldrb	w0, [x19, 16]
	ldp	w1, w5, [x19, 20]
	lsl	w1, w1, 9
	orr	w0, w5, w0, lsl 18
	orr	w2, w1, w4, lsl 19
	ldr	x1, .LC29
	orr	w2, w2, w0
	mov	w0, 4
	orr	w2, w3, w2
	str	w2, [x22]
	bl	dprint_vfmw
	ldr	w2, [x19, 28]
	mov	w0, 4
	ldr	x1, .LC31
	str	w2, [x22, 4]
	bl	dprint_vfmw
	ldp	w3, w1, [x19, 44]
	ldp	w2, w0, [x19, 52]
	ldr	w4, [x19, 36]
	lsl	w3, w3, 24
	lsl	w2, w2, 18
	ldrb	w5, [x19, 41]
	orr	w2, w2, w1, lsl 21
	orr	w3, w3, w4, lsl 29
	ldp	w4, w1, [x19, 60]
	orr	w3, w3, w2
	lsl	w2, w4, 12
	orr	w2, w2, w0, lsl 15
	ldp	w4, w0, [x19, 68]
	orr	w2, w3, w2
	lsl	w3, w4, 6
	ldr	w4, [x19, 76]
	orr	w1, w3, w1, lsl 9
	ldrb	w3, [x19, 40]
	orr	w2, w2, w1
	orr	w0, w4, w0, lsl 3
	orr	w4, w2, w0
	lsl	w2, w5, 27
	orr	w2, w2, w3, lsl 28
	ldr	x1, .LC33
	orr	w2, w4, w2
	mov	w0, 4
	str	w2, [x22, 8]
	bl	dprint_vfmw
	ldp	w2, w3, [x19, 88]
	ldp	w1, w4, [x19, 80]
	ldr	w0, [x19, 96]
	lsl	w3, w3, 8
	lsl	w4, w4, 16
	orr	w3, w3, w2, lsl 12
	ldr	w2, [x19, 100]
	orr	w1, w4, w1, lsl 22
	orr	w3, w3, w1
	ldr	x1, .LC35
	orr	w2, w2, w0, lsl 4
	mov	w0, 4
	orr	w2, w3, w2
	str	w2, [x22, 12]
	bl	dprint_vfmw
	ldr	w2, [x24, 1108]
	mov	w0, 4
	ldr	x1, .LC37
	str	w2, [x22, 16]
	bl	dprint_vfmw
	ldr	w2, [x24, 1112]
	mov	w0, 4
	ldr	x1, .LC39
	str	w2, [x22, 20]
	bl	dprint_vfmw
	ldr	w2, [x19, 1292]
	mov	w0, 4
	ldr	x1, .LC41
	add	x2, x19, x2, lsl 2
	ldr	w2, [x2, 1476]
	str	w2, [x22, 24]
	bl	dprint_vfmw
	ldr	w2, [x24, 1120]
	mov	w0, 4
	ldr	x1, .LC43
	str	w2, [x22, 28]
	bl	dprint_vfmw
	ldr	w20, [x19, 2484]
	ldr	x23, .LC45
	cbz	w20, .L67
	mov	w21, 0
	.p2align 2
.L65:
	add	x3, x19, x21, uxtw 2
	add	w4, w21, 8
	mov	w2, w4
	mov	x1, x23
	mov	w0, 4
	add	w21, w21, 1
	ldr	w3, [x3, 2420]
	add	x3, x3, 336
	ldr	w3, [x19, x3, lsl 2]
	str	w3, [x22, w4, uxtw 2]
	bl	dprint_vfmw
	ldr	w20, [x19, 2484]
	cmp	w20, w21
	bhi	.L65
	cmp	w20, 15
	bhi	.L81
	.p2align 2
.L67:
	ldr	w3, [x19, 2420]
	add	w4, w20, 8
	mov	w2, w4
	mov	x1, x23
	add	x3, x3, 336
	mov	w0, 4
	add	w20, w20, 1
	ldr	w3, [x19, x3, lsl 2]
	str	w3, [x22, w4, uxtw 2]
	bl	dprint_vfmw
	cmp	w20, 15
	bls	.L67
.L81:
	ldr	w2, [x24, 1124]
	mov	w0, 4
	ldr	x1, .LC47
	add	x27, x19, 128
	str	w2, [x22, 100]
	add	x21, x22, 104
	mov	w20, 26
	bl	dprint_vfmw
	.p2align 2
.L66:
	ldr	w3, [x27], 4
	mov	w2, w20
	str	w3, [x21], 4
	mov	x1, x23
	mov	w0, 4
	add	w20, w20, 1
	bl	dprint_vfmw
	cmp	w20, 42
	bne	.L66
	ldr	w2, [x24, 1116]
	mov	w0, 4
	ldr	x1, .LC49
	str	w2, [x22, 172]
	bl	dprint_vfmw
	ldp	w2, w3, [x19, 192]
	ldr	x1, .LC51
	mov	w0, 4
	orr	w2, w3, w2, lsl 16
	str	w2, [x22, 216]
	bl	dprint_vfmw
	mov	x1, x24
	mov	x0, x19
	bl	HEVC_WriteTileInfo
	mov	w21, w0
	cbnz	w0, .L82
	ldr	w2, [x24, 1128]
	mov	w0, 4
	ldr	x1, .LC55
	str	w2, [x22, 220]
	bl	dprint_vfmw
	ldr	w2, [x24, 1140]
	mov	w0, 4
	ldr	x1, .LC57
	str	w2, [x22, 224]
	bl	dprint_vfmw
	ldr	w2, [x24, 1132]
	mov	w0, 4
	ldr	x1, .LC59
	str	w2, [x22, 228]
	bl	dprint_vfmw
	ldr	w2, [x24, 1144]
	mov	w0, 4
	ldr	x1, .LC61
	str	w2, [x22, 232]
	bl	dprint_vfmw
	ldr	w2, [x24, 1136]
	mov	w0, 4
	ldr	x1, .LC63
	str	w2, [x22, 236]
	bl	dprint_vfmw
	ldrb	w4, [x19, 220]
	ldrb	w3, [x19, 221]
	ldp	w1, w2, [x19, 228]
	lsl	w3, w3, 23
	ldrb	w0, [x19, 222]
	orr	w3, w3, w4, lsl 24
	lsl	w2, w2, 13
	ldrb	w4, [x19, 223]
	orr	w2, w2, w1, lsl 16
	orr	w3, w3, w2
	ldrb	w1, [x19, 224]
	lsl	w2, w4, 21
	ldrb	w4, [x19, 225]
	orr	w2, w2, w0, lsl 22
	ldrb	w0, [x19, 236]
	orr	w3, w3, w2
	lsl	w2, w4, 19
	orr	w1, w2, w1, lsl 20
	ldrb	w2, [x19, 237]
	orr	w3, w3, w1
	ldrb	w1, [x19, 238]
	lsl	w2, w2, 11
	orr	w2, w2, w0, lsl 12
	ldp	w4, w0, [x19, 240]
	orr	w3, w3, w2
	ubfiz	w4, w4, 5, 5
	and	w0, w0, 31
	orr	w1, w4, w1, lsl 10
	orr	w3, w3, w1
	ldr	x1, .LC65
	orr	w3, w3, w0
	mov	w0, 4
	mov	w2, w3
	str	w3, [x22, 240]
	bl	dprint_vfmw
	ldp	w2, w3, [x19, 248]
	ldr	x1, .LC67
	mov	w0, 4
	orr	w2, w3, w2, lsl 16
	str	w2, [x22, 244]
	add	x19, x19, 260
	bl	dprint_vfmw
	str	w26, [x22, 252]
	ldr	x1, .LC69
	mov	w2, w26
	mov	w0, 4
	bl	dprint_vfmw
	mov	x1, x22
	mov	w0, 64
	bl	HEVC_GetVirAddr
	mov	x20, x0
	mov	w1, w25
	mov	w0, 64
	bl	HEVC_GetPhyAddr
	mov	x0, 0
	.p2align 2
.L70:
	ldr	w1, [x19, x0]
	str	w1, [x20, x0]
	add	x0, x0, 4
	cmp	x0, 1024
	bne	.L70
.L63:
	mov	w0, w21
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L82:
	ldr	x1, .LC53
	mov	w0, 1
	mov	w21, -1
	bl	dprint_vfmw
	b	.L63
.L80:
	ldr	x2, .LC23
	mov	w0, 0
	ldr	x3, .LC22
	mov	w21, -1
	ldr	x1, .LC24
	add	x2, x2, 2000
	bl	dprint_vfmw
	b	.L63
	.size	HEVCHAL_V5R6C1_SetPicMsg, .-HEVCHAL_V5R6C1_SetPicMsg
	.align	3
.LC22:
	.xword	.LC21
	.align	3
.LC23:
	.xword	.LANCHOR0
	.align	3
.LC24:
	.xword	.LC6
	.align	3
.LC25:
	.xword	vfmw_Osal_Func_Ptr_S
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCHAL_SetSliceMsgStreamAddrInfo
	.type	HEVCHAL_SetSliceMsgStreamAddrInfo, %function
HEVCHAL_SetSliceMsgStreamAddrInfo:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x26, x0
	mov	x0, x30
	mov	x25, x1
	mov	x19, x2
	mov	w21, w3
	bl	_mcount
	ldr	x23, .LC74
	add	x27, x25, 16
	mov	w22, 1
	mov	w20, 0
	mov	x24, x23
.L89:
	lsl	w2, w20, 2
	mov	w3, w21
	sub	w2, w2, w20
	mov	x1, x23
	mov	w0, 4
	lsl	w5, w20, 2
	cbz	w20, .L91
	ldr	w4, [x27, -16]
	cbz	w4, .L87
.L85:
	ldr	w4, [x27]
	and	w5, w4, -16
	ldr	w4, [x26, 1332]
	and	w4, w4, -16
	sub	w4, w5, w4
	str	w4, [x19]
	ldr	w4, [x19]
	bl	dprint_vfmw
	ldr	w0, [x27]
	add	w3, w21, 4
	ldr	w1, [x27, -8]
	mov	w2, w22
	add	w0, w1, w0, lsl 3
	mov	x1, x23
	and	w0, w0, 127
	str	w0, [x19, 4]
	mov	w0, 4
	ldr	w4, [x19, 4]
	bl	dprint_vfmw
	ldr	w0, [x27, -16]
	add	w3, w21, 8
	str	w0, [x19, 8]
	add	w2, w22, 1
	mov	x1, x23
	mov	w0, 4
	ldr	w4, [x19, 8]
	bl	dprint_vfmw
.L88:
	add	w20, w20, 1
	add	x27, x27, 4
	cmp	w20, 2
	add	x19, x19, 12
	add	w21, w21, 12
	add	w22, w22, 3
	bne	.L89
	mov	w0, 0
.L86:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L87:
	str	wzr, [x19]
	sub	w2, w5, w20
	mov	w3, w21
	mov	x1, x24
	ldr	w4, [x19]
	mov	w0, 4
	bl	dprint_vfmw
	str	wzr, [x19, 4]
	add	w3, w21, 4
	mov	w2, w22
	ldr	w4, [x19, 4]
	mov	x1, x24
	mov	w0, 4
	bl	dprint_vfmw
	str	wzr, [x19, 8]
	add	w3, w21, 8
	add	w2, w22, 1
	ldr	w4, [x19, 8]
	mov	x1, x24
	mov	w0, 4
	bl	dprint_vfmw
	b	.L88
.L91:
	ldr	w4, [x25]
	cbnz	w4, .L85
	ldr	x2, .LC70
	mov	w0, 0
	ldr	x1, .LC72
	add	x2, x2, 2032
	bl	dprint_vfmw
	mov	w0, -1
	b	.L86
	.size	HEVCHAL_SetSliceMsgStreamAddrInfo, .-HEVCHAL_SetSliceMsgStreamAddrInfo
	.align	3
.LC70:
	.xword	.LANCHOR0
	.align	3
.LC72:
	.xword	.LC71
	.align	3
.LC74:
	.xword	.LC73
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCHAL_SetSliceMsgAPCIndex
	.type	HEVCHAL_SetSliceMsgAPCIndex, %function
HEVCHAL_SetSliceMsgAPCIndex:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	w5, [x19, 68]
	cbz	w5, .L99
	mov	w8, 15
	mov	w4, 0
	mov	w0, 0
	b	.L98
	.p2align 3
.L96:
	cmp	w7, w0
	beq	.L105
.L97:
	add	w0, w0, 1
	cmp	w5, w0
	bls	.L99
.L98:
	add	x3, x19, x0, uxtw 2
	and	w2, w0, 7
	lsl	w6, w2, 2
	cmp	w2, 7
	sub	w7, w5, #1
	ldr	w2, [x3, 372]
	lsl	w2, w2, w6
	orr	w4, w4, w2
	bne	.L96
	str	w4, [x20, w8, sxtw 2]
	add	w0, w0, 1
	add	w8, w8, 1
	mov	w4, 0
	ldr	w5, [x19, 68]
	cmp	w5, w0
	bhi	.L98
.L99:
	ldr	w5, [x19, 72]
	cbz	w5, .L92
	mov	w8, 17
	mov	w4, 0
	mov	w0, 0
	b	.L102
	.p2align 3
.L100:
	cmp	w7, w0
	beq	.L106
.L101:
	add	w0, w0, 1
	cmp	w5, w0
	bls	.L92
.L102:
	add	x3, x19, x0, uxtw 2
	and	w2, w0, 7
	lsl	w6, w2, 2
	cmp	w2, 7
	sub	w7, w5, #1
	ldr	w2, [x3, 436]
	lsl	w2, w2, w6
	orr	w4, w4, w2
	bne	.L100
	str	w4, [x20, w8, sxtw 2]
	add	w0, w0, 1
	add	w8, w8, 1
	mov	w4, 0
	ldr	w5, [x19, 72]
	cmp	w5, w0
	bhi	.L102
.L92:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L105:
	str	w4, [x20, w8, sxtw 2]
	ldr	w5, [x19, 68]
	b	.L97
	.p2align 3
.L106:
	str	w4, [x20, w8, sxtw 2]
	ldr	w5, [x19, 72]
	b	.L101
	.size	HEVCHAL_SetSliceMsgAPCIndex, .-HEVCHAL_SetSliceMsgAPCIndex
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCHAL_SetSliceMsgWPInfo
	.type	HEVCHAL_SetSliceMsgWPInfo, %function
HEVCHAL_SetSliceMsgWPInfo:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	mov	x21, x2
	mov	x19, x1
	bl	_mcount
	mov	x1, x21
	mov	w0, 64
	bl	HEVC_GetVirAddr
	mov	x20, x0
	mov	x1, x21
	mov	w0, 128
	bl	HEVC_GetVirAddr
	ldrb	w1, [x22, 41]
	cbz	w1, .L108
	ldr	w1, [x19, 76]
	cmp	w1, 1
	beq	.L109
.L108:
	ldrb	w1, [x22, 40]
	cmp	w1, 1
	beq	.L127
.L107:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L127:
	ldr	w1, [x19, 76]
	cbnz	w1, .L107
	ldr	w1, [x19, 68]
	mov	w2, 0
	cbz	w1, .L116
	.p2align 2
.L113:
	uxtw	x1, w2
	ldr	w3, [x19, 580]
	add	w7, w2, 32
	add	x6, x19, x1, lsl 2
	and	w4, w3, 7
	add	x1, x19, x1, lsl 3
	ldrb	w5, [x6, 716]
	ldr	w3, [x6, 588]
	ubfiz	w3, w3, 3, 9
	orr	w3, w3, w5, lsl 12
	orr	w3, w3, w4
	str	w3, [x20, w2, uxtw 2]
	ldrb	w5, [x1, 1100]
	ldr	w4, [x1, 844]
	ldr	w3, [x19, 584]
	ubfiz	w4, w4, 3, 9
	orr	w4, w4, w5, lsl 12
	and	w3, w3, 7
	orr	w3, w4, w3
	str	w3, [x0, w2, uxtw 2]
	add	w2, w2, 1
	ldrb	w3, [x1, 1104]
	ldr	w1, [x1, 848]
	and	w1, w1, 511
	orr	w1, w1, w3, lsl 9
	str	w1, [x0, w7, uxtw 2]
	ldr	w1, [x19, 68]
	cmp	w1, w2
	bhi	.L113
	ldr	w1, [x19, 76]
	cbnz	w1, .L107
.L116:
	ldr	w1, [x19, 72]
	cbz	w1, .L107
	mov	w2, 0
	.p2align 2
.L114:
	uxtw	x1, w2
	ldr	w3, [x19, 580]
	add	w6, w2, 16
	add	w8, w2, 48
	add	x7, x19, x1, lsl 2
	and	w4, w3, 7
	add	x1, x19, x1, lsl 3
	add	w2, w2, 1
	ldrb	w5, [x7, 780]
	ldr	w3, [x7, 652]
	ubfiz	w3, w3, 3, 9
	orr	w3, w3, w5, lsl 12
	orr	w3, w3, w4
	str	w3, [x20, w6, uxtw 2]
	ldrb	w5, [x1, 1228]
	ldr	w4, [x1, 972]
	ldr	w3, [x19, 584]
	ubfiz	w4, w4, 3, 9
	orr	w4, w4, w5, lsl 12
	and	w3, w3, 7
	orr	w3, w4, w3
	str	w3, [x0, w6, uxtw 2]
	ldrb	w3, [x1, 1232]
	ldr	w1, [x1, 976]
	and	w1, w1, 511
	orr	w1, w1, w3, lsl 9
	str	w1, [x0, w8, uxtw 2]
	ldr	w1, [x19, 72]
	cmp	w1, w2
	bhi	.L114
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L109:
	ldr	w1, [x19, 68]
	mov	w2, 0
	cbnz	w1, .L113
	b	.L107
	.size	HEVCHAL_SetSliceMsgWPInfo, .-HEVCHAL_SetSliceMsgWPInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCHAL_V5R6C1_SetSliceMsg
	.type	HEVCHAL_V5R6C1_SetSliceMsg, %function
HEVCHAL_V5R6C1_SetSliceMsg:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	w27, w3
	mov	x25, x2
	mov	w21, w5
	mov	w26, w6
	mov	w24, w7
	ldr	w23, [x29, 96]
	ldr	w22, [x29, 104]
	bl	_mcount
	mov	w0, w27
	bl	MEM_Phy2Vir
	mov	x19, x0
	cbz	x0, .L140
	ldr	x1, .LC79
	mov	x2, 1280
	ldr	x3, [x1, 96]
	mov	w1, 0
	blr	x3
	ldr	x1, .LC81
	mov	w0, 4
	bl	dprint_vfmw
	mov	w3, w27
	mov	x2, x19
	mov	x1, x25
	mov	x0, x20
	bl	HEVCHAL_SetSliceMsgStreamAddrInfo
	cmn	w0, #1
	beq	.L130
	ldrb	w1, [x25, 32]
	ldr	w0, [x25, 28]
	ubfiz	w0, w0, 19, 7
	orr	w2, w0, w1, lsl 18
	ldrb	w1, [x25, 24]
	ldrb	w0, [x25, 25]
	lsl	w0, w0, 26
	orr	w0, w0, w1, lsl 27
	ldr	x1, .LC82
	orr	w0, w2, w0
	ldr	w2, [x25, 36]
	orr	w2, w0, w2
	mov	w0, 4
	str	w2, [x19, 24]
	bl	dprint_vfmw
	ldp	w3, w1, [x25, 72]
	ldr	w0, [x25, 60]
	lsl	w3, w3, 8
	ldr	w4, [x25, 44]
	orr	w5, w3, w0, lsl 16
	ldr	x0, .LC77
	add	x0, x0, 2104
	ldr	w2, [x0, x1, lsl 2]
	ldr	w1, [x25, 56]
	ldr	w0, [x25, 68]
	lsl	w1, w1, 20
	orr	w1, w1, w4, lsl 24
	orr	w3, w5, w1
	orr	w0, w2, w0, lsl 2
	orr	w2, w3, w0
	ldrb	w1, [x25, 64]
	ldrb	w3, [x25, 65]
	lsl	w3, w3, 14
	orr	w0, w3, w1, lsl 15
	ldr	w1, [x25, 40]
	orr	w3, w2, w0
	ldrb	w2, [x25, 52]
	lsl	w2, w2, 27
	orr	w0, w2, w1, lsl 28
	ldr	x1, .LC83
	orr	w2, w3, w0
	mov	w0, 4
	str	w2, [x19, 28]
	bl	dprint_vfmw
	str	w26, [x19, 32]
	ldr	x1, .LC85
	mov	w2, w26
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w0, [x20, 24]
	ldr	x1, .LC87
	add	w0, w0, 1
	udiv	w2, w26, w0
	msub	w0, w2, w0, w26
	orr	w2, w0, w2, lsl 16
	mov	w0, 4
	str	w2, [x19, 36]
	bl	dprint_vfmw
	str	w24, [x19, 40]
	ldr	x1, .LC89
	mov	w2, w24
	mov	w0, 4
	bl	dprint_vfmw
	ldp	w3, w2, [x25, 96]
	ldr	x1, .LC91
	mov	w0, 4
	ubfiz	w3, w3, 8, 5
	and	w2, w2, 31
	orr	w2, w3, w2
	str	w2, [x19, 44]
	bl	dprint_vfmw
	ldrb	w0, [x25, 113]
	ldrb	w1, [x25, 112]
	ldp	w3, w4, [x25, 104]
	lsl	w1, w1, 2
	ldrb	w2, [x25, 115]
	orr	w1, w1, w0, lsl 3
	ldrb	w0, [x25, 114]
	ubfiz	w3, w3, 16, 4
	ubfiz	w4, w4, 8, 4
	orr	w4, w3, w4
	orr	w3, w4, w1
	orr	w0, w2, w0, lsl 1
	ldr	x1, .LC93
	orr	w2, w3, w0
	mov	w0, 4
	str	w2, [x19, 48]
	bl	dprint_vfmw
	ldr	w4, [x25, 68]
	cbz	w4, .L136
	add	x3, x25, 116
	mov	w2, 0
	mov	w0, 0
	.p2align 2
.L132:
	ldr	w1, [x3], 4
	lsl	w1, w1, w0
	add	w0, w0, 1
	cmp	w0, w4
	orr	w2, w2, w1
	bne	.L132
	mov	w0, w2
.L131:
	ldr	x1, .LC95
	str	w0, [x19, 52]
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w4, [x25, 72]
	cbz	w4, .L137
	add	x3, x25, 180
	mov	w2, 0
	mov	w0, 0
	.p2align 2
.L134:
	ldr	w1, [x3], 4
	lsl	w1, w1, w0
	add	w0, w0, 1
	cmp	w0, w4
	orr	w2, w2, w1
	bne	.L134
	mov	w0, w2
.L133:
	ldr	x1, .LC97
	str	w0, [x19, 56]
	mov	w0, 4
	bl	dprint_vfmw
	mov	x1, x19
	mov	x0, x25
	bl	HEVCHAL_SetSliceMsgAPCIndex
	ldr	w2, [x25, 564]
	mov	w0, 4
	ldr	x1, .LC99
	str	w2, [x19, 92]
	bl	dprint_vfmw
	ldr	w2, [x20, 84]
	mov	w3, 16394
	ldr	x1, .LC101
	mov	w0, 4
	lsr	w2, w2, 1
	orr	w2, w3, w2, lsl 8
	str	w2, [x19, 96]
	bl	dprint_vfmw
	ldr	x27, [x20, 2496]
	ldrb	w2, [x25, 1357]
	add	x24, x27, 1356
	ubfiz	w2, w2, 30, 1
	ldp	w0, w1, [x24, 8]
	and	w0, w0, 16383
	ubfiz	w1, w1, 16, 14
	orr	w0, w2, w0
	ldr	w2, [x24, 4]
	ubfiz	w2, w2, 14, 2
	orr	w2, w2, w1
	ldr	x1, .LC102
	orr	w2, w2, w0
	mov	w0, 4
	str	w2, [x19, 100]
	bl	dprint_vfmw
	ldr	w2, [x24, 28]
	mov	w0, 4
	ldr	x1, .LC104
	and	w2, w2, 131071
	str	w2, [x19, 104]
	bl	dprint_vfmw
	ldr	w2, [x24, 88]
	mov	w0, 4
	ldr	x1, .LC106
	str	w2, [x19, 108]
	bl	dprint_vfmw
	ldr	w2, [x24, 92]
	mov	w0, 4
	ldr	x1, .LC108
	str	w2, [x19, 112]
	bl	dprint_vfmw
	ldr	w0, [x24, 40]
	ldrh	w2, [x24, 44]
	ldr	x1, .LC110
	orr	w2, w2, w0, lsl 16
	mov	w0, 4
	str	w2, [x19, 116]
	bl	dprint_vfmw
	ldr	w0, [x24, 56]
	ldrh	w2, [x24, 60]
	ldr	x1, .LC112
	orr	w2, w2, w0, lsl 16
	mov	w0, 4
	str	w2, [x19, 120]
	bl	dprint_vfmw
	ldr	w2, [x24, 36]
	mov	w0, 4
	ldr	x1, .LC114
	and	w2, w2, 131071
	str	w2, [x19, 124]
	bl	dprint_vfmw
	ldr	w2, [x24, 96]
	mov	w0, 4
	ldr	x1, .LC116
	str	w2, [x19, 128]
	bl	dprint_vfmw
	ldr	w2, [x24, 100]
	mov	w0, 4
	ldr	x1, .LC118
	str	w2, [x19, 132]
	bl	dprint_vfmw
	ldr	w0, [x24, 48]
	ldrh	w2, [x24, 52]
	ldr	x1, .LC120
	orr	w2, w2, w0, lsl 16
	mov	w0, 4
	str	w2, [x19, 136]
	bl	dprint_vfmw
	ldr	w0, [x24, 64]
	ldrh	w2, [x24, 68]
	ldr	x1, .LC122
	orr	w2, w2, w0, lsl 16
	mov	w0, 4
	str	w2, [x19, 140]
	bl	dprint_vfmw
	ldp	w2, w1, [x24, 72]
	ldr	w0, [x24, 84]
	ubfiz	w2, w2, 24, 5
	ubfiz	w1, w1, 16, 5
	and	w0, w0, 31
	orr	w0, w2, w0
	ldr	w2, [x24, 80]
	ubfiz	w2, w2, 8, 5
	orr	w2, w2, w1
	ldr	x1, .LC124
	orr	w2, w2, w0
	mov	w0, 4
	str	w2, [x19, 144]
	bl	dprint_vfmw
	ldr	w0, [x24, 20]
	ldrb	w2, [x27, 1356]
	add	w0, w0, 15
	asr	w0, w0, 4
	ubfiz	w3, w2, 26, 1
	sub	w0, w0, #1
	ldr	w2, [x24, 116]
	ubfiz	w1, w0, 8, 9
	ldr	w0, [x24, 16]
	ubfiz	w2, w2, 4, 4
	add	w0, w0, 15
	asr	w0, w0, 4
	sub	w0, w0, #1
	ubfiz	w0, w0, 17, 9
	orr	w0, w1, w0
	ldr	w1, [x24, 112]
	and	w1, w1, 15
	orr	w2, w2, w1
	ldr	x1, .LC126
	orr	w0, w0, w2
	orr	w2, w3, w0
	mov	w0, 4
	str	w2, [x19, 148]
	bl	dprint_vfmw
	ldp	w0, w2, [x24, 104]
	ldr	x1, .LC128
	and	w2, w2, 8191
	orr	w2, w2, w0, lsl 16
	mov	w0, 4
	str	w2, [x19, 152]
	bl	dprint_vfmw
	ldr	w2, [x24, 120]
	mov	w0, 4
	ldr	x1, .LC130
	and	w2, w2, 1048575
	str	w2, [x19, 156]
	bl	dprint_vfmw
	ldr	w2, [x24, 124]
	mov	w0, 4
	ldr	x1, .LC132
	str	w2, [x19, 160]
	bl	dprint_vfmw
	ldr	w2, [x24, 128]
	mov	w0, 4
	ldr	x1, .LC134
	str	w2, [x19, 164]
	bl	dprint_vfmw
	ldrh	w2, [x25, 1500]
	mov	w0, 4
	ldr	x1, .LC136
	str	w2, [x19, 168]
	bl	dprint_vfmw
	str	w23, [x19, 172]
	ldr	x1, .LC137
	mov	w2, w23
	mov	w0, 4
	bl	dprint_vfmw
	str	w22, [x19, 176]
	ldr	x1, .LC139
	mov	w2, w22
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w2, [x24, 132]
	mov	w0, 4
	ldr	x1, .LC141
	add	w2, w2, w2, lsr 31
	ubfx	x2, x2, 1, 20
	str	w2, [x19, 180]
	bl	dprint_vfmw
	ldr	w2, [x24, 136]
	mov	w0, 4
	ldr	x1, .LC143
	str	w2, [x19, 184]
	bl	dprint_vfmw
	ldr	w2, [x24, 140]
	mov	w0, 4
	ldr	x1, .LC145
	str	w2, [x19, 188]
	bl	dprint_vfmw
	ldr	w2, [x24, 24]
	mov	w0, 4
	ldr	x1, .LC147
	and	w2, w2, 131071
	str	w2, [x19, 192]
	bl	dprint_vfmw
	ldr	w2, [x24, 32]
	mov	w0, 4
	ldr	x1, .LC149
	and	w2, w2, 131071
	str	w2, [x19, 196]
	bl	dprint_vfmw
	str	w21, [x19, 252]
	ldr	x1, .LC150
	mov	w2, w21
	mov	w0, 4
	bl	dprint_vfmw
	mov	x0, x20
	mov	x2, x19
	mov	x1, x25
	bl	HEVCHAL_SetSliceMsgWPInfo
	mov	w0, 0
.L130:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L136:
	mov	w0, 0
	mov	w2, 0
	b	.L131
.L137:
	mov	w0, 0
	mov	w2, 0
	b	.L133
.L140:
	ldr	x2, .LC77
	mov	w0, 0
	ldr	x3, .LC76
	ldr	x1, .LC78
	add	x2, x2, 2072
	bl	dprint_vfmw
	mov	w0, -1
	b	.L130
	.size	HEVCHAL_V5R6C1_SetSliceMsg, .-HEVCHAL_V5R6C1_SetSliceMsg
	.align	3
.LC76:
	.xword	.LC75
	.align	3
.LC77:
	.xword	.LANCHOR0
	.align	3
.LC78:
	.xword	.LC6
	.align	3
.LC79:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC81:
	.xword	.LC80
	.align	3
.LC82:
	.xword	.LC40
	.align	3
.LC83:
	.xword	.LC42
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
	.align	3
.LC95:
	.xword	.LC94
	.align	3
.LC97:
	.xword	.LC96
	.align	3
.LC99:
	.xword	.LC98
	.align	3
.LC101:
	.xword	.LC100
	.align	3
.LC102:
	.xword	.LC46
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
	.xword	.LC48
	.align	3
.LC139:
	.xword	.LC138
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
	.align	3
.LC149:
	.xword	.LC148
	.align	3
.LC150:
	.xword	.LC68
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCHAL_CheckParaValid
	.type	HEVCHAL_CheckParaValid, %function
HEVCHAL_CheckParaValid:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w20, wzr
	bgt	.L146
	cbz	x19, .L147
	ldr	w1, [x19, 2484]
	mov	w0, 0
	cmp	w1, 16
	bhi	.L148
.L143:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L146:
	ldr	x2, .LC152
	mov	w4, 1
	ldr	x1, .LC154
	mov	w3, w20
	add	x2, x2, 2120
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L143
	.p2align 3
.L148:
	ldr	x2, .LC152
	ldr	x3, .LC159
	ldr	x1, .LC157
	add	x2, x2, 2120
	bl	dprint_vfmw
	mov	w0, -1
	b	.L143
.L147:
	ldr	x2, .LC152
	mov	w0, 0
	ldr	x3, .LC156
	ldr	x1, .LC157
	add	x2, x2, 2120
	bl	dprint_vfmw
	mov	w0, -1
	b	.L143
	.size	HEVCHAL_CheckParaValid, .-HEVCHAL_CheckParaValid
	.align	3
.LC152:
	.xword	.LANCHOR0
	.align	3
.LC154:
	.xword	.LC153
	.align	3
.LC156:
	.xword	.LC155
	.align	3
.LC157:
	.xword	.LC6
	.align	3
.LC159:
	.xword	.LC158
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCHAL_GetVdmRegVirAddr
	.type	HEVCHAL_GetVdmRegVirAddr, %function
HEVCHAL_GetVdmRegVirAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w20, wzr
	bgt	.L154
	ldr	x0, [x19]
	cbz	x0, .L152
.L153:
	mov	w0, 0
.L151:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L152:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	str	x0, [x19]
	cbnz	x0, .L153
	ldr	x2, .LC162
	ldr	x1, .LC164
	add	x2, x2, 2144
	bl	dprint_vfmw
	mov	w0, -1
	b	.L151
	.p2align 3
.L154:
	ldr	x1, .LC161
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L151
	.size	HEVCHAL_GetVdmRegVirAddr, .-HEVCHAL_GetVdmRegVirAddr
	.align	3
.LC161:
	.xword	.LC160
	.align	3
.LC162:
	.xword	.LANCHOR0
	.align	3
.LC164:
	.xword	.LC163
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCHAL_CheckSlicePara
	.type	HEVCHAL_CheckSlicePara, %function
HEVCHAL_CheckSlicePara:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w1
	mov	w20, w2
	bl	_mcount
	cbz	x19, .L160
	ldr	w2, [x19, 92]
	mov	w0, 0
	cmp	w2, w20
	ccmp	w21, wzr, 4, cc
	cset	w1, gt
	cbnz	w1, .L161
.L157:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L161:
	ldr	x1, .LC169
	mov	w3, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L157
.L160:
	ldr	x2, .LC165
	mov	w3, w21
	ldr	x1, .LC167
	mov	w0, 1
	add	x2, x2, 2176
	bl	dprint_vfmw
	mov	w0, -1
	b	.L157
	.size	HEVCHAL_CheckSlicePara, .-HEVCHAL_CheckSlicePara
	.align	3
.LC165:
	.xword	.LANCHOR0
	.align	3
.LC167:
	.xword	.LC166
	.align	3
.LC169:
	.xword	.LC168
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCHAL_FindNextSlicePara
	.type	HEVCHAL_FindNextSlicePara, %function
HEVCHAL_FindNextSlicePara:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x22, x3
	mov	x0, x30
	mov	w20, w2
	mov	w21, w1
	bl	_mcount
	ldr	w1, [x19, 92]
	cmp	w20, w21
	str	w20, [x22]
	bge	.L163
	ldr	x19, [x19, 1504]
	cbz	x19, .L166
	ldr	w0, [x19, 92]
	cmp	w1, w0
	bcc	.L163
	add	w2, w20, 1
	b	.L165
	.p2align 3
.L167:
	ldr	x19, [x19, 1504]
	cbz	x19, .L166
	ldr	w0, [x19, 92]
	cmp	w1, w0
	bcc	.L163
.L165:
	cmp	w2, w21
	str	w2, [x22]
	add	w2, w2, 1
	bne	.L167
.L163:
	mov	x0, x19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L166:
	mov	x19, 0
	mov	x0, x19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVCHAL_FindNextSlicePara, .-HEVCHAL_FindNextSlicePara
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCHAL_CheckSliceAddrValid
	.type	HEVCHAL_CheckSliceAddrValid, %function
HEVCHAL_CheckSliceAddrValid:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w21, w1
	mov	w19, w2
	bl	_mcount
	cmp	w21, w19
	ldr	w3, [x20, 572]
	bgt	.L173
	cmp	w19, w3
	blt	.L173
	ldr	w2, [x20, 92]
	mov	w0, 0
	cmp	w2, w3
	bhi	.L177
.L175:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L173:
	ldr	x1, .LC171
	mov	w4, w19
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L175
	.p2align 3
.L177:
	ldr	x1, .LC173
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L175
	.size	HEVCHAL_CheckSliceAddrValid, .-HEVCHAL_CheckSliceAddrValid
	.align	3
.LC171:
	.xword	.LC170
	.align	3
.LC173:
	.xword	.LC172
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCHAL_V5R6C1_CfgVdmReg
	.type	HEVCHAL_V5R6C1_CfgVdmReg, %function
HEVCHAL_V5R6C1_CfgVdmReg:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w2
	mov	x20, x3
	mov	x23, x1
	bl	_mcount
	ldr	x1, .LC175
	sbfiz	x0, x21, 6, 32
	ldr	x2, .LC174
	cmp	x20, xzr
	ldrb	w1, [x1]
	add	x0, x2, x0
	ccmp	w1, 1, 4, eq
	ldr	w0, [x0, 8]
	bne	.L190
	ldr	x2, .LC179
	ldr	x0, [x2, w0, sxtw 3]
	cbz	x0, .L185
	ldr	w26, [x0, 1272]
	uxtb	w0, w26
	and	w25, w0, 1
.L181:
	cmp	w1, 1
	beq	.L182
	strb	w0, [x20, 1]
.L182:
	ldr	w2, [x19, 5188]
	mov	w0, 1
	ldrb	w3, [x19, 7]
	cmp	w2, 1
	ldr	w1, [x19, 24]
	csetm	w2, eq
	str	wzr, [x29, 92]
	bfi	w0, w2, 2, 2
	ldr	w2, [x19, 20]
	bfi	w0, w3, 6, 1
	strb	wzr, [x29, 94]
	and	w0, w0, 127
	mov	x3, x20
	and	w0, w0, -49
	strb	w0, [x29, 95]
	madd	w2, w1, w2, w2
	ldr	w22, [x29, 92]
	mov	w0, 8
	add	w1, w2, w1
	mov	w2, w21
	bfi	w22, w1, 0, 20
	str	w22, [x19, 2512]
	mov	w1, w22
	str	w22, [x29, 92]
	bl	MFDE_ConfigReg
	ldr	x1, .LC181
	mov	w2, w22
	mov	w0, 3
	mov	w22, 3075
	mov	w24, w0
	movk	w22, 0x30, lsl 16
	bl	dprint_vfmw
	str	wzr, [x29, 92]
	strb	wzr, [x29, 95]
	mov	w1, 0
	strb	wzr, [x19, 5]
	mov	x3, x20
	ldr	w2, [x19, 1328]
	ldr	w0, [x19, 1340]
	bfi	w1, w2, 4, 1
	mov	w2, 13
	bfi	w1, w0, 6, 1
	ldrh	w0, [x29, 94]
	orr	w1, w1, -128
	strb	w1, [x29, 93]
	bfi	w0, w24, 0, 12
	ldrb	w1, [x19]
	strh	w0, [x29, 94]
	lsr	x0, x0, 8
	bfi	w0, w1, 6, 1
	strb	w2, [x29, 92]
	and	w0, w0, 127
	mov	w2, w21
	bfi	w0, w25, 4, 1
	strb	w0, [x29, 95]
	mov	w0, 12
	ldr	w25, [x29, 92]
	str	w25, [x19, 2516]
	mov	w1, w25
	bl	MFDE_ConfigReg
	ldr	x1, .LC183
	mov	w2, w25
	mov	w0, w24
	bl	dprint_vfmw
	ldr	w25, [x23, 72]
	mov	x3, x20
	mov	w2, w21
	and	w25, w25, -16
	mov	w0, 16
	mov	w1, w25
	str	w25, [x19, 2520]
	bl	MFDE_ConfigReg
	ldr	x1, .LC185
	mov	w2, w25
	mov	w0, w24
	bl	dprint_vfmw
	ldr	w1, [x23, 56]
	mov	x3, x20
	mov	w2, w21
	mov	w0, 20
	and	w1, w1, -16
	str	w1, [x19, 2524]
	bl	MFDE_ConfigReg
	ldr	w1, [x19, 1332]
	mov	x3, x20
	mov	w2, w21
	mov	w0, 24
	and	w1, w1, -16
	str	w1, [x19, 2528]
	bl	MFDE_ConfigReg
	add	x4, x19, 2304
	mov	w0, 60
	mov	x3, x20
	mov	w2, w21
	mov	w1, w22
	stp	w22, w22, [x4, 232]
	stp	w22, w22, [x4, 240]
	str	w22, [x19, 2552]
	str	w22, [x19, 2556]
	str	w22, [x19, 2560]
	bl	MFDE_ConfigReg
	mov	x3, x20
	mov	w2, w21
	mov	w1, w22
	mov	w0, 64
	bl	MFDE_ConfigReg
	mov	x3, x20
	mov	w2, w21
	mov	w1, w22
	mov	w0, 68
	bl	MFDE_ConfigReg
	mov	x3, x20
	mov	w2, w21
	mov	w1, w22
	mov	w0, 72
	bl	MFDE_ConfigReg
	mov	x3, x20
	mov	w2, w21
	mov	w1, w22
	mov	w0, 76
	bl	MFDE_ConfigReg
	mov	x3, x20
	mov	w2, w21
	mov	w1, w22
	mov	w0, 80
	bl	MFDE_ConfigReg
	mov	x3, x20
	mov	w2, w21
	mov	w1, w22
	mov	w0, 84
	bl	MFDE_ConfigReg
	ldr	w1, [x19, 1288]
	mov	x3, x20
	mov	w2, w21
	mov	w0, 96
	add	x1, x1, 336
	ldr	w4, [x19, x1, lsl 2]
	and	w4, w4, -256
	str	w4, [x19, 2564]
	mov	w1, w4
	str	w4, [x29, 92]
	bl	MFDE_ConfigReg
	cmp	w26, 1
	beq	.L191
.L183:
	ldr	w22, [x19, 1296]
	mov	x3, x20
	mov	w0, 100
	mov	w2, w21
	mov	w1, w22
	str	w22, [x19, 2568]
	bl	MFDE_ConfigReg
	ldr	x1, .LC191
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w22, [x19, 1304]
	mov	x3, x20
	mov	w0, 104
	mov	w2, w21
	mov	w1, w22
	str	w22, [x19, 2572]
	bl	MFDE_ConfigReg
	ldr	x1, .LC193
	mov	w2, w22
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w1, [x19, 1312]
	mov	x3, x20
	mov	w2, w21
	mov	w0, 108
	bl	MFDE_ConfigReg
	ldr	w4, [x19, 1316]
	mov	x3, x20
	mov	w2, w21
	mov	w0, 116
	mov	w1, w4
	str	w4, [x19, 2588]
	bl	MFDE_ConfigReg
	ldr	w4, [x19, 1320]
	mov	x3, x20
	mov	w2, w21
	mov	w0, 120
	mov	w1, w4
	str	w4, [x19, 2592]
	bl	MFDE_ConfigReg
	ldr	w4, [x19, 1324]
	mov	x3, x20
	str	w4, [x19, 2596]
	mov	w2, w21
	mov	w1, w4
	mov	w0, 124
	bl	MFDE_ConfigReg
	str	wzr, [x19, 2612]
	mov	x3, x20
	mov	w2, w21
	mov	w1, 0
	mov	w0, 128
	str	wzr, [x29, 92]
	bl	MFDE_ConfigReg
	strh	wzr, [x29, 92]
	mov	w0, 132
	mov	x3, x20
	ldr	w1, [x29, 92]
	mov	w2, w21
	str	w1, [x19, 2616]
	bl	MFDE_ConfigReg
	ldr	w0, [x19, 196]
	cmp	w0, 4096
	bhi	.L192
	mov	w1, 1
	mov	w19, w1
.L184:
	mov	x3, x20
	mov	w0, 4
	mov	w2, w21
	bl	SCD_ConfigReg
	ldr	x1, .LC195
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	mov	x3, x20
	mov	w2, w21
	mov	w1, 0
	mov	w0, 152
	bl	MFDE_ConfigReg
	ldr	x1, .LC197
	mov	w2, 0
	mov	w0, 3
	bl	dprint_vfmw
	mov	w0, 32
	mov	x3, x20
	mov	w2, w21
	mov	w1, -1
	bl	MFDE_ConfigReg
	mov	w0, 0
.L180:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L192:
	mov	w1, 0
	mov	w19, 0
	b	.L184
	.p2align 3
.L185:
	mov	w25, 0
	mov	w0, 0
	mov	w26, 0
	b	.L181
	.p2align 3
.L191:
	mov	x3, x20
	mov	w2, w21
	mov	w1, 60
	mov	w0, 92
	bl	MFDE_ConfigReg
	ldr	x1, .LC187
	mov	w2, 60
	mov	w0, w24
	bl	dprint_vfmw
	ldr	w1, [x19, 1288]
	mov	w2, w21
	mov	w0, 112
	mov	x3, x20
	add	x1, x19, x1, lsl 2
	ldr	w22, [x1, 1612]
	mov	w1, w22
	bl	MFDE_ConfigReg
	ldr	x1, .LC189
	mov	w2, w22
	mov	w0, w24
	bl	dprint_vfmw
	b	.L183
.L190:
	ldr	x2, .LC176
	mov	x3, x20
	ldr	x1, .LC178
	mov	w0, 0
	add	x2, x2, 2200
	bl	dprint_vfmw
	mov	w0, -1
	b	.L180
	.size	HEVCHAL_V5R6C1_CfgVdmReg, .-HEVCHAL_V5R6C1_CfgVdmReg
	.align	3
.LC174:
	.xword	g_VdmDrvParam
	.align	3
.LC175:
	.xword	g_HalDisable
	.align	3
.LC176:
	.xword	.LANCHOR0
	.align	3
.LC178:
	.xword	.LC177
	.align	3
.LC179:
	.xword	s_pstVfmwChan
	.align	3
.LC181:
	.xword	.LC180
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCHAL_V5R6C1_SetSliceMsgSedOnly
	.type	HEVCHAL_V5R6C1_SetSliceMsgSedOnly, %function
HEVCHAL_V5R6C1_SetSliceMsgSedOnly:
	sub	sp, sp, #80
	stp	x29, x30, [sp, 16]
	add	x29, sp, 16
	stp	x19, x20, [sp, 32]
	stp	x21, x22, [sp, 48]
	stp	x23, x24, [sp, 64]
	mov	x22, x0
	mov	x0, x30
	mov	x23, x1
	bl	_mcount
	ldr	w3, [x22, 2488]
	ldr	x1, [x22, 2496]
	cmp	w3, wzr
	ble	.L194
	mov	w0, 0
	mov	w24, 0
	mov	x19, 0
	.p2align 2
.L196:
	ldrb	w2, [x1, 25]
	cmp	w2, wzr
	csel	w24, w24, w0, ne
	add	w0, w0, 1
	csel	x19, x19, x1, ne
	cmp	w0, w3
	ldr	x1, [x1, 1504]
	bne	.L196
	cbz	x19, .L194
	sub	w0, w0, w24
	mov	w20, 0
	cmp	w0, wzr
	mov	w21, 205
	bgt	.L208
	b	.L204
	.p2align 3
.L214:
	ldr	x4, [x19, 1504]
	ldrb	w8, [x22, 225]
	ldr	w2, [x1, 56]
	ldr	w0, [x4, 92]
	mov	w5, w2
	sub	w0, w0, #1
	cbz	w8, .L212
	ldr	w1, [x4, 568]
	mov	w5, w2
	.p2align 2
.L201:
	str	w1, [sp]
	mov	x2, x19
	str	w0, [sp, 8]
	mov	w4, 0
	mov	x1, x23
	mov	x0, x22
	add	w20, w20, 1
	bl	HEVCHAL_V5R6C1_SetSliceMsg
	cbnz	w0, .L213
	ldr	w0, [x22, 2488]
	ldr	x19, [x19, 1504]
	sub	w0, w0, w24
	cmp	w0, w20
	ble	.L204
.L208:
	add	w1, w20, 5
	sub	w0, w0, #1
	cmp	w0, w20
	mov	w0, w1
	add	w2, w20, 6
	ccmp	w20, w21, 0, gt
	add	x0, x23, x0, sxtw 2
	mov	w1, w2
	mov	w5, 0
	ldr	w6, [x19, 80]
	add	x1, x23, x1, sxtw 2
	ldr	w7, [x19, 92]
	ldr	w3, [x0, 56]
	ble	.L214
	ldp	w1, w0, [x22, 20]
	madd	w0, w1, w0, w0
	add	w0, w0, w1
.L212:
	mov	w1, w0
	b	.L201
	.p2align 3
.L204:
	mov	w0, 0
.L198:
	add	sp, x29, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L213:
	ldr	x2, .LC198
	mov	w0, 1
	ldr	x1, .LC202
	add	x2, x2, 2232
	bl	dprint_vfmw
	add	sp, x29, 0
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L194:
	ldr	x2, .LC198
	mov	w0, 1
	ldr	x1, .LC200
	add	x2, x2, 2232
	bl	dprint_vfmw
	mov	w0, -1
	b	.L198
	.size	HEVCHAL_V5R6C1_SetSliceMsgSedOnly, .-HEVCHAL_V5R6C1_SetSliceMsgSedOnly
	.align	3
.LC198:
	.xword	.LANCHOR0
	.align	3
.LC200:
	.xword	.LC199
	.align	3
.LC202:
	.xword	.LC201
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCHAL_V5R6C1_StartDec
	.type	HEVCHAL_V5R6C1_StartDec, %function
HEVCHAL_V5R6C1_StartDec:
	sub	sp, sp, #176
	stp	x29, x30, [sp, 16]
	add	x29, sp, 16
	stp	x19, x20, [sp, 32]
	stp	x21, x22, [sp, 48]
	stp	x23, x24, [sp, 64]
	stp	x25, x26, [sp, 80]
	stp	x27, x28, [sp, 96]
	sxtw	x1, w1
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	x22, x2
	str	x1, [x29, 112]
	bl	_mcount
	ldr	x21, .LC203
	lsl	x2, x20, 6
	mov	w1, w20
	sub	x2, x2, x20
	mov	x0, x19
	lsl	x2, x2, 2
	sub	x23, x2, x20
	add	x2, x2, x23, lsl 2
	add	x2, x21, x2
	str	x2, [x29, 120]
	bl	HEVCHAL_CheckParaValid
	cmn	w0, #1
	beq	.L218
	ldr	x23, [x29, 120]
	mov	w1, w20
	mov	x0, x23
	bl	HEVCHAL_GetVdmRegVirAddr
	cmn	w0, #1
	beq	.L218
	mov	w2, w20
	mov	x3, x22
	mov	x1, x23
	mov	x0, x19
	bl	HEVCHAL_V5R6C1_CfgVdmReg
	ldp	w2, w3, [x23, 72]
	mov	x1, x23
	mov	x0, x19
	bl	HEVCHAL_V5R6C1_SetPicMsg
	ldr	x20, [x19, 2496]
	cbz	x20, .L263
	ldr	w0, [x19, 5188]
	cmp	w0, 1
	beq	.L264
	ldr	w22, [x20, 92]
	cbnz	w22, .L265
	mov	x27, x20
	str	wzr, [x29, 108]
.L221:
	ldp	w22, w0, [x19, 20]
	ldr	w1, [x19, 2488]
	madd	w0, w22, w0, w0
	cmp	w1, wzr
	add	w22, w0, w22
	ble	.L224
	ldr	w0, [x29, 108]
	mov	w2, 0
	mov	w24, 0
	mov	w28, 0
	add	w1, w0, 4
	add	w0, w0, 5
	stp	w1, w0, [x29, 128]
	ldr	x0, [x29, 112]
	add	x20, x0, x0, lsl 2
	lsl	x20, x20, 4
	sub	x20, x20, x0
	lsl	x20, x20, 1
	sub	x20, x20, x0
	lsl	x20, x20, 1
	.p2align 2
.L236:
	ldr	w0, [x29, 128]
	mov	w1, w28
	add	w3, w0, w28
	ldr	w0, [x29, 132]
	add	w25, w28, w0
	add	x3, x20, x3, sxtw
	mov	x0, x27
	add	x4, x20, x25, sxtw
	add	x3, x21, x3, lsl 2
	add	x4, x21, x4, lsl 2
	ldr	w26, [x3, 56]
	ldr	w3, [x4, 56]
	str	w3, [x29, 156]
	bl	HEVCHAL_CheckSlicePara
	cmn	w0, #1
	beq	.L218
	ldr	w1, [x19, 2488]
	add	w28, w28, 1
	ldr	w6, [x27, 80]
	cmp	w1, w28
	ldr	w7, [x27, 92]
	ble	.L239
	ldr	x23, [x27, 1504]
	cbnz	x23, .L262
	b	.L226
	.p2align 3
.L266:
	add	w28, w28, 1
	cmp	w1, w28
	ble	.L225
	ldr	x23, [x23, 1504]
	cbz	x23, .L226
.L262:
	ldr	w0, [x23, 92]
	cmp	w7, w0
	bcs	.L266
.L231:
	cmp	w25, 209
	ccmp	w1, w28, 4, ne
	beq	.L267
	ldr	w3, [x23, 92]
	ldrb	w0, [x19, 225]
	sub	w3, w3, #1
	mov	w4, w3
	cbz	w0, .L234
	ldr	w4, [x23, 568]
.L234:
	ldr	w0, [x29, 132]
	add	w0, w28, w0
	add	x0, x20, x0, sxtw
	add	x0, x21, x0, lsl 2
	ldr	w5, [x0, 56]
.L233:
	mov	w2, w22
	mov	w1, w4
	mov	x0, x27
	str	w3, [x27, 572]
	stp	w6, w7, [x29, 136]
	stp	w5, w3, [x29, 144]
	str	w4, [x29, 152]
	bl	HEVCHAL_CheckSliceAddrValid
	cmn	w0, #1
	beq	.L218
	ldp	w5, w3, [x29, 144]
	ldr	w4, [x29, 152]
	mov	x2, x27
	str	w3, [sp, 8]
	mov	x0, x19
	ldp	w6, w7, [x29, 136]
	ldr	x1, [x29, 120]
	ldr	w3, [x29, 156]
	str	w4, [sp]
	mov	w4, w26
	bl	HEVCHAL_V5R6C1_SetSliceMsg
	mov	w25, w0
	cbnz	w0, .L268
	ldr	w0, [x19, 2488]
	add	w24, w24, 1
	ldr	w2, [x27, 572]
	cmp	w28, w0
	bge	.L269
	mov	x27, x23
	b	.L236
.L265:
	ldrb	w0, [x19, 225]
	sub	w8, w22, #1
	mov	w9, w8
	cbz	w0, .L222
	ldr	w9, [x20, 568]
.L222:
	ldr	x2, [x29, 112]
	mov	w24, 1
	ldp	w11, w10, [x20, 8]
	lsl	x0, x2, 6
	mov	w7, 0
	sub	x0, x0, x2
	mov	w6, 0
	lsl	x1, x0, 2
	sub	x0, x1, x2
	mov	x2, x20
	stp	wzr, wzr, [x20, 8]
	ldp	w28, w27, [x20]
	stp	w24, wzr, [x20]
	add	x0, x1, x0, lsl 2
	add	x0, x21, x0
	ldr	w1, [x19, 1332]
	ldp	w26, w25, [x20, 16]
	stp	w1, wzr, [x20, 16]
	ldr	x1, [x29, 120]
	ldp	w4, w3, [x0, 72]
	ldr	w5, [x0, 80]
	mov	x0, x19
	str	w9, [sp]
	str	w8, [sp, 8]
	stp	w11, w10, [x29, 152]
	bl	HEVCHAL_V5R6C1_SetSliceMsg
	ldp	w11, w10, [x29, 152]
	cbnz	w0, .L270
	stp	w28, w27, [x20]
	stp	w11, w10, [x20, 8]
	stp	w26, w25, [x20, 16]
	str	w22, [x20, 92]
	str	w24, [x29, 108]
	ldr	x27, [x19, 2496]
	b	.L221
	.p2align 3
.L267:
	str	xzr, [x27, 1504]
	mov	w4, w22
	mov	w3, w22
	mov	w5, 0
	ldr	w28, [x19, 2488]
	b	.L233
.L239:
	mov	x23, x27
	.p2align 2
.L225:
	cbnz	x23, .L231
	.p2align 2
.L226:
	ldr	x2, .LC204
	mov	w0, 1
	ldr	x1, .LC209
	mov	w25, -1
	add	x2, x2, 2272
	bl	dprint_vfmw
	b	.L217
.L218:
	mov	w25, -1
.L217:
	add	sp, x29, 0
	mov	w0, w25
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
.L268:
	ldr	x2, .LC204
	mov	w0, 1
	ldr	x1, .LC211
	mov	w25, -1
	add	x2, x2, 2272
	bl	dprint_vfmw
	b	.L217
.L269:
	cmp	w24, wzr
	ccmp	w0, wzr, 4, gt
	ble	.L224
	ldr	x2, [x29, 112]
	ldr	w3, [x29, 108]
	add	x1, x2, x2, lsl 2
	add	w0, w3, w0
	lsl	x1, x1, 4
	add	w0, w0, 4
	sub	x1, x1, x2
	lsl	x1, x1, 1
	sub	x1, x1, x2
	lsl	x1, x1, 1
	add	x0, x1, x0, sxtw
	add	x21, x21, x0, lsl 2
	ldr	w0, [x21, 56]
	bl	HEVCHAL_V5R6C1_CutSliceChain
	b	.L217
.L264:
	ldr	x1, [x29, 120]
	mov	x0, x19
	bl	HEVCHAL_V5R6C1_SetSliceMsgSedOnly
	mov	w25, w0
	b	.L217
.L224:
	ldr	x1, .LC213
	mov	w0, 1
	mov	w25, -1
	bl	dprint_vfmw
	b	.L217
.L270:
	ldr	x2, .LC204
	mov	w0, w24
	ldr	x1, .LC207
	mov	w25, -1
	add	x2, x2, 2272
	bl	dprint_vfmw
	b	.L217
.L263:
	ldr	x2, .LC204
	mov	w0, 0
	ldr	x1, .LC206
	mov	w25, -1
	add	x2, x2, 2272
	bl	dprint_vfmw
	b	.L217
	.size	HEVCHAL_V5R6C1_StartDec, .-HEVCHAL_V5R6C1_StartDec
	.align	3
.LC203:
	.xword	g_HwMem
	.align	3
.LC204:
	.xword	.LANCHOR0
	.align	3
.LC206:
	.xword	.LC205
	.align	3
.LC207:
	.xword	.LC201
	.align	3
.LC209:
	.xword	.LC208
	.align	3
.LC211:
	.xword	.LC210
	.align	3
.LC213:
	.xword	.LC212
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	s_InitValue, %object
	.size	s_InitValue, 1920
s_InitValue:
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	153
	.word	200
	.word	139
	.word	141
	.word	157
	.word	154
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	184
	.word	-1
	.word	-1
	.word	-1
	.word	184
	.word	63
	.word	94
	.word	138
	.word	182
	.word	154
	.word	111
	.word	141
	.word	154
	.word	154
	.word	139
	.word	139
	.word	138
	.word	153
	.word	136
	.word	167
	.word	152
	.word	152
	.word	110
	.word	110
	.word	124
	.word	125
	.word	140
	.word	153
	.word	125
	.word	127
	.word	140
	.word	109
	.word	111
	.word	143
	.word	127
	.word	111
	.word	79
	.word	108
	.word	123
	.word	63
	.word	110
	.word	110
	.word	124
	.word	125
	.word	140
	.word	153
	.word	125
	.word	127
	.word	140
	.word	109
	.word	111
	.word	143
	.word	127
	.word	111
	.word	79
	.word	108
	.word	123
	.word	63
	.word	91
	.word	171
	.word	134
	.word	141
	.word	140
	.word	92
	.word	137
	.word	138
	.word	140
	.word	152
	.word	138
	.word	139
	.word	153
	.word	74
	.word	149
	.word	92
	.word	139
	.word	107
	.word	122
	.word	152
	.word	140
	.word	179
	.word	166
	.word	182
	.word	140
	.word	227
	.word	122
	.word	197
	.word	111
	.word	111
	.word	125
	.word	110
	.word	110
	.word	94
	.word	124
	.word	108
	.word	124
	.word	107
	.word	125
	.word	141
	.word	179
	.word	153
	.word	125
	.word	107
	.word	125
	.word	141
	.word	179
	.word	153
	.word	125
	.word	107
	.word	125
	.word	141
	.word	179
	.word	153
	.word	125
	.word	140
	.word	139
	.word	182
	.word	182
	.word	152
	.word	136
	.word	152
	.word	136
	.word	153
	.word	136
	.word	139
	.word	111
	.word	136
	.word	139
	.word	111
	.word	-1
	.word	153
	.word	138
	.word	138
	.word	-1
	.word	-1
	.word	79
	.word	110
	.word	122
	.word	95
	.word	79
	.word	63
	.word	31
	.word	31
	.word	153
	.word	153
	.word	168
	.word	140
	.word	198
	.word	-1
	.word	-1
	.word	-1
	.word	153
	.word	185
	.word	107
	.word	139
	.word	126
	.word	154
	.word	197
	.word	185
	.word	201
	.word	149
	.word	154
	.word	139
	.word	154
	.word	154
	.word	154
	.word	152
	.word	149
	.word	107
	.word	167
	.word	154
	.word	153
	.word	111
	.word	154
	.word	154
	.word	139
	.word	139
	.word	107
	.word	167
	.word	91
	.word	122
	.word	107
	.word	167
	.word	125
	.word	110
	.word	94
	.word	110
	.word	95
	.word	79
	.word	125
	.word	111
	.word	110
	.word	78
	.word	110
	.word	111
	.word	111
	.word	95
	.word	94
	.word	108
	.word	123
	.word	108
	.word	125
	.word	110
	.word	94
	.word	110
	.word	95
	.word	79
	.word	125
	.word	111
	.word	110
	.word	78
	.word	110
	.word	111
	.word	111
	.word	95
	.word	94
	.word	108
	.word	123
	.word	108
	.word	121
	.word	140
	.word	61
	.word	154
	.word	154
	.word	196
	.word	196
	.word	167
	.word	154
	.word	152
	.word	167
	.word	182
	.word	182
	.word	134
	.word	149
	.word	136
	.word	153
	.word	121
	.word	136
	.word	137
	.word	169
	.word	194
	.word	166
	.word	167
	.word	154
	.word	167
	.word	137
	.word	182
	.word	155
	.word	154
	.word	139
	.word	153
	.word	139
	.word	123
	.word	123
	.word	63
	.word	153
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	170
	.word	153
	.word	123
	.word	123
	.word	107
	.word	121
	.word	107
	.word	121
	.word	167
	.word	151
	.word	183
	.word	140
	.word	151
	.word	183
	.word	140
	.word	-1
	.word	124
	.word	138
	.word	94
	.word	-1
	.word	-1
	.word	79
	.word	154
	.word	137
	.word	95
	.word	79
	.word	63
	.word	31
	.word	31
	.word	153
	.word	153
	.word	168
	.word	169
	.word	198
	.word	-1
	.word	-1
	.word	-1
	.word	153
	.word	160
	.word	107
	.word	139
	.word	126
	.word	154
	.word	197
	.word	185
	.word	201
	.word	134
	.word	154
	.word	139
	.word	154
	.word	154
	.word	183
	.word	152
	.word	149
	.word	92
	.word	167
	.word	154
	.word	153
	.word	111
	.word	154
	.word	154
	.word	139
	.word	139
	.word	107
	.word	167
	.word	91
	.word	107
	.word	107
	.word	167
	.word	125
	.word	110
	.word	124
	.word	110
	.word	95
	.word	94
	.word	125
	.word	111
	.word	111
	.word	79
	.word	125
	.word	126
	.word	111
	.word	111
	.word	79
	.word	108
	.word	123
	.word	93
	.word	125
	.word	110
	.word	124
	.word	110
	.word	95
	.word	94
	.word	125
	.word	111
	.word	111
	.word	79
	.word	125
	.word	126
	.word	111
	.word	111
	.word	79
	.word	108
	.word	123
	.word	93
	.word	121
	.word	140
	.word	61
	.word	154
	.word	154
	.word	196
	.word	167
	.word	167
	.word	154
	.word	152
	.word	167
	.word	182
	.word	182
	.word	134
	.word	149
	.word	136
	.word	153
	.word	121
	.word	136
	.word	122
	.word	169
	.word	208
	.word	166
	.word	167
	.word	154
	.word	152
	.word	167
	.word	182
	.word	170
	.word	154
	.word	139
	.word	153
	.word	139
	.word	123
	.word	123
	.word	63
	.word	124
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	170
	.word	153
	.word	138
	.word	138
	.word	122
	.word	121
	.word	122
	.word	121
	.word	167
	.word	151
	.word	183
	.word	140
	.word	151
	.word	183
	.word	140
	.word	-1
	.word	224
	.word	167
	.word	122
	.word	-1
	.word	-1
	.type	__func__.12316, %object
	.size	__func__.12316, 18
__func__.12316:
	.string	"HEVCWriteCabacTab"
	.zero	6
	.type	__func__.12337, %object
	.size	__func__.12337, 29
__func__.12337:
	.string	"HEVCHAL_V5R6C1_CutSliceChain"
	.zero	3
	.type	__func__.12356, %object
	.size	__func__.12356, 19
__func__.12356:
	.string	"HEVC_WriteTileInfo"
	.zero	5
	.type	__func__.12382, %object
	.size	__func__.12382, 25
__func__.12382:
	.string	"HEVCHAL_V5R6C1_SetPicMsg"
	.zero	7
	.type	__func__.12402, %object
	.size	__func__.12402, 34
__func__.12402:
	.string	"HEVCHAL_SetSliceMsgStreamAddrInfo"
	.zero	6
	.type	__func__.12458, %object
	.size	__func__.12458, 27
__func__.12458:
	.string	"HEVCHAL_V5R6C1_SetSliceMsg"
	.zero	5
	.type	s_SliceTypeForPMV, %object
	.size	s_SliceTypeForPMV, 12
s_SliceTypeForPMV:
	.word	2
	.word	1
	.word	0
	.zero	4
	.type	__func__.12469, %object
	.size	__func__.12469, 23
__func__.12469:
	.string	"HEVCHAL_CheckParaValid"
	.zero	1
	.type	__func__.12475, %object
	.size	__func__.12475, 25
__func__.12475:
	.string	"HEVCHAL_GetVdmRegVirAddr"
	.zero	7
	.type	__func__.12481, %object
	.size	__func__.12481, 23
__func__.12481:
	.string	"HEVCHAL_CheckSlicePara"
	.zero	1
	.type	__func__.12508, %object
	.size	__func__.12508, 25
__func__.12508:
	.string	"HEVCHAL_V5R6C1_CfgVdmReg"
	.zero	7
	.type	__func__.12528, %object
	.size	__func__.12528, 34
__func__.12528:
	.string	"HEVCHAL_V5R6C1_SetSliceMsgSedOnly"
	.zero	6
	.type	__func__.12558, %object
	.size	__func__.12558, 24
__func__.12558:
	.string	"HEVCHAL_V5R6C1_StartDec"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC4:
	ASCII(.string	"can not map mn virtual address!\n" )
	.zero	7
.LC6:
	ASCII(.string	"%s: %s\n" )
.LC9:
	ASCII(.string	"HEVCWriteCabacTab return error.\n" )
	.zero	7
.LC11:
	ASCII(.string	"can not map slice msg virtual address!\n" )
.LC17:
	ASCII(.string	"can not map slice segment info virtual address!\n" )
	.zero	7
.LC21:
	ASCII(.string	"can not map down msg virtual address!\n" )
	.zero	1
.LC26:
	ASCII(.string	"pic msg burst0:\n" )
	.zero	7
.LC28:
	ASCII(.string	"D0 = 0x%x\n" )
	.zero	5
.LC30:
	ASCII(.string	"D1 = 0x%x\n" )
	.zero	5
.LC32:
	ASCII(.string	"D2 = 0x%x\n" )
	.zero	5
.LC34:
	ASCII(.string	"D3 = 0x%x\n" )
	.zero	5
.LC36:
	ASCII(.string	"D4 = 0x%x\n" )
	.zero	5
.LC38:
	ASCII(.string	"D5 = 0x%x\n" )
	.zero	5
.LC40:
	ASCII(.string	"D6 = 0x%x\n" )
	.zero	5
.LC42:
	ASCII(.string	"D7 = 0x%x\n" )
	.zero	5
.LC44:
	ASCII(.string	"D%d = 0x%x\n" )
	.zero	4
.LC46:
	ASCII(.string	"D25 = 0x%x\n" )
	.zero	4
.LC48:
	ASCII(.string	"D43 = 0x%x\n" )
	.zero	4
.LC50:
	ASCII(.string	"D54 = 0x%x\n" )
	.zero	4
.LC52:
	ASCII(.string	"HEVC_WriteTileInfo return error.\n" )
	.zero	6
.LC54:
	ASCII(.string	"D55 = 0x%x\n" )
	.zero	4
.LC56:
	ASCII(.string	"D56 = 0x%x\n" )
	.zero	4
.LC58:
	ASCII(.string	"D57 = 0x%x\n" )
	.zero	4
.LC60:
	ASCII(.string	"D58 = 0x%x\n" )
	.zero	4
.LC62:
	ASCII(.string	"D59 = 0x%x\n" )
	.zero	4
.LC64:
	ASCII(.string	"D60 = 0x%x\n" )
	.zero	4
.LC66:
	ASCII(.string	"D61 = 0x%x\n" )
	.zero	4
.LC68:
	ASCII(.string	"D63 = 0x%x\n" )
	.zero	4
.LC71:
	ASCII(.string	"%s FATAL: i=0, valid_bitlen=0\n" )
	.zero	1
.LC73:
	ASCII(.string	"slicemsg D[%d] addr 0x%x = 0x%x\n" )
	.zero	7
.LC75:
	ASCII(.string	"HEVCHAL_SetSliceMsg can not map slice msg virtual address!\n" )
	.zero	4
.LC80:
	ASCII(.string	"slice msg info:\n" )
	.zero	7
.LC84:
	ASCII(.string	"D8 = 0x%x\n" )
	.zero	5
.LC86:
	ASCII(.string	"D9 = 0x%x\n" )
	.zero	5
.LC88:
	ASCII(.string	"D10 = 0x%x\n" )
	.zero	4
.LC90:
	ASCII(.string	"D11 = 0x%x\n" )
	.zero	4
.LC92:
	ASCII(.string	"D12 = 0x%x\n" )
	.zero	4
.LC94:
	ASCII(.string	"D13 = 0x%x\n" )
	.zero	4
.LC96:
	ASCII(.string	"D14 = 0x%x\n" )
	.zero	4
.LC98:
	ASCII(.string	"D23 = 0x%x\n" )
	.zero	4
.LC100:
	ASCII(.string	"D24 = 0x%x\n" )
	.zero	4
.LC103:
	ASCII(.string	"D26 = 0x%x\n" )
	.zero	4
.LC105:
	ASCII(.string	"D27 = 0x%x\n" )
	.zero	4
.LC107:
	ASCII(.string	"D28 = 0x%x\n" )
	.zero	4
.LC109:
	ASCII(.string	"D29 = 0x%x\n" )
	.zero	4
.LC111:
	ASCII(.string	"D30 = 0x%x\n" )
	.zero	4
.LC113:
	ASCII(.string	"D31 = 0x%x\n" )
	.zero	4
.LC115:
	ASCII(.string	"D32 = 0x%x\n" )
	.zero	4
.LC117:
	ASCII(.string	"D33 = 0x%x\n" )
	.zero	4
.LC119:
	ASCII(.string	"D34 = 0x%x\n" )
	.zero	4
.LC121:
	ASCII(.string	"D35 = 0x%x\n" )
	.zero	4
.LC123:
	ASCII(.string	"D36 = 0x%x\n" )
	.zero	4
.LC125:
	ASCII(.string	"D37 = 0x%x\n" )
	.zero	4
.LC127:
	ASCII(.string	"D38 = 0x%x\n" )
	.zero	4
.LC129:
	ASCII(.string	"D39 = 0x%x\n" )
	.zero	4
.LC131:
	ASCII(.string	"D40 = 0x%x\n" )
	.zero	4
.LC133:
	ASCII(.string	"D41 = 0x%x\n" )
	.zero	4
.LC135:
	ASCII(.string	"D42 = 0x%x\n" )
	.zero	4
.LC138:
	ASCII(.string	"D44 = 0x%x\n" )
	.zero	4
.LC140:
	ASCII(.string	"D45 = 0x%x\n" )
	.zero	4
.LC142:
	ASCII(.string	"D46 = 0x%x\n" )
	.zero	4
.LC144:
	ASCII(.string	"D47 = 0x%x\n" )
	.zero	4
.LC146:
	ASCII(.string	"D48 = 0x%x\n" )
	.zero	4
.LC148:
	ASCII(.string	"D49 = 0x%x\n" )
	.zero	4
.LC153:
	ASCII(.string	"%s VdhId %d >= %d\n" )
	.zero	5
.LC155:
	ASCII(.string	"pParam is null\n" )
.LC158:
	ASCII(.string	"FATAL: ApcSize > 16\n" )
	.zero	3
.LC160:
	ASCII(.string	"VdhId is wrong! HEVC4HAL_V200R003_StartDec\n" )
	.zero	4
.LC163:
	ASCII(.string	"%s vdm register virtual address not mapped, reset failed!\n" )
	.zero	5
.LC166:
	ASCII(.string	"%s: i = %d, pSlicePara = NULL!\n" )
.LC168:
	ASCII(.string	"SliceSegmentTileAddress %d < prevEndCtbInSliceTile %d\n" )
	.zero	1
.LC170:
	ASCII(.string	"end_ctb_in_slice_raster(%d)/end_ctb_in_slice_tile(%d) > pic_max_ctb(%d)\n" )
	.zero	7
.LC172:
	ASCII(.string	"SliceSegmentTileAddress %d > end_ctb_in_slice_tile %d\n" )
	.zero	1
.LC177:
	ASCII(.string	"%s: pMfdeTask(%p) = NULL\n" )
	.zero	6
.LC180:
	ASCII(.string	"HEVC_BASIC_CFG0 = 0x%x\n" )
.LC182:
	ASCII(.string	"HEVC_BASIC_CFG1 = 0x%x\n" )
.LC184:
	ASCII(.string	"AVM_ADDR = 0x%x\n" )
	.zero	7
.LC186:
	ASCII(.string	"VREG_V200R003_PART_DEC_OVER_INT_LEVEL=0x%x\n" )
	.zero	4
.LC188:
	ASCII(.string	"VREG_LINE_NUM_STADDR = 0x%x\n" )
	.zero	3
.LC190:
	ASCII(.string	"HEVC_VFMW_YSTADDR_1D = 0x%x\n" )
	.zero	3
.LC192:
	ASCII(.string	"HEVC_VFMW_UVOFFSET_1D = 0x%x\n" )
	.zero	2
.LC194:
	ASCII(.string	"SCD REG_EMAR_ID = 0x%x\n" )
.LC196:
	ASCII(.string	"VREG_FF_APT_EN = 0x%x\n" )
	.zero	1
.LC199:
	ASCII(.string	"%s : pTargetSlicePara == NULL\n" )
	.zero	1
.LC201:
	ASCII(.string	"%s 0: set slice msg failed!\n" )
	.zero	3
.LC205:
	ASCII(.string	"%s pFirstSlice = NULL!\n" )
.LC208:
	ASCII(.string	"%s pTargetSlicePara is NULL!\n" )
	.zero	2
.LC210:
	ASCII(.string	"%s 1: set slice msg failed!\n" )
	.zero	3
.LC212:
	ASCII(.string	"No slice to dec, add up msg report.\n" )
	.bss
	.align	3
.LANCHOR1 = . + 0
	.type	s_CabacMN, %object
	.size	s_CabacMN, 928
s_CabacMN:
	.zero	928
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
