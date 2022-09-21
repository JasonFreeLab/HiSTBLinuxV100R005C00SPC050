/******************************************************************************

Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_ca_set_otp_fuse.c
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2014-04-29
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hi_type.h"
#include "hi_unf_advca.h"

#define MAX_CMDLINE_LEN     1280
#define MAX_ARGS_COUNT      10
#define MAX_ARGS_LEN            128

extern HI_S32 HI_UNF_ADVCA_SetTZEnable(HI_BOOL bValue);

static HI_BOOL check_enable(HI_CHAR *pValue)
{
    return strncmp(pValue, "enable", strlen("enable")) == 0 ? HI_TRUE : HI_FALSE;
}

static HI_BOOL check_disable(HI_CHAR *pValue)
{
    return strncmp(pValue, "disable", strlen("disable")) == 0 ? HI_TRUE : HI_FALSE;
}

static HI_S32 get_flash_type(HI_CHAR *pValue, HI_UNF_ADVCA_FLASH_TYPE_E *penFlashType)
{
    HI_S32 Ret = HI_SUCCESS;

    if (0 == strncmp(pValue, "spi", strlen("spi")))
    {
        *penFlashType = HI_UNF_ADVCA_FLASH_TYPE_SPI;
    }
    else if (0 == strncmp(pValue,"nand", strlen("nand")))
    {
        *penFlashType = HI_UNF_ADVCA_FLASH_TYPE_NAND;
    }
    else if (0 == strncmp(pValue,"emmc", strlen("emmc")))
    {
        *penFlashType = HI_UNF_ADVCA_FLASH_TYPE_EMMC;
    }
    else
    {
        Ret = HI_FAILURE;
    }

    return Ret;
}

static HI_S32 get_jtag_mode(HI_CHAR *pValue, HI_UNF_ADVCA_JTAG_MODE_E *penJtagMode)
{
    HI_S32 Ret = HI_SUCCESS;

    if (0 == strncmp(pValue, "open", strlen("open")))
    {
        *penJtagMode = HI_UNF_ADVCA_JTAG_MODE_OPEN;
    }
    else if (0 == strncmp(pValue,"protect", strlen("protect")))
    {
        *penJtagMode = HI_UNF_ADVCA_JTAG_MODE_PROTECT;
    }
    else if (0 == strncmp(pValue,"close", strlen("close")))
    {
        *penJtagMode = HI_UNF_ADVCA_JTAG_MODE_CLOSED;
    }
    else
    {
        printf("get_jtag_mode failed\n");
        Ret = HI_FAILURE;
    }

    return Ret;

}

HI_S32 parse_cmdline(HI_CHAR *pCmdLine, HI_S32 *pArgc, HI_CHAR **Argv)
{
    HI_CHAR *ptr = pCmdLine;
    HI_U32 i;

    while ((*ptr == ' ') && (*ptr++ != '\0'))
    {
        ;
    }

    for (i = strlen(ptr); i > 0; i--)
    {
        if ((*(ptr + i - 1) == 0x0a) || (*(ptr + i - 1) == ' '))
        {
            *(ptr + i - 1) = '\0';
        }
        else
        {
            break;
        }
    }

    for (i = 0; i < MAX_ARGS_COUNT; i++)
    {
        HI_U32 j = 0;
        while ((*ptr == ' ') && (*(++ptr) != '\0'))
        {
            ;
        }

        while ((*ptr != ' ') && (*ptr != '\0') && (j < MAX_ARGS_LEN))
        {
            Argv[i][j++] = *ptr++;
        }

        Argv[i][j] = '\0';
        if ('\0' == *ptr)
        {
            i++;
            break;
        }
    }
    *pArgc = i;

    return HI_SUCCESS;
}

HI_VOID show_usage(HI_VOID)
{
    printf("Usage:\n"
            "./sample_ca_set_otp_fuse name value\n");
    printf("\n[WARNING]: The OTP fuse can only be set once, please be careful to set the OTP fuse."
            "If you are not clear about the OTP fuse, please contact HiSilicon.\n");
    printf("------------------------------------------\n");
    printf("name: stbsn            value: 0x12345678(4 bytes number)\n");
    printf("name: marketid         value: 0x12345678(4 bytes number)\n");
    printf("name: sosmarketid         value: 0x12345678(4 bytes number)\n");
    printf("name: versionid        value: 0x12345678(4 bytes number)\n");
    printf("name: marketidcheck    value: enable\n");
    printf("name: versionidcheck   value: enable\n");
    printf("name: selfboot         value: disable\n");
    printf("name: bootenc          value: disable\n");
    printf("name: runtimecheck     value: enable\n");
    printf("name: ddrwakeup        value: disable\n");
    printf("name: ddrwakeupcheck   value: enable\n");
    printf("name: scs              value: spi | nand | emmc\n");
    printf("name: trustzone        value: enable\n");
    printf("name: jtagmode         value: open | protect | close\n");
    printf("name: bootdec          value: enable\n");
    printf("name: globallock       value: enable\n");

}

HI_S32 run_cmdline(HI_S32 argc, HI_CHAR** argv)
{
    HI_S32 Ret = HI_FAILURE;
    HI_U32 id  = 0;
    HI_U8  buf[4] = {0};
    HI_UNF_ADVCA_OTP_FUSE_E eOtpFuse;
    HI_UNF_ADVCA_OTP_ATTR_S stOtpAttr;
    HI_BOOL bCheck;
    HI_UNF_ADVCA_FLASH_TYPE_E enFlashType;
    HI_UNF_ADVCA_JTAG_MODE_E enJtagMode;

    if (strncmp(argv[1], "stbsn", strlen ("stbsn")) == 0)
    {
        id = strtoul(argv[2], NULL, 16);
        memcpy(buf, &id, sizeof (buf));
        buf[0] = (id >> 24) & 0xFF;
        buf[1] = (id >> 16) & 0xFF;
        buf[2] = (id >> 8)  & 0xFF;
        buf[3] = id         & 0xFF;

        Ret = HI_UNF_ADVCA_SetStbSn(buf);
    }
    else if (strncmp(argv[1], "marketidcheck", strlen("marketidcheck")) == 0)
    {
        bCheck = check_enable(argv[2]);
        if (HI_TRUE == bCheck)
        {
            eOtpFuse = HI_UNF_ADVCA_OTP_BOOT_MSID_CHECK_ACTIVATION;
            stOtpAttr.unOtpFuseAttr.stDefaultAttr.bEnable = HI_TRUE;
            Ret = HI_UNF_ADVCA_SetOtpFuse((HI_UNF_ADVCA_OTP_FUSE_E)eOtpFuse, &stOtpAttr);
        }

    }
    else if (strncmp(argv[1], "versionidcheck", strlen("versionidcheck")) == 0)
    {
        bCheck = check_enable(argv[2]);
        if (HI_TRUE == bCheck)
        {
            eOtpFuse = HI_UNF_ADVCA_OTP_VERSION_ID_CHECK_ACTIVATION;
            stOtpAttr.unOtpFuseAttr.stDefaultAttr.bEnable = HI_TRUE;
            Ret = HI_UNF_ADVCA_SetOtpFuse((HI_UNF_ADVCA_OTP_FUSE_E)eOtpFuse, &stOtpAttr);
        }
    }
    else if (strncmp(argv[1], "ddrwakeupcheck", strlen("ddrwakeupcheck")) == 0)
    {
        bCheck = check_enable(argv[2]);
        if (HI_TRUE == bCheck)
        {
            eOtpFuse = HI_UNF_ADVCA_OTP_DDR_WAKEUP_CHECK_ACTIVATION;
            stOtpAttr.unOtpFuseAttr.stDefaultAttr.bEnable = HI_TRUE;
            Ret = HI_UNF_ADVCA_SetOtpFuse((HI_UNF_ADVCA_OTP_FUSE_E)eOtpFuse, &stOtpAttr);
        }
    }
    else if (strncmp(argv[1], "marketid", strlen("marketid")) == 0)
    {
        id = strtoul(argv[2], NULL, 16);
        memcpy(buf, &id, sizeof (buf));
        buf[0] = (id >> 24) & 0xFF;
        buf[1] = (id >> 16) & 0xFF;
        buf[2] = (id >> 8)  & 0xFF;
        buf[3] = id         & 0xFF;

        Ret = HI_UNF_ADVCA_SetMarketId(buf);
    }
    else if (strncmp(argv[1], "sosmarketid", strlen("sosmarketid")) == 0)
    {
        HI_S32 i;
        memset(buf, 0x0, sizeof (buf));
        memset(&stOtpAttr, 0x0, sizeof (stOtpAttr));

        id = strtoul(argv[2], NULL, 16);
        memcpy(buf, &id, sizeof (buf));
        buf[0] = (id >> 24) & 0xFF;
        buf[1] = (id >> 16) & 0xFF;
        buf[2] = (id >> 8)  & 0xFF;
        buf[3] = id         & 0xFF;

        for (i = 0; i < 4; i++)
        {
            memcpy(&stOtpAttr.unOtpFuseAttr.stMarketId.u8MSID[i], &buf[i], sizeof (HI_U8));
        }

        Ret = HI_UNF_ADVCA_SetOtpFuse(HI_UNF_ADVCA_OTP_SOS_MARKET_SEGMENT_ID, &stOtpAttr);
    }
    else if (strncmp(argv[1], "versionid", strlen("versionid")) == 0)
    {
        id = strtoul(argv[2], NULL, 16);
        memcpy(buf, &id, sizeof (buf));
        buf[0] = (id >> 24) & 0xFF;
        buf[1] = (id >> 16) & 0xFF;
        buf[2] = (id >> 8)  & 0xFF;
        buf[3] = id         & 0xFF;

        Ret = HI_UNF_ADVCA_SetVersionId(buf);
    }
    else if (strncmp(argv[1], "selfboot", strlen("selfboot")) == 0)
    {
        bCheck = check_disable(argv[2]);
        if (HI_TRUE == bCheck)
        {
            eOtpFuse = HI_UNF_ADVCA_OTP_SELF_BOOT_DEACTIVATION;
            stOtpAttr.unOtpFuseAttr.stDefaultAttr.bEnable = HI_TRUE;
            Ret = HI_UNF_ADVCA_SetOtpFuse((HI_UNF_ADVCA_OTP_FUSE_E)eOtpFuse, &stOtpAttr);
        }
    }
    else if (strncmp(argv[1], "bootenc", strlen("bootenc")) == 0)
    {
        bCheck = check_disable(argv[2]);
        if (HI_TRUE == bCheck)
        {
            eOtpFuse = HI_UNF_ADVCA_OTP_BOOT_ENCRYPTION_DEACTIVATION;
            stOtpAttr.unOtpFuseAttr.stDefaultAttr.bEnable = HI_TRUE;
            Ret = HI_UNF_ADVCA_SetOtpFuse((HI_UNF_ADVCA_OTP_FUSE_E)eOtpFuse, &stOtpAttr);
        }

        bCheck = check_enable(argv[2]);
        if (HI_TRUE == bCheck)
        {
            eOtpFuse = HI_UNF_ADVCA_OTP_BOOT_ENCRYPTION_DEACTIVATION;
            stOtpAttr.unOtpFuseAttr.stDefaultAttr.bEnable = HI_FALSE;
            Ret = HI_UNF_ADVCA_SetOtpFuse((HI_UNF_ADVCA_OTP_FUSE_E)eOtpFuse, &stOtpAttr);
        }
    }
    else if (strncmp(argv[1], "runtimecheck", strlen("runtimecheck")) == 0)
    {
        bCheck = check_enable(argv[2]);
        if (HI_TRUE == bCheck)
        {
            eOtpFuse = HI_UNF_ADVCA_OTP_RUNTIME_CHECK_ACTIVATION;
            stOtpAttr.unOtpFuseAttr.stDefaultAttr.bEnable = HI_TRUE;
            Ret = HI_UNF_ADVCA_SetOtpFuse((HI_UNF_ADVCA_OTP_FUSE_E)eOtpFuse, &stOtpAttr);
        }

    }
    else if (strncmp(argv[1], "ddrwakeup", strlen("ddrwakeup")) == 0)
    {
        bCheck = check_disable(argv[2]);
        if (HI_TRUE == bCheck)
        {
            eOtpFuse = HI_UNF_ADVCA_OTP_DDR_WAKEUP_DEACTIVATION;
            stOtpAttr.unOtpFuseAttr.stDefaultAttr.bEnable = HI_TRUE;
            Ret = HI_UNF_ADVCA_SetOtpFuse((HI_UNF_ADVCA_OTP_FUSE_E)eOtpFuse, &stOtpAttr);
        }
    }
    else if (strncmp(argv[1], "scs", strlen("scs")) == 0)
    {
        Ret = get_flash_type(argv[2], &enFlashType);
        if (HI_SUCCESS == Ret)
        {
            Ret = HI_UNF_ADVCA_EnableSecBoot(enFlashType);
        }
    }
    else if (strncmp(argv[1], "trustzone", strlen("trustzone")) == 0)
    {
        bCheck = check_enable(argv[2]);
        if (HI_TRUE == bCheck)
        {
            Ret = HI_UNF_ADVCA_SetTZEnable(HI_TRUE);
        }
    }
    else if (strncmp(argv[1], "jtagmode", strlen("jtagmode")) == 0)
    {
        Ret = get_jtag_mode(argv[2], &enJtagMode);
        if (HI_SUCCESS == Ret)
        {
            Ret = HI_UNF_ADVCA_SetJtagMode(enJtagMode);
        }
    }
    else if (strncmp(argv[1], "bootdec", strlen("bootdec")) == 0)
    {
        bCheck = check_enable(argv[2]);
        if (HI_TRUE == bCheck)
        {
            eOtpFuse = HI_UNF_ADVCA_OTP_BOOT_DECRYPTION_ACTIVATION;
            stOtpAttr.unOtpFuseAttr.stDefaultAttr.bEnable = HI_TRUE;
            Ret = HI_UNF_ADVCA_SetOtpFuse((HI_UNF_ADVCA_OTP_FUSE_E)eOtpFuse, &stOtpAttr);
        }
    }
    else if (strncmp(argv[1], "globallock", strlen("globallock")) == 0)
    {
        bCheck = check_enable(argv[2]);
        if (HI_TRUE == bCheck)
        {
            eOtpFuse = HI_UNF_ADVCA_OTP_GLOBAL_LOCK_ACTIVATION;
            stOtpAttr.unOtpFuseAttr.stDefaultAttr.bEnable = HI_TRUE;
            Ret = HI_UNF_ADVCA_SetOtpFuse((HI_UNF_ADVCA_OTP_FUSE_E)eOtpFuse, &stOtpAttr);
        }
    }

    if (HI_SUCCESS == Ret)
    {
        printf("set %s  %s success\n", argv[1], argv[2]);
    }
    else
    {
        printf("set %s  %s fail\n", argv[1], argv[2]);
    }



    return Ret;
}


HI_S32 main(HI_S32 argc, HI_CHAR** argv)
{
    HI_S32 Ret;

    Ret = HI_UNF_ADVCA_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("HI_UNF_ADVCA_Init failed\n");
        return HI_FAILURE;
    }

    if(argc <= 2)
    {
        show_usage();
        Ret = HI_FAILURE;
        goto DEINIT;
    }

    (HI_VOID)run_cmdline(argc, argv);

DEINIT:
    (HI_VOID)HI_UNF_ADVCA_DeInit();
    return Ret;
}


