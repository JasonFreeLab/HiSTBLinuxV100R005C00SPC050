/******************************************************************************

Copyright (C), 2004-2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_otp_getscsstatus.c
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2017-07-18
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hi_type.h"
#include "hi_unf_otp.h"


HI_S32 main(int argc, char *argv[])
{
    HI_S32 ret =HI_SUCCESS;
    HI_BOOL status = HI_FALSE;

    ret = HI_UNF_OTP_Init();
    if(HI_SUCCESS != ret)
    {
        printf("OTP init failed\n");
        return HI_FAILURE;
    }

    ret = HI_UNF_OTP_GetSCSStat(&status);
    if(HI_SUCCESS != ret)
    {
        printf("OTP enable SCS enable failed\n");
        (HI_VOID)HI_UNF_OTP_DeInit();
        return HI_FAILURE;
    }

    printf("OTP SCS status:%s\n",status == HI_TRUE ? "enable" : "disable");

    (HI_VOID)HI_UNF_OTP_DeInit();

    return HI_SUCCESS;
}


