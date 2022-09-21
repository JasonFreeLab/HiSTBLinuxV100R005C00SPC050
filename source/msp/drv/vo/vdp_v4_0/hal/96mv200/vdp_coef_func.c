#include "vdp_coef_func.h"
#if EDA_TEST
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "vdp_frw.h"
#endif

#if EMU_TEST
#include "himem_wrap.h"
Cell cell;
#elif EDA_TEST

#include "CqHash.h"
#include "dlfcn.h"

extern void (*HiMemWordWr)(const Cell*);
extern Cell* (*HiMemWordRd)(const Cell*);
extern Cell cell;

#endif

#if 0
static HI_U32 uGetRand(HI_U32 max, HI_U32 min)
{
    HI_U32 u32_max_data = 0;
    HI_U32 u32_min_data = 0;
    HI_U32 u32_rand_data = 0;

    if(max > min)
    {
        u32_max_data = max;
        u32_min_data = min;
    }
    else
    {
        u32_max_data = min;
        u32_min_data = max;
    }

    u32_rand_data = u32_min_data + rand()%((HI_U64)u32_max_data + 1 - u32_min_data);

    return (u32_rand_data);
}

static HI_S32 sGetRand(HI_S32 max, HI_S32 min)
{
    HI_U32 u32_max_data = 0;
    HI_U32 u32_min_data = 0;

    HI_S32 s32_return_data = 0;

    if(((max == 0)&&(min == 0)) || (min == max))
    {
        cout << "Error, Worng sRand seed!" << endl;
    }
    else if(((max >= 0)&&(min > 0)) || ((max > 0)&&(min >= 0)))
    {
        if(max > min)
        {
            u32_max_data = max;
            u32_min_data = min;
        }
        else
        {
            u32_max_data = min;
            u32_min_data = max;
        }

        s32_return_data = (u32_min_data + rand()%(u32_max_data + 1 - u32_min_data));
    }
    else if(((max <= 0)&&(min < 0)) || ((max < 0)&&(min <= 0)))
    {
        if(abs(max) > abs(min))
        {
            u32_max_data = abs(max);
            u32_min_data = abs(min);
        }
        else
        {
            u32_max_data = abs(min);
            u32_min_data = abs(max);
        }

        s32_return_data = -(u32_min_data + rand()%(u32_max_data + 1 - u32_min_data));
    }
    else
    {
        if((max > 0)&&(min < 0))
        {
            u32_max_data = abs(max);
            u32_min_data = abs(min);
        }
        else
        {
            u32_max_data = abs(min);
            u32_min_data = abs(max);
        }

        if(rand()%2 == 0)
        {
            s32_return_data = -(rand()%(u32_min_data + 1));
        }
        else
        {
            s32_return_data =    rand()%(u32_max_data + 1);
        }
    }

    return s32_return_data;
}
#endif
#if 0
static HI_U32 VDP_FUNC_FindMax(HI_U32* u32Array, HI_U32 num)
{
    HI_U32 ii;
    HI_U32 u32TmpData = u32Array[0];

    for(ii=1;ii<num;ii++)
    {
        if(u32TmpData < u32Array[ii])
        {
            u32TmpData = u32Array[ii];
        }
    }
    return u32TmpData;
}


