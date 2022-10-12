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

#ifndef __HISI_TA_AUTH_H
#define __HISI_TA_AUTH_H

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * widevine 服务
 */
#define TEE_SERVICE_WIDEVINE \
{ \
    0x79b77788, \
    0x9789, \
    0x4a7a, \
    { \
        0xa2, 0xbe, 0xb6, 0x01, 0x55, 0xee, 0xf5, 0xf8 \
    } \
}

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * emptydrm 服务
 */
#define TEE_SERVICE_EMPTYDRM \
{ \
    0x79b77788, \
    0x9789, \
    0x4a7a, \
    { \
        0xa2, 0xbe, 0xb6, 0x01, 0x55, 0x11, 0x11, 0x11 \
    } \
}

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * playready 服务
 */
#define TEE_SERVICE_PLAYREADY \
{ \
    0x79b77788, \
    0x9789, \
    0x4a7a, \
    { \
        0xa2, 0xbe, 0xb6, 0x01, 0x55, 0xee, 0xf5, 0xf9 \
    } \
}

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * HDMI HDCP 加密服务
 */
#define TEE_SERVICE_HDMI \
{ \
    0x40e4a246, \
    0xc1a7, \
    0x11e6, \
    { \
        0xa4, 0xa6, 0xce, 0xc0, 0xc9, 0x32, 0xce, 0x01 \
    } \
}

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * Notification task
 */
#define TEE_SERVICE_HISI_DEMO \
{ \
     0x8f194022, \
     0xc9a2, \
     0x11e6, \
     { \
         0x9d, 0x9d, 0xce, 0xc0, 0xc9, 0x32, 0xce, 0x01 \
     } \
}

/**
 * @ingroup  TEE_SERVICE_CRYPTO_VERIFY
 *
 * CRYPTO_VERIFY
 */
#define TEE_SERVICE_CRYPTO_VERIFY \
{ \
    0x46b84766, \
    0x42b0, \
    0x11e6, \
    { \
        0xbe, 0xb8, 0x9e, 0x71, 0x12, 0x8c, 0xae, 0x77 \
    } \
}

#define TEE_SERVICE_DRM \
{ \
    0x14047d2d, \
    0xf236, \
    0x48a0, \
    { \
        0xa0, 0xc4, 0xc1, 0xcc, 0xcb, 0xb6, 0x45, 0x46 \
    } \
}

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * Notification task
 */
#define TEE_SERVICE_SEC_MMZ \
{ \
     0xd93d4688, \
     0xbde7, \
     0x11e6, \
     { \
         0xa4, 0xa6, 0xce, 0xc0, 0xc9, 0x32, 0xce, 0x01 \
     } \
}

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * Notification task
 */
#define TEE_SERVICE_VFMW \
{ \
     0x3c2bfc84, \
     0xc03c, \
     0x11e6, \
     { \
         0xa4, 0xa6, 0xce, 0xc0, 0xc9, 0x32, 0xce, 0x01 \
     } \
}

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * Notification task
 */
#define TEE_SERVICE_HISI_TEST \
{ \
     0x0E0E0E0E, \
     0x0E0E, \
     0x0E0E, \
     { \
         0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E \
     } \
}

#define TEE_SERVICE_HISI_VDP \
{ \
     0x1E1E1E1E, \
     0x1E1E, \
     0x1E1E, \
     { \
         0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E \
     } \
}

/**
 * SMMU TASK
 *
 */
#define TEE_SERVICE_SMMU \
{\
    0x08684bd8, \
    0xbde8, \
    0x11e6, \
    {\
        0xa4, 0xa6, 0xce, 0xc0, 0xc9, 0x32, 0xce, 0x01 \
    }\
}

#define TEE_SERVICE_VPSS \
{\
       0x3acc8b1b, \
       0xa7e1, \
       0xe511, \
       {\
               0xb8,0x6d,0x9a,0x79,0xf0,0x6e,0x94,0x78 \
       }\
}

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * Notification task
 */
#define TEE_SERVICE_DMX \
{\
    0xca0b4c78, \
    0xbcf2, \
    0x11e6, \
    {\
        0xa4, 0xa6, 0xce, 0xc0, 0xc9, 0x32, 0xce, 0x01 \
    }\
}

/* *
 *@ingroup  TEE_COMMON_DATA
 *
 * COMMON TA
 *
 * */

