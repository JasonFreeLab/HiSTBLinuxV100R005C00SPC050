/******************************************************************************

Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_ca_crypto.c
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2013-08-28
Last Modified :
Description   :  
Function List :
History       :
******************************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hi_type.h"
#include "hi_common.h"
#include "hi_unf_advca.h"
#include "hi_unf_cipher.h"
#include "parse_config_file.h"

/***************************** Macro Definition ******************************/

#define TEXT_LEN    (1024)
#define KEY_LEN     (16)

#define PLAINTEXT_TAG     "PLAINTTEXT"
#define SESSIONKEY1_TAG   "SESSIONKEY1"
#define SESSIONKEY2_TAG   "SESSIONKEY2"
#define SESSIONKEY3_TAG   "SESSIONKEY3"
#define SESSIONKEY4_TAG   "SESSIONKEY4"
#define CONTENTKEY_TAG    "CONTENTKEY"
/*************************** Structure Definition ****************************/

/********************** Global Variable declaration **************************/

HI_U8 g_PlainText[TEXT_LEN]           = {0};
HI_U8 g_sessionkey1[KEY_LEN]          = {0};
HI_U8 g_sessionkey2[KEY_LEN]          = {0};
HI_U8 g_sessionkey3[KEY_LEN]          = {0};
HI_U8 g_sessionkey4[KEY_LEN]          = {0};
HI_U8 g_contentkey[KEY_LEN]           = {0};

HI_U32 g_PlainTextLen                    = 0;
KEYLADDER_TYPE_E g_KladType;
HI_UNF_ADVCA_ALG_TYPE_E       g_kladAlg  = HI_UNF_ADVCA_ALG_TYPE_BUTT;
HI_UNF_CIPHER_ALG_E           g_cipherAlg = HI_UNF_CIPHER_ALG_BUTT;
HI_UNF_CIPHER_WORK_MODE_E     g_cipherMode = HI_UNF_CIPHER_WORK_MODE_BUTT;

/******************************* API declaration *****************************/

static HI_VOID show_usage(HI_VOID)
{
    printf("./sample_ca_crypot configfilename\n");
    printf("config file include: ");    
    printf("PLAINTTEXT, SESSIONKEY1, SESSIONKEY2, SESSIONKEY3, SESSIONKEY4, CONTENTKEY\n");    
}

static HI_VOID printBuffer(HI_CHAR *string, HI_U8 *pu8Input, HI_U32 u32Length)
{    
    HI_U32 i = 0;    

    if (NULL != string)    
    {        
        printf("%s\n", string);    
    }    

    for (i = 0 ; i < u32Length; i++)
    {
        if((i % 16 == 0) && (i != 0))
            printf("\n");

        printf("0x%02x ", pu8Input[i]);
    }

    printf("\n");

    return;
}

static HI_VOID show_keyladderinfo(HI_VOID)
{
    if (KEYLADDER_TYPE_R2R == g_KladType)
    {
        printf("Keyladder type is R2R\n");
    }
    else if (KEYLADDER_TYPE_MISC == g_KladType)
    {
        printf("Keyladder type is Misc\n");
    }
    else if (KEYLADDER_TYPE_SP == g_KladType)
    {
        printf("Keyladder type is SP\n");
    }
    else
    {
        printf("Keyladder type is unknow\n");        
    }

    if (HI_UNF_ADVCA_ALG_TYPE_TDES == g_kladAlg)
    {
        printf("Keyladder Alg  is TDES\n");
    }
    else if (HI_UNF_ADVCA_ALG_TYPE_AES == g_kladAlg)
    {
        printf("Keyladder Alg  is AES\n");
    }
    return;
}


