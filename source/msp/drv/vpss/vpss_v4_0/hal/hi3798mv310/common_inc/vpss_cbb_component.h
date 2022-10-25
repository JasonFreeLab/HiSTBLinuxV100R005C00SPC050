//����ÿ����Ŀ�߼��ܹ�ö�٣���������ͨ��ö�٣��㷨ģ��ö�٣�����ģ��ö�ٵ�

#ifndef __VPSS_CBB_COMPONENT_H__
#define __VPSS_CBB_COMPONENT_H__

#include "hi_type.h"

typedef enum
{
    CBB_FRAME_READ_REF = 0x0,  //ref  ref_v2
    CBB_FRAME_READ_REE,     //ree, ref_v3
    CBB_FRAME_READ_CUR,
    CBB_FRAME_READ_NX1,
    CBB_FRAME_READ_NX2,

    CBB_FRAME_WRITE_RFR, //rfr, nx2_v2 wbc
    CBB_FRAME_WRITE_CUE,  //cue, cur_v3

    CBB_FRAME_WRITE_VHD0,
    CBB_FRAME_BUTT,
} CBB_FRAME_CHANNEL_E;


typedef enum
{
    CBB_INFO_DEI_ST = 0,  //st_w, st_r
    CBB_INFO_PRJ_V,
    CBB_INFO_PRJ_H,
    CBB_INFO_RGMV,      //���ݶ�дָ������
    CBB_INFO_BLKMV,
    CBB_INFO_TNR_MAD,   //mad_w,
    CBB_INFO_SNR_MAD,   //  snr_mad_r
    CBB_INFO_STT,       //����ģ���ͳ�ƻ�дͨ��
    CBB_INFO_BUTT,
} CBB_INFO_CHANNEL_E;

typedef enum
{
    CBB_INFO_WBC_ALL,
    CBB_INFO_WBC_RWZB,  //����ָ��
    CBB_INFO_WBC_BUTT,
} CBB_CALC_INFO_E; //�߼������д��Ϣ

typedef enum
{
    CBB_FUNC_VC1,           //������������vc������id
    CBB_FUNC_VHD0_CROP,
    CBB_FUNC_VHD0_VPZME,    //����
    CBB_FUNC_VHD0_ZME,
    CBB_FUNC_VHD0_LBOX,
    CBB_FUNC_VHD0_MIRROR,
    CBB_FUNC_VHD0_FLIP,
    CBB_FUNC_VHD0_UV,
    CBB_FUNC_TUNNEL_IN,
    CBB_FUNC_TUNNEL_OUT, //����
    CBB_FUNC_TRANS,
    CBB_FUNC_SMMU,
    CBB_FUNC_ROTATION_Y,
    CBB_FUNC_ROTATION_C,
    CBB_FUNC_SPEED_UP_4PIXEL,
    CBB_FUNC_CTS10BIT,
    CBB_FUNC_BUTT,
} CBB_FUNC_E;

/*
ON/OFF
mode: user defaut random
para: pq_struct
*/



typedef enum
{
    CBB_ISR_NODE_COMPLETE = 0,  //raw_eof
    CBB_ISR_TIMEOUT,            //raw_timeout
    CBB_ISR_BUS_WRITE_ERR,      //raw_bus_w_err
    CBB_ISR_LIST_COMPLETE,      //raw_eof_end
    CBB_ISR_VHD0_TUNNEL,        //raw_vhd0_tunl
    CBB_ISR_DCMP_ERR,           //raw_dcmp_err
    CBB_ISR_BUS_READ_ERR,       //raw_bus_r_err

    CBB_ISR_SMMU_S_MIN,
    CBB_ISR_SMMU_S_TLBMISS  = CBB_ISR_SMMU_S_MIN,       //ints_tlbmiss_stat
    CBB_ISR_SMMU_S_PTW_TRANS,   //ints_ptw_trans_stat
    CBB_ISR_SMMU_S_TLBINVALID_RD,   //ints_tlbinvalid_rd_msk
    CBB_ISR_SMMU_S_TLBINVALID_WR,   //ints_tlbinvalid_wr_msk

    CBB_ISR_SMMU_NS_MIN,
    CBB_ISR_SMMU_NS_TLBMISS = CBB_ISR_SMMU_NS_MIN,  //ints_tlbmiss_stat
    CBB_ISR_SMMU_NS_PTW_TRANS,  //ints_ptw_trans_stat
    CBB_ISR_SMMU_NS_TLBINVALID_RD,  //ints_tlbinvalid_rd_msk
    CBB_ISR_SMMU_NS_TLBINVALID_WR,  //ints_tlbinvalid_wr_msk

    CBB_ISR_BUTT,
} CBB_ISR_E;

#endif
