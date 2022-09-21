/******************************************************************************

Copyright (C), 2004-2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_otp_set_fuse.c
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2017-07-20
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include "hi_unf_otp.h"
#include "hi_type.h"

HI_VOID show_usage(HI_VOID)
{
    printf("Usage:\n"
            "./sample_set_otp_fuse name value\n");
    printf("\n[WARNING]: The OTP fuse can only be set once, please be careful to set the OTP fuse."
            "If you are not clear about the OTP fuse, please contact HiSilicon.\n");
    printf("------------------------------------------\n");
    printf("name: marketid         value: 0x12345678(4 bytes number)\n");
    printf("name: bootversionid          value: 0x12345678(4 bytes number)\n");
}

HI_S32 run_cmdline(HI_S32 argc, HI_CHAR** argv)
{
    HI_S32 Ret = HI_FAILURE;
    HI_U32 id  = 0;
    HI_U8  buf[4] = {0};

    if (strncmp(argv[1], "marketid", strlen("marketid")) == 0)
    {
        id = strtoul(argv[2], NULL, 16);
        buf[0] = (id >> 24) & 0xFF;
        buf[1] = (id >> 16) & 0xFF;
        buf[2] = (id >> 8)  & 0xFF;
        buf[3] = id         & 0xFF;

        Ret = HI_UNF_OTP_SetMSID(buf,4);
    }
    else if (strncmp(argv[1], "bootversionid", strlen("bootversionid")) == 0)
    {
        id = strtoul(argv[2], NULL, 16);
        buf[0] = (id >> 24) & 0xFF;
        buf[1] = (id >> 16) & 0xFF;
        buf[2] = (id >> 8)  & 0xFF;
        buf[3] = id         & 0xFF;

        Ret = HI_UNF_OTP_SetBootVersionID(buf, 4);
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

    Ret = HI_UNF_OTP_Init();
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
    (HI_VOID)HI_UNF_OTP_DeInit();
    return Ret;
}


