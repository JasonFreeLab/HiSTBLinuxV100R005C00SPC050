#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vdm_hal.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_GetHalMemSize
	.type	VDMHAL_V4R3C1_GetHalMemSize, %function
VDMHAL_V4R3C1_GetHalMemSize:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 6291456
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V4R3C1_GetHalMemSize, .-VDMHAL_V4R3C1_GetHalMemSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_OpenHAL
	.type	VDMHAL_V4R3C1_OpenHAL, %function
VDMHAL_V4R3C1_OpenHAL:
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
	bl	H264HAL_V4R3C1_InitHal
	cmp	w0, wzr
	mov	x0, x21
	csetm	w19, ne
	bl	HEVCHAL_V4R3C1_InitHal
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
	.size	VDMHAL_V4R3C1_OpenHAL, .-VDMHAL_V4R3C1_OpenHAL
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
	.global	VDMHAL_V4R3C1_CloseHAL
	.type	VDMHAL_V4R3C1_CloseHAL, %function
VDMHAL_V4R3C1_CloseHAL:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V4R3C1_CloseHAL, .-VDMHAL_V4R3C1_CloseHAL
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_CalcFsSize
	.type	VDMHAL_V4R3C1_CalcFsSize, %function
VDMHAL_V4R3C1_CalcFsSize:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w23, w0
	mov	x0, x30
	mov	w27, w1
	mov	w28, w2
	mov	w24, w3
	mov	w25, w4
	mov	x22, x5
	bl	_mcount
	sub	w1, w27, #32
	mov	w0, 8160
	cmp	w1, w0
	bhi	.L21
	sub	w1, w28, #32
	mov	w21, w28
	cmp	w1, w0
	bhi	.L21
	add	w0, w27, 15
	add	w20, w28, 15
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
	cmp	w25, 16
	beq	.L26
	cmp	w25, 17
	beq	.L47
	mul	w19, w0, w19
	ldr	x4, .LC28
	add	w3, w3, 255
	add	w21, w28, 31
	and	w26, w3, -256
	mul	w19, w19, w20
	ldr	x5, [x4, w23, sxtw 3]
	and	w21, w21, -32
	add	w19, w19, 143
	mov	w6, 0
	and	w19, w19, -128
	mov	w7, 0
	asr	w3, w19, 1
.L37:
	ldr	w0, [x5, 1200]
	cmp	w0, 1
	beq	.L48
.L41:
	cmp	w24, 1
	mov	w28, 0
	mov	w8, 0
	mov	w27, 0
	mul	w21, w21, w26
	beq	.L49
.L30:
	mul	w2, w6, w7
	lsl	w1, w27, 2
	lsl	w0, w2, 2
	sub	w1, w1, w27
	sub	w2, w0, w2
	lsl	w0, w21, 2
	sub	w0, w0, w21
	lsr	w0, w0, 1
	add	w0, w0, w2, lsr 1
	add	w20, w0, w1, lsr 1
.L31:
	add	x2, x5, 290816
	ldr	w0, [x2, 1120]
	cbz	w0, .L50
	add	x0, x5, 294912
	cmp	w25, 17
	str	w20, [x0, 592]
	str	w3, [x2, 3508]
	lsl	w3, w26, 4
	str	w8, [x2, 3468]
	str	w28, [x2, 3472]
	beq	.L33
.L52:
	ldr	w0, [x2, 1128]
	mov	w1, 32
	str	w3, [x2, 3460]
	lsr	w3, w3, 1
	cmp	w0, 32
	str	w3, [x2, 3464]
	csel	w0, w0, w1, le
	cmp	w25, 16
	str	w0, [x2, 3512]
	add	w0, w21, w27
	str	w0, [x2, 3492]
	beq	.L51
.L35:
	ldr	x0, [x4, w23, sxtw 3]
	mov	w5, 1024
	add	w1, w20, 1056
	add	x3, x0, 294912
	add	w2, w1, w19
	add	w6, w2, w5
	str	w19, [x3, 596]
	str	w5, [x3, 604]
	ldrsb	w0, [x0, 44]
	cmp	w0, 1
	csel	w2, w6, w2, eq
	cbz	x22, .L42
	str	w1, [x22, 4]
	mov	w0, 0
	ldr	x3, [x4, w23, sxtw 3]
	add	x3, x3, 290816
	ldr	w3, [x3, 1128]
	stp	w3, w19, [x22, 8]
	ldr	x3, [x4, w23, sxtw 3]
	add	x3, x3, 290816
	ldr	w3, [x3, 3512]
	stp	w3, w5, [x22, 16]
	str	w2, [x22]
	ldr	x2, [x4, w23, sxtw 3]
	add	x2, x2, 294912
	str	w1, [x2, 600]
.L43:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L51:
	ldr	w0, [x5, 1508]
	cmp	w0, 8
	ble	.L35
	lsl	w0, w21, 2
	ldr	x1, .LC30
	sub	w21, w0, w21
	lsl	w0, w27, 2
	sub	w27, w0, w27
	mov	w0, 31
	mul	w6, w6, w7
	lsr	w27, w27, 1
	lsl	w7, w7, 5
	add	w21, w27, w21, lsr 1
	str	w7, [x2, 3476]
	str	w21, [x2, 3484]
	str	w6, [x2, 3488]
	str	x4, [x29, 120]
	bl	dprint_vfmw
	ldr	x4, [x29, 120]
	b	.L35
	.p2align 3
.L50:
	ldr	x1, .LC27
	add	x0, x2, 3456
	mov	x2, 1248
	str	x4, [x29, 96]
	stp	w8, w7, [x29, 108]
	ldr	x5, [x1, 96]
	mov	w1, 0
	stp	w6, w3, [x29, 116]
	blr	x5
	ldr	x4, [x29, 96]
	cmp	w25, 17
	ldp	w6, w3, [x29, 116]
	ldp	w8, w7, [x29, 108]
	ldr	x5, [x4, w23, sxtw 3]
	add	x0, x5, 294912
	add	x2, x5, 290816
	str	w20, [x0, 592]
	str	w3, [x2, 3508]
	lsl	w3, w26, 4
	str	w8, [x2, 3468]
	str	w28, [x2, 3472]
	bne	.L52
.L33:
	mov	w0, 1
	add	w21, w21, w27
	str	w0, [x2, 3512]
	lsr	w0, w3, 1
	str	w3, [x2, 3460]
	str	w21, [x2, 3492]
	str	w0, [x2, 3464]
	b	.L35
	.p2align 3
.L26:
	ldr	x4, .LC28
	mul	w19, w20, w3
	add	w3, w27, 255
	ldr	x5, [x4, w23, sxtw 3]
	add	w19, w19, 143
	and	w26, w3, -256
	and	w19, w19, -128
	ldr	w0, [x5, 1508]
	cmp	w0, 8
	ble	.L53
	ldr	w0, [x5, 1200]
	add	w6, w28, 31
	and	w6, w6, -32
	lsr	w7, w26, 2
	cmp	w0, 1
	asr	w3, w19, 1
	bne	.L41
	.p2align 2
.L48:
	adds	w1, w27, 511
	add	w27, w27, 1022
	csel	w27, w27, w1, mi
	add	w0, w28, 126
	and	w27, w27, -512
	cmp	w27, wzr
	add	w8, w27, 63
	csel	w8, w8, w27, lt
	adds	w27, w28, 63
	csel	w27, w0, w27, mi
	asr	w8, w8, 6
	asr	w27, w27, 6
	lsl	w8, w8, 1
	lsl	w27, w27, 5
	cmp	w24, 1
	mul	w21, w21, w26
	mul	w27, w27, w8
	mov	w28, w27
	bne	.L30
.L49:
	lsl	w1, w20, 6
	sub	w20, w1, w20, lsl 4
	mul	w20, w20, w26
	b	.L31
	.p2align 3
.L47:
	ldr	x4, .LC28
	add	w3, w27, 255
	add	w21, w28, 63
	and	w26, w3, -256
	mov	w19, 128
	mov	w3, 64
	and	w21, w21, -64
	movk	w3, 0x12, lsl 16
	ldr	x5, [x4, w23, sxtw 3]
	movk	w19, 0x24, lsl 16
	mov	w6, 0
	mov	w7, 0
	b	.L37
	.p2align 3
.L53:
	asr	w3, w19, 1
	mov	w6, 0
	mov	w7, 0
	b	.L37
	.p2align 3
.L42:
	mov	w0, 0
	b	.L43
	.p2align 3
.L21:
	ldr	x2, .LC24
	mov	w0, 0
	ldr	x3, .LC23
	ldr	x1, .LC25
	add	x2, x2, 24
	bl	dprint_vfmw
	mov	w0, -1
	b	.L43
	.size	VDMHAL_V4R3C1_CalcFsSize, .-VDMHAL_V4R3C1_CalcFsSize
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
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC28:
	.xword	s_pstVfmwChan
	.align	3
.LC30:
	.xword	.LC29
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_GetRpuSize
	.type	VDMHAL_V4R3C1_GetRpuSize, %function
VDMHAL_V4R3C1_GetRpuSize:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1024
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V4R3C1_GetRpuSize, .-VDMHAL_V4R3C1_GetRpuSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_CalcFsNum
	.type	VDMHAL_V4R3C1_CalcFsNum, %function
VDMHAL_V4R3C1_CalcFsNum:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x19, x3
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	cbz	x19, .L60
	cmp	w21, 17
	ldr	x2, .LC34
	beq	.L61
	ldr	x3, [x2, w20, sxtw 3]
	mov	w4, 32
	add	x1, x3, 290816
	ldr	w0, [x1, 1128]
	cmp	w0, w4
	csel	w0, w0, w4, le
	str	w0, [x1, 3512]
	ldr	w0, [x3, 632]
	cmp	w0, 2
	beq	.L62
.L59:
	ldr	x1, [x2, w20, sxtw 3]
	mov	w0, 0
	add	x1, x1, 290816
	ldr	w1, [x1, 1128]
	str	w1, [x19, 8]
	ldr	x1, [x2, w20, sxtw 3]
	add	x1, x1, 290816
	ldr	w1, [x1, 3512]
	str	w1, [x19, 16]
.L57:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L61:
	ldr	x0, [x2, w20, sxtw 3]
	mov	w1, 1
	add	x0, x0, 290816
	str	w1, [x0, 3512]
	b	.L59
	.p2align 3
.L62:
	ldr	w0, [x1, 1132]
	str	w0, [x1, 3512]
	b	.L59
.L60:
	ldr	x2, .LC31
	mov	w0, 1
	ldr	x1, .LC33
	add	x2, x2, 56
	bl	dprint_vfmw
	mov	w0, -1
	b	.L57
	.size	VDMHAL_V4R3C1_CalcFsNum, .-VDMHAL_V4R3C1_CalcFsNum
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
	.global	VDMHAL_V4R3C1_DynamicAllocFrame
	.type	VDMHAL_V4R3C1_DynamicAllocFrame, %function
VDMHAL_V4R3C1_DynamicAllocFrame:
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
	add	x1, x1, 290816
	add	x1, x1, 1152
	bl	DelAllFrameMemRecord
	cbnz	w0, .L83
.L64:
	ldr	x1, [x21, w19, sxtw 3]
	mov	w2, 255
	add	x1, x1, 290816
	add	x0, x1, 1152
	add	x1, x1, 3456
	.p2align 2
.L65:
	str	w2, [x0], 72
	cmp	x1, x0
	bne	.L65
	mov	w0, 1088
	cmp	w23, 1920
	ccmp	w22, w0, 0, le
	ble	.L66
	ldr	x0, [x21, w19, sxtw 3]
	ldr	w1, [x20, 8]
.L67:
	add	x2, x0, 290816
	ldr	w3, [x0, 1456]
	mov	w0, w19
	add	w1, w3, w1
	str	w1, [x2, 1132]
	bl	VCTRL_GetVidStd
	ldr	x1, [x21, w19, sxtw 3]
	ldr	w2, [x1, 632]
	cmp	w2, 2
	ccmp	w0, 17, 4, eq
	beq	.L70
	add	x1, x1, 290816
	ldr	w0, [x1, 1132]
	str	w0, [x20, 16]
	ldr	x1, [x21, w19, sxtw 3]
.L70:
	add	x0, x1, 294912
	add	x1, x1, 262144
	mov	w4, 1
	mov	w3, w22
	mov	w2, w23
	str	wzr, [x0, 632]
	str	w4, [x1, 2032]
	str	w4, [x0, 1172]
	mov	w0, 31
	ldr	x1, .LC39
	ldr	w4, [x20, 8]
	ldr	w5, [x20, 16]
	bl	dprint_vfmw
	ldr	x0, .LC40
	ldr	x4, [x0]
	cbz	x4, .L71
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
.L71:
	ldr	x3, .LC41
	mov	x2, 528
	ldr	x0, [x21, w19, sxtw 3]
	mov	w1, 0
	ldr	x3, [x3, 96]
	add	x0, x0, 294912
	add	x0, x0, 640
	blr	x3
	ldr	x1, [x21, w19, sxtw 3]
	mov	w0, w19
	add	x1, x1, 294912
	str	wzr, [x1, 1168]
	bl	FSP_ClearContextAll
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L66:
	ldr	x0, [x21, w19, sxtw 3]
	ldr	w1, [x0, 36]
	cmp	w1, 24
	beq	.L82
	add	x1, x0, 294912
	ldr	w1, [x1, 1228]
	cbnz	w1, .L82
	ldr	w1, [x20, 8]
	add	w1, w1, 4
	str	w1, [x20, 8]
	ldr	x0, [x21, w19, sxtw 3]
	b	.L67
.L82:
	ldr	w1, [x20, 8]
	b	.L67
.L83:
	ldr	x1, .LC37
	mov	w0, 0
	bl	dprint_vfmw
	b	.L64
	.size	VDMHAL_V4R3C1_DynamicAllocFrame, .-VDMHAL_V4R3C1_DynamicAllocFrame
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
	.global	VDMHAL_V4R3C1_DynamicAllocFrame_Only
	.type	VDMHAL_V4R3C1_DynamicAllocFrame_Only, %function
VDMHAL_V4R3C1_DynamicAllocFrame_Only:
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
	add	x4, x4, 290816
	str	w5, [x4, 1132]
	ldr	w4, [x19, 8]
	ldr	w5, [x19, 16]
	bl	dprint_vfmw
	ldr	x0, .LC45
	ldr	x4, [x0]
	cbz	x4, .L84
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
.L84:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.size	VDMHAL_V4R3C1_DynamicAllocFrame_Only, .-VDMHAL_V4R3C1_DynamicAllocFrame_Only
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
	.global	VDMHAL_V4R3C1_ArrangeMem_Normal
	.type	VDMHAL_V4R3C1_ArrangeMem_Normal, %function
VDMHAL_V4R3C1_ArrangeMem_Normal:
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
	bhi	.L119
	ldr	x20, .LC50
	ldr	x0, [x20, w19, sxtw 3]
	add	x1, x0, 290816
	ldr	w26, [x1, 1124]
	ldr	w1, [x0, 100]
	cmp	w1, 2
	beq	.L120
	mov	w2, 1
	ldr	w3, [x0, 1204]
	ldr	w4, [x0, 1208]
	ldr	w5, [x0, 1212]
	ldr	x1, .LC52
	str	w2, [x0, 1200]
	mov	w0, w2
	bl	dprint_vfmw
.L93:
	mov	w2, w25
	add	x3, x29, 104
	mov	w1, w22
	mov	w0, w19
	bl	VDMHAL_V4R3C1_CalcFsNum
	mov	w25, w0
	add	x5, x29, 104
	mov	w4, w22
	mov	w3, w27
	mov	w2, w24
	mov	w1, w23
	mov	w0, w19
	bl	VDMHAL_V4R3C1_CalcFsSize
	orr	w0, w25, w0
	cbnz	w0, .L121
	ldr	x27, [x20, w19, sxtw 3]
	ldr	w22, [x29, 104]
	cmp	w26, w22
	add	x26, x27, 290816
	ldr	w25, [x26, 1128]
	ldr	w5, [x26, 1144]
	beq	.L122
