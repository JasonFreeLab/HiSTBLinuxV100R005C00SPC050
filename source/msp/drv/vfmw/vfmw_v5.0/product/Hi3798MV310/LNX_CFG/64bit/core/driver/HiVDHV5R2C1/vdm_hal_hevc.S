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
	.global	HEVCHAL_V5R2C1_InitHal
	.type	HEVCHAL_V5R2C1_InitHal, %function
HEVCHAL_V5R2C1_InitHal:
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
	.size	HEVCHAL_V5R2C1_InitHal, .-HEVCHAL_V5R2C1_InitHal
	.align	3
.LC10:
	.xword	.LC9
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCGet_V5R2C1_VirAddr
	.type	HEVCGet_V5R2C1_VirAddr, %function
HEVCGet_V5R2C1_VirAddr:
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
	.size	HEVCGet_V5R2C1_VirAddr, .-HEVCGet_V5R2C1_VirAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCGet_V5R2C1_PhyAddr
	.type	HEVCGet_V5R2C1_PhyAddr, %function
HEVCGet_V5R2C1_PhyAddr:
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
	.size	HEVCGet_V5R2C1_PhyAddr, .-HEVCGet_V5R2C1_PhyAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCHAL_V5R2C1_CutSliceChain
	.type	HEVCHAL_V5R2C1_CutSliceChain, %function
HEVCHAL_V5R2C1_CutSliceChain:
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
	.size	HEVCHAL_V5R2C1_CutSliceChain, .-HEVCHAL_V5R2C1_CutSliceChain
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
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x21, x0
	mov	w23, w1
	mov	x0, x30
	mov	w20, w2
	mov	x22, x3
	bl	_mcount
	cbz	w23, .L32
	sub	w23, w23, #1
	ldr	x25, .LC18
	ldr	x24, .LC20
	add	x23, x23, 1
	mov	x19, 0
	.p2align 2
.L34:
	ldr	w0, [x21, x19, lsl 2]
	mov	w2, w19
	str	w0, [x22, x19, lsl 2]
	mov	x1, x25
	mov	w0, 4
	ldr	w3, [x21, x19, lsl 2]
	bl	dprint_vfmw
	ldr	w3, [x22, x19, lsl 2]
	mov	w2, w20
	mov	w0, 4
	mov	x1, x24
	add	x19, x19, 1
	add	w20, w20, w0
	bl	dprint_vfmw
	cmp	x19, x23
	bne	.L34
.L32:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	HEVC_WriteQmatrix, .-HEVC_WriteQmatrix
	.align	3
.LC18:
	.xword	.LC17
	.align	3
.LC20:
	.xword	.LC19
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_WriteTileInfo
	.type	HEVC_WriteTileInfo, %function
HEVC_WriteTileInfo:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x1
	mov	x25, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 1128]
	bl	MEM_Phy2Vir
	mov	x24, x0
	cbz	x0, .L38
	ldr	x21, .LC26
	add	x26, x25, 1742
	add	x27, x0, 1024
	mov	x22, x0
.L39:
	add	x28, x22, 4
	add	x23, x22, 516
	mov	x20, x26
	mov	x19, 0
	b	.L43
	.p2align 3
.L55:
	ldrb	w5, [x20, 1]
	add	x28, x28, 4
	ldrb	w4, [x20]
	add	x20, x20, 4
	ldrb	w3, [x20, -5]
	ldrb	w2, [x20, -6]
	lsl	w4, w4, 16
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3, lsl 8
	orr	w2, w4, w2
	str	w2, [x22, x19]
	add	x19, x19, 4
	bl	dprint_vfmw
	cmp	x23, x28
	beq	.L54
.L43:
	add	w0, w19, 3
	mov	x1, x21
	cmp	w0, 255
	mov	w2, 0
	mov	w0, 4
	ble	.L55
	str	wzr, [x22, x19]
	mov	x1, x21
	mov	w0, 4
	add	x28, x28, 4
	add	x19, x19, 4
	add	x20, x20, 4
	bl	dprint_vfmw
	cmp	x23, x28
	bne	.L43
.L54:
	add	x22, x22, 512
	add	x26, x26, 256
	cmp	x27, x22
	bne	.L39
	add	x2, x24, 1028
	add	x1, x25, 2256
	mov	w0, 0
	b	.L47
	.p2align 3
.L57:
	ldp	w4, w3, [x1, -4]
	add	w0, w0, 1
	add	x2, x2, 4
	cmp	w0, 20
	add	x1, x1, 8
	orr	w3, w4, w3, lsl 16
	str	w3, [x2, -8]
	beq	.L56
.L47:
	cmp	w0, 9
	ble	.L57
	add	w0, w0, 1
	str	wzr, [x2, -4]
	cmp	w0, 20
	add	x2, x2, 4
	add	x1, x1, 8
	bne	.L47
.L56:
	add	x24, x24, 1108
	add	x25, x25, 2336
	mov	w0, 0
	b	.L50
	.p2align 3
.L59:
	ldp	w2, w1, [x25, -4]
	add	w0, w0, 1
	add	x24, x24, 4
	cmp	w0, 22
	add	x25, x25, 8
	orr	w1, w2, w1, lsl 16
	str	w1, [x24, -8]
	beq	.L58
.L50:
	cmp	w0, 10
	ble	.L59
	add	w0, w0, 1
	str	wzr, [x24, -4]
	cmp	w0, 22
	add	x24, x24, 4
	add	x25, x25, 8
	bne	.L50
.L58:
	mov	w0, 0
.L40:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L38:
	ldr	x2, .LC23
	mov	w0, 0
	ldr	x3, .LC22
	ldr	x1, .LC24
	add	x2, x2, 1976
	bl	dprint_vfmw
	mov	w0, -1
	b	.L40
	.size	HEVC_WriteTileInfo, .-HEVC_WriteTileInfo
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
.LC26:
	.xword	.LC25
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCHAL_V5R2C1_SetPicMsg
	.type	HEVCHAL_V5R2C1_SetPicMsg, %function
