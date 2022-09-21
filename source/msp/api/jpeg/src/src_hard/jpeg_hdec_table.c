/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_hdec_table.c
Version           : Initial Draft
Author            : sdk
Created          : 2017/07/05
Description      : get table
Function List    : 协议表从T81 协议来的


History          :
Date                       Author                Modification
2017/07/05             sdk                    Created file
******************************************************************************/

/***************************** add include here*********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jpeglib.h"
#include "jerror.h"

#include "hi_jpeg_checkpara.h"
#include "jpeg_hdec_api.h"
#include "jpeg_sdec_table.h"
#include "hi_gfx_sys.h"

/***************************** Macro Definition ********************************/
#define  LU                 0
#define  CH                 1
#define  MAX_TAB            2

#define CAI_JPEG_SWAP(a,b)  do{ a=a+b; b=a-b; a=a-b; } while(0)

/***************************** Structure Definition ****************************/

/***************************** Global Variable declaration *********************/

/***************************** API forward declarations ************************/
static inline HI_VOID JPEG_HDEC_GetQuantTable(const struct jpeg_decompress_struct *cinfo);
static inline HI_U32 JPEG_HDEC_HuffmanDcDec   (const JHUFF_TBL *huff_tbl, unsigned int bit[256]);
static inline HI_U32 JPEG_HDEC_HuffmanAcDec   (const JHUFF_TBL *huff_tbl);

static HI_VOID JPEG_HDEC_GetHuffmanTable    (const struct jpeg_decompress_struct *cinfo);
static HI_VOID JPEG_HDEC_GetHuffmanDcTable  (const struct jpeg_decompress_struct *cinfo);
static HI_VOID JPEG_HDEC_GetHuffmanAcTable  (const struct jpeg_decompress_struct *cinfo);
static HI_VOID JPEG_HDEC_DcTableForReg(const struct jpeg_decompress_struct *cinfo, JHUFF_TBL* pDcHuffmanTable, HI_U32 HuffCode[], HI_U32 MaxIndex, HI_U32 TabNum);

/******************************* API realization *****************************/

/*****************************************************************************
* func          : JPEG_HDEC_GetTable
* description   : get table, include quant table and huffman table
                  CNcomment: 获取量化表和哈夫曼表   CNend\n
* param[in]     : cinfo       CNcomment: 解码对象   CNend\n
* retval        : HI_TRUE     CNcomment: support    CNend\n
* retval        : HI_FALSE    CNcomment: unsupport  CNend\n
* others:       : NA
*****************************************************************************/
HI_BOOL JPEG_HDEC_GetTable(j_decompress_ptr cinfo)
{
    CHECK_JPEG_EQUAL_RETURN(NULL, cinfo, HI_FALSE);
    JPEG_HDEC_GetQuantTable(cinfo);
    JPEG_HDEC_GetHuffmanTable(cinfo);
    return HI_TRUE;
}


static HI_VOID JPEG_HDEC_GetQuantTable(const struct jpeg_decompress_struct *cinfo)
{
     HI_U16  *QCr = NULL;
     HI_U16  *QCb = NULL;
     HI_U16  *QY  = NULL;
     HI_S32 s32Cnt = 0;
     HI_S32 quant_tbl_no[NUM_QUANT_TBLS] = {0};

     jpeg_component_info  *compptr = NULL;
     JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

     HI_U16 T81ProtocolLuQuantTable[DCTSIZE2] = {
                                       16, 11, 10, 16, 24, 40, 51, 61,
                                       12, 12, 14, 19, 26, 58, 60, 55,
                                       14, 13, 16, 24, 40, 57, 69, 56,
                                       14, 17, 22, 29, 51, 87, 80, 62,
                                       18, 22, 37, 56, 68, 109,103,77,
                                       24, 35, 55, 64, 81, 104,113,92,
                                       49, 64, 78, 87, 103,121,120,101,
                                       72, 92, 95, 98, 112,100,103,99
                                      };
     HI_U16 T81ProtocolChQuantTable[DCTSIZE2] = {
                                         17, 18, 24, 47, 99, 99, 99, 99,
                                         18, 21, 26, 66, 99, 99, 99, 99,
                                         24, 26, 56, 99, 99, 99, 99, 99,
                                         47, 66, 99, 99, 99, 99, 99, 99,
                                         99, 99, 99, 99, 99, 99, 99, 99,
                                         99, 99, 99, 99, 99, 99, 99, 99,
                                         99, 99, 99, 99, 99, 99, 99, 99,
                                         99, 99, 99, 99, 99, 99, 99, 99
                                        };

     if (NULL == cinfo->quant_tbl_ptrs[0])
     {
         QY  = (unsigned short *)T81ProtocolLuQuantTable;
         QCb = (unsigned short *)T81ProtocolChQuantTable;
         QCr = (unsigned short *)T81ProtocolChQuantTable;
     }
     else
     {
         for (s32Cnt = 0, compptr = cinfo->comp_info; s32Cnt < cinfo->num_components; s32Cnt++, compptr++)
         {
              quant_tbl_no[s32Cnt] = ((compptr->quant_tbl_no < 0 || compptr->quant_tbl_no >= NUM_QUANT_TBLS)) ? (0) : (compptr->quant_tbl_no);
         }

         if (NULL == cinfo->quant_tbl_ptrs[quant_tbl_no[0]])
         {
             ERREXIT1(cinfo, JERR_NO_QUANT_TABLE, quant_tbl_no[0]);
         }
         QY  = cinfo->quant_tbl_ptrs[quant_tbl_no[0]]->quantval;
         QCb = (cinfo->quant_tbl_ptrs[quant_tbl_no[1]] == NULL) ? (QY)  : (cinfo->quant_tbl_ptrs[quant_tbl_no[1]]->quantval);
         QCr = (cinfo->quant_tbl_ptrs[quant_tbl_no[2]] == NULL) ? (QCb) : (cinfo->quant_tbl_ptrs[quant_tbl_no[2]]->quantval);
     }

     for (s32Cnt = 0; s32Cnt < DCTSIZE2; s32Cnt++)
     {
         pJpegHandle->s32QuantTab[s32Cnt] = QY[s32Cnt] + (QCb[s32Cnt] << 8) + (QCr[s32Cnt] << 16);
     }

     return;
}


