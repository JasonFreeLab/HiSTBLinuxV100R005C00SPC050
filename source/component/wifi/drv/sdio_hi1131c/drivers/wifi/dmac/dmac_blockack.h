/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_blockack.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年4月8日
  最近修改   :
  功能描述   : dmac_blockack.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年4月8日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_BLOCKACK_H__
#define __DMAC_BLOCKACK_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "hal_ext_if.h"
#include "dmac_ext_if.h"
#include "dmac_user.h"
#include "dmac_main.h"
#include "dmac_tx_bss_comm.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_BLOCKACK_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 判断一个seq num是否在发送窗口内 */
#define DMAC_BAW_WITHIN(_start, _bawsz, _seqno)      \
        ((((_seqno) - (_start)) & 4095) < (_bawsz))

/* 计算seq num到ba窗start的偏移量 */
#define DMAC_BA_INDEX(_st, _seq) (((_seq) - (_st)) & 4095)

#define DMAC_TX_BUF_BITMAP_LOG2_WORD_SIZE 5 /* log2(32) == 5 */
#define DMAC_TX_BUF_BITMAP_WORD_MASK (DMAC_TX_BUF_BITMAP_WORD_SIZE - 1)

/* TX_BUF_BITMAP_SET, TX_BUF_BITMAP_CLR -
 * Find the word by dividing the index by the number of bits per word.
 * Find the bit within the word by masking out all but the LSBs of the index.
 * Set or clear the relevant bit within the relevant word.
 */
#define DMAC_TX_BUF_BITMAP_SET(_bitmap, _idx)              \
    (_bitmap[_idx >> DMAC_TX_BUF_BITMAP_LOG2_WORD_SIZE] |= \
    (1 << (_idx & DMAC_TX_BUF_BITMAP_WORD_MASK)))

#define DMAC_TX_BUF_BITMAP_CLR(_bitmap, _idx)              \
    (_bitmap[_idx >> DMAC_TX_BUF_BITMAP_LOG2_WORD_SIZE] &= \
    ~((oal_uint32)(1 << (_idx & DMAC_TX_BUF_BITMAP_WORD_MASK))))

#define DMAC_TX_BUF_BITMAP_IS_SET(_bitmap, _idx) \
    ((_bitmap[_idx >> DMAC_TX_BUF_BITMAP_LOG2_WORD_SIZE] & \
    (1 << (_idx & DMAC_TX_BUF_BITMAP_WORD_MASK))) != 0)

/* 判断index为n 在bitmap中的bit位是否是1 */
#define DMAC_BA_ISSET(_bm, _n)        (((_n) < (DMAC_BA_BMP_SIZE)) &&          \
                                     ((_bm)[(_n) >> 5] & (1 << ((_n) & 31))))

#define DMAC_BA_MAX_SW_RETRIES  3

/* Default values for receive timeout */
#define DMAC_BA_RX_VO_TIMEOUT      40  /* 40 milliseconds */
#define DMAC_BA_RX_VI_TIMEOUT      100 /* 100 milliseconds */
#define DMAC_BA_RX_BE_TIMEOUT      100 /* 100 milliseconds */
#define DMAC_BA_RX_BK_TIMEOUT      100 /* 100 milliseconds */

#define DMAC_DUMP_BA_BITMAP_PATH "/tmp/dump_ba_bitmap.txt"

#define WLAN_AMPDU_TX_MAX_NUM_DEBUG WLAN_AMPDU_TX_MAX_NUM

#define WLAN_RX_RESET_BA_THREHOLD 32 /* BA会话未建立收到一定聚合帧发送DELBA */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern oal_uint8    g_uc_aggr_num;
/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
typedef struct
{
    oal_uint32              ul_bitmap_low;
    oal_uint32              ul_bitmap_high;
    oal_uint8               auc_bitmap[DMAC_BA_BMP_SIZE >> 3];
    oal_uint8               uc_tid;
    oal_uint8               auc_resv[3];

    oal_uint16              us_ba_ssn;
    oal_uint16              us_ba_sw_barlsn;

    dmac_ba_tx_stru        *pst_tx_ba;
}dmac_ba_tx_status_stru;