HEVCHAL_V5R2C1_SetPicMsg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w2
	mov	x23, x1
	mov	w22, w3
	bl	_mcount
	mov	w0, w21
	bl	MEM_Phy2Vir
	mov	x20, x0
	cbz	x0, .L75
	ldr	x3, .LC31
	mov	x2, 1280
	mov	w1, 0
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x1, .LC33
	mov	w0, 4
	bl	dprint_vfmw
	ldrb	w5, [x19, 6]
	ldrb	w3, [x19, 8]
	ldrb	w1, [x19, 7]
	ldrb	w2, [x19, 9]
	ldrb	w0, [x19, 10]
	lsl	w1, w1, 24
	lsl	w2, w2, 22
	orr	w6, w1, w5, lsl 25
	orr	w2, w2, w3, lsl 23
	ldr	w4, [x19, 12]
	orr	w1, w6, w2
	orr	w3, w1, w0, lsl 21
	ldrb	w1, [x19, 16]
	ldp	w5, w2, [x19, 20]
	lsl	w5, w5, 9
	orr	w2, w2, w1, lsl 18
	orr	w0, w5, w4, lsl 19
	ldr	x1, .LC35
	orr	w0, w0, w2
	mov	w2, w21
	orr	w0, w3, w0
	str	w0, [x20]
	mov	w0, 4
	ldr	w3, [x20]
	bl	dprint_vfmw
	ldr	w0, [x19, 28]
	str	w0, [x20, 4]
	ldp	w5, w1, [x19, 44]
	ldp	w0, w3, [x19, 52]
	ldr	w2, [x19, 36]
	lsl	w5, w5, 24
	lsl	w0, w0, 18
	ldr	w4, [x19, 68]
	orr	w0, w0, w1, lsl 21
	orr	w5, w5, w2, lsl 29
	ldp	w2, w1, [x19, 60]
	orr	w0, w5, w0
	lsl	w5, w2, 12
	orr	w2, w5, w3, lsl 15
	orr	w5, w0, w2
	lsl	w0, w4, 6
	ldp	w3, w2, [x19, 72]
	orr	w4, w0, w1, lsl 9
	ldrb	w1, [x19, 40]
	orr	w2, w2, w3, lsl 3
	ldrb	w3, [x19, 41]
	orr	w0, w5, w4
	orr	w2, w0, w2
	lsl	w0, w3, 27
	orr	w0, w0, w1, lsl 28
	orr	w0, w2, w0
	str	w0, [x20, 8]
	ldp	w3, w2, [x19, 80]
	ldp	w5, w4, [x19, 88]
	ldp	w1, w0, [x19, 96]
	lsl	w4, w4, 8
	lsl	w2, w2, 16
	orr	w4, w4, w5, lsl 12
	orr	w2, w2, w3, lsl 22
	orr	w2, w4, w2
	orr	w0, w0, w1, lsl 4
	orr	w0, w2, w0
	str	w0, [x20, 12]
	ldr	w0, [x23, 1108]
	str	w0, [x20, 16]
	ldr	w0, [x23, 1112]
	str	w0, [x20, 20]
	ldr	w0, [x19, 1292]
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 1476]
	str	w0, [x20, 24]
	ldr	w0, [x23, 1120]
	str	w0, [x20, 28]
	ldr	w0, [x19, 2484]
	cbz	w0, .L66
	mov	w1, 0
	.p2align 2
.L64:
	add	x0, x19, x1, uxtw 2
	add	w2, w1, 8
	add	w1, w1, 1
	ldr	w0, [x0, 2420]
	add	x0, x0, 336
	ldr	w0, [x19, x0, lsl 2]
	str	w0, [x20, w2, uxtw 2]
	ldr	w0, [x19, 2484]
	cmp	w0, w1
	bhi	.L64
	cmp	w0, 15
	bhi	.L67
	.p2align 2
.L66:
	ldr	w1, [x19, 2420]
	add	w2, w0, 8
	add	w0, w0, 1
	add	x1, x1, 336
	cmp	w0, 15
	ldr	w1, [x19, x1, lsl 2]
	str	w1, [x20, w2, uxtw 2]
	bls	.L66
.L67:
	ldr	w1, [x23, 1124]
	add	x0, x19, 128
	str	w1, [x20, 100]
	add	x3, x19, 192
	add	x1, x20, 104
	.p2align 2
.L65:
	ldr	w2, [x0], 4
	str	w2, [x1], 4
	cmp	x3, x0
	bne	.L65
	ldr	w0, [x23, 1116]
	mov	x1, x23
	str	w0, [x20, 172]
	mov	x0, x19
	ldp	w2, w3, [x19, 192]
	orr	w2, w3, w2, lsl 16
	str	w2, [x20, 216]
	bl	HEVC_WriteTileInfo
	mov	w24, w0
	cbnz	w0, .L76
	ldr	w0, [x23, 1128]
	mov	x1, x20
	str	w0, [x20, 220]
	mov	w0, 64
	ldr	w2, [x23, 1140]
	str	w2, [x20, 224]
	ldr	w2, [x23, 1132]
	str	w2, [x20, 228]
	ldr	w2, [x23, 1144]
	str	w2, [x20, 232]
	ldr	w2, [x23, 1136]
	str	w2, [x20, 236]
	ldp	w4, w3, [x19, 228]
	ldrb	w2, [x19, 220]
	ldrb	w5, [x19, 221]
	lsl	w3, w3, 13
	lsl	w5, w5, 23
	orr	w5, w5, w2, lsl 24
	orr	w2, w3, w4, lsl 16
	orr	w3, w5, w2
	ldrb	w4, [x19, 222]
	ldrb	w5, [x19, 223]
	lsl	w5, w5, 21
	orr	w2, w5, w4, lsl 22
	ldrb	w4, [x19, 224]
	orr	w5, w3, w2
	ldrb	w3, [x19, 225]
	lsl	w3, w3, 19
	orr	w2, w3, w4, lsl 20
	ldrb	w4, [x19, 236]
	orr	w3, w5, w2
	ldrb	w5, [x19, 237]
	lsl	w5, w5, 11
	orr	w2, w5, w4, lsl 12
	orr	w5, w3, w2
	ldp	w4, w2, [x19, 240]
	ubfiz	w3, w4, 5, 5
	ldrb	w4, [x19, 238]
	and	w2, w2, 31
	orr	w3, w3, w4, lsl 10
	orr	w3, w5, w3
	orr	w2, w3, w2
	str	w2, [x20, 240]
	ldp	w2, w3, [x19, 248]
	orr	w2, w3, w2, lsl 16
	str	w2, [x20, 244]
	str	w22, [x20, 252]
	bl	HEVC_GetVirAddr
	mov	x20, x0
	mov	w1, w21
	mov	w0, 64
	bl	HEVC_GetPhyAddr
	mov	w2, w0
	mov	x3, x20
	add	x0, x19, 260
	mov	w1, 256
	bl	HEVC_WriteQmatrix