static HI_VOID show_cipherinfo(HI_VOID)
{
    if (HI_UNF_CIPHER_ALG_AES == g_cipherAlg)
    {
        printf("Cipher Alg is AES\n");
    }
    else if (HI_UNF_CIPHER_ALG_3DES == g_cipherAlg)
    {
        printf("Cipher Alg is TDES\n");
    }
    else
    {
        printf("Cipher Alg is unknow\n");
    }

    if (HI_UNF_CIPHER_WORK_MODE_ECB == g_cipherMode)
    {
        printf("Cipher Alg mode is ECB\n");
    }
    else if (HI_UNF_CIPHER_WORK_MODE_CBC == g_cipherMode)
    {
        printf("Cipher Alg mode is CBC\n");
    }
    else
    {
        printf("Cipher Alg mode is %x\n", g_cipherMode);
    }
    return;
}

static HI_VOID show_info(HI_VOID)
{
    show_keyladderinfo();
    show_cipherinfo();
}

static HI_S32 configCipher(HI_HANDLE hHandle)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UNF_CIPHER_CTRL_S CipherCtrl;

    memset(&CipherCtrl, 0, sizeof(HI_UNF_CIPHER_CTRL_S));
    CipherCtrl.enAlg = g_cipherAlg;
    CipherCtrl.enWorkMode = g_cipherMode;
    CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
    if (g_cipherAlg == HI_UNF_CIPHER_ALG_AES)
    {
        CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
    }
    else
    {
        CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_DES_2KEY;
    }
    
    CipherCtrl.bKeyByCA = HI_TRUE;
    if(CipherCtrl.enWorkMode != HI_UNF_CIPHER_WORK_MODE_ECB)
    {
        CipherCtrl.stChangeFlags.bit1IV = 1;  //must set for CBC , CFB mode        
        //memcpy(CipherCtrl.u32IV, u8IVBuf, 16);
    }

    memcpy(CipherCtrl.u32Key, g_contentkey, 16);
    s32Ret = HI_UNF_CIPHER_ConfigHandle(hHandle, &CipherCtrl);

    printBuffer("Content key:", g_contentkey, 16);
    if(HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 _configR2RKeyladder(HI_HANDLE hHandle)
{
    HI_S32 Ret = 0;
    HI_UNF_ADVCA_KEYLADDER_LEV_E enStage = 0;

    if (HI_UNF_ADVCA_ALG_TYPE_AES == g_kladAlg)
    {
        Ret  = HI_UNF_ADVCA_SetR2RAlg(HI_UNF_ADVCA_ALG_TYPE_AES);
    }
    else if (HI_UNF_ADVCA_ALG_TYPE_TDES == g_kladAlg)
    {
        Ret  = HI_UNF_ADVCA_SetR2RAlg(HI_UNF_ADVCA_ALG_TYPE_TDES);
    }
    
    Ret |= HI_UNF_ADVCA_GetR2RKeyLadderStage(&enStage);
    
    if(enStage >= HI_UNF_ADVCA_KEYLADDER_LEV2)
    {
        Ret |= HI_UNF_ADVCA_SetR2RSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV1, g_sessionkey1);
        if (HI_SUCCESS != Ret)
        {
            return HI_FAILURE;
        }
        printBuffer("session 1", g_sessionkey1, 16);
    }

    if(enStage >= HI_UNF_ADVCA_KEYLADDER_LEV3)
    {
        Ret |= HI_UNF_ADVCA_SetR2RSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV2, g_sessionkey2);
        if (HI_SUCCESS != Ret)
        {
            return HI_FAILURE;
        }
        printBuffer("session 2", g_sessionkey2, 16);        
    }

    
    return configCipher(hHandle);
}


