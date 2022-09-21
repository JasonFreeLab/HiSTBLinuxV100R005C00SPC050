#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vdm_hal.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_GetHalMemSize
	.type	VDMHAL_V5R6C1_GetHalMemSize, %function
VDMHAL_V5R6C1_GetHalMemSize:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 6291456
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V5R6C1_GetHalMemSize, .-VDMHAL_V5R6C1_GetHalMemSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_OpenHAL
	.type	VDMHAL_V5R6C1_OpenHAL, %function
VDMHAL_V5R6C1_OpenHAL:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L15
	ldp	w23, w22, [x19]
	ldr	w19, [x19, 8]
	cbz	w23, .L16
	mov	w0, 6291455
	cmp	w22, w0
	ble	.L17
	cmp	w19, wzr
	bgt	.L18
	sxtw	x20, w19
	ldr	x25, .LC14
	ldr	x21, .LC15
	mov	x2, 268
	add	x0, x20, x20, lsl 4
	mov	w1, 0
	lsl	x0, x0, 2
	ldr	x3, [x25, 96]
	sub	x0, x0, x20
	add	x0, x21, x0, lsl 2
	blr	x3
	ldr	x24, .LC0
	lsl	x0, x20, 6
	ldr	x3, [x25, 96]
	sub	x0, x0, x20
	mov	w1, 4
	lsl	x0, x0, 2
	str	w1, [x21]
	sub	x25, x0, x20
	mov	x2, 1256
	mov	w1, 0
	add	x25, x0, x25, lsl 2
	add	x21, x24, x25
	mov	x0, x21
	blr	x3
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	mov	x2, x0
	ldr	x1, .LC17
	str	x0, [x24, x25]
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 53248
	movk	w0, 0xf8c3, lsl 16
	bl	MEM_Phy2Vir
	mov	x2, x0
	ldr	x1, .LC19
	str	x0, [x21, 16]
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1256
	add	w4, w23, 1023
	and	w4, w4, -1024
	add	w1, w23, w22
	smull	x19, w19, w0
	sub	w1, w1, w4
	mov	w2, 1024
	add	x0, x19, 56
	add	x19, x19, 896
	stp	w4, w1, [x21, 32]
	str	w2, [x21, 40]
	add	x0, x24, x0
	add	x2, x24, x19
	mov	w1, w4
	.p2align 2
.L8:
	str	w1, [x0], 4
	add	w1, w1, 1280
	cmp	x0, x2
	bne	.L8
	lsl	x0, x20, 6
	add	w2, w4, 266240
	sub	x0, x0, x20
	add	w2, w2, 3072
	lsl	x0, x0, 2
	add	w3, w2, 4096
	sub	x20, x0, x20
	mov	w7, 210
	add	w3, w3, 1024
	add	x0, x0, x20, lsl 2
	add	w1, w3, 32768
	add	x0, x24, x0
	add	w1, w1, 1023
	and	w1, w1, -32768
	add	w4, w1, 4427776
	add	w5, w1, 4370432
	str	w7, [x0, 1080]
	add	x7, x0, 1024
	add	w4, w4, 1024
	add	w5, w5, 2048
	add	w6, w1, 589824
	add	w8, w1, 45056
	stp	w2, w1, [x7, 80]
	stp	w1, w1, [x7, 88]
	str	w3, [x0, 1124]
	add	w3, w1, 1773568
	add	w3, w3, 1152
	add	w7, w1, 1093632
	add	w2, w1, 4390912
	cmp	w4, w3
	add	w2, w2, 1024
	str	w7, [x0, 1164]
	add	w7, w1, 4423680
	str	w5, [x0, 1192]
	str	w3, [x0, 1152]
	add	w5, w1, 4374528
	str	w2, [x0, 1204]
	add	w5, w5, 1024
	str	w2, [x0, 1220]
	csel	w2, w4, w3, cs
	add	w3, w7, 1024
	str	w3, [x0, 1200]
	add	w3, w1, 1769472
	add	w4, w6, 2048
	add	w3, w3, 2048
	str	w5, [x0, 1196]
	sub	w2, w2, w23
	add	w5, w1, 1179648
	add	w5, w5, 2048
	str	w1, [x0, 1172]
	str	w4, [x0, 1132]
	cmp	w22, w2
	add	w4, w1, 2142208
	str	w3, [x0, 1144]
	str	w3, [x0, 1148]
	add	w3, w1, 3190784
	str	w6, [x0, 1120]
	add	w1, w1, 4239360
	str	w6, [x0, 1128]
	str	wzr, [x0, 1156]
	str	w8, [x0, 1160]
	str	wzr, [x0, 1184]
	str	w5, [x0, 1136]
	str	w5, [x0, 1140]
	str	w4, [x0, 1168]
	str	w3, [x0, 1176]
	str	w1, [x0, 1208]
	bcc	.L9
	mov	x0, x21
	bl	H264HAL_V5R6C1_InitHal
	cmp	w0, wzr
	mov	x0, x21
	csetm	w19, ne
	bl	HEVCHAL_V5R6C1_InitHal
	cmp	w0, wzr
	csinv	w19, w19, wzr, eq
.L4:
	mov	w0, w19
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L18:
	ldr	x1, .LC13
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	ldr	x25, [sp, 64]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L9:
	ldr	x1, .LC21
	mov	w3, w22
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	b	.L4
.L16:
	ldr	x3, .LC9
.L13:
	ldr	x2, .LC5
	mov	w0, 0
	ldr	x1, .LC7
	mov	w19, -1
	bl	dprint_vfmw
	b	.L4
.L17:
	ldr	x3, .LC11
	b	.L13
.L15:
	ldr	x3, .LC4
	b	.L13
	.size	VDMHAL_V5R6C1_OpenHAL, .-VDMHAL_V5R6C1_OpenHAL
	.align	3
.LC0:
	.xword	g_HwMem
	.align	3
.LC4:
	.xword	.LC3
	.align	3
.LC5:
	.xword	.LANCHOR0
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
.LC14:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC15:
	.xword	g_VdmExtParam
	.align	3
.LC17:
	.xword	.LC16
	.align	3
.LC19:
	.xword	.LC18
	.align	3
.LC21:
	.xword	.LC20
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_CloseHAL
	.type	VDMHAL_V5R6C1_CloseHAL, %function
VDMHAL_V5R6C1_CloseHAL:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V5R6C1_CloseHAL, .-VDMHAL_V5R6C1_CloseHAL
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_CalcFsSize
	.type	VDMHAL_V5R6C1_CalcFsSize, %function
VDMHAL_V5R6C1_CalcFsSize:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w22, w0
	mov	x0, x30
	mov	w25, w1
	mov	w26, w2
	mov	w23, w3
	mov	w24, w4
	mov	x21, x5
	bl	_mcount
	sub	w1, w25, #32
	mov	w0, 8160
	cmp	w1, w0
	bhi	.L21
	sub	w1, w26, #32
	mov	w8, w26
	cmp	w1, w0
	bhi	.L21
	add	w0, w25, 15
	add	w20, w26, 15
	asr	w0, w0, 4
	ldr	x1, .LC26
	mov	w2, 36
	asr	w20, w20, 4
	cmp	w0, 45
	mov	w19, 32
	ccmp	w20, w2, 0, le
	ldrb	w1, [x1]
	cset	w4, le
	mov	w2, 64
	cmp	w4, wzr
	lsl	w3, w0, 4
	csel	w19, w19, w2, eq
	cmp	w1, 1
	csel	w19, w19, w2, ne
	cmp	w24, 16
	beq	.L26
	cmp	w24, 17
	beq	.L52
	mul	w19, w0, w19
	sub	w0, w24, #17
	cmp	w0, 1
	mul	w19, w19, w20
	add	w19, w19, 143
	and	w19, w19, -128
	asr	w4, w19, 1
	bls	.L27
	ldr	x27, .LC27
	add	w3, w3, 255
	add	w8, w26, 31
	and	w28, w3, -256
	and	w8, w8, -32
	mov	w5, 0
	ldr	x7, [x27, w22, sxtw 3]
	mov	w6, 0
.L29:
	ldr	w0, [x7, 1240]
	cmp	w0, 1
	beq	.L53
	mov	w26, 0
	mov	w3, 0
	mov	w25, 0
.L30:
	cmp	w23, 1
	mul	w23, w8, w28
	beq	.L54
	mul	w2, w5, w6
	lsl	w1, w25, 2
	lsl	w0, w2, 2
	sub	w1, w1, w25
	sub	w2, w0, w2
	lsl	w0, w23, 2
	sub	w0, w0, w23
	lsr	w0, w0, 1
	add	w0, w0, w2, lsr 1
	add	w20, w0, w1, lsr 1
.L32:
	add	x2, x7, 503808
	ldr	w0, [x2, 1288]
	cbz	w0, .L55
.L33:
	add	x0, x7, 507904
	cmp	w24, 17
	str	w20, [x0, 760]
	str	w3, [x2, 3636]
	str	w26, [x2, 3640]
	str	w4, [x2, 3676]
	beq	.L34
	ldr	w0, [x2, 1296]
	mov	w1, 32
	cmp	w0, 32
	csel	w0, w0, w1, le
	str	w0, [x2, 3680]
	ldr	w0, [x7, 632]
	cmp	w0, 2
	beq	.L56
.L35:
	lsl	w3, w28, 4
	sub	w24, w24, #16
	add	w0, w25, w23
	str	w3, [x2, 3628]
	cmp	w24, 2
	lsr	w3, w3, 1
	str	w0, [x2, 3660]
	str	w3, [x2, 3632]
	bls	.L36
.L37:
	ldr	x0, [x27, w22, sxtw 3]
	mov	w4, 1024
	add	w1, w20, 1056
	add	x3, x0, 507904
	add	w2, w1, w19
	add	w5, w2, w4
	str	w19, [x3, 764]
	str	w4, [x3, 772]
	ldrsb	w0, [x0, 44]
	cmp	w0, 1
	csel	w2, w5, w2, eq
	cbz	x21, .L47
	str	w1, [x21, 4]
	mov	w0, 0
	ldr	x3, [x27, w22, sxtw 3]
	add	x3, x3, 503808
	ldr	w3, [x3, 1296]
	stp	w3, w19, [x21, 8]
	ldr	x3, [x27, w22, sxtw 3]
	add	x3, x3, 503808
	ldr	w3, [x3, 3680]
	stp	w3, w4, [x21, 16]
	str	w2, [x21]
	ldr	x2, [x27, w22, sxtw 3]
	add	x2, x2, 507904
	str	w1, [x2, 768]
.L48:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L34:
	lsl	w3, w28, 4
	mov	w0, 1
	str	w3, [x2, 3628]
	lsr	w3, w3, 1
	str	w0, [x2, 3680]
	add	w0, w25, w23
	str	w3, [x2, 3632]
	str	w0, [x2, 3660]
.L36:
	ldr	w0, [x7, 1548]
	cmp	w0, 8
	ble	.L37
	lsl	w0, w23, 2
	ldr	x1, .LC30
	sub	w23, w0, w23
	lsl	w0, w25, 2
	sub	w25, w0, w25
	mov	w0, 31
	mul	w5, w5, w6
	lsr	w25, w25, 1
	lsl	w6, w6, 5
	add	w23, w25, w23, lsr 1
	str	w6, [x2, 3644]
	str	w23, [x2, 3652]
	str	w5, [x2, 3656]
	bl	dprint_vfmw
	b	.L37
	.p2align 3
.L55:
	ldr	x1, .LC28
	add	x0, x2, 3624
	mov	x2, 1248
	stp	w4, w3, [x29, 96]
	ldr	x7, [x1, 96]
	mov	w1, 0
	stp	w6, w5, [x29, 104]
	blr	x7
	ldr	x7, [x27, w22, sxtw 3]
	ldp	w4, w3, [x29, 96]
	add	x2, x7, 503808
	ldp	w6, w5, [x29, 104]
	b	.L33
	.p2align 3
.L54:
	lsl	w1, w20, 6
	sub	w20, w1, w20, lsl 4
	mul	w20, w20, w28
	b	.L32
	.p2align 3
.L53:
	adds	w3, w25, 2047
	add	w25, w25, 4094
	csel	w25, w25, w3, mi
	add	w0, w26, 126
	and	w25, w25, -2048
	cmp	w25, wzr
	add	w3, w25, 127
	csel	w3, w3, w25, lt
	adds	w25, w26, 63
	csel	w25, w0, w25, mi
	asr	w3, w3, 7
	asr	w25, w25, 6
	lsl	w25, w25, 5
	mul	w25, w25, w3
	mov	w26, w25
	b	.L30
	.p2align 3
.L26:
	ldr	x27, .LC27
	mul	w19, w20, w3
	add	w3, w25, 255
	ldr	x7, [x27, w22, sxtw 3]
	add	w19, w19, 143
	and	w28, w3, -256
	and	w19, w19, -128
	ldr	w0, [x7, 1548]
	cmp	w0, 8
	ble	.L57
	add	w5, w26, 31
	lsr	w6, w28, 2
	and	w5, w5, -32
	asr	w4, w19, 1
	b	.L29
	.p2align 3
.L52:
	mov	w4, 64
	mov	w19, 128
	movk	w4, 0x12, lsl 16
	movk	w19, 0x24, lsl 16
.L27:
	ldr	x27, .LC27
	add	w3, w25, 255
	add	w8, w26, 63
	and	w28, w3, -256
	and	w8, w8, -64
	ldr	x7, [x27, w22, sxtw 3]
	ldr	w0, [x7, 1548]
	cmp	w0, 8
	ble	.L45
	lsr	w6, w28, 2
	mov	w5, w8
	b	.L29
	.p2align 3
.L57:
	asr	w4, w19, 1
	mov	w5, 0
	mov	w6, 0
	b	.L29
	.p2align 3
.L56:
	ldr	w0, [x2, 1300]
	str	w0, [x2, 3680]
	b	.L35
	.p2align 3
.L47:
	mov	w0, 0
	b	.L48
	.p2align 3
.L45:
	mov	w5, 0
	mov	w6, 0
	b	.L29
	.p2align 3
.L21:
	ldr	x2, .LC24
	mov	w0, 0
	ldr	x3, .LC23
	ldr	x1, .LC25
	add	x2, x2, 24
	bl	dprint_vfmw
	mov	w0, -1
	b	.L48
	.size	VDMHAL_V5R6C1_CalcFsSize, .-VDMHAL_V5R6C1_CalcFsSize
	.align	3
.LC23:
	.xword	.LC22
	.align	3
.LC24:
	.xword	.LANCHOR0
	.align	3
.LC25:
	.xword	.LC6
	.align	3
.LC26:
	.xword	g_not_direct_8x8_inference_flag
	.align	3
.LC27:
	.xword	s_pstVfmwChan
	.align	3
.LC28:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC30:
	.xword	.LC29
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_GetRpuSize
	.type	VDMHAL_V5R6C1_GetRpuSize, %function
VDMHAL_V5R6C1_GetRpuSize:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1024
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V5R6C1_GetRpuSize, .-VDMHAL_V5R6C1_GetRpuSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_CalcFsNum
	.type	VDMHAL_V5R6C1_CalcFsNum, %function
VDMHAL_V5R6C1_CalcFsNum:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x19, x3
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	cbz	x19, .L64
	cmp	w21, 17
	ldr	x2, .LC34
	beq	.L65
	ldr	x3, [x2, w20, sxtw 3]
	mov	w4, 32
	add	x1, x3, 503808
	ldr	w0, [x1, 1296]
	cmp	w0, w4
	csel	w0, w0, w4, le
	str	w0, [x1, 3680]
	ldr	w0, [x3, 632]
	cmp	w0, 2
	beq	.L66
.L63:
	ldr	x1, [x2, w20, sxtw 3]
	mov	w0, 0
	add	x1, x1, 503808
	ldr	w1, [x1, 1296]
	str	w1, [x19, 8]
	ldr	x1, [x2, w20, sxtw 3]
	add	x1, x1, 503808
	ldr	w1, [x1, 3680]
	str	w1, [x19, 16]
.L61:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L65:
	ldr	x0, [x2, w20, sxtw 3]
	mov	w1, 1
	add	x0, x0, 503808
	str	w1, [x0, 3680]
	b	.L63
	.p2align 3
.L66:
	ldr	w0, [x1, 1300]
	str	w0, [x1, 3680]
	b	.L63
.L64:
	ldr	x2, .LC31
	mov	w0, 1
	ldr	x1, .LC33
	add	x2, x2, 56
	bl	dprint_vfmw
	mov	w0, -1
	b	.L61
	.size	VDMHAL_V5R6C1_CalcFsNum, .-VDMHAL_V5R6C1_CalcFsNum
	.align	3
.LC31:
	.xword	.LANCHOR0
	.align	3
.LC33:
	.xword	.LC32
	.align	3
.LC34:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_DynamicAllocFrame
	.type	VDMHAL_V5R6C1_DynamicAllocFrame, %function
VDMHAL_V5R6C1_DynamicAllocFrame:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	w23, w1
	mov	w22, w2
	mov	x20, x3
	bl	_mcount
	ldr	x21, .LC35
	mov	w0, w19
	ldr	x1, [x21, w19, sxtw 3]
	add	x1, x1, 503808
	add	x1, x1, 1320
	bl	DelAllFrameMemRecord
	cbnz	w0, .L87
.L68:
	ldr	x1, [x21, w19, sxtw 3]
	mov	w2, 255
	add	x1, x1, 503808
	add	x0, x1, 1320
	add	x1, x1, 3624
	.p2align 2
.L69:
	str	w2, [x0], 72
	cmp	x1, x0
	bne	.L69
	mov	w0, 1088
	cmp	w23, 1920
	ccmp	w22, w0, 0, le
	ble	.L70
	ldr	x0, [x21, w19, sxtw 3]
	ldr	w1, [x20, 8]
.L71:
	add	x2, x0, 503808
	ldr	w3, [x0, 1496]
	mov	w0, w19
	add	w1, w3, w1
	str	w1, [x2, 1300]
	bl	VCTRL_GetVidStd
	ldr	x1, [x21, w19, sxtw 3]
	ldr	w2, [x1, 632]
	cmp	w2, 2
	ccmp	w0, 17, 4, eq
	beq	.L74
	add	x1, x1, 503808
	ldr	w0, [x1, 1300]
	str	w0, [x20, 16]
	ldr	x1, [x21, w19, sxtw 3]
.L74:
	add	x0, x1, 507904
	add	x1, x1, 475136
	mov	w4, 1
	mov	w3, w22
	mov	w2, w23
	str	wzr, [x0, 800]
	str	w4, [x1, 2200]
	str	w4, [x0, 1340]
	mov	w0, 31
	ldr	x1, .LC39
	ldr	w4, [x20, 8]
	ldr	w5, [x20, 16]
	bl	dprint_vfmw
	ldr	x0, .LC40
	ldr	x4, [x0]
	cbz	x4, .L75
	ldp	w1, w2, [x20, 12]
	ldp	w3, w5, [x20, 4]
	ldr	w0, [x20, 20]
	stp	w2, w1, [x29, 72]
	stp	w5, w3, [x29, 64]
	stp	w0, w23, [x29, 80]
	str	w22, [x29, 88]
	mov	w3, 28
	add	x2, x29, 64
	mov	w1, 121
	mov	w0, w19
	blr	x4
.L75:
	ldr	x3, .LC41
	mov	x2, 528
	ldr	x0, [x21, w19, sxtw 3]
	mov	w1, 0
	ldr	x3, [x3, 96]
	add	x0, x0, 507904
	add	x0, x0, 808
	blr	x3
	ldr	x1, [x21, w19, sxtw 3]
	mov	w0, w19
	add	x1, x1, 507904
	str	wzr, [x1, 1336]
	bl	FSP_ClearContextAll
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L70:
	ldr	x0, [x21, w19, sxtw 3]
	ldr	w1, [x0, 36]
	cmp	w1, 24
	beq	.L86
	add	x1, x0, 507904
	ldr	w1, [x1, 1396]
	cbnz	w1, .L86
	ldr	w1, [x20, 8]
	add	w1, w1, 4
	str	w1, [x20, 8]
	ldr	x0, [x21, w19, sxtw 3]
	b	.L71
