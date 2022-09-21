/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : spacc_intf.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "cipher_adapt.h"
#include "spacc_body.h"
#include "spacc_union_define.h"

#define SAPCC_MAX_CHN                     8
#define AES_BLOCK_SIZE                    16
#define SPACC_TIME_OUT                    100000
#define SPACC_PAD_BUF_SIZE                128
#define MAX_PKG_NUMBER                    10000
#define SPACC_KEY_LEN                     32
#define UNIX_MAX                          0XFFFFFFFF

cipher_mutex g_SymcMutex;
cipher_mutex g_DigestMutex;
cipher_mutex g_SymcMutex;

#define SPACC_CheckHandle(ChanId)   \
    do \
    { \
        if (ChanId >= SAPCC_MAX_CHN) \
        { \
            HI_ERR_CIPHER("chan %d is too large, max: %d\n", ChanId, SAPCC_MAX_CHN); \
            cipher_mutex_unlock(&g_SymcMutex);    \
            return HI_ERR_CIPHER_INVALID_PARA; \
        } \
        if (HI_FALSE == s_stSymcChn[ChanId].bIsOpen) \
        { \
            HI_ERR_CIPHER("chan %d is not open\n", ChanId); \
            cipher_mutex_unlock(&g_SymcMutex);    \
            return HI_ERR_CIPHER_INVALID_HANDLE; \
        } \
    } while (0)

#define CHAN0_CIPHER_IV                  (g_u32CipherRegBase + 0x0000)
#define CHAN0_CIPHER_DOUT                (g_u32CipherRegBase + 0x0080)
#define CHAN0_CIPHER_KEY                 (g_u32CipherRegBase + 0x0100)
#define CHAN0_SM1_SK                     (g_u32CipherRegBase + 0x0200)
#define ODD_EVEN_KEY_SEL                 (g_u32CipherRegBase + 0x0290)
#define HDCP_MODE_CTRL                   (g_u32CipherRegBase + 0x0300)
#define SEC_CHN_CFG                      (g_u32CipherRegBase + 0x0304)
#define CALC_ST0                         (g_u32CipherRegBase + 0x0318)
#define CALC_ERR                         (g_u32CipherRegBase + 0x0320)
#define CHAN0_CCM_GCM_TAG                (g_u32CipherRegBase + 0x0380)
#define CHAN0_CIPHER_CTRL                (g_u32CipherRegBase + 0x0400)
#define CIPHER_INT_RAW                   (g_u32CipherRegBase + 0x040c)
#define CHAN0_CIPHER_DIN                 (g_u32CipherRegBase + 0x0420)

#define SYMC_INT_LEVEL     100 //(SPACC_MAX_DEPTH/2) //中断水平线

typedef HI_VOID (*funcCipherCallback)(HI_U32);

typedef struct hiSPACC_ENV_S
{
    cipher_mmz_buf_t stMmzBuf;
} SPACC_ENV_S;

typedef struct hiSPACC_SYMC_CHN_S
{
    HI_BOOL bIsOpen;
    HI_U32  u32HardNum;
    HI_U32  u32BlockSize;

    HI_BOOL bSymcDone;
    cipher_queue_head     queue;

    HI_UNF_CIPHER_DATA_S  *pstNodeList;
    HI_U32  u32NodeNum;
    HI_U32  u32NodeCur;
    HI_U32  u32TotalLen;

    HI_U8 *pu8PadVirAddr;
    HI_U32 u32PadPhyAddr;

    HI_VOID* pWichFile;

    CIPHER_CONFIG_CTRL_EX stCtrl;

    funcCipherCallback callback;
} SPACC_SYMC_CHN_S;

typedef struct hiSPACC_DIGEST_CHN_S
{
    HI_BOOL  bIsOpen;
    HI_U32   u32HardNum;
    HI_U32  u32NodeNum;
    HI_U32  u32NodeCur;
    HI_U32  u32BlockSize;

    HI_BOOL bDigestDone;
    cipher_queue_head queue;

    funcCipherCallback callback;

    HI_VOID* pWichFile;
} SPACC_DIGEST_CHN_S;


static SPACC_ENV_S        s_stSpaccEnv;
static SPACC_SYMC_CHN_S   s_stSymcChn[SAPCC_MAX_CHN];
static SPACC_DIGEST_CHN_S s_stDigestChn[SAPCC_MAX_CHN];

HI_VOID *g_u32CipherRegBase;
HI_VOID *g_u32Sm4RegBase;

HI_S32 DRV_CIPHER_ConfigChn(HI_U32 softChnId,  CIPHER_CONFIG_CTRL_EX *pConfig);

#ifdef INT_ENABLE
irqreturn_t DRV_Cipher_ISR(HI_S32 irq, HI_VOID *devId)
{
    HI_U32 u32ChnMask, i;

    u32ChnMask = spacc_symc_done_notify();
    HI_INFO_CIPHER("SPACC ISR IRQ: %d, u32ChnMask 0x%x\n", irq, u32ChnMask);

    for(i=CIPHER_PKGxN_CHAN_MIN; i<=CIPHER_PKGxN_CHAN_MAX; i++)
    {
        if ((u32ChnMask >> i) & 0x01)
        {
            if (s_stSymcChn[i].callback)
            {
                s_stSymcChn[i].callback(i);
            }
            else
            {
                s_stSymcChn[i].bSymcDone = HI_TRUE;
                HI_INFO_CIPHER("chn %d wake up\n", i);
                cipher_queue_wait_up(&s_stSymcChn[i].queue);
            }
        }
    }

    u32ChnMask = spacc_digest_done_notify();
    for(i=CIPHER_PKGxN_CHAN_MIN; i<=CIPHER_PKGxN_CHAN_MAX; i++)
    {
        if ((u32ChnMask >> i) & 0x01)
        {
            if (s_stDigestChn[i].callback)
            {
                s_stDigestChn[i].callback(i);
            }
            else
            {
                s_stDigestChn[i].bDigestDone = HI_TRUE;
                cipher_queue_wait_up(&s_stDigestChn[i].queue);
            }
        }
    }

    return IRQ_HANDLED;
}
#endif

HI_S32 DRV_CIPHER_Reset(HI_VOID)
{
    HI_U32 Value;
    HI_U32 *pvirt;

    pvirt = cipher_ioremap_nocache(CIPHER_SPACC_CRG_ADDR_PHY, 16);
    if (pvirt == 0)
    {
        HI_ERR_CIPHER("ioremap_nocache phy addr err:%x.\n", CIPHER_SPACC_CRG_ADDR_PHY);
        return HI_FAILURE;
    }

    HAL_CIPHER_ReadReg(pvirt, &Value);

    HAL_SET_BIT(Value, 0);   /* clock opened */
    HAL_CIPHER_WriteReg(pvirt,Value);

    HAL_SET_BIT(Value, 1); /* reset */
    HAL_CIPHER_WriteReg(pvirt,Value);
    cipher_msleep(5);

    HAL_CLEAR_BIT(Value, 1); /* cancel reset */
    HAL_CIPHER_WriteReg(pvirt,Value);

    cipher_iounmap(pvirt);

    return HI_SUCCESS;
}

HI_S32 DRV_CIPHER_Init(HI_VOID)
{
    HI_S32 ret;
    HI_U32 u32ptaddr = 0;
    HI_U32 i;

    cipher_mutex_init(&g_SymcMutex);

    g_u32CipherRegBase = cipher_ioremap_nocache(CIPHER_CIPHER_REG_BASE_ADDR_PHY, 0x2000);
    if (g_u32CipherRegBase == HI_NULL)
    {
        HI_ERR_CIPHER("ioremap_nocache Cipher Reg failed\n");
        return HI_FAILURE;
    }

    g_u32Sm4RegBase = cipher_ioremap_nocache(CIPHER_SM4_REG_BASE_ADDR_PHY, 0x10);
    if (HI_NULL == g_u32Sm4RegBase)
    {
        HI_ERR_CIPHER("ioremap_nocache Sm4 Reg failed\n");
        return HI_FAILURE;
    }

    cipher_memset_s(&s_stSpaccEnv, sizeof(s_stSpaccEnv), 0, sizeof(SPACC_ENV_S));
    cipher_memset_s(&s_stSymcChn, sizeof(s_stSymcChn), 0, sizeof(s_stSymcChn));
    cipher_memset_s(&s_stDigestChn, sizeof(s_stDigestChn), 0, sizeof(s_stDigestChn));

    s_stSpaccEnv.stMmzBuf.u32Size = spacc_get_node_list_size() + SPACC_PAGE_SIZE;
    ret = cipher_mmz_alloc_remap("CIPHER_ChnBuf", &s_stSpaccEnv.stMmzBuf);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Can NOT get mem for cipher, init failed, exit...\n");
        return HI_FAILURE;
    }
    u32ptaddr = cipher_mmu_table_addr();

    for(i=CIPHER_PKGxN_CHAN_MIN; i<=CIPHER_PKGxN_CHAN_MAX; i++)
    {
        cipher_queue_init(&s_stSymcChn[i].queue);
        cipher_queue_init(&s_stDigestChn[i].queue);
        s_stSymcChn[i].u32PadPhyAddr = s_stSpaccEnv.stMmzBuf.u32StartPhyAddr + SPACC_PAD_BUF_SIZE * i;
        s_stSymcChn[i].pu8PadVirAddr = s_stSpaccEnv.stMmzBuf.pu8StartVirAddr + SPACC_PAD_BUF_SIZE * i;
        s_stSymcChn[i].u32HardNum = i;
        s_stDigestChn[i].u32HardNum = i;
    }

    ret = spacc_init(g_u32CipherRegBase, u32ptaddr,
                     s_stSpaccEnv.stMmzBuf.u32StartPhyAddr + SPACC_PAGE_SIZE,
                     s_stSpaccEnv.stMmzBuf.pu8StartVirAddr + SPACC_PAGE_SIZE);
    if(HI_SUCCESS != ret)
    {
        cipher_mmz_release_unmap(&s_stSpaccEnv.stMmzBuf);
        return HI_FAILURE;
    }

#ifdef REE_SECURE_ENABLE
    {
        U_SEC_CHN_CFG stSecCfg;

        HAL_CIPHER_ReadReg(SEC_CHN_CFG, &stSecCfg.u32);
        stSecCfg.bits.cipher_sec_chn_cfg |= 0x01;
        stSecCfg.bits.hash_sec_chn_cfg |= 0x01;
        HAL_CIPHER_WriteReg(SEC_CHN_CFG, stSecCfg.u32);
    }
#endif

    /* request irq */
    /*
     * CIPHER_IRQ_NUMBER is valid for linux-3.x.y but invalid for linux-4.4.y
     * irq number is defined in linux-4.4.y/arch/arm/boot/dts/hi3796mvxxx.dts for linux-4.4.y
     * the irq num of "cipher" is 126
     * the irq num of "multicipher" is 75
     */
#ifdef INT_ENABLE
#ifdef REE_NONSECURE_ENABLE
    ret = cipher_request_irq(CIPHER_IRQ_NUMBER, DRV_Cipher_ISR, "multicipher");
#else
    ret = cipher_request_irq(CIPHER_IRQ_NUMBER, DRV_Cipher_ISR, "cipher");
#endif
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Irq request failure, ret=%d, irq = %d", ret, CIPHER_IRQ_NUMBER);
        cipher_mmz_release_unmap(&s_stSpaccEnv.stMmzBuf);
        return HI_FAILURE;
    }
#endif

    SM4_Disable();

    return HI_SUCCESS;
}

HI_VOID DRV_CIPHER_DeInit(HI_VOID)
{
    HI_S32 ret;

    ret = spacc_deinit();
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("spacc deinit failed.");
    }

#ifdef INT_ENABLE
#ifdef REE_NONSECURE_ENABLE
    cipher_free_irq(CIPHER_IRQ_NUMBER, "multicipher");
#else
    cipher_free_irq(CIPHER_IRQ_NUMBER, "cipher");
#endif
#endif

    SM4_Disable();

    cipher_mmz_release_unmap(&s_stSpaccEnv.stMmzBuf);

    cipher_iounmap(g_u32CipherRegBase);

    return;
}

HI_S32 DRV_CIPHER_Resume(HI_VOID)
{
    HI_S32 ret;
    U_SEC_CHN_CFG stSecCfg;
    SPACC_SYMC_CHN_S *pstChn;
    HI_U32 i;

    ret = spacc_init(g_u32CipherRegBase, cipher_mmu_table_addr(),
                     s_stSpaccEnv.stMmzBuf.u32StartPhyAddr + SPACC_PAGE_SIZE,
                     s_stSpaccEnv.stMmzBuf.pu8StartVirAddr + SPACC_PAGE_SIZE);
    if(HI_SUCCESS != ret)
    {
        return HI_FAILURE;
    }

    HAL_CIPHER_ReadReg(SEC_CHN_CFG, &stSecCfg.u32);
    stSecCfg.bits.cipher_sec_chn_cfg |= 0x01;
    stSecCfg.bits.hash_sec_chn_cfg |= 0x01;
    HAL_CIPHER_WriteReg(SEC_CHN_CFG, stSecCfg.u32);

   /* Re-config the chn of cipher which is opened */
    for(i = CIPHER_PKGx1_CHAN; i < SPACC_LOGIC_MAX_CHN; i++)
    {
        pstChn = &s_stSymcChn[i];

        /* The chn is opened*/
        if (HI_TRUE == pstChn->bIsOpen)
        {
            /* Re-config the chn of cipher */
            ret = DRV_CIPHER_ConfigChn(i, &pstChn->stCtrl);
            if (ret != HI_SUCCESS)
            {
                HI_ERR_CIPHER("Re-Config cipher chn %d failed!\n", i);
                return ret;
            }
        }
    }

    /* If use klad, user must re-load hard key to cipher,
     *  beause cpu can't access the hard key which provided by klad logic to cipher.
     */
    HI_PRINT("If use cipher with klad key,  please re-load the klad key to cipher\n");

    return HI_SUCCESS;

}

HI_VOID DRV_CIPHER_Suspend(HI_VOID)
{
    spacc_deinit();
}