static HI_S32 _configMiscKeyladder(HI_HANDLE hHandle)
{
    HI_S32 Ret = 0;
    HI_UNF_ADVCA_KEYLADDER_ATTR_S stKeyladderAttr;
    HI_UNF_ADVCA_OTP_FUSE_E enOtpFuse;
    HI_UNF_ADVCA_OTP_ATTR_S stOtpFuseAttr;

    memset(&stKeyladderAttr, 0, sizeof(HI_UNF_ADVCA_KEYLADDER_ATTR_S));
    stKeyladderAttr.unKlAttr.stMiscKlAttr.enMiscKlAttr = HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_ENABLE;
    stKeyladderAttr.unKlAttr.stMiscKlAttr.bEnable = HI_TRUE;
    Ret = HI_UNF_ADVCA_SetKeyLadderAttr(HI_UNF_ADVCA_KEYLADDER_MISC, &stKeyladderAttr);	
    
    
    memset(&stKeyladderAttr, 0, sizeof(HI_UNF_ADVCA_KEYLADDER_ATTR_S));
    stKeyladderAttr.unKlAttr.stMiscKlAttr.enMiscKlAttr = HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_ALG;
    stKeyladderAttr.unKlAttr.stMiscKlAttr.enAlgType = g_kladAlg;
    Ret = HI_UNF_ADVCA_SetKeyLadderAttr(HI_UNF_ADVCA_KEYLADDER_MISC, &stKeyladderAttr);

    enOtpFuse = HI_UNF_ADVCA_OTP_MISC_KL_LEVEL_SEL;
    memset(&stOtpFuseAttr, 0, sizeof(stOtpFuseAttr));
    Ret = HI_UNF_ADVCA_GetOtpFuse(enOtpFuse, &stOtpFuseAttr);
    if(Ret != HI_SUCCESS)
    {
        goto DEACTIVEMISC;
    }
    if(stOtpFuseAttr.unOtpFuseAttr.stKeyladderLevSel.enKeyladderLevel >= HI_UNF_ADVCA_KEYLADDER_LEV2)
    {
        memset(&stKeyladderAttr, 0, sizeof(HI_UNF_ADVCA_KEYLADDER_ATTR_S));
        stKeyladderAttr.unKlAttr.stMiscKlAttr.enMiscKlAttr = HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_SESSION_KEY;
		stKeyladderAttr.unKlAttr.stMiscKlAttr.enStage = HI_UNF_ADVCA_KEYLADDER_LEV1;
        memcpy(stKeyladderAttr.unKlAttr.stMiscKlAttr.u8SessionKey, g_sessionkey1, 16);
        Ret |= HI_UNF_ADVCA_SetKeyLadderAttr(HI_UNF_ADVCA_KEYLADDER_MISC, &stKeyladderAttr);
        if (Ret != HI_SUCCESS)
        {
            goto DEACTIVEMISC;
        }
        printBuffer("session 1", g_sessionkey1, 16);
    }
    if(stOtpFuseAttr.unOtpFuseAttr.stKeyladderLevSel.enKeyladderLevel >= HI_UNF_ADVCA_KEYLADDER_LEV3)
    {
        memset(&stKeyladderAttr, 0, sizeof(HI_UNF_ADVCA_KEYLADDER_ATTR_S));
        stKeyladderAttr.unKlAttr.stMiscKlAttr.enMiscKlAttr = HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_SESSION_KEY;
		stKeyladderAttr.unKlAttr.stMiscKlAttr.enStage = HI_UNF_ADVCA_KEYLADDER_LEV2;
        memcpy(stKeyladderAttr.unKlAttr.stMiscKlAttr.u8SessionKey, g_sessionkey2, 16);
        Ret |= HI_UNF_ADVCA_SetKeyLadderAttr(HI_UNF_ADVCA_KEYLADDER_MISC, &stKeyladderAttr);
        if (Ret != HI_SUCCESS)
        {
            goto DEACTIVEMISC;
        }
        printBuffer("session 2", g_sessionkey2, 16);
        
    }
    if(stOtpFuseAttr.unOtpFuseAttr.stKeyladderLevSel.enKeyladderLevel >= HI_UNF_ADVCA_KEYLADDER_LEV4)
    {
        memset(&stKeyladderAttr, 0, sizeof(HI_UNF_ADVCA_KEYLADDER_ATTR_S));
        stKeyladderAttr.unKlAttr.stMiscKlAttr.enMiscKlAttr = HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_SESSION_KEY;
		stKeyladderAttr.unKlAttr.stMiscKlAttr.enStage = HI_UNF_ADVCA_KEYLADDER_LEV3;
        memcpy(stKeyladderAttr.unKlAttr.stMiscKlAttr.u8SessionKey, g_sessionkey3, 16);
        Ret |= HI_UNF_ADVCA_SetKeyLadderAttr(HI_UNF_ADVCA_KEYLADDER_MISC, &stKeyladderAttr);
        if (Ret != HI_SUCCESS)
        {
            goto DEACTIVEMISC;
        }
        printBuffer("session 3", g_sessionkey3, 16);
    }
    if(stOtpFuseAttr.unOtpFuseAttr.stKeyladderLevSel.enKeyladderLevel >= HI_UNF_ADVCA_KEYLADDER_LEV5)
    {
        memset(&stKeyladderAttr, 0, sizeof(HI_UNF_ADVCA_KEYLADDER_ATTR_S));
        stKeyladderAttr.unKlAttr.stMiscKlAttr.enMiscKlAttr = HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_SESSION_KEY;
		stKeyladderAttr.unKlAttr.stMiscKlAttr.enStage = HI_UNF_ADVCA_KEYLADDER_LEV4;
        memcpy(stKeyladderAttr.unKlAttr.stMiscKlAttr.u8SessionKey, g_sessionkey4, 16);
        Ret |= HI_UNF_ADVCA_SetKeyLadderAttr(HI_UNF_ADVCA_KEYLADDER_MISC, &stKeyladderAttr);
        if (Ret != HI_SUCCESS)
        {
            goto DEACTIVEMISC;
        }
        printBuffer("session 4", g_sessionkey4, 16);
    }

    configCipher(hHandle);

DEACTIVEMISC:    
    stKeyladderAttr.unKlAttr.stMiscKlAttr.enMiscKlAttr = HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_ENABLE;
    stKeyladderAttr.unKlAttr.stMiscKlAttr.bEnable = HI_FALSE;
    Ret = HI_UNF_ADVCA_SetKeyLadderAttr(HI_UNF_ADVCA_KEYLADDER_MISC, &stKeyladderAttr);
    
    return Ret;
}