.L96:
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
	add	x0, x0, 290816
	ldr	w1, [x0, 1120]
	str	w22, [x0, 1124]
	cbz	w1, .L123
	mov	w1, w23
	mov	w0, w19
	bl	VDMHAL_V4R3C1_DynamicAllocFrame_Only
.L99:
	ldr	x4, [x20, w19, sxtw 3]
	mov	w3, w25
	ldr	x1, .LC58
	mov	w2, w22
	add	x4, x4, 290816
	mov	w0, 31
	ldr	w4, [x4, 1144]
	bl	dprint_vfmw
	ldr	x19, [x20, w19, sxtw 3]
	ldr	x0, .LC59
	add	x19, x19, 294912
	ldr	x0, [x0]
	blr	x0
	str	w0, [x19, 608]
	mov	w1, 2
.L91:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	mov	w0, w1
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L123:
	mov	w1, w23
	mov	w0, w19
	bl	VDMHAL_V4R3C1_DynamicAllocFrame
	b	.L99
	.p2align 3
.L120:
	add	x2, x0, 1024
	mov	w1, -1
	stp	wzr, wzr, [x2, 176]
	stp	w1, w1, [x2, 184]
	b	.L93
	.p2align 3
.L122:
	cmp	w5, 1
	beq	.L96
	ldr	w0, [x26, 1120]
	cmp	w0, 1
	beq	.L96
	cbz	x21, .L124
	add	x1, x27, 294912
	add	x22, x26, 3456
	mov	x0, x27
	ldr	w23, [x1, 592]
	cbz	w25, .L125
.L101:
	add	x0, x0, 290816
	ldr	w2, [x0, 1132]
	cmp	w2, 30
	bgt	.L126
.L102:
	ldr	x24, .LC59
	add	x26, x26, 3456
	mov	w0, 8
	str	w2, [x26, 48]
	ldr	x1, [x24, 24]
	blr	x1
	ldr	x7, [x20, w19, sxtw 3]
	add	x9, x7, 294912
	ldr	w0, [x9, 632]
	cbz	w0, .L107
	ldp	w10, w6, [x26, 56]
	mov	x1, x26
	mov	w5, 0
	mov	w8, 1
	.p2align 2
.L106:
	uxtw	x0, w5
	add	w5, w5, 1
	lsl	x2, x0, 6
	add	x2, x2, x0, lsl 3
	add	x2, x7, x2
	add	x11, x2, 290816
	uxtw	x2, w6
	lsl	x3, x2, 2
	add	x4, x2, 20
	sub	x3, x3, x2
	add	w6, w6, 1
	ldr	w2, [x11, 1184]
	add	x3, x1, x3, lsl 2
	ldr	w12, [x11, 1164]
	add	w2, w2, 1023
	and	w2, w2, -1024
	strb	w8, [x3, 472]
	str	w2, [x3, 464]
	add	w2, w23, w2
	str	w12, [x3, 468]
	str	w2, [x1, x4, lsl 2]
	str	w6, [x1, 60]
	ldr	w2, [x11, 1156]
	cmp	w2, 255
	beq	.L104
	ldr	w2, [x1, 68]
	ldr	w4, [x11, 1200]
	add	w3, w2, 1
	uxtw	x2, w2
	lsl	x0, x2, 2
	sub	x0, x0, x2
	add	x0, x1, x0, lsl 2
	str	w4, [x0, 848]
	str	w3, [x1, 68]
.L104:
	ldr	w0, [x1, 64]
	cmp	w0, w10
	bcs	.L105
	ldr	w3, [x11, 1160]
	add	x2, x27, x0, uxtw 3
	add	x2, x2, 290816
	add	w0, w0, 1
	cmp	w3, 255
	beq	.L105
	ldr	w3, [x11, 1216]
	str	w3, [x2, 3664]
	strb	w8, [x2, 3668]
	str	w0, [x1, 64]
.L105:
	ldr	w0, [x9, 632]
	cmp	w5, w0
	bcc	.L106
.L107:
	ldr	x3, [x24, 104]
	mov	x2, 1232
	mov	x1, x22
	mov	x0, x21
	blr	x3
	ldr	x1, [x20, w19, sxtw 3]
	mov	w3, 1
	ldr	x2, [x24, 32]
	mov	w0, 8
	add	x1, x1, 294912
	str	w3, [x1, 636]
	blr	x2
	mov	w1, 0
	b	.L91
	.p2align 3
.L126:
	ldr	x1, .LC65
	mov	w0, 31
	bl	dprint_vfmw
	ldr	x0, [x20, w19, sxtw 3]
	mov	w1, 30
	mov	w2, w1
	add	x0, x0, 290816
	str	w1, [x0, 1132]
	b	.L102
	.p2align 3
.L125:
	ldr	x1, .LC63
	mov	w0, 31
	bl	dprint_vfmw
	ldr	x0, [x20, w19, sxtw 3]
	b	.L101
	.p2align 3
.L119:
	ldr	x2, .LC48
	mov	w0, 0
	ldr	x1, .LC49
	ldr	x3, .LC47
	add	x2, x2, 80
	bl	dprint_vfmw
	mov	w1, -1
	b	.L91
	.p2align 3
.L121:
	ldr	x1, .LC54
	mov	w0, 31
	bl	dprint_vfmw
	mov	w1, -1
	b	.L91
.L124:
	ldr	x2, .LC48
	mov	w0, 0
	ldr	x1, .LC49
	ldr	x3, .LC61
	add	x2, x2, 144
	bl	dprint_vfmw
	mov	w1, -1
	b	.L91
	.size	VDMHAL_V4R3C1_ArrangeMem_Normal, .-VDMHAL_V4R3C1_ArrangeMem_Normal
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
	.global	VDMHAL_V4R3C1_ArrangeMem_Specific
	.type	VDMHAL_V4R3C1_ArrangeMem_Specific, %function
VDMHAL_V4R3C1_ArrangeMem_Specific:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w23, w0
	mov	w20, w2
	mov	x0, x30
	mov	w24, w1
	mov	w25, w4
	mov	w27, w5
	mov	w19, w6
	mov	w26, w7
	ldr	x21, [x29, 144]
	str	w3, [x29, 124]
	bl	_mcount
	cbz	w20, .L194
	sub	w1, w25, #32
	mov	w0, 8160
	cmp	w1, w0
	bhi	.L130
	sub	w1, w27, #32
	cmp	w1, w0
	bhi	.L130
	cbz	x21, .L195
	ldr	x0, .LC73
	cmp	w19, 20
	mov	x2, 1232
	mov	w1, 0
	mov	w6, 20
	mov	w22, 32
	ldr	x3, [x0, 96]
	mov	x0, x21
	csel	w19, w19, w6, le
	blr	x3
	ldr	x1, .LC74
	add	w0, w25, 15
	asr	w0, w0, 4
	add	w8, w27, 15
	cmp	w0, 45
	asr	w8, w8, 4
	ldrb	w2, [x1]
	mov	w1, 36
	ccmp	w8, w1, 0, le
	mov	w1, 64
	cset	w3, le
	cmp	w3, wzr
	csel	w22, w22, w1, eq
	cmp	w2, 1
	csel	w22, w22, w1, ne
	cmp	w24, 16
	lsl	w1, w0, 4
	beq	.L196
	cmp	w24, 17
	beq	.L138
	mul	w22, w0, w22
	ldr	w0, [x29, 124]
	mul	w22, w22, w8
	add	w22, w22, 143
	and	w22, w22, -128
	mul	w3, w19, w22
	cmp	w0, w3
	ble	.L136
	asr	w0, w22, 1
	add	w1, w1, 255
	stp	w0, w19, [x21, 52]
	add	w19, w20, 1023
	add	w6, w27, 31
	and	w19, w19, -1024
	and	w28, w1, -256
	and	w6, w6, -32
	add	w11, w27, 63
	mov	w10, 0
	mov	w9, 0
	sub	w7, w19, w20
.L140:
	adds	w0, w25, 511
	add	w4, w25, 1022
	csel	w0, w4, w0, mi
	ldr	w1, [x29, 128]
	and	w2, w0, -512
	cmp	w2, wzr
	add	w0, w2, 63
	csel	w0, w0, w2, lt
	cmp	w11, wzr
	add	w2, w11, 63
	asr	w0, w0, 6
	csel	w4, w2, w11, lt
	cmp	w1, 1
	asr	w2, w4, 6
	lsl	w4, w0, 6
	lsl	w0, w0, 1
	mul	w4, w4, w2
	stp	w0, w4, [x21, 12]
	lsl	w0, w28, 4
	str	w0, [x21, 4]
	asr	w0, w0, 1
	str	w0, [x21, 8]
	beq	.L197
	mul	w5, w6, w28
	mul	w8, w10, w9
	lsl	w0, w5, 2
	lsl	w2, w4, 2
	sub	w5, w0, w5
	lsl	w0, w8, 2
	sub	w0, w0, w8
	sub	w2, w2, w4
	asr	w0, w0, 1
	add	w0, w0, w5, asr 1
	add	w27, w0, w2, lsr 1
.L143:
	ldr	w0, [x29, 136]
	tbnz	w0, #31, .L144
	stp	w3, w7, [x29, 100]
	stp	w6, w9, [x29, 108]
	stp	w10, w4, [x29, 116]
	bl	VCTRL_GetChanWidth
	mov	w23, w0
	ldr	w0, [x29, 136]
	bl	VCTRL_GetChanHeight
	cmn	w23, #1
	ccmn	w0, #1, 4, ne
	ldp	w3, w7, [x29, 100]
	ldp	w6, w9, [x29, 108]
	ldp	w10, w4, [x29, 116]
	beq	.L198
	ldr	w1, [x29, 128]
	add	w5, w23, 15
	and	w5, w5, -16
	add	w0, w0, 15
	cmp	w1, 1
	add	w11, w5, 255
	and	w0, w0, -16
	and	w11, w11, -256
	beq	.L199
	adds	w8, w0, 63
	add	w0, w0, 126
	csel	w0, w0, w8, mi
	adds	w8, w5, 511
	add	w5, w5, 1022
	asr	w0, w0, 6
	csel	w5, w5, w8, mi
	and	w5, w5, -512
	add	w8, w5, 63
	cmp	w5, wzr
	csel	w5, w8, w5, lt
	asr	w5, w5, 6
	lsl	w8, w5, 1
	lsl	w5, w0, 2
	mul	w11, w11, w0
	sub	w0, w5, w0
	lsl	w0, w0, 5
	mul	w5, w8, w0
	mul	w8, w10, w9
	lsl	w0, w11, 2
	sub	w11, w0, w11
	lsl	w0, w8, 2
	lsl	w11, w11, 6
	sub	w0, w0, w8
	asr	w0, w0, 1
	add	w0, w0, w11, asr 1
	add	w0, w0, w5, lsr 1
.L147:
	cmp	w27, w0
	ldr	w23, [x29, 136]
	bgt	.L200
.L144:
	mul	w25, w6, w28
	cmp	w23, wzr
	str	w4, [x29, 120]
	add	w0, w25, w4
	ccmp	w24, 16, 0, ge
	str	w0, [x21, 36]
	stp	w9, w10, [x29, 112]
	bne	.L149
	ldr	x0, .LC77
	stp	w3, w7, [x29, 104]
	ldr	x0, [x0, w23, sxtw 3]
	add	x0, x0, 294912
	add	x0, x0, 1240
	bl	IsMain10Profile
	ldp	w3, w7, [x29, 104]
	ldp	w9, w10, [x29, 112]
	ldr	w4, [x29, 120]
	cbnz	w0, .L201
	.p2align 2
.L149:
	cbnz	w26, .L151
	str	wzr, [x21, 48]
.L152:
	ldr	x2, .LC68
	ldr	x3, .LC84
.L192:
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
.L151:
	ldr	w0, [x29, 124]
	cmp	w26, 32
	mov	w4, 32
	sub	w3, w0, w3
	csel	w4, w26, w4, le
	sub	w3, w3, w7
	sdiv	w3, w3, w27
	cmp	w3, w4
	csel	w4, w3, w4, le
	str	w4, [x21, 48]
	cbz	w4, .L152
	sub	w6, w4, #1
	mov	x3, 476
	mov	w1, 12
	ldr	w5, [x21, 60]
	add	x0, x21, 464
	umaddl	x1, w6, w1, x3
	uxtw	x3, w6
	add	x1, x21, x1
	.p2align 2
.L157:
	str	w19, [x0], 12
	add	w19, w19, w27
	cmp	x0, x1
	bne	.L157
	madd	w2, w27, w4, w7
	add	x3, x3, 21
	add	w5, w5, w4
	add	w1, w2, w20
	add	x0, x21, 80
	add	x3, x21, x3, lsl 2
	str	w5, [x21, 60]
	.p2align 2
.L159:
	str	w1, [x0], 4
	add	w1, w1, 32
	cmp	x3, x0
	bne	.L159
	ldr	w5, [x21, 56]
	add	w2, w2, w4, lsl 5
	add	w20, w2, w20
	cbz	w5, .L164
	sub	w3, w5, #1
	ldr	w7, [x21, 64]
	add	x3, x3, 27
	add	x1, x21, 208
	mov	w0, w20
	add	x3, x21, x3, lsl 3
	.p2align 2
.L163:
	str	w0, [x1], 8
	add	w0, w0, w22
	cmp	x1, x3
	bne	.L163
	add	w0, w5, w7
	str	w0, [x21, 64]
.L164:
	madd	w2, w5, w22, w2
	str	w2, [x21]
	tbnz	w23, #31, .L162
	ldr	x0, .LC77
	ldr	x0, [x0, w23, sxtw 3]
	cbz	x0, .L162
	add	w20, w2, w20
	cbz	w4, .L162
	mov	w3, 12
	mov	x1, 860
	add	x0, x21, 848
	umaddl	x1, w6, w3, x1
	add	x1, x21, x1
	.p2align 2
.L165:
	str	w20, [x0], 12
	add	w20, w20, 1024
	cmp	x1, x0
	bne	.L165
.L162:
	add	w2, w2, w4, lsl 10
	mov	w0, 0
	str	w2, [x21]
.L186:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L196:
	mul	w22, w8, w1
	ldr	w0, [x29, 124]
	add	w22, w22, 143
	and	w22, w22, -128
	mul	w3, w19, w22
	cmp	w0, w3
	ble	.L136
	asr	w0, w22, 1
	add	w1, w25, 255
	stp	w0, w19, [x21, 52]
	add	w19, w20, 1023
	and	w28, w1, -256
	and	w19, w19, -1024
	sub	w7, w19, w20
	tbnz	w23, #31, .L191
	ldr	x0, .LC77
	stp	w3, w7, [x29, 112]
	str	w8, [x29, 120]
	ldr	x0, [x0, w23, sxtw 3]
	add	x0, x0, 294912
	add	x0, x0, 1240
	bl	IsMain10Profile
	ldp	w3, w7, [x29, 112]
	ldr	w8, [x29, 120]
	cbz	w0, .L191
	cmp	w28, wzr
	add	w9, w28, 3
	csel	w9, w9, w28, lt
	add	w10, w27, 31
	asr	w9, w9, 2
	and	w10, w10, -32
	add	w11, w27, 63
	mov	w6, w27
	b	.L140
	.p2align 3
.L197:
	lsl	w0, w8, 4
	mul	w0, w0, w28
	lsl	w2, w0, 2
	sub	w27, w2, w0
	b	.L143
	.p2align 3
.L138:
	lsl	w3, w19, 14
	ldr	w0, [x29, 124]
	add	w3, w3, w19, lsl 11
	add	w3, w3, w19
	lsl	w3, w3, 7
	cmp	w0, w3
	ble	.L136
	mov	w0, 64
	add	w11, w27, 63
	movk	w0, 0x12, lsl 16
	add	w1, w25, 255
	stp	w0, w19, [x21, 52]
	add	w19, w20, 1023
	mov	w22, 128
	and	w19, w19, -1024
	and	w28, w1, -256
	and	w6, w11, -64
	movk	w22, 0x24, lsl 16
	mov	w10, 0
	mov	w9, 0
	sub	w7, w19, w20
	b	.L140
	.p2align 3
