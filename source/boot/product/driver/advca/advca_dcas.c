/******************************************************************************

Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : advca_dcas.c
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2017-03-14
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "command.h"
#include "advca_drv.h"
#include "advca_reg.h"
#include "otp.h"
#include "hi_unf_otp.h"


static HI_S32 DCAS_WaitStat(HI_VOID)
{
    HI_U32 u32Cnt = 0;
    CA_V300_CA_STATE_U unCaState;

    while (u32Cnt < 100)
    {
        unCaState.u32 = 0;
        ca_rdReg(CA_V300_CA_STATE, unCaState.u32);
        if (unCaState.bits.klad_busy == 0)
        {
            break;
        }
        udelay(1000);
        u32Cnt++;
    }

    if (u32Cnt >= 100)
    {
        return HI_FAILURE;
    }

    return unCaState.bits.err_state;
}

static HI_S32 DCAS_DecryptDCAS(HI_U32 enLevel, HI_U32 *pu32DataIn)
{
    HI_S32 s32Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_DCAS_CTRL_U unDCASCtrl;

    ca_rdReg(CA_V300_CONFIG_STATE, unConfigStatus.u32);
    if(unConfigStatus.bits.st_vld != 1)
    {
        printf("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    s32Ret = DCAS_WaitStat();
    if (HI_FAILURE == s32Ret)
    {
        printf("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    ca_wtReg(CA_V300_CA_DIN0, pu32DataIn[0]);
    ca_wtReg(CA_V300_CA_DIN1, pu32DataIn[1]);
    ca_wtReg(CA_V300_CA_DIN2, pu32DataIn[2]);
    ca_wtReg(CA_V300_CA_DIN3, pu32DataIn[3]);

    unDCASCtrl.u32 = 0;
    unDCASCtrl.bits.dsc_code_mc_alg_sel = 0;
    unDCASCtrl.bits.level_sel = enLevel;
    unDCASCtrl.bits.tdes_aes_sel = 1;//0:tdes, 1:aes

    ca_wtReg(CA_V300_DCAS_CTRL, unDCASCtrl.u32);

    s32Ret = DCAS_WaitStat();
    if (s32Ret != HI_SUCCESS)
    {
        printf("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    return HI_SUCCESS;
}

static HI_VOID DCAS_PrintKeyStatus(HI_VOID)
{
    HI_UNF_ADVCA_CHECKSUM_FLAG_U unChecksum;

    ca_rdReg(CA_V300_CHECKSUM_FLAG, unChecksum.u32);
    printf("--CA secret key checksum flag: 0x%08x\n", unChecksum.u32);

    if(0 == unChecksum.bits.ChipID_JTAGKey)
    {
        printf("--ChipID_JTAGKey verify:       failed\n");
    }
    else
    {
        printf("--ChipID_JTAGKey verify:       success\n");
    }

    if(0 == unChecksum.bits.ESCK)
    {
        printf("--ESCK verify:                 failed\n");
    }
    else
    {
        printf("--ESCK verify:                 success\n");
    }

    return ;
}

static HI_VOID DCAS_PrintRegInfo(HI_VOID)
{
    HI_U32 u32Debug = 0;

    ca_rdReg(REG_SYS_BRM_DEBUG, u32Debug);
    printf("--Register infomation:         0x%08x\n", u32Debug);

    return ;
}

static HI_VOID DCAS_PrintDaNonce(HI_VOID)
{
    HI_S32 s32Ret          = HI_SUCCESS;
    HI_U32 au32VendorId[4] = {0};
    HI_U32 au32EK2[4]      = {0};
    HI_U32 au32Nonce[4]    = {0};
    HI_U32 u32DaNonce[4]   = {0};
    HI_U32 u32MSBAddr      = 0;
    HI_U32 u32LSBAddr      = 0;

    ca_rdReg(CA_V300_DCAS_CHIP_ID_MSB, u32MSBAddr);
    ca_rdReg(CA_V300_DCAS_CHIP_ID_LSB, u32LSBAddr);

    s32Ret = DCAS_DecryptDCAS(8, au32VendorId);
    if (s32Ret != HI_SUCCESS)
    {
        printf("DCAS_DecryptDCAS failed, 0x%x\n", s32Ret);
        return ;
    }

    au32EK2[0] = ((u32MSBAddr & 0xff) << 24) | (((u32MSBAddr >> 8) & 0xff) << 16) | (((u32MSBAddr >> 16) & 0xff) << 8) | ((u32MSBAddr >> 24) & 0xff);
    au32EK2[1] = ((u32LSBAddr & 0xff) << 24) | (((u32LSBAddr >> 8) & 0xff) << 16) | (((u32LSBAddr >> 16) & 0xff) << 8) | ((u32LSBAddr >> 24) & 0xff);;
    s32Ret = DCAS_DecryptDCAS(0, au32EK2);
    if (s32Ret != HI_SUCCESS)
    {
        printf("DCAS_DecryptDCAS failed, 0x%x\n", s32Ret);
        return ;
    }

    au32Nonce[0] = au32EK2[0];
    au32Nonce[1] = au32EK2[1];
    s32Ret = DCAS_DecryptDCAS(9, au32Nonce);
    if (s32Ret != HI_SUCCESS)
    {
        printf("DCAS_DecryptDCAS failed, 0x%x\n", s32Ret);
        return ;
    }

    ca_rdReg(CA_V300_DA_NOUCE, u32DaNonce[0]);
    ca_rdReg(CA_V300_DA_NOUCE+4, u32DaNonce[1]);
    ca_rdReg(CA_V300_DA_NOUCE+8, u32DaNonce[2]);
    ca_rdReg(CA_V300_DA_NOUCE+12, u32DaNonce[3]);
    printf("--DaNonce: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
        u32DaNonce[0] & 0xff, (u32DaNonce[0] >> 8) & 0xff, (u32DaNonce[0] >> 16) & 0xff, (u32DaNonce[0] >> 24) & 0xff,
        u32DaNonce[1] & 0xff, (u32DaNonce[1] >> 8) & 0xff, (u32DaNonce[1] >> 16) & 0xff, (u32DaNonce[1] >> 24) & 0xff,
        u32DaNonce[2] & 0xff, (u32DaNonce[2] >> 8) & 0xff, (u32DaNonce[2] >> 16) & 0xff, (u32DaNonce[2] >> 24) & 0xff,
        u32DaNonce[3] & 0xff, (u32DaNonce[3] >> 8) & 0xff, (u32DaNonce[3] >> 16) & 0xff, (u32DaNonce[3] >> 24) & 0xff);

    return ;
}

HI_S32 ADVCA_DCAS_ReadOtp(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    HI_U32 i = 0;

    HI_UNF_OTP_Init();

    for (i = 0; i < 0x200; i++)
    {
        if (!(i & 0x3))
        {
            printf("\n%04x ", i * 4);
        }

        printf("%08x ", OTP_Read(i * 4));
    }
    printf("\n");

    return HI_SUCCESS;
}
U_BOOT_CMD(otp_read_all, 3, 1, ADVCA_DCAS_ReadOtp, "Read all otp infomation ,for example otp_read_all","");

HI_S32 ADVCA_DCAS_GetInfo(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    printf("*********************DCAS information*********************\n");
    DCAS_PrintKeyStatus();
    DCAS_PrintRegInfo();
    DCAS_PrintDaNonce();
    printf("**********************************************************\n");

    return HI_SUCCESS;
}
U_BOOT_CMD(dcas_info, 3, 1, ADVCA_DCAS_GetInfo, "Print dcas infomation ,for example dcas_info","");

