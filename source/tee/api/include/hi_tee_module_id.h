/*
 * Copyright (c) 2017, Hisilicon Limited
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef HI_TEE_MODULE_ID_H
#define HI_TEE_MODULE_ID_H

/*
 * Drv Module ID
 */

typedef enum tagMODULE_ID_E
{
    HI_MODULE_ID_LOG = 0,
    HI_MODULE_ID_MEM,
    HI_MODULE_ID_MMZ,
    HI_MODULE_ID_SMMU,
    HI_MODULE_ID_TIMER,
    HI_MODULE_ID_KLAD,
    HI_MODULE_ID_OTP,
    HI_MODULE_ID_CIPHER,
    HI_MODULE_ID_VFMW,
    HI_MODULE_ID_VO,
    HI_MODULE_ID_HDMI,
    HI_MODULE_ID_I2C,
    HI_MODULE_ID_PVR,
    HI_MODULE_ID_BEIDOU,
    HI_MODULE_ID_DISPCTRL,
    HI_MODULE_ID_DEMUX,        /**< The Module ID of Demux must be 15 */
    HI_MODULE_ID_PLCIPHER,     /**< The Module ID of Demux must be 16 */
    HI_MODULE_ID_PM,
    HI_MODULE_ID_CERT,
    HI_MODULE_ID_TALOAD,
    HI_MODULE_ID_SM,
    HI_MODULE_ID_VDP,
    HI_MODULE_ID_AVPLAY,
    HI_MODULE_ID_MAILBOX,
    HI_MODULE_ID_NETFLIX,
    HI_MODULE_ID_UNKNOWN,
    HI_MODULE_ID_BUTT
} HI_MODULE_ID_E;

typedef struct TEE_IOCTRL_ARGS
{
	unsigned long arg0;
	unsigned long arg1;
	unsigned long arg2;
	unsigned long arg3;
	unsigned long arg4;
	unsigned long arg5;
	unsigned long arg6;
	unsigned long arg7;
} TEE_IOCTRL_ARGS_ST;

#ifdef CFG_HI_TEE_VFMW_SUPPORT
#define TEE_VFMW_IOCTL_INIT                             0x1
#define TEE_VFMW_IOCTL_EXIT                             0x2
#define TEE_VFMW_IOCTL_RESUME                           0x3
#define TEE_VFMW_IOCTL_SUSPEND                          0x4
#define TEE_VFMW_IOCTL_CONTROL                          0x5
#define TEE_VFMW_IOCTL_THREAD                           0x6
#define TEE_VFMW_IOCTL_GET_IMAGE                        0x7
#define TEE_VFMW_IOCTL_RELEASE_IMAGE                    0x8
#define TEE_VFMW_IOCTL_READ_PROC                        0x9
#define TEE_VFMW_IOCTL_WRITE_PROC                       0xa
#endif

#ifdef CFG_HI_TEE_AVPLAY_SUPPORT
#define TEE_AVPLAY_IOCTL_E2RCOPY	                    0x1
#endif

#ifdef CFG_HI_TEE_LOG_SUPPORT
#define TEE_LOG_IOCTL_SETLEVEL                          0x1
#define TEE_LOG_IOCTL_GETLEVEL                          0x2
#endif

#ifdef CFG_HI_TEE_DEMUX_SUPPORT
#define TEE_DEMUX_IOCTL_NEW_DESC                        0x1
#define TEE_DEMUX_IOCTL_DEL_DESC                        0x2
#define TEE_DEMUX_IOCTL_ATTACH_DESC                     0x3
#define TEE_DEMUX_IOCTL_DETACH_DESC                     0x4
#define TEE_DEMUX_IOCTL_GET_DESC_ATTR                   0x5
#define TEE_DEMUX_IOCTL_SET_DESC_ATTR                   0x6
#define TEE_DEMUX_IOCTL_SET_DESC_EVEN                   0x7
#define TEE_DEMUX_IOCTL_SET_DESC_ODD                    0x8
#define TEE_DEMUX_IOCTL_SET_DESC_EVEN_IV                0x9
#define TEE_DEMUX_IOCTL_SET_DESC_ODD_IV                 0xa
#define TEE_DEMUX_IOCTL_GET_KEYID                       0xb
#define TEE_DEMUX_IOCTL_NEW_SC                          0xc
#define TEE_DEMUX_IOCTL_DEL_SC                          0xd
#define TEE_DEMUX_IOCTL_GET_SC_ATTR                     0xe
#define TEE_DEMUX_IOCTL_SET_SC_ATTR                     0xf
#define TEE_DEMUX_IOCTL_SET_SC_EVEN                     0x10
#define TEE_DEMUX_IOCTL_SET_SC_ODD                      0x11
#define TEE_DEMUX_IOCTL_ATTACH_SC                       0x12
#define TEE_DEMUX_IOCTL_DETACH_SC                       0x13
#define TEE_DEMUX_IOCTL_GET_SC_KEYID                    0x14
#define TEE_DEMUX_IOCTL_GET_CHNID                       0x15
#define TEE_DEMUX_IOCTL_GET_CAP                         0x16
#define TEE_DEMUX_IOCTL_REG_CHAN                        0x17
#define TEE_DEMUX_IOCTL_UNREG_CHAN                      0x18
#define TEE_DEMUX_IOCTL_REG_OQ                          0x19
#define TEE_DEMUX_IOCTL_UNREG_OQ                        0x1a
#define TEE_DEMUX_IOCTL_REG_RAM_PORT                    0x1b
#define TEE_DEMUX_IOCTL_UNREG_RAM_PORT                  0x1c
#define TEE_DEMUX_IOCTL_LOCK_CHAN                       0x1d
#define TEE_DEMUX_IOCTL_UNLOCK_CHAN                     0x1e
#define TEE_DEMUX_IOCTL_REG_VID_SECBUF                  0x1f
#define TEE_DEMUX_IOCTL_UNREG_VID_SECBUF                0x20
#define TEE_DEMUX_IOCTL_REG_AUD_SECBUF                  0x21
#define TEE_DEMUX_IOCTL_UNREG_AUD_SECBUF                0x22
#define TEE_DEMUX_IOCTL_FIXUP_AUD_SECBUF                0x23
#define TEE_DEMUX_IOCTL_PARSER_PES_HEADER               0x24
#define TEE_DEMUX_IOCTL_PARSER_DISP_CONTROL             0x25
#define TEE_DEMUX_IOCTL_GET_PES_HEADER_LEN              0x26
#define TEE_DEMUX_IOCTL_REG_REC_SECBUF                  0x27
#define TEE_DEMUX_IOCTL_UNREG_REC_SECBUF                0x28
#define TEE_DEMUX_IOCTL_FIXUP_HEVC_INDEX                0x29
#define TEE_DEMUX_IOCTL_REG_SECTION_SECBUF              0x2a
#define TEE_DEMUX_IOCTL_UNREG_SECTION_SECBUF            0x2b
#define TEE_DEMUX_IOCTL_FIXUP_SECTION_SECBUF            0x2c
#define TEE_DEMUX_IOCTL_CHECK_REC_SECBUF_ADDR           0x2d
#define TEE_DEMUX_IOCTL_DESCRAMBLER_NONSEC_KEY_ACQUIRE  0x2e
#define TEE_DEMUX_IOCTL_DESCRAMBLER_NONSEC_KEY_RELEASE  0x2f
#endif

#endif /*HI_TEE_MODULE_ID_H*/