typedef struct
{
    /*类型*/
    oal_bool_enum_uint8 en_is_before_tx_track;

    /*tid队列相关信息*/
    oal_uint8       uc_tid;                    /*tid*/
    oal_uint16      us_tid_total_mpdu_num;     /*tid队列中总的mpdu数目*/
    oal_uint8       uc_tid_retry_mpdu_num;     /*tid队列中存在多少个重传mpdu*/
    oal_uint8       uc_tid_record_mpdu_num;    /*aus_tid_seqnum中记录了tid队列中多少个mpdu的seqnum*/
    oal_uint16      aus_tid_seqnum[WLAN_AMPDU_TX_MAX_NUM];        /*保存tid队列中的seqnum*/

    /*ba handle中相关信息*/
    oal_uint32      aul_bitmap[4];             /*ba handle中的bitmap*/
    oal_uint16      us_seq_start;
    oal_uint16      us_lsn;
    oal_uint16      us_baw_head;
    oal_uint16      us_baw_tail;

    union
    {
        struct
        {
            /*调度出的描述符链信息*/
            oal_uint16      aus_schedule_seqnum[WLAN_AMPDU_TX_MAX_NUM];
            oal_uint8       uc_schedule_mpdu_num;
            oal_uint8       auc_resv0[3];
        } st_schedule;
        struct
        {
            /*发送完成上报的描述符链信息*/
            oal_uint16      aus_report_seqnum[WLAN_AMPDU_TX_MAX_NUM];     /*发送完成描述符链seqnum*/
            oal_uint8       uc_report_mpdu_num;        /*发送完成的mpdu数目*/
            oal_uint8       uc_tx_status;              /*发送完成描述符状态*/
            oal_uint8       auc_resv1[2];
        } st_report;

    } un_mix_dscr;

}dmac_seq_track_stru;