.L86:
	ldr	w1, [x20, 8]
	b	.L71
.L87:
	ldr	x1, .LC37
	mov	w0, 0
	bl	dprint_vfmw
	b	.L68
	.size	VDMHAL_V5R6C1_DynamicAllocFrame, .-VDMHAL_V5R6C1_DynamicAllocFrame
	.align	3
.LC35:
	.xword	s_pstVfmwChan
	.align	3
.LC37:
	.xword	.LC36
	.align	3
.LC39:
	.xword	.LC38
	.align	3
.LC40:
	.xword	g_event_report
	.align	3
.LC41:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_DynamicAllocFrame_Only
	.type	VDMHAL_V5R6C1_DynamicAllocFrame_Only, %function
VDMHAL_V5R6C1_DynamicAllocFrame_Only:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x3
	mov	w22, w1
	mov	w21, w2
	bl	_mcount
	ldr	x4, .LC42
	mov	w3, w21
	ldr	w5, [x19, 8]
	mov	w2, w22
	ldr	x1, .LC44
	mov	w0, 31
	ldr	x4, [x4, w20, sxtw 3]
	add	x4, x4, 503808
	str	w5, [x4, 1300]
	ldr	w4, [x19, 8]
	ldr	w5, [x19, 16]
	bl	dprint_vfmw
	ldr	x0, .LC45
	ldr	x4, [x0]
	cbz	x4, .L88
	ldp	w1, w2, [x19, 12]
	ldp	w3, w5, [x19, 4]
	ldr	w0, [x19, 20]
	stp	w2, w1, [x29, 56]
	stp	w5, w3, [x29, 48]
	stp	w0, w22, [x29, 64]
	str	w21, [x29, 72]
	mov	w3, 28
	add	x2, x29, 48
	mov	w1, 122
	mov	w0, w20
	blr	x4
.L88:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.size	VDMHAL_V5R6C1_DynamicAllocFrame_Only, .-VDMHAL_V5R6C1_DynamicAllocFrame_Only
	.align	3
.LC42:
	.xword	s_pstVfmwChan
	.align	3
.LC44:
	.xword	.LC43
	.align	3
.LC45:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_ArrangeMem_Normal
	.type	VDMHAL_V5R6C1_ArrangeMem_Normal, %function
VDMHAL_V5R6C1_ArrangeMem_Normal:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	w19, w0
	mov	x0, x30
	mov	w22, w1
	mov	w23, w2
	mov	w24, w3
	mov	w25, w4
	mov	w27, w5
	mov	x21, x6
	bl	_mcount
	str	xzr, [x29, 120]
	add	x0, x29, 104
	cmp	w22, 20
	stp	xzr, xzr, [x0]
	bhi	.L129
	ldr	x20, .LC50
	ldr	x0, [x20, w19, sxtw 3]
	add	x1, x0, 503808
	ldr	w26, [x1, 1292]
	ldr	w1, [x0, 100]
	cmp	w1, 2
	beq	.L130
	and	w1, w22, -17
	cmp	w1, wzr
	ccmp	w22, 18, 4, ne
	beq	.L131
.L98:
	cmp	w22, 17
	cset	w2, eq
.L99:
	ldr	w3, [x0, 1244]
	ldr	w4, [x0, 1248]
	ldr	w5, [x0, 1252]
	ldr	x1, .LC52
	str	w2, [x0, 1240]
	mov	w0, 1
	bl	dprint_vfmw
.L97:
	mov	w2, w25
	add	x3, x29, 104
	mov	w1, w22
	mov	w0, w19
	bl	VDMHAL_V5R6C1_CalcFsNum
	mov	w25, w0
	add	x5, x29, 104
	mov	w4, w22
	mov	w3, w27
	mov	w2, w24
	mov	w1, w23
	mov	w0, w19
	bl	VDMHAL_V5R6C1_CalcFsSize
	orr	w0, w25, w0
	cbnz	w0, .L132
	ldr	x27, [x20, w19, sxtw 3]
	ldr	w22, [x29, 104]
	cmp	w26, w22
	add	x26, x27, 503808
	ldr	w25, [x26, 1296]
	ldr	w5, [x26, 1312]
	beq	.L133
.L102:
	ldr	x2, .LC48
	mov	w3, w22
	ldr	x1, .LC56
	mov	w4, w25
	add	x2, x2, 112
	mov	w0, 31
	bl	dprint_vfmw
	ldr	x0, [x20, w19, sxtw 3]
	add	x3, x29, 104
	mov	w2, w24
	add	x0, x0, 503808
	ldr	w1, [x0, 1288]
	str	w22, [x0, 1292]
	cbz	w1, .L134
	mov	w1, w23
	mov	w0, w19
	bl	VDMHAL_V5R6C1_DynamicAllocFrame_Only
.L105:
	ldr	x4, [x20, w19, sxtw 3]
	mov	w3, w25
	ldr	x1, .LC58
	mov	w2, w22
	add	x4, x4, 503808
	mov	w0, 31
	ldr	w4, [x4, 1312]
	bl	dprint_vfmw
	ldr	x19, [x20, w19, sxtw 3]
	ldr	x0, .LC59
	add	x19, x19, 507904
	ldr	x0, [x0]
	blr	x0
	str	w0, [x19, 776]
	mov	w1, 2
.L95:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	mov	w0, w1
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L134:
	mov	w1, w23
	mov	w0, w19
	bl	VDMHAL_V5R6C1_DynamicAllocFrame
	b	.L105
	.p2align 3
.L131:
	mov	w1, 2159
	cmp	w23, 3839
	ccmp	w24, w1, 0, le
	mov	w2, 1
	cset	w1, gt
	cbnz	w1, .L99
	b	.L98
	.p2align 3
.L133:
	cmp	w5, 1
	beq	.L102
	ldr	w0, [x26, 1288]
	cmp	w0, 1
	beq	.L102
	cbz	x21, .L135
	add	x1, x27, 507904
	add	x22, x26, 3624
	mov	x0, x27
	ldr	w23, [x1, 760]
	cbz	w25, .L136
.L107:
	add	x0, x0, 503808
	ldr	w2, [x0, 1300]
	cmp	w2, 30
	bgt	.L137
.L108:
	ldr	x24, .LC59
	add	x26, x26, 3624
	mov	w0, 8
	str	w2, [x26, 48]
	ldr	x1, [x24, 24]
	blr	x1
	ldr	x7, [x20, w19, sxtw 3]
	add	x9, x7, 507904
	ldr	w0, [x9, 800]
	cbz	w0, .L113
	ldp	w10, w6, [x26, 56]
	mov	x1, x26
	mov	w5, 0
	mov	w8, 1
	.p2align 2
.L112:
	uxtw	x0, w5
	add	w5, w5, 1
	lsl	x2, x0, 6
	add	x2, x2, x0, lsl 3
	add	x2, x7, x2
	add	x11, x2, 503808
	uxtw	x2, w6
	lsl	x3, x2, 2
	add	x4, x2, 20
	sub	x3, x3, x2
	add	w6, w6, 1
	ldr	w2, [x11, 1352]
	add	x3, x1, x3, lsl 2
	ldr	w12, [x11, 1332]
	add	w2, w2, 1023
	and	w2, w2, -1024
	strb	w8, [x3, 472]
	str	w2, [x3, 464]
	add	w2, w23, w2
	str	w12, [x3, 468]
	str	w2, [x1, x4, lsl 2]
	str	w6, [x1, 60]
	ldr	w2, [x11, 1324]
	cmp	w2, 255
	beq	.L110
	ldr	w2, [x1, 68]
	ldr	w4, [x11, 1368]
	add	w3, w2, 1
	uxtw	x2, w2
	lsl	x0, x2, 2
	sub	x0, x0, x2
	add	x0, x1, x0, lsl 2
	str	w4, [x0, 848]
	str	w3, [x1, 68]
.L110:
	ldr	w0, [x1, 64]
	cmp	w0, w10
	bcs	.L111
	ldr	w3, [x11, 1328]
	add	x2, x27, x0, uxtw 3
	add	x2, x2, 503808
	add	w0, w0, 1
	cmp	w3, 255
	beq	.L111
	ldr	w3, [x11, 1384]
	str	w3, [x2, 3832]
	strb	w8, [x2, 3836]
	str	w0, [x1, 64]
.L111:
	ldr	w0, [x9, 800]
	cmp	w5, w0
	bcc	.L112
.L113:
	ldr	x3, [x24, 104]
	mov	x2, 1232
	mov	x1, x22
	mov	x0, x21
	blr	x3
	ldr	x1, [x20, w19, sxtw 3]
	mov	w3, 1
	ldr	x2, [x24, 32]
	mov	w0, 8
	add	x1, x1, 507904
	str	w3, [x1, 804]
	blr	x2
	mov	w1, 0
	b	.L95
	.p2align 3
.L130:
	add	x2, x0, 1024
	mov	w1, -1
	stp	wzr, wzr, [x2, 216]
	stp	w1, w1, [x2, 224]
	b	.L97
	.p2align 3
.L137:
	ldr	x1, .LC65
	mov	w0, 31
	bl	dprint_vfmw
	ldr	x0, [x20, w19, sxtw 3]
	mov	w1, 30
	mov	w2, w1
	add	x0, x0, 503808
	str	w1, [x0, 1300]
	b	.L108
	.p2align 3
.L136:
	ldr	x1, .LC63
	mov	w0, 31
	bl	dprint_vfmw
	ldr	x0, [x20, w19, sxtw 3]
	b	.L107
	.p2align 3
.L129:
	ldr	x2, .LC48
	mov	w0, 0
	ldr	x1, .LC49
	ldr	x3, .LC47
	add	x2, x2, 80
	bl	dprint_vfmw
	mov	w1, -1
	b	.L95
	.p2align 3
.L132:
	ldr	x1, .LC54
	mov	w0, 31
	bl	dprint_vfmw
	mov	w1, -1
	b	.L95
.L135:
	ldr	x2, .LC48
	mov	w0, 0
	ldr	x1, .LC49
	ldr	x3, .LC61
	add	x2, x2, 144
	bl	dprint_vfmw
	mov	w1, -1
	b	.L95
	.size	VDMHAL_V5R6C1_ArrangeMem_Normal, .-VDMHAL_V5R6C1_ArrangeMem_Normal
	.align	3
.LC47:
	.xword	.LC46
	.align	3
.LC48:
	.xword	.LANCHOR0
	.align	3
.LC49:
	.xword	.LC6
	.align	3
.LC50:
	.xword	s_pstVfmwChan
	.align	3
.LC52:
	.xword	.LC51
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
.LC59:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC61:
	.xword	.LC60
	.align	3
.LC63:
	.xword	.LC62
	.align	3
.LC65:
	.xword	.LC64
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_ArrangeMem_Specific
	.type	VDMHAL_V5R6C1_ArrangeMem_Specific, %function
VDMHAL_V5R6C1_ArrangeMem_Specific:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w25, w0
	mov	w22, w2
	mov	x0, x30
	mov	w24, w1
	mov	w19, w3
	mov	w21, w4
	mov	w28, w5
	mov	w20, w6
	mov	w26, w7
	ldr	x23, [x29, 144]
	bl	_mcount
	cbz	w22, .L217
	sub	w1, w21, #32
	mov	w0, 8160
	cmp	w1, w0
	bhi	.L141
	sub	w1, w28, #32
	cmp	w1, w0
	bhi	.L141
	cbz	x23, .L218
	ldr	x0, .LC73
	cmp	w20, 20
	mov	x2, 1232
	mov	w1, 0
	mov	w6, 20
	ldr	x3, [x0, 96]
	mov	x0, x23
	csel	w27, w20, w6, le
	mov	w20, 32
	blr	x3
	ldr	x1, .LC74
	add	w0, w21, 15
	asr	w0, w0, 4
	add	w3, w28, 15
	cmp	w0, 45
	asr	w3, w3, 4
	ldrb	w2, [x1]
	mov	w1, 36
	ccmp	w3, w1, 0, le
	mov	w1, 64
	cset	w4, le
	cmp	w4, wzr
	csel	w20, w20, w1, eq
	cmp	w2, 1
	csel	w20, w20, w1, ne
	cmp	w24, 16
	lsl	w1, w0, 4
	beq	.L219
	cmp	w24, 17
	beq	.L185
	mul	w20, w0, w20
	mul	w20, w20, w3
	add	w20, w20, 143
	and	w20, w20, -128
.L149:
	mul	w4, w27, w20
	cmp	w19, w4
	ble	.L147
	sub	w4, w19, w4
	sub	w0, w24, #17
	add	w19, w22, 1023
	cmp	w0, 1
	and	w19, w19, -1024
	asr	w0, w20, 1
	stp	w0, w27, [x23, 52]
	sub	w6, w19, w22
	sub	w4, w4, w6
	bls	.L220
	add	w1, w1, 255
	add	w2, w28, 31
	and	w1, w1, -256
	and	w27, w2, -32
	lsl	w0, w1, 4
	str	w0, [x23, 4]
	asr	w0, w0, 1
	str	w0, [x23, 8]
	tbnz	w25, #31, .L213
	ldr	x9, .LC77
	mov	w5, 0
	mov	w7, 0
	ldr	x0, [x9, w25, sxtw 3]
	ldr	w0, [x0, 1240]
	cmp	w0, 1
	beq	.L221
.L190:
	mov	w9, 0
	mov	w0, 0
	mov	w28, 0
.L152:
	stp	w0, w9, [x23, 12]
	ldr	w0, [x29, 128]
	cmp	w0, 1
	beq	.L222
	mul	w3, w27, w1
	mul	w9, w7, w5
	lsl	w0, w3, 2
	lsl	w21, w28, 2
	sub	w3, w0, w3
	lsl	w0, w9, 2
	sub	w0, w0, w9
	sub	w21, w21, w28
	asr	w0, w0, 1
	add	w0, w0, w3, asr 1
	add	w21, w0, w21, lsr 1
.L154:
	ldr	w0, [x29, 136]
	tbnz	w0, #31, .L155
	stp	w4, w6, [x29, 104]
	stp	w1, w5, [x29, 112]
	str	w7, [x29, 120]
	bl	VCTRL_GetChanWidth
	mov	w25, w0
	ldr	w0, [x29, 136]
	bl	VCTRL_GetChanHeight
	cmn	w25, #1
	ldr	w7, [x29, 120]
	ccmn	w0, #1, 4, ne
	ldp	w4, w6, [x29, 104]
	ldp	w1, w5, [x29, 112]
	beq	.L223
	ldr	w2, [x29, 128]
	add	w3, w25, 15
	and	w8, w3, -16
	add	w0, w0, 15
	cmp	w2, 1
	add	w3, w8, 255
	and	w0, w0, -16
	and	w10, w3, -256
	beq	.L224
	ldr	x3, .LC77
	ldr	w2, [x29, 136]
	ldr	x3, [x3, w2, sxtw 3]
	ldr	w3, [x3, 1240]
	cmp	w3, 1
	beq	.L159
	add	w3, w0, 126
	adds	w0, w0, 63
	csel	w3, w3, w0, mi
	mov	w9, 0
	asr	w3, w3, 6
.L160:
	mul	w3, w10, w3
	mul	w10, w7, w5
	lsl	w8, w3, 2
	sub	w3, w8, w3
	lsl	w0, w10, 2
	lsl	w3, w3, 6
	sub	w0, w0, w10
	asr	w0, w0, 1
	add	w0, w0, w3, asr 1
	add	w0, w0, w9
.L158:
	cmp	w21, w0
	ldr	w25, [x29, 136]
	bgt	.L225
.L155:
	mul	w1, w27, w1
	sub	w0, w24, #16
	cmp	w0, 1
	add	w0, w1, w28
	str	w0, [x23, 36]
	bls	.L226
	cbz	w26, .L164
	cmp	w24, wzr
	ccmp	w24, 3, 4, ne
	beq	.L162
	sdiv	w4, w4, w21
	cmp	w26, 32
	mov	w0, 32
	csel	w26, w26, w0, le
	cmp	w4, w26
	csel	w4, w4, w26, le
	str	w4, [x23, 48]
.L165:
	cbz	w4, .L163
	sub	w5, w4, #1
	mov	x2, 476
	mov	w1, 12
	ldr	w3, [x23, 60]
	add	x0, x23, 464
	umaddl	x1, w5, w1, x2
	uxtw	x2, w5
	add	x1, x23, x1
	.p2align 2
.L168:
	str	w19, [x0], 12
	add	w19, w19, w21
	cmp	x0, x1
	bne	.L168
	madd	w21, w21, w4, w6
	add	x2, x2, 21
	add	w3, w4, w3
	add	w1, w21, w22
	add	x0, x23, 80
	add	x2, x23, x2, lsl 2
	str	w3, [x23, 60]
	.p2align 2
.L170:
	str	w1, [x0], 4
	add	w1, w1, 32
	cmp	x2, x0
	bne	.L170
	ldr	w3, [x23, 56]
	add	w21, w21, w4, lsl 5
	add	w22, w21, w22
	cbz	w3, .L175
	sub	w2, w3, #1
	ldr	w6, [x23, 64]
	add	x2, x2, 27
	add	x1, x23, 208
	mov	w0, w22
	add	x2, x23, x2, lsl 3
	.p2align 2
.L174:
	str	w0, [x1], 8
	add	w0, w0, w20
	cmp	x1, x2
	bne	.L174
	add	w0, w3, w6
	str	w0, [x23, 64]
.L175:
	madd	w20, w3, w20, w21
	str	w20, [x23]
	tbnz	w25, #31, .L173
	ldr	x0, .LC77
	ldr	x0, [x0, w25, sxtw 3]
	cbz	x0, .L173
	add	w0, w20, w22
	cbz	w4, .L173
	mov	w3, 12
	mov	x2, 860
	add	x1, x23, 848
	umaddl	x2, w5, w3, x2
	add	x2, x23, x2
	.p2align 2
.L176:
	str	w0, [x1], 12
	add	w0, w0, 1024
	cmp	x2, x1
	bne	.L176
.L173:
	add	w20, w20, w4, lsl 10
	mov	w0, 0
	str	w20, [x23]
.L208:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L226:
	lsl	w0, w1, 2
	sub	w1, w0, w1
	lsl	w0, w28, 2
	sub	w0, w0, w28
	lsr	w28, w28, 1
	lsr	w0, w0, 1
	madd	w7, w7, w5, w28
	add	w0, w0, w1, asr 1
	lsl	w5, w5, 4
	stp	w0, w7, [x23, 28]
	str	w5, [x23, 20]
	cbnz	w26, .L162
.L164:
	str	wzr, [x23, 48]
.L163:
	ldr	x2, .LC68
	ldr	x3, .LC83
.L214:
	ldr	x1, .LC69
	add	x2, x2, 184
	mov	w0, 0
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
.L162:
	cmp	w26, 32
	mov	w0, 32
	sdiv	w4, w4, w21
	csel	w26, w26, w0, le
	cmp	w26, w4
	csel	w4, w26, w4, le
	str	w4, [x23, 48]
	b	.L165
	.p2align 3