HI_U32 VDP_FUNC_GenCoef(VDP_COEF_GEN_CFG* stCfg)
{
    HI_U32 ii=0;
    HI_S32 tmp_data=0;

    if(stCfg->coef_data_mode == VDP_RM_COEF_MODE_TYP)
    {
        if(stCfg->coef_data_type == COEF_DATA_TYPE_U8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                ((HI_U8*)stCfg->p_coef_new)[ii] = ((HI_U8*)stCfg->p_coef)[ii];
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = ((HI_U8*)stCfg->p_coef)[ii];
                }
            }
        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_S8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                ((HI_S8*)stCfg->p_coef_new)[ii] = ((HI_S8*)stCfg->p_coef)[ii];
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = ((HI_S8*)stCfg->p_coef)[ii];
                }
            }

        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_U16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                ((HI_U16*)stCfg->p_coef_new)[ii] = ((HI_U16*)stCfg->p_coef)[ii];
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = ((HI_U16*)stCfg->p_coef)[ii];
                    //cout<< dec<< (HI_U32) (((HI_U16*)stCfg->p_coef)[ii]) <<endl;

                }
            }

        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_S16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                ((HI_S16*)stCfg->p_coef_new)[ii] = ((HI_S16*)stCfg->p_coef)[ii];
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = ((HI_S16*)stCfg->p_coef)[ii];
                }
            }

        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_U32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                ((HI_U32*)stCfg->p_coef_new)[ii] = ((HI_U32*)stCfg->p_coef)[ii];
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = ((HI_U32*)stCfg->p_coef)[ii];
                }
            }

        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_S32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                ((HI_S32*)stCfg->p_coef_new)[ii] = ((HI_S32*)stCfg->p_coef)[ii];
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = ((HI_S32*)stCfg->p_coef)[ii];
                }
            }

        }

    }
    else if(stCfg->coef_data_mode == VDP_RM_COEF_MODE_RAN)
    {
        if(stCfg->coef_data_type == COEF_DATA_TYPE_U8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = sGetRandEx(stCfg->coef_min,stCfg->coef_max);
                ((HI_U8*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }
        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_S8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = sGetRandEx(stCfg->coef_min,stCfg->coef_max);
                ((HI_S8*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }

        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_U16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = sGetRandEx(stCfg->coef_min,stCfg->coef_max);
                ((HI_U16*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }

        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_S16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = sGetRandEx(stCfg->coef_min,stCfg->coef_max);
                ((HI_S16*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }

        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_U32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = uGetRandEx(stCfg->coef_min,stCfg->coef_max);
                ((HI_U32*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }

        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_S32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = sGetRandEx(stCfg->coef_min,stCfg->coef_max);
                ((HI_S32*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }

        }

    }
    else if(stCfg->coef_data_mode == VDP_RM_COEF_MODE_ZRO)
    {
        if(stCfg->coef_data_type == COEF_DATA_TYPE_U8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = 0;
                ((HI_U8*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }
        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_S8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = 0;
                ((HI_S8*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }

        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_U16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = 0;
                ((HI_U16*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }

        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_S16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = 0;
                ((HI_S16*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }

        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_U32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = 0;
                ((HI_U32*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }

        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_S32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = 0;
                ((HI_S32*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }

        }

    }
    else if(stCfg->coef_data_mode == VDP_RM_COEF_MODE_MIN)
    {
        if(stCfg->coef_data_type == COEF_DATA_TYPE_U8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_min;
                ((HI_U8*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }
        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_S8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_min;
                ((HI_S8*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }

        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_U16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_min;
                ((HI_U16*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }

        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_S16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_min;
                ((HI_S16*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }

        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_U32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_min;
                ((HI_U32*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }

        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_S32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_min;
                ((HI_S32*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }

        }

    }
    else if(stCfg->coef_data_mode == VDP_RM_COEF_MODE_MAX)
    {
        if(stCfg->coef_data_type == COEF_DATA_TYPE_U8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_max;
                ((HI_U8*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }
        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_S8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_max;
                ((HI_S8*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }

        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_U16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_max;
                ((HI_U16*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }

        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_S16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_max;
                ((HI_S16*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }

        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_U32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_max;
                ((HI_U32*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }

        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_S32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_max;
                ((HI_S32*)stCfg->p_coef_new)[ii] = tmp_data;
                if(stCfg->ps32_coef_temp != NULL)
                {
                    stCfg->ps32_coef_temp[ii] = tmp_data;
                }
            }

        }

    }
#if 0
    else if(stCfg->coef_data_mode == VDP_RM_COEF_MODE_UP)
    {
        if(stCfg->coef_data_type == COEF_DATA_TYPE_U8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = sGetRandEx(stCfg->coef_min,stCfg->coef_max);
                ((HI_U8*)stCfg->p_coef_new)[ii] = tmp_data;
            }

            qsort(stCfg->p_coef_new     , stCfg->length , sizeof(HI_U8) , VDP_FUNC_CoefUpSortU8);

            if(stCfg->ps32_coef_temp != NULL)
            {
                for(ii=0;ii<stCfg->length;ii++)
                    stCfg->ps32_coef_temp[ii] = ((HI_S32*)stCfg->p_coef_new)[ii];
            }
        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_S8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = sGetRandEx(stCfg->coef_min,stCfg->coef_max);
                ((HI_S8*)stCfg->p_coef_new)[ii] = tmp_data;
            }

            qsort(stCfg->p_coef_new     , stCfg->length , sizeof(HI_S8) , VDP_FUNC_CoefUpSortS8);

            if(stCfg->ps32_coef_temp != NULL)
            {
                for(ii=0;ii<stCfg->length;ii++)
                    stCfg->ps32_coef_temp[ii] = ((HI_S32*)stCfg->p_coef_new)[ii];
            }
        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_U16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = sGetRandEx(stCfg->coef_min,stCfg->coef_max);
                ((HI_U16*)stCfg->p_coef_new)[ii] = tmp_data;
            }
            qsort(stCfg->p_coef_new     , stCfg->length , sizeof(HI_U16) , VDP_FUNC_CoefUpSortU16);
            if(stCfg->ps32_coef_temp != NULL)
            {
                for(ii=0;ii<stCfg->length;ii++)
                    stCfg->ps32_coef_temp[ii] = ((HI_S32*)stCfg->p_coef_new)[ii];
            }
        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_S16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = sGetRandEx(stCfg->coef_min,stCfg->coef_max);
                ((HI_S16*)stCfg->p_coef_new)[ii] = tmp_data;
            }

            qsort(stCfg->p_coef_new     , stCfg->length , sizeof(HI_S16) , VDP_FUNC_CoefUpSortS16);

            if(stCfg->ps32_coef_temp != NULL)
            {
                for(ii=0;ii<stCfg->length;ii++)
                    stCfg->ps32_coef_temp[ii] = ((HI_S32*)stCfg->p_coef_new)[ii];
            }
        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_U32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = uGetRandEx(stCfg->coef_min,stCfg->coef_max);
                ((HI_U32*)stCfg->p_coef_new)[ii] = tmp_data;
            }

            qsort(stCfg->p_coef_new    , stCfg->length , sizeof(HI_U32) , VDP_FUNC_CoefUpSortU32);

            if(stCfg->ps32_coef_temp != NULL)
            {
                for(ii=0;ii<stCfg->length;ii++)
                    stCfg->ps32_coef_temp[ii] = ((HI_S32*)stCfg->p_coef_new)[ii];
            }
        }
        else if(stCfg->coef_data_type == COEF_DATA_TYPE_S32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = sGetRandEx(stCfg->coef_min,stCfg->coef_max);
                ((HI_S32*)stCfg->p_coef_new)[ii] = tmp_data;
            }

            qsort(stCfg->p_coef_new     , stCfg->length , sizeof(HI_S32) , VDP_FUNC_CoefUpSortS32);

            if(stCfg->ps32_coef_temp != NULL)
            {
                for(ii=0;ii<stCfg->length;ii++)
                    stCfg->ps32_coef_temp[ii] = ((HI_S32*)stCfg->p_coef_new)[ii];
            }
        }
    }
#endif
    else
    {
        VDP_PRINT("Error, VDP_FUNC_GenCoef don't support this mode!\n");
    }

}
#endif
HI_U32 VDP_FUNC_SendCoef(VDP_DRV_COEF_SEND_CFG* stCfg)
{
#if 0
    HI_U32 ii,jj,kk,nn,mm;
    HI_U32 addr_base   = stCfg->coef_addr;
    HI_U32 addr_offset = 0;
    HI_U32 addr=addr_base;

    HI_U32 cycle_num = stCfg->cycle_num ;
    HI_U32 total_bit_len = 0;

    VDP_U128_S stData128;
    HI_U32 coef_cnt = 0;

    HI_S32 tmp_data = 0;
    HI_U32 total_burst_num = 0;
    HI_U32 total_burst_cycle_num = 0;
    HI_U32 lut_cnt  = 0;
    HI_U32 max_num_each_burst = 0;
    HI_U32 max_len=0;
    HI_U32 cycle_cnt=0;

//    bOpenStiFile(stCfg->sti_type);

    for(ii=0;ii<stCfg->lut_num;ii++)
    {
        total_bit_len = total_bit_len + stCfg->coef_bit_length[ii];
    }

    //send data

    max_len = VDP_FUNC_FindMax( stCfg->lut_length , stCfg->lut_num) ;
//    cycle_num = (128 * stCfg->burst_num) / total_bit_len ;

    VDP_ASSERT(total_bit_len * cycle_num <= 128);

    if(stCfg->burst_num == 1)
    {
        total_burst_num = (max_len + cycle_num -1)/cycle_num;

        for(kk=0; kk<total_burst_num; kk++)
        {
            memset((void*)&stData128, 0 , sizeof(stData128));
            for(mm=0 ; mm<cycle_num ; mm++)
            {
                coef_cnt = kk * cycle_num + mm ;
                for(nn=0; nn < stCfg->lut_num ; nn++)
                {
                    if(coef_cnt < stCfg->lut_length[nn])
                    {
                        tmp_data = ((HI_S32**)stCfg->p_coef_array)[nn][coef_cnt];
                    }
                    else
                    {
                        tmp_data = 0;
                    }
                    VDP_FUNC_Push128(&stData128, tmp_data, stCfg->coef_bit_length[nn]);
                }
            }
            addr = addr_base + addr_offset;
            addr_offset = addr_offset + 16;
            VDP_FUNC_WriteDDR(stCfg->sti_type,stCfg->fp_coef,addr,&stData128);
        }

    }
    else
    {
        total_burst_cycle_num = (max_len + cycle_num -1)/cycle_num;
        max_num_each_burst    = 128/(stCfg->coef_bit_length[0]);

        for(kk=0; kk<total_burst_cycle_num; kk++)
        {
            memset((void*)&stData128, 0 , sizeof(stData128));
            cycle_cnt = 0;
            for(nn=0; nn<(cycle_num * stCfg->lut_num);nn++)
            {
                if((kk*cycle_num+cycle_cnt)< stCfg->lut_length[lut_cnt] )
                {
                    tmp_data = ((HI_S32**)stCfg->p_coef_array)[lut_cnt][kk*cycle_num+cycle_cnt] ;
                }
                else
                {
                    tmp_data = 0;
                }
                VDP_FUNC_Push128(&stData128, tmp_data, stCfg->coef_bit_length[lut_cnt]);

                lut_cnt++;
                coef_cnt++;
                if(lut_cnt == stCfg->lut_num)
                {
                    lut_cnt = 0 ;
                    cycle_cnt++ ;
                }

                if((coef_cnt == max_num_each_burst && cycle_cnt < cycle_num) || cycle_cnt == cycle_num)
                {
                    coef_cnt = 0;
                    addr = addr_base + addr_offset;
                    VDP_FUNC_WriteDDR(stCfg->sti_type,stCfg->fp_coef,addr,&stData128);
                    addr_offset  = addr_offset + 16;
                    memset((void*)&stData128, 0 , sizeof(stData128));
                }

            }

        }

    }

//    bCloseStiFile(stCfg->sti_type);
    VDP_PRINT("VDP_FUNC_SendCoef exit!\n");
    return (addr_base + addr_offset);
#endif
return HI_SUCCESS;
}

HI_U32 VDP_FUNC_Push128(VDP_U128_S* pstData128, HI_U32 coef_data, HI_U32 bit_len)
{

    coef_data = coef_data & (0xFFFFFFFF >> (32-bit_len));

    if(pstData128->depth < 32)
    {
        if((pstData128->depth + bit_len) <= 32)
        {
            pstData128->data0 = (coef_data << pstData128->depth) | pstData128->data0;
        }
        else
        {
            pstData128->data0 = (coef_data << pstData128->depth) | pstData128->data0;
//            pstData128->data1 = coef_data >> (pstData128->depth + bit_len - 32);
            pstData128->data1 = coef_data >> (32 - pstData128->depth%32);
        }
    }
    else if(pstData128->depth >= 32 && pstData128->depth < 64)
    {
        if((pstData128->depth + bit_len) <= 64)
        {
            pstData128->data1 = (coef_data << pstData128->depth%32) | pstData128->data1;
        }
        else
        {
            pstData128->data1 = (coef_data << pstData128->depth%32) | pstData128->data1;
//            pstData128->data2 = coef_data >> (pstData128->depth%32 + bit_len - 64);
            pstData128->data2 = coef_data >> (32 - pstData128->depth%32);
        }
    }
    else if(pstData128->depth >= 64 && pstData128->depth < 96)
    {
        if((pstData128->depth + bit_len) <= 96)
        {
            pstData128->data2 = (coef_data << pstData128->depth%32) | pstData128->data2;
        }
        else
        {
            pstData128->data2 = (coef_data << pstData128->depth%32) | pstData128->data2;
//            pstData128->data3 = coef_data >> (pstData128->depth%32 + bit_len - 96);
            pstData128->data3 = coef_data >> (32 - pstData128->depth%32);
        }
    }
    else if(pstData128->depth >= 96)
    {
        if((pstData128->depth + bit_len) <= 128)
        {
            pstData128->data3 = (coef_data << (pstData128->depth%32)) | pstData128->data3;
        }
    }

    pstData128->depth = pstData128->depth + bit_len;

    if(pstData128->depth <= 128)
    {
        return 1;
    }
    else
    {
        VDP_PRINT("Error! VDP_FUNC_Push128 depth out of range\n");
        return 0;
    }

return HI_SUCCESS;
}


HI_U32 VDP_FUNC_WriteDDR(STI_FILE_TYPE_E enStiType, FILE* fp_coef ,HI_U32 addr, VDP_U128_S * pstData128 )
{
#if 0
    HI_U32 ii=0;
    HI_U32 u32DataArr[4]={pstData128->data0,pstData128->data1,pstData128->data2,pstData128->data3};

#if COEF2FPGA
//    fprintf(fp_coef,"%08x%08x%08x%08x\n",pstData128->data3,pstData128->data2,pstData128->data1,pstData128->data0);
    for(ii=0;ii<4;ii++)
    {
        fwrite(&( u32DataArr[ii]),sizeof(HI_U32),1,fp_coef);
    }
#endif

// #ifdef PROBE_EN
    fprintf(fp_coef,"%08x%08x%08x%08x\n",pstData128->data3,pstData128->data2,pstData128->data1,pstData128->data0);
// #endif
#ifdef UT_TEST
    fprintf(fp_coef,"%08x%08x%08x%08x\n",pstData128->data3,pstData128->data2,pstData128->data1,pstData128->data0);
#else

#if VDP_COEF_PROBE_FILE_EN
    fprintf(fpStiProbeFile[enStiType],"%08x%08x%08x%08x\n",pstData128->data3,pstData128->data2,pstData128->data1,pstData128->data0);
#endif

    sc_uint<32>     uDataTemp = 0;
    for(ii=0;ii<4;ii++)
    {
        cell.addr = addr + ii*4;
        uDataTemp = u32DataArr[ii];
        cell.data = uDataTemp;

#if VDP_MMU_EN
        cell.pa_va_flag = 1;//1:PA 0:VA
#endif
        HiMemWordWr(&cell);
#if VDP_COEF_PROBE_FILE_EN
        vPrintCellData(enStiType,&cell);
#endif
#if COEF_DEBUG
        cout << hex << "cell.addr " << cell.addr << " ; cell.data " << cell.data <<endl;
#endif
    }


#endif
    return 0;

#endif
return HI_SUCCESS;
}
//add coef up sort
HI_S32 VDP_FUNC_CoefUpSortU8(const void *a, const void *b)
{
    return ((HI_S32)*(HI_U8 *)a - (HI_S32)*(HI_U8 *)b) ;
}

HI_S32 VDP_FUNC_CoefUpSortS8(const void *a, const void *b)
{
    return ((HI_S32)*(HI_S8 *)a - (HI_S32)*(HI_S8 *)b) ;
}

HI_S32 VDP_FUNC_CoefUpSortU16(const void *a, const void *b)
{
    return ((HI_S32)*(HI_U16 *)a - (HI_S32)*(HI_U16 *)b) ;
}

HI_S32 VDP_FUNC_CoefUpSortS16(const void *a, const void *b)
{
    return ((HI_S32)*(HI_S16 *)a - (HI_S32)*(HI_S16 *)b) ;
}

HI_S32 VDP_FUNC_CoefUpSortU32(const void *a, const void *b)
{
    if(*(HI_U32 *)a > *(HI_U32 *)b)
        return true;
    else if(*(HI_U32 *)a == *(HI_U32 *)b)
        return false ;
    else
        return -1;
}

HI_S32 VDP_FUNC_CoefUpSortS32(const void *a, const void *b)
{
    return (*(HI_S32 *)a - *(HI_S32 *)b) ;
}