typedef struct
{
    dmac_seq_track_stru             ast_seq_bitmap_log[OAM_SEQ_TRACK_NUM];
    oal_uint16                      us_track_head;
    oal_uint16                      us_track_tail;
    oal_bool_enum_uint8             en_track_off;
    oal_uint8                       uc_tid;
    oal_uint8                       uc_track_remain;
    oal_uint8                       auc_reserve[1];
}dmac_tx_ba_track_stru;
#ifdef _PRE_WLAN_FEATURE_AMPDU
//#if (_PRE_TARGET_PRODUCT_TYPE_VSPM310DMB == _PRE_CONFIG_TARGET_PRODUCT)
//extern dmac_tx_ba_track_stru g_ast_tx_ba_track[WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC][HAL_MAX_AMPDU_LUT_SIZE];
//#endif
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
extern oal_uint8 g_auc_non_proxysta_ba_lut_index_table[DMAC_Proxysta_BA_LUT_IDX_BMAP_LEN];
extern oal_uint8 g_auc_proxysta_ba_lut_index_table[DMAC_Proxysta_BA_LUT_IDX_BMAP_LEN];
#endif

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 inline函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : dmac_ba_rx_seqno_lt
 功能描述  : 判断seq1是否小于seq2
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  dmac_ba_rx_seqno_lt(oal_uint16 us_seq1, oal_uint16 us_seq2)
{
    if(((us_seq1 < us_seq2) && ((us_seq2 - us_seq1) < DMAC_BA_RX_ALLOW_MIN_SEQNO_BY_TWO)) ||
       ((us_seq1 > us_seq2) && ((us_seq1 - us_seq2) > DMAC_BA_RX_ALLOW_MAX_SEQNO_BY_TWO)))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : dmac_ba_rx_seqno_gt
 功能描述  : 判断seq1是否大于seq2
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  dmac_ba_rx_seqno_gt(oal_uint16 us_seq1, oal_uint16 us_seq2)
{
    return dmac_ba_rx_seqno_lt(us_seq2, us_seq1);
}

/*****************************************************************************
 函 数 名  : dmac_ba_seqno_lt
 功能描述  : 判断seq1是否小于seq2
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 dmac_ba_seqno_lt(oal_uint16 us_seq1, oal_uint16 us_seq2)
{
    if(((us_seq1 < us_seq2) && ((us_seq2 - us_seq1) < DMAC_BA_MAX_SEQNO_BY_TWO)) ||
       ((us_seq1 > us_seq2) && ((us_seq1 - us_seq2) > DMAC_BA_MAX_SEQNO_BY_TWO)))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : dmac_ba_seqno_gt
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  dmac_ba_seqno_gt(oal_uint16 us_seq1, oal_uint16 us_seq2)
{
    return dmac_ba_seqno_lt(us_seq2, us_seq1);
}

/*****************************************************************************
 函 数 名  : dmac_ba_rx_seqno_leq
 功能描述  : 判断seq1是否小于或等于seq2
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  dmac_ba_rx_seqno_leq(oal_uint16 us_seq1, oal_uint16 us_seq2)
{
    if(((us_seq1 <= us_seq2) && ((us_seq2 - us_seq1) < DMAC_BA_RX_ALLOW_MIN_SEQNO_BY_TWO)) ||
       ((us_seq1 > us_seq2) && ((us_seq1 - us_seq2) > DMAC_BA_RX_ALLOW_MAX_SEQNO_BY_TWO)))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : dmac_ba_rx_seqno_geq
 功能描述  : 判断seq1是否大于或等于seq2
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  dmac_ba_rx_seqno_geq(oal_uint16 us_seq1, oal_uint16 us_seq2)
{
    return dmac_ba_rx_seqno_leq(us_seq2, us_seq1);
}

/*****************************************************************************
 函 数 名  : dmac_ba_seqno_leq
 功能描述  : 判断seq1是否小于或等于seq2
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 dmac_ba_seqno_leq(oal_uint16 us_seq1, oal_uint16 us_seq2)
{
    if(((us_seq1 <= us_seq2) && ((us_seq2 - us_seq1) < DMAC_BA_MAX_SEQNO_BY_TWO)) ||
       ((us_seq1 > us_seq2) && ((us_seq1 - us_seq2) > DMAC_BA_MAX_SEQNO_BY_TWO)))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : dmac_ba_seqno_geq
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  dmac_ba_seqno_geq(oal_uint16 us_seq1, oal_uint16 us_seq2)
{
    return dmac_ba_seqno_leq(us_seq2, us_seq1);
}


/*****************************************************************************
 函 数 名  : dmac_ba_seqnum_out_window
 功能描述  : 确认seqnum是否在ba窗口外
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  dmac_ba_seqnum_out_window(dmac_ba_tx_stru *pst_ba_hdl, oal_uint16 us_seq_num)
{
    return (oal_bool_enum_uint8)(dmac_ba_seqno_gt(us_seq_num, pst_ba_hdl->us_last_seq_num) || dmac_ba_seqno_gt(pst_ba_hdl->us_baw_start, us_seq_num));
}

/*****************************************************************************
 函 数 名  : dmac_ba_seqno_bound_chk
 功能描述  :
 This function compares the given sequence number with the specified
 upper and lower bounds and returns its position relative to them.
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_ba_seqno_bound_chk(oal_uint16 us_seq_lo, oal_uint16 us_seq_hi, oal_uint16 us_seq)
{
    oal_bool_enum_uint8 en_lo_chk;
    oal_bool_enum_uint8 en_hi_chk;
    oal_uint8 uc_chk_res = 0;

    en_lo_chk  = dmac_ba_rx_seqno_leq(us_seq_lo, us_seq);
    en_hi_chk  = dmac_ba_rx_seqno_leq(us_seq, us_seq_hi);

    if((OAL_TRUE == en_lo_chk) && (OAL_TRUE == en_hi_chk))
    {
        uc_chk_res = DMAC_BA_BETWEEN_SEQLO_SEQHI;
    }
    else if(OAL_FALSE== en_hi_chk)
    {
        uc_chk_res = DMAC_BA_GREATER_THAN_SEQHI;
    }

    return uc_chk_res;
}

/*****************************************************************************
 函 数 名  : dmac_ba_get_lut_index
 功能描述  : 从BA LUT index bitmap table中获取一个BA lut index，如果BA LUT index
             bitmap table已经满了，则返回一个不可用的index
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_ba_get_lut_index(oal_uint8 *puc_ba_lut_index_table)
{
    return oal_get_lut_index(puc_ba_lut_index_table, DMAC_BA_LUT_IDX_BMAP_LEN, HAL_MAX_BA_LUT_SIZE);
}

/*****************************************************************************
 函 数 名  : dmac_ba_get_lut_index_proxysta
 功能描述  : 从两个字节中获取第一个非零bit的值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
OAL_STATIC OAL_INLINE oal_uint8  dmac_ba_get_lut_index_proxysta(oal_uint8 *puc_ba_lut_index_table)
{
    return oal_get_lut_index(puc_ba_lut_index_table, DMAC_Proxysta_BA_LUT_IDX_BMAP_LEN, HAL_PROXYSTA_MAX_BA_LUT_SIZE);
}
#endif
/*****************************************************************************
 函 数 名  : dmac_ba_get_lut_index_non_proxysta
 功能描述  : 从两个字节中获取第一个非零bit的值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
OAL_STATIC OAL_INLINE oal_uint8  dmac_ba_get_lut_index_non_proxysta(oal_uint8 *puc_ba_lut_index_table)
{
    return oal_get_lut_index(puc_ba_lut_index_table, DMAC_Non_Proxysta_BA_LUT_IDX_BMAP_LEN, HAL_PROXYSTA_MAX_BA_LUT_SIZE);
}
#endif
/*****************************************************************************
 函 数 名  : dmac_ba_del_lut_index
 功能描述  : 从BA LUT index bitmap table中删除一个BA lut index
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_ba_del_lut_index(oal_uint8 *puc_ba_lut_index_table, oal_uint8 uc_lut_index)
{
    oal_del_lut_index(puc_ba_lut_index_table, uc_lut_index);
}

/*****************************************************************************
 函 数 名  : dmac_update_txba_session_params_ap
 功能描述  : 当AMPDU的确认策略为NORMAL ACK时，需要根据AMPDU的参数更新BA的参数信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_update_txba_session_params_ap(
                dmac_tid_stru          *pst_dmac_tid,
                oal_uint8               uc_ampdu_max_num)
{
    if(OAL_PTR_NULL != pst_dmac_tid->pst_ba_tx_hdl)
    {
        /*  ampdu的最大的聚合个数不能超过BA窗的大小 */
        pst_dmac_tid->pst_ba_tx_hdl->us_baw_size = OAL_MIN(pst_dmac_tid->pst_ba_tx_hdl->us_baw_size, uc_ampdu_max_num);
    }
}