static HI_S32 _configSPKeyladder(HI_HANDLE hHandle)
{
    HI_S32 Ret = 0;
    HI_UNF_ADVCA_KEYLADDER_ATTR_S stKeyladderAttr;
    HI_UNF_ADVCA_OTP_FUSE_E enOtpFuse;
    HI_UNF_ADVCA_OTP_ATTR_S stOtpFuseAttr;

    memset(&stKeyladderAttr, 0, sizeof(HI_UNF_ADVCA_KEYLADDER_ATTR_S));
    stKeyladderAttr.unKlAttr.stSPKlAttr.enSPKlAttr = HI_UNF_ADVCA_KEYLADDER_SP_ATTR_ENABLE;
    stKeyladderAttr.unKlAttr.stSPKlAttr.bEnable = HI_TRUE;
    Ret = HI_UNF_ADVCA_SetKeyLadderAttr(HI_UNF_ADVCA_KEYLADDER_SP, &stKeyladderAttr);	
    
    memset(&stKeyladderAttr, 0, sizeof(HI_UNF_ADVCA_KEYLADDER_ATTR_S));
    stKeyladderAttr.unKlAttr.stSPKlAttr.enSPKlAttr = HI_UNF_ADVCA_KEYLADDER_SP_ATTR_ALG;
    stKeyladderAttr.unKlAttr.stSPKlAttr.enAlgType = g_kladAlg;
    Ret = HI_UNF_ADVCA_SetKeyLadderAttr(HI_UNF_ADVCA_KEYLADDER_SP, &stKeyladderAttr);

    enOtpFuse = HI_UNF_ADVCA_OTP_SP_KL_LEVEL_SEL;
    memset(&stOtpFuseAttr, 0, sizeof(stOtpFuseAttr));
    Ret = HI_UNF_ADVCA_GetOtpFuse(enOtpFuse, &stOtpFuseAttr);
    if(Ret != HI_SUCCESS)
    {
        goto DEACTIVESP;
    }
    if(stOtpFuseAttr.unOtpFuseAttr.stKeyladderLevSel.enKeyladderLevel >= HI_UNF_ADVCA_KEYLADDER_LEV2)
    {
        memset(&stKeyladderAttr, 0, sizeof(HI_UNF_ADVCA_KEYLADDER_ATTR_S));
        stKeyladderAttr.unKlAttr.stSPKlAttr.enSPKlAttr = HI_UNF_ADVCA_KEYLADDER_SP_ATTR_SESSION_KEY;
		stKeyladderAttr.unKlAttr.stSPKlAttr.enStage = HI_UNF_ADVCA_KEYLADDER_LEV1;
        memcpy(stKeyladderAttr.unKlAttr.stSPKlAttr.u8SessionKey, g_sessionkey1, 16);
        Ret = HI_UNF_ADVCA_SetKeyLadderAttr(HI_UNF_ADVCA_KEYLADDER_SP, &stKeyladderAttr);
        if (Ret != HI_SUCCESS)
        {
            goto DEACTIVESP;
        }

        printBuffer("session 1", g_sessionkey1, 16);
    }
    if(stOtpFuseAttr.unOtpFuseAttr.stKeyladderLevSel.enKeyladderLevel >= HI_UNF_ADVCA_KEYLADDER_LEV3)
    {
        memset(&stKeyladderAttr, 0, sizeof(HI_UNF_ADVCA_KEYLADDER_ATTR_S));
        stKeyladderAttr.unKlAttr.stSPKlAttr.enSPKlAttr = HI_UNF_ADVCA_KEYLADDER_SP_ATTR_SESSION_KEY;
		stKeyladderAttr.unKlAttr.stSPKlAttr.enStage = HI_UNF_ADVCA_KEYLADDER_LEV2;
        memcpy(stKeyladderAttr.unKlAttr.stSPKlAttr.u8SessionKey, g_sessionkey2, 16);
        Ret = HI_UNF_ADVCA_SetKeyLadderAttr(HI_UNF_ADVCA_KEYLADDER_SP, &stKeyladderAttr);
        if (Ret != HI_SUCCESS)
        {
            goto DEACTIVESP;
        }

        printBuffer("session 2", g_sessionkey2, 16);
    }
    if(stOtpFuseAttr.unOtpFuseAttr.stKeyladderLevSel.enKeyladderLevel >= HI_UNF_ADVCA_KEYLADDER_LEV4)
    {
        memset(&stKeyladderAttr, 0, sizeof(HI_UNF_ADVCA_KEYLADDER_ATTR_S));
        stKeyladderAttr.unKlAttr.stSPKlAttr.enSPKlAttr = HI_UNF_ADVCA_KEYLADDER_SP_ATTR_SESSION_KEY;
		stKeyladderAttr.unKlAttr.stSPKlAttr.enStage = HI_UNF_ADVCA_KEYLADDER_LEV3;
        memcpy(stKeyladderAttr.unKlAttr.stSPKlAttr.u8SessionKey, g_sessionkey3, 16);
        Ret = HI_UNF_ADVCA_SetKeyLadderAttr(HI_UNF_ADVCA_KEYLADDER_SP, &stKeyladderAttr);
        if (Ret != HI_SUCCESS)
        {
            goto DEACTIVESP;
        }

        printBuffer("session 3", g_sessionkey3, 16);        
    }
    if(stOtpFuseAttr.unOtpFuseAttr.stKeyladderLevSel.enKeyladderLevel >= HI_UNF_ADVCA_KEYLADDER_LEV5)
    {
        memset(&stKeyladderAttr, 0, sizeof(HI_UNF_ADVCA_KEYLADDER_ATTR_S));
        stKeyladderAttr.unKlAttr.stSPKlAttr.enSPKlAttr = HI_UNF_ADVCA_KEYLADDER_SP_ATTR_SESSION_KEY;
		stKeyladderAttr.unKlAttr.stSPKlAttr.enStage = HI_UNF_ADVCA_KEYLADDER_LEV4;
        memcpy(stKeyladderAttr.unKlAttr.stSPKlAttr.u8SessionKey, g_sessionkey4, 16);
        Ret = HI_UNF_ADVCA_SetKeyLadderAttr(HI_UNF_ADVCA_KEYLADDER_SP, &stKeyladderAttr);
        if (Ret != HI_SUCCESS)
        {
            goto DEACTIVESP;
        }

        printBuffer("session 4", g_sessionkey4, 16);        
    }

    configCipher(hHandle);

DEACTIVESP:   
	//After use the SP keyladder, deactive the SP keyladder
    stKeyladderAttr.unKlAttr.stSPKlAttr.enSPKlAttr = HI_UNF_ADVCA_KEYLADDER_SP_ATTR_ENABLE;
    stKeyladderAttr.unKlAttr.stSPKlAttr.bEnable = HI_FALSE;
    Ret = HI_UNF_ADVCA_SetKeyLadderAttr(HI_UNF_ADVCA_KEYLADDER_SP, &stKeyladderAttr);
    
    return Ret;
}