.L62:
	mov	w0, w24
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L76:
	ldr	x1, .LC37
	mov	w0, 1
	mov	w24, -1
	bl	dprint_vfmw
	b	.L62
.L75:
	ldr	x2, .LC29
	mov	w0, 0
	ldr	x3, .LC28
	mov	w24, -1
	ldr	x1, .LC30
	add	x2, x2, 2000
	bl	dprint_vfmw
	b	.L62
	.size	HEVCHAL_V5R2C1_SetPicMsg, .-HEVCHAL_V5R2C1_SetPicMsg
	.align	3
.LC28:
	.xword	.LC27
	.align	3
.LC29:
	.xword	.LANCHOR0
	.align	3
.LC30:
	.xword	.LC6
	.align	3
.LC31:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC33:
	.xword	.LC32
	.align	3
.LC35:
	.xword	.LC34
	.align	3
.LC37:
	.xword	.LC36
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
	ldr	x23, .LC42
	add	x27, x25, 16
	mov	w22, 1
	mov	w20, 0
	mov	x24, x23
.L83:
	lsl	w2, w20, 2
	mov	w3, w21
	sub	w2, w2, w20
	mov	x1, x23
	mov	w0, 4
	lsl	w5, w20, 2
	cbz	w20, .L85
	ldr	w4, [x27, -16]
	cbz	w4, .L81
.L79:
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
.L82:
	add	w20, w20, 1
	add	x27, x27, 4
	cmp	w20, 2
	add	x19, x19, 12
	add	w21, w21, 12
	add	w22, w22, 3
	bne	.L83
	mov	w0, 0
.L80:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L81:
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
	b	.L82
.L85:
	ldr	w4, [x25]
	cbnz	w4, .L79
	ldr	x2, .LC38
	mov	w0, 0
	ldr	x1, .LC40
	add	x2, x2, 2032
	bl	dprint_vfmw
	mov	w0, -1
	b	.L80
	.size	HEVCHAL_SetSliceMsgStreamAddrInfo, .-HEVCHAL_SetSliceMsgStreamAddrInfo
	.align	3
.LC38:
	.xword	.LANCHOR0
	.align	3
.LC40:
	.xword	.LC39
	.align	3
.LC42:
	.xword	.LC41
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
	cbz	w5, .L93
	mov	w8, 15
	mov	w4, 0
	mov	w0, 0
	b	.L92
	.p2align 3
.L90:
	cmp	w7, w0
	beq	.L99
.L91:
	add	w0, w0, 1
	cmp	w5, w0
	bls	.L93
.L92:
	add	x3, x19, x0, uxtw 2
	and	w2, w0, 7
	lsl	w6, w2, 2
	cmp	w2, 7
	sub	w7, w5, #1
	ldr	w2, [x3, 372]
	lsl	w2, w2, w6
	orr	w4, w4, w2
	bne	.L90
	str	w4, [x20, w8, sxtw 2]
	add	w0, w0, 1
	add	w8, w8, 1
	mov	w4, 0
	ldr	w5, [x19, 68]
	cmp	w5, w0
	bhi	.L92
.L93:
	ldr	w5, [x19, 72]
	cbz	w5, .L86
	mov	w8, 17
	mov	w4, 0
	mov	w0, 0
	b	.L96
	.p2align 3
.L94:
	cmp	w7, w0
	beq	.L100
.L95:
	add	w0, w0, 1
	cmp	w5, w0
	bls	.L86
.L96:
	add	x3, x19, x0, uxtw 2
	and	w2, w0, 7
	lsl	w6, w2, 2
	cmp	w2, 7
	sub	w7, w5, #1
	ldr	w2, [x3, 436]
	lsl	w2, w2, w6
	orr	w4, w4, w2
	bne	.L94
	str	w4, [x20, w8, sxtw 2]
	add	w0, w0, 1
	add	w8, w8, 1
	mov	w4, 0
	ldr	w5, [x19, 72]
	cmp	w5, w0
	bhi	.L96
.L86:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L99:
	str	w4, [x20, w8, sxtw 2]
	ldr	w5, [x19, 68]
	b	.L91
	.p2align 3
.L100:
	str	w4, [x20, w8, sxtw 2]
	ldr	w5, [x19, 72]
	b	.L95
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
	cbz	w1, .L102
	ldr	w1, [x19, 76]
	cmp	w1, 1
	beq	.L103
.L102:
	ldrb	w1, [x22, 40]
	cmp	w1, 1
	beq	.L121
.L101:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L121:
	ldr	w1, [x19, 76]
	cbnz	w1, .L101
	ldr	w1, [x19, 68]
	mov	w2, 0
	cbz	w1, .L110
	.p2align 2
.L107:
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
	bhi	.L107
	ldr	w1, [x19, 76]
	cbnz	w1, .L101
.L110:
	ldr	w1, [x19, 72]
	cbz	w1, .L101
	mov	w2, 0
	.p2align 2
.L108:
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
	bhi	.L108
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L103:
	ldr	w1, [x19, 68]
	mov	w2, 0
	cbnz	w1, .L107
	b	.L101
	.size	HEVCHAL_SetSliceMsgWPInfo, .-HEVCHAL_SetSliceMsgWPInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCHAL_V5R2C1_SetSliceMsg
	.type	HEVCHAL_V5R2C1_SetSliceMsg, %function