/*****************************************************************************
 函 数 名  : dmac_ba_update_start_seq_num
 功能描述  : This function updates the start sequence number for the block-ack session
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_ba_update_start_seq_num(dmac_ba_tx_stru *pst_tx_ba, oal_uint16 us_seq_num)
{
    pst_tx_ba->us_baw_start = us_seq_num;
    pst_tx_ba->us_last_seq_num = DMAC_BA_SEQ_SUB(us_seq_num, 1);
    pst_tx_ba->us_baw_head = 0;
    pst_tx_ba->us_baw_tail = 0;
}


/*****************************************************************************
 函 数 名  : dmac_ba_is_tx_data_useful
 功能描述  : This function checks whether the Transmitted Data frame is useful enough
             to be buffered.
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 dmac_ba_is_tx_data_useful(dmac_ba_tx_stru *pst_tx_ba, oal_uint16 us_seq_num)
{
   return dmac_ba_seqno_geq(us_seq_num, pst_tx_ba->us_baw_start);
}

/*****************************************************************************
 函 数 名  : dmac_reset_tx_ampdu_session
 功能描述  : 删除AMPDU的相关信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月7日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_reset_tx_ampdu_session(
                hal_to_dmac_device_stru    *pst_hal_device,
                dmac_user_stru             *pst_dmac_user,
                oal_uint8                   uc_tid)
{
    dmac_tid_stru      *pst_tid_queue;

    pst_tid_queue = &(pst_dmac_user->ast_tx_tid_queue[uc_tid]);

    OAM_INFO_LOG1(0, OAM_SF_BA, "{dmac_reset_tx_ampdu_session::tid=%d.}", uc_tid);

    /* 清空与该AMPDU相关的HT信息 */
    pst_tid_queue->st_ht_tx_hdl.uc_ampdu_max_num  = 0;
    pst_tid_queue->en_tx_mode = DMAC_TX_MODE_NORMAL;
}

