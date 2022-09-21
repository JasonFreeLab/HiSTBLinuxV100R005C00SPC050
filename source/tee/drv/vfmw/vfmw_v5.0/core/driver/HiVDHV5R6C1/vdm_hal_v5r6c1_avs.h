#ifndef __VDM_HAL_V5R6C1_AVS_H__
#define __VDM_HAL_V5R6C1_AVS_H__


#include "basedef.h"
#include "mem_manage.h"
#include "syn_cmn.h"

/*AVS下行消息池定义*/
typedef struct
{
    USIGN pic_width_in_mb:          9;
    USIGN rsv0:                     7;
    USIGN pic_height_in_mb:         9;
    USIGN chroma_format:            2;
    USIGN sample_precision:         2;
    USIGN rsv1:                     3;
} AVS_V5R6C1_DWNMSG_D0;

typedef struct
{
    USIGN progressive_frame:        1;
    USIGN picture_structure:        2;
    USIGN pic_coding_type:          2;
    USIGN top_field_first:          1;
    USIGN repeat_first_field:       1;
    USIGN fix_qp:                   1;
    USIGN pic_qp:                   6;
    USIGN skip_mode_flag:           1;
    USIGN ad_pred_mode_disable:     1;
    USIGN pic_ref_flag:             1;
    USIGN no_fwd_ref_flag:          1;
    UINT32 bit18_err_flag:          1;
    UINT32 rsv:                     13;
} AVS_V5R6C1_DWNMSG_D1;

typedef struct
{
    USIGN loop_flt_disable:         1;
    USIGN loop_flt_para_flag:       1;
    USIGN alpha_c_offset:           5;
    USIGN beta_offset:              5;
    USIGN rsv:                      20;
} AVS_V5R6C1_DWNMSG_D2;

typedef struct
{
    USIGN fwd_top_field_first_0:    1;
    USIGN fwd_picture_structure_0:  2;
    USIGN fwd_top_field_first_1:    1;
    USIGN fwd_picture_structure_1:  2;
    USIGN bwd_top_field_first:      1;
    USIGN bwd_picture_structure:    2;
    USIGN rsv:                      23;
} AVS_V5R6C1_DWNMSG_D3;

typedef struct
{
    USIGN bwd_address:              32;
} AVS_V5R6C1_DWNMSG_D4;

typedef struct
{
    USIGN fwd_address_0:            32;
} AVS_V5R6C1_DWNMSG_D5;

typedef struct
{
    USIGN fwd_address_1:            32;
} AVS_V5R6C1_DWNMSG_D6;

typedef struct
{
    USIGN rcn_address:             32;
} AVS_V5R6C1_DWNMSG_D7;

typedef struct
{
    USIGN col_pic_type:             1;
    USIGN rsv0:                     23;
    USIGN col_pic_struct:           2;
    USIGN rsv1:                     6;
} AVS_V5R6C1_DWNMSG_D8;

typedef struct
{
    USIGN bit_stream_address_0:     32;
} AVS_V5R6C1_DWNMSG_D9;

typedef struct
{
    USIGN bit_len_0:                24;
    USIGN bit_offset_0:             7;
    USIGN rsv:                      1;
} AVS_V5R6C1_DWNMSG_D10;

typedef struct
{
    USIGN bit_stream_address_1:     32;
} AVS_V5R6C1_DWNMSG_D11;

typedef struct
{
#if 1
    USIGN weighting_quant_flag:           1;
    USIGN chroma_quant_param_disable:    1;
    USIGN chroma_quant_param_delta_v:    6;
    USIGN chroma_quant_param_delta_u:    6;
    USIGN aec_enable:                      1;
    USIGN p_filed_enhanced_flag:          1;
    USIGN b_filed_enhanced_flag:          1;
    USIGN rsv:                             15;
#endif
#if 0
    UINT32 bit_len_1:                24;
    UINT32 bit_offset_1:             7;
    UINT32 rsv:                      1;
#endif
} AVS_V5R6C1_DWNMSG_D12;

typedef struct
{
    USIGN pmv_top_addr:         32;
} AVS_V5R6C1_DWNMSG_D13;

typedef struct
{
    USIGN topmb_intra_addr:         32;
} AVS_V5R6C1_DWNMSG_D14;

typedef struct
{
    USIGN  colpic_mv_addr:           32;
} AVS_V5R6C1_DWNMSG_D16;

typedef struct
{
    USIGN pmv_cfg_table:           32;
} AVS_V5R6C1_DWNMSG_D17_48;

typedef struct
{
    USIGN  pmv_colmb_addr:           32;
} AVS_V5R6C1_DWNMSG_D49;
typedef struct
{
    USIGN  dblk_top_addr:         32;
} AVS_V5R6C1_DWNMSG_D50;
typedef struct
{
    USIGN  sed_top_addr:         32;
} AVS_V5R6C1_DWNMSG_D51;


typedef struct
{
    UADDR bit_stream_addr_0;
    SINT32 bit_offset_0;
    SINT32 bit_len_0;
    UADDR bit_stream_addr_1;
    SINT32 bit_offset_1;
    SINT32 bit_len_1;
    SINT32 slice_start_mbn;
    SINT32 slice_end_mbn;
    UADDR next_slice_para_addr;
} AVS_V5R6C1_SLCINFO_S;


#ifdef __cplusplus
extern "C" {
#endif

SINT32 AVSHAL_V5R6C1_StartDec(AVS_DEC_PARAM_S *pAvsDecParam, SINT32 VdhId, VOID *pTask);

#ifdef __cplusplus
}
#endif


#endif //__VDM_HAL_AVS_H__