HEVCHAL_V5R2C1_SetSliceMsg:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	w25, w3
	mov	x19, x2
	mov	w21, w5
	mov	w24, w6
	mov	w23, w7
	bl	_mcount
	mov	w0, w25
	bl	MEM_Phy2Vir
	mov	x22, x0
	cbz	x0, .L134
	ldr	x1, .LC47
	mov	x2, 1280
	ldr	x3, [x1, 96]
	mov	w1, 0
	blr	x3
	mov	w3, w25
	mov	x2, x22
	mov	x1, x19
	mov	x0, x20
	bl	HEVCHAL_SetSliceMsgStreamAddrInfo
	cmn	w0, #1
	beq	.L124
	ldrb	w4, [x19, 24]
	ldrb	w2, [x19, 25]
	ldrb	w1, [x19, 32]
	ldr	w0, [x19, 28]
	lsl	w2, w2, 26
	ldr	w3, [x19, 36]
	orr	w2, w2, w4, lsl 27
	ubfiz	w0, w0, 19, 7
	orr	w2, w2, w3
	orr	w0, w0, w1, lsl 18
	orr	w0, w2, w0
	ldr	x1, .LC45
	str	w0, [x22, 24]
	add	x0, x1, 2104
	ldp	w5, w3, [x19, 56]
	ldr	w1, [x19, 44]
	ldr	w2, [x19, 76]
	lsl	w5, w5, 20
	orr	w5, w5, w1, lsl 24
	ldr	w4, [x0, x2, lsl 2]
	ldp	w0, w1, [x19, 68]
	lsl	w1, w1, 8
	orr	w0, w4, w0, lsl 2
	orr	w1, w1, w3, lsl 16
	ldrb	w3, [x19, 64]
	orr	w2, w5, w1
	ldr	w1, [x19, 40]
	orr	w4, w2, w0
	ldrb	w0, [x19, 65]
	lsl	w0, w0, 14
	orr	w0, w0, w3, lsl 15
	orr	w2, w4, w0
	ldrb	w0, [x19, 52]
	lsl	w0, w0, 27
	orr	w0, w0, w1, lsl 28
	orr	w0, w2, w0
	str	w0, [x22, 28]
	str	w24, [x22, 32]
	ldr	w0, [x20, 24]
	add	w0, w0, 1
	udiv	w1, w24, w0
	msub	w0, w1, w0, w24
	orr	w0, w0, w1, lsl 16
	str	w0, [x22, 36]
	str	w23, [x22, 40]
	ldp	w1, w0, [x19, 96]
	ubfiz	w1, w1, 8, 5
	and	w0, w0, 31
	orr	w0, w1, w0
	str	w0, [x22, 44]
	ldp	w0, w4, [x19, 104]
	ldrb	w3, [x19, 113]
	ldrb	w2, [x19, 112]
	ubfiz	w0, w0, 16, 4
	ldrb	w1, [x19, 114]
	ubfiz	w4, w4, 8, 4
	ldrb	w5, [x19, 115]
	lsl	w2, w2, 2
	orr	w4, w0, w4
	orr	w2, w2, w3, lsl 3
	orr	w0, w4, w2
	orr	w1, w5, w1, lsl 1
	orr	w0, w0, w1
	str	w0, [x22, 48]
	ldr	w4, [x19, 68]
	cbz	w4, .L130
	add	x3, x19, 116
	mov	w2, 0
	mov	w0, 0
	.p2align 2
.L126:
	ldr	w1, [x3], 4
	lsl	w1, w1, w0
	add	w0, w0, 1
	cmp	w0, w4
	orr	w2, w2, w1
	bne	.L126
.L125:
	str	w2, [x22, 52]
	ldr	w4, [x19, 72]
	cbz	w4, .L131
	add	x3, x19, 180
	mov	w2, 0
	mov	w0, 0
	.p2align 2
.L128:
	ldr	w1, [x3], 4
	lsl	w1, w1, w0
	add	w0, w0, 1
	cmp	w0, w4
	orr	w2, w2, w1
	bne	.L128
.L127:
	mov	x1, x22
	mov	x0, x19
	str	w2, [x22, 56]
	bl	HEVCHAL_SetSliceMsgAPCIndex
	ldr	w0, [x19, 564]
	mov	w4, 16394
	str	w0, [x22, 92]
	mov	x2, x22
	mov	x0, x20
	mov	x1, x19
	ldr	w3, [x20, 84]
	lsr	w3, w3, 1
	orr	w3, w4, w3, lsl 8
	str	w3, [x22, 96]
	ldr	w3, [x29, 80]
	str	w3, [x22, 172]
	ldr	w3, [x29, 88]
	str	w3, [x22, 176]
	str	w21, [x22, 252]
	bl	HEVCHAL_SetSliceMsgWPInfo
	mov	w0, 0
.L124:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L130:
	mov	w2, 0
	b	.L125
.L131:
	mov	w2, 0
	b	.L127
.L134:
	ldr	x2, .LC45
	mov	w0, 0
	ldr	x3, .LC44
	ldr	x1, .LC46
	add	x2, x2, 2072
	bl	dprint_vfmw
	mov	w0, -1
	b	.L124
	.size	HEVCHAL_V5R2C1_SetSliceMsg, .-HEVCHAL_V5R2C1_SetSliceMsg
	.align	3
.LC44:
	.xword	.LC43
	.align	3
.LC45:
	.xword	.LANCHOR0
	.align	3
.LC46:
	.xword	.LC6
	.align	3
.LC47:
	.xword	vfmw_Osal_Func_Ptr_S
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
	bgt	.L140
	cbz	x19, .L141
	ldr	w1, [x19, 2484]
	mov	w0, 0
	cmp	w1, 16
	bhi	.L142
.L137:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L140:
	ldr	x2, .LC49
	mov	w4, 1
	ldr	x1, .LC51
	mov	w3, w20
	add	x2, x2, 2120
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L137
	.p2align 3
.L142:
	ldr	x2, .LC49
	ldr	x3, .LC56
	ldr	x1, .LC54
	add	x2, x2, 2120
	bl	dprint_vfmw
	mov	w0, -1
	b	.L137