#define TEE_SERVICE_COMMON \
{\
    0x000ac3b0, \
    0xbf6f, \
    0x11e7, \
    {\
        0x8f, 0x1a, 0x08, 0x00, 0x20, 0x0c, 0x9a, 0x66 \
    }\
}


/* *
 * @ingroup  TEE_STB_PLCIPHER
 *
 * Notification task
 */
#define TEE_SERVICE_PLCIPHER \
{\
    0x7ce373d9, \
    0x60f7, \
    0x43aa, \
    {\
         0xa7, 0x3f, 0x4e, 0x6b, 0xc9, 0x85, 0x99, 0x6b \
    }\
}

/**
 * @ingroup  TEE_SERVICE_KLAD
 *
 * Notification task
 */
#define TEE_SERVICE_KLAD \
{\
    0xc9cf6b2a, \
    0x4b60, \
    0x11e7, \
    {\
        0xa9, 0x19, 0x92, 0xeb, 0xcb, 0x67, 0xfe, 0x33 \
    }\
}

/**
 * @ingroup  TEE_STB_CRYPTOEN
 *
 * Notification task
 */
#define TEE_SERVICE_CRYPTOEN \
{\
    0xd9420c8e, \
    0x8daa, \
    0x439d, \
    {\
        0xa1, 0xe2, 0x91, 0x30, 0x16, 0xb1, 0x81, 0x0c \
    }\
}


/**
 * @ingroup  TEE_STB_PVR
 *
 * Notification task
 */
#define TEE_SERVICE_PVR \
{\
    0x569985fe,\
    0xbac0,\
    0x11e6,\
    {\
        0xa4, 0xa6, 0xce, 0xc0, 0xc9, 0x32, 0xce, 0x01\
    }\
}

/**
 * @ingroup  TEE_STB_AVPLAY
 *
 * Notification task
 */
#define TEE_SERVICE_AVPLAY \
{ \
     0x99985ef1, \
     0xd62d, \
     0x4524, \
     { \
         0x9d, 0xd1, 0xd9, 0x83, 0x45, 0x48, 0xd9, 0x8e \
     } \
}

/**
 * @ingroup  TEE_STB_MCU
 *
 * Notification task
 */
#define TEE_SERVICE_MCU \
{ \
     0x5766695a, \
     0x9b44, \
     0x4f9b, \
     { \
         0x80, 0xd6, 0x74, 0x1f, 0x88, 0x62, 0x4c, 0x41 \
     } \
}

/**
 * @ingroup  TEE_STB_LOG
 *
 * Notification task
 */
#define TEE_SERVICE_LOG \
{ \
     0x99986666, \
     0x6666, \
     0x4566, \
     { \
         0x96, 0xd6, 0xd6, 0x86, 0x46, 0x46, 0xd6, 0x86 \
     } \
}

/**
 * @ingroup  TEE_ID
 *
 * VMX ULTRA VMXTA task
 */
#define TEE_SERVICE_STB_VMX_ULTRA_VMXTA \
{ \
     0xd70f330c, \
     0xc8dd, \
     0x11e6, \
     { \
         0x9d, 0x9d, 0xce, 0xc0, 0xc9, 0x32, 0xce, 0x01 \
     } \
}

/**
 * @ingroup  TEE_ID
 *
 * VMX ULTRA videomarkTA task
 */
#define TEE_SERVICE_STB_VMX_ULTRA_videomarkTA \
{ \
     0xd70f3550, \
     0xc8dd, \
     0x11e6, \
     { \
         0x9d, 0x9d, 0xce, 0xc0, 0xc9, 0x32, 0xce, 0x01 \
     } \
}

/**
 * @ingroup  TEE_ID
 *
 * VMX ULTRA VMXTAC_TEST_TA2
 */
#define TEE_SERVICE_STB_VMX_ULTRA_VMXTAC_TEST_TA2 \
{ \
     0xd70f364a, \
     0xc8dd, \
     0x11e6, \
     { \
         0x9d, 0x9d, 0xce, 0xc0, 0xc9, 0x32, 0xce, 0x01 \
     } \
}
/**
 * @ingroup  TEE_ID
 *
 * VMX ULTRA VMXTAC_TEST_TA3
 */
#define TEE_SERVICE_STB_VMX_ULTRA_VMXTAC_TEST_TA3 \
{ \
     0xd70f3726, \
     0xc8dd, \
     0x11e6, \
     { \
         0x9d, 0x9d, 0xce, 0xc0, 0xc9, 0x32, 0xce, 0x01 \
     } \
}