.L219:
	mul	w20, w3, w1
	add	w20, w20, 143
	and	w20, w20, -128
	mul	w4, w27, w20
	cmp	w19, w4
	ble	.L147
	sub	w4, w19, w4
	add	w19, w22, 1023
	and	w19, w19, -1024
	asr	w0, w20, 1
	stp	w0, w27, [x23, 52]
	sub	w6, w19, w22
	add	w1, w21, 255
	sub	w4, w4, w6
	and	w1, w1, -256
	mov	w27, w28
	tbnz	w25, #31, .L151
	ldr	x9, .LC77
	stp	w4, w6, [x29, 104]
	stp	w1, w3, [x29, 112]
	ldr	x0, [x9, w25, sxtw 3]
	str	x9, [x29, 120]
	add	x0, x0, 507904
	add	x0, x0, 1408
	bl	IsMain10Profile
	ldp	w4, w6, [x29, 104]
	ldp	w1, w3, [x29, 112]
	ldr	x9, [x29, 120]
	cbz	w0, .L186
	cmp	w1, wzr
	add	w5, w1, 3
	csel	w5, w5, w1, lt
	add	w7, w28, 31
	asr	w5, w5, 2
	and	w7, w7, -32
	mov	w27, w28
.L150:
	lsl	w0, w1, 4
	str	w0, [x23, 4]
	asr	w0, w0, 1
	str	w0, [x23, 8]
	ldr	x0, [x9, w25, sxtw 3]
	ldr	w0, [x0, 1240]
	cmp	w0, 1
	bne	.L190
.L221:
	cmp	w24, 17
	mov	w0, 1920
	ccmp	w21, w0, 0, ne
	ble	.L190
	adds	w0, w21, 2047
	add	w21, w21, 4094
	csel	w0, w21, w0, mi
	and	w9, w0, -2048
	cmp	w9, wzr
	add	w0, w9, 127
	csel	w0, w0, w9, lt
	add	w9, w28, 126
	adds	w28, w28, 63
	asr	w0, w0, 7
	csel	w28, w9, w28, mi
	asr	w28, w28, 6
	lsl	w28, w28, 5
	mul	w28, w28, w0
	mov	w9, w28
	b	.L152
	.p2align 3
.L222:
	lsl	w0, w3, 4
	mul	w0, w0, w1
	lsl	w21, w0, 2
	sub	w21, w21, w0
	b	.L154
	.p2align 3
.L151:
	lsl	w0, w1, 4
	str	w0, [x23, 4]
	asr	w0, w0, 1
	str	w0, [x23, 8]
.L213:
	mov	w9, 0
	mov	w0, 0
	mov	w5, 0
	mov	w7, 0
	mov	w28, 0
	b	.L152
	.p2align 3
.L185:
	mov	w20, 128
	movk	w20, 0x24, lsl 16
	b	.L149
	.p2align 3
.L220:
	add	w1, w21, 255
	add	w2, w28, 63
	and	w1, w1, -256
	and	w27, w2, -64
	tbnz	w25, #31, .L151
	ldr	x9, .LC77
	ldr	x0, [x9, w25, sxtw 3]
	ldr	w0, [x0, 1548]
	cmp	w0, 8
	ble	.L187
	cmp	w1, wzr
	add	w5, w1, 3
	csel	w5, w5, w1, lt
	mov	w7, w27
	asr	w5, w5, 2
	b	.L150
	.p2align 3
.L224:
	mul	w0, w0, w10
	lsl	w3, w0, 2
	sub	w0, w3, w0
	b	.L158
	.p2align 3
.L159:
	adds	w9, w0, 63
	add	w3, w0, 126
	csel	w3, w3, w9, mi
	adds	w0, w8, 2047
	add	w8, w8, 4094
	asr	w3, w3, 6
	csel	w8, w8, w0, mi
	and	w8, w8, -2048
	add	w9, w8, 127
	cmp	w8, wzr
	csel	w8, w9, w8, lt
	lsl	w9, w3, 2
	sub	w9, w9, w3
	asr	w8, w8, 7
	lsl	w9, w9, 5
	mul	w9, w8, w9
	lsr	w9, w9, 1
	b	.L160
.L186:
	mov	w27, w28
	mov	w7, 0
	mov	w5, 0
	b	.L150
.L187:
	mov	w7, 0
	mov	w5, 0
	b	.L150
.L141:
	ldr	x2, .LC68
	ldr	x3, .LC70
	b	.L214
.L147:
	ldr	x2, .LC68
	ldr	x3, .LC76
	b	.L214
.L217:
	ldr	x2, .LC68
	ldr	x3, .LC67
	b	.L214
.L225:
	ldr	x2, .LC68
	ldr	x3, .LC81
	b	.L214
.L223:
	ldr	x1, .LC79
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L208
.L218:
	ldr	x2, .LC68
	ldr	x3, .LC72
	b	.L214
	.size	VDMHAL_V5R6C1_ArrangeMem_Specific, .-VDMHAL_V5R6C1_ArrangeMem_Specific
	.align	3
.LC67:
	.xword	.LC66
	.align	3
.LC68:
	.xword	.LANCHOR0
	.align	3
.LC69:
	.xword	.LC6
	.align	3
.LC70:
	.xword	.LC22
	.align	3
.LC72:
	.xword	.LC71
	.align	3
.LC73:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC74:
	.xword	g_not_direct_8x8_inference_flag
	.align	3
.LC76:
	.xword	.LC75
	.align	3
.LC77:
	.xword	s_pstVfmwChan
	.align	3
.LC79:
	.xword	.LC78
	.align	3
.LC81:
	.xword	.LC80
	.align	3
.LC83:
	.xword	.LC82
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_ArrangeMem
	.type	VDMHAL_V5R6C1_ArrangeMem, %function
VDMHAL_V5R6C1_ArrangeMem:
	sub	sp, sp, #112
	stp	x29, x30, [sp, 32]
	add	x29, sp, 32
	stp	x19, x20, [sp, 48]
	stp	x21, x22, [sp, 64]
	stp	x23, x24, [sp, 80]
	stp	x25, x26, [sp, 96]
	mov	w24, w0
	mov	x0, x30
	mov	w19, w7
	mov	w25, w1
	mov	w20, w2
	mov	w21, w3
	mov	w22, w4
	mov	w26, w5
	mov	w23, w6
	bl	_mcount
	cmn	w19, #2
	beq	.L231
	tbnz	w19, #31, .L232
	mov	w0, w19
	bl	VCTRL_GetVidStd
	mov	w1, w0
	ldr	x0, .LC84
	ldr	x0, [x0, w19, sxtw 3]
	ldr	w0, [x0, 1488]
	cmp	w0, 1
	beq	.L234
.L229:
	ldr	x0, [x29, 80]
	mov	w7, w26
	str	x0, [sp, 16]
	mov	w6, w22
	mov	w5, w21
	mov	w4, w20
	mov	w3, w25
	mov	w2, w24
	str	w23, [sp]
	mov	w0, w19
	str	w19, [sp, 8]
	bl	VDMHAL_V5R6C1_ArrangeMem_Specific
.L233:
	add	sp, x29, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L232:
	mov	w1, 21
	b	.L229
	.p2align 3
.L231:
	mov	w1, 16
	b	.L229
	.p2align 3
.L234:
	ldr	x6, [x29, 80]
	mov	w5, w23
	mov	w4, w22
	mov	w3, w21
	mov	w2, w20
	mov	w0, w19
	bl	VDMHAL_V5R6C1_ArrangeMem_Normal
	b	.L233
	.size	VDMHAL_V5R6C1_ArrangeMem, .-VDMHAL_V5R6C1_ArrangeMem
	.align	3
.LC84:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_ResetVdm
	.type	VDMHAL_V5R6C1_ResetVdm, %function
VDMHAL_V5R6C1_ResetVdm:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w21, w0
	mov	x0, x30
	bl	_mcount
	cmp	w21, wzr
	ble	.L236
	ldr	x2, .LC85
	mov	w4, 0
	ldr	x1, .LC87
	mov	w3, w21
	add	x2, x2, 224
	mov	w0, 0
	bl	dprint_vfmw
.L235:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L236:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L251
	sxtw	x23, w21
	ldr	x20, .LC90
	lsl	x0, x23, 6
	sub	x0, x0, x23
	lsl	x0, x0, 2
	sub	x26, x0, x23
	add	x26, x0, x26, lsl 2
	ldr	x0, [x20, x26]
	add	x1, x0, 61440
	ldr	w24, [x0, 36]
	ldr	w1, [x1, 2052]
	str	w1, [x29, 92]
	and	w1, w1, 3
	cbz	w1, .L235
	ldr	x25, .LC91
	mov	w19, 0
	mov	x22, x26
	ldr	x0, [x25, 224]
	blr	x0
	ldr	x0, [x20, x26]
	add	x0, x0, 61440
	ldr	w1, [x0, 2060]
	str	w1, [x29, 92]
	orr	w1, w1, 2
	strb	w1, [x29, 92]
	ldr	w1, [x29, 92]
	str	w1, [x0, 2060]
	b	.L241
	.p2align 3
.L252:
	add	w19, w19, 1
	cmp	w19, 1000
	beq	.L242
.L241:
	ldr	x1, [x25, 232]
	mov	x0, 30
	blr	x1
	ldr	x0, [x20, x22]
	add	x0, x0, 61440
	ldr	w0, [x0, 2064]
	str	w0, [x29, 92]
	tbz	x0, 1, .L252
	cmp	w19, 999
	bgt	.L242
	ldr	x2, .LC85
	mov	w3, w21
	ldr	x1, .LC95
	mov	w0, 0
	add	x2, x2, 224
	bl	dprint_vfmw
.L244:
	lsl	x0, x23, 6
	ldr	x2, [x25, 224]
	sub	x0, x0, x23
	lsl	x0, x0, 2
	sub	x23, x0, x23
	add	x23, x0, x23, lsl 2
	ldr	x0, [x20, x23]
	add	x0, x0, 61440
	ldr	w1, [x0, 2060]
	str	w1, [x29, 92]
	and	w1, w1, -3
	strb	w1, [x29, 92]
	ldr	w1, [x29, 92]
	str	w1, [x0, 2060]
	blr	x2
	ldr	x0, [x20, x23]
	str	w24, [x0, 36]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L242:
	ldr	x2, .LC85
	mov	w3, w21
	ldr	x1, .LC93
	mov	w0, 0
	add	x2, x2, 224
	bl	dprint_vfmw
	b	.L244
.L251:
	ldr	x1, .LC89
	mov	x2, 0
	bl	dprint_vfmw
	b	.L235
	.size	VDMHAL_V5R6C1_ResetVdm, .-VDMHAL_V5R6C1_ResetVdm
	.align	3
.LC85:
	.xword	.LANCHOR0
	.align	3
.LC87:
	.xword	.LC86
	.align	3
.LC89:
	.xword	.LC88
	.align	3
.LC90:
	.xword	g_HwMem
	.align	3
.LC91:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC93:
	.xword	.LC92
	.align	3
.LC95:
	.xword	.LC94
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_SetSmmuPageTableAddr
	.type	VDMHAL_V5R6C1_SetSmmuPageTableAddr, %function
VDMHAL_V5R6C1_SetSmmuPageTableAddr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC96
	ldr	x3, [x0, 376]
	cbz	x3, .L253
	add	x2, x29, 60
	add	x1, x29, 56
	add	x0, x29, 52
	blr	x3
	cbnz	w19, .L255
	ldr	x0, .LC97
	ldp	w3, w2, [x29, 52]
	ldr	w1, [x29, 60]
	ldr	x0, [x0]
	add	x0, x0, 61440
	str	w3, [x0, 524]
	str	w2, [x0, 772]
	str	w1, [x0, 776]
.L253:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L255:
	ldr	x20, .LC98
	mov	w3, w19
	ldr	x21, .LC100
	mov	w4, 1
	add	x20, x20, 248
	mov	w0, 32
	mov	x1, x21
	mov	x2, x20
	bl	dprint_vfmw
	mov	w3, w19
	mov	x2, x20
	mov	x1, x21
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	mov	w3, w19
	mov	x2, x20
	mov	x1, x21
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.size	VDMHAL_V5R6C1_SetSmmuPageTableAddr, .-VDMHAL_V5R6C1_SetSmmuPageTableAddr
	.align	3
.LC96:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC97:
	.xword	g_HwMem
	.align	3
.LC98:
	.xword	.LANCHOR0
	.align	3
.LC100:
	.xword	.LC99
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_EnableSmmu
	.type	VDMHAL_V5R6C1_EnableSmmu, %function
VDMHAL_V5R6C1_EnableSmmu:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC102
	mov	w1, 8
	movk	w1, 0x3, lsl 16
	ldr	x0, [x0]
	add	x0, x0, 61440
	str	w1, [x0]
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V5R6C1_EnableSmmu, .-VDMHAL_V5R6C1_EnableSmmu
	.align	3
.LC102:
	.xword	g_HwMem
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_GlbResetX
	.type	VDMHAL_V5R6C1_GlbResetX, %function
VDMHAL_V5R6C1_GlbResetX:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	sxtw	x19, w0
	mov	x0, x30
	bl	_mcount
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L279
	cmp	w19, wzr
	ble	.L280
	ldr	x22, .LC103
	mov	w4, 1
	ldr	x23, .LC108
	mov	w3, w19
	add	x21, x22, 288
	mov	w0, 32
	mov	x1, x23
	mov	x2, x21
	bl	dprint_vfmw
	ldrb	w20, [x29, 92]
	and	w20, w20, 3
	cmp	w20, 1
	beq	.L281
.L260:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L280:
	sxtw	x0, w19
	ldr	x21, .LC106
	lsl	x20, x0, 6
	sub	x20, x20, x0
	lsl	x20, x20, 2
	sub	x0, x20, x0
	add	x20, x20, x0, lsl 2
	ldr	x0, [x21, x20]
	add	x0, x0, 61440
	ldr	w0, [x0, 2052]
	str	w0, [x29, 92]
	and	w0, w0, 3
	cmp	w0, 1
	bne	.L260
	ldr	x24, .LC109
	ldr	x0, [x24, 224]
	blr	x0
	ldr	x22, .LC103
	ldr	x0, [x21, x20]
	add	x0, x0, 61440
	ldr	w1, [x0, 2060]
	str	w1, [x29, 92]
	orr	w1, w1, 1
	strb	w1, [x29, 92]
	ldr	w1, [x29, 92]
	str	w1, [x0, 2060]
	b	.L275
	.p2align 3
.L281:
	ldr	x24, .LC109
	ldr	x0, [x24, 224]
	blr	x0
	mov	w4, w20
	mov	w3, w19
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	ldrb	w5, [x29, 92]
	mov	w4, w20
	ldr	x1, .LC114
	mov	w3, w19
	orr	w5, w5, 1
	mov	x2, x21
	mov	w0, 32
	strb	w5, [x29, 92]
	bl	dprint_vfmw
.L275:
	sxtw	x23, w19
	ldr	x25, .LC108
	lsl	x21, x23, 6
	ldr	x26, .LC106
	sub	x21, x21, x23
	mov	w20, 0
	lsl	x21, x21, 2
	sub	x21, x21, x23
	b	.L270
	.p2align 3
.L267:
	bl	dprint_vfmw
	ldrb	w0, [x29, 92]
	tbnz	x0, 0, .L269
.L282:
	add	w20, w20, 1
	cmp	w20, 1000
	beq	.L271
.L270:
	ldr	x1, [x24, 232]
	mov	x0, 30
	blr	x1
	cmp	w19, wzr
	add	x0, x21, x21, lsl 2
	add	x5, x0, x23
	mov	w4, 1
	mov	w3, w19
	add	x2, x22, 288
	mov	x1, x25
	mov	w0, 32
	bgt	.L267
	ldr	x0, [x26, x5]
	add	x0, x0, 61440
	ldr	w0, [x0, 2064]
	str	w0, [x29, 92]
	ldrb	w0, [x29, 92]
	tbz	x0, 0, .L282
.L269:
	cmp	w20, 999
	bgt	.L271
	ldr	x1, .LC113
	mov	w3, w19
	add	x2, x22, 288
	mov	w0, 0
	bl	dprint_vfmw
.L273:
	cmp	w19, wzr
	ble	.L283
	add	x22, x22, 288
	ldr	x1, .LC108
	mov	w3, w19
	mov	x2, x22
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x1, .LC114
	mov	w3, w19
	mov	x2, x22
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L271:
	ldr	x1, .LC111
	mov	w3, w19
	add	x2, x22, 288
	mov	w0, 0
	bl	dprint_vfmw
	b	.L273
	.p2align 3
.L283:
	lsl	x0, x19, 6
	ldr	x1, .LC106
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x19, x0, x19
	add	x0, x0, x19, lsl 2
	ldr	x0, [x1, x0]
	add	x0, x0, 61440
	ldr	w1, [x0, 2060]
	str	w1, [x29, 92]
	and	w1, w1, -2
	strb	w1, [x29, 92]
	ldr	w1, [x29, 92]
	str	w1, [x0, 2060]
	b	.L260
	.p2align 3
.L279:
	ldr	x2, .LC103
	mov	w3, -121438208
	ldr	x1, .LC105
	add	x2, x2, 288
	bl	dprint_vfmw
	b	.L260
	.size	VDMHAL_V5R6C1_GlbResetX, .-VDMHAL_V5R6C1_GlbResetX
	.align	3
.LC103:
	.xword	.LANCHOR0
	.align	3
.LC105:
	.xword	.LC104
	.align	3
.LC106:
	.xword	g_HwMem
	.align	3
.LC108:
	.xword	.LC107
	.align	3
.LC109:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC111:
	.xword	.LC110
	.align	3
.LC113:
	.xword	.LC112
	.align	3
.LC114:
	.xword	.LC99
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_GlbReset
	.type	VDMHAL_V5R6C1_GlbReset, %function
VDMHAL_V5R6C1_GlbReset:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L287
	mov	w0, 0
	bl	VDMHAL_V5R6C1_GlbResetX
.L284:
	ldp	x29, x30, [sp], 16
	ret
.L287:
	ldr	x2, .LC116
	mov	w3, -121438208
	ldr	x1, .LC117
	add	x2, x2, 312
	bl	dprint_vfmw
	b	.L284
	.size	VDMHAL_V5R6C1_GlbReset, .-VDMHAL_V5R6C1_GlbReset
	.align	3
.LC116:
	.xword	.LANCHOR0
	.align	3
.LC117:
	.xword	.LC104
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_ClearIntState
	.type	VDMHAL_V5R6C1_ClearIntState, %function
VDMHAL_V5R6C1_ClearIntState:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	sxtw	x19, w0
	mov	x0, x30
	mov	x20, x19
	bl	_mcount
	ldr	x21, .LC119
	ldr	x0, .LC118
	add	x1, x21, x19, lsl 6
	ldrsw	x1, [x1, 8]
	ldr	x0, [x0, x1, lsl 3]
	cbz	x0, .L298
	ldr	w22, [x0, 1272]
.L289:
	cmp	w20, wzr
	bgt	.L300
	lsl	x0, x19, 6
	ldr	x23, .LC122
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x20, x0, x19
	add	x20, x0, x20, lsl 2
	ldr	x0, [x23, x20]
	cbz	x0, .L301
.L292:
	cmp	w22, 1
	bne	.L299
	add	x19, x21, x19, lsl 6
	ldr	w1, [x19, 44]
	cmp	w1, 1
	beq	.L299
	ldr	w2, [x0, 28]
	cmp	w1, 2
	beq	.L302
	cmp	w1, 3
	bne	.L288
	mov	w1, -15
	str	w1, [x0, 32]
	b	.L288
	.p2align 3
.L300:
	ldr	x2, .LC120
	mov	w4, 0
	ldr	x1, .LC121
	mov	w3, w20
	add	x2, x2, 336
	mov	w0, 0
	bl	dprint_vfmw