.L191:
	add	w11, w27, 63
	mov	w6, w27
	mov	w10, 0
	mov	w9, 0
	b	.L140
	.p2align 3
.L199:
	mul	w0, w0, w11
	lsl	w5, w0, 2
	sub	w0, w5, w0
	b	.L147
.L130:
	ldr	x2, .LC68
	ldr	x3, .LC70
	b	.L192
.L201:
	lsl	w0, w25, 2
	sub	w1, w0, w25
	lsl	w0, w4, 2
	sub	w0, w0, w4
	lsr	w4, w4, 1
	lsr	w0, w0, 1
	madd	w10, w10, w9, w4
	add	w0, w0, w1, asr 1
	ldr	x1, .LC82
	lsl	w9, w9, 5
	str	w9, [x21, 20]
	stp	w0, w10, [x21, 28]
	mov	w0, 0
	stp	w3, w7, [x29, 116]
	bl	dprint_vfmw
	ldp	w3, w7, [x29, 116]
	b	.L149
.L136:
	ldr	x2, .LC68
	ldr	x3, .LC76
	b	.L192
.L194:
	ldr	x2, .LC68
	ldr	x3, .LC67
	b	.L192
.L198:
	ldr	x1, .LC79
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L186
.L200:
	ldr	x2, .LC68
	ldr	x3, .LC81
	b	.L192
.L195:
	ldr	x2, .LC68
	ldr	x3, .LC72
	b	.L192
	.size	VDMHAL_V4R3C1_ArrangeMem_Specific, .-VDMHAL_V4R3C1_ArrangeMem_Specific
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
.LC82:
	.xword	.LC29
	.align	3
.LC84:
	.xword	.LC83
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_ArrangeMem
	.type	VDMHAL_V4R3C1_ArrangeMem, %function
VDMHAL_V4R3C1_ArrangeMem:
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
	beq	.L206
	tbnz	w19, #31, .L207
	mov	w0, w19
	bl	VCTRL_GetVidStd
	mov	w1, w0
	ldr	x0, .LC85
	ldr	x0, [x0, w19, sxtw 3]
	ldr	w0, [x0, 1448]
	cmp	w0, 1
	beq	.L209
.L204:
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
	bl	VDMHAL_V4R3C1_ArrangeMem_Specific
.L208:
	add	sp, x29, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L207:
	mov	w1, 21
	b	.L204
	.p2align 3
.L206:
	mov	w1, 16
	b	.L204
	.p2align 3
.L209:
	ldr	x6, [x29, 80]
	mov	w5, w23
	mov	w4, w22
	mov	w3, w21
	mov	w2, w20
	mov	w0, w19
	bl	VDMHAL_V4R3C1_ArrangeMem_Normal
	b	.L208
	.size	VDMHAL_V4R3C1_ArrangeMem, .-VDMHAL_V4R3C1_ArrangeMem
	.align	3
.LC85:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_ResetVdm
	.type	VDMHAL_V4R3C1_ResetVdm, %function
VDMHAL_V4R3C1_ResetVdm:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w21, w0
	mov	x0, x30
	bl	_mcount
	cmp	w21, wzr
	ble	.L211
	ldr	x2, .LC86
	mov	w4, 0
	ldr	x1, .LC88
	mov	w3, w21
	add	x2, x2, 224
	mov	w0, 0
	bl	dprint_vfmw
.L210:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L211:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L223
	sxtw	x22, w21
	ldr	x24, .LC91
	lsl	x0, x22, 6
	ldr	x20, .LC92
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x1, x0, x22
	ldr	x2, [x20]
	add	x0, x0, x1, lsl 2
	ldr	x0, [x24, x0]
	ldr	w25, [x0, 36]
	ldr	w23, [x2, 120]
	tbz	x23, 0, .L210
	ldr	x26, .LC93
	mov	w0, 2
	bfi	w23, w0, 8, 2
	str	w23, [x2, 120]
	mov	w19, 0
	orr	w23, w23, 64
	ldr	x0, [x26, 224]
	blr	x0
	ldr	x0, [x20]
	str	w23, [x0, 120]
	b	.L215
	.p2align 3
.L224:
	add	w19, w19, 1
	cmp	w19, 1000
	beq	.L216
.L215:
	ldr	x1, [x26, 232]
	mov	x0, 30
	blr	x1
	ldr	x0, [x20]
	ldr	w0, [x0, 372]
	tbz	x0, 2, .L224
	cmp	w19, 999
	bgt	.L216
	ldr	x2, .LC86
	mov	w3, w21
	ldr	x1, .LC97
	mov	w0, 0
	add	x2, x2, 224
	bl	dprint_vfmw
.L218:
	ldr	x0, [x20]
	and	w23, w23, -65
	str	w23, [x0, 120]
	and	w23, w23, -769
	ldr	x0, [x26, 224]
	blr	x0
	lsl	x0, x22, 6
	ldr	x1, [x20]
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x22, x0, x22
	str	w23, [x1, 120]
	add	x22, x0, x22, lsl 2
	ldr	x0, [x24, x22]
	str	w25, [x0, 36]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L216:
	ldr	x2, .LC86
	mov	w3, w21
	ldr	x1, .LC95
	mov	w0, 0
	add	x2, x2, 224
	bl	dprint_vfmw
	b	.L218
.L223:
	ldr	x1, .LC90
	mov	x2, 0
	bl	dprint_vfmw
	b	.L210
	.size	VDMHAL_V4R3C1_ResetVdm, .-VDMHAL_V4R3C1_ResetVdm
	.align	3
.LC86:
	.xword	.LANCHOR0
	.align	3
.LC88:
	.xword	.LC87
	.align	3
.LC90:
	.xword	.LC89
	.align	3
.LC91:
	.xword	g_HwMem
	.align	3
.LC92:
	.xword	g_pstRegCrg
	.align	3
.LC93:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC95:
	.xword	.LC94
	.align	3
.LC97:
	.xword	.LC96
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_SetSmmuPageTableAddr
	.type	VDMHAL_V4R3C1_SetSmmuPageTableAddr, %function
VDMHAL_V4R3C1_SetSmmuPageTableAddr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC98
	ldr	x3, [x0, 376]
	cbz	x3, .L225
	add	x2, x29, 60
	add	x1, x29, 56
	add	x0, x29, 52
	blr	x3
	cbnz	w19, .L227
	ldr	x0, .LC99
	ldp	w3, w2, [x29, 52]
	ldr	w1, [x29, 60]
	ldr	x0, [x0]
	add	x0, x0, 61440
	str	w3, [x0, 524]
	str	w2, [x0, 772]
	str	w1, [x0, 776]
.L225:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L227:
	ldr	x20, .LC100
	mov	w3, w19
	ldr	x21, .LC102
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
	.size	VDMHAL_V4R3C1_SetSmmuPageTableAddr, .-VDMHAL_V4R3C1_SetSmmuPageTableAddr
	.align	3
.LC98:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC99:
	.xword	g_HwMem
	.align	3
.LC100:
	.xword	.LANCHOR0
	.align	3
.LC102:
	.xword	.LC101
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_EnableSmmu
	.type	VDMHAL_V4R3C1_EnableSmmu, %function
VDMHAL_V4R3C1_EnableSmmu:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC104
	mov	w1, 8
	ldr	x0, [x0]
	add	x0, x0, 61440
	str	w1, [x0]
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V4R3C1_EnableSmmu, .-VDMHAL_V4R3C1_EnableSmmu
	.align	3
.LC104:
	.xword	g_HwMem
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_GlbResetX
	.type	VDMHAL_V4R3C1_GlbResetX, %function
VDMHAL_V4R3C1_GlbResetX:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w23, w0
	mov	x0, x30
	bl	_mcount
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L244
	ldr	x20, .LC108
	ldr	x0, [x20]
	ldr	w22, [x0, 120]
	tbnz	x22, 0, .L245
.L232:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L245:
	ldr	x21, .LC109
	mov	w1, 2
	bfi	w22, w1, 8, 2
	str	w22, [x0, 120]
	mov	w19, 0
	orr	w22, w22, 16
	ldr	x0, [x21, 224]
	blr	x0
	ldr	x0, [x20]
	str	w22, [x0, 120]
	b	.L236
	.p2align 3
.L246:
	add	w19, w19, 1
	cmp	w19, 1000
	beq	.L237
.L236:
	ldr	x1, [x21, 232]
	mov	x0, 30
	blr	x1
	ldr	x0, [x20]
	ldr	w0, [x0, 372]
	tbz	x0, 0, .L246
	cmp	w19, 999
	bgt	.L237
	ldr	x2, .LC105
	mov	w3, w23
	ldr	x1, .LC113
	mov	w0, 0
	add	x2, x2, 288
	bl	dprint_vfmw
.L239:
	ldr	x0, [x20]
	and	w22, w22, -17
	str	w22, [x0, 120]
	and	w22, w22, -769
	ldr	x0, [x21, 224]
	blr	x0
	ldr	x0, [x20]
	str	w22, [x0, 120]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L237:
	ldr	x2, .LC105
	mov	w3, w23
	ldr	x1, .LC111
	mov	w0, 0
	add	x2, x2, 288
	bl	dprint_vfmw
	b	.L239
.L244:
	ldr	x2, .LC105
	mov	w3, -121438208
	ldr	x1, .LC107
	add	x2, x2, 288
	bl	dprint_vfmw
	b	.L232
	.size	VDMHAL_V4R3C1_GlbResetX, .-VDMHAL_V4R3C1_GlbResetX
	.align	3
.LC105:
	.xword	.LANCHOR0
	.align	3
.LC107:
	.xword	.LC106
	.align	3
.LC108:
	.xword	g_pstRegCrg
	.align	3
.LC109:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC111:
	.xword	.LC110
	.align	3
.LC113:
	.xword	.LC112
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_GlbReset
	.type	VDMHAL_V4R3C1_GlbReset, %function
VDMHAL_V4R3C1_GlbReset:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L250
	mov	w0, 0
	bl	VDMHAL_V4R3C1_GlbResetX
.L247:
	ldp	x29, x30, [sp], 16
	ret
.L250:
	ldr	x2, .LC114
	mov	w3, -121438208
	ldr	x1, .LC115
	add	x2, x2, 312
	bl	dprint_vfmw
	b	.L247
	.size	VDMHAL_V4R3C1_GlbReset, .-VDMHAL_V4R3C1_GlbReset
	.align	3
.LC114:
	.xword	.LANCHOR0
	.align	3
.LC115:
	.xword	.LC106
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_ClearIntState
	.type	VDMHAL_V4R3C1_ClearIntState, %function
VDMHAL_V4R3C1_ClearIntState:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	sxtw	x19, w0
	mov	x0, x30
	mov	x20, x19
	bl	_mcount
	ldr	x21, .LC117
	ldr	x0, .LC116
	add	x1, x21, x19, lsl 6
	ldrsw	x1, [x1, 8]
	ldr	x0, [x0, x1, lsl 3]
	cbz	x0, .L261
	ldr	w22, [x0, 1232]
.L252:
	cmp	w20, wzr
	bgt	.L263
	lsl	x0, x19, 6
	ldr	x23, .LC120
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x20, x0, x19
	add	x20, x0, x20, lsl 2
	ldr	x0, [x23, x20]
	cbz	x0, .L264
.L255:
	cmp	w22, 1
	bne	.L262
	add	x19, x21, x19, lsl 6
	ldr	w1, [x19, 44]
	cmp	w1, 1
	beq	.L262
	ldr	w2, [x0, 28]
	cmp	w1, 2
	beq	.L265
	cmp	w1, 3
	bne	.L251
	mov	w1, -15
	str	w1, [x0, 32]
	b	.L251
	.p2align 3
.L263:
	ldr	x2, .LC118
	mov	w4, 0
	ldr	x1, .LC119
	mov	w3, w20
	add	x2, x2, 336
	mov	w0, 0
	bl	dprint_vfmw