.L141:
	ldr	x2, .LC49
	mov	w0, 0
	ldr	x3, .LC53
	ldr	x1, .LC54
	add	x2, x2, 2120
	bl	dprint_vfmw
	mov	w0, -1
	b	.L137
	.size	HEVCHAL_CheckParaValid, .-HEVCHAL_CheckParaValid
	.align	3
.LC49:
	.xword	.LANCHOR0
	.align	3
.LC51:
	.xword	.LC50
	.align	3
.LC53:
	.xword	.LC52
	.align	3
.LC54:
	.xword	.LC6
	.align	3
.LC56:
	.xword	.LC55
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
	bgt	.L148
	ldr	x0, [x19]
	cbz	x0, .L146
.L147:
	mov	w0, 0
.L145:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L146:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	str	x0, [x19]
	cbnz	x0, .L147
	ldr	x2, .LC59
	ldr	x1, .LC61
	add	x2, x2, 2144
	bl	dprint_vfmw
	mov	w0, -1
	b	.L145
	.p2align 3
.L148:
	ldr	x1, .LC58
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L145
	.size	HEVCHAL_GetVdmRegVirAddr, .-HEVCHAL_GetVdmRegVirAddr
	.align	3
.LC58:
	.xword	.LC57
	.align	3
.LC59:
	.xword	.LANCHOR0
	.align	3
.LC61:
	.xword	.LC60
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
	cbz	x19, .L154
	ldr	w2, [x19, 92]
	mov	w0, 0
	cmp	w2, w20
	ccmp	w21, wzr, 4, cc
	cset	w1, gt
	cbnz	w1, .L155
.L151:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L155:
	ldr	x1, .LC66
	mov	w3, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L151
.L154:
	ldr	x2, .LC62
	mov	w3, w21
	ldr	x1, .LC64
	mov	w0, 1
	add	x2, x2, 2176
	bl	dprint_vfmw
	mov	w0, -1
	b	.L151
	.size	HEVCHAL_CheckSlicePara, .-HEVCHAL_CheckSlicePara
	.align	3
.LC62:
	.xword	.LANCHOR0
	.align	3
.LC64:
	.xword	.LC63
	.align	3
.LC66:
	.xword	.LC65
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
	bge	.L157
	ldr	x19, [x19, 1360]
	cbz	x19, .L160
	ldr	w0, [x19, 92]
	cmp	w1, w0
	bcc	.L157
	add	w2, w20, 1
	b	.L159
	.p2align 3
.L161:
	ldr	x19, [x19, 1360]
	cbz	x19, .L160
	ldr	w0, [x19, 92]
	cmp	w1, w0
	bcc	.L157
.L159:
	cmp	w2, w21
	str	w2, [x22]
	add	w2, w2, 1
	bne	.L161
.L157:
	mov	x0, x19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L160:
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
	bgt	.L167
	cmp	w19, w3
	blt	.L167
	ldr	w2, [x20, 92]
	mov	w0, 0
	cmp	w2, w3
	bhi	.L171
.L169:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L167:
	ldr	x1, .LC68
	mov	w4, w19
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L169
	.p2align 3
.L171:
	ldr	x1, .LC70
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L169
	.size	HEVCHAL_CheckSliceAddrValid, .-HEVCHAL_CheckSliceAddrValid
	.align	3
.LC68:
	.xword	.LC67
	.align	3
.LC70:
	.xword	.LC69
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCHAL_V5R2C1_CfgVdmReg
	.type	HEVCHAL_V5R2C1_CfgVdmReg, %function
HEVCHAL_V5R2C1_CfgVdmReg:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w2
	mov	x20, x3
	mov	x22, x1
	bl	_mcount
	ldr	x1, .LC72
	sbfiz	x0, x21, 6, 32
	ldr	x2, .LC71
	cmp	x20, xzr
	ldrb	w1, [x1]
	add	x0, x2, x0
	ccmp	w1, 1, 4, eq
	ldr	w0, [x0, 8]
	bne	.L186
	ldr	x2, .LC76
	ldr	x0, [x2, w0, sxtw 3]
	cbz	x0, .L181
	ldr	w23, [x0, 1272]
	uxtb	w0, w23
	and	w25, w0, 1
.L175:
	cmp	w1, 1
	beq	.L176
	strb	w0, [x20, 1]
.L176:
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
	ldr	w24, [x29, 92]
	mov	w0, 8
	add	w1, w2, w1
	mov	w2, w21
	bfi	w24, w1, 0, 20
	str	w24, [x19, 2512]
	mov	w1, w24
	str	w24, [x29, 92]
	bl	MFDE_ConfigReg
	ldr	x1, .LC78
	mov	w2, w24
	mov	w0, 3
	bl	dprint_vfmw
	str	wzr, [x29, 92]
	ldr	w1, [x19, 1328]
	mov	w0, 0
	ldr	w2, [x19, 1340]
	bfi	w0, w1, 4, 1
	ldr	w1, [x19, 196]
	bfi	w0, w2, 6, 1
	mov	w2, 13
	orr	w0, w0, -128
	cmp	w1, 1920
	strb	w2, [x29, 92]
	strb	w0, [x29, 93]
	bls	.L187
	ldrb	w1, [x19]
	mov	w2, 0
	strb	wzr, [x19, 5]
	and	w1, w1, 1
.L178:
	ldrb	w0, [x29, 95]
	mov	w24, 3
	mov	x3, x20
	bfi	w0, w2, 5, 1
	strb	w0, [x29, 95]
	mov	w2, w21
	ldrh	w0, [x29, 94]
	bfi	w0, w24, 0, 12
	strh	w0, [x29, 94]
	lsr	x0, x0, 8
	bfi	w0, w1, 6, 1
	and	w0, w0, 127
	bfi	w0, w25, 4, 1
	strb	w0, [x29, 95]
	mov	w0, 12
	ldr	w25, [x29, 92]
	str	w25, [x19, 2516]
	mov	w1, w25
	bl	MFDE_ConfigReg
	ldr	x1, .LC80
	mov	w2, w25
	mov	w0, w24
	bl	dprint_vfmw
	ldr	w25, [x22, 72]
	mov	x3, x20
	mov	w2, w21
	and	w25, w25, -16
	mov	w0, 16
	mov	w1, w25
	str	w25, [x19, 2520]
	bl	MFDE_ConfigReg
	ldr	x1, .LC82
	mov	w2, w25
	mov	w0, w24
	bl	dprint_vfmw
	ldr	w4, [x22, 56]
	mov	x3, x20
	mov	w2, w21
	mov	w0, 20
	and	w4, w4, -16
	str	w4, [x19, 2524]
	mov	w1, w4
	mov	w22, 3075
	movk	w22, 0x30, lsl 16
	bl	MFDE_ConfigReg
	ldr	w4, [x19, 1332]
	mov	x3, x20
	mov	w2, w21
	mov	w0, 24
	and	w4, w4, -16
	str	w4, [x19, 2528]
	mov	w1, w4
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
	cmp	w23, 1
	beq	.L188