/*****************************************************************************
 函 数 名  : dmac_reset_tx_ba_state_prot
 功能描述  : 删除HT相关的参数信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月7日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_reset_tx_ba_state_prot(
                hal_to_dmac_device_stru    *pst_hal_device,
                dmac_user_stru             *pst_dmac_user,
                oal_uint8                   uc_tid)

{
    dmac_reset_tx_ampdu_session(pst_hal_device, pst_dmac_user, uc_tid);
}


/*****************************************************************************
 函 数 名  : dmac_ba_addto_baw
 功能描述  : 一个子mpdu加入ampdu 更新记录seq num的窗口
 输入参数  : 无
 输出参数  : return TRUE表示是重传包 不需要再加入窗口bitmap, FALSE表示不是重传包，加入baw bitmap
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月7日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 dmac_ba_addto_baw(dmac_ba_tx_stru *pst_tx_ba_handle)
{
    oal_uint16    us_index;
    oal_uint16    us_cindex;
#if 0
    /* 重传包不需要移窗处理 */
    if (pst_tx_dscr->bit_is_retried)
    {
        return OAL_TRUE;
    }
#endif
    /*更新最后发送MPDU序列号*/
    pst_tx_ba_handle->us_last_seq_num = DMAC_BA_SEQ_ADD(pst_tx_ba_handle->us_last_seq_num, 1);

    /*获取最后发送MPDU和第一个未确定MPDU之间的序列号差值*/
    us_index = DMAC_BA_INDEX(pst_tx_ba_handle->us_baw_start, pst_tx_ba_handle->us_last_seq_num);

    /*获取bitmap中，最后发送MPDU对应位置*/
    us_cindex = (pst_tx_ba_handle->us_baw_head + us_index) & (DMAC_TID_MAX_BUFS - 1);

    /*置位bitmap中对应bit*/
    DMAC_TX_BUF_BITMAP_SET(pst_tx_ba_handle->aul_tx_buf_bitmap, us_cindex);

    if (us_index >= ((pst_tx_ba_handle->us_baw_tail - pst_tx_ba_handle->us_baw_head) & (DMAC_TID_MAX_BUFS - 1)))
    {
        pst_tx_ba_handle->us_baw_tail = us_cindex;
        OAL_INCR(pst_tx_ba_handle->us_baw_tail, DMAC_TID_MAX_BUFS);
    }

    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : dmac_ba_update_baw
 功能描述  : 更新ba窗
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_ba_update_baw(dmac_ba_tx_stru *pst_tx_ba_handle, oal_uint16 us_seqno)
{
    oal_uint16  us_index;
    oal_uint16  us_cindex;
    oal_uint32  ul_cindex;

    us_index  = DMAC_BA_INDEX(pst_tx_ba_handle->us_baw_start, us_seqno);
    us_cindex = (pst_tx_ba_handle->us_baw_head + us_index) & (DMAC_TID_MAX_BUFS - 1);
    ul_cindex = (oal_uint32)us_cindex;

    DMAC_TX_BUF_BITMAP_CLR(pst_tx_ba_handle->aul_tx_buf_bitmap, ul_cindex);

    while (pst_tx_ba_handle->us_baw_head != pst_tx_ba_handle->us_baw_tail &&
           !DMAC_TX_BUF_BITMAP_IS_SET(pst_tx_ba_handle->aul_tx_buf_bitmap, pst_tx_ba_handle->us_baw_head))
    {
        pst_tx_ba_handle->us_baw_start = DMAC_BA_SEQNO_ADD(pst_tx_ba_handle->us_baw_start, 1);
        OAL_INCR(pst_tx_ba_handle->us_baw_head, DMAC_TID_MAX_BUFS);
    }
}

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_uint32  dmac_ba_filter_serv(mac_vap_stru *pst_vap,
                                      dmac_user_stru *pst_dmac_user,
                                      dmac_rx_ctl_stru *pst_cb_ctrl,
                                      mac_ieee80211_frame_stru  *pst_frame_hdr);

