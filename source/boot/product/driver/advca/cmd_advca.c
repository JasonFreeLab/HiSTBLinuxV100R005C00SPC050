/******************************************************************************

Copyright (C), 2005-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : cmd_advca.c
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2014-09-19
Last Modified :
Description   :  
Function List :
History       :
******************************************************************************/
#ifndef HI_ADVCA_FUNCTION_RELEASE

#ifdef ADVCA_CMD_TEST

#include "hi_common.h"
#include "command.h"
#include "exports.h"
#include "hi_unf_advca.h"


HI_S32 ADVCA_SetAntiRollBack_test(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    HI_U32  addr = 0;
    HI_U32  length = 0;
    HI_UNF_ADVCA_OTP_ATTR_S stOtpAttr;
    
    HI_UNF_ADVCA_Init();

    addr   = simple_strtoul(argv[1], NULL, 16);
    length = simple_strtoul(argv[2], NULL, 16);

    memset(&stOtpAttr, 0x0, sizeof (HI_UNF_ADVCA_OTP_ATTR_S));
    stOtpAttr.unOtpFuseAttr.stVersionNumber.u32OTPAddr   = addr;
    stOtpAttr.unOtpFuseAttr.stVersionNumber.u32OTPLength = length;

    HI_UNF_ADVCA_SetOtpFuse(HI_UNF_ADVCA_OTP_ANTIROLLBACK_VERSION, &stOtpAttr);

    return HI_SUCCESS;
}
U_BOOT_CMD(advca_setVersionNumber,3,1,ADVCA_SetAntiRollBack_test,"Set antirollback ,for example advca_setVersionNumber addr length ","");

HI_S32 ADVCA_GetAntiRollBack_test(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    HI_U32  addr = 0;
    HI_U32  length = 0;
    HI_UNF_ADVCA_OTP_ATTR_S stOtpAttr;
    
    HI_UNF_ADVCA_Init();

    addr   = simple_strtoul(argv[1], NULL, 16);
    length = simple_strtoul(argv[2], NULL, 16);

    memset(&stOtpAttr, 0x0, sizeof (HI_UNF_ADVCA_OTP_ATTR_S));
    stOtpAttr.unOtpFuseAttr.stVersionNumber.u32OTPAddr   = addr;
    stOtpAttr.unOtpFuseAttr.stVersionNumber.u32OTPLength = length;

    HI_UNF_ADVCA_GetOtpFuse(HI_UNF_ADVCA_OTP_ANTIROLLBACK_VERSION, &stOtpAttr);

    printf("VersionNumber is %d\n", stOtpAttr.unOtpFuseAttr.stVersionNumber.u32VersionNumber);

    return HI_SUCCESS;
}
U_BOOT_CMD(advca_getVersionNumber,3,1,ADVCA_GetAntiRollBack_test,"Get antirollback ,for example advca_getVersionNumber addr length ","");

#endif /* #ifdef ADVCA_CMD_TEST */
#endif /* #ifndef HI_ADVCA_FUNCTION_RELEASE */