.L288:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L299:
	mov	w1, -1
	str	w1, [x0, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L298:
	mov	w22, 0
	b	.L289
	.p2align 3
.L301:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L293
	str	x0, [x23, x20]
	b	.L292
	.p2align 3
.L302:
	mov	w1, -12
	str	w1, [x0, 32]
	b	.L288
.L293:
	ldr	x1, .LC124
	mov	w0, 0
	bl	dprint_vfmw
	b	.L288
	.size	VDMHAL_V5R6C1_ClearIntState, .-VDMHAL_V5R6C1_ClearIntState
	.align	3
.LC118:
	.xword	s_pstVfmwChan
	.align	3
.LC119:
	.xword	g_VdmDrvParam
	.align	3
.LC120:
	.xword	.LANCHOR0
	.align	3
.LC121:
	.xword	.LC86
	.align	3
.LC122:
	.xword	g_HwMem
	.align	3
.LC124:
	.xword	.LC123
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_ClearMMUIntState
	.type	VDMHAL_V5R6C1_ClearMMUIntState, %function
VDMHAL_V5R6C1_ClearMMUIntState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	sxtw	x19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, wzr
	bgt	.L308
	lsl	x3, x19, 6
	ldr	x20, .LC127
	sub	x3, x3, x19
	lsl	x3, x3, 2
	sub	x19, x3, x19
	add	x19, x3, x19, lsl 2
	ldr	x0, [x20, x19]
	cbz	x0, .L309
.L306:
	add	x0, x0, 61440
	mov	w1, 7
	str	w1, [x0, 44]
.L303:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L308:
	ldr	x2, .LC125
	mov	w3, w19
	ldr	x1, .LC126
	mov	w4, 0
	add	x2, x2, 368
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L309:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L307
	str	x0, [x20, x19]
	b	.L306
.L307:
	ldr	x1, .LC128
	mov	w0, 0
	bl	dprint_vfmw
	b	.L303
	.size	VDMHAL_V5R6C1_ClearMMUIntState, .-VDMHAL_V5R6C1_ClearMMUIntState
	.align	3
.LC125:
	.xword	.LANCHOR0
	.align	3
.LC126:
	.xword	.LC86
	.align	3
.LC127:
	.xword	g_HwMem
	.align	3
.LC128:
	.xword	.LC123
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_MaskInt
	.type	VDMHAL_V5R6C1_MaskInt, %function
VDMHAL_V5R6C1_MaskInt:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	sxtw	x19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, wzr
	bgt	.L315
	lsl	x3, x19, 6
	ldr	x20, .LC131
	sub	x3, x3, x19
	lsl	x3, x3, 2
	sub	x19, x3, x19
	add	x19, x3, x19, lsl 2
	ldr	x0, [x20, x19]
	cbz	x0, .L316
.L313:
	mov	w1, -1
	str	w1, [x0, 36]
.L310:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L315:
	ldr	x2, .LC129
	mov	w3, w19
	ldr	x1, .LC130
	mov	w4, 0
	add	x2, x2, 400
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L316:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L314
	str	x0, [x20, x19]
	b	.L313
.L314:
	ldr	x1, .LC132
	mov	w0, 0
	bl	dprint_vfmw
	b	.L310
	.size	VDMHAL_V5R6C1_MaskInt, .-VDMHAL_V5R6C1_MaskInt
	.align	3
.LC129:
	.xword	.LANCHOR0
	.align	3
.LC130:
	.xword	.LC86
	.align	3
.LC131:
	.xword	g_HwMem
	.align	3
.LC132:
	.xword	.LC123
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_GetIntMaskCfg
	.type	VDMHAL_V5R6C1_GetIntMaskCfg, %function
VDMHAL_V5R6C1_GetIntMaskCfg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 1
	mov	w1, -6
	mov	w0, -2
	ldr	x19, [sp, 16]
	csel	w0, w1, w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMHAL_V5R6C1_GetIntMaskCfg, .-VDMHAL_V5R6C1_GetIntMaskCfg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_EnableInt
	.type	VDMHAL_V5R6C1_EnableInt, %function
VDMHAL_V5R6C1_EnableInt:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC134
	sxtw	x0, w19
	ldr	x2, .LC133
	add	x1, x1, x0, lsl 6
	ldrsw	x1, [x1, 8]
	ldr	x1, [x2, x1, lsl 3]
	cbz	x1, .L328
	ldr	w20, [x1, 1272]
.L321:
	cmp	w19, wzr
	bgt	.L329
	lsl	x19, x0, 6
	ldr	x21, .LC137
	sub	x19, x19, x0
	lsl	x19, x19, 2
	sub	x0, x19, x0
	add	x19, x19, x0, lsl 2
	ldr	x0, [x21, x19]
	cbz	x0, .L330
.L324:
	mov	w1, -6
	mov	w2, -2
	cmp	w20, 1
	csel	w1, w1, w2, eq
	str	w1, [x0, 36]
.L320:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L329:
	ldr	x2, .LC135
	mov	w3, w19
	ldr	x1, .LC136
	mov	w4, 0
	add	x2, x2, 424
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L328:
	mov	w20, 0
	b	.L321
	.p2align 3
.L330:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L325
	str	x0, [x21, x19]
	b	.L324
.L325:
	ldr	x1, .LC138
	mov	w0, 0
	bl	dprint_vfmw
	b	.L320
	.size	VDMHAL_V5R6C1_EnableInt, .-VDMHAL_V5R6C1_EnableInt
	.align	3
.LC133:
	.xword	s_pstVfmwChan
	.align	3
.LC134:
	.xword	g_VdmDrvParam
	.align	3
.LC135:
	.xword	.LANCHOR0
	.align	3
.LC136:
	.xword	.LC86
	.align	3
.LC137:
	.xword	g_HwMem
	.align	3
.LC138:
	.xword	.LC123
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_CheckReg
	.type	VDMHAL_V5R6C1_CheckReg, %function
VDMHAL_V5R6C1_CheckReg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w22, w0
	mov	x0, x30
	sxtw	x19, w1
	bl	_mcount
	cmp	w19, wzr
	bgt	.L348
	lsl	x0, x19, 6
	ldr	x21, .LC142
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x20, x0, x19
	add	x20, x0, x20, lsl 2
	ldr	x0, [x21, x20]
	cbz	x0, .L349
.L334:
	sub	w0, w22, #1
	cmp	w0, 6
	bls	.L350
	ldr	x2, .LC139
	mov	w3, w22
	ldr	x1, .LC146
	mov	w0, 0
	add	x2, x2, 448
	bl	dprint_vfmw
	mov	w0, 0
.L347:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L350:
	ldr	x1, .LC147
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx341
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx341:
	.section	.rodata
	.align	0
	.align	2
.L341:
	.byte	(.L345 - .Lrtx341) / 4
	.byte	(.L342 - .Lrtx341) / 4
	.byte	(.L343 - .Lrtx341) / 4
	.byte	(.L344 - .Lrtx341) / 4
	.byte	(.L346 - .Lrtx341) / 4
	.byte	(.L336 - .Lrtx341) / 4
	.byte	(.L338 - .Lrtx341) / 4
	.text
	.p2align 3
.L346:
	mov	x1, 61480
.L340:
	lsl	x0, x19, 6
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x19, x0, x19
	add	x19, x0, x19, lsl 2
	ldr	x0, [x21, x19]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	w0, [x0, x1]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L345:
	mov	x1, 28
	b	.L340
	.p2align 3
.L344:
	mov	x1, 40
	b	.L340
	.p2align 3
.L343:
	mov	x1, 36
	b	.L340
	.p2align 3
.L342:
	mov	x1, 32
	b	.L340
	.p2align 3
.L338:
	mov	x1, 62272
	b	.L340
	.p2align 3
.L336:
	mov	x1, 62304
	b	.L340
	.p2align 3
.L349:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L335
	str	x0, [x21, x20]
	b	.L334
	.p2align 3
.L348:
	ldr	x2, .LC139
	mov	w3, w19
	ldr	x1, .LC141
	mov	w0, 0
	add	x2, x2, 448
	bl	dprint_vfmw
	mov	w0, -1
	b	.L347
.L335:
	ldr	x2, .LC139
	mov	w0, 0
	ldr	x1, .LC144
	add	x2, x2, 448
	bl	dprint_vfmw
	mov	w0, 0
	b	.L347
	.size	VDMHAL_V5R6C1_CheckReg, .-VDMHAL_V5R6C1_CheckReg
	.align	3
.LC139:
	.xword	.LANCHOR0
	.align	3
.LC141:
	.xword	.LC140
	.align	3
.LC142:
	.xword	g_HwMem
	.align	3
.LC144:
	.xword	.LC143
	.align	3
.LC146:
	.xword	.LC145
	.align	3
.LC147:
	.xword	.L341
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_ReadMMUMask
	.type	VDMHAL_V5R6C1_ReadMMUMask, %function
VDMHAL_V5R6C1_ReadMMUMask:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	sxtw	x19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, wzr
	ble	.L354
	ldr	x2, .LC149
	mov	w3, w19
	ldr	x1, .LC150
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L354:
	lsl	x0, x19, 6
	ldr	x1, .LC148
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x19, x0, x19
	add	x19, x0, x19, lsl 2
	ldr	x0, [x1, x19]
	ldr	x19, [sp, 16]
	add	x0, x0, 61440
	ldp	x29, x30, [sp], 32
	ldr	w0, [x0, 32]
	ret
	.size	VDMHAL_V5R6C1_ReadMMUMask, .-VDMHAL_V5R6C1_ReadMMUMask
	.align	3
.LC148:
	.xword	g_HwMem
	.align	3
.LC149:
	.xword	.LANCHOR1
	.align	3
.LC150:
	.xword	.LC107
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_WriteMMUMask
	.type	VDMHAL_V5R6C1_WriteMMUMask, %function
VDMHAL_V5R6C1_WriteMMUMask:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	sxtw	x19, w1
	bl	_mcount
	cmp	w19, wzr
	ble	.L358
	ldr	x2, .LC152
	mov	w3, w19
	ldr	x1, .LC153
	mov	w4, 1
	add	x2, x2, 32
	mov	w0, 32
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L358:
	lsl	x0, x19, 6
	ldr	x1, .LC151
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x19, x0, x19
	add	x19, x0, x19, lsl 2
	ldr	x0, [x1, x19]
	add	x0, x0, 61440
	str	w20, [x0, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMHAL_V5R6C1_WriteMMUMask, .-VDMHAL_V5R6C1_WriteMMUMask
	.align	3
.LC151:
	.xword	g_HwMem
	.align	3
.LC152:
	.xword	.LANCHOR1
	.align	3
.LC153:
	.xword	.LC99
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_PrepareDec
	.type	VDMHAL_V5R6C1_PrepareDec, %function
VDMHAL_V5R6C1_PrepareDec:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w20, w0
	mov	x22, x1
	mov	x0, x30
	mov	w21, w2
	mov	x19, x3
	bl	_mcount
	cbz	x22, .L379
	cmp	w21, wzr
	bgt	.L380
	cmp	w20, 6
	mov	w2, 0
	cset	w1, eq
	mov	w0, 0
	mov	x3, x19
	bl	SCD_ConfigReg
	mov	x3, x19
	mov	w2, 0
	mov	w1, 1
	mov	w0, 8
	bl	SCD_ConfigReg
	cmp	w20, 18
	bls	.L381
.L378:
	mov	w0, -1
	b	.L361
	.p2align 3
.L381:
	ldr	x0, .LC158
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx364
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx364:
	.section	.rodata
	.align	0
	.align	2
.L364:
	.byte	(.L374 - .Lrtx364) / 4
	.byte	(.L365 - .Lrtx364) / 4
	.byte	(.L366 - .Lrtx364) / 4
	.byte	(.L367 - .Lrtx364) / 4
	.byte	(.L378 - .Lrtx364) / 4
	.byte	(.L368 - .Lrtx364) / 4
	.byte	(.L369 - .Lrtx364) / 4
	.byte	(.L378 - .Lrtx364) / 4
	.byte	(.L370 - .Lrtx364) / 4
	.byte	(.L371 - .Lrtx364) / 4
	.byte	(.L372 - .Lrtx364) / 4
	.byte	(.L372 - .Lrtx364) / 4
	.byte	(.L372 - .Lrtx364) / 4
	.byte	(.L373 - .Lrtx364) / 4
	.byte	(.L378 - .Lrtx364) / 4
	.byte	(.L374 - .Lrtx364) / 4
	.byte	(.L375 - .Lrtx364) / 4
	.byte	(.L376 - .Lrtx364) / 4
	.byte	(.L377 - .Lrtx364) / 4
	.text
	.p2align 3
.L374:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	H264HAL_V5R6C1_StartDec
.L361:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L376:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	VP9HAL_V5R6C1_StartDec
	b	.L361
	.p2align 3
.L375:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	HEVCHAL_V5R6C1_StartDec
	b	.L361
	.p2align 3
.L373:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	VP8HAL_V5R6C1_StartDec
	b	.L361
	.p2align 3
.L372:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	VP6HAL_V5R6C1_StartDec
	b	.L361
	.p2align 3
.L371:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	RV9HAL_V5R6C1_StartDec
	b	.L361
	.p2align 3
.L370:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	RV8HAL_V5R6C1_StartDec
	b	.L361
	.p2align 3
.L369:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	AVSHAL_V5R6C1_StartDec
	b	.L361
	.p2align 3
.L368:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	DIVX3HAL_V5R6C1_StartDec
	b	.L361
	.p2align 3
.L367:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	MP2HAL_V5R6C1_StartDec
	b	.L361
	.p2align 3
.L366:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	MP4HAL_V5R6C1_StartDec
	b	.L361
	.p2align 3
.L365:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	VC1HAL_V5R6C1_StartDec
	b	.L361
	.p2align 3
.L377:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	AVS2HAL_V5R6C1_StartDec
	b	.L361
	.p2align 3
.L380:
	ldr	x2, .LC154
	mov	w3, w21
	ldr	x1, .LC157
	mov	w4, 0
	add	x2, x2, 64
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L379:
	ldr	x2, .LC154
	mov	x3, 0
	ldr	x1, .LC156
	mov	w0, 0
	add	x2, x2, 64
	bl	dprint_vfmw
	mov	w0, -1
	b	.L361
	.size	VDMHAL_V5R6C1_PrepareDec, .-VDMHAL_V5R6C1_PrepareDec
	.align	3
.LC154:
	.xword	.LANCHOR1
	.align	3
.LC156:
	.xword	.LC155
	.align	3
.LC157:
	.xword	.LC86
	.align	3
.LC158:
	.xword	.L364
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_IsVdmReady
	.type	VDMHAL_V5R6C1_IsVdmReady, %function
VDMHAL_V5R6C1_IsVdmReady:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sxtw	x0, w19
	ldr	x2, .LC159
	lsl	x1, x0, 6
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x0, x1, x0
	add	x0, x1, x0, lsl 2
	ldr	x0, [x2, x0]
	cbz	x0, .L387
	cmp	w19, wzr
	ble	.L388
	ldr	x2, .LC162
	mov	w4, 1
	ldr	x1, .LC164
	mov	w3, w19
	add	x2, x2, 96
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, 0
.L384:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L388:
	ldr	w0, [x0, 28]
	ldr	x19, [sp, 16]
	ubfx	x0, x0, 17, 1
	ldp	x29, x30, [sp], 32
	ret
.L387:
	ldr	x2, .LC162
	ldr	x3, .LC161
	ldr	x1, .LC163
	add	x2, x2, 96
	bl	dprint_vfmw
	mov	w0, -1
	b	.L384
	.size	VDMHAL_V5R6C1_IsVdmReady, .-VDMHAL_V5R6C1_IsVdmReady
	.align	3
.LC159:
	.xword	g_HwMem
	.align	3
.LC161:
	.xword	.LC160
	.align	3
.LC162:
	.xword	.LANCHOR1
	.align	3
.LC163:
	.xword	.LC6
	.align	3
.LC164:
	.xword	.LC107
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_IsVdmRun
	.type	VDMHAL_V5R6C1_IsVdmRun, %function
VDMHAL_V5R6C1_IsVdmRun:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sxtw	x0, w19
	ldr	x2, .LC165
	lsl	x1, x0, 6
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x0, x1, x0
	add	x0, x1, x0, lsl 2
	ldr	x0, [x2, x0]
	cbz	x0, .L394
	cmp	w19, wzr
	ble	.L395
	ldr	x2, .LC168
	mov	w4, 1
	ldr	x1, .LC169
	mov	w3, w19
	add	x2, x2, 128
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, 1
.L391:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L395:
	ldr	w0, [x0, 40]
	ldr	x19, [sp, 16]
	cmp	w0, 1
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L394:
	ldr	x1, .LC167
	bl	dprint_vfmw
	mov	w0, 0
	b	.L391
	.size	VDMHAL_V5R6C1_IsVdmRun, .-VDMHAL_V5R6C1_IsVdmRun
	.align	3
.LC165:
	.xword	g_HwMem
	.align	3
.LC167:
	.xword	.LC166
	.align	3
.LC168:
	.xword	.LANCHOR1
	.align	3
.LC169:
	.xword	.LC107
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_IsVdhDecOver
	.type	VDMHAL_V5R6C1_IsVdhDecOver, %function
VDMHAL_V5R6C1_IsVdhDecOver:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	sxtw	x0, w20
	ldr	x1, .LC170
	lsl	x2, x0, 6
	sub	x2, x2, x0
	lsl	x2, x2, 2
	sub	x0, x2, x0
	add	x0, x2, x0, lsl 2
	ldr	x0, [x1, x0]
	cbz	x0, .L404
	mov	w1, w20
	mov	w0, w19
	bl	VDMHAL_V5R6C1_CheckReg
	cmp	w19, 2
	beq	.L401
	cmp	w19, 3
	beq	.L401
	cmp	w19, 1
	ubfx	x0, x0, 17, 1
	beq	.L398
	ldr	x2, .LC172
	mov	w3, w19
	ldr	x1, .LC174
	mov	w0, 0
	add	x2, x2, 152
	bl	dprint_vfmw
	mov	w0, 0
.L398:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L401:
	and	w0, w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L404:
	ldr	x2, .LC172
	ldr	x3, .LC171
	ldr	x1, .LC173
	add	x2, x2, 152
	bl	dprint_vfmw
	mov	w0, -1
	b	.L398
	.size	VDMHAL_V5R6C1_IsVdhDecOver, .-VDMHAL_V5R6C1_IsVdhDecOver
	.align	3
.LC170:
	.xword	g_HwMem
	.align	3
.LC171:
	.xword	.LC160
	.align	3
.LC172:
	.xword	.LANCHOR1
	.align	3
.LC173:
	.xword	.LC6
	.align	3
.LC174:
	.xword	.LC145
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_IsVdhPartDecOver
	.type	VDMHAL_V5R6C1_IsVdhPartDecOver, %function
VDMHAL_V5R6C1_IsVdhPartDecOver:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	sxtw	x0, w20
	ldr	x1, .LC175
	lsl	x2, x0, 6
	sub	x2, x2, x0
	lsl	x2, x2, 2
	sub	x0, x2, x0
	add	x0, x2, x0, lsl 2
	ldr	x0, [x1, x0]
	cbz	x0, .L413
	mov	w1, w20
	mov	w0, w19
	bl	VDMHAL_V5R6C1_CheckReg
	cmp	w19, 1
	beq	.L409
	cmp	w19, 2
	ubfx	x0, x0, 2, 1
	bne	.L414
.L407:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L414:
	ldr	x2, .LC177
	mov	w3, w19
	ldr	x1, .LC179
	mov	w0, 0
	add	x2, x2, 184
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L409:
	ubfx	x0, x0, 19, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L413:
	ldr	x2, .LC177
	ldr	x3, .LC176
	ldr	x1, .LC178
	add	x2, x2, 184
	bl	dprint_vfmw
	mov	w0, -1
	b	.L407
	.size	VDMHAL_V5R6C1_IsVdhPartDecOver, .-VDMHAL_V5R6C1_IsVdhPartDecOver
	.align	3
.LC175:
	.xword	g_HwMem
	.align	3
.LC176:
	.xword	.LC160
	.align	3
.LC177:
	.xword	.LANCHOR1
	.align	3
.LC178:
	.xword	.LC6
	.align	3
.LC179:
	.xword	.LC145
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_UpdateHardwareInfo
	.type	VDMHAL_V5R6C1_UpdateHardwareInfo, %function
VDMHAL_V5R6C1_UpdateHardwareInfo:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w22, w0
	mov	x0, x30
	bl	_mcount
	cmp	w22, wzr
	bgt	.L416
	ldr	x4, .LC180
	add	x0, x4, 4
	add	x4, x4, 128
	ldr	w1, [x4, -128]
	cmp	w1, 1
	bne	.L420
	b	.L431
	.p2align 3
.L441:
	cmp	x0, x4
	beq	.L440
.L420:
	ldr	w1, [x0]
	add	x0, x0, 4
	cmp	w1, 1
	bne	.L441
.L431:
	mov	w19, w1
.L417:
	sxtw	x20, w22
	ldr	x24, .LC185
	lsl	x0, x20, 6
	sub	x0, x0, x20
	lsl	x0, x0, 2
	sub	x21, x0, x20
	add	x21, x0, x21, lsl 2
	ldr	x1, [x24, x21]
	cbz	x1, .L442
.L421:
	lsl	x0, x20, 2
	ldr	x21, .LC187
	sub	x4, x0, x20
	ldr	x2, .LC191
	lsl	x0, x4, 4
	ldr	w3, [x1, 12]
	sub	x0, x0, x4
	lsl	x5, x20, 6
	lsl	x0, x0, 2
	add	x4, x21, x0
	str	w3, [x21, x0]
	add	x0, x2, x5
	ldr	w3, [x1, 28]
	ldr	w0, [x0, 56]
	str	w3, [x4, 4]
	cmp	w0, 1
	beq	.L443
	cmp	w19, 1
	beq	.L444
	ldr	w5, [x1, 4096]
	ldr	w3, [x1, 4108]
	ldr	w2, [x1, 208]
	ldr	w0, [x1, 212]
	stp	w2, w0, [x4, 8]
	stp	w5, w3, [x4, 16]
	cbz	w19, .L445
.L426:
	mov	w0, 180
	add	x4, x1, 32768
	add	x1, x4, 256
	smull	x2, w22, w0
	add	x0, x2, 52
	add	x2, x2, 180
	add	x0, x21, x0
	add	x3, x21, x2
	.p2align 2
.L427:
	ldr	w2, [x1], 4
	str	w2, [x0], 4
	cmp	x3, x0
	bne	.L427
	mov	w0, 0
	cbnz	w19, .L434
	lsl	x1, x20, 2
	ldr	w3, [x4, 384]
	sub	x20, x1, x20
	ldr	w2, [x4, 388]
	lsl	x1, x20, 4
	sub	x1, x1, x20
	add	x21, x21, x1, lsl 2
	stp	w2, w3, [x21, 44]
.L434:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L445:
	ldr	w5, [x1, 176]
	ldr	w0, [x1, 180]
	stp	w5, w0, [x4, 24]
	ldr	w3, [x1, 184]
	ldr	w2, [x1, 188]
	ldr	w0, [x1, 192]
	stp	w3, w2, [x4, 32]
	str	w0, [x4, 40]
	b	.L426
	.p2align 3
.L440:
	mov	w19, 0
	b	.L417
.L443:
	ldr	w2, [x1, 4108]
	mov	w0, 0
	str	w2, [x4, 20]
	and	w2, w2, 1048575
	ldr	w1, [x1, 176]
	stp	w2, w1, [x4, 20]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L444:
	sub	x0, x5, x20
	and	w23, w3, 131071
	lsl	x0, x0, 2
	sub	x1, x0, x20
	add	x0, x0, x1, lsl 2
	add	x0, x24, x0
	ldr	w0, [x0, 56]
	bl	MEM_Phy2Vir
	cbz	x0, .L446
	sub	w1, w23, #1
	cmp	w1, 199
	bhi	.L432
	lsl	w1, w23, 2
	sub	w1, w1, #4
	lsl	x1, x1, 2
	add	x3, x1, 8
.L425:
	lsl	x2, x20, 2
	ldr	w4, [x0, x1]
	sub	x2, x2, x20
	lsl	x1, x2, 4
	sub	x2, x1, x2
	lsl	x1, x20, 6
	sub	x1, x1, x20
	add	x2, x21, x2, lsl 2
	lsl	x1, x1, 2
	str	w4, [x2, 16]
	ldr	w3, [x0, x3]
	sub	x0, x1, x20
	str	w3, [x2, 20]
	add	x1, x1, x0, lsl 2
	ldr	x1, [x24, x1]
	ldr	w3, [x1, 208]
	ldr	w0, [x1, 212]
	stp	w3, w0, [x2, 8]
	b	.L426
.L442:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L422
	str	x0, [x24, x21]
	mov	x1, x0
	b	.L421
.L432:
	mov	x3, 8
	mov	x1, 0
	b	.L425
.L416:
	ldr	x2, .LC181
	mov	w4, 0
	ldr	x1, .LC182
	mov	w3, w22
	add	x2, x2, 216
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L434
.L446:
	ldr	x2, .LC181
	ldr	x3, .LC189
	ldr	x1, .LC190
	add	x2, x2, 216
	bl	dprint_vfmw
	mov	w0, -1
	b	.L434
.L422:
	ldr	x1, .LC186
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L434
	.size	VDMHAL_V5R6C1_UpdateHardwareInfo, .-VDMHAL_V5R6C1_UpdateHardwareInfo
	.align	3
.LC180:
	.xword	g_DSPState
	.align	3
.LC181:
	.xword	.LANCHOR1
	.align	3
.LC182:
	.xword	.LC86
	.align	3
.LC185:
	.xword	g_HwMem
	.align	3
.LC186:
	.xword	.LC123
	.align	3
.LC187:
	.xword	g_BackUp
	.align	3
.LC189:
	.xword	.LC188
	.align	3
.LC190:
	.xword	.LC6
	.align	3
.LC191:
	.xword	g_VdmDrvParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_ReadMsgSlot
	.type	VDMHAL_V5R6C1_ReadMsgSlot, %function
VDMHAL_V5R6C1_ReadMsgSlot:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	mov	w19, w2
	bl	_mcount
	cmp	x20, xzr
	ccmp	x21, xzr, 4, ne
	beq	.L451
	cmp	w19, 800
	bhi	.L452
	ldr	x3, .LC196
	ubfiz	x2, x19, 2, 30
	mov	x1, x21
	mov	x0, x20
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 0
.L449:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L452:
	ldr	x1, .LC195
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L449
	.p2align 3
.L451:
	ldr	x1, .LC193
	mov	x3, x21
	mov	x2, x20
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L449
	.size	VDMHAL_V5R6C1_ReadMsgSlot, .-VDMHAL_V5R6C1_ReadMsgSlot
	.align	3
.LC193:
	.xword	.LC192
	.align	3
.LC195:
	.xword	.LC194
	.align	3
.LC196:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_WriteMsgSlot
	.type	VDMHAL_V5R6C1_WriteMsgSlot, %function
VDMHAL_V5R6C1_WriteMsgSlot:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	w21, w2
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L454
	sub	w0, w21, #1
	cmp	w0, 255
	bhi	.L454
	ldr	x3, .LC199
	ubfiz	x2, x21, 2, 30
	mov	x1, x20
	mov	x0, x19
	ldr	x3, [x3, 104]
	blr	x3
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L454:
	ldr	x1, .LC198
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	VDMHAL_V5R6C1_WriteMsgSlot, .-VDMHAL_V5R6C1_WriteMsgSlot
	.align	3
.LC198:
	.xword	.LC197
	.align	3
.LC199:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_CfgRpMsg
	.type	VDMHAL_V5R6C1_CfgRpMsg, %function
VDMHAL_V5R6C1_CfgRpMsg:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x20, 64]
	bl	MEM_Phy2Vir
	mov	x20, x0
	cbz	x0, .L504
	ldr	w2, [x19, 44]
	sub	w0, w2, #1
	cmp	w0, 199
	bhi	.L505
	ldr	w3, [x19, 64]
	ldp	w0, w2, [x19, 28]
	ldr	w6, [x19, 4]
	lsl	w0, w0, w3
	lsl	w2, w2, w3
	add	w1, w0, 255
	cmp	w0, 1920
	and	w1, w1, -256
	lsl	w3, w1, 4
	bgt	.L501
	cmp	w6, 17
	beq	.L501
	strb	wzr, [x19]
	mov	w4, 0
	strb	wzr, [x19, 1]
.L464:
	cmp	w6, 16
	beq	.L465
.L509:
	add	w0, w2, 31
	mov	w23, 8
	and	w0, w0, -32
	madd	w0, w0, w1, w4
.L488:
	ldr	w2, [x19, 20]
	mov	w1, w3
	str	w2, [x20]
	ldr	w2, [x19, 20]
	add	w2, w0, w2
	str	w2, [x20, 4]
	ldr	w2, [x19, 8]
	str	w2, [x20, 8]
	ldr	w2, [x19, 8]
	add	w0, w0, w2
	str	w0, [x20, 12]
	ldrb	w0, [x19, 1]
	cbnz	w0, .L506
.L467:
	str	w1, [x20, 16]
	mov	w3, 0
	str	w4, [x20, 20]
	mov	w2, 0
	ldp	w1, w0, [x19, 28]
	sub	w0, w0, #1
	sub	w1, w1, #1
	bfi	w2, w0, 0, 9
	bfi	w3, w1, 0, 9
	strh	w2, [x29, 74]
	strh	w3, [x29, 72]
	ldr	w0, [x29, 72]
	str	w0, [x20, 24]
	ldr	w0, [x19, 52]
	ldp	w21, w22, [x19, 28]
	sub	w0, w0, #1
	cmp	w0, 1
	bls	.L507
.L469:
	ldr	w0, [x19, 56]
	mov	w11, 0
	cbz	w0, .L508
.L470:
	cmp	w0, 1
	beq	.L486
.L514:
	sub	w11, w11, #1
	uxth	w11, w11
.L487:
	ldr	w3, [x19, 64]
	ldrb	w4, [x19]
	ldr	w2, [x19, 52]
	sub	w3, w3, #4
	ldrb	w1, [x29, 74]
	ldrb	w0, [x29, 75]
	and	w2, w2, 3
	bfi	w1, w4, 0, 1
	strh	w11, [x29, 72]
	bfi	w0, w3, 0, 2
	ldrb	w3, [x19, 1]
	bfi	w1, w2, 4, 2
	bfi	w0, w23, 2, 4
	bfi	w1, w2, 6, 2
	bfi	w0, w3, 6, 1
	strb	w1, [x29, 74]
	strb	w0, [x29, 75]
	mov	w0, 0
	ldr	w1, [x29, 72]
	str	w1, [x20, 28]
.L500:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L501:
	ldrb	w4, [x19]
	strb	wzr, [x19, 1]
	cmp	w4, 1
	mov	w4, 0
	bne	.L464
	adds	w4, w0, 2047
	add	w0, w0, 4094
	csel	w0, w0, w4, mi
	add	w5, w2, 126
	and	w0, w0, -2048
	cmp	w0, wzr
	add	w4, w0, 127
	csel	w0, w4, w0, lt
	adds	w7, w2, 63
	csel	w4, w5, w7, mi
	asr	w0, w0, 7
	asr	w4, w4, 6
	cmp	w6, 16
	lsl	w4, w4, 5
	mul	w4, w0, w4
	bne	.L509
.L465:
	madd	w0, w2, w1, w4
	mov	w23, 10
	b	.L488
	.p2align 3
.L506:
	add	w0, w3, 15
	cmp	w3, wzr
	csel	w1, w0, w3, lt
	asr	w1, w1, 4
	b	.L467
	.p2align 3
.L508:
	ldr	w0, [x19, 64]
	cmp	w0, 6
	beq	.L491
	cmp	w0, 5
	beq	.L492
	cmp	w0, 4
	mov	w2, 8
	beq	.L471
	ldr	x1, .LC207
	mov	w0, 1
	bl	dprint_vfmw
	mov	w2, 1
.L471:
	ldr	w8, [x19, 44]
	cmp	w8, wzr
	ble	.L502
	mul	w12, w22, w21
	mov	w4, 0
	mov	w6, 0
	sub	w13, w12, #1
	mov	w11, 0
	sub	w9, w2, #1
	b	.L474
	.p2align 3
.L512:
	ldrsh	w6, [x10, 70]
	sub	w6, w6, #1
	add	w6, w6, w2
	udiv	w6, w6, w2
	mul	w6, w6, w2
	cmp	w0, w6
	bgt	.L477
.L476:
	add	w4, w4, 1
	cmp	w4, w8
	bge	.L510
.L485:
	cmp	w4, 199
	bgt	.L511
.L474:
	add	x10, x19, x4, sxtw 2
	cmp	w4, wzr
	ldrsh	w1, [x10, 74]
	sub	w0, w1, #1
	add	w0, w0, w2
	udiv	w0, w0, w2
	mul	w0, w0, w2
	bgt	.L512
	ccmp	w0, w6, 0, ne
	ble	.L476
.L479:
	ldrsh	w1, [x10, 72]
	cmp	w12, w0
	csel	w0, w0, w13, hi
	add	w5, w11, 1
	udiv	w1, w1, w2
	mul	w1, w1, w2
	cmp	w1, w0
	csel	w1, w1, wzr, le
	cmp	w5, 252
	bgt	.L513
	udiv	w7, w1, w21
	sxtw	x3, w11
	mov	w11, w5
	mov	w8, 0
	add	x3, x3, 6
	add	w4, w4, 1
	lsl	x3, x3, 3
	udiv	w5, w0, w21
	msub	w1, w7, w21, w1
	bfi	w8, w1, 0, 9
	mov	w1, 0
	bfi	w1, w7, 0, 9
	strh	w8, [x29, 76]
	strh	w1, [x29, 78]
	mov	w1, 0
	msub	w0, w5, w21, w0
	bfi	w1, w0, 0, 9
	mov	w0, 0
	bfi	w0, w5, 0, 9
	ldr	w5, [x29, 76]
	str	w5, [x20, x3]
	add	x3, x3, 4
	strh	w1, [x29, 76]
	strh	w0, [x29, 78]
	ldr	w0, [x29, 76]
	str	w0, [x20, x3]
	ldr	w8, [x19, 44]
	cmp	w4, w8
	blt	.L485
.L510:
	ldr	w0, [x19, 56]
	cmp	w0, 1
	bne	.L514
	.p2align 2
.L486:
	strh	wzr, [x29, 72]
	sub	w21, w21, #1
	strh	wzr, [x29, 74]
	mov	w2, 0
	sub	w22, w22, #1
	mov	w1, 0
	ldr	w3, [x29, 72]
	bfi	w2, w21, 0, 9
	bfi	w1, w22, 0, 9
	strh	w2, [x29, 72]
	strh	w1, [x29, 74]
	mov	w11, 0
	str	w0, [x19, 44]
	str	w3, [x20, 48]
	ldr	w0, [x29, 72]
	str	w0, [x20, 52]
	b	.L487
	.p2align 3
.L507:
	add	w22, w22, w22, lsr 31
	asr	w22, w22, 1
	b	.L469
	.p2align 3
.L480:
	udiv	w0, w0, w2
	ldrsh	w1, [x5, 76]
	udiv	w1, w1, w2
	mul	w0, w0, w2
	mul	w1, w1, w2
	cmp	w0, w1
	add	w14, w1, 1
	bhi	.L481
	sub	w1, w4, #1
	cmp	w0, w14
	add	x1, x19, x1, sxtw 2
	beq	.L481
	ldrsh	w1, [x1, 74]
	sub	w1, w1, #1
	add	w1, w1, w2
	udiv	w1, w1, w2
	mul	w1, w1, w2
	cmp	w0, w1
	bhi	.L479
.L481:
	cmp	w7, 199
	mov	w4, w3
	bgt	.L515
	ldrsh	w1, [x5, 78]
.L477:
	add	w3, w4, 1
	add	x5, x19, x4, sxtw 2
	cmp	w8, w3
	add	w0, w9, w1
	add	w7, w3, 1
	bgt	.L480
	udiv	w0, w0, w2
	mul	w0, w0, w2
	b	.L479
.L492:
	mov	w2, 4
	b	.L471
	.p2align 3
.L515:
	add	x0, x19, x3, sxtw 2
	ldrsh	w0, [x0, 74]
	sub	w0, w0, #1
	add	w0, w0, w2
	udiv	w0, w0, w2
	mul	w0, w0, w2
	b	.L479
.L511:
	ldr	x2, .LC202
	mov	w3, 2176
	ldr	x1, .LC209
	mov	w0, 0
	add	x2, x2, 280
	bl	dprint_vfmw
.L502:
	mov	w11, 0
	ldr	w0, [x19, 56]
	b	.L470
.L491:
	mov	w2, 2
	b	.L471
.L513:
	mov	w0, 1
	str	w0, [x19, 56]
	b	.L486
.L505:
	ldr	x1, .LC205
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L500
.L504:
	ldr	x2, .LC202
	mov	w0, 0
	ldr	x3, .LC201
	ldr	x1, .LC203
	add	x2, x2, 256
	bl	dprint_vfmw
	mov	w0, -1
	b	.L500
	.size	VDMHAL_V5R6C1_CfgRpMsg, .-VDMHAL_V5R6C1_CfgRpMsg
	.align	3
.LC201:
	.xword	.LC200
	.align	3
.LC202:
	.xword	.LANCHOR1
	.align	3
.LC203:
	.xword	.LC6
	.align	3
.LC205:
	.xword	.LC204
	.align	3
.LC207:
	.xword	.LC206
	.align	3
.LC209:
	.xword	.LC208
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_CfgRpReg
	.type	VDMHAL_V5R6C1_CfgRpReg, %function
VDMHAL_V5R6C1_CfgRpReg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x0, x30
	mov	w21, w3
	mov	x22, x1
	mov	x20, x4
	bl	_mcount
	str	wzr, [x29, 60]
	cmp	w21, wzr
	bgt	.L542
	ldr	x0, [x22]
	cbz	x0, .L543
.L519:
	ldr	x19, .LC213
	ldr	w3, [x22, 64]
	ldrb	w0, [x19]
	and	w3, w3, -16
	str	w3, [x29, 60]
	cmp	w0, 1
	beq	.L544
	mov	x0, x20
	mov	w2, 16
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	mov	w3, 53763
	movk	w3, 0x2000, lsl 16
	str	w3, [x29, 60]
	cmp	w0, 1
	beq	.L545
	mov	x0, x20
	mov	w2, 12
	mov	w1, 2
	mov	w22, 3075
	movk	w22, 0x30, lsl 16
	bl	VDH_Record_RegData
	str	w22, [x29, 60]
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L546
	mov	x0, x20
	mov	w3, w22
	mov	w2, 60
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L547
	mov	x0, x20
	mov	w3, w22
	mov	w2, 64
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L548
	mov	x0, x20
	mov	w3, w22
	mov	w2, 68
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L549
	mov	x0, x20
	mov	w3, w22
	mov	w2, 72
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L550
	mov	x0, x20
	mov	w3, w22
	mov	w2, 76
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L551
	mov	x0, x20
	mov	w3, w22
	mov	w2, 80
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L552
	mov	x0, x20
	mov	w3, w22
	mov	w2, 84
	mov	w1, 2
	bl	VDH_Record_RegData
	mov	w0, 0
.L539:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L544:
	sxtw	x1, w21
	ldr	x2, .LC214
	lsl	x0, x1, 6
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x4, x0, x1
	add	x0, x0, x4, lsl 2
	ldr	x0, [x2, x0]
	str	w3, [x0, 16]
.L522:
	lsl	x0, x1, 6
	mov	w4, 53763
	sub	x0, x0, x1
	movk	w4, 0x2000, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 12]