.L251:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L262:
	mov	w1, -1
	str	w1, [x0, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L261:
	mov	w22, 0
	b	.L252
	.p2align 3
.L264:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L256
	str	x0, [x23, x20]
	b	.L255
	.p2align 3
.L265:
	mov	w1, -12
	str	w1, [x0, 32]
	b	.L251
.L256:
	ldr	x1, .LC122
	mov	w0, 0
	bl	dprint_vfmw
	b	.L251
	.size	VDMHAL_V4R3C1_ClearIntState, .-VDMHAL_V4R3C1_ClearIntState
	.align	3
.LC116:
	.xword	s_pstVfmwChan
	.align	3
.LC117:
	.xword	g_VdmDrvParam
	.align	3
.LC118:
	.xword	.LANCHOR0
	.align	3
.LC119:
	.xword	.LC87
	.align	3
.LC120:
	.xword	g_HwMem
	.align	3
.LC122:
	.xword	.LC121
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_ClearMMUIntState
	.type	VDMHAL_V4R3C1_ClearMMUIntState, %function
VDMHAL_V4R3C1_ClearMMUIntState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	sxtw	x19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, wzr
	bgt	.L271
	lsl	x3, x19, 6
	ldr	x20, .LC125
	sub	x3, x3, x19
	lsl	x3, x3, 2
	sub	x19, x3, x19
	add	x19, x3, x19, lsl 2
	ldr	x0, [x20, x19]
	cbz	x0, .L272
.L269:
	add	x0, x0, 61440
	mov	w1, 7
	str	w1, [x0, 44]
.L266:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L271:
	ldr	x2, .LC123
	mov	w3, w19
	ldr	x1, .LC124
	mov	w4, 0
	add	x2, x2, 368
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L272:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L270
	str	x0, [x20, x19]
	b	.L269
.L270:
	ldr	x1, .LC126
	mov	w0, 0
	bl	dprint_vfmw
	b	.L266
	.size	VDMHAL_V4R3C1_ClearMMUIntState, .-VDMHAL_V4R3C1_ClearMMUIntState
	.align	3
.LC123:
	.xword	.LANCHOR0
	.align	3
.LC124:
	.xword	.LC87
	.align	3
.LC125:
	.xword	g_HwMem
	.align	3
.LC126:
	.xword	.LC121
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_MaskInt
	.type	VDMHAL_V4R3C1_MaskInt, %function
VDMHAL_V4R3C1_MaskInt:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	sxtw	x19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, wzr
	bgt	.L278
	lsl	x3, x19, 6
	ldr	x20, .LC129
	sub	x3, x3, x19
	lsl	x3, x3, 2
	sub	x19, x3, x19
	add	x19, x3, x19, lsl 2
	ldr	x0, [x20, x19]
	cbz	x0, .L279
.L276:
	mov	w1, -1
	str	w1, [x0, 36]
.L273:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L278:
	ldr	x2, .LC127
	mov	w3, w19
	ldr	x1, .LC128
	mov	w4, 0
	add	x2, x2, 400
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L279:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L277
	str	x0, [x20, x19]
	b	.L276
.L277:
	ldr	x1, .LC130
	mov	w0, 0
	bl	dprint_vfmw
	b	.L273
	.size	VDMHAL_V4R3C1_MaskInt, .-VDMHAL_V4R3C1_MaskInt
	.align	3
.LC127:
	.xword	.LANCHOR0
	.align	3
.LC128:
	.xword	.LC87
	.align	3
.LC129:
	.xword	g_HwMem
	.align	3
.LC130:
	.xword	.LC121
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_GetIntMaskCfg
	.type	VDMHAL_V4R3C1_GetIntMaskCfg, %function
VDMHAL_V4R3C1_GetIntMaskCfg:
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
	.size	VDMHAL_V4R3C1_GetIntMaskCfg, .-VDMHAL_V4R3C1_GetIntMaskCfg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_EnableInt
	.type	VDMHAL_V4R3C1_EnableInt, %function
VDMHAL_V4R3C1_EnableInt:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC132
	sxtw	x0, w19
	ldr	x2, .LC131
	add	x1, x1, x0, lsl 6
	ldrsw	x1, [x1, 8]
	ldr	x1, [x2, x1, lsl 3]
	cbz	x1, .L291
	ldr	w20, [x1, 1232]
.L284:
	cmp	w19, wzr
	bgt	.L292
	lsl	x19, x0, 6
	ldr	x21, .LC135
	sub	x19, x19, x0
	lsl	x19, x19, 2
	sub	x0, x19, x0
	add	x19, x19, x0, lsl 2
	ldr	x0, [x21, x19]
	cbz	x0, .L293
.L287:
	mov	w1, -6
	mov	w2, -2
	cmp	w20, 1
	csel	w1, w1, w2, eq
	str	w1, [x0, 36]
.L283:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L292:
	ldr	x2, .LC133
	mov	w3, w19
	ldr	x1, .LC134
	mov	w4, 0
	add	x2, x2, 424
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L291:
	mov	w20, 0
	b	.L284
	.p2align 3
.L293:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L288
	str	x0, [x21, x19]
	b	.L287
.L288:
	ldr	x1, .LC136
	mov	w0, 0
	bl	dprint_vfmw
	b	.L283
	.size	VDMHAL_V4R3C1_EnableInt, .-VDMHAL_V4R3C1_EnableInt
	.align	3
.LC131:
	.xword	s_pstVfmwChan
	.align	3
.LC132:
	.xword	g_VdmDrvParam
	.align	3
.LC133:
	.xword	.LANCHOR0
	.align	3
.LC134:
	.xword	.LC87
	.align	3
.LC135:
	.xword	g_HwMem
	.align	3
.LC136:
	.xword	.LC121
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_CheckReg
	.type	VDMHAL_V4R3C1_CheckReg, %function
VDMHAL_V4R3C1_CheckReg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w22, w0
	mov	x0, x30
	sxtw	x19, w1
	bl	_mcount
	cmp	w19, wzr
	bgt	.L311
	lsl	x0, x19, 6
	ldr	x21, .LC140
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x20, x0, x19
	add	x20, x0, x20, lsl 2
	ldr	x0, [x21, x20]
	cbz	x0, .L312
.L297:
	sub	w0, w22, #1
	cmp	w0, 6
	bls	.L313
	ldr	x2, .LC137
	mov	w3, w22
	ldr	x1, .LC144
	mov	w0, 0
	add	x2, x2, 448
	bl	dprint_vfmw
	mov	w0, 0
.L310:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L313:
	ldr	x1, .LC145
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx304
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx304:
	.section	.rodata
	.align	0
	.align	2
.L304:
	.byte	(.L308 - .Lrtx304) / 4
	.byte	(.L305 - .Lrtx304) / 4
	.byte	(.L306 - .Lrtx304) / 4
	.byte	(.L307 - .Lrtx304) / 4
	.byte	(.L309 - .Lrtx304) / 4
	.byte	(.L299 - .Lrtx304) / 4
	.byte	(.L301 - .Lrtx304) / 4
	.text
	.p2align 3
.L309:
	mov	x1, 61480
.L303:
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
.L308:
	mov	x1, 28
	b	.L303
	.p2align 3
.L307:
	mov	x1, 40
	b	.L303
	.p2align 3
.L306:
	mov	x1, 36
	b	.L303
	.p2align 3
.L305:
	mov	x1, 32
	b	.L303
	.p2align 3
.L301:
	mov	x1, 62272
	b	.L303
	.p2align 3
.L299:
	mov	x1, 62304
	b	.L303
	.p2align 3
.L312:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L298
	str	x0, [x21, x20]
	b	.L297
	.p2align 3
.L311:
	ldr	x2, .LC137
	mov	w3, w19
	ldr	x1, .LC139
	mov	w0, 0
	add	x2, x2, 448
	bl	dprint_vfmw
	mov	w0, -1
	b	.L310
.L298:
	ldr	x2, .LC137
	mov	w0, 0
	ldr	x1, .LC142
	add	x2, x2, 448
	bl	dprint_vfmw
	mov	w0, 0
	b	.L310
	.size	VDMHAL_V4R3C1_CheckReg, .-VDMHAL_V4R3C1_CheckReg
	.align	3
.LC137:
	.xword	.LANCHOR0
	.align	3
.LC139:
	.xword	.LC138
	.align	3
.LC140:
	.xword	g_HwMem
	.align	3
.LC142:
	.xword	.LC141
	.align	3
.LC144:
	.xword	.LC143
	.align	3
.LC145:
	.xword	.L304
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_ReadMMUMask
	.type	VDMHAL_V4R3C1_ReadMMUMask, %function
VDMHAL_V4R3C1_ReadMMUMask:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	sxtw	x19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, wzr
	ble	.L317
	ldr	x2, .LC147
	mov	w3, w19
	ldr	x1, .LC149
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L317:
	lsl	x0, x19, 6
	ldr	x1, .LC146
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
	.size	VDMHAL_V4R3C1_ReadMMUMask, .-VDMHAL_V4R3C1_ReadMMUMask
	.align	3
.LC146:
	.xword	g_HwMem
	.align	3
.LC147:
	.xword	.LANCHOR1
	.align	3
.LC149:
	.xword	.LC148
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_WriteMMUMask
	.type	VDMHAL_V4R3C1_WriteMMUMask, %function
VDMHAL_V4R3C1_WriteMMUMask:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	sxtw	x19, w1
	bl	_mcount
	cmp	w19, wzr
	ble	.L321
	ldr	x2, .LC151
	mov	w3, w19
	ldr	x1, .LC152
	mov	w4, 1
	add	x2, x2, 32
	mov	w0, 32
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L321:
	lsl	x0, x19, 6
	ldr	x1, .LC150
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
	.size	VDMHAL_V4R3C1_WriteMMUMask, .-VDMHAL_V4R3C1_WriteMMUMask
	.align	3
.LC150:
	.xword	g_HwMem
	.align	3
.LC151:
	.xword	.LANCHOR1
	.align	3
.LC152:
	.xword	.LC101
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_PrepareDec
	.type	VDMHAL_V4R3C1_PrepareDec, %function
VDMHAL_V4R3C1_PrepareDec:
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
	cbz	x22, .L341
	cmp	w21, wzr
	bgt	.L342
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
	cmp	w20, 17
	bls	.L343
.L340:
	mov	w0, -1
	b	.L324
	.p2align 3
.L343:
	ldr	x0, .LC157
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx327
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx327:
	.section	.rodata
	.align	0
	.align	2
.L327:
	.byte	(.L337 - .Lrtx327) / 4
	.byte	(.L328 - .Lrtx327) / 4
	.byte	(.L329 - .Lrtx327) / 4
	.byte	(.L330 - .Lrtx327) / 4
	.byte	(.L340 - .Lrtx327) / 4
	.byte	(.L331 - .Lrtx327) / 4
	.byte	(.L332 - .Lrtx327) / 4
	.byte	(.L340 - .Lrtx327) / 4
	.byte	(.L333 - .Lrtx327) / 4
	.byte	(.L334 - .Lrtx327) / 4
	.byte	(.L335 - .Lrtx327) / 4
	.byte	(.L335 - .Lrtx327) / 4
	.byte	(.L335 - .Lrtx327) / 4
	.byte	(.L336 - .Lrtx327) / 4
	.byte	(.L340 - .Lrtx327) / 4
	.byte	(.L337 - .Lrtx327) / 4
	.byte	(.L338 - .Lrtx327) / 4
	.byte	(.L339 - .Lrtx327) / 4
	.text
	.p2align 3
.L337:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	H264HAL_V4R3C1_StartDec
.L324:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L338:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	HEVCHAL_V4R3C1_StartDec
	b	.L324
	.p2align 3
.L336:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	VP8HAL_V4R3C1_StartDec
	b	.L324
	.p2align 3
.L335:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	VP6HAL_V4R3C1_StartDec
	b	.L324
	.p2align 3
.L334:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	RV9HAL_V4R3C1_StartDec
	b	.L324
	.p2align 3
.L333:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	RV8HAL_V4R3C1_StartDec
	b	.L324
	.p2align 3
.L332:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	AVSHAL_V4R3C1_StartDec
	b	.L324
	.p2align 3
.L331:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	DIVX3HAL_V4R3C1_StartDec
	b	.L324
	.p2align 3
.L330:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	MP2HAL_V4R3C1_StartDec
	b	.L324
	.p2align 3
.L329:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	MP4HAL_V4R3C1_StartDec
	b	.L324
	.p2align 3
.L328:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	VC1HAL_V4R3C1_StartDec
	b	.L324
	.p2align 3
.L339:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	VP9HAL_V4R3C1_StartDec
	b	.L324
	.p2align 3
.L342:
	ldr	x2, .LC153
	mov	w3, w21
	ldr	x1, .LC156
	mov	w4, 0
	add	x2, x2, 64
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L341:
	ldr	x2, .LC153
	mov	x3, 0
	ldr	x1, .LC155
	mov	w0, 0
	add	x2, x2, 64
	bl	dprint_vfmw
	mov	w0, -1
	b	.L324
	.size	VDMHAL_V4R3C1_PrepareDec, .-VDMHAL_V4R3C1_PrepareDec
	.align	3
.LC153:
	.xword	.LANCHOR1
	.align	3
.LC155:
	.xword	.LC154
	.align	3
.LC156:
	.xword	.LC87
	.align	3
.LC157:
	.xword	.L327
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_IsVdmReady
	.type	VDMHAL_V4R3C1_IsVdmReady, %function
VDMHAL_V4R3C1_IsVdmReady:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sxtw	x0, w19
	ldr	x2, .LC158
	lsl	x1, x0, 6
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x0, x1, x0
	add	x0, x1, x0, lsl 2
	ldr	x0, [x2, x0]
	cbz	x0, .L349
	cmp	w19, wzr
	ble	.L350
	ldr	x2, .LC161
	mov	w4, 1
	ldr	x1, .LC163
	mov	w3, w19
	add	x2, x2, 96
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, 0
.L346:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L350:
	ldr	w0, [x0, 28]
	ldr	x19, [sp, 16]
	ubfx	x0, x0, 17, 1
	ldp	x29, x30, [sp], 32
	ret
.L349:
	ldr	x2, .LC161
	ldr	x3, .LC160
	ldr	x1, .LC162
	add	x2, x2, 96
	bl	dprint_vfmw
	mov	w0, -1
	b	.L346
	.size	VDMHAL_V4R3C1_IsVdmReady, .-VDMHAL_V4R3C1_IsVdmReady
	.align	3
.LC158:
	.xword	g_HwMem
	.align	3
.LC160:
	.xword	.LC159
	.align	3
.LC161:
	.xword	.LANCHOR1
	.align	3
.LC162:
	.xword	.LC6
	.align	3
.LC163:
	.xword	.LC148
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_IsVdmRun
	.type	VDMHAL_V4R3C1_IsVdmRun, %function
VDMHAL_V4R3C1_IsVdmRun:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sxtw	x0, w19
	ldr	x2, .LC164
	lsl	x1, x0, 6
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x0, x1, x0
	add	x0, x1, x0, lsl 2
	ldr	x0, [x2, x0]
	cbz	x0, .L356
	cmp	w19, wzr
	ble	.L357
	ldr	x2, .LC167
	mov	w4, 1
	ldr	x1, .LC168
	mov	w3, w19
	add	x2, x2, 128
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, 1
.L353:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L357:
	ldr	w0, [x0, 40]
	ldr	x19, [sp, 16]
	cmp	w0, 1
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L356:
	ldr	x1, .LC166
	bl	dprint_vfmw
	mov	w0, 0
	b	.L353
	.size	VDMHAL_V4R3C1_IsVdmRun, .-VDMHAL_V4R3C1_IsVdmRun
	.align	3
.LC164:
	.xword	g_HwMem
	.align	3
.LC166:
	.xword	.LC165
	.align	3
.LC167:
	.xword	.LANCHOR1
	.align	3
.LC168:
	.xword	.LC148
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_IsVdhDecOver
	.type	VDMHAL_V4R3C1_IsVdhDecOver, %function
VDMHAL_V4R3C1_IsVdhDecOver:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	sxtw	x0, w20
	ldr	x1, .LC169
	lsl	x2, x0, 6
	sub	x2, x2, x0
	lsl	x2, x2, 2
	sub	x0, x2, x0
	add	x0, x2, x0, lsl 2
	ldr	x0, [x1, x0]
	cbz	x0, .L366
	mov	w1, w20
	mov	w0, w19
	bl	VDMHAL_V4R3C1_CheckReg
	cmp	w19, 2
	beq	.L363
	cmp	w19, 3
	beq	.L363
	cmp	w19, 1
	ubfx	x0, x0, 17, 1
	beq	.L360
	ldr	x2, .LC171
	mov	w3, w19
	ldr	x1, .LC173
	mov	w0, 0
	add	x2, x2, 152
	bl	dprint_vfmw
	mov	w0, 0
.L360:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L363:
	and	w0, w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L366:
	ldr	x2, .LC171
	ldr	x3, .LC170
	ldr	x1, .LC172
	add	x2, x2, 152
	bl	dprint_vfmw
	mov	w0, -1
	b	.L360
	.size	VDMHAL_V4R3C1_IsVdhDecOver, .-VDMHAL_V4R3C1_IsVdhDecOver
	.align	3
.LC169:
	.xword	g_HwMem
	.align	3
.LC170:
	.xword	.LC159
	.align	3
.LC171:
	.xword	.LANCHOR1
	.align	3
.LC172:
	.xword	.LC6
	.align	3
.LC173:
	.xword	.LC143
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_IsVdhPartDecOver
	.type	VDMHAL_V4R3C1_IsVdhPartDecOver, %function
VDMHAL_V4R3C1_IsVdhPartDecOver:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	sxtw	x0, w20
	ldr	x1, .LC174
	lsl	x2, x0, 6
	sub	x2, x2, x0
	lsl	x2, x2, 2
	sub	x0, x2, x0
	add	x0, x2, x0, lsl 2
	ldr	x0, [x1, x0]
	cbz	x0, .L375
	mov	w1, w20
	mov	w0, w19
	bl	VDMHAL_V4R3C1_CheckReg
	cmp	w19, 1
	beq	.L371
	cmp	w19, 2
	ubfx	x0, x0, 2, 1
	bne	.L376
.L369:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L376:
	ldr	x2, .LC176
	mov	w3, w19
	ldr	x1, .LC178
	mov	w0, 0
	add	x2, x2, 184
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L371:
	ubfx	x0, x0, 19, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L375:
	ldr	x2, .LC176
	ldr	x3, .LC175
	ldr	x1, .LC177
	add	x2, x2, 184
	bl	dprint_vfmw
	mov	w0, -1
	b	.L369
	.size	VDMHAL_V4R3C1_IsVdhPartDecOver, .-VDMHAL_V4R3C1_IsVdhPartDecOver
	.align	3
.LC174:
	.xword	g_HwMem
	.align	3
.LC175:
	.xword	.LC159
	.align	3
.LC176:
	.xword	.LANCHOR1
	.align	3
.LC177:
	.xword	.LC6
	.align	3
.LC178:
	.xword	.LC143
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_UpdateHardwareInfo
	.type	VDMHAL_V4R3C1_UpdateHardwareInfo, %function
VDMHAL_V4R3C1_UpdateHardwareInfo:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w21, w0
	mov	x0, x30
	bl	_mcount
	cmp	w21, wzr
	bgt	.L378
	ldr	x4, .LC179
	ldr	w0, [x4]
	cmp	w0, 1
	beq	.L379
	add	x0, x4, 4
	add	x4, x4, 128
	b	.L382
	.p2align 3
.L418:
	cmp	x0, x4
	beq	.L417
.L382:
	ldr	w1, [x0]
	add	x0, x0, 4
	cmp	w1, 1
	bne	.L418
.L379:
	sxtw	x19, w21
	ldr	x24, .LC184
	lsl	x0, x19, 6
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x1, x0, x19
	add	x0, x0, x1, lsl 2
	ldr	x2, [x24, x0]
	cbz	x2, .L419
	lsl	x0, x19, 2
	ldr	x20, .LC185
	sub	x1, x0, x19
	ldr	w3, [x2, 12]
	lsl	x0, x1, 4
	mov	w22, 1
	sub	x0, x0, x1
	lsl	x0, x0, 2
	add	x1, x20, x0
	str	w3, [x20, x0]
	ldr	w2, [x2, 28]
	str	w2, [x1, 4]
.L385:
	lsl	x0, x19, 6
	and	w23, w2, 131071
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x1, x0, x19
	add	x0, x0, x1, lsl 2
	add	x0, x24, x0
	ldr	w0, [x0, 56]
	bl	MEM_Phy2Vir
	cbz	x0, .L420
	sub	w1, w23, #1
	cmp	w1, 199
	bhi	.L394
	lsl	w1, w23, 2
	sub	w1, w1, #4
	lsl	x1, x1, 2
	add	x3, x1, 8
.L388:
	lsl	x2, x19, 2
	ldr	w4, [x0, x1]
	sub	x2, x2, x19
	lsl	x1, x2, 4
	sub	x2, x1, x2
	lsl	x1, x19, 6
	sub	x1, x1, x19
	add	x2, x20, x2, lsl 2
	lsl	x1, x1, 2
	str	w4, [x2, 16]
	ldr	w3, [x0, x3]
	sub	x0, x1, x19
	str	w3, [x2, 20]
	add	x1, x1, x0, lsl 2
	ldr	x1, [x24, x1]
	ldr	w3, [x1, 208]
	ldr	w0, [x1, 212]
	stp	w3, w0, [x2, 8]
	b	.L389
	.p2align 3
.L417:
	sxtw	x19, w21
	ldr	x24, .LC184
	lsl	x0, x19, 6
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x1, x0, x19
	add	x0, x0, x1, lsl 2
	ldr	x1, [x24, x0]
	cbz	x1, .L421
	lsl	x0, x19, 2
	ldr	x20, .LC185
	sub	x2, x0, x19
	ldr	w3, [x1, 12]
	lsl	x0, x2, 4
	mov	w22, 0
	sub	x0, x0, x2
	lsl	x0, x0, 2
	add	x2, x20, x0
	str	w3, [x20, x0]
	ldr	w0, [x1, 28]
	str	w0, [x2, 4]
.L386:
	lsl	x0, x19, 2
	ldr	w2, [x1, 4096]
	sub	x4, x0, x19
	ldr	w5, [x1, 4116]
	lsl	x0, x4, 4
	ldr	w3, [x1, 208]
	sub	x0, x0, x4
	add	x0, x20, x0, lsl 2
	stp	w2, w5, [x0, 16]
	ldr	w2, [x1, 212]
	str	w3, [x0, 8]
	str	w2, [x0, 12]
	cbnz	w22, .L389
	ldr	w5, [x1, 176]
	ldr	w2, [x1, 180]
	stp	w5, w2, [x0, 24]
	ldr	w4, [x1, 184]
	ldr	w3, [x1, 188]
	ldr	w2, [x1, 192]
	stp	w4, w3, [x0, 32]
	str	w2, [x0, 40]
.L389:
	mov	w0, 180
	add	x4, x1, 32768
	add	x1, x4, 256
	smull	x2, w21, w0
	add	x0, x2, 52
	add	x2, x2, 180
	add	x0, x20, x0
	add	x3, x20, x2
	.p2align 2
.L390:
	ldr	w2, [x1], 4
	str	w2, [x0], 4
	cmp	x3, x0
	bne	.L390
	mov	w0, 0
	cbnz	w22, .L404
	lsl	x1, x19, 2
	ldr	w3, [x4, 384]
	sub	x19, x1, x19
	ldr	w2, [x4, 388]
	lsl	x1, x19, 4
	sub	x1, x1, x19
	add	x20, x20, x1, lsl 2
	stp	w2, w3, [x20, 44]
.L404:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L394:
	mov	x3, 8
	mov	x1, 0
	b	.L388
.L378:
	ldr	x2, .LC180
	mov	w4, 0
	ldr	x1, .LC181
	mov	w3, w21
	add	x2, x2, 216
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L404
.L421:
	mov	w22, 0
.L391:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L384
	lsl	x2, x19, 6
	lsl	x3, x19, 2
	sub	x2, x2, x19
	sub	x4, x3, x19
	lsl	x2, x2, 2
	lsl	x3, x4, 4
	sub	x1, x2, x19
	sub	x3, x3, x4
	ldr	x20, .LC185
	lsl	x3, x3, 2
	add	x2, x2, x1, lsl 2
	add	x1, x20, x3
	str	x0, [x24, x2]
	ldr	w2, [x0, 12]
	str	w2, [x20, x3]
	ldr	w2, [x0, 28]
	str	w2, [x1, 4]
	cbnz	w22, .L385
	mov	x1, x0
	b	.L386
.L419:
	mov	w22, 1
	b	.L391
.L420:
	ldr	x2, .LC180
	ldr	x3, .LC188
	ldr	x1, .LC189
	add	x2, x2, 216
	bl	dprint_vfmw
	mov	w0, -1
	b	.L404
.L384:
	ldr	x1, .LC186
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L404
	.size	VDMHAL_V4R3C1_UpdateHardwareInfo, .-VDMHAL_V4R3C1_UpdateHardwareInfo
	.align	3
.LC179:
	.xword	g_DSPState
	.align	3
.LC180:
	.xword	.LANCHOR1
	.align	3
.LC181:
	.xword	.LC87
	.align	3
.LC184:
	.xword	g_HwMem
	.align	3
.LC185:
	.xword	g_BackUp
	.align	3
.LC186:
	.xword	.LC121
	.align	3
.LC188:
	.xword	.LC187
	.align	3
.LC189:
	.xword	.LC6
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_ReadMsgSlot
	.type	VDMHAL_V4R3C1_ReadMsgSlot, %function
VDMHAL_V4R3C1_ReadMsgSlot:
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
	beq	.L426
	cmp	w19, 800
	bhi	.L427
	ldr	x3, .LC194
	ubfiz	x2, x19, 2, 30
	mov	x1, x21
	mov	x0, x20
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 0
.L424:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L427:
	ldr	x1, .LC193
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L424
	.p2align 3
.L426:
	ldr	x1, .LC191
	mov	x3, x21
	mov	x2, x20
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L424
	.size	VDMHAL_V4R3C1_ReadMsgSlot, .-VDMHAL_V4R3C1_ReadMsgSlot
	.align	3
.LC191:
	.xword	.LC190
	.align	3
.LC193:
	.xword	.LC192
	.align	3
.LC194:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_WriteMsgSlot
	.type	VDMHAL_V4R3C1_WriteMsgSlot, %function
VDMHAL_V4R3C1_WriteMsgSlot:
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
	beq	.L429
	sub	w0, w21, #1
	cmp	w0, 255
	bhi	.L429
	ldr	x3, .LC197
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
.L429:
	ldr	x1, .LC196
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	VDMHAL_V4R3C1_WriteMsgSlot, .-VDMHAL_V4R3C1_WriteMsgSlot
	.align	3
.LC196:
	.xword	.LC195
	.align	3
.LC197:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_CfgRpMsg
	.type	VDMHAL_V4R3C1_CfgRpMsg, %function
VDMHAL_V4R3C1_CfgRpMsg:
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
	cbz	x0, .L471
	ldr	w2, [x19, 44]
	sub	w0, w2, #1
	cmp	w0, 199
	bhi	.L472
	ldp	w2, w0, [x19, 28]
	ldr	w4, [x19, 64]
	mov	w3, 0
	ldrb	w5, [x19]
	lsl	w2, w2, w4
	lsl	w0, w0, w4
	cmp	w5, 1
	add	w1, w2, 255
	and	w1, w1, -256
	lsl	w5, w1, 4
	beq	.L473
.L436:
	ldr	w2, [x19, 4]
	cmp	w2, 16
	beq	.L437
	add	w0, w0, 31
	mov	w23, 8
	and	w0, w0, -32
	madd	w0, w0, w1, w3
.L458:
	ldr	w1, [x19, 20]
	mov	w4, 0
	str	w1, [x20]
	mov	w2, 0
	ldr	w1, [x19, 20]
	add	w1, w0, w1
	str	w1, [x20, 4]
	ldr	w1, [x19, 8]
	str	w1, [x20, 8]
	ldr	w1, [x19, 8]
	add	w0, w0, w1
	str	w0, [x20, 12]
	str	w5, [x20, 16]
	str	w3, [x20, 20]
	ldp	w1, w0, [x19, 28]
	sub	w0, w0, #1
	sub	w1, w1, #1
	bfi	w2, w0, 0, 9
	bfi	w4, w1, 0, 9
	strh	w2, [x29, 74]
	strh	w4, [x29, 72]
	ldr	w0, [x29, 72]
	str	w0, [x20, 24]
	ldr	w0, [x19, 52]
	ldp	w21, w22, [x19, 28]
	sub	w0, w0, #1
	cmp	w0, 1
	bls	.L474
.L439:
	ldr	w0, [x19, 56]
	mov	w11, 0
	cbz	w0, .L475
.L440:
	cmp	w0, 1
	beq	.L456
.L480:
	sub	w11, w11, #1
	uxth	w11, w11
.L457:
	ldrb	w4, [x19]
	ldr	w2, [x19, 52]
	ldr	w3, [x19, 64]
	ldrb	w0, [x29, 74]
	and	w2, w2, 3
	ldrb	w1, [x29, 75]
	sub	w3, w3, #4
	bfi	w0, w4, 0, 1
	strh	w11, [x29, 72]
	bfi	w0, w2, 4, 2
	bfi	w1, w3, 0, 2
	bfi	w0, w2, 6, 2
	bfi	w1, w23, 2, 4
	strb	w0, [x29, 74]
	mov	w0, 0
	strb	w1, [x29, 75]
	ldr	w1, [x29, 72]
	str	w1, [x20, 28]
.L469:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L475:
	ldr	w0, [x19, 64]
	cmp	w0, 6
	beq	.L461
	cmp	w0, 5
	beq	.L462
	cmp	w0, 4
	mov	w2, 8
	beq	.L441
	ldr	x1, .LC205
	mov	w0, 1
	bl	dprint_vfmw
	mov	w2, 1
.L441:
	ldr	w8, [x19, 44]
	cmp	w8, wzr
	ble	.L470
	mul	w12, w22, w21
	mov	w4, 0
	mov	w6, 0
	sub	w13, w12, #1
	mov	w11, 0
	sub	w9, w2, #1
	b	.L444
	.p2align 3
.L478:
	ldrsh	w6, [x10, 70]
	sub	w6, w6, #1
	add	w6, w6, w2
	udiv	w6, w6, w2
	mul	w6, w6, w2
	cmp	w0, w6
	bgt	.L447
.L446:
	add	w4, w4, 1
	cmp	w4, w8
	bge	.L476
.L455:
	cmp	w4, 199
	bgt	.L477
.L444:
	add	x10, x19, x4, sxtw 2
	cmp	w4, wzr
	ldrsh	w1, [x10, 74]
	sub	w0, w1, #1
	add	w0, w0, w2
	udiv	w0, w0, w2
	mul	w0, w0, w2
	bgt	.L478
	ccmp	w0, w6, 0, ne
	ble	.L446
.L449:
	ldrsh	w1, [x10, 72]
	cmp	w12, w0
	csel	w0, w0, w13, hi
	add	w5, w11, 1
	udiv	w1, w1, w2
	mul	w1, w1, w2
	cmp	w1, w0
	csel	w1, w1, wzr, le
	cmp	w5, 252
	bgt	.L479
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
	blt	.L455
.L476:
	ldr	w0, [x19, 56]
	cmp	w0, 1
	bne	.L480
	.p2align 2
.L456:
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
	b	.L457
	.p2align 3
.L437:
	madd	w0, w0, w1, w3
	mov	w23, 10
	b	.L458
	.p2align 3
.L473:
	adds	w3, w2, 511
	add	w2, w2, 1022
	csel	w2, w2, w3, mi
	add	w4, w0, 126
	and	w2, w2, -512
	cmp	w2, wzr
	add	w3, w2, 63
	csel	w2, w3, w2, lt
	adds	w6, w0, 63
	csel	w3, w4, w6, mi
	asr	w2, w2, 6
	asr	w3, w3, 6
	lsl	w2, w2, 1
	lsl	w3, w3, 5
	mul	w3, w2, w3
	b	.L436
	.p2align 3
.L474:
	add	w22, w22, w22, lsr 31
	asr	w22, w22, 1
	b	.L439
	.p2align 3
.L450:
	udiv	w0, w0, w2
	ldrsh	w1, [x5, 76]
	udiv	w1, w1, w2
	mul	w0, w0, w2
	mul	w1, w1, w2
	cmp	w0, w1
	add	w14, w1, 1
	bhi	.L451
	sub	w1, w4, #1
	cmp	w0, w14
	add	x1, x19, x1, sxtw 2
	beq	.L451
	ldrsh	w1, [x1, 74]
	sub	w1, w1, #1
	add	w1, w1, w2
	udiv	w1, w1, w2
	mul	w1, w1, w2
	cmp	w0, w1
	bhi	.L449
.L451:
	cmp	w7, 199
	mov	w4, w3
	bgt	.L481
	ldrsh	w1, [x5, 78]
.L447:
	add	w3, w4, 1
	add	x5, x19, x4, sxtw 2
	cmp	w8, w3
	add	w0, w9, w1
	add	w7, w3, 1
	bgt	.L450
	udiv	w0, w0, w2
	mul	w0, w0, w2
	b	.L449
.L462:
	mov	w2, 4
	b	.L441
	.p2align 3
.L481:
	add	x0, x19, x3, sxtw 2
	ldrsh	w0, [x0, 74]
	sub	w0, w0, #1
	add	w0, w0, w2
	udiv	w0, w0, w2
	mul	w0, w0, w2
	b	.L449
.L477:
	ldr	x2, .LC200
	mov	w3, 2158
	ldr	x1, .LC207
	mov	w0, 0
	add	x2, x2, 280
	bl	dprint_vfmw
.L470:
	mov	w11, 0
	ldr	w0, [x19, 56]
	b	.L440
.L461:
	mov	w2, 2
	b	.L441
.L479:
	mov	w0, 1
	str	w0, [x19, 56]
	b	.L456
.L472:
	ldr	x1, .LC203
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L469
.L471:
	ldr	x2, .LC200
	mov	w0, 0
	ldr	x3, .LC199
	ldr	x1, .LC201
	add	x2, x2, 256
	bl	dprint_vfmw
	mov	w0, -1
	b	.L469
	.size	VDMHAL_V4R3C1_CfgRpMsg, .-VDMHAL_V4R3C1_CfgRpMsg
	.align	3
.LC199:
	.xword	.LC198
	.align	3
.LC200:
	.xword	.LANCHOR1
	.align	3
.LC201:
	.xword	.LC6
	.align	3
.LC203:
	.xword	.LC202
	.align	3
.LC205:
	.xword	.LC204
	.align	3
.LC207:
	.xword	.LC206
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_CfgRpReg
	.type	VDMHAL_V4R3C1_CfgRpReg, %function
VDMHAL_V4R3C1_CfgRpReg:
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
	bgt	.L508
	ldr	x0, [x22]
	cbz	x0, .L509
.L485:
	ldr	x19, .LC211
	ldr	w3, [x22, 64]
	ldrb	w0, [x19]
	and	w3, w3, -16
	str	w3, [x29, 60]
	cmp	w0, 1
	beq	.L510
	mov	x0, x20
	mov	w2, 16
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	mov	w3, 53763
	movk	w3, 0x2000, lsl 16
	str	w3, [x29, 60]
	cmp	w0, 1
	beq	.L511
	mov	x0, x20
	mov	w2, 12
	mov	w1, 2
	mov	w22, 3075
	movk	w22, 0x30, lsl 16
	bl	VDH_Record_RegData
	str	w22, [x29, 60]
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L512
	mov	x0, x20
	mov	w3, w22
	mov	w2, 60
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L513
	mov	x0, x20
	mov	w3, w22
	mov	w2, 64
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L514
	mov	x0, x20
	mov	w3, w22
	mov	w2, 68
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L515
	mov	x0, x20
	mov	w3, w22
	mov	w2, 72
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L516
	mov	x0, x20
	mov	w3, w22
	mov	w2, 76
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L517
	mov	x0, x20
	mov	w3, w22
	mov	w2, 80
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L518
	mov	x0, x20
	mov	w3, w22
	mov	w2, 84
	mov	w1, 2
	bl	VDH_Record_RegData
	mov	w0, 0
.L505:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L510:
	sxtw	x1, w21
	ldr	x2, .LC212
	lsl	x0, x1, 6
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x4, x0, x1
	add	x0, x0, x4, lsl 2
	ldr	x0, [x2, x0]
	str	w3, [x0, 16]
.L488:
	lsl	x0, x1, 6
	mov	w4, 53763
	sub	x0, x0, x1
	movk	w4, 0x2000, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 12]
