#ifndef __DRV_VENC_BUF_MNG_H__
#define __DRV_VENC_BUF_MNG_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/************************cabac/cavlc coding************************/
static const HI_U8 g_msZerosTable[] =
{
    8, 7, 6, 6, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

#define MsZeros(zeros, c) \
    { \
        HI_U32 __code__ = (c); \
        zeros = g_msZerosTable[__code__ >> 24]; \
        if (8 == zeros) \
        { zeros += g_msZerosTable[0xFF & (__code__ >> 16)]; \
            if (16 == zeros) \
            { zeros += g_msZerosTable[0xFF & (__code__ >> 8)]; \
                if (24 == zeros) \
                { zeros += g_msZerosTable[0xFF & __code__ ]; } } } \
    }

#define ue_vlc(bits, code, val) \
    {                            \
        HI_U32 zeros;             \
        code = (val) + 1;          \
        MsZeros(zeros, code);       \
        bits = 63 - (zeros << 1);    \
    }

#define se_vlc(bits, code, val) \
    {                            \
        HI_U32 zeros;             \
        code = (((val) < 0 ? -(val) : (val)) << 1) | ((val) <= 0); \
        MsZeros(zeros, code);       \
        bits = 63 - (zeros << 1);    \
    }

#define REV32(x) ((((HI_U32)(x)) >> 24) + ((((HI_U32)(x)) >> 8) & (HI_U32)0xFF00) + \
                  (((HI_U32)(x)) << 24) + ((((HI_U32)(x)) << 8) & (HI_U32)0xFF0000))

/************************************************
Processor-related definitions

 Notes:
 1)All length units are addressing step of processor, and ARM is the "bytes";
 2)All W/R operations carried out in accordance with word, so need:
   buffer length of the packet should be in word-alignment;
   elements of the queue should be in word-alignment;
 *************************************************/

#define WORD_ALIGN 0x04       /*Bytes included in one word*/

typedef struct
{
    HI_U32  tU32a; // only used in ShowBits32 and FlushBits31/32
    HI_U32  tU32b;
    HI_U32* pBuff;
    HI_U32  tBits;
    HI_U32  totalBits;
    HI_U32  bBigEndian;
} tBitStream;

typedef struct
{
    HI_U32* pBase;  /* base addr    */
    HI_U32  Len;    /* max length   */
    HI_U32  Head;   /* head pointer */
    HI_U32  Sum;
    HI_U32  Mean;
} VALG_FIFO_S;

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
#define FrmRateCntBufNum  65

__inline static HI_VOID VENC_DRV_FifoInit(VALG_FIFO_S* pFifo, HI_VOID* pBase, HI_U32 Len, HI_U32 Mean)
{
    int i;

    pFifo->pBase = (HI_U32*)pBase;
    if (Len >= FrmRateCntBufNum) {Len = FrmRateCntBufNum;}

    pFifo->Len  = Len;
    pFifo->Head = 0;
    pFifo->Sum  = 0;
    pFifo->Mean = Mean;

    for (i = 0; i < Len; i++)
    {
        pFifo->pBase[i] = 0;
    }
}

__inline static HI_VOID VENC_DRV_FifoWriteInit(VALG_FIFO_S* pFifo, HI_U32 Val)
{
    if (pFifo->pBase == NULL)
    {
        return;
    }

    pFifo->Sum -= pFifo->pBase[pFifo->Head];
    pFifo->Sum += Val;

    pFifo->pBase[pFifo->Head] = Val;

    pFifo->Head++;

    if (pFifo->Head >= pFifo->Len)
    {
        pFifo->Head -= pFifo->Len;
    }
}

__inline static HI_VOID VENC_DRV_FifoWrite(VALG_FIFO_S* pFifo, HI_U32 Val)
{
    if (pFifo->pBase == NULL)
    {
        return;
    }

    if (pFifo->Sum > pFifo->Mean)
    {
        //pFifo->Sum -= pFifo->Mean;
        pFifo->Sum -= pFifo->pBase[pFifo->Head];
    }
    else
    {
        pFifo->Sum = 0;
    }

    pFifo->Sum += Val;

    pFifo->pBase[pFifo->Head] = Val;

    pFifo->Head++;

    if (pFifo->Head >= pFifo->Len)
    {
        pFifo->Head -= pFifo->Len;
    }
}

HI_VOID VENC_DRV_BsOpenBitStream(tBitStream* pBS, HI_U32* pBuffer);
HI_VOID VENC_DRV_BsPutBits31(tBitStream* pBS, HI_U32 code, HI_U32 bits);
HI_VOID VENC_DRV_BsPutBits32(tBitStream* pBS, HI_U32 code, HI_U32 bits);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