static HI_S32 setConfigure(HI_HANDLE hHandle)
{
    if (KEYLADDER_TYPE_R2R == g_KladType)
    {
        return _configR2RKeyladder(hHandle);
    }
    else if (KEYLADDER_TYPE_MISC == g_KladType)
    {
        return _configMiscKeyladder(hHandle);
    }
    else if (KEYLADDER_TYPE_SP == g_KladType)
    {
        return _configSPKeyladder(hHandle);
    }

    return HI_SUCCESS;
}


static HI_S32 get_plainttext(HI_CHAR *pName, HI_U8 *pData, HI_U32 *pDataLen)
{
	HI_CHAR *value = NULL;
    HI_S32 i;
    
	value = get_config_var(pName);
	if (NULL == value)
	{
		return -1;
	}

    for (i = 0; i < strlen (value) / 2; i++)
    {
        sscanf(value + 2 * i, "%2x", (HI_U32 *)&pData[i]);
    }

    *pDataLen = i;

    return 0;
}

static HI_S32 readConfigFile(HI_CHAR *pFileName)
{
    HI_S32 s32ValueNum = 0;
    HI_S32 s32Ret = 0;

    s32ValueNum = parse_config_file(pFileName);
    if (0 == s32ValueNum || MAX_VAR_NUM < s32ValueNum)
    {
        return HI_FAILURE;
    }

    s32Ret  = get_key_value(SESSIONKEY1_TAG, g_sessionkey1, KEY_LEN);
    s32Ret |= get_key_value(SESSIONKEY2_TAG, g_sessionkey2, KEY_LEN);
    s32Ret |= get_key_value(SESSIONKEY3_TAG, g_sessionkey3, KEY_LEN);
    s32Ret |= get_key_value(SESSIONKEY4_TAG, g_sessionkey4, KEY_LEN);
    s32Ret |= get_key_value(SESSIONKEY4_TAG, g_sessionkey4, KEY_LEN);
    s32Ret |= get_key_value(CONTENTKEY_TAG, g_contentkey, KEY_LEN);
    s32Ret |= get_plainttext(PLAINTEXT_TAG, g_PlainText, &g_PlainTextLen);
    s32Ret |= get_keyladder_type(&g_KladType);
    s32Ret |= get_keyladder_alg(&g_kladAlg);
    s32Ret |= get_cipher_alg(&g_cipherAlg);
    s32Ret |= get_cipher_mode(&g_cipherMode);
    if (s32Ret != 0)
    {
        printf("read config key failed\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}


HI_S32 main(HI_S32 argc,HI_CHAR **argv)
{
    HI_S32 Ret;
    HI_HANDLE hCipher;
    HI_MMZ_BUF_S PlainBuf,EncrytedBuf;
    HI_UNF_CIPHER_ATTS_S stCipherAttr;

    if (argc != 2)
    {
        show_usage();
        return 0;
    }

    Ret = readConfigFile(argv[1]);
    if (HI_SUCCESS != Ret)
    {
        return HI_FAILURE;
    }

    strcpy(PlainBuf.bufname,"plain_text");
    PlainBuf.bufsize = 0x1000;
    PlainBuf.overflow_threshold = 100;
    PlainBuf.underflow_threshold = 0;
    Ret = HI_MMZ_Malloc(&PlainBuf);
    if (HI_SUCCESS != Ret)
    {
        printf("HI_MMZ_Malloc failed:%x\n",Ret);
        return HI_FAILURE;
    }

    strcpy(EncrytedBuf.bufname,"encrypted_text");
    EncrytedBuf.bufsize = 0x1000;
    EncrytedBuf.overflow_threshold = 100;
    EncrytedBuf.underflow_threshold = 0;
    Ret = HI_MMZ_Malloc(&EncrytedBuf);
    if (HI_SUCCESS != Ret)
    {
        printf("HI_MMZ_Malloc failed:%x\n",Ret);
        (HI_VOID)HI_MMZ_Free(&PlainBuf);
        return HI_FAILURE;
    }

    if (HI_SUCCESS != HI_UNF_ADVCA_Init())
    {
        printf("HI_UNF_ADVCA_Init failed:%x\n",Ret);
        goto FREE;
    }

    if (HI_SUCCESS != HI_UNF_CIPHER_Init())
    {
        printf("HI_UNF_CIPHER_Init failed:%x\n",Ret);
        goto CA_DEINIT;
    }

    memset(&stCipherAttr, 0, sizeof(stCipherAttr));
    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    Ret = HI_UNF_CIPHER_CreateHandle(&hCipher, &stCipherAttr);
    if (HI_SUCCESS != Ret)
    {
        printf("HI_UNF_CIPHER_CreateHandle failed:%x\n",Ret);
        goto CLOSE;
    }

    show_info();

    Ret  = setConfigure(hCipher);

    if (HI_SUCCESS != Ret)
    {
        printf("config error\n");
        goto DESTROY;

    }

    /* encryption demo */  
    memcpy(PlainBuf.user_viraddr, g_PlainText, TEXT_LEN);
    memset(EncrytedBuf.user_viraddr, 0, EncrytedBuf.bufsize);   
    Ret = HI_UNF_CIPHER_Encrypt(hCipher,PlainBuf.phyaddr, EncrytedBuf.phyaddr, TEXT_LEN);
    if (HI_SUCCESS != Ret)
    {
        printf("HI_UNF_CIPHER_Encrypt failed:%x\n",Ret);
        goto DESTROY;
    }

    printBuffer("plaint data", PlainBuf.user_viraddr, g_PlainTextLen);
    printBuffer("encrypt result:", EncrytedBuf.user_viraddr, g_PlainTextLen);

    Ret = HI_SUCCESS;
DESTROY:
    (HI_VOID)HI_UNF_CIPHER_DestroyHandle(hCipher);
CLOSE:
    (HI_VOID)HI_UNF_CIPHER_DeInit();
CA_DEINIT:
    (HI_VOID)HI_UNF_ADVCA_DeInit();
FREE:
    (HI_VOID)HI_MMZ_Free(&PlainBuf);
    (HI_VOID)HI_MMZ_Free(&EncrytedBuf);    

    return Ret;
}