.L490:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 60]
.L492:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 64]
.L494:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 68]
.L496:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 72]
.L498:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 76]
.L500:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 80]
.L502:
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
.L509:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L486
	str	x0, [x22]
	b	.L485
	.p2align 3
.L508:
	ldr	x2, .LC208
	mov	w4, 0
	ldr	x1, .LC209
	mov	w3, w21
	add	x2, x2, 304
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L505
.L486:
	ldr	x1, .LC210
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L505
.L515:
	ldr	x2, .LC212
	sxtw	x1, w21
	b	.L496
.L514:
	ldr	x2, .LC212
	sxtw	x1, w21
	b	.L494
.L513:
	ldr	x2, .LC212
	sxtw	x1, w21
	b	.L492
.L512:
	ldr	x2, .LC212
	sxtw	x1, w21
	b	.L490
.L517:
	ldr	x2, .LC212
	sxtw	x1, w21
	b	.L500
.L516:
	ldr	x2, .LC212
	sxtw	x1, w21
	b	.L498
.L518:
	ldr	x2, .LC212
	sxtw	x1, w21
	b	.L502
.L511:
	ldr	x2, .LC212
	sxtw	x1, w21
	b	.L488
	.size	VDMHAL_V4R3C1_CfgRpReg, .-VDMHAL_V4R3C1_CfgRpReg
	.align	3