.L524:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 60]
.L526:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 64]
.L528:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 68]
.L530:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 72]
.L532:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 76]
.L534:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 80]
.L536:
	lsl	x3, x1, 6
	mov	w4, 3075
	sub	x3, x3, x1
	movk	w4, 0x30, lsl 16
	lsl	x3, x3, 2
	mov	w0, 0
	sub	x1, x3, x1
	add	x1, x3, x1, lsl 2
	ldr	x1, [x2, x1]
	str	w4, [x1, 84]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L543:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L520
	str	x0, [x22]
	b	.L519
	.p2align 3
.L542:
	ldr	x2, .LC210
	mov	w4, 0
	ldr	x1, .LC211
	mov	w3, w21
	add	x2, x2, 304
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L539
.L520:
	ldr	x1, .LC212
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L539
.L549:
	ldr	x2, .LC214
	sxtw	x1, w21
	b	.L530
.L548:
	ldr	x2, .LC214
	sxtw	x1, w21
	b	.L528
.L547:
	ldr	x2, .LC214
	sxtw	x1, w21
	b	.L526
.L546:
	ldr	x2, .LC214
	sxtw	x1, w21
	b	.L524
.L551:
	ldr	x2, .LC214
	sxtw	x1, w21
	b	.L534
.L550:
	ldr	x2, .LC214
	sxtw	x1, w21
	b	.L532
