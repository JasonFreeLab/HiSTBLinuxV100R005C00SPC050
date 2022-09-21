/******************************************************************************

  Copyright (C), 2004-2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : sample_plcipher.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2017/04/07
  Description   :
  History       :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#include "hi_adp.h"
#include "hi_unf_common.h"
#include "hi_unf_disp.h"
#include "hi_unf_demux.h"
#include "hi_adp_mpi.h"
#include "hi_unf_payloadcipher.h"

#include "parse_config_file.h"


#define PLCIPHERCHANNELNUM 3

#define FIX_ARGNUM 4
#define MAX_ARGNUM 9

#define MAXBB (47*1024)
#ifdef CHIP_TYPE_hi3716mv420
#define MINBB (188*16)
#else
#define MINBB (188)
#endif

HI_MMZ_BUF_S PlainBuf1,EncrytedBuf1;

HI_BOOL bMMZAlloced = HI_FALSE;
#define MMZLEN  (47*1024 + 188*16)



HI_S32 AllocMMZ(const char* mmz_name,HI_MMZ_BUF_S* pMMZ)
{
    HI_S32 ret;

    memset(pMMZ, 0, sizeof(HI_MMZ_BUF_S));
    strcpy(pMMZ->bufname,mmz_name);
    pMMZ->bufsize = MMZLEN;
    pMMZ->overflow_threshold = 100;
    pMMZ->underflow_threshold = 0;
    ret = HI_MMZ_Malloc(pMMZ);
    if (HI_SUCCESS != ret)
    {
        printf("HI_MMZ_Malloc failed:%x\n",ret);
        return HI_FAILURE;
    }
    memset(pMMZ->user_viraddr, 0,pMMZ->bufsize);

    return ret;

}


HI_S32 AllocAllMMZ(HI_VOID)
{
    HI_S32 ret;
    if (bMMZAlloced)
    {
        memset(PlainBuf1.user_viraddr, 0, PlainBuf1.bufsize);
        memset(EncrytedBuf1.user_viraddr, 0, EncrytedBuf1.bufsize);
        return HI_SUCCESS;
    }

    ret = AllocMMZ("PlainBuf1",&PlainBuf1);
    ret |= AllocMMZ("EncrytedBuf1",&EncrytedBuf1);
    if (HI_SUCCESS != ret)
    {
        printf("HI_MMZ_Malloc failed:%x\n",ret);
        return HI_FAILURE;
    }

    bMMZAlloced = HI_TRUE;
    return ret;
}
HI_S32 FreeAllMMZ(HI_VOID)
{
    if (!bMMZAlloced)
    {
       return HI_SUCCESS;
    }

    if (PlainBuf1.bufsize != 0)
    {
        (HI_VOID)HI_MMZ_Free(&PlainBuf1);
    }

    if (EncrytedBuf1.bufsize != 0)
    {
        (HI_VOID)HI_MMZ_Free(&EncrytedBuf1);
    }

    bMMZAlloced = HI_FALSE;
    return HI_SUCCESS;
}

static HI_VOID printBuffer(HI_CHAR *string, HI_U8 *pu8Input, HI_U32 u32Length)
{
    HI_U32 i = 0;

    if ( NULL != string )
    {
        printf("%s\n", string);
    }

    for ( i = 0 ; i < u32Length; i++ )
    {
        if( (i % 16 == 0) && (i != 0)) printf("\n");
        printf("0x%02x ,", pu8Input[i]);
    }
    printf("\n");

    return;
}

static HI_VOID show_usage(HI_VOID)
{
    printf(" usage: sample_plcipher configfile file_to_encrypt file_encrypted pid1 pid2 pid3 pid4 pid5 \n");
    printf(" examples: \n");
    printf("   sample_plcipher cw_key_config.ini plain.ts encrypted.ts 0x20 0x21\n");
}

static HI_S32 readConfigFile(HI_CHAR *pFileName, HI_UNF_PLCIPHER_ALG_E *penAlg, HI_UNF_PLCIPHER_KEY_EVENODD_E *penOddEven,
                                                    HI_U8 *pu8OddKey, HI_U8 *pu8EvenKey, HI_U8 *pu8OddIv, HI_U8 *pu8EvenIv)
{
    HI_S32 s32ValueNum = 0;
    HI_S32 s32Ret = 0;

    s32ValueNum = parse_config_file(pFileName);
    if (0 == s32ValueNum || MAX_VAR_NUM < s32ValueNum)
    {
        return HI_FAILURE;
    }

    s32Ret |= get_cwkey_alg_type(penAlg);
    s32Ret |= get_cwkey_oddeven_type(penOddEven);
    s32Ret |= get_key_value("CLEARODDKEY", pu8OddKey, 16);
    printBuffer("odd key: ", pu8OddKey, 16);
    s32Ret |= get_key_value("CLEAREVENKEY", pu8EvenKey, 16);
    printBuffer("even key: ", pu8EvenKey, 16);
    s32Ret |= get_key_value("CLEARODDIV", pu8OddIv, 16);
    printBuffer("odd iv: ", pu8OddIv, 16);
    s32Ret |= get_key_value("CLEAREVENIV", pu8EvenIv, 16);
    printBuffer("even iv: ", pu8EvenIv, 16);

    if (s32Ret != 0)
    {
        printf("read config key failed\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 main(HI_S32 argc, HI_CHAR *argv[])
{
    HI_S32   Ret = HI_FAILURE;
    HI_S32   index = 0;
    HI_U32   TmpPid = 0;
    HI_U32   PidNum = 0;
    HI_S32   ReadLen = 0;

    FILE     *pEncOutTsFile = HI_NULL;
    FILE     *pEncInTsFile = HI_NULL;

    HI_HANDLE  hPLCipher;
    HI_UNF_PLCIPHER_ALG_E   enAlg;
    HI_UNF_PLCIPHER_KEY_EVENODD_E enOddEven;
    HI_UNF_PLCIPHER_ATTR_S stAttr;
    HI_U8 u8ClearOddKey[16] = {0};
    HI_U8 u8ClearEvenKey[16] = {0};
    HI_U8 u8ClearOddIv[16] = {0};
    HI_U8 u8ClearEvenIv[16] = {0};

    if (argc < FIX_ARGNUM || argc > MAX_ARGNUM)
    {
        show_usage();
        return 0;
    }
    printf("argc = %d\n",argc);

    /* get the pid num */
    PidNum = argc - FIX_ARGNUM;

    Ret = readConfigFile(argv[1], &enAlg, &enOddEven, u8ClearOddKey, u8ClearEvenKey, u8ClearOddIv, u8ClearEvenIv);
    if (HI_SUCCESS != Ret)
    {
        printf("readConfigFile failed\n");
        return 0;
    }

    pEncInTsFile = fopen(argv[2], "rb");
    pEncOutTsFile = fopen(argv[3], "wb");
    if (HI_NULL == pEncInTsFile || HI_NULL == pEncOutTsFile)
    {
        printf("Open original or new file failed\n");
        return 0;
    }

    AllocAllMMZ();

    Ret = HI_UNF_PLCIPHER_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("HI_UNF_PLCIPHER_Init failed, Ret[0x%x]\n", Ret);
        goto out0;
    }

    Ret = HI_UNF_PLCIPHER_Create(&hPLCipher);
    if (HI_SUCCESS != Ret)
    {
        printf("HI_UNF_PLCIPHER_Create failed, Ret[0x%x]\n", Ret);
        goto out1;
    }

    Ret = HI_UNF_PLCIPHER_GetAttr(hPLCipher, &stAttr);
    if (HI_SUCCESS != Ret)
    {
        printf("HI_UNF_PLCIPHER_GetAttr failed, Ret[0x%x]\n", Ret);
        goto out2;
    }

    stAttr.enAlg = enAlg;

    if (PidNum > 0)
    {
        stAttr.bPIDFilterEn = HI_TRUE;
        stAttr.u32PidNum = PidNum;
        memset(stAttr.u16PID, 0xff, HI_UNF_PLCIPHER_PIDFILTER_NUM*2);

        for (index = 0; index < PidNum; index++)
        {
            if (strstr(argv[FIX_ARGNUM+index], "0x") || strstr(argv[FIX_ARGNUM+index], "0X"))
            {
                TmpPid = strtoul(argv[FIX_ARGNUM+index], NULL ,16);
            }
            else
            {
                TmpPid = strtoul(argv[FIX_ARGNUM+index], NULL, 10);
            }
            stAttr.u16PID[index] = TmpPid;
        }
    }
    else
    {
        stAttr.bPIDFilterEn = HI_FALSE;
    }

    Ret = HI_UNF_PLCIPHER_SetAttr(hPLCipher, &stAttr);
    if (HI_SUCCESS != Ret)
    {
        printf("HI_UNF_PLCIPHER_SetAttr failed, Ret[0x%x]\n", Ret);
        goto out2;
    }

    if (HI_UNF_PLCIPHER_KEY_ODD == enOddEven)
    {
        Ret = HI_UNF_PLCIPHER_SetKey(hPLCipher, HI_UNF_PLCIPHER_KEY_ODD, u8ClearOddKey, sizeof(u8ClearOddKey));
        Ret |= HI_UNF_PLCIPHER_SetIV(hPLCipher, HI_UNF_PLCIPHER_KEY_ODD, u8ClearOddIv, sizeof(u8ClearOddIv));
        if (HI_SUCCESS != Ret)
        {
            printf("HI_UNF_PLCIPHER_SetKey or HI_UNF_PLCIPHER_SetIV ODD failed, Ret[0x%x]\n", Ret);
            goto out2;
        }
    }
    else
    {
        Ret = HI_UNF_PLCIPHER_SetKey(hPLCipher, HI_UNF_PLCIPHER_KEY_EVEN, u8ClearEvenKey, sizeof(u8ClearEvenKey));
        Ret |= HI_UNF_PLCIPHER_SetIV(hPLCipher, HI_UNF_PLCIPHER_KEY_EVEN, u8ClearEvenIv, sizeof(u8ClearEvenIv));
        if (HI_SUCCESS != Ret)
        {
            printf("HI_UNF_PLCIPHER_SetKey or HI_UNF_PLCIPHER_SetIV EVEN failed, Ret[0x%x]\n", Ret);
            goto out2;
        }
    }

    /* encrypt the clear TS stream */
    while((ReadLen=fread(PlainBuf1.user_viraddr, 1, MAXBB, pEncInTsFile)) != 0)
    {
        if ((ReadLen % MINBB) != 0)
        {
            printf("ReadLen[0x%x] must be 188 or 188*16 aligned, may reach the end of file\n", ReadLen);
            break;
        }

        Ret = HI_UNF_PLCIPHER_Encrypt(hPLCipher, (HI_VOID *)((HI_ULONG)(PlainBuf1.phyaddr)), (HI_VOID *)((HI_ULONG)EncrytedBuf1.phyaddr), ReadLen);
        if (HI_SUCCESS != Ret)
        {
            printf("HI_UNF_PLCIPHER_Encrypt failed, Ret[0x%x]\n", Ret);
            break;
        }

        fwrite(EncrytedBuf1.user_viraddr, 1, ReadLen, pEncOutTsFile);
    }

out2:
    Ret = HI_UNF_PLCIPHER_Destroy(hPLCipher);
    if (HI_SUCCESS != Ret)
    {
        printf("HI_UNF_PLCIPHER_Destroy failed, Ret[0x%x]\n", Ret);
    }

out1:
    Ret = HI_UNF_PLCIPHER_DeInit();
    if (HI_SUCCESS != Ret)
    {
        printf("HI_UNF_PLCIPHER_DeInit failed, Ret[0x%x]\n", Ret);
    }

out0:
    FreeAllMMZ();

    if (HI_NULL != pEncOutTsFile && HI_NULL != pEncInTsFile)
    {
        fclose(pEncOutTsFile);
        pEncOutTsFile = HI_NULL;
        fclose(pEncInTsFile);
        pEncInTsFile = HI_NULL;
    }

    printf("end\n");
    return Ret;
}

