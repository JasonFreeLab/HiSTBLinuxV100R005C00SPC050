/*********************************************************************************
*
*  Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
*  This program is confidential and proprietary to Hisilicon Technologies Co., Ltd.
*  (Hisilicon), and may not be copied, reproduced, modified, disclosed to
*  others, published or used, in whole or in part, without the express prior
*  written permission of Hisilicon.
*
***********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hi_type.h"
#include "hi_unf_common.h"
#include "hi_unf_advca.h"
#include "hi_unf_ecs.h"


/***************************** Macro Definition ******************************/
#define TEXT_LEN  16
#define MAX_DATA_SIZE   (512*1024)

#define HI_DEBUG_ADVCA printf
/*************************** Structure Definition ****************************/
/********************** Global Variable declaration **************************/

HI_U8 data[16] = {0x67,0xb1,0xf8,0x28,0xdd,0x93,0x41,0xbc,0xca,0xed,0x73,0xd4,0x8d,0xa8,0xe9,0x1f};

static HI_U8 u8InputKey[16]= {0x33,0x34,0x34,0x52,0x34,0x55,0x45,0x84,0x54,0x54,0x84,0x53,0x34,0x47,0x34,0x47};
static HI_U8 u8OutputKey[16] = {0};
/******************************* API declaration *****************************/

#define CMAC_VALUE_LEN 16

HI_S32 main(HI_S32 argc,HI_CHAR **argv)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_S32 i;
    
    if (HI_SUCCESS != HI_UNF_ADVCA_Init())
    {
        HI_DEBUG_ADVCA("HI_UNF_ADVCA_Init failed:%x\n",Ret);
        return HI_FAILURE;
    }


    Ret = HI_UNF_ADVCA_CalculteAES_CMAC(data, CMAC_VALUE_LEN, u8InputKey, u8OutputKey);
    if (HI_SUCCESS != Ret)
    {
        HI_DEBUG_ADVCA("Fail to calculate data CMAC. Ret: %d\n",Ret);
    }

    HI_DEBUG_ADVCA("Data CMAC value is :");
    for (i=0; i< CMAC_VALUE_LEN; i++)
    {
       HI_DEBUG_ADVCA(" 0x%x", u8OutputKey[i]);
    }


    (HI_VOID)HI_UNF_ADVCA_DeInit(); 
    
    return Ret;
}