.L179:
	ldr	w22, [x19, 1296]
	mov	x3, x20
	mov	w0, 100
	mov	w2, w21
	mov	w1, w22
	str	w22, [x19, 2568]
	bl	MFDE_ConfigReg
	ldr	x1, .LC88
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
	ldr	x1, .LC90
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
	bls	.L182
	mov	w1, 0
	mov	w19, 0
.L180:
	mov	x3, x20
	mov	w0, 4
	mov	w2, w21
	bl	SCD_ConfigReg
	ldr	x1, .LC92
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	mov	x3, x20
	mov	w2, w21
	mov	w1, 0
	mov	w0, 152
	bl	MFDE_ConfigReg
	ldr	x1, .LC94
	mov	w2, 0
	mov	w0, 3
	bl	dprint_vfmw
	mov	w0, 32
	mov	x3, x20
	mov	w2, w21
	mov	w1, -1
	bl	MFDE_ConfigReg
	mov	w0, 0
.L174:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L187:
	mov	w0, 1
	strb	wzr, [x19]
	strb	w0, [x19, 5]
	mov	w1, 0
	mov	w2, 1
	b	.L178
	.p2align 3
.L182:
	mov	w1, 1
	mov	w19, w1
	b	.L180
	.p2align 3
.L181:
	mov	w25, 0
	mov	w0, 0
	mov	w23, 0
	b	.L175
	.p2align 3
.L188:
	mov	x3, x20
	mov	w2, w21
	mov	w1, 60
	mov	w0, 92
	bl	MFDE_ConfigReg
	ldr	x1, .LC84
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
	ldr	x1, .LC86
	mov	w2, w22
	mov	w0, w24
	bl	dprint_vfmw
	b	.L179
.L186:
	ldr	x2, .LC73
	mov	x3, x20
	ldr	x1, .LC75
	mov	w0, 0
	add	x2, x2, 2200
	bl	dprint_vfmw
	mov	w0, -1
	b	.L174
	.size	HEVCHAL_V5R2C1_CfgVdmReg, .-HEVCHAL_V5R2C1_CfgVdmReg
	.align	3
.LC71:
	.xword	g_VdmDrvParam
	.align	3
.LC72:
	.xword	g_HalDisable
	.align	3
.LC73:
	.xword	.LANCHOR0
	.align	3
.LC75:
	.xword	.LC74
	.align	3
.LC76:
	.xword	s_pstVfmwChan
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCHAL_V5R2C1_SetSliceMsgSedOnly
	.type	HEVCHAL_V5R2C1_SetSliceMsgSedOnly, %function
HEVCHAL_V5R2C1_SetSliceMsgSedOnly:
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
	ble	.L190
	mov	w0, 0
	mov	w24, 0
	mov	x19, 0
	.p2align 2
.L192:
	ldrb	w2, [x1, 25]
	cmp	w2, wzr
	csel	w24, w24, w0, ne
	add	w0, w0, 1
	csel	x19, x19, x1, ne
	cmp	w0, w3
	ldr	x1, [x1, 1360]
	bne	.L192
	cbz	x19, .L190
	sub	w0, w0, w24
	mov	w20, 0
	cmp	w0, wzr
	mov	w21, 205
	bgt	.L204
	b	.L200
	.p2align 3
.L210:
	ldr	x4, [x19, 1360]
	ldrb	w8, [x22, 225]
	ldr	w2, [x1, 56]
	ldr	w0, [x4, 92]
	mov	w5, w2
	sub	w0, w0, #1
	cbz	w8, .L208
	ldr	w1, [x4, 568]
	mov	w5, w2
	.p2align 2
.L197:
	str	w1, [sp]
	mov	x2, x19
	str	w0, [sp, 8]
	mov	w4, 0
	mov	x1, x23
	mov	x0, x22
	add	w20, w20, 1
	bl	HEVCHAL_V5R2C1_SetSliceMsg
	cbnz	w0, .L209
	ldr	w0, [x22, 2488]
	ldr	x19, [x19, 1360]
	sub	w0, w0, w24
	cmp	w0, w20
	ble	.L200
.L204:
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
	ble	.L210
	ldp	w1, w0, [x22, 20]
	madd	w0, w1, w0, w0
	add	w0, w0, w1
.L208:
	mov	w1, w0
	b	.L197
	.p2align 3
.L200:
	mov	w0, 0
.L194:
	add	sp, x29, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L209:
	ldr	x2, .LC95
	mov	w0, 1
	ldr	x1, .LC99
	add	x2, x2, 2232
	bl	dprint_vfmw
	add	sp, x29, 0
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L190:
	ldr	x2, .LC95
	mov	w0, 1
	ldr	x1, .LC97
	add	x2, x2, 2232
	bl	dprint_vfmw
	mov	w0, -1
	b	.L194
	.size	HEVCHAL_V5R2C1_SetSliceMsgSedOnly, .-HEVCHAL_V5R2C1_SetSliceMsgSedOnly
	.align	3
.LC95:
	.xword	.LANCHOR0
	.align	3
.LC97:
	.xword	.LC96
	.align	3
.LC99:
	.xword	.LC98
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCHAL_V5R2C1_StartDec
	.type	HEVCHAL_V5R2C1_StartDec, %function