static HI_VOID JPEG_HDEC_GetHuffmanTable(const struct jpeg_decompress_struct *cinfo)
{
    JPEG_HDEC_GetHuffmanDcTable(cinfo);
    JPEG_HDEC_GetHuffmanAcTable(cinfo);
    return;
}

static HI_VOID JPEG_HDEC_GetHuffmanDcTable(const struct jpeg_decompress_struct *cinfo)
{
    HI_U32 huffcode[MAX_TAB][256]  = {{0}};
    HI_U32 max_idx[MAX_TAB]        = {0};

    HI_U8 *pDcDefaultTable = (HI_U8*)gs_u8DefaultDC;
    JHUFF_TBL DcHuffmanTablePtr[MAX_TAB] = { { {0}, {0}, 0} };

    if ((NULL == cinfo->dc_huff_tbl_ptrs[0]) || (NULL != cinfo->dc_huff_tbl_ptrs[2]))
    {
        pDcDefaultTable += 1;
        HI_GFX_Memcpy(&(DcHuffmanTablePtr[LU].bits[1]), pDcDefaultTable, 16);
        pDcDefaultTable += 16;
        HI_GFX_Memcpy(&(DcHuffmanTablePtr[LU].huffval[0]), pDcDefaultTable, 12);
        pDcDefaultTable += 12;
        pDcDefaultTable += 1;
        pDcDefaultTable += 1;
        HI_GFX_Memcpy(&(DcHuffmanTablePtr[CH].bits[1]), pDcDefaultTable, 16);
        pDcDefaultTable += 16;
        HI_GFX_Memcpy(&(DcHuffmanTablePtr[CH].huffval[0]), pDcDefaultTable, 12);
        pDcDefaultTable += 12;
    }
    else
    {
        HI_GFX_Memcpy(&(DcHuffmanTablePtr[LU]), cinfo->dc_huff_tbl_ptrs[0], sizeof(DcHuffmanTablePtr[LU]));
        if (NULL == cinfo->dc_huff_tbl_ptrs[1])
        {
           HI_GFX_Memcpy(&(DcHuffmanTablePtr[CH]),cinfo->dc_huff_tbl_ptrs[0],sizeof(DcHuffmanTablePtr[LU]));
        }
        else
        {
            HI_GFX_Memcpy(&(DcHuffmanTablePtr[CH]),cinfo->dc_huff_tbl_ptrs[1],sizeof(DcHuffmanTablePtr[LU]));
        }
    }

    max_idx[LU] = JPEG_HDEC_HuffmanDcDec(&DcHuffmanTablePtr[LU], huffcode[LU]);
    max_idx[CH] = JPEG_HDEC_HuffmanDcDec(&DcHuffmanTablePtr[CH], huffcode[CH]);

    JPEG_HDEC_DcTableForReg(cinfo, &DcHuffmanTablePtr[LU], huffcode[LU], max_idx[LU],LU);
    JPEG_HDEC_DcTableForReg(cinfo, &DcHuffmanTablePtr[CH], huffcode[CH], max_idx[CH],CH);

    return;
}


