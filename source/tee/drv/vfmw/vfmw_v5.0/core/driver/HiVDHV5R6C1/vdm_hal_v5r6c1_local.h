#ifndef _VDM_HAL_V5R6C1_LOCAL_HEADER_
#define _VDM_HAL_V5R6C1_LOCAL_HEADER_


#include "basedef.h"
#include "mem_manage.h"
#include "vfmw.h"
#include "vdm_hal.h"
#ifdef _cplusplus
extern "C" {
#endif

#define    DNR_V5R6C1_ON_LINE_OR_OFF          		0  // 1 online; 0 offline
#define    VHB_V5R6C1_STRIDE_BYTE             0x400                      // byte stride
#define    VHB_V5R6C1_STRIDE_WORD             (VHB_V5R6C1_STRIDE_BYTE/4)        // word stride
#define    SLOT_V5R6C1_WIDTH_BYTE             64                         // 64 byte
#define    SLOT_V5R6C1_WIDTH_WORD             (SLOT_V5R6C1_WIDTH_BYTE/4)        // 16 word
#define    HALF_V5R6C1_SLOT_WIDTH_WORD        8                          // 8 word
#define    MSG_V5R6C1_SLOT_HEIGHT_BYTE        (32*1024)                  // one slot height
#define    HW_V5R6C1_MEM_SIZE                 (640*1024)
#define    HW_HEVC_MEM_SIZE            			(6 * 1024 * 1024)

#define    MSG_V5R6C1_SLOT_NUM                (MAX_SLICE_SLOT_NUM + 5)
#define    UP_V5R6C1_MSG_SLOT_INDEX           0
#define    RP_V5R6C1_MSG_SLOT_INDEX           2
#define    DN_V5R6C1_MSG_SLOT_INDEX           4
#define    RP_V5R6C1_MSG_SLOT_NUM             2
#define    DN_V5R6C1_MSG_SLOT_NUM             1
#define    VDM_V5R6C1_REG_SIZE               	1024    //分配的寄存器大小
#define    RP_V5R6C1_MSG_SIZE                 (RP_V5R6C1_MSG_SLOT_NUM * MSG_SLOT_SIZE)  //分配的消息大小, WORD
#define    DN_V5R6C1_MSG_SIZE                 (DN_V5R6C1_MSG_SLOT_NUM * MSG_SLOT_SIZE)  //分配的消息大小, WORD
#define    VDM_V5R6C1_REG_USED_SIZE           512                             //实际使用的寄存器大小, WORD
#define    RP_V5R6C1_MSG_USED_SIZE            (RP_V5R6C1_MSG_SIZE)                      //实际使用的消息大小, WORD

#define    CA_V5R6C1_MN_ADDR_LEN              (64*4*20)
#define    SED_V5R6C1_TOP_ADDR_LEN            (352*96)//(64*4*96)
#define    PMV_V5R6C1_TOP_ADDR_LEN            (352*128)//(64*4*96)
#define    RCN_V5R6C1_TOP_ADDR_LEN            (352*128)//(64*4*96)
#define    ITRANS_V5R6C1_TOP_ADDR_LEN         (352*128)//(128*128)
#define    DBLK_V5R6C1_TOP_ADDR_LEN           (352*192)//(128*512)
#define    PPFD_V5R6C1_BUF_LEN_DEFAULT        (64*4*400) //(64*4*800)
#define    ONEMB_V5R6C1_PMV_COLMB_ADDR_LEN    (20*4)   //计算得知，大致需要16words/mb，现在多分配一点
#define    DNR2D_V5R6C1_BUF_LEN               (2048*1088*3/2)  //(1920*1088*3/2)

//db defines
#define    DB_V5R6C1_THR_LEASTBLKDIFF 		0    //key para, (0-128)
#define    DB_V5R6C1_ALPHA_SCALE 				8
#define    DB_V5R6C1_BETA_SCALE 				8

/************************************************************************/
/* VDM寄存器                                                            */
/************************************************************************/
//crg virtual registers
#define    VREG_CRG_VDH_CLK_SEL                         0x000
#define    VREG_CRG_VDH_CLK_SKIP                        0x001

//control registers
#define    VREG_V5R6C1_VDH_START                      0x000
#define    VREG_V5R6C1_VDH_REPAIR                     0x004
#define    VREG_V5R6C1_BASIC_CFG0                     0x008
#define    VREG_V5R6C1_BASIC_CFG1                     0x00c
#define    VREG_V5R6C1_AVM_ADDR                       0x010
#define    VREG_V5R6C1_VAM_ADDR                       0x014
#define    VREG_V5R6C1_STREAM_BASE_ADDR               0x018

//state registers
#define    VREG_V5R6C1_VDH_STATE                      0x01c
#define    VREG_V5R6C1_INT_STATE                      0x020
#define    VREG_V5R6C1_INT_MASK                       0x024
#define    VREG_V5R6C1_VCTRL_STATE                    0x028

//emar & timeout registers
#define    VREG_V5R6C1_EMAR_ID                        0x030    //0x0000FF00: no   RAM OnChip
//0x0001FF00: all  RAM OnChip
//0x0002FF00: all  RAM OnChip, except DBLK/DNR RAM
#define    VREG_V5R6C1_RPT_CNT                        0x034
#define    VREG_V5R6C1_VCTRL_TO                       0x038
#define    VREG_V5R6C1_SED_TO                         0x03c
#define    VREG_V5R6C1_ITRANS_TO                      0x040
#define    VREG_V5R6C1_PMV_TO                         0x044
#define    VREG_V5R6C1_PRC_TO                         0x048
#define    VREG_V5R6C1_RCN_TO                         0x04c
#define    VREG_V5R6C1_DBLK_TO                        0x050
#define    VREG_V5R6C1_PPFD_TO                        0x054
#define    VREG_V5R6C1_PART_DEC_OVER_INT_LEVEL        0x05c

//1d registers
#define    VREG_V5R6C1_YSTADDR_1D                     0x060
#define    VREG_V5R6C1_YSTRIDE_1D                     0x064
#define    VREG_V5R6C1_UVOFFSET_1D                    0x068

//prc registers
#define    VREG_V5R6C1_HEAD_INF_OFFSET                0x06c
#define    VREG_V5R6C1_LINE_NUM_STADDR                0x070

//10Bit extra 2bit
#define    VREG_V5R6C1_YSTRIDE_2BIT                   0x074
#define    VREG_V5R6C1_YOFFSET_2BIT                   0x078
#define    VREG_V5R6C1_UVOFFSET_2BIT                  0x07C

//ppfd registers
#define    VREG_V5R6C1_PPFD_BUF_ADDR                  0x080
#define    VREG_V5R6C1_PPFD_BUF_LEN                   0x084

#define    VREG_V5R6C1_DNR_MBINFO_STADDR  			0x090
#define    VREG_V5R6C1_REF_PIC_TYPE  					0x094
#define    VREG_V5R6C1_FF_APT_EN 						0x098
#define    VREG_V5R6C1_DOWN_CLK_CFG                   0x09C

//performance count registers
#define    VREG_V5R6C1_DEC_CYCLEPERPIC                0x0B0
#define    VREG_V5R6C1_RD_BDWIDTH_PERPIC              0x0B4
#define    VREG_V5R6C1_WR_BDWIDTH_PERPIC              0x0B8
#define    VREG_V5R6C1_RD_REQ_PERPIC                  0x0BC
#define    VREG_V5R6C1_WR_REQ_PERPIC                  0x0C0

#define    VREG_V5R6C1_MB0_QP_IN_CURR_PIC        		0x0D0
#define    VREG_V5R6C1_SWITCH_ROUNDING        		0x0D4

//axi registers
#define    VREG_V5R6C1_AXI_TEST_ST                    0x0E0
#define    VREG_V5R6C1_AXI_TEST_MODE                  0x0E4
#define    VREG_V5R6C1_AXI_TEST_ADDR                  0x0E8
#define    VREG_V5R6C1_AXI_TEST_CMD                   0x0EC
#define    VREG_V5R6C1_AXI_TEST_STA                   0x0F0
#define    VREG_V5R6C1_AXI_TEST_RAM                   0x100  //0x100~0x13F

//rpr registers
#define    VREG_V5R6C1_RPR_START                      0x140
#define    VREG_V5R6C1_RPR_SRC_YSTADDR_1D             0x144
#define    VREG_V5R6C1_RPR_SRC_YSTRIDE_1D             0x148
#define    VREG_V5R6C1_RPR_SRC_UVOFFSET_1D            0x14c
#define    VREG_V5R6C1_RPR_SRC_WIDTH_HEIGHT           0x150
#define    VREG_V5R6C1_RPR_DST_YSTADDR_1D             0x154
#define    VREG_V5R6C1_RPR_DST_YSTRIDE_1D             0x158
#define    VREG_V5R6C1_RPR_DST_UVOFFSET_1D            0x15c
#define    VREG_V5R6C1_RPR_DST_WIDTH_HEIGHT           0x160

//sed registers
#define    VREG_V5R6C1_SED_STA                        0x1000
#define    VREG_V5R6C1_SED_FSTMB                   0x1008
#define    VREG_V5R6C1_SED_LSTMB                    0x100c
#define    VREG_V5R6C1_SED_STATE1                  0x1014
#define    VREG_V5R6C1_LUMA_HISTORGRAM                0x8100
#define    VREG_V5R6C1_LUMA_SUM_LOW                   0x8180
#define    VREG_V5R6C1_LUMA_SUM_HIGH                  0x8184

//smmu
#define    VREG_V5R6C1_SMMU_SCR                       0xf000

#define    VREG_V5R6C1_SMMU_INTSTAT_S                 0xf018
#define    VREG_V5R6C1_SMMU_INTCLR_S                  0xf01c

#define    VREG_V5R6C1_SMMU_INTSTAT_NS                0xf028
#define    VREG_V5R6C1_SMMU_INTCLR_NS                 0xf02c

#ifdef ENV_SOS_KERNEL
#define    VREG_V5R6C1_SMMU_CB_TTBR                   0xf208
#define    VREG_V5R6C1_SMMU_ERR_RDADDR                0xf2f0
#define    VREG_V5R6C1_SMMU_ERR_WRADDR                0xf2f4
#define    VREG_V5R6C1_SMMU_INTMASK                   0xf010
#else
#define    VREG_V5R6C1_SMMU_CB_TTBR                   0xf20c
#define    VREG_V5R6C1_SMMU_ERR_RDADDR                0xf304
#define    VREG_V5R6C1_SMMU_ERR_WRADDR                0xf308
#define    VREG_V5R6C1_SMMU_INTMASK                   0xf020
#endif

#define    VREG_V5R6C1_SMMU_FAULT_ADDR_RD_S           0xf350
#define    VREG_V5R6C1_SMMU_FAULT_ADDR_WR_S           0xf330

#define    VREG_V5R6C1_SMMU_FAULT_ADDR_RD_NS          0xf360
#define    VREG_V5R6C1_SMMU_FAULT_ADDR_WR_NS          0Xf340

// crg
#define    VREG_V5R6C1_VDHCRG_CLKSEL                  0xf804
#define    VREG_V5R6C1_VDHCRG_RESET                   0xf80c
#define    VREG_V5R6C1_VDHCRG_RST_STATE               0xf810

/* VDM寄存器位域定义 */
typedef struct
{
    USIGN dec_start:                            1;
    USIGN reserved:                             31;
} VDH_V5R6C1_START;

typedef struct
{
    USIGN repair_start:                         1;
    USIGN reserved:                             31;
} VDH_V5R6C1_REPAIR;

typedef struct
{
    USIGN mbamt_to_dec:                         20;
    USIGN memory_clock_gating_en:               1;
    USIGN module_clock_gating_en:               1;
    USIGN marker_bit_detect_en:                 1;
    USIGN ac_last_detect_en:                    1;
    USIGN coef_idx_detect_en:                   1;
    USIGN vop_type_detect_en:                   1;
    USIGN work_mode:                            2;
    USIGN luma_sum_en:                          1;   //亮度像素和计算使能
    USIGN luma_historgam_en:                    1;   //亮度直方图计算使能
    USIGN load_qmatrix_flag:                    1;
    USIGN sec_mode_en:                          1;
} BASIC_V5R6C1_CFG0;

typedef struct
{
    USIGN mbamt_to_dec:                         20;
    USIGN memory_clock_gating_en:               1;
    USIGN module_clock_gating_en:               1;
    USIGN marker_bit_detect_en:                 1;
    USIGN ac_last_detect_en:                    1;
    USIGN coef_idx_detect_en:                   1;
    USIGN vop_type_detect_en:                   1;
    USIGN work_mode:							2;
    USIGN luma_sum_en:							1;
    USIGN luma_histogram_en:					1;
    USIGN load_qmatrix_flag:                    1;
    USIGN vdh_safe_flag:                        1;
} HEVC_BASIC_CFG0;

typedef struct
{
    USIGN video_standard:                       4;
    USIGN reserved:                           	7;
    USIGN vpss_info_en:                         1;
    USIGN mfd_mmu_en :                          1;
    USIGN uv_order_en:                          1;
    USIGN fst_slc_grp:                          1;
    USIGN mv_output_en:                         1;
    USIGN max_slcgrp_num:                       12;
    USIGN line_num_output_en:                   1;
    USIGN dblk_2d_en:                           1;
    USIGN compress_en:                          1;
    USIGN ppfd_en:                              1;
} BASIC_V5R6C1_CFG1;

typedef struct
{
    USIGN video_standard:                       4;
    USIGN reserved:                           	7;
    USIGN vpss_info_en:                         1;
    USIGN mfd_mmu_en :                          1;
    USIGN uv_order_en :                         1;
    USIGN fst_slc_grp:                          1;
    USIGN mv_output_en:                         1;
    USIGN max_slcgrp_num:                       12;
    USIGN line_num_output_en:                   1;
    USIGN vdh_2d_en:                            1;
    USIGN frm_cmp_en:                          	1;
    USIGN ppfd_en:                              1;
} HEVC_BASIC_CFG1;

typedef struct
{
    USIGN av_msg_addr:                          32;
} AVM_V5R6C1_ADDR;

typedef struct
{
    USIGN va_msg_addr:                          32;
} VAM_V5R6C1_ADDR;

typedef struct
{
    USIGN stream_base_addr:                     32;
} STREAM_V5R6C1_BASE_ADDR;

typedef struct
{
    USIGN ystaddr_1d:                           32;
} YSTADDR_V5R6C1_1D;

typedef struct
{
    USIGN ystride_1d:                           32;
} YSTRIDE_V5R6C1_1D;

typedef struct
{
    USIGN uvoffset_1d:                          32;
} UVOFFSET_V5R6C1_1D;

typedef struct
{
    USIGN head_inf_offset:                      32;
} HEAD_V5R6C1_INF_OFFSET;

typedef struct
{
    USIGN ff_apt_en:                            1;
    USIGN reserved:                             31;
} FF_V5R6C1_APT_EN;

typedef struct
{
    USIGN ref_pic_type_0:                       2;
    USIGN ref_pic_type_1:                       2;
    USIGN ref_pic_type_2:                       2;
    USIGN ref_pic_type_3:                       2;
    USIGN ref_pic_type_4:                       2;
    USIGN ref_pic_type_5:                       2;
    USIGN ref_pic_type_6:                       2;
    USIGN ref_pic_type_7:                       2;

    USIGN ref_pic_type_8:                       2;
    USIGN ref_pic_type_9:                       2;
    USIGN ref_pic_type_10:                      2;
    USIGN ref_pic_type_11:                      2;
    USIGN ref_pic_type_12:                      2;
    USIGN ref_pic_type_13:                      2;
    USIGN ref_pic_type_14:                      2;
    USIGN ref_pic_type_15:                      2;
} REF_V5R6C1_PIC_TYPE;

typedef struct
{
    USIGN decoded_slice_num:                    17;
    USIGN intrs_vdh_dec_over:                   1;
    USIGN intrs_vdh_dec_err:                    1;
    USIGN version_id:                           8;
    USIGN reserved:                             5;
} VDH_V5R6C1_STATE;
typedef struct
{
    USIGN intrs_vdm_dec_over:                   1;
    USIGN intrs_vdm_dec_err:                    1;
    USIGN reserved:                             30;
} INT_V5R6C1_STATE;

typedef struct
{
    USIGN intrs_vdm_dec_over:                   1;
    USIGN intrs_vdm_dec_err:                    1;
    USIGN reserved:                             30;
} INT_V5R6C1_MASK;

typedef struct
{
    USIGN ppfd_buf_addr:                        32;
} PPFD_V5R6C1_BUF_ADDR;

typedef struct
{
    USIGN ppfd_buf_len:                         16;
    USIGN reserved:                             16;
} PPFD_V5R6C1_BUF_LEN;

//MPEG2修补消息池
typedef struct
{
    USIGN src_luma_addr:                        32;
} VDMRPMSG_V5R6C1_D0;

typedef struct
{
    USIGN src_chroma_addr:                      32;
} VDMRPMSG_V5R6C1_D1;

typedef struct
{
    USIGN dst_luma_addr:                        32;
} VDMRPMSG_V5R6C1_D2;

typedef struct
{
    USIGN dst_chroma_addr:                      32;
} VDMRPMSG_V5R6C1_D3;

typedef struct
{
    USIGN stride_1d:                            32;
} VDMRPMSG_V5R6C1_D4;
typedef struct
{
    USIGN headInfOffset:                        32;
} VDMRPMSG_V5R6C1_D5;
typedef struct
{
    USIGN pic_width_in_mb:                      9;
    USIGN reserved0:                            7;
    USIGN pic_height_in_mb:                     9;
    USIGN reserved1:                            7;
} VDMRPMSG_V5R6C1_D6;

typedef struct
{
    USIGN total_grp_num_minus1:                 16;
    USIGN compress_flag:                        1;
    USIGN reserved0:                            3;
    USIGN dst_store_mode:                       2;
    USIGN src_load_mode:                        2;
    USIGN ctb_size:                             2;
    USIGN bit_depth:                            4;
    USIGN vdh_2d_en:							1;
	USIGN reserved1:                            1;
} VDMRPMSG_V5R6C1_D7; //BitDepth像素位深，[8,14]，非8时不压缩

typedef struct
{
    USIGN ystride_nbit:                         20;
    USIGN reserved:                             12;
} VDMRPMSG_V5R6C1_D8;  //光栅格式，nbit相邻行跨度(16byte对齐,byte单位)

typedef struct
{
    USIGN yoffset_nbit:                         32;
} VDMRPMSG_V5R6C1_D9;  //光栅格式，亮度nbit相对亮度8bit偏移(16byte对齐)

typedef struct
{
    USIGN uvoffset_nbit:                        32;
} VDMRPMSG_V5R6C1_D10;  //光栅格式，色度nbit相对nbit偏移(16byte对齐)

typedef struct
{
    USIGN reserved:                             32;
} VDMRPMSG_V5R6C1_D11;

typedef struct
{
    USIGN start_mbx:                            9;
    USIGN reserved0:                            7;
    USIGN start_mby:                            9;
    USIGN reserved1:                            7;
} VDMRPMSG_V5R6C1_D12;  // D0 in Burst1 (VDH)

typedef struct
{
    USIGN end_mbx:                              9;
    USIGN reserved0:                            7;
    USIGN end_mby:                              9;
    USIGN reserved1:                            7;
} VDMRPMSG_V5R6C1_D13;  // D1 in Burst1 (VDH)

typedef struct
{
    USIGN mbgrp_stuffing_type:                  2;
    USIGN reserved:                             30;
} VDMRPMSG_V5R6C1_D14;  // D2 in Burst1 (VDH)

typedef struct
{
    USIGN ystride_2bit:                         32;
} YSTRIDE_2BIT;

typedef struct
{
    USIGN yoffset_2bit:                         32;
} YOFFSET_2BIT;

typedef struct
{
    USIGN uvoffset_2bit:                        32;
} UVOFFSET_2BIT;

typedef struct
{
    USIGN vdh_vdec_clken:  2;
    USIGN vdh_dsp_clken :  2;
    USIGN vdh_mmu_clken :  2;
    USIGN vdh_bpd_clken :  2;
    USIGN vdh_scd_clken :  2;
    USIGN vdh_mfde_clken:  2;
    USIGN reserved      :  20;

} VDHREG_CLKSEL;

typedef struct
{
    USIGN vdh_all_srst_req :  1;
    USIGN vdh_mfde_srst_req:  1;
    USIGN vdh_scd_srst_req :  1;
    USIGN vdh_bpd_srst_req :  1;
    USIGN reserved         :  28;

} VDHREG_RESET;

typedef struct
{
    USIGN vdh_all_srst_ok :  1;
    USIGN vdh_mfde_srst_ok:  1;
    USIGN vdh_scd_srst_ok :  1;
    USIGN vdh_bpd_srst_ok :  1;
    USIGN vdh_idle        :  1;
    USIGN vdh_bpd_idle    :  1;
    USIGN vdh_scd_idle    :  1;
    USIGN vdh_mfde_idle   :  1;
    USIGN reserved        :  24;

} VDHREG_RST_STATE;


//寄存器及消息池结构体
typedef struct
{
    VDH_V5R6C1_START           *vdh_start;
    VDH_V5R6C1_REPAIR          *vdh_repair;
    BASIC_V5R6C1_CFG0          *basic_cfg0;
    BASIC_V5R6C1_CFG1          *basic_cfg1;
    AVM_V5R6C1_ADDR            *avm_addr;
    VAM_V5R6C1_ADDR            *vam_addr;
    STREAM_V5R6C1_BASE_ADDR    *stream_base_addr;
    YSTADDR_V5R6C1_1D          *ystaddr_1d;
    YSTRIDE_V5R6C1_1D          *ystride_1d;
    UVOFFSET_V5R6C1_1D         *uvoffset_1d;
    HEAD_V5R6C1_INF_OFFSET     *head_inf_offset;
    VDH_V5R6C1_STATE           *vdh_state;
    INT_V5R6C1_STATE           *int_state;
    INT_V5R6C1_MASK            *int_mask;
    REF_V5R6C1_PIC_TYPE        *RefPicType;
    FF_V5R6C1_APT_EN           *FfAptEn;
} VDMHAL_V5R6C1_REGINF_S;

typedef struct
{
    VDMRPMSG_V5R6C1_D0   *d0;
    VDMRPMSG_V5R6C1_D1   *d1;
    VDMRPMSG_V5R6C1_D2   *d2;
    VDMRPMSG_V5R6C1_D3   *d3;
    VDMRPMSG_V5R6C1_D4   *d4;

    VDMRPMSG_V5R6C1_D8   *d8[MAX_UP_MSG_SLICE_NUM];  // D0 in Burst1 (VDH)
    VDMRPMSG_V5R6C1_D9   *d9[MAX_UP_MSG_SLICE_NUM];  // D1 in Burst1 (VDH)
    VDMRPMSG_V5R6C1_D10   *d10[MAX_UP_MSG_SLICE_NUM];  // D2 in Burst1 (VDH)
} VDMHAL_V5R6C1_RPMSGINF_S;


#ifdef _cplusplus
}
#endif

#endif