HEVCHAL_V5R2C1_StartDec:
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
	ldr	x21, .LC100
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
	beq	.L214
	ldr	x23, [x29, 120]
	mov	w1, w20
	mov	x0, x23
	bl	HEVCHAL_GetVdmRegVirAddr
	cmn	w0, #1
	beq	.L214
	mov	w2, w20
	mov	x3, x22
	mov	x1, x23
	mov	x0, x19
	bl	HEVCHAL_V5R2C1_CfgVdmReg
	ldp	w2, w3, [x23, 72]
	mov	x1, x23
	mov	x0, x19
	bl	HEVCHAL_V5R2C1_SetPicMsg
	ldr	x20, [x19, 2496]
	cbz	x20, .L259
	ldr	w0, [x19, 5188]
	cmp	w0, 1
	beq	.L260
	ldr	w22, [x20, 92]
	cbnz	w22, .L261
	mov	x27, x20
	str	wzr, [x29, 108]
.L217:
	ldp	w22, w0, [x19, 20]
	ldr	w1, [x19, 2488]
	madd	w0, w22, w0, w0
	cmp	w1, wzr
	add	w22, w0, w22
	ble	.L220
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
.L232:
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
	beq	.L214
	ldr	w1, [x19, 2488]
	add	w28, w28, 1
	ldr	w6, [x27, 80]
	cmp	w1, w28
	ldr	w7, [x27, 92]
	ble	.L235
	ldr	x23, [x27, 1360]
	cbnz	x23, .L258
	b	.L222
	.p2align 3
.L262:
	add	w28, w28, 1
	cmp	w1, w28
	ble	.L221
	ldr	x23, [x23, 1360]
	cbz	x23, .L222
.L258:
	ldr	w0, [x23, 92]
	cmp	w7, w0
	bcs	.L262
.L227:
	cmp	w25, 209
	ccmp	w1, w28, 4, ne
	beq	.L263
	ldr	w3, [x23, 92]
	ldrb	w0, [x19, 225]
	sub	w3, w3, #1
	mov	w4, w3
	cbz	w0, .L230
	ldr	w4, [x23, 568]
.L230:
	ldr	w0, [x29, 132]
	add	w0, w28, w0
	add	x0, x20, x0, sxtw
	add	x0, x21, x0, lsl 2
	ldr	w5, [x0, 56]
.L229:
	mov	w2, w22
	mov	w1, w4
	mov	x0, x27
	str	w3, [x27, 572]
	stp	w6, w7, [x29, 136]
	stp	w5, w3, [x29, 144]
	str	w4, [x29, 152]
	bl	HEVCHAL_CheckSliceAddrValid
	cmn	w0, #1
	beq	.L214
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
	bl	HEVCHAL_V5R2C1_SetSliceMsg
	mov	w25, w0
	cbnz	w0, .L264
	ldr	w0, [x19, 2488]
	add	w24, w24, 1
	ldr	w2, [x27, 572]
	cmp	w28, w0
	bge	.L265
	mov	x27, x23
	b	.L232
.L261:
	ldrb	w0, [x19, 225]
	sub	w8, w22, #1
	mov	w9, w8
	cbz	w0, .L218
	ldr	w9, [x20, 568]
.L218:
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
	bl	HEVCHAL_V5R2C1_SetSliceMsg
	ldp	w11, w10, [x29, 152]
	cbnz	w0, .L266
	stp	w28, w27, [x20]
	stp	w11, w10, [x20, 8]
	stp	w26, w25, [x20, 16]
	str	w22, [x20, 92]
	str	w24, [x29, 108]
	ldr	x27, [x19, 2496]
	b	.L217
	.p2align 3
.L263:
	str	xzr, [x27, 1360]
	mov	w4, w22
	mov	w3, w22
	mov	w5, 0
	ldr	w28, [x19, 2488]
	b	.L229
.L235:
	mov	x23, x27
	.p2align 2
.L221:
	cbnz	x23, .L227
	.p2align 2
.L222:
	ldr	x2, .LC101
	mov	w0, 1
	ldr	x1, .LC106
	mov	w25, -1
	add	x2, x2, 2272
	bl	dprint_vfmw
	b	.L213
.L214:
	mov	w25, -1
.L213:
	add	sp, x29, 0
	mov	w0, w25
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
.L264:
	ldr	x2, .LC101
	mov	w0, 1
	ldr	x1, .LC108
	mov	w25, -1
	add	x2, x2, 2272
	bl	dprint_vfmw
	b	.L213
.L265:
	cmp	w24, wzr
	ccmp	w0, wzr, 4, gt
	ble	.L220
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
	bl	HEVCHAL_V5R2C1_CutSliceChain
	b	.L213
.L260:
	ldr	x1, [x29, 120]
	mov	x0, x19
	bl	HEVCHAL_V5R2C1_SetSliceMsgSedOnly
	mov	w25, w0
	b	.L213
.L220:
	ldr	x1, .LC110
	mov	w0, 1
	mov	w25, -1
	bl	dprint_vfmw
	b	.L213
.L266:
	ldr	x2, .LC101
	mov	w0, w24
	ldr	x1, .LC104
	mov	w25, -1
	add	x2, x2, 2272
	bl	dprint_vfmw
	b	.L213
.L259:
	ldr	x2, .LC101
	mov	w0, 0
	ldr	x1, .LC103
	mov	w25, -1
	add	x2, x2, 2272
	bl	dprint_vfmw
	b	.L213
	.size	HEVCHAL_V5R2C1_StartDec, .-HEVCHAL_V5R2C1_StartDec
	.align	3
.LC100:
	.xword	g_HwMem
	.align	3
.LC101:
	.xword	.LANCHOR0
	.align	3
.LC103:
	.xword	.LC102
	.align	3
.LC104:
	.xword	.LC98
	.align	3
.LC106:
	.xword	.LC105
	.align	3
.LC108:
	.xword	.LC107
	.align	3
.LC110:
	.xword	.LC109
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
	.type	__func__.11792, %object
	.size	__func__.11792, 18
__func__.11792:
	.string	"HEVCWriteCabacTab"
	.zero	6
	.type	__func__.11813, %object
	.size	__func__.11813, 29