static HI_VOID JPEG_HDEC_DcTableForReg(const struct jpeg_decompress_struct *cinfo, JHUFF_TBL* pDcHuffmanTable, HI_U32 HuffCode[], HI_U32 MaxIndex, HI_U32 TabNum)
{
    HI_U32 sum_syms   = 0;
    HI_U32 syms       = 0;
    HI_U32 temp       = 0;
    HI_U32 index     = 0;
    HI_U32 index1     = 0;
    HI_U32 dc_hufflen[12] = {0};
    HI_U32 dc_sym[12]     = {0};
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    if (MaxIndex > 16)
    {
       ERREXIT(cinfo, JERR_BAD_HUFF_TABLE);
    }

    for (index = 0; index < MaxIndex; index++)
    {
       syms = pDcHuffmanTable->bits[index + 1];
       sum_syms += syms;
       while ((syms--) && (temp < 12))
       {
           dc_hufflen[temp] = index + 1;
           dc_sym[temp] = pDcHuffmanTable->huffval[temp];
           temp++;
       }
    }

    if (sum_syms > 12)
    {
       ERREXIT(cinfo, JERR_BAD_HUFF_TABLE);
    }

    for (index = 0; index < sum_syms; index++)
    {
       for (index1 = index + 1; index1 < sum_syms; index1++)
       {
           if (dc_sym[index] > dc_sym[index1])
           {
               CAI_JPEG_SWAP(dc_sym[index],     dc_sym[index1]);
               CAI_JPEG_SWAP(dc_hufflen[index], dc_hufflen[index1]);
               CAI_JPEG_SWAP(HuffCode[index],   HuffCode[index1]);
           }
       }

       if (dc_sym[index] >= 12)
       {
           ERREXIT(cinfo, JERR_BAD_HUFF_TABLE);
       }
    }


    for (index = 0;index < sum_syms; index++)
    {
        *(pJpegHandle->u32HuffDcTab + dc_sym[index]) = (0 == TabNum) ?
                                                       ( ((*(pJpegHandle->u32HuffDcTab + dc_sym[index])) & 0xfffff000)
                                                        | ((dc_hufflen[index] & 0xf) << 8) \
                                                        | ((HuffCode[index] & 0xff))) :
                                                       (  ((*(pJpegHandle->u32HuffDcTab + dc_sym[index])) & 0xff000fff)
                                                        | ((dc_hufflen[index] & 0xf) << 20) \
                                                        | ((HuffCode[index] & 0xff) << 12));

    }

    return;
}