HI_S32 HI_DRV_CIPHER_CreateHandle(CIPHER_HANDLE_S *pstCIHandle, HI_VOID* file)
{
    HI_U32 i = 0, j = 0;
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32Key[12];
    HI_U32 u32OddKey[8];

    cipher_memset_s(u32Key, sizeof(u32Key), 0, sizeof(u32Key));
    cipher_memset_s(u32OddKey, sizeof(u32OddKey), 0, sizeof(u32OddKey));
    if ( HI_NULL == pstCIHandle)
    {
        HI_ERR_CIPHER("Invalid params!\n");
        return HI_FAILURE;
    }

    if(HI_UNF_CIPHER_TYPE_BUTT <= pstCIHandle->stCipherAtts.enCipherType)
    {
        HI_ERR_CIPHER("Invalid cipher type!\n");
        return HI_FAILURE;
    }

    if(cipher_mutex_lock(&g_SymcMutex))
    {
        HI_ERR_CIPHER("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    for(j = 0; j < 12; j++)
    {
        u32Key[j] = DRV_CIPHER_Rand();
    }
    for(j = 0; j < 8; j++)
    {
        u32OddKey[j] = DRV_CIPHER_Rand();
    }
    if (pstCIHandle->stCipherAtts.enCipherType == HI_UNF_CIPHER_TYPE_COPY_AVOID)
    {
        if (HI_FALSE == s_stSymcChn[0].bIsOpen)
        {
            i = 0;
        }
        else
        {
            i = SAPCC_MAX_CHN;
        }
    }
    else
    {
        for(i = CIPHER_PKGxN_CHAN_MIN; i <= CIPHER_PKGxN_CHAN_MAX; i++)
        {
            if (HI_FALSE == s_stSymcChn[i].bIsOpen)
            {
                break;
            }
        }
    }
    if (i <= CIPHER_PKGxN_CHAN_MAX)
    {
        s_stSymcChn[i].bIsOpen = HI_TRUE;
        s_stSymcChn[i].pWichFile = file;
        s_stSymcChn[i].callback = HI_NULL;
        s_stSymcChn[i].pstNodeList = HI_NULL;
        s_stSymcChn[i].u32NodeNum = 0;
        s_stSymcChn[i].u32NodeNum = 0;
        pstCIHandle->hCIHandle = HI_HANDLE_MAKEHANDLE(HI_ID_CIPHER, 0, i);
        ret = spacc_symc_setkey(s_stSymcChn[i].u32HardNum, u32Key, u32OddKey, SPACC_KEY_LEN);
        if(HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("spacc clear SM1_SK key failed, ret = 0x%x.", ret);
            return HI_FAILURE;
        }
    }
    else
    {
        HI_ERR_CIPHER("No more cipher chan left.\n");
        ret = HI_FAILURE;
    }

    cipher_mutex_unlock(&g_SymcMutex);

    return ret;
}

static HI_S32 DRV_CIPHER_Param_Check(SYMC_ALG_EN  enSymcAlg,
                                     SYMC_MODE_EN enSymcMode,
                                     SYMC_DAT_WIDTH_EN enSymcWidth,
                                     HI_UNF_CIPHER_SM1_ROUND_E  enSm1Round)
{
   /* the mode depend on alg, which limit to hardware
    * des/3des support ecb/cbc/cfb/ofb
    * aes support ecb/cbc/cfb/ofb/ctr/ccm/gcm
    * sm1 support ecb/cbc/cfb/ofb
    * sm4 support ecb/cbc/ctr
    */
    if ((enSymcAlg == SYMC_ALG_DES)
        || (enSymcAlg == SYMC_ALG_3DES)
        || (enSymcAlg == SYMC_ALG_SM1))
    {
        if ( (enSymcMode != SYMC_MODE_ECB)
            && (enSymcMode != SYMC_MODE_CBC)
            && (enSymcMode != SYMC_MODE_CFB)
            && (enSymcMode != SYMC_MODE_OFB))
        {
            HI_ERR_CIPHER("Invalid alg %d and mode: %d\n",enSymcAlg, enSymcMode);
            return HI_ERR_CIPHER_INVALID_PARA;
         }
    }
    else if (enSymcAlg == SYMC_ALG_SM4)
    {
        if ( (enSymcMode != SYMC_MODE_ECB)
            && (enSymcMode != SYMC_MODE_CBC)
            && (enSymcMode != SYMC_MODE_CTR))
        {
            HI_ERR_CIPHER("Invalid alg %d and mode %d\n",enSymcAlg, enSymcMode);
            return HI_ERR_CIPHER_INVALID_PARA;
         }
    }

   /* the bit width depend on alg and mode, which limit to hardware
    * des/3des with cfb/ofb support bit1, bit8, bit 64.
    * aes with cfb/ofb only support bit128.
    * sm1 with ofb only support bit128, cfb support bit1, bit8, bit 64.
    */
	if ((enSymcAlg == SYMC_ALG_DES) || (enSymcAlg == SYMC_ALG_3DES))
    {
        if((enSymcMode == SYMC_MODE_CFB) || (enSymcMode == SYMC_MODE_OFB))
        {
            if ((enSymcWidth != SYMC_DAT_WIDTH_64) && (enSymcWidth != SYMC_DAT_WIDTH_8)
                 && (enSymcWidth != SYMC_DAT_WIDTH_1))
            {
                HI_ERR_CIPHER("Invalid mode %d and bit width %d\n",enSymcMode, enSymcWidth);
                return HI_ERR_CIPHER_INVALID_PARA;
            }
        }
    }

    if (enSymcAlg == SYMC_ALG_AES)
    {

        if ((enSymcMode == SYMC_MODE_CFB) && (enSymcWidth >= SYMC_DAT_WIDTH_COUNT))
        {
            HI_ERR_CIPHER("Invalid alg %d mode %d and width %d\n", enSymcAlg, enSymcMode, enSymcWidth);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
        if ((enSymcMode == SYMC_MODE_OFB) && (enSymcWidth != SYMC_DAT_WIDTH_128))
        {
            HI_ERR_CIPHER("Invalid alg %d mode %d and width %d\n", enSymcAlg, enSymcMode, enSymcWidth);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }

    if (enSymcAlg == SYMC_ALG_SM1)
    {
        if ((enSymcMode == SYMC_MODE_OFB) && (enSymcWidth != SYMC_DAT_WIDTH_128))
        {
            HI_ERR_CIPHER("Invalid alg %d mode %d and width %d\n", enSymcAlg, enSymcMode, enSymcWidth);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
        if ((enSymcMode == SYMC_MODE_CFB) && (enSymcWidth >= SYMC_DAT_WIDTH_COUNT))
        {
            HI_ERR_CIPHER("Invalid alg %d mode %d and width %d\n", enSymcAlg, enSymcMode, enSymcWidth);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }

    if ((enSymcAlg == SYMC_ALG_SM1)  &&  (enSm1Round >= HI_UNF_CIPHER_SM1_ROUND_BUTT))
    {
        HI_ERR_CIPHER("Invalid alg %d and Sm1Round %d\n",enSymcAlg, enSm1Round);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_CIPHER_MatchenAlg(CIPHER_CONFIG_CTRL_EX *pConfig,
                               SYMC_ALG_EN  *penSymcAlg,
                               HI_U32 *pu32BlockSize)
{
    /*set alg and block size*/
    switch(pConfig->enAlg)
    {
        case HI_UNF_CIPHER_ALG_DES:
            *penSymcAlg = SYMC_ALG_DES;
            *pu32BlockSize = 8;
            break;
        case HI_UNF_CIPHER_ALG_3DES:
            *penSymcAlg = SYMC_ALG_3DES;
            *pu32BlockSize = 8;
            break;
        case HI_UNF_CIPHER_ALG_AES:
            *penSymcAlg = SYMC_ALG_AES;
            *pu32BlockSize = 16;
            break;
        case HI_UNF_CIPHER_ALG_DMA:
            *penSymcAlg = SYMC_ALG_NULL_CIPHER;
            *pu32BlockSize = 16;
            break;
        case HI_UNF_CIPHER_ALG_SM1:
            *penSymcAlg = SYMC_ALG_SM1;
            *pu32BlockSize = 16;
            break;
        case HI_UNF_CIPHER_ALG_SM4:
            *penSymcAlg = SYMC_ALG_SM4;
            *pu32BlockSize = 16;
            break;
        default:
            HI_ERR_CIPHER("Invalid alg: 0x%x\n", pConfig->enAlg);
            return HI_ERR_CIPHER_INVALID_PARA;
    }

        return HI_SUCCESS;
}

static HI_S32 DRV_CIPHER_MatchWorkMode(CIPHER_CONFIG_CTRL_EX *pConfig,
                                         SYMC_MODE_EN *penSymcMode)
{
    switch(pConfig->enWorkMode)
    {
        case HI_UNF_CIPHER_WORK_MODE_ECB:
            *penSymcMode = SYMC_MODE_ECB;
            break;
        case HI_UNF_CIPHER_WORK_MODE_CBC:
            *penSymcMode = SYMC_MODE_CBC;
            break;
        case HI_UNF_CIPHER_WORK_MODE_CFB:
            *penSymcMode = SYMC_MODE_CFB;
            break;
        case HI_UNF_CIPHER_WORK_MODE_OFB:
            *penSymcMode = SYMC_MODE_OFB;
            break;
        case HI_UNF_CIPHER_WORK_MODE_CTR:
            *penSymcMode = SYMC_MODE_CTR;
            break;
        case HI_UNF_CIPHER_WORK_MODE_CCM:
            *penSymcMode = SYMC_MODE_CCM;
            break;
        case HI_UNF_CIPHER_WORK_MODE_GCM:
            *penSymcMode = SYMC_MODE_GCM;
            break;
        default:
            HI_ERR_CIPHER("Invalid mode: 0x%x\n", pConfig->enWorkMode);
            return HI_ERR_CIPHER_INVALID_PARA;
    }

        return HI_SUCCESS;
}

static HI_S32 DRV_CIPHER_MatchBitWidth(CIPHER_CONFIG_CTRL_EX *pConfig,
                               SYMC_DAT_WIDTH_EN *penSymcWidth)
{
    /* set the bit width which depend on alg and mode */
    if ((pConfig->enWorkMode == HI_UNF_CIPHER_WORK_MODE_CFB)
        || (pConfig->enWorkMode == HI_UNF_CIPHER_WORK_MODE_OFB))
    {
        switch(pConfig->enBitWidth)
        {
            case HI_UNF_CIPHER_BIT_WIDTH_64BIT:
                *penSymcWidth = SYMC_DAT_WIDTH_64;
                break;
            case HI_UNF_CIPHER_BIT_WIDTH_8BIT:
                *penSymcWidth = SYMC_DAT_WIDTH_8;
                break;
            case HI_UNF_CIPHER_BIT_WIDTH_1BIT:
                *penSymcWidth = SYMC_DAT_WIDTH_1;
                break;
            case HI_UNF_CIPHER_BIT_WIDTH_128BIT:
                *penSymcWidth = SYMC_DAT_WIDTH_128;
                break;
            default:
                HI_ERR_CIPHER("Invalid width: 0x%x, mode 0x%x, alg 0x%x\n", pConfig->enBitWidth,
                    pConfig->enWorkMode, pConfig->enAlg);
                return HI_ERR_CIPHER_INVALID_PARA;
        }
    }
    else
    {
        *penSymcWidth = SYMC_DAT_WIDTH_128;
    }

    return HI_SUCCESS;
}

/*change the unf params to drive params*/
static HI_S32 DRV_CIPHER_Param(CIPHER_CONFIG_CTRL_EX *pConfig,
                               SYMC_ALG_EN  *penSymcAlg,
                               SYMC_MODE_EN *penSymcMode,
                               SYMC_DAT_WIDTH_EN *penSymcWidth,
                               HI_U32 *pu32Klen,
                               HI_U32 *pu32BlockSize)
{
    HI_S32 Ret;

    /*set alg and block size*/
    Ret = DRV_CIPHER_MatchenAlg(pConfig, penSymcAlg, pu32BlockSize);
    if(Ret != HI_SUCCESS)
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    /* set the mode which depend on alg */
    Ret = DRV_CIPHER_MatchWorkMode(pConfig, penSymcMode);
    if(Ret != HI_SUCCESS)
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    /* set the bit width which depend on alg and mode */
    Ret = DRV_CIPHER_MatchBitWidth(pConfig, penSymcWidth);
    if(Ret != HI_SUCCESS)
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

   /* set the key length depend on alg
    * des/3des support 2key and 3key
    * aes support 128, 192, and 256
    * sm1 support ak/ek/sk
    * sm4 support 128
    */
    if (pConfig->enAlg == HI_UNF_CIPHER_ALG_AES)
    {
        switch(pConfig->enKeyLen)
        {
            case HI_UNF_CIPHER_KEY_AES_128BIT:
                *pu32Klen = 16;
                break;
            case HI_UNF_CIPHER_KEY_AES_192BIT:
                *pu32Klen = 24;
                break;
            case HI_UNF_CIPHER_KEY_AES_256BIT:
                *pu32Klen = 32;
                break;
            default:
                HI_ERR_CIPHER("Invalid key len: 0x%x\n", pConfig->enKeyLen);
                return HI_ERR_CIPHER_INVALID_PARA;
        }
    }
    else if(pConfig->enAlg == HI_UNF_CIPHER_ALG_SM1)
    {
        *pu32Klen = 48;
    }
    else if(pConfig->enAlg == HI_UNF_CIPHER_ALG_SM4)
    {
        *pu32Klen = 16;
    }
    else if(pConfig->enAlg == HI_UNF_CIPHER_ALG_3DES)
    {
        /*check k1 != k2*/
        if (pConfig->bKeyByCA == HI_FALSE)
        {
            if (memcmp(&pConfig->u32Key[0], &pConfig->u32Key[2], 8) == 0)
            {
                HI_ERR_CIPHER("Invalid 3DES key, k1 = k2 \n");
                return HI_ERR_CIPHER_INVALID_PARA;
            }
        }

        switch(pConfig->enKeyLen)
        {
            case HI_UNF_CIPHER_KEY_DES_2KEY:
                *pu32Klen = 16;
                break;
            case HI_UNF_CIPHER_KEY_DES_3KEY:
                /*check k2 != k3*/
                if (pConfig->bKeyByCA == HI_FALSE)
                {
                    if (memcmp(&pConfig->u32Key[2], &pConfig->u32Key[4], 8) == 0)
                    {
                        HI_ERR_CIPHER("Invalid 3DES key, k2 = k3 \n");
                        return HI_ERR_CIPHER_INVALID_PARA;
                    }
                }
                *pu32Klen = 24;
                break;
            default:
                HI_ERR_CIPHER("Invalid key len: 0x%x\n", pConfig->enKeyLen);
                return HI_ERR_CIPHER_INVALID_PARA;
        }
    }
    else if(pConfig->enAlg == HI_UNF_CIPHER_ALG_DES)
    {
        *pu32Klen = 8;
    }

    if (pConfig->stChangeFlags.bit1IV > CIPHER_IV_CHANGE_ALL_PKG)
    {
        HI_ERR_CIPHER("Invalid IV Change Flags: 0x%x\n", pConfig->stChangeFlags.bit1IV);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if ((pConfig->stChangeFlags.bit1IV == CIPHER_IV_CHANGE_ALL_PKG)
        && ((pConfig->enWorkMode == HI_UNF_CIPHER_WORK_MODE_CCM)
            || (pConfig->enWorkMode == HI_UNF_CIPHER_WORK_MODE_GCM)))
    {
        HI_ERR_CIPHER("Invalid IV Change Flags: 0x%x\n", pConfig->stChangeFlags.bit1IV);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (pConfig->bKeyByCA && (pConfig->enCaType >= HI_UNF_CIPHER_CA_TYPE_BUTT))
    {
        HI_ERR_CIPHER("Invalid CA Type: 0x%x\n", pConfig->enCaType);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

//    printk("enSymcAlg %d, enSymcMode %d, u32Klen %d, enSymcWidth %d\n", *penSymcAlg, *penSymcMode, *pu32Klen, *penSymcWidth);

    return DRV_CIPHER_Param_Check(*penSymcAlg, *penSymcMode, *penSymcWidth , pConfig->enSm1Round);
}

HI_S32 DRV_CIPHER_ConfigChn(HI_U32 softChnId,  CIPHER_CONFIG_CTRL_EX *pConfig)
{
    HI_S32 ret;
    HI_U32 u32KeyLen = 0;
    HI_U32 u32IV[4];
    HI_U32 u32IvLen;
    HI_U32 i;
    HI_UNF_CIPHER_CTRL_CHANGE_FLAG_S stChangeFlags;
    SPACC_SYMC_CHN_S *pstChn = &s_stSymcChn[softChnId];
    HI_U8 *pu8Buf;
    SYMC_DAT_WIDTH_EN enSymcWidth;
    SYMC_ALG_EN  enSymcAlg;
    SYMC_MODE_EN enSymcMode;
    HI_U32 u32Klen = 0;

    stChangeFlags.bit1IV = pstChn->stCtrl.stChangeFlags.bit1IV;

    cipher_memset_s(u32IV, sizeof(u32IV), 0, sizeof(u32IV));
    cipher_memcpy_s(&pstChn->stCtrl,sizeof(pstChn->stCtrl), pConfig, sizeof(CIPHER_CONFIG_CTRL_EX));
    if (pstChn->stCtrl.bKeyByCA == HI_TRUE)
    {
        pstChn->stCtrl.stChangeFlags.bit1IV = stChangeFlags.bit1IV;
    }

    ret = DRV_CIPHER_Param(pConfig, &enSymcAlg, &enSymcMode,
        &enSymcWidth, &u32Klen, &pstChn->u32BlockSize);
    if (HI_SUCCESS != ret)
    {
        return HI_FAILURE;
    }

    if( pConfig->enWorkMode == HI_UNF_CIPHER_WORK_MODE_CCM)
    {
        /* The octet lengths of N are denoted  n,
         * The octet length of the binary represen tation of the
         * octet length of the payload denoted q,
         * n is an element of {7, 8, 9, 10, 11, 12, 13}
         * n + q = 15
         * here the string of N  is pConfig->u32IV, and n is pConfig->u32IVLen.
         */
        if ((pConfig->u32IVLen< 7) || (pConfig->u32IVLen > 13))
        {
            HI_ERR_CIPHER("Invalid IV LEN: 0x%x\n", pConfig->u32IVLen);
            return HI_ERR_CIPHER_INVALID_PARA;
        }

        /* the parameter t denotes the octet length of T(tag)
         * t is an element of  { 4, 6, 8, 10, 12, 14, 16}
         * here t is pConfig->u32TagLen
         */
        if ((pConfig->u32TagLen & 0x01) || (pConfig->u32TagLen < 4) || (pConfig->u32TagLen > 16))
        {
            HI_ERR_CIPHER("Invalid TAG LEN: 0x%x\n", pConfig->u32TagLen);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
        /* Formatting of the Counter Blocks(IV for CTR)
         *
         * According to the CCM spec, the counter is equivalent to
         * a formatting of the counter index i into a complete data block.
         * The counter blocks Ctri are formatted as shown below:
         * | Octet number:  0    1 ... 15-q    16-q ... 15
         * | Contents:     Flags     N             [i]
         * Within each block Ctri, the N is get from pConfig->u32IV, n + q = 15,
         * so the q equal to 15 - pConfig->u32IVLen.
         * the [i] is the block conut start with 0,
         * In the Flags field, Bits 0, 1, and 2 contain the encoding of q - 1,
         * others bits shall be set to 0.
         * so the first byte of IV shall be q -1, that is 15 - pConfig->u32IVLen - 1
         */
        pu8Buf = (HI_U8*)u32IV;
        cipher_memset_s(pu8Buf, sizeof(u32IV), 0, 16);
        pu8Buf[0] = 14 - pConfig->u32IVLen; /*IV[0] = q - 1 = 15 - n -1*/
        cipher_memcpy_s(pu8Buf + 1, sizeof(u32IV) -1, pConfig->u32IV, pConfig->u32IVLen);
        u32IvLen = pConfig->u32IVLen + 1;

    }
    else if ( pConfig->enWorkMode == HI_UNF_CIPHER_WORK_MODE_GCM)
    {
       /* According to the GCM spec, the IVLen >= 1, typical equal to 12,
        * but limit to hard logic devising, the IVLen can't large than 16.
        */
        if (pConfig->u32IVLen > 16)
        {
            HI_ERR_CIPHER("Invalid IV LEN: 0x%x\n", pConfig->u32IVLen);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
        cipher_memcpy_s(u32IV, sizeof(u32IV), pConfig->u32IV, pConfig->u32IVLen);
        u32IvLen = pConfig->u32IVLen;
    }
    else if (pConfig->enWorkMode <= HI_UNF_CIPHER_WORK_MODE_CTR)
    {
        /* IV length, 16 for aes, 8 for des/3des*/
        cipher_memcpy_s(u32IV, sizeof(u32IV), pConfig->u32IV, 16);
        u32IvLen = 16;
    }
    else
    {
         HI_ERR_CIPHER("Invalid mode: 0x%x\n", pConfig->enWorkMode);
         return HI_ERR_CIPHER_INVALID_PARA;
    }

    /*chn 1~7, data transferred by DMA */
    if (softChnId != 0)
    {
        ret = spacc_symc_config(pstChn->u32HardNum, enSymcAlg, enSymcMode,
            enSymcWidth, pConfig->enSm1Round, u32Klen, pConfig->bKeyByCA);
        if (SPACC_OK != ret)
        {
            HI_ERR_CIPHER("spacc_symc_config failed\n");
            return HI_FAILURE;
        }

        ret = spacc_symc_setkey(pstChn->u32HardNum, pConfig->u32Key, pConfig->u32OddKey, u32Klen);
        if(HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("spacc set key failed, ret = 0x%x.", ret);
            return HI_FAILURE;
        }

        /* If use KLAD, the hard key and IV should be set by KLAD
         * The KLAD should call HI_DRV_CIPHER_SetIV to set IV,
         * and send the hard key to spacc within hard logic,
         * which don't signal to software drives.
         */
        if ( pConfig->bKeyByCA == HI_FALSE)
        {
            ret = spacc_symc_setiv(pstChn->u32HardNum, (HI_U8*)u32IV, u32IvLen);
            if (SPACC_OK != ret)
            {
                HI_ERR_CIPHER("spacc_symc_config failed\n");
                return HI_FAILURE;
            }
        }
    }
    else     /*chn 0, data transferred by CPU, spacc_body do not drvie chn0*/
    {
        U_CHAN0_CIPHER_CTRL stChn0Ctrl;

        HAL_CIPHER_WriteReg(ODD_EVEN_KEY_SEL, 0x00);
        for(i=0; i<8; i++)
        {
            HAL_CIPHER_WriteReg(CHAN0_CIPHER_KEY + i *4, pConfig->u32Key[i]);
        }
        if (enSymcAlg == SYMC_ALG_SM1)
        {
            for(i=0; i<4; i++)
            {
                HAL_CIPHER_WriteReg(CHAN0_SM1_SK+i*4, pConfig->u32Key[i + 8]);
            }
        }

        /* If use KLAD, the hard key and IV should be set by KLAD
         * The KLAD should call HI_DRV_CIPHER_SetIV to set IV,
         * and send the hard key to spacc within hard logic,
         * which don't signal to software drives.
         */
        if ( pConfig->bKeyByCA == HI_FALSE)
        {
            for(i=0; i<4; i++)
            {
                HAL_CIPHER_WriteReg(CHAN0_CIPHER_IV + i *4, u32IV[i]);
            }
        }
        if (enSymcAlg == SYMC_ALG_AES)
        {
            u32KeyLen = u32Klen/8 - 2;
        }
        else if (enSymcAlg == SYMC_ALG_3DES)
        {
            u32KeyLen = (u32Klen == 16 ? 3 : 2);
        }

        stChn0Ctrl.u32 = 0x00;
        stChn0Ctrl.bits.sym_ch0_sm1_round_num = pConfig->enSm1Round;
        stChn0Ctrl.bits.sym_ch0_ivin_sel = 0x01;
        stChn0Ctrl.bits.sym_ch0_key_sel = pConfig->bKeyByCA;
        stChn0Ctrl.bits.sym_ch0_key_length = u32KeyLen;
        stChn0Ctrl.bits.sym_ch0_dat_width = enSymcWidth;
        stChn0Ctrl.bits.sym_ch0_alg_sel = enSymcAlg;
        stChn0Ctrl.bits.sym_ch0_alg_mode = enSymcMode;
        if (pConfig->enWorkMode == HI_UNF_CIPHER_WORK_MODE_GCM)
        {
            stChn0Ctrl.bits.sym_ch0_gcm_iv_len = pConfig->u32IVLen - 1;
        }
        HAL_CIPHER_WriteReg(CHAN0_CIPHER_CTRL, stChn0Ctrl.u32);
    }

    return HI_SUCCESS;
}

HI_S32 HI_DRV_CIPHER_ConfigChnEx(HI_U32 softChnId, CIPHER_CONFIG_CTRL_EX *pConfig)
{
    HI_S32 ret;

    if ( HI_NULL == pConfig)
    {
        HI_ERR_CIPHER("Invalid params!\n");
        return HI_FAILURE;
    }

    if(cipher_mutex_lock(&g_SymcMutex))
    {
        HI_ERR_CIPHER("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    SPACC_CheckHandle(softChnId);

    ret = DRV_CIPHER_ConfigChn(softChnId, pConfig);

    cipher_mutex_unlock(&g_SymcMutex);

    return ret;
}

/*This function will be called by KLAD*/
HI_S32 HI_DRV_CIPHER_SetIV(HI_HANDLE hCIHandle,  HI_U8 *pu8IV, HI_U32 u32IVLen)
{
    HI_U32 softChnId;
    SPACC_SYMC_CHN_S *pstChn;
    HI_U32 i;
    HI_S32 ret;

    if (pu8IV == HI_NULL)
    {
        HI_ERR_CIPHER("pu8IV is null!\n");
        return HI_FAILURE;
    }
    if (u32IVLen > 16)
    {
        HI_ERR_CIPHER("u32IVLen overflow!\n");
        return HI_FAILURE;
    }

    softChnId = HI_HANDLE_GET_CHNID(hCIHandle);
    SPACC_CheckHandle(softChnId);

    if(cipher_mutex_lock(&g_SymcMutex))
    {
        HI_ERR_CIPHER("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    pstChn = &s_stSymcChn[softChnId];
    memcpy(pstChn->stCtrl.u32IV, pu8IV, u32IVLen);

    if (softChnId == 0)
    {
        for(i=0; i<4; i++)
        {
            HAL_CIPHER_WriteReg(CHAN0_CIPHER_IV + i *4, pstChn->stCtrl.u32IV[i]);
        }
    }
    else
    {
        ret = spacc_symc_setiv(pstChn->u32HardNum, pu8IV, u32IVLen);
        if (SPACC_OK != ret)
        {
            HI_ERR_CIPHER("spacc_symc_config failed\n");
            return HI_FAILURE;
        }
    }

    pstChn->stCtrl.stChangeFlags.bit1IV = CIPHER_IV_CHANGE_ONE_PKG;

     cipher_mutex_unlock(&g_SymcMutex);

    return HI_SUCCESS;

}

HI_S32 HI_DRV_CIPHER_DestroyHandle(HI_HANDLE hCipherchn)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 softChnId = 0;
    HI_U32 u32Key[12];
    HI_U32 u32OddKey[8];

    softChnId = HI_HANDLE_GET_CHNID(hCipherchn);
    SPACC_CheckHandle(softChnId);

    if(cipher_mutex_lock(&g_SymcMutex))
    {
        HI_ERR_CIPHER("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    cipher_memset_s(u32Key, sizeof(u32Key), 0, sizeof(u32Key));
    cipher_memset_s(u32OddKey, sizeof(u32OddKey), 0, sizeof(u32OddKey));

    ret = spacc_symc_setkey(s_stSymcChn[softChnId].u32HardNum, u32Key, u32OddKey, SPACC_KEY_LEN);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("spacc clear key failed, ret = 0x%x.", ret);
        return HI_FAILURE;
    }

    s_stSymcChn[softChnId].bIsOpen = HI_FALSE;

    cipher_mutex_unlock(&g_SymcMutex);

    return HI_SUCCESS;
}

static HI_S32 DRV_CIPHER_SymcWaitDone(SPACC_SYMC_CHN_S *pstChn, HI_U32 u32TimeOut)
{
    HI_S32 ret = HI_SUCCESS;
    HI_S32 wait;
    HI_U32 src_addr = HI_NULL;
    HI_U32 dst_addr = HI_NULL;
    HI_U32 in_addr = HI_NULL, in_size = 0;
    HI_U32 out_addr = HI_NULL, out_size = 0;


#ifdef INT_ENABLE
    wait = cipher_queue_wait_timeout(pstChn->queue, pstChn->bSymcDone != HI_FALSE, u32TimeOut);
    if (wait == 0)
    {
        HI_ERR_CIPHER("Encrypt time out! Chn %d, CIPHER_IRQ_NUMBER: %d\n", pstChn->u32HardNum, CIPHER_IRQ_NUMBER);
        ret = HI_FAILURE;
    }
#else
    while(--u32TimeOut)
    {
        if (spacc_symc_done_try(pstChn->u32HardNum))
        {
            break;
        }
        cipher_msleep(1);
    }
    if (u32TimeOut == 0)
    {
        HI_ERR_CIPHER("Encrypt time out!\n");
        ret = HI_FAILURE;
    }
#endif

    if(HI_UNF_CIPHER_ALG_SM4 == pstChn->stCtrl.enAlg)
    {
        SM4_Disable();
    }

   /* check error code
    * bit0: klad_key_use_err
    * bit1: alg_len_err
    * bit2: smmu_page_unvlid
    */
    wait = spacc_symc_get_err_code(pstChn->u32HardNum, &src_addr, &dst_addr);
    if(wait & 0x01)
    {
        HI_ERR_CIPHER("cipher error: klad_key_use_err, chn %d !!!\n", pstChn->u32HardNum);
        ret = HI_FAILURE;
    }
    if(wait & 0x02)
    {
        HI_ERR_CIPHER("cipher error: alg_len_err, chn %d !!!\n", pstChn->u32HardNum);
        ret = HI_FAILURE;
    }
    if(wait & 0x04)
    {
        HI_ERR_CIPHER("cipher error: smmu_page_unvlid, chn %d !!!\n", pstChn->u32HardNum);
        spacc_symc_last_node(pstChn->u32HardNum, &in_addr, &in_size, &out_addr, &out_size);
        HI_ERR_CIPHER("in_addr: 0x%x, in_size 0x%x, out_addr 0x%x, out_size 0x%x\n",
            in_addr, in_size, out_addr, out_size);
        HI_ERR_CIPHER("CIPHER_IN_BUF_RPTR: 0x%x, CIPHER_OUT_BUF_RPTR 0x%x\n", src_addr, dst_addr);
#ifdef HI_CIPHER_DEBUG
        __dump_backtraces();
        dump_mem();
#endif
        ret = HI_FAILURE;
    }

    return ret;
}

static HI_S32 DRV_CIPHER_DigestWaitDone(SPACC_DIGEST_CHN_S *pstChn)
{
    HI_S32 ret = HI_SUCCESS;
    HI_S32 wait;
    HI_U32 u32TimeOut = SPACC_TIME_OUT;
    HI_U32 src_addr = HI_NULL, addr = HI_NULL, size = 0;

#ifdef INT_ENABLE
    wait = cipher_queue_wait_timeout(pstChn->queue, pstChn->bDigestDone!= HI_FALSE, u32TimeOut);
    if (wait == 0)
    {
        HI_ERR_CIPHER("hash time out! CIPHER_IRQ_NUMBER: %d\n", CIPHER_IRQ_NUMBER);
        ret = HI_FAILURE;
    }
#else
    u32TimeOut = 0;
    while(u32TimeOut++ < SPACC_TIME_OUT)
    {
        if (spacc_digest_done_try(pstChn->u32HardNum))
        {
            break;
        }
        cipher_msleep(1);
    }
    if (u32TimeOut >= SPACC_TIME_OUT)
    {
        HI_ERR_CIPHER("hash time out!\n");
        ret = HI_FAILURE;
    }
#endif

   /* check error code
    * bit0: klad_key_use_err
    * bit1: alg_len_err
    * bit2: smmu_page_unvlid
    */
    wait = spacc_digest_get_err_code(pstChn->u32HardNum, &src_addr);
    if(wait & 0x01)
    {
        HI_ERR_CIPHER("hash error: klad_key_use_err, chn %d !!!\n", pstChn->u32HardNum);
        ret = HI_FAILURE;
    }
    if(wait & 0x02)
    {
        HI_ERR_CIPHER("hash error: alg_len_err, chn %d !!!\n", pstChn->u32HardNum);
        ret = HI_FAILURE;
    }
    if(wait & 0x04)
    {
        HI_ERR_CIPHER("hash error: smmu_page_unvlid, chn %d !!!\n", pstChn->u32HardNum);
        spacc_digest_last_node(pstChn->u32HardNum, &addr, &size);
        HI_ERR_CIPHER("Addr 0x%x, size 0x%x, SRC CHANn_HASH_IN_BUF_RPTR: 0x%x\n", addr, size, src_addr);
#ifdef HI_CIPHER_DEBUG
        __dump_backtraces();
        dump_mem();
#endif
        ret = HI_FAILURE;
    }

    return ret;
}

static HI_S32 DRV_CIPHER_CCM_HeadFormat(SPACC_SYMC_CHN_S *pstChn, HI_U32 u32EncLen, HI_U8 u8B0[16], HI_U8 u8B1[16], HI_U32 *pu32B1Len)
{
    HI_U8 *pbuf;
    HI_U32 u32Index;

    if ( HI_NULL == pstChn)
    {
        HI_ERR_CIPHER("Invalid params!\n");
        return HI_FAILURE;
    }

    /* Format B0*/
    /* The leading octet of the first block of the formatting, B0,
     * contains four flags for control information: two single bits,
     * called  Reserved  and  Adata, and two strings of three bits,
     * to encode the values t and q.  The encoding of t is [(t -2)/2],
     * and the encoding of q is [ q-1].
     * The ordering of the flags with in the octet is given:
     *  _____________________________________________________
     * |Bit number  7     |   6   | 5  4  3     |  2  1  0   |
     * |Contents  Reserved  Adata   [( t -2)/2] |  [q-1]     |
     *  -----------------------------------------------------
     * The remaining 15 octets of the first block of  the formatting are
     * devoted to the nonce and the binary representation of
     * the message length in  q octets, as given:
     *  _____________________________________________
     * |Octet number  0   | 1 ... 15-q | 16-q ... 15 |
     * |Contents    Flags |      N     |      Q      |
     *  ---------------------------------------------
    */
    pbuf = u8B0;
    u32Index = 0;
    cipher_memset_s(pbuf, AES_BLOCK_SIZE, 0, AES_BLOCK_SIZE);
    pbuf[u32Index]  = (pstChn->stCtrl.u32ALen > 0 ? 1 : 0) << 6;//Adata
    pbuf[u32Index] |= ((pstChn->stCtrl.u32TagLen- 2)/2) << 3;// ( t -2)/2
    pbuf[u32Index] |= ((15 - pstChn->stCtrl.u32IVLen) - 1);// q-1, n+q=15
    u32Index++;
    cipher_memcpy_s(&pbuf[u32Index], AES_BLOCK_SIZE - u32Index,
        pstChn->stCtrl.u32IV, pstChn->stCtrl.u32IVLen);
    u32Index+=pstChn->stCtrl.u32IVLen;
    if(u32Index <= 12)
    {
        u32Index = 12;
        pbuf[u32Index++] = (HI_U8)(u32EncLen >> 24);
        pbuf[u32Index++] = (HI_U8)(u32EncLen >> 16);
        pbuf[u32Index++] = (HI_U8)(u32EncLen >> 8);
        pbuf[u32Index++] = (HI_U8)(u32EncLen);
    }
    else if ((u32Index == 13) && (u32EncLen <= 0xFFFFFF))
    {
        pbuf[u32Index++] = (HI_U8)(u32EncLen >> 16);
        pbuf[u32Index++] = (HI_U8)(u32EncLen >> 8);
        pbuf[u32Index++] = (HI_U8)(u32EncLen);
    }
    else if ((u32Index == 14) && (u32EncLen <= 0xFFFF))
    {
        pbuf[u32Index++] = (HI_U8)(u32EncLen >> 8);
        pbuf[u32Index++] = (HI_U8)(u32EncLen);
    }
    else
    {
        HI_ERR_CIPHER("Invalid Mlen: 0x%x, q: 0x%x!\n", u32EncLen, 16 - u32Index);
        return HI_FAILURE;
    }
//    HI_PRINT_HEX("B0", pbuf, u32Index);

   /* Formatting of the Associated Data in B1, the length of A denotes as a*/
   /* The value a is encoded according to the following three cases:
    * If 0 < a < 2^16 - 2^8, then a  is encoded as a[0..15], i.e., two octets.
    * If 2^16 - 2^8 ≤a < 2^32, then a  is encoded as 0xff || 0xfe || a[0..31], i.e., six octets.
    * If 2^32 ≤a < 2^64, then  a is encoded as 0xff || 0xff || a[0..63], i.e., ten octets.
    * For example, if a=2^16, the encoding of a  is
    * 11111111 11111110 00000000 00000001 00000000 00000000.
    */
    pbuf = u8B1;
    u32Index = 0;
    if (pstChn->stCtrl.u32ALen > 0)
    {
        if (pstChn->stCtrl.u32ALen < (0x10000 - 0x100))
        {
            pbuf[u32Index++] = (HI_U8)(pstChn->stCtrl.u32ALen >> 8);
            pbuf[u32Index++] = (HI_U8)(pstChn->stCtrl.u32ALen);
        }
        else
        {
            pbuf[u32Index++] = 0xFF;
            pbuf[u32Index++] = 0xFE;
            pbuf[u32Index++] = (HI_U8)(pstChn->stCtrl.u32ALen >> 24);
            pbuf[u32Index++] = (HI_U8)(pstChn->stCtrl.u32ALen >> 16);
            pbuf[u32Index++] = (HI_U8)(pstChn->stCtrl.u32ALen >> 8);
            pbuf[u32Index++] = (HI_U8)pstChn->stCtrl.u32ALen;
        }
    }
    *pu32B1Len  = u32Index;

    return HI_SUCCESS;
}

static HI_S32 DRV_CIPHER_CPUInput(HI_U8 *pu8DI, HI_U8 *pu8DO, HI_U32 u32Len,
                                  HI_U32 u32BS, HI_U32 u32Ctrl, HI_BOOL bSetLast)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32Offset = 0;
    HI_U32 u32Time;
    HI_U32 u32Buf[4];
    HI_U32 u32Size;
    HI_U32 i;
    U_CHAN0_CIPHER_CTRL chn0_ctrl;
    U_CIPHER_INT_RAW    int_raw;

    chn0_ctrl.u32 = u32Ctrl;

    while(u32Offset < u32Len)
    {
        /*Compute one block, if less than one block, padding with 0*/
        u32Size = (u32Offset + u32BS) < u32Len ? u32BS : u32Len - u32Offset;
        cipher_memset_s(u32Buf, sizeof(u32Buf), 0, sizeof(u32Buf));
        cipher_memcpy_s(u32Buf, sizeof(u32Buf), &pu8DI[u32Offset], u32Size);
        for(i=0; i<u32BS/4; i++)
        {
            HAL_CIPHER_WriteReg(CHAN0_CIPHER_DIN + i*4, u32Buf[i]);
        }

        /* may be needs set last flag when compute last block*/
        if(((u32Offset + u32BS) >= u32Len) && bSetLast)
        {
            chn0_ctrl.bits.sym_ch0_ccm_gcm_pc_last = 0x01;
        }
        HAL_CIPHER_WriteReg(CHAN0_CIPHER_CTRL, chn0_ctrl.u32);

        /* start working */
        HAL_CIPHER_WriteReg(CHAN0_CIPHER_CTRL, chn0_ctrl.u32 | 0x01);

        /*Waiting compute finished*/
        u32Time = 0;
        HAL_CIPHER_ReadReg(CIPHER_INT_RAW, &int_raw.u32);
        while(!(int_raw.bits.cipher_chn_obuf_raw & 0x01) && (u32Time++ < SPACC_TIME_OUT))
        {
            HAL_CIPHER_ReadReg(CIPHER_INT_RAW, &int_raw.u32);
        }
        if(u32Time >= SPACC_TIME_OUT)
        {
            HI_ERR_CIPHER("Chn 0 time out!\n");
            return HI_FAILURE;
        }

        /*Clean raw interrupt */
        int_raw.u32 = 0x00;
        int_raw.bits.cipher_chn_obuf_raw = 0x01;
        HAL_CIPHER_WriteReg(CIPHER_INT_RAW, int_raw.u32);

        /*May be needs read output data*/
        if (pu8DO)
        {
            for(i=0; i<u32BS/4; i++)
            {
                HAL_CIPHER_ReadReg(CHAN0_CIPHER_DOUT + i*4, &u32Buf[i]);
            }
            cipher_memcpy_s(&pu8DO[u32Offset], u32Len, (HI_U8*)u32Buf, u32Size);
        }

        /*prepare compute next block*/
        u32Offset += u32BS;
        chn0_ctrl.u32 &= ~(0x01 << 15); //iv set
    }

    return ret;
}

static HI_S32 DRV_CIPHER_CpuEncPhy(CIPHER_DATA_S *pstCIData, HI_U32 u32BlockSize, HI_BOOL bIsDecrypt)
{
    HI_U32 ret;
    HI_U8  *pu8SrcVir = HI_NULL;
    HI_U8  *pu8DestVir = HI_NULL;
    HI_U8  *pu8AadVir = HI_NULL;
    HI_U32 u32Val;
    HI_U32 u32Offset = 0;
    SPACC_SYMC_CHN_S *pstChn = &s_stSymcChn[0];
    U_CHAN0_CIPHER_CTRL chn0_ctrl;
    HI_BOOL bSetLast;
    HI_U8 u8B[32];

    cipher_mmz_buf_t stSrcMmzBuf;
    cipher_mmz_buf_t stDestMmzBuf;
    cipher_mmz_buf_t stAadMmzBuf;

    /*mapping phy address of SRC*/
    stSrcMmzBuf.u32Size = pstCIData->u32DataLength;
    stSrcMmzBuf.u32StartPhyAddr = pstCIData->ScrPhyAddr;
    ret = cipher_mmz_map(&stSrcMmzBuf);
    if ( HI_FAILURE == ret)
    {
        HI_ERR_CIPHER("DRV SRC MMZ MAP ERROR!, addr = 0x%x!\n", pstCIData->ScrPhyAddr);
        return ret;
    }
    pu8SrcVir = stSrcMmzBuf.pu8StartVirAddr;
    stDestMmzBuf.u32Size = pstCIData->u32DataLength;

    /*mapping phy address of DST*/
    stDestMmzBuf.u32StartPhyAddr = pstCIData->DestPhyAddr;
    ret = cipher_mmz_map(&stDestMmzBuf);
    if ( HI_FAILURE == ret)
    {
        HI_ERR_CIPHER("DRV DEST MMZ MAP ERROR! addr = 0x%x!\n", pstCIData->DestPhyAddr);
        cipher_mmz_unmap(&stSrcMmzBuf);

        return ret;
    }
    pu8DestVir = stDestMmzBuf.pu8StartVirAddr;

    /*mapping phy address of A for CCM/GCM*/
    if ((pstChn->stCtrl.enWorkMode == HI_UNF_CIPHER_WORK_MODE_CCM)
        || (pstChn->stCtrl.enWorkMode == HI_UNF_CIPHER_WORK_MODE_GCM))
    {
        stAadMmzBuf.u32Size = pstChn->stCtrl.u32ALen;
        stAadMmzBuf.u32StartPhyAddr = pstChn->stCtrl.u32APhyAddr;
        ret = cipher_mmz_map(&stAadMmzBuf);
        if ( HI_FAILURE == ret)
        {
            cipher_mmz_unmap(&stSrcMmzBuf);
            cipher_mmz_unmap(&stDestMmzBuf);
            HI_ERR_CIPHER("DRV AD MMZ MAP ERROR!, addr = 0x%x!\n", pstChn->stCtrl.u32APhyAddr);
            return ret;
        }
        pu8AadVir = stAadMmzBuf.pu8StartVirAddr;
    }

    /*Decrypt or encrypt*/
    HAL_CIPHER_ReadReg(CHAN0_CIPHER_CTRL, &chn0_ctrl.u32);
    chn0_ctrl.bits.sym_ch0_decrypt = bIsDecrypt;
    HAL_CIPHER_WriteReg(CHAN0_CIPHER_CTRL, chn0_ctrl.u32);

    if(pstChn->stCtrl.enWorkMode == HI_UNF_CIPHER_WORK_MODE_CCM)
    {
        /*Format N and A*/
        cipher_memset_s(u8B, sizeof(u8B), 0, sizeof(u8B));
        ret = DRV_CIPHER_CCM_HeadFormat(pstChn, pstCIData->u32DataLength, u8B, u8B+16, &u32Offset);
        if (ret != HI_SUCCESS)
        {
            goto _exit;
        }

        /*Set last block size*/
        chn0_ctrl.bits.sym_ccm_gcm_last_block = (pstCIData->u32DataLength + 15) % 16;

        /*Set flag N*/
        chn0_ctrl.bits.sym_ch0_ccm_gcm_input_flag = 0x00; //N

        /*Compute B0, contains N*/
        bSetLast = (pstChn->stCtrl.u32ALen + pstCIData->u32DataLength == 0) ? HI_TRUE : HI_FALSE;
        DRV_CIPHER_CPUInput(u8B, HI_NULL, 16, 16, chn0_ctrl.u32, bSetLast);

        /*Don't update IV any more*/
        chn0_ctrl.bits.sym_ch0_ivin_sel = 0x00;

        /*Compute A*/
        u32Val = pstChn->stCtrl.u32ALen + u32Offset;
        if (u32Val > 16) /* A and a can't puts in one block*/
        {
            /*Set flag A*/
            chn0_ctrl.bits.sym_ch0_ccm_gcm_input_flag = 0x01; //A

            /*Fill head of A to B1 split joint 16 byets*/
            cipher_memcpy_s(u8B+16+u32Offset, sizeof(u8B) - 16 - u32Offset,
                pu8AadVir, 16 - u32Offset);

            /*Compute B1, contains the coding of a and head of A*/
            DRV_CIPHER_CPUInput(u8B+16, HI_NULL, 16, 16, chn0_ctrl.u32, HI_FALSE);

            /*Compute the left data of A*/
            bSetLast = (pstCIData->u32DataLength == 0) ? HI_TRUE : HI_FALSE;
            DRV_CIPHER_CPUInput(pu8AadVir+16-u32Offset,
                HI_NULL, pstChn->stCtrl.u32ALen-(16-u32Offset),
                16, chn0_ctrl.u32, bSetLast);
        }
        else if (u32Val > 0) /* A and a can puts in one block*/
        {
            /*Set flag A*/
            chn0_ctrl.bits.sym_ch0_ccm_gcm_input_flag = 0x01; //A
            /*Fill A to B1 split joint 16 byets*/
            cipher_memcpy_s(u8B+16+u32Offset, sizeof(u8B) - 16 - u32Offset, pu8AadVir, pstChn->stCtrl.u32ALen);

            /*Compute B1, contains the coding of a and A*/
            bSetLast = (pstCIData->u32DataLength == 0) ? HI_TRUE : HI_FALSE;
            DRV_CIPHER_CPUInput(u8B+16, HI_NULL, 16, 16, chn0_ctrl.u32, bSetLast);
        }

        /*Next, compute the P*/
        chn0_ctrl.bits.sym_ch0_ccm_gcm_input_flag = 0x02; //P
    }
    else if (pstChn->stCtrl.enWorkMode == HI_UNF_CIPHER_WORK_MODE_GCM)
    {
        /*Set last block size*/
        chn0_ctrl.bits.sym_ccm_gcm_last_block = (pstCIData->u32DataLength + 15) % 16;

        /*Compute A*/
        if (pstChn->stCtrl.u32ALen > 0)
        {
            /*Set flag A*/
            chn0_ctrl.bits.sym_ch0_ccm_gcm_input_flag = 0x00; //A

            /*Compute A*/
            bSetLast = (pstCIData->u32DataLength == 0) ? HI_TRUE : HI_FALSE;
            DRV_CIPHER_CPUInput(pu8AadVir, HI_NULL, pstChn->stCtrl.u32ALen,
                u32BlockSize, chn0_ctrl.u32, bSetLast);

            chn0_ctrl.bits.sym_ch0_ivin_sel = 0x00;
        }

        /*Don't update IV any more*/
        chn0_ctrl.bits.sym_ch0_ccm_gcm_input_flag = 0x01; //P
    }

    /*Compute P*/
    if (pstCIData->u32DataLength > 0)
    {
        if(HI_UNF_CIPHER_ALG_SM4 == pstChn->stCtrl.enAlg)
        {
            SM4_Enable();
        }

        DRV_CIPHER_CPUInput(pu8SrcVir, pu8DestVir, pstCIData->u32DataLength,
            u32BlockSize, chn0_ctrl.u32, HI_TRUE);

        if(HI_UNF_CIPHER_ALG_SM4 == pstChn->stCtrl.enAlg)
        {
            SM4_Disable();
        }

        /*Don't update IV any more*/
        chn0_ctrl.bits.sym_ch0_ivin_sel = 0x00;
    }

    /*Compute LEN(C) for GCM*/
    if (pstChn->stCtrl.enWorkMode == HI_UNF_CIPHER_WORK_MODE_GCM)
    {
        /*Set flag LEN(C)*/
        cipher_memset_s(u8B, sizeof(u8B), 0, sizeof(u8B));
        chn0_ctrl.bits.sym_ch0_ccm_gcm_input_flag = 0x02; //LEN

        /*Format LEN(C) = LEN(A) || LEN(P), coding in bits*/
        u8B[3] = (HI_U8)((pstChn->stCtrl.u32ALen >> 29)&0x07);
        u8B[4] = (HI_U8)((pstChn->stCtrl.u32ALen >> 21)&0xff);
        u8B[5] = (HI_U8)((pstChn->stCtrl.u32ALen >> 13)&0xff);
        u8B[6] = (HI_U8)((pstChn->stCtrl.u32ALen >> 5)&0xff);
        u8B[7] = (HI_U8)((pstChn->stCtrl.u32ALen << 3)&0xff);

        u8B[11] = (HI_U8)((pstCIData->u32DataLength >> 29)&0x07);
        u8B[12] = (HI_U8)((pstCIData->u32DataLength >> 21)&0xff);
        u8B[13] = (HI_U8)((pstCIData->u32DataLength >> 13)&0xff);
        u8B[14] = (HI_U8)((pstCIData->u32DataLength >> 5)&0xff);
        u8B[15] = (HI_U8)((pstCIData->u32DataLength << 3)&0xff);

        /*Compute LEN(C)*/
        DRV_CIPHER_CPUInput(u8B, HI_NULL, 16, 16, chn0_ctrl.u32, HI_FALSE);
    }
_exit:

    /*Unmap phy address*/
    cipher_mmz_unmap(&stSrcMmzBuf);
    cipher_mmz_unmap(&stDestMmzBuf);
    if ((pstChn->stCtrl.enWorkMode == HI_UNF_CIPHER_WORK_MODE_CCM) || (pstChn->stCtrl.enWorkMode == HI_UNF_CIPHER_WORK_MODE_GCM))
    {
        cipher_mmz_unmap(&stAadMmzBuf);
    }

    return HI_SUCCESS;

}

static HI_S32 DRV_CIPHER_CCM_NA(SPACC_SYMC_CHN_S *pstChn, HI_U32 u32EncLen)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U8 *pbuf;
    HI_U32 u32Index;
    HI_U32 count = 0, alen = 0;
    HI_U32 u32Flag = 0;

    pbuf = pstChn->pu8PadVirAddr;
    u32Index = 0;
    cipher_memset_s(pbuf, SPACC_PAD_BUF_SIZE, 0, 32);

    /*Format B0 and head of B1*/
    DRV_CIPHER_CCM_HeadFormat(pstChn, u32EncLen, pbuf, pbuf+16, &alen);
//  HI_PRINT_HEX("B0", pbuf, 16);

    /*B0 contains the N, set flag N, for N, A, P, must set the first and last flag.*/
    u32Flag = SPACC_CTRL_SYMC_IN_CCM_N | SPACC_CTRL_SYMC_IN_LAST | SPACC_CTRL_SYMC_IN_FIRST;
    if ((pstChn->stCtrl.u32ALen == 0) && (u32EncLen == 0))
    {
        u32Flag |= SPACC_CTRL_SYMC_CCM_LAST;
    }
    ret = spacc_symc_addbuf(pstChn->u32HardNum, pstChn->u32PadPhyAddr, 16, SPACC_BUF_TYPE_SYMC_IN, u32Flag);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("spacc add N buf failed, ret = 0x%x.", ret);
        return HI_FAILURE;
    }
    u32Index += 16;

    /* a > 0, add the phy of A into node list*/
    if (alen)
    {
//      HI_PRINT_HEX("B1", pbuf +16, alen);

      /* 1st. add the phy of B1 into node list, which contains the coding of a*/
        ret = spacc_symc_addbuf(pstChn->u32HardNum, pstChn->u32PadPhyAddr + 16,
            alen, SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_IN_CCM_A);
        if(HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("spacc add A LEN buf failed, ret = 0x%x.", ret);
            return HI_FAILURE;
        }
        u32Index += alen;

        /* 2nd. add the phy of A into node list*/
        ret = spacc_symc_addbuf(pstChn->u32HardNum, pstChn->stCtrl.u32APhyAddr, pstChn->stCtrl.u32ALen,
            SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_IN_CCM_A);
        if(HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("spacc add A buf failed, ret = 0x%x.", ret);
            return HI_FAILURE;
        }
    }

    /*if alen + Alen do not aligned with 16, padding 0 to the tail*/
    count = (pstChn->stCtrl.u32ALen + alen) % AES_BLOCK_SIZE;
    if(count != 0)
    {
        /*Compute the padding length*/
        count = AES_BLOCK_SIZE - count;

        /*Set zero*/
        cipher_memset_s(&pbuf[u32Index], SPACC_PAD_BUF_SIZE - u32Index, 0, 16);

        /* add the padding phy of A into node list*/
        ret = spacc_symc_addbuf(pstChn->u32HardNum, pstChn->u32PadPhyAddr + u32Index,
            count, SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_IN_CCM_A);
        if(HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("spacc add A PAD buf failed, ret = 0x%x.", ret);
            return HI_FAILURE;
        }
        u32Index += count;
    }

    u32Flag = SPACC_CTRL_SYMC_IN_LAST;
    if (u32EncLen == 0)
    {
        /*if do not contains the P, set CCM last flag signal to hardware*/
        u32Flag |= SPACC_CTRL_SYMC_CCM_LAST;
    }
    spacc_symc_addctrl(pstChn->u32HardNum, SPACC_BUF_TYPE_SYMC_IN, u32Flag);

    return HI_SUCCESS;

}

static HI_S32 DRV_CIPHER_GCM_A(SPACC_SYMC_CHN_S *pstChn)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U8 *pbuf;
    HI_U32 count = 0;
    HI_U32 u32Index = 0;

    pbuf = pstChn->pu8PadVirAddr;
    if (pstChn->stCtrl.u32ALen)
    {
        /*Add phy of A into node list*/
        ret = spacc_symc_addbuf(pstChn->u32HardNum, pstChn->stCtrl.u32APhyAddr, pstChn->stCtrl.u32ALen,
            SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_IN_GCM_A);
        if(HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("spacc add A buf failed, ret = 0x%x.", ret);
            return HI_FAILURE;
        }

        /*if Alen do not aligned with 16, padding 0 to the tail*/
        count = pstChn->stCtrl.u32ALen % AES_BLOCK_SIZE;
        if(count != 0)
        {
            /*Compute the padding length*/
            count = AES_BLOCK_SIZE - count;

            /*Set zero*/
            cipher_memset_s(&pbuf[u32Index], SPACC_PAD_BUF_SIZE - u32Index, 0, 16);

            /* add the padding phy of A into node list*/
            ret = spacc_symc_addbuf(pstChn->u32HardNum,
                pstChn->u32PadPhyAddr + u32Index, count,
                SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_IN_GCM_A);
            if(HI_SUCCESS != ret)
            {
                HI_ERR_CIPHER("spacc add A PAD buf failed, ret = 0x%x.", ret);
                return HI_FAILURE;
            }
            u32Index+=count;
        }

        /* Set A last flag*/
        spacc_symc_addctrl(pstChn->u32HardNum, SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_IN_LAST);
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_CIPHER_GCM_LEN(SPACC_SYMC_CHN_S *pstChn, HI_U32 u32EncLen)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U8 *pbuf;
    HI_U32 u32Index = 32;

    /* Format len(C), 16 byets, coding in bits.
     * Byet0~7:  bits number of Add
     * Byet8~15: bits number of P
     */

    pbuf = pstChn->pu8PadVirAddr;

    pbuf[u32Index+0]  = 0x00;
    pbuf[u32Index+1]  = 0x00;
    pbuf[u32Index+2]  = 0x00;
    pbuf[u32Index+3] = (HI_U8)((pstChn->stCtrl.u32ALen >> 29)&0x07);
    pbuf[u32Index+4] = (HI_U8)((pstChn->stCtrl.u32ALen >> 21)&0xff);
    pbuf[u32Index+5] = (HI_U8)((pstChn->stCtrl.u32ALen >> 13)&0xff);
    pbuf[u32Index+6] = (HI_U8)((pstChn->stCtrl.u32ALen >> 5)&0xff);
    pbuf[u32Index+7] = (HI_U8)((pstChn->stCtrl.u32ALen << 3)&0xff);

    pbuf[u32Index+8]  = 0x00;
    pbuf[u32Index+9]  = 0x00;
    pbuf[u32Index+10] = 0x00;
    pbuf[u32Index+11] = (HI_U8)((u32EncLen >> 29)&0x07);
    pbuf[u32Index+12] = (HI_U8)((u32EncLen >> 21)&0xff);
    pbuf[u32Index+13] = (HI_U8)((u32EncLen >> 13)&0xff);
    pbuf[u32Index+14] = (HI_U8)((u32EncLen >> 5)&0xff);
    pbuf[u32Index+15] = (HI_U8)((u32EncLen << 3)&0xff);

    /*Add to nodes list*/
    ret = spacc_symc_addbuf(pstChn->u32HardNum,
        pstChn->u32PadPhyAddr + u32Index, 16, SPACC_BUF_TYPE_SYMC_IN,
        SPACC_CTRL_SYMC_IN_GCM_LEN | SPACC_CTRL_SYMC_IN_LAST);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("spacc add P buf failed, ret = 0x%x.", ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_CIPHER_Encrypt(CIPHER_DATA_S *pstCIData, HI_BOOL bIsDecrypt)
{
    HI_S32 ret = HI_SUCCESS;
    SPACC_SYMC_CHN_S *pstChn;
    HI_U32 softChnId = 0;

    if ( HI_NULL == pstCIData || pstCIData->CIHandle == 0)
    {
        HI_ERR_CIPHER("Invalid params!\n");
        return HI_FAILURE;
    }
    softChnId = HI_HANDLE_GET_CHNID(pstCIData->CIHandle);
    SPACC_CheckHandle(softChnId);
    pstChn = &s_stSymcChn[softChnId];

    if (softChnId != 0)
    {
        if (pstChn->stCtrl.enWorkMode == HI_UNF_CIPHER_WORK_MODE_CCM)
        {
            /*format N and A, add to node list*/
            ret = DRV_CIPHER_CCM_NA(pstChn, pstCIData->u32DataLength);
            if(HI_SUCCESS != ret)
            {
                return ret;
            }

            /* Add the phy of P into node list*/
            if (pstCIData->u32DataLength > 0)
            {
                /*Add in buffer*/
                ret = spacc_symc_addbuf(pstChn->u32HardNum, pstCIData->ScrPhyAddr, pstCIData->u32DataLength,
                    SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_IN_CCM_P | SPACC_CTRL_SYMC_IN_LAST);
                if(HI_SUCCESS != ret)
                {
                    HI_ERR_CIPHER("spacc add P buf failed, ret = 0x%x.", ret);
                    return HI_FAILURE;
                }

                /*Add out buffer*/
                ret = spacc_symc_addbuf(pstChn->u32HardNum, pstCIData->DestPhyAddr, pstCIData->u32DataLength,
                    SPACC_BUF_TYPE_SYMC_OUT, SPACC_CTRL_SYMC_OUT_LAST);
                if(HI_SUCCESS != ret)
                {
                    HI_ERR_CIPHER("spacc add P buf failed, ret = 0x%x.", ret);
                    return HI_FAILURE;
                }
            }
            else
            {
                /* If P is null, must add a empty node into node list, limit to hardware devising*/
                ret = spacc_symc_addbuf(pstChn->u32HardNum, 0x00, 0x00, SPACC_BUF_TYPE_SYMC_OUT,
                    SPACC_CTRL_SYMC_OUT_LAST);
                if(HI_SUCCESS != ret)
                {
                    HI_ERR_CIPHER("spacc add P buf failed, ret = 0x%x.", ret);
                    return HI_FAILURE;
                }
            }

            /*Set CCM last flag*/
            spacc_symc_addctrl(pstChn->u32HardNum, SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_CCM_LAST);

        }
        else if (pstChn->stCtrl.enWorkMode == HI_UNF_CIPHER_WORK_MODE_GCM)
        {
            /*format N, add to node list*/
            ret = DRV_CIPHER_GCM_A(pstChn);
            if(HI_SUCCESS != ret)
            {
                return ret;
            }

            /* Add the phy of P into node list*/
            if (pstCIData->u32DataLength > 0)
            {
                /*Add in buffer*/
                ret = spacc_symc_addbuf(pstChn->u32HardNum, pstCIData->ScrPhyAddr,
                      pstCIData->u32DataLength, SPACC_BUF_TYPE_SYMC_IN,
                      SPACC_CTRL_SYMC_IN_GCM_P | SPACC_CTRL_SYMC_IN_LAST);
                if(HI_SUCCESS != ret)
                {
                    HI_ERR_CIPHER("spacc add P buf failed, ret = 0x%x.", ret);
                    return HI_FAILURE;
                }

                /*Add out buffer*/
                ret = spacc_symc_addbuf(pstChn->u32HardNum, pstCIData->DestPhyAddr,
                    pstCIData->u32DataLength, SPACC_BUF_TYPE_SYMC_OUT, SPACC_CTRL_NONE);
                if(HI_SUCCESS != ret)
                {
                    HI_ERR_CIPHER("spacc add P buf failed, ret = 0x%x.", ret);
                    return HI_FAILURE;
                }
            }

            /*At the and of GCM, must add a empty node to nodes list, limit to hardware devising*/
            ret = spacc_symc_addbuf(pstChn->u32HardNum, 0x00, 0x00,
                SPACC_BUF_TYPE_SYMC_OUT, SPACC_CTRL_SYMC_OUT_LAST);
            if(HI_SUCCESS != ret)
            {
                HI_ERR_CIPHER("spacc add P buf failed, ret = 0x%x.", ret);
                return HI_FAILURE;
            }

            /*Format the length fields of C and add to nodes list*/
            ret = DRV_CIPHER_GCM_LEN(pstChn, pstCIData->u32DataLength);
            if(HI_SUCCESS != ret)
            {
                return ret;
            }
        }
        else //ECB/CBC/CBF/OFB/CTR
        {
            /*except ccm/gcm, the data length must not zero*/
            if (pstCIData->u32DataLength == 0)
            {
                HI_ERR_CIPHER("Invalid data len 0x%x.", pstCIData->u32DataLength);
                return HI_ERR_CIPHER_INVALID_PARA;
            }

            /* The length of data depend on alg and mode, which limit to hardware
             * for ecb/cbc/ofb/cfb, the data length must aligned with block size.
             * for ctr/ccm/gcm, support any data length.
             */
            if (((pstChn->stCtrl.enWorkMode == HI_UNF_CIPHER_WORK_MODE_ECB)
                || (pstChn->stCtrl.enWorkMode == HI_UNF_CIPHER_WORK_MODE_CBC)
                || (pstChn->stCtrl.enWorkMode == HI_UNF_CIPHER_WORK_MODE_OFB)
                || (pstChn->stCtrl.enWorkMode == HI_UNF_CIPHER_WORK_MODE_CFB))
                && (pstChn->stCtrl.enAlg != HI_UNF_CIPHER_ALG_DMA))
            {
                if (pstCIData->u32DataLength % pstChn->u32BlockSize != 0)
                {
                    HI_ERR_CIPHER("Invalid data len 0x%x.", pstCIData->u32DataLength);
                    return HI_ERR_CIPHER_INVALID_PARA;
                }
            }

            /*Add in buffer*/
            ret  = spacc_symc_addbuf(pstChn->u32HardNum, pstCIData->ScrPhyAddr,
                pstCIData->u32DataLength, SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_IN_LAST);

            /*Add out buffer*/
            ret |= spacc_symc_addbuf(pstChn->u32HardNum, pstCIData->DestPhyAddr,
                pstCIData->u32DataLength, SPACC_BUF_TYPE_SYMC_OUT, SPACC_CTRL_SYMC_OUT_LAST);

        }
        if(HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("spacc add out buf failed, ret = 0x%x.", ret);
            return HI_FAILURE;
        }

        pstChn->bSymcDone = HI_FALSE;

        /*Start working*/
        spacc_symc_start(pstChn->u32HardNum, bIsDecrypt, pstChn->stCtrl.stChangeFlags.bit1IV);

        if (pstChn->stCtrl.stChangeFlags.bit1IV == CIPHER_IV_CHANGE_ONE_PKG)
        {
            /*only update IV for first pkg*/
            pstChn->stCtrl.stChangeFlags.bit1IV = 0;
        }

        /* Waiting hardware computing finished*/
        ret = DRV_CIPHER_SymcWaitDone(pstChn, SPACC_TIME_OUT);
        if(HI_SUCCESS != ret)
        {
            return HI_FAILURE;
        }

    }
    else
    {
        /*Chn 0, CPU mode*/
        ret = DRV_CIPHER_CpuEncPhy(pstCIData, pstChn->u32BlockSize, bIsDecrypt);
        if(HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("Cpu Encrypt err\n");
            return HI_FAILURE;
        }
    }

    flush_cache();

    return ret;

}

HI_S32 HI_DRV_CIPHER_GetTag(CIPHER_TAG_S *pstTag)
{
    HI_U32 softChnId = 0;
    SPACC_SYMC_CHN_S *pstChn;
    HI_U32 i;

    if ( HI_NULL == pstTag)
    {
        HI_ERR_CIPHER("Invalid params!\n");
        return HI_FAILURE;
    }
    softChnId = HI_HANDLE_GET_CHNID(pstTag->CIHandle);
    SPACC_CheckHandle(softChnId);
    pstChn = &s_stSymcChn[softChnId];

    if ((pstChn->stCtrl.enWorkMode != HI_UNF_CIPHER_WORK_MODE_CCM)
        && (pstChn->stCtrl.enWorkMode != HI_UNF_CIPHER_WORK_MODE_GCM))
    {
        HI_ERR_CIPHER("Invalid mode %d!\n", pstChn->stCtrl.enWorkMode);
        return HI_FAILURE;
    }
    pstTag->u32TagLen = pstChn->stCtrl.u32TagLen;

    /* Read tag for CCM/GCM*/
    if (softChnId == 0)
    {
        for(i=0; i<4; i++)
        {
            HAL_CIPHER_ReadReg(CHAN0_CCM_GCM_TAG + i*4, &pstTag->u32Tag[i]);
        }
    }
    else
    {
        spacc_symc_gettag(pstChn->u32HardNum, (HI_U8*)pstTag->u32Tag);
    }

    return HI_SUCCESS;
}

HI_S32 HI_DRV_CIPHER_Encrypt(CIPHER_DATA_S *pstCIData)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 softChnId;

    if(cipher_mutex_lock(&g_SymcMutex))
    {
        HI_ERR_CIPHER("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    softChnId = HI_HANDLE_GET_CHNID(pstCIData->CIHandle);
    SPACC_CheckHandle(softChnId);

    ret = DRV_CIPHER_Encrypt(pstCIData, HI_FALSE);
    cipher_mutex_unlock(&g_SymcMutex);

    return ret;
}

HI_S32 HI_DRV_CIPHER_Decrypt(CIPHER_DATA_S *pstCIData)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 softChnId;

    if(cipher_mutex_lock(&g_SymcMutex))
    {
        HI_ERR_CIPHER("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    softChnId = HI_HANDLE_GET_CHNID(pstCIData->CIHandle);
    SPACC_CheckHandle(softChnId);

    ret = DRV_CIPHER_Encrypt(pstCIData, HI_TRUE);

    cipher_mutex_unlock(&g_SymcMutex);

    return ret;
}

/*Get odd/even key flag and P flag*/
static HI_U32 DRV_CIPHER_GetPayloadCtrl(HI_BOOL bOddKey, HI_UNF_CIPHER_WORK_MODE_E enMode)
{
    HI_U32 u32Ctrl = 0;

    u32Ctrl = bOddKey ? SPACC_CTRL_SYMC_ODD_KEY : SPACC_CTRL_SYMC_EVEN_KEY;

    if (enMode == HI_UNF_CIPHER_WORK_MODE_CCM)
    {
        u32Ctrl |= SPACC_CTRL_SYMC_IN_CCM_P;
    }
    else if (enMode == HI_UNF_CIPHER_WORK_MODE_GCM)
    {
        u32Ctrl |= SPACC_CTRL_SYMC_IN_GCM_P;
    }

    return u32Ctrl;
}

static HI_S32 DRV_CIPHER_AddNodes(SPACC_SYMC_CHN_S *pstChn, HI_U32 u32IntLevel)
{
    HI_U32 i = 0;
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32Nodes;
    HI_U32 u32Cur;
    HI_U32 u32Ctrl;
    HI_U32 u32Total;

//  printk("chn %d, cur %d, num %d\n", pstChn->u32HardNum, pstChn->u32NodeCur, pstChn->u32NodeNum);
    if(pstChn->u32NodeCur < pstChn->u32NodeNum)
    {
        u32Nodes = MIN(u32IntLevel, pstChn->u32NodeNum - pstChn->u32NodeCur);
//      printk("cur %d, num %d, now node: %d\n", pstChn->u32NodeCur, pstChn->u32NodeNum, u32Nodes);
        u32Cur = pstChn->u32NodeCur;
        u32Total = 0;
        for (i = 0; i < u32Nodes; i++)
        {
            /*Get odd/even key flag and P flag*/
            u32Ctrl = DRV_CIPHER_GetPayloadCtrl(pstChn->pstNodeList[u32Cur].bOddKey, pstChn->stCtrl.enWorkMode);

            /*Add P in*/
            ret = spacc_symc_addbuf(pstChn->u32HardNum, pstChn->pstNodeList[u32Cur].u32SrcPhyAddr,
                pstChn->pstNodeList[u32Cur].u32ByteLength, SPACC_BUF_TYPE_SYMC_IN, u32Ctrl);
            if(HI_SUCCESS != ret)
            {
                HI_ERR_CIPHER("spacc add in buf failed, ret = 0x%x.", ret);
                return HI_FAILURE;
            }

            /*Add P out*/
            ret = spacc_symc_addbuf(pstChn->u32HardNum, pstChn->pstNodeList[u32Cur].u32DestPhyAddr,
                pstChn->pstNodeList[u32Cur].u32ByteLength, SPACC_BUF_TYPE_SYMC_OUT, SPACC_CTRL_NONE);
            if(HI_SUCCESS != ret)
            {
                HI_ERR_CIPHER("spacc add in buf failed, ret = 0x%x.", ret);
                return HI_FAILURE;
            }
            u32Total += pstChn->pstNodeList[u32Cur].u32ByteLength;
            pstChn->u32NodeCur++;
            u32Cur++;
        }
 //     printk("total 0x%x, blockSize 0x%x\n", u32Total, pstChn->u32BlockSize);

       /* For each compute, the total length of valid nodes list
        * must aligned with block size, otherwise can't recv interrupt,
        * which limit to hardware devising.
        */

        /* Compute the tail length*/
        u32Total %= pstChn->u32BlockSize;
        if (u32Total > 0)
        {
            u32Total = pstChn->u32BlockSize - u32Total;
        }

//      printk("cur %d, num %d\n", pstChn->u32NodeCur, pstChn->u32NodeNum);

        /*if the total length don't aligned with block size, split joint the follow nodes*/
        while((u32Total > 0) && (pstChn->u32NodeCur < pstChn->u32NodeNum))
        {
            /*The next node large than tail size, just split it to 2 nodes */
            if (pstChn->pstNodeList[u32Cur].u32ByteLength > u32Total)
            {
                /*Add P in*/
                u32Ctrl = DRV_CIPHER_GetPayloadCtrl(pstChn->pstNodeList[u32Cur].bOddKey, pstChn->stCtrl.enWorkMode);
                ret = spacc_symc_addbuf(pstChn->u32HardNum, pstChn->pstNodeList[u32Cur].u32SrcPhyAddr,
                    u32Total, SPACC_BUF_TYPE_SYMC_IN, u32Ctrl);
                if(HI_SUCCESS != ret)
                {
                    HI_ERR_CIPHER("spacc add in buf failed, ret = 0x%x.", ret);
                    return HI_FAILURE;
                }

                /*Add P out*/
                ret = spacc_symc_addbuf(pstChn->u32HardNum, pstChn->pstNodeList[u32Cur].u32DestPhyAddr,
                    u32Total, SPACC_BUF_TYPE_SYMC_OUT, SPACC_CTRL_NONE);
                if(HI_SUCCESS != ret)
                {
                    HI_ERR_CIPHER("spacc add in buf failed, ret = 0x%x.", ret);
                    return HI_FAILURE;
                }

                /*Let next node skip the tail size*/
                pstChn->pstNodeList[u32Cur].u32SrcPhyAddr += u32Total;
                pstChn->pstNodeList[u32Cur].u32DestPhyAddr+= u32Total;
                pstChn->pstNodeList[u32Cur].u32ByteLength -= u32Total;
                u32Nodes++;
                u32Total = 0;
            }
            else
            {
                /*The next node less than tail size, add it to nodes list */

                /*Add P in*/
                u32Ctrl = DRV_CIPHER_GetPayloadCtrl(pstChn->pstNodeList[u32Cur].bOddKey, pstChn->stCtrl.enWorkMode);
                ret = spacc_symc_addbuf(pstChn->u32HardNum, pstChn->pstNodeList[u32Cur].u32SrcPhyAddr,
                    pstChn->pstNodeList[u32Cur].u32ByteLength, SPACC_BUF_TYPE_SYMC_IN, u32Ctrl);
                if(HI_SUCCESS != ret)
                {
                    HI_ERR_CIPHER("spacc add in buf failed, ret = 0x%x.", ret);
                    return HI_FAILURE;
                }

                /*Add P out*/
                ret = spacc_symc_addbuf(pstChn->u32HardNum, pstChn->pstNodeList[u32Cur].u32DestPhyAddr,
                    pstChn->pstNodeList[u32Cur].u32ByteLength, SPACC_BUF_TYPE_SYMC_OUT, SPACC_CTRL_NONE);
                if(HI_SUCCESS != ret)
                {
                    HI_ERR_CIPHER("spacc add in buf failed, ret = 0x%x.", ret);
                    return HI_FAILURE;
                }

                /*re-compute the tail size*/
                u32Total -= pstChn->pstNodeList[u32Cur].u32ByteLength;

                /*Process next node*/
                u32Cur++;
                u32Nodes++;
                pstChn->u32NodeCur++;
            }
        }
//        printk("chn %d, cur %d, num %d\n", pstChn->u32HardNum, pstChn->u32NodeCur, pstChn->u32NodeNum);
    }

    /* Set last flag*/
    if (pstChn->u32NodeCur == pstChn->u32NodeNum)
    {
        /* Set CCM last flag*/
        if (pstChn->stCtrl.enWorkMode == HI_UNF_CIPHER_WORK_MODE_CCM)
        {
            spacc_symc_addctrl(pstChn->u32HardNum, SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_CCM_LAST);
        }
        else if (pstChn->stCtrl.enWorkMode == HI_UNF_CIPHER_WORK_MODE_GCM)
        {
            /* Set GCM last flag*/
            spacc_symc_addctrl(pstChn->u32HardNum, SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_IN_LAST);

            /*At the and of GCM, must add a empty P node to nodes list, limit to hardware devising*/
            ret = spacc_symc_addbuf(pstChn->u32HardNum, 0x00, 0x00,
                SPACC_BUF_TYPE_SYMC_OUT, SPACC_CTRL_SYMC_OUT_LAST);
            if(HI_SUCCESS != ret)
            {
                HI_ERR_CIPHER("spacc add P buf failed, ret = 0x%x.", ret);
                return HI_FAILURE;
            }

            /*After compute P, compute LEN(C) for GCM */
            ret = DRV_CIPHER_GCM_LEN(pstChn, pstChn->u32TotalLen);
            if(HI_SUCCESS != ret)
            {
                return ret;
            }
        }

        /* Set symc last flag*/
        spacc_symc_addctrl(pstChn->u32HardNum, SPACC_BUF_TYPE_SYMC_IN, SPACC_CTRL_SYMC_IN_LAST);
        spacc_symc_addctrl(pstChn->u32HardNum, SPACC_BUF_TYPE_SYMC_OUT, SPACC_CTRL_SYMC_OUT_LAST);
    }

    return HI_SUCCESS;
}

static HI_VOID DRV_CIPHER_Callback(HI_U32 ChnId)
{
    HI_S32 ret = HI_SUCCESS;
    SPACC_SYMC_CHN_S *pstChn;

    pstChn = &s_stSymcChn[ChnId];

    /*Compute the follow nodes*/
    if(pstChn->u32NodeCur < pstChn->u32NodeNum)
    {
        ret = DRV_CIPHER_AddNodes(pstChn, SYMC_INT_LEVEL);
        if (ret == HI_SUCCESS)
        {
            spacc_symc_restart(pstChn->u32HardNum, pstChn->stCtrl.stChangeFlags.bit1IV);
        }
    }
    else
    {
        /*All the nodes compute finished, wake up user*/
        pstChn->bSymcDone = HI_TRUE;
        HI_INFO_CIPHER("chn %d wake up\n", pstChn->u32HardNum);
        cipher_queue_wait_up(&pstChn->queue);
    }
}

static HI_S32 DRV_CIPHER_EncryptMulti(CIPHER_PKG_S *psPkg, HI_BOOL bIsDecrypt)
{
    HI_U32 softChnId = 0;
    HI_S32 ret = HI_SUCCESS;
    SPACC_SYMC_CHN_S *pstChn;
    HI_U32 u32Remainder = 0;
    HI_U32 i;

    if (psPkg == HI_NULL)
    {
        HI_ERR_CIPHER("Invalid psPkg.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (psPkg->u32PkgNum == 0 || psPkg->u32PkgNum > MAX_PKG_NUMBER)
    {
        HI_ERR_CIPHER("Error: you send 0 pkg, must >= 1.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    softChnId = HI_HANDLE_GET_CHNID(psPkg->CIHandle);
    SPACC_CheckHandle(softChnId);
    pstChn = &s_stSymcChn[softChnId];

    HI_INFO_CIPHER("u32PkgNum %d\n", psPkg->u32PkgNum);
    pstChn->pstNodeList = cipher_malloc(psPkg->u32PkgNum * sizeof(HI_UNF_CIPHER_DATA_S));
    if (pstChn->pstNodeList == HI_NULL)
    {
        HI_ERR_CIPHER("Malloc for pkg failed.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }
    /*copy node list from user space to kernel*/
    if (cipher_copy_from_user(pstChn->pstNodeList, psPkg->pu8Pkg,
            psPkg->u32PkgNum * sizeof(HI_UNF_CIPHER_DATA_S)))
    {
        HI_ERR_CIPHER("--copy data from user fail!\n");
        return HI_FAILURE;
    }

    /*Compute and check the nodes length*/
    pstChn->u32TotalLen = 0;
    for(i=0; i<psPkg->u32PkgNum; i++)
    {
        /* Used the odd key must accord with conditions as follows:*/
        if (pstChn->pstNodeList[i].bOddKey)
        {
             /* 1. Only support aes ecb/cbc/cfb/ofb/ctr */
            if ((pstChn->stCtrl.enAlg != HI_UNF_CIPHER_ALG_AES)
               || ((pstChn->stCtrl.enWorkMode != HI_UNF_CIPHER_WORK_MODE_ECB)
                  && (pstChn->stCtrl.enWorkMode != HI_UNF_CIPHER_WORK_MODE_CBC)
                  && (pstChn->stCtrl.enWorkMode != HI_UNF_CIPHER_WORK_MODE_CFB)
                  && (pstChn->stCtrl.enWorkMode != HI_UNF_CIPHER_WORK_MODE_OFB)
                  && (pstChn->stCtrl.enWorkMode != HI_UNF_CIPHER_WORK_MODE_CTR)))
            {
                 HI_ERR_CIPHER("Odd key only support aes ecb/cbc/cfb/ofb/ctr.");
                 return HI_FAILURE;
            }

            /* 2. Only support aes128 */
            if (pstChn->stCtrl.enKeyLen != HI_UNF_CIPHER_KEY_AES_128BIT)
            {
                 HI_ERR_CIPHER("Odd key only support aes128.");
                 return HI_FAILURE;
            }

            /* 3. each node length must be a multiple of 64*/
            if ((pstChn->pstNodeList[i].u32ByteLength % 64) != 0)
            {
                 HI_ERR_CIPHER("Odd key only supported when each node length is a multiple of 64.");
                 return HI_FAILURE;
            }
        }

        /* each node length can't be zero*/
        if(pstChn->pstNodeList[i].u32ByteLength == 0)
        {
            HI_ERR_CIPHER("PKG len must large than 0.\n");
            return HI_ERR_CIPHER_INVALID_PARA;
        }

        if((UNIX_MAX - pstChn->u32TotalLen) < pstChn->pstNodeList[i].u32ByteLength)
        {
            HI_ERR_CIPHER("PKG len error.\n");
            return HI_FAILURE;
        }
        pstChn->u32TotalLen += pstChn->pstNodeList[i].u32ByteLength;
    }

    /*Before compute P, compute N and A for CCM firstly*/
    if (pstChn->stCtrl.enWorkMode == HI_UNF_CIPHER_WORK_MODE_CCM)
    {
        /*Format N and A, add to node list*/
        ret = DRV_CIPHER_CCM_NA(pstChn, pstChn->u32TotalLen);
        if(HI_SUCCESS != ret)
        {
            return ret;
        }

        if (pstChn->u32TotalLen == 0)
        {
            /* If P is null, must add a empty node into node list, limit to hardware devising*/
            ret = spacc_symc_addbuf(pstChn->u32HardNum, 0x00, 0x00, SPACC_BUF_TYPE_SYMC_OUT,
                SPACC_CTRL_SYMC_OUT_LAST);
            if(HI_SUCCESS != ret)
            {
                HI_ERR_CIPHER("spacc add P buf failed, ret = 0x%x.", ret);
                return HI_FAILURE;
            }
        }
    }
    /*Before compute P, compute A for GCM firstly*/
    else if (pstChn->stCtrl.enWorkMode == HI_UNF_CIPHER_WORK_MODE_GCM)
    {
        ret = DRV_CIPHER_GCM_A(pstChn);
        if(HI_SUCCESS != ret)
        {
            return ret;
        }
    }
    else if((pstChn->stCtrl.enWorkMode == HI_UNF_CIPHER_WORK_MODE_ECB)
        || (pstChn->stCtrl.enWorkMode == HI_UNF_CIPHER_WORK_MODE_CBC)
        || (pstChn->stCtrl.enWorkMode == HI_UNF_CIPHER_WORK_MODE_CFB)
        || (pstChn->stCtrl.enWorkMode == HI_UNF_CIPHER_WORK_MODE_OFB))
    {
       /* The length of data depend on alg and mode, which limit to hardware
        * for ecb/cbc/ofb/cfb, the total data length must aligned with block size.
        * for ctr/ccm/gcm, support any data length.
        */
        if(pstChn->u32TotalLen % pstChn->u32BlockSize != 0)
        {
            HI_ERR_CIPHER("PKG len must align with 16.\n");
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }

    pstChn->u32NodeNum = psPkg->u32PkgNum;
    pstChn->u32NodeCur = 0;

    /* For one time compute, the max nodes is 127, but 126 for first time,
     * here we compute 100 nodes firstly,
     * Because under each compute, the total length of valid nodes list
     * must aligned with block size, otherwise can't recv interrupt.
     * if the total length don't aligned with block size, we must
     * split joint the follow nodes with current nodes to multiple block size.
     * so it follows that, the nodes num for this time compute may be larger than 100,
     * The worst is that we need add 15 nodes(each node only carry 1 bye data)
     * within this time, that is the SYMC_INT_LEVEL must less than 127 - 16 - 1= 110.
     */
    u32Remainder = MIN(psPkg->u32PkgNum, SYMC_INT_LEVEL);
    ret = DRV_CIPHER_AddNodes(pstChn, u32Remainder);
    if (ret == HI_SUCCESS)
    {
        pstChn->callback = DRV_CIPHER_Callback;
        pstChn->bSymcDone = HI_FALSE;
        spacc_symc_start(pstChn->u32HardNum, bIsDecrypt, pstChn->stCtrl.stChangeFlags.bit1IV);
    }

    return ret;
}

HI_S32 HI_DRV_CIPHER_EncryptMulti(CIPHER_PKG_S *psPkg)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 softChnId = 0;
    SPACC_SYMC_CHN_S *pstChn;

    if(cipher_mutex_lock(&g_SymcMutex))
    {
        HI_ERR_CIPHER("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    softChnId = HI_HANDLE_GET_CHNID(psPkg->CIHandle);
    SPACC_CheckHandle(softChnId);
    pstChn = &s_stSymcChn[softChnId];

    ret = DRV_CIPHER_EncryptMulti(psPkg, HI_FALSE);
    if (ret != HI_SUCCESS)
    {
        if (pstChn->pstNodeList)
        {
            cipher_free(pstChn->pstNodeList);
        }

        cipher_mutex_unlock(&g_SymcMutex);

        return ret;
    }

    ret = DRV_CIPHER_SymcWaitDone(pstChn, SPACC_TIME_OUT);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("spacc symc active failed, ret = 0x%x.", ret);
    }

    if (pstChn->pstNodeList)
    {
        cipher_free(pstChn->pstNodeList);
    }

    if (pstChn->stCtrl.stChangeFlags.bit1IV == CIPHER_IV_CHANGE_ONE_PKG)
    {
        spacc_symc_getiv(pstChn->u32HardNum, pstChn->stCtrl.u32IV, 16);
    }

    cipher_mutex_unlock(&g_SymcMutex);

    return ret;

}

HI_S32 HI_DRV_CIPHER_DecryptMulti(CIPHER_PKG_S *psPkg)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 softChnId = 0;
    SPACC_SYMC_CHN_S *pstChn;

    if(cipher_mutex_lock(&g_SymcMutex))
    {
        HI_ERR_CIPHER("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    softChnId = HI_HANDLE_GET_CHNID(psPkg->CIHandle);
    SPACC_CheckHandle(softChnId);
    pstChn = &s_stSymcChn[softChnId];

    ret = DRV_CIPHER_EncryptMulti(psPkg, HI_TRUE);
    if (ret != HI_SUCCESS)
    {
        if (pstChn->pstNodeList)
        {
            cipher_free(pstChn->pstNodeList);
        }

        cipher_mutex_unlock(&g_SymcMutex);

        return ret;
    }

    ret = DRV_CIPHER_SymcWaitDone(pstChn, SPACC_TIME_OUT);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("spacc symc active failed, ret = 0x%x.", ret);
    }

    if (pstChn->pstNodeList)
    {
        cipher_free(pstChn->pstNodeList);
    }

    if (pstChn->stCtrl.stChangeFlags.bit1IV == CIPHER_IV_CHANGE_ONE_PKG)
    {
        spacc_symc_getiv(pstChn->u32HardNum, pstChn->stCtrl.u32IV, 16);
    }

    cipher_mutex_unlock(&g_SymcMutex);

    return ret;
}

static HI_S32 DRV_DIGEST_Config(CIPHER_HASH_DATA_S *pCipherHashData, SPACC_CTRL_EN *penCtrl)
{
    HI_S32 ret = HI_SUCCESS;
    DIGEST_ALG_EN digest_alg;
    DIGEST_MODE_EN digest_mode;

    *penCtrl = SPACC_CTRL_NONE;

    switch(pCipherHashData->enShaType)
    {
    case HI_UNF_CIPHER_HASH_TYPE_SHA1:
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1:
        digest_alg = DIGEST_ALG_SHA1;
        digest_mode = DIGEST_MODE_HASH;
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA224:
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA224:
        digest_alg = DIGEST_ALG_SHA224;
        digest_mode = DIGEST_MODE_HASH;
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA256:
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256:
        digest_alg = DIGEST_ALG_SHA256;
        digest_mode = DIGEST_MODE_HASH;
        break;
     case HI_UNF_CIPHER_HASH_TYPE_SHA384:
     case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA384:
        digest_alg = DIGEST_ALG_SHA384;
        digest_mode = DIGEST_MODE_HASH;
        break;
     case HI_UNF_CIPHER_HASH_TYPE_SHA512:
     case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA512:
        digest_alg = DIGEST_ALG_SHA512;
        digest_mode = DIGEST_MODE_HASH;
        break;
     case HI_UNF_CIPHER_HASH_TYPE_SM3:
        digest_alg = DIGEST_ALG_SM3;
        digest_mode = DIGEST_MODE_HASH;
        break;
     default:
        HI_ERR_CIPHER("Invalid hash type: 0x%x\n", pCipherHashData->enShaType);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    ret = spacc_digest_config(pCipherHashData->u32HardChn, digest_alg, digest_mode, HI_FALSE);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("spacc set digest mode failed, chn %d, alg %d, mode %d.\n",
            pCipherHashData->u32HardChn, digest_alg, digest_mode);
        return HI_FAILURE;
    }

    *penCtrl |= SPACC_CTRL_HASH_IN_FIRST;
    *penCtrl |= SPACC_CTRL_HASH_IN_LAST;

    return HI_SUCCESS;

}

HI_S32 HI_DRV_CIPHER_CalcHashInit(CIPHER_HASH_DATA_S *pCipherHashData)
{
    return HI_SUCCESS;
}

HI_S32 HI_DRV_CIPHER_CalcHashUpdate(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 ret = HI_SUCCESS;
    SPACC_CTRL_EN enCtrl;
    HI_U32 u32HardChn;
    SPACC_DIGEST_CHN_S *pstChn;

    if(cipher_mutex_lock(&g_SymcMutex))
    {
        HI_ERR_CIPHER("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    u32HardChn = pCipherHashData->u32HardChn;
    pstChn = &s_stDigestChn[pCipherHashData->u32HardChn];

    /*configure hash register*/
    ret = DRV_DIGEST_Config(pCipherHashData, &enCtrl);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("cipher config failed, ret = 0x%x.\n", ret);
        cipher_mutex_unlock(&g_SymcMutex);
        return HI_FAILURE;
    }

    /*Add the phy of data to nodes list*/
    ret = spacc_digest_addbuf(u32HardChn, pCipherHashData->u32DataPhy,
        pCipherHashData->u32DataLen, enCtrl);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("spacc add in buf failed, ret = 0x%x.\n", ret);
        cipher_mutex_unlock(&g_SymcMutex);
        return HI_FAILURE;
    }

    pstChn->bDigestDone = HI_FALSE;

    /*Start working*/
    ret = spacc_digest_start(u32HardChn, enCtrl, pCipherHashData->u32ShaVal);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("spacc add in buf failed, ret = 0x%x.\n", ret);
        cipher_mutex_unlock(&g_SymcMutex);
        return HI_FAILURE;
    }

    /* Waiting hardware computing finished*/
    ret = DRV_CIPHER_DigestWaitDone(pstChn);
    if(HI_SUCCESS == ret)
    {
        /*Read hash result*/
        spacc_digest_get(pCipherHashData->u32HardChn, pCipherHashData->u32ShaVal);
    }

    cipher_mutex_unlock(&g_SymcMutex);

    return ret;
}

HI_S32 HI_DRV_CIPHER_CalcHashFinal(CIPHER_HASH_DATA_S *pCipherHashData)
{
    return HI_DRV_CIPHER_CalcHashUpdate(pCipherHashData);
}

HI_S32 HI_DRV_CIPHER_GetHandleConfigEx(CIPHER_CONFIG_CTRL_EX *pstCipherConfig)
{
    SPACC_SYMC_CHN_S *pstChn;
    HI_U32 softChnId;

    if ( pstCipherConfig == 0)
    {
        HI_ERR_CIPHER("Invalid params!\n");
        return HI_FAILURE;
    }

    softChnId = HI_HANDLE_GET_CHNID(pstCipherConfig->CIHandle);
    SPACC_CheckHandle(softChnId);
    pstChn = &s_stSymcChn[softChnId];

    cipher_memcpy_s(pstCipherConfig, sizeof(CIPHER_CONFIG_CTRL_EX), &pstChn->stCtrl, sizeof(pstChn->stCtrl));

    return HI_SUCCESS;
}

HI_S32 HI_DRV_CIPHER_GetIV(HI_U32 ChnId, HI_U32 u32IV[4])
{
    return spacc_symc_getiv(ChnId, u32IV, 16);
}

HI_S32 HI_DRV_CIPHER_CencDecrypt(CIPHER_CENC_DECRYPT_S *pstCencDecrypt)
{
#ifdef HI_SMMU_SUPPORT
    HI_S32 ret;

    if(cipher_mutex_lock(&g_SymcMutex))
    {
        HI_ERR_CIPHER("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    ret = Cipher_CencDecrypt(pstCencDecrypt);

    cipher_mutex_unlock(&g_SymcMutex);

    return ret;
#else
    HI_ERR_CIPHER("CENC Decrypt only support SMMU Addr!!!");
    return HI_FAILURE;
#endif
}

HI_S32 DRV_CIPHER_Release(struct inode * inode, struct file * file)
{
    HI_U32 i;

    for (i = 0; i < SAPCC_MAX_CHN; i++)
    {
        if (s_stSymcChn[i].pWichFile == file)
        {
            s_stSymcChn[i].bIsOpen = HI_FALSE;
            s_stSymcChn[i].pWichFile = NULL;
        }
    }
    return 0;
}

HI_S32 DRV_CIPHER_Open(struct inode * inode, struct file * file)
{
    return HI_SUCCESS;
}

#ifdef HDCP_ENABLE
HI_S32 HI_DRV_CIPHER_CPU_Encrypt(HI_U8 *pu8Input,
                              HI_U32 u32InputLen,
                              HI_U8 *pu8Output,
                              HI_DRV_CIPHER_HDCP_KEY_MODE_E enHdcpEnMode,
                              HI_DRV_CIPHER_HDCP_ROOT_KEY_TYPE_E enRootKeyType,
                              HI_DRV_HDCPKEY_TYPE_E enHDCPKeyType,
                              CIPHER_Config_CTRL *pConfig,
                              HI_BOOL bIsDecrypt)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32KeyBlock = 0;
    HI_U32 i = 0, j;
    HI_U32 u32Mode = 0;
    HI_U32 u32Val, u32Time = 0;
    HI_U32 u32BlockSize = 8;
    U_CHAN0_CIPHER_CTRL chn0_ctrl;

    if ( NULL == pu8Input )
    {
        HI_ERR_CIPHER("Invalid param , null pointer input!\n");
        return HI_FAILURE;
    }

    if ((pConfig->CIpstCtrl.enAlg == HI_UNF_CIPHER_ALG_AES)
        || (pConfig->CIpstCtrl.enAlg == HI_UNF_CIPHER_ALG_SM1)
        || (pConfig->CIpstCtrl.enAlg == HI_UNF_CIPHER_ALG_SM4))
    {
        u32BlockSize = 16;
    }

    if (enHdcpEnMode == CIPHER_HDCP_MODE_HDCP_KEY)
    {
        u32Mode |= 0x01; //hdcp_mode_en
        u32Mode |= enRootKeyType << 1;
        u32Mode |= enHDCPKeyType << 8; //hdcp_wr_sel
    }

    HAL_CIPHER_WriteReg(HDCP_MODE_CTRL, u32Mode);
    HAL_CIPHER_WriteReg(ODD_EVEN_KEY_SEL, 0x00);

    cipher_msleep(1000);

    chn0_ctrl.u32 = 0x00;
    chn0_ctrl.bits.sym_ch0_alg_mode = pConfig->CIpstCtrl.enWorkMode;
    chn0_ctrl.bits.sym_ch0_alg_sel = pConfig->CIpstCtrl.enAlg;
    chn0_ctrl.bits.sym_ch0_decrypt = bIsDecrypt;
    chn0_ctrl.bits.sym_ch0_dat_width = pConfig->CIpstCtrl.enBitWidth;
    chn0_ctrl.bits.sym_ch0_key_length = pConfig->CIpstCtrl.enKeyLen;
    chn0_ctrl.bits.sym_ch0_key_sel = pConfig->CIpstCtrl.bKeyByCA;
    chn0_ctrl.bits.sym_ch0_ivin_sel = pConfig->CIpstCtrl.stChangeFlags.bit1IV;
    chn0_ctrl.bits.sym_ch0_sm1_round_num = 0;
    for(i=0; i<8; i++)
    {
        HAL_CIPHER_WriteReg(CHAN0_CIPHER_KEY + i*4, pConfig->CIpstCtrl.u32Key[i]);
//        printk("key[%d]: 0x%x\n", i, pConfig->CIpstCtrl.u32Key[i]);
    }

    if(pConfig->CIpstCtrl.stChangeFlags.bit1IV)
    {
        for(i=0; i<4; i++)
        {
            HAL_CIPHER_WriteReg(CHAN0_CIPHER_IV + i*4, pConfig->CIpstCtrl.u32IV[i]);
//            printk("iv[%d]: 0x%x\n", i, pConfig->CIpstCtrl.u32IV[i]);
        }
    }

    u32KeyBlock = u32InputLen / u32BlockSize;
    for(j = 0; j < u32KeyBlock; j++)
    {
        HAL_CIPHER_WriteReg(CHAN0_CIPHER_CTRL, chn0_ctrl.u32);
        for(i=0; i<u32BlockSize/4; i++)
        {
            cipher_memcpy_s(&u32Val, sizeof(u32Val), &pu8Input[j * u32BlockSize + i*4], 4);
            HAL_CIPHER_WriteReg(CHAN0_CIPHER_DIN + i*4, u32Val);
//            printk("in[%d]: 0x%x\n", j * 4 + i, u32Val);
        }

        if(HI_UNF_CIPHER_ALG_SM4 == pConfig->CIpstCtrl.enAlg)
        {
            SM4_Enable();
        }
        //start
        chn0_ctrl.bits.sym_ch0_start= 0x01;
        HAL_CIPHER_WriteReg(CHAN0_CIPHER_CTRL, chn0_ctrl.u32);
        while(chn0_ctrl.bits.sym_ch0_start && u32Time++ < SPACC_TIME_OUT)
        {
            HAL_CIPHER_ReadReg(CHAN0_CIPHER_CTRL, &chn0_ctrl.u32);
        }
        if(u32Time >= SPACC_TIME_OUT)
        {
            HI_ERR_CIPHER("Chn 0 time out!\n");
            ret = HI_FAILURE;
            goto __EXIT_HDCP__;
        }

        if(HI_UNF_CIPHER_ALG_SM4 == pConfig->CIpstCtrl.enAlg)
        {
            SM4_Disable();
        }

        if ( NULL != pu8Output )
        {
            for(i=0; i<u32BlockSize/4; i++)
            {
                HAL_CIPHER_ReadReg(CHAN0_CIPHER_DOUT + i*4, &u32Val);
                cipher_memcpy_s(&pu8Output[j * u32BlockSize + i*4], 4, &u32Val, 4);
            }
        }
        for(i=0; i<u32BlockSize/4; i++)
        {
            HAL_CIPHER_ReadReg(CHAN0_CIPHER_DOUT + i*4, &u32Val);
 //           printk("out[%d]: 0x%x\n", j * 4 + i, u32Val);
        }
        chn0_ctrl.bits.sym_ch0_ivin_sel = 0x00;
    }

__EXIT_HDCP__:
    HAL_CIPHER_WriteReg(HDCP_MODE_CTRL, 0x70); //hdmi read clk enable

    return ret;
}

HI_S32 HI_DRV_CIPHER_EncryptHDCPKey(CIPHER_HDCP_KEY_TRANSFER_S *pstHdcpKeyTransfer)
{
    HI_S32 ret = HI_SUCCESS;
    if(cipher_mutex_lock(&g_SymcMutex))
    {
        HI_ERR_CIPHER("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }
    ret = DRV_CIPHER_EncryptHDCPKey(pstHdcpKeyTransfer);
    cipher_mutex_unlock(&g_SymcMutex);
    return ret;
}

HI_S32 HI_DRV_CIPHER_LoadHdcpKey(HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S *pstFlashHdcpKey)
{
    HI_S32 ret = HI_SUCCESS;
    if(cipher_mutex_lock(&g_SymcMutex))
    {
        HI_ERR_CIPHER("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }
    ret = DRV_CIPHER_LoadHdcpKey(pstFlashHdcpKey);
    cipher_mutex_unlock(&g_SymcMutex);
    return ret;
}

HI_VOID HI_DRV_CIPHER_SetHdmiReadClk(HI_DRV_HDCPKEY_TYPE_E enHDCPKeyType)
{
    switch(enHDCPKeyType)
    {
    case HI_DRV_HDCPKEY_TX0:
        HAL_CIPHER_WriteReg(HDCP_MODE_CTRL, 0x10);
        break;
     case HI_DRV_HDCPKEY_RX0:
        HAL_CIPHER_WriteReg(HDCP_MODE_CTRL, 0x20);
        break;
     case HI_DRV_HDCPKEY_RX0V22:
        HAL_CIPHER_WriteReg(HDCP_MODE_CTRL, 0x40);
        break;
    default:
        HI_ERR_CIPHER("Set Hdmi Read Clk failed! unknow key type: 0x%x\n", enHDCPKeyType);
        break;
    }
}
#endif


/******* proc function begin ********/
#if (1 == HI_PROC_SUPPORT)
HI_S32 DRV_CIPHER_ProcGetStatus(CIPHER_CHN_STATUS_S *pstCipherStatus)
{
    HI_U32 i = 0;

    for (i = 0; i < 8; i++)
    {
        if (HI_TRUE == s_stSymcChn[i].bIsOpen)
        {
            pstCipherStatus[i].ps8Openstatus = "open ";
        }
        else
        {
            pstCipherStatus[i].ps8Openstatus = "close";
        }
    }
    return spacc_symc_proc_status(pstCipherStatus);
}
#endif

#ifdef EXPORT_ENABLE
EXPORT_SYMBOL(HI_DRV_CIPHER_CreateHandle);
EXPORT_SYMBOL(HI_DRV_CIPHER_ConfigChnEx);
EXPORT_SYMBOL(HI_DRV_CIPHER_DestroyHandle);
EXPORT_SYMBOL(HI_DRV_CIPHER_Encrypt);
EXPORT_SYMBOL(HI_DRV_CIPHER_Decrypt);
EXPORT_SYMBOL(HI_DRV_CIPHER_EncryptMulti);
EXPORT_SYMBOL(HI_DRV_CIPHER_DecryptMulti);
EXPORT_SYMBOL(HI_DRV_CIPHER_GetHandleConfigEx);
EXPORT_SYMBOL(HI_DRV_CIPHER_SoftReset);
EXPORT_SYMBOL(HI_DRV_CIPHER_LoadHdcpKey);
EXPORT_SYMBOL(HI_DRV_CIPHER_CalcHashInit);
EXPORT_SYMBOL(HI_DRV_CIPHER_CalcHashUpdate);
EXPORT_SYMBOL(HI_DRV_CIPHER_CalcHashFinal);
EXPORT_SYMBOL(HI_DRV_CIPHER_GetTag);
EXPORT_SYMBOL(HI_DRV_CIPHER_CPU_Encrypt);
#endif