.L552:
	ldr	x2, .LC214
	sxtw	x1, w21
	b	.L536
.L545:
	ldr	x2, .LC214
	sxtw	x1, w21
	b	.L522
	.size	VDMHAL_V5R6C1_CfgRpReg, .-VDMHAL_V5R6C1_CfgRpReg
	.align	3
.LC210:
	.xword	.LANCHOR1
	.align	3
.LC211:
	.xword	.LC86
	.align	3
.LC212:
	.xword	.LC123
	.align	3
.LC213:
	.xword	g_HalDisable
	.align	3
.LC214:
	.xword	g_HwMem
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_MakeDecReport
	.type	VDMHAL_V5R6C1_MakeDecReport, %function
VDMHAL_V5R6C1_MakeDecReport:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L583
	ldr	x23, [x19, 8]
	ldr	w21, [x19]
	ldr	w22, [x19, 16]
	cbz	x23, .L584
	sxtw	x22, w22
	ldr	x20, .LC223
	lsl	x0, x22, 6
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x1, x0, x22
	add	x0, x0, x1, lsl 2
	ldr	x0, [x20, x0]
	cbz	x0, .L557
	ldr	x2, .LC224
	add	x0, x2, 4
	add	x2, x2, 128
	ldr	w1, [x2, -128]
	cmp	w1, 1
	bne	.L560
	b	.L572
	.p2align 3
.L586:
	cmp	x0, x2
	beq	.L585
.L560:
	ldr	w1, [x0]
	add	x0, x0, 4
	cmp	w1, 1
	bne	.L586
.L572:
	mov	w19, w1
.L558:
	ldr	x3, .LC228
	mov	x2, 820
	mov	w1, 0
	mov	x0, x23
	ldr	x3, [x3, 96]
	blr	x3
	lsl	x0, x22, 6
	lsl	x1, x22, 2
	sub	x0, x0, x22
	sub	x1, x1, x22
	lsl	x0, x0, 2
	lsl	x2, x1, 4
	sub	x3, x0, x22
	sub	x1, x2, x1
	ldr	x4, .LC229
	add	x2, x0, x3, lsl 2
	add	x2, x20, x2
	add	x1, x4, x1, lsl 2
	ldr	w0, [x2, 40]
	str	w0, [x23, 4]
	ldr	w1, [x1, 4]
	ubfx	x0, x1, 17, 2
	cmp	w0, 1
	beq	.L573
	and	w1, w1, 131072
	cmp	w1, wzr
	ccmp	w21, 3, 0, ne
	cset	w1, ne
.L561:
	lsl	x0, x22, 2
	str	w1, [x23]
	sub	x0, x0, x22
	cmp	w21, wzr
	lsl	x1, x0, 4
	ccmp	w21, 15, 4, ne
	sub	x0, x1, x0
	add	x0, x4, x0, lsl 2
	ldr	w2, [x0, 4]
	and	w2, w2, 131071
	str	w2, [x23, 12]
	beq	.L587
.L562:
	cmp	w2, 200
	bhi	.L588
.L564:
	lsl	x0, x22, 6
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x1, x0, x22
	add	x0, x0, x1, lsl 2
	add	x20, x20, x0
	ldr	w21, [x20, 56]
	mov	w0, w21
	bl	MEM_Phy2Vir
	cbz	x0, .L589
	lsl	x3, x22, 2
	ldr	x19, .LC234
	sub	x3, x3, x22
	ldr	w2, [x23, 12]
	mov	x1, x0
	add	x20, x22, x3, lsl 3
	lsl	w2, w2, 2
	add	x0, x19, x20, lsl 7
	bl	VDMHAL_V5R6C1_ReadMsgSlot
	ldr	w0, [x23, 12]
	cbz	w0, .L569
	sub	w2, w0, #1
	mov	x5, 22
	add	x1, x23, 18
	mov	w0, 2
	add	x5, x5, x2, uxtw 2
	lsl	x3, x20, 5
	add	x5, x23, x5
	.p2align 2
.L568:
	sub	w2, w0, #1
	add	x4, x3, x0, uxtw
	add	x2, x3, x2
	add	w0, w0, 4
	ldr	w2, [x19, x2, lsl 2]
	strh	w2, [x1, -2]
	ldr	w2, [x19, x4, lsl 2]
	strh	w2, [x1], 4
	cmp	x5, x1
	bne	.L568
.L569:
	mov	w0, 6
	bl	IsDprintTypeEnable
	cbnz	w0, .L590
.L555:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L587:
	cmp	w19, 1
	beq	.L591
	ldr	x1, .LC230
	ldrb	w1, [x1]
	cbnz	w1, .L562
	ldrb	w0, [x0, 19]
	and	w0, w0, 3
	cmp	w0, 2
	bne	.L562
	mov	w0, 1
	strh	wzr, [x23, 16]
	str	w0, [x23, 12]
	mov	w0, 0
	strh	wzr, [x23, 18]
	b	.L555
	.p2align 3
.L585:
	mov	w19, 0
	b	.L558
	.p2align 3
.L590:
	ldr	x1, .LC236
	mov	w0, 6
	ldr	w2, [x23, 12]
	mov	w20, 0
	bl	dprint_vfmw
	mov	w2, w21
	ldr	x1, .LC238
	lsl	x21, x22, 2
	mov	w0, 6
	sub	x21, x21, x22
	bl	dprint_vfmw
	ldr	x24, .LC240
	add	x21, x22, x21, lsl 3
	lsl	x21, x21, 5
	.p2align 2
.L570:
	add	w1, w20, 3
	add	w3, w20, 2
	add	w0, w20, 1
	add	x7, x21, x20, uxtw
	add	x1, x21, x1
	add	x3, x21, x3
	add	x0, x21, x0
	mov	w2, w20
	add	w20, w20, 4
	ldr	w6, [x19, x1, lsl 2]
	mov	x1, x24
	ldr	w5, [x19, x3, lsl 2]
	ldr	w4, [x19, x0, lsl 2]
	mov	w0, 6
	ldr	w3, [x19, x7, lsl 2]
	bl	dprint_vfmw
	ldr	w0, [x23, 12]
	lsl	w0, w0, 2
	sub	w0, w0, #3
	cmp	w0, w20
	bhi	.L570
	ldr	x1, .LC242
	mov	w0, 6
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L573:
	mov	w1, 0
	b	.L561
	.p2align 3
.L588:
	ldr	x1, .LC232
	mov	w3, 200
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x23, 12]
	b	.L564
	.p2align 3
.L591:
	ldr	w0, [x0, 16]
	ubfx	x0, x0, 21, 2
	cmp	w0, 2
	bne	.L562
	strh	wzr, [x23, 16]
	mov	w0, 0
	strh	wzr, [x23, 18]
	str	w19, [x23, 12]
	b	.L555
.L589:
	ldr	x2, .LC219
	ldr	x3, .LC233
	ldr	x1, .LC220
	add	x2, x2, 328
	bl	dprint_vfmw
	mov	w0, -1
	b	.L555
.L557:
	ldr	x2, .LC219
	ldr	x3, .LC225
.L581:
	ldr	x1, .LC220
	mov	w0, 0
	add	x2, x2, 328
	bl	dprint_vfmw
	mov	w0, -1
	b	.L555
.L584:
	ldr	x2, .LC219
	ldr	x3, .LC222
	b	.L581
.L583:
	ldr	x2, .LC219
	ldr	x3, .LC218
	b	.L581
	.size	VDMHAL_V5R6C1_MakeDecReport, .-VDMHAL_V5R6C1_MakeDecReport
	.align	3
.LC218:
	.xword	.LC217
	.align	3
.LC219:
	.xword	.LANCHOR1
	.align	3
.LC220:
	.xword	.LC6
	.align	3
.LC222:
	.xword	.LC221
	.align	3
.LC223:
	.xword	g_HwMem
	.align	3
.LC224:
	.xword	g_DSPState
	.align	3
.LC225:
	.xword	.LC160
	.align	3
.LC228:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC229:
	.xword	g_BackUp
	.align	3
.LC230:
	.xword	g_not_allow_H264FullPictureRepair_flag
	.align	3
.LC232:
	.xword	.LC231
	.align	3
.LC233:
	.xword	.LC188
	.align	3
.LC234:
	.xword	g_UpMsg
	.align	3
.LC236:
	.xword	.LC235
	.align	3
.LC238:
	.xword	.LC237
	.align	3
.LC240:
	.xword	.LC239
	.align	3
.LC242:
	.xword	.LC241
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_PrepareRepair
	.type	VDMHAL_V5R6C1_PrepareRepair, %function
VDMHAL_V5R6C1_PrepareRepair:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	w22, w0
	mov	x0, x30
	sxtw	x19, w3
	mov	x23, x1
	mov	w26, w2
	mov	x24, x4
	bl	_mcount
	ldr	x25, .LC243
	lsl	x0, x19, 6
	cmp	w19, wzr
	sub	x0, x0, x19
	mov	x21, x19
	lsl	x0, x0, 2
	sub	x20, x0, x19
	add	x20, x0, x20, lsl 2
	add	x27, x20, x25
	bgt	.L603
	ldr	x0, [x20, x25]
	cbz	x0, .L604
	cbz	w26, .L605
.L597:
	cmp	w26, 1
	mov	w20, 0
	beq	.L606
.L594:
	mov	w0, w20
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L604:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L596
	str	x0, [x20, x25]
	cbnz	w26, .L597
	.p2align 2
.L605:
	lsl	x0, x19, 3
	ldr	x25, .LC248
	sub	x0, x0, x19
	lsl	x0, x0, 3
	sub	x0, x0, x19
	lsl	x0, x0, 1
	sub	x0, x0, x19
	add	x0, x25, x0, lsl 4
	ldr	w1, [x0, 44]
	cmp	w1, wzr
	ble	.L598
	cmp	w22, 6
	bne	.L599
	ldrb	w1, [x23, 17]
	mov	w2, 0
	cmp	w1, 1
	csel	w1, w1, w2, eq
	str	w1, [x0, 924]
.L599:
	mov	x4, x24
	mov	w3, w21
	mov	x2, x23
	mov	x1, x27
	mov	w0, w22
	mov	w20, 0
	bl	VDMHAL_V5R6C1_CfgRpReg
	lsl	x0, x19, 3
	mov	w2, w21
	sub	x0, x0, x19
	mov	x1, x27
	lsl	x0, x0, 3
	sub	x0, x0, x19
	lsl	x0, x0, 1
	sub	x0, x0, x19
	add	x0, x25, x0, lsl 4
	bl	VDMHAL_V5R6C1_CfgRpMsg
	ldr	x27, [sp, 80]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L606:
	cmp	w22, 6
	bne	.L601
	ldrb	w0, [x23, 17]
	cmp	w0, 1
	bne	.L601
	lsl	x0, x19, 3
	ldr	x25, .LC248
	sub	x0, x0, x19
	lsl	x0, x0, 3
	sub	x0, x0, x19
	lsl	x0, x0, 1
	sub	x19, x0, x19
	lsl	x19, x19, 4
	add	x0, x25, x19
	ldr	w1, [x0, 916]
	cmp	w1, wzr
	ble	.L601
	mov	w1, 2
	mov	x4, x24
	mov	w3, w21
	mov	x2, x23
	str	w1, [x0, 924]
	mov	x1, x27
	mov	w0, w22
	bl	VDMHAL_V5R6C1_CfgRpReg
	add	x0, x19, 872
	mov	w2, w21
	mov	x1, x27
	add	x0, x25, x0
	bl	VDMHAL_V5R6C1_CfgRpMsg
	ldr	x27, [sp, 80]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L603:
	ldr	x2, .LC244
	mov	w4, 0
	ldr	x1, .LC245
	mov	w3, w19
	add	x2, x2, 360
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L594
	.p2align 3
.L601:
	ldr	x1, .LC252
	mov	w0, 0
	mov	w20, 0
	bl	dprint_vfmw
	b	.L594
.L598:
	ldr	x1, .LC250
	mov	w0, 0
	mov	w20, 0
	bl	dprint_vfmw
	b	.L594
.L596:
	ldr	x1, .LC247
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L594
	.size	VDMHAL_V5R6C1_PrepareRepair, .-VDMHAL_V5R6C1_PrepareRepair
	.align	3
.LC243:
	.xword	g_HwMem
	.align	3
.LC244:
	.xword	.LANCHOR1
	.align	3
.LC245:
	.xword	.LC86
	.align	3
.LC247:
	.xword	.LC246
	.align	3
.LC248:
	.xword	g_RepairParam
	.align	3
.LC250:
	.xword	.LC249
	.align	3
.LC252:
	.xword	.LC251
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_StartHwRepair
	.type	VDMHAL_V5R6C1_StartHwRepair, %function
VDMHAL_V5R6C1_StartHwRepair:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	sxtw	x20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x21, .LC253
	ldrb	w4, [x21]
	cmp	w4, 1
	bne	.L631
	cmp	w20, wzr
	ble	.L632
	ldr	x22, .LC255
	mov	w3, w20
	ldr	x23, .LC256
	mov	w0, 32
	add	x2, x22, 392
	mov	x1, x23
	bl	dprint_vfmw
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L615
	mov	x0, x19
	mov	w3, -2
	mov	w2, 36
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L628
.L610:
	cbz	x19, .L633
.L624:
	ldr	x1, .LC259
	sbfiz	x0, x20, 6, 32
	mov	w2, 1
	str	w2, [x19, 4]
	add	x1, x1, x0
	mov	x0, x19
	ldr	w1, [x1, 8]
	str	w1, [x19, 8]
	strb	w20, [x19]
	strb	w2, [x19, 2]
	bl	VDH_PostTask
.L607:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L632:
	sxtw	x0, w20
	ldr	x3, .LC254
	lsl	x1, x0, 6
	mov	w4, 67108864
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x2, x1, x0
	add	x1, x1, x2, lsl 2
	ldr	x1, [x3, x1]
	str	w4, [x1, 8]
.L613:
	lsl	x1, x0, 6
	mov	w2, -2
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x0, x1, x0
	add	x0, x1, x0, lsl 2
	ldr	x0, [x3, x0]
	str	w2, [x0, 36]
.L611:
	ldr	x0, .LC260
	ldr	x0, [x0, 224]
	blr	x0
	cmp	w20, wzr
	ble	.L627
	ldr	x22, .LC255
	ldr	x23, .LC256
.L620:
	add	x22, x22, 408
	mov	w3, w20
	mov	x2, x22
	mov	x1, x23
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	mov	w3, w20
	mov	x2, x22
	mov	x1, x23
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x22
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	b	.L607
	.p2align 3
.L609:
	cmp	w20, wzr
	ble	.L625
	ldr	x22, .LC255
	ldr	x23, .LC256
.L615:
	mov	w4, 1
	mov	w3, w20
	add	x2, x22, 392
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	ldrb	w0, [x21]
	cmp	w0, 1
	bne	.L610
.L628:
	ldr	x0, .LC260
	ldr	x0, [x0, 224]
	blr	x0
	b	.L620
	.p2align 3
.L631:
	mov	x0, x19
	mov	w3, 67108864
	mov	w2, 8
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L609
	mov	x0, x19
	mov	w3, -2
	mov	w2, 36
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L611
	cbnz	x19, .L624
.L633:
	ldr	x2, .LC255
	mov	x3, 0
	ldr	x1, .LC258
	mov	w0, 0
	add	x2, x2, 408
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L627:
	lsl	x0, x20, 6
	ldr	x1, .LC254
	sub	x0, x0, x20
	mov	w3, 1
	lsl	x0, x0, 2
	sub	x20, x0, x20
	add	x0, x0, x20, lsl 2
	ldr	x2, [x1, x0]
	str	wzr, [x2]
	ldr	x2, [x1, x0]
	str	w3, [x2]
	ldr	x0, [x1, x0]
	str	wzr, [x0]
	b	.L607
.L625:
	ldr	x3, .LC254
	sxtw	x0, w20
	b	.L613
	.size	VDMHAL_V5R6C1_StartHwRepair, .-VDMHAL_V5R6C1_StartHwRepair
	.align	3
.LC253:
	.xword	g_HalDisable
	.align	3
.LC254:
	.xword	g_HwMem
	.align	3
.LC255:
	.xword	.LANCHOR1
	.align	3
.LC256:
	.xword	.LC99
	.align	3
.LC258:
	.xword	.LC257
	.align	3
.LC259:
	.xword	g_VdmDrvParam
	.align	3
.LC260:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_CalVdhClkSkip
	.type	VDMHAL_V5R6C1_CalVdhClkSkip, %function
VDMHAL_V5R6C1_CalVdhClkSkip:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x0, x30
	bl	_mcount
	ldr	x24, .LC262
	ldr	w28, [x24, 128]
	tbnz	w28, #31, .L666
	ldr	x25, .LC265
	add	x20, x24, 132
	ldr	x27, .LC268
	add	x24, x24, 256
	ldr	x26, .LC267
	mov	w23, 30
	mov	w22, 0
	mov	w21, 0
	add	x25, x25, 440
	mov	w19, 0
	b	.L637
	.p2align 3
.L669:
	mov	w3, w28
	mov	x2, x25
	mov	x1, x26
	mov	w0, 1
	bl	dprint_vfmw
.L639:
	cmp	x24, x20
	beq	.L667
.L656:
	ldr	w28, [x20], 4
	tbnz	w28, #31, .L668
.L637:
	mov	w0, w28
	bl	VCTRL_IsChanActive
	cbnz	w0, .L669
	mov	w0, w28
	bl	FSP_GetInst
	cbz	x0, .L640
	ldp	w1, w0, [x0, 40]
	adds	w19, w1, 15
	add	w1, w1, 30
	add	w21, w0, 30
	csel	w19, w1, w19, mi
	adds	w0, w0, 15
	asr	w19, w19, 4
	csel	w0, w21, w0, mi
	asr	w21, w0, 4
.L640:
	ldr	x1, [x27, w28, sxtw 3]
	mov	w0, w28
	ldr	w1, [x1, 1568]
	cmp	w1, 31
	csel	w23, w23, w1, lt
	bl	VCTRL_GetVidStd
	cmp	w0, 17
	bls	.L670
.L659:
	cmp	x24, x20
	mov	w22, 0
	bne	.L656
.L667:
	lsl	w0, w22, 2
	mov	w3, 23813
	sub	w22, w0, w22
	movk	w3, 0xdb4f, lsl 16
	lsl	w1, w22, 6
	mov	w0, 32
	mov	w2, 25
	umull	x1, w1, w3
	ldp	x19, x20, [sp, 16]
	lsr	x1, x1, 53
	sub	w0, w0, w1
	cmp	w0, w2
	csel	w0, w0, w2, le
	cmp	w0, wzr
	csel	w0, w0, wzr, ge
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L670:
	ldr	x1, .LC269
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx643
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx643:
	.section	.rodata
	.align	0
	.align	2
