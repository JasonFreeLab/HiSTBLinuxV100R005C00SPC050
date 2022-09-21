/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_traffic_classify.h
  版 本 号   : 初稿
  作    者   :  
  生成日期   : 2015.9.8
  最近修改   :
  功能描述   : hmac_traffic_classify.c的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015.9.8
    作    者   :  
    修改内容   : 创建文件
******************************************************************************/

#ifndef __HMAC_TRAFFIC_CLASSIFY__
#define __HMAC_TRAFFIC_CLASSIFY__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN

/*****************************************************************************
  1头文件包含
*****************************************************************************/
#include "oal_profiling.h"
#include "oal_net.h"
#include "oal_ext_if.h"
#include "frw_ext_if.h"
#include "hmac_tx_data.h"
#include "hmac_tx_amsdu.h"
#include "mac_frame.h"
#include "mac_data.h"
#include "hmac_frag.h"
#include "hmac_11i.h"
#include "hmac_user.h"

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#include "hmac_ext_if.h"
#endif
#ifdef _PRE_WLAN_FEATURE_MCAST /* 组播转单播 */
#include "hmac_m2u.h"
#endif

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
#include "hmac_proxy_arp.h"
#endif

#include "hmac_crypto_tkip.h"
#include "hmac_device.h"
#include "hmac_resource.h"

#include "hmac_tcp_opt.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_TRAFFIC_CLASSIFY_H

/*****************************************************************************
  2宏定义
*****************************************************************************/


/*****************************************************************************
  3结构体
*****************************************************************************/



/*****************************************************************************
    用户结构体: 包含了已识别业务、待识别业务序列
    这里借助hmac_user_stru，在hmac_user_stru结构体中添加宏定义字段:
    _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN
*****************************************************************************/

/*****************************************************************************
    RTP头结构体:结构体中没有包含最后的CSRC标识符
*****************************************************************************/
typedef struct 
{
    /*---------------------------------------------------------------------------
                                    RTP头结构
    -----------------------------------------------------------------------------
    |version|P|X|   CSRC数   |M|          PT           |       序号             |
    |  2bit |1|1|    4bit    |1|        7bit           |         16bit          |
    -----------------------------------------------------------------------------
    |                               时间戳 32bit                                |
    -----------------------------------------------------------------------------
    |                                 SSRC 32bit                                |
    -----------------------------------------------------------------------------
    |               CSRC 每个CSRC标识符32bit 标识符个数由CSRC数决定             |
    ---------------------------------------------------------------------------*/
    
    oal_uint8       uc_version_and_CSRC;    /* 版本号2bit、填充位(P)1bit、扩展位(X)1bit、CSRC数目4bit */
    oal_uint8       uc_payload_type;        /* 标记1bit、有效载荷类型(PT)7bit */
    oal_uint16      us_RTP_idx;             /* RTP发送序号 */
    oal_uint32      ul_RTP_time_stamp;      /* 时间戳 */
    oal_uint32      ul_SSRC;                /* SSRC */

}hmac_tx_rtp_hdr;

/*****************************************************************************
  3 函数实现
*****************************************************************************/
extern oal_void hmac_tx_traffic_classify(
                mac_tx_ctl_stru     *pst_tx_ctl,
                mac_ip_header_stru  *pst_ip, 
                oal_uint8           *puc_tid);

#endif /* endif _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif  /* end of hmac_traffic_classify.h */