__func__.11813:
	.string	"HEVCHAL_V5R2C1_CutSliceChain"
	.zero	3
	.type	__func__.11832, %object
	.size	__func__.11832, 19
__func__.11832:
	.string	"HEVC_WriteTileInfo"
	.zero	5
	.type	__func__.11858, %object
	.size	__func__.11858, 25
__func__.11858:
	.string	"HEVCHAL_V5R2C1_SetPicMsg"
	.zero	7
	.type	__func__.11878, %object
	.size	__func__.11878, 34
__func__.11878:
	.string	"HEVCHAL_SetSliceMsgStreamAddrInfo"
	.zero	6
	.type	__func__.11932, %object
	.size	__func__.11932, 27
__func__.11932:
	.string	"HEVCHAL_V5R2C1_SetSliceMsg"
	.zero	5
	.type	s_SliceTypeForPMV, %object
	.size	s_SliceTypeForPMV, 12
s_SliceTypeForPMV:
	.word	2
	.word	1
	.word	0
	.zero	4
	.type	__func__.11943, %object
	.size	__func__.11943, 23
__func__.11943:
	.string	"HEVCHAL_CheckParaValid"
	.zero	1
	.type	__func__.11949, %object
	.size	__func__.11949, 25
__func__.11949:
	.string	"HEVCHAL_GetVdmRegVirAddr"
	.zero	7
	.type	__func__.11955, %object
	.size	__func__.11955, 23
__func__.11955:
	.string	"HEVCHAL_CheckSlicePara"
	.zero	1
	.type	__func__.11982, %object
	.size	__func__.11982, 25
__func__.11982:
	.string	"HEVCHAL_V5R2C1_CfgVdmReg"
	.zero	7
	.type	__func__.12002, %object
	.size	__func__.12002, 34
__func__.12002:
	.string	"HEVCHAL_V5R2C1_SetSliceMsgSedOnly"
	.zero	6
	.type	__func__.12032, %object
	.size	__func__.12032, 24
__func__.12032:
	.string	"HEVCHAL_V5R2C1_StartDec"
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
	ASCII(.string	"qmatrix[%d] = 0x%x\n" )
	.zero	4
.LC19:
	ASCII(.string	"picmsg Dxx addr 0x%x = 0x%x\n" )
	.zero	3
.LC21:
	ASCII(.string	"can not map slice segment info virtual address!\n" )
	.zero	7
.LC25:
	ASCII(.string	"TileId: 0x%x\n" )
	.zero	2
.LC27:
	ASCII(.string	"can not map down msg virtual address!\n" )
	.zero	1
.LC32:
	ASCII(.string	"pic msg burst0:\n" )
	.zero	7
.LC34:
	ASCII(.string	"picmsg D[0] addr 0x%x = 0x%x\n" )
	.zero	2
.LC36:
	ASCII(.string	"HEVC_WriteTileInfo return error.\n" )
	.zero	6
.LC39:
	ASCII(.string	"%s FATAL: i=0, valid_bitlen=0\n" )
	.zero	1
.LC41:
	ASCII(.string	"slicemsg D[%d] addr 0x%x = 0x%x\n" )
	.zero	7
.LC43:
	ASCII(.string	"HEVCHAL_V5R2C1_SetSliceMsg can not map slice msg virtual address!\n" )
	.zero	5
.LC50:
	ASCII(.string	"%s VdhId %d >= %d\n" )
	.zero	5
.LC52:
	ASCII(.string	"pParam is null\n" )
.LC55:
	ASCII(.string	"FATAL: ApcSize > 16\n" )
	.zero	3
.LC57:
	ASCII(.string	"VdhId is wrong! HEVC4HAL_V200R003_StartDec\n" )
	.zero	4
.LC60:
	ASCII(.string	"%s vdm register virtual address not mapped, reset failed!\n" )
	.zero	5
.LC63:
	ASCII(.string	"%s: i = %d, pSlicePara = NULL!\n" )
.LC65:
	ASCII(.string	"SliceSegmentTileAddress %d < prevEndCtbInSliceTile %d\n" )
	.zero	1
.LC67:
	ASCII(.string	"end_ctb_in_slice_raster(%d)/end_ctb_in_slice_tile(%d) > pic_max_ctb(%d)\n" )
	.zero	7
.LC69:
	ASCII(.string	"SliceSegmentTileAddress %d > end_ctb_in_slice_tile %d\n" )
	.zero	1
.LC74:
	ASCII(.string	"%s: pMfdeTask(%p) = NULL\n" )
	.zero	6
.LC77:
	ASCII(.string	"HEVC_BASIC_CFG0 = 0x%x\n" )
.LC79:
	ASCII(.string	"HEVC_BASIC_CFG1 = 0x%x\n" )
.LC81:
	ASCII(.string	"AVM_ADDR = 0x%x\n" )
	.zero	7
.LC83:
	ASCII(.string	"VREG_V200R003_PART_DEC_OVER_INT_LEVEL=0x%x\n" )
	.zero	4
.LC85:
	ASCII(.string	"VREG_LINE_NUM_STADDR = 0x%x\n" )
	.zero	3
.LC87:
	ASCII(.string	"HEVC_VFMW_YSTADDR_1D = 0x%x\n" )
	.zero	3
.LC89:
	ASCII(.string	"HEVC_VFMW_UVOFFSET_1D = 0x%x\n" )
	.zero	2
.LC91:
	ASCII(.string	"SCD REG_EMAR_ID = 0x%x\n" )
.LC93:
	ASCII(.string	"VREG_FF_APT_EN = 0x%x\n" )
	.zero	1
.LC96:
	ASCII(.string	"%s : pTargetSlicePara == NULL\n" )
	.zero	1
.LC98:
	ASCII(.string	"%s 0: set slice msg failed!\n" )
	.zero	3
.LC102:
	ASCII(.string	"%s pFirstSlice = NULL!\n" )
.LC105:
	ASCII(.string	"%s pTargetSlicePara is NULL!\n" )
	.zero	2
.LC107:
	ASCII(.string	"%s 1: set slice msg failed!\n" )
	.zero	3
.LC109:
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