.LC208:
	.xword	.LANCHOR1
	.align	3
.LC209:
	.xword	.LC87
	.align	3
.LC210:
	.xword	.LC121
	.align	3
.LC211:
	.xword	g_HalDisable
	.align	3
.LC212:
	.xword	g_HwMem
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_MakeDecReport
	.type	VDMHAL_V4R3C1_MakeDecReport, %function
VDMHAL_V4R3C1_MakeDecReport:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L549
	ldr	x23, [x19, 8]
	ldr	w21, [x19]
	ldr	w22, [x19, 16]
	cbz	x23, .L550
	sxtw	x22, w22
	ldr	x20, .LC221
	lsl	x0, x22, 6
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x1, x0, x22
	add	x0, x0, x1, lsl 2
	ldr	x0, [x20, x0]
	cbz	x0, .L523
	ldr	x2, .LC222
	add	x0, x2, 4
	add	x2, x2, 128
	ldr	w1, [x2, -128]
	cmp	w1, 1
	bne	.L526
	b	.L538
	.p2align 3
.L552:
	cmp	x0, x2
	beq	.L551
.L526:
	ldr	w1, [x0]
	add	x0, x0, 4
	cmp	w1, 1
	bne	.L552
.L538:
	mov	w19, w1
.L524:
	ldr	x3, .LC226
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
	ldr	x4, .LC227
	add	x2, x0, x3, lsl 2
	add	x2, x20, x2
	add	x1, x4, x1, lsl 2
	ldr	w0, [x2, 40]
	str	w0, [x23, 4]
	ldr	w1, [x1, 4]
	ubfx	x0, x1, 17, 2
	cmp	w0, 1
	beq	.L539
	and	w1, w1, 131072
	cmp	w1, wzr
	ccmp	w21, 3, 0, ne
	cset	w1, ne
.L527:
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
	beq	.L553
.L528:
	cmp	w2, 200
	bhi	.L554
.L530:
	lsl	x0, x22, 6
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x1, x0, x22
	add	x0, x0, x1, lsl 2
	add	x20, x20, x0
	ldr	w21, [x20, 56]
	mov	w0, w21
	bl	MEM_Phy2Vir
	cbz	x0, .L555
	lsl	x3, x22, 2
	ldr	x19, .LC232
	sub	x3, x3, x22
	ldr	w2, [x23, 12]
	mov	x1, x0
	add	x20, x22, x3, lsl 3
	lsl	w2, w2, 2
	add	x0, x19, x20, lsl 7
	bl	VDMHAL_V4R3C1_ReadMsgSlot
	ldr	w0, [x23, 12]
	cbz	w0, .L535
	sub	w2, w0, #1
	mov	x5, 22
	add	x1, x23, 18
	mov	w0, 2
	add	x5, x5, x2, uxtw 2
	lsl	x3, x20, 5
	add	x5, x23, x5
	.p2align 2
.L534:
	sub	w2, w0, #1
	add	x4, x3, x0, uxtw
	add	x2, x3, x2
	add	w0, w0, 4
	ldr	w2, [x19, x2, lsl 2]
	strh	w2, [x1, -2]
	ldr	w2, [x19, x4, lsl 2]
	strh	w2, [x1], 4
	cmp	x5, x1
	bne	.L534
.L535:
	mov	w0, 6
	bl	IsDprintTypeEnable
	cbnz	w0, .L556
.L521:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L553:
	cmp	w19, 1
	beq	.L557
	ldr	x1, .LC228
	ldrb	w1, [x1]
	cbnz	w1, .L528
	ldrb	w0, [x0, 19]
	and	w0, w0, 3
	cmp	w0, 2
	bne	.L528
	mov	w0, 1
	strh	wzr, [x23, 16]
	str	w0, [x23, 12]
	mov	w0, 0
	strh	wzr, [x23, 18]
	b	.L521
	.p2align 3
.L551:
	mov	w19, 0
	b	.L524
	.p2align 3
.L556:
	ldr	x1, .LC234
	mov	w0, 6
	ldr	w2, [x23, 12]
	mov	w20, 0
	bl	dprint_vfmw
	mov	w2, w21
	ldr	x1, .LC236
	lsl	x21, x22, 2
	mov	w0, 6
	sub	x21, x21, x22
	bl	dprint_vfmw
	ldr	x24, .LC238
	add	x21, x22, x21, lsl 3
	lsl	x21, x21, 5
	.p2align 2
.L536:
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
	bhi	.L536
	ldr	x1, .LC240
	mov	w0, 6
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L539:
	mov	w1, 0
	b	.L527
	.p2align 3
.L554:
	ldr	x1, .LC230
	mov	w3, 200
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x23, 12]
	b	.L530
	.p2align 3
.L557:
	ldr	w0, [x0, 16]
	ubfx	x0, x0, 21, 2
	cmp	w0, 2
	bne	.L528
	strh	wzr, [x23, 16]
	mov	w0, 0
	strh	wzr, [x23, 18]
	str	w19, [x23, 12]
	b	.L521
.L555:
	ldr	x2, .LC217
	ldr	x3, .LC231
	ldr	x1, .LC218
	add	x2, x2, 328
	bl	dprint_vfmw
	mov	w0, -1
	b	.L521
.L523:
	ldr	x2, .LC217
	ldr	x3, .LC223
.L547:
	ldr	x1, .LC218
	mov	w0, 0
	add	x2, x2, 328
	bl	dprint_vfmw
	mov	w0, -1
	b	.L521
.L550:
	ldr	x2, .LC217
	ldr	x3, .LC220
	b	.L547
.L549:
	ldr	x2, .LC217
	ldr	x3, .LC216
	b	.L547
	.size	VDMHAL_V4R3C1_MakeDecReport, .-VDMHAL_V4R3C1_MakeDecReport
	.align	3
.LC216:
	.xword	.LC215
	.align	3
.LC217:
	.xword	.LANCHOR1
	.align	3
.LC218:
	.xword	.LC6
	.align	3
.LC220:
	.xword	.LC219
	.align	3
.LC221:
	.xword	g_HwMem
	.align	3
.LC222:
	.xword	g_DSPState
	.align	3
.LC223:
	.xword	.LC159
	.align	3
.LC226:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC227:
	.xword	g_BackUp
	.align	3
.LC228:
	.xword	g_not_allow_H264FullPictureRepair_flag
	.align	3
.LC230:
	.xword	.LC229
	.align	3
.LC231:
	.xword	.LC187
	.align	3
.LC232:
	.xword	g_UpMsg
	.align	3
.LC234:
	.xword	.LC233
	.align	3
.LC236:
	.xword	.LC235
	.align	3
.LC238:
	.xword	.LC237
	.align	3
.LC240:
	.xword	.LC239
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_PrepareRepair
	.type	VDMHAL_V4R3C1_PrepareRepair, %function
VDMHAL_V4R3C1_PrepareRepair:
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
	ldr	x25, .LC241
	lsl	x0, x19, 6
	cmp	w19, wzr
	sub	x0, x0, x19
	mov	x21, x19
	lsl	x0, x0, 2
	sub	x20, x0, x19
	add	x20, x0, x20, lsl 2
	add	x27, x20, x25
	bgt	.L569
	ldr	x0, [x20, x25]
	cbz	x0, .L570
	cbz	w26, .L571
.L563:
	cmp	w26, 1
	mov	w20, 0
	beq	.L572
.L560:
	mov	w0, w20
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L570:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L562
	str	x0, [x20, x25]
	cbnz	w26, .L563
	.p2align 2
.L571:
	lsl	x0, x19, 3
	ldr	x25, .LC246
	sub	x0, x0, x19
	lsl	x0, x0, 3
	sub	x0, x0, x19
	lsl	x0, x0, 1
	sub	x0, x0, x19
	add	x0, x25, x0, lsl 4
	ldr	w1, [x0, 44]
	cmp	w1, wzr
	ble	.L564
	cmp	w22, 6
	bne	.L565
	ldrb	w1, [x23, 17]
	mov	w2, 0
	cmp	w1, 1
	csel	w1, w1, w2, eq
	str	w1, [x0, 924]
.L565:
	mov	x4, x24
	mov	w3, w21
	mov	x2, x23
	mov	x1, x27
	mov	w0, w22
	mov	w20, 0
	bl	VDMHAL_V4R3C1_CfgRpReg
	lsl	x0, x19, 3
	mov	w2, w21
	sub	x0, x0, x19
	mov	x1, x27
	lsl	x0, x0, 3
	sub	x0, x0, x19
	lsl	x0, x0, 1
	sub	x0, x0, x19
	add	x0, x25, x0, lsl 4
	bl	VDMHAL_V4R3C1_CfgRpMsg
	ldr	x27, [sp, 80]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L572:
	cmp	w22, 6
	bne	.L567
	ldrb	w0, [x23, 17]
	cmp	w0, 1
	bne	.L567
	lsl	x0, x19, 3
	ldr	x25, .LC246
	sub	x0, x0, x19
	lsl	x0, x0, 3
	sub	x0, x0, x19
	lsl	x0, x0, 1
	sub	x19, x0, x19
	lsl	x19, x19, 4
	add	x0, x25, x19
	ldr	w1, [x0, 916]
	cmp	w1, wzr
	ble	.L567
	mov	w1, 2
	mov	x4, x24
	mov	w3, w21
	mov	x2, x23
	str	w1, [x0, 924]
	mov	x1, x27
	mov	w0, w22
	bl	VDMHAL_V4R3C1_CfgRpReg
	add	x0, x19, 872
	mov	w2, w21
	mov	x1, x27
	add	x0, x25, x0
	bl	VDMHAL_V4R3C1_CfgRpMsg
	ldr	x27, [sp, 80]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L569:
	ldr	x2, .LC242
	mov	w4, 0
	ldr	x1, .LC243
	mov	w3, w19
	add	x2, x2, 360
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L560
	.p2align 3
.L567:
	ldr	x1, .LC250
	mov	w0, 0
	mov	w20, 0
	bl	dprint_vfmw
	b	.L560
.L564:
	ldr	x1, .LC248
	mov	w0, 0
	mov	w20, 0
	bl	dprint_vfmw
	b	.L560
.L562:
	ldr	x1, .LC245
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L560
	.size	VDMHAL_V4R3C1_PrepareRepair, .-VDMHAL_V4R3C1_PrepareRepair
	.align	3
.LC241:
	.xword	g_HwMem
	.align	3
.LC242:
	.xword	.LANCHOR1
	.align	3
.LC243:
	.xword	.LC87
	.align	3
.LC245:
	.xword	.LC244
	.align	3
.LC246:
	.xword	g_RepairParam
	.align	3
.LC248:
	.xword	.LC247
	.align	3
.LC250:
	.xword	.LC249
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_StartHwRepair
	.type	VDMHAL_V4R3C1_StartHwRepair, %function
VDMHAL_V4R3C1_StartHwRepair:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	sxtw	x20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x21, .LC251
	ldrb	w4, [x21]
	cmp	w4, 1
	bne	.L597
	cmp	w20, wzr
	ble	.L598
	ldr	x22, .LC253
	mov	w3, w20
	ldr	x23, .LC254
	mov	w0, 32
	add	x2, x22, 392
	mov	x1, x23
	bl	dprint_vfmw
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L581
	mov	x0, x19
	mov	w3, -2
	mov	w2, 36
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L594
.L576:
	cbz	x19, .L599
.L590:
	ldr	x1, .LC257
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
.L573:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L598:
	sxtw	x0, w20
	ldr	x3, .LC252
	lsl	x1, x0, 6
	mov	w4, 67108864
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x2, x1, x0
	add	x1, x1, x2, lsl 2
	ldr	x1, [x3, x1]
	str	w4, [x1, 8]
.L579:
	lsl	x1, x0, 6
	mov	w2, -2
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x0, x1, x0
	add	x0, x1, x0, lsl 2
	ldr	x0, [x3, x0]
	str	w2, [x0, 36]
.L577:
	ldr	x0, .LC258
	ldr	x0, [x0, 224]
	blr	x0
	cmp	w20, wzr
	ble	.L593
	ldr	x22, .LC253
	ldr	x23, .LC254
.L586:
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
	b	.L573
	.p2align 3
.L575:
	cmp	w20, wzr
	ble	.L591
	ldr	x22, .LC253
	ldr	x23, .LC254
.L581:
	mov	w4, 1
	mov	w3, w20
	add	x2, x22, 392
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	ldrb	w0, [x21]
	cmp	w0, 1
	bne	.L576
.L594:
	ldr	x0, .LC258
	ldr	x0, [x0, 224]
	blr	x0
	b	.L586
	.p2align 3
.L597:
	mov	x0, x19
	mov	w3, 67108864
	mov	w2, 8
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L575
	mov	x0, x19
	mov	w3, -2
	mov	w2, 36
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L577
	cbnz	x19, .L590
.L599:
	ldr	x2, .LC253
	mov	x3, 0
	ldr	x1, .LC256
	mov	w0, 0
	add	x2, x2, 408
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L593:
	lsl	x0, x20, 6
	ldr	x1, .LC252
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
	b	.L573
.L591:
	ldr	x3, .LC252
	sxtw	x0, w20
	b	.L579
	.size	VDMHAL_V4R3C1_StartHwRepair, .-VDMHAL_V4R3C1_StartHwRepair
	.align	3