extern oal_void  dmac_ba_reset_rx_handle(mac_device_stru *pst_device, dmac_ba_rx_stru **ppst_rx_ba, oal_uint8 uc_tid, dmac_user_stru *pst_dmac_user);
extern oal_void  dmac_ba_reset_tx_handle(mac_device_stru *pst_device, dmac_ba_tx_stru **ppst_tx_ba, oal_uint8 uc_tid);

extern oal_uint32  dmac_ba_timeout_fn(oal_void *p_arg);
extern oal_uint32  dmac_ba_send_bar(dmac_ba_tx_stru *pst_tx_ba_handle, dmac_user_stru *pst_dmac_user, dmac_tid_stru *pst_tid_queue);
extern oal_uint16  dmac_ba_calculate_min_mpdu_len(dmac_user_stru *pst_dmac_user, hal_tx_txop_alg_stru *pst_txop_alg);
extern oal_void dmac_ba_addto_baw_multi(dmac_ba_tx_stru *pst_tx_ba_handle, oal_uint8 uc_new_mpdu_num);
extern oal_uint32  dmac_ba_send_bar(dmac_ba_tx_stru *pst_tx_ba_handle, dmac_user_stru *pst_dmac_user, dmac_tid_stru *pst_tid_queue);
extern oal_void  dmac_move_ba_window_ahead(dmac_ba_tx_stru *pst_ba_hdl, oal_uint16 us_lsn);

extern oal_void  dmac_ba_track_tail_update(oal_uint8 uc_device_id, oal_uint8 uc_lut_idx);
extern oal_void  dmac_ba_track_ba_hander(oal_uint8 uc_device_id, dmac_ba_tx_stru *pst_tx_ba, oal_uint8 uc_tid, oal_bool_enum_uint8 en_is_before_tx);
extern oal_void  dmac_ba_track_tid_queue(oal_uint8 uc_device_id, hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_lut_idx, dmac_tid_stru *pst_tid_queue);
extern oal_void  dmac_ba_track_report_seqnum(oal_uint8 uc_device_id, oal_uint8 uc_lut_idx, oal_uint8 uc_dscr_idx, oal_uint16 us_seq_num);
extern oal_void  dmac_ba_track_schedule_seqnum(oal_uint8 uc_device_id, oal_uint8 uc_lut_idx, oal_dlist_head_stru *pst_sch_dscr_head);
extern oal_void  dmac_ba_track_stop(oal_uint8 uc_device_id, oal_uint8 uc_lut_idx);
extern oal_void dmac_nontxop_txba_num_updata(dmac_user_stru *pst_dmac_user, oal_uint8 uc_tid, oal_bool_enum_uint8 en_is_addba);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_blockack.h */