/**
 * @ingroup  TEE_ID
 *
 * VMX ULTRA VMXTAC_TEST_TA1
 */
#define TEE_SERVICE_STB_VMX_ULTRA_VMXTAC_TEST_TA1 \
{ \
     0xd70f3a8c, \
     0xc8dd, \
     0x11e6, \
     { \
         0x9d, 0x9d, 0xce, 0xc0, 0xc9, 0x32, 0xce, 0x01 \
     } \
}


/**
 * @ingroup  TEE_ID
 *
 * VMX ULTRA update TA
 */
#define TEE_SERVICE_STB_UPDATE_TA \
{ \
     0x66666666, \
     0x6666, \
     0x6666, \
     { \
         0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66 \
     } \
}

/**
 * @ingroup  TEE_ID
 *
 * VMX ULTRA diplay TA
 */
#define TEE_SERVICE_STB_DISPLAY_TA \
{ \
     0x77777777, \
     0x7777, \
     0x7777, \
     { \
         0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77 \
     } \
}


/**
 * @ingroup  TEE_ID
 *
 * DCAS_COMMON task
 *
 * UUID: 9546a217-c9e0-40df-b8b2-e161e102e585
 */
#define TEE_SERVICE_DCAS_COMMON \
{ \
     0x17a24695, \
     0xe0c9, \
     0xdf40, \
     { \
         0xb8, 0xb2, 0xe1, 0x61, 0xe1, 0x02, 0xe5, 0x85 \
     } \
}

/**
 * @ingroup  TEE_ID
 *
 * DCAS_NDS task
 *
 * UUID: 2e8021e9-af35-4599-95baf374c229adb3
 */
#define TEE_SERVICE_DCAS_NDS \
{ \
    0xe921802e, \
    0x35af, \
    0x9945, \
    { \
        0x95, 0xba, 0xf3, 0x74, 0xc2, 0x29, 0xad, 0xb3 \
    } \
}

/**
 * @ingroup  TEE_ID
 *
 * sumavision TA task
 *
 * UUID: 3ddb56c2-0f03-4888-ae19-eca62e59917e
 */
#define TEE_SERVICE_DCAS_SUMA \
{ \
    0xc256db3d, \
    0x030f, \
    0x8848, \
    { \
        0xae, 0x19, 0xec, 0xa6, 0x2e, 0x59, 0x91, 0x7e \
    } \
}

/**
 * @ingroup  TEE_ID
 *
 * novel-superTV TA task
 *
 * UUID: 888105c8-4d8a-704b-891e1631f8b8f388
 */
#define TEE_SERVICE_DCAS_NOVEL \
{ \
    0xc8058188, \
    0x8a4d, \
    0x4b70, \
    { \
        0x89, 0x1e, 0x16, 0x31, 0xf8, 0xb8, 0xf3, 0x88 \
    } \
}

/**
 * @ingroup  TEE_ID
 *
 * NETFLIX TA
 */
#define TEE_SERVICE_NETFLIX \
{ \
     0x4c526126, \
     0xa26f, \
     0x452f, \
     { \
         0xb4, 0x8f, 0x37, 0x4c, 0x09, 0x38, 0x62, 0x31 \
     } \
}

/**
 *  * @ingroup  TEE_ID
 *   *
 *    * session manage
 *     */
#define TEE_SERVICE_SESSION_MANAGE \
{ \
    0x90ae48e5, \
    0xc757, \
    0x44a7, \
    { \
        0xb5, 0x13, 0xde, 0x4b, 0x2b, 0x14, 0xa0, 0x7c \
    } \
}

#define DEVCHIP_USER_CA_NAME       "__user_ca_name__"
#define DEVCHIP_DEFAULT_CA_NAME    "default"
#define DEVCHIP_DEFAULT_CA_UID     0

typedef struct {
	TEEC_UUID uuid[16];  /* TA UUID */
	unsigned char *ca_name; /* CA name */
	unsigned int uid; /* CA user id */
} st_ta_auth;

/**
 * hisi_set_ca_login_info() - Set CA login information according to authentication in TA.
 * Keep ca name, or set it with proc/pid/cmdline of current task or DEVCHIP_DEFAULT_CA_NAME.
 *
 * @param dev_file		Device which CA get from teecd via ictl.
 * @param context		Context which CA has initialized.
 *
 * @return 0 success, other failed.
 */
int hisi_set_ca_login_info(TC_NS_DEV_File *dev_file, TC_NS_ClientContext *context);
#endif /* __HISI_TA_AUTH_H */