.LC251:
	.xword	g_HalDisable
	.align	3
.LC252:
	.xword	g_HwMem
	.align	3
.LC253:
	.xword	.LANCHOR1
	.align	3
.LC254:
	.xword	.LC101
	.align	3
.LC256:
	.xword	.LC255
	.align	3
.LC257:
	.xword	g_VdmDrvParam
	.align	3
.LC258:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_CalVdhClkSkip
	.type	VDMHAL_V4R3C1_CalVdhClkSkip, %function
VDMHAL_V4R3C1_CalVdhClkSkip:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x0, x30
	bl	_mcount
	ldr	x24, .LC260
	ldr	w28, [x24, 128]
	tbnz	w28, #31, .L632
	ldr	x25, .LC263
	add	x20, x24, 132
	ldr	x27, .LC266
	add	x24, x24, 256
	ldr	x26, .LC265
	mov	w23, 30
	mov	w22, 0
	mov	w21, 0
	add	x25, x25, 440
	mov	w19, 0
	b	.L603
	.p2align 3
.L635:
	mov	w3, w28
	mov	x2, x25
	mov	x1, x26
	mov	w0, 1
	bl	dprint_vfmw
.L605:
	cmp	x24, x20
	beq	.L633
.L622:
	ldr	w28, [x20], 4
	tbnz	w28, #31, .L634
.L603:
	mov	w0, w28
	bl	VCTRL_IsChanActive
	cbnz	w0, .L635
	mov	w0, w28
	bl	FSP_GetInst
	cbz	x0, .L606
	ldp	w1, w0, [x0, 40]
	adds	w19, w1, 15
	add	w1, w1, 30
	add	w21, w0, 30
	csel	w19, w1, w19, mi
	adds	w0, w0, 15
	asr	w19, w19, 4
	csel	w0, w21, w0, mi
	asr	w21, w0, 4
.L606:
	ldr	x1, [x27, w28, sxtw 3]
	mov	w0, w28
	ldr	w1, [x1, 1528]
	cmp	w1, 31
	csel	w23, w23, w1, lt
	bl	VCTRL_GetVidStd
	cmp	w0, 17
	bls	.L636
.L625:
	cmp	x24, x20
	mov	w22, 0
	bne	.L622
.L633:
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
.L636:
	ldr	x1, .LC267
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx609
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx609:
	.section	.rodata
	.align	0
	.align	2
.L609:
	.byte	(.L618 - .Lrtx609) / 4
	.byte	(.L618 - .Lrtx609) / 4
	.byte	(.L618 - .Lrtx609) / 4
	.byte	(.L618 - .Lrtx609) / 4
	.byte	(.L625 - .Lrtx609) / 4
	.byte	(.L618 - .Lrtx609) / 4
	.byte	(.L618 - .Lrtx609) / 4
	.byte	(.L625 - .Lrtx609) / 4
	.byte	(.L618 - .Lrtx609) / 4
	.byte	(.L618 - .Lrtx609) / 4
	.byte	(.L618 - .Lrtx609) / 4
	.byte	(.L618 - .Lrtx609) / 4
	.byte	(.L618 - .Lrtx609) / 4
	.byte	(.L618 - .Lrtx609) / 4
	.byte	(.L625 - .Lrtx609) / 4
	.byte	(.L619 - .Lrtx609) / 4
	.byte	(.L618 - .Lrtx609) / 4
	.byte	(.L618 - .Lrtx609) / 4
	.text
	.p2align 3
.L618:
	mul	w22, w19, w21
	mul	w22, w22, w23
	b	.L605
	.p2align 3
.L634:
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
.L601:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L619:
	mul	w22, w19, w21
	mul	w22, w22, w23
	lsl	w22, w22, 1
	b	.L605
.L632:
	mov	w0, 25
	b	.L601
	.size	VDMHAL_V4R3C1_CalVdhClkSkip, .-VDMHAL_V4R3C1_CalVdhClkSkip
	.align	3
.LC260:
	.xword	g_ChanCtx
	.align	3
.LC263:
	.xword	.LANCHOR1
	.align	3
.LC265:
	.xword	.LC264
	.align	3
.LC266:
	.xword	s_pstVfmwChan
	.align	3
.LC267:
	.xword	.L609
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_GetVdmClk
	.type	VDMHAL_V4R3C1_GetVdmClk, %function
VDMHAL_V4R3C1_GetVdmClk:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w20, 3
	bls	.L645
.L638:
	ldr	x0, .LC270
	sbfiz	x19, x19, 6, 32
	mov	w1, 500
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L645:
	ldr	x0, .LC269
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx640
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx640:
	.section	.rodata
	.align	0
	.align	2
.L640:
	.byte	(.L638 - .Lrtx640) / 4
	.byte	(.L641 - .Lrtx640) / 4
	.byte	(.L642 - .Lrtx640) / 4
	.byte	(.L643 - .Lrtx640) / 4
	.text
	.p2align 3
.L642:
	ldr	x0, .LC270
	sbfiz	x19, x19, 6, 32
	mov	w1, 100
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L641:
	ldr	x0, .LC270
	sbfiz	x19, x19, 6, 32
	mov	w1, 540
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L643:
	ldr	x0, .LC270
	sbfiz	x19, x19, 6, 32
	mov	w1, 600
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMHAL_V4R3C1_GetVdmClk, .-VDMHAL_V4R3C1_GetVdmClk
	.align	3
.LC269:
	.xword	.L640
	.align	3
.LC270:
	.xword	g_VdmDrvParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_StartHwDecode
	.type	VDMHAL_V4R3C1_StartHwDecode, %function
VDMHAL_V4R3C1_StartHwDecode:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	w20, wzr
	ble	.L647
	ldr	x2, .LC271
	mov	w4, 0
	ldr	x1, .LC272
	mov	w3, w20
	add	x2, x2, 472
	mov	w0, 0
	bl	dprint_vfmw
.L646:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L647:
	ldr	x21, .LC273
	ldrb	w0, [x21]
	cmp	w0, 1
	bne	.L681
	ldr	x1, .LC276
	ldr	x2, [x1]
	ldr	w0, [x2, 120]
	ubfx	x3, x0, 8, 2
	cbz	w3, .L652
	and	w0, w0, -769
	str	w0, [x2, 120]
.L652:
	ldr	x24, .LC274
	sxtw	x22, w20
	ldr	x2, .LC275
	mov	w3, 500
	add	x0, x24, x22, lsl 6
	ldr	w23, [x0, 8]
	str	w3, [x0, 16]
	ldr	x0, [x2, w23, sxtw 3]
	ldr	w25, [x0, 1232]
.L651:
	ldr	x0, [x1]
	ldr	w1, [x0, 120]
	and	w1, w1, -258049
	str	w1, [x0, 120]
	ldr	w1, [x0, 120]
	orr	w1, w1, 131072
	str	w1, [x0, 120]
.L653:
	mov	w0, 12
	mov	x3, x19
	mov	w2, w20
	mov	w1, 3
	bl	SCD_ConfigReg
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L682
	mov	w1, 2
	mov	x0, x19
	mov	w3, -1431655766
	mov	w2, 156
	bl	VDH_Record_RegData
	ldr	x1, .LC277
	ldrb	w0, [x21]
	ldr	w1, [x1]
	cmp	w1, 1
	beq	.L683
.L655:
	mov	w3, 0
.L654:
	cmp	w0, 1
	beq	.L684
	mov	x0, x19
	mov	w2, 61472
	mov	w1, 2
	bl	VDH_Record_RegData
	cmp	w25, 1
	ldrb	w0, [x21]
	beq	.L685
.L658:
	mov	w3, -2
.L657:
	cmp	w0, 1
	beq	.L686
	mov	x0, x19
	mov	w2, 36
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L687
	cbz	x19, .L688
	mov	w0, 1
	strb	w20, [x19]
	stp	w0, w23, [x19, 4]
	mov	x0, x19
	bl	VDH_PostTask
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L685:
	mov	w3, -6
	b	.L657
	.p2align 3
.L683:
	mov	w3, 7
	b	.L654
	.p2align 3
.L681:
	mov	w3, 0
	mov	w2, 0
	mov	w1, 0
	mov	x0, x19
	sxtw	x22, w20
	bl	VDH_Record_RegData
	ldr	x24, .LC274
	ldr	x1, .LC275
	mov	w2, 500
	add	x0, x24, x22, lsl 6
	ldrb	w3, [x21]
	cmp	w3, 1
	ldr	w23, [x0, 8]
	str	w2, [x0, 16]
	ldr	x0, [x1, w23, sxtw 3]
	ldr	w25, [x0, 1232]
	beq	.L689
	mov	w3, 0
	mov	w2, 1
	mov	w1, 0
	mov	x0, x19
	bl	VDH_Record_RegData
	b	.L653
	.p2align 3
.L682:
	ldr	x2, .LC277
	lsl	x1, x22, 6
	sub	x1, x1, x22
	ldr	x26, .LC278
	lsl	x1, x1, 2
	ldr	w2, [x2]
	cmp	w2, 1
	sub	x2, x1, x22
	add	x1, x1, x2, lsl 2
	mov	w2, -1431655766
	ldr	x1, [x26, x1]
	str	w2, [x1, 156]
	bne	.L655
	mov	w3, 7
	b	.L656
	.p2align 3
.L684:
	ldr	x26, .LC278
.L656:
	lsl	x0, x22, 6
	cmp	w25, 1
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x1, x0, x22
	add	x0, x0, x1, lsl 2
	ldr	x0, [x26, x0]
	add	x0, x0, 61440
	str	w3, [x0, 32]
	beq	.L671
	mov	w0, 1
	b	.L658
	.p2align 3
.L686:
	ldr	x26, .LC278
.L659:
	lsl	x1, x22, 6
	ldr	x19, .LC279
	sub	x1, x1, x22
	mov	x0, 30
	lsl	x1, x1, 2
	sub	x2, x1, x22
	add	x1, x1, x2, lsl 2
	ldr	x1, [x26, x1]
	str	w3, [x1, 36]
	ldr	x1, [x19, 232]
	blr	x1
	ldr	x0, [x19, 224]
	blr	x0
.L662:
	lsl	x0, x22, 6
	mov	w2, 1
	sub	x1, x0, x22
	add	x24, x24, x0
	lsl	x0, x1, 2
	ldr	x3, .LC281
	sub	x22, x0, x22
	mov	w1, 4
	add	x22, x0, x22, lsl 2
	ldr	x0, [x26, x22]
	str	wzr, [x0]
	ldr	x0, [x26, x22]
	str	w2, [x0]
	ldr	x0, [x26, x22]
	str	wzr, [x0]
	ldr	w2, [x24, 8]
	mov	w0, w2
	ldr	w2, [x3, w2, sxtw 2]
	bl	VDEC_Lowdelay_Event_Time
	b	.L646
	.p2align 3
.L688:
	ldr	x2, .LC271
	mov	x3, 0
	ldr	x1, .LC280
	mov	w0, 0
	add	x2, x2, 472
	bl	dprint_vfmw
	b	.L646
	.p2align 3
.L671:
	mov	w3, -6
	b	.L659
.L689:
	ldr	x1, .LC276
	b	.L651
.L687:
	ldr	x19, .LC279
	mov	x0, 30
	ldr	x1, [x19, 232]
	blr	x1
	ldr	x0, [x19, 224]
	blr	x0
	ldr	x26, .LC278
	b	.L662
	.size	VDMHAL_V4R3C1_StartHwDecode, .-VDMHAL_V4R3C1_StartHwDecode
	.align	3
.LC271:
	.xword	.LANCHOR1
	.align	3
.LC272:
	.xword	.LC87
	.align	3
.LC273:
	.xword	g_HalDisable
	.align	3
.LC274:
	.xword	g_VdmDrvParam
	.align	3
.LC275:
	.xword	s_pstVfmwChan
	.align	3
.LC276:
	.xword	g_pstRegCrg
	.align	3
.LC277:
	.xword	mask_mmu_err_int
	.align	3
.LC278:
	.xword	g_HwMem
	.align	3
.LC279:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC280:
	.xword	.LC255
	.align	3
.LC281:
	.xword	g_LowDelaySeqIndex
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_GetCharacter
	.type	VDMHAL_V4R3C1_GetCharacter, %function
VDMHAL_V4R3C1_GetCharacter:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x2, .LC282
	mov	w3, 15
	ldr	x0, .LC283
	mov	w1, 4
	str	w3, [x2]
	str	w1, [x0]
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V4R3C1_GetCharacter, .-VDMHAL_V4R3C1_GetCharacter
	.align	3
.LC282:
	.xword	g_VdmCharacter
	.align	3
.LC283:
	.xword	g_eVdmVersion
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_WriteBigTitle1DYuv
	.type	VDMHAL_V4R3C1_WriteBigTitle1DYuv, %function
VDMHAL_V4R3C1_WriteBigTitle1DYuv:
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
	beq	.L735
	mov	w20, 2
	cmp	w0, w20
	csinc	w20, w20, wzr, ne
.L692:
	ldr	x0, [x29, 112]
	cbz	x0, .L691
	ldr	x0, .LC285
	mov	w4, 0
	add	x3, x29, 144
	mov	w2, 4194304
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L695
	ldr	x0, .LC289
	mov	w4, 0
	add	x3, x29, 176
	mov	w2, 4194304
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L695
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
	bne	.L696
	lsr	w1, w3, 1
	lsr	w0, w19, 1
	str	w1, [x29, 120]
	add	x1, x25, 2097152
	str	w0, [x29, 104]
	str	x1, [x29, 136]
	ldr	x28, .LC290
	ldr	x20, [x29, 152]
	cbz	w3, .L698
	mov	w27, 0
	str	wzr, [x29, 132]
	.p2align 2
.L697:
	cbz	w19, .L700
	ldr	w0, [x29, 124]
	lsr	w23, w27, 4
	ldr	w24, [x29, 132]
	mov	w26, 0
	mul	w0, w23, w0
	ubfiz	x23, x27, 8, 4
	add	x23, x0, x23
	.p2align 2
.L699:
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
	bhi	.L699
.L700:
	ldr	w0, [x29, 132]
	add	w27, w27, 1
	add	w0, w0, w19
	str	w0, [x29, 132]
	ldr	w0, [x29, 128]
	cmp	w0, w27
	bne	.L697
.L698:
	ldr	w0, [x29, 128]
	ldr	x3, [x28, 88]
	ldr	x2, [x29, 112]
	mul	w1, w19, w0
	mov	x0, x20
	blr	x3
	ldr	w0, [x29, 120]
	cbz	w0, .L790
	ldr	w1, [x29, 124]
	mov	w26, 0
	mov	w24, 0
	asr	w0, w1, 1
	str	w0, [x29, 132]
	.p2align 2
.L704:
	cbz	w19, .L706
	ldr	w0, [x29, 132]
	lsr	w22, w24, 3
	uxtw	x23, w26
	mov	w27, 0
	mul	w0, w22, w0
	ubfiz	x22, x24, 8, 3
	add	x22, x0, x22
	.p2align 2
.L703:
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
	bhi	.L703
.L706:
	ldr	w0, [x29, 120]
	add	w24, w24, 1
	add	w26, w26, w19
	cmp	w0, w24
	bne	.L704
	ldr	w0, [x29, 108]
	cmp	w0, 1
	beq	.L791
.L732:
	ldr	w0, [x29, 108]
	cbnz	w0, .L709
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
.L709:
	ldr	w0, [x29, 104]
	ldr	w1, [x29, 120]
.L785:
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
.L691:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
	.p2align 3
.L695:
	ldr	x1, .LC287
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
.L735:
	mov	w20, 0
	b	.L692
.L696:
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
	ldr	x28, .LC290
	ldr	x20, [x29, 152]
	bls	.L714
	ldr	w27, [x29, 120]
	.p2align 2