.L643:
	.byte	(.L652 - .Lrtx643) / 4
	.byte	(.L652 - .Lrtx643) / 4
	.byte	(.L652 - .Lrtx643) / 4
	.byte	(.L652 - .Lrtx643) / 4
	.byte	(.L659 - .Lrtx643) / 4
	.byte	(.L652 - .Lrtx643) / 4
	.byte	(.L652 - .Lrtx643) / 4
	.byte	(.L659 - .Lrtx643) / 4
	.byte	(.L652 - .Lrtx643) / 4
	.byte	(.L652 - .Lrtx643) / 4
	.byte	(.L652 - .Lrtx643) / 4
	.byte	(.L652 - .Lrtx643) / 4
	.byte	(.L652 - .Lrtx643) / 4
	.byte	(.L652 - .Lrtx643) / 4
	.byte	(.L659 - .Lrtx643) / 4
	.byte	(.L653 - .Lrtx643) / 4
	.byte	(.L652 - .Lrtx643) / 4
	.byte	(.L652 - .Lrtx643) / 4
	.text
	.p2align 3
.L652:
	mul	w22, w19, w21
	mul	w22, w22, w23
	b	.L639
	.p2align 3
.L668:
	lsl	w1, w22, 2
	mov	w0, 23813
	sub	w22, w1, w22
	movk	w0, 0xdb4f, lsl 16
	lsl	w22, w22, 6
	mov	w1, 32
	mov	w2, 25
	umull	x0, w22, w0
	lsr	x0, x0, 53
	sub	w0, w1, w0
	cmp	w0, w2
	csel	w0, w0, w2, le
	cmp	w0, wzr
	csel	w0, w0, wzr, ge
.L635:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L653:
	mul	w22, w19, w21
	mul	w22, w22, w23
	lsl	w22, w22, 1
	b	.L639
.L666:
	mov	w0, 25
	b	.L635
	.size	VDMHAL_V5R6C1_CalVdhClkSkip, .-VDMHAL_V5R6C1_CalVdhClkSkip
	.align	3
.LC262:
	.xword	g_ChanCtx
	.align	3
.LC265:
	.xword	.LANCHOR1
	.align	3
.LC267:
	.xword	.LC266
	.align	3
.LC268:
	.xword	s_pstVfmwChan
	.align	3
.LC269:
	.xword	.L643
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_GetVdmClk
	.type	VDMHAL_V5R6C1_GetVdmClk, %function
VDMHAL_V5R6C1_GetVdmClk:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w20, 3
	bls	.L679
.L672:
	ldr	x0, .LC272
	sbfiz	x19, x19, 6, 32
	mov	w1, 500
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L679:
	ldr	x0, .LC271
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx674
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx674:
	.section	.rodata
	.align	0
	.align	2
.L674:
	.byte	(.L672 - .Lrtx674) / 4
	.byte	(.L675 - .Lrtx674) / 4
	.byte	(.L676 - .Lrtx674) / 4
	.byte	(.L677 - .Lrtx674) / 4
	.text
	.p2align 3
.L676:
	ldr	x0, .LC272
	sbfiz	x19, x19, 6, 32
	mov	w1, 100
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L675:
	ldr	x0, .LC272
	sbfiz	x19, x19, 6, 32
	mov	w1, 540
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L677:
	ldr	x0, .LC272
	sbfiz	x19, x19, 6, 32
	mov	w1, 600
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMHAL_V5R6C1_GetVdmClk, .-VDMHAL_V5R6C1_GetVdmClk
	.align	3
.LC271:
	.xword	.L674
	.align	3
.LC272:
	.xword	g_VdmDrvParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_StartHwDecode
	.type	VDMHAL_V5R6C1_StartHwDecode, %function
VDMHAL_V5R6C1_StartHwDecode:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	mov	w0, 8
	cmp	w20, wzr
	str	w0, [x29, 92]
	ble	.L681
	ldr	x2, .LC273
	mov	w4, 0
	ldr	x1, .LC274
	mov	w3, w20
	add	x2, x2, 472
	mov	w0, 0
	bl	dprint_vfmw
.L680:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L681:
	add	x0, x29, 92
	bl	HI_DRV_SYS_GetChipPackageType
	ldr	x22, .LC275
	ldr	w0, [x29, 92]
	ldrb	w1, [x22]
	cmp	w0, wzr
	cset	w21, ne
	cmp	w1, 1
	bne	.L720
	ldr	x0, .LC276
	ldr	x2, [x0]
	ldr	w0, [x2, 120]
	ubfx	x3, x0, 8, 2
	cmp	w3, w21
	beq	.L713
	bfi	w0, w21, 8, 2
	str	w0, [x2, 120]
.L713:
	ldr	x0, .LC277
	ldr	x23, .LC278
	ldrb	w0, [x0,w21,uxtw]
	adr	x2, .Lrtx688
	add	x0, x2, w0, sxtb #2
	br	x0
.Lrtx688:
	.section	.rodata
	.align	0
	.align	2
.L688:
	.byte	(.L687 - .Lrtx688) / 4
	.byte	(.L689 - .Lrtx688) / 4
	.byte	(.L690 - .Lrtx688) / 4
	.byte	(.L691 - .Lrtx688) / 4
	.text
	.p2align 3
.L690:
	sxtw	x21, w20
	mov	w2, 100
	add	x0, x23, x21, lsl 6
	str	w2, [x0, 16]
.L692:
	add	x0, x23, x21, lsl 6
	ldr	x2, .LC279
	cmp	w1, 1
	ldr	w24, [x0, 8]
	ldr	x0, [x2, w24, sxtw 3]
	ldr	w25, [x0, 1272]
	bne	.L721
	ldr	x0, .LC276
	ldr	x0, [x0]
	ldr	w1, [x0, 120]
	and	w1, w1, -258049
	str	w1, [x0, 120]
	ldr	w1, [x0, 120]
	orr	w1, w1, 131072
	str	w1, [x0, 120]
.L694:
	mov	w0, 12
	mov	x3, x19
	mov	w2, w20
	mov	w1, 3
	bl	SCD_ConfigReg
	ldrb	w0, [x22]
	cmp	w0, 1
	beq	.L722
	mov	w1, 2
	mov	x0, x19
	mov	w3, -1431655766
	mov	w2, 156
	bl	VDH_Record_RegData
	ldr	x1, .LC280
	ldrb	w0, [x22]
	ldr	w1, [x1]
	cmp	w1, 1
	beq	.L723
.L696:
	mov	w3, 0
.L695:
	cmp	w0, 1
	beq	.L724
	mov	x0, x19
	mov	w2, 61472
	mov	w1, 2
	bl	VDH_Record_RegData
	cmp	w25, 1
	ldrb	w0, [x22]
	beq	.L725
.L699:
	mov	w3, -2
.L698:
	cmp	w0, 1
	beq	.L726
	mov	x0, x19
	mov	w2, 36
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x22]
	cmp	w0, 1
	beq	.L727
	cbz	x19, .L728
	mov	w0, 1
	strb	w20, [x19]
	stp	w0, w24, [x19, 4]
	mov	x0, x19
	bl	VDH_PostTask
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L725:
	mov	w3, -6
	b	.L698
	.p2align 3
.L723:
	mov	w3, 15
	b	.L695
	.p2align 3
.L689:
	sxtw	x21, w20
	mov	w2, 540
	add	x0, x23, x21, lsl 6
	str	w2, [x0, 16]
	b	.L692
	.p2align 3
.L687:
	sxtw	x21, w20
	mov	w2, 500
	add	x0, x23, x21, lsl 6
	str	w2, [x0, 16]
	b	.L692
	.p2align 3
.L691:
	sxtw	x21, w20
	mov	w2, 600
	add	x0, x23, x21, lsl 6
	str	w2, [x0, 16]
	b	.L692
	.p2align 3
.L720:
	mov	w1, 0
	mov	w3, w21
	mov	w2, 0
	mov	x0, x19
	bl	VDH_Record_RegData
	ldrb	w1, [x22]
	b	.L713
	.p2align 3
.L721:
	mov	w3, 0
	mov	w2, 1
	mov	w1, 0
	mov	x0, x19
	bl	VDH_Record_RegData
	b	.L694
	.p2align 3
.L722:
	ldr	x2, .LC280
	lsl	x1, x21, 6
	sub	x1, x1, x21
	ldr	x26, .LC281
	lsl	x1, x1, 2
	ldr	w2, [x2]
	cmp	w2, 1
	sub	x2, x1, x21
	add	x1, x1, x2, lsl 2
	mov	w2, -1431655766
	ldr	x1, [x26, x1]
	str	w2, [x1, 156]
	bne	.L696
	mov	w3, 15
	b	.L697
	.p2align 3
.L726:
	ldr	x26, .LC281
.L700:
	lsl	x1, x21, 6
	ldr	x19, .LC282
	sub	x1, x1, x21
	mov	x0, 30
	lsl	x1, x1, 2
	sub	x2, x1, x21
	add	x1, x1, x2, lsl 2
	ldr	x1, [x26, x1]
	str	w3, [x1, 36]
	ldr	x1, [x19, 232]
	blr	x1
	ldr	x0, [x19, 224]
	blr	x0
.L703:
	lsl	x0, x21, 6
	mov	w2, 1
	sub	x1, x0, x21
	add	x23, x23, x0
	lsl	x0, x1, 2
	ldr	x3, .LC284
	sub	x21, x0, x21
	mov	w1, 4
	add	x21, x0, x21, lsl 2
	ldr	x0, [x26, x21]
	str	wzr, [x0]
	ldr	x0, [x26, x21]
	str	w2, [x0]
	ldr	x0, [x26, x21]
	str	wzr, [x0]
	ldr	w2, [x23, 8]
	mov	w0, w2
	ldr	w2, [x3, w2, sxtw 2]
	bl	VDEC_Lowdelay_Event_Time
	b	.L680
	.p2align 3
.L724:
	ldr	x26, .LC281
.L697:
	lsl	x0, x21, 6
	cmp	w25, 1
	sub	x0, x0, x21
	lsl	x0, x0, 2
	sub	x1, x0, x21
	add	x0, x0, x1, lsl 2
	ldr	x0, [x26, x0]
	add	x0, x0, 61440
	str	w3, [x0, 32]
	beq	.L712
	mov	w0, 1
	b	.L699
	.p2align 3
.L728:
	ldr	x2, .LC273
	mov	x3, 0
	ldr	x1, .LC283
	mov	w0, 0
	add	x2, x2, 472
	bl	dprint_vfmw
	b	.L680
	.p2align 3
.L712:
	mov	w3, -6
	b	.L700
.L727:
	ldr	x19, .LC282
	mov	x0, 30
	ldr	x1, [x19, 232]
	blr	x1
	ldr	x0, [x19, 224]
	blr	x0
	ldr	x26, .LC281
	b	.L703
	.size	VDMHAL_V5R6C1_StartHwDecode, .-VDMHAL_V5R6C1_StartHwDecode
	.align	3
.LC273:
	.xword	.LANCHOR1
	.align	3
.LC274:
	.xword	.LC86
	.align	3
.LC275:
	.xword	g_HalDisable
	.align	3
.LC276:
	.xword	g_pstRegCrg
	.align	3
.LC277:
	.xword	.L688
	.align	3
.LC278:
	.xword	g_VdmDrvParam
	.align	3
.LC279:
	.xword	s_pstVfmwChan
	.align	3
.LC280:
	.xword	mask_mmu_err_int
	.align	3
.LC281:
	.xword	g_HwMem
	.align	3
.LC282:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC283:
	.xword	.LC257
	.align	3
.LC284:
	.xword	g_LowDelaySeqIndex
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_GetCharacter
	.type	VDMHAL_V5R6C1_GetCharacter, %function
VDMHAL_V5R6C1_GetCharacter:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x2, .LC285
	mov	w3, 15
	ldr	x0, .LC286
	mov	w1, 4
	str	w3, [x2]
	str	w1, [x0]
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V5R6C1_GetCharacter, .-VDMHAL_V5R6C1_GetCharacter
	.align	3
.LC285:
	.xword	g_VdmCharacter
	.align	3
.LC286:
	.xword	g_eVdmVersion
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_WriteBigTitle1DYuv
	.type	VDMHAL_V5R6C1_WriteBigTitle1DYuv, %function
VDMHAL_V5R6C1_WriteBigTitle1DYuv:
	stp	x29, x30, [sp, -208]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	str	x0, [x29, 112]
	mov	x0, x30
	mov	w21, w3
	mov	x22, x1
	mov	w19, w2
	str	w4, [x29, 108]
	bl	_mcount
	ubfx	x0, x21, 29, 2
	stp	xzr, xzr, [x29, 144]
	stp	xzr, xzr, [x29, 160]
	stp	xzr, xzr, [x29, 176]
	stp	xzr, xzr, [x29, 192]
	cmp	w0, 1
	beq	.L774
	mov	w20, 2
	cmp	w0, w20
	csinc	w20, w20, wzr, ne
.L731:
	ldr	x0, [x29, 112]
	cbz	x0, .L730
	ldr	x0, .LC288
	mov	w4, 0
	add	x3, x29, 144
	mov	w2, 4194304
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L734
	ldr	x0, .LC292
	mov	w4, 0
	add	x3, x29, 176
	mov	w2, 4194304
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L734
	add	w19, w19, 15
	add	w21, w21, 15
	and	w19, w19, -16
	and	w0, w21, -16
	add	w1, w19, 255
	mov	w3, w0
	and	w1, w1, -256
	add	w0, w0, 62
	lsl	w1, w1, 4
	ldr	x25, [x29, 184]
	mov	w2, w1
	adds	w1, w3, 31
	csel	w0, w0, w1, mi
	add	w21, w2, 15
	cmp	w2, wzr
	asr	w0, w0, 5
	csel	w21, w21, w2, lt
	cmp	w20, wzr
	asr	w21, w21, 4
	ccmp	w20, 3, 4, ne
	stp	w2, w3, [x29, 124]
	mul	w21, w0, w21
	add	x21, x22, x21, sxtw
	bne	.L735
	lsr	w1, w3, 1
	lsr	w0, w19, 1
	str	w1, [x29, 120]
	add	x1, x25, 2097152
	str	w0, [x29, 104]
	str	x1, [x29, 136]
	ldr	x28, .LC293
	ldr	x20, [x29, 152]
	cbz	w3, .L737
	mov	w27, 0
	str	wzr, [x29, 132]
	.p2align 2
.L736:
	cbz	w19, .L739
	ldr	w0, [x29, 124]
	lsr	w23, w27, 4
	ldr	w24, [x29, 132]
	mov	w26, 0
	mul	w0, w23, w0
	ubfiz	x23, x27, 8, 4
	add	x23, x0, x23
	.p2align 2
.L738:
	lsr	w1, w26, 8
	add	x0, x24, x26, uxtw
	ubfiz	x1, x1, 12, 20
	ldr	x5, [x28, 104]
	add	x1, x1, x23
	mov	x2, 256
	add	x1, x22, x1
	add	x0, x20, x0
	add	w26, w26, 256
	blr	x5
	cmp	w19, w26
	bhi	.L738
.L739:
	ldr	w0, [x29, 132]
	add	w27, w27, 1
	add	w0, w0, w19
	str	w0, [x29, 132]
	ldr	w0, [x29, 128]
	cmp	w0, w27
	bne	.L736
.L737:
	ldr	w0, [x29, 128]
	ldr	x3, [x28, 88]
	ldr	x2, [x29, 112]
	mul	w1, w19, w0
	mov	x0, x20
	blr	x3
	ldr	w0, [x29, 120]
	cbz	w0, .L829
	ldr	w1, [x29, 124]
	mov	w26, 0
	mov	w24, 0
	asr	w0, w1, 1
	str	w0, [x29, 132]
	.p2align 2
.L743:
	cbz	w19, .L745
	ldr	w0, [x29, 132]
	lsr	w22, w24, 3
	uxtw	x23, w26
	mov	w27, 0
	mul	w0, w22, w0
	ubfiz	x22, x24, 8, 3
	add	x22, x0, x22
	.p2align 2
.L742:
	lsr	w1, w27, 8
	add	x0, x23, x27, uxtw
	ubfiz	x1, x1, 11, 21
	ldr	x5, [x28, 104]
	add	x1, x1, x22
	mov	x2, 256
	add	x1, x21, x1
	add	x0, x20, x0
	add	w27, w27, 256
	blr	x5
	cmp	w19, w27
	bhi	.L742
.L745:
	ldr	w0, [x29, 120]
	add	w24, w24, 1
	add	w26, w26, w19
	cmp	w0, w24
	bne	.L743
	ldr	w0, [x29, 108]
	cmp	w0, 1
	beq	.L830
.L771:
	ldr	w0, [x29, 108]
	cbnz	w0, .L748
	ldr	x3, [x28, 96]
	mov	x2, 1048576
	ldr	x0, [x29, 136]
	mov	w1, 128
	blr	x3
	ldr	x3, [x28, 96]
	mov	x2, 1048576
	mov	w1, 128
	mov	x0, x25
	blr	x3
.L748:
	ldr	w0, [x29, 104]
	ldr	w1, [x29, 120]
.L824:
	mul	w19, w0, w1
	ldr	x20, [x29, 112]
	mov	x0, x25
	ldr	x3, [x28, 88]
	mov	w1, w19
	mov	x2, x20
	blr	x3
	ldr	x3, [x28, 88]
	mov	x2, x20
	ldr	x0, [x29, 136]
	mov	w1, w19
	blr	x3
	ldr	w0, [x29, 160]
	ldr	x1, [x29, 152]
	bl	MEM_ReleaseMemBlock
	ldr	x3, [x28, 96]
	mov	x2, 32
	mov	w1, 0
	add	x0, x29, 144
	blr	x3
	ldr	w0, [x29, 192]
	ldr	x1, [x29, 184]
	bl	MEM_ReleaseMemBlock
	ldr	x3, [x28, 96]
	mov	x2, 32
	mov	w1, 0
	add	x0, x29, 176
	blr	x3
.L730:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
	.p2align 3
.L734:
	ldr	x1, .LC290
	mov	w0, 1
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
	.p2align 3
.L774:
	mov	w20, 0
	b	.L731
.L735:
	cmp	w20, 1
	ldr	w1, [x29, 128]
	cset	w0, ne
	str	w0, [x29, 120]
	cmp	w1, w0
	lsr	w0, w19, 1
	str	w0, [x29, 104]
	lsr	w0, w1, 1
	str	w0, [x29, 132]
	add	x0, x25, 2097152
	str	x0, [x29, 136]
	ldr	x28, .LC293
	ldr	x20, [x29, 152]
	bls	.L753
	ldr	w27, [x29, 120]
	.p2align 2
.L755:
	cbz	w19, .L756
	ldr	w0, [x29, 124]
	lsr	w24, w27, 4
	lsr	w23, w27, 1
	mov	w26, 0
	mul	w0, w24, w0
	mul	w23, w23, w19
	ubfiz	x24, x27, 8, 4
	add	x24, x0, x24
	.p2align 2
.L754:
	lsr	w1, w26, 8
	add	x0, x23, x26, uxtw
	ubfiz	x1, x1, 12, 20
	ldr	x5, [x28, 104]
	add	x1, x1, x24
	mov	x2, 256
	add	x1, x22, x1
	add	x0, x20, x0
	add	w26, w26, 256
	blr	x5
	cmp	w19, w26
	bhi	.L754
.L756:
	ldr	w0, [x29, 128]
	add	w27, w27, 2
	cmp	w0, w27
	bhi	.L755