static HI_VOID JPEG_HDEC_GetHuffmanAcTable(const struct jpeg_decompress_struct *cinfo)
{
     HI_U32 TabNum = 0;
     HI_U32 index = 0;
     HI_U32 pre_index = 0;
     HI_U32 sum_syms = 0;
     HI_U32 syms = 0;

     HI_U32 min_tab[MAX_TAB][16]    = {{0}};
     HI_U32 base_tab[MAX_TAB][16]   = {{0}};
     HI_U32 max_idx[MAX_TAB]        = {0};

     JHUFF_TBL AcHuffmanTablePtr[MAX_TAB] = { { {0}, {0}, 0} };

     HI_U8 *pAcDefaultTable = (HI_U8*)gs_u8DefaultAC;
     JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

     if ((NULL == cinfo->ac_huff_tbl_ptrs[0]) || (NULL != cinfo->ac_huff_tbl_ptrs[2]))
     {
         pAcDefaultTable += 1;
         HI_GFX_Memset(&(AcHuffmanTablePtr[LU].bits[0]),0,17);
         HI_GFX_Memcpy(&(AcHuffmanTablePtr[LU].bits[1]), pAcDefaultTable, 16);
         pAcDefaultTable += 16;
         HI_GFX_Memset(&(AcHuffmanTablePtr[LU].huffval[0]),0,256);
         HI_GFX_Memcpy(&(AcHuffmanTablePtr[LU].huffval[0]), pAcDefaultTable, 162);
         pAcDefaultTable += 162;
         pAcDefaultTable += 1;
         pAcDefaultTable += 1;
         HI_GFX_Memset(&(AcHuffmanTablePtr[CH].bits[0]),0,17);
         HI_GFX_Memcpy(&(AcHuffmanTablePtr[CH].bits[1]), pAcDefaultTable, 16);
         pAcDefaultTable += 16;
         HI_GFX_Memset(&(AcHuffmanTablePtr[CH].huffval[0]),0,256);
         HI_GFX_Memcpy(&(AcHuffmanTablePtr[CH].huffval[0]), pAcDefaultTable, 162);
     }
     else
     {
         HI_GFX_Memset(&(AcHuffmanTablePtr[LU].bits[0]),0,17);
         HI_GFX_Memset(&(AcHuffmanTablePtr[LU].huffval[0]),0,256);
         HI_GFX_Memset(&(AcHuffmanTablePtr[CH].bits[0]),0,17);
         HI_GFX_Memset(&(AcHuffmanTablePtr[CH].huffval[0]),0,256);
         HI_GFX_Memcpy(&(AcHuffmanTablePtr[LU]), cinfo->ac_huff_tbl_ptrs[0], sizeof(AcHuffmanTablePtr[LU]));

         if (NULL == cinfo->ac_huff_tbl_ptrs[1])
         {
             HI_GFX_Memcpy(&(AcHuffmanTablePtr[CH]),cinfo->ac_huff_tbl_ptrs[0],sizeof(AcHuffmanTablePtr[LU]));
         }
         else
         {
             HI_GFX_Memcpy(&(AcHuffmanTablePtr[CH]),cinfo->ac_huff_tbl_ptrs[1],sizeof(AcHuffmanTablePtr[LU]));
         }
     }

     max_idx[LU] = JPEG_HDEC_HuffmanAcDec(&AcHuffmanTablePtr[0]);
     max_idx[CH] = JPEG_HDEC_HuffmanAcDec(&AcHuffmanTablePtr[1]);

     for (TabNum = 0; TabNum < MAX_TAB; TabNum++)
     {
          sum_syms = 0;
          for (index = 0; index < 16; index++)
          {
              syms = AcHuffmanTablePtr[TabNum].bits[index + 1];
              pre_index = index?(index - 1):(0);

              if (index < max_idx[TabNum])
              {
                  min_tab[TabNum][index] = (min_tab[TabNum][pre_index] + AcHuffmanTablePtr[TabNum].bits[index]) << 1;
                  if (syms)
                  {
                      base_tab[TabNum][index] = sum_syms - min_tab[TabNum][index];
                  }
                  sum_syms += AcHuffmanTablePtr[TabNum].bits[index+1];
              }
              else
              {
                  min_tab[TabNum][index] = ~0;
              }
          }

          if (sum_syms > 256)
          {
             ERREXIT(cinfo, JERR_BAD_HUFF_TABLE);
          }

          for (index = 0; index < sum_syms; index++)
          {
              pJpegHandle->u32HufAcSymbolTab[index] |= (0 == TabNum) ?
                                                       ((unsigned int)(AcHuffmanTablePtr[LU].huffval[index])):
                                                       ((unsigned int)(AcHuffmanTablePtr[CH].huffval[index]) << 8);
          }
     }

     for (index = 0; index < 8;index++)
     {
         pJpegHandle->u32HufAcMinTab[index] =   ( (min_tab[CH][2 * index + 1] & 0xff) << 24)
                                                 | ((min_tab[CH][2 * index] & 0xff) << 16)
                                                 | ((min_tab[LU][2 * index + 1] & 0xff) << 8)
                                                 | ((min_tab[LU][2 * index] & 0xff));

         pJpegHandle->u32HufAcBaseTab[index] =  ( (base_tab[CH][2 * index + 1] & 0xff) << 24)
                                                 | ((base_tab[CH][2 * index] & 0xff) << 16)
                                                 | ((base_tab[LU][2 * index + 1] & 0xff) << 8)
                                                 | ((base_tab[LU][2 * index] & 0xff));
     }

     return;
}

static inline HI_U32 JPEG_HDEC_HuffmanDcDec(const JHUFF_TBL *huff_tbl, unsigned int bit[256])
{
    HI_U32 idx     = 0;
    HI_U32 cnt     = 0;
    HI_U32 loc     = 0;
    HI_U32 value   = 0;
    HI_U32 max_idx = 0;

    HI_GFX_Memset(bit,0,sizeof(bit[0]));

    for (idx = 1; idx < 17; idx++)
    {
       if (0 == huff_tbl->bits[idx])
       {
          value <<= 1;
          continue;
       }

       max_idx = idx;

       for (cnt = huff_tbl->bits[max_idx]; cnt > 0 && loc < 256; cnt--)
       {
           bit[loc] = value;
           loc++;
           value++;
       }

       value <<= 1;
    }

    return max_idx;
}

static inline HI_U32 JPEG_HDEC_HuffmanAcDec(const JHUFF_TBL *huff_tbl)
{
    HI_U32 index   = 0;
    HI_U32 max_idx = 0;

    for (index = 1; index < 17; index++)
    {
       if (0 == huff_tbl->bits[index])
       {
        continue;
       }
       max_idx = index;
    }

    return max_idx;
}
