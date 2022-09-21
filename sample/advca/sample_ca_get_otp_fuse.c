/******************************************************************************

Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_ca_get_otp_fuse.c
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

extern HI_S32 HI_UNF_ADVCA_GetTZEnStatus(HI_BOOL *pbEn);

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
            "./sample_ca_get_otp_fuse name\n");
    printf("------------------------------------------\n");
    printf("name: stbsn            Get STB serial number\n");
    printf("name: marketid         Get market segment id\n");
    printf("name: sosmarketid      Get sos market segment id\n");
    printf("name: versionid        Get version id\n");
    printf("name: marketidcheck    Get marketid check status\n");
    printf("name: versionidcheck   Get versionid check status\n");
    printf("name: selfboot         Get self boot status\n");
    printf("name: bootenc          Get boot encrypt  status\n");
    printf("name: runtimecheck     Get runtime check status\n");
    printf("name: ddrwakeup        Get ddr wake up status\n");
    printf("name: ddrwakeupcheck   Get ddr wake up check status\n");
    printf("name: scs              Get secure chipset startup status\n");
    printf("name: trustzone        Get trustzone status\n");
    printf("name: jtagmode         Get jtag mode\n");
    printf("name: bootdec          Get boot force decrypt status\n");
    printf("name: globallock       Get globallock status\n");
    printf("name: chipid           Get chip id\n");

}

HI_S32 run_cmdline(HI_S32 argc, HI_CHAR** argv)
{
    HI_U32 id  = 0;
    HI_U8  buf[4] = {0};
    HI_UNF_ADVCA_OTP_ATTR_S stOtpAttr;
    HI_BOOL bCheck;
    HI_UNF_ADVCA_FLASH_TYPE_E enFlashType;
    HI_UNF_ADVCA_JTAG_MODE_E enJtagMode;
    HI_S32 i;

    if (strncmp(argv[1], "stbsn", strlen ("stbsn")) == 0)
    {
        memset(buf, 0x0, sizeof (buf));

        HI_UNF_ADVCA_GetStbSn(buf);

        id = (buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + buf[3];

        printf("STB serial number is:%x\n", id);
    }
    else if (strncmp(argv[1], "marketidcheck", strlen("marketidcheck")) == 0)
    {
        memset(&stOtpAttr, 0x0, sizeof (stOtpAttr));
        HI_UNF_ADVCA_GetOtpFuse(HI_UNF_ADVCA_OTP_BOOT_MSID_CHECK_ACTIVATION, &stOtpAttr);

        printf("marketid check is %s\n", stOtpAttr.unOtpFuseAttr.stDefaultAttr.bEnable == HI_TRUE ? "enable" : "disable");
    }
    else if (strncmp(argv[1], "versionidcheck", strlen("versionidcheck")) == 0)
    {
        memset(&stOtpAttr, 0x0, sizeof (stOtpAttr));
        HI_UNF_ADVCA_GetOtpFuse(HI_UNF_ADVCA_OTP_VERSION_ID_CHECK_ACTIVATION, &stOtpAttr);

        printf("versionid check is %s\n", stOtpAttr.unOtpFuseAttr.stDefaultAttr.bEnable == HI_TRUE ? "enable" : "disable");
    }
    else if (strncmp(argv[1], "ddrwakeupcheck", strlen("ddrwakeupcheck")) == 0)
    {
        memset(&stOtpAttr, 0x0, sizeof (stOtpAttr));
        HI_UNF_ADVCA_GetOtpFuse(HI_UNF_ADVCA_OTP_DDR_WAKEUP_CHECK_ACTIVATION, &stOtpAttr);

        printf("ddr wake up check  is %s\n", stOtpAttr.unOtpFuseAttr.stDefaultAttr.bEnable == HI_TRUE ? "enable" : "disable");
    }
    else if (strncmp(argv[1], "marketid", strlen("marketid")) == 0)
    {
        memset(buf, 0x0, sizeof (buf));

        HI_UNF_ADVCA_GetMarketId(buf);

        id = (buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + buf[3];

        printf("Market segment id is:%x\n", id);
    }
    else if (strncmp(argv[1], "versionid", strlen("versionid")) == 0)
    {
        memset(buf, 0x0, sizeof (buf));

        HI_UNF_ADVCA_GetMarketId(buf);

        id = (buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + buf[3];

        printf("version id is:%x\n", id);
    }
    else if (strncmp(argv[1], "selfboot", strlen("selfboot")) == 0)
    {
        memset(&stOtpAttr, 0x0, sizeof (stOtpAttr));
        HI_UNF_ADVCA_GetOtpFuse(HI_UNF_ADVCA_OTP_SELF_BOOT_DEACTIVATION, &stOtpAttr);

        printf("self boot is %s\n", stOtpAttr.unOtpFuseAttr.stDefaultAttr.bEnable == HI_FALSE ? "enable" : "disable");
    }
    else if (strncmp(argv[1], "bootenc", strlen("bootenc")) == 0)
    {
        memset(&stOtpAttr, 0x0, sizeof (stOtpAttr));
        HI_UNF_ADVCA_GetOtpFuse(HI_UNF_ADVCA_OTP_BOOT_ENCRYPTION_DEACTIVATION, &stOtpAttr);

        printf("boot enc is %s\n", stOtpAttr.unOtpFuseAttr.stDefaultAttr.bEnable == HI_FALSE ? "enable" : "disable");
    }
    else if (strncmp(argv[1], "runtimecheck", strlen("runtimecheck")) == 0)
    {
        memset(&stOtpAttr, 0x0, sizeof (stOtpAttr));
        HI_UNF_ADVCA_GetOtpFuse(HI_UNF_ADVCA_OTP_RUNTIME_CHECK_ACTIVATION, &stOtpAttr);

        printf("runtime check is %s\n", stOtpAttr.unOtpFuseAttr.stDefaultAttr.bEnable == HI_TRUE ? "enable" : "disable");
    }
    else if (strncmp(argv[1], "ddrwakeup", strlen("ddrwakeup")) == 0)
    {
        memset(&stOtpAttr, 0x0, sizeof (stOtpAttr));
        HI_UNF_ADVCA_GetOtpFuse(HI_UNF_ADVCA_OTP_DDR_WAKEUP_DEACTIVATION, &stOtpAttr);

        printf("ddr wake up is %s\n", stOtpAttr.unOtpFuseAttr.stDefaultAttr.bEnable == HI_FALSE ? "enable" : "disable");
    }
    else if (strncmp(argv[1], "scs", strlen("scs")) == 0)
    {
        memset(&stOtpAttr, 0x0, sizeof (stOtpAttr));
        HI_UNF_ADVCA_GetOtpFuse(HI_UNF_ADVCA_OTP_SECURE_BOOT_ACTIVATION, &stOtpAttr);

        enFlashType = stOtpAttr.unOtpFuseAttr.stEnableSecureBoot.enFlashType;
        printf("secure chipset startup is %s\n", stOtpAttr.unOtpFuseAttr.stEnableSecureBoot.bEnable == HI_TRUE ? "enable" : "disable");
        printf("Startup flash mode: %s\n", enFlashType ==  HI_UNF_ADVCA_FLASH_TYPE_SPI ? "SPI" :
        (enFlashType ==  HI_UNF_ADVCA_FLASH_TYPE_NAND ? "NAND" : (enFlashType == HI_UNF_ADVCA_FLASH_TYPE_EMMC ? "EMMC" :
        (enFlashType == HI_UNF_ADVCA_FLASH_TYPE_SPI_NAND ? "SPI_NAND" :
        (enFlashType == HI_UNF_ADVCA_FLASH_TYPE_SD ? "SD" : "Unknow")))));
    }
    else if (strncmp(argv[1], "trustzone", strlen("trustzone")) == 0)
    {
        HI_UNF_ADVCA_GetTZEnStatus(&bCheck);
        printf("Trustzone is: %s\n",(bCheck == HI_TRUE) ? "enable" : "disable");
    }
    else if (strncmp(argv[1], "jtagmode", strlen("jtagmode")) == 0)
    {
        memset(&stOtpAttr, 0x0, sizeof (stOtpAttr));
        HI_UNF_ADVCA_GetOtpFuse(HI_UNF_ADVCA_OTP_JTAG_MODE, &stOtpAttr);

        enJtagMode = stOtpAttr.unOtpFuseAttr.stJtagPrtMode.enJtagMode;
        printf("JTAG mode is: %s\n", enJtagMode ==  HI_UNF_ADVCA_JTAG_MODE_OPEN ? "Open" :
        (enJtagMode == HI_UNF_ADVCA_JTAG_MODE_PROTECT ? "Protected" : "Closed"));
    }
    else if (strncmp(argv[1], "bootdec", strlen("bootdec")) == 0)
    {
        memset(&stOtpAttr, 0x0, sizeof (stOtpAttr));
        HI_UNF_ADVCA_GetOtpFuse(HI_UNF_ADVCA_OTP_BOOT_DECRYPTION_ACTIVATION, &stOtpAttr);

        printf("boot decrypt is %s\n", stOtpAttr.unOtpFuseAttr.stDefaultAttr.bEnable == HI_TRUE ? "enable" : "disable");
    }
    else if (strncmp(argv[1], "globallock", strlen("globallock")) == 0)
    {
        memset(&stOtpAttr, 0x0, sizeof (stOtpAttr));
        HI_UNF_ADVCA_GetOtpFuse(HI_UNF_ADVCA_OTP_GLOBAL_LOCK_ACTIVATION, &stOtpAttr);

        printf("Global lock is %s\n", stOtpAttr.unOtpFuseAttr.stDefaultAttr.bEnable == HI_TRUE ? "enable" : "disable");
    }
    else if (strncmp(argv[1], "chipid", strlen("chipid")) == 0)
    {
        memset(&stOtpAttr, 0x0, sizeof (stOtpAttr));
        HI_UNF_ADVCA_GetOtpFuse(HI_UNF_ADVCA_OTP_CHIP_ID, &stOtpAttr);

        printf("ChipId: ");
        for (i = 0; i < 8; i++)
        {
            printf("0x%02x, ", stOtpAttr.unOtpFuseAttr.stChipId.au8ChipId[i]);
        }
        printf("\n");
    }
    else if (strncmp(argv[1], "sosmarketid", strlen("sosmarketid")) == 0)
    {
        memset(buf, 0x0, sizeof (buf));
        memset(&stOtpAttr, 0x0, sizeof (stOtpAttr));
        HI_UNF_ADVCA_GetOtpFuse(HI_UNF_ADVCA_OTP_SOS_MARKET_SEGMENT_ID, &stOtpAttr);

        for (i = 0; i < 4; i++)
        {
            memcpy(&buf[i], &stOtpAttr.unOtpFuseAttr.stMarketId.u8MSID[i], sizeof (HI_U8));
        }

        id = (buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + buf[3];
        printf("sos msid number is:%x\n", id);
    }

    return HI_SUCCESS;
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

    if(argc <= 1)
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