.L753:
	ldr	w0, [x29, 128]
	ldr	x3, [x28, 88]
	ldr	x2, [x29, 112]
	mul	w1, w19, w0
	mov	x0, x20
	lsr	w1, w1, 1
	blr	x3
	ldr	w0, [x29, 132]
	cbz	w0, .L831
	ldr	w1, [x29, 124]
	mov	w26, 0
	mov	w24, 0
	asr	w0, w1, 1
	str	w0, [x29, 128]
	.p2align 2
.L760:
	cbz	w19, .L762
	ldr	w0, [x29, 128]
	lsr	w22, w24, 3
	uxtw	x23, w26
	mov	w27, 0
	mul	w0, w22, w0
	ubfiz	x22, x24, 8, 3
	add	x22, x0, x22
	.p2align 2
.L759:
	lsr	w1, w27, 8
	add	x0, x23, x27, uxtw
	ubfiz	x1, x1, 11, 21
	ldr	x5, [x28, 104]
	add	x1, x1, x22
	mov	x2, 256
	add	x1, x21, x1
	add	x0, x20, x0
	add	w27, w27, 256
	blr	x5
	cmp	w19, w27
	bhi	.L759
.L762:
	ldr	w0, [x29, 132]
	add	w24, w24, 1
	add	w26, w26, w19
	cmp	w0, w24
	bne	.L760
	ldr	w0, [x29, 108]
	cmp	w0, 1
	beq	.L832
	ldr	w0, [x29, 108]
	cbnz	w0, .L765
	ldr	w1, [x29, 120]
	ldr	w0, [x29, 132]
	cmp	w0, w1
	bls	.L768
	.p2align 2
.L769:
	ldr	w0, [x29, 120]
	ldr	w1, [x29, 132]
	add	w0, w0, 2
	str	w0, [x29, 120]
	cmp	w1, w0
	bhi	.L769
.L768:
	ldr	x3, [x28, 96]
	mov	x2, 1048576
	ldr	x0, [x29, 136]
	mov	w1, 128
	blr	x3
	ldr	x3, [x28, 96]
	mov	x2, 1048576
	mov	w1, 128
	mov	x0, x25
	blr	x3
.L765:
	ldr	w0, [x29, 104]
	ldr	w1, [x29, 132]
	b	.L824
.L830:
	mov	w0, 0
	mov	w6, 0
	.p2align 2
.L747:
	ldr	w1, [x29, 104]
	mov	w5, w0
	cbz	w1, .L749
	ldr	w1, [x29, 104]
	add	w5, w1, w0
	mov	w1, 1
	.p2align 2
.L746:
	sub	w3, w1, #1
	uxtw	x2, w0
	ldr	x4, [x29, 136]
	add	w0, w0, 1
	cmp	w0, w5
	ldrb	w3, [x20, x3]
	strb	w3, [x4, x2]
	ldrb	w3, [x20, w1, uxtw]
	add	w1, w1, 2
	strb	w3, [x25, x2]
	bne	.L746
.L749:
	ldr	w0, [x29, 120]
	add	w6, w6, 1
	add	x20, x20, x19
	cmp	w0, w6
	mov	w0, w5
	bne	.L747
	b	.L748
.L832:
	ldr	w0, [x29, 120]
	mov	w7, 0
	mul	w1, w19, w0
	lsl	w0, w19, 1
	add	x20, x20, x1
	.p2align 2
.L764:
	ldr	w3, [x29, 104]
	cbz	w3, .L766
	lsr	w1, w7, 1
	mov	w2, 1
	mul	w1, w1, w3
	add	w6, w3, w1
	.p2align 2
.L763:
	sub	w5, w2, #1
	uxtw	x3, w1
	ldr	x4, [x29, 136]
	add	w1, w1, 1
	cmp	w6, w1
	ldrb	w5, [x20, x5]
	strb	w5, [x4, x3]
	ldrb	w5, [x20, w2, uxtw]
	add	w2, w2, 2
	strb	w5, [x25, x3]
	bne	.L763
.L766:
	ldr	w1, [x29, 132]
	add	w7, w7, 2
	add	x20, x20, x0
	cmp	w1, w7
	bhi	.L764
	b	.L765
.L831:
	ldr	w0, [x29, 108]
	cmp	w0, 1
	beq	.L765
	ldr	w0, [x29, 108]
	cbz	w0, .L768
	b	.L765
.L829:
	ldr	w0, [x29, 108]
	cmp	w0, 1
	bne	.L771
	b	.L748
	.size	VDMHAL_V5R6C1_WriteBigTitle1DYuv, .-VDMHAL_V5R6C1_WriteBigTitle1DYuv
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
.LC293:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CRG_ConfigReg
	.type	CRG_ConfigReg, %function
CRG_ConfigReg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	mov	x21, x2
	bl	_mcount
	ldr	x0, .LC294
	ldrb	w0, [x0]
	cmp	w0, 1
	bne	.L840
	cbnz	w19, .L836
	ldr	x0, .LC295
	ldr	x1, [x0]
	ldr	w0, [x1, 120]
	ubfx	x2, x0, 8, 2
	cmp	w20, w2
	beq	.L833
	bfi	w0, w20, 8, 2
	str	w0, [x1, 120]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L836:
	cmp	w19, 1
	beq	.L841
.L833:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L840:
	mov	w3, w20
	mov	w2, w19
	mov	x0, x21
	mov	w1, 0
	bl	VDH_Record_RegData
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L841:
	ldr	x0, .LC295
	ldr	x1, [x0]
	ldr	w0, [x1, 120]
	bfi	w0, w20, 12, 5
	and	w0, w0, -131073
	str	w0, [x1, 120]
	ldr	w0, [x1, 120]
	orr	w0, w0, 131072
	str	w0, [x1, 120]
	b	.L833
	.size	CRG_ConfigReg, .-CRG_ConfigReg
	.align	3
.LC294:
	.xword	g_HalDisable
	.align	3
.LC295:
	.xword	g_pstRegCrg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MFDE_ConfigReg
	.type	MFDE_ConfigReg, %function
MFDE_ConfigReg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	uxtw	x20, w0
	mov	x0, x30
	mov	w21, w1
	sxtw	x19, w2
	mov	x22, x3
	bl	_mcount
	ldr	x0, .LC296
	ldrb	w4, [x0]
	cmp	w4, 1
	bne	.L846
	cmp	w19, wzr
	ble	.L847
	ldr	x2, .LC298
	mov	w3, w19
	ldr	x1, .LC299
	mov	w0, 32
	add	x2, x2, 392
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L847:
	lsl	x0, x19, 6
	ldr	x1, .LC297
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x19, x0, x19
	add	x19, x0, x19, lsl 2
	ldr	x0, [x1, x19]
	str	w21, [x0, x20]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L846:
	mov	w3, w21
	mov	w2, w20
	mov	x0, x22
	mov	w1, 2
	bl	VDH_Record_RegData
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	MFDE_ConfigReg, .-MFDE_ConfigReg
	.align	3
.LC296:
	.xword	g_HalDisable
	.align	3
.LC297:
	.xword	g_HwMem
	.align	3
.LC298:
	.xword	.LANCHOR1
	.align	3
.LC299:
	.xword	.LC99
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.56715, %object
	.size	__func__.56715, 22
__func__.56715:
	.string	"VDMHAL_V5R6C1_OpenHAL"
	.zero	2
	.type	__func__.56789, %object
	.size	__func__.56789, 25
__func__.56789:
	.string	"VDMHAL_V5R6C1_CalcFsSize"
	.zero	7
	.type	__func__.56815, %object
	.size	__func__.56815, 24
__func__.56815:
	.string	"VDMHAL_V5R6C1_CalcFsNum"
	.type	__func__.56858, %object
	.size	__func__.56858, 32
__func__.56858:
	.string	"VDMHAL_V5R6C1_ArrangeMem_Normal"
	.type	__FUNCTION__.56859, %object
	.size	__FUNCTION__.56859, 32
__FUNCTION__.56859:
	.string	"VDMHAL_V5R6C1_ArrangeMem_Normal"
	.type	__func__.56801, %object
	.size	__func__.56801, 33
__func__.56801:
	.string	"VDMHAL_V5R6C1_FillMemArrangeInfo"
	.zero	7
	.type	__func__.56941, %object
	.size	__func__.56941, 34
__func__.56941:
	.string	"VDMHAL_V5R6C1_ArrangeMem_Specific"
	.zero	6
	.type	__func__.56963, %object
	.size	__func__.56963, 23
__func__.56963:
	.string	"VDMHAL_V5R6C1_ResetVdm"
	.zero	1
	.type	__func__.56973, %object
	.size	__func__.56973, 35
__func__.56973:
	.string	"VDMHAL_V5R6C1_SetSmmuPageTableAddr"
	.zero	5
	.type	__func__.56993, %object
	.size	__func__.56993, 24
__func__.56993:
	.string	"VDMHAL_V5R6C1_GlbResetX"
	.type	__func__.56983, %object
	.size	__func__.56983, 23
__func__.56983:
	.string	"VDMHAL_V5R6C1_GlbReset"
	.zero	1
	.type	__func__.57005, %object
	.size	__func__.57005, 28
__func__.57005:
	.string	"VDMHAL_V5R6C1_ClearIntState"
	.zero	4
	.type	__func__.57011, %object
	.size	__func__.57011, 31
__func__.57011:
	.string	"VDMHAL_V5R6C1_ClearMMUIntState"
	.zero	1
	.type	__func__.57017, %object
	.size	__func__.57017, 22
__func__.57017:
	.string	"VDMHAL_V5R6C1_MaskInt"
	.zero	2
	.type	__func__.57030, %object
	.size	__func__.57030, 24
__func__.57030:
	.string	"VDMHAL_V5R6C1_EnableInt"
	.type	__func__.57039, %object
	.size	__func__.57039, 23
__func__.57039:
	.string	"VDMHAL_V5R6C1_CheckReg"
	.align	3
.LANCHOR1 = . + 0
	.type	__func__.57053, %object
	.size	__func__.57053, 26
__func__.57053:
	.string	"VDMHAL_V5R6C1_ReadMMUMask"
	.zero	6
	.type	__func__.57058, %object
	.size	__func__.57058, 27
__func__.57058:
	.string	"VDMHAL_V5R6C1_WriteMMUMask"
	.zero	5
	.type	__func__.57090, %object
	.size	__func__.57090, 25
__func__.57090:
	.string	"VDMHAL_V5R6C1_PrepareDec"
	.zero	7
	.type	__func__.57095, %object
	.size	__func__.57095, 25
__func__.57095:
	.string	"VDMHAL_V5R6C1_IsVdmReady"
	.zero	7
	.type	__func__.57100, %object
	.size	__func__.57100, 23
__func__.57100:
	.string	"VDMHAL_V5R6C1_IsVdmRun"
	.zero	1
	.type	__func__.57106, %object
	.size	__func__.57106, 27
__func__.57106:
	.string	"VDMHAL_V5R6C1_IsVdhDecOver"
	.zero	5
	.type	__func__.57116, %object
	.size	__func__.57116, 31
__func__.57116:
	.string	"VDMHAL_V5R6C1_IsVdhPartDecOver"
	.zero	1
	.type	__func__.57131, %object
	.size	__func__.57131, 33
__func__.57131:
	.string	"VDMHAL_V5R6C1_UpdateHardwareInfo"
	.zero	7
	.type	__func__.57204, %object
	.size	__func__.57204, 23
__func__.57204:
	.string	"VDMHAL_V5R6C1_CfgRpMsg"
	.zero	1
	.type	__func__.57181, %object
	.size	__func__.57181, 24
__func__.57181:
	.string	"VDMHAL_CfgNotFullRepair"
	.type	__func__.57215, %object
	.size	__func__.57215, 23
__func__.57215:
	.string	"VDMHAL_V5R6C1_CfgRpReg"
	.zero	1
	.type	__func__.57228, %object
	.size	__func__.57228, 28
__func__.57228:
	.string	"VDMHAL_V5R6C1_MakeDecReport"
	.zero	4
	.type	__func__.57267, %object
	.size	__func__.57267, 28
__func__.57267:
	.string	"VDMHAL_V5R6C1_PrepareRepair"
	.zero	4
	.type	__func__.57455, %object
	.size	__func__.57455, 15
__func__.57455:
	.string	"MFDE_ConfigReg"
	.zero	1
	.type	__func__.57274, %object
	.size	__func__.57274, 28
__func__.57274:
	.string	"VDMHAL_V5R6C1_StartHwRepair"
	.zero	4
	.type	__func__.57313, %object
	.size	__func__.57313, 28
__func__.57313:
	.string	"VDMHAL_V5R6C1_CalVdhClkSkip"
	.zero	4
	.type	__func__.57337, %object
	.size	__func__.57337, 28
__func__.57337:
	.string	"VDMHAL_V5R6C1_StartHwDecode"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC3:
	ASCII(.string	"pOpenParam = NULL error!" )
	.zero	7
.LC6:
	ASCII(.string	"%s: %s\n" )
.LC8:
	ASCII(.string	"MemBaseAddr = 0 error!" )
	.zero	1
.LC10:
	ASCII(.string	"VDMHAL_V5R6C1_OpenHAL: Size error!" )
	.zero	5
.LC12:
	ASCII(.string	"VdhId is wrong!!!\n" )
	.zero	5
.LC16:
	ASCII(.string	"g_VdmRegVirAddr, g_VdmResetVirAddr = %p\n" )
	.zero	7
.LC18:
	ASCII(.string	"BPDRegVirAddr %p\n" )
	.zero	6
.LC20:
	ASCII(.string	"!!!!!! HAL memory not enouph! need %d, have %d\n" )
.LC22:
	ASCII(.string	"image size out of range" )
.LC29:
	ASCII(.string	"VDMHAL ArrangeMem HEVC/VP9/AVS2 10 bit\n" )
.LC32:
	ASCII(.string	"%s pstVfmwFrameSizeInfo = NULL\n" )
.LC36:
	ASCII(.string	"DelAllFrameMemRecord err in VDMHAL_V5R6C1_ArrangeMem!\n" )
	.zero	1
.LC38:
	ASCII(.string	"Report arrange frame buffer: wxh %dx%d, FsNum %d, PmvNum %d\n" )
	.zero	3
.LC43:
	ASCII(.string	"Report arrange frame buffer only: wxh %dx%d, FsNum %d, PmvNum %d\n" )
	.zero	6
.LC46:
	ASCII(.string	"VidStd Invalid" )
	.zero	1
.LC51:
	ASCII(.string	"Set CompressEn %d, LossCompressEn %d, YCompRatio %d, UVCompRatio %d\n" )
	.zero	3
.LC53:
	ASCII(.string	"VDMHAL_V5R6C1_CalcFsSize err!\n" )
	.zero	1
.LC55:
	ASCII(.string	"%s, need arrange, Size: %#x, Num: %#x, RefChanged: %#x\n" )
.LC57:
	ASCII(.string	"DFS, report event. Size: 0x%x, Num: %d, RefChanged: %d\n" )
.LC60:
	ASCII(.string	"pVdmMemArrange is NULL" )
	.zero	1
.LC62:
	ASCII(.string	"DFS, no ref frame!\n" )
	.zero	4
.LC64:
	ASCII(.string	"DFS, Frame number = %d > 30, Then, Frame num = 30, \n" )
	.zero	3
.LC66:
	ASCII(.string	"VDMHAL_V5R6C1_ArrangeMem Mem addr is NULL" )
	.zero	6
.LC71:
	ASCII(.string	"'pVdmMemArrange' is NULL" )
	.zero	7
.LC75:
	ASCII(.string	"MemSize not enough for pmv slot" )
.LC78:
	ASCII(.string	"VDMHAL_V200R003_ArrangeMem get ChanWidth/ChanHeight failed!\n" )
	.zero	3
.LC80:
	ASCII(.string	"ImgSlotLen > ChanSlotLen" )
	.zero	7
.LC82:
	ASCII(.string	"cann't allocate img slot" )
	.zero	7
.LC86:
	ASCII(.string	"%s: VdhId(%d) > %d\n" )
	.zero	4
.LC88:
	ASCII(.string	"VDMHAL_V5R6C1_ResetVdm: map vdm register fail, vir(reg) = (%p)\n" )
.LC92:
	ASCII(.string	"%s module id %d failed!\n" )
	.zero	7
.LC94:
	ASCII(.string	"%s module id %d success!\n" )
	.zero	6
.LC99:
	ASCII(.string	"%s: WR_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\n" )
	.zero	3
.LC104:
	ASCII(.string	"%s: map vdm register 0x%x failed!\n" )
	.zero	5
.LC107:
	ASCII(.string	"%s: RD_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\n" )
	.zero	3
.LC110:
	ASCII(.string	"%s VdhId %d failed!\n" )
	.zero	3
.LC112:
	ASCII(.string	"%s VdhId %d success!\n" )
	.zero	2
.LC123:
	ASCII(.string	"vdm register virtual address not mapped, reset failed!\n" )
.LC140:
	ASCII(.string	"%s: VdhId(%d) Invalid!\n" )
.LC143:
	ASCII(.string	"%s: vdm register virtual address not mapped, reset failed!\n" )
	.zero	4
.LC145:
	ASCII(.string	"%s: unkown reg_id = %d\n" )
.LC155:
	ASCII(.string	"%s: pDecParam(%p) = NULL\n" )
	.zero	6
.LC160:
	ASCII(.string	"VDM register not mapped yet!" )
	.zero	3
.LC166:
	ASCII(.string	"VDM register not mapped yet!\n" )
	.zero	2
.LC188:
	ASCII(.string	"can NOT map vir addr for up-msg" )
.LC192:
	ASCII(.string	"ReadUpMsgSlot error! pDst=%p, pSrc=%p\n" )
	.zero	1
.LC194:
	ASCII(.string	"ReadUpMsgSlot error! upmsg_size(%d) > 512\n" )
	.zero	5
.LC197:
	ASCII(.string	"WriteMsgSlot error!\n" )
	.zero	3
.LC200:
	ASCII(.string	"can not map repair msg virtual address!" )
.LC204:
	ASCII(.string	"ValidGroupNum=%d out of range!\n" )
.LC206:
	ASCII(.string	"align_mb error\n" )
.LC208:
	ASCII(.string	"[%s][%d]sclie_num is wrong! %d \n" )
	.zero	7
.LC217:
	ASCII(.string	"'pMakeDecReport' is NULL" )
	.zero	7
.LC221:
	ASCII(.string	"'pDecReport' is NULL" )
	.zero	3
.LC231:
	ASCII(.string	"pDecReport->DecSliceNum(%d) > %d, set to 0 for full repair.\n" )
	.zero	3
.LC235:
	ASCII(.string	"\n***** UpMsg DecSliceNum=%d\n" )
	.zero	3
.LC237:
	ASCII(.string	"\n***** Up Msg (phy addr: %#8x) *****\n" )
	.zero	2
.LC239:
	ASCII(.string	"\n0x%02x 0x%08x 0x%08x 0x%08x 0x%08x\n" )
	.zero	3
.LC241:
	ASCII(.string	"\n***** Up Msg print finished *****\n" )
	.zero	4
.LC246:
	ASCII(.string	"vdm register virtual address not mapped, VDMHAL_V200R003_PrepareRepair failed!\n" )
.LC249:
	ASCII(.string	"FIRST_REPAIR Parameter Error!\n" )
	.zero	1
.LC251:
	ASCII(.string	"SECOND_REPAIR Parameter Error!\n" )
.LC257:
	ASCII(.string	"%s: pMfdeTask(%p) = NULL\n" )
	.zero	6
.LC266:
	ASCII(.string	"%s The channel %d is not active\n" )
	.zero	7
.LC287:
	ASCII(.string	"BigTile1d_y" )
	.zero	4
.LC289:
	ASCII(.string	"failed mem_allocMemBlock BigTile_yuv save!\n" )
	.zero	4
.LC291:
	ASCII(.string	"BigTile1d_uv" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