.L716:
	cbz	w19, .L717
	ldr	w0, [x29, 124]
	lsr	w24, w27, 4
	lsr	w23, w27, 1
	mov	w26, 0
	mul	w0, w24, w0
	mul	w23, w23, w19
	ubfiz	x24, x27, 8, 4
	add	x24, x0, x24
	.p2align 2
.L715:
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
	bhi	.L715
.L717:
	ldr	w0, [x29, 128]
	add	w27, w27, 2
	cmp	w0, w27
	bhi	.L716
.L714:
	ldr	w0, [x29, 128]
	ldr	x3, [x28, 88]
	ldr	x2, [x29, 112]
	mul	w1, w19, w0
	mov	x0, x20
	lsr	w1, w1, 1
	blr	x3
	ldr	w0, [x29, 132]
	cbz	w0, .L792
	ldr	w1, [x29, 124]
	mov	w26, 0
	mov	w24, 0
	asr	w0, w1, 1
	str	w0, [x29, 128]
	.p2align 2
.L721:
	cbz	w19, .L723
	ldr	w0, [x29, 128]
	lsr	w22, w24, 3
	uxtw	x23, w26
	mov	w27, 0
	mul	w0, w22, w0
	ubfiz	x22, x24, 8, 3
	add	x22, x0, x22
	.p2align 2
.L720:
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
	bhi	.L720
.L723:
	ldr	w0, [x29, 132]
	add	w24, w24, 1
	add	w26, w26, w19
	cmp	w0, w24
	bne	.L721
	ldr	w0, [x29, 108]
	cmp	w0, 1
	beq	.L793
	ldr	w0, [x29, 108]
	cbnz	w0, .L726
	ldr	w1, [x29, 120]
	ldr	w0, [x29, 132]
	cmp	w0, w1
	bls	.L729
	.p2align 2
.L730:
	ldr	w0, [x29, 120]
	ldr	w1, [x29, 132]
	add	w0, w0, 2
	str	w0, [x29, 120]
	cmp	w1, w0
	bhi	.L730
.L729:
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
.L726:
	ldr	w0, [x29, 104]
	ldr	w1, [x29, 132]
	b	.L785
.L791:
	mov	w0, 0
	mov	w6, 0
	.p2align 2
.L708:
	ldr	w1, [x29, 104]
	mov	w5, w0
	cbz	w1, .L710
	ldr	w1, [x29, 104]
	add	w5, w1, w0
	mov	w1, 1
	.p2align 2
.L707:
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
	bne	.L707
.L710:
	ldr	w0, [x29, 120]
	add	w6, w6, 1
	add	x20, x20, x19
	cmp	w0, w6
	mov	w0, w5
	bne	.L708
	b	.L709
.L793:
	ldr	w0, [x29, 120]
	mov	w7, 0
	mul	w1, w19, w0
	lsl	w0, w19, 1
	add	x20, x20, x1
	.p2align 2
.L725:
	ldr	w3, [x29, 104]
	cbz	w3, .L727
	lsr	w1, w7, 1
	mov	w2, 1
	mul	w1, w1, w3
	add	w6, w3, w1
	.p2align 2
.L724:
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
	bne	.L724
.L727:
	ldr	w1, [x29, 132]
	add	w7, w7, 2
	add	x20, x20, x0
	cmp	w1, w7
	bhi	.L725
	b	.L726
.L792:
	ldr	w0, [x29, 108]
	cmp	w0, 1
	beq	.L726
	ldr	w0, [x29, 108]
	cbz	w0, .L729
	b	.L726
.L790:
	ldr	w0, [x29, 108]
	cmp	w0, 1
	bne	.L732
	b	.L709
	.size	VDMHAL_V4R3C1_WriteBigTitle1DYuv, .-VDMHAL_V4R3C1_WriteBigTitle1DYuv
	.align	3
.LC285:
	.xword	.LC284
	.align	3
.LC287:
	.xword	.LC286
	.align	3
.LC289:
	.xword	.LC288
	.align	3
.LC290:
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
	ldr	x0, .LC291
	ldrb	w0, [x0]
	cmp	w0, 1
	bne	.L801
	cbnz	w19, .L797
	ldr	x0, .LC292
	ldr	x1, [x0]
	ldr	w0, [x1, 120]
	ubfx	x2, x0, 8, 2
	cmp	w20, w2
	beq	.L794
	bfi	w0, w20, 8, 2
	str	w0, [x1, 120]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L797:
	cmp	w19, 1
	beq	.L802
.L794:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L801:
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
.L802:
	ldr	x0, .LC292
	ldr	x1, [x0]
	ldr	w0, [x1, 120]
	bfi	w0, w20, 12, 5
	and	w0, w0, -131073
	str	w0, [x1, 120]
	ldr	w0, [x1, 120]
	orr	w0, w0, 131072
	str	w0, [x1, 120]
	b	.L794
	.size	CRG_ConfigReg, .-CRG_ConfigReg
	.align	3
.LC291:
	.xword	g_HalDisable
	.align	3
.LC292:
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
	ldr	x0, .LC293
	ldrb	w4, [x0]
	cmp	w4, 1
	bne	.L807
	cmp	w19, wzr
	ble	.L808
	ldr	x2, .LC295
	mov	w3, w19
	ldr	x1, .LC296
	mov	w0, 32
	add	x2, x2, 392
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L808:
	lsl	x0, x19, 6
	ldr	x1, .LC294
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
.L807:
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
.LC293:
	.xword	g_HalDisable
	.align	3
.LC294:
	.xword	g_HwMem
	.align	3
.LC295:
	.xword	.LANCHOR1
	.align	3
.LC296:
	.xword	.LC101
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.54177, %object
	.size	__func__.54177, 22
__func__.54177:
	.string	"VDMHAL_V4R3C1_OpenHAL"
	.zero	2
	.type	__func__.54251, %object
	.size	__func__.54251, 25
__func__.54251:
	.string	"VDMHAL_V4R3C1_CalcFsSize"
	.zero	7
	.type	__func__.54277, %object
	.size	__func__.54277, 24
__func__.54277:
	.string	"VDMHAL_V4R3C1_CalcFsNum"
	.type	__func__.54319, %object
	.size	__func__.54319, 32
__func__.54319:
	.string	"VDMHAL_V4R3C1_ArrangeMem_Normal"
	.type	__FUNCTION__.54320, %object
	.size	__FUNCTION__.54320, 32
__FUNCTION__.54320:
	.string	"VDMHAL_V4R3C1_ArrangeMem_Normal"
	.type	__func__.54263, %object
	.size	__func__.54263, 33
__func__.54263:
	.string	"VDMHAL_V4R3C1_FillMemArrangeInfo"
	.zero	7
	.type	__func__.54400, %object
	.size	__func__.54400, 34
__func__.54400:
	.string	"VDMHAL_V4R3C1_ArrangeMem_Specific"
	.zero	6
	.type	__func__.54423, %object
	.size	__func__.54423, 23
__func__.54423:
	.string	"VDMHAL_V4R3C1_ResetVdm"
	.zero	1
	.type	__func__.54433, %object
	.size	__func__.54433, 35
__func__.54433:
	.string	"VDMHAL_V4R3C1_SetSmmuPageTableAddr"
	.zero	5
	.type	__func__.54454, %object
	.size	__func__.54454, 24
__func__.54454:
	.string	"VDMHAL_V4R3C1_GlbResetX"
	.type	__func__.54443, %object
	.size	__func__.54443, 23
__func__.54443:
	.string	"VDMHAL_V4R3C1_GlbReset"
	.zero	1
	.type	__func__.54466, %object
	.size	__func__.54466, 28
__func__.54466:
	.string	"VDMHAL_V4R3C1_ClearIntState"
	.zero	4
	.type	__func__.54472, %object
	.size	__func__.54472, 31
__func__.54472:
	.string	"VDMHAL_V4R3C1_ClearMMUIntState"
	.zero	1
	.type	__func__.54478, %object
	.size	__func__.54478, 22
__func__.54478:
	.string	"VDMHAL_V4R3C1_MaskInt"
	.zero	2
	.type	__func__.54491, %object
	.size	__func__.54491, 24
__func__.54491:
	.string	"VDMHAL_V4R3C1_EnableInt"
	.type	__func__.54500, %object
	.size	__func__.54500, 23
__func__.54500:
	.string	"VDMHAL_V4R3C1_CheckReg"
	.align	3
.LANCHOR1 = . + 0
	.type	__func__.54514, %object
	.size	__func__.54514, 26
__func__.54514:
	.string	"VDMHAL_V4R3C1_ReadMMUMask"
	.zero	6
	.type	__func__.54519, %object
	.size	__func__.54519, 27
__func__.54519:
	.string	"VDMHAL_V4R3C1_WriteMMUMask"
	.zero	5
	.type	__func__.54550, %object
	.size	__func__.54550, 25
__func__.54550:
	.string	"VDMHAL_V4R3C1_PrepareDec"
	.zero	7
	.type	__func__.54555, %object
	.size	__func__.54555, 25
__func__.54555:
	.string	"VDMHAL_V4R3C1_IsVdmReady"
	.zero	7
	.type	__func__.54560, %object
	.size	__func__.54560, 23
__func__.54560:
	.string	"VDMHAL_V4R3C1_IsVdmRun"
	.zero	1
	.type	__func__.54566, %object
	.size	__func__.54566, 27
__func__.54566:
	.string	"VDMHAL_V4R3C1_IsVdhDecOver"
	.zero	5
	.type	__func__.54576, %object
	.size	__func__.54576, 31
__func__.54576:
	.string	"VDMHAL_V4R3C1_IsVdhPartDecOver"
	.zero	1
	.type	__func__.54591, %object
	.size	__func__.54591, 33
__func__.54591:
	.string	"VDMHAL_V4R3C1_UpdateHardwareInfo"
	.zero	7
	.type	__func__.54664, %object
	.size	__func__.54664, 23
__func__.54664:
	.string	"VDMHAL_V4R3C1_CfgRpMsg"
	.zero	1
	.type	__func__.54641, %object
	.size	__func__.54641, 24
__func__.54641:
	.string	"VDMHAL_CfgNotFullRepair"
	.type	__func__.54675, %object
	.size	__func__.54675, 23
__func__.54675:
	.string	"VDMHAL_V4R3C1_CfgRpReg"
	.zero	1
	.type	__func__.54688, %object
	.size	__func__.54688, 28
__func__.54688:
	.string	"VDMHAL_V4R3C1_MakeDecReport"
	.zero	4
	.type	__func__.54727, %object
	.size	__func__.54727, 28
__func__.54727:
	.string	"VDMHAL_V4R3C1_PrepareRepair"
	.zero	4
	.type	__func__.54914, %object
	.size	__func__.54914, 15
__func__.54914:
	.string	"MFDE_ConfigReg"
	.zero	1
	.type	__func__.54734, %object
	.size	__func__.54734, 28
__func__.54734:
	.string	"VDMHAL_V4R3C1_StartHwRepair"
	.zero	4
	.type	__func__.54773, %object
	.size	__func__.54773, 28
__func__.54773:
	.string	"VDMHAL_V4R3C1_CalVdhClkSkip"
	.zero	4
	.type	__func__.54796, %object
	.size	__func__.54796, 28
__func__.54796:
	.string	"VDMHAL_V4R3C1_StartHwDecode"
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
	ASCII(.string	"VDMHAL_V4R3C1_OpenHAL: Size error!" )
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
	ASCII(.string	"VDMHAL ArrangeMem HEVC 10 bit\n" )
	.zero	1
.LC32:
	ASCII(.string	"%s pstVfmwFrameSizeInfo = NULL\n" )
.LC36:
	ASCII(.string	"DelAllFrameMemRecord err in VDMHAL_V4R3C1_ArrangeMem!\n" )
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
	ASCII(.string	"VDMHAL_V4R3C1_CalcFsSize err!\n" )
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
	ASCII(.string	"VDMHAL_V4R3C1_ArrangeMem Mem addr is NULL" )
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
.LC83:
	ASCII(.string	"cann't allocate img slot" )
	.zero	7
.LC87:
	ASCII(.string	"%s: VdhId(%d) > %d\n" )
	.zero	4
.LC89:
	ASCII(.string	"VDMHAL_V4R3C1_ResetVdm: map vdm register fail, vir(reg) = (%p)\n" )
.LC94:
	ASCII(.string	"%s module id %d failed!\n" )
	.zero	7
.LC96:
	ASCII(.string	"%s module id %d success!\n" )
	.zero	6
.LC101:
	ASCII(.string	"%s: WR_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\n" )
	.zero	3
.LC106:
	ASCII(.string	"%s: map vdm register 0x%x failed!\n" )
	.zero	5
.LC110:
	ASCII(.string	"%s VdhId %d failed!\n" )
	.zero	3
.LC112:
	ASCII(.string	"%s VdhId %d success!\n" )
	.zero	2
.LC121:
	ASCII(.string	"vdm register virtual address not mapped, reset failed!\n" )
.LC138:
	ASCII(.string	"%s: VdhId(%d) Invalid!\n" )
.LC141:
	ASCII(.string	"%s: vdm register virtual address not mapped, reset failed!\n" )
	.zero	4
.LC143:
	ASCII(.string	"%s: unkown reg_id = %d\n" )
.LC148:
	ASCII(.string	"%s: RD_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\n" )
	.zero	3
.LC154:
	ASCII(.string	"%s: pDecParam(%p) = NULL\n" )
	.zero	6
.LC159:
	ASCII(.string	"VDM register not mapped yet!" )
	.zero	3
.LC165:
	ASCII(.string	"VDM register not mapped yet!\n" )
	.zero	2
.LC187:
	ASCII(.string	"can NOT map vir addr for up-msg" )
.LC190:
	ASCII(.string	"ReadUpMsgSlot error! pDst=%p, pSrc=%p\n" )
	.zero	1
.LC192:
	ASCII(.string	"ReadUpMsgSlot error! upmsg_size(%d) > 512\n" )
	.zero	5
.LC195:
	ASCII(.string	"WriteMsgSlot error!\n" )
	.zero	3
.LC198:
	ASCII(.string	"can not map repair msg virtual address!" )
.LC202:
	ASCII(.string	"ValidGroupNum=%d out of range!\n" )
.LC204:
	ASCII(.string	"align_mb error\n" )
.LC206:
	ASCII(.string	"[%s][%d]sclie_num is wrong! %d \n" )
	.zero	7
.LC215:
	ASCII(.string	"'pMakeDecReport' is NULL" )
	.zero	7
.LC219:
	ASCII(.string	"'pDecReport' is NULL" )
	.zero	3
.LC229:
	ASCII(.string	"pDecReport->DecSliceNum(%d) > %d, set to 0 for full repair.\n" )
	.zero	3
.LC233:
	ASCII(.string	"\n***** UpMsg DecSliceNum=%d\n" )
	.zero	3
.LC235:
	ASCII(.string	"\n***** Up Msg (phy addr: %#8x) *****\n" )
	.zero	2
.LC237:
	ASCII(.string	"\n0x%02x 0x%08x 0x%08x 0x%08x 0x%08x\n" )
	.zero	3
.LC239:
	ASCII(.string	"\n***** Up Msg print finished *****\n" )
	.zero	4
.LC244:
	ASCII(.string	"vdm register virtual address not mapped, VDMHAL_V200R003_PrepareRepair failed!\n" )
.LC247:
	ASCII(.string	"FIRST_REPAIR Parameter Error!\n" )
	.zero	1
.LC249:
	ASCII(.string	"SECOND_REPAIR Parameter Error!\n" )
.LC255:
	ASCII(.string	"%s: pMfdeTask(%p) = NULL\n" )
	.zero	6
.LC264:
	ASCII(.string	"%s The channel %d is not active\n" )
	.zero	7
.LC284:
	ASCII(.string	"BigTile1d_y" )
	.zero	4
.LC286:
	ASCII(.string	"failed mem_allocMemBlock BigTile_yuv save!\n" )
	.zero	4
.LC288:
	ASCII(.string	"BigTile1d_uv" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
